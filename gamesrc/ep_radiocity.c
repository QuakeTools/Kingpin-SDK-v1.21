// RADIO CITY
#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

qboolean ProcessRCMomo (edict_t *self, edict_t *other);

qboolean EP_RC_CastSight ( edict_t *self, edict_t *other, cast_memory_t *mem )
{
	if (self->name_index == NAME_MOMO && other->client)
	{
		if (mem->timestamp < (level.time - 8))
		{	// haven't seen them for a while
			other->episode_flags &= ~EP_RC_MOMO_ASKED_MONEY;
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

	if (self->name_index == NAME_SCALPER && other->client) 
	{
			
		other->episode_flags &= ~EP_RC_SCALPER_ASKED_MONEY;
		
		mem->flags &= ~MEMORY_ASSHOLE;
		
		return true;
	}

	if (self->name_index == NAME_LOLA && other->client)
	{
		if ((mem->memory_type == MEMORY_TYPE_ENEMY) && !(other->client->pers.weapon))
		{	// give them a chance to make friends if they holster
			self->enemy = NULL;

			// make them a neutral instead of enemy
			AI_RemoveFromMemory( self, mem );
			AI_AddToMemory( self, mem, MEMORY_TYPE_NEUTRAL );
			mem->flags &= ~MEMORY_HOSTILE_ENEMY;
		}

		return false;
	}

	return false;
}

qboolean EP_RC_CastUse (edict_t *self, edict_t *other, edict_t *activator)
{
	return false;
}

qboolean EP_RC_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{
	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
	
	switch (saywhat)
	{
	
	case say_neutral:

		if	((self->name_index == NAME_MOMO)
			 &&	(other->client))
		{
			return (ProcessRCMomo (self, other));
		}

		if (self->name_index == NAME_SCALPER && other->client)
		{

			if(other->episode_flags & EP_RC_SCALPER_GAVE_MONEY)
			{
				if (!(other->episode_flags & EP_RC_SCALPER_RANDOM))
				{
					EP_Skidrow_Register_EPFLAG (other, EP_RC_SCALPER_RANDOM);
					Voice_Random (self, other, &rc_scalper[6], 3);
				}
				else
				{
					Voice_Specific (self, other, rc_scalper, 3);
					other->episode_flags = other->client->pers.episode_flags &= ~EP_RC_SCALPER_RANDOM;
				}
				return true;
			}

			if (!(other->episode_flags & EP_RC_SCALPER_LINE1))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_RC_SCALPER_LINE1);
				Voice_Random (self, other, rc_scalper, 2);
				return true;
			}

			/*
			if (other->episode_flags & EP_RC_SCALPER_ASKED_MONEY)
			{
				Voice_Random (self, other, &rc_scalper[6], 3);
				return true;
			}
			*/

			if (!(other->episode_flags & EP_RC_TALKED_TO_SCALPER) && !(self->episode_flags & EP_RC_SCALPER_GAVE_MONEY))
			{
				mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
				
				Voice_Random (self, other, rc_scalper, 2);
				EP_Skidrow_Register_EPFLAG (other, EP_RC_TALKED_TO_SCALPER);
				mem->response = Resp_Scalper_GotTicket;

				return true;
			}
			else if (!(other->episode_flags & EP_RC_SCALPER_ASKED_MONEY) && !(self->episode_flags & EP_RC_SCALPER_GAVE_MONEY))
			{
				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
				{
					Voice_Random (self, other, rc_scalper, 2);
						
					EP_Skidrow_Register_EPFLAG (other, EP_RC_SCALPER_ASKED_MONEY);
					EP_Skidrow_Register_EPFLAG (other, EP_RC_TALKED_TO_SCALPER);
					mem->response = Resp_Scalper_GotTicket;

					return true;
				}
			}

			// have they responded yet?
			else if (	(other->response_ent == self)
					 &&	(other->last_response_time > (level.time - 5)))
			{
					
				if (other->last_response == resp_yes)
				{	
					int     index;
					gitem_t *item;

					Voice_Random ( self, other, &rc_scalper[2], 2 );
					// gi.dprintf ("Scalper: here's your ticket \n");

					item = FindItem ("Ticket");
					index = ITEM_INDEX (item);
					other->client->pers.inventory[ index ] = 1;
					// show icon and name on status bar
					other->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
					other->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
					other->client->pickup_msg_time = level.time + 5.5;
						
					EP_Skidrow_Register_EPFLAG (other, EP_RC_SCALPER_GAVE_MONEY);
					EP_Skidrow_Register_EPFLAG (other, EP_RC_SCALPER_NOTEPAD);
				}
				else
				{
					Voice_Random (self, other, &rc_scalper[4], 2);
					mem->response = Resp_Scalper_GotTicket;
				}

				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
					mem->response = NULL;

				other->response_ent = NULL;
				return true;
			}

			else if (	(specific[0].last_played < (level.time - 3))
					 &&	(specific[1].last_played < (level.time - 4)))
			{
				Voice_Random ( self, other, rc_scalper, 2 );

				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
					mem->response = Resp_Scalper_GotTicket;
					
				return true;
			}

			else
			{
				if (!(other->episode_flags & EP_RC_SCALPER_NOTEPAD))
				{
					EP_Skidrow_Register_EPFLAG (other, EP_RC_SCALPER_NOTEPAD);
					Voice_Specific ( self, other, rc_scalper, 6);
				}
				else
					Voice_Random ( self, other, &rc_scalper[6], 3);
				return true;
			}
			
			return true;
		}
		

		if (self->name_index == NAME_LOLA && other->client)
		{
			if (!(other->episode_flags & EP_RC_LOLA_CLUE1))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_RC_LOLA_CLUE1);
				EP_Skidrow_Register_EPFLAG (other, EP_RC_LOLA_NOTEBOOK);
				Voice_Specific (self, other, rc_lola, 0);
			}
			else 
			{
				Voice_Random (self, other, &rc_lola[1], 3);
				other->episode_flags = other->client->pers.episode_flags &= ~EP_RC_LOLA_CLUE1;
			}
			return true;
		}

		return false;
		break;
	
	case say_hostile:

		if	((self->name_index == NAME_MOMO)
			 &&	(other->client))
		{
			return (ProcessRCMomo (self, other));
		}
		
		if	(self->name_index == NAME_SCALPER && (other->client))
		{

			if(other->episode_flags & EP_RC_SCALPER_GAVE_MONEY)
			{
				if (!(other->episode_flags & EP_RC_SCALPER_RANDOM))
				{
					EP_Skidrow_Register_EPFLAG (other, EP_RC_SCALPER_RANDOM);
					Voice_Random (self, other, &rc_scalper[6], 3);
				}
				else
				{
					Voice_Specific (self, other, rc_scalper, 3);
					other->episode_flags = other->client->pers.episode_flags &= ~EP_RC_SCALPER_RANDOM;
				}
				return true;
			}

			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
				
				Voice_Random (self, other, &rc_scalper[6], 3);
				
				return true;
			}
		

			else
			{
				
				Voice_Random (self, other, &rc_scalper[9], 4);
				
				return true;
			}

		}

		if (self->name_index == NAME_LOLA && other->client)
		{
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
			
				// Voice_Random (self, other, &rc_lola[4], 3);
				if (!(other->episode_flags & EP_RC_LOLA_CLUE1))
				{
					EP_Skidrow_Register_EPFLAG (other, EP_RC_LOLA_CLUE1);
					EP_Skidrow_Register_EPFLAG (other, EP_RC_LOLA_NOTEBOOK);
					Voice_Specific (self, other, rc_lola, 0);
				}
				else 
				{
					Voice_Random (self, other, &rc_lola[1], 3);
					other->episode_flags = other->client->pers.episode_flags &= ~EP_RC_LOLA_CLUE1;
				}

				return true;
			}
			else
			{
				// just do a random curse at the player
				Voice_Random (self, other, &rc_lola[4], 3);	
				return true;
			}
		
			return true;
		}
		return false;
		break;
	}


	return false;
}

void EP_RC_ItemPickup ( edict_t *self, edict_t *other )
{

}

// EP_RC_Script

void EP_RC_Script( edict_t *ent, char *scriptname )
{

}

void Resp_Scalper_GotTicket ( edict_t *self, edict_t *other, response_t response )
{

	if (response == resp_yes)
	{
		Voice_Player_Specific(self, TT_YES);
		
		if (!(self->episode_flags & EP_RC_SCALPER_GAVE_MONEY))
		{
			if (self->client->pers.currentcash >= 50)
			{
				self->client->pers.currentcash-=50;
				Voice_Specific( self, other, player_50bucks, 0 );

				other->episode_flags |= EP_RC_SCALPER_GAVE_MONEY;
			}
			else
			{
				// gi.cprintf( self, PRINT_HIGH, "FIXME: you don't have 50 bucks.\n" );
				Voice_Specific( self, other, player_50bucks, 1 );
				response = resp_no;
			}
		}
		else
		{
			// gi.cprintf( self, PRINT_HIGH, "FIXME: you don't have 50 bucks.\n" );
			Voice_Specific( self, other, player_50bucks, 1 );
			response = resp_no;
		}
	}
	else if (response == resp_no)
	{
		// gi.cprintf( self, PRINT_HIGH, "FIXME: you don't have 50 bucks.\n" );
		Voice_Specific( self, other, player_50bucks, 1 );
		Voice_Player_Specific(self, TT_NO);
	}

	other->cast_info.talk_ent = self;

	self->response_ent = other;
	self->last_response_time = level.time;
	self->last_response = response;

}


void Resp_RCMomo_GotMoney ( edict_t *self, edict_t *other, response_t response )
{
	cast_memory_t	*mem;
		
	if (self->episode_flags & EP_RC_MOMO_TOOK_MONEY)
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
qboolean ProcessRCMomo (edict_t *self, edict_t *other)			
{
	
	cast_memory_t	*mem;	

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];

	if (mem->flags & MEMORY_LASTWARNING)
	{
		Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (other->episode_flags & EP_RC_MOMO_TOOK_MONEY)
	{
		// Ridah, 5-8-99, we've already taken their money, so say one of the following..

		if (!(mem->flags & MEMORY_ASSHOLE))
			Voice_Random ( self, other, &momo_specific[12], 2);		// so what's it gonna be... in or out?
		else	// they've cussed us, don't act all happy to see them
			Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (!(other->episode_flags & EP_RC_MOMO_FIRST_TIME))
	{
		
		Voice_Specific (self, other, momo_specific, 20); // welcome.wav

		EP_Skidrow_Register_EPFLAG (other, EP_RC_MOMO_FIRST_TIME);

		return true;
	}

	// Ridah, 5-8-99, I changed this so it clears this flag in EP_CastSight() if Momo sees you after not having seen you for a while
	if (!(other->episode_flags & EP_RC_MOMO_ASKED_MONEY))
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

		EP_Skidrow_Register_EPFLAG (other, EP_RC_MOMO_ASKED_MONEY);

		mem->response = Resp_RCMomo_GotMoney;
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
				
				EP_Skidrow_Register_EPFLAG (other, EP_RC_MOMO_TOOK_MONEY);

				// TBD: at this point need to have momo walk away to a path corner cast

				Voice_Specific( self, other, momo_specific, 10 );	// go on in


				// JOSEPH 9-MAR-99
				// in case there's more than one door
				{	// unlock the door for player
					// Find target door
					edict_t	*e;
					int		i;
					
					for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
					{
						if ((e->targetname) && (!strcmp(e->targetname, "bardoor_rc")))
						{
							// Unlock target door
							if (e->key == -1)
							{
								e->key = 0;	
								e->targetname = NULL;							
							}
						}
					}
					
					
					EP_Skidrow_Register_EPFLAG (other, EP_RC_MOMO_TOOK_MONEY);
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
					mem->response = Resp_RCMomo_GotMoney;
				}

			}
		}
		else
		{
			Voice_Random (self, other, &momo_specific[12], 5); 

			if (momo_specific[12].last_played == level.time)
			{	// we just asked them if they wanna come in, so let them respond
				mem->response = Resp_RCMomo_GotMoney;
			}
		}

	}
			
	return true;
}


int FindMarxBrothers (edict_t *player)
{
	if (player->episode_flags & EP_RC_GROUCHO_DEAD
		&& player->episode_flags & EP_RC_HARPO_DEAD
		&& player->episode_flags & EP_RC_CHICO_DEAD)
		return (1);

	return (0);

}


int	EP_RC_HiredGuysFlags (edict_t *player, edict_t *self)
{
	int marx_brothers_defeated;
	cast_memory_t *cast_memory;

	marx_brothers_defeated = FindMarxBrothers (player); 

	if (self->name_index == NAME_BUTCH)
	{		
		
		if (player->episode_flags & EP_RC_JOKERS_HIRED)
			return (1);

		if (player->episode_flags & EP_RC_PAY_500)
		{
			if (player->client->pers.currentcash >= 500)
			{
				player->client->pers.currentcash-=500;
				EP_Skidrow_Register_EPFLAG (player, EP_RC_JOKERS_HIRED);
				
				{
					// auto hire butch and patrick
					edict_t *Patrick;

					Patrick = EP_GetCharacter (NAME_PATRICK);

					if (Patrick)
					{
						cast_memory = level.global_cast_memory[Patrick->character_index][player->character_index];

						cast_memory->flags |= MEMORY_HIRED;
						cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						cast_memory->flags |= MEMORY_HIRE_ASK;

						Patrick->leader = player;
						Patrick->cast_info.aiflags |= AI_NOWALK_FACE;
						Patrick->order = ORDER_FOLLOWME;
						Patrick->order_timestamp = level.time;
						Patrick->spawnflags &= ~2;
						player->client->pers.friends++;
					}
					
					cast_memory = level.global_cast_memory[self->character_index][player->character_index];
					cast_memory->flags |= MEMORY_HIRED;
					cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
					cast_memory->flags |= MEMORY_HIRE_ASK;
					player->client->pers.friends++;
					self->spawnflags &= ~2;
					//gi.dprintf ("DEBUG: hired patrick and butch %d\n", player->client->pers.friends);
					
				}
				return(1);
			}
			else
			{
				Voice_Specific (self, player, rc_butch, 12);
				return (0);
			}
		}
		else if (player->episode_flags & EP_RC_BUTCH_500)
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_PAY_500);
			Voice_Specific (self, player, rc_butch, 12);
			return (0);
		}
		else if (player->episode_flags & EP_RC_FAILED_TEST)
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_500);
			Voice_Random (self, player, &rc_butch[7], 2);
			return (0);
		}
		
		// the player had defeated all three 
		// and he didn't cheat
		if (marx_brothers_defeated && !(player->episode_flags & EP_RC_FAILED_TEST))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_JOKERS_HIRED);
			Voice_Random (self, player, &rc_butch[9], 2);
			{
				// need to auto hire butch and patrick
				{
					// auto hire butch and patrick
					edict_t *Patrick;

					Patrick = EP_GetCharacter (NAME_PATRICK);

					if (Patrick)
					{
						cast_memory = level.global_cast_memory[Patrick->character_index][player->character_index];

						cast_memory->flags |= MEMORY_HIRED;
						cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						cast_memory->flags |= MEMORY_HIRE_ASK;

						Patrick->leader = player;
						Patrick->cast_info.aiflags |= AI_NOWALK_FACE;
						Patrick->order = ORDER_FOLLOWME;
						Patrick->order_timestamp = level.time;
						Patrick->spawnflags &= ~2;
						player->client->pers.friends++;
					}
					
					cast_memory = level.global_cast_memory[self->character_index][player->character_index];
					cast_memory->flags |= MEMORY_HIRED;
					cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
					cast_memory->flags |= MEMORY_HIRE_ASK;
					player->client->pers.friends++;
					self->spawnflags &= ~2;
					//gi.dprintf ("DEBUG: hired patrick and butch %d\n", player->client->pers.friends);
					
				}	
			}
			return (1);
		}
		
		if (!(player->episode_flags & EP_RC_BUTCH_FIRST))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_FIRST);
			Voice_Random (self, player, rc_butch, 3);
		}
		else if (!(player->episode_flags & EP_RC_BUTCH_TALK1))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_TALK1);			
			Voice_Specific (self, player, rc_butch, 3);
		}
		else if (!(player->episode_flags & EP_RC_BUTCH_TALK2))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_TALK2);
			Voice_Specific (self, player, rc_butch, 4);
		}
		else
		{
			player->episode_flags = player->client->pers.episode_flags &= ~EP_RC_BUTCH_TALK1;
			player->episode_flags = player->client->pers.episode_flags &= ~EP_RC_BUTCH_TALK2;
			Voice_Specific (self, player, rc_butch, 11);
		}

		return (0);
	}
	
	if (self->name_index == NAME_PATRICK)
	{		
		
		if (player->episode_flags & EP_RC_JOKERS_HIRED)
			return (1);

		if (player->episode_flags & EP_RC_PAY_500)
		{
			if (player->client->pers.currentcash >= 500)
			{
				player->client->pers.currentcash-=500;
				EP_Skidrow_Register_EPFLAG (player, EP_RC_JOKERS_HIRED);
				
				{
					// auto hire butch and patrick
					edict_t *Butch;

					Butch = EP_GetCharacter (NAME_BUTCH);

					if (Butch)
					{
						cast_memory = level.global_cast_memory[Butch->character_index][player->character_index];

						cast_memory->flags |= MEMORY_HIRED;
						cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						cast_memory->flags |= MEMORY_HIRE_ASK;

						Butch->leader = player;
						Butch->cast_info.aiflags |= AI_NOWALK_FACE;
						Butch->order = ORDER_FOLLOWME;
						Butch->order_timestamp = level.time;
						Butch->spawnflags &= ~2;
						player->client->pers.friends++;
					}
					
					cast_memory = level.global_cast_memory[self->character_index][player->character_index];
					cast_memory->flags |= MEMORY_HIRED;
					cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
					cast_memory->flags |= MEMORY_HIRE_ASK;
					player->client->pers.friends++;
					self->spawnflags &= ~2;
					// gi.dprintf ("DEBUG: hired patrick and butch %d\n", player->client->pers.friends);
					
				}
				return(1);
			}
			else
			{
				Voice_Specific (self, player, rc_patrick, 12);
				return (0);
			}
		}
		else if (player->episode_flags & EP_RC_BUTCH_500)
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_PAY_500);
			Voice_Specific (self, player, rc_patrick, 12);
			return (0);
		}
		else if (player->episode_flags & EP_RC_FAILED_TEST)
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_500);
			Voice_Random (self, player, &rc_patrick[7], 2);
			return (0);
		}
		
		// the player had defeated all three 
		// and he didn't cheat
		if (marx_brothers_defeated && !(player->episode_flags & EP_RC_FAILED_TEST))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_JOKERS_HIRED);
			Voice_Random (self, player, &rc_patrick[9], 2);
			{
				// need to auto hire butch and patrick
				{
					// auto hire butch and patrick
					edict_t *Butch;

					Butch = EP_GetCharacter (NAME_BUTCH);

					if (Butch)
					{
						cast_memory = level.global_cast_memory[Butch->character_index][player->character_index];

						cast_memory->flags |= MEMORY_HIRED;
						cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						cast_memory->flags |= MEMORY_HIRE_ASK;

						Butch->leader = player;
						Butch->cast_info.aiflags |= AI_NOWALK_FACE;
						Butch->order = ORDER_FOLLOWME;
						Butch->order_timestamp = level.time;
						Butch->spawnflags &= ~2;
						player->client->pers.friends++;
					}
					
					cast_memory = level.global_cast_memory[self->character_index][player->character_index];
					cast_memory->flags |= MEMORY_HIRED;
					cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
					cast_memory->flags |= MEMORY_HIRE_ASK;
					player->client->pers.friends++;
					self->spawnflags &= ~2;
					// gi.dprintf ("DEBUG: hired patrick and butch %d\n", player->client->pers.friends);
					
				}	
			}
			return (1);
		}
		
		if (!(player->episode_flags & EP_RC_BUTCH_FIRST))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_FIRST);
			Voice_Random (self, player, rc_patrick, 3);
		}
		else if (!(player->episode_flags & EP_RC_BUTCH_TALK1))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_TALK1);			
			Voice_Specific (self, player, rc_patrick, 3);
		}
		else if (!(player->episode_flags & EP_RC_BUTCH_TALK2))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_RC_BUTCH_TALK2);
			Voice_Specific (self, player, rc_patrick, 4);
		}
		else
		{
			player->episode_flags = player->client->pers.episode_flags &= ~EP_RC_BUTCH_TALK1;
			player->episode_flags = player->client->pers.episode_flags &= ~EP_RC_BUTCH_TALK2;
			Voice_Specific (self, player, rc_patrick, 11);
		}

		return (0);
	}
	
	if (player->episode_flags & EP_RC_JOKERS_HIRED)
	{
		cast_memory = level.global_cast_memory[self->character_index][player->character_index];

		if (cast_memory && !(cast_memory->flags & MEMORY_HIRED))
		{
			if (player->client->pers.friends < 2)
			{
				cast_memory->flags |= MEMORY_HIRED;
				cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
				cast_memory->flags |= MEMORY_HIRE_ASK;

				Voice_Random (self, player, rc_joker, 4);

				player->client->pers.friends++;
				self->spawnflags &= ~2;
			}
			else
			{
				Voice_Specific (self, player, hiredguy_ask, 10);
				return (0);
			}
		}

		return (1);
	}
	else
	{
		// Voice_Random (self, player, &rc_joker[4], 6);
		
		if (self->gender == GENDER_MALE)
		{
			if (!(player->episode_flags & EP_RC_JOKERS_NOTEPAD))
			{
				EP_Skidrow_Register_EPFLAG (player, EP_RC_JOKERS_NOTEPAD);
				Voice_Random (self, player, &rc_joker[6], 2);
			}
			else
				Voice_Random (self, player, &rc_joker[4], 6);
		}
		else 
			gi.dprintf ("ERROR no female jokers\n");
	}
		

	return (0);	
}

void EP_RCFlags (edict_t *self)
{
	if (self->name_index == NAME_MOMO)
	{
		self->cast_info.aiflags |= AI_IMMORTAL;
		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
	}

	// David should have his weapons invisible till he gets hired
}

void EP_RC_CheckMomo (edict_t *ent, cast_memory_t	*mem)
{
	if (ent->episode_flags & EP_RC_MOMO_ASKED_MONEY)
	 	mem->inc++;
				
}

qboolean EP_RC_DoKey (edict_t *self, edict_t *other)
{
	return false;
}

extern mmove_t	punk_move_walk_dokey;
extern mmove_t	punk_move_crch_dokey;

extern mmove_t  runt_move_walk_dokey;
extern mmove_t	runt_move_crch_dokey;

extern mmove_t	bitch_move_walk_dokey;

extern mmove_t	thug_move_walk_dokey;
extern mmove_t	thug_move_crch_dokey;

void EP_RC_Check_DoKey (edict_t *self, edict_t *ent)
{
	return;
}


void EP_RC_ReachedDoKey (edict_t *self)
{
	vec3_t	vec;
	float	dist;

	VectorSubtract (self->s.origin, self->goal_ent->s.origin, vec);
	dist = VectorLength (vec);
	
}

void EP_RC_EndDoKey (edict_t *self)
{
	edict_t		*dest = NULL;
	edict_t		*ent = NULL;
	edict_t		*player;

	player = &g_edicts[1];

}

void EP_RC_HiredGuysRegisterFlags (edict_t *ent, edict_t *other)
{

	return;
}

void EP_RC_SpecialEventDeath (edict_t *self)
{
	edict_t *player;

	player = &g_edicts[1];

	if (self->name_index == NAME_GROUCHO)
		EP_Skidrow_Register_EPFLAG (player, EP_RC_GROUCHO_DEAD);
	else if (self->name_index == NAME_HARPO)
		EP_Skidrow_Register_EPFLAG (player, EP_RC_HARPO_DEAD);
	else if (self->name_index == NAME_CHICO)
		EP_Skidrow_Register_EPFLAG (player, EP_RC_CHICO_DEAD);

}

/*QUAKED rc_initiation_observer (.5 .5 1) (-16 -16 -24) (16 16 48)
will check to see if the player cheated
*/

void rc_observer_think (edict_t *self)
{
	edict_t *player;

	self->nextthink = level.time + 0.1;

	player = &g_edicts[1];

	if(player->episode_flags & EP_RC_JOKERS_HIRED)
		return;

	if (player->episode_flags & EP_RC_INTOBRUSH)
	{
		if (player->client->gun_noise)
		{
			{
				edict_t *Butch = NULL;
				edict_t *Patrick = NULL;

				Patrick = EP_GetCharacter (NAME_PATRICK);
				Butch = EP_GetCharacter (NAME_BUTCH);

				if (Butch || Patrick)
				{
					gi.dprintf ("Hey! We heard that\n");
					EP_Skidrow_Register_EPFLAG (player, EP_RC_FAILED_TEST);
					
					if (Butch)
						gi.sound(player, CHAN_VOICE, gi.soundindex("rc/actors/male/butch/hearshooting.wav"), 1, ATTN_NORM, 0);
					else
						gi.sound(player, CHAN_VOICE, gi.soundindex("rc/actors/male/patrick/hearshooting.wav"), 1, ATTN_NORM, 0);


					self->nextthink = level.time + 15.0;
				}
			}
		}
	}
}

void SP_rc_initiation_observer (edict_t *self)
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

	self->think = rc_observer_think;
	self->nextthink = level.time + 0.1;

	AI_Ent_droptofloor( self );
}


/*QUAKED rc_initiation_brush (.5 .5 0) ?
marks where the player can no longer fire his gun
*/

void rc_initiation_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t	vec;

	if (!(other->client))
		return;

	// are we going into, or out of the territory?
	
	VectorSubtract( other->s.origin, self->pos1, vec );
	vec[2] = 0;
	VectorNormalize( vec );

	if (DotProduct( vec, self->movedir ) > 0)
	{		// going into
		EP_Skidrow_Register_EPFLAG (other, EP_RC_INTOBRUSH);
		other->episode_flags = other->client->pers.episode_flags &= ~EP_RC_OUTOFBRUSH;

		if (!(other->episode_flags & EP_RC_THE_WARNING))
		{
			EP_Skidrow_Register_EPFLAG (other, EP_RC_THE_WARNING);
			{
				edict_t *Butch = NULL;
				edict_t *Patrick = NULL;

				Patrick = EP_GetCharacter (NAME_PATRICK);
				Butch = EP_GetCharacter (NAME_BUTCH);

				if (Butch || Patrick)
				{
					if (Butch)
						gi.sound(other, CHAN_VOICE, gi.soundindex("rc/actors/male/butch/noshooting.wav"), 1, ATTN_NORM, 0);
					else
						gi.sound(other, CHAN_VOICE, gi.soundindex("rc/actors/male/patrick/noshooting.wav"), 1, ATTN_NORM, 0);
				}
			}
			
		}

	}
	else	// going out of
	{
		EP_Skidrow_Register_EPFLAG (other, EP_RC_OUTOFBRUSH);
		other->episode_flags = other->client->pers.episode_flags &= ~EP_RC_INTOBRUSH;
	}

	other->time_territory_touched = level.time;

}

void SP_rc_initiation_brush ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = rc_initiation_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

	// set the center pos
	VectorAdd( ent->absmin, ent->absmax, ent->pos1 );
	VectorScale( ent->pos1, 0.5, ent->pos1 );

	AngleVectors( ent->s.angles, ent->movedir, NULL, NULL );
}


#include "ep_log.h"

extern int	the_log_page;

void EP_RC_Player_Log (edict_t *self, int page)
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
	else if (the_log_page >= NUM_RC_PLAYER_LOG)
		the_log_page = 0;

	for (i=1; i<NUM_RC_PLAYER_LOG; i++)
	{
		if (self->client->pers.episode_flags & ep_rc_player_log[i].ep_flag)
			cnt++;

		if (cnt == the_log_page)
		{
			select = i;
			break;
		}
	}	

	if (!page || !the_log_page)
	for (i=0; i<NUM_RC_PLAYER_LOG; i++)
	{
		if (ep_rc_player_log[i].new_clue == true)
		{
			select = i;
			break;
		}
	}

	if (cnt == 0)
	{
		the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_rc_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcpy (game.helpmessage2, ep_rc_player_log[0].ep_text);
	}
	else
	{
		if (select == 0)
			the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_rc_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcat (game.helpmessage2, ep_rc_player_log[select].ep_text);
		if (page)
			gi.sound(self, CHAN_VOICE, gi.soundindex("world/pageturn.wav"), 1, ATTN_NONE, 0);
	}
	

}


qboolean EP_RC_Flash_Newflag (edict_t *self, int ep_flag)
{
	int i;
	qboolean gotone = false;

	for (i=0; i<NUM_RC_PLAYER_LOG; i++)
	{
		if (ep_rc_player_log[i].ep_flag == ep_flag)
		{
			ep_rc_player_log[i].new_clue = true;
			gotone = true;
		}
		else
			ep_rc_player_log[i].new_clue = false;
	}

	return (gotone);

}
