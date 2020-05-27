/******************************************************************************

  SHIPYARDS - Episode specific code

*******************************************************************************/

#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

qboolean ProcessSYMomo (edict_t *self, edict_t *other);
qboolean ProcessMoe (edict_t *self, edict_t *player, cast_memory_t *mem);
void misc_sy_afraid_think (edict_t *self);

qboolean EP_SY_CastSight ( edict_t *self, edict_t *other, cast_memory_t *mem )
{
	if (self->name_index == NAME_MOE && other->client)
	{
		if (mem->timestamp < (level.time - 8))
		{	// haven't seen them for a while
			other->episode_flags &= ~EP_SY_MOE_FIRST_SIGHT;
		}
		return false;
	}

	if (self->name_index == NAME_MOMO && other->client)
	{
		if (mem->timestamp < (level.time - 8))
		{	// haven't seen them for a while
			other->episode_flags &= ~EP_SY_MOMO_ASKED_MONEY;
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

	if (self->name_index == NAME_POPEYE && other->client)
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

qboolean EP_SY_CastUse (edict_t *self, edict_t *other, edict_t *activator)
{
	return false;
}

qboolean EP_SY_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{
	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
	
	switch (saywhat)
	{
	
	case say_neutral:

		if (self->name_index == NAME_MOE && other->client)
		{
			if (!(other->episode_flags & EP_SY_MOE_FIRST_SIGHT))
			{
				// HEY WHAT ARE YOU DOING HERE
				EP_Skidrow_Register_EPFLAG (other, EP_SY_MOE_FIRST_SIGHT);
				Voice_Specific (self, other, ty_mo, 0);
				mem->flags |= MEMORY_UPSET;
				return true;
			}

			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE || mem->flags & MEMORY_UPSET)
			{
				mem->flags |= MEMORY_UPSET;
				return (ProcessMoe (self, other, mem));
			}
			else
				return true;
		}
				
		if (self->name_index == NAME_BWILLIE && other->client)
		{
			Voice_Random (self, other, sy_bigwillie, 5);
			return true;
		}

		if (self->name_index == NAME_DOGG && other->client)
		{
			Voice_Random (self, other, sy_dogg, 5);
			return true;
		}

		if	((self->name_index == NAME_MOMO)
			 &&	(other->client))
		{
			return (ProcessSYMomo (self, other));
		}

		if (self->name_index == NAME_POPEYE && other->client)
		{
			{
				float dist;
				vec3_t vec;

				VectorSubtract (self->s.origin, other->s.origin, vec);
				dist = VectorLength (vec);
				if (dist > 192)
				{
					Voice_Specific (self, other, sy_popeye, 22);
					return true;
				}

			}

			if (!(other->episode_flags & EP_SY_SCREAMING_BITCH))
			{
				// tell player about the bigwillie's girl
				EP_Skidrow_Register_EPFLAG (other, EP_SY_SCREAMING_BITCH);
				Voice_Specific (self, other, sy_popeye, 0);
			}
			else if (!(other->episode_flags & EP_SY_TACKLE))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_SY_TACKLE);
				Voice_Specific (self, other, sy_popeye, 1);
			}
			else if (!(other->client->pers.friends) && !(other->episode_flags & EP_SY_GOTO_SALTYDOG))
			{
				// tell them to go to the bar
				EP_Skidrow_Register_EPFLAG (other, EP_SY_GOTO_SALTYDOG);
				Voice_Specific (self, other, sy_popeye, 2);
			}
			else if (other->episode_flags & EP_SY_FOUND_BITCH)
			{
				// player found the remains so just say ambient
				
				if (!(other->episode_flags & EP_SY_POPEYE_LASTLINE))
				{
					EP_Skidrow_Register_EPFLAG (other, EP_SY_POPEYE_LASTLINE);
					Voice_Specific (self, other, sy_popeye, 12);
				}
				else
					Voice_Random (self, other, &sy_popeye[9], 7);
			}
			else
			{
				Voice_Random (self, other, &sy_popeye[3], 6);
			}
			return true;
		}

		return false;

		break;
	case say_hostile:

		if (self->name_index == NAME_MOE && other->client)
		{
			mem->flags &= ~MEMORY_UPSET;
			return (ProcessMoe (self, other, mem));
		}
		
		if (self->name_index == NAME_BWILLIE && other->client)
		{
			Voice_Random (self, other, sy_bigwillie, 5);
			return true;
		}

		if (self->name_index == NAME_DOGG && other->client)
		{
			Voice_Random (self, other, sy_dogg, 5);
			return true;
		}

		if (self->name_index == NAME_MOMO && other->client)
		{
			return (ProcessSYMomo (self, other));
		}

		if (self->name_index == NAME_POPEYE && other->client)
		{
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
			
				if (other->episode_flags & EP_SY_FOUND_BITCH)
				{
					// player found the remains so just say ambient
					// Voice_Random (self, other, &sy_popeye[9], 7);
					if (!(other->episode_flags & EP_SY_POPEYE_LASTLINE))
					{
						EP_Skidrow_Register_EPFLAG (other, EP_SY_POPEYE_LASTLINE);
						Voice_Specific (self, other, sy_popeye, 12);
					}
					else
						Voice_Random (self, other, &sy_popeye[9], 7);
				}
				else
					Voice_Random (self, other, &sy_popeye[3], 6);

				return true;
			}
			else
			{
				// just do a random speech
				Voice_Random (self, other, &sy_popeye[16], 3);	

				return true;
			}
		}

		return false;
		
		break;
	}

	return false;
}

void EP_SY_ItemPickup ( edict_t *self, edict_t *other )
{
	/*
	if (!Q_strcasecmp( self->classname, "item_lure" ))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_SY_GOT_LURE);
	}
	*/
	if (!Q_strcasecmp( self->classname, "item_lizzyhead" ))
	{
		// EP_Skidrow_Register_EPFLAG (other, EP_SY_FOUND_BITCH);

		if (!(other->episode_flags & EP_SY_FOUND_BITCH))
		{
			//edict_t *Sal;
			
			EP_Skidrow_Register_EPFLAG (other, EP_SY_FOUND_BITCH);

			//Sal = EP_GetCharacter (NAME_SAL);

			//if (Sal)
			//{
			//	Voice_Specific (Sal, other, sy_sal, 3);

			//}
			//else 
			gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/tellwilly.wav"), 1, ATTN_NORM, 0);
		}
	}

}

void EP_SY_Script( edict_t *ent, char *scriptname )
{

}

void Resp_SYMomo_GotMoney ( edict_t *self, edict_t *other, response_t response )
{
	cast_memory_t	*mem;
		
	if (self->episode_flags & EP_SY_MOMO_TOOK_MONEY)
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


qboolean ProcessMoe (edict_t *self, edict_t *player, cast_memory_t *mem)
{
	if (player->episode_flags & EP_SY_MOE_RUNAWAY)
		return false;

	if (player->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE || mem->flags & MEMORY_UPSET)
	{
		mem->flags &= ~MEMORY_ASSHOLE;

		if (!(player->episode_flags & EP_SY_MOE_ESCALATE1))
		{	
			player->episode_flags = player->client->pers.episode_flags &= ~EP_SY_MOE_FEAR3;
			player->episode_flags = player->client->pers.episode_flags &= ~EP_SY_MOE_FEAR2;
			player->episode_flags = player->client->pers.episode_flags &= ~EP_SY_MOE_FEAR1;
			
			EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_ESCALATE1);
			Voice_Random (self, player, &ty_mo[1], 4);
		}

		else if (!(player->episode_flags & EP_SY_MOE_ESCALATE2))
		{	
			EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_ESCALATE2);
			Voice_Random (self, player, &ty_mo[1], 4);
		}

		else if (!(player->episode_flags & EP_SY_MOE_ESCALATE3))
		{	
			EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_ESCALATE3);
			Voice_Random (self, player, &ty_mo[1], 4);
		}
						
		else
		{
			// Moe is brave enough to attack the player now
			{
				edict_t *Larry;
				edict_t *Curly;

				// MO ATTACK THE PLAYER LINE
				Voice_Specific (self, player, ty_mo, 8);
					
				AI_MakeEnemy(self, self->cast_info.talk_ent, 0);
				
				Larry = EP_GetCharacter (NAME_LARRY);
				Curly = EP_GetCharacter (NAME_CURLY);

				if (Larry)
				{
					// make larry hostile
					AI_MakeEnemy(Larry, self->cast_info.talk_ent, 0);
				}

				if (Curly)
				{
					// make curly hostile
					AI_MakeEnemy(Curly, self->cast_info.talk_ent, 0);
				}

			}
		}
		
	}	
	else
	{
		if (!(player->episode_flags & EP_SY_MOE_FEAR1))
		{	
			// GENERIC MOE CURSE AFRAID
			player->episode_flags = player->client->pers.episode_flags &= ~EP_SY_MOE_ESCALATE1;
			player->episode_flags = player->client->pers.episode_flags &= ~EP_SY_MOE_ESCALATE2;
			player->episode_flags = player->client->pers.episode_flags &= ~EP_SY_MOE_ESCALATE3;
			EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_FEAR1);
			EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_LASTLINE);
			Voice_Specific (self, player, ty_mo, 5);
		}
			
		else if (!(player->episode_flags & EP_SY_MOE_FEAR2))
		{	
			// GENERIC MOE CURSE AFRAID
			EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_FEAR2);
			Voice_Specific (self, player, ty_mo, 6);
		}

		else if (!(player->episode_flags & EP_SY_MOE_FEAR3))
		{	
			// GENERIC MOE CURSE AFRAID
			EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_FEAR3);
			Voice_Specific (self, player, ty_mo, 7);
		}

		else
		{
				
			// make Moe run off to misc_sy_afraid
			{
				edict_t *ent = NULL;

				ent = G_Find (ent, FOFS(classname), "misc_sy_afraid");

				if (ent)
				{
					self->goal_ent = ent;
					ent->cast_info.aiflags |= AI_GOAL_RUN;
					ent->think = misc_sy_afraid_think;
					ent->nextthink = level.time + 0.1;
					self->cast_info.aiflags &= ~AI_TALK;

					EP_Skidrow_Register_EPFLAG (player, EP_SY_MOE_RUNAWAY);
				}
				else
					gi.dprintf ("moe missing misc_sy_afraid marker\n");
			}


		}
		
		last_client_talk = level.time + 2;
		return true;
	}

	return true;
}

			
// generic process for hostile or neutral momo			
qboolean ProcessSYMomo (edict_t *self, edict_t *other)			
{
	
	cast_memory_t	*mem;	

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];

	if (mem->flags & MEMORY_LASTWARNING)
	{
		Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (other->episode_flags & EP_SY_MOMO_TOOK_MONEY)
	{
		// Ridah, 5-8-99, we've already taken their money, so say one of the following..

		if (!(mem->flags & MEMORY_ASSHOLE))
			Voice_Random ( self, other, &momo_specific[12], 2);		// so what's it gonna be... in or out?
		else	// they've cussed us, don't act all happy to see them
			Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (!(other->episode_flags & EP_SY_MOMO_FIRST_TIME))
	{
		
		Voice_Specific (self, other, momo_specific, 19); // welcome.wav

		EP_Skidrow_Register_EPFLAG (other, EP_SY_MOMO_FIRST_TIME);

		return true;
	}

	// Ridah, 5-8-99, I changed this so it clears this flag in EP_CastSight() if Momo sees you after not having seen you for a while
	if (!(other->episode_flags & EP_SY_MOMO_ASKED_MONEY))
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

		EP_Skidrow_Register_EPFLAG (other, EP_SY_MOMO_ASKED_MONEY);

		mem->response = Resp_SYMomo_GotMoney;
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
				
				EP_Skidrow_Register_EPFLAG (other, EP_SY_MOMO_TOOK_MONEY);

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
						if ((e->targetname) && (!strcmp(e->targetname, "bardoor_sy")))
						{
							// Unlock target door
							if (e->key == -1)
							{
								e->key = 0;	
								e->targetname = NULL;							
							}
						}
					}
					
					EP_Skidrow_Register_EPFLAG (other, EP_SY_MOMO_TOOK_MONEY);
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
					mem->response = Resp_SYMomo_GotMoney;
				}

			}
		}
		else
		{
			Voice_Random (self, other, &momo_specific[12], 5); 

			if (momo_specific[12].last_played == level.time)
			{	// we just asked them if they wanna come in, so let them respond
				mem->response = Resp_SYMomo_GotMoney;
			}
		}

	}
			
	return true;
}


int	EP_SY_HiredGuysFlags (edict_t *player, edict_t *self)
{
	cast_memory_t *cast_memory;
	
	if (self->name_index == NAME_BIGWILLIE)
	{
		if (player->episode_flags & EP_SY_BW_HIRED)
			return (1);

		if (player->episode_flags & EP_SY_FOUND_BITCH && !(player->episode_flags & EP_SY_BIGWILLIE_REVENGE))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_SY_BIGWILLIE_REVENGE);
			Voice_Specific (self, player, sy_bigwillie, 5);
			return (0);
		}

		if (!(player->episode_flags & EP_SY_BW_HIRED) && player->episode_flags & EP_SY_FOUND_BITCH)
		{
			edict_t	*Lefty;

			Lefty = EP_GetCharacter (NAME_LEFTY);

			EP_Skidrow_Register_EPFLAG (player, EP_SY_BW_HIRED);

			{
				int     index;
				gitem_t *item;

				item = FindItem ("Lizzy Head");
				index = ITEM_INDEX (item);
				player->client->pers.inventory[ index ] = 0;
			}
					
			
			switch (player->client->pers.friends)
			{
			case 0: // Big Willie and Lefty will join
				{
					if (Lefty)
					{
						//cast_memory = level.global_cast_memory[Lefty->character_index][player->character_index];
						//cast_memory->flags |= MEMORY_HIRED;
						//cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						//cast_memory->flags |= MEMORY_HIRE_ASK;
						//player->client->pers.friends++;
						cast_memory = level.global_cast_memory[Lefty->character_index][player->character_index];

						cast_memory->flags |= MEMORY_HIRED;
						cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						cast_memory->flags |= MEMORY_HIRE_ASK;

						Lefty->leader = player;
						Lefty->cast_info.aiflags |= AI_NOWALK_FACE;
						Lefty->order = ORDER_FOLLOWME;
						Lefty->order_timestamp = level.time;
						
						// hack to fix trigger spawn problem
						Lefty->spawnflags &= ~2;

						player->client->pers.friends++;

						EP_Skidrow_Register_EPFLAG (player, EP_SY_LEFTY_HIRED);
					}

					cast_memory = level.global_cast_memory[self->character_index][player->character_index];
					cast_memory->flags |= MEMORY_HIRED;
					cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
					cast_memory->flags |= MEMORY_HIRE_ASK;
					player->client->pers.friends++;

					// hack to fix trigger spawn problem
					self->spawnflags &= ~2;

					// Voice_Specific (self, player, sy_bigwillie, 5);

					{
						int     index;
						gitem_t *item;

						item = FindItem ("Shipyard_Key");
						index = ITEM_INDEX (item);
						player->client->pers.inventory[ index ] = 1;
						// show icon and name on status bar
						player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
						player->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
						player->client->pickup_msg_time = level.time + 5.5;
					}
				}
				return (1);
				break;
			case 1: // Big Willie will join
				cast_memory = level.global_cast_memory[self->character_index][player->character_index];
				cast_memory->flags |= MEMORY_HIRED;
				cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
				cast_memory->flags |= MEMORY_HIRE_ASK;
				player->client->pers.friends++;
				
				// hack to fix trigger spawn problem
				self->spawnflags &= ~2;
				// Voice_Specific (self, player, sy_bigwillie, 5);
				
				{
					int     index;
					gitem_t *item;

					item = FindItem ("Shipyard_Key");
					index = ITEM_INDEX (item);
					player->client->pers.inventory[ index ] = 1;
					// show icon and name on status bar
					player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
					player->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
					player->client->pickup_msg_time = level.time + 5.5;
				}
				return (1);
				break;
			case 2: // no one can join
				gi.dprintf ("FIXME: level problem with Bigwillie\n");
				return (1);
				break;
			}
		}
	}
	
	if (self->name_index == NAME_SAL)
	{
		if (!(player->episode_flags & EP_SY_GOFIND_BITCH_SAL))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_SY_GOFIND_BITCH_SAL);
			Voice_Specific (self, player, sy_sal, 0);
			return (0);
		}
		if (!(player->episode_flags & EP_SY_SAL_SECONDLINE))
		{
			Voice_Specific (self, player, sy_sal, 2);
			EP_Skidrow_Register_EPFLAG (player, EP_SY_SAL_SECONDLINE);
			return (0);
		}
		else if (!(player->episode_flags & EP_SY_HIRED_SAL))
		{
			if (player->client->pers.friends < 2)
			{

				// Voice_Specific (self, player, sy_sal, 2);
				EP_Skidrow_Register_EPFLAG (player, EP_SY_HIRED_SAL);

				cast_memory = level.global_cast_memory[self->character_index][player->character_index];

				cast_memory->flags |= MEMORY_HIRED;
				cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
				cast_memory->flags |= MEMORY_HIRE_ASK;

				self->leader = player;
				self->cast_info.aiflags |= AI_NOWALK_FACE;
				self->order = ORDER_FOLLOWME;
				self->order_timestamp = level.time;

				self->spawnflags &= ~2;

				player->client->pers.friends++;
			
				{
					int     index;
					gitem_t *item;
									  
					item = FindItem ("Warehouse_Key");
					index = ITEM_INDEX (item);
					player->client->pers.inventory[ index ] = 1;
					// show icon and name on status bar
					player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
					player->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
					player->client->pickup_msg_time = level.time + 5.5;
				}
				return (1);
			}
			else
			{
				Voice_Random (self, player, sy_sal, 2);
				return (0);
			}
		}
		else // note to self this may be a problem
			return (1);
	}

	if (self->name_index == NAME_BLEFTY)
	{
		if (!(player->episode_flags & EP_SY_GOFIND_BITCH))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_SY_GOFIND_BITCH);
			Voice_Specific (self, player, sy_lefty, 3);
		}
		else if (!(player->episode_flags & EP_SY_FOUND_BITCH))
		{
			// hey your back without lizzy
			Voice_Random (self, player, sy_lefty, 3);
		}
		else if (player->episode_flags & EP_SY_FOUND_BITCH)
		{
			Voice_Random (self, player, &sy_lefty[3], 2);
		}
		return (0);

	}

	if (self->name_index == NAME_LEFTY)
	{
		if (player->episode_flags & EP_SY_LEFTY_HIRED)
			return (1);
		
		if (player->episode_flags & EP_SY_BW_HIRED)
		{
			if (player->client->pers.episode_flags & EP_SY_BIGWILLIE_DEAD || player->client->pers.episode_flags & EP_SY_SAL_DEAD)
			{
				// gi.dprintf ("hires: %d\n", player->client->pers.friends);
				if (player->client->pers.friends < 2)
				{
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

					EP_Skidrow_Register_EPFLAG (player, EP_SY_LEFTY_HIRED);
				
					return (1);
				}
				else
					Voice_Random (self, player, sy_lefty, 2);
			}
			else
				Voice_Random (self, player, sy_lefty, 2);
			
			return (0);
		}

		if (!(player->episode_flags & EP_SY_GOFIND_BITCH))
		{
			EP_Skidrow_Register_EPFLAG (player, EP_SY_GOFIND_BITCH);
			Voice_Specific (self, player, sy_lefty, 3);
		}
		else if (!(player->episode_flags & EP_SY_FOUND_BITCH))
		{
			// hey your back without lizzy
			Voice_Random (self, player, sy_lefty, 3);
		}
		else if (player->episode_flags & EP_SY_FOUND_BITCH)
		{
			Voice_Random (self, player, &sy_lefty[3], 2);
		}
		return (0);
		
	}

	return (1);
}

void EP_SYFlags (edict_t *self)
{
	if (self->name_index == NAME_MOMO)
	{
		self->cast_info.aiflags |= AI_IMMORTAL;

		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
	}
}

qboolean EP_SY_DoKey (edict_t *self, edict_t *other)
{
	return false;
}

void EP_SY_Check_DoKey (edict_t *self, edict_t *ent)
{

}

void EP_SY_ReachedDoKey (edict_t *self)
{

}

void EP_SY_EndDoKey (edict_t *self)
{

}

qboolean EP_SY_UnlockDoorFlag (edict_t *ent)
{
	return false;
}

void EP_SY_HiredGuysRegisterFlags (edict_t *ent, edict_t *other)
{

}

/*QUAKED ai_sy_dykes_boundry (.5 .5 1) ?
touching this brush will cause mo larry and curly to attack
*/


void ai_sy_boundry_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{

	edict_t *Moe;

	if (!(other->client))
		return;

	Moe = EP_GetCharacter (NAME_MOE);

	if (Moe)
	{
		edict_t *Larry;
		edict_t *Curly;
		
		Larry = EP_GetCharacter (NAME_LARRY);
		Curly = EP_GetCharacter (NAME_CURLY);
		
		if (Larry)
		{
			AI_MakeEnemy(Larry, other, 0);
		}
		
		if (Curly)
		{
			AI_MakeEnemy(Curly, other, 0);
		}

		
	}
	
	
}

void SP_sy_dykes_boundry ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_sy_boundry_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}

void	EP_SY_CheckMomo (edict_t *ent, cast_memory_t	*mem)
{
	if (ent->episode_flags & EP_SY_MOMO_ASKED_MONEY)
	 	mem->inc++;
				
}


extern mmove_t  runt_move_walk_dokey;

/*QUAKED misc_sy_afraid (.5 .5 1) (-16 -16 -24) (16 16 48)
used as the location mo will run to before larry and curly attack him
*/
	 
void misc_sy_afraid_think (edict_t *self)
{
	edict_t *Moe;
	edict_t *Larry;
	edict_t *Curly;
	edict_t *Player;
	vec3_t	vec;
	float	dist;

	extern void AI_CreateCharacterMemory(edict_t *src, edict_t *dest);

	Player = &g_edicts[1];

	Moe = EP_GetCharacter (NAME_MOE);

	if (Moe)
	{
		
		VectorSubtract (Moe->s.origin, self->s.origin, vec);
		dist = VectorLength (vec);

		// gi.dprintf ("dist: %5.3f\n", dist);

		if (dist < 256)
		{
			Moe->cast_info.currentmove = &runt_move_walk_dokey;
			Moe->cast_info.aiflags &= ~AI_TALK;
	
			Larry = EP_GetCharacter (NAME_LARRY);
			Curly = EP_GetCharacter (NAME_CURLY);

			if (Larry)
			{
				{
					cast_memory_t	*mem;

					mem = level.global_cast_memory[ Larry->character_index ][ Moe->character_index ];
					
					if (mem)
						AI_MakeEnemy(Larry, Moe, 0);	
					else
					{
						AI_CreateCharacterMemory(Larry, Moe);
						AI_MakeEnemy(Larry, Moe, 0);	
					}

				}
				
			}

			if (Curly)
			{	
				{
					cast_memory_t	*mem;

					mem = level.global_cast_memory[ Curly->character_index ][ Moe->character_index ];
					
					if (mem)
						AI_MakeEnemy(Curly, Moe, 0);	
					else
					{
						AI_CreateCharacterMemory(Curly, Moe);
						AI_MakeEnemy(Curly, Moe, 0);	
					}
				}
			}
		}
		else
			self->nextthink = level.time + 0.1;

	}
	

}

void SP_misc_sy_afraid (edict_t *self)
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

	gi.linkentity (self);
}

void larry_say (edict_t *self)
{
	edict_t *Larry;
	edict_t *Player;

	Player = &g_edicts[1];
	Larry = EP_GetCharacter (NAME_LARRY);

	Voice_Specific (Larry, Player, ty_larry, 0);
}

void EP_SY_SpecialEventDeath (edict_t *self)
{
	edict_t *Player;
	Player = &g_edicts[1];

	if (self->name_index == NAME_MOE)
	{
		{
			edict_t *Larry;

			Larry = EP_GetCharacter (NAME_LARRY);

			if (Larry)
			{
				{
					edict_t *larry_noise;

					larry_noise = G_Spawn ();
					larry_noise->think = larry_say;
					larry_noise->nextthink = level.time + 1.5;
					gi.linkentity (larry_noise);
				}
			}

		}
	}

	if (self->name_index == NAME_BIGWILLIE)
	{
		EP_Skidrow_Register_EPFLAG (Player, EP_SY_BIGWILLIE_DEAD);
	}

	if (self->name_index == NAME_SAL)
	{
		EP_Skidrow_Register_EPFLAG (Player, EP_SY_SAL_DEAD);
	}
}


/*QUAKED ai_sy_oilcan (.5 .5 1) ?
set EP_SY_GOTO_DOORSHUT flag
*/

void ai_sy_oilcan_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!(other->client))
		return;

	if (!(other->episode_flags & EP_SY_GOTO_DOORSHUT))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_SY_GOTO_DOORSHUT);
		// gi.sound(ent, CHAN_VOICE, gi.soundindex("need_oilcan.wav"), 1, ATTN_NORM, 0);
	}
	// FIXME
	// we need to play a wav file
	
}

void SP_sy_oilcan ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_sy_oilcan_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}

/*QUAKED ai_sy_blefty (.5 .5 1) ?
blefty unlink
*/

void ai_sy_blefty_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	edict_t	*BLefty;

	if (!(other->client))
		return;

	if (other->episode_flags & EP_SY_FOUND_BITCH)
	{

		BLefty = EP_GetCharacter (NAME_BLEFTY);

		if (BLefty)
			gi.unlinkentity (BLefty);

		self->touch = NULL;
	}

	
}

void SP_sy_blefty ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_sy_blefty_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}



#include "ep_log.h"

extern int	the_log_page;

void EP_SY_Player_Log (edict_t *self, int page)
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
	else if (the_log_page >= NUM_SY_PLAYER_LOG)
		the_log_page = 0;

	for (i=1; i<NUM_SY_PLAYER_LOG; i++)
	{
		if (self->client->pers.episode_flags & ep_sy_player_log[i].ep_flag)
			cnt++;

		if (cnt == the_log_page)
		{
			select = i;
			break;
		}
	}	

	if (!page || !the_log_page)
	for (i=0; i<NUM_SY_PLAYER_LOG; i++)
	{
		if (ep_sy_player_log[i].new_clue == true)
		{
			select = i;
			break;
		}
	}

	if (cnt == 0)
	{
		the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_sy_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcpy (game.helpmessage2, ep_sy_player_log[0].ep_text);
	}
	else
	{
		if (select == 0)
			the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_sy_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcat (game.helpmessage2, ep_sy_player_log[select].ep_text);
		if (page)
			gi.sound(self, CHAN_VOICE, gi.soundindex("world/pageturn.wav"), 1, ATTN_NONE, 0);
	}
	
	

}


qboolean EP_SY_Flash_Newflag (edict_t *self, int ep_flag)
{
	int i;
	qboolean gotone = false;

	for (i=0; i<NUM_SY_PLAYER_LOG; i++)
	{
		if (ep_sy_player_log[i].ep_flag == ep_flag)
		{
			ep_sy_player_log[i].new_clue = true;
			gotone = true;
		}
		else
			ep_sy_player_log[i].new_clue = false;
	}

	return (gotone);

}
