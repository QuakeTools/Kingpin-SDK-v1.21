/******************************************************************************

  POSIONVILLE - Episode specific code

*******************************************************************************/

#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

qboolean ProcessPVMomo (edict_t *self, edict_t *other);
qboolean ProcessPVYolanda (edict_t *self, edict_t *other);

void Resp_PVLouie_TellsMe (edict_t *self, edict_t *other, response_t response);
void misc_pv_afraid_think (edict_t *self);

// This gets called whenever a character (player or AI) is sighted by an AI character
// in the Posionville episode

qboolean EP_Poisonville_CastSight ( edict_t *self, edict_t *other, cast_memory_t *mem )
{
	if (self->name_index == NAME_MOMO && other->client)
	{
		if (mem->timestamp < (level.time - 8))
		{	// haven't seen them for a while
			other->episode_flags &= ~EP_PV_MOMO_ASKED_MONEY;
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

	if (self->name_index == NAME_YOLANDA && other->client)
	{
		if (mem->timestamp < (level.time - 8))
		{	// haven't seen them for a while
			if (!(other->episode_flags & EP_PV_YOLANDA_TOOK_MONEY))
			other->episode_flags &= ~EP_PV_YOLANDA_ASKED_MONEY;
		}

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

	if (	(	(self->name_index == NAME_LAUREL)
			||	(self->name_index == NAME_HARDEY))
		&&	(other->client) )
	{
		if (self->enemy)
		{
			self->goal_ent = NULL;

			return false;
		}

		if (other->current_territory != self->cast_group || VectorDistance(self->s.origin, other->s.origin) > AI_NOT_HOLSTERED_RANGE_1)
		{
			// Ignore them
			return true;
		}
		else
		{
			if (VectorDistance (self->s.origin, other->s.origin) > AI_NOT_HOLSTERED_RANGE_1)
			{
				// Dont get mad yet
				return true;
			}
			else
			{
				// too close waist em
				AI_MakeEnemy( self, other, 0 );
				AI_StartAttack( self, other );
				self->goal_ent = NULL;
				return false;
			}
		}
	}

	return false;
}

// EP_Posionville_CastUse
// Called when ever a character is "used" (like when someone dies that has a ->deathtarget set)

qboolean EP_Poisonville_CastUse (edict_t *self, edict_t *other, edict_t *activator)
{
	return false;
}


// EP_Posionville_EventSpeech
// Called on speech occasions 
//
//	Return TRUE so that the normal speech routines don't say something as well

qboolean EP_Poisonville_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{
	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
	
	switch (saywhat)
	{
	
	case say_neutral:

		if (self->name_index == NAME_LAUREL && other->name_index == NAME_YOLANDA)
		{
			Voice_Random (self, other, neutral_converse_to_female, 10);
			return true;
		}
		
		if (self->name_index == NAME_HARDEY && other->name_index == NAME_YOLANDA)
		{
			Voice_Random (self, other, neutral_converse_to_female, 10);
			return true;
		}
		
		if	((self->name_index == NAME_MOMO)
			 &&	(other->client))
		{
			return (ProcessPVMomo (self, other));
		}

		if (self->name_index == NAME_YOLANDA)
		{
			if (other->client)
			{
				// hack to save test time for yolanda
				// other->episode_flags |= EP_PV_HIRED_SAFE_BOY;
			
				if (other->episode_flags & EP_PV_HIRED_SAFE_BOY)
				{
					{
						edict_t *Laurel;
						edict_t *Hardey;

						Laurel = EP_GetCharacter (NAME_LAUREL);
						Hardey = EP_GetCharacter (NAME_HARDEY);

						if (Laurel && Hardey)
							return (ProcessPVYolanda (self, other));
						else 
							Voice_Random (self, other, &yolanda_specific[0], 5);			
					}
				}
				else
					Voice_Random (self, other, &yolanda_specific[0], 5);			
			
				return true;
			}
			else
			{
				Voice_Random (self, other, &yolanda_specific[12], 5); 
				return true;
			}
		}

		if (self->name_index == NAME_LOUIE && other->client)
		{

			if (other->episode_flags & EP_PV_SAFE_DOCS)
			{
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE2);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE3);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE5);
			}

			if (!(other->episode_flags & EP_PV_TALKED_LOUIE))
			{
				// hey your alive... I gotta job for you you get me the files from 
				// nicki blanco's safe and I'll let ya hire my guys
				
				Voice_Specific (self, other, pv_louie, 0);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE);

				return true;
			}

			if (!(other->episode_flags & EP_PV_TALKED_LOUIE2))
			{
				Voice_Specific (self, other, pv_louie, 1);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE2);

				return true;
			}
			if (!(other->episode_flags & EP_PV_TALKED_LOUIE3))
			{
				Voice_Specific (self, other, pv_louie, 3);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE3);

				return true;
			}
			if (!(other->episode_flags & EP_PV_TALKED_LOUIE5))
			{
				Voice_Specific (self, other, pv_louie, 18);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE5);

				return true;
			}
										 
			if (!(other->episode_flags & EP_PV_SAFE_DOCS_DELIVERED))
			{
				if ((other->client->pers.inventory[ITEM_INDEX(FindItem("Safe docs"))]) 
					&& (other->episode_flags & EP_PV_SAFE_DOCS)) 
				{
					// a deal is a deal my guys will run with you now
					Voice_Specific (self, other, pv_louie, 15);
					EP_Skidrow_Register_EPFLAG (other, EP_PV_SAFE_DOCS_DELIVERED);
					
					{
						int     index;
						gitem_t *item;

						item = FindItem ("Safe docs");
						index = ITEM_INDEX (item);
						other->client->pers.inventory[index] = 0;						
					}

					return true;
				}
				else
				{										 
					if (!(other->client->pers.episode_flags & EP_PV_SENT_TO_GET_SAFEDOCS))
					{
						Voice_Specific (self, other, pv_louie, 4);
						EP_Skidrow_Register_EPFLAG (other, EP_PV_SENT_TO_GET_SAFEDOCS);
						return true;
					}
					
					if (!(other->client->pers.episode_flags & EP_PV_LOUIE_SPEACH_1))
					{
						Voice_Specific (self, other, pv_louie, 13);
						EP_Skidrow_Register_EPFLAG (other, EP_PV_LOUIE_SPEACH_1);

						return true;
					}
					
					if (!(other->client->pers.episode_flags & EP_PV_TALKED_LOUIE4))
					{
						Voice_Specific (self, other, pv_louie, 14);
						EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE4);

						return true;
					}
					
					if (!(other->client->pers.episode_flags & EP_PV_LOUIE_SPEACH_2))
					{
						Voice_Specific (self, other, pv_louie, 19);
						EP_Skidrow_Register_EPFLAG (other, EP_PV_LOUIE_SPEACH_2);

						{
							cast_memory_t	*mem;

							mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
							
							mem->response = Resp_PVLouie_TellsMe;
						}

						return true;
					}
					
					{
						// random speak about the wearabouts of the safe
						Voice_Random (self, other, &pv_louie[9], 5);
					}

					return true;
				}
			}

			else
			{
				if (!(other->client->pers.episode_flags & EP_PV_LOUIE_KEY))
				{
					int     index;
					gitem_t *item;

					Voice_Specific (self, other, pv_louie, 16);
					EP_Skidrow_Register_EPFLAG (other, EP_PV_LOUIE_KEY);

					item = FindItem ("Chem_Plant_Key");
					index = ITEM_INDEX (item);
					other->client->pers.inventory[ index ] = 1;
					// show icon and name on status bar
					other->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
					other->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
					other->client->pickup_msg_time = level.time + 5.5;
					
				}
				// thanks see ya again sometime
				Voice_Specific (self, other, pv_louie, 12);
			}

			return true;
		}


		return false;
		break;
	
	case say_hostile:

		
		if (self->name_index == NAME_LOUIE && other->client)
		{
			if (other->episode_flags & EP_PV_SAFE_DOCS)
			{
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE2);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE3);
				EP_Skidrow_Register_EPFLAG (other, EP_PV_TALKED_LOUIE5);

				Voice_Random (self, other, &pv_louie[6], 3);

				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;

				return true;
			}

			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
			
				Voice_Random (self, other, &pv_louie[9], 3);		

				return true;
			}
			else
			{
				// just do a random curse at the player
				
				Voice_Random (self, other, &pv_louie[6], 3);
				return true;
			}
		}


		if (self->name_index == NAME_MOMO && other->client)
		{
			return (ProcessPVMomo (self, other));
		}

		if (self->name_index == NAME_YOLANDA && other->client)
		{
			self->cast_info.aiflags &= ~AI_NO_TALK;

			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
		
				Voice_Random (self, other, &yolanda_specific[0], 2);

				return true;
			}
			else
			{
				Voice_Random (self, other, &yolanda_specific[17], 8);	
			}

			self->cast_info.aiflags |= AI_NO_TALK;

			return true;
		}

		return false;
		break;
	}


	return false;
}


// EP_Posionville_ItemPickup
// Called whenever an item is picked up

void EP_Poisonville_ItemPickup ( edict_t *self, edict_t *other )
{

if (!Q_strcasecmp( self->classname, "item_safedocs" ))
{
	EP_Skidrow_Register_EPFLAG (other, EP_PV_SAFE_DOCS);
	EP_Skidrow_Register_EPFLAG (other, EP_PV_SAFEDOORISOPEN);
}

}

// EP_Posionville_Script

void EP_Poisonville_Script( edict_t *ent, char *scriptname )
{

}


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Special Posionville entities

//................................................


//==========================================================================================
//
// RESPONSES

void Resp_PVLouie_TellsMe (edict_t *self, edict_t *other, response_t response)
{
	
	if (response == resp_yes)
	{
		Voice_Player_Specific(self, TT_YES);
		{
			cast_memory_t	*mem;
			mem = level.global_cast_memory[ other->character_index ][ self->character_index ];
			mem->response = NULL;
		}
	}
	else
	{
		Voice_Player_Specific(self, TT_NO);

		self->episode_flags = self->client->pers.episode_flags &= ~EP_PV_LOUIE_SPEACH_1;
		self->episode_flags = self->client->pers.episode_flags &= ~EP_PV_LOUIE_SPEACH_2;
	}

	self->response_ent = other;
	self->last_response_time = level.time;
	self->last_response = response;
}

void Resp_PVYolanda_GotMoney ( edict_t *self, edict_t *other, response_t response )
{

	if (self->episode_flags & EP_PV_YOLANDA_TOOK_MONEY)
		return;

	if (response == resp_yes)
	{
		Voice_Player_Specific(self, TT_YES);
		
		if (!(self->episode_flags & EP_PV_YOLANDA_TOOK_MONEY))
		{
			if (self->client->pers.currentcash >= 10)
			{
				Voice_Random (self, other, player_money_yes, NUM_PLAYER_MONEY_YES);

				self->client->pers.currentcash -= 10;
				other->currentcash += 10;

				EP_Skidrow_Register_EPFLAG (self, EP_PV_YOLANDA_TOOK_MONEY);

				{
					edict_t *ent = NULL;

					ent = G_Find (ent, FOFS(classname), "misc_pv_afraid");

					Voice_Specific (other, self, yolanda_specific, 11);

					if (ent)
					{
						other->goal_ent = ent;
						ent->cast_info.aiflags |= AI_GOAL_RUN;
						ent->think = misc_pv_afraid_think;
						ent->nextthink = level.time + 2.0;
						other->cast_info.aiflags &= ~AI_TALK;
						{
							cast_memory_t	*mem;

							mem = level.global_cast_memory[ other->character_index ][ self->character_index ];

							self->last_response_time = 0;	// so we don't process this response again
							mem->response = NULL;
							self->response_ent = NULL;
						}

					}
					else
						gi.dprintf ("yolanda missing misc_pv_afraid marker\n");
				}
			}
			else
			{
				Voice_Random (self, other, player_money_no, NUM_PLAYER_MONEY_NO);

				response = resp_no;
			}
		}

	}
	else if (response == resp_no)
	{
		Voice_Specific( self, other, specific, 6 );
		Voice_Player_Specific(self, TT_NO);
	}

	self->response_ent = other;
	self->last_response_time = level.time;
	self->last_response = response;

}


qboolean ProcessPVYolanda (edict_t *self, edict_t *other)
{

	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];

	if (other->episode_flags & EP_PV_YOLANDA_TOOK_MONEY)
	{
		Voice_Random (self, other, &yolanda_specific[0], 3);	
		return true;
	}

	if (!(other->episode_flags & EP_PV_YOLANDA_ASKED_MONEY))		
	{
		Voice_Specific (self, other, yolanda_specific, 6);
		EP_Skidrow_Register_EPFLAG (other, EP_PV_YOLANDA_ASKED_MONEY);
		mem->response = Resp_PVYolanda_GotMoney;
		return true;
	}
	/*
	else if (	(other->response_ent == self)
			 &&	(other->last_response_time > (level.time - 5)))
	{
		if (other->last_response == resp_yes)
		{	
				Voice_Specific (self, other, yolanda_specific, 25);
		}
		else	// they said no
		{
			Voice_Specific (self, other, yolanda_specific, 25);
		}

		other->last_response_time = 0;	// so we don't process this response again

		mem->response = NULL;
		other->response_ent = NULL;

		return true;
	}
	*/
	else
	{
		Voice_Random (self, other, &yolanda_specific[8], 2); 

		if (yolanda_specific[8].last_played == level.time 
			|| yolanda_specific[9].last_played == level.time )
		{	
			mem->response = Resp_PVYolanda_GotMoney;
		}
				
	}

	return true;
}


void Resp_PVMomo_GotMoney ( edict_t *self, edict_t *other, response_t response )
{
	cast_memory_t	*mem;
		
	if (self->episode_flags & EP_PV_MOMO_TOOK_MONEY)
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
qboolean ProcessPVMomo (edict_t *self, edict_t *other)			
{
	
	cast_memory_t	*mem;	

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];

	if (mem->flags & MEMORY_LASTWARNING)
	{
		Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (other->episode_flags & EP_PV_MOMO_TOOK_MONEY)
	{
		// Ridah, 5-8-99, we've already taken their money, so say one of the following..

		if (!(mem->flags & MEMORY_ASSHOLE))
			Voice_Random ( self, other, &momo_specific[12], 2);		// so what's it gonna be... in or out?
		else	// they've cussed us, don't act all happy to see them
			Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (!(other->episode_flags & EP_PV_MOMO_FIRST_TIME))
	{
		
		Voice_Specific (self, other, momo_specific, 17); // welcome.wav

		EP_Skidrow_Register_EPFLAG (other, EP_PV_MOMO_FIRST_TIME);

		return true;
	}

	// Ridah, 5-8-99, I changed this so it clears this flag in EP_CastSight() if Momo sees you after not having seen you for a while
	if (!(other->episode_flags & EP_PV_MOMO_ASKED_MONEY))
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

		EP_Skidrow_Register_EPFLAG (other, EP_PV_MOMO_ASKED_MONEY);

		mem->response = Resp_Momo_GotMoney;
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
				
				EP_Skidrow_Register_EPFLAG (other, EP_PV_MOMO_TOOK_MONEY);

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
						if ((e->targetname) && (!strcmp(e->targetname, "bardoor_pv")))
						{
							// Unlock target door
							if (e->key == -1)
							{
								e->key = 0;	
								e->targetname = NULL;							
							}
						}
					}
					
					EP_Skidrow_Register_EPFLAG (other, EP_PV_MOMO_TOOK_MONEY);
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
					mem->response = Resp_PVMomo_GotMoney;
				}

			}
		}
		else
		{
			Voice_Random (self, other, &momo_specific[12], 5); 

			if (momo_specific[12].last_played == level.time)
			{	// we just asked them if they wanna come in, so let them respond
				mem->response = Resp_PVMomo_GotMoney;
			}
		}

	}
			
	return true;
}

// 
// PROCEDURES

int	EP_PV_HiredGuysFlags (edict_t *player, edict_t *self)
{
	if ((self->name_index == NAME_FINGERS || self->name_index == NAME_BUSTER))
	{
		edict_t *Buster;
		edict_t *Fingers;
		cast_memory_t *cast_memory;

		Buster = EP_GetCharacter (NAME_BUSTER);
		Fingers = EP_GetCharacter (NAME_FINGERS);
	
		cast_memory = level.global_cast_memory[self->character_index][player->character_index];

		if (player->episode_flags & EP_PV_SAFE_DOCS_DELIVERED && cast_memory && !(cast_memory->flags & MEMORY_HIRED))
		{
			Voice_Specific (self, player, hiredguy_ask, 10);
			return (0);
		}

		if (player->episode_flags & EP_PV_TALKED_LOUIE)
		{
			if (Buster && self == Buster)
			{
				if (Fingers)
				{
					cast_memory = level.global_cast_memory[Fingers->character_index][player->character_index];

					if (cast_memory && cast_memory->flags & MEMORY_HIRED)
					{
						// gi.dprintf ("FIXME SOUND TODO: %s:sorry I only work alone\n", Buster->name);
						Voice_Specific (self, player, hiredguy_ask, 18);
						return (0);
					}
				}
			}
			else if (Fingers && self == Fingers)
			{
				if (Buster)
				{
					cast_memory = level.global_cast_memory[Buster->character_index][player->character_index];
					if (cast_memory && cast_memory->flags & MEMORY_HIRED)
					{
						// gi.dprintf ("FIXME SOUND TODO: %s:sorry I only work alone\n", Fingers->name);
						Voice_Specific (self, player, hiredguy_ask, 18);
						return (0);
					}
				}
			}
		

			{
				cast_memory_t *cast_memory;

				if (Buster && self == Buster)
				{
					cast_memory = level.global_cast_memory[self->character_index][player->character_index];
				
					if (!(cast_memory->flags & MEMORY_HIRE_FIRST_TIME))
					{
						cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						Voice_Specific (self, player, hiredguy_ask, 14);
						return (0);
					}
					else
						return (1);
				}
				else if (Fingers && self == Fingers)
				{
					cast_memory = level.global_cast_memory[self->character_index][player->character_index];
					if (!(cast_memory->flags & MEMORY_HIRE_FIRST_TIME))
					{
						cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
						Voice_Specific (self, player, hiredguy_ask, 16);
						return (0);
					}
					else
						return (1);
				}
			}
		}
		else 
		{
			Voice_Random (self, player, &hiredguy_ask[10], 4);
			return (0);
		}
		// only the two safe crackers are allowed to join the player
		return (1);
	}
	else if (player->episode_flags & EP_PV_SAFE_DOCS_DELIVERED)
		return (1);
	else 
	{
		if (!(player->episode_flags & EP_PV_FIND_LOUIE))
			EP_Skidrow_Register_EPFLAG (player, EP_PV_FIND_LOUIE);

		if (self->gender == GENDER_MALE)
			Voice_Random (self, player, &hiredguy_ask[10], 4);
		else
			Voice_Random (self, player, &hiredgal_specific[12], 4);

		return (0);
	}
}

void EP_PV_SpecialEventDeath (edict_t *self)
{
	edict_t *player;
	edict_t *idiot;

	player = &g_edicts[1];
	
	if (self->name_index == NAME_BUSTER)
		EP_Skidrow_Register_EPFLAG (player, EP_PV_BUSTERISDEAD);

	if (self->name_index == NAME_FINGERS)
		EP_Skidrow_Register_EPFLAG (player, EP_PV_FINGERSISDEAD);

	if ( !(player->episode_flags & EP_PV_SAFEDOORISOPEN) &&
		(player->episode_flags & EP_PV_BUSTERISDEAD && player->episode_flags & EP_PV_FINGERSISDEAD))
	{
		idiot = G_Find (NULL, FOFS (targetname), "trigger_idiot");

		if (idiot)
			idiot->use (idiot, player, player);
		else
			gi.dprintf ("error you are an idiot\n");

		player->episode_flags = player->client->pers.episode_flags = 0;
	}

}

void EP_PVFlags (edict_t *self)
{
	if (self->name_index == NAME_MOMO)
	{
		self->cast_info.aiflags |= AI_IMMORTAL;
		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
	}
	else if ((strstr (level.mapname, "bar_")))
	{
		// make all weapons invisible while we are in a bar
		if (self->gender == GENDER_MALE || self->gender == GENDER_FEMALE)
		{
			self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
			self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
		}
	}
}


void EP_PV_CheckMomo (edict_t *ent, cast_memory_t	*mem)
{
	if (ent->episode_flags & EP_PV_MOMO_ASKED_MONEY)
	 	mem->inc++;
				
}

qboolean EP_PV_DoKey (edict_t *self, edict_t *other)
{
	if (other->name_index == NAME_FINGERS || other->name_index == NAME_BUSTER && self->client)
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

void EP_PV_Check_DoKey (edict_t *self, edict_t *ent)
{
	edict_t *Buster;
	edict_t *Fingers;
	edict_t *dest;
	vec3_t	vec;
	float	dist;

	Buster = EP_GetCharacter (NAME_BUSTER);
	Fingers = EP_GetCharacter (NAME_FINGERS);
	
	if (!ent)
		return;

	if (!(ent->targetname))
	{
		if (Fingers)
		{
			self->cast_info.aiflags &= ~AI_DOKEY;
			Fingers->cast_info.aiflags &= ~AI_DOKEY;
		}
		if (Buster)
		{
			self->cast_info.aiflags &= ~AI_DOKEY;
			Buster->cast_info.aiflags &= ~AI_DOKEY;
		}
	
		return;
	}

		
	// its a safe and its locked
	if (!strcmp (ent->targetname, "safe_door") && ent->key == -1)
	{
		dest = G_Find (NULL, FOFS (targetname), ent->target); // ai_safespot

		if (Buster && Buster->cast_info.aiflags & AI_DOKEY)
		{
			if (!(Buster->goal_ent) || !(Buster->enemy))
			{	
				if (visible (Buster, dest))
				{
					VectorSubtract (Buster->s.origin, dest->s.origin, vec);
					dist = VectorLength (vec);

					if (dist < 384)
					{
						Buster->goal_ent = dest; 
						self->cast_info.aiflags &= ~AI_DOKEY;
						Buster->cast_info.aiflags &= ~AI_DOKEY;
						Buster->cast_info.currentmove = &runt_move_walk_dokey;
					}
				}
			}
		}
		else if (Fingers && Fingers->cast_info.aiflags & AI_DOKEY)
		{
			if (!(Fingers->goal_ent) || !(Fingers->enemy))
			{
				if (visible (Fingers, dest))
				{
					VectorSubtract (Fingers->s.origin, dest->s.origin, vec);
					dist = VectorLength (vec);
					
					if (dist < 384)
					{
						Fingers->goal_ent = dest; 
				
						self->cast_info.aiflags &= ~AI_DOKEY;
						Fingers->cast_info.aiflags &= ~AI_DOKEY;

						Fingers->cast_info.currentmove = &thug_move_walk_dokey; // this should be called dokey

						// make the guns invisible
						Fingers->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
						Fingers->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);

					}
				}
			}
		}
		else 
			gi.dprintf ("there is no one to open the safe\n");
	}
	


}


void EP_PV_ReachedDoKey (edict_t *self)
{
	vec3_t	vec;
	float	dist;
	edict_t		*dest;

	VectorSubtract (self->s.origin, self->goal_ent->s.origin, vec);
	dist = VectorLength (vec);
	
	if (dist < 32)
	{
		if (self->name_index == NAME_BUSTER)
		{
			self->cast_info.currentmove = &runt_move_crch_dokey;
		}
		else if (self->name_index == NAME_FINGERS)
		{
			self->goal_ent = NULL;

			dest = G_Find (NULL, FOFS (targetname), "trigger_fingers"); 
			if (dest->use)
			{
					dest->use (dest, self, self);
			}

			self->cast_info.currentmove = &thug_move_crch_dokey;
		}
		else if (self->name_index == NAME_YOLANDA)
		{
			self->goal_ent = NULL;
			self->cast_info.currentmove = self->cast_info.move_stand;
			self->cast_info.aiflags |= AI_TALK;
			
			{
				edict_t *Laurel;
				vec3_t	vec;
				
				Laurel = EP_GetCharacter (NAME_LAUREL);

				if (Laurel)
				{
					VectorSubtract (Laurel->s.origin, self->s.origin, vec);
					VectorNormalize (vec);
					self->ideal_yaw = vectoyaw (vec);
					M_ChangeYawOld (self);
					Laurel->cast_info.aiflags |= AI_TALK;

					Voice_Specific (Laurel, self, neutral_converse_to_female, 6);
				}

			}

		}
		
	}
	/*
	else if (dist < 128)
	{
		if (self->name_index == NAME_LAUREL)
		{
			self->goal_ent = NULL;
			self->cast_info.currentmove = self->cast_info.move_stand;
			
			{
				edict_t *Yolanda;
				vec3_t	vec;
				
				Yolanda = EP_GetCharacter (NAME_YOLANDA);

				if (Yolanda)
				{
					VectorSubtract (self->s.origin, Yolanda->s.origin, vec);
					VectorNormalize (vec);
					Yolanda->ideal_yaw = vectoyaw (vec);
					M_ChangeYawOld (Yolanda);
					self->cast_info.aiflags |= AI_TALK;

					Voice_Specific (self, Yolanda, neutral_converse_to_female, 6);
				}

			}
		}
		else if (self->name_index == NAME_HARDEY)
		{
			self->goal_ent = NULL;
			self->cast_info.currentmove = self->cast_info.move_stand;
		
		}
	}
	*/

}

void EP_PV_EndDoKey (edict_t *self)
{
	edict_t		*dest;
	edict_t		*player;

	player = &g_edicts[1];

	if (self->name_index == NAME_BUSTER)
	{
		self->cast_info.currentmove = self->cast_info.move_run;

		dest = G_Find (NULL, FOFS (targetname), "trigger_buster"); 

		if (dest)
			if (dest->use)
			{
					dest->use (dest, self, self);
			}

		// spawn a grenade
		// FIXME: need to replace with dynamite
		{
			// JOSEPH 17-MAY-99
			fire_dynamite (self, self->s.origin, vec3_origin, 120, 750, 5.0, 256);
			// fire_grenade (self, self->s.origin, vec3_origin, 120, 750, 5.0, 256);
			// END JOSEPH
			// gi.dprintf ("FIXME SOUND TODO: %s: run she's gonna blow\n", self->name);
			Voice_Specific (self, player, hiredguy_ask, 15);
			EP_Skidrow_Register_EPFLAG (player, EP_PV_SAFEDOORISOPEN);
		}

	}
	else if (self->name_index == NAME_FINGERS)
	{
		self->cast_info.currentmove = self->cast_info.move_run;
		// gi.dprintf ("FIXME SOUND TODO %s: there you go easy money!\n", self->name);
		Voice_Specific (self, player, hiredguy_ask, 17);
		EP_Skidrow_Register_EPFLAG (player, EP_PV_SAFEDOORISOPEN);
		
		// he's done so show the guns
		self->s.model_parts[PART_GUN].invisible_objects = 0;
		self->s.model_parts[PART_GUN2].invisible_objects = 0;

	}	

}

qboolean EP_PV_UnlockDoorFlag (edict_t *ent)
{

	return false;

}

void EP_PV_HiredGuysRegisterFlags (edict_t *ent, edict_t *other)
{
	if (other->name_index == NAME_FINGERS || other->name_index == NAME_BUSTER)
		EP_Skidrow_Register_EPFLAG (ent, EP_PV_HIRED_SAFE_BOY);		
}

/*QUAKED misc_pv_afraid (.5 .5 1) (-16 -16 -24) (16 16 48)
used by actors to pick location where it is safer to run away from the player
*/

void misc_pv_afraid_think (edict_t *self)
{
	edict_t *Yolanda;
	edict_t *Laurel;
	edict_t *Hardey;
	vec3_t	vec;
	float	dist;

	Yolanda = EP_GetCharacter (NAME_YOLANDA);

	if (!self->count)
	{
		if (Yolanda)
		{
			self->count = 1;
			gi.sound(Yolanda, CHAN_VOICE, gi.soundindex("actors/female/yolanda/shakin.wav"), 1, ATTN_NORM, 0);
		}
	}
	else if (self->count == 3)
		return;

	if (Yolanda)
	{
		
		VectorSubtract (Yolanda->s.origin, self->s.origin, vec);
		dist = VectorLength (vec);

		// gi.dprintf ("dist: %5.3f\n", dist);

		if (dist < 128)
		{
			if (self->count == 1)
			{
				Yolanda->cast_info.currentmove = &bitch_move_walk_dokey;
				Yolanda->cast_info.aiflags &= ~AI_TALK;
			}
	
			Laurel = EP_GetCharacter (NAME_LAUREL);
			Hardey = EP_GetCharacter (NAME_HARDEY);

			if (Laurel && self->count == 1)
			{
				{
					edict_t *ent = NULL;

					ent = G_Find (ent, FOFS(classname), "misc_pv_afraid");

					if (ent)
					{
						Laurel->goal_ent = ent;
						ent->cast_info.aiflags |= AI_GOAL_RUN;
						Laurel->cast_info.aiflags &= ~AI_TALK;
					}
					
				}

				Laurel->cast_info.talk_ent = NULL;
				Laurel->cast_info.currentmove = Laurel->cast_info.move_run;
				self->count = 2;
				self->nextthink = level.time + 2.0;
			}

			else if (Hardey && self->count == 2)
			{	
				/*
				{
					edict_t *ent = NULL;

					ent = G_Find (ent, FOFS(classname), "misc_pv_afraid");

					if (ent)
					{
						// Hardey->goal_ent = ent;
						ent->cast_info.aiflags |= AI_GOAL_RUN;
						Hardey->cast_info.aiflags &= ~AI_TALK;
					}
					
				}
				*/

				if (Laurel)
					Hardey->goal_ent = Laurel;
				else
					Hardey->goal_ent = Yolanda;

				Hardey->cast_info.aiflags &= ~AI_TALK;
				Hardey->cast_info.talk_ent = NULL;
				Hardey->cast_info.currentmove = Hardey->cast_info.move_run;
				self->count = 3;
			}
		}
		else
			self->nextthink = level.time + 0.1;

	}
	

}

void SP_misc_pv_afraid (edict_t *self)
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
	self->count = 0;

	AI_Ent_droptofloor( self );

	gi.linkentity (self);
}


/*QUAKED ai_pv_fuseblown1 (.5 .5 1) ?
This will set the EP_PV_FUSEBLOWN flag
*/

void ai_fuseblown_touch1 (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{	
	int     index;
	gitem_t *item;

	if (!(other->client))
		return;
	
	item = FindItem ("Fuse");
	index = ITEM_INDEX (item);

	if (other->client->pers.inventory[ index ])
	{
		self->touch = NULL;
		return;
	}	

	if (!(other->episode_flags & EP_PV_ONEFUSE))
		EP_Skidrow_Register_EPFLAG (other, EP_PV_ONEFUSE);
	
	if (!(other->episode_flags & EP_PV_FUSEISBLOWN1))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_PV_FUSEISBLOWN1);
		
		if (other->episode_flags & EP_PV_ONEFUSE && other->episode_flags & EP_PV_FUSEISBLOWN2)
		{
			gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/fuse2.wav"), 1, ATTN_NORM, 0);
		}
		else
		{
			gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/fuse1.wav"), 1, ATTN_NORM, 0);
		}

		self->touch = NULL;

	}
	// FIXME
	// we need to play a wav file
	
}

void SP_pv_fuse_blown1 (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_fuseblown_touch1;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}

/*QUAKED ai_pv_fuseblown2 (.5 .5 1) ?
This will set the EP_PV_FUSEBLOWN flag
*/

void ai_fuseblown_touch2 (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	int     index;
	gitem_t *item;

	if (!(other->client))
		return;

	item = FindItem ("Fuse");
	index = ITEM_INDEX (item);

	if (other->client->pers.inventory[ index ])
	{
		self->touch = NULL;
		return;
	}

	if (!(other->episode_flags & EP_PV_ONEFUSE))
		EP_Skidrow_Register_EPFLAG (other, EP_PV_ONEFUSE);
	
	if (!(other->episode_flags & EP_PV_FUSEISBLOWN2))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_PV_FUSEISBLOWN2);
		
		if (other->episode_flags & EP_PV_ONEFUSE && other->episode_flags & EP_PV_FUSEISBLOWN1)
		{
			gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/fuse2.wav"), 1, ATTN_NORM, 0);
		}
		else
		{
			gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/fuse1.wav"), 1, ATTN_NORM, 0);
		}

		self->touch = NULL;

	}

	// FIXME
	// we need to play a wav file
	
}

void SP_pv_fuse_blown2 (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_fuseblown_touch2;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}


/*QUAKED ai_pv_deadlouie (.5 .5 1) ?
This will set the EP_PV_LOUIEPVB flag
*/

void ai_louiedead_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!(other->client))
		return;

	if (!(other->episode_flags & EP_PV_LOUIEPVB))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_PV_LOUIEPVB);
		// gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/louieisdead.wav"), 1, ATTN_NORM, 0);
		self->touch = NULL;
	}
	
	// FIXME
	// we need to play a wav file
	
}

void SP_pv_deadlouie (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_louiedead_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}

#include "ep_log.h"

extern int	the_log_page;

void EP_PV_Player_Log (edict_t *self, int page)
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
	else if (the_log_page >= NUM_PV_PLAYER_LOG)
		the_log_page = 0;

	for (i=1; i<NUM_PV_PLAYER_LOG; i++)
	{
		if (self->client->pers.episode_flags & ep_pv_player_log[i].ep_flag)
			cnt++;

		if (cnt == the_log_page)
		{
			select = i;
			break;
		}
	}	

	if (!page || !the_log_page)
	for (i=0; i<NUM_PV_PLAYER_LOG; i++)
	{
		if (ep_pv_player_log[i].new_clue == true)
		{
			select = i;
			break;
		}
	}

	if (cnt == 0)
	{
		the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_pv_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcpy (game.helpmessage2, ep_pv_player_log[0].ep_text);
	}
	else
	{
		if (select == 0)
			the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_pv_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcat (game.helpmessage2, ep_pv_player_log[select].ep_text);
		if (page)
			gi.sound(self, CHAN_VOICE, gi.soundindex("world/pageturn.wav"), 1, ATTN_NONE, 0);
	}


	

}

qboolean EP_PV_Flash_Newflag (edict_t *self, int ep_flag)
{
	int i;
	qboolean gotone = false;

	for (i=0; i<NUM_PV_PLAYER_LOG; i++)
	{
		if (ep_pv_player_log[i].ep_flag == ep_flag)
		{
			ep_pv_player_log[i].new_clue = true;
			gotone = true;
		}
		else
			ep_pv_player_log[i].new_clue = false;
	}

	return (gotone);
}
