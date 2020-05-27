// STEELTOWN
#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

qboolean ProcessSteeltownMomo (edict_t *self, edict_t *other);

qboolean ProcessKroker (edict_t *self, edict_t *player, cast_memory_t *mem);
qboolean ProcessKids (edict_t *self, edict_t *player, cast_memory_t *mem);
qboolean ProcessSteeltownBambi (edict_t *self, edict_t *player, cast_memory_t *mem);

qboolean EP_Steeltown_CastSight ( edict_t *self, edict_t *other, cast_memory_t *mem )
{

	if (self->name_index == NAME_DAVID && other->client)
	{
		if (other->client && (mem->memory_type == MEMORY_TYPE_ENEMY) )
		{	// give them a chance to make friends if they holster
			
			self->s.model_parts[PART_GUN].invisible_objects = 0;
			self->s.model_parts[PART_GUN2].invisible_objects = 0;
		}
	}
	
	if (self->name_index == NAME_PETE)
	{
		if (other->client && (mem->memory_type == MEMORY_TYPE_ENEMY) /*&& !(other->client->pers.weapon)*/)
		{	// give them a chance to make friends if they holster
			self->enemy = NULL;

			// make them a neutral instead of enemy
			AI_RemoveFromMemory( self, mem );
			AI_AddToMemory( self, mem, MEMORY_TYPE_NEUTRAL );
			mem->flags &= ~MEMORY_HOSTILE_ENEMY;
		}
		// ignore them
		return true;
	}

	if (self->name_index == NAME_MOMO && other->client)
	{
		if (mem->timestamp < (level.time - 8))
		{	// haven't seen them for a while
			other->episode_flags &= ~EP_Steeltown_MOMO_ASKED_MONEY;
			// mem->flags &= ~MEMORY_LASTWARNING;
		}

		if ((mem->memory_type == MEMORY_TYPE_ENEMY) /*&& !other->client->pers.weapon*/)
		{	// give them a chance to make friends if they holster
			self->enemy = NULL;

			// make them a neutral instead of enemy
			AI_RemoveFromMemory( self, mem );
			AI_AddToMemory( self, mem, MEMORY_TYPE_NEUTRAL );
			mem->flags &= ~MEMORY_HOSTILE_ENEMY;
		}

		return true;
	}

	if ((self->name_index >= NAME_KID_1 && self->name_index <= NAME_KID_8) && other->client)
	{
		if ( !(other->client->pers.holsteredweapon) ) 
		{
			mem->flags |= MEMORY_AFRAID;
		}
		else
		{
			self->cast_info.aiflags &= ~AI_NO_TALK;
			mem->flags &= ~MEMORY_AFRAID;
		}

		if ((mem->memory_type == MEMORY_TYPE_ENEMY) )
		{	
			self->enemy = NULL;

			// make them a neutral instead of enemy
			AI_RemoveFromMemory( self, mem );
			AI_AddToMemory( self, mem, MEMORY_TYPE_NEUTRAL );
			mem->flags &= ~MEMORY_HOSTILE_ENEMY;
		}

		return true;
	}


	if (self->name_index == NAME_KROKER && other->client)
	{

		if ((mem->memory_type == MEMORY_TYPE_ENEMY) )//&& !(other->episode_flags & EP_Steeltown_KROKER_BOLT) /*&& !other->client->pers.weapon*/)
		{	// give them a chance to make friends if they holster
			self->enemy = NULL;

			// make them a neutral instead of enemy
			AI_RemoveFromMemory( self, mem );
			AI_AddToMemory( self, mem, MEMORY_TYPE_NEUTRAL );
			mem->flags &= ~MEMORY_HOSTILE_ENEMY;

			mem->flags |= MEMORY_ASSHOLE;
			return true;
		}
		else if (other->episode_flags & EP_Steeltown_KROKER_BOLT)
			return false;
		else
			return true;
	}
	
	return false;
}

qboolean EP_Steeltown_CastUse (edict_t *self, edict_t *other, edict_t *activator)
{
	return false;
}

qboolean EP_Steeltown_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{
	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
	
	switch (saywhat)
	{
	
	case say_neutral:

		if ((self->name_index == NAME_BAMBI) && other->client)
		{
			return (ProcessSteeltownBambi (self, other, mem));
		}

		if	((self->name_index == NAME_MOMO)
			 &&	(other->client))
		{
			return (ProcessSteeltownMomo (self, other));
		}

		if (self->name_index == NAME_PETE && other->client)
		{
			Voice_Random (self, other, steeltown_pete, 4);
			return true;
		}

		if (self->name_index == NAME_MATHEW && other->client)
		{
			if (!(other->episode_flags & EP_Steeltown_MATHEW_CLUE1))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MATHEW_CLUE1);
				EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MATHEW_LINE1);
				Voice_Specific (self, other, steeltown_mathew, 0);
			}
			else if (!(other->episode_flags & EP_Steeltown_MATHEW_CLUE2))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MATHEW_CLUE2);
				Voice_Specific (self, other, steeltown_mathew, 1);
			}
			else 
			{
				Voice_Random (self, other, &steeltown_mathew[2], 4);
				other->episode_flags = other->client->pers.episode_flags &= ~EP_Steeltown_MATHEW_CLUE1;
				other->episode_flags = other->client->pers.episode_flags &= ~EP_Steeltown_MATHEW_CLUE2;
			}
			
			return true;
		}

		if (self->name_index == NAME_BRITTANY && other->client)
		{
			if (!(other->episode_flags & EP_Steeltown_BRITTANY_CLUE1))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_BRITTANY_CLUE1);
				EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_BRITTANY_LINE1);
				Voice_Specific (self, other, steeltown_brittany, 0);
			}
			else 
			{
				Voice_Random (self, other, &steeltown_brittany[4], 3);
				other->episode_flags = other->client->pers.episode_flags &= ~EP_Steeltown_BRITTANY_CLUE1;
			}
			return true;
		}
		
		if (self->name_index == NAME_KROKER && other->client)
		{
			return (ProcessKroker (self, other, mem));
		}

		if ((self->name_index >= NAME_KID_1 && self->name_index <= NAME_KID_8) && other->client)
		{
			return (ProcessKids (self, other, mem));
		}

		return false;
		break;
	
	case say_hostile:

		if ((self->name_index == NAME_BAMBI) && other->client)
		{
			return (ProcessSteeltownBambi (self, other, mem));
		}

		if (self->name_index == NAME_MOMO && other->client)
		{
			return (ProcessSteeltownMomo (self, other));
		}

		if (self->name_index == NAME_MATHEW && other->client)
		{
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
			
				Voice_Random (self, other, &steeltown_mathew[2], 4);

				return true;
			}
			else
			{
				// just do a random curse at the player
				Voice_Random (self, other, &steeltown_mathew[6], 3);	
				return true;
			}
		
			return true;
		}

		if (self->name_index == NAME_BRITTANY && other->client)
		{
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
			
				Voice_Random (self, other, &steeltown_brittany[4], 3);

				return true;
			}
			else
			{
				// just do a random curse at the player
				Voice_Random (self, other, &steeltown_brittany[1], 3);	
				return true;
			}
		
			return true;
		}

		if (self->name_index == NAME_PETE && other->client)
		{
			Voice_Random (self, other, &steeltown_pete[4], 4);
			return true;
		}
		
		if (self->name_index == NAME_KROKER && other->client)
		{
			return (ProcessKroker (self, other, mem));
		}
				
		if ((self->name_index >= NAME_KID_1 && self->name_index <= NAME_KID_8) && other->client)
		{
			return (ProcessKids (self, other, mem));
		}

		return false;
		break;
	}


	return false;
}

void EP_Steeltown_ItemPickup ( edict_t *self, edict_t *other )
{

}

// EP_Steeltown_Script

void EP_Steeltown_Script( edict_t *ent, char *scriptname )
{

}

extern mmove_t  runt_move_walk_dokey;
extern mmove_t	runt_move_crch_dokey;

qboolean ProcessSteeltownBambi (edict_t *self, edict_t *player, cast_memory_t *mem)
{
	if (mem->flags & MEMORY_ASSHOLE)
	{
		if (player->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
		{
			mem->flags &= ~MEMORY_ASSHOLE;
			
			if ((player->episode_flags & EP_Steeltown_DAVID_DEAD) || (player->episode_flags & EP_Steeltown_DAVID_SAY1))
				Voice_Random (self, player, &steeltown_bambi[12], 3);
			else if (player->episode_flags & EP_Steeltown_KIDS_CLUE)
				Voice_Random (self, player, &steeltown_bambi[1], 3);
			
			return true;
		}
		else
		{
			// just do a random curse at the player
			Voice_Random (self, player, &steeltown_bambi[7], 3);	
			return true;
		}
	}
	else
	{
		if (player->episode_flags & EP_Steeltown_BAMBI_DONE)
		{
			Voice_Random (self, player, &steeltown_bambi[12], 3);
			return true;
		}
		else if (player->episode_flags & EP_Steeltown_DAVID_DEAD)
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_BAMBI_DONE);

			Voice_Specific (self, player, steeltown_bambi, 11);
			
			{
				int     index;
				gitem_t *item;
								  
				item = FindItem ("Office_Key");
				index = ITEM_INDEX (item);
				player->client->pers.inventory[ index ] = 1;
					// show icon and name on status bar
				player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
				player->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
				player->client->pickup_msg_time = level.time + 5.5;
			}
			return true;
		}
		else if (player->episode_flags & EP_Steeltown_DAVID_SAY3)
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_BAMBI_DONE);

			Voice_Specific (self, player, steeltown_bambi, 10);
			
			{
				int     index;
				gitem_t *item;
								  
				item = FindItem ("Office_Key");
				index = ITEM_INDEX (item);
				player->client->pers.inventory[ index ] = 1;
					// show icon and name on status bar
				player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
				player->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
				player->client->pickup_msg_time = level.time + 5.5;
			}
			return true;
		}
		else if (!(player->episode_flags & EP_Steeltown_BAMBI_LINE1))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_BAMBI_LINE1);
			Voice_Specific (self, player, steeltown_bambi, 0);
		}
		else
		{
			// go find my brother
			Voice_Random (self, player, &steeltown_bambi[4], 3);
		}
		
		return true;
	}
			
	
}

qboolean ProcessKids (edict_t *self, edict_t *player, cast_memory_t *mem)
{
	qboolean runaway = false;

	if (mem->flags & MEMORY_ASSHOLE)
	{
		// RUN AWAY
		runaway = true;
		Voice_Random (self, player, &steeltown_kids[8] , 4);

	}
	else if (!(self->episode_flags & EP_Steeltown_KIDS_CLUE))
	{
		
		if (!(player->episode_flags & EP_Steeltown_KIDS_CLUE1))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_KIDS_CLUE1);
			Voice_Specific (self, player, steeltown_kids, 6);
		}
		else if (!(player->episode_flags & EP_Steeltown_KIDS_CLUE2))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_KIDS_CLUE2);
			Voice_Specific (self, player, steeltown_kids, 3);
		}
		else
			Voice_Random (self, player, steeltown_kids, 8);

		return true;
	}
	else
		runaway = true;
		//

	if (runaway)
	{
		{

			#define MAXCHOICES	8
	
			edict_t	*ent = NULL;
			int		num_choices = 0;
			edict_t	*choice[MAXCHOICES];
			int		rval;
			float	dist[MAXCHOICES];
			
			while(1)
			{
				ent = G_Find (ent, FOFS(classname), "misc_steeltown_afraid");
				if (!ent)
					break;
				if ((dist[num_choices] = VectorDistance( ent->s.origin, self->s.origin )) > 384)
					choice[num_choices++] = ent;
				if (num_choices == MAXCHOICES)
					break;
			}

			if (!num_choices)
			{
				// gi.dprintf( "AI: can't find a misc_skidrow_afraid\n");
				mem->flags &= ~MEMORY_AFRAID;
			}
			else if (self->groundentity)
			{
				
				// gi.dprintf( "AI: Going to misc_skidrow_afraid\n");
				// rval = rand() % num_choices;
				{
					int i;
					float olddist = 0;

					for (i=0; i<num_choices; i++)
					{
						if (dist[i] > olddist)
						{
							rval = i;
							olddist = dist[i];
						}
					}
				}

				if (!(choice[rval]->cast_info.aiflags & AI_GOAL_RUN))
					Voice_Specific( self, player, specific, 25 );

				choice[rval]->cast_info.aiflags |= AI_GOAL_RUN;
				self->cast_info.aiflags |= AI_RUN_LIKE_HELL;

				self->goal_ent = choice[rval];
				self->cast_info.aiflags |= AI_GOAL_IGNOREENEMY;

				self->cast_info.currentmove = self->cast_info.move_run;
			}
		}
		return true;
	}
	return true;
}

qboolean ProcessKroker (edict_t *self, edict_t *player, cast_memory_t *mem)
{
	if (mem->flags & MEMORY_ASSHOLE)
	{
		
		edict_t *dest = NULL;
		edict_t	*ent = NULL;

		// if ((player->episode_flags & EP_Steeltown_KROKER_SAY))
		if ((player->episode_flags & EP_Steeltown_KROKER_BOLT))
		{
			AI_MakeEnemy(self, player, 0);			
			return false;
		}
		// dont shoot let me open the safe
		Voice_Specific (self, player, steeltown_kroker, 0);
		
		ent = G_Find (NULL, FOFS (targetname), "safe_door"); 

		if (ent)
		{
			if (ent->key == -1)
			{
				dest = G_Find (NULL, FOFS (targetname), ent->target); // ai_safespot
				self->goal_ent = dest; 
				self->cast_info.currentmove = &runt_move_walk_dokey; // this should be called dokey

				// make the guns invisible
				self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
				self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
			}
			else
			{
				 // the safe is open
				 // player must have met up with him again just make him hostile
				AI_MakeEnemy(self, player, 0);
			}
		}
		else
		{
			gi.dprintf ("FIXME: failed to find safe_door\n");
		}
	}
	else
	{
		if (!(player->episode_flags & EP_Steeltown_KROKER_SAY))
		{
			Voice_Specific (self, player, steeltown_kroker, 1);
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_KROKER_SAY);
			return true;
		}
		else
		{
			AI_MakeEnemy(self, player, 0);
			return true;
		}
	}

	return false;
}

void Resp_SteeltownMomo_GotMoney ( edict_t *self, edict_t *other, response_t response )
{
	cast_memory_t	*mem;
		
	if (self->episode_flags & EP_Steeltown_MOMO_TOOK_MONEY)
		return;

	mem = level.global_cast_memory[ other->character_index ][ self->character_index ];

	if (response == resp_yes)
	{
		Voice_Player_Specific(self, TT_YES);
		Voice_Random (self, other, player_money_yes, NUM_PLAYER_MONEY_YES);		// yes
	}
	else if (response == resp_no)
	{
		Voice_Player_Specific (self, TT_NO);
		Voice_Random (self, other, player_money_no, NUM_PLAYER_MONEY_NO);		// no
	}

	self->response_ent = other;
	self->last_response_time = level.time;
	self->last_response = response;
}

			
// generic process for hostile or neutral momo			
qboolean ProcessSteeltownMomo (edict_t *self, edict_t *other)			
{
	
	cast_memory_t	*mem;	

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];

	if (mem->flags & MEMORY_LASTWARNING)
	{
		Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (other->episode_flags & EP_Steeltown_MOMO_TOOK_MONEY)
	{
		// Ridah, 5-8-99, we've already taken their money, so say one of the following..

		if (!(mem->flags & MEMORY_ASSHOLE))
			Voice_Random ( self, other, &momo_specific[12], 2);		// so what's it gonna be... in or out?
		else	// they've cussed us, don't act all happy to see them
			Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (!(other->episode_flags & EP_Steeltown_MOMO_FIRST_TIME))
	{
		
		Voice_Specific (self, other, momo_specific, 18); // welcome.wav

		EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MOMO_FIRST_TIME);

		return true;
	}

	// Ridah, 5-8-99, I changed this so it clears this flag in EP_CastSight() if Momo sees you after not having seen you for a while
	if (!(other->episode_flags & EP_Steeltown_MOMO_ASKED_MONEY))
	{
		// note to Rafael: you can use "inc" for anything.. usually used to count events
		if (!mem->inc)
		{
			if (!( mem->flags & MEMORY_ASSHOLE))
			{
				Voice_Random (self, other, &momo_specific[1], 3); // 10 dollar cover charge
				mem->inc = 1;
			}
			else
			{
				Voice_Specific (self, other, momo_specific, 5);		// now it's 20 bucks!
				mem->inc = 2;
			}
		}
		else
		{
			Voice_Specific (self, other, momo_specific, 9); // your back
		}

		EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MOMO_ASKED_MONEY);

		mem->response = Resp_SteeltownMomo_GotMoney;
		return true;
	}

	// have they responded yet?
	else if (	(other->response_ent == self)
			 &&	(other->last_response_time > (level.time - 5)))
	{
				
		if (other->last_response == resp_yes)
		{	
			edict_t	*door = NULL;
			int	cost;

			if ( mem->flags	& MEMORY_ASSHOLE)
			{
				if (mem->inc < 3)
					cost = 20;
				else
					cost = 30;
			}
			else
			{
				cost = 10;
			}
				
			// have we really have money to give?
			if (other->client->pers.currentcash >= cost)
			{
				other->client->pers.currentcash -= cost;
				self->currentcash += cost;
				
				EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MOMO_TOOK_MONEY);

				// TBD: at this point need to have momo walk away to a path corner cast

				Voice_Specific( self, other, &momo_specific[0], 10 );	// go on in


				// JOSEPH 9-MAR-99
				// in case there's more than one door
				{	// unlock the door for player
					// Find target door
					edict_t	*e;
					int		i;
					
					for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
					{
						if ((e->targetname) && (!strcmp(e->targetname, "bardoor_st")))
						{
							// Unlock target door
							if (e->key == -1)
							{
								e->key = 0;	
								e->targetname = NULL;							
							}
						}
					}
					
					
					EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MOMO_TOOK_MONEY);
				}
				// END JOSEPH

			}
			else
			{
				// don't have money to give
				Voice_Random( self, other, &momo_specific[7], 2 );	// see me later when you got the money
			}
		}
		else	// they said no
		{
			Voice_Random( self, other, &momo_specific[13], 3 );
		}

		other->last_response_time = 0;	// so we don't process this response again

		mem->response = NULL;
		other->response_ent = NULL;

		return true;
	}

	else 
	{

		if (mem->flags & MEMORY_ASSHOLE)
		{
			if (!(mem->flags & MEMORY_UPSET))
			{
				mem->flags |= MEMORY_UPSET;

				if (mem->inc < 3)
				{
					Voice_Specific (self, other, momo_specific, 5);
				}
				else	// 30 bucks for you now!
				{
					Voice_Specific (self, other, momo_specific, 6);
				}
			}
			else
			{
				Voice_Random (self, other, &momo_specific[12], 4); 

				// This needs to be here, or Momo will never take the money when mad
				if (momo_specific[12].last_played == level.time)
				{	// we just asked them if they wanna come in, so let them respond
					mem->response = Resp_SteeltownMomo_GotMoney;
				}

			}
		}
		else
		{
			Voice_Random (self, other, &momo_specific[12], 5); 

			if (momo_specific[12].last_played == level.time)
			{	// we just asked them if they wanna come in, so let them respond
				mem->response = Resp_SteeltownMomo_GotMoney;
			}
		}

	}
			
	return true;
}



int	EP_Steeltown_HiredGuysFlags (edict_t *player, edict_t *self)
{
	if (self->name_index == NAME_DAVID)
	{
		if (player->episode_flags & EP_Steeltown_DAVID_SAY3)
		{
			if (!(player->episode_flags & EP_Steeltown_DAVID_HIRED))
			{
				cast_memory_t *cast_memory;

				cast_memory = level.global_cast_memory[self->character_index][player->character_index];

				cast_memory->flags |= MEMORY_HIRED;
				cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
				cast_memory->flags |= MEMORY_HIRE_ASK;

				self->leader = player;
				self->cast_info.aiflags |= AI_NOWALK_FACE;
				self->order = ORDER_FOLLOWME;
				self->order_timestamp = level.time;

				player->client->pers.friends++;

				self->spawnflags &= ~2;

				self->s.model_parts[PART_GUN].invisible_objects = 0;
				self->s.model_parts[PART_GUN2].invisible_objects = 0;

				EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_DAVID_HIRED);

			}

			return (1);
		}
		
		if (!(player->episode_flags & EP_Steeltown_DAVID_SAY1))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_DAVID_SAY1);
			Voice_Specific (self, player, steeltown_david, 0);

			return (0);
		}
		else if (!(player->episode_flags & EP_Steeltown_DAVID_SAY2))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_DAVID_SAY2);
			Voice_Specific (self, player, steeltown_david, 1);

			return (0);
		}
		else if (!(player->episode_flags & EP_Steeltown_DAVID_SAY3))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_DAVID_SAY3);
			Voice_Specific (self, player, steeltown_david, 2);

			return (0);
		}
	}

	return (1);	
}

void EP_SteeltownFlags (edict_t *self)
{
	if (self->name_index == NAME_MOMO)
	{
		self->cast_info.aiflags |= AI_IMMORTAL;
		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
	}

	if (self->name_index == NAME_DAVID)
	{
		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
	}

	// David should have his weapons invisible till he gets hired
}

void EP_Steeltown_CheckMomo (edict_t *ent, cast_memory_t	*mem)
{
	if (ent->episode_flags & EP_Steeltown_MOMO_ASKED_MONEY)
	 	mem->inc++;
				
}

qboolean EP_Steeltown_DoKey (edict_t *self, edict_t *other)
{
	if (other->name_index == NAME_DAVID && self->client)
		return true;
	else
		return false;
}

extern mmove_t	punk_move_walk_dokey;
extern mmove_t	punk_move_crch_dokey;

extern mmove_t  runt_move_walk_dokey;
extern mmove_t	runt_move_crch_dokey;

extern mmove_t	bitch_move_walk_dokey;

extern mmove_t	thug_move_walk_dokey;
extern mmove_t	thug_move_crch_dokey;

void EP_Steeltown_Check_DoKey (edict_t *self, edict_t *ent)
{
	edict_t *David;
	edict_t *dest;
	vec3_t	vec;
	float	dist;

	David = EP_GetCharacter (NAME_DAVID);

	if (!ent)
		return;

	if (!(ent->targetname))
	{
		if (David)
		{
			self->cast_info.aiflags &= ~AI_DOKEY;
			David->cast_info.aiflags &= ~AI_DOKEY;
		}
		return;
	}

	

	// its a safe and its locked
	if (!strcmp (ent->targetname, "david_door") && ent->key == -1)
	{
		dest = G_Find (NULL, FOFS (targetname), ent->target); // ai_safespot

		if (David && David->cast_info.aiflags & AI_DOKEY)
		{
			if (!(David->goal_ent) || !(David->enemy))
			{
				if (visible (David, dest))
				{
					VectorSubtract (David->s.origin, dest->s.origin, vec);
					dist = VectorLength (vec);
					
					if (dist < 384)
					{
						David->goal_ent = dest; 
				
						self->cast_info.aiflags &= ~AI_DOKEY;
						David->cast_info.aiflags &= ~AI_DOKEY;

						David->cast_info.currentmove = &punk_move_walk_dokey; // this should be called dokey

						// make the guns invisible
						//David->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
						//David->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);

					}
				}
			}
		}
		else 
			gi.dprintf ("there is no one to open the safe\n");
	}
	

	return;
}


void EP_Steeltown_ReachedDoKey (edict_t *self)
{
	vec3_t	vec;
	float	dist;
	edict_t		*dest;

	VectorSubtract (self->s.origin, self->goal_ent->s.origin, vec);
	dist = VectorLength (vec);
	
	if (dist < 32)
	{
		if (self->name_index == NAME_KROKER)
		{
			self->cast_info.currentmove = &runt_move_crch_dokey;
		}
		else if (self->name_index == NAME_DAVID)
		{
			self->goal_ent = NULL;

			dest = G_Find (NULL, FOFS (targetname), "trigger_david"); 
			if (dest->use)
					dest->use (dest, self, self);

			self->cast_info.currentmove = &punk_move_crch_dokey;
		}
	}
		
}

void EP_Steeltown_EndDoKey (edict_t *self)
{
	edict_t		*dest = NULL;
	edict_t		*ent = NULL;
	edict_t		*player;

	player = &g_edicts[1];

	if (self->name_index == NAME_KROKER)
	{
		self->cast_info.currentmove = self->cast_info.move_run;

		dest = G_Find (NULL, FOFS (targetname), "trigger_kroker"); 
			if (dest->use)
					dest->use (dest, self, self);

		{
			// bolt outta here
			ent = G_Find (ent, FOFS(classname), "misc_kroker_afraid");

			if (ent)
			{
				self->goal_ent = ent; 
				ent->cast_info.aiflags |= AI_GOAL_RUN;
				self->cast_info.aiflags |= AI_RUN_LIKE_HELL;
				self->cast_info.aiflags |= AI_GOAL_IGNOREENEMY;
				self->cast_info.currentmove = self->cast_info.move_run;

				EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_KROKER_BOLT);
			}
			else
				gi.dprintf ("didn't find misc_kroker_afraid\n");
		}
	}

	else if (self->name_index == NAME_DAVID)	
	{
		self->cast_info.currentmove = self->cast_info.move_run;
		
		// gi.dprintf ("FIXME SOUND TODO %s: there you go easy money!\n", self->name);
		// Voice_Specific (self, player, hiredguy_ask, 17);

		
		// he's done so show the guns
		//self->s.model_parts[PART_GUN].invisible_objects = 0;
		//self->s.model_parts[PART_GUN2].invisible_objects = 0;

	}	

}

void EP_Steeltown_HiredGuysRegisterFlags (edict_t *ent, edict_t *other)
{
	return;
}

void EP_Steeltown_SpecialEventDeath (edict_t *self)
{
	edict_t *player;

	player = &g_edicts[1];

	if (self->name_index == NAME_DAVID && strstr (level.mapname, "steel3"))
	{
		EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_DAVID_DEAD);
		
		if (player->episode_flags & EP_Steeltown_BAMBI_LINE1)
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_DAVID_DEAD_A);
		else
			EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_DAVID_DEAD_B);

		gi.sound(player, CHAN_VOICE, gi.soundindex("scenaric/daviddead.wav"), 1, ATTN_NORM, 0);
		
	}
	
}

/*QUAKED misc_steeltown_afraid (.5 .5 1) (-16 -16 -24) (16 16 48)
used by kids in the mill to run away
*/

void SP_misc_steeltown_afraid (edict_t *self)
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

	self->cast_info.aiflags |= AI_RUN_LIKE_HELL;
	
	AI_Ent_droptofloor( self );
}

/*QUAKED misc_kroker_afraid (.5 .5 1) (-16 -16 -24) (16 16 48)
safe spot for kroker
*/

void SP_misc_kroker_afraid (edict_t *self)
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

	self->cast_info.aiflags |= AI_RUN_LIKE_HELL;
	
	AI_Ent_droptofloor( self );
}

/*QUAKED ai_moker_notinoffice (.5 .5 1) ?
This will set the EP_Steeltown_MOKER_NOTINOFFICE flag
*/

void ai_moker_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!(other->client))
		return;

	if (!(other->episode_flags & EP_Steeltown_MOKER_NOTINOFFICE))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_Steeltown_MOKER_NOTINOFFICE);
		gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/mokersnothere.wav"), 1, ATTN_NORM, 0);
	}
	// FIXME
	// we need to play a wav file
	
}

void SP_moker_notinoffice ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_moker_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}


#include "ep_log.h"

extern int	the_log_page;

void EP_Steeltown_Player_Log (edict_t *self, int page)
{
	int len; 
	int i;
	int	cnt = 0;
	int	select = 0;

	len = 0;

	Com_sprintf (game.helpmessage1, sizeof(game.helpmessage1), "");
	Com_sprintf (game.helpmessage2, sizeof(game.helpmessage2), "");
	
	the_log_page += page;
	
	if (the_log_page < 0)
		the_log_page = 0;
	else if (the_log_page >= NUM_ST_PLAYER_LOG)
		the_log_page = 0;

	for (i=1; i<NUM_ST_PLAYER_LOG; i++)
	{
		if (self->client->pers.episode_flags & ep_st_player_log[i].ep_flag)
			cnt++;

		if (cnt == the_log_page)
		{
			select = i;
			break;
		}
	}	
	
	if (!page || !the_log_page)
	for (i=0; i<NUM_ST_PLAYER_LOG; i++)
	{
		if (ep_st_player_log[i].new_clue == true)
		{
			select = i;
			break;
		}
	}

	if (cnt == 0)
	{
		the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_st_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcpy (game.helpmessage2, ep_st_player_log[0].ep_text);
	}
	else
	{
		if (select == 0)
			the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_st_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcat (game.helpmessage2, ep_st_player_log[select].ep_text);
		if (page)
			gi.sound(self, CHAN_VOICE, gi.soundindex("world/pageturn.wav"), 1, ATTN_NONE, 0);
	}
	

}

qboolean EP_Steeltown_Flash_Newflag (edict_t *self, int ep_flag)
{
	int i;
	qboolean gotone = false;

	for (i=0; i<NUM_ST_PLAYER_LOG; i++)
	{
		if (ep_st_player_log[i].ep_flag == ep_flag)
		{
			ep_st_player_log[i].new_clue = true;
			gotone = true;
		}
		else
			ep_st_player_log[i].new_clue = false;
	}

	return (gotone);
}
