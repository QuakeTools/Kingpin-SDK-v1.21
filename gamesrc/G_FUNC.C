
#include "g_local.h"
#include "g_func.h"

/*
=========================================================

  PLATS

  movement options:

  linear
  smooth start, hard stop
  smooth start, smooth stop

  start
  end
  acceleration
  speed
  deceleration
  begin sound
  end sound
  target fired when reaching end
  wait at end

  object characteristics that use move segments
  ---------------------------------------------
  movetype_push, or movetype_stop
  action when touched
  action when blocked
  action when used
	disabled?
  auto trigger spawning


=========================================================
*/

//
// Support routines for movement (changes in origin using velocity)
//

void Move_Done (edict_t *self)
{
	edict_t *ent;

// BEGIN:	Xatrix/Ridah/Navigator/08-apr-1998
	ent = self->goalentity;

	//VectorCopy (self->moveinfo.end_origin, self->s.origin);
	
	// spawn some nodes, if this entity hasn't been routed
	if ((!ent || (!ent->nav_data.goal_index && (ent->wait < 0 || ent->wait > 0.1))) && nav_dynamic->value && (level.node_data->node_count < (MAX_NODES-2)))
	{
		edict_t	*trav=NULL;
		node_t	*top_node;
		vec3_t	move_vec, start_org;
		int		rval;
		route_t	route;

		// record the ending position
		VectorCopy(self->s.origin, self->cast_info.saved_goal);

		// is there a human standing on this plat?
		while (trav = G_Find(trav, FOFS(classname), "player"))
		{
			if (trav->groundentity == self)
			{	// this player is standing on us, so drop a node

				// find the players position at the plat's previous position
				VectorSubtract(self->cast_info.saved_goal, self->cast_info.last_sighting, move_vec);

				// see if we can get to here from the start position

				// find a node close to us to use for destination checking
				top_node = NAV_GetClosestNode( trav, VIS_PARTIAL, true, false );

				if (!top_node)
					goto drop_node;

					// temporarily move the platform to the bottom position
					VectorCopy(self->cast_info.last_sighting, self->s.origin);
					gi.linkentity(self);

				VectorSubtract( trav->s.origin, move_vec, trav->s.origin );
				gi.linkentity(trav);

				rval = NAV_Route_EntityToNode( trav, NULL, top_node, VIS_PARTIAL, true, false, &route );

				VectorAdd( trav->s.origin, move_vec, trav->s.origin );
				gi.linkentity(trav);

					// move the platform back
					VectorCopy(self->cast_info.saved_goal, self->s.origin);
					gi.linkentity(self);

				if (rval)
					break;		// already a route here

drop_node:

				VectorSubtract(trav->s.origin, move_vec, start_org);

				// drop the end position                          (LANDING so other nodes don't see us, but we can see them)
				NAV_CreateNode( trav, trav->s.origin, vec3_origin, NODE_LANDING, -1, trav->waterlevel);
				top_node = trav->active_node_data->nodes[trav->active_node_data->node_count - 1];

					// temporarily move the platform to the bottom position
					VectorCopy(self->cast_info.last_sighting, self->s.origin);
					gi.linkentity(self);

				NAV_CreateNode( trav, start_org, vec3_origin, NODE_PLAT, top_node->index, trav->waterlevel);

					// move the platform back
					VectorCopy(self->cast_info.saved_goal, self->s.origin);
					gi.linkentity(self);

				if (ent)
					ent->nav_data.goal_index = true;	// tell this path_corner to ignore future NAV tests for new nodes
				trav->nav_build_data->current_node->goal_ent = self;
				self->nav_data.cache_node = (int)(top_node->index);

				// resume checking from the player's current position
				trav->nav_build_data->current_node = top_node;

				break;
			}
		}
	}
// END:		Xatrix/Ridah/Navigator/08-apr-1998

	VectorClear (self->velocity);
	self->moveinfo.endfunc (self);
}

void Move_Final (edict_t *ent)
{
	if (ent->moveinfo.remaining_distance == 0)
	{
		Move_Done (ent);
		return;
	}

	VectorScale (ent->moveinfo.dir, ent->moveinfo.remaining_distance / FRAMETIME, ent->velocity);

	ent->think = Move_Done;
	ent->nextthink = level.time + FRAMETIME;
}

void Move_Begin (edict_t *ent)
{
	float	frames;

	if ((ent->moveinfo.speed * FRAMETIME) >= ent->moveinfo.remaining_distance)
	{
		Move_Final (ent);
		return;
	}
	VectorScale (ent->moveinfo.dir, ent->moveinfo.speed, ent->velocity);
	frames = floor((ent->moveinfo.remaining_distance / ent->moveinfo.speed) / FRAMETIME);
	ent->moveinfo.remaining_distance -= frames * ent->moveinfo.speed * FRAMETIME;
	ent->nextthink = level.time + (frames * FRAMETIME);
	ent->think = Move_Final;
}

void Think_AccelMove (edict_t *ent);

void Move_Calc (edict_t *ent, vec3_t dest, void(*func)(edict_t*))
{
	VectorClear (ent->velocity);
	VectorSubtract (dest, ent->s.origin, ent->moveinfo.dir);
	ent->moveinfo.remaining_distance = VectorNormalize (ent->moveinfo.dir);
	ent->moveinfo.endfunc = func;

	if (ent->moveinfo.speed == ent->moveinfo.accel && ent->moveinfo.speed == ent->moveinfo.decel)
	{
		if (level.current_entity == ((ent->flags & FL_TEAMSLAVE) ? ent->teammaster : ent))
		{
			Move_Begin (ent);
		}
		else
		{
			ent->nextthink = level.time + FRAMETIME;
			ent->think = Move_Begin;
		}
	}
	else
	{
		// accelerative
		ent->moveinfo.current_speed = 0;
		ent->think = Think_AccelMove;
		ent->nextthink = level.time + FRAMETIME;
	}
}

//
// Support routines for angular movement (changes in angle using avelocity)
//

void AngleMove_Done (edict_t *ent)
{
	VectorClear (ent->avelocity);
	ent->moveinfo.endfunc (ent);
}

void AngleMove_Final (edict_t *ent)
{
	vec3_t	move;

	if (ent->moveinfo.state == STATE_UP)
		VectorSubtract (ent->moveinfo.end_angles, ent->s.angles, move);
	else
		VectorSubtract (ent->moveinfo.start_angles, ent->s.angles, move);

	if (VectorCompare (move, vec3_origin))
	{
		AngleMove_Done (ent);
		return;
	}

	VectorScale (move, 1.0/FRAMETIME, ent->avelocity);

	ent->think = AngleMove_Done;
	ent->nextthink = level.time + FRAMETIME;
}

void AngleMove_Begin (edict_t *ent)
{
	vec3_t	destdelta;
	float	len;
	float	traveltime;
	float	frames;

	// set destdelta to the vector needed to move
	if (ent->moveinfo.state == STATE_UP)
		VectorSubtract (ent->moveinfo.end_angles, ent->s.angles, destdelta);
	else
		VectorSubtract (ent->moveinfo.start_angles, ent->s.angles, destdelta);
	
	// calculate length of vector
	len = VectorLength (destdelta);
	
	// divide by speed to get time to reach dest
	traveltime = len / ent->moveinfo.speed;

	if (traveltime < FRAMETIME)
	{
		AngleMove_Final (ent);
		return;
	}

	frames = floor(traveltime / FRAMETIME);

	// scale the destdelta vector by the time spent traveling to get velocity
	VectorScale (destdelta, 1.0 / traveltime, ent->avelocity);

	// set nextthink to trigger a think when dest is reached
	ent->nextthink = level.time + frames * FRAMETIME;
	ent->think = AngleMove_Final;
}

void AngleMove_Calc (edict_t *ent, void(*func)(edict_t*))
{
	VectorClear (ent->avelocity);
	ent->moveinfo.endfunc = func;
	if (level.current_entity == ((ent->flags & FL_TEAMSLAVE) ? ent->teammaster : ent))
	{
		AngleMove_Begin (ent);
	}
	else
	{
		ent->nextthink = level.time + FRAMETIME;
		ent->think = AngleMove_Begin;
	}
}


/*
==============
Think_AccelMove

The team has completed a frame of movement, so
change the speed for the next frame
==============
*/
#define AccelerationDistance(target, rate)	(target * ((target / rate) + 1) / 2)

void plat_CalcAcceleratedMove(moveinfo_t *moveinfo)
{
	float	accel_dist;
	float	decel_dist;

	moveinfo->move_speed = moveinfo->speed;

	if (moveinfo->remaining_distance < moveinfo->accel)
	{
		moveinfo->current_speed = moveinfo->remaining_distance;
		return;
	}

	accel_dist = AccelerationDistance (moveinfo->speed, moveinfo->accel);
	decel_dist = AccelerationDistance (moveinfo->speed, moveinfo->decel);

	if ((moveinfo->remaining_distance - accel_dist - decel_dist) < 0)
	{
		float	f;

		f = (moveinfo->accel + moveinfo->decel) / (moveinfo->accel * moveinfo->decel);
		moveinfo->move_speed = (-2 + sqrt(4 - 4 * f * (-2 * moveinfo->remaining_distance))) / (2 * f);
		decel_dist = AccelerationDistance (moveinfo->move_speed, moveinfo->decel);
	}

	moveinfo->decel_distance = decel_dist;
};

void plat_Accelerate (moveinfo_t *moveinfo)
{
	// are we decelerating?
	if (moveinfo->remaining_distance <= moveinfo->decel_distance)
	{
		if (moveinfo->remaining_distance < moveinfo->decel_distance)
		{
			if (moveinfo->next_speed)
			{
				moveinfo->current_speed = moveinfo->next_speed;
				moveinfo->next_speed = 0;
				return;
			}
			if (moveinfo->current_speed > moveinfo->decel)
				moveinfo->current_speed -= moveinfo->decel;
		}
		return;
	}

	// are we at full speed and need to start decelerating during this move?
	if (moveinfo->current_speed == moveinfo->move_speed)
		if ((moveinfo->remaining_distance - moveinfo->current_speed) < moveinfo->decel_distance)
		{
			float	p1_distance;
			float	p2_distance;
			float	distance;

			p1_distance = moveinfo->remaining_distance - moveinfo->decel_distance;
			p2_distance = moveinfo->move_speed * (1.0 - (p1_distance / moveinfo->move_speed));
			distance = p1_distance + p2_distance;
			moveinfo->current_speed = moveinfo->move_speed;
			moveinfo->next_speed = moveinfo->move_speed - moveinfo->decel * (p2_distance / distance);
			return;
		}

	// are we accelerating?
	if (moveinfo->current_speed < moveinfo->speed)
	{
		float	old_speed;
		float	p1_distance;
		float	p1_speed;
		float	p2_distance;
		float	distance;

		old_speed = moveinfo->current_speed;

		// figure simple acceleration up to move_speed
		moveinfo->current_speed += moveinfo->accel;
		if (moveinfo->current_speed > moveinfo->speed)
			moveinfo->current_speed = moveinfo->speed;

		// are we accelerating throughout this entire move?
		if ((moveinfo->remaining_distance - moveinfo->current_speed) >= moveinfo->decel_distance)
			return;

		// during this move we will accelrate from current_speed to move_speed
		// and cross over the decel_distance; figure the average speed for the
		// entire move
		p1_distance = moveinfo->remaining_distance - moveinfo->decel_distance;
		p1_speed = (old_speed + moveinfo->move_speed) / 2.0;
		p2_distance = moveinfo->move_speed * (1.0 - (p1_distance / p1_speed));
		distance = p1_distance + p2_distance;
		moveinfo->current_speed = (p1_speed * (p1_distance / distance)) + (moveinfo->move_speed * (p2_distance / distance));
		moveinfo->next_speed = moveinfo->move_speed - moveinfo->decel * (p2_distance / distance);
		return;
	}

	// we are at constant velocity (move_speed)
	return;
};

void Think_AccelMove (edict_t *ent)
{
	ent->moveinfo.remaining_distance -= ent->moveinfo.current_speed;

	if (ent->moveinfo.current_speed == 0)		// starting or blocked
		plat_CalcAcceleratedMove(&ent->moveinfo);

	plat_Accelerate (&ent->moveinfo);

	// will the entire move complete on next frame?
	if (ent->moveinfo.remaining_distance <= ent->moveinfo.current_speed)
	{
		Move_Final (ent);
		return;
	}

	VectorScale (ent->moveinfo.dir, ent->moveinfo.current_speed*10, ent->velocity);
	ent->nextthink = level.time + FRAMETIME;
	ent->think = Think_AccelMove;
}


void plat_go_down (edict_t *ent);

void plat_hit_top (edict_t *ent)
{
	if (!(ent->flags & FL_TEAMSLAVE))
	{
		if (ent->moveinfo.sound_end)
			gi.sound (ent, CHAN_NO_PHS_ADD+CHAN_VOICE, ent->moveinfo.sound_end, 1, ATTN_STATIC, 0);
		ent->s.sound = 0;
	}
	ent->moveinfo.state = STATE_TOP;

	ent->think = plat_go_down;
	ent->nextthink = level.time + 3;
}

void plat_hit_bottom (edict_t *ent)
{
	if (!(ent->flags & FL_TEAMSLAVE))
	{
		if (ent->moveinfo.sound_end)
			gi.sound (ent, CHAN_NO_PHS_ADD+CHAN_VOICE, ent->moveinfo.sound_end, 1, ATTN_STATIC, 0);
		ent->s.sound = 0;
	}
	ent->moveinfo.state = STATE_BOTTOM;
}

void plat_go_down (edict_t *ent)
{
	if (!(ent->flags & FL_TEAMSLAVE))
	{
		if (ent->moveinfo.sound_start)
			gi.sound (ent, CHAN_NO_PHS_ADD+CHAN_VOICE, ent->moveinfo.sound_start, 1, ATTN_STATIC, 0);
		ent->s.sound = ent->moveinfo.sound_middle;
	}
	ent->moveinfo.state = STATE_DOWN;
	Move_Calc (ent, ent->moveinfo.end_origin, plat_hit_bottom);
}

void plat_go_up (edict_t *ent)
{
	if (!(ent->flags & FL_TEAMSLAVE))
	{
		if (ent->moveinfo.sound_start)
			gi.sound (ent, CHAN_NO_PHS_ADD+CHAN_VOICE, ent->moveinfo.sound_start, 1, ATTN_STATIC, 0);
		ent->s.sound = ent->moveinfo.sound_middle;
	}
	ent->moveinfo.state = STATE_UP;
	Move_Calc (ent, ent->moveinfo.start_origin, plat_hit_top);
}

void plat_blocked (edict_t *self, edict_t *other)
{
	if (!(other->svflags & SVF_MONSTER) && !(other->client) )
	{
		// give it a chance to go away on it's own terms (like gibs)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, 100000, 1, 0, MOD_CRUSH);
		// if it's still there, nuke it
		if (other)
			BecomeExplosion1 (other);
		return;
	}

	// Ridah, small objects shouldn't hurt
	if (VectorDistance( self->absmin, self->absmax) > 200)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);

	if (self->moveinfo.state == STATE_UP)
		plat_go_down (self);
	else if (self->moveinfo.state == STATE_DOWN)
		plat_go_up (self);
}


void Use_Plat (edict_t *ent, edict_t *other, edict_t *activator)
{ 
	if (ent->think)
		return;		// already down
	plat_go_down (ent);
}


void Touch_Plat_Center (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
/*
// BEGIN:	Xatrix/Ridah/Navigator/07-apr-1998
if (!(other->cast_info.aiflags & AI_GRUNT))
// END:		Xatrix/Ridah/Navigator/07-apr-1998
	
	if (!other->client)
		return;
*/		
	if (other->health <= 0)
		return;

	ent = ent->enemy;	// now point at the plat, not the trigger
	
	if (ent->moveinfo.state == STATE_BOTTOM)
// BEGIN:	Xatrix/Ridah/Navigator/08-apr-1998
	{
		edict_t *character=NULL;
		int		i=0;

		// inform characters of the trigger
		while (character = level.characters[i++])
		{
			if ((!character->client) && ((other == character) || (VectorDistance(character->s.origin, other->s.origin) < 512)))
				character->target_ent = ent;
		}

		plat_go_up (ent);
	}
// END:		Xatrix/Ridah/Navigator/08-apr-1998

	else if (ent->moveinfo.state == STATE_TOP)
		ent->nextthink = level.time + 1;	// the player is still on the plat, so delay going down
}

void plat_spawn_inside_trigger (edict_t *ent)
{
	edict_t	*trigger;
	vec3_t	tmin, tmax;

//
// middle trigger
//	
	trigger = G_Spawn();
	trigger->touch = Touch_Plat_Center;
	trigger->movetype = MOVETYPE_NONE;
	trigger->solid = SOLID_TRIGGER;
	trigger->enemy = ent;
	
	tmin[0] = ent->mins[0] + 25;
	tmin[1] = ent->mins[1] + 25;
	tmin[2] = ent->mins[2];

	tmax[0] = ent->maxs[0] - 25;
	tmax[1] = ent->maxs[1] - 25;
	tmax[2] = ent->maxs[2] + 8;

	tmin[2] = tmax[2] - (ent->pos1[2] - ent->pos2[2] + st.lip);

	if (ent->spawnflags & PLAT_LOW_TRIGGER)
		tmax[2] = tmin[2] + 8;
	
	if (tmax[0] - tmin[0] <= 0)
	{
		tmin[0] = (ent->mins[0] + ent->maxs[0]) *0.5;
		tmax[0] = tmin[0] + 1;
	}
	if (tmax[1] - tmin[1] <= 0)
	{
		tmin[1] = (ent->mins[1] + ent->maxs[1]) *0.5;
		tmax[1] = tmin[1] + 1;
	}
	
	VectorCopy (tmin, trigger->mins);
	VectorCopy (tmax, trigger->maxs);

	gi.linkentity (trigger);
}


/*QUAKED func_plat (0 .5 .8) ? PLAT_LOW_TRIGGER
speed	default 150

Plats are always drawn in the extended position, so they will light correctly.

If the plat is the target of another trigger or button, it will start out disabled in the extended position until it is trigger, when it will lower and become a normal plat.

"speed"	overrides default 200.
"accel" overrides default 500
"lip"	overrides default 8 pixel lip

If the "height" key is set, that will determine the amount the plat moves, instead of being implicitly determoveinfoned by the model's height.

Set "sounds" to one of the following:
1) base fast
2) chain slow
*/
void SP_func_plat (edict_t *ent)
{
	VectorClear (ent->s.angles);
	ent->solid = SOLID_BSP;
	ent->movetype = MOVETYPE_PUSH;

	gi.setmodel (ent, ent->model);

	ent->blocked = plat_blocked;

	if (!ent->speed)
		ent->speed = 20;
	else
		ent->speed *= 0.1;

	if (!ent->accel)
		ent->accel = 5;
	else
		ent->accel *= 0.1;

	if (!ent->decel)
		ent->decel = 5;
	else
		ent->decel *= 0.1;

	if (!ent->dmg)
		ent->dmg = 2;

	if (!st.lip)
		st.lip = 8;

	// pos1 is the top position, pos2 is the bottom
	VectorCopy (ent->s.origin, ent->pos1);
	VectorCopy (ent->s.origin, ent->pos2);
	if (st.height)
		ent->pos2[2] -= st.height;
	else
		ent->pos2[2] -= (ent->maxs[2] - ent->mins[2]) - st.lip;

	ent->use = Use_Plat;

	plat_spawn_inside_trigger (ent);	// the "start moving" trigger	

	if (ent->targetname)
	{
		ent->moveinfo.state = STATE_UP;
	}
	else
	{
		VectorCopy (ent->pos2, ent->s.origin);
		gi.linkentity (ent);
		ent->moveinfo.state = STATE_BOTTOM;
	}

	ent->moveinfo.speed = ent->speed;
	ent->moveinfo.accel = ent->accel;
	ent->moveinfo.decel = ent->decel;
	ent->moveinfo.wait = ent->wait;
	VectorCopy (ent->pos1, ent->moveinfo.start_origin);
	VectorCopy (ent->s.angles, ent->moveinfo.start_angles);
	VectorCopy (ent->pos2, ent->moveinfo.end_origin);
	VectorCopy (ent->s.angles, ent->moveinfo.end_angles);

	// JOSEPH 13-MAY-99
	ent->moveinfo.sound_start = gi.soundindex ("world/plats/pt1_strt.wav");
	ent->moveinfo.sound_middle = gi.soundindex ("world/plats/pt1_mid.wav");
	ent->moveinfo.sound_end = gi.soundindex ("world/plats/pt1_end.wav");
	// END JOSEPH
}

//====================================================================

/*QUAKED func_rotating (0 .5 .8) ? START_ON REVERSE X_AXIS Y_AXIS TOUCH_PAIN STOP ANIMATED ANIMATED_FAST
You need to have an origin brush as part of this entity.  The center of that brush will be
the point around which it is rotated. It will rotate around the Z axis by default.  You can
check either the X_AXIS or Y_AXIS box to change that.

"speed" determines how fast it moves; default value is 100.
"dmg"	damage to inflict when blocked (2 default)

REVERSE will cause the it to rotate in the opposite direction.
STOP mean it will stop moving instead of pushing entities
*/

void rotating_blocked (edict_t *self, edict_t *other)
{
	// Ridah, rotating doors shouldn't hurt
	//T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);

	// tell them to back up
	if (other->svflags & SVF_MONSTER)
	{
		if (other->cast_info.move_avoid_reverse_walk)
			other->cast_info.currentmove = other->cast_info.move_avoid_reverse_walk;
	}
}

void rotating_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (self->avelocity[0] || self->avelocity[1] || self->avelocity[2])
	{
//		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);

		// tell them to back up
		if (other->svflags & SVF_MONSTER)
		{
			if (other->cast_info.move_avoid_reverse_walk)
				other->cast_info.currentmove = other->cast_info.move_avoid_reverse_walk;
		}
	}
}

void rotating_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (!VectorCompare (self->avelocity, vec3_origin))
	{
		self->s.sound = 0;
		VectorClear (self->avelocity);
		self->touch = NULL;
	}
	else
	{
		self->s.sound = self->moveinfo.sound_middle;
		VectorScale (self->movedir, self->speed, self->avelocity);
		if (self->spawnflags & 16)
			self->touch = rotating_touch;
	}
}

void SP_func_rotating (edict_t *ent)
{
	ent->solid = SOLID_BSP;
	if (ent->spawnflags & 32)
		ent->movetype = MOVETYPE_STOP;
	else
		ent->movetype = MOVETYPE_PUSH;

	// set the axis of rotation
	VectorClear(ent->movedir);
	if (ent->spawnflags & 4)
		ent->movedir[2] = 1.0;
	else if (ent->spawnflags & 8)
		ent->movedir[0] = 1.0;
	else // Z_AXIS
		ent->movedir[1] = 1.0;

	// check for reverse rotation
	if (ent->spawnflags & 2)
		VectorNegate (ent->movedir, ent->movedir);

	if (!ent->speed)
		ent->speed = 100;
	if (!ent->dmg)
		ent->dmg = 2;

//	ent->moveinfo.sound_middle = "world/doors/hydro1.wav";

	ent->use = rotating_use;
	if (ent->dmg)
		ent->blocked = rotating_blocked;

	if (ent->spawnflags & 1)
		ent->use (ent, NULL, NULL);

	if (ent->spawnflags & 64)
		ent->s.effects |= EF_ANIM_ALL;
	if (ent->spawnflags & 128)
		ent->s.effects |= EF_ANIM_ALLFAST;

	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
}

/*
======================================================================

BUTTONS

======================================================================
*/

// JOSEPH 27-MAY-99
/*QUAKED func_button (0 .5 .8) ? AUTO_OPEN ONOFF NOMONSTER
When a button is touched, it moves some distance in the direction of it's angle, triggers all of it's targets, waits some time, then returns to it's original position where it can be triggered again.

NOMONSTER	monsters will not trigger this door

"angle"		determines the opening direction
"target"	all entities with a matching targetname will be used
"speed"		override the default 40 speed
"wait"		override the default 1 second wait (-1 = never return)
"lip"		override the default 4 pixel lip remaining at end of move
"health"	if set, the button must be killed instead of touched
"sounds"
1) silent
2) normal
3) valve
4) wheel
5) console switch
6) push button
7) thunk switch
8) wall
*/
// END JOSEPH

void button_done (edict_t *self)
{
	self->moveinfo.state = STATE_BOTTOM;
	self->s.effects &= ~EF_ANIM23;
	self->s.effects |= EF_ANIM01;
}

// JOSEPH 21-MAY-99
void button_return (edict_t *self)
{
	int setbutton = 0;
	
	self->moveinfo.state = STATE_DOWN;

	{
		int i;
		edict_t	*e = NULL;
		
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "func_lift")) &&
				(e->target2) && (self->target2) && (!strcmp(e->target2, self->target2)))
			{
				self->moveinfo.start_origin[2] = e->s.origin[2] + self->handleflag;
				Move_Calc (self, self->moveinfo.start_origin, button_done);
				setbutton = 1;
			}
		}
	}
	
	if (!setbutton)
		Move_Calc (self, self->moveinfo.start_origin, button_done);

	self->s.frame = 0;

	if (self->health)
		self->takedamage = DAMAGE_YES;
}


void button_return2 (edict_t *self)
{
	int setbutton = 0;
	
	self->moveinfo.state = STATE_DOWN;

	{
		int i;
		edict_t	*e = NULL;
		
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "func_lift")) &&
				(e->target2) && (self->target2) && (!strcmp(e->target2, self->target2)))
			{
				self->moveinfo.start_origin[2] = e->s.origin[2] + self->handleflag;
				Move_Calc (self, self->moveinfo.start_origin, button_done);
				setbutton = 1;
			}
		}
	}
	
	if (!setbutton)
		Move_Calc (self, self->moveinfo.start_origin, button_done);
	
	self->s.frame = 0;

	if (self->health)
		self->takedamage = DAMAGE_YES;
}
// END JOSEPH

void button_wait (edict_t *self)
{
	self->moveinfo.state = STATE_TOP;
	self->s.effects &= ~EF_ANIM01;
	self->s.effects |= EF_ANIM23;

	G_UseTargets (self, self->activator);
	
	// RAFAEL
	if (self->activate_flags & ACTIVATE_AND_OPEN)
		self->activate_flags &= ~ACTIVATE_AND_OPEN;
	
	self->s.frame = 1;
	
	if (self->moveinfo.wait >= 0)
	{
		self->nextthink = level.time + self->moveinfo.wait;
		self->think = button_return;
	}
}

void button_fire (edict_t *self)
{
	if (self->moveinfo.state == STATE_UP || self->moveinfo.state == STATE_TOP)
		return;

// BEGIN:	Xatrix/Ridah/Navigator/07-apr-1998
	// if this button hasn't been pressed yet, spawn a node here
	if (!self->deadflag && nav_dynamic->value && self->activator->client)
	{
		NAV_CreateNode( self->activator, self->activator->s.origin, vec3_origin, (short) (NODE_BUTTON + (NODE_DUCKING*(self->activator->maxs[2] == 4))), -1, self->activator->waterlevel);

		self->deadflag = true;
		self->nav_data.cache_node = (int)(self->activator->nav_build_data->current_node->index);

		self->activator->nav_build_data->current_node->goal_ent = self;
	}

	self->timestamp = level.time;
// END:		Xatrix/Ridah/Navigator/07-apr-1998

	self->moveinfo.state = STATE_UP;
	if (self->moveinfo.sound_start && !(self->flags & FL_TEAMSLAVE))
		gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start, 1, ATTN_STATIC, 0);

	// JOSEPH 21-MAY-99
	{
		int i;
		edict_t	*e = NULL;
		
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "func_lift")) &&
				(e->target2) && (self->target2) && (!strcmp(e->target2, self->target2)))
			{
				self->moveinfo.end_origin[2] = e->s.origin[2] + self->handleflag;
				Move_Calc (self, self->moveinfo.end_origin, button_wait);
				return;
			}
		}
	}
	Move_Calc (self, self->moveinfo.end_origin, button_wait);	
	// END JOSEPH
}

void button_use (edict_t *self, edict_t *other, edict_t *activator)
{
	// JOSEPH 21-MAY-99
	if (self->owner && (self->owner->spawnflags & DOOR_NOMONSTER) && (other->svflags & SVF_MONSTER))
		return;
	// END JOSEPH
	
	// RAFAEL
	if (self->activate_flags & ACTIVATE_GENERAL && activator->client)
	{
		if (!(self->activate_flags & ACTIVATE_AND_OPEN))
		{
			//gi.dprintf ("activator: %s next to button\n", activator->classname);	
			return;
		}
		else
		{
			//gi.dprintf ("activator: %s used the button\n", activator->classname);	
		}
	}
	
	self->activator = activator;
	button_fire (self);
}

void button_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	// JOSEPH 15-MAY-99
	if (self->owner && (self->owner->spawnflags & DOOR_NOMONSTER) && (other->svflags & SVF_MONSTER))
		return;
	// END JOSEPH

	// RAFAEL
	if (self->activate_flags & ACTIVATE_GENERAL && other->client)
	{
		if (!(self->activate_flags & ACTIVATE_AND_OPEN))
		{
			// gi.dprintf ("other: %s next to button\n", other->classname);	
			return;
		}
		else
		{
			// gi.dprintf ("other: %s used the button\n", other->classname);	
		}
	}

	if (other->health <= 0)
		return;

	self->activator = other;
	button_fire (self);
}

void button_killed (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->activator = attacker;
	self->health = self->max_health;
	self->takedamage = DAMAGE_NO;
	button_fire (self);
}

// JOSEPH 27-MAY-99
void func_button_sound (edict_t *ent, int buttonsound)
{
	switch (buttonsound)
	{
		default:
		case 0:
		case 2:
			ent->moveinfo.sound_start = gi.soundindex  ("world/switches/butn2.wav");
			break;
		case 3:
			ent->moveinfo.sound_start = gi.soundindex  ("world/switches/valve.wav");
			break;		
		case 4:
			ent->moveinfo.sound_start = gi.soundindex  ("world/switches/wheel.wav");
			break;
		case 5:
			ent->moveinfo.sound_start = gi.soundindex  ("world/switches/console switch.wav");
			break;
		case 6:
			ent->moveinfo.sound_start = gi.soundindex  ("world/switches/pushbutton.wav");
			break;
		case 7:
			ent->moveinfo.sound_start = gi.soundindex  ("world/switches/thunk switch.wav");
			break;
		case 8:
			ent->moveinfo.sound_start = gi.soundindex  ("world/switches/wall.wav");
			break;
	}
}

void SP_func_button (edict_t *ent)
{
	vec3_t	abs_movedir;
	float	dist;

	G_SetMovedir (ent->s.angles, ent->movedir);
	ent->movetype = MOVETYPE_STOP;
	ent->solid = SOLID_BSP;
	gi.setmodel (ent, ent->model);

	if (ent->sounds != 1)
	{
		func_button_sound (ent, ent->sounds);
	}
	
	//if (ent->sounds != 1)
	//	ent->moveinfo.sound_start = gi.soundindex ("world/switches/butn2.wav");
	
	if (!ent->speed)
		ent->speed = 40;
	if (!ent->accel)
		ent->accel = ent->speed;
	if (!ent->decel)
		ent->decel = ent->speed;

	if (!ent->wait)
		ent->wait = 3;
	if (!st.lip)
		st.lip = 4;

	VectorCopy (ent->s.origin, ent->pos1);
	abs_movedir[0] = fabs(ent->movedir[0]);
	abs_movedir[1] = fabs(ent->movedir[1]);
	abs_movedir[2] = fabs(ent->movedir[2]);
	dist = abs_movedir[0] * ent->size[0] + abs_movedir[1] * ent->size[1] + abs_movedir[2] * ent->size[2] - st.lip;
	VectorMA (ent->pos1, dist, ent->movedir, ent->pos2);

	ent->use = button_use;
	ent->s.effects |= EF_ANIM01;

	if (ent->health)
	{
		ent->max_health = ent->health;
		ent->die = button_killed;
		ent->takedamage = DAMAGE_YES;
	}
	else if (! ent->targetname)
		ent->touch = button_touch;

	ent->moveinfo.state = STATE_BOTTOM;

	ent->moveinfo.speed = ent->speed;
	ent->moveinfo.accel = ent->accel;
	ent->moveinfo.decel = ent->decel;
	ent->moveinfo.wait = ent->wait;
	VectorCopy (ent->pos1, ent->moveinfo.start_origin);
	VectorCopy (ent->s.angles, ent->moveinfo.start_angles);
	VectorCopy (ent->pos2, ent->moveinfo.end_origin);
	VectorCopy (ent->s.angles, ent->moveinfo.end_angles);

	gi.linkentity (ent);

	// RAFAEL
	if (!(ent->spawnflags & 1))
		ent->activate_flags |= ACTIVATE_GENERAL;
}
// END JOSEPH

// JOSEPH 20-MAY-99
void func_door_sound (edict_t *ent, int doorsound)
{
	switch (doorsound)
	{
		default:
		case 0:
		case 2:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/dr1_strt.wav");
			ent->moveinfo.sound_middle = gi.soundindex  ("world/doors/dr1_mid.wav");
			ent->moveinfo.sound_end = gi.soundindex  ("world/doors/dr1_end.wav");
			break;
		case 3:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/dr2_strt.wav");
			ent->moveinfo.sound_middle = gi.soundindex  ("world/doors/dr2_mid.wav");
			ent->moveinfo.sound_end2 = gi.soundindex  ("world/doors/dr2_endb.wav");
			break;		
		case 4:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/dr3_strt.wav");
			ent->moveinfo.sound_middle = gi.soundindex  ("world/doors/dr3_mid.wav");
			ent->moveinfo.sound_end2 = gi.soundindex  ("world/doors/dr3_endb.wav");
			break;
		break;
		case 5:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/dr4_strt.wav");
			ent->moveinfo.sound_middle = gi.soundindex  ("world/doors/dr4_mid.wav");
			ent->moveinfo.sound_end = gi.soundindex  ("world/doors/dr4_end.wav");
			break;
		case 6:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/dr5_strt.wav");
			ent->moveinfo.sound_middle = gi.soundindex  ("world/doors/dr5_mid.wav");
			ent->moveinfo.sound_end = gi.soundindex  ("world/doors/dr5_end.wav");
			break;
		case 7:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/dr6_strt.wav");
			ent->moveinfo.sound_middle = gi.soundindex  ("world/doors/dr6_mid.wav");
			ent->moveinfo.sound_end = gi.soundindex  ("world/doors/dr6_end.wav");
			break;
		case 8:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/dr7_strt.wav");
			ent->moveinfo.sound_middle = gi.soundindex  ("world/doors/dr7_mid.wav");
			ent->moveinfo.sound_end = gi.soundindex  ("world/doors/dr7_end.wav");
			break;
		case 9:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/drawer_w1.wav");
			ent->moveinfo.sound_end = gi.soundindex  ("world/doors/drawer_w2.wav");
			break;
		case 10:
			ent->moveinfo.sound_start = gi.soundindex  ("world/doors/drawer_m1.wav");
			ent->moveinfo.sound_end = gi.soundindex  ("world/doors/drawer_m2.wav");
			break;
	}
}
// END JOSEPH


// JOSEPH 20-MAY-99
/*
======================================================================

DOORS

  spawn a trigger surrounding the entire team unless it is
  already targeted by another

======================================================================
*/

/*QUAKED func_door (0 .5 .8) ? START_OPEN AUTO_OPEN CRUSHER NOMONSTER ANIMATED TOGGLE ANIMATED_FAST SURF2_ALPHA 
TOGGLE		wait in both the start and end states for a trigger event.
START_OPEN	the door to moves to its destination when spawned, and operate in reverse.  It is used to temporarily or permanently close off an area when triggered (not useful for touch or takedamage doors).
NOMONSTER	monsters will not trigger this door

"message"	is printed when the door is touched if it is a trigger door and it hasn't been fired yet
"angle"		determines the opening direction
"targetname" if set, no touch field will be spawned and a remote button or trigger field activates the door.
"health"	if set, door must be shot open
"speed"		movement speed (100 default)
"wait"		wait before returning (3 default, -1 = never return)
"lip"		lip remaining at end of move (8 default)
"dmg"		damage to inflict when blocked (2 default)
"sounds"    default = 2;
1)	silent
2)	Medium metal sliding rollup door
3)	Wooden swinging door 
4)	Metal swinging door
5)	Metal light sliding TRAIN door
6)	Very large rolling metal door
7)  Metal swing-up garage door
8)  Wooden swinging door two
9)  Wooden drawer
10) Metal drawer  
*/

// END JOSEPH

void door_use_areaportals (edict_t *self, qboolean open)
{
	edict_t	*t = NULL;

	if (!self->target)
		return;

	while ((t = G_Find (t, FOFS(targetname), self->target)))
	{
		if (Q_stricmp(t->classname, "func_areaportal") == 0)
		{
			gi.SetAreaPortalState (t->style, open);
		}
	}
}

void door_go_down (edict_t *self);

// JOSEPH 7-OCT-98
void door_hit_top (edict_t *self)
{
	if (!(self->flags & FL_TEAMSLAVE))
	{
		if (self->moveinfo.sound_end)
			// Open end
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_end, 1, ATTN_STATIC, 0);
		self->s.sound = 0;
	}
	self->moveinfo.state = STATE_TOP;
	if (self->spawnflags & DOOR_TOGGLE)
		return;
	if (self->moveinfo.wait >= 0)
	{
		self->think = door_go_down;
		self->nextthink = level.time + self->moveinfo.wait;
	}
}

void door_hit_bottom (edict_t *self)
{
	if (!(self->flags & FL_TEAMSLAVE))
	{
		if (self->moveinfo.sound_end2)
			// Close end
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_end2, 1, ATTN_STATIC, 0);
		else if (self->moveinfo.sound_end)
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_end, 1, ATTN_STATIC, 0);		
		self->s.sound = 0;
	}
	self->moveinfo.state = STATE_BOTTOM;
	door_use_areaportals (self, false);
}

void door_go_down (edict_t *self)
{
	if (!(self->flags & FL_TEAMSLAVE))
	{
		if (self->moveinfo.sound_start2)
			// Close start
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start2, 1, ATTN_STATIC, 0);
		else if (self->moveinfo.sound_start)
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start, 1, ATTN_STATIC, 0); 
		if (self->moveinfo.sound_middle2)
			self->s.sound = self->moveinfo.sound_middle2;
		else
			self->s.sound = self->moveinfo.sound_middle;
	}
	if (self->max_health)
	{
		self->takedamage = DAMAGE_YES;
		self->health = self->max_health;
	}
	
	self->moveinfo.state = STATE_DOWN;
	if (strcmp(self->classname, "func_door") == 0)
		Move_Calc (self, self->moveinfo.start_origin, door_hit_bottom);
	else if (strcmp(self->classname, "func_door_rotating") == 0)
		AngleMove_Calc (self, door_hit_bottom);
// Joseph
	else if (strcmp(self->classname, "func_subdoor_base") == 0)
		AngleMove_Calc (self, door_hit_bottom);
	else if (strcmp(self->classname, "func_subdoor_handle2") == 0)
		AngleMove_Calc (self, door_hit_bottom);
}

void door_go_up (edict_t *self, edict_t *activator)
{
 	if (self->moveinfo.state == STATE_UP)
		return;		// already going up

	if (self->moveinfo.state == STATE_TOP)
	{	// reset top wait time
		if (self->moveinfo.wait >= 0)
			self->nextthink = level.time + self->moveinfo.wait;
		return;
	}
	
	if (!(self->flags & FL_TEAMSLAVE))
	{
		if (self->moveinfo.sound_start)
			// Open start
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start, 1, ATTN_STATIC, 0);
		self->s.sound = self->moveinfo.sound_middle;
	}
	self->moveinfo.state = STATE_UP;
	if (strcmp(self->classname, "func_door") == 0)
		Move_Calc (self, self->moveinfo.end_origin, door_hit_top);
	else if (strcmp(self->classname, "func_door_rotating") == 0)
	{

		if (!self->avelocity[0] && !self->avelocity[1] && !self->avelocity[2])
		{
			// Ridah, rotate away from the player
			if (self->target_ent && !self->style)
			{
				static vec3_t	mins = {-12, -12, -4};
				static vec3_t	maxs = { 12,  12,  4};
				float	yaw;
				vec3_t	pos;
//				vec3_t	vec;
				trace_t	tr;
//				float	fraction;

//gi.dprintf("yo\n");

				// first, trace the self->target_ent towards the door
				VectorAdd( self->absmin, self->absmax, pos );
				VectorScale( pos, 0.5, pos );

//				AngleVectors( self->target_ent->s.angles, vec, NULL, NULL );
//				VectorMA( self->target_ent->s.origin, 128, vec, pos );

				tr = gi.trace( self->target_ent->s.origin, mins, maxs, pos, self->target_ent, CONTENTS_SOLID );

//				fraction = tr.fraction;

//NAV_DrawLine( self->target_ent->s.origin, tr.endpos );

				for (yaw=0.02; yaw<0.1; yaw += 0.02)
				{
					// try rotating it, see if we hit the activator
					VectorScale (self->moveinfo.end_angles, yaw, self->s.angles);
					gi.linkentity(self);

//					tr = gi.trace( self->target_ent->s.origin, mins, maxs, pos, self->target_ent, CONTENTS_SOLID );

					if ( !ValidBoxAtLoc(tr.endpos, mins, maxs, self->target_ent, CONTENTS_SOLID) )
//					if ( tr.fraction < fraction )
					{
						VectorNegate (self->moveinfo.end_angles, self->moveinfo.end_angles);
						break;
					}
				}

				// move it back
				VectorClear (self->s.angles);
				gi.linkentity(self);
			}
		}

		AngleMove_Calc (self, door_hit_top);
	}
	else if (strcmp(self->classname, "func_subdoor_base") == 0)
		AngleMove_Calc (self, door_hit_top);
	else if (strcmp(self->classname, "func_subdoor_handle2") == 0)
		AngleMove_Calc (self, door_hit_top);

	G_UseTargets (self, activator);
	door_use_areaportals (self, true);
}

#if 0
void door_use (edict_t *self, edict_t *other, edict_t *activator)
{
	edict_t	*ent;


	// RAFAEL
	if (activator)
	{
		if (self->activate_flags & ACTIVATE_GENERAL && (activator->client))
		{
			if (!(self->activate_flags & ACTIVATE_AND_OPEN))
			{
				//gi.dprintf ("activator: %s next to door\n", activator->classname);	
				return;
			}
			else
			{
				self->activate_flags &= ~ACTIVATE_AND_OPEN;
				//gi.dprintf ("activator: %s used the door\n", activator->classname);	
			}
		}
		else if (!activator->client /*&& activator->cast_group == 1*/ && self->key)
		{
			return;
		}
		
		// HACK to stop rockets from opening doors
		else if (activator->movetype == MOVETYPE_FLYMISSILE)
			return;
	}

	
	// hack this may cause us problems test first
	if (self->flags & FL_TEAMSLAVE)
		return;

	if (self->spawnflags & DOOR_TOGGLE)
	{
		if (self->moveinfo.state == STATE_UP || self->moveinfo.state == STATE_TOP)
		{
			// trigger all paired doors
			for (ent = self ; ent ; ent = ent->teamchain)
			{
				ent->message = NULL;
				ent->touch = NULL;
				door_go_down (ent);
			}
			return;
		}
	}
	
	// trigger all paired doors
	for (ent = self ; ent ; ent = ent->teamchain)
	{
// BEGIN:	Xatrix/Ridah/Navigator/08-apr-1998
	// inform others of the trigger
		if (activator)
		{
			ent->target_ent = activator;
			activator->target_ent = ent;
		}
		else
			ent->target_ent = NULL;
// END:		Xatrix/Ridah/Navigator/08-apr-1998

		ent->message = NULL;
		ent->touch = NULL;
		door_go_up (ent, activator);

	}
};
#endif

void door_use (edict_t *self, edict_t *other, edict_t *activator)
{
	edict_t	*ent;


	// RAFAEL
	if (activator)
	{
		if (self->activate_flags & ACTIVATE_GENERAL && (activator->client))
		{
			if (!(self->activate_flags & ACTIVATE_AND_OPEN))
			{
				//gi.dprintf ("activator: %s next to door\n", activator->classname);	
				return;
			}
			else
			{
				self->activate_flags &= ~ACTIVATE_AND_OPEN;
				//gi.dprintf ("activator: %s used the door\n", activator->classname);	
			}
		}
		else if (!activator->client /*&& activator->cast_group == 1*/ && self->key)
		{
			return;
		}
		
		// HACK to stop rockets from opening doors
		else if (activator->movetype == MOVETYPE_FLYMISSILE)
			return;
	}

	
	if (self->flags & FL_TEAMSLAVE)
	{
		// this will help the teamed door to open if the activated door is FL_TEAMSLAVE
		if (!(strcmp (self->classname, "func_door")))
		{
			if (self->teammaster)
			{
				edict_t *teammaster;

				teammaster = self->teammaster;

				if (teammaster->spawnflags & DOOR_TOGGLE)
				{
					if (teammaster->moveinfo.state == STATE_UP || teammaster->moveinfo.state == STATE_TOP)
					{
						// trigger all paired doors
						for (ent = teammaster ; ent ; ent = ent->teamchain)
						{
							ent->message = NULL;
							ent->touch = NULL;
							door_go_down (ent);
						}
						return;
					}
				}
				
				// trigger all paired doors
				for (ent = teammaster ; ent ; ent = ent->teamchain)
				{
				// inform others of the trigger
					if (activator)
					{
						ent->target_ent = activator;
						activator->target_ent = ent;
					}
					else
						ent->target_ent = NULL;

					ent->message = NULL;
					ent->touch = NULL;
					door_go_up (ent, activator);

				}

			}
			else 
				return;

		}
		else
			return;
	}
	else 
	{
		if (self->spawnflags & DOOR_TOGGLE)
		{
			if (self->moveinfo.state == STATE_UP || self->moveinfo.state == STATE_TOP)
			{
				// trigger all paired doors
				for (ent = self ; ent ; ent = ent->teamchain)
				{
					ent->message = NULL;
					ent->touch = NULL;
					door_go_down (ent);
				}
				return;
			}
		}
		
		// trigger all paired doors
		for (ent = self ; ent ; ent = ent->teamchain)
		{
		// inform others of the trigger
			if (activator)
			{
				ent->target_ent = activator;
				activator->target_ent = ent;
			}
			else
				ent->target_ent = NULL;

			ent->message = NULL;
			ent->touch = NULL;
			door_go_up (ent, activator);

		}
	}
};


void Touch_DoorTrigger (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (other->health <= 0)
		return;
/*
	if (!(other->svflags & SVF_MONSTER) && (!other->client))
		return;
*/
	if (self->key)
		return;

	if (other->cast_group == 1)
		; 
	else if (	(self->owner->spawnflags & DOOR_NOMONSTER) && (other->svflags & SVF_MONSTER)
		&&	((self->owner->cast_group != 1) || (other->cast_group != 1) || (!other->leader)))	// Ridah 25-May-99, new flag for use on Bar doors so friendly guys don't get so stuck
		return;

	if (level.time < self->touch_debounce_time)
		return;
	self->touch_debounce_time = level.time + 1.0;

	door_use (self->owner, other, other);
}

void Think_CalcMoveSpeed (edict_t *self)
{
	edict_t	*ent;
	float	min;
	float	time;
	float	newspeed;
	float	ratio;
	float	dist;

	if (self->flags & FL_TEAMSLAVE)
		return;		// only the team master does this

	// find the smallest distance any member of the team will be moving
	min = fabs(self->moveinfo.distance);
	for (ent = self->teamchain; ent; ent = ent->teamchain)
	{
		dist = fabs(ent->moveinfo.distance);
		if (dist < min)
			min = dist;
	}

	time = min / self->moveinfo.speed;

	// adjust speeds so they will all complete at the same time
	for (ent = self; ent; ent = ent->teamchain)
	{
		newspeed = fabs(ent->moveinfo.distance) / time;
		ratio = newspeed / ent->moveinfo.speed;
		if (ent->moveinfo.accel == ent->moveinfo.speed)
			ent->moveinfo.accel = newspeed;
		else
			ent->moveinfo.accel *= ratio;
		if (ent->moveinfo.decel == ent->moveinfo.speed)
			ent->moveinfo.decel = newspeed;
		else
			ent->moveinfo.decel *= ratio;
		ent->moveinfo.speed = newspeed;
	}
}

void Think_SpawnDoorTrigger (edict_t *ent)
{
	edict_t		*other;
	vec3_t		mins, maxs;

	if (ent->flags & FL_TEAMSLAVE)
		return;		// only the team leader spawns a trigger

	VectorCopy (ent->absmin, mins);
	VectorCopy (ent->absmax, maxs);

	for (other = ent->teamchain ; other ; other=other->teamchain)
	{
		AddPointToBounds (other->absmin, mins, maxs);
		AddPointToBounds (other->absmax, mins, maxs);
	}

	// expand 
	mins[0] -= 60;
	mins[1] -= 60;
	maxs[0] += 60;
	maxs[1] += 60;

	other = G_Spawn ();
	VectorCopy (mins, other->mins);
	VectorCopy (maxs, other->maxs);
	other->owner = ent;
	other->solid = SOLID_TRIGGER;
	other->movetype = MOVETYPE_NONE;
	other->touch = Touch_DoorTrigger;
	gi.linkentity (other);

	if (ent->spawnflags & DOOR_START_OPEN)
		door_use_areaportals (ent, true);

	Think_CalcMoveSpeed (ent);
}

void door_blocked  (edict_t *self, edict_t *other)
{
	edict_t	*ent;

	if (!(other->svflags & SVF_MONSTER) && !(other->client) )
	{
		
		// give it a chance to go away on it's own terms (like gibs)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, 100000, 1, 0, MOD_CRUSH);
		// if it's still there, nuke it
		if (other)
			BecomeExplosion1 (other);
		return;
		
	}

	if (!strcmp (self->classname, "func_door_rotating"))
	{
		// don't do any damage

		// tell them to back up
//		if (other->svflags & SVF_MONSTER)
//		{
//			if (other->cast_info.move_avoid_reverse_walk)
//				other->cast_info.currentmove = other->cast_info.move_avoid_reverse_walk;
//		}

	}
	else
	{
		if (other->groundentity == self)
			if (developer->value)
				gi.dprintf ("%s inflicting damage on %s\n", self->classname, other->classname);
		
		// Ridah, small objects shouldn't hurt
		if (VectorDistance( self->absmin, self->absmax) > 200)
			T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);
	}

//if (!ValidBoxAtLoc( other->s.origin, other->mins, other->maxs, other, MASK_PLAYERSOLID))
//	gi.dprintf( "door stuck in entity\n" );
/*
// BEGIN:	Xatrix/Ridah/Navigator/16-apr-1998
	// Hack, Cast's that get stuck in doors should duck at all costs
	if ((other->svflags & SVF_MONSTER) && (other->cast_info.move_crstand))
	{
		other->maxs[2] = DUCKING_MAX_Z;
		if (other->cast_info.move_crouch_down)
		{
			other->cast_info.currentmove = other->cast_info.move_crouch_down;
			return;
		}
	}
// END:		Xatrix/Ridah/Navigator/16-apr-1998
*/
	if (self->spawnflags & DOOR_CRUSHER)
		return;


// if a door has a negative wait, it would never come back if blocked,
// so let it just squash the object to death real fast
	if (self->moveinfo.wait >= 0)
	{
		if (self->moveinfo.state == STATE_DOWN)
		{
			for (ent = self->teammaster ; ent ; ent = ent->teamchain)
				door_go_up (ent, ent->activator);
		}
		else
		{
			for (ent = self->teammaster ; ent ; ent = ent->teamchain)
				door_go_down (ent);
		}
	}
}

void door_killed (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	edict_t	*ent;

	for (ent = self->teammaster ; ent ; ent = ent->teamchain)
	{
		ent->health = ent->max_health;
		ent->takedamage = DAMAGE_NO;
	}
	door_use (self->teammaster, attacker, attacker);
}

void door_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!(other->client) && !(other->svflags & SVF_MONSTER))
		return;

	if (level.time < self->touch_debounce_time)
		return;
	self->touch_debounce_time = level.time + 5.0;

	gi.centerprintf (other, "%s", self->message);
	// JOSEPH 29-MAR-99
	//gi.sound (other, CHAN_AUTO, gi.soundindex ("misc/talk1.wav"), 1, ATTN_NORM, 0);
	// END JOSEPH
}

void SP_func_door (edict_t *ent)
{
	vec3_t	abs_movedir;

	// JOSEPH 1-OCT-98
	if (ent->sounds != 1)
	{
		func_door_sound (ent, ent->sounds);
	}
	// END JOSEPH

	G_SetMovedir (ent->s.angles, ent->movedir);
	ent->movetype = MOVETYPE_PUSH;
	ent->solid = SOLID_BSP;
	gi.setmodel (ent, ent->model);

	ent->blocked = door_blocked;
	ent->use = door_use;
	
	if (!ent->speed)
		ent->speed = 100;
	
	if (!ent->accel)
		ent->accel = ent->speed;
	if (!ent->decel)
		ent->decel = ent->speed;

	if (!ent->wait)
		ent->wait = 3;
	if (!st.lip)
		st.lip = 8;
	if (!ent->dmg)
		ent->dmg = 2;

	// calculate second position
	VectorCopy (ent->s.origin, ent->pos1);
	abs_movedir[0] = fabs(ent->movedir[0]);
	abs_movedir[1] = fabs(ent->movedir[1]);
	abs_movedir[2] = fabs(ent->movedir[2]);
	ent->moveinfo.distance = abs_movedir[0] * ent->size[0] + abs_movedir[1] * ent->size[1] + abs_movedir[2] * ent->size[2] - st.lip;
	VectorMA (ent->pos1, ent->moveinfo.distance, ent->movedir, ent->pos2);

	// if it starts open, switch the positions
	if (ent->spawnflags & DOOR_START_OPEN)
	{
		VectorCopy (ent->pos2, ent->s.origin);
		VectorCopy (ent->pos1, ent->pos2);
		VectorCopy (ent->s.origin, ent->pos1);
	}

	ent->moveinfo.state = STATE_BOTTOM;

	if (ent->health)
	{
		ent->takedamage = DAMAGE_YES;
		ent->die = door_killed;
		ent->max_health = ent->health;
	}
	else if (ent->targetname && ent->message)
	{
		gi.soundindex ("misc/talk.wav");
		ent->touch = door_touch;
	}
	
	ent->moveinfo.speed = ent->speed;
	ent->moveinfo.accel = ent->accel;
	ent->moveinfo.decel = ent->decel;
	ent->moveinfo.wait = ent->wait;
	VectorCopy (ent->pos1, ent->moveinfo.start_origin);
	VectorCopy (ent->s.angles, ent->moveinfo.start_angles);
	VectorCopy (ent->pos2, ent->moveinfo.end_origin);
	VectorCopy (ent->s.angles, ent->moveinfo.end_angles);

	if (ent->spawnflags & 16)
		ent->s.effects |= EF_ANIM_ALL;
	if (ent->spawnflags & 64)
		ent->s.effects |= EF_ANIM_ALLFAST;

	// to simplify logic elsewhere, make non-teamed doors into a team of one
	if (!ent->team)
		ent->teammaster = ent;

	gi.linkentity (ent);

	ent->nextthink = level.time + FRAMETIME;
	if (ent->health || ent->targetname)
		ent->think = Think_CalcMoveSpeed;
	else
		ent->think = Think_SpawnDoorTrigger;

	if (ent->spawnflags & 128)
		ent->s.renderfx2 |= RF2_SURF_ALPHA;

	// RAFAEL
	if (!(ent->spawnflags & 2))
		ent->activate_flags |= ACTIVATE_GENERAL;
	
}

// JOSEPH 20-MAY-99
/*QUAKED func_door_rotating (0 .5 .8) ? START_OPEN REVERSE SURF_ALPHA NOMONSTER ANIMATED TOGGLE X_AXIS Y_AXIS
TOGGLE causes the door to wait in both the start and end states for a trigger event.

START_OPEN	the door to moves to its destination when spawned, and operate in reverse.  It is used to temporarily or permanently close off an area when triggered (not useful for touch or takedamage doors).
NOMONSTER	monsters will not trigger this door

You need to have an origin brush as part of this entity.  The center of that brush will be
the point around which it is rotated. It will rotate around the Z axis by default.  You can
check either the X_AXIS or Y_AXIS box to change that.

"distance" is how many degrees the door will be rotated.
"speed" determines how fast the door moves; default value is 100.

REVERSE will cause the door to rotate in the opposite direction.

"style"		0 = rotate away from it's activator, 1 = fixed rotation (default 0)
"message"	is printed when the door is touched if it is a trigger door and it hasn't been fired yet
"angle"		determines the opening direction
"targetname" if set, no touch field will be spawned and a remote button or trigger field activates the door.
"health"	if set, door must be shot open
"speed"		movement speed (100 default)
"wait"		wait before returning (3 default, -1 = never return)
"dmg"		damage to inflict when blocked (2 default)
"sounds"    default = 2;
1)	silent
2)	Medium metal sliding rollup door
3)	Wooden swinging door 
4)	Metal swinging door
5)	Metal light sliding TRAIN door
6)	Very large rolling metal door
7)  Metal swing-up garage door
8)  Wooden swinging door two
9)  Wooden drawer
10) Metal drawer  
*/
// END JOSEPH

void SP_func_door_rotating (edict_t *ent)
{
	VectorClear (ent->s.angles);

	// set the axis of rotation
	VectorClear(ent->movedir);
	if (ent->spawnflags & DOOR_X_AXIS)
		ent->movedir[2] = 1.0;
	else if (ent->spawnflags & DOOR_Y_AXIS)
		ent->movedir[0] = 1.0;
	else // Z_AXIS
		ent->movedir[1] = 1.0;

	// check for reverse rotation
	if (ent->spawnflags & DOOR_REVERSE)
		VectorNegate (ent->movedir, ent->movedir);

	if (!st.distance)
	{
		gi.dprintf("%s at %s with no distance set\n", ent->classname, vtos(ent->s.origin));
		st.distance = 90;
	}

	VectorCopy (ent->s.angles, ent->pos1);
	VectorMA (ent->s.angles, st.distance, ent->movedir, ent->pos2);
	ent->moveinfo.distance = st.distance;

	ent->movetype = MOVETYPE_PUSH;
	ent->solid = SOLID_BSP;
	gi.setmodel (ent, ent->model);

	ent->blocked = door_blocked;
	ent->use = door_use;

	if (!ent->speed)
		ent->speed = 100;

	if (!ent->accel)
		ent->accel = ent->speed;
	if (!ent->decel)
		ent->decel = ent->speed;

	if (!ent->wait)
		ent->wait = 3;
	if (!ent->dmg)
		ent->dmg = 2;

	// JOSEPH 1-OCT-98
	if (ent->sounds != 1)
	{
		func_door_sound (ent, ent->sounds);
	}
	// END JOSEPH

	// if it starts open, switch the positions
	if (ent->spawnflags & DOOR_START_OPEN)
	{
		VectorCopy (ent->pos2, ent->s.angles);
		VectorCopy (ent->pos1, ent->pos2);
		VectorCopy (ent->s.angles, ent->pos1);
		VectorNegate (ent->movedir, ent->movedir);
	}

	if (ent->health)
	{
		ent->takedamage = DAMAGE_YES;
		ent->die = door_killed;
		ent->max_health = ent->health;
	}
	
	if (ent->targetname && ent->message)
	{
		gi.soundindex ("misc/talk.wav");
		ent->touch = door_touch;
	}

	ent->moveinfo.state = STATE_BOTTOM;
	ent->moveinfo.speed = ent->speed;
	ent->moveinfo.accel = ent->accel;
	ent->moveinfo.decel = ent->decel;
	ent->moveinfo.wait = ent->wait;
	VectorCopy (ent->s.origin, ent->moveinfo.start_origin);
	VectorCopy (ent->pos1, ent->moveinfo.start_angles);
	VectorCopy (ent->s.origin, ent->moveinfo.end_origin);
	VectorCopy (ent->pos2, ent->moveinfo.end_angles);

	if (ent->spawnflags & 16)
		ent->s.effects |= EF_ANIM_ALL;

	// to simplify logic elsewhere, make non-teamed doors into a team of one
	if (!ent->team)
		ent->teammaster = ent;

	gi.linkentity (ent);

	ent->nextthink = level.time + FRAMETIME;
	
	//if (ent->health || ent->targetname)
	//	ent->think = Think_CalcMoveSpeed;
	//else
	if (ent->key == -1 && ent->targetname)
		ent->think = Think_SpawnDoorTrigger;
	else if (ent->targetname)
		ent->think = Think_CalcMoveSpeed;
	else
		ent->think = Think_SpawnDoorTrigger;

	// RAFAEL
	//if (!(ent->spawnflags & 256))
	ent->activate_flags |= ACTIVATE_GENERAL;
	
	if ((ent->spawnflags & 4))
		ent->s.renderfx2 |= RF2_SURF_ALPHA;

}

// Joseph

/*QUAKED func_subdoor_base (0 .5 .8) ? X REVERSE CRUSHER NOMONSTER ANIMATED TOGGLE X_AXIS Y_AXIS AUTO_OPEN

The func_subdoor_handle1 will rotate 90 deg then the door will open with func_subdoor_handle2.
  
TOGGLE causes the door to wait in both the start and end states for a trigger event.

NOMONSTER	monsters will not trigger this door

You need to have an origin brush as part of this entity.  The center of that brush will be
the point around which it is rotated. It will rotate around the Z axis by default. You can
check either the X_AXIS or Y_AXIS box to change that.

You also need a:

 func_subdoor_handle1 - Handle with origin in the center
 
 func_subdoor_handle2 - Handle with origin at the door origin

 Both handles are in the same area in level space

"distance" is how many degrees the door will be rotated.
"speed" determines how fast the door moves; default value is 100.

REVERSE will cause the door to rotate in the opposite direction.

"message"	is printed when the door is touched if it is a trigger door and it hasn't been fired yet
"angle"		determines the opening direction
"targetname" if set, no touch field will be spawned and a remote button or trigger field activates the door.
"health"	if set, door must be shot open
"speed"		movement speed (100 default)
"wait"		wait before returning (3 default, -1 = never return)
"dmg"		damage to inflict when blocked (2 default)
"sounds"
1)	silent
2)	light
3)	medium
4)	heavy
*/

/*QUAKED func_subdoor_handle1 (0 .5 .8) ? X REVERSE X X X X X_AXIS Y_AXIS

Will rotate 90 deg with the func_subdoor_base.
  
You need to have an origin brush in the center of this entity. The center of that brush will be
the point around which it is rotated. It will rotate around the Z axis by default. You can
check either the X_AXIS or Y_AXIS box to change that.

"duration" is how long the rotation will take place.

REVERSE will cause the handle to rotate in the opposite direction.
*/

// JOSEPH 26-AUG-98

/*QUAKED func_subdoor_handle2 (0 .5 .8)

Will rotate with door
It's origin should be the door's origin
*/

// END JOSEPH

void door_use_subdoor (edict_t *self, edict_t *other, edict_t *activator)
{
	edict_t	*ent;

	// trigger subdoor and handle
	ent = self;
	ent->message = NULL;
	ent->touch = NULL;
	door_go_up(ent, activator);
	activator->target_ent = ent;
	if (ent->handle2)
	{
		ent = ent->handle2;
		ent->message = NULL;
		ent->touch = NULL;
 		door_go_up(ent, activator);
		activator->target_ent = ent;
	}
};

void Think_stop_handle (edict_t *self)
{
    if ((self->handle) && (self->handle2))
	{
		VectorClear(self->handle->avelocity);
		self->handle->solid = 0;
		self->handle->svflags |= SVF_NOCLIENT;
		self->handle2->svflags &= ~SVF_NOCLIENT;
	}
	
	door_use_subdoor (self->save_self->owner, self->save_other, self->save_other);	
}

void Touch_DoorTrigger_subdoor (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	int		Taxis;
	float	deg;
	float	traveltime;
	float	frames;
	
	if (other->health <= 0)
		return;

	if ((self->owner->spawnflags & DOOR_NOMONSTER) && (other->svflags & SVF_MONSTER))
		return;

	if (level.time < self->touch_debounce_time)
		return;
	
	self->touch_debounce_time = level.time + 1.0;
	
	if ((self->owner->doorflag) && (!self->owner->firstnode))
	{
		if (self->owner->handle->duration) 
			traveltime = self->owner->handle->duration;
				else traveltime = 0.5;
		
		deg = 90;
		
		self->owner->firstnode = 1;

		self->owner->save_self = self;
		self->owner->save_other = other;

		if (self->owner->handle)
		{
			if (self->owner->handle->spawnflags & DOOR_X_AXIS)
				Taxis = ROLL;
			else if (self->owner->handle->spawnflags & DOOR_Y_AXIS)
				Taxis = PITCH;
			else // Z_AXIS
				Taxis = YAW;
		
            self->owner->handle->avelocity[Taxis] = (deg / traveltime);
			
			if (self->owner->handle->spawnflags & DOOR_REVERSE)
				self->owner->handle->avelocity[Taxis] = -(self->owner->handle->avelocity[Taxis]);	
		}
		if (traveltime < FRAMETIME)
		{
			Think_stop_handle (self->owner);
			return;
		}

		frames = floor(traveltime / FRAMETIME);

		self->owner->nextthink = level.time + (FRAMETIME * (frames+1));
		self->owner->think = Think_stop_handle;
	}
}

void door_touch_subdoor (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!(other->client))
		return;

	if (level.time < self->touch_debounce_time)
		return;
	self->touch_debounce_time = level.time + 5.0;

	gi.centerprintf (other, "%s", self->message);
	// JOSEPH 29-MAR-99
	//gi.sound (other, CHAN_AUTO, gi.soundindex ("misc/talk1.wav"), 1, ATTN_NORM, 0);
	// END JOSEPH
}

void Think_SpawnDoorTrigger_subdoor (edict_t *ent)
{
	edict_t		*other, *handle, *chainent;
	vec3_t		mins, maxs;
	
	// Kill trigger if door is a slave
	if (ent->flags & FL_TEAMSLAVE)
	{
		return;
	}
    	
	// Set pointers to all slaves from master
	for (chainent = ent->teammaster; chainent; chainent = chainent->teamchain)
	{
		if (chainent->handleflag)
		{
			ent->handle = chainent; 
		}
		else if (chainent->handle2flag)
		{
			ent->handle2 = chainent; 		
		}
	}
	
	// JOSEPH 1-OCT-98
	// Pre-rotate handle1 to match handle2 
	if (ent->handle)
	{
		handle = ent->handle;
		
		if (ent->spawnflags & DOOR_X_AXIS)
		{
			if(ent->spawnflags & DOOR_REVERSE)
			{
				handle->s.angles[0] += 90;
			}
			else
			{
				handle->s.angles[0] -= 90;
			}
		}
		else if (ent->spawnflags & DOOR_Y_AXIS)
		{
			if(ent->spawnflags & DOOR_REVERSE)
			{
				handle->s.angles[1] += 90;
			}
			else
			{
				handle->s.angles[1] -= 90;
			}		
		}
		else // Z_AXIS
		{
			if(ent->spawnflags & DOOR_REVERSE)
			{
				handle->s.angles[2] += 90;
			}
			else
			{
				handle->s.angles[2] -= 90;
			}		
		}
	}
	// END JOSEPH
	
	// Set handle2 to move like door
	if (ent->handle2)
	{
		handle = ent->handle2;
			
		VectorClear (handle->s.angles);
			
		VectorCopy (ent->movedir, handle->movedir);
			
		VectorCopy (handle->s.angles, handle->pos1);
			
		VectorMA (handle->s.angles, ent->moveinfo.distance, handle->movedir, handle->pos2);
			
		handle->moveinfo.distance = ent->moveinfo.distance;

		handle->speed = ent->speed;
		handle->accel = ent->accel;
		handle->decel = ent->decel;
			
		handle->wait = ent->wait;
		handle->dmg = ent->dmg;
			
		// if it starts open, switch the positions
		if (ent->spawnflags & DOOR_START_OPEN)
		{
			VectorCopy (handle->pos2, handle->s.angles);
			VectorCopy (handle->pos1, handle->pos2);
			VectorCopy (handle->s.angles, handle->pos1);
			VectorNegate (handle->movedir, handle->movedir);
		}

		handle->moveinfo.state = STATE_BOTTOM;
		handle->moveinfo.speed = handle->speed;
		handle->moveinfo.accel = handle->accel;
		handle->moveinfo.decel = handle->decel;
		handle->moveinfo.wait  = handle->wait = -1;
			
		VectorCopy (handle->s.origin, handle->moveinfo.start_origin);
		VectorCopy (handle->pos1, handle->moveinfo.start_angles);
		VectorCopy (handle->s.origin, handle->moveinfo.end_origin);
		VectorCopy (handle->pos2, handle->moveinfo.end_angles);
			
		gi.linkentity (handle);
    	
	}
	
	if (ent->flags & FL_TEAMSLAVE)
		return;		// only the team leader spawns a trigger

	VectorCopy (ent->absmin, mins);
	VectorCopy (ent->absmax, maxs);

	for (other = ent->teamchain ; other ; other=other->teamchain)
	{
		AddPointToBounds (other->absmin, mins, maxs);
		AddPointToBounds (other->absmax, mins, maxs);
	}

	// expand 
	mins[0] -= 60;
	mins[1] -= 60;
	maxs[0] += 60;
	maxs[1] += 60;

	other = G_Spawn ();
	VectorCopy (mins, other->mins);
	VectorCopy (maxs, other->maxs);
	other->owner = ent;
	other->solid = SOLID_TRIGGER;
	other->movetype = MOVETYPE_NONE;
	other->touch = Touch_DoorTrigger_subdoor;
	gi.linkentity (other);

	if (ent->spawnflags & DOOR_START_OPEN)
		door_use_areaportals (ent, true);
}

void SP_func_subdoor_base (edict_t *ent)
{
	VectorClear (ent->s.angles);

	// set the axis of rotation
	VectorClear(ent->movedir);
	
	if (ent->spawnflags & DOOR_X_AXIS)
		ent->movedir[2] = 1.0;
	else if (ent->spawnflags & DOOR_Y_AXIS)
		ent->movedir[0] = 1.0;
	else // Z_AXIS
		ent->movedir[1] = 1.0;
	
	// check for reverse rotation
	if (ent->spawnflags & DOOR_REVERSE)
		VectorNegate (ent->movedir, ent->movedir);

	if (!st.distance)
	{
		gi.dprintf("%s at %s with no distance set\n", ent->classname, vtos(ent->s.origin));
		st.distance = 90;
	}

	VectorCopy (ent->s.angles, ent->pos1);
	VectorMA (ent->s.angles, st.distance, ent->movedir, ent->pos2);
	ent->moveinfo.distance = st.distance;

	ent->movetype = MOVETYPE_PUSH;
	ent->solid = SOLID_BSP;
	ent->doorflag = 1;
	gi.setmodel (ent, ent->model);

	ent->blocked = door_blocked;
	ent->use = door_use_subdoor;

	if (!ent->speed)
		ent->speed = 100;
	if (!ent->accel)
		ent->accel = ent->speed;
	if (!ent->decel)
		ent->decel = ent->speed;

	//if (!ent->wait)
	//	ent->wait = 3;
	
	// Only opens once
	ent->wait = -1;

	if (!ent->dmg)
		ent->dmg = 2;

	if (ent->sounds != 1)
	{
		ent->moveinfo.sound_start = gi.soundindex  ("doors/dr1_strt.wav");
		ent->moveinfo.sound_middle = gi.soundindex  ("doors/dr1_mid.wav");
		ent->moveinfo.sound_end = gi.soundindex  ("doors/dr1_end.wav");
	}

	// if it starts open, switch the positions
	if (ent->spawnflags & DOOR_START_OPEN)
	{
		VectorCopy (ent->pos2, ent->s.angles);
		VectorCopy (ent->pos1, ent->pos2);
		VectorCopy (ent->s.angles, ent->pos1);
		VectorNegate (ent->movedir, ent->movedir);
	}

	if (ent->health)
	{
		ent->takedamage = DAMAGE_YES;
		ent->die = door_killed;
		ent->max_health = ent->health;
	}
	
	if (ent->targetname && ent->message)
	{
		gi.soundindex ("misc/talk.wav");
		ent->touch = door_touch_subdoor;
	}

	ent->moveinfo.state = STATE_BOTTOM;
	ent->moveinfo.speed = ent->speed;
	ent->moveinfo.accel = ent->accel;
	ent->moveinfo.decel = ent->decel;
	ent->moveinfo.wait = ent->wait;
	VectorCopy (ent->s.origin, ent->moveinfo.start_origin);
	VectorCopy (ent->pos1, ent->moveinfo.start_angles);
	VectorCopy (ent->s.origin, ent->moveinfo.end_origin);
	VectorCopy (ent->pos2, ent->moveinfo.end_angles);

	if (ent->spawnflags & 16)
		ent->s.effects |= EF_ANIM_ALL;

	// to simplify logic elsewhere, make non-teamed doors into a team of one
	if (!ent->team)
		ent->teammaster = ent;

	gi.linkentity (ent);

	ent->nextthink = level.time + FRAMETIME;
	ent->think = Think_SpawnDoorTrigger_subdoor;

	// RAFAEL
	if (!(ent->spawnflags & 256))
		ent->activate_flags |= ACTIVATE_GENERAL;


}

void think_none (edict_t *self)
{
// Need for some reason???
}

void SP_func_subdoor_handle1 (edict_t *ent)
{
	VectorClear (ent->s.angles);
	ent->movetype = MOVETYPE_PUSH;
	ent->solid = SOLID_BSP;
	ent->handleflag = 1;
	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
	ent->think = think_none;
}

void SP_func_subdoor_handle2 (edict_t *ent)
{
	VectorClear (ent->s.angles);
	ent->movetype = MOVETYPE_PUSH;
	ent->solid = SOLID_BSP;
	ent->handle2flag = 1;
	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
	ent->think = think_none;
    ent->svflags |= SVF_NOCLIENT;
}

// END JOSEPH

/*QUAKED func_water (0 .5 .8) ? START_OPEN TRANSLUCENT
func_water is a moveable water brush.  It must be targeted to operate.  Use a non-water texture at your own risk.

START_OPEN causes the water to move to its destination when spawned and operate in reverse.

"angle"		determines the opening direction (up or down only)
"speed"		movement speed (25 default)
"wait"		wait before returning (-1 default, -1 = TOGGLE)
"lip"		lip remaining at end of move (0 default)
"sounds"	(yes, these need to be changed)
0)	no sound
1)	water
2)	lava
*/

void SP_func_water (edict_t *self)
{
	vec3_t	abs_movedir;

	G_SetMovedir (self->s.angles, self->movedir);
	self->movetype = MOVETYPE_PUSH;
	self->solid = SOLID_BSP;
	gi.setmodel (self, self->model);

	switch (self->sounds)
	{
		default:
			break;

		case 1: // water
			self->moveinfo.sound_start = gi.soundindex  ("world/mov_watr.wav");
			self->moveinfo.sound_end = gi.soundindex  ("world/stp_watr.wav");
			break;

		case 2: // lava
			self->moveinfo.sound_start = gi.soundindex  ("world/mov_watr.wav");
			self->moveinfo.sound_end = gi.soundindex  ("world/stp_watr.wav");
			break;
	}

	// calculate second position
	VectorCopy (self->s.origin, self->pos1);
	abs_movedir[0] = fabs(self->movedir[0]);
	abs_movedir[1] = fabs(self->movedir[1]);
	abs_movedir[2] = fabs(self->movedir[2]);
	self->moveinfo.distance = abs_movedir[0] * self->size[0] + abs_movedir[1] * self->size[1] + abs_movedir[2] * self->size[2] - st.lip;
	VectorMA (self->pos1, self->moveinfo.distance, self->movedir, self->pos2);

	// if it starts open, switch the positions
	if (self->spawnflags & DOOR_START_OPEN)
	{
		VectorCopy (self->pos2, self->s.origin);
		VectorCopy (self->pos1, self->pos2);
		VectorCopy (self->s.origin, self->pos1);
	}

	VectorCopy (self->pos1, self->moveinfo.start_origin);
	VectorCopy (self->s.angles, self->moveinfo.start_angles);
	VectorCopy (self->pos2, self->moveinfo.end_origin);
	VectorCopy (self->s.angles, self->moveinfo.end_angles);

	self->moveinfo.state = STATE_BOTTOM;

	if (!self->speed)
		self->speed = 25;
	self->moveinfo.accel = self->moveinfo.decel = self->moveinfo.speed = self->speed;

	if (!self->wait)
		self->wait = -1;
	self->moveinfo.wait = self->wait;

	self->use = door_use;

	if (self->wait == -1)
		self->spawnflags |= DOOR_TOGGLE;

	self->classname = "func_door";

	if (self->spawnflags & 2)
	{
		self->s.renderfx |= RF_TRANSLUCENT;
	}

	gi.linkentity (self);
}


#define TRAIN_START_ON		1
#define TRAIN_TOGGLE		2
#define TRAIN_BLOCK_STOPS	4

// JOSEPH 25_APR-99
/*QUAKED func_train (0 .5 .8) ? START_ON TOGGLE BLOCK_STOPS SURF2_ALPHA
Trains are moving platforms that players can ride.
The targets origin specifies the min point of the train at each corner.
The train spawns at the first target it is pointing at.
If the train is the target of a button or trigger, it will not begin moving until activated.
speed	default 100
dmg		default	2
noise	looping sound to play when the train is in motion
*/
// END JOSEPH

void train_next (edict_t *self);

void train_blocked (edict_t *self, edict_t *other)
{
	if (!(other->svflags & SVF_MONSTER) && !(other->client) )
	{
		// give it a chance to go away on it's own terms (like gibs)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, 100000, 1, 0, MOD_CRUSH);
		// if it's still there, nuke it
		if (other)
			BecomeExplosion1 (other);
		return;
	}

	if (level.time < self->touch_debounce_time)
		return;

	if (!self->dmg)
		return;
	self->touch_debounce_time = level.time + 0.5;

	// Ridah, small objects shouldn't hurt
	if (VectorDistance( self->absmin, self->absmax) > 200)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);
}

void train_wait (edict_t *self)
{
	if (self->target_ent->pathtarget)
	{
		char	*savetarget;
		edict_t	*ent;

		ent = self->target_ent;
		savetarget = ent->target;
		ent->target = ent->pathtarget;
		G_UseTargets (ent, self->activator);
		ent->target = savetarget;

		// make sure we didn't get killed by a killtarget
		if (!self->inuse)
			return;
	}

	if (self->moveinfo.wait)
	{
		if (self->moveinfo.wait > 0)
		{
			self->nextthink = level.time + self->moveinfo.wait;
			self->think = train_next;
		}
		else if (self->spawnflags & TRAIN_TOGGLE)  // && wait < 0
		{
			train_next (self);
			self->spawnflags &= ~TRAIN_START_ON;
			VectorClear (self->velocity);
			self->nextthink = 0;
		}

		if (!(self->flags & FL_TEAMSLAVE))
		{
			if (self->moveinfo.sound_end)
				gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_end, 1, ATTN_STATIC, 0);
			self->s.sound = 0;
		}
	}
	else
	{
		train_next (self);
	}
	
}

void train_next (edict_t *self)
{
	edict_t		*ent;
	vec3_t		dest;
	qboolean	first;

	first = true;
again:
	if (!self->target)
	{
//		gi.dprintf ("train_next: no next target\n");
		return;
	}

	ent = G_PickTarget (self->target);
	if (!ent)
	{
		gi.dprintf ("train_next: bad target %s\n", self->target);
		return;
	}

	// JOSEPH 16-OCT-98
	self->moveinfo.accel = self->accel;
	self->moveinfo.decel = self->decel;
	
	if (ent->accel)
	{
		self->accel = 1;
		self->decel = ent->accel; //15;
	}
	else if (ent->decel)
	{
		self->accel = ent->decel; //15;
		self->decel = 1;
	}
	else
	{
		self->accel = self->decel = self->moveinfo.speed;
	}
	// END JOSEPH
	
	self->target = ent->target;

	// check for a teleport path_corner
	if (ent->spawnflags & 1)
	{
		if (!first)
		{
			gi.dprintf ("connected teleport path_corners, see %s at %s\n", ent->classname, vtos(ent->s.origin));
			return;
		}
		first = false;
		VectorSubtract (ent->s.origin, self->mins, self->s.origin);
		VectorCopy (self->s.origin, self->s.old_origin);
		// JOSEPH 23-APR-99
		self->s.event = EV_OTHER_TELEPORT;
		// END JOSEPH
		gi.linkentity (self);
		goto again;
	}

	self->moveinfo.wait = ent->wait;
	self->target_ent = ent;

	if (!(self->flags & FL_TEAMSLAVE))
	{
		if (self->moveinfo.sound_start)
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start, 1, ATTN_STATIC, 0);
		self->s.sound = self->moveinfo.sound_middle;
	}

	VectorSubtract (ent->s.origin, self->mins, dest);
	self->moveinfo.state = STATE_TOP;
	VectorCopy (self->s.origin, self->moveinfo.start_origin);
	VectorCopy (dest, self->moveinfo.end_origin);
	Move_Calc (self, dest, train_wait);
	self->spawnflags |= TRAIN_START_ON;

// BEGIN:	Xatrix/Ridah/Navigator/12-apr-1999
	self->goalentity = ent;
// END:		Xatrix/Ridah/Navigator/12-apr-1999
}

void train_resume (edict_t *self)
{
	edict_t	*ent;
	vec3_t	dest;

	ent = self->target_ent;

	VectorSubtract (ent->s.origin, self->mins, dest);
	self->moveinfo.state = STATE_TOP;
	VectorCopy (self->s.origin, self->moveinfo.start_origin);
	VectorCopy (dest, self->moveinfo.end_origin);
	Move_Calc (self, dest, train_wait);
	self->spawnflags |= TRAIN_START_ON;
}

void func_train_find (edict_t *self)
{
	edict_t *ent;

	if (!self->target)
	{
		gi.dprintf ("train_find: no target\n");
		return;
	}
	ent = G_PickTarget (self->target);
	if (!ent)
	{
		gi.dprintf ("train_find: target %s not found\n", self->target);
		return;
	}

	// JOSEPH 16-OCT-98
	if (ent->accel)
	{
		self->accel = 1;
		self->decel = ent->accel; //15;
	}
	else if (ent->decel)
	{
		self->accel = ent->decel; //15;
		self->decel = 1;
	}
	else
	{
		self->accel = self->decel = self->moveinfo.speed;
	}
	// END JOSEPH		
	
	self->target = ent->target;

	VectorSubtract (ent->s.origin, self->mins, self->s.origin);
	gi.linkentity (self);

	// if not triggered, start immediately
	if (!self->targetname)
		self->spawnflags |= TRAIN_START_ON;

	if (self->spawnflags & TRAIN_START_ON)
	{
		self->nextthink = level.time + FRAMETIME;
		self->think = train_next;
		self->activator = self;
	}

// BEGIN:	Xatrix/Ridah/Navigator/12-apr-1999
	self->goalentity = ent;
// END:		Xatrix/Ridah/Navigator/12-apr-1999
}

void train_use (edict_t *self, edict_t *other, edict_t *activator)
{
// BEGIN:	Xatrix/Ridah/Navigator/09-apr-1998
	// record the start position of this moving entity
	VectorCopy(self->s.origin, self->cast_info.last_sighting);
	self->last_goal = self->goalentity;
// END:		Xatrix/Ridah/Navigator/09-apr-1998

	self->activator = activator;

	if (self->spawnflags & TRAIN_START_ON)
	{
		if (!(self->spawnflags & TRAIN_TOGGLE))
			return;
		self->spawnflags &= ~TRAIN_START_ON;
		VectorClear (self->velocity);
		self->nextthink = 0;
	}
	else
	{
		if (self->target_ent)
			train_resume(self);
		else
			train_next(self);
	}
}

// JOSEPH 12-MAY-99
void Think_train_sound_B (edict_t *ent)
{
	if ((ent->handle) && (ent->handle->moveinfo.sound_middle))
	{
		if (ent->handle->velocity[0] || ent->handle->velocity[1] || ent->handle->velocity[2] ||
			ent->handle->avelocity[0] || ent->handle->avelocity[1] || ent->handle->avelocity[2])
		{
			vec3_t origin;
			
			VectorAdd (ent->handle->absmin, ent->handle->absmax, origin);				
			VectorScale (origin, 0.5, origin);

			VectorCopy (origin, ent->s.origin);
			
			gi.positioned_sound(ent->s.origin, ent, CHAN_AUTO, ent->handle->moveinfo.sound_middle, 1, 1, 0);
			
			ent->nextthink = level.time + ent->handle->reactdelay;
		}
		else
		{
			ent->nextthink = level.time + 0.1;			
		}
	}
}

void Think_train_sound2_B (edict_t *ent)
{
	if ((ent->handle) && (ent->handle->handle))
	{
		vec3_t origin;
	
		VectorAdd (ent->handle->handle->absmin, ent->handle->handle->absmax, origin);				
		VectorScale (origin, 0.5, origin);

		VectorCopy (origin, ent->handle->s.origin);
	}
	
	ent->nextthink = level.time + 0.1;
}

void Start_train_sound_B (edict_t *ent)
{
	edict_t	*sound = NULL;
	edict_t	*sound2 = NULL;

	sound = G_Spawn();
	
	if (!sound)
		return;

	sound2 = G_Spawn();
	
	if (!sound2)
		return;

	gi.linkentity (sound);
	gi.linkentity (sound2);

	sound->handle = ent;
	sound2->handle = sound;

	sound->think = Think_train_sound_B;
	Think_train_sound_B(sound);

	sound2->think = Think_train_sound2_B;
	sound2->nextthink = level.time + 0.1;

	return;
}

void SP_func_train (edict_t *self)
{
	self->movetype = MOVETYPE_PUSH;

	VectorClear (self->s.angles);
	self->blocked = train_blocked;
	if (self->spawnflags & TRAIN_BLOCK_STOPS)
		self->dmg = 0;
	else
	{
		if (!self->dmg)
			self->dmg = 100;
	}
	self->solid = SOLID_BSP;
	gi.setmodel (self, self->model);

	//if (st.noise)
	//	self->moveinfo.sound_middle = gi.soundindex  (st.noise);

	if (!self->speed)
		self->speed = 100;

	self->moveinfo.speed = self->speed;
	self->moveinfo.accel = self->moveinfo.decel = self->moveinfo.speed;

	self->use = train_use;

	// JOSEPH 25-APR-99
	if (self->spawnflags & 8)
		self->s.renderfx2 |= RF2_SURF_ALPHA;
	// END JOSEPH

	gi.linkentity (self);

	if (self->target)
	{
		// start trains on the second frame, to make sure their targets have had
		// a chance to spawn
		self->nextthink = level.time + FRAMETIME;
		self->think = func_train_find;
	}
	else
	{
		gi.dprintf ("func_train without a target at %s\n", vtos(self->absmin));
	}

	if (st.noise)
	{	
		char string[256];
		
		sprintf(string, "%s%s", st.noise, ".wav");
		
		self->moveinfo.sound_middle = gi.soundindex(string);
		if (!self->reactdelay)
			self->reactdelay = 1.0;
		Start_train_sound_B (self);
	}
}
// END JOSEPH


// JOSEPH 25-APR-99
/*QUAKED func_train_rotating (0 .5 .8) ? START_ON TOGGLE BLOCK_STOPS SURF2_ALPHA
Trains are moving platforms that players can ride.
The targets origin specifies the min point of the train at each corner.
The train spawns at the first target it is pointing at.
If the train is the target of a button or trigger, it will not begin moving until activated.
dmg		   default	2
noise	   looping sound to play when the train is in motion
reactdelay length of the sound in seconds

  On the path corner:
speed    departure speed from that corner 
rotate   angle change for X Y Z to next corner 
duration duration for angle change (overrides speed)
*/
// END JOSEPH

float AngleAdd (float a2, float a1)
{
	return (a1 + a2);
}

void Move_Begin_rotating (edict_t *ent)
{
	float	frames;

    // Stand still rotation 
	if (ent->durationflag)
    {
		ent->nextthink = level.time + (ent->lastduration);
		ent->think = Move_Final;
		return;
    }

	if (((ent->moveinfo.speed * FRAMETIME) >= ent->moveinfo.remaining_distance))  
	{
		Move_Final(ent);
		return;
	}
	
	VectorScale (ent->moveinfo.dir, ent->moveinfo.speed, ent->velocity);
	frames = floor((ent->moveinfo.remaining_distance / ent->moveinfo.speed) / FRAMETIME);
	ent->moveinfo.remaining_distance -= frames * ent->moveinfo.speed * FRAMETIME;
	ent->nextthink = level.time + (frames * FRAMETIME);
	ent->think = Move_Final;
}

void Move_Calc_rotating (edict_t *ent, vec3_t dest, void(*func)(edict_t*))
{
// BEGIN:	Xatrix/Ridah/Navigator/09-apr-1998
	// record the start and ending positions of this moving entity
	VectorCopy(ent->s.origin, ent->cast_info.last_sighting);
	VectorCopy(dest, ent->cast_info.saved_goal);
// END:		Xatrix/Ridah/Navigator/09-apr-1998

    //gi.dprintf ("MIN%s MAX%s", vtos(ent->mins), vtos(ent->maxs));
	
	VectorClear (ent->velocity);
	VectorSubtract (dest, ent->s.origin, ent->moveinfo.dir);
	ent->moveinfo.remaining_distance = VectorNormalize (ent->moveinfo.dir);
	ent->moveinfo.endfunc = func;

	if (ent->moveinfo.speed == ent->moveinfo.accel && ent->moveinfo.speed == ent->moveinfo.decel)
	{
		if (level.current_entity == ((ent->flags & FL_TEAMSLAVE) ? ent->teammaster : ent))
		{
			Move_Begin_rotating (ent);
		}
		else
		{
			ent->nextthink = level.time + FRAMETIME;
			ent->think = Move_Begin_rotating;
		}
	}
	else
	{
		// accelerative
		ent->moveinfo.current_speed = 0;
		ent->think = Think_AccelMove;
		ent->nextthink = level.time + FRAMETIME;
	}
}

void train_next_rotating (edict_t *self);

void train_blocked_rotating (edict_t *self, edict_t *other)
{
	
	//gi.dprintf ("train_blocked_rotating %s\n", vtos(self->s.angles));
	if (!(other->svflags & SVF_MONSTER) && !(other->client) )
	{
		// give it a chance to go away on it's own terms (like gibs)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, 100000, 1, 0, MOD_CRUSH);
		// if it's still there, nuke it
		if (other)
			BecomeExplosion1 (other);
		return;
	}

	if (level.time < self->touch_debounce_time)
		return;

	if (!self->dmg)
		return;
	self->touch_debounce_time = level.time + 0.5;

	// Ridah, small objects shouldn't hurt
	if (VectorDistance( self->absmin, self->absmax) > 200)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);
}

void train_wait_rotating (edict_t *self)
{
	if (self->target_ent->pathtarget)
	{
		char	*savetarget;
		edict_t	*ent;

		ent = self->target_ent;
		savetarget = ent->target;
		ent->target = ent->pathtarget;
		G_UseTargets (ent, self->activator);
		ent->target = savetarget;

		// make sure we didn't get killed by a killtarget
		if (!self->inuse)
			return;
	}

	if (self->moveinfo.wait)
	{
		VectorClear(self->avelocity);
		
		// JOSEPH 1-OCT-98
		// Force proper angle
		VectorCopy(self->angletarget, self->s.angles);
		
		if (self->moveinfo.wait > 0)
		{
			self->nextthink = level.time + self->moveinfo.wait;
			self->think = train_next_rotating;
		}
		else if (self->spawnflags & TRAIN_TOGGLE)  // && wait < 0
		{
			train_next_rotating (self);
			self->avelflag = 1;
			VectorCopy(self->avelocity, self->save_avel);
			VectorClear(self->avelocity);
			self->spawnflags &= ~TRAIN_START_ON;
			VectorClear (self->velocity);
			self->nextthink = 0;
		}

		if (!(self->flags & FL_TEAMSLAVE))
		{
			// JOSEPH 5-APR-99
			//if (self->moveinfo.sound_end)
			//	gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_end, 1, ATTN_STATIC, 0);
			//self->s.sound = 0;
			// END JOSEPH
		}
	}
	else
	{
		train_next_rotating (self);
	}
	
}

// JOSEPH 6-NOV-98
void train_next_rotating (edict_t *self)
{
	edict_t			*ent;
	vec3_t			dest;
	vec3_t			dir;
	float			remain;
	qboolean		first;
	int				frames;

	first = true;
again:
	if (!self->target)
	{
//		gi.dprintf ("train_next: no next target\n");
		return;
	}
	
	ent = G_PickTarget (self->target);

	if (!ent)
	{
		gi.dprintf ("train_next: bad target %s\n", self->target);
		return;
	}

	// JOSEPH 20-APR-99
	self->moveinfo.accel = self->accel;
	self->moveinfo.decel = self->decel;
	
	if (ent->accel)
	{
		self->accel = 1;
		self->decel = ent->accel; //15;
	}
	else if (ent->decel)
	{
		self->accel = ent->decel; //15;
		self->decel = 1;
	}
	else
	{
		self->accel = self->decel = self->moveinfo.speed;
	}
	// END JOSEPH
	
	// Clear stand still duration flag
	self->durationflag = 0;
	
	// JOSEPH 6-JAN-99
	/*if ((self->name) && (!strcmp(self->name, "Joe9000")))
	{
		gi.dprintf ("TARGET ANGLE %s\n", vtos(self->angletarget));
	}*/
	//gi.dprintf ("SPEED %f\n", self->speed);
	//gi.dprintf ("DURATION %f\n", self->duration);
	// END JOSEPH
	
	// Set speed
	if (self->firstnode)
    {
		// Set rotation from saved first node
		VectorSubtract(ent->s.origin, self->nodeorigin, dir);
		remain = VectorNormalize (dir);		
		
		if (!self->duration)
		{
			// Set speed from saved first node
			self->moveinfo.speed = self->moveinfo.accel = self->moveinfo.decel = self->speed;

			frames = floor((remain / self->moveinfo.speed) / FRAMETIME);	
			if (frames) frames++;

			if (self->rotate[0]) self->avelocity[0] = (self->rotate[0] / frames)*10;	
				else self->avelocity[0] = 0;
			if (self->rotate[1]) self->avelocity[1] = (self->rotate[1] / frames)*10;	
				else self->avelocity[1] = 0;		
			if (self->rotate[2]) self->avelocity[2] = (self->rotate[2] / frames)*10;	
				else self->avelocity[2] = 0;  
		}
		else if (remain)
		{
			// Set speed from duration saved from current node	
			self->moveinfo.speed = self->moveinfo.accel = self->moveinfo.decel = (remain / (self->duration));

			frames = floor((remain / self->moveinfo.speed) / FRAMETIME);	
			if (frames) frames++;

			if (self->rotate[0]) self->avelocity[0] = (self->rotate[0] / frames)*10;	
				else self->avelocity[0] = 0;
			if (self->rotate[1]) self->avelocity[1] = (self->rotate[1] / frames)*10;	
				else self->avelocity[1] = 0;		
			if (self->rotate[2]) self->avelocity[2] = (self->rotate[2] / frames)*10;	
				else self->avelocity[2] = 0;  
		}
		else
		{
			// Set stand still duration flag
			self->durationflag = 1;
			
			if (self->rotate[0]) self->avelocity[0] = (self->rotate[0] / (self->duration/*+0.1*/));	
				else self->avelocity[0] = 0;
			if (self->rotate[1]) self->avelocity[1] = (self->rotate[1] / (self->duration/*+0.1*/));	
				else self->avelocity[1] = 0;		
			if (self->rotate[2]) self->avelocity[2] = (self->rotate[2] / (self->duration/*+0.1*/));	
				else self->avelocity[2] = 0;  
		}

		self->firstnode = 0;  
    }
	else
    {
		// Force proper angle
		VectorCopy(self->angletarget, self->s.angles);
	    
		//gi.dprintf ("CURRENT ANGLE %s\n", vtos(self->s.angles));
		//gi.dprintf ("TARGET  ANGLE %s\n", vtos(self->angletarget));
		//gi.dprintf ("SPEED %f\n", self->speed);
		//gi.dprintf ("DURATION %f\n", self->duration);

		// Set rotation from saved current node
		VectorSubtract(ent->s.origin, self->nodeorigin, dir);
		remain = VectorNormalize (dir);
		
		if (!self->duration)
		{	
			// Set speed from saved current node
			self->moveinfo.speed = self->moveinfo.accel = self->moveinfo.decel = self->speed;		
			
			frames = floor((remain / self->moveinfo.speed) / FRAMETIME);	
			if (frames) frames++;
			
			if (self->rotate[0]) self->avelocity[0] = (self->rotate[0] / frames)*10;	
				else self->avelocity[0] = 0;
			if (self->rotate[1]) self->avelocity[1] = (self->rotate[1] / frames)*10;	
				else self->avelocity[1] = 0;		
			if (self->rotate[2]) self->avelocity[2] = (self->rotate[2] / frames)*10;	
				else self->avelocity[2] = 0;    
		}
		else if (remain)
		{
			// Set speed from duration saved from current node	
			self->moveinfo.speed = self->moveinfo.accel = self->moveinfo.decel = ((remain / self->duration));		
			
			frames = floor((remain / self->moveinfo.speed) / FRAMETIME);	
			if (frames) frames++;
			
			if (self->rotate[0]) self->avelocity[0] = (self->rotate[0] / frames)*10;	
				else self->avelocity[0] = 0;
			if (self->rotate[1]) self->avelocity[1] = (self->rotate[1] / frames)*10;	
				else self->avelocity[1] = 0;		
			if (self->rotate[2]) self->avelocity[2] = (self->rotate[2] / frames)*10;	
				else self->avelocity[2] = 0;    
		}
		else
		{
			// Set stand still duration flag
			self->durationflag = 1;

			self->moveinfo.speed = self->moveinfo.accel = self->moveinfo.decel = 0;

			if (self->rotate[0]) self->avelocity[0] = (self->rotate[0] / (self->duration));	
				else self->avelocity[0] = 0;
			if (self->rotate[1]) self->avelocity[1] = (self->rotate[1] / (self->duration));	
				else self->avelocity[1] = 0;		
			if (self->rotate[2]) self->avelocity[2] = (self->rotate[2] / (self->duration));	
				else self->avelocity[2] = 0;   
		}
	}
	
	// Save speed for next node or continue at current speed if node speed = 0 
	if (ent->speed) self->speed = ent->speed;

	// Save duration for calc
	self->lastduration = self->duration;
	
	// Save duration for next node
	self->duration = ent->duration;

	// Save node origin for next node
	VectorCopy(ent->s.origin, self->nodeorigin);
	
	// Save target angle for next node
	self->angletarget[0] = AngleAdd(self->s.angles[0], self->rotate[0]);
	self->angletarget[1] = AngleAdd(self->s.angles[1], self->rotate[1]);
	self->angletarget[2] = AngleAdd(self->s.angles[2], self->rotate[2]);
		
	// Save rotation info from next node
	VectorCopy(ent->rotate, self->rotate);
	
	self->target = ent->target;

	// check for a teleport path_corner
	if (ent->spawnflags & 1)
	{
		if (!first)
		{
			gi.dprintf ("connected teleport path_corners, see %s at %s\n", ent->classname, vtos(ent->s.origin));
			return;
		}
		first = false;
		// JOSEPH 2-APR_99
		VectorSubtract (ent->s.origin, /*self->mins*/vec3_origin, self->s.origin);
		// END JOSEPH
		VectorCopy (self->s.origin, self->s.old_origin);
		gi.linkentity (self);
		goto again;
	}

	self->moveinfo.wait = ent->wait;
	self->target_ent = ent;

	if (!(self->flags & FL_TEAMSLAVE))
	{
		if (self->moveinfo.sound_start)
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start, 1, ATTN_STATIC, 0);
		// JOSEPH 5-APR-99
		//self->s.sound = self->moveinfo.sound_middle;
		// END JOSEPH
	}

	// JOSEPH 2-APR-99
	VectorSubtract (ent->s.origin, vec3_origin, dest);
	// END JOSEPH	
	self->moveinfo.state = STATE_TOP;
	VectorCopy (self->s.origin, self->moveinfo.start_origin);
	VectorCopy (dest, self->moveinfo.end_origin);
	Move_Calc_rotating (self, dest, train_wait_rotating);
	self->spawnflags |= TRAIN_START_ON;
}
// END JOSEPH

void train_resume_rotating (edict_t *self)
{
	edict_t	*ent;
	vec3_t	dest;
    
	ent = self->target_ent;

	// JOSEPH 2-APR-99
	VectorSubtract (ent->s.origin, /*self->mins*/vec3_origin, dest);
	// END JOSEPH
	self->moveinfo.state = STATE_TOP;
	VectorCopy (self->s.origin, self->moveinfo.start_origin);
	VectorCopy (dest, self->moveinfo.end_origin);
	Move_Calc_rotating (self, dest, train_wait_rotating);
	if (self->avelflag)
	{
		VectorCopy(self->save_avel, self->avelocity);
		self->avelflag = 0;
	}
	self->spawnflags |= TRAIN_START_ON;
}

void func_train_find_rotating (edict_t *self)
{
	edict_t *ent;
		
	if (!self->target)
	{
		gi.dprintf ("train_find: no target\n");
		return;
	}
	ent = G_PickTarget (self->target);
	if (!ent)
	{
		gi.dprintf ("train_find: target %s not found\n", self->target);
		return;
	}
	self->target = ent->target;

	// JOSEPH 20-APR-99
	if (ent->accel)
	{
		self->accel = 1;
		self->decel = ent->accel; //15;
	}
	else if (ent->decel)
	{
		self->accel = ent->decel; //15;
		self->decel = 1;
	}
	else
	{
		self->accel = self->decel = self->moveinfo.speed;
	}
	// END JOSEPH		
	
	// Save info from first node
	self->speed = ent->speed;
	self->duration = ent->duration;
	VectorCopy(ent->rotate, self->rotate);
	VectorCopy(ent->s.origin, self->nodeorigin);

	// JOSEPH 21-APR-99
	VectorCopy(ent->s.origin, self->s.origin);
	// END JOSEPH
	
	// Set first node flag
	self->firstnode = 1;	

	//VectorSubtract (ent->s.origin, self->mins, self->s.origin);
	//gi.linkentity (self);

	// if not triggered, start immediately
	if (!self->targetname)
		self->spawnflags |= TRAIN_START_ON;

	if (self->spawnflags & TRAIN_START_ON)
	{
		self->nextthink = level.time + FRAMETIME;
		self->think = train_next_rotating;
		self->activator = self;
	}
}

void train_use_rotating (edict_t *self, edict_t *other, edict_t *activator)
{
	self->activator = activator;

	if (self->spawnflags & TRAIN_START_ON)
	{
		if (!(self->spawnflags & TRAIN_TOGGLE))
			return;
		self->spawnflags &= ~TRAIN_START_ON;
		VectorClear (self->velocity);
		self->nextthink = 0;
	}
	else
	{
		if (self->target_ent)
			train_resume_rotating(self);
		else
			train_next_rotating(self);
	}
}

// JOSEPH 6-APR-99
void Think_train_sound (edict_t *ent)
{
	if ((ent->handle) && (ent->handle->moveinfo.sound_middle))
	{
		if (ent->handle->velocity[0] || ent->handle->velocity[1] || ent->handle->velocity[2] ||
			ent->handle->avelocity[0] || ent->handle->avelocity[1] || ent->handle->avelocity[2])
		{
			VectorCopy (ent->handle->s.origin, ent->s.origin);
			gi.positioned_sound(ent->s.origin, ent, CHAN_AUTO, ent->handle->moveinfo.sound_middle, 1, 1, 0);
			
			ent->nextthink = level.time + ent->handle->reactdelay;
		}
		else
		{
			ent->nextthink = level.time + 0.1;			
		}
	}
}

void Think_train_sound2 (edict_t *ent)
{
	if ((ent->handle) && (ent->handle->handle))
	{
		VectorCopy (ent->handle->handle->s.origin, ent->handle->s.origin);
	}
	
	ent->nextthink = level.time + 0.1;
}

void Start_train_sound (edict_t *ent)
{
	edict_t	*sound = NULL;
	edict_t	*sound2 = NULL;

	sound = G_Spawn();
	
	if (!sound)
		return;

	sound2 = G_Spawn();
	
	if (!sound2)
		return;

	gi.linkentity (sound);
	gi.linkentity (sound2);

	sound->handle = ent;
	sound2->handle = sound;

	sound->think = Think_train_sound;
	Think_train_sound(sound);

	sound2->think = Think_train_sound2;
	sound2->nextthink = level.time + 0.1;

	return;
}
// END JOSEPH

// JOSEPH 5-APR-99
void touch_train_die (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (other->health <= 0)
		return;

	T_Damage (other, ent, ent, vec3_origin, other->s.origin, vec3_origin, 666, 1, 0, MOD_CRUSH);		
}
// END JOSEPH

// JOSEPH 6-APR-99
void SP_func_train_rotating (edict_t *self)
{
	// hack for now
	//return;
	
	self->movetype = MOVETYPE_PUSH;
	self->solid = SOLID_BSP;
	
	VectorClear (self->s.angles);
	self->blocked = train_blocked_rotating;
	if (self->spawnflags & TRAIN_BLOCK_STOPS)
		self->dmg = 0;
	else
	{
		if (!self->dmg)
			self->dmg = 100;
	}

	// JOSEPH 20-APR-99
	self->moveinfo.speed = self->speed;
	self->moveinfo.accel = self->moveinfo.decel = self->moveinfo.speed;
	// END JOSEPH
	
	gi.setmodel (self, self->model);

	//if (st.noise)
	//	self->moveinfo.sound_middle = gi.soundindex  (st.noise);

	self->use = train_use_rotating;

	// JOSEPH 2-APR-99
	//VectorClear(self->mins);
	// END JOSEPH

	self->maxs[0] *= 2;
	self->maxs[1] *= 2;
	self->maxs[2] *= 2;	
	
	// JOSEPH 25-APR-99
	if (self->spawnflags & 8)
		self->s.renderfx2 |= RF2_SURF_ALPHA;
	// END JOSEPH
		
	gi.linkentity (self);
	
	// set the abs box - expand for rotation
	{
		float		max, v;
		int			i;

		max = 0;
		for (i=0 ; i<3 ; i++)
		{
			v =fabs(self->mins[i]);
			if (v > max)
				max = v;
			v =fabs(self->maxs[i]);
			if (v > max)
				max = v;
		}
		for (i=0 ; i<3 ; i++)
		{
			self->absmin[i] = self->s.origin[i] - max;
			self->absmax[i] = self->s.origin[i] + max;
		}
	}
	
	if (self->dmg == 666)
	{
		self->touch = touch_train_die;
	}

	if (self->target)
	{
		// start trains on the second frame, to make sure their targets have had
		// a chance to spawn
		self->nextthink = level.time + FRAMETIME;
		self->think = func_train_find_rotating;
	}
	// JOSEPH 8-APR-99
	else
	{
		gi.dprintf ("func_train_rotating without a target at %s\n", vtos(self->absmin));
	}

	if (st.noise)
	{	
		char string[256];
		
		//self->moveinfo.sound_middle = gi.soundindex("world/trainout.wav");
		//self->reactdelay = 1.0;
		
		sprintf(string, "%s%s", st.noise, ".wav");
		
		self->moveinfo.sound_middle = gi.soundindex(string);
		if (!self->reactdelay)
			self->reactdelay = 1.0;
		Start_train_sound (self);
	}
	// END JOSEPH
}
// END JOSEPH


/*QUAKED trigger_elevator (0.3 0.1 0.6) (-8 -8 -8) (8 8 8)
*/
void trigger_elevator_use (edict_t *self, edict_t *other, edict_t *activator)
{
	edict_t *target;

	
	// RAFAEL
/*
	if (activator)
	if (self->activate_flags & ACTIVATE_GENERAL && activator->client)
	{
		if (!(self->activate_flags & ACTIVATE_AND_OPEN))
		{
			//gi.dprintf ("activator: %s next to door\n", activator->classname);	
			return;
		}
		else
		{
			self->activate_flags &= ~ACTIVATE_AND_OPEN;
			//gi.dprintf ("activator: %s used the door\n", activator->classname);	
		}
	}
*/
	
	if (self->movetarget->nextthink)
	{
//		gi.dprintf("elevator busy\n");
		return;
	}

	if (!other->pathtarget)
	{
		gi.dprintf("elevator used with no pathtarget\n");
		return;
	}

	target = G_PickTarget (other->pathtarget);
	if (!target)
	{
		gi.dprintf("elevator used with bad pathtarget: %s\n", other->pathtarget);
		return;
	}

	self->movetarget->target_ent = target;
	train_resume (self->movetarget);
}

void trigger_elevator_init (edict_t *self)
{
	if (!self->target)
	{
		gi.dprintf("trigger_elevator has no target\n");
		return;
	}
	self->movetarget = G_PickTarget (self->target);
	if (!self->movetarget)
	{
		gi.dprintf("trigger_elevator unable to find target %s\n", self->target);
		return;
	}
	if (strcmp(self->movetarget->classname, "func_train") != 0)
	{
		gi.dprintf("trigger_elevator target %s is not a train\n", self->target);
		return;
	}

	self->use = trigger_elevator_use;
	self->svflags = SVF_NOCLIENT;

}

void SP_trigger_elevator (edict_t *self)
{
	// RAFAEL
//	if (!(self->spawnflags & 2))
//		self->activate_flags |= ACTIVATE_GENERAL;

	self->think = trigger_elevator_init;
	self->nextthink = level.time + FRAMETIME;
}


/*QUAKED func_timer (0.3 0.1 0.6) (-8 -8 -8) (8 8 8) START_ON
"wait"			base time between triggering all targets, default is 1
"random"		wait variance, default is 0

so, the basic time between firing is a random time between
(wait - random) and (wait + random)

"delay"			delay before first firing when turned on, default is 0

"pausetime"		additional delay used only the very first time
				and only if spawned with START_ON

These can used but not touched.
*/
void func_timer_think (edict_t *self)
{
	G_UseTargets (self, self->activator);
	self->nextthink = level.time + self->wait + crandom() * self->random;
}

void func_timer_use (edict_t *self, edict_t *other, edict_t *activator)
{
	self->activator = activator;

	// if on, turn it off
	if (self->nextthink)
	{
		self->nextthink = 0;
		return;
	}

	// turn it on
	if (self->delay)
		self->nextthink = level.time + self->delay;
	else
		func_timer_think (self);
}

void SP_func_timer (edict_t *self)
{
	if (!self->wait)
		self->wait = 1.0;

	self->use = func_timer_use;
	self->think = func_timer_think;

	if (self->random >= self->wait)
	{
		self->random = self->wait - FRAMETIME;
		gi.dprintf("func_timer at %s has random >= wait\n", vtos(self->s.origin));
	}

	if (self->spawnflags & 1)
	{
		self->nextthink = level.time + 1.0 + st.pausetime + self->delay + self->wait + crandom() * self->random;
		self->activator = self;
	}

	self->svflags = SVF_NOCLIENT;
}


/*QUAKED func_conveyor (0 .5 .8) ? START_ON TOGGLE
Conveyors are stationary brushes that move what's on them.
The brush should be have a surface with at least one current content enabled.
speed	default 100
*/

void func_conveyor_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (self->spawnflags & 1)
	{
		self->speed = 0;
		self->spawnflags &= ~1;
	}
	else
	{
		self->speed = self->count;
		self->spawnflags |= 1;
	}

	if (!(self->spawnflags & 2))
		self->count = 0;
}

void SP_func_conveyor (edict_t *self)
{
	if (!self->speed)
		self->speed = 100;

	if (!(self->spawnflags & 1))
	{
		self->count = self->speed;
		self->speed = 0;
	}

	self->use = func_conveyor_use;

	gi.setmodel (self, self->model);
	self->solid = SOLID_BSP;
	gi.linkentity (self);
}


/*QUAKED func_door_secret (0 .5 .8) ? always_shoot 1st_left 1st_down
A secret door.  Slide back and then to the side.

open_once		doors never closes
1st_left		1st move is left of arrow
1st_down		1st move is down from arrow
always_shoot	door is shootebale even if targeted

"angle"		determines the direction
"dmg"		damage to inflic when blocked (default 2)
"wait"		how long to hold in the open position (default 5, -1 means hold)
*/

#define SECRET_ALWAYS_SHOOT	1
#define SECRET_1ST_LEFT		2
#define SECRET_1ST_DOWN		4

void door_secret_move1 (edict_t *self);
void door_secret_move2 (edict_t *self);
void door_secret_move3 (edict_t *self);
void door_secret_move4 (edict_t *self);
void door_secret_move5 (edict_t *self);
void door_secret_move6 (edict_t *self);
void door_secret_done (edict_t *self);

void door_secret_use (edict_t *self, edict_t *other, edict_t *activator)
{
	// make sure we're not already moving
	if (!VectorCompare(self->s.origin, vec3_origin))
		return;

	Move_Calc (self, self->pos1, door_secret_move1);
	door_use_areaportals (self, true);
}

void door_secret_move1 (edict_t *self)
{
	self->nextthink = level.time + 1.0;
	self->think = door_secret_move2;
}

void door_secret_move2 (edict_t *self)
{
	Move_Calc (self, self->pos2, door_secret_move3);
}

void door_secret_move3 (edict_t *self)
{
	if (self->wait == -1)
		return;
	self->nextthink = level.time + self->wait;
	self->think = door_secret_move4;
}

void door_secret_move4 (edict_t *self)
{
	Move_Calc (self, self->pos1, door_secret_move5);
}

void door_secret_move5 (edict_t *self)
{
	self->nextthink = level.time + 1.0;
	self->think = door_secret_move6;
}

void door_secret_move6 (edict_t *self)
{
	Move_Calc (self, vec3_origin, door_secret_done);
}

void door_secret_done (edict_t *self)
{
	if (!(self->targetname) || (self->spawnflags & SECRET_ALWAYS_SHOOT))
	{
		self->health = 0;
		self->takedamage = DAMAGE_YES;
	}
	door_use_areaportals (self, false);
}

void door_secret_blocked  (edict_t *self, edict_t *other)
{
	if (!(other->svflags & SVF_MONSTER) && !(other->client) )
	{
		// give it a chance to go away on it's own terms (like gibs)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, 100000, 1, 0, MOD_CRUSH);
		// if it's still there, nuke it
		if (other)
			BecomeExplosion1 (other);
		return;
	}

	if (level.time < self->touch_debounce_time)
		return;
	self->touch_debounce_time = level.time + 0.5;

	// Ridah, small objects shouldn't hurt
	if (VectorDistance( self->absmin, self->absmax) > 200)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);
}

void door_secret_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	door_secret_use (self, attacker, attacker);
}

void SP_func_door_secret (edict_t *ent)
{
	vec3_t	forward, right, up;
	float	side;
	float	width;
	float	length;

	ent->moveinfo.sound_start = gi.soundindex  ("doors/dr1_strt.wav");
	ent->moveinfo.sound_middle = gi.soundindex  ("doors/dr1_mid.wav");
	ent->moveinfo.sound_end = gi.soundindex  ("doors/dr1_end.wav");

	ent->movetype = MOVETYPE_PUSH;
	ent->solid = SOLID_BSP;
	gi.setmodel (ent, ent->model);

	ent->blocked = door_secret_blocked;
	ent->use = door_secret_use;

	if (!(ent->targetname) || (ent->spawnflags & SECRET_ALWAYS_SHOOT))
	{
		ent->health = 0;
		ent->takedamage = DAMAGE_YES;
		ent->die = door_secret_die;
	}

	if (!ent->dmg)
		ent->dmg = 2;

	if (!ent->wait)
		ent->wait = 5;

	ent->moveinfo.accel =
	ent->moveinfo.decel =
	ent->moveinfo.speed = 50;

	// calculate positions
	AngleVectors (ent->s.angles, forward, right, up);
	VectorClear (ent->s.angles);
	side = 1.0 - (ent->spawnflags & SECRET_1ST_LEFT);
	if (ent->spawnflags & SECRET_1ST_DOWN)
		width = fabs(DotProduct(up, ent->size));
	else
		width = fabs(DotProduct(right, ent->size));
	length = fabs(DotProduct(forward, ent->size));
	if (ent->spawnflags & SECRET_1ST_DOWN)
		VectorMA (ent->s.origin, -1 * width, up, ent->pos1);
	else
		VectorMA (ent->s.origin, side * width, right, ent->pos1);
	VectorMA (ent->pos1, length, forward, ent->pos2);

	if (ent->health)
	{
		ent->takedamage = DAMAGE_YES;
		ent->die = door_killed;
		ent->max_health = ent->health;
	}
	else if (ent->targetname && ent->message)
	{
		gi.soundindex ("misc/talk.wav");
		ent->touch = door_touch;
	}
	
	ent->classname = "func_door";

	gi.linkentity (ent);
}


/*QUAKED func_killbox (1 0 0) ?
Kills everything inside when fired, irrespective of protection.
*/
void use_killbox (edict_t *self, edict_t *other, edict_t *activator)
{
	KillBox (self);
}

void SP_func_killbox (edict_t *ent)
{
	gi.setmodel (ent, ent->model);
	ent->use = use_killbox;
	ent->svflags = SVF_NOCLIENT;
}

// JOSEPH 8-FEB-99
/*UAKED rotating_light (0 .5 .8) (-8 -8 -8) (8 8 8) START_OFF ALARM
"health"	if set, the light may be killed.
*/

// RAFAEL 
// note to self
// the lights will take damage from explosions
// this could leave a player in total darkness very bad
 
#define START_OFF	1

void rotating_light_alarm (edict_t *self)
{
	if (self->spawnflags & START_OFF)
	{
		self->think = NULL;
		self->nextthink = 0;	
	}
	else
	{
		gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start, 1, ATTN_STATIC, 0);
		self->nextthink = level.time + 1;
	}
}

void rotating_light_killed (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_WELDING_SPARKS);
	gi.WriteByte (30);
	gi.WritePosition (self->s.origin);
	gi.WriteDir (vec3_origin);
	gi.WriteByte (0xe0 + (rand()&7));
	gi.multicast (self->s.origin, MULTICAST_PVS);

	self->s.effects &= ~EF_SPINNINGLIGHTS;
	self->use = NULL;

	self->think = G_FreeEdict;	
	self->nextthink = level.time + 0.1;
	
}

static void rotating_light_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (self->spawnflags & START_OFF)
	{
		self->spawnflags &= ~START_OFF;
		self->s.effects |= EF_SPINNINGLIGHTS;

		if (self->spawnflags & 2)
		{
			self->think = rotating_light_alarm;
			self->nextthink = level.time + 0.1;
		}
	}
	else
	{
		self->spawnflags |= START_OFF;
		self->s.effects &= ~EF_SPINNINGLIGHTS;
	}
}
	

void SP_rotating_light (edict_t *self)
{

	self->movetype = MOVETYPE_STOP;
	self->solid = SOLID_BBOX;
	
	self->s.modelindex = gi.modelindex ("models/objects/light/tris.md2");
	
	self->s.frame = 0;
		
	self->use = rotating_light_use;
	
	if (self->spawnflags & START_OFF)
		self->s.effects &= ~EF_SPINNINGLIGHTS;
	else
	{
		self->s.effects |= EF_SPINNINGLIGHTS;
	}

	if (!self->speed)
		self->speed = 32;
	// this is a real cheap way
	// to set the radius of the light
	// self->s.frame = self->speed;

	if (!self->health)
	{
		self->health = 10;
		self->max_health = self->health;
		self->die = rotating_light_killed;
		self->takedamage = DAMAGE_YES;
	}
	else
	{
		self->max_health = self->health;
		self->die = rotating_light_killed;
		self->takedamage = DAMAGE_YES;
	}
	
	if (self->spawnflags & 2)
	{
		self->moveinfo.sound_start = gi.soundindex ("misc/alarm.wav");	
	}
	
	gi.linkentity (self);

}


/*UAKED func_object_repair (1 .5 0) (-8 -8 -8) (8 8 8) 
object to be repaired.
The default delay is 1 second
"delay" the delay in seconds for spark to occur
*/

void object_repair_fx (edict_t *ent)
{
 
 
	ent->nextthink = level.time + ent->delay;

	if (ent->health <= 100)
		ent->health++;
 	else
	{
		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_WELDING_SPARKS);
		gi.WriteByte (10);
		gi.WritePosition (ent->s.origin);
		gi.WriteDir (vec3_origin);
		gi.WriteByte (0xe0 + (rand()&7));
		gi.multicast (ent->s.origin, MULTICAST_PVS);
	}
	
}


void object_repair_dead (edict_t *ent)
{
	G_UseTargets (ent, ent);
	ent->nextthink = level.time + 0.1;
	ent->think = object_repair_fx;
}

void object_repair_sparks (edict_t *ent)
{
 
	if (ent->health < 0)
	{
		ent->nextthink = level.time + 0.1;
		ent->think = object_repair_dead;
		return;
	}

	ent->nextthink = level.time + ent->delay;
	
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_WELDING_SPARKS);
	gi.WriteByte (10);
	gi.WritePosition (ent->s.origin);
	gi.WriteDir (vec3_origin);
	gi.WriteByte (0xe0 + (rand()&7));
	gi.multicast (ent->s.origin, MULTICAST_PVS);
	
}

void SP_object_repair (edict_t *ent)
{
	ent->movetype = MOVETYPE_NONE;
	ent->solid = SOLID_BBOX;
	ent->classname = "object_repair";
	VectorSet (ent->mins, -8, -8, 8);
	VectorSet (ent->maxs, 8, 8, 8);
	ent->think = object_repair_sparks;
	ent->nextthink = level.time + 1.0;
	ent->health = 100;
	if (!ent->delay)
		ent->delay = 1.0;
	
}
// END JOSEPH 

// JOSEPH 26-APR-99
/*QUAKED func_lift (0 .5 .8) ? START_ON TOGGLE BLOCK_STOPS
Lifts are moving platforms that players can ride.
The targets origin specifies the min point of the lift at each corner.
The lift spawns at the first target it is pointing at.
If the lift is the target of a button or trigger, it will not begin moving until activated.
speed	default 100
dmg		default	2
noise	looping sound to play when the lift is in motion
target2 string ID for attached button
*/
// END JOSEPH

void lift_next (edict_t *self);

void lift_blocked (edict_t *self, edict_t *other)
{
	if (!(other->svflags & SVF_MONSTER) && !(other->client) )
	{
		// give it a chance to go away on it's own terms (like gibs)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, 100000, 1, 0, MOD_CRUSH);
		// if it's still there, nuke it
		if (other)
			BecomeExplosion1 (other);
		return;
	}

	if (level.time < self->touch_debounce_time)
		return;

	if (!self->dmg)
		return;
	self->touch_debounce_time = level.time + 0.5;

	// Ridah, small objects shouldn't hurt
	if (VectorDistance( self->absmin, self->absmax) > 200)
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);
}

void lift_wait (edict_t *self)
{
	if (self->target_ent->pathtarget)
	{
		char	*savetarget;
		edict_t	*ent;

		ent = self->target_ent;
		savetarget = ent->target;
		ent->target = ent->pathtarget;
		G_UseTargets (ent, self->activator);
		ent->target = savetarget;

		// make sure we didn't get killed by a killtarget
		if (!self->inuse)
			return;
	}

	if (self->moveinfo.wait)
	{
		if (self->moveinfo.wait > 0)
		{
			self->nextthink = level.time + self->moveinfo.wait;
			self->think = lift_next;
		}
		else if (self->spawnflags & TRAIN_TOGGLE)  // && wait < 0
		{
			lift_next (self);
			self->spawnflags &= ~TRAIN_START_ON;
			VectorClear (self->velocity);
			self->nextthink = 0;
		}

		if (!(self->flags & FL_TEAMSLAVE))
		{
			if (self->moveinfo.sound_end)
				gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_end, 1, ATTN_STATIC, 0);
			self->s.sound = 0;
		}
	}
	else
	{
		lift_next (self);
	}
	
}

void lift_next (edict_t *self)
{
	edict_t		*ent;
	vec3_t		dest;
	qboolean	first;

	first = true;
again:
	if (!self->target)
	{
//		gi.dprintf ("lift_next: no next target\n");
		return;
	}

	ent = G_PickTarget (self->target);
	if (!ent)
	{
		gi.dprintf ("lift_next: bad target %s\n", self->target);
		return;
	}

	self->target = ent->target;

	// check for a teleport path_corner
	if (ent->spawnflags & 1)
	{
		if (!first)
		{
			gi.dprintf ("connected teleport path_corners, see %s at %s\n", ent->classname, vtos(ent->s.origin));
			return;
		}
		first = false;
		VectorSubtract (ent->s.origin, self->mins, self->s.origin);
		VectorCopy (self->s.origin, self->s.old_origin);
		gi.linkentity (self);
		goto again;
	}

	self->moveinfo.wait = ent->wait;
	self->target_ent = ent;

	if (!(self->flags & FL_TEAMSLAVE))
	{
		if (self->moveinfo.sound_start)
			gi.sound (self, CHAN_NO_PHS_ADD+CHAN_VOICE, self->moveinfo.sound_start, 1, ATTN_STATIC, 0);
		self->s.sound = self->moveinfo.sound_middle;
	}

	VectorSubtract (ent->s.origin, self->mins, dest);
	self->moveinfo.state = STATE_TOP;
	VectorCopy (self->s.origin, self->moveinfo.start_origin);
	VectorCopy (dest, self->moveinfo.end_origin);
	Move_Calc (self, dest, lift_wait);
	self->spawnflags |= TRAIN_START_ON;

// BEGIN:	Xatrix/Ridah/Navigator/12-apr-1999
	self->goalentity = ent;
// END:		Xatrix/Ridah/Navigator/12-apr-1999
}

void lift_resume (edict_t *self)
{
	edict_t	*ent;
	vec3_t	dest;

	ent = self->target_ent;

	VectorSubtract (ent->s.origin, self->mins, dest);
	self->moveinfo.state = STATE_TOP;
	VectorCopy (self->s.origin, self->moveinfo.start_origin);
	VectorCopy (dest, self->moveinfo.end_origin);
	Move_Calc (self, dest, lift_wait);
	self->spawnflags |= TRAIN_START_ON;
}

void func_lift_find (edict_t *self)
{
	edict_t *ent;

	if (!self->target)
	{
		gi.dprintf ("lift_find: no target\n");
		return;
	}
	ent = G_PickTarget (self->target);
	if (!ent)
	{
		gi.dprintf ("lift_find: target %s not found\n", self->target);
		return;
	}

	self->target = ent->target;

	VectorSubtract (ent->s.origin, self->mins, self->s.origin);
	gi.linkentity (self);

	// JOSEPH 28-APR-99
	if (self->target2)
	{
		int i;
		edict_t	*e = NULL;
			
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "func_button")) &&
				(e->target2) &&(!strcmp(e->target2, self->target2)))
			{
				e->handleflag = self->s.origin[2] - e->s.origin[2];
			}
		}
	}
	// END JOSEPH

	// if not triggered, start immediately
	if (!self->targetname)
		self->spawnflags |= TRAIN_START_ON;

	if (self->spawnflags & TRAIN_START_ON)
	{
		self->nextthink = level.time + FRAMETIME;
		self->think = lift_next;
		self->activator = self;
	}

// BEGIN:	Xatrix/Ridah/Navigator/12-apr-1999
	self->goalentity = ent;
// END:		Xatrix/Ridah/Navigator/12-apr-1999
}

void lift_use (edict_t *self, edict_t *other, edict_t *activator)
{
// BEGIN:	Xatrix/Ridah/Navigator/09-apr-1998
	// record the start position of this moving entity
	VectorCopy(self->s.origin, self->cast_info.last_sighting);
	self->last_goal = self->goalentity;
// END:		Xatrix/Ridah/Navigator/09-apr-1998

	self->activator = activator;

	if (self->spawnflags & TRAIN_START_ON)
	{
		if (!(self->spawnflags & TRAIN_TOGGLE))
			return;
		self->spawnflags &= ~TRAIN_START_ON;
		VectorClear (self->velocity);
		self->nextthink = 0;
	}
	else
	{
		if (self->target_ent)
			lift_resume(self);
		else
			lift_next(self);
	}
}

// JOSEPH 22-APR-99
void SP_func_lift (edict_t *self)
{
	self->movetype = MOVETYPE_PUSH;

	VectorClear (self->s.angles);
	self->blocked = lift_blocked;
	if (self->spawnflags & TRAIN_BLOCK_STOPS)
		self->dmg = 0;
	else
	{
		if (!self->dmg)
			self->dmg = 100;
	}
	self->solid = SOLID_BSP;
	gi.setmodel (self, self->model);

	if (st.noise)
		self->moveinfo.sound_middle = gi.soundindex  (st.noise);

	if (!self->speed)
		self->speed = 100;

	self->moveinfo.speed = self->speed;
	self->moveinfo.accel = self->moveinfo.decel = self->moveinfo.speed;

	self->use = lift_use;
	
	gi.linkentity (self);

	if (self->target)
	{
		// start lifts on the second frame, to make sure their targets have had
		// a chance to spawn
		self->nextthink = level.time + FRAMETIME;
		self->think = func_lift_find;
	}
	else
	{
		gi.dprintf ("func_lift without a target at %s\n", vtos(self->absmin));
	}
}
// END JOSEPH
