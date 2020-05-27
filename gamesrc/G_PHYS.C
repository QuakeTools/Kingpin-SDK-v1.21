// g_phys.c

#include "g_local.h"

/*


pushmove objects do not obey gravity, and do not interact with each other or trigger fields, but block normal movement and push normal objects when they move.

onground is set for toss objects when they come to a complete rest.  it is set for steping or walking objects 

doors, plats, etc are SOLID_BSP, and MOVETYPE_PUSH
bonus items are SOLID_TRIGGER touch, and MOVETYPE_TOSS
corpses are SOLID_NOT and MOVETYPE_TOSS
crates are SOLID_BBOX and MOVETYPE_TOSS
walking monsters are SOLID_SLIDEBOX and MOVETYPE_STEP
flying/floating monsters are SOLID_SLIDEBOX and MOVETYPE_FLY

solid_edge items only clip against bsp models.

*/


/*
============
SV_TestEntityPosition

============
*/
edict_t	*SV_TestEntityPosition (edict_t *ent)
{
	trace_t	trace;
	int		mask;

	if (ent->clipmask)
		mask = ent->clipmask;
	else
		mask = MASK_SOLID;
	trace = gi.trace (ent->s.origin, ent->mins, ent->maxs, ent->s.origin, ent, mask);
	
	if (trace.startsolid)
		return g_edicts;
		
	return NULL;
}


/*
================
SV_CheckVelocity
================
*/
void SV_CheckVelocity (edict_t *ent)
{
	int		i;

//
// bound velocity
//
	for (i=0 ; i<3 ; i++)
	{
		if (ent->velocity[i] > sv_maxvelocity->value)
			ent->velocity[i] = sv_maxvelocity->value;
		else if (ent->velocity[i] < -sv_maxvelocity->value)
			ent->velocity[i] = -sv_maxvelocity->value;
	}
}

/*
=============
SV_RunThink

Runs thinking code for this frame if necessary
=============
*/
qboolean SV_RunThink (edict_t *ent)
{
	float	thinktime;

	thinktime = ent->nextthink;
	if (thinktime <= 0)
		return true;
	if (thinktime > level.time+0.001)
		return true;
	
	ent->nextthink = 0;
	
	if (!ent->think)
	{
		ent->nextthink = 0;
		return true;

		// hack to stop crash bug
		// gi.error ("NULL ent->think");
	}
	ent->think (ent);

	return false;
}

/*
==================
SV_Impact

Two entities have touched, so run their touch functions
==================
*/
void SV_Impact (edict_t *e1, trace_t *trace)
{
	edict_t		*e2;
//	cplane_t	backplane;

	e2 = trace->ent;

	if (e1->touch && e1->solid != SOLID_NOT)
		e1->touch (e1, e2, &trace->plane, trace->surface);
	
	if (e2->touch && e2->solid != SOLID_NOT)
		e2->touch (e2, e1, NULL, NULL);
}


/*
==================
ClipVelocity

Slide off of the impacting object
returns the blocked flags (1 = floor, 2 = step / wall)
==================
*/
#define	STOP_EPSILON	0.1

int ClipVelocity (vec3_t in, vec3_t normal, vec3_t out, float overbounce)
{
	float	backoff;
	float	change;
	int		i, blocked;
	
	blocked = 0;
	if (normal[2] > 0)
		blocked |= 1;		// floor
	if (!normal[2])
		blocked |= 2;		// step
	
	backoff = DotProduct (in, normal) * overbounce;

	for (i=0 ; i<3 ; i++)
	{
		change = normal[i]*backoff;
		out[i] = in[i] - change;
		if (out[i] > -STOP_EPSILON && out[i] < STOP_EPSILON)
			out[i] = 0;
	}

	return blocked;
}


/*
============
SV_FlyMove

The basic solid body movement clip that slides along multiple planes
Returns the clipflags if the velocity was modified (hit something solid)
1 = floor
2 = wall / step
4 = dead stop
============
*/
#define	MAX_CLIP_PLANES	5
int SV_FlyMove (edict_t *ent, float time, int mask)
{
	edict_t		*hit;
	int			bumpcount, numbumps;
	vec3_t		dir;
	float		d;
	int			numplanes;
	vec3_t		planes[MAX_CLIP_PLANES];
	vec3_t		primal_velocity, original_velocity, new_velocity;
	int			i, j;
	trace_t		trace;
	vec3_t		end;
	float		time_left;
	int			blocked;
	
	numbumps = 4;
	
	blocked = 0;
	VectorCopy (ent->velocity, original_velocity);
	VectorCopy (ent->velocity, primal_velocity);
	numplanes = 0;
	
	time_left = time;

	ent->groundentity = NULL;
	for (bumpcount=0 ; bumpcount<numbumps ; bumpcount++)
	{
		for (i=0 ; i<3 ; i++)
			end[i] = ent->s.origin[i] + time_left * ent->velocity[i];

		trace = gi.trace (ent->s.origin, ent->mins, ent->maxs, end, ent, mask);

		if (trace.allsolid)
		{	// entity is trapped in another solid
//			if (bumpcount == 0)
//				gi.dprintf( "WARNING: %s is stuck inside %s at (%s)\n", ent->classname, trace.ent->classname, vtos(ent->s.origin) );
			VectorCopy (vec3_origin, ent->velocity);
			return 3;
		}

		if ((trace.fraction > 0) && !(trace.ent->svflags & SVF_MONSTER) && !trace.ent->client)
		{	// covered some distance
			VectorCopy (trace.endpos, ent->s.origin);
			VectorCopy (ent->velocity, original_velocity);
			numplanes = 0;
		}
		else if ((trace.ent->svflags & SVF_MONSTER) || trace.ent->client)	// stay well clear of other characters
		{
			// Ridah, don't climb beneath another character
			if (ent->flags & FL_FLY)
			{	// abort climbing
				AngleVectors( ent->s.angles, ent->velocity, NULL, NULL );
				VectorScale( ent->velocity, -32, ent->velocity );

				ent->velocity[2] = 0;

				ent->flags &= ~FL_FLY;

				if (ent->cast_info.move_end_climb)
					ent->cast_info.currentmove = ent->cast_info.move_end_climb;
			}
			else if (ent->s.origin[2] > (trace.ent->s.origin[2] + trace.ent->maxs[2]))
			{	// they're below us, jump randomly to get off
				VectorSet (ent->velocity, random()*128, random()*128, 220);

				return 20;
			}
			else
			{
				VectorCopy (vec3_origin, ent->velocity);
			}

			return 3;
		}

		if (trace.fraction == 1)
		{
			blocked = -1;
			break;		// moved the entire distance
		}

		hit = trace.ent;

		if (trace.plane.normal[2] > 0.7)
		{
			blocked |= 1;		// floor
			if ( hit->solid == SOLID_BSP)
			{
				ent->groundentity = hit;
				ent->groundentity_linkcount = hit->linkcount;
			}
		}
		if (!trace.plane.normal[2])
		{
			blocked |= 2;		// step
		}

//
// run the impact function
//
		SV_Impact (ent, &trace);
		if (!ent->inuse)
			break;		// removed by the impact function

		
		time_left -= time_left * trace.fraction;
		
	// cliped to another plane
		if (numplanes >= MAX_CLIP_PLANES)
		{	// this shouldn't really happen
			VectorCopy (vec3_origin, ent->velocity);
			return 3;
		}

		VectorCopy (trace.plane.normal, planes[numplanes]);
		numplanes++;

//
// modify original_velocity so it parallels all of the clip planes
//
		for (i=0 ; i<numplanes ; i++)
		{
			ClipVelocity (original_velocity, planes[i], new_velocity, 1);

			for (j=0 ; j<numplanes ; j++)
				if ((j != i) && !VectorCompare (planes[i], planes[j]))
				{
					if (DotProduct (new_velocity, planes[j]) < 0)
						break;	// not ok
				}
			if (j == numplanes)
				break;
		}
		
		if (i != numplanes)
		{	// go along this plane
//gi.dprintf( "Adjusting velocity for %s\n", ent->classname );
			VectorCopy (new_velocity, ent->velocity);

// Xatrix/Ridah, help Cast members's jump up to ledges
			if ( ent->velocity[2] > 60 && !(ent->flags & FL_FLY) )
				ent->velocity[2] += (sv_gravity->value*FRAMETIME*0.5);
// Xatrix/Ridah, help grunt's jump up to ledges
		}
		else
		{	// go along the crease
			if (numplanes != 2)
			{
//				gi.dprintf ("clip velocity, numplanes == %i\n",numplanes);
				VectorCopy (vec3_origin, ent->velocity);
				return 7;
			}
			CrossProduct (planes[0], planes[1], dir);
			d = DotProduct (dir, ent->velocity);
			VectorScale (dir, d, ent->velocity);
		}

//
// if original velocity is against the original velocity, stop dead
// to avoid tiny occilations in sloping corners
//
		if (DotProduct (ent->velocity, primal_velocity) <= 0)
		{
//gi.dprintf( "Clearing velocity for occilations for %s\n", ent->classname );
			VectorCopy (vec3_origin, ent->velocity);
			return blocked;
		}
	}

// Ridah, trying to fix jumping onto ledges problem in SR1 (for example)
//	ent->velocity[0] = primal_velocity[0];
//	ent->velocity[1] = primal_velocity[1];

	return blocked;
}


/*
============
SV_AddGravity

============
*/
void SV_AddGravity (edict_t *ent)
{
	ent->velocity[2] -= ent->gravity * sv_gravity->value * FRAMETIME;
}

/*
===============================================================================

PUSHMOVE

===============================================================================
*/

/*
============
SV_PushEntity

Does not change the entities velocity at all
============
*/
trace_t SV_PushEntity (edict_t *ent, vec3_t push)
{
	trace_t	trace;
	vec3_t	start;
	vec3_t	end;
	int		mask;

	VectorCopy (ent->s.origin, start);
	VectorAdd (start, push, end);

retry:
	if (ent->clipmask)
		mask = ent->clipmask;
	else
		mask = MASK_SOLID;

	trace = gi.trace (start, ent->mins, ent->maxs, end, ent, mask);
	
	VectorCopy (trace.endpos, ent->s.origin);
	gi.linkentity (ent);

	if (trace.fraction != 1.0)
	{
		SV_Impact (ent, &trace);

		// if the pushed entity went away and the pusher is still there
		if (!trace.ent->inuse && ent->inuse)
		{
			// move the pusher back and try again
			VectorCopy (start, ent->s.origin);
			gi.linkentity (ent);
			goto retry;
		}
	}

	if (ent->inuse)
		G_TouchTriggers (ent);

	return trace;
}					


typedef struct
{
	edict_t	*ent;
	vec3_t	origin;
	vec3_t	angles;
	float	deltayaw;
} pushed_t;
pushed_t	pushed[MAX_EDICTS], *pushed_p;

edict_t	*obstacle;

/*
============
SV_Push

Objects need to be moved back on a failed push,
otherwise riders would continue to slide.
============
*/
extern void door_blocked  (edict_t *self, edict_t *other);

qboolean SV_Push (edict_t *pusher, vec3_t move, vec3_t amove)
{
	int			i, e;
	edict_t		*check, *block;
	vec3_t		mins, maxs;
	pushed_t	*p;
	vec3_t		org, org2, move2, forward, right, up;

	// clamp the move to 1/8 units, so the position will
	// be accurate for client side prediction
	for (i=0 ; i<3 ; i++)
	{
		float	temp;
		temp = move[i]*8.0;
		if (temp > 0.0)
			temp += 0.5;
		else
			temp -= 0.5;
		move[i] = 0.125 * (int)temp;
	}

	// find the bounding box
	for (i=0 ; i<3 ; i++)
	{
		mins[i] = pusher->absmin[i] + move[i];
		maxs[i] = pusher->absmax[i] + move[i];
	}

// we need this for pushing things later
	VectorSubtract (vec3_origin, amove, org);
	AngleVectors (org, forward, right, up);

// save the pusher's original position
	pushed_p->ent = pusher;
	VectorCopy (pusher->s.origin, pushed_p->origin);
	VectorCopy (pusher->s.angles, pushed_p->angles);
	if (pusher->client)
		pushed_p->deltayaw = pusher->client->ps.pmove.delta_angles[YAW];
	pushed_p++;

// move the pusher to it's final position
	VectorAdd (pusher->s.origin, move, pusher->s.origin);
	VectorAdd (pusher->s.angles, amove, pusher->s.angles);
	gi.linkentity (pusher);

// see if any solid entities are inside the final position
	check = g_edicts+1;
	for (e = 1; e < globals.num_edicts; e++, check++)
	{
		if (!check->inuse)
			continue;
		if (check->movetype == MOVETYPE_PUSH
		|| check->movetype == MOVETYPE_STOP
		|| check->movetype == MOVETYPE_NONE
		|| check->movetype == MOVETYPE_NOCLIP)
			continue;

		if (!check->area.prev)
			continue;		// not linked in anywhere

		// Ridah, dead monsters don't block door
		if (check->svflags & SVF_MONSTER && check->health <= 0)
		{
			//gi.dprintf( "SV_Push todo: Gib blocking characters\n");
			continue;
		}

		// Ridah, dead clients shouldn't block doors
		if (check->client && (check->health <= 0 || !check->solid))
			continue;

	// if the entity is standing on the pusher, it will definitely be moved
		if (check->groundentity != pusher)
		{
			// see if the ent needs to be tested
			if ( check->absmin[0] >= maxs[0]
			|| check->absmin[1] >= maxs[1]
			|| check->absmin[2] >= maxs[2]
			|| check->absmax[0] <= mins[0]
			|| check->absmax[1] <= mins[1]
			|| check->absmax[2] <= mins[2] )
				continue;

			// see if the ent's bbox is inside the pusher's final position
			if (!SV_TestEntityPosition (check))
				continue;
		}

		// Ridah, doors don't push
		if ((pusher->blocked == door_blocked) && !pusher->style && !(check->svflags & SVF_MONSTER))
		{
			// move it back
			VectorSubtract (pusher->s.origin, move, pusher->s.origin);
			VectorSubtract (pusher->s.angles, amove, pusher->s.angles);
			gi.linkentity (pusher);

			obstacle = check;
			return false;
		}

		if ((pusher->movetype == MOVETYPE_PUSH) || (check->groundentity == pusher))
		{
			// move to a visible node
			if ((check->svflags & SVF_MONSTER) && !check->goal_ent)
			{
				extern void AI_FreeAndClearGoalEnt( edict_t *self );
				node_t *node;

				if (node = NAV_GetClosestNode( check, VIS_PARTIAL, false, false ))
				{
					check->goal_ent = G_Spawn();
					check->goal_ent->owner = check;

					VectorCopy( node->origin, check->goal_ent->s.origin );

					check->goal_ent->think = AI_FreeAndClearGoalEnt;
					check->goal_ent->nextthink = level.time + 3;
					check->goal_ent->dmg_radius = 0;		// get real close to it

					if (check->cast_info.move_runwalk)
						check->cast_info.currentmove = check->cast_info.move_runwalk;
					else
						check->cast_info.currentmove = check->cast_info.move_run;

				}
			}

			// move this entity
			pushed_p->ent = check;
			VectorCopy (check->s.origin, pushed_p->origin);
			VectorCopy (check->s.angles, pushed_p->angles);
			pushed_p++;

			// try moving the contacted entity 
			VectorAdd (check->s.origin, move, check->s.origin);
			if (check->client)
			{	// FIXME: doesn't rotate monsters?
				check->client->ps.pmove.delta_angles[YAW] += amove[YAW];
				// JOSEPH 5-APR-99
				if (pusher->touch)
					pusher->touch(pusher, check, 0, 0);
				// END JOSEPH
			}

			// figure movement due to the pusher's amove
			VectorSubtract (check->s.origin, pusher->s.origin, org);
			org2[0] = DotProduct (org, forward);
			org2[1] = -DotProduct (org, right);
			org2[2] = DotProduct (org, up);
			VectorSubtract (org2, org, move2);
			VectorAdd (check->s.origin, move2, check->s.origin);

			// may have pushed them off an edge
			if (check->groundentity != pusher)
				check->groundentity = NULL;

			block = SV_TestEntityPosition (check);
			if (!block)
			{	// pushed ok
				gi.linkentity (check);
				// impact?
				continue;
			}

			// if it is ok to leave in the old position, do it
			// this is only relevent for riding entities, not pushed
			// FIXME: this doesn't acount for rotation
			VectorSubtract (check->s.origin, move, check->s.origin);
			block = SV_TestEntityPosition (check);
			if (!block)
			{
				pushed_p--;
				continue;
			}
		}
		
		// save off the obstacle so we can call the block function
		obstacle = check;

		// move back any entities we already moved
		// go backwards, so if the same entity was pushed
		// twice, it goes back to the original position
		for (p=pushed_p-1 ; p>=pushed ; p--)
		{
			VectorCopy (p->origin, p->ent->s.origin);
			VectorCopy (p->angles, p->ent->s.angles);
			if (p->ent->client)
			{
				p->ent->client->ps.pmove.delta_angles[YAW] = p->deltayaw;
			}
			gi.linkentity (p->ent);
		}
		return false;
	}

//FIXME: is there a better way to handle this?
	// see if anything we moved has touched a trigger
	for (p=pushed_p-1 ; p>=pushed ; p--)
		G_TouchTriggers (p->ent);

	return true;
}

/*
================
SV_Physics_Pusher

Bmodel objects don't interact with each other, but
push all box objects
================
*/
void SV_Physics_Pusher (edict_t *ent)
{
	vec3_t		move, amove;
	edict_t		*part, *mv;

	// if not a team captain, so movement will be handled elsewhere
	if ( ent->flags & FL_TEAMSLAVE)
		return;

	// make sure all team slaves can move before commiting
	// any moves or calling any think functions
	// if the move is blocked, all moved objects will be backed out
//retry:
	pushed_p = pushed;
	for (part = ent ; part ; part=part->teamchain)
	{
		if (part->velocity[0] || part->velocity[1] || part->velocity[2] ||
			part->avelocity[0] || part->avelocity[1] || part->avelocity[2]
			)
		{	// object is moving
			VectorScale (part->velocity, FRAMETIME, move);
			VectorScale (part->avelocity, FRAMETIME, amove);

			// JOSEPH 5-APR-99
			if (!SV_Push (part, move, amove))
				break;	// move was blocked
			// END JOSEPH
		}
	}
	if (pushed_p > &pushed[MAX_EDICTS])
		gi.error (ERR_FATAL, "pushed_p > &pushed[MAX_EDICTS], memory corrupted");

	if (part)
	{
		// the move failed, bump all nextthink times and back out moves
		for (mv = ent ; mv ; mv=mv->teamchain)
		{
			if (mv->nextthink > 0)
				mv->nextthink += FRAMETIME;
		}

		// if the pusher has a "blocked" function, call it
		// otherwise, just stay in place until the obstacle is gone
		if (part->blocked)
			part->blocked (part, obstacle);
#if 0
		// if the pushed entity went away and the pusher is still there
		if (!obstacle->inuse && part->inuse)
			goto retry;
#endif
	}
	else
	{
		// the move succeeded, so call all think functions
		for (part = ent ; part ; part=part->teamchain)
		{
			SV_RunThink (part);
		}
	}

	// JOSEPH 28-APR-99
	if (ent->classname)
	{
		if (!strcmp(ent->classname, "func_button"))
		{
			int i;
			edict_t	*e = NULL;
			
			for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
			{
				if ((e->classname) && (!strcmp(e->classname, "func_lift")) &&
					(e->target2) && (ent->target2) && (!strcmp(e->target2, ent->target2)))
				{
					ent->s.origin[2] = e->s.origin[2] + ent->handleflag;
				}
			}
		}
		else if	(!strcmp(ent->classname, "func_lift"))
		{
			int i;
			edict_t	*e = NULL;
			
			for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
			{
				if ((e->classname) && (!strcmp(e->classname, "func_button")) &&
					(e->target2) && (ent->target2) && (!strcmp(e->target2, ent->target2)))
				{
					e->s.origin[2] = ent->s.origin[2] + e->handleflag;
				}
			}
		}
	}
	// END JOSEPH
}

//==================================================================

/*
=============
SV_Physics_None

Non moving objects can only think
=============
*/
void SV_Physics_None (edict_t *ent)
{
// regular thinking
	SV_RunThink (ent);
}

/*
=============
SV_Physics_Noclip

A moving object that doesn't obey physics
=============
*/
void SV_Physics_Noclip (edict_t *ent)
{
// regular thinking
	if (!SV_RunThink (ent))
		return;
	
	VectorMA (ent->s.angles, FRAMETIME, ent->avelocity, ent->s.angles);
	VectorMA (ent->s.origin, FRAMETIME, ent->velocity, ent->s.origin);

	gi.linkentity (ent);
}

/*
==============================================================================

TOSS / BOUNCE

==============================================================================
*/

// JOSEPH 24-AUG-98
/*
=============
SV_Physics_Toss

Toss, bounce, and fly movement.  When onground, do nothing.
=============
*/
void SV_Physics_Toss (edict_t *ent)
{
	trace_t		trace;
	vec3_t		move;
	float		backoff;
	edict_t		*slave;
	qboolean	wasinwater;
	qboolean	isinwater;
	vec3_t		old_origin;

// regular thinking
	SV_RunThink (ent);

	// if not a team captain, so movement will be handled elsewhere
	if ( ent->flags & FL_TEAMSLAVE)
		return;

	if (ent->velocity[2] > 0)
		ent->groundentity = NULL;

// check for the groundentity going away
	if (ent->groundentity)
		if (!ent->groundentity->inuse)
			ent->groundentity = NULL;
// if onground, return without moving
	if ( ent->groundentity && ent->movetype != MOVETYPE_TOSS_SLIDE )
	{
		// JOSEPH 7-OCT-98
		if (ent->fallerflag)
		{
			
			// JOSEPH 22-JAN-99
			// If the object just hit the floor
			if (ent->fallingflag)
			{
				ent->fallingflag = 0;	
				if (!strcmp(ent->classname, "props_trashcanA"))
				{
					gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/trash2.wav"), 1, ATTN_NORM, 0);
				}
				else if (!strcmp(ent->classname, "props_crate"))
				{
					gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/crate2.wav"), 1, ATTN_NORM, 0);
				}
			}
			// END JOSEPH

			// Fix if sitting off center
			ent->movetype = MOVETYPE_STEP;
			think_checkedges(ent);
		}
		// END JOSEPH
		return;
	}

	VectorCopy (ent->s.origin, old_origin);

	SV_CheckVelocity (ent);

// add gravity
	if (ent->movetype != MOVETYPE_FLY
	&& ent->movetype != MOVETYPE_FLYMISSILE)
		SV_AddGravity (ent);

// move angles
	VectorMA (ent->s.angles, FRAMETIME, ent->avelocity, ent->s.angles);

// move origin
	VectorScale (ent->velocity, FRAMETIME, move);
	trace = SV_PushEntity (ent, move);
	if (!ent->inuse)
		return;

	if (trace.fraction < 1)
	{
		// RAFAEL
		if (ent->movetype == MOVETYPE_WALLBOUNCE)
			backoff = 2.0;
		// RAFAEL ( else )		
		else if (ent->movetype == MOVETYPE_BOUNCE)
			backoff = 1.5;
		// Ridah, testing
		else if (ent->velocity[2] > -120)
			backoff = 1;
		else
			backoff = 1.3;

		ClipVelocity (ent->velocity, trace.plane.normal, ent->velocity, backoff);

    	// RAFAEL
		if (ent->movetype == MOVETYPE_WALLBOUNCE)
			vectoangles (ent->velocity, ent->s.angles);

	// stop if on ground
		// RAFAEL
		if (trace.plane.normal[2] > 0.7 && ent->movetype != MOVETYPE_WALLBOUNCE && ent->movetype != MOVETYPE_TOSS_SLIDE)	// Ridah, testing
		{		
			if (ent->velocity[2] < 60 || ent->movetype != MOVETYPE_BOUNCE )
			{
				ent->groundentity = trace.ent;
				ent->groundentity_linkcount = trace.ent->linkcount;
				VectorCopy (vec3_origin, ent->velocity);
				VectorCopy (vec3_origin, ent->avelocity);
			}
		}

		// Ridah, testing
		if (trace.plane.normal[2] > 0.0 && ent->movetype == MOVETYPE_TOSS_SLIDE)	// Ridah, testing
		{
			VectorMA( ent->velocity, -0.07, ent->velocity, ent->velocity );	// add some friction
			ent->velocity[2] += ent->gravity * sv_gravity->value * FRAMETIME * trace.plane.normal[2];
			if (trace.fraction <= 0.1)
			{
				float	oldpitch;

				oldpitch = ent->s.angles[PITCH];
				vectoangles (ent->velocity, ent->s.angles);
				ent->s.angles[PITCH] = oldpitch;

				VectorCopy (vec3_origin, ent->avelocity);
				ent->avelocity[PITCH] = -300 * VectorLength(ent->velocity)/800;	// roll in direction we're going

				SV_Physics_Toss(ent);
				return;
			}
		}

//		if (ent->touch)
//			ent->touch (ent, trace.ent, &trace.plane, trace.surface);
	}
	
	
// check for water transition
	wasinwater = (ent->watertype & MASK_WATER);
	ent->watertype = gi.pointcontents (ent->s.origin);
	isinwater = ent->watertype & MASK_WATER;

	if (isinwater)
		ent->waterlevel = 1;
	else
		ent->waterlevel = 0;

	// JOSEPH 13-MAY-99
	/*if (!wasinwater && isinwater)
		gi.positioned_sound (old_origin, g_edicts, CHAN_AUTO, gi.soundindex("misc/h2ohit1.wav"), 1, 1, 0);
	else if (wasinwater && !isinwater)
		gi.positioned_sound (ent->s.origin, g_edicts, CHAN_AUTO, gi.soundindex("misc/h2ohit1.wav"), 1, 1, 0);*/
	// END JOSEPH

// move teamslaves
	for (slave = ent->teamchain; slave; slave = slave->teamchain)
	{
		VectorCopy (ent->s.origin, slave->s.origin);
		gi.linkentity (slave);
	}
}
// END JOSEPH

/*
===============================================================================

STEPPING MOVEMENT

===============================================================================
*/

/*
=============
SV_Physics_Step

Monsters freefall when they don't have a ground entity, otherwise
all movement is done with discrete steps.

This is also used for objects that have become still on the ground, but
will fall if the floor is pulled out from under them.
FIXME: is this true?
=============
*/

//FIXME: hacked in for E3 demo
#define	sv_stopspeed		100
#define sv_friction			6
#define sv_waterfriction	1

void SV_AddRotationalFriction (edict_t *ent)
{
	int		n;
	float	adjustment;

	VectorMA (ent->s.angles, FRAMETIME, ent->avelocity, ent->s.angles);
	adjustment = FRAMETIME * sv_stopspeed * sv_friction;
	for (n = 0; n < 3; n++)
	{
		if (ent->avelocity[n] > 0)
		{
			ent->avelocity[n] -= adjustment;
			if (ent->avelocity[n] < 0)
				ent->avelocity[n] = 0;
		}
		else
		{
			ent->avelocity[n] += adjustment;
			if (ent->avelocity[n] > 0)
				ent->avelocity[n] = 0;
		}
	}
}

// JOSEPH 24-AUG-98

void SV_Physics_Step (edict_t *ent)
{
	qboolean	wasonground;
	qboolean	hitsound = false;
	float		*vel;
	float		speed, newspeed, control;
	float		friction;
	edict_t		*groundentity;
	int			mask;
	int			retval;
	vec3_t		oldpos;

	// BEGIN:	Xatrix/Ridah
	vec3_t	old_vel;
	// END:		Xatrix/Ridah

	// Joseph
	if (ent->fallerflag)
	{
		// Fix if sitting off center
		think_checkedges(ent);
	}
	
	// airborn monsters should always check for ground
	if (!ent->groundentity)
		M_CheckGround (ent);

	groundentity = ent->groundentity;

	SV_CheckVelocity (ent);

	if (groundentity)
		wasonground = true;
	else
		wasonground = false;
		
	if (ent->avelocity[0] || ent->avelocity[1] || ent->avelocity[2])
		SV_AddRotationalFriction (ent);

	// add gravity except:
	//   flying monsters
	//   swimming monsters who are in the water
	if (! wasonground)
		if (!(ent->flags & FL_FLY))
			if (!((ent->flags & FL_SWIM) && (ent->waterlevel > 2)))
			{
				if (ent->velocity[2] < sv_gravity->value*-0.1)
					hitsound = true;
// Ridah, 1-may-99, disabled this to prevent guys getting stuck in water
//				if (ent->waterlevel == 0)
					SV_AddGravity (ent);
			}
/*
	// friction for flying monsters that have been given vertical velocity
	if ((ent->flags & FL_FLY) && (ent->velocity[2] != 0))
	{
		speed = fabs(ent->velocity[2]);
		control = speed < sv_stopspeed ? sv_stopspeed : speed;
		friction = sv_friction/3;
		newspeed = speed - (FRAMETIME * control * friction);
		if (newspeed < 0)
			newspeed = 0;
		newspeed /= speed;
		ent->velocity[2] *= newspeed;
	}
*/
	// friction for flying monsters that have been given vertical velocity
	if ((ent->flags & FL_SWIM) && (ent->velocity[2] != 0))
	{
		speed = fabs(ent->velocity[2]);
		control = speed < sv_stopspeed ? sv_stopspeed : speed;
		newspeed = speed - (FRAMETIME * control * sv_waterfriction * ent->waterlevel);
		if (newspeed < 0)
			newspeed = 0;
		newspeed /= speed;
		ent->velocity[2] *= newspeed;
	}

	if (ent->velocity[2] || ent->velocity[1] || ent->velocity[0])
	{
		// apply friction
		// let dead monsters who aren't completely onground slide
		if ((wasonground) || (ent->flags & (FL_SWIM|FL_FLY)))
			if (!(ent->health <= 0.0 && !M_CheckBottom(ent)))
			{
				vel = ent->velocity;
				speed = sqrt(vel[0]*vel[0] +vel[1]*vel[1]);
				if (speed)
				{
					friction = sv_friction;

					control = speed < sv_stopspeed ? sv_stopspeed : speed;
					newspeed = speed - FRAMETIME*control*friction;

					if (newspeed < 0)
						newspeed = 0;
					newspeed /= speed;

					vel[0] *= newspeed;
					vel[1] *= newspeed;
				}
			}

		// BEGIN:	Xatrix/Ridah
		// JOSEPH 26-APR-99
		if ((ent->svflags & SVF_MONSTER) || (ent->monsterprop))
		// END JOSEPH
		{
//			if (ent->cast_info.aiflags & AI_PLAYERCLIP)
				mask = MASK_PLAYERSOLID | CONTENTS_MONSTERCLIP;
//			else
//				mask = MASK_MONSTERSOLID;
		}
		else
			mask = MASK_SOLID;

		VectorCopy (ent->velocity, old_vel);
		// END:		Xatrix/Ridah

		VectorCopy (ent->s.origin, oldpos );

		retval = SV_FlyMove (ent, FRAMETIME, mask);

#if 0	// leave this here for now.

		// Ridah, HACK... sometimes they get stuck, we should debug this properly when we get the time
		if (!ValidBoxAtLoc( ent->s.origin, ent->mins, ent->maxs, ent, MASK_SOLID ))
		{	// move back to old position and clear velocity
			int iter=0;

			VectorCopy (oldpos, ent->s.origin);
			VectorClear (ent->velocity);

			// find a good position
			while (!ValidBoxAtLoc( ent->s.origin, ent->mins, ent->maxs, ent, MASK_SOLID ))
			{
				VectorAdd( ent->s.origin, tv((random()-0.5) * 64, (random()-0.5) * 64, (random()-0.5) * 64), ent->s.origin );

				if (++iter > 10)
					break;
			}

//			if (iter <= 4)
//			{	// make sure they're on the ground
//				M_droptofloor( ent );
//			}

			goto exit_vel_check;		// get out of here?
		}
#endif

		// BEGIN:	Xatrix/Ridah
		if (!ent->groundentity || (ent->flags & FL_FLY))
		{
			node_t	*land_node;

			// Ridah, prevent guys getting stuck trying to jump
			if (VectorDistance( ent->s.origin, oldpos ) < 1 && !ent->groundentity && (ent->last_onground < (level.time - 2)))
			{
				ent->velocity[0] = crandom() * 300;
				ent->velocity[1] = crandom() * 300;

				if (ent->velocity[2] < -200)
					ent->velocity[2] = -200;

				ent->velocity[2] += random() * 350;

				ent->nav_data.goal_index = 0;
				ent->last_onground = level.time;
			}

			if (ent->velocity[2] > 80 && retval != 20)
			{	// while rising, maintain XY velocity
				ent->velocity[0] = old_vel[0];
				ent->velocity[1] = old_vel[1];
			}

			// see if we've gone passed the landing position
			if (	!(ent->flags & FL_FLY)
				&&	(retval == -1) && (ent->nav_data.goal_index)
				&&	(land_node = level.node_data->nodes[ent->nav_data.goal_index-1]))
//				&&	(land_node->node_type & NODE_LANDING))
			{
				vec3_t	unit_vel, goal_dir, goal_vec;
				float	vel_scale, dist;

				VectorSubtract( land_node->origin, ent->s.origin, goal_vec );
				goal_vec[2] = 0;
				dist = VectorNormalize2( goal_vec, goal_dir );

				if (dist > 16)
				{

					VectorCopy( ent->velocity, unit_vel );
					unit_vel[2] = 0;
					vel_scale = VectorNormalize( unit_vel );

					if (DotProduct( unit_vel, goal_dir ) < 0.8)
					{	// we've either gone passed, or need some correction
						vec3_t new_pos;
						float	old_z;

						if (VectorLength( goal_vec ) < 40)
						{
							new_pos[0] = land_node->origin[0];
							new_pos[1] = land_node->origin[1];
							new_pos[2] = ent->s.origin[2];

							if (ValidBoxAtLoc( new_pos, ent->mins, ent->maxs, ent, MASK_PLAYERSOLID | MASK_MONSTERSOLID ))
							{	// move there, it's safe, and clear velocity
								VectorCopy( new_pos, ent->s.origin );
								ent->velocity[0] = ent->velocity[1] = 0;

								goto exit_vel_check;
							}
						}

						// we need to adjust our velocity
						if (land_node->origin[2] < (ent->s.origin[2] - 64))
						{
							old_z = ent->velocity[2];
							VectorScale( goal_dir, vel_scale, ent->velocity );
							ent->velocity[2] = old_z;
						}
						
					}

				}
			}	

			if (	(ent->flags & FL_FLY)
				&&	((land_node = level.node_data->nodes[ent->nav_data.goal_index-1]) || ((ent->flags &= ~FL_FLY) && false))
				/*&&	(land_node->node_type & NODE_LANDING)*/)
			{	// if climbing ladder, and we're reached the landing position, stop

				// Ridah, 8-jun-99, make sure dog's don't climb ladders
				if (!ent->gender)
				{
					goto abort_climb;
				}

				if (ent->s.origin[2] > land_node->origin[2])
				{
//gi.dprintf( "-> end of climb\n" );
//					VectorSubtract( land_node->origin, ent->s.origin, ent->velocity );
					AngleVectors( ent->s.angles, ent->velocity, NULL, NULL );
					ent->velocity[2] = 0;
					VectorNormalize( ent->velocity );
					VectorScale( ent->velocity, 96, ent->velocity );

					ent->velocity[2] = 200;

					ent->flags &= ~FL_FLY;
					ent->nav_data.goal_index = 0;		// look for a new node
					ent->nav_data.cache_node = -1;

					if (ent->cast_info.move_end_climb)
						ent->cast_info.currentmove = ent->cast_info.move_end_climb;
				}
				else
				{
					trace_t tr;
					vec3_t	end, goal_vec;

					VectorSubtract( land_node->origin, ent->s.origin, goal_vec );

					ent->velocity[0] = goal_vec[0];
					ent->velocity[1] = goal_vec[1];
					ent->velocity[2] = 120;

					// if another character is above us, abort
					VectorCopy( ent->s.origin, end );
					end[2] += 128;
					tr = gi.trace( ent->s.origin, ent->mins, ent->maxs, end, ent, MASK_PLAYERSOLID | MASK_MONSTERSOLID );
					
					if ((tr.fraction < 1) && (tr.ent->svflags & SVF_MONSTER))
					{

abort_climb:

						AngleVectors( ent->s.angles, goal_vec, NULL, NULL );
						VectorScale( goal_vec, -64, ent->velocity );
						ent->flags &= ~FL_FLY;
						ent->nav_data.goal_index = 0;

						if (ent->cast_info.move_end_climb)
						{
							ent->cast_info.currentmove = ent->cast_info.move_end_climb;
						}
						else if (ent->cast_info.move_jump)
						{
							ent->cast_info.currentmove = ent->cast_info.move_jump;
						}
					}
					else if (ent->s.origin[2] > (land_node->origin[2] - 48))
					{	// we're near the top, stopping climbing anim
//gi.dprintf( "near end of climb\n" );
						if (ent->cast_info.move_end_climb)
							ent->cast_info.currentmove = ent->cast_info.move_end_climb;

						// add some forward momentum
						AngleVectors( ent->s.angles, goal_vec, NULL, NULL );
						VectorMA( ent->velocity, 64, goal_vec, ent->velocity );
					}

				}

			}
		}

exit_vel_check:

		// END:		Xatrix/Ridah

		gi.linkentity (ent);
		G_TouchTriggers (ent);

// Note to Ryan: we can't use this because we are playing specific sounds elsewhere
/*
		if (ent->groundentity)
			if (!wasonground)
				if (hitsound)
					// BEGIN:	Xatrix/Ridah/Navigator/03-apr-1998
					if (!(ent->cast_info.move_run))
					// END:		Xatrix/Ridah/Navigator/03-apr-1998
						gi.sound (ent, 0, gi.soundindex("world/land.wav"), 1, 1, 0);
*/
	}

// regular thinking
	SV_RunThink (ent);
}

// END JOSEPH

//============================================================================
/*
================
G_RunEntity

================
*/
void G_RunEntity (edict_t *ent)
{
	if (ent->prethink)
		ent->prethink (ent);

	switch ( (int)ent->movetype)
	{
	case MOVETYPE_PUSH:
	case MOVETYPE_STOP:
		SV_Physics_Pusher (ent);
		break;
	case MOVETYPE_NONE:
		SV_Physics_None (ent);
		break;
	case MOVETYPE_NOCLIP:
		SV_Physics_Noclip (ent);
		break;
	case MOVETYPE_STEP:
		SV_Physics_Step (ent);
		break;
	case MOVETYPE_TOSS:
	case MOVETYPE_BOUNCE:
	case MOVETYPE_FLY:
	case MOVETYPE_FLYMISSILE:
	case MOVETYPE_WALLBOUNCE:
	case MOVETYPE_TOSS_SLIDE:
		SV_Physics_Toss (ent);
		break;
	default:
		gi.error ("SV_Physics: bad movetype %i", (int)ent->movetype);			
	}
}
