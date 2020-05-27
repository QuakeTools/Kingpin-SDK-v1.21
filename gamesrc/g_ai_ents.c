// g_ai_ents.c
//
// Contains AI related entities

#include "g_local.h"
#include "g_func.h"

void AI_Ent_droptofloor ( edict_t *self )
{
	trace_t tr;
	vec3_t	start, dest;

	VectorCopy( self->s.origin, start );
	start[2] += 0.1;

	VectorCopy( start, dest );
	dest[2] -= 4000;

	tr = gi.trace( start, self->mins, self->maxs, dest, self, MASK_PLAYERSOLID );

	if (tr.startsolid || tr.allsolid)
	{
		gi.dprintf( "Warning: %s in solid at (%s)\n", self->classname, vtos(self->s.origin) );
		return;
	}
	if (tr.fraction == 1)
	{
		gi.dprintf( "Warning: %s above ground at (%s)\n", self->classname, vtos(self->s.origin) );
		return;
	}

	VectorCopy( tr.endpos, self->s.origin );
}

//======================================================================================

/*QUAKED ai_boundary (.5 .5 0) ?
Character will abort pursuing player when touching this brush. Will 
take cover until the player is out of view, then return to guarding position (if 
character has been assigned one).

	"moral"	range from 1 (Coward) to 7 (Psycotic). Only characters with an equal or lower moral level will be effected by this brush.
*/

void boundary_takecover_think ( edict_t *self )
{
	if (!self->owner->combat_goalent)
	{
		if ((self->owner->cast_info.aiflags & (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH)) != (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH))
		{
			AI_ForceTakeCover( self->owner, self->owner->enemy, true );
		}

		G_FreeEdict( self );
		return;
	}

	if (self->owner->health <= 0)
	{
		G_FreeEdict( self );
		return;
	}

	self->nextthink = level.time + 1.0;
}

void ai_boundary_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
#define	DEBUG_AI_BOUNDARY		0

	edict_t *thinker;

	if (!(other->svflags & SVF_MONSTER))
		return;

	if (other->cast_group != self->cast_group)
		return;
	else if (other->moral > self->moral)
		return;

	// abort taking cover	
	other->cast_info.aiflags &= ~AI_TAKE_COVER;
	other->combat_goalent = NULL;

	//	we should go into a Take Cover mode for a bit, and then return to our guarding
	//	position, if possible.

	if (other->enemy)
	{
		cast_memory_t	*mem;

		if ((other->cast_info.aiflags & (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH)) != (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH))
		{

			// Just go back to our start position

			if (!AI_ForceTakeCover( other, other->enemy, true ))
			{
				if (mem = level.global_cast_memory[other->character_index][other->enemy->character_index])
				{	
					// pretend that we haven't seen them in a while
					mem->timestamp = level.time - 5;
					mem->flags |= MEMORY_TAUNT;
					other->enemy = NULL;

					if (DEBUG_AI_BOUNDARY)
						gi.dprintf( "Sending %s to start position\n", other->name );

					// go back to our start position
					other->combat_goalent = other->goal_ent = other->start_ent;
					other->combat_goalent->cast_info.aiflags |= AI_GOAL_RUN;

					thinker = G_Spawn();
					thinker->owner = other;
					thinker->nextthink = level.time + 3;
					thinker->think = boundary_takecover_think;

					mem->ignore_time = level.time + 2;
				}
			}
//			else
//			{
//				if (DEBUG_AI_BOUNDARY)
//					gi.dprintf( "%s taking cover\n", other->name );
//			}
		}
/*
		// tell all our friends in our vacinity to do the same
		mem = other->cast_info.friend_memory;

		while (mem)
		{
			if (g_edicts[mem->cast_ent].health > 0 && VectorDistance( other->s.origin, g_edicts[mem->cast_ent].s.origin ) < 256)
			{
				edict_t	*dude;
				cast_memory_t	*dude_mem;

				dude = &g_edicts[mem->cast_ent];

				if (dude->enemy)
				{
					if ((dude->cast_info.aiflags & (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH)) != (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH))
					{
						if (!AI_ForceTakeCover( dude ))
						{
							dude_mem = level.global_cast_memory[dude->character_index][dude->enemy->character_index];

							// pretend that we haven't seen them in a while
							dude_mem->timestamp = level.time - 5;
							dude_mem->flags |= MEMORY_TAUNT;
							dude_mem->ignore_time = level.time + 2;
//							dude->enemy = NULL;
						}
						else
						{
							if (DEBUG_AI_BOUNDARY)
								gi.dprintf( "%s taking cover\n", dude->name );
						}
					}
				}

				if ((dude->cast_info.aiflags & (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH)) != (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH))
				{
					if (DEBUG_AI_BOUNDARY)
						gi.dprintf( "Sending %s to start position\n", dude->name );

					// go back to our start position
					dude->goal_ent = dude->start_ent;
					dude->goal_ent->cast_info.aiflags |= AI_GOAL_RUN;

					thinker = G_Spawn();
					thinker->owner = dude;
					thinker->nextthink = level.time + 1;
					thinker->think = boundary_takecover_think;
				}

			}

			mem = mem->next;
		}
*/
	}
	else if ((other->cast_info.aiflags & (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH)) != (AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH))
	{
		if (DEBUG_AI_BOUNDARY)
			gi.dprintf( "Sending %s to start position\n", other->name );

		// start walking back to our start position
		other->goal_ent = other->start_ent;
		other->goal_ent->cast_info.aiflags |= AI_GOAL_RUN;

		thinker = G_Spawn();
		thinker->owner = other;
		thinker->nextthink = level.time + 1;
		thinker->think = boundary_takecover_think;
	}

}

void SP_ai_boundary (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_boundary_touch;

	// set the center pos
	VectorAdd( ent->absmin, ent->absmax, ent->pos1 );
	VectorScale( ent->pos1, 0.5, ent->pos1 );

	ent->svflags |= SVF_NOCLIENT;

	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
}

//======================================================================================

/*QUAKED ai_event_hostile (.5 .5 0) ?
Character touching this brush will become a hostile enemy to all other characters
in LOS, that have the same "cast_group" as the brush.

"cast_group" must be > 0 for this brush to have any effect.
*/

void ai_event_hostile_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	int	i;
	cast_memory_t	*mem;
	edict_t			*icast;

	if (self->last_talk_time > (level.time - 0.5))
		return;
	self->last_talk_time = level.time;

	if (!(other->svflags & SVF_MONSTER) && !(other->client))
		return;

	if (other->cast_group == self->cast_group)
		return;

	// for all characters that belong to this entity, make them hostile towards us
	for (i=0; i<level.num_characters; i++)
	{
		if (!level.characters[i])
			continue;

		icast = level.characters[i];

		if (icast->cast_group != self->cast_group)
			continue;

		if (icast->health <= 0 || !icast->inuse)
			continue;

		mem = level.global_cast_memory[i][other->character_index];

		if (!mem)
			continue;
		if (mem->timestamp < (level.time - ENEMY_SIGHT_DURATION*2))
			continue;
		if (mem->flags & MEMORY_HOSTILE_ENEMY)
			continue;

		AI_MakeEnemy( icast, other, 0 );

		// now send them to us, if they can see/hear us
		if (	(mem->timestamp > (level.time - ENEMY_SIGHT_DURATION))
//			||	(gi.inPHS( other->s.origin, icast->s.origin ))
			||	(gi.inPVS( other->s.origin, icast->s.origin )))
		{
			AI_RecordSighting( icast, other, VectorDistance(icast->s.origin, other->s.origin) );
		}
	}
}

void SP_ai_event_hostile (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	if (ent->cast_group < 1)
	{
		gi.dprintf("Warning: ai_event_hostile without a valid cast_group\n");
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_event_hostile_touch;

	ent->svflags |= SVF_NOCLIENT;

	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
}

//======================================================================================

/*QUAKED ai_event_follow (.5 .5 0) ?
Client touching this brush will become a leader to all other characters
in LOS, that have the same "cast_group" as the brush.

"cast_group" must be > 0 for this brush to have any effect.
*/

void ai_event_follow_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	int	i;
	edict_t			*icast;

	if (self->last_talk_time > (level.time - 0.5))
		return;
	self->last_talk_time = level.time;

	if (!(other->client))
		return;

	if (other->cast_group != self->cast_group)
		return;

	// for all characters that belong to this entity, make them follow us
	for (i=0; i<level.num_characters; i++)
	{
		if (!level.characters[i])
			continue;

		icast = level.characters[i];

		if (icast->cast_group != self->cast_group)
			continue;

		if (icast->health <= 0 || !icast->inuse)
			continue;

		if (icast->leader)
			continue;

		icast->leader = other;
	}
}

void SP_ai_event_follow (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	if (ent->cast_group < 1)
	{
		gi.dprintf("Warning: ai_event_follow without a valid cast_group\n");
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_event_follow_touch;

	ent->svflags |= SVF_NOCLIENT;

	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
}

//======================================================================================

/*QUAKED ai_guard (.5 .5 1) (-16 -16 -24) (16 16 48)
Set a cast's "guard_target" to the "targetname" of this entity.
That character will then guard this location.

  "targetname" links to "guard_target" for the cast entity(s)
  "guard_radius" is the max guarding radius (default = 512)
*/

void SP_ai_guard (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs,  16,  16,  48);

	if (!self->guard_radius)
		self->guard_radius = 512;

	AI_Ent_droptofloor( self );
}

//======================================================================================

/*QUAKED ai_territory (.5 .5 0) ?
Marks the boundary of a gang's territory.

A character touching this will be deemed inside the gang's
territory. This means war if sighted.

!!NOTE!!: Point the "angles" in the direction of the territory. This lets
the AI know if the character is walking into or out of the territory.

  "cast_group" is the group that owns this territory
  "angles" points to the direction of the territory
  "radius" distance from brush before the player will be attacked (default 512)
*/

void ai_territory_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t	vec;

	if (!(other->svflags & SVF_MONSTER) && !(other->client))
		return;

	// are we going into, or out of the territory?
	
	VectorSubtract( other->s.origin, self->pos1, vec );
	vec[2] = 0;
	VectorNormalize( vec );

	if (DotProduct( vec, self->movedir ) > 0)
	{		// going into
//		if (nav_dynamic->value && other->client && (!other->last_territory_touched || (other->last_territory_touched->cast_group != self->cast_group)))
//			gi.dprintf("%s going into %s territory\n", other->classname, EP_GetGangName(self->cast_group) );

		if ((!other->last_territory_touched || (other->last_territory_touched->cast_group != self->cast_group)))
		{
			other->last_territory_touched = self;
			other->current_territory = self->cast_group;
		}
	}
	else	// going out of
	{
//		if (nav_dynamic->value && other->client && other->last_territory_touched)
//			gi.dprintf("%s leaving %s territory\n", other->classname, EP_GetGangName(self->cast_group) );

		if (other->last_territory_touched)
		{
			other->last_territory_touched = NULL;
			other->current_territory = self->cast_group;
		}
	}

	other->time_territory_touched = level.time;

}

void SP_ai_territory ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_territory_touch;

	if (!ent->cast_group)
		ent->cast_group = 2;

	if (!ent->dmg_radius)
		ent->dmg_radius = 512;

	if (!ent->moral)
	{
		gi.dprintf( "\n\nWARNING: ai_territory without a 'moral' (defaulting to 7)\nUse a 'moral' = 1 to PREVENT the gang members getting hostile when you enter their turf\n\n" );
		ent->moral = MORAL_AGGRESSIVE;
	}

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

	// set the center pos
	VectorAdd( ent->absmin, ent->absmax, ent->pos1 );
	VectorScale( ent->pos1, 0.5, ent->pos1 );

	AngleVectors( ent->s.angles, ent->movedir, NULL, NULL );
}

/*QUAKED ai_safespot (.5 .5 1) (-16 -16 -24) (16 16 48)

Set a cast's "flee_target" to the "targetname" of this entity.
That character will then flee to this location.

  "targetname" links to "flee_target" for the cast entity(s)
*/

void SP_ai_safespot (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs,  16,  16,  48);

	AI_Ent_droptofloor( self );
}


/*QUAKED ai_reset (.5 .5 0) ?
This is a brush that will reset a cast location to his 
startup location

  FIXME: Is this implemented yet?
*/
void ai_reset_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	EP_Reset (self, other);
}

void SP_ai_reset (edict_t *ent)
{

	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_reset_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}

/*QUAKED ai_combat_spot (.5 .5 1) (-16 -16 -24) (16 16 48)

  A good place to go to get a vantage point during fighting.
*/

void SP_ai_combat_spot (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict(self);
		return;
	}

	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs,  16,  16,  48);

	AI_Ent_droptofloor( self );
}


/*QUAKED ai_trigger_character (.5 .5 0) ?
When the player touches this brush, the targetted character will start
following it's path_corner.

  "target"	link this with the "targetname" of the character to be triggered
*/

void ai_trigger_character_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);

void SP_ai_trigger_character (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_trigger_character_touch;
	
	if (!ent->cast_group)
		ent->cast_group = 2;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
}

void ai_trigger_character_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	edict_t	*trav=NULL;

	if (!(other->client))
		return;

	while (trav = G_Find(trav, FOFS(targetname), self->target))
	{
		trav->spawnflags |= SPAWNFLAG_IMMEDIATE_FOLLOW_PATH;
	}
}

/*QUAKED ai_locked_door (.5 .5 0) ?
A character touching this brush will check the targetted door to see if it is closed.
If so, the character will head towards the specified path_corner_cast.

Example use: guiding AI characters away from a locked door

  "target"		link this with the "targetname" of the door to check
  "pathtarget"	linked with "targetname" of path_corner_cast to head for
*/

void ai_locked_door_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);

void locked_door_think( edict_t *ent )
{
	if (ent->pathtarget)
		ent->target_ent = G_Find( NULL, FOFS(targetname), ent->pathtarget );
	if (!ent->target_ent)
	{
		gi.dprintf( "ai_locked_door has invalid pathtarget (should point to a path_corner_cast)\n" );
		return;
	}

	if (ent->target)
		ent->goal_ent = G_Find( NULL, FOFS(targetname), ent->target );
	if (!ent->goal_ent)
	{
		gi.dprintf( "ai_locked_door has invalid target (should point to a door)\n" );
		return;
	}
}

void SP_ai_locked_door (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_locked_door_touch;

	ent->svflags |= SVF_NOCLIENT;

	ent->think = locked_door_think;
	ent->nextthink = level.time + 0.1;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
}

void ai_locked_door_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!self->goal_ent)
		return;

	// JOSEPH 14-MAY-99
	if (!(other->svflags & SVF_MONSTER))
		return;
	// END JOSEPH

	if (other->goal_ent == self->goal_ent)
		return;

	// if it's not closed, ignore
	if (!(self->goal_ent->moveinfo.state == STATE_BOTTOM || self->goal_ent->moveinfo.state == STATE_DOWN))
		return;

	other->goal_ent = self->goal_ent;
	other->cast_info.aiflags |= AI_GOAL_IGNOREENEMY;
}

//======================================================================================

void ai_button_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	// JOSEPH 14-MAY-99
	if (!(other->svflags & SVF_MONSTER))
		return;
	// END JOSEPH

	self->owner->use( self->owner, other, other );
}

void ai_button_think (edict_t *self)
{
	edict_t	*trav;
	route_t	r;

// disabled this, doesn't work too well, need a better approach
// eg. they'll activate lifts when they shouldn't
return;

	// check characters to see if any are within range

	while (		(self->count < level.num_characters)
			&&	(level.characters[self->count])
			&&	(	(level.characters[self->count]->client)
				 ||	(level.characters[self->count]->health < 0)))
	{
		self->count++;
	}

	if (self->count < level.num_characters)
	{	// check this character

		if (!level.characters[self->count])
			goto fail;

		trav = level.characters[self->count];

		if (!trav->inuse || trav->health <= 0)
			goto fail;

		if (trav->activator)
			goto fail;

		if (trav->cast_info.currentmove->frame->aifunc != ai_run)
			goto fail;

		if (VectorDistance( trav->s.origin, self->s.origin ) > 200)
			goto fail;

		if (!AI_ClearSight( self, trav, false ))
			goto fail;

		if (!NAV_Route_EntityToEntity( trav, NULL, self, VIS_PARTIAL, false, &r ))
			goto fail;

		// good enough..
		trav->activator = self->owner;

	}

fail:

	self->count++;

	if (self->count > level.num_characters)
		self->count = 0;

	self->nextthink = level.time + 0.1;
}
