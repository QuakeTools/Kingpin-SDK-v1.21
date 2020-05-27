//==============================================================
// g_ai_fight.c
//
// Combat oriented AI routines
//==============================================================

#include "g_local.h"

//============================================================================


void AI_CheckMakeEnemy( edict_t *self, edict_t *other )
{
	if (other != self->enemy && other->cast_group != self->cast_group && other->enemy == self)
	{	// make them our enemy now
		
		if (	!self->enemy
			||	!(self->cast_info.aiflags & AI_MELEE)
			||	VectorDistance(self->s.origin, other->s.origin) < 128)
		{
			if (level.global_cast_memory[self->character_index][other->character_index])
				self->enemy = other;
		}
	}
}

/*
==================
AI_BeginAttack

  Returns true if OK to attack, false otherwise

  May start a new movement for the character, to straighten up, or avoid something/someone
==================
*/
qboolean AI_BeginAttack( edict_t *self )
{
	vec3_t	vec;
	float	dist;


	// Ridah, 7-5-99, If they've been ordered to attack us by a client, get mad at them also
	if (self->enemy && self->enemy->leader)
		AI_MakeEnemy( self, self->enemy->leader, 0 );


	if (!self->enemy || (self->enemy->health <= 0))
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
		return false;
	}

	dist = VectorDistance( self->s.origin, self->enemy->s.origin );


	// Ridah, 19-may-99, Grenade AI
	if (self->cast_info.aiflags & AI_GRENADE_GUY)
	{
		if (( self->s.origin[2] - self->enemy->s.origin[2] ) < -256)
		{
			if (self->cast_info.currentmove != self->cast_info.move_avoid_run)
				AI_EndAttack(self);		// try find something else to do

			return false;
		}
	}


	if (	!(self->cast_info.aiflags & AI_SIDE_ATTACK))
// Ridah 7/5/99, fixes shooting with back to player (happens in SR1 courtyard sometimes)
//		&&	(	(dist > FACE_ANIM_DIST)
//			 ||	(self->cast_info.aiflags & AI_FACE_ATTACK)))
	{

		if (!directly_infront(self, self->enemy))
		{	// we need to straighten up
			float	dist;

			VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
			dist = VectorNormalize( vec );
			self->ideal_yaw = vectoyaw( vec );

			if ((dist > 384) && (self->maxs[2] == self->cast_info.standing_max_z))
			{
				int side_result;

				side_result = AI_SideTrace( self, 48, 90, SIDE_RANDOM );

				if (side_result && self->cast_info.move_lside_step)
				{
					if (side_result < 0)
						self->cast_info.currentmove = self->cast_info.move_lside_step;
					else
						self->cast_info.currentmove = self->cast_info.move_rside_step;
				}
				else
				{
					self->cast_info.currentmove = self->cast_info.move_avoid_walk;
				}

				return false;
			}
			else
			{
				M_ChangeYaw(self);
			}

		}

	}
/*
	if (	(self->cast_info.move_avoid_reverse_run)
		&&	(self->cast_info.last_reverse < (level.time - 5))
		&&	(dist < 64))
	{
		// trace a line backwards, make sure we can move there
		if ( AI_YawTrace( self, 64, 180 ) )
		{
			self->cast_info.currentmove = self->cast_info.move_avoid_reverse_run;
			self->cast_info.last_reverse = level.time;
			return false;
		}
	}
*/
	if (!AI_ClearSight(self, self->enemy, true))
	{	// can't see them directly, will we hit another enemy? if so keep firing

		static vec3_t mins = { -8, -8,  -4 };
		static vec3_t maxs = {  8,  8,   4 };
		vec3_t	start, end;
		trace_t tr;
		cast_memory_t	*tr_memory;

		VectorCopy( self->s.origin, start );
		start[2] += self->viewheight - 8;

		VectorCopy( self->enemy->s.origin, end );
		end[2] += self->enemy->viewheight - 8;

		tr = gi.trace( start, mins, maxs, end, self, MASK_PLAYERSOLID );

		if (tr.fraction < 1)
		{
			if (tr.ent == world)
			{
				if (self->cast_info.currentmove != self->cast_info.move_avoid_run)
					AI_EndAttack(self);		// try find something else to do

				return false;
			}
			else if (tr.ent->svflags & SVF_MONSTER || tr.ent->client)
			{
				tr_memory = level.global_cast_memory[self->character_index][tr.ent->character_index];

				if (!tr_memory || !(tr_memory->flags & MEMORY_HOSTILE_ENEMY))
				{
					if (self->cast_info.currentmove != self->cast_info.move_avoid_run)
						AI_EndAttack(self);		// try find something else to do

					return false;
				}
			}
		}
	}

	if (self->dont_takecover_time == 99999)
	{	// attack for at least 2 seconds
		if (!(self->cast_info.aiflags & AI_MELEE))
			self->dont_takecover_time = level.time + 2 + random()*4;
		else
			self->dont_takecover_time = 0;
	}

	return true;
}

/*
=============
AI_AvoidDangerousEntity

  Alerts all AI in vaccinity of the given ent, so they can flee if possible
=============
*/
void AI_AvoidDangerousEntity( edict_t *ent )
{
	int i;
	float	old_time;

	if (deathmatch->value)
		return;

	ent->s.origin[2] += 4;
	old_time = level.time;

	for (i=1; i<level.num_characters; i++)
	{
		if (!level.characters[i] || level.characters[i]->health <= 0)
			continue;

		if (level.characters[i] == ent)
			continue;

		if (!ent->client && VectorDistance( level.characters[i]->s.origin, ent->s.origin ) > ent->dmg_radius*2)
			continue;

		// if they are already fleeing this ent, check our fleeing position
		if (level.characters[i]->cast_info.aiflags & AI_TAKE_COVER)
		{
			if (level.characters[i]->combat_goalent && !CanDamage( level.characters[i]->combat_goalent, ent ))
				continue;
		}

		if (!gi.inPVS( level.characters[i]->s.origin, ent->s.origin ))
			continue;

		if ((VectorDistance( level.characters[i]->s.origin, ent->s.origin ) > 64) && !CanDamage( level.characters[i], ent))
			continue;

//		gi.dprintf( "RUN FOR YOUR LIVES!!!!\n" );

		level.characters[i]->last_gethidepos = 0;
		level.time -= 0.1;		// so we bypass speed optimization

		AI_ForceTakeCover( level.characters[i], ent, (ent->client == NULL) );
		ent->noise_time = level.time;

	}

	level.time = old_time;
	ent->s.origin[2] -= 4;
}

/*
=============
AI_CheckAttack

  Generic check for ability and willingness to attack our enemy
=============
*/
qboolean AI_CheckAttack(edict_t *self)
{
	float dist;

	// Ridah, 17-may-99, fixes health_threshold not working
	if (self->goal_ent && (self->cast_info.aiflags & AI_GOAL_IGNOREENEMY) && (VectorDistance(self->s.origin, self->goal_ent->s.origin) > 256))
	{
		self->cast_info.currentmove = self->cast_info.move_run;
		return false;
	}

	if ( !self->cast_info.attack || !self->cast_info.long_attack )
		return false;	// never attack if we are unable to

	if (!self->cast_info.move_run)
		return false;

	if (self->cast_info.pausetime > (level.time - 1))
		return false;

	if (self->combat_goalent && (VectorDistance(self->s.origin, self->combat_goalent->s.origin) > 128))
		return false;

	if (!AI_HasLeaderButGoForEnemy(self, self->enemy))
	{
		return false;
	}

	if ( !self->enemy || (self->enemy->health <= 0) || !self->enemy->inuse )
	{
		self->enemy = NULL;
		return false;
	}
	
	if ( !AI_ClearSight( self, self->enemy, true ) )
	{
		route_t	route;

		// we can't hit them from here, should we pursue them?

		if ( NAV_Route_EntityToEntity( self, NULL, self->enemy, VIS_PARTIAL, false, &route ) )
		{
			AI_StartRun( self );
		}

		return false;
	}

	if ( self->cast_info.aiflags & AI_MELEE )
	{
		if (	(fabs( self->s.origin[2] - self->enemy->s.origin[2] ) > 32)
			||	(VectorDistance( self->s.origin, self->enemy->s.origin ) > 96 ))
		{
			return false;
		}
	}

	dist = VectorDistance(self->enemy->s.origin, self->s.origin);
/*
	if (	((dist < FACE_ANIM_DIST) && !infront(self, self->enemy))
		||	((dist >= FACE_ANIM_DIST) && !directly_infront(self, self->enemy)))
	{
		vec3_t vec;
		float	dist;

		// just straighten up
		VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
		dist = VectorNormalize( vec );

		if ( self->maxs[2] == self->cast_info.standing_max_z )
		{
			self->ideal_yaw = vectoyaw( vec );

			if (dist < AI_GUARDING_DIST)
			{
				if (self->cast_info.move_avoid_reverse_walk)
					self->cast_info.currentmove = self->cast_info.move_avoid_reverse_walk;
			}
			else
				self->cast_info.avoid(self, self->enemy, true);

			return true;
		}
		else
		{
			if (self->cast_info.move_avoid_crwalk)
			{
				self->ideal_yaw = vectoyaw( vec );
				self->cast_info.currentmove = self->cast_info.move_avoid_crwalk;
				return true;
			}
			else	// just keep using ai_run()
			{
				self->cast_info.currentmove = self->cast_info.move_crwalk;
				return false;
			}
		}
	}
*/
	if (dist < self->cast_info.max_attack_distance)
	{
		// we can attack from here

		return self->cast_info.attack(self);
	}
	else if (!(self->cast_info.aiflags & AI_MELEE))
	{	// attack from far away

		self->cast_info.long_attack(self);

		return false;
	}

	return false;
}

/*
===========
AI_Goto_CombatTarget
===========
*/
qboolean AI_Goto_CombatTarget( edict_t *self )
{
	if (self->combattarget)
	{
		edict_t		*target, *oldtarget;

		target = NULL;
		while ((target = G_Find (target, FOFS(targetname), self->combattarget)) != NULL)
		{
			if (strcmp(target->classname, "path_corner") == 0)
			{
				if (self->health > 0)
				{
					self->combat_goalent = target;
					target->cast_info.aiflags |= AI_GOAL_RUN;
					self->cast_info.aiflags |= AI_RUN_LIKE_HELL;

					self->cast_info.currentmove = self->cast_info.move_run;
					self->combattarget = NULL;

					return true;
				}
				else	// we're dead, but check for pathtarget's
				{
					oldtarget = target;

					// check all items in chain
					while (target)
					{
						if (target->pathtarget)
						{	// fire it in 2 seconds (otherwise we might cause a loop)
							char *savetarget;

							if (target->delay < 2)
								target->delay = 2;

							savetarget = target->target;
							target->target = target->pathtarget;
							G_UseTargets (target, self);
							target->target = savetarget;
						}

						if (!target->target)
							return false;

						target = G_Find (NULL, FOFS(targetname), target->target);

						if (target == oldtarget)	// looped around
							return false;
					}
				}
			}
		}
	}

	return false;
}

void GotoCombatTargetThink( edict_t *self )
{
	if (self->owner->health > 0)
		AI_Goto_CombatTarget( self->owner );

	G_FreeEdict( self );
}

/*
===========
AI_StartAttack

  Begins an attack on enemy
===========
*/
void AI_StartAttack(edict_t *self, edict_t *enemy)
{
	mmove_t		*oldmove;
	cast_memory_t	*mem;

	if (!self->pain_debounce_time)
		self->pain_debounce_time = 0.1;		// so we attack them from now on

	// FIXME: remember the current enemy, if it exists?
	self->enemy = enemy;


	if (mem = level.global_cast_memory[self->character_index][enemy->character_index])
	{
		mem->flags |= MEMORY_STARTED_ATTACK;
	}


	if (self->combattarget)
	{
		if (self->delay)
		{	// set a thinker to get us moving
			edict_t	*thinker;

			thinker = G_Spawn();
			thinker->owner = self;
			thinker->think = GotoCombatTargetThink;
			thinker->nextthink = level.time + self->delay;
		}
		else	// go now
		{
			if (AI_Goto_CombatTarget( self ))
				return;
		}
	}

	oldmove = self->cast_info.currentmove;

	self->cast_info.checkattack(self);

	if (oldmove == self->cast_info.currentmove)
	{	// start running
		self->cast_info.currentmove = self->cast_info.move_run;
	}
}

//============================================================================
// General Combat AI routines

#define		COMBAT_FORCED_HIDE		1

/*
=============
CombatHideThink
=============
*/
/*
void CombatHideThink ( edict_t *thinker )
{
	edict_t *ent;

	ent = thinker->owner;

	if (!(ent->cast_info.aiflags & AI_TAKE_COVER))
	{	// not hiding anymore so free ourself
		G_FreeEdict( thinker );
	}
}
*/
/*
=============
AI_ProcessCombat

  For each AI character, take a look at what they're currently doing, and look
  for something they could be doing that would be better for them.
=============
*/
void CheckStillHiding( edict_t *self );

void AI_ProcessCombat (void)
{
	int i;
	edict_t *ent;

	for (i=0; i<level.num_characters; i++)
	{
		ent = level.characters[i];

		if (!ent || ent->client)
			continue;

		if (!ent->enemy)
			continue;

		if (ent->health <= 0)
			continue;

		if (ent->enemy->health <= 0)
			continue;

		if (AI_ClearSight( ent, ent->enemy, false ))
		{		// visible

			ent->combat_last_visible = level.time;
			VectorCopy( ent->enemy->s.origin, ent->combat_last_visible_pos );

		}
		else	// not visible
		{

			if (!(ent->cast_info.aiflags & AI_TAKE_COVER))
			{	// not currently hiding

				// should we start hiding, rather than walk straight into their trap?

				if (	(ent->combat_last_visible > (level.time - 0.5))
					&&	(	(!ent->enemy->client && !(ent->enemy->cast_info.aiflags & AI_MELEE))
						||	(ent->enemy->client && ent->enemy->client->pers.weapon && ent->enemy->client->pers.weapon->ammo))) // they have a weapon capable of doing some damage
				{
					// ok so start hiding, but should we hide from the position they were last visible from? or just them?

					if ((ent->moral < MORAL_PSYCOTIC) /*&& (VectorDistance( ent->enemy->s.origin, ent->combat_last_visible_pos ) < (256 * ent->moral))*/)
					{	// hide from last visible position

						{
							vec3_t org;

							VectorCopy( ent->enemy->s.origin, org );
							VectorCopy( ent->combat_last_visible_pos, ent->enemy->s.origin );
							AI_ForceTakeCover( ent, ent->enemy, true );
							VectorCopy( org, ent->enemy->s.origin );

							if (ent->moral > 2)	// don't wait there forever
							{
								ent->cast_info.aiflags &= ~AI_TAKECOVER_IGNOREHEALTH;

								ent->take_cover_time = level.time + (float)(ent->moral * 2);
							}
						}

					}

				}

			}
			else	// we are currently hiding, yell something out perhaps?
			{

			}

		}
	}
}
