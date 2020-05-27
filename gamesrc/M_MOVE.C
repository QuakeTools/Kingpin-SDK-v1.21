// m_move.c -- monster movement

#include "g_local.h"

#define	STEPSIZE	28

// JOSEPH 20-AUG-98
/*
=============
M_CheckBottom

Returns false if any part of the bottom of the entity is off an edge that
is not a staircase.

=============
*/
int c_yes, c_no;

qboolean M_CheckBottom (edict_t *ent)
{
	vec3_t	mins, maxs, start, stop;
	trace_t	trace;
	int		x, y;
	float	mid, bottom, stepsize;

	stepsize = STEPSIZE;

	if (ent->fallerflag)
	{	
		vec3_t	oldmins, oldmaxs;
		
		stepsize = 8;
	
		oldmins[0] = (ent->mins[0] / 8);
		oldmins[1] = (ent->mins[1] / 8);
		oldmins[2] = (ent->mins[2]);

		oldmaxs[0] = (ent->maxs[0] / 8);
		oldmaxs[1] = (ent->maxs[1] / 8);
		oldmaxs[2] = (ent->maxs[2]);

		VectorAdd (ent->s.origin, oldmins, mins);
		VectorAdd (ent->s.origin, oldmaxs, maxs);
	}
	else
	{
		VectorAdd (ent->s.origin, ent->mins, mins);
		VectorAdd (ent->s.origin, ent->maxs, maxs);
	}

// if all of the points under the corners are solid world, don't bother
// with the tougher checks
// the corners must be within 16 of the midpoint
	start[2] = mins[2] - 1;
	for	(x=0 ; x<=1 ; x++)
		for	(y=0 ; y<=1 ; y++)
		{
			start[0] = x ? maxs[0] : mins[0];
			start[1] = y ? maxs[1] : mins[1];
			if (gi.pointcontents (start) != CONTENTS_SOLID)
				goto realcheck;
		}

	c_yes++;
	return true;		// we got out easy

realcheck:
	c_no++;
//
// check it for real...
//
	start[2] = mins[2];
	
// the midpoint must be within 16 of the bottom
	start[0] = stop[0] = (mins[0] + maxs[0])*0.5;
	start[1] = stop[1] = (mins[1] + maxs[1])*0.5;
	stop[2] = start[2] - 2*stepsize;				// Ridah, this was changed from STEPSIZE, which is why we must initialize it at the top
	trace = gi.trace (start, vec3_origin, vec3_origin, stop, ent, MASK_MONSTERSOLID);

	if (trace.fraction == 1.0)
		return false;
	mid = bottom = trace.endpos[2];
	
// the corners must be within 16 of the midpoint	
	for	(x=0 ; x<=1 ; x++)
		for	(y=0 ; y<=1 ; y++)
		{
			start[0] = stop[0] = x ? maxs[0] : mins[0];
			start[1] = stop[1] = y ? maxs[1] : mins[1];
			
			trace = gi.trace (start, vec3_origin, vec3_origin, stop, ent, MASK_MONSTERSOLID);
			
			if (trace.fraction != 1.0 && trace.endpos[2] > bottom)
				bottom = trace.endpos[2];
			if (trace.fraction == 1.0 || mid - trace.endpos[2] > stepsize)
				return false;
		}

	c_yes++;
	return true;
}
// END JOSEPH

// JOSEPH 7-OCT-98
void think_checkedges (edict_t *ent)
{
	vec3_t	mins, maxs, start, stop;
	trace_t	trace;
	int		x, y;
	float	mid, bottom, stepsize;
	vec3_t	oldmins, oldmaxs;
	int		currentcorner, fall;		
	
	stepsize = 8;
	fall = 0;

	// JOSEPH 25-SEP-98
	/*if ((ent->s.origin[0] != ent->s.old_origin[0]) ||
		(ent->s.origin[1] != ent->s.old_origin[1]) ||
		(ent->s.origin[2] != ent->s.old_origin[2]))*/
	{
		// Set to floor angles
		vec3_t	avec, stop;
		trace_t	trace;
			
		VectorCopy(ent->s.origin, stop);
		stop[2] -= 16*2;

		trace = gi.trace (ent->s.origin, ent->mins, ent->maxs, stop, ent, MASK_MONSTERSOLID);
		if (trace.fraction < 1)
		{
			VectorCopy (trace.plane.normal, avec);
			avec[0] = acos(trace.plane.normal[2])/M_PI*180;
			avec[2] = atan2(trace.plane.normal[1], trace.plane.normal[0])/M_PI*180;
			avec[1] = ent->s.angles[1];
			
			if (avec[2] == 180)
			{
				avec[0] = -avec[0];
				avec[2] = 0; 
			}
			else if (avec[2] == 90)
			{
				avec[2] = avec[0];
				avec[0] = 0; 
			}
			else if (avec[2] == -90)
			{
				avec[2] = -avec[0];
				avec[0] = 0; 
			}

			VectorCopy (avec, ent->s.angles);
		}
	}

	/*if (ent->s.angles[0] > 20 || ent->s.angles[2] > 20 ||
		ent->s.angles[0] < -20 || ent->s.angles[2] < -20)
	{
		// Slope slide
		think_slide (ent);	
	}*/

	oldmins[0] = (ent->mins[0] /8);
	oldmins[1] = (ent->mins[1] /8);
	oldmins[2] = (ent->mins[2]);

	oldmaxs[0] = (ent->maxs[0] /8);
	oldmaxs[1] = (ent->maxs[1] /8);
	oldmaxs[2] = (ent->maxs[2]);

	VectorAdd (ent->s.origin, oldmins, mins);
	VectorAdd (ent->s.origin, oldmaxs, maxs);

	// if all of the points under the corners are solid world, don't bother
	// with the tougher checks
	// the corners must be within 16 of the midpoint
	start[2] = mins[2] - 1;
	for	(x=0 ; x<=1 ; x++)
		for	(y=0 ; y<=1 ; y++)
		{
			start[0] = x ? maxs[0] : mins[0];
			start[1] = y ? maxs[1] : mins[1];
			if (gi.pointcontents (start) != CONTENTS_SOLID)
				goto realcheck;
		}

	return;	// we got out easy

realcheck:
	//
	// check it for real...
	//
	start[2] = mins[2];
	
	// the midpoint must be within 16 of the bottom
	start[0] = stop[0] = (mins[0] + maxs[0])*0.5;
	start[1] = stop[1] = (mins[1] + maxs[1])*0.5;
	stop[2] = start[2] - 2*stepsize;
	trace = gi.trace (start, vec3_origin, vec3_origin, stop, ent, MASK_MONSTERSOLID);

	//if (trace.fraction == 1.0)
	//	return false;
	mid = bottom = trace.endpos[2];
	
	// the corners must be within 16 of the midpoint	
	for	(x=0 ; x<=1 ; x++)
	{
		for	(y=0 ; y<=1 ; y++)
		{
			start[0] = stop[0] = x ? maxs[0] : mins[0];
			start[1] = stop[1] = y ? maxs[1] : mins[1];
			
			trace = gi.trace (start, vec3_origin, vec3_origin, stop, ent, MASK_MONSTERSOLID);
			
			if (trace.fraction != 1.0 && trace.endpos[2] > bottom)
				bottom = trace.endpos[2];
			if (trace.fraction == 1.0 || mid - trace.endpos[2] > stepsize)
			{
				fall = 1;
			}
		}
	}

	if (fall)
	{
		vec3_t	move, forward, right, up, newvec;
		int speed = 140;
		int movesize = 1;
		float randmove2 = 0; //(random()-0.5)/2;
		float randmove =  0; //(random()-0.5);
		int	  nocorner[4] = {0, 0, 0, 0};
		
		// Stop any drag sound
		ent->s.sound = 0;
		
		oldmins[0] = (ent->mins[0]);
		oldmins[1] = (ent->mins[1]);
		oldmins[2] = (ent->mins[2]);

		oldmaxs[0] = (ent->maxs[0]);
		oldmaxs[1] = (ent->maxs[1]);
		oldmaxs[2] = (ent->maxs[2]);

		VectorAdd (ent->s.origin, oldmins, mins);
		VectorAdd (ent->s.origin, oldmaxs, maxs);
		
		currentcorner = 0;
		
		for	(x=0 ; x<=1 ; x++)
		{
			for	(y=0 ; y<=1 ; y++)
			{
				currentcorner++;
				
				start[0] = stop[0] = x ? maxs[0] : mins[0];
				start[1] = stop[1] = y ? maxs[1] : mins[1];
				
				trace = gi.trace (start, vec3_origin, vec3_origin, stop, ent, MASK_MONSTERSOLID);
				
				if (trace.fraction != 1.0 && trace.endpos[2] > bottom)
					bottom = trace.endpos[2];
				if (trace.fraction == 1.0 || mid - trace.endpos[2] > stepsize)
				{
					nocorner[currentcorner] = 1;
				}
			}
		}
		
		VectorClear(move);
		
		if (nocorner[1])
		{
			VectorSet(newvec, -1.0, -1, 0);
			VectorAdd(move, newvec ,move);
		}
		if (nocorner[2])
		{
			VectorSet(newvec, -1, 1, 0);
			VectorAdd(move, newvec ,move);
		}
		if (nocorner[3])
		{
			VectorSet(newvec, 1, -1.0, 0);
			VectorAdd(move, newvec ,move);
		}
		if (nocorner[0])
		{
			VectorSet(newvec, 1, 1, 0);
			VectorAdd(move, newvec ,move);
		}					 

		// JOSEPH 17-MAY-99
		if (!ent->pullingflag)
		{
			AngleVectors (move, forward, right, up);

			VectorScale (move, speed, ent->velocity);
			VectorMA (ent->velocity, 85, up, ent->velocity);
			ent->movetype = MOVETYPE_TOSS;
		}
		// END JOSEPH
		
		// Object is falling
		ent->fallingflag = 1;
			
		ent->groundentity = NULL;
	}
}
// END JOSEPH

// JOSEPH 24-AUG-98
void think_slide (edict_t *ent)
{
	vec3_t	mins, maxs, start, stop;
	trace_t	trace;
	int		x, y;
	float	mid, bottom, stepsize;
	vec3_t	oldmins, oldmaxs;
    int		nocorner[4];
	int		currentcorner, fall;		
	
	stepsize = 1;
	fall = 0;

	oldmins[0] = (ent->mins[0] / 8);
	oldmins[1] = (ent->mins[1] / 8);
	oldmins[2] = (ent->mins[2]);

	oldmaxs[0] = (ent->maxs[0] / 8);
	oldmaxs[1] = (ent->maxs[1] / 8);
	oldmaxs[2] = (ent->maxs[2]);

	VectorAdd (ent->s.origin, oldmins, mins);
	VectorAdd (ent->s.origin, oldmaxs, maxs);

	// if all of the points under the corners are solid world, don't bother
	// with the tougher checks
	// the corners must be within 16 of the midpoint
	start[2] = mins[2] - 1;
	for	(x=0 ; x<=1 ; x++)
		for	(y=0 ; y<=1 ; y++)
		{
			start[0] = x ? maxs[0] : mins[0];
			start[1] = y ? maxs[1] : mins[1];
			if (gi.pointcontents (start) != CONTENTS_SOLID)
				goto realcheck;
		}

	return;	// we got out easy

realcheck:
	//
	// check it for real...
	//
	start[2] = mins[2];
	
	// the midpoint must be within 16 of the bottom
	start[0] = stop[0] = (mins[0] + maxs[0])*0.5;
	start[1] = stop[1] = (mins[1] + maxs[1])*0.5;
	stop[2] = start[2] - 2*stepsize;
	trace = gi.trace (start, vec3_origin, vec3_origin, stop, ent, MASK_MONSTERSOLID);

	//if (trace.fraction == 1.0)
	//	return false;
	mid = bottom = trace.endpos[2];
	
	currentcorner = 0;

	// the corners must be within 16 of the midpoint	
	for	(x=0 ; x<=1 ; x++)
	{
		for	(y=0 ; y<=1 ; y++)
		{
			currentcorner++;
			
			start[0] = stop[0] = x ? maxs[0] : mins[0];
			start[1] = stop[1] = y ? maxs[1] : mins[1];
			
			trace = gi.trace (start, vec3_origin, vec3_origin, stop, ent, MASK_MONSTERSOLID);
			
			if (trace.fraction != 1.0 && trace.endpos[2] > bottom)
				bottom = trace.endpos[2];
			if (trace.fraction == 1.0 || mid - trace.endpos[2] > stepsize)
			{
				nocorner[currentcorner] = 1;			
				fall = 1;
			}
		}
	}

	if (fall)
	{
		vec3_t	move, forward, right, up, endorigin;
		trace_t	trace;
		int speed = 4;
		int movesize = 1;
		float randmove = (random()-0.5)/3;
		float randmove2 = (random())/3;

		if (nocorner[2] && nocorner[3])
		{
			VectorSet(move, movesize+randmove2, randmove, 0);
		}
		else if (nocorner[3] && nocorner[1])
		{
			VectorSet(move, randmove, (-movesize)+randmove2, 0);
		}
		else if (nocorner[1] && nocorner[0])
		{
			VectorSet(move, (-movesize)+randmove2, randmove, 0);
		}
		else if (nocorner[0] && nocorner[2])
		{
			VectorSet(move, randmove, movesize+randmove2, 0);
		}
		else if (nocorner[2])
		{
			VectorSet(move, movesize+randmove, movesize+randmove2, 0);
		}
		else if (nocorner[0])
		{
			VectorSet(move, (-movesize)+randmove, movesize+randmove2, 0);
		}
		else if (nocorner[3])
		{
			VectorSet(move, movesize+randmove, (-movesize)+randmove2, 0);
		}
		else if (nocorner[1])
		{
			VectorSet(move, (-movesize)+randmove, (-movesize)+randmove, 0);
		}

		AngleVectors (move, forward, right, up);

		VectorScale (move, speed, move);
		VectorAdd(ent->s.origin, move, endorigin);
		trace = gi.trace (ent->s.origin, ent->mins, ent->maxs, endorigin, ent, MASK_MONSTERSOLID);	
		VectorCopy(trace.endpos, ent->s.origin);
		//ent->movetype = MOVETYPE_STEP;
		ent->groundentity = NULL;
	}
}
// END JOSEPH

// JOSEPH 24-AUG-98
/*
=============
SV_movestep

Called by monster program code.
The move will be adjusted for slopes and stairs, but if the move isn't
possible, no move is done, false is returned, and
pr_global_struct->trace_normal is set to the normal of the blocking wall
=============
*/
//FIXME since we need to test end position contents here, can we avoid doing
//it again later in catagorize position?
qboolean SV_movestep (edict_t *ent, vec3_t move, qboolean relink)
{
	float		dz;
	vec3_t		oldorg, neworg, end;
	trace_t		trace;
	int			i;
	float		stepsize;
	vec3_t		test;
	int			contents;

// BEGIN:	Xatrix/Ridah/Navigator/14-apr-1998
	int			mask = MASK_MONSTERSOLID;

	if (ent->cast_info.aiflags & AI_PLAYERCLIP)
		mask = MASK_PLAYERSOLID;
	else if (ent->flags & FL_RESPAWN)	// used for moveout command
		mask = MASK_SOLID;
// END:		Xatrix/Ridah/Navigator/14-apr-1998

// try the move	
	VectorCopy (ent->s.origin, oldorg);
	VectorAdd (ent->s.origin, move, neworg);

// flying monsters don't step up
	if ( ent->flags & (FL_SWIM | FL_FLY) )
	{
	// try one move with vertical motion, then one without
		for (i=0 ; i<2 ; i++)
		{
			VectorAdd (ent->s.origin, move, neworg);
			if (i == 0 && ent->enemy)
			{
				if (!ent->goalentity)
					ent->goalentity = ent->enemy;
				dz = ent->s.origin[2] - ent->goalentity->s.origin[2];
				if (ent->goalentity->client)
				{
					if (dz > 40)
						neworg[2] -= 8;
					if (!((ent->flags & FL_SWIM) && (ent->waterlevel < 2)))
						if (dz < 30)
							neworg[2] += 8;
				}
				else
				{
						if (dz > 8)
							neworg[2] -= 8;
						else if (dz > 0)
							neworg[2] -= dz;
						else if (dz < -8)
							neworg[2] += 8;
						else
							neworg[2] += dz;
					
				}
			}
			
// BEGIN:	Xatrix/Ridah/Navigator/14-apr-1998		(use modified mask for Grunts)
			trace = gi.trace (ent->s.origin, ent->mins, ent->maxs, neworg, ent, mask);
// END:		Xatrix/Ridah/Navigator/14-apr-1998

			// fly monsters don't enter water voluntarily
			if (ent->flags & FL_FLY)
			{
				if (!ent->waterlevel)
				{
					test[0] = trace.endpos[0];
					test[1] = trace.endpos[1];
					test[2] = trace.endpos[2] + ent->mins[2] + 1;
					contents = gi.pointcontents(test);
					if (contents & MASK_WATER)
						return false;
				}
			}

			// swim monsters don't exit water voluntarily
			if (ent->flags & FL_SWIM)
			{
				if (ent->waterlevel < 2)
				{
					test[0] = trace.endpos[0];
					test[1] = trace.endpos[1];
					test[2] = trace.endpos[2] + ent->mins[2] + 1;
					contents = gi.pointcontents(test);
					if (!(contents & MASK_WATER))
						return false;
				}
			}

			if (trace.fraction == 1)
			{
				VectorCopy (trace.endpos, ent->s.origin);
				if (relink)
				{
					gi.linkentity (ent);
					G_TouchTriggers (ent);
				}
				return true;
			}
			
			if (!ent->enemy)
				break;
		}
		
		return false;
	}

// push down from a step height above the wished position
	if (!(ent->cast_info.aiflags & AI_NOSTEP))
		stepsize = STEPSIZE;
	else
		stepsize = 1;

// BEGIN: Xatrix/Ridah/Navigator/03-apr-1998
	if (ent->nav_data.goal_index && ((level.node_data->nodes[ent->nav_data.goal_index-1]->origin[2] - ent->s.origin[2]) > 0))
	{
		stepsize += 8;

		if (ent->waterlevel > 2)
			stepsize = 1;
	}
// END:   Xatrix/Ridah/Navigator/03-apr-1998

	neworg[2] += stepsize;
	VectorCopy (neworg, end);
	end[2] -= stepsize*2;

	trace = gi.trace (neworg, ent->mins, ent->maxs, end, ent, mask);

	// Ridah, tell this ent to avoid us if possible
	if ((trace.ent && trace.ent->svflags & SVF_MONSTER) && (ent->health > 0))	// Ridah, Fixes life after death bug
	{
		extern void AI_GetAvoidDirection( edict_t *self, edict_t *other );

		AI_GetAvoidDirection( trace.ent, ent );
		ent->cast_info.currentmove = ent->cast_info.move_avoid_walk;
	}

	if (trace.allsolid)
		return false;

	if (trace.startsolid)
	{
		neworg[2] -= stepsize;
		trace = gi.trace (neworg, ent->mins, ent->maxs, end, ent, mask);
		if (trace.allsolid || trace.startsolid || trace.fraction == 0)
		{
			return false;
		}
	}

// BEGIN:	Xatrix/Ridah/Navigator/03-apr-1998
	// don't let monsters walk onto other monsters
	if ((trace.fraction < 1) && (trace.ent->svflags & SVF_MONSTER))
	{
		return false;
	}
// END:		Xatrix/Ridah/Navigator/03-apr-1998

	// don't go in to lava/slime
	if (ent->waterlevel < 2)
	{
		test[0] = trace.endpos[0];
		test[1] = trace.endpos[1];
		test[2] = trace.endpos[2] + ent->mins[2] + 16;
		contents = gi.pointcontents(test);

		if (contents & (CONTENTS_LAVA|CONTENTS_SLIME))
			return false;
	}

	if (trace.fraction == 1)
	{
	// if monster had the ground pulled out, go ahead and fall
		if ( ent->flags & FL_PARTIALGROUND )
		{
			VectorAdd (ent->s.origin, move, ent->s.origin);
			if (relink)
			{
				gi.linkentity (ent);
				G_TouchTriggers (ent);
			}
			ent->groundentity = NULL;
			return true;
		}
// BEGIN: Xatrix/Ridah/Navigator/14-apr-1998
		else
		{
			float fall_dist=0;

			// never fall into water
			VectorCopy(trace.endpos, neworg);
			VectorCopy(neworg, end);
			end[2] -= 2048;

			trace = gi.trace( neworg, ent->mins, ent->maxs, end, ent, mask );

			test[0] = trace.endpos[0];
			test[1] = trace.endpos[1];
			test[2] = trace.endpos[2] + ent->mins[2] + 16;
			contents = gi.pointcontents(test);

			if (contents & MASK_WATER)
				return false;
			

/*
			// let them fall into water if they should be doing so
			if (	ent->waterlevel
				||	(ent->count && level.node_data->nodes[ent->count-1]->waterlevel)
				||	(ent->goalentity && ent->goalentity->waterlevel))
			{
				VectorAdd (ent->s.origin, move, ent->s.origin);
				VectorScale(move, 10, ent->velocity);
				ent->groundentity = NULL;

				return true;
			}
*/

			if (	(ent->nav_data.goal_index && ((fall_dist = level.node_data->nodes[ent->nav_data.goal_index-1]->origin[2] - ent->s.origin[2]) < 0)) 
				||	(ent->goalentity && (( fall_dist = ent->goalentity->s.origin[2] - ent->s.origin[2]) < 0)))
			{
//				VectorCopy(trace.endpos, neworg);
				VectorCopy(neworg, end);
				end[2] += (fall_dist - 48);

				trace = gi.trace( neworg, ent->mins, ent->maxs, end, ent, mask );

				if (trace.fraction < 1)
				{	// start to fall
					VectorAdd (ent->s.origin, move, ent->s.origin);
					VectorScale(move, 5, ent->velocity);
					ent->groundentity = NULL;

					return true;
				}
			}
		}
// END:   Xatrix/Ridah/Navigator/23-mar-1998

		// walked off an edge
		return false;
	}

	// check point traces down for dangling corners
	VectorCopy (trace.endpos, ent->s.origin);
	
	if (!M_CheckBottom (ent))
	{
		if ( ent->flags & FL_PARTIALGROUND )
		{	// entity had floor mostly pulled out from underneath it
			// and is trying to correct
			if (relink)
			{
				gi.linkentity (ent);
				G_TouchTriggers (ent);
			}
			return true;
		}
		
		// Joseph
		if (!ent->fallerflag)
		{	
			// Ridah, don't bother checking all corners
//			VectorCopy (oldorg, ent->s.origin);
//			return false;
		}
		else 
		{
			vec3_t	forward, right, up;
			int speed = 140;
			
			// JOSEPH 7-OCT-98
			// Stop any drag sound
			ent->s.sound = 0;
			
			// Object is falling
			ent->fallingflag = 1;
			// END JOSEPH
			
			// JOSEPH 17-MAY-99
			if (!ent->pullingflag)
			{
				AngleVectors (move, forward, right, up);

				VectorScale (move, speed, ent->velocity);
				VectorMA (ent->velocity, 100, up, ent->velocity);
				ent->movetype = MOVETYPE_TOSS;
			}
			// END JOSEPH

			// JOSEPH 17-MAY-99
			//VectorAdd (ent->s.origin, move, ent->s.origin);
			// END JOSEPH
			if (relink)
			{
				gi.linkentity (ent);
				G_TouchTriggers (ent);
			}
			ent->groundentity = NULL;
			return true;
		}
	}

	if ( ent->flags & FL_PARTIALGROUND )
	{
		ent->flags &= ~FL_PARTIALGROUND;
	}
	ent->groundentity = trace.ent;
	ent->groundentity_linkcount = trace.ent->linkcount;

// the move is ok
	if (relink)
	{
		gi.linkentity (ent);
		G_TouchTriggers (ent);
	}
	return true;
}
// END JOSEPH

//============================================================================

/*
===============
M_ChangeYaw

===============
*/
void M_ChangeYaw (edict_t *ent)
{
	float	ideal;
	float	current;
	float	move;
	float	speed;
	
	current = anglemod(ent->s.angles[YAW]);
	ideal = ent->ideal_yaw;

	if (current == ideal)
		return;

	move = ideal - current;
	speed = ent->yaw_speed;

	// Ridah, turn faster if we have an enemy
	if (ent->enemy)
	{
		speed *= 4;
		if (speed > 80)
			speed = 80;
	}
	else if (ent->cast_info.currentmove && (ent->cast_info.currentmove->frame->dist))
	{	// dependant on speed
		speed *= (fabs(ent->cast_info.currentmove->frame->dist) / 16.0);
		if (speed > 60)
			speed = 60;
		if (speed < 20)
			speed = 20;

//if (ent->name)
//gi.dprintf( "%s yaw = %2.1f\n", ent->name, speed );
	}

	if (ideal > current)
	{
		if (move >= 180)
			move = move - 360;
	}
	else
	{
		if (move <= -180)
			move = move + 360;
	}
	if (move > 0)
	{
		if (move > speed)
			move = speed;
	}
	else
	{
		if (move < -speed)
			move = -speed;
	}
	
	ent->s.angles[YAW] = anglemod (current + move);
}

void M_ChangeYawOld (edict_t *ent)
{
	float ideal;
	float current;
	float move;
	float speed;

	current = anglemod (ent->s.angles[YAW]);
	ideal = ent->ideal_yaw;

	if (current == ideal)
		return;

	move = ideal - current;
	speed = ent->yaw_speed;

	if (ideal > current)
	{
		if (move >= 180)
			move = move - 360;
	}
	else
	{
		if (move <= -180)
			move = move + 360;
	}
	if (move > 0)
	{
		if (move > speed)
			move = speed;
	}
	else
	{
		if (move < -speed)
			move = -speed;
	}

	ent->s.angles[YAW] = anglemod (current + move);
}

/*
======================
SV_StepDirection

Turns to the movement direction, and walks the current distance if
facing it.

======================
*/
qboolean SV_StepDirection (edict_t *ent, float yaw, float dist)
{
	vec3_t		move, oldorigin;
	float		delta;
	
	ent->ideal_yaw = yaw;
	M_ChangeYaw (ent);
	
	yaw = yaw*M_PI*2 / 360;
	move[0] = cos(yaw)*dist;
	move[1] = sin(yaw)*dist;
	move[2] = 0;

	VectorCopy (ent->s.origin, oldorigin);
	if (SV_movestep (ent, move, false))
	{
		delta = ent->s.angles[YAW] - ent->ideal_yaw;
		if (delta > 45 && delta < 315)
		{		// not turned far enough, so don't take the step
			VectorCopy (oldorigin, ent->s.origin);
		}
		gi.linkentity (ent);
		G_TouchTriggers (ent);
		return true;
	}
	gi.linkentity (ent);
	G_TouchTriggers (ent);
	return false;
}

/*
======================
SV_FixCheckBottom

======================
*/
void SV_FixCheckBottom (edict_t *ent)
{
	ent->flags |= FL_PARTIALGROUND;
}



/*
================
SV_NewChaseDir

================
*/
#define	DI_NODIR	-1
void SV_NewChaseDir (edict_t *actor, edict_t *enemy, float dist)
{
	float	deltax,deltay;
	float	d[3];
	float	tdir, olddir, turnaround;

	//FIXME: how did we get here with no enemy
	if (!enemy)
		return;

	olddir = anglemod( (int)(actor->ideal_yaw/45)*45 );
	turnaround = anglemod(olddir - 180);

	deltax = enemy->s.origin[0] - actor->s.origin[0];
	deltay = enemy->s.origin[1] - actor->s.origin[1];
	if (deltax>10)
		d[1]= 0;
	else if (deltax<-10)
		d[1]= 180;
	else
		d[1]= DI_NODIR;
	if (deltay<-10)
		d[2]= 270;
	else if (deltay>10)
		d[2]= 90;
	else
		d[2]= DI_NODIR;

// try direct route
	if (d[1] != DI_NODIR && d[2] != DI_NODIR)
	{
		if (d[1] == 0)
			tdir = d[2] == 90 ? 45 : 315;
		else
			tdir = d[2] == 90 ? 135 : 215;
			
		if (tdir != turnaround && SV_StepDirection(actor, tdir, dist))
			return;
	}

// try other directions
	if ( ((rand()&3) & 1) ||  abs(deltay)>abs(deltax))
	{
		tdir=d[1];
		d[1]=d[2];
		d[2]=tdir;
	}

	if (d[1]!=DI_NODIR && d[1]!=turnaround 
	&& SV_StepDirection(actor, d[1], dist))
			return;

	if (d[2]!=DI_NODIR && d[2]!=turnaround
	&& SV_StepDirection(actor, d[2], dist))
			return;

/* there is no direct path to the player, so pick another direction */

	if (olddir!=DI_NODIR && SV_StepDirection(actor, olddir, dist))
			return;

	if (rand()&1) 	/*randomly determine direction of search*/
	{
		for (tdir=0 ; tdir<=315 ; tdir += 45)
			if (tdir!=turnaround && SV_StepDirection(actor, tdir, dist) )
					return;
	}
	else
	{
		for (tdir=315 ; tdir >=0 ; tdir -= 45)
			if (tdir!=turnaround && SV_StepDirection(actor, tdir, dist) )
					return;
	}

	if (turnaround != DI_NODIR && SV_StepDirection(actor, turnaround, dist) )
			return;

	actor->ideal_yaw = olddir;		// can't move

// if a bridge was pulled out from underneath a monster, it may not have
// a valid standing position at all

	if (!M_CheckBottom (actor))
		SV_FixCheckBottom (actor);
}

/*
======================
SV_CloseEnough

======================
*/
qboolean SV_CloseEnough (edict_t *ent, edict_t *goal, float dist)
{
	int		i;
	
	for (i=0 ; i<3 ; i++)
	{
		if (goal->absmin[i] > ent->absmax[i] + dist)
			return false;
		if (goal->absmax[i] < ent->absmin[i] - dist)
			return false;
	}
	return true;
}


/*
======================
M_MoveToGoal
======================
*/
void M_MoveToGoal (edict_t *ent, float dist)
{
	edict_t		*goal;
	
	goal = ent->goalentity;

	if (!ent->groundentity && !(ent->flags & (FL_FLY|FL_SWIM)))
		return;

// if the next step hits the enemy, return immediately
	if (ent->enemy &&  SV_CloseEnough (ent, ent->enemy, dist) )
		return;

// bump around...
	if ( (rand()&3)==1 || !SV_StepDirection (ent, ent->ideal_yaw, dist))
	{
		if (ent->inuse)
			SV_NewChaseDir (ent, goal, dist);
	}
}


/*
===============
M_walkmove
===============
*/
qboolean M_walkmove (edict_t *ent, float yaw, float dist)
{
	vec3_t	 move;
	qboolean rval;
//	qboolean changezval = false;

	if (ent->svflags & SVF_MONSTER && dist >= 28)
		dist = 28;
		// gi.dprintf ("%s: tried to move %5.2f\n", ent->classname, dist);
	
	if (!ent->groundentity && !(ent->flags & (FL_FLY|FL_SWIM)))
		return false;

	yaw = yaw*M_PI*2 / 360;
	
	move[0] = cos(yaw)*dist;
	move[1] = sin(yaw)*dist;
	move[2] = 0;
/*
	if (ent->maxs[2] == DUCKING_MAX_Z)
	{
		ent->maxs[2] = 8;//4; // Ridah, as requested
		changezval = true;
	}
*/	
	rval = SV_movestep(ent, move, true);
/*
	if (changezval)
	{
		ent->maxs[2] = DUCKING_MAX_Z;
	}
*/		
		
	return rval;
}
