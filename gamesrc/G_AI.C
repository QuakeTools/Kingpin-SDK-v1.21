// g_ai.c

#include "g_local.h"
#include "g_func.h"

qboolean AI_FindTarget (edict_t *self);

// RAFAEL	28-dec-98
qboolean AI_HearPlayer (edict_t *self);

extern cvar_t	*maxclients;

qboolean	enemy_vis;
qboolean	enemy_infront;
int			enemy_range;
float		enemy_yaw;

void AI_GetAvoidDirection( edict_t *self, edict_t *other );

//============================================================================



//============================================================================

/*
=============
ai_onfire_run

  Called while a character is running around on fire
==============
*/
void ai_onfire_run( edict_t *self, float dist )
{
	int side_result;

	if (self->onfiretime <= 0)
	{	// stopping running around
		self->cast_info.currentmove = self->cast_info.move_stand;

		return;
	}

	if (!self->groundentity)
		return;

//	M_ChangeYaw( self );
	self->s.angles[YAW] = self->ideal_yaw;

	if (M_walkmove (self, self->s.angles[YAW], dist*0.5) && AI_SideTrace( self, 64, 0, 1 ))
		return;

	// look for a new direction

	side_result = AI_SideTrace( self, 128, 30, SIDE_RANDOM );

	if (side_result)
	{
		self->ideal_yaw = anglemod(self->s.angles[YAW] + (30.0 * side_result));
		return;
	}

	side_result = AI_SideTrace( self, 32, 45, SIDE_RANDOM );

	if (side_result)
	{
		self->ideal_yaw = anglemod(self->s.angles[YAW] + (30.0 * side_result));
		return;
	}

	// try a sharper angle
	side_result = AI_SideTrace( self, 64, 100, SIDE_RANDOM );

	if (side_result)
	{
		self->ideal_yaw = anglemod(self->s.angles[YAW] + (100.0 * side_result));
		return;
	}

	side_result = AI_SideTrace( self, 8, 150, SIDE_RANDOM );

	if (side_result)
	{
		self->ideal_yaw = anglemod(self->s.angles[YAW] + (150.0 * side_result));
		return;
	}

	// last ditch, try running to our attacker

//	ai_run( self, dist );

//	self->cast_info.currentmove = self->cast_info.move_stand;

};

/*
=============
ai_move

Move the specified distance at current facing.
This replaces the QC functions: ai_forward, ai_back, ai_pain, and ai_painforward
==============
*/
void ai_move (edict_t *self, float dist)
{
	M_walkmove (self, self->s.angles[YAW], dist);

	// Ridah, added this so we turn to face our attacker after killed
	if (self->health <= 0)
	{
		M_ChangeYaw( self );

		if (self->velocity[2] < -50 && fabs(self->velocity[0]) < 50 && fabs(self->velocity[1]) < 50 && !self->groundentity && self->gravity < 1.0)
		{
			self->gravity = 0.1;	// sliding down wall?
		}
	}
}


/*
============
AI_CheckEvade
============
*/
void AI_CheckEvade( edict_t *self )
{
	vec3_t	vec;
	cast_memory_t *mem=NULL;
	edict_t	**enemy;

	if (self->enemy)
		enemy = &self->enemy;
	else
		enemy = &self->cast_info.avoid_ent;

	if (!(*enemy))
	{
		self->cast_info.currentmove = self->cast_info.move_stand;

		return;
	}

	if (self->combat_goalent)
	{
		if (	(*enemy)->client
			&&	(!(*enemy)->client->pers.holsteredweapon)
			&&	((*enemy)->client->pers.weapon))
		{	// get the fuck outta here
			self->cast_info.currentmove = self->cast_info.move_run;
			return;
		}
		else if (	!(*enemy)->client
				&&	((*enemy)->noise_time > (level.time - 2) && (*enemy)->noise_type == PNOISE_WEAPON))
		{	// get the fuck outta here
			self->cast_info.currentmove = self->cast_info.move_run;
			return;
		}
	}
	else if ((enemy == &self->cast_info.avoid_ent) || self->pain_debounce_time < (level.time - 3))
	{
		if ((*enemy) && (*enemy)->health > 0)
		{
			mem = level.global_cast_memory[self->character_index][(*enemy)->character_index];

			if (mem && (mem->timestamp > (level.time - 4)))
			{
				if ((*enemy)->client)
				{
					if (	(!(*enemy)->client->pers.holsteredweapon)
						&&	((*enemy)->client->pers.weapon))
					{
						float dist;

						VectorSubtract( (*enemy)->s.origin, self->s.origin, vec );
						dist = VectorNormalize( vec );
						
						self->ideal_yaw = vectoyaw( vec );

						if (dist < AI_NOT_HOLSTERED_RANGE_1)
						{
							if (self->moral > MORAL_HAPPY || directly_infront((*enemy), self))
							{
								AI_StartAttack( self, (*enemy) );

								if (self->cast_info.sight)
									self->cast_info.sight ( self, (*enemy) );
							}
							else if (AI_SideTrace( self, -64, 0, 1) && dist < 64)
							{	// go back again
								self->cast_info.currentmove = self->cast_info.move_evade;
							}
						}
						else if (directly_infront((*enemy), self)
							&&	(*enemy)->client
							&&	(*enemy)->client->pers.weapon
							&&	(*enemy)->client->pers.weapon->ammo)
						{
							if (AI_CheckTakeCover( self ))
							{	// get outta here
								self->cast_info.currentmove = self->cast_info.move_run;
							}
							else if (AI_SideTrace( self, -64, 0, 1))
							{	// go back again
								self->cast_info.currentmove = self->cast_info.move_evade;
							}
							else if (dist < 400)
							{
								AI_StartAttack( self, (*enemy) );
							}
						}

						return;
					}
				}
				else	// AI character
				{
					// FIXME: do more thorough AI here?

					if (enemy == &self->enemy)
					{
						self->cast_info.currentmove = self->cast_info.move_run;
					}

					return;
				}
			}

			if (mem)
			{	// they're not hostile anymore
				mem->flags &= ~MEMORY_HOSTILE_ENEMY;
			}
		}

	}

	// noone to evade, resume standing

	(*enemy) = NULL;
	self->cast_info.currentmove = self->cast_info.move_stand;

}

/*
=============
AI_ClearSight

  Checks that we can draw a line to other, without hitting something else in the process
=============
*/
qboolean AI_ClearSight ( edict_t *self, edict_t *other, qboolean boxtrace )
{
	static vec3_t mins = { -8, -8,  -4 };
	static vec3_t maxs = {  8,  8,  4 };
	// Ridah, used for Flamethrower AI
	static vec3_t mins2 = { -12, -12, -12 };
	static vec3_t maxs2 = {  12,  12,  12 };
	vec3_t	start, end, vec;
	float	*tmins, *tmaxs;
	int		mask;
	trace_t tr;
	qboolean	rval;
	float	dist, progdist, distleft;

	if (!self || !other)
		return false;

	if (boxtrace)
	{
		if (self->cast_info.max_attack_distance == 384)
		{
			tmins = mins2;
			tmaxs = maxs2;
		}
		else
		{
			tmins = mins;
			tmaxs = maxs;
		}
		mask = MASK_PLAYERSOLID;
	}
	else
	{
		tmins = NULL;
		tmaxs = NULL;
		mask = MASK_SOLID;
	}

again:

	VectorCopy( self->s.origin, start );
	start[2] += self->viewheight-8*boxtrace;	// adjust for gun position
	VectorCopy( other->s.origin, end );
	end[2] += other->viewheight-8*boxtrace;

	VectorSubtract( end, start, vec );
	dist = VectorNormalize( vec );
	progdist = 0;
	distleft = dist;

	if (fabs(vec[2]) > 0.8)	// too steep
		return false;

	tr = gi.trace( start, tmins, tmaxs, end, self, mask );

	while (		(tr.fraction < 1)
			&&	(	((tr.ent) && (tr.ent->s.renderfx2 & RF2_SURF_ALPHA))
				 || (tr.contents & MASK_ALPHA)
				 ||	(tr.surface->flags & SURF_ALPHA)
// Rafael : this will allow immortals to see through non breaking glass				 
				 || (tr.contents & CONTENTS_TRANSLUCENT && tr.contents & CONTENTS_WINDOW && self->cast_info.aiflags & AI_IMMORTAL)
	 ))
	{
		progdist += tr.fraction * dist;
		distleft -= tr.fraction * dist;

		if (distleft < 14)
		{	// gone passed the point, return true
			return true;
		}

		VectorMA( tr.endpos, 12, vec, start );
		tr = gi.trace( start, tmins, tmaxs, end, self, mask );
	}

	rval = ((tr.ent == other) || (tr.fraction == 1));

	if (!rval && self->deadflag && self->viewheight < 32)
	{
		self->viewheight = 32;
		goto again;
	}

	return rval;
}


/*
=============
AI_MoveToPlatCenter

  moves the character towards the center position of the platform
=============
*/
void AI_MoveToPlatCenter( edict_t *self, edict_t *plat)
{
	vec3_t center, vec;
	node_t	*plat_node;
	
	if (plat->deadflag)
	{
		plat_node = level.node_data->nodes[plat->nav_data.cache_node];
		VectorCopy(plat_node->origin, center);
		center[2] = self->s.origin[2];

		VectorSubtract(center, self->s.origin, vec);
		VectorNormalize2(vec, vec);
		self->ideal_yaw = vectoyaw(vec);
		M_ChangeYaw(self);

		M_walkmove(self, self->ideal_yaw, 15);
	}
}

/*
=============
AI_CheckTalk

  look for a friend in close vicinity, to make a talking jesture at
=============
*/
qboolean AI_CheckTalk( edict_t *self )
{
	cast_memory_t *cast=NULL;
	float		best_dist=500, this_dist;
	edict_t		*best_cast=NULL;
	int			count=1, total;
	int			i;

	if (!self->cast_info.talk)	// can't speak
		return false;

	if (self->goal_ent || self->enemy)
		return false;

	// check our current talk_ent
	if (self->cast_info.talk_ent)
	{
		if (!(cast = level.global_cast_memory[self->character_index][self->cast_info.talk_ent->character_index]))
		{
			self->cast_info.talk_ent = NULL;
			return false;
		}

		if (	((cast->timestamp > (level.time - 1)) && (++count))
			&&	(/*!best_cast ||*/ infront(&g_edicts[cast->cast_ent], self))	// ignore them if they aren't facing us
			&&	((this_dist = VectorDistance(g_edicts[cast->cast_ent].s.origin, self->s.origin)) < best_dist))
		{
			best_cast = &g_edicts[cast->cast_ent];
			best_dist = this_dist;
		}
	}

	// check clients
	for (i=1; i<=maxclients->value; i++)
	{
		if (g_edicts[i].client && g_edicts[i].health > 0)
		{

			cast = level.global_cast_memory[self->character_index][g_edicts[i].character_index];

			if (cast)
			{
				if ((cast->timestamp_dist < 300) && (cast->timestamp > (level.time - 3))
					&&	(((&g_edicts[i] == self->leader) && (g_edicts[i].last_talk_time < (level.time - 4)))
					|| (directly_infront(&g_edicts[i], self))))
				{
					// pick the client that spoke most recently
					if (!best_cast || !best_cast->client || (best_cast->last_talk_time < g_edicts[i].last_talk_time))
					{
						best_cast = &g_edicts[i];
					}
				}
			}
		}
	}

	if (best_cast)
		goto done;

	if (self->cast_info.last_talk_turn > (level.time - 2))
	{	// ignore other AI characters for this time
		goto done;
	}


	if (!best_cast)		// only check for other ents if our current talk_ent isn't valid anymore
	for (i=0; i<3; i++)
	{
		switch (i)
		{
		case 0:
			cast = self->cast_info.friend_memory;
			break;
		case 1:
			cast = self->cast_info.neutral_memory;
			break;
		case 2:
			cast = self->cast_info.enemy_memory;
			break;
		}


		total = (int) (random() * 10);

		while (cast)
		{

			if (	((cast->timestamp > (level.time - 1)) && (++count))
				&&	(/*!best_cast ||*/ infront(&g_edicts[cast->cast_ent], self))	// ignore them if they aren't facing us
				&&	(g_edicts[cast->cast_ent].cast_info.aiflags & AI_TALK)
				&&	!(g_edicts[cast->cast_ent].cast_info.aiflags & AI_NO_TALK)
				&&	((this_dist = VectorDistance(g_edicts[cast->cast_ent].s.origin, self->s.origin)) < best_dist))
			{
				best_cast = &g_edicts[cast->cast_ent];
				best_dist = this_dist;
			}

//			if (count > 6)	// only check 5 visible friends at once
//				break;

			cast = cast->next;
		}

		if (i==0 && best_cast)
			break;
	}

	self->cast_info.last_talk_turn = level.time;

done:

	if (best_cast)
	{
		if (directly_infront(self, best_cast) || !self->cast_info.move_avoid_walk)
		{
			self->cast_info.talk(self);
		}
		// else	// turn to face them
		else 
		{
			vec3_t vec;

			if (self->cast_info.aiflags & AI_SIT_TALK)
			{
				self->cast_info.aiflags &= ~AI_SIT_TALK;
			}
			else
			{
				VectorSubtract(best_cast->s.origin, self->s.origin, vec);
				VectorNormalize(vec);
				self->ideal_yaw = vectoyaw(vec);
				self->cast_info.currentmove = self->cast_info.move_avoid_walk;
			}

			self->cast_info.aiflags |= AI_TALK;

			// talk straight away
			//self->last_talk_time = 0;
		}

		self->cast_info.talk_ent = best_cast;

		return true;
	}

	return false;
}

/*
=============
AI_TalkThink

  Generic talking for all characters (currently only supports males)
=============
*/
void AI_TalkThink( edict_t *self, qboolean ismale )
{
#include "voice_punk.h"
#include "voice_bitch.h"

	edict_t	*talk_ent;
	cast_memory_t	*mem;

	if (level.cut_scene_time)
		return;

	if (!(self->cast_info.aiflags & AI_TALK))
		return;

	if (self->enemy)	// don't talk normally if we're mad
		return;

	if (!(talk_ent = self->cast_info.talk_ent))
		return;

	if (VectorDistance( talk_ent->s.origin, self->s.origin ) > 600 || !directly_infront(talk_ent, self))
	{
		self->cast_info.talk_ent = NULL;
		return;
	}

	if (	(self->cast_info.talk_ent == &g_edicts[1])
		&&	(self->cast_info.talk_ent->last_talk_time < (level.time - TALK_OTHER_DELAY*2))
		&&	(self->last_talk_time > (level.time - TALK_SELF_DELAY)))
	{
		return;
	}

//	if (last_client_talk && last_client_talk > (level.time - TALK_OTHER_DELAY))
//		return;	// don't talk too much around the client

	if (self->leader && VectorDistance( self->s.origin, self->leader->s.origin ) < 384 )
	{
		if ((self->last_talk_time < (level.time - TALK_SELF_DELAY)) && (self->health < self->max_health/2))
		// if (self->last_talk_time < level.time - (TALK_SELF_DELAY * 4) && (self->health < 50))
		{	// we've been hired, only speak when we're hurt
			if (self->gender == GENDER_MALE)
			{
				Voice_Random( self, self->leader, friendlyhurt, NUM_FRIENDLYHURT );
				return;
			}
		}

		return;
	}
	

	if ((talk_ent->health <= 0) || !visible(self, talk_ent) || !infront(talk_ent, self))
	{
		self->cast_info.talk_ent = NULL;
		return;
	}

	mem = level.global_cast_memory[self->character_index][talk_ent->character_index];
	if (!mem || (mem->flags & MEMORY_NO_TALK))
		return;

	// say something!
	if (	(	(self->last_talk_time < (level.time - TALK_SELF_DELAY))			// we haven't spoken for a while
			 ||	(	(talk_ent->client || talk_ent->last_talk_time)		// if they haven't spoken yet, don't bother
				 &&	(talk_ent->last_talk_time > (level.time - TALK_OTHER_DELAY*1.5))	// or they've just said something, and we've allowed some time for them to finish saying it
				 &&	(talk_ent->cast_info.talk_ent == self)
				 &&	(self->last_talk_time < talk_ent->last_talk_time)
				 &&	(self->last_talk_time < (level.time - TALK_OTHER_DELAY))))
		&&	(talk_ent->last_talk_time < (level.time - TALK_OTHER_DELAY)))
	{
		if (talk_ent->client)
		{
			if (!self->cast_group)
			{	// we're neutral
				cast_memory_t	*mem;

				mem = level.global_cast_memory[self->character_index][talk_ent->character_index];

				if (!mem || !(mem->flags & MEMORY_ASSHOLE))
				{
					if (!EP_EventSpeech( self, talk_ent, say_neutral ))
					{
						if (ismale)
							Voice_Random(self, self->cast_info.talk_ent, neutral_talk, NUM_NEUTRAL_TALK);
						else
							Voice_Random(self, self->cast_info.talk_ent, f_neutral_talk, F_NUM_NEUTRAL_TALK);
					}
				}
				else	// he's a jerk
				{
					if (!EP_EventSpeech( self, talk_ent, say_hostile ))
					{
						if (ismale)
							Voice_Random(self, self->cast_info.talk_ent, neutral_asshole_talk, NUM_NEUTRAL_ASSHOLE_TALK);
						else
							Voice_Random(self, self->cast_info.talk_ent, f_profanity_level1, F_NUM_PROFANITY_LEVEL1);
					}
				}
			}
			else if (self->cast_group != talk_ent->cast_group)
			{	// profanity time

				if (!EP_EventSpeech( self, talk_ent, say_hostile ))
				{
					// JOSEPH 26-MAY-99
					// if first sighting, play specific sound
					if (self->name_index == NAME_NICKIBLANCO)
					{
						Voice_Specific(self, self->cast_info.talk_ent, nickiblanco, 10);							
					}
					else if (self->name_index == NAME_TYRONE)
					{
						Voice_Specific(self, self->cast_info.talk_ent, ty_tyrone, 10);							
					}	
					else if (self->name_index == NAME_MOKER)
					{
						Voice_Specific(self, self->cast_info.talk_ent, steeltown_moker, 10);							
					}								
					else if (self->name_index == NAME_JESUS)
					{
						Voice_Specific(self, self->cast_info.talk_ent, sr_jesus, 10);							
					}	
					else if (self->name_index == NAME_HEILMAN)
					{
						Voice_Specific(self, self->cast_info.talk_ent, heilman, 10);							
					}	
					else if (self->name_index == NAME_BLUNT)
					{
						Voice_Specific(self, self->cast_info.talk_ent, blunt, 10);							
					}	
					else if (self->name_index == NAME_KINGPIN)
					{
						Voice_Specific(self, self->cast_info.talk_ent, kingpin, 10);							
					}	
					else if (ismale && specific[0].last_played < 0.1)
					{
						Voice_Specific(self, self->cast_info.talk_ent, specific, 0); // What are you doing on my street
					}
					// END JOSEPH
					else if (!ismale && f_specific[0].last_played < 0.1)
					{
						Voice_Random (self, self->cast_info.talk_ent, f_specific, 4); // What are you doing on my street
					}

					// check profanity level
					else if (talk_ent->profanity_level <= 1)
					{
						if (ismale)
							Voice_Random(self, self->cast_info.talk_ent, profanity_level1, NUM_PROFANITY_LEVEL1);
						else
							Voice_Random(self, self->cast_info.talk_ent, f_profanity_level1, F_NUM_PROFANITY_LEVEL1);
					}
					else if (talk_ent->profanity_level <= 2)
					{
						if (ismale)
							Voice_Random(self, self->cast_info.talk_ent, profanity_level2, NUM_PROFANITY_LEVEL2);
						else
							Voice_Random(self, self->cast_info.talk_ent, f_profanity_level2, F_NUM_PROFANITY_LEVEL2);
					}
					else if (talk_ent->profanity_level == 3)
					{
						// Ridah, 31-may-99, fixed the game crashing everytime you cussed a character 3 times
						if (ismale)
							Voice_Random(self, self->cast_info.talk_ent, profanity_level3, NUM_PROFANITY_LEVEL3); // kill that mofo
						else
							Voice_Random(self, self->cast_info.talk_ent, f_profanity_level3, F_NUM_PROFANITY_LEVEL3); // kill that mofo

						// go for them!
						AI_MakeEnemy(self, self->cast_info.talk_ent, 0);

					}

					// allow more of a delay than usual
					last_client_talk = level.time + 3;

				}
			}
		}
		else	// AI -> AI chat
		{
			if (!EP_EventSpeech( self, talk_ent, say_neutral))
			{
				if (ismale)
					Voice_Random(self, self->cast_info.talk_ent, neutral_converse, NUM_NEUTRAL_CONVERSE);
				else
					Voice_Random(self, self->cast_info.talk_ent, f_neutral_converse, F_NUM_NEUTRAL_CONVERSE);
			}
		}

		if (self->last_talk_time == level.time)
		{
			if (!directly_infront( self, self->cast_info.talk_ent ))
			{
				self->cast_info.avoid( self, self->cast_info.talk_ent, true );
			}
			else if (self->cast_info.currentmove == self->cast_info.move_stand)
			{	// make talking gesture if we're just standing around
				self->cast_info.talk(self);

			}
		}
	}

}


#define	TAKECOVER_BEHIND			8
#define	TAKECOVER_INFRONT			13
#define	TAKECOVER_DIRECTLY_INFRONT	18

#define	SIGHT_ENEMY_ATTACKTIME		2.0	// attack for at least this duration before fleeing again

void CheckStillHiding( edict_t *self )
{
	if (self->owner->health <= 0)
	{
		G_FreeEdict( self );
		return;
	}

	if (!(self->owner->cast_info.aiflags & AI_TAKE_COVER) || (self->owner->cover_ent && !self->owner->cover_ent->inuse))
	{	// they're not hiding anymore, stop checking
		self->owner->combat_goalent = NULL;
		self->owner->cast_info.aiflags &= ~AI_TAKE_COVER;
		G_FreeEdict( self );
		return;
	}

	if ((self->owner->cover_ent != self->owner->enemy) && (self->owner->cover_ent->noise_time < (level.time - 5)))
	{	// stop hiding
		self->owner->combat_goalent = NULL;
		self->owner->cast_info.aiflags &= ~AI_TAKE_COVER;
		G_FreeEdict( self );
		return;
	}

	if (self->owner->cast_info.currentmove == self->owner->cast_info.move_evade)
	{
		// start running
		self->owner->cast_info.currentmove = self->owner->cast_info.move_run;
		self->nextthink = level.time + 1.0;
		return;
	}


	if (self->owner->combat_goalent == self && self->owner->cover_ent && ((VectorDistance(self->owner->s.origin, self->s.origin) > 256) || ValidBoxAtLoc( self->s.origin, self->owner->mins, tv(16, 16, 4), self->owner, MASK_PLAYERSOLID )))
	{
		float	dist;
		vec3_t vec;

		// turn to face them
		VectorSubtract( self->owner->cover_ent->s.origin, self->owner->s.origin, vec );
		vec[2] = 0;
		dist = VectorNormalize(vec);

		// should they keep hiding?
		if ((self->owner->cast_info.currentmove->frame->aifunc == ai_stand) && (VectorDistance( self->s.origin, self->owner->s.origin ) < 128))
		{
			self->owner->ideal_yaw = vectoyaw(vec);
			M_ChangeYaw( self->owner );

			// make sure we're still aware of them
			AI_RecordSighting(self->owner, self->owner->cover_ent, dist);

			if (AI_ClearSight( self->owner->cover_ent, self->owner, false ))
			{	// they can see us, we gotta do something or we're dead meat
				self->owner->combat_goalent = NULL;
				self->owner->cast_info.aiflags &= ~AI_TAKE_COVER;

				if (!(self->owner->cast_info.aiflags & AI_MELEE))
					self->owner->dont_takecover_time = 99999;//level.time + SIGHT_ENEMY_ATTACKTIME;	// allow some time to get some shots off

				self->owner->cast_info.aiflags &= ~AI_TAKECOVER_IGNOREHEALTH;

				G_FreeEdict( self );

				return;
			}

			if (self->owner->cast_info.aiflags & AI_TAKECOVER_IGNOREHEALTH)
			{	// stay here until they see us
				goto skiptest;
			}

			if (self->owner->cast_info.aiflags & AI_MELEE)
			{
				route_t route;

				// Ridah, modified this so hiding Melee guys don't foolishly keep running out into the line of fire for no reason
				if (	infront(self->owner->cover_ent, self->owner)		// we're infront of them
					&&	self->owner->cover_ent->client && self->owner->cover_ent->client->pers.weapon && self->owner->cover_ent->client->pers.weapon->ammo)
				{	// they have a weapon, keep hiding
					goto skiptest;
				}
				else if (VectorDistance( self->owner->cover_ent->s.origin, self->owner->s.origin ) > 256)
				{	// if too far away, keep hiding

					if (NAV_Route_EntityToEntity( self->owner, NULL, self->owner->cover_ent, VIS_PARTIAL, false, &route ))
					{	
						if (route.dist > 256)
							goto skiptest;
					}
					else	// no route, keep hiding
					{
						goto skiptest;
					}

				}
			}

			if (!infront( self->owner->cover_ent, self->owner ))
			{	// they're not looking at us
				if (self->owner->health > ((MORAL_MAX - self->owner->moral) * TAKECOVER_BEHIND))
				{
					self->owner->combat_goalent = NULL;
					self->owner->cast_info.aiflags &= ~AI_TAKE_COVER;
					self->owner->dont_takecover_time = 99999;//level.time + SIGHT_ENEMY_ATTACKTIME * (random()+1);
					G_FreeEdict( self );
					return;
				}
			}

			else if (self->owner->cast_group && !directly_infront( self->owner->cover_ent, self->owner ))
			{	// not looking directly at us, but in our general direction
				if (self->owner->health > ((MORAL_MAX - self->owner->moral) * TAKECOVER_INFRONT))
				{
					self->owner->combat_goalent = NULL;
					self->owner->cast_info.aiflags &= ~AI_TAKE_COVER;
					self->owner->dont_takecover_time = 99999;//level.time + SIGHT_ENEMY_ATTACKTIME;

					G_FreeEdict( self );

					return;
				}
			}

			else if (self->owner->cast_group)
			{	// looking directly at us
				if (self->owner->health > ((MORAL_MAX - self->owner->moral) * TAKECOVER_DIRECTLY_INFRONT))
				{
					self->owner->combat_goalent = NULL;
					self->owner->cast_info.aiflags &= ~AI_TAKE_COVER;
					self->owner->dont_takecover_time = 99999;//level.time + SIGHT_ENEMY_ATTACKTIME;

					G_FreeEdict( self );

					return;
				}
			}

		}

skiptest:

		if ((dist < 2000) && (VectorDistance( self->s.origin, self->owner->s.origin ) < 384) && (self->owner->last_getcombatpos < (level.time - 2.0)))
		{	// look for somewhere else to go to
			float *pos;

			if (	(self->owner->cast_info.aiflags & AI_MELEE)
				||	(self->owner->health < ((MORAL_MAX - self->owner->moral) * TAKECOVER_INFRONT)))
			{	// look for somewhere further away

				if (pos = NAV_GetHidePos( self->owner, self->owner->cover_ent, HIDEPOS_FURTHER ))
				{
					edict_t *combatent;

					if (VectorDistance( pos, self->s.origin ) > 96)
					{
						combatent = self;
						VectorCopy( pos, combatent->s.origin );
						
						self->owner->combat_goalent = combatent;
						combatent->cast_info.aiflags |= AI_GOAL_RUN;
						self->owner->cast_info.aiflags |= AI_TAKE_COVER;
						self->owner->cast_info.aiflags |= AI_RUN_LIKE_HELL;

						self->owner->cast_info.currentmove = self->owner->cast_info.move_run;
						self->owner->wait = -1;

						combatent->owner = self->owner;
						combatent->think = CheckStillHiding;
						combatent->nextthink = level.time + 1;	// give us some time to get there
					}

					return;
				}
			}

			else if (	(self->owner->moral > MORAL_HAPPY)
				&&	(self->owner->health > ((MORAL_MAX - self->owner->moral) * TAKECOVER_INFRONT)))
			{	// sneak up on them

				if (pos = NAV_GetHidePos( self->owner, self->owner->cover_ent, HIDEPOS_CLOSER ))
				{
					edict_t *combatent;

					if (VectorDistance( pos, self->s.origin ) > 96)
					{
						combatent = self;
						VectorCopy( pos, combatent->s.origin );
						
						self->owner->combat_goalent = combatent;
						combatent->cast_info.aiflags |= AI_GOAL_RUN;
						self->owner->cast_info.aiflags |= AI_TAKE_COVER;
						self->owner->cast_info.aiflags |= AI_RUN_LIKE_HELL;

						self->owner->cast_info.currentmove = self->owner->cast_info.move_run;
						self->owner->wait = -1;

						combatent->owner = self->owner;
						combatent->think = CheckStillHiding;
						combatent->nextthink = level.time + 1;	// give us some time to get there
					}

					return;
				}
			}

		}

		self->nextthink = level.time + 0.2;

		return;
	}

	if (self->owner->combat_goalent == self)
	{
		self->owner->combat_goalent = NULL;
		self->owner->cast_info.aiflags &= ~AI_TAKE_COVER;
	}

	// not hiding anymore

	G_FreeEdict( self );
}

/*
=============
AI_CheckTakeCover

  Returns true if we should go hide, and we've found a good hiding position
=============
*/
void Weapon_Blackjack (edict_t *ent);

qboolean AI_CheckTakeCover( edict_t *self )
{
	float *pos=NULL;
	qboolean	evade=true;		// make evade action before fleeing

	if (self->cast_info.aiflags & AI_NO_TAKE_COVER)
		return false;

	if (self->dont_takecover_time > level.time)
		return false;

	if (self->leader && !(self->cast_info.aiflags & AI_HOLD_POSITION))
		return false;	// no hiding when we're following

	if (self->combat_goalent)	// probably heading for a combat pos, let them continue
		return false;

	if (self->last_getcombatpos > (level.time - 1))
		return false;

	if (!self->enemy)
		return false;

	// Ridah 16-may-99, hired guys don't hide
	if (self->cast_group == 1 && self->leader)
		return false;
	// done.

	// should we hide?

	// Ridah, always hide every now and then if we're a firing enemy, since that's what any sane human
	//	being would do
	if (	!(self->cast_info.aiflags & AI_MELEE)
//		&&	((rand()%MORAL_MAX) < (MORAL_MAX+2 - self->moral))
		&&	!(self->enemy->cast_info.aiflags & AI_MELEE)
		&&	(!self->enemy->client || (self->enemy->client->pers.weapon && self->enemy->client->pers.weapon->ammo))
		&&	/*directly_*/infront(self->enemy, self)
		&&	AI_ClearSight( self->enemy, self, false ))
//		&&	(self->last_gethidepos < (level.time - (1.0 + self->moral/MORAL_MAX))))
	{
//		cast_memory_t	*mem;
//		edict_t			*trav;
		qboolean		nohide=false;
/*
		// TEAM AI: if we have a friend around, only take cover if they're happily firing
		mem = self->cast_info.friend_memory;
		while (mem)
		{
			trav = &g_edicts[mem->cast_ent];

			if (	(mem->timestamp > (level.time - 10))
				&&	(trav->health > 0)
				&&	(trav->enemy)
				&&	(!(trav->cast_info.aiflags & AI_MELEE))
				&&	(	(trav->noise_time < (level.time - 2))
					 ||	(trav->cast_info.aiflags & AI_TAKE_COVER)))
			{
				nohide = true;
				break;
			}

			mem = mem->next;
		}
*/
		if (!nohide && (pos = NAV_GetHidePos( self, self->enemy, HIDEPOS_ANY )))
		{
			evade = false;
			goto done;
		}
	}

	if (	(self->cast_info.aiflags & AI_MELEE)
		&&	(	(self->enemy->client)
			 &&	(self->enemy->client->pers.weapon)
			 &&	(self->enemy->client->pers.weapon->ammo))
		&&	(random() < 0.3 || VectorDistance( self->enemy->s.origin, self->s.origin ) > 128))
	{	// don't do any other tests, we REALLY want to hide from this enemy!

		if (pos = NAV_GetHidePos( self, self->enemy, HIDEPOS_FURTHER ))
		{
			goto done;
		}

	}
	else if (infront( self->enemy, self ))
	{
		if (directly_infront( self->enemy, self ))
		{
			if (self->health > ((MORAL_MAX - self->moral) * TAKECOVER_DIRECTLY_INFRONT))
				return false;
		}
		else
		{
			if (self->health > ((MORAL_MAX - self->moral) * TAKECOVER_INFRONT))
				return false;
		}
	}
	else if (self->health > ((MORAL_MAX - self->moral) * TAKECOVER_BEHIND))
		return false;


	// find somewhere to go
	if (!pos)
	{

		if (self->cast_group)
		{	// look for a friend with a gun (assume we know where all our friends are)
			int i;
			edict_t *other, *best=NULL;
			float	best_dist=2048, this_dist;
			route_t	route;

			for (i=0; i<level.num_characters; i++)
			{
				other = level.characters[i];

				if (!other)
					continue;

				if (other->health <= 0 || !other->inuse)
					continue;

				if (self->cast_group != other->cast_group)
					continue;

				if (self == other)
					continue;

				this_dist = VectorDistance( self->s.origin, other->s.origin );

				if ((this_dist < 384) && other->enemy)
					continue;

				if (other->client)
					goto accepted;

				if (best)
				{
					if (best->cast_info.aiflags & AI_MELEE)
					{
						if (!(other->cast_info.aiflags & AI_MELEE))
						{
							goto accepted;
						}
					}
					else
					{
						if (other->cast_info.aiflags & AI_MELEE)
						{	// no good
							continue;
						}
					}
				}
				else if (!(self->cast_info.aiflags & AI_MELEE))
				{
					if (other->cast_info.aiflags & AI_MELEE)
					{	// no good, we have weapon and this friend doesn't
						continue;
					}
					else	// is it worth going to get them?
					{
						if (!NAV_Route_EntityToEntity( self, NULL, other, VIS_PARTIAL, false, &route ))
							continue;

						if (route.dist > 1000)	// too far away
							continue;
					}
				}

				if (this_dist > best_dist)
					continue;

accepted:

				best = other;
				best_dist = this_dist;

				if (other->client)
					break;

			}

			if (best)
			{
//gi.dprintf( "%s fleeing to %s\n", self->name, best->name );
				pos = best->s.origin;
				self->cover_ent = self->enemy;
				self->last_getcombatpos = level.time;
				self->last_gethidepos = level.time;
				goto done;
			}
		}

		pos = NAV_GetHidePos( self, self->enemy, HIDEPOS_FURTHER );
	}

done:

	if (pos)
	{
		edict_t *combatent;

		combatent = G_Spawn();
		VectorCopy( pos, combatent->s.origin );
		
		self->combat_goalent = combatent;
		combatent->cast_info.aiflags |= AI_GOAL_RUN;
		self->cast_info.aiflags |= AI_TAKE_COVER;
		self->cast_info.aiflags |= AI_RUN_LIKE_HELL;
		self->wait = -1;

		combatent->owner = self;
		combatent->think = CheckStillHiding;
		combatent->nextthink = level.time + 1;	// give us some time to get there
/*
		// make sure we run AWAY from our enemy
		{
			node_t *node;

			if (node = NAV_GetClosestNode( self, VIS_PARTIAL, true, true ))
				self->nav_data.goal_index = node->index + 1;
		}
*/
	}

	if (	evade
		&&	(self->last_stand_evade < (level.time - 4))
		&&	(pos || ((rand()%10) < 3))
		&&	(self->moral < 3)
		&&	self->cast_info.move_evade
		&&	self->maxs[2] == self->cast_info.standing_max_z
		&&	directly_infront( self->enemy, self )
		&&	AI_ClearSight(self, self->enemy, false)
		&&	self->health > self->max_health/2)
	{
		self->last_stand_evade = level.time;
		self->cast_info.currentmove = self->cast_info.move_evade;
		if (self->cast_info.backoff)
			self->cast_info.backoff( self, self->enemy );
	}

	return (pos != NULL);
}

/*
=============
AI_ForceTakeCover
=============
*/
qboolean AI_ForceTakeCover( edict_t *self, edict_t *enemy, qboolean ignorehealth )
{
	float *pos;
	int		hidepos_type;

	if (self->cast_info.aiflags & AI_NO_TAKE_COVER)
		return false;

	// Note to Ryan: take a look at this. nasty hack because of crash bug
	if (!(enemy))
		return false;

	if (enemy->svflags & SVF_MONSTER)
		hidepos_type = HIDEPOS_FURTHER;
	else
		hidepos_type = HIDEPOS_ANY;

	if (pos = NAV_GetHidePos( self, enemy, hidepos_type ))
	{
		edict_t *combatent;

		combatent = G_Spawn();
		VectorCopy( pos, combatent->s.origin );
		
		self->combat_goalent = combatent;
		combatent->cast_info.aiflags |= AI_GOAL_RUN;
		combatent->cast_info.aiflags |= AI_RUN_LIKE_HELL;
		self->cast_info.aiflags |= AI_TAKE_COVER;
		self->cast_info.aiflags |= AI_RUN_LIKE_HELL;

		combatent->owner = self;
		combatent->think = CheckStillHiding;
		combatent->nextthink = level.time + 1;	// give us some time to get there

		if (ignorehealth)
			self->cast_info.aiflags |= AI_TAKECOVER_IGNOREHEALTH;

		if (self->maxs[2] == self->cast_info.standing_max_z)
			self->cast_info.currentmove = self->cast_info.move_run;
/*
		// make sure we run AWAY from our enemy
		{
			node_t *node;

			if (node = NAV_GetClosestNode( self, VIS_PARTIAL, true, true ))
				self->nav_data.goal_index = node->index + 1;
		}
*/
		return true;
	}

	return false;
}

/*
=============
AI_TooClose

  returns true if "goal" is within the AI_TOO_CLOSE_DIST range from "self"
  mostly used to make sure followers don't obstruct their leader
=============
*/
qboolean AI_TooClose(edict_t *self, edict_t *goal)
{
	float	scale;

	if (VectorCompare(goal->velocity, vec3_origin))
		return false;

	// allow to walk real close if they're standing on a plat and not moving
	if (goal->groundentity && goal->groundentity->use && VectorCompare(goal->groundentity->velocity, vec3_origin))
		return false;

	scale = 1.0;
	if (VectorLength(goal->velocity))
		scale = 1.5;

	return (VectorDistance(self->s.origin, goal->s.origin) < AI_TOO_CLOSE_DIST*scale);
}

/*
=============
AI_FollowLeader

  modification of AI_TooClose(), returns true if we need to move away from, or towards the goal
=============
*/
qboolean AI_FollowLeader(edict_t *self, edict_t *goal)
{
	float dist;
	float	scale;

	dist = VectorDistance(self->s.origin, goal->s.origin);

	// allow to walk real close if they're standing on a plat and not moving
	if (	goal->groundentity
		&&	goal->groundentity->use)
	{
		if (goal->groundentity != self->groundentity)
			return true;
		else if (dist < 64 && !VectorCompare(goal->velocity, vec3_origin))
			return true;
		else
			return false;
	}

	scale = 1.0;
	if (VectorLength(goal->velocity))
		scale = 1.5;

	return ((dist < AI_TOO_CLOSE_DIST*scale) || (dist > scale*(AI_GUARDING_DIST * (infront(goal, self) ? 1 : 0.5))));
}

/*
==============
AI_End_CrouchStand_Down

  Goes to the standing animation according to what we're currently doing
==============
*/
void AI_End_CrouchStand_Down(edict_t *self)
{
	self->cast_info.currentmove = self->cast_info.move_crwalk;
}

/*
==============
AI_End_CrouchStand_Up

  Goes to the standing animation according to what we're currently doing
==============
*/
void AI_End_CrouchStand_Up(edict_t *self)
{
	self->cast_info.currentmove = self->cast_info.move_run;
}

/*
==============
AI_EndAttack

  resume attacking if they so desire, otherwise "stand"

  usually called at the end of pain, or attacking animations
==============
*/
void AI_EndAttack(edict_t *self)
{
	mmove_t *oldmove;

	// hack to turn off the flamethrow effect
	if (self->s.renderfx2 & RF2_FLAMETHROWER)
		self->s.renderfx2 &= ~RF2_FLAMETHROWER;
	
	if (self->enemy && AI_CheckTakeCover(self))
	{
		if (self->cast_info.currentmove != self->cast_info.move_evade)
			self->cast_info.currentmove = self->cast_info.move_run;
		return;
	}

	oldmove = self->cast_info.currentmove;
	if (!self->enemy || !self->cast_info.checkattack(self))
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
		self->cast_info.talk(self);

		if (self->enemy)
			self->cast_info.currentmove = self->cast_info.move_run;
		
	}
}

/*
==============
AI_GetOrientation

  returns one of ORIENTATION_* depending on which side of "self", "other" is on
==============
*/
int AI_GetOrientation( edict_t *self, edict_t *other )
{
	vec3_t	right, rorg, lorg, rvec, lvec;
	float diff;

	// determine right or left side impact
	AngleVectors(self->s.angles, NULL, right, NULL);
	VectorMA(self->s.origin,  16, right, rorg);
	VectorMA(self->s.origin, -16, right, lorg);

	VectorSubtract(other->s.origin, rorg, rvec);
	VectorSubtract(other->s.origin, lorg, lvec);

	diff = VectorLength(rvec) - VectorLength(lvec);

	if (diff < -8) // right
	{
		return ORIENTATION_RIGHT;
	}
	else if (diff > 8) // left
	{
		return ORIENTATION_LEFT;
	}

	// center
	return ORIENTATION_CENTER;
}

/*
==============
AI_CheckStillInair

  called while jumping, so we stay on a single jumping frame while in the air
==============
*/
void AI_CheckStillInair(edict_t *self)
{
	if (!self->groundentity)
		self->s.frame--;		// stay on the current frame
	else
	{
		float dist;

		dist = self->fall_height - self->s.origin[2];

		if ( dist < 48)
		{	// get out of this anim
			self->cast_info.currentmove->endfunc(self);
		}
		else if ( dist > 256 )
		{
			T_Damage( self, world, world, vec3_origin, self->s.origin, vec3_origin, 2 + (int)((0.01*dist)*(0.01*dist)), 0, 0, MOD_FALLING );
		}
	}
}

/*
==============
AI_EndJump

  called at the end of a jump, so we return to running, or crouch walking frames
==============
*/
void AI_EndJump(edict_t *self)
{
	if (!self->cast_info.move_run)
		return;

	// clear cached nodes
//	self->nav_data.cache_node = -1;
//	self->nav_data.goal_index = 0;

	// resume walking
	if (self->maxs[2] < self->cast_info.standing_max_z)
		self->cast_info.currentmove = self->cast_info.move_crwalk;
	else
		self->cast_info.currentmove = self->cast_info.move_run;
}


// JOSEPH 20-NOV-98
/*
==============
AI_AfterLife

  Generic character elimination routine.
==============
*/
void AI_AfterLife(edict_t *self)
{
	// Seconds dead
	self->deadticks++;

	// Set body on floor angle
	if (self->deadticks <= 1)
	{
		/*vec3_t	avec, stop;
		trace_t	trace;
			
		VectorCopy(self->s.origin, stop);
		stop[2] -= 16*2;

		trace = gi.trace (self->s.origin, self->mins, self->maxs, stop, self, MASK_DEADSOLID);
		if (trace.fraction < 1)
		{
			VectorCopy (trace.plane.normal, avec);
			avec[0] = acos(trace.plane.normal[2])/M_PI*180;
			avec[2] = atan2(trace.plane.normal[1], trace.plane.normal[0])/M_PI*180;
			avec[1] = self->s.angles[1];
			
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

			VectorCopy (avec, self->s.angles);

			// Ridah, the angles seem to be opposite?
			VectorScale( self->s.angles, -1, self->s.angles );
			self->s.angles[YAW] = -self->s.angles[YAW];	// return YAW to normal
		}*/
		
		/*vec3_t	avec1, avec2, avect, angles, start, stop, headorg, legsorg;
		trace_t	trace;
		
		// Use object_bounds to get head position
		{
			vec3_t org, ang, mins, maxs;
			vec3_t forward, right, up;
			vec3_t rmins, rmaxs, pmins, pmaxs;

			VectorCopy (self->s.origin, org);
			VectorCopy (self->s.angles, ang);
			
			VectorCopy (self->s.model_parts[PART_HEAD].object_bounds[0][self->s.frame].mins, mins);
			VectorCopy (self->s.model_parts[PART_HEAD].object_bounds[0][self->s.frame].maxs, maxs);
			
			AngleVectors (ang, forward, right, up);

			VectorMA (org, ((mins[0] + maxs[0]) * 0.5), forward, org);
			VectorMA (org, -((mins[1] + maxs[1]) * 0.5), right, org);
			VectorMA (org, (mins[2] + maxs[2]) * 0.5, up, org);

			// find rotated positions of mins/maxs, and then build the new min/max
			VectorScale ( forward, mins[0], rmins);
			VectorMA (rmins, -mins[1], right, rmins);
			VectorMA (rmins, mins[2], up, rmins);

			VectorScale ( forward, maxs[0], rmaxs);
			VectorMA (rmaxs, -maxs[1], right, rmaxs);
			VectorMA (rmaxs, maxs[2], up, rmaxs);

			pmins[0] = (rmins[0] < rmaxs[0] ? rmins[0] : rmaxs[0]);
			pmins[1] = (rmins[1] < rmaxs[1] ? rmins[1] : rmaxs[1]);
			pmins[2] = (rmins[2] < rmaxs[2] ? rmins[2] : rmaxs[2]);

			pmaxs[0] = (rmins[0] > rmaxs[0] ? rmins[0] : rmaxs[0]);
			pmaxs[1] = (rmins[1] > rmaxs[1] ? rmins[1] : rmaxs[1]);
			pmaxs[2] = (rmins[2] > rmaxs[2] ? rmins[2] : rmaxs[2]);

			// now align the mins/maxs with the origin
			mins[0] = pmins[0] - (0.5*(pmaxs[0] + pmins[0]));
			mins[1] = pmins[1] - (0.5*(pmaxs[1] + pmins[1]));
			mins[2] = pmins[2] - (0.5*(pmaxs[2] + pmins[2]));
			maxs[0] = pmaxs[0] - (0.5*(pmaxs[0] + pmins[0]));
			maxs[1] = pmaxs[1] - (0.5*(pmaxs[1] + pmins[1]));
			maxs[2] = pmaxs[2] - (0.5*(pmaxs[2] + pmins[2]));

			headorg[0] = org[0] + (mins[0] + maxs[0]) / 2;
			headorg[1] = org[1] + (mins[1] + maxs[1]) / 2;
			headorg[2] = org[2] + (mins[2] + maxs[2]) / 2;
		}
		
		// Use object_bounds to get legs position
		{
			vec3_t org, ang, mins, maxs;
			vec3_t forward, right, up;
			vec3_t rmins, rmaxs, pmins, pmaxs;

			VectorCopy (self->s.origin, org);
			VectorCopy (self->s.angles, ang);
			
			VectorCopy (self->s.model_parts[PART_LEGS].object_bounds[0][self->s.frame].mins, mins);
			VectorCopy (self->s.model_parts[PART_LEGS].object_bounds[0][self->s.frame].maxs, maxs);
			
			AngleVectors (ang, forward, right, up);

			VectorMA (org, ((mins[0] + maxs[0]) * 0.5), forward, org);
			VectorMA (org, -((mins[1] + maxs[1]) * 0.5), right, org);
			VectorMA (org, (mins[2] + maxs[2]) * 0.5, up, org);

			// find rotated positions of mins/maxs, and then build the new min/max
			VectorScale ( forward, mins[0], rmins);
			VectorMA (rmins, -mins[1], right, rmins);
			VectorMA (rmins, mins[2], up, rmins);

			VectorScale ( forward, maxs[0], rmaxs);
			VectorMA (rmaxs, -maxs[1], right, rmaxs);
			VectorMA (rmaxs, maxs[2], up, rmaxs);

			pmins[0] = (rmins[0] < rmaxs[0] ? rmins[0] : rmaxs[0]);
			pmins[1] = (rmins[1] < rmaxs[1] ? rmins[1] : rmaxs[1]);
			pmins[2] = (rmins[2] < rmaxs[2] ? rmins[2] : rmaxs[2]);

			pmaxs[0] = (rmins[0] > rmaxs[0] ? rmins[0] : rmaxs[0]);
			pmaxs[1] = (rmins[1] > rmaxs[1] ? rmins[1] : rmaxs[1]);
			pmaxs[2] = (rmins[2] > rmaxs[2] ? rmins[2] : rmaxs[2]);

			// now align the mins/maxs with the origin
			mins[0] = pmins[0] - (0.5*(pmaxs[0] + pmins[0]));
			mins[1] = pmins[1] - (0.5*(pmaxs[1] + pmins[1]));
			mins[2] = pmins[2] - (0.5*(pmaxs[2] + pmins[2]));
			maxs[0] = pmaxs[0] - (0.5*(pmaxs[0] + pmins[0]));
			maxs[1] = pmaxs[1] - (0.5*(pmaxs[1] + pmins[1]));
			maxs[2] = pmaxs[2] - (0.5*(pmaxs[2] + pmins[2]));

			legsorg[0] = org[0] + (mins[0] + maxs[0]) / 2;
			legsorg[1] = org[1] + (mins[1] + maxs[1]) / 2;
			legsorg[2] = org[2] + (mins[2] + maxs[2]) / 2;
		}

		VectorCopy(headorg, start);
		VectorCopy(headorg, stop);
		stop[2] = start[2] - 16*4;
		trace = gi.trace (start, NULL, NULL, stop, self, MASK_DEADSOLID);

		if (trace.fraction < 1)
		{
			VectorCopy(trace.endpos, avec1);
		}
		else
		{
			VectorCopy(start, avec1);
		}

		VectorCopy(legsorg, start);
		VectorCopy(legsorg, stop);
		stop[2] = start[2] - 16*4;
		trace = gi.trace (start, NULL, NULL, stop, self, MASK_DEADSOLID);

		if (trace.fraction < 1)
		{
			VectorCopy(trace.endpos, avec2);
		}
		else
		{
			VectorCopy(start, avec2);
		}

		if ((avec1[2] != avec2[2]))
		{
			if ((headorg[0] > self->s.origin[0]) || (headorg[1] > self->s.origin[1]))
			{
				VectorSubtract(avec2, avec1, avect);
			}
			else
			{
				VectorSubtract(avec1, avec2, avect);
			}
			
			VectorNormalize(avect);
			vectoangles(avect, angles);	
			angles[1] = self->s.angles[1];
			VectorCopy (angles, self->s.angles);
		}*/
	}
		
	// If the body is not to be moved 
	if (!self->deadticks)
	{
		self->think = NULL;
		self->nextthink = -1;
		self->solid = 0;
		return;		
	}
	
	if (self->deadticks > (60*1))
	{
		edict_t	*other=NULL;
		trace_t tr;
		vec3_t	end, travelvec;
		byte	i;
		long	len;
		float	dir;
		int     dir2;
		byte    BW = SFX_BLOOD_WIDTH;
		byte    BH = SFX_BLOOD_HEIGHT;
		long    rnd1, rnd2;

		// Ridah, 11/22/98 added distance check and optimization

		// If no player can see the body
//		while (other = G_Find(other, FOFS(classname), "player"))
		for (i=0; i<(int)maxclients->value; i++)
		{
			other = &g_edicts[1 + i];	// clients start at g_edicts[1]

			if (!other->inuse)
				continue;

			if (infront(other, self) || (VectorDistance(other->s.origin, self->s.origin) < 1024))
			{	
				self->nextthink = level.time + FRAMETIME * 20;
				return;
			}
		}

		// Determine drag direction
		dir = -10;
		dir2 = 0;
		VectorCopy (self->s.origin, end);
		end[dir2] += dir * 20;
		tr = gi.trace (self->s.origin, NULL, NULL, end, self, MASK_SHOT);
		VectorSubtract(self->s.origin, tr.endpos, travelvec);
		len = VectorNormalize(travelvec);			
		if (len > 100) goto dragit;

		dir = 10;
		dir2 = 0;
		VectorCopy (self->s.origin, end);
		end[dir2] += dir * 20;
		tr = gi.trace (self->s.origin, NULL, NULL, end, self, MASK_SHOT);
		VectorSubtract(self->s.origin, tr.endpos, travelvec);
		len = VectorNormalize(travelvec);			
		if (len > 100) goto dragit;

		dir = -10;
		dir2 = 1;
		VectorCopy (self->s.origin, end);
		end[dir2] += dir * 20;
		tr = gi.trace (self->s.origin, NULL, NULL, end, self, MASK_SHOT);
		VectorSubtract(self->s.origin, tr.endpos, travelvec);
		len = VectorNormalize(travelvec);			
		if (len > 100) goto dragit;

		dir = 10;
		dir2 = 1;
		VectorCopy (self->s.origin, end);
		end[dir2] += dir * 20;
		tr = gi.trace (self->s.origin, NULL, NULL, end, self, MASK_SHOT);
		VectorSubtract(self->s.origin, tr.endpos, travelvec);
		len = VectorNormalize(travelvec);			
		if (len > 100) goto dragit; else goto forgetit;

	dragit:

		rnd1 = ((rand()&7)-4);
		
		// Drag the body
		for (i=0; i <= 10; i++)
		{
			VectorCopy (self->s.origin, end);
			end[2] -= 32+8;

			tr = gi.trace (self->s.origin, NULL, NULL, end, self, MASK_SHOT);

			SurfaceSpriteEffect(SFX_SPRITE_SURF_BLOOD1, BW--, BH--,
								tr.ent, tr.endpos, tr.plane.normal);
			
			self->s.origin[dir2] += dir;

			rnd2 = ((rand()&3)-2);

			if (dir == 1)
				self->s.origin[2] += (rnd1 + rnd2); 	
			else
				self->s.origin[1] += (rnd2 + rnd2); 	
		}

	forgetit:

		// Unload this cast's memory, since we won't be needing it anymore
		//AI_UnloadCastMemory( self );

		// Remove the body
		self->think = NULL;
		self->nextthink = -1;
		self->solid = 0;
		self->svflags |= SVF_NOCLIENT;
		return;
	}

	self->nextthink = level.time + FRAMETIME * 10;
}
// END JOSEPH


/*	trace_t tr;
	vec3_t	end;
	
	VectorCopy (self->s.origin, end);
	end[2] -= 32+8;

	tr = gi.trace (self->s.origin, NULL, NULL, end, self, MASK_SHOT);

	SurfaceSpriteEffect(SFX_SPRITE_SURF_BLOOD1, SFX_BLOOD_WIDTH, SFX_BLOOD_HEIGHT,
						tr.ent, tr.endpos, tr.plane.normal);
*/
			
/*
==============
AI_EndDeath

  Generic end of death routine. Should call this for all characters that die, then do any
  special stuff for that character.
==============
*/
void AI_EndDeath(edict_t *self)
{
	// Ridah 16-may-99, stop dead bodies from sinking through floor
	if (!self->groundentity)
	{
		return;
	}
	// done.

	// Ridah, 7-5-99, fixes shooting dead bodies
//	if (!(self->svflags & SVF_DEADMONSTER))
	if (self->mins[0] != -64)
	{
		// Ridah, had to expand this even further to accomodate the punk death frames
		VectorSet (self->mins, -64, -64, -24);
		VectorSet (self->maxs,  64,  64, -4);
		self->movetype = MOVETYPE_NONE;
		self->svflags |= SVF_DEADMONSTER;
		gi.linkentity (self);
/*
		// if this position isn't valid, use the old, smaller box
		{
			trace_t tr;

			tr = gi.trace( self->s.origin, self->mins, self->maxs, self->s.origin, self, MASK_SHOT );

			if (tr.startsolid)
			{
				VectorSet (self->mins, -16, -16, -24);
				VectorSet (self->maxs,  16,  16, 0);
				gi.linkentity (self);
			}
		}
*/
	}

	// Ridah, modified this so we only spawn blood once
	if (!(self->flags & FL_SPAWNED_BLOODPOOL) && VectorCompare( self->velocity, vec3_origin ))
	{
		SpawnBloodPool (self);
		self->flags |= FL_SPAWNED_BLOODPOOL;
	}

	AI_AfterLife(self);
	// END JOSEPH
}

/*
===============
AI_SideTrace

  Returns a 1 if a RIGHT rotation will point in a direction that is free of obstacles

  Returns -1 if LEFT, 0 otherwise
===============
*/
int AI_SideTrace( edict_t *self, float dist, float inyaw, int side )
{
	trace_t	tr;
	vec3_t	angle, vec, end, end2, mins;
	float	yaw;
	int		count=0;

	VectorCopy( self->mins, mins );
	mins[2] += 16;

	// pick a random direction
	if ((side == 1) || (!side && (random() <= 0.5)))
		yaw =  inyaw;
	else
		yaw = -inyaw;

	while (1)
	{
		VectorCopy(self->s.angles, angle);
		angle[YAW] += yaw;

		AngleVectors( angle, vec, NULL, NULL );

		// trace in this direction
		VectorMA( self->s.origin, dist, vec, end );

		tr = gi.trace( self->s.origin, mins, self->maxs, end, self, MASK_PLAYERSOLID );

		if (tr.fraction == 1)
		{

			// make sure we can see our enemy from here
			if (self->enemy)
			{
				vec3_t	oldorg;
				int		result;

				VectorCopy( self->s.origin, oldorg );
				VectorCopy( tr.endpos, self->s.origin );
	
				result = AI_ClearSight(self, self->enemy, true);

				VectorCopy( oldorg, self->s.origin );

				if (!result)
				{
					goto blocked;
				}

			}

			// check this is on ground
			VectorCopy( end, end2 );
			end2[2] -= 64;

			tr = gi.trace( end, mins, self->maxs, end2, self, MASK_PLAYERSOLID );

			if (tr.fraction < 1)
			{
				// go ahead!

				if (yaw < 0)
					return -1;	// left side
				else
					return  1;	// right side
			}

		}

blocked:

		if (count++ || !inyaw || side)
			break;

		yaw *= -1;
	}

	return 0;
}

void AI_CheckStillClimbingLadder( edict_t *self )
{
	if (self->groundentity)
	{	// we're on ground, so resume moving
		self->cast_info.currentmove = self->cast_info.move_stand;
	}
}

/*
===============
AI_EndRun

  checks to see if we should walk or run
===============
*/
void AI_EndRun( edict_t *self )
{
	if (!self->last_goal)
		return;

	if (!self->cast_info.move_run)
		return;

	if (	(self->enemy != self->last_goal)
		&&	(VectorDistance( self->s.origin, self->last_goal->s.origin ) < AI_GUARDING_DIST * 2 )
		&&	(VectorLength( self->last_goal->velocity) < 200))
	{	// close enough to walk
		self->cast_info.currentmove = self->cast_info.move_runwalk;
	}
	else if ((self->last_goal != self->goal_ent) && (!self->last_goal || self->last_goal != self->guard_ent))
	{
		self->cast_info.currentmove = self->cast_info.move_run;
	}
}

/*
===============
AI_YawTrace

  Returns a 1 if a YAW rotation from self's angles will point in a direction that is free of obstacles

  Returns 0 otherwise
===============
*/
int AI_YawTrace( edict_t *self, float dist, float inyaw )
{
	trace_t	tr;
	vec3_t	angle, vec, end, end2, mins;
	int		count=0;

	VectorCopy( self->mins, mins );
	mins[2] += 16;

	VectorCopy(self->s.angles, angle);
	angle[YAW] = anglemod(angle[YAW] + inyaw);

	AngleVectors( angle, vec, NULL, NULL );

	// trace in this direction
	VectorMA( self->s.origin, dist, vec, end );

	tr = gi.trace( self->s.origin, mins, self->maxs, end, self, MASK_PLAYERSOLID );

	if (tr.fraction == 1)
	{
		// check this is on ground
		VectorCopy( end, end2 );
		end2[2] -= 64;

		tr = gi.trace( end, mins, self->maxs, end2, self, MASK_PLAYERSOLID );

		if (tr.fraction < 1)
		{
			// go ahead!
			return  true;
		}

	}

	return false;
}

/*
=============
AI_StartRun

  Start us moving
=============
*/
void AI_StartRun( edict_t *self )
{
	// start running to them
	if ( self->maxs[2] > DUCKING_MAX_Z )
		self->cast_info.currentmove = self->cast_info.move_run;
	else
		self->cast_info.currentmove = self->cast_info.move_crwalk;
}


void AI_FreeAndClearGoalEnt( edict_t *self )
{
	if (self->owner->goal_ent == self)
		self->owner->goal_ent = NULL;

	G_FreeEdict( self );
}

/*
=============
ai_stand

Used for standing around and looking for TARGETS
Distance is for slight position adjustments needed by the animations
==============
*/
void ai_stand (edict_t *self, float dist)
{

	if (dist)
		M_walkmove (self, self->s.angles[YAW], dist);

	if (self->leader && !self->leader->active_node_data)	// we're loading up a new map
	{
		return;
	}

	if (self->cast_info.aiflags & AI_DUCKATTACK)
	{	// return to standing

		self->cast_info.aiflags &= ~AI_DUCKATTACK;

		if (self->maxs[2] < self->cast_info.standing_max_z)
		{
			self->maxs[2] = self->cast_info.standing_max_z;

			self->cast_info.currentmove = self->cast_info.move_stand_up;
			self->s.frame = self->cast_info.currentmove->firstframe;
			return;
		}
	}

	// Ridah, Check DUCKING/STANDING status
	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		if (self->cast_info.move_crstand && self->cast_info.currentmove != self->cast_info.move_crstand)
		{	// we should be ducking
			self->cast_info.currentmove = self->cast_info.move_crstand;
			self->s.frame = self->cast_info.currentmove->firstframe;
		}
		else if (self->leader && !(self->cast_info.aiflags & AI_TAKE_COVER) && (self->leader->maxs[2] > DUCKING_MAX_Z))	// can we stand now?
		{
			trace_t tr;

			self->maxs[2] = self->cast_info.standing_max_z;
			tr = gi.trace(self->s.origin, self->mins, self->maxs, self->s.origin, self, MASK_PLAYERSOLID);
			if (tr.startsolid)	// can't safely stand
			{
				self->maxs[2] = DUCKING_MAX_Z;
			}
			else
			{
				self->cast_info.currentmove = self->cast_info.move_stand;
				self->s.frame = self->cast_info.currentmove->firstframe;
			}
		}
	}
	else	// not physically ducking, so make sure our animation frame reflects this
	{
		if (	(self->cast_info.currentmove == self->cast_info.move_crstand)
			&&	(self->cast_info.move_crstand != self->cast_info.move_stand))
		{	// we should be standing
			self->cast_info.currentmove = self->cast_info.move_stand;
			self->s.frame = self->cast_info.currentmove->firstframe;

		}
	}
	// Ridah, done.

	// Ridah, Do pausetime stuff, making sure we stay paused if we have to, or resume moving otherwise
	if (!self->groundentity)
	{
		if (self->cast_info.move_jump && self->cast_info.currentmove != self->cast_info.move_jump)
			self->cast_info.currentmove = self->cast_info.move_jump;

		return;
	}
	else if (self->groundentity->use && !VectorCompare(self->groundentity->velocity, vec3_origin))
	{
		self->cast_info.pausetime = level.time + 1;
	}

	// make sure we don't abort our goal waypoint next time we try to move
	self->moveinfo.wait = level.time + 3;
	self->wait = level.time + 3;

	if (self->cast_info.pausetime > level.time)
	{	
		// see if we should wait for a lift or door
		if (self->target_ent)
		{
			if (VectorCompare(self->target_ent->velocity, vec3_origin) && VectorCompare(self->target_ent->avelocity, vec3_origin))
			{	// it's not moving, are we at our destination?

				if	(self->target_ent->use != Use_Plat)
				{
					if (self->groundentity != self->target_ent)
					{	// stopped, and we're not standing on it, so proceed
						self->target_ent = NULL;
						self->cast_info.pausetime = 0;

						return;
					}
					else if (self->target_ent->nextthink > (level.time + 0.1))
					{
						if (!self->nav_data.goal_index || (VectorDistance(level.node_data->nodes[self->nav_data.goal_index-1]->origin, self->s.origin) < 128))
						{
							self->target_ent = NULL;
							self->cast_info.pausetime = 0;

							return;
						}
					}
					else	// it's stopped, and not about to go anywhere
					{
						self->target_ent = NULL;
						self->cast_info.pausetime = 0;

						return;
					}
				}
				else if	(self->groundentity == self->target_ent)
				{
					if (self->target_ent->moveinfo.state == STATE_TOP)
					{
						self->target_ent = NULL;
						self->cast_info.pausetime = 0;

						return;
					}
				}
				else if (self->target_ent->moveinfo.state == STATE_BOTTOM)
				{
					self->target_ent = NULL;
					self->cast_info.pausetime = 0;

					return;
				}
			}

			// keep waiting
			self->cast_info.pausetime = level.time + 0.2;

		}

		if (self->groundentity && self->groundentity->use)
		{	// make sure all corners are on the platform
			trace_t tr;
			vec3_t	org, orgdest;
			float	x, y;

			for (x=-16; x<24; x+=32)
			{
				for (y=-16; y<24; y+=32)
				{
					VectorSet(org, self->s.origin[0]+x, self->s.origin[1]+y, self->s.origin[2]-23);
					VectorSet(orgdest, self->s.origin[0]+x, self->s.origin[1]+y, self->s.origin[2]-30);
					tr = gi.trace(org, NULL, NULL, orgdest, self, MASK_SOLID);

					if ((tr.fraction == 1) || (tr.ent != self->groundentity))
					{
						// set a running frame
						if (self->cast_info.move_run)
							self->s.frame = self->cast_info.move_run->firstframe 
											+	(	((int)(level.time * 10))
												 %	(self->cast_info.move_run->lastframe - self->cast_info.move_run->firstframe));

						AI_MoveToPlatCenter(self, self->groundentity);
						return;
					}
				}
			}
		}
		// should we attack someonw while waiting?
		else if (self->enemy || AI_FindTarget(self))
		{
			if (AI_BeginAttack(self))
			{
				self->cast_info.attack( self );
			}
		}
		// should we get out of the way?
		else if (self->target_ent && self->target_ent->velocity[2])
		{
			// are we within the XY axis bounds?
			if (	(	(self->s.origin[0] > (self->target_ent->absmin[0] - 20))
					 && (self->s.origin[0] < (self->target_ent->absmax[0] + 20)))
				&&	(	(self->s.origin[1] > (self->target_ent->absmin[1] - 20))
					 && (self->s.origin[1] < (self->target_ent->absmax[1] + 20))))
			{
				float	*pos;
				vec3_t	mins, maxs;

				// move out of it's way

				// set a running frame
				if (self->cast_info.move_run)
					self->s.frame = self->cast_info.move_run->firstframe 
									+	(	((int)(level.time * 10))
										 %	(self->cast_info.move_run->lastframe - self->cast_info.move_run->firstframe));

				VectorSet( mins,
					self->target_ent->absmin[0] - 20,
					self->target_ent->absmin[1] - 20,
					-9999 );

				VectorSet( maxs,
					self->target_ent->absmax[0] + 20,
					self->target_ent->absmax[1] + 20,
					9999 );

				// look for a safe position
				if (pos = NAV_GetReachableNodeOutsideBounds ( self, mins, maxs ))
				{
					vec3_t vec;

					// face this direction
					VectorSubtract( pos, self->s.origin, vec );
					VectorNormalize( vec );
					self->ideal_yaw = vectoyaw( vec );

					M_ChangeYaw( self );

					// move towards it
					M_walkmove( self, self->ideal_yaw, 10 );
				}
			}
		}

		return;
	}
	// Ridah, done.

	// Ridah, check for a reason to do something (if we're too close to our leader, or there is an enemy we should seek)
	if ((!(self->cast_info.aiflags & AI_HOLD_POSITION) || self->enemy) && self->leader && !(self->cast_info.aiflags & AI_TAKE_COVER))
	{
		if (	!(self->leader->waterlevel)			// don't follow a swimming leader
			&&	AI_FollowLeader(self, self->leader))
		{
			self->last_goal = self->leader;

			AI_EndRun(self);	// does distance checking, will start us moving

			if (self->cast_info.currentmove->frame->aifunc != ai_stand && VectorDistance(self->s.origin, self->leader->s.origin) <= AI_TOO_CLOSE_DIST)
			{	// look for a node we can reach

				AI_GetAvoidDirection( self, self->leader );
				self->cast_info.currentmove = self->cast_info.move_avoid_walk;

			}

		}

	}

	if (self->cover_ent && (self->cast_info.aiflags & AI_TAKE_COVER))
	{
		float goaldist;

		if (	self->combat_goalent
			&&	(	((goaldist = VectorDistance( self->s.origin, self->combat_goalent->s.origin )) > 64)
				 ||	(	!ValidBoxAtLoc( self->combat_goalent->s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID )
					 &&	goaldist < 128 )))
		{	// we should be running to it
			self->cast_info.currentmove = self->cast_info.move_run;
			return;
		}

		// pretend we're ducking for vis test
		self->viewheight = DUCKING_MAX_Z - 4;

		// if they can see us, and we're standing around, abort taking cover
		if (AI_ClearSight( self->cover_ent, self, false))
		{
			self->cast_info.aiflags &= ~AI_TAKE_COVER;
			self->combat_goalent = NULL;
			self->cast_info.currentmove = self->cast_info.move_run;

			return;
		}

// Ridah, 5-7-99, had to modify this to prevent Betty crouching bug
		self->viewheight = self->maxs[2] - 4;
		if (self->maxs[2] > DUCKING_MAX_Z && AI_ClearSight( self->cover_ent, self, false))
		{
			self->maxs[2] = DUCKING_MAX_Z;
			if (self->cast_info.move_crouch_down)
				self->cast_info.currentmove = self->cast_info.move_crouch_down;
		}

		return;
	}

	/*
	if (	self->goal_ent 
		&&	!self->leader
		&&	!(self->cast_info.aiflags & AI_TAKE_COVER)
		&&	(	!self->enemy
			 ||	(self->cast_info.aiflags & AI_GOAL_IGNOREENEMY)))
	*/
	if (self->goal_ent && !self->leader && !(self->cast_info.aiflags & AI_TAKE_COVER))
	{
		float goaldist;

		if (	(self->cast_info.move_run)
			&&	(	(self->cast_info.goal_ent_pausetime < level.time)))
//				 ||	(self->goal_ent->solid == SOLID_TRIGGER)))
		{
			goaldist = VectorDistance(self->s.origin, self->goal_ent->s.origin);

			if (	(self->goal_ent->touch == path_corner_cast_touch)
				||	(goaldist > 256 ))
			{
				// Ridah, fixes jerky movement in SR1 intro
				if (level.cut_scene_time)
				{
					if ((self->goal_ent->touch == path_corner_cast_touch) && (self->name_index == NAME_INTROGUY1) && (goaldist < 32))
					{	// simulate touching it
						self->goal_ent->touch( self->goal_ent, self, NULL, NULL );
						return;
					}
				}

				self->nav_data.cache_node = -1;
				self->nav_data.goal_index = 0;
				self->cast_info.currentmove = self->cast_info.move_runwalk;
				return;
			}

			if (self->goal_ent->target)
			{	// face the target (eg. the Radio in Skidrow points into the room)
				edict_t	*targ;

				if (targ = G_Find( NULL, FOFS( targetname ), self->goal_ent->target ))
				{
					if (!directly_infront( self, targ ))	// straighten up
					{
						if (self->cast_info.avoid)
						{
							self->cast_info.avoid( self, targ, true );
							return;
						}
					}
				}
				else
				{
//					gi.dprintf( "ai_stand: Unable to locate 'target' to face\n" );
				}

			}
			else if (!directly_infront( self, self->goal_ent ))	// straighten up
			{
				if (self->cast_info.avoid)
				{
					self->cast_info.avoid( self, self->goal_ent, true );
					return;
				}
			}

			if (!(self->goal_ent->cast_info.aiflags & AI_GOALENT_MANUAL_CLEAR))
			{
				self->goal_ent = NULL;	// we made it there
			}
		}
	}

	// If guarding something, and we've moved out of range, abort the pursuit
	if (self->guard_ent && !(self->cast_info.aiflags & AI_TAKE_COVER))
	{
		if (	(VectorDistance( self->s.origin, self->guard_ent->s.origin ) > self->guard_ent->guard_radius)
			||	(!AI_ClearSight(self, self->guard_ent, false)))
		{
			AI_StartRun ( self );
			return;
		}
	}

	// RAFAEL	28-dec-98
	if (AI_HearPlayer (self))
	{
		return;
	}
	
	// look for things to be hostile at
	
	if (self->enemy)
	{
		AI_StartAttack( self, self->enemy );
		return;
	}
	else if (AI_FindTarget (self))
	{
		return;
	}

	if (!(self->cast_info.aiflags & AI_TAKE_COVER) && !(self->spawnflags & 1) && (self->cast_info.idle) && (level.time > self->cast_info.idle_time))
	{
		if (self->cast_info.idle_time)
		{
			self->cast_info.idle (self);
			self->cast_info.idle_time = level.time + 15 + random() * 15;
		}
		else
		{
			self->cast_info.idle_time = level.time + random() * 15;
		}
	}

	if (	!(self->cast_info.aiflags & AI_TAKE_COVER)
		&&	!(self->goal_ent)
		&&	(self->target))
// Ridah, removed this optimization, since we are always using trigger spawned characters anyway
//		&&	(	(self->spawnflags & SPAWNFLAG_IMMEDIATE_FOLLOW_PATH)
//			 ||	(	(VectorDistance(self->s.origin, g_edicts[1].s.origin) < 800)
//				 &&	(gi.inPVS(g_edicts[1].s.origin, self->s.origin)))))	// Optimization, so we only walk if the player is close
	{	// resume following our path_corner

		self->goal_ent = G_PickTarget(self->target);
		if (!self->goal_ent)
		{
			gi.dprintf ("%s can't find target %s at %s\n", self->classname, self->target, vtos(self->s.origin));
			self->target = NULL;
		}

	}

	// if we're crouched, and we can stand, then go for it
	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		if (self->stand_if_idle_time < level.time)
		{
			if (self->stand_if_idle_time > (level.time - 0.5))
			{
				self->maxs[2] = self->cast_info.standing_max_z;

				if (!ValidBoxAtLoc( self->s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID ))
					self->maxs[2] = DUCKING_MAX_Z;
				else if (self->cast_info.move_stand_up)
					self->cast_info.currentmove = self->cast_info.move_stand_up;
			}
			else
			{
				self->stand_if_idle_time = level.time + 3;
			}
		}
	}

	if ((self->cast_info.aiflags & AI_HOLD_POSITION) && !self->enemy)
	{
		// Ridah, 6-jun-99, Friendly's should avoid grenades when staying put, then come back
		if (!(self->cast_info.aiflags & AI_TAKE_COVER) || !(self->cover_ent) || (self->cover_ent->svflags & SVF_MONSTER))
		{	// we aren't avoiding anything

			if (VectorDistance( self->s.origin, self->holdpos_ent->s.origin ) >= AI_GUARDING_DIST)
			{
				self->cast_info.currentmove = self->cast_info.move_run;
			}
		}
	}

}


/*
=============
ai_walk

The monster is walking it's beat
=============
*/
void ai_walk (edict_t *self, float dist)
{
	M_MoveToGoal (self, dist);

	// check for noticing an enemy
	if (AI_FindTarget (self))
		return;

	if ((self->cast_info.search) && (level.time > self->cast_info.idle_time))
	{
		if (self->cast_info.idle_time)
		{
			self->cast_info.search (self);
			self->cast_info.idle_time = level.time + 15 + random() * 15;
		}
		else
		{
			self->cast_info.idle_time = level.time + random() * 15;
		}
	}
}


/*
=============
ai_charge

Turns towards target and advances
Use this call with a distnace of 0 to replace ai_face
==============
*/
void ai_charge (edict_t *self, float dist)
{
	vec3_t	v;

	if (self->enemy)
	{
		VectorSubtract (self->enemy->s.origin, self->s.origin, v);
		self->ideal_yaw = vectoyaw(v);
		M_ChangeYaw (self);
	}

	if (dist)
		if (!M_walkmove (self, self->s.angles[YAW], dist ))
			M_walkmove (self, self->s.angles[YAW] + 60*(rand()%3 - 1), 0.5 * dist);
}


qboolean ai_checksafeground( edict_t *self, vec3_t oldpos )
{
	vec3_t	end, start;
	trace_t	tr;
	float	x, y;

	for (x=-14; x<=14; x+=28)
	{

		for (y=-14; y<=14; y+=28)
		{

			VectorCopy( self->s.origin, start );
			start[0] += x;
			start[1] += y;

			VectorCopy( start, end );
			end[2] += self->mins[2] - 16;

			tr = gi.trace( start, vec3_origin, vec3_origin, end, self, MASK_PLAYERSOLID );

			if (tr.fraction == 1)
			{
				VectorCopy( oldpos, self->s.origin );
				gi.linkentity( self );

				return false;
			}

		}

	}

	return true;
}


/*
=============
ai_turn

don't move, but turn towards ideal_yaw
Distance is for slight position adjustments needed by the animations
=============
*/
void ai_turn (edict_t *self, float dist)
{
	vec3_t	oldpos;
//	qboolean	wassafeground;

	// wassafeground = ai_checksafeground( self, oldpos );

	VectorCopy( self->s.origin, oldpos );

	self->cast_info.aiflags &= ~AI_TURN_BLOCKED;

	if (dist > 32)
		dist = 32;

	if (self->groundentity && dist
		&&	(!(self->cast_info.aiflags & AI_NOWALK_FACE)))	// Ridah 5-8-99, fixes "aiflags 1" not working
	{
		if (!M_walkmove (self, self->s.angles[YAW], dist) && !self->leader)
		{
			self->cast_info.aiflags |= AI_TURN_BLOCKED;

			if (self->cast_info.currentmove->endfunc == AI_EndAttack)
			{	// call it now, since we can't move
				AI_EndAttack( self );
			}
		}
	}

	if (self->cast_info.avoid_ent)
	{
		// if not above safe ground, go back
		// if (wassafeground && dist && !ai_checksafeground( self, oldpos ))
		if (dist && !ai_checksafeground( self, oldpos ))
		{
			mmove_t *oldmove;

			if (self->cast_info.currentmove->endfunc == AI_EndAttack)
			{	// call it now, since we can't move
				oldmove = self->cast_info.currentmove;

				AI_EndAttack( self );

				if (self->cast_info.currentmove == oldmove)
				{
					self->cast_info.currentmove = self->cast_info.move_stand;

				}

				goto done;
			}
		}

		if (self->cast_info.last_avoid > (level.time - 1.5))
		{
			vec3_t vec;

			VectorSubtract( self->cast_info.avoid_ent->s.origin, self->s.origin, vec );
			VectorNormalize( vec );
			self->ideal_yaw = vectoyaw( vec );

			if (	(self->cast_info.currentmove->endfunc == AI_EndAttack)
				&&	(directly_infront( self, self->cast_info.avoid_ent )))
			{	// call it now, since we're facing them
				AI_EndAttack( self );
			}
		}
		else if (dist)	// been too long
		{
			self->cast_info.avoid_ent = NULL;
		}
		else	// just straighten up
		{
			vec3_t	vec;

			VectorSubtract( self->cast_info.avoid_ent->s.origin, self->s.origin, vec );
			VectorNormalize( vec );
			self->ideal_yaw = vectoyaw(vec);
		}
	}
	else if (self->enemy)
	{
		vec3_t	vec;

		VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
		VectorNormalize( vec );
		self->ideal_yaw = vectoyaw(vec);
	}

done:

	M_ChangeYaw (self);
}


void ai_turn2 (edict_t *self, float dist)
{
/*	Ridah, ai_turn does this now
	// quick fix to face the player
	if (self->enemy)
	{
		vec3_t	vec;

		VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
		VectorNormalize( vec );

		self->ideal_yaw = vectoyaw( vec );

		M_ChangeYaw( self );
	}
*/
	self->cast_info.avoid_ent = self->enemy;

	ai_turn (self, dist);
}

/*
==============
ai_sidestep

  move "dist" to the right
==============
*/
void ai_sidestep( edict_t *self, float dist)
{
	vec3_t	oldpos;

	VectorCopy( self->s.origin, oldpos );

	self->cast_info.aiflags &= ~AI_TURN_BLOCKED;

	if (dist > 32)
		dist = 32;

	if (dist)
	{
		if (!M_walkmove (self, self->s.angles[YAW] + 90, dist))
		{
			self->cast_info.aiflags |= AI_TURN_BLOCKED;

			if (self->cast_info.currentmove->endfunc == AI_EndAttack)
			{	// call it now, since we can't move
				mmove_t *om;

				om = self->cast_info.currentmove;

				AI_EndAttack( self );

				if (self->cast_info.currentmove == om)
				{
					self->cast_info.currentmove = self->cast_info.move_run;
				}
			}
		}
	}

	if (self->cast_info.avoid_ent)
	{
		// if not above safe ground, go back
		if (dist && !ai_checksafeground( self, oldpos ))
		{
			if (self->cast_info.currentmove->endfunc == AI_EndAttack)
			{	// call it now, since we can't move
				AI_EndAttack( self );
			}
		}

		if (self->cast_info.last_avoid > (level.time - 1.5))
		{
			vec3_t vec;

			VectorSubtract( self->cast_info.avoid_ent->s.origin, self->s.origin, vec );
			VectorNormalize( vec );
			self->ideal_yaw = vectoyaw( vec );
		}
		else	// been too long
		{
			self->cast_info.avoid_ent = NULL;
		}
	}
	else if (self->enemy)
	{
		vec3_t	vec;

		VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
		VectorNormalize( vec );
		self->ideal_yaw = vectoyaw(vec);
	}


	M_ChangeYaw (self);

}

/*
=============
range

returns the range catagorization of an entity reletive to self
0	melee range, will become hostile even if back is turned
1	visibility and infront, or visibility and show hostile
2	infront and show hostile
3	only triggered by damage
=============
*/
int range (edict_t *self, edict_t *other)
{
	vec3_t	v;
	float	len;

	VectorSubtract (self->s.origin, other->s.origin, v);
	len = VectorLength (v);
	if (len < MELEE_DISTANCE)
		return RANGE_MELEE;
	if (len < 500)
		return RANGE_NEAR;
	if (len < 1000)
		return RANGE_MID;
	return RANGE_FAR;
}

/*
=============
visible

returns 1 if the entity is visible to self, even if not infront ()
=============
*/
qboolean visible (edict_t *self, edict_t *other)
{
	vec3_t	spot1;
	vec3_t	spot2;
	trace_t	trace;

	VectorCopy (self->s.origin, spot1);
	spot1[2] += self->viewheight;
	VectorCopy (other->s.origin, spot2);
	spot2[2] += other->viewheight;
	trace = gi.trace (spot1, vec3_origin, vec3_origin, spot2, self, MASK_OPAQUE);
	
	if (trace.fraction == 1.0)
		return true;
	return false;
}


/*
=============
infront

returns 1 if other is in front (in sight) of self
=============
*/
qboolean infront (edict_t *self, edict_t *other)
{
	vec3_t	vec;
	float	dot;
	vec3_t	forward;
	
	AngleVectors (self->s.angles, forward, NULL, NULL);
	VectorSubtract (other->s.origin, self->s.origin, vec);
	VectorNormalize (vec);
	dot = DotProduct (vec, forward);
	
	if (dot > 0.2)
		return true;
	return false;
}

/*
=============
directly_infront

returns 1 if other is directly in front of self (pointing at)
=============
*/
qboolean directly_infront (edict_t *self, edict_t *other)
{
	vec3_t	vec;
	float	dot;
	vec3_t	forward, ang;
	float	len;

	VectorCopy( self->s.angles, ang );
	ang[PITCH] = 0;
	
	AngleVectors (ang, forward, NULL, NULL);
	VectorSubtract (other->s.origin, self->s.origin, vec);
	vec[2] = 0;
	len = VectorNormalize (vec);
	dot = DotProduct (vec, forward);
	
	if (dot > (0.98 - (len < 1024 ? 0.1 * (1.0 - (len/1024.0)) : 0)))
		return true;
	return false;
}

/*
=============
directly_infront_angles

returns 1 if other is directly in front of self (pointing at)
=============
*/
qboolean directly_infront_angle (vec3_t ang1, edict_t *self, edict_t *other)
{
	vec3_t	vec;
	float	dot;
	vec3_t	forward;//, ang;

//	VectorCopy( self->s.angles, ang );
//	ang[PITCH] = 0;
	
	AngleVectors (ang1, forward, NULL, NULL);
	VectorSubtract (other->s.origin, self->s.origin, vec);
//	vec[2] = 0;
	VectorNormalize (vec);
	dot = DotProduct (vec, forward);
	
	if (dot > 0.98)
		return true;
	return false;
}


//=============================================================================

/*
============
FacingIdeal

============
*/
qboolean FacingIdeal(edict_t *self)
{
	float	delta;

	delta = anglemod(self->s.angles[YAW] - self->ideal_yaw);
	if (delta > 45 && delta < 315)
		return false;
	return true;
}

//=============================================================================


//=============================================================================

extern void button_use (edict_t *self, edict_t *other, edict_t *activator);
extern void func_explosive_use(edict_t *self, edict_t *other, edict_t *activator);
extern void func_explosive_explode (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject);

// Ridah, new AI system movements functions
/*
================
AI_canmove

  tries a (CPU friendly) move to the destination point, making sure we don't move inside
  another solid, into water, or fall off an edge
================
*/
qboolean AI_canmove( edict_t *self, vec3_t dest )
{	// returns true if the dest box is valid
	trace_t tr;
	vec3_t dropdest;
	float	lift = 0;
	vec3_t	dir;

	VectorSubtract( dest, self->s.origin, dir );
	VectorNormalize( dir );

	tr = gi.trace(dest, self->mins, self->maxs, dest, self, MASK_PLAYERSOLID|CONTENTS_MONSTERCLIP);

	if (tr.startsolid || tr.allsolid)
	{	// try lifting up slightly
		dest[2] += (lift = 24);
		tr = gi.trace(dest, self->mins, self->maxs, dest, self, MASK_PLAYERSOLID | CONTENTS_MONSTERCLIP);

		if (tr.startsolid || tr.allsolid)
			dest[2] -= lift;

	}

	if (tr.startsolid || tr.allsolid)
	{
		edict_t	*activator;

		if (tr.ent == world || !(tr.ent->svflags & SVF_MONSTER))
		{	// try a line trace to find a blocking character
			tr = gi.trace(self->s.origin, NULL, NULL, dest, self, MASK_PLAYERSOLID|CONTENTS_MONSTERCLIP);
		}

		// get this character to get out of our way
		if (	(tr.fraction < 1)
			&&	(tr.ent != world) /* && [tr.ent is not an enemy (neutral or friend)]*/
			&&	(tr.ent->cast_info.avoid))
		{

			if (tr.ent->cast_info.last_avoid < (level.time - 2))
			if (	(tr.ent->cast_info.currentmove->frame[0].aifunc == ai_stand)
				||	(tr.ent->enemy && (VectorDistance(tr.ent->enemy->s.origin, tr.ent->s.origin) > 64)))
			{
				// tell them to move out the way, since they're not doing much
				tr.ent->cast_info.avoid(tr.ent, self, false);
			}

			// stop going for our current node
			self->nav_data.cache_node = -1;
			self->nav_data.goal_index = 0;

			// pause for a bit?
			if (!self->enemy)
			{
				self->cast_info.currentmove = self->cast_info.move_stand;
				self->cast_info.pausetime = level.time + 1;


			}

			return false;
		}
		else if (	(tr.ent->use)
				 &&	(tr.ent->use == button_use)
				 &&	(tr.ent->targetname)
				 &&	(!self->activator)
				 &&	(activator = G_Find( NULL, FOFS(target), tr.ent->targetname )))
		{	// go for this button
			self->activator = activator;

			// stop going for our current node
			self->nav_data.cache_node = -1;
			self->nav_data.goal_index = 0;
		}
		else if ((tr.ent->die == func_explosive_explode) && (tr.ent->takedamage == DAMAGE_YES))
		{	// blow it up
			T_Damage( tr.ent, self, self, dir, tr.endpos, vec3_origin, 50, 0, 0, MOD_UNKNOWN );
		}
		else //if (tr.ent->client || tr.ent->svflags & SVF_MONSTER)
		{	// go around it
			int res;

			res = AI_SideTrace( self, 32, 90, 0 );

			if (res < 0)
				self->ideal_yaw = self->s.angles[YAW] - 90;
			else if (res > 0)
				self->ideal_yaw = self->s.angles[YAW] - 90;

			M_ChangeYaw( self );
		}

		return false;
	}

//	if (self->waterlevel)		// swimming grunt doesn't need to check for onground
//		return true;

	VectorCopy(dest, dropdest);
	dropdest[2] -= (16 + lift);

	dest[2] += 0.1;
	tr = gi.trace(dest, self->mins, self->maxs, dropdest, self, MASK_PLAYERSOLID|CONTENTS_MONSTERCLIP);
	dest[2] -= 0.1;

	if (!tr.startsolid && !tr.allsolid && (tr.fraction < 1))
	{
		dest[2] = tr.endpos[2];
		return true;
	}
	else
	{
		dest[2] -= lift;
		return false;
	}
}

/*
=================
AI_movetogoal

  More robust movement code, which tries a CPU friendly move first, and then
  several walkmove()'s allowing for obstructions
=================
*/
qboolean AI_movetogoal (edict_t *self, edict_t *goal, float dist)
{
	vec3_t		dir, oldorg, dest;
	int			yaw, rnd;
	int			aborted=false;
	float		diff, goal_dist;
	float		slide_scale = 1.0;
	qboolean	moved=false;
	qboolean changezval = false;

/*
	if (	(self->cast_info.currentmove == self->cast_info.move_run)
		&&	(self->last_goal && self->last_goal->client)
		&&	(	(VectorLength( self->last_goal->velocity ) > dist*10)
			 ||	(VectorDistance(self->s.origin, self->last_goal->s.origin) > 256)))
	{
		dist *= 2;	// keep up with the player
		if (dist > 32)
			dist = 32;	// Ridah, they can run through walls if more than this
	}
*/
	self->flags &= ~FL_FLY;

	VectorSubtract(goal->s.origin, self->s.origin, dir);
	goal_dist = VectorNormalize(dir);
	self->ideal_yaw = vectoyaw(dir);

	// if we're walking up a steep slope, make sure we don't try and move too far
	if ((fabs(dir[2]) > 0.4) && (dist*fabs(dir[2]) > 20.0))
	{
		dist = 20.0 / fabs(dir[2]);
	}

	M_ChangeYaw(self);

	yaw = self->s.angles[YAW];

	if (dist > 4 && (diff = fabs(AngleDiff(self->s.angles[YAW], self->ideal_yaw))) > 30)
	{
//		dist *= 0.5;	// turning, don't go so far

//		if (dist < 4)
//			dist = 4;

		if (diff < 90)
			dist *= (1 - 0.8*(diff / 90));
		else
			dist *= (1 - 0.8*(90 / 90));

		// walk forwards
		AngleVectors( self->s.angles, dir, NULL, NULL );
		VectorMA( self->s.origin, dist, dir, dest );
	}
	// can we simply move towards this position?
	else if ((dist > 4) || (goal_dist < 32))
	{
		VectorMA(self->s.origin, dist, dir, dest);
	}
	else	// go forward if walking
	{
		vec3_t	fwd;

		AngleVectors( self->s.angles, fwd, NULL, NULL );
		VectorMA(self->s.origin, dist, fwd, dest);
	}

	yaw = self->s.angles[YAW];

	if (self->maxs[2] == DUCKING_MAX_Z)
	{
		self->maxs[2] = 8; //4;	// Ridah, modified as per requested
		changezval = true;
	}

	moved = AI_canmove(self, dest);

	if (changezval)
	{
		self->maxs[2] = DUCKING_MAX_Z;
	}

	if (moved)
	{
		VectorCopy(dest, self->s.origin);
		gi.linkentity(self);
		G_TouchTriggers (self);
		return true;
	}

	// nope, try walkmove()

	if ((((int) level.time) % 6) < 3)
		rnd = -1;
	else
		rnd = 1;

	VectorCopy(self->s.origin, oldorg);
	self->goalentity = goal;			// used by SV_movestep() for falling from air

	while (dist > 0)
	{
		if (M_walkmove(self, yaw,			dist))
		{
			moved=true;
			break;
		}

		if (dist > 16)
		{
			dist -= 8;
			continue;
		}

		if (!M_walkmove(self, yaw+(60*rnd), dist*0.7))
		if (!M_walkmove(self, yaw+(100*rnd), dist*0.5))
		if (!M_walkmove(self, yaw+(140*rnd), dist*0.3))
/*
		if (!M_walkmove(self, yaw-(60*rnd), dist*0.7))
		if (!M_walkmove(self, yaw-(100*rnd), dist*0.5))
		if (!M_walkmove(self, yaw-(140*rnd), dist*0.3))
*/
		{
			dist -= 3;
			continue;
		}

		break;
	}
/*
	if ((dist <= 0) && (self->maxs[2] > DUCKING_MAX_Z))
	{	// try ducking
		self->maxs[2] = DUCKING_MAX_Z;
		if (!M_walkmove(self, yaw, dist*0.5))
		{
			self->maxs[2] = self->cast_info.standing_max_z;
		}
		else
		{
			if (self->cast_info.move_crouch_down)
				self->cast_info.currentmove = self->cast_info.move_crouch_down;
		}
	}
*/
	if (aborted)
	{
		self->goalentity = NULL;
		return false;
	}

	if (dist <= 0)
	{
		return false;
	}

	// always face the direction we just went
	VectorSubtract(self->s.origin, oldorg, dir);
	VectorNormalize2(dir, dir);
	self->ideal_yaw = vectoyaw(dir);

	self->yaw_speed *= 0.25;

	M_ChangeYaw(self);

	self->yaw_speed *= 4;

	return moved;
}

/*
=================
AI_jump

  Called whenever a character needs to jump somewhere
=================
*/
void AI_jump (edict_t *self, float dist)
{
	vec3_t	forward;

	if (dist < 0)
		dist = -dist;

	// VectorCopy (self->goalentity->s.angles, self->s.angles);
	AngleVectors (self->s.angles, forward, NULL, NULL);
	VectorScale (forward, dist, self->velocity);
	self->velocity[2] = dist;

	if (self->groundentity)
		self->groundentity = NULL;
}

/*
=================
AI_climb

  Called whenever a character is climbing a ladder
=================
*/
void AI_climb (edict_t *self)
{
	static edict_t *goal = NULL;
	edict_t *save;
	
	if (!goal)
		goal = G_Spawn();

	save = self->goalentity;
	self->goalentity = goal;

	VectorCopy (self->s.origin, goal->s.origin);
	VectorCopy (self->s.angles, goal->s.angles);
	goal->s.origin[2] += 20;

//	self->enemy = goal;

	self->velocity[2] = 200;
//	ai_move (self, 0);

	self->wait = level.time + 1;
	self->moveinfo.wait = level.time + 1;
	
	if (self->nav_data.goal_index && (level.node_data->nodes[self->nav_data.goal_index-1]->origin[2] > self->s.origin[2]))
	{
		self->flags |= FL_FLY;
	}
	else	// done climbing
	{
		self->flags &= ~FL_FLY;
		AI_jump (self, 150);
		self->velocity[2] += 100;
		self->groundentity = NULL;
		self->cast_info.aiflags &= ~AI_SKILL_LADDER;
		self->cast_info.currentmove = self->cast_info.move_stand;

		self->wait = level.time + 4;
		self->moveinfo.wait = level.time + 1;
		level.node_data->nodes[self->nav_data.goal_index-1]->ignore_time = level.time + 3;	// don't go back to the landing node, or we may fall down
		self->nav_data.goal_index = 0;	// re-scan for a new path when we land
		self->nav_data.cache_node = -1;
	}
	
//	self->enemy = NULL;
	self->goalentity = save;

	self->s.frame = self->cast_info.move_stand->firstframe;
}

qboolean ValidBoxAtLoc(vec3_t org, vec3_t mins, vec3_t maxs, edict_t *ignore, int mask)
{
	trace_t tr;

	tr = gi.trace(org, mins, maxs, org, ignore, mask);

	return (!tr.allsolid);
}

void AI_GetAvoidDirection( edict_t *self, edict_t *other )
{
	vec3_t dir;
/*
	if (AI_SideTrace( self, 64, 0, 1 ))
	{
		self->ideal_yaw = entyaw( other, self );
	}
	else
*/
	if (NAV_GetAvoidDirection( self, other, dir ))
	{
		self->ideal_yaw = vectoyaw( dir );
	}
	else
	{
		self->ideal_yaw = anglemod( entyaw( other, self ) + 1.0*(rand()%90 - 45) );
	}
}

// Ridah, done.

//------------------------------------------------------------------------------
// New AI system
//
//	This is used whenever the cast member is doing something that involves moving
//	- will weigh up all current objectives, and carry out the desired action

extern void path_corner_cast_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);
extern void path_corner_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);

void ai_runFLASHLIGHT ( edict_t *self, float dist )
{
	trace_t tr;
	vec3_t	forward;
	vec3_t	end;
	vec3_t	mins, maxs;
	edict_t	*light;
	vec3_t	angles, origin;

	ai_run (self, dist);
	
	VectorCopy (self->s.angles, angles);
	angles[0] += crandom() * 1.5; 
	angles[1] += crandom() * 1.5; 
	angles[2] += crandom() * 1.5; 
	VectorCopy (self->s.origin, origin);
	AngleVectors (angles, forward, NULL, NULL);
	VectorCopy (origin, end);
	VectorMA (end, 8194, forward, end);

	VectorSet (mins, -8, -8, -8 );
	VectorSet (maxs, 8, 8, 8);

	tr = gi.trace (self->s.origin, mins, maxs, end, self, MASK_SHOT);

	if (tr.ent->client || tr.ent->svflags & SVF_MONSTER)
		if (!(tr.ent->flags & FL_NOTARGET))
			EP_EventSpeech (self, tr.ent, say_flashlight);

	/*
	if (tr.ent->client || tr.ent->svflags & SVF_MONSTER)
	{
		// If this is a friend, go easy on them
		if (!(tr.ent->cast_group) && (tr.ent->cast_group != self->cast_group))
			// they aren't on our side, are they a friend?
			if (!(cast_memory = level.global_cast_memory[self->character_index][tr.ent->character_index]))
			{	// record this sighting, so we can start to attack them

				AI_RecordSighting(self, tr.ent, VectorDistance(self->s.origin, tr.ent->s.origin) );
				cast_memory = level.global_cast_memory[self->character_index][tr.ent->character_index];

			}
	}
	*/

	light = G_Spawn();
	VectorCopy (tr.endpos, light->s.origin);
	light->s.renderfx |= RF_BEAM;
	light->s.effects |= EF_FLASHLIGHT;
	light->nextthink = level.time + 0.1;
	light->think = G_FreeEdict;
	gi.linkentity (light);
	
}


void ai_run ( edict_t *self, float dist )
{
	static edict_t tempgoal;
	edict_t		**goal=NULL;
	int			len;
	edict_t		tempent, *ptempent;

	route_t		route;
	node_t		*goal_node;
	vec3_t		vec, oldorg;
	int			rval, reached_goal=false;
	float		goaldist, ideal_dist;
	qboolean	moved, avoiding=false;

	if (self->cast_info.aiflags & AI_RUN_LIKE_HELL)
	{
		dist *= 1.5;
		if (dist > 32)
			dist = 32;
	}

	if (self->cast_info.move_crwalk && (self->maxs[2] < self->cast_info.standing_max_z) && (self->cast_info.currentmove != self->cast_info.move_crwalk))
	{	// we should be ducking
		self->cast_info.currentmove = self->cast_info.move_crwalk;
		self->s.frame = self->cast_info.currentmove->firstframe;
	}

	// if ducking, don't stand for at least 5 seconds after we stop
	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		self->stand_if_idle_time = level.time + 5;
	}

	tempgoal.active_node_data = level.node_data;

	if (fabs(self->s.angles[2]) > 1)
		self->s.angles[2] *= 0.8;
	else
		self->s.angles[2] = 0;

	if (self->enemy && (self->enemy->health <= 0))
	{
		self->enemy = NULL;

		if (	!(self->cast_info.aiflags & AI_TAKE_COVER)
			&&	!(self->goal_ent)
			&&	(self->cast_info.currentmove->frame->aifunc == ai_stand)
			&&	(self->start_ent)
			&&	(VectorDistance( self->s.origin, self->start_ent->s.origin) > 256))
		{	// go back to the start pos if we're not doing anything
			self->goal_ent = self->start_ent;
		}
	}

	if (self->leader && (self->leader->health <= 0))
		self->leader = NULL;

	if (!self->groundentity)
	{
		if (self->cast_info.move_jump && self->cast_info.currentmove != self->cast_info.move_jump)
			self->cast_info.currentmove = self->cast_info.move_jump;

		return;
	}

	if (self->leader && (!self->leader->active_node_data || (self->leader->waterlevel > 1)))
	{	// don't move
		self->cast_info.currentmove = self->cast_info.move_stand;

		return;
	}

	// if we've been told to stand put, only attack under special conditions
	if (	(self->leader)
		&&	(self->cast_info.aiflags & AI_HOLD_POSITION)
		&&	(!(self->cast_info.aiflags & AI_MELEE) || !self->enemy || (VectorDistance(self->s.origin, self->enemy->s.origin) > 96)))
	{
		// if running away, let us go
		if (	!(self->cast_info.aiflags & AI_TAKE_COVER)
			&&	(VectorDistance( self->s.origin, self->holdpos_ent->s.origin ) < AI_GUARDING_DIST)
			&&	(self->pain_debounce_time < (level.time - 2)))	// Ridah, 20-may-99, added this so hired guy's don't stand around while being shot at
		{
			self->cast_info.currentmove = self->cast_info.move_stand;
			self->s.frame = self->cast_info.currentmove->firstframe;
			self->cast_info.pausetime = level.time + 1.0;

			return;
		}
	}

	if (self->cast_info.aiflags & AI_SKILL_LADDER)
	{
	
		if (self->groundentity)
			self->cast_info.aiflags &= ~AI_SKILL_LADDER;
		else
			return;
	}
	else
	{
		self->flags &= ~FL_FLY;
	}

	if ((self->cast_info.aiflags & AI_HOLD_POSITION) && !self->enemy)
	{
		// Ridah, 6-jun-99, Friendly's should avoid grenades when staying put, then come back
		if (!(self->cast_info.aiflags & AI_TAKE_COVER) || !(self->cover_ent) || (self->cover_ent->svflags & SVF_MONSTER))
		{	// we aren't avoiding anything

			if (VectorDistance( self->s.origin, self->holdpos_ent->s.origin ) < AI_GUARDING_DIST)
			{
				// make sure they stop taking cover
				self->cast_info.aiflags &= ~AI_TAKE_COVER;
				self->cover_ent = NULL;

				self->cast_info.currentmove = self->cast_info.move_stand;
				self->s.frame = self->cast_info.currentmove->firstframe;

				return;
			}
			else	// run to our hold position
			{
				goal = &self->holdpos_ent;
				ideal_dist = AI_GUARDING_DIST;
				goto got_goal;
			}
		}
		else	// we are running away from something dangerous, we should return afterwards
		{
		}
	}

	if (self->cast_info.pausetime > level.time)
	{
		
		self->cast_info.currentmove = self->cast_info.move_stand;
		return;
	}
	
	if (self->groundentity && self->groundentity->use && !VectorCompare(self->groundentity->velocity, vec3_origin))
	{	// standing on a plat that's moving
		self->cast_info.pausetime = level.time + 0.5;
		self->cast_info.currentmove = self->cast_info.move_stand;

	}

	// see if we should wait for a lift or door
	if (self->target_ent)
	{
		if ( !VectorCompare(self->target_ent->velocity, vec3_origin) )
		{	// it's moving, hang around
			self->cast_info.currentmove = self->cast_info.move_stand;
			self->cast_info.pausetime = level.time + 0.2;
			return;
		}
		else if (self->target_ent->nextthink > level.time + 0.1)
		{	// it's not moving, and isn't about to start moving, so stop checking it
			self->target_ent = NULL;
		}
	}

	//===================================================================================
	//
	// Select a "goal"
	goal = &self->leader;
	ideal_dist = AI_GUARDING_DIST;

	if (	(*goal)
		&&	(AI_TooClose(self, self->leader)))
	{	// always get out of leader's way
		avoiding = true;
		goto got_goal;
	}

	if (*goal && VectorDistance( self->s.origin, (*goal)->s.origin ) > 384)
	{
		self->cast_info.aiflags |= AI_RUN_LIKE_HELL;
	}

	if (*goal && (*goal)->groundentity && (*goal)->groundentity->use)
	{
		if (!(*goal)->velocity[0] && !(*goal)->velocity[1])
		{	// standing still
			ideal_dist = AI_TOO_CLOSE_DIST;

			goto got_goal;
		}
		else	// it's moving, so we should wait
		{
			self->cast_info.pausetime = level.time + 0.2;
			self->target_ent = (*goal)->groundentity;

			self->cast_info.currentmove = self->cast_info.move_stand;


			return;
		}
	}
	// if our leader has recently issued a followme, and is far away, go to them
	else if (*goal && ((*goal)->order == ORDER_FOLLOWME) && ((*goal)->order_timestamp > (level.time - 20))
			&& (((*goal)->order_timestamp > (level.time - 5)) || (VectorDistance((*goal)->s.origin, self->s.origin) > 256)))
	{	// abort attack
		goto got_goal;
	}

enemy_again:

	if (self->enemy || (self->combat_goalent && self->cover_ent))
	{
		cast_memory_t *mem;
		edict_t	**enemy;

		// find out what we're going for
		if (self->enemy)
		{
			enemy = &self->enemy;

			if (!AI_HasLeaderButGoForEnemy(self, self->enemy))
			{
				self->enemy = NULL;
				goto enemy_again;
			}
		}
		else
		{
			enemy = &self->cover_ent;
		}

		// make sure we run
		if (self->maxs[2] == self->cast_info.standing_max_z)
			self->cast_info.currentmove = self->cast_info.move_run;

		// make sure we can see them, or have recently seen them
		if ((*enemy)->svflags & SVF_MONSTER || (*enemy)->client)
		{
			// if no memory, stop them being our enemy
			if (!(mem = level.global_cast_memory[self->character_index][(*enemy)->character_index]))
			{
				(*enemy) = NULL;
				goto enemy_again;
			}

			if (	((!self->combat_goalent) || (self->combat_goalent->think != CheckStillHiding))
				&&	((*enemy)->client && ((*enemy)->light_level <= 30))
				&&	(mem->timestamp < (level.time - 5)))
			{	// go for the last sighted position

				// DEMO HACK: send Bernie to Louie if he's alive (drastic times call for drastic measures)
				if (	(level.episode == EP_SKIDROW)
					&&	(self->name_index == NAME_ARNOLD))
				{
					edict_t	*louie;
					route_t	route;

					louie = EP_GetCharacter( NAME_LOUIE );

					// if they're near Louie, better go protect him
					if (	(louie)
						&&	(louie->health > 0)
						&&	(	!NAV_Route_EntityToEntity((*enemy), NULL, louie, VIS_PARTIAL, false, &route)
							||	(route.dist < 3000)))
					{
						self->goal_ent = louie;
						(*enemy) = NULL;
						louie->cast_info.aiflags |= AI_GOALENT_MANUAL_CLEAR;

						goto gonetolouie;
					}
				}
				// done DEMO HACK


				memset( &tempent, 0, sizeof(edict_t) );
				tempent.active_node_data = level.node_data;

				VectorCopy( mem->last_known_origin, tempent.s.origin );
				ptempent = &tempent;
				goal = &ptempent;
				VectorCopy( (*enemy)->maxs, tempent.maxs );
				VectorCopy( (*enemy)->mins, tempent.mins );

				if ((VectorDistance(self->s.origin, (*goal)->s.origin) < 128) && AI_ClearSight( self, (*goal), false ))
				{
					(*enemy) = NULL;
					goto enemy_again;
				}

gonetolouie:

				goto got_goal;
			}
		}

		goal = &(*enemy);
		ideal_dist = AI_GUARDING_DIST;

		if (	self->combat_goalent
			&&	(self->combat_goalent->inuse || (self->combat_goalent = NULL)))	// clear it if it's been freed
		{
			goal = &self->combat_goalent;

			ideal_dist = 16;	// get really close

			// if we're right infront of our enemy, abort
			if (	(self->enemy)
				&&	!(self->cast_info.aiflags & AI_GOAL_IGNOREENEMY)		// Ridah, 17-mar-99, fixes Jesus not going to threshold_target
				&&	(VectorDistance( self->s.origin, self->enemy->s.origin ) < 128)
				&&	(infront( self, self->enemy ))
				&&	(self->last_getcombatpos < (level.time - 3))
				&&	(AI_ClearSight( self->enemy, self, false )))
			{	// abort
				self->combat_goalent = NULL;
				self->cast_info.aiflags &= ~AI_TAKE_COVER;
				goto enemy_again;
			}

			if (	!(self->cast_info.aiflags & AI_MELEE)
				&&	!(self->cast_info.aiflags & AI_GOAL_IGNOREENEMY)		// Ridah, 17-mar-99, fixes Jesus not going to threshold_target
				&&	!(self->cast_info.aiflags & AI_TAKE_COVER)
				&&	((*goal)->think == G_FreeEdict)
				&&	AI_ClearSight(self, (*enemy), true))
			{
				if (self->cast_info.checkattack(self))
				{
					self->combat_goalent = NULL;
					return;		// this character has started an attack, and doesn't want to move any further
				}
			}

			if (	(self->cast_info.aiflags & AI_TAKE_COVER)
				 &&	(AI_ClearSight((*enemy), *goal, false)))
			{	// abort it
				self->cast_info.aiflags &= ~AI_TAKE_COVER;
				self->combat_goalent = NULL;
				self->dont_takecover_time = level.time + 10;
				goto enemy_again;
			}

		}
		else if (self->cast_info.checkattack)
		{	// do a character specific check for beginning an attack

			if (AI_CheckTakeCover(self))
			{
				// taking cover
//				goto (*enemy)_again;
				self->goalentity = NULL;
				self->wait = -1;
				return;
			}
			else if (AI_ClearSight(self, (*goal), true))
			{
				if (self->cast_info.checkattack(self))
				{
					self->dont_takecover_time = level.time + 5;	// attack for at least a few seconds
					return;		// this character has started an attack, and doesn't want to move any further
				}
			}
			else if (self->last_getcombatpos < (level.time - 2))
			{	// look for a good combat position
				float	*pos;

				if (pos = NAV_GetCombatPos( self, (*goal), self->cast_info.aiflags & AI_MELEE ))
				{
					edict_t *combatent;

					combatent = G_Spawn();
					VectorCopy( pos, combatent->s.origin );

					self->cast_info.aiflags &= ~AI_GOAL_IGNOREENEMY;
					self->cast_info.aiflags &= ~AI_TAKE_COVER;
					
					self->combat_goalent = combatent;
					combatent->cast_info.aiflags |= AI_GOAL_RUN;

					combatent->think = G_FreeEdict;
					combatent->nextthink = level.time + 5;	// give us some time to get there

					// go for it this frame
					goto enemy_again;
				}
			}

		}
	}
	else
	{	// look for things to be hostile at
		if ((self->s.frame == self->cast_info.currentmove->firstframe) && AI_FindTarget (self))
			goto enemy_again;
	}


	// If guarding something, and we've moved out of range, abort the pursuit
	if (self->guard_ent)
	{
		if (!(*goal))
		{	// if not doing anything else, return to the guard_ent
			if (	(VectorDistance( self->s.origin, self->guard_ent->s.origin ) > self->guard_ent->guard_radius)
				||	(!AI_ClearSight(self, self->guard_ent, false)))
//			if (VectorDistance( self->s.origin, self->guard_ent->s.origin ) > AI_GUARDING_DIST)
			{
				goal = &self->guard_ent;
				ideal_dist = AI_GUARDING_DIST;
			}
		}
		else if (	(VectorDistance( self->s.origin, self->guard_ent->s.origin ) > self->guard_ent->guard_radius)
				 &&	(!gi.inPVS(self->s.origin, self->guard_ent->s.origin))
				 &&	(!self->enemy || !AI_ClearSight(self, self->enemy, false)))		// don't go back if we can see our enemy
		{
			cast_memory_t	*mem;

			// always abort an enemy if it exists
			if (self->enemy)
			{
				mem = level.global_cast_memory[self->character_index][self->enemy->character_index];

				if (mem)
				{
					mem->ignore_time = level.time + ENEMY_SIGHT_DURATION + 0.2;	// ignore them for a bit
				}

				self->enemy = NULL;
			}

			goal = &self->guard_ent;
			ideal_dist = AI_GUARDING_DIST;
		}
	}

got_goal:

	// Ridah, 17-may-99, fixes Jesus not going to threshold_target
	if ((!(*goal) || (self->cast_info.aiflags & AI_GOAL_IGNOREENEMY)) && self->goal_ent)
	{
		goal = &self->goal_ent;

		if ((*goal)->solid == SOLID_TRIGGER)
			ideal_dist = 0;
		else if ((*goal)->dmg_radius)
			ideal_dist = (*goal)->dmg_radius;
		else
			ideal_dist = 128;
	}

	// should we press a button?
	if (self->activator)
	{
		if (self->activator->moveinfo.state != STATE_BOTTOM)
		{	// button has been pressed (probably by someone else)
			self->activator = NULL;
		}
		else	// go for the button
		{
			goal = &self->activator;
			ideal_dist = 0;
		}
	}


	//===================================================================================
	//
	// move towards this "goal"

	// always run to our attacker if on fire
	if ((self->onfiretime > 0) && (self->onfireent))
	{
		goal = &self->onfireent;
		ideal_dist = 64;
	}

	self->last_goal = *goal;

	if (!(*goal))
	{	// we don't have a goal, time for a beer

		self->cast_info.currentmove = self->cast_info.move_stand;

		return;

	}
	else	// we have a "goal"
	{

		// if it's our leader, make sure they are still reachable (not on a platform)

		if (	((*goal) == self->leader)
			&&	((*goal)->groundentity)
			&&	((*goal)->groundentity->use)
			&&	(!VectorCompare((*goal)->groundentity->velocity, vec3_origin)))
		{
			// They're on a lift, so hang around for a bit
			self->cast_info.pausetime = level.time + 2;
			self->cast_info.currentmove = self->cast_info.move_stand;
			self->s.frame = self->cast_info.currentmove->firstframe;

			
			return;
		}

		// handle ->goal_ent specially
		else if ((goal == &self->goal_ent) || (goal == &self->combat_goalent) || ((goal == &self->leader) && !avoiding))
		{
			float	goal_dist;

			goal_dist = VectorDistance( self->s.origin, (*goal)->s.origin );

			// Make sure we are running if we should be
			if (self->maxs[2] == self->cast_info.standing_max_z)
			{
				if (self->cast_info.move_runwalk && (goal == &self->leader) && (goal_dist < 256))
				{
					if (self->cast_info.currentmove != self->cast_info.move_runwalk)
					{
						self->cast_info.currentmove = self->cast_info.move_runwalk;
						self->s.frame = self->cast_info.currentmove->firstframe;
						self->cast_info.aiflags &= ~AI_RUN_LIKE_HELL;
					}
				}
				else if (((*goal) == self->enemy) || ((*goal)->cast_info.aiflags & AI_GOAL_RUN) /*&& (goal_dist > ideal_dist*2)*/)
				{
					self->cast_info.currentmove = self->cast_info.move_run;
				}
				else if (self->cast_info.move_runwalk)
				{
					self->cast_info.currentmove = self->cast_info.move_runwalk;
					self->cast_info.aiflags &= ~AI_RUN_LIKE_HELL;
				}
			}

			// should we stop moving?

			if ((*goal)->solid != SOLID_TRIGGER)
			{	// we can't touch it, so just get close to it

				if (goal_dist < ideal_dist)	// FIXME: make this configurable?
				{

					if (	(goal != &self->leader)
						||	(	((*goal)->client == NULL && (*goal)->cast_info.currentmove->frame->aifunc == ai_stand)
							 ||	((*goal)->client != NULL && VectorLength((*goal)->velocity) < 50)))
					{
						self->cast_info.currentmove = self->cast_info.move_stand;


						if ((goal == &self->goal_ent) && !(self->goal_ent->cast_info.aiflags & AI_GOALENT_MANUAL_CLEAR))
						{
							self->goal_ent = NULL;	// we made it there
						}

						if (goal == &self->combat_goalent)	// we've reached it, so clear it out
						{

							if (!(self->cast_info.aiflags & AI_TAKE_COVER))
							{
								self->combat_goalent = NULL;
							}

						}
						else if ((*goal) == self->start_ent && (*goal) == self->goal_ent)
						{
							self->goal_ent->cast_info.aiflags &= ~AI_GOAL_RUN;
							self->goal_ent = NULL;
						}

						return;
					}

				}
				else
				{
					if (	((*goal)->solid != SOLID_BBOX)
						&&	(VectorDistance( self->s.origin, (*goal)->s.origin ) < 64)
						&&	(!ValidBoxAtLoc( (*goal)->s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID )))
					{	// we can't get there
						self->cast_info.aiflags &= ~AI_TAKE_COVER;
						*goal = NULL;
						return;
					}
				}

			}

			// is it dangerous to go for it?
			else if (	(self->enemy)
					 &&	!(self->cast_info.aiflags & AI_GOAL_IGNOREENEMY)		// Ridah, 17-mar-99, fixes Jesus not going to threshold_target
					 &&	((*goal)->touch == path_corner_cast_touch)
					 &&	(	(VectorDistance( self->enemy->s.origin, (*goal)->s.origin ) < 256)
						 ||	(	(VectorDistance( self->enemy->s.origin, self->s.origin ) < 512)
							 &&	(infront(self->enemy, self)))))
			{	// simulate touching the path_corner
				(*goal)->touch( (*goal), self, NULL, NULL );
				return;
			}

			// can we walk straight towards it?
			else if (	(goal_dist < ideal_dist*2)
					 &&	(NAV_Visible( self->s.origin, (*goal)->s.origin, VIS_PARTIAL, self->maxs[2] < self->cast_info.standing_max_z ))
					 &&	(NAV_Reachable( self->s.origin, (*goal)->s.origin, (byte)self->waterlevel, (byte)(*goal)->waterlevel, (self->maxs[2] < self->cast_info.standing_max_z), REACHABLE_POOR )))
			{
				self->nav_data.cache_node = -1;
				self->nav_data.goal_index = 0;

				if (goal_dist < ideal_dist/2)
				{
					if ((*goal)->target && ((*goal)->touch == path_corner_cast_touch))
					{	// simulate touching the path_corner
						(*goal)->touch( (*goal), self, NULL, NULL );
					}
					else
					{
						if (!strcmp( (*goal)->classname, "cast_origin" ))
						{
							goal = NULL;
						}

						self->cast_info.currentmove = self->cast_info.move_stand;

						return;
					}
				}
			}

//			NAV_DrawLine( self->s.origin, (*goal)->s.origin );
		}

		else if (goal == &self->guard_ent)
		{
			// just walk back there
			if (	(self->maxs[2] == self->cast_info.standing_max_z)
				&&	(self->cast_info.currentmove == self->cast_info.move_run))
			{
				self->cast_info.currentmove = self->cast_info.move_runwalk;
			}
		}
	}

	// are we within the ideal range of our goal?

	if (	((*goal) != self->enemy)
		&&	!((*goal)->touch)
		&&	(ideal_dist > 0.1)
		&&	((goaldist = VectorDistance (self->s.origin, (*goal)->s.origin)) < ideal_dist)
		&&	NAV_Visible( self->s.origin, (*goal)->s.origin, VIS_LINE, self->maxs[2] < self->cast_info.standing_max_z ))
//		&&	AI_ClearSight(self, (*goal)))
	{
		self->cast_info.aiflags &= ~AI_IGNORE_ENEMY;

		if (	(!self->leader || ((*goal) != self->leader->moveout_ent))

			&&	(	((*goal) != self->leader)
				 ||	(!(*goal)->groundentity)
				 ||	(!(*goal)->groundentity->use)
				 ||	(!VectorCompare((*goal)->velocity, vec3_origin)))

			&&	(	(AI_FollowLeader(self, (*goal))		// if they are on a lift, and trying to move, we should avoid them, otherwise stay real close
				 &&	(	!((*goal)->groundentity)
					 ||	!((*goal)->groundentity->use)
					 ||	!VectorCompare((*goal)->velocity, vec3_origin)))))
		{	// move back, away from goal

			VectorSubtract(self->s.origin, (*goal)->s.origin, vec);

			VectorNormalize2(vec, vec);
			VectorScale(vec, 64, vec);
			VectorAdd(self->s.origin, vec, tempgoal.s.origin);

			AI_movetogoal(self, &tempgoal, dist);

			return;
		}

		self->cast_info.currentmove = self->cast_info.move_stand;

		return;
	}


	// Check for fast running (same as player)

	// Ridah, if the guy is a friendly, and he's hurt, don't run as fast
	if (self->cast_group != 1 || self->health > self->max_health/2)
	{
		if (((*goal)->client || ((*goal)->svflags & SVF_MONSTER)) || ((*goal)->cast_info.aiflags & AI_RUN_LIKE_HELL))
		{

			if (self->cast_info.aiflags & AI_RUN_LIKE_HELL)
			{
				dist*=2.5;
				if (dist > 32)
					dist = 32;	// Ridah, they can run through walls if more than this
			}
			
			// RAFAEL 30-DEC-98
			if (self->cast_info.aiflags & AI_RUSH_THE_PLAYER)
			{
				dist*=2.5;
				if (dist > 32)
					dist = 32;
			}

		}
	}

	// need to put this here because the dist for new models are > 32
	if (dist > 32)
		dist = 32;


	//===================================================================================
	//
	// We need to move somewhere

	tempgoal.nav_data.goal_index = self->nav_data.goal_index;

	goal_node = NULL;

	// find a path to the player
	if (self->nav_data.goal_index > 0)
	{
		goal_node = level.node_data->nodes[self->nav_data.goal_index-1];
		rval = ROUTE_INDIRECT;
	}
	else
	{

		rval = NAV_Route_EntityToEntity(self, goal_node, (*goal), VIS_PARTIAL, false, &route);

		// update current node
		self->nav_data.goal_index = tempgoal.nav_data.goal_index = route.path+1;

		if (rval == ROUTE_INDIRECT)
		{
			goal_node = level.node_data->nodes[self->nav_data.goal_index-1];

			// is it a crouching node?
			if (goal_node->node_type & NODE_DUCKING)
			{
				if (self->maxs[2] > DUCKING_MAX_Z)
				{
					if (self->cast_info.move_crouch_down)
						self->cast_info.currentmove = self->cast_info.move_crouch_down;
					self->maxs[2] = DUCKING_MAX_Z;

					return;
				}
			}

			// allow 5 seconds to reach the new target
			self->wait = level.time + 5;
		}
		else if (rval == ROUTE_DIRECT)
		{
// Disabled this, if we have a direct route, then we don't need to change this
/*
			if (((*goal)->solid == SOLID_BBOX) && ((*goal)->maxs[2] < (*goal)->cast_info.standing_max_z) && (self->maxs[2] > DUCKING_MAX_Z))
			{
				if (self->cast_info.move_crouch_down)
					self->cast_info.currentmove = self->cast_info.move_crouch_down;
				self->maxs[2] = DUCKING_MAX_Z;

				return;
			}
*/
			self->wait = level.time + 3.5;
		}
	}

	
	self->last_rval = rval;


	if (!rval)
	{	// no route
		int	max_cnt=50;

		if ((goal != &self->enemy) || !(self->cast_info.aiflags & AI_MELEE) || (self->cast_info.aiflags & AI_NO_TAKE_COVER))
		{	// resort to id's movement code (YUCK!)
			self->goalentity = (*goal);
			M_MoveToGoal (self, dist);
		}
		else // hide until we can reach them again
		{
			AI_ForceTakeCover( self, self->enemy, true );
			self->cast_info.aiflags &= ~AI_TAKECOVER_IGNOREHEALTH;
		}

		if (nav_aipath->value && (*goal))
		{
			gi.dprintf( "%s", self->classname );
			if (self->name)
				gi.dprintf( " (%s)", self->name );
			gi.dprintf( " has no route to %s\n", self->classname, (*goal)->classname );
		}

		if (gi.inPVS( g_edicts[1].s.origin, self->s.origin ))
		{
			max_cnt = 5;
		}

		if (self->noroute_count++ > max_cnt)		// keep trying for some time
		{
			if (/*(*goal) ==*/ self->enemy)		// don't bother going for them if there isn't a route
			{
				self->combat_goalent = NULL;
				AI_ForceTakeCover( self, self->enemy, false );

//				if (self->cast_info.aiflags & AI_TAKE_COVER)
					return;
			}
			else if (self->combat_goalent && (*goal) == self->combat_goalent)
			{
				self->combat_goalent = NULL;
				return;
			}

			// stop going for whatever we were going for
			self->cast_info.pausetime = level.time + 2;
			self->cast_info.currentmove = self->cast_info.move_stand;
			self->s.frame = self->cast_info.currentmove->firstframe;

			return;
		}

		goto done;

	}
	else
	{
		self->noroute_count = 0;
	}

	// successfully found a route

	if (rval == ROUTE_DIRECT)
	{	// we can reach the "goal" directly
		float	goal_dist;

		goal_dist = VectorDistance( self->s.origin, (*goal)->s.origin );

		if (goal_dist < dist)
			dist = goal_dist;

		self->goalentity = (*goal);
		AI_movetogoal(self, (*goal), dist);

		if (!(*goal))	// it's been cleared somewhere
			return;

		if (nav_aipath->value)
		{
			NAV_DrawLine( self->s.origin, (*goal)->s.origin );
		}

		goto done;
	}

	// indirect route

// =============================================================================================

// FIXME: if goal is a character, and we are not within gi.PHS() or gi.PVS(), then we can't 
// follow them, since we can't see or hear them. Therefore, we should either go to their last
// sighted position, or give up on them.

// =============================================================================================

	VectorCopy(goal_node->origin, tempgoal.s.origin);
	tempgoal.s.origin[2] = self->s.origin[2];
	len = VectorDistance(self->s.origin, tempgoal.s.origin);
	tempgoal.s.origin[2] = goal_node->origin[2];

	if (len <= dist*1.2)
	{	// reached the waypoint
		reached_goal = true;
		dist = len;
	}

	if (nav_aipath->value)
	{
		NAV_DrawLine( self->s.origin, tempgoal.s.origin );
		NAV_Debug_DrawPath( &tempgoal, (*goal) );
	}

	//===================================================================================
	//
	// are we about to reach the "goal"?

	if (reached_goal)
	{

		// should we JUMP?

		if (goal_node->node_type & NODE_JUMP)
		{

			// do we really want to jump here?
			if (	(NAV_Route_NodeToEntity(goal_node, (*goal), VIS_PARTIAL, &route) == ROUTE_INDIRECT)
				&&	(route.path == goal_node->goal_index))
			{

				if ((level.node_data->nodes[goal_node->goal_index]->origin[2] - 54) > goal_node->origin[2])
				{		// must be a ladder

	
					// note to Ryan jun-07-99 
					// The dogs can go up and down ladders. Can this be stopped? 
					
					// move us to the ladder if possible, if not abort climbing
					/*
					if (ValidBoxAtLoc( tempgoal.s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID ))
					{
						VectorCopy( tempgoal.s.origin, self->s.origin );

						self->s.angles[YAW] = self->ideal_yaw = (float) goal_node->yaw;
						self->cast_info.aiflags |= AI_SKILL_LADDER;
						self->nav_data.goal_index = route.path+1;
						AI_climb (self);

						if (self->cast_info.move_start_climb)
							self->cast_info.currentmove = self->cast_info.move_start_climb;
					}
					else	// abort running for a bit
					{
						self->cast_info.currentmove = self->cast_info.move_stand;
						self->cast_info.pausetime = level.time + 1.0;
						self->nav_data.goal_index = 0;

						return;
					}
					*/
					
					if ((self->gender) && ValidBoxAtLoc( tempgoal.s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID ))
					{
						VectorCopy( tempgoal.s.origin, self->s.origin );

						self->s.angles[YAW] = self->ideal_yaw = (float) goal_node->yaw;
						self->cast_info.aiflags |= AI_SKILL_LADDER;
						self->nav_data.goal_index = route.path+1;
						AI_climb (self);

						if (self->cast_info.move_start_climb)
							self->cast_info.currentmove = self->cast_info.move_start_climb;
					}
					else	// abort running for a bit
					{
						self->cast_info.currentmove = self->cast_info.move_stand;
						self->cast_info.pausetime = level.time + 1.0;
						self->nav_data.goal_index = 0;

						return;
					}

				}
				else	// normal jump
				{
					vec3_t neworg;
					float	speed;

					self->flags &= ~FL_FLY;

					VectorSubtract(level.node_data->nodes[goal_node->goal_index]->origin, goal_node->origin, vec);
					VectorNormalize2(vec, vec);
					self->s.angles[YAW] = vectoyaw(vec);

					if ((speed = VectorLength(goal_node->jump_vel)) > 250)
					{
						vec3_t	vec;
						float	length;

						AI_jump (self, 200);

						VectorCopy(goal_node->jump_vel, vec);

						self->velocity[2] = 0;
						vec[2] = 0;

						length = VectorLength( vec );

						if (length < 20)
						{
							VectorNormalize( vec );
							VectorScale( vec, 20, vec );
							
							goal_node->jump_vel[0] = vec[0];
							goal_node->jump_vel[1] = vec[1];

							level.node_data->modified = true;
						}
						else
						{
							VectorNormalize( self->velocity );
							VectorScale( self->velocity, length, self->velocity );
						}

						self->velocity[2] = goal_node->jump_vel[2];

						if (goal_node->jump_vel[2] > 200)
							self->velocity[2] = 300;
						else if (goal_node->jump_vel[2] < 180)
							self->velocity[2] = 180;
					}
					else
					{
						AI_jump (self, 200);
						self->velocity[2] = 200;
					}

					VectorCopy(self->s.origin, neworg);
					neworg[2] += 1;
					if (ValidBoxAtLoc(neworg, self->mins, self->maxs, self, MASK_PLAYERSOLID))
						self->s.origin[2] += 1;

					self->groundentity = NULL;

					if (self->cast_info.move_jump)
						self->cast_info.currentmove = self->cast_info.move_jump;

					// we need a way of playing character specific jump sounds
					//gi.sound(self, CHAN_VOICE, gi.soundindex("*jump1.wav"), 0.8, ATTN_NORM, 0);

					gi.linkentity(self);
				}

				self->nav_data.goal_index = goal_node->goal_index + 1;
				reached_goal = false;

				goto done;
			}

		}

	}

	//===================================================================================
	//
	// Perform the move towards the goal node

	VectorCopy(self->s.origin, oldorg);
	
	// move towards the node
	moved = AI_movetogoal(self, &tempgoal, dist);

	//...................................................................................
	// Evaluate the move

	// did we get closer?
	if (moved)
	{
		self->moveinfo.wait = level.time + 0.4;
	}
	else if (	(self->moveinfo.wait < level.time)
			 ||	(self->wait < level.time)
			 ||	(!ValidBoxAtLoc( tempgoal.s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID)))
	{	// abort this node, we've been trying to get to it for long enough

		goal_node->ignore_time = level.time + 3;
		self->nav_data.cache_node = -1;
		self->moveinfo.wait = level.time + 0.7;		// give some time on the next node
		self->wait = level.time + 3;
		self->nav_data.goal_index = 0;
		reached_goal = false;

	}
	else // will a jump be useful here?
	{
		if ((self->s.origin[2] + 16 < (&tempgoal)->s.origin[2]))
		{
			vec3_t start, mins, dir, org;
			trace_t	trace;

			VectorCopy(self->s.origin, start);

			AngleVectors(self->s.angles, dir, NULL, NULL);
			VectorScale(dir, 32, dir);
			VectorAdd(start, dir, org);

			VectorCopy(self->mins, mins);
			mins[2] += 8;

			trace = gi.trace(start, mins, self->maxs, org, self, MASK_PLAYERSOLID);

			if ((trace.fraction < 1) && !(trace.ent->svflags & SVF_MONSTER) && (fabs(trace.plane.normal[2]) < 0.1))
			{
				// set ideal velocity
				dir[2] = 310;

				// see if clear at head
				start[2] += 32;
				org[2] += 32;

				trace = gi.trace(start, NULL, NULL, org, self, MASK_SOLID);

				if (trace.fraction == 1)
				{	// safe to jump
					AI_jump (self, 150);
					self->velocity[2] += 100;

					if (self->cast_info.move_jump)
						self->cast_info.currentmove = self->cast_info.move_jump;
				}
			}
		}
	}

done:

	if (	(self->maxs[2] < self->cast_info.standing_max_z)
		&&	(	(goal_node && !(goal_node->node_type & NODE_DUCKING))
			 ||	(rval == ROUTE_DIRECT)))
	{	// we should return to standing, if possible
		trace_t tr;

		self->maxs[2] = self->cast_info.standing_max_z;
		tr = gi.trace(self->s.origin, self->mins, self->maxs, self->s.origin, self, MASK_PLAYERSOLID);
		if (	tr.startsolid
			||	(goal_node && !NAV_Visible( self->s.origin, goal_node->origin, VIS_PARTIAL, false ))
			||	((rval == ROUTE_DIRECT) && (*goal) && !NAV_Visible( self->s.origin, (*goal)->s.origin, VIS_PARTIAL, false )))
		{	// can't safely stand
			self->maxs[2] = DUCKING_MAX_Z;
		}
		else if (self->cast_info.move_stand_up)	// ok to stand
		{
//gi.dprintf("2\n");
			self->cast_info.currentmove = self->cast_info.move_stand_up;
			self->s.frame = self->cast_info.currentmove->firstframe;
			return;
		}
		else
		{
			self->cast_info.currentmove = self->cast_info.move_run;
		}
	}

	if (reached_goal)
	{

		// press a button?
		if (	(goal_node->node_type & NODE_BUTTON)
			&&	(goal_node->goal_ent)
			&&	((goal_node->goal_ent->timestamp < (level.time - 4)) || (goal_node->goal_ent->activator != self))
			&&	(goal_node->goal_ent->use))
		{	// simulate touching it
			goal_node->goal_ent->use( goal_node->goal_ent, self, self );

			self->cast_info.pausetime = level.time + 2;	// wait for it to do something

			// walk backwards
			self->cast_info.currentmove = self->cast_info.move_avoid_reverse_walk;
			self->ideal_yaw = (float)goal_node->yaw;	// don't turn

			self->activator = NULL;		// stop going for a button

			return;
		}

		if (	(goal_node->node_type & NODE_PLAT)
			&&	(self->groundentity == goal_node->goal_ent)
			&&	(VectorCompare( self->groundentity->velocity, vec3_origin )))
		{
			// we're standing on it, so trigger it
			if (self->groundentity->targetname)
			{
				edict_t *btn=NULL, *btn2=NULL;
				char	*targetname;

				targetname = self->groundentity->targetname;

				while (btn = G_Find( btn, FOFS( target ), targetname ))
				{
					if (!strcmp(btn->classname, "trigger_relay") && btn->targetname)
					{	// check this target

						btn2 = NULL;
						while (btn2 = G_Find( btn2, FOFS( target ), btn->targetname ))
						{
							if (fabs( btn2->absmin[2] - self->s.origin[2] ) < 64)
							{
								btn2->use( btn2, self, self );
								break;
							}
						}
					}
					else if (btn->solid == SOLID_BSP)
					{
						if (fabs( btn->absmin[2] - self->s.origin[2] ) < 64)
						{
							btn->use( btn, self, self );
							break;
						}
					}
				}
			}
			else
			{
				self->groundentity->use( self->groundentity, self, self );
			}

			return;
		}

		if (!(*goal))
		{	// it's been cleared
			return;
		}

		// find the next waypoint
		rval = NAV_Route_EntityToEntity( self, goal_node, (*goal), VIS_PARTIAL, false, &route);

		self->nav_data.goal_index = tempgoal.nav_data.goal_index = route.path+1;

		if (rval == ROUTE_INDIRECT)
		{
			int i, temp_rval, rval2;
			node_t	*temp_node;

			// check for a plat along the route that's not ready
			temp_node	= goal_node;
			i			= 0;
			while ((temp_rval = NAV_Route_NodeToEntity( temp_node, (*goal), VIS_PARTIAL, &route)) && (i++ < 3))
			{
				if (temp_rval == ROUTE_DIRECT)
					break;

				temp_node = level.node_data->nodes[route.path];
				if (temp_node->node_type & NODE_PLAT)
				{
					if (	temp_node->goal_ent
						&&	VectorCompare(temp_node->goal_ent->velocity, vec3_origin))
					{	// platform is stationary
						trace_t tr;
						vec3_t	src, dest;

						// make sure this lift will take us to the goal
						if (	!(rval2 = NAV_Route_NodeToEntity( temp_node, (*goal), VIS_PARTIAL, &route))
							||	(rval2 == ROUTE_DIRECT)
							||	(route.path != temp_node->goal_index))
						{
							break;	// we don't want to go on the lift
						}

						// make sure it is waiting for us

						VectorCopy(temp_node->origin, dest);
						dest[2] -= 1;
						VectorCopy(temp_node->origin, src);
						src[2] += 1;

						tr = gi.trace(src, self->mins, self->maxs, dest, self, MASK_SOLID);

						if (!tr.startsolid && (tr.ent == temp_node->goal_ent) && (tr.fraction < 1))
							break;	// cool, it's there waiting for us

						// hmm, it's not waiting, should we press a button for it to come back down?
						if (temp_node->goal_ent->targetname)
						{
							edict_t *btn=NULL, *btn2=NULL;
							char	*targetname;

							targetname = temp_node->goal_ent->targetname;

							while (btn = G_Find( btn, FOFS( target ), targetname ))
							{
								if (!strcmp(btn->classname, "trigger_relay") && btn->targetname)
								{	// check this target

									btn2 = NULL;
									while (btn2 = G_Find( btn2, FOFS( target ), btn->targetname ))
									{
										if (fabs( btn2->absmin[2] - self->s.origin[2] ) < 64)
										{
											btn2->use( btn2, self, self );
											break;
										}
									}
								}
								else if (btn->solid == SOLID_BSP)
								{
									if (fabs( btn->absmin[2] - self->s.origin[2] ) < 64)
									{
										btn->use( btn, self, self );
										break;
									}
								}
							}
						}
					}

					// damn, route is broken, so hang around for a bit
					self->cast_info.pausetime = level.time + 2;

					self->target_ent = temp_node->goal_ent;
					self->cast_info.currentmove = self->cast_info.move_stand;
					self->nav_data.goal_index = tempgoal.nav_data.goal_index = goal_node->index+1;		// check again when done waiting

					return;
				}
			}

			self->wait = level.time + 3;
			goal_node = level.node_data->nodes[self->nav_data.goal_index-1];

			// is it a crouching node?
			if (goal_node->node_type & NODE_DUCKING)
			{
				if (self->maxs[2] == self->cast_info.standing_max_z)
				{
					if (self->cast_info.move_crouch_down)
						self->cast_info.currentmove = self->cast_info.move_crouch_down;
					self->maxs[2] = DUCKING_MAX_Z;
				}
			}

		}
	}
	else if (goal_node && !(goal_node->node_type & NODE_DUCKING) && (self->maxs[2] < self->cast_info.standing_max_z))
	{	// can we stand?
		if (NAV_Visible( self->s.origin, goal_node->origin, VIS_PARTIAL, false ))
		{
			self->maxs[2] = self->cast_info.standing_max_z;
			if (self->cast_info.move_stand_up)
			{
				self->cast_info.currentmove = self->cast_info.move_stand_up;
				self->s.frame = self->cast_info.currentmove->firstframe;
				return;
			}
		}
	}

	self->goalentity = (*goal);
}

void ai_runDOKEY (edict_t *self, float dist)
{
	AI_movetogoal(self, self->goal_ent, dist);
}
