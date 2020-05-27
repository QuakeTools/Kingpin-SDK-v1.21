
/******************************************************************************

  SKIDROW - Episode specific code

*******************************************************************************/

#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

void Pull_Alarm_Think (edict_t *ent);
qboolean EP_Skidrow_ProcessMagicJ( edict_t *self, edict_t *other, cast_memory_t *mem );

qboolean ProcessMomo (edict_t *self, edict_t *other);
void EP_skidrow_radio_on (edict_t *self);

void Resp_Lenny (edict_t *self, edict_t *other, response_t response);

//............................................................................
// This gets called whenever a character (player or AI) is sighted by an AI character
// in the Skidrow episode

// Returns TRUE if no further processing should take place in AI_RecordSighting()

qboolean EP_Skidrow_CastSight ( edict_t *self, edict_t *other, cast_memory_t *mem )
{

	// Jesus (SR4 boss), if player gets battery, go into Psycho mode
	if (self->name_index == NAME_JESUS && other->client && !(self->cast_info.aiflags & AI_NO_TAKE_COVER))
	{
		static int battery_index;

		if (!battery_index)
			battery_index = 1 + ITEM_INDEX(FindItem("Battery"));

		if (other->client->pers.inventory[battery_index - 1])
		{	// go into Psycho mode
			self->cast_info.aiflags |= AI_NO_TAKE_COVER;

			// gi.dprintf( "SOUND TODO: Leave that battery alone muthafucka!!\n" );
			Voice_Specific (self, other, sr_jesus, 16);

			// release if currently hiding
			self->combat_goalent = NULL;
			self->cast_info.aiflags &= ~AI_TAKE_COVER;
			self->dont_takecover_time = 99999;
		}

		return false;
	}

	if (self->name_index == NAME_RUMMY || self->name_index == NAME_NICK || self->name_index == NAME_ED)
	{
		if (self->name_index == NAME_RUMMY && other->client)
		{
			other->episode_flags &= ~EP_SKIDROW_RUMMY_ASKED_WINE;
		}

		if (other->client && (mem->memory_type == MEMORY_TYPE_ENEMY) && !(other->client->pers.weapon))
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
	
	// Ridah, 5-8-99, added this so Momo asks you for the money if he hasn't seen you for a while
	if (self->name_index == NAME_MOMO && other->client)
	{
		if (mem->timestamp < (level.time - 8))
		{	// haven't seen them for a while
			other->episode_flags &= ~EP_SKIDROW_MOMO_ASKED_MONEY;
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

	// Hack, don't let Mona talk, or it'll probably sound too "feminin"
	if (self->name_index == NAME_MONA)
	{
		self->cast_info.aiflags |= AI_NO_TALK;
	}

	// Ridah, if listening to the radio, ignore player unless he's really close
	if (	(	(self->name_index == NAME_BERNIE)
			||	(self->name_index == NAME_ARNOLD))
		&&	(other->client)
		&&	(self->goal_ent && self->goal_ent->think == EP_skidrow_radio_on))
	{
		if (self->enemy)
		{
			self->goal_ent = NULL;

			return false;
		}

		if (other->current_territory != self->cast_group || VectorDistance(self->s.origin, other->s.origin) > AI_NOT_HOLSTERED_RANGE_2)
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

	if (self->name_index == NAME_LAMONT)
	{
		float dist;

		if (self->enemy)	// currently attacking
		{
			self->cast_info.aiflags |= AI_NO_TALK;
			return false;
		}
		else
		{
			self->cast_info.aiflags &= ~AI_NO_TALK;
		}

		dist = VectorDistance(self->s.origin, other->s.origin);

		self->cast_info.aiflags |= AI_FASTWALK;

		// check if player has entered range 1
		if (other->client)
		{
			if (dist < AI_NOT_HOLSTERED_RANGE_1)
			{
				if (mem->inc < 10)
				{	// we've come from outside the range
					if (mem->inc < 4)
						mem->inc++;

					mem->inc += 10;	// signify that we are now inside the range
				}
			}
			else
			{
				if (mem->inc >= 10)
				{	// just left the range 1
					mem->inc -= 10;
				}
			}
		}
		else if (VectorDistance( self->s.origin, g_edicts[1].s.origin ) < AI_NOT_HOLSTERED_RANGE_1)
		{	// talk to the player since they're close by
			return false;
		}

		// now talk if we're standing around
		if (	(self->last_talk_time < (level.time - 3))
			&&	(	(self->cast_info.currentmove->frame->aifunc == ai_stand)
				 ||	(other->client && dist < AI_NOT_HOLSTERED_RANGE_1/2)))
		{	// Lamont's a nut case..

			if (dist < AI_NOT_HOLSTERED_RANGE_1/2)
				self->cast_info.pausetime = level.time + 2;

			if (other->client && (dist < AI_NOT_HOLSTERED_RANGE_1))	// talk shit to player
			{
				// client is close, act hostile

				if (mem->inc%10 >= 4)
				{	// attack
					AI_MakeEnemy( self, other, 0 );
					Voice_Specific( self, other, lamont_random, 14 );
				}

				if (	(lamont_random[10 + mem->inc%10].last_played < (level.time - 10))
					||	(lamont_random[10 + mem->inc%10].last_played > level.time))
				{
					Voice_Specific( self, other, lamont_random, 10 + mem->inc%10 );
				}
				else	// randomly abuse player, and go on about Lenny
				{
					Voice_Random( self, other, &lamont_random[6], 7 );
				}

			}
			else if (!(other->client))
			{
				Voice_Random( self, other, lamont_random, 6 );
			}
			else	// they are a client, but a good distance away
			{
				Voice_Random( self, other, &lamont_random[0], 9 );
			}

			if ((dist < AI_NOT_HOLSTERED_RANGE_1) && !directly_infront( self, other))
				self->cast_info.avoid( self, other, true );
			else
				self->cast_info.talk( self );

			// pick a random path_corner to go to next
			if (self->goal_ent && self->goal_ent->target)
			{
				edict_t *trav=NULL;
				int		i;

				i = rand()%4;

				while (i-- && self->goal_ent->target && (trav = G_PickTarget(self->goal_ent->target)))
				{
					self->goal_ent = trav;
				}

				self->goal_ent->wait = 1 + rand()%4;
			}
		}

		if (self->goal_ent && !self->goal_ent->wait)
			self->goal_ent->wait = 1 + rand()%4;


		return false;
	}
	// Ridah, play Beth's special "backoff"
	if ( self->name_index == NAME_BETH && other->client && (self->last_talk_time < (level.time - 3)) )
	{
		if (	(!(other->client->pers.holsteredweapon))
			 &&	(other->client->pers.weapon)
			 &&	(!(mem->flags & MEMORY_WARNED_BACKOFF)))
		{
			float dist;

			dist = VectorDistance( self->s.origin, other->s.origin );

			if (dist < AI_NOT_HOLSTERED_RANGE_2)
			{
				mem->flags |= MEMORY_WARNED_BACKOFF;
				Voice_Random(self, other, &beth_specific[7], 2);
			}

		}
	}

	if ( self->name_index == NAME_MAGICJ && other->client)
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

		return EP_Skidrow_ProcessMagicJ (self, other, mem);
	}

	if ( self->cast_group == GANG_RATGANG )
	{
		
		cast_memory_t	*mem;
		
		mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
		
		if (other->client && !(other->episode_flags & EP_SKIDROW_RATS_PISSED)) 
		{
			EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_RATS_PISSED);
		}

		if (mem->flags & MEMORY_TAUNT && last_client_talk > level.time)
		{
			mem->flags &= ~MEMORY_TAUNT;

			Voice_Random(self, self->cast_info.talk_ent, profanity_level2, NUM_PROFANITY_LEVEL2);
			last_client_talk = level.time + 3 + rand()%10;
			
			self->cast_info.currentmove = self->cast_info.move_stand;

			

		}

	}

	return false;
}

//............................................................................
// EP_Skidrow_CastUse
// Called when ever a character is "used" (like when someone dies)

qboolean EP_Skidrow_CastUse (edict_t *self, edict_t *other, edict_t *activator)
{

	if ((other->name_index == NAME_LOUIE) && (other->health <= 0))
	{	// Louie has been killed, so walk to him
		self->goal_ent = other;
		self->target = NULL;

		other->cast_info.aiflags |= AI_GOAL_RUN;	// Run to him

// gi.dprintf( "Louie has been killed, sending Al in to investigate\n" );

		return true;
	}

	return false;

}


//............................................................................
// EP_Skidrow_EventSpeech
// Called on speech occasions (including flashlight hitting player)
//
//	Return TRUE so that the normal speech routines don't say something as well

qboolean EP_Skidrow_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{
	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
	

	//............................................................................
	// LAMONT
	if ( self->name_index == NAME_LAMONT )
	{	// Lamont speech done in EP_CastSight()
		return true;
	}

	// Hack, record that we've been to the Bar
	if (other->client && level.bar_lvl)
	{
		// other->client->pers.episode_flags = other->episode_flags |= EP_BAR_FIRST_TIME;
		EP_Skidrow_Register_EPFLAG (other, EP_BAR_FIRST_TIME);
	}

	switch (saywhat)
	{
	
	case say_neutral:

		if (self->name_index == NAME_RUMMY && other->client)
		{
			if (other->episode_flags & EP_SKIDROW_RUMMY_GAVE_WINE)
			{
				Voice_Random (self, other, &rummy[14], 2);
				return true;
			}

			if (!(other->episode_flags & EP_SKIDROW_TALKED_TO_RUMMY) && !(self->episode_flags & EP_SKIDROW_RUMMY_GAVE_WINE))
			{
				mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
				
				Voice_Random (self, other, &rummy[8], 2);
				EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_TALKED_TO_RUMMY);
				mem->response = Resp_Rummy_GotWine;

				return true;
			}
			else if (!(other->episode_flags & EP_SKIDROW_RUMMY_ASKED_WINE) && !(self->episode_flags & EP_SKIDROW_RUMMY_GAVE_WINE))
			{
				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
				{
					Voice_Random (self, other, &rummy[8], 2);
					// other->episode_flags |= EP_SKIDROW_RUMMY_ASKED_WINE;
					// other->client->pers.episode_flags |= EP_SKIDROW_RUMMY_ASKED_WINE;
						
					EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_RUMMY_ASKED_WINE);
					EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_TALKED_TO_RUMMY);
					mem->response = Resp_Rummy_GotWine;

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

					Voice_Random ( self, other, &rummy[4], 2 );
					// gi.dprintf ("Rummy: the combination is 36 26 36 ... \n");

					item = FindItem ("Whiskey");
					index = ITEM_INDEX (item);
					other->client->pers.inventory[ index ] = 0;
					// show icon and name on status bar
					other->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
					other->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
					other->client->pickup_msg_time = level.time + 5.5;
						
					// other->episode_flags |= EP_SKIDROW_RUMMY_GAVE_WINE;
					// other->client->pers.episode_flags |= EP_SKIDROW_RUMMY_GAVE_WINE;

					EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_RUMMY_GAVE_WINE);

					{	
						edict_t	*e;
						int		i;
							
						for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
						{
							if ((e->targetname) && (!strcmp(e->targetname, "safedoor_sr")))
							{
								// Unlock target door
								if (e->key == -1)
								{
									e->key = 0;	
									e->targetname = NULL;							
								}
							}
						}
							
					}

				}
				else
				{
					Voice_Random (self, other, &rummy[10], 2);
					mem->response = Resp_Rummy_GotWine;
				}

				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
					mem->response = NULL;

				other->response_ent = NULL;
				return true;
			}

			// ask for wine
			else if (	(specific[4].last_played < (level.time - 3))
					 &&	(specific[9].last_played < (level.time - 4)))
			{
				Voice_Random ( self, other, &rummy[8], 2 );

				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
					mem->response = Resp_Rummy_GotWine;

				return true;
			}

			else
			{
				Voice_Random ( self, other, &rummy[12], 2);
				return true;
			}
			
			return true;
		}
			
		if (self->name_index == NAME_NICK && other->client)
		{
			if (!(other->episode_flags & EP_SKIDROW_NICK_TOLD_BIKE))
			{
				Voice_Specific (self, other, nick, 6);
				EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_NICK_TOLD_BIKE);
				return true;
			}
				
			if (!(other->episode_flags & EP_SKIDROW_NICK_WARNING_1))
			{
				Voice_Specific (self, other, nick, 0);
				// other->client->pers.episode_flags = other->episode_flags |= EP_SKIDROW_JOSEPH_WARNING_1;		
				
				EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_NICK_WARNING_1);
			}
			else if (!(other->episode_flags & EP_SKIDROW_NICK_WARNING_2))
			{
				Voice_Random (self, other, &nick[1], 2);
				// other->client->pers.episode_flags = other->episode_flags |= EP_SKIDROW_JOSEPH_WARNING_2;		

				EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_NICK_WARNING_2);
			}
			else if (!(other->episode_flags & EP_SKIDROW_NICK_WARNING_3))
			{
				Voice_Random (self, other, &nick[3], 2);
				// other->client->pers.episode_flags = other->episode_flags |= EP_SKIDROW_JOSEPH_WARNING_3;		

				EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_NICK_WARNING_3);
			}
			else
			{
				Voice_Specific( self, other, nick, 5 );
				other->client->pers.episode_flags = other->episode_flags &= ~EP_SKIDROW_NICK_WARNING_1;		
				other->client->pers.episode_flags = other->episode_flags &= ~EP_SKIDROW_NICK_WARNING_2;		
				other->client->pers.episode_flags = other->episode_flags &= ~EP_SKIDROW_NICK_WARNING_3;		
			}
			
			return true;
		}

		if (self->name_index == NAME_ED && other->client)
		{
			Voice_Random (self, other, rummy, 4);
			return true;
		}
		
		if (self->name_index == NAME_LENNY && other->client)
		{

			self->cast_info.aiflags |= AI_REPEAT_TALK_JESTURE;

			// Have they got the watch?
			if ((other->client->pers.inventory[ITEM_INDEX(FindItem("Watch"))]) ||
				(other->episode_flags & EP_SKIDROW_LENNY_TOOK_WATCH)) 
			{	// got the watch..

				if (!(other->client->pers.inventory[ITEM_INDEX(FindItem("StoreRoomKey"))]))
				{	// Lenny hasn't given the key yet..

					if (mem->inc != 199)	// we haven't praised them yet
					{
						if (other->client->pers.episode_flags & EP_TALKED_TO_LENNY)
						{
							Voice_Specific( self, other, lenny_table, 1 );	// that's great!
							self->last_talk_time -= TALK_SELF_DELAY - 1.5;	// only wait 1.5 before we speak again, regardless of whether they respond or not
							other->last_talk_time = self->last_talk_time - 1;	// must have this so we don't think they've said something after us as a result of the above hack
						}
						else
						{
							Voice_Specific( self, other, lenny_table, 0 );	// christ, that's great!
							self->last_talk_time -= TALK_SELF_DELAY - 4.5;	// wait 4.5 seconds
							other->last_talk_time = self->last_talk_time - 1;	// must have this so we don't think they've said something after us as a result of the above hack
						}

						mem->inc = 199;
					}
					else	// give them the watch
					{
						int     index;
						gitem_t *item;

						// Lenny takes the watch
						item = FindItem ("Watch");
						index = ITEM_INDEX (item);
						other->client->pers.inventory[ index ] = 0;						

						// other->episode_flags |= EP_SKIDROW_LENNY_TOOK_WATCH;
						// other->client->pers.episode_flags |= EP_SKIDROW_LENNY_TOOK_WATCH;

						EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_LENNY_TOOK_WATCH);

						// Lenny gives player the key
						Voice_Specific( self, other, lenny_table, 2 );	// here's the key
						item = FindItem ("StoreRoomKey");
						index = ITEM_INDEX (item);
						other->client->pers.inventory[ index ]++;
						// show icon and name on status bar
						other->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
						other->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
						other->client->pickup_msg_time = level.time + 5.5;

						mem->inc = 0;
					}
				}
				else	// given them the watch, just chat
				{
					if (!mem->inc)
					{	
						Voice_Specific( self, other, lenny_table, 14 );
						mem->inc = 1;
					}
					else if (mem->inc == 1)
					{	// thanks again
						Voice_Random( self, other, &lenny_table[14], 2 );
						mem->inc = 2;
					}
					else if (mem->inc == 2)
					{	// you'd better leave now
						Voice_Specific( self, other, lenny_table, 13 );
						self->last_talk_time += 5;		 // this is a long one, give us more time to say it all
						mem->inc = 3;
					}
					else	// random stuff
					{
						Voice_Random( self, other, &lenny_table[10], 3 );
						if (mem->inc++ > 4)
							mem->inc = 1;	/// thank them again
					}

				}

				mem->response = Resp_Lenny;
				return true;
			}

			// if we've cussed him, act hostile back
			else if (other->response_ent == self && other->last_response == resp_no)
			{
				Voice_Random( self, other, &lenny_table[17], 3 );
				other->response_ent = NULL;	// get over it
			}

			// talked to them yet?
			else if (other->client->pers.episode_flags & EP_TALKED_TO_LENNY)
			{
				// random chat, we've already asked them about Lamont

				if (self->last_talk_time < (level.time - 15))	// haven't spoken for a while, they must have left and come back
				{
					Voice_Random( self, other, &lenny_table[22], 3 );
				}
				else if (mem->inc > 4)
				{	// been here too long
					Voice_Specific( self, other, lenny_table, 13 );
					self->last_talk_time += 3;		 // this is a long one, give us more time to say it all
					mem->inc = 0;
				}
				else
				{
					Voice_Random( self, other, &lenny_table[4], 9 );
					mem->inc++;
				}

				mem->response = Resp_Lenny;
				return true;
			}

			// first greeting
			else
			{
				if (mem->inc == 0)
				{	// hey you're that dude
					Voice_Specific( self, other, lenny_table, 3 );
					self->last_talk_time -= TALK_SELF_DELAY - 5;
					other->last_talk_time = self->last_talk_time - 1;	// must have this so we don't think they've said something after us as a result of the above hack
					mem->inc++;
				}
				else if (mem->inc == 1)
				{	// jesus
					Voice_Specific( self, other, lenny_table, 17 );
					self->last_talk_time -= TALK_SELF_DELAY - 2;
					other->last_talk_time = self->last_talk_time - 1;	// must have this so we don't think they've said something after us as a result of the above hack
					mem->inc++;
				}
				else
				{
					Voice_Specific( self, other, lenny_table, 4 );	// go kill lamont for me
				
					// other->client->pers.episode_flags = other->episode_flags |= EP_TALKED_TO_LENNY;		
					self->last_talk_time -= TALK_SELF_DELAY - 3;
					other->last_talk_time = self->last_talk_time - 1;	// must have this so we don't think they've said something after us as a result of the above hack

					mem->inc = 0;

					EP_Skidrow_Register_EPFLAG (other, EP_TALKED_TO_LENNY);
				}

				mem->response = Resp_Lenny;
				return true;
			}

		}

		//............................................................................
		// LISA
		// note to self:
		// this will ensure that she keeps the same tone of voice
		if ( self->name_index == NAME_LISA && other->client)/* && !other->client->pers.inventory[ITEM_INDEX(FindItem("Pistol"))])*/
		{
			int		index;
//			int		rval;
			edict_t	*Igmo;

			index = ITEM_INDEX (FindItem ("Pistol"));

			Igmo = EP_GetCharacter( NAME_IGMO ); 

			// check to see if the player has a pistol
			if (!Igmo)
			{
				// gi.dprintf ("SOUND TODO: Shit... your one bad ass Dude!\n");
				Voice_Specific (self, other, mona_specific, 13);

			}
			else if (other->client->pers.inventory [index]) 
			{
				Voice_Random (self, other, &lisa_specific[5], 3);		// Ridah, NOTE! new method of playing specific sounds, without repeating one's self
			}
			else if (other->client->pers.episode_flags & EP_PAWNOMATIC_FIRST_TIME)
			{
				Voice_Random (self, other, &lisa_specific[2], 6);
			}
			else
				Voice_Random(self, other, lisa_specific, 8);

			return true;
		}
		//............................................................................
		// BETH
		else if ( self->name_index == NAME_BETH && other->client)
		{
			if (other->client->pers.episode_flags & EP_SKIDROW_GOT_COIL)
			{
				Voice_Random (self, other, &beth_specific[4] , 3);	
			}
			else
			{
				Voice_Random(self, other, beth_specific, 6);
			}
			return true;
		}

		//............................................................................
		// MONA
		// JOSEPH 19-MAR-99
		else if ( self->name_index == NAME_MONA && other->client)
		{
			edict_t	*Lamont;

			Lamont = EP_GetCharacter( NAME_LAMONT );

			self->cast_info.aiflags &= ~AI_NO_TALK;

			if (Lamont && !(other->episode_flags & EP_SKIDROW_MONA_FIRST_TIME))
				EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MONA_FIRST_TIME);

			// If the player has killed Lamont
			if ((!Lamont || Lamont->health <= 0))
			{
				if (!(other->client->pers.episode_flags & EP_TALKED_TO_LENNY) && rand()%2)
					Voice_Random (self, other, &mona_specific[0], 4);	// make sure they know about Lenny in the bar
				else
					Voice_Random (self, other, &mona_specific[13], 2);	// you're one bad ass mofo
			}
			// If the player hasn't visited the bar
			else if (!(other->client->pers.episode_flags & EP_BAR_FIRST_TIME))
			{
				Voice_Random (self, other, &mona_specific[0], 8);
			}
			// If the player hasn't talked to lenny
			else if (!(other->client->pers.episode_flags & EP_TALKED_TO_LENNY))
			{
				Voice_Random (self, other, &mona_specific[10], 3);
			}
			else
			{
				Voice_Random (self, other, &mona_specific[4], 6);
			}
			
			self->cast_info.aiflags |= AI_NO_TALK;

			return true;
		}		
		// END JOSEPH


		//............................................................................
		// MAGICJ
		if	(	(self->name_index == NAME_MAGICJ)
			 &&	(other->client))
		{

			if (other->episode_flags & EP_SKIDROW_MAGICJ_GAVE_DOLLAR)
			{
				Voice_Random ( self, other, mj_random, 4);
				return true;
			}

			if (!(other->episode_flags & EP_SKIDROW_MAGICJ_ASKED_DOLLAR))
			{

				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
				{
					Voice_Specific( self, other, specific, 4 );
					// other->episode_flags |= EP_SKIDROW_MAGICJ_ASKED_DOLLAR;
					// other->client->pers.episode_flags |= EP_SKIDROW_MAGICJ_ASKED_DOLLAR;

					EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MAGICJ_ASKED_DOLLAR);

					mem->response = Resp_MagicJ_GotDollar;

					return true;
				}

			}

			// have they responded yet?
			else if (	(other->response_ent == self)
					 &&	(other->last_response_time > (level.time - 5)))
			{
				
				if (other->last_response == resp_yes)
				{	// give the crow bar to the player
					int     index;
					gitem_t *item;

					Voice_Specific( self, other, specific, 7 );
					item = FindItem ("Crowbar");
					index = ITEM_INDEX (item);
					other->client->pers.inventory[ index ]++;
					// show icon and name on status bar
					other->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
					other->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
					other->client->pickup_msg_time = level.time + 5.5;
					
					// other->episode_flags |= EP_SKIDROW_MAGICJ_GAVE_DOLLAR;
					// other->client->pers.episode_flags |= EP_SKIDROW_MAGICJ_GAVE_DOLLAR;

					EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MAGICJ_GAVE_DOLLAR);
				}
				else
				{
					Voice_Specific( self, other, specific, 8 );
				}

				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
					mem->response = NULL;

				other->response_ent = NULL;

				return true;
			}

			// randomly ask them about the iron bar
			else if (	(specific[4].last_played < (level.time - 30))
					 &&	(specific[9].last_played < (level.time - 40)))
			{
				Voice_Specific( self, other, specific, 9 );

				if (mem = level.global_cast_memory[ self->character_index ][ other->character_index ])
					mem->response = Resp_MagicJ_GotDollar;

				return true;
			}

			else
			{
				Voice_Random ( self, other, mj_random, 4);
				return true;
			}

		}
		// END JOSEPH

		//............................................................................
		// LEROY -> BETTY
		if (	(self->name_index == NAME_LEROY)
			&&	(other->name_index == NAME_BETTY))
		{
			Voice_Random(self, self->cast_info.talk_ent, neutral_converse_to_female, NUM_NEUTRAL_CONVERSE_TO_FEMALE);
			return true;
		}


		//............................................................................
		// BUSTER -> JED (doors.bsp scripting test)
		if (	(self->name_index == NAME_BUSTER)
			&&	(other->name_index == NAME_JED))
		{

			mem = level.global_cast_memory[self->character_index][other->character_index];

			if (mem->inc++ > 2)
			{	// time to bury them
				Voice_Specific(self, other, profanity_level2, 14 );
				AI_MakeEnemy( self, other, 0 );

				return true;
			}

			
			if (mem->inc == 1)
				Voice_Specific(self, other, profanity_level2, 7 );
			else if (mem->inc == 2)
				Voice_Specific(self, other, profanity_level2, 17 );
			else if (mem->inc == 3)
				Voice_Specific(self, other, profanity_level2, 11 );

			// pretend he's going to respond soon, so we don't wait so long
			other->last_talk_time = level.time + 2;

			return true;
		}

		// JOSEPH 13-FEB-99
		//............................................................................
		// MOMO
		if	(	(self->name_index == NAME_MOMO)
			 &&	(other->client))
		{
			return (ProcessMomo (self, other));
		}
		// END JOSEPH		

		break;
	
	case say_hostile:
		
		if (self->name_index == NAME_ED && other->client)
		{
			Voice_Random (self, other, rummy, 4);
			return true;
		}

		if ( self->name_index == NAME_BETH && other->client)
		{
			// Rafael: we need more negative sounds
			if (rand()%100 > 75)
				Voice_Random (self, other, &f_fightsounds[0],3);
			else
			Voice_Specific (self, other, beth_specific, 7);
			return true;
		}

		//............................................................................
		// MONA
		// JOSEPH 19-MAR-99
		if ( self->name_index == NAME_MONA && other->client)
		{
			{
				edict_t *Lamont;
				
				Lamont = EP_GetCharacter( NAME_LAMONT );
				
				if (Lamont && !(other->episode_flags & EP_SKIDROW_MONA_FIRST_TIME))
					EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MONA_FIRST_TIME);
			}
			
			
			self->cast_info.aiflags &= ~AI_NO_TALK;

			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
						
				
				
				Voice_Random (self, other, &mona_specific[0], 8);

				return true;
			}
			else
			{
				Voice_Random (self, other, &mona_specific[15], 5);	
			}

			self->cast_info.aiflags |= AI_NO_TALK;

			return true;
		}		
		// END JOSEPH
		
		if	(	(self->name_index == NAME_MAGICJ)
			 &&	(other->client))
		{
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
				
				Voice_Random ( self, other, mj_random, 4);
				return true;
			}
		

			else
			{
				if ((rand()%10) < 4)
					Voice_Specific (self, other, specific, 29);
				else
				Voice_Random ( self, other, &specific[23], 2);
				return true;
			}

		}

		
		if	(	(self->name_index == NAME_RUMMY  || self->name_index == NAME_NICK)
			 &&	(other->client))
		{
			
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
				
				if (self->name_index == NAME_RUMMY)
					Voice_Random (self, other, &rummy[12], 2);
				else
				{
					if (!(other->episode_flags & EP_SKIDROW_NICK_TOLD_BIKE))
					{
						Voice_Specific (self, other, nick, 6);
						EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_NICK_TOLD_BIKE);
					}
					else
						Voice_Random ( self, other, rummy, 3);
				}
				return true;
			}
		

			else
			{
				
				if (self->name_index == NAME_RUMMY)
					Voice_Random (self, other, &rummy[12], 2);
				else
				{
					if (!(other->episode_flags & EP_SKIDROW_NICK_TOLD_BIKE))
					{
						Voice_Specific (self, other, nick, 6);
						EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_NICK_TOLD_BIKE);
					}
					else
						Voice_Random ( self, other, rummy, 3);
				}
				return true;
			}

		}

		// JOSEPH 13-FEB-99
		if (self->name_index == NAME_MOMO && other->client)
		{
			return (ProcessMomo (self, other));
		}	
		
		// END JOSEPH
		
		if (	((self->name_index == NAME_BETTY) || (self->name_index == NAME_LEROY))
			&&	other->client)
		{
			edict_t *betty;
			betty = EP_GetCharacter (NAME_BETTY);

			if (!betty || betty->health < 0)
				return false;

			self->last_talk_time = level.time;

			{
				edict_t *leroy;
				leroy = EP_GetCharacter (NAME_LEROY);

				if (leroy && leroy->health > 0)
				{
//					return true;		// never speak to player if leroy is there

					float	time_offset;

					time_offset = 0.0;
				
					mem = level.global_cast_memory[ leroy->character_index ][ other->character_index ];

					if (mem->flags & MEMORY_LASTWARNING && directly_infront(other, self))	// they're looking at her
					{
						Voice_Random ( leroy, self->cast_info.talk_ent, &specific[16], 2);
//						Voice_Specific(leroy, self->cast_info.talk_ent, specific, 16 + rand()%2); // die
						AI_MakeEnemy(leroy, self->cast_info.talk_ent, 0);
					}
					else if (mem->flags & MEMORY_UPSET)
					{
						mem->flags |= MEMORY_LASTWARNING;

						if (!specific[15].last_played || specific[15].last_played > level.time)
							Voice_Specific ( leroy, other, specific, 15); // step off
						else
							Voice_Random ( leroy, other, &specific[12], 3);

						time_offset = 10.0;
					}
					else if (mem->flags & MEMORY_ASSHOLE)
					{
						Voice_Random ( leroy, other, &specific[12], 3);
						
						mem->flags |= MEMORY_UPSET;

						time_offset = 3.0;
					}
					else
					{
						Voice_Random ( leroy, other, &specific[12], 3);

						mem->flags |= MEMORY_ASSHOLE;
					}
					
					last_client_talk = level.time + 3 + time_offset;

					// Ridah, turn to face them, or make a gesture
					if (!infront( leroy, other ))
					{
						leroy->cast_info.avoid( leroy, other, true );
					}
					else
					{
						// make talking gesture if we're just standing around
						if (leroy->cast_info.currentmove == leroy->cast_info.move_stand)
							leroy->cast_info.talk(leroy);
					}

				}
				else
				{
					return false;
				}
			}
			
			return true;
		}


			
		
// Ridah, not used anymore
/*		
		if (self->name_index == NAME_LEROY && other->client)
		{
			{
				edict_t *betty;
				static int		rnd;
				float	time_offset;

				time_offset = 0.0;

				mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
				
				betty = EP_GetCharacter (NAME_BETTY);

				if (betty && betty->health > 0)
				{
					if (VectorDistance( self->s.origin, betty->s.origin ) < 256)
					{	// don't say anything just yet
//						self->last_talk_time = level.time;
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					// is not on the map anymore
					return false;
				}
				
				return true;
			}

		}
*/		
		break;

	case say_flashlight: 

		// We put it in here so it only occurs if we aren't already angry at them
		if (self->enemy != other)
		{
			cast_memory_t	*mem, *premem;

			// get the memory of this "other" character before we record the sighting
			premem = level.global_cast_memory[self->character_index][other->character_index];

			AI_RecordSighting(self, other, VectorDistance(self->s.origin, other->s.origin));

			// get the post sighting memory
			mem = level.global_cast_memory[self->character_index][other->character_index];

			// if we recorded a new sighting (or hadn't seen them in a while), and they are hostile..
			if (	(!premem || (premem->timestamp < (level.time - 10)))
				&&	(mem->flags & MEMORY_HOSTILE_ENEMY))
			{

//gi.dprintf ("%s: there he is!\n", self->name);	// Rafael: make sure you call the Voice routines, so they don't talk again for a bit

				return true;
			}

		}

		break;
// Ridah, this is a mess, we should just scan for names, and go from there
/*
	case say_alisthatyou: 
		AI_RecordSighting(self, other, VectorDistance(self->s.origin, other->s.origin));
		gi.dprintf ("%s: Al is that you?\n", self->classname);
			break;
	case say_behindthebarrel: break;
	case say_forabuck: break;
	case say_talktobetty: 
		if (self->name_index == NAME_LEROY)
		{
			Voice_Random(self, self->cast_info.talk_ent, neutral_converse_to_female, NUM_NEUTRAL_CONVERSE_TO_FEMALE);
			return true;
		}
		break;
*/
	}

	return false;
}

//............................................................................
// EP_Skidrow_ItemPickup
// Called whenever an item is picked up
 
void EP_Skidrow_ItemPickup ( edict_t *self, edict_t *other )
{
if (!Q_strcasecmp( self->classname, "item_coil" ))
{
	
		// other->client->pers.episode_flags |= EP_SKIDROW_GOT_COIL;
		// other->episode_flags |= EP_SKIDROW_GOT_COIL;

		EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_GOT_COIL);
}
	
// note to self
// for now they should just listen to the radio or wake up if they see the player
#if 0
	edict_t /* *Al,*/ *Bernie, *Arnold, *radio ;

	if (!Q_strcasecmp( self->classname, "item_coil" ))
	{
	
		other->episode_flags |= EP_SKIDROW_GOT_COIL;
		
		//Al = EP_GetCharacter( NAME_AL );
		Bernie = EP_GetCharacter( NAME_BERNIE );

		if (/*Al &&*/ Bernie)
		{
			Bernie->cast_info.aiflags |= AI_GOAL_RUN;		// So we run back to him
		
			// send him to Bernie

			//Al->goal_ent = Bernie;		// this will make him walk to Bernie
									// we then use the sight handler (above) to stop him
									// when he gets close, and send them all to the 2nd door
		}
		else
		{
			//Al = EP_GetCharacter( NAME_AL );
			Bernie = EP_GetCharacter( NAME_BERNIE );
			Arnold = EP_GetCharacter( NAME_ARNOLD );

			//if (Al)
			//	AI_MakeEnemy(Al, other, 0);
			if (Bernie)
				AI_MakeEnemy(Bernie, other, 0);
			if (Arnold)
				AI_MakeEnemy(Arnold, other, 0);

			// gi.dprintf ("CHEATER: AL, Arnold, and Bernie made hostile\n");
		}

		// kill the radio
		radio = G_Find( NULL, FOFS(classname), "misc_skidrow_radio" );
		if (!radio)
		{
			gi.dprintf( "EP_Skidrow_CastSight: Can't find radio to turn off!!\n");
		}
		else
		{
			radio->think = NULL;
			radio->nextthink = -1;
		}

	}
#endif
}


//............................................................................
// Special event-driven scripting. Usually called when a character reaches a
// path_corner_cast with the "scriptname" field set.

void EP_Skidrow_Script( edict_t *ent, char *scriptname )
{
	edict_t	*other;

//gi.dprintf( "Script '%s' called by %s\n", scriptname, ent->classname );

	switch (ent->name_index)
	{

	//================================================================================================
	// Test script using doors.bsp
	case NAME_JED:

		if (!strcmp( scriptname, "jed_script" ))
		{
			// Tell Jed to start evading Buster
			ent->enemy = EP_GetCharacter( NAME_BUSTER );
			AI_RecordSighting( ent, ent->enemy, VectorDistance( ent->s.origin, ent->enemy->s.origin ) );
			ent->cast_info.currentmove = ent->cast_info.move_evade;
		}

		break;

	case NAME_BUSTER:

		if (!strcmp( scriptname, "buster_script" ))
		{
			// Stand here looking at Jed

			other = EP_GetCharacter( NAME_JED );

			AI_RecordSighting( ent, other, VectorDistance( ent->s.origin, other->s.origin ) );
			ent->cast_info.avoid( ent, other, true );
			ent->cast_info.talk_ent = other;


			// find our mates and tell them to look at Jed also, but don't talk
			{
				int i;

				for (i=0; i<level.num_characters; i++)
				{
					if (!level.characters[i])
						continue;

					if (	(level.characters[i] != ent)
						&&	(level.characters[i]->cast_group == ent->cast_group)
						&&	(VectorDistance( level.characters[i]->s.origin, ent->s.origin ) < 256))
					{
						AI_RecordSighting( level.characters[i], other, VectorDistance( level.characters[i]->s.origin, other->s.origin ) );
						level.global_cast_memory[level.characters[i]->character_index][other->character_index]->flags |= MEMORY_NO_TALK;

						level.characters[i]->cast_info.talk_ent = other;

						level.characters[i]->cast_info.avoid( level.characters[i], other, true );
					}
				}

			}

		}

		break;


#define SR1_INTRO 1

#if SR1_INTRO	// out for demo
	//================================================================================================
	// SR1 intro

	case NAME_TOUGHGUY1:

		if (!strcmp( scriptname, "intro_script1" ))
		{	// say something, do talking motion
			ent->last_talk_time = level.time + 2;
			ent->cast_info.talk( ent );

			ent->cast_info.pausetime = level.time + 7;
		}

		else if (!strcmp( scriptname, "intro_script2" ))
		{	// tell the other guy to come with us
			
			ent->yaw_speed = 40;

			other = EP_GetCharacter( NAME_TOUGHGUY2 );

			other->last_talk_time = level.time + 2;
			other->cast_info.talk( ent );

			other->yaw_speed = 40;

			other->leader = ent;
//			ent->cast_info.aiflags |= AI_GOALENT_MANUAL_CLEAR;
			other->cast_info.pausetime = level.time + 2;

		}

		break;

	default:

		if (!strcmp( scriptname, "intro_player_script1" ))
		{	// go into death frame
			static mframe_t	frames[] = {
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
				NULL, 0, NULL,
			};
			static mmove_t	move = {725, 755, frames, NULL};

			other = EP_GetCharacter( NAME_INTROGUY1 );

			other->yaw_speed = 5;

			other->s.frame = move.firstframe;
			other->cast_info.currentmove = &move;

			other->s.model_parts[PART_GUN].invisible_objects = 0xFF;

			if (!(cl_parental_lock->value && !cl_parental_override->value))
			{
				// set pain skins
				other->s.model_parts[PART_HEAD].skinnum[0] =  other->s.model_parts[PART_HEAD].baseskin + 1;
				other->s.model_parts[PART_BODY].skinnum[0] =  other->s.model_parts[PART_BODY].baseskin + 1;
			}
		}

		else if (!strcmp( scriptname, "intro_camera3" ))
		{
			void intro_player_standup( edict_t *self );

			edict_t *thinker;

			thinker = G_Spawn();
			thinker->nextthink = level.time + 0.5;
			thinker->think = intro_player_standup;
		}

		else if (!strcmp( scriptname, "intro_player_script1a" ))
		{
			// delete the tough guys
			other = EP_GetCharacter( NAME_TOUGHGUY1 );
			G_FreeEdict( other );
			other = EP_GetCharacter( NAME_TOUGHGUY2 );
			G_FreeEdict( other );

		}

		else if (!strcmp( scriptname, "intro_player_script2" ))
		{	// we're at the corner, crouch down and grab the pipe
			void intro_player_pickup_pipe( edict_t *self );

			static mframe_t	frames[] = 
			{
				NULL,	  0.000, NULL,	// frame 0
				NULL,	  0.000, NULL,	// frame 1
				NULL,	  0.000, NULL,	// frame 2
				NULL,	  0.000, NULL,	// frame 3
			};
			static mmove_t	move = {570, 573, frames, intro_player_pickup_pipe};

			ent->yaw_speed = 40;

			// crouch down
			ent->cast_info.currentmove = &move;
			ent->s.frame = ent->cast_info.currentmove->firstframe;
			ent->maxs[2] = DUCKING_MAX_Z;


			// release the player from the camera
			other = NULL;
			while (other = G_Find( other, FOFS(classname), "misc_cutscene_trigger" ))
			{
				if (other->nextthink >= level.time && other->think)
				{
					other->wait = 2/FRAMETIME;
				}
			}
		}
		else if (!strcmp( scriptname, "intro_end" ))
		{	// end of intro

			other = EP_GetCharacter( NAME_INTROGUY1 );
			G_FreeEdict( other );

		}

		break;
#endif

	}


	// Alarm
	if (!strcmp( scriptname, "alarm" ))
	{
		// We need some assistance!

		edict_t	*marker;

		// find the 2nd door ambush marker, tell all 3 guys to move to it
		marker = G_Find( NULL, FOFS(classname), "misc_skidrow_ambush" );
		if (!marker)
		{
			gi.dprintf( "EP_Skidrow_Script: Can't find ambush marker!!\n");
		}
		else
		{
			edict_t *plyr;

			if (plyr = EP_GetCharacter( NAME_BERNIE ))
			{
				plyr->goal_ent = plyr->start_ent = marker;
				plyr->guard_ent = NULL;
				plyr->target = NULL;		// stop guarding the radio area/patrolling
			}

//			if (plyr = EP_GetCharacter( NAME_AL ))
//				plyr->goal_ent = marker;

			if (plyr = EP_GetCharacter( NAME_ARNOLD ))
			{
				plyr->goal_ent = marker;
				plyr->guard_ent = NULL;
				plyr->target = NULL;		// stop guarding the radio area/patrolling
			}

		}

		// kill the radio
		marker = G_Find( NULL, FOFS(classname), "misc_skidrow_radio" );
		if (marker)
		{
			G_FreeEdict( marker );
		}
	}

}


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#if SR1_INTRO	// out for demo

void intro_player_standup( edict_t *self )
{	// stand up
	edict_t	 *trav, *other;

	trav = G_Find( NULL, FOFS(targetname), "intro_player_corner1a" );

	other = EP_GetCharacter( NAME_INTROGUY1 );

	other->cast_info.currentmove = other->cast_info.move_stand_up;
	other->s.frame = other->cast_info.currentmove->firstframe;
	other->maxs[2] = other->cast_info.standing_max_z;

	other->last_talk_time = level.time;	// make talking jesture when standing

	// head for the corner in a few seconds
	other->goal_ent = trav;
	other->cast_info.goal_ent_pausetime = level.time + 2.5;		// pause for a bit

//			other->maxs[2] = DUCKING_MAX_Z;
}

void intro_player_turnaround( edict_t *self )
{
	edict_t *other;

	//self->owner->cast_info.currentmove = self->owner->cast_info.move_stand_up;
	//self->owner->maxs[2] = self->owner->cast_info.standing_max_z;

	// turn to face alley
	other = NULL;
	while (other = G_Find( other, FOFS(targetname), "intro_corner1" ))
	{
//		if (VectorDistance(self->owner->s.origin, other->s.origin) < 384)
		{
			self->owner->goal_ent = other;
//			self->owner->cast_info.goal_ent_pausetime = level.time + 0.5;
			self->owner->goal_ent->cast_info.aiflags |= AI_GOALENT_MANUAL_CLEAR;
			break;
		}
	}

	G_FreeEdict( self );
}

void intro_player_pickup_pipe( edict_t *self )
{
	edict_t *think;

	// show the pipe
	self->s.model_parts[PART_GUN].invisible_objects = 0x0;

//	self->cast_info.currentmove = self->cast_info.move_crstand;
	self->cast_info.currentmove = self->cast_info.move_stand_up;
	self->maxs[2] = self->cast_info.standing_max_z;

	think = G_Spawn();
	think->nextthink = level.time + 0.7;
	think->think = intro_player_turnaround;
	think->owner = self;
}
#endif

qboolean EP_Skidrow_ProcessMagicJ( edict_t *self, edict_t *other, cast_memory_t *mem )
{
	if (	(other->client)
		&&	(!(other->client->pers.holsteredweapon))
		&&	(mem->flags & MEMORY_AFRAID )
		&&	(other->client->pers.weapon) )
	{
		float	dist;

		dist = VectorDistance( self->s.origin, other->s.origin );

		// if running, don't say or do anything
		if (self->cast_info.currentmove->frame->aifunc == ai_run)
			return true;


		if (	(dist < AI_NOT_HOLSTERED_RANGE_1)
			&&	!(mem->flags & MEMORY_HOSTILE_ENEMY))
		
		{

			#define MAXCHOICES	8
	
			edict_t	*ent = NULL;
			int		num_choices = 0;
			edict_t	*choice[MAXCHOICES];
			int		rval;
			float	dist[MAXCHOICES];
			
			while(1)
			{
				ent = G_Find (ent, FOFS(classname), "misc_skidrow_afraid");
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
					// gi.sound(ent, CHAN_VOICE, gi.soundindex("actors/skidrow/magicj/fuckthat.wav"), 1, ATTN_NORM, 0);
					Voice_Specific( self, other, specific, 25 );

				choice[rval]->cast_info.aiflags |= AI_GOAL_RUN;
				self->cast_info.aiflags |= AI_RUN_LIKE_HELL;

				self->goal_ent = choice[rval];
				self->cast_info.aiflags |= AI_GOAL_IGNOREENEMY;

				self->cast_info.currentmove = self->cast_info.move_run;
			}
		}
		
		else if (dist < AI_NOT_HOLSTERED_RANGE_2)
		{
			#define	TIME_TO_COMPLY_OR_I_RUN		5.0
			
			if (!(mem->flags & MEMORY_HOSTILE_ENEMY))
			{
				if (	(level.time > mem->not_holstered_attack_time)
					&&	(level.time < (mem->not_holstered_attack_time+5)))
				{	
					// gi.dprintf ("stay away I'll fuck you up\n");
					
					if (!(self->cast_info.aiflags & AI_NO_TALK))
					{
						self->cast_info.aiflags |= AI_NO_TALK;

						if (rand()%3 == 0)
							Voice_Specific( self, other, specific, 23 );	// fuck you up
						else //if (rand()%3 == 1)
							Voice_Specific( self, other, specific, 24 );	// fuck that
//						else
//							Voice_Specific( self, other, specific, 25 );	// be back
					}

// Ridah, not sure what this was for, but it causes behavoural problem
//					if (self->groundentity)
//						self->cast_info.currentmove = self->cast_info.move_avoid_walk;
					
					if (ai_debug_memory->value)
					{
						gi.dprintf("AI_RecordSighting: is cowering!\n");
					}
				}
				else if (level.time > mem->not_holstered_attack_time)
				{

					if (!(other->client->pers.weapon->ammo))
						Voice_Specific( self, other, specific, 22 );	// put that pipe down
					else
						Voice_Random( self, other, m_backoff, NUM_BACKOFF );

					// give them some "time to comply"
					mem->not_holstered_attack_time = level.time + TIME_TO_COMPLY_OR_I_RUN;

					if (ai_debug_memory->value)
					{
						gi.dprintf("AI_RecordSighting: i'm about to run in %d seconds\n", (int) TIME_TO_COMPLY_OR_I_RUN);
					}

					// if we're standing around, turn to face them
					if (	(self->cast_info.currentmove->frame->aifunc == ai_stand)
						&&	(self->cast_info.move_avoid_walk && self->cast_info.move_avoid_crwalk))
					{
						self->cast_info.avoid( self, other, true );
					}

				}
			
			}
			
			// if we're standing around, turn to face them
			if (self->cast_info.currentmove->frame->aifunc == ai_stand)
			{
				vec3_t vec;

				VectorSubtract( other->s.origin, self->s.origin, vec );
				VectorNormalize( vec );
				self->ideal_yaw = vectoyaw( vec );

				M_ChangeYaw( self );
			}

			// evade?
			if (self->cast_info.currentmove->frame->aifunc == ai_stand && self->cast_info.move_stand_evade && (self->moral < MORAL_AGGRESSIVE))
			{
				self->cast_info.currentmove = self->cast_info.move_stand_evade;
				self->last_stand_evade = level.time;
			}
		}
/*
		else if (dist < AI_NOT_HOLSTERED_RANGE_3)
		{	// if walking, ignore, if running, turn to face them, ready for attack if they get within range

			if (VectorLength( other->velocity ) > 210)
			{	// running
				
				// if we're standing around, turn to face them
				if (self->cast_info.currentmove->frame->aifunc == ai_stand)
				{
					vec3_t vec;

					VectorSubtract( other->s.origin, self->s.origin, vec );
					VectorNormalize( vec );
					self->ideal_yaw = vectoyaw( vec );

					M_ChangeYaw( self );
				}

			}

		}
*/
		return true;
	}

	return false;
}

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Special Skidrow entities

//................................................
// Radio

/*QUAKED misc_skidrow_radio (.5 .5 1) (-16 -16 -24) (16 16 48)
Bernie and the guys will listen to this. After the radio has stopped,
they'll discuss the game for some time.

  "delay"	time to wait between starting to listen to the radio
  "wait"	time spent listening to the radio each time
  "speed"	time spent discussing the game afterwards
*/

/*QUAKED misc_skidrow_radio_repeater (.5 .5 1) (-16 -16 -24) (16 16 48)
Use to tag the speaker inside the warehouse
*/

void EP_Radio_On_First_Time (edict_t *self);

void radio_snd_think (edict_t *self)
{
	self->count++;

	if (self->count == 1)
	{
		gi.sound ( self, CHAN_VOICE, gi.soundindex ("world/cheerup.wav"), 1, ATTN_NORM, 0);	
		self->nextthink = level.time + 1.0;
	}
	else if (self->count == 2 || self->count == 3)
	{
		gi.sound ( self, CHAN_VOICE, gi.soundindex ("world/cheerhigh.wav"), 1, ATTN_NORM, 0);	
		self->nextthink = level.time + 6.0;
	}
	else if (self->count == 4)
	{
		gi.sound ( self, CHAN_VOICE, gi.soundindex ("world/cheerdown.wav"), 1, ATTN_NORM, 0);
		self->nextthink = level.time + 2.0;
	}
	else
		self->think = G_FreeEdict;
}

void Skidrow_Radio_Sound (edict_t *self)
{
	edict_t *radio_snd;

	radio_snd = G_Spawn ();
	radio_snd->think = radio_snd_think;
	radio_snd->nextthink = level.time + 0.1;
	radio_snd->count = 0;
}


void radio_loop_think (edict_t *self)
{
	gi.sound ( self, CHAN_VOICE, gi.soundindex ("world/cheerlow.wav"), 1, ATTN_NORM, 0);
	self->nextthink = level.time + 1.0;
}

void Skidrow_Radio_Loop (edict_t *self)
{
	edict_t	*radio_loop;

	radio_loop = G_Spawn ();
	radio_loop->think = radio_loop_think;
	radio_loop->nextthink = level.time + 1.0;
}

void EP_skidrow_radio_stop_discuss (edict_t *self)
{
	// self->think = EP_skidrow_radio_on;
	self->think = EP_Radio_On_First_Time;

	self->nextthink = level.time + self->delay;
	self->timestamp = self->nextthink + self->wait;		// set the time to stop playing
}

void EP_skidrow_radio_off (edict_t *self)
{
	edict_t	*Bernie/*, *Al*/, *Arnold;

	Bernie	= EP_GetCharacter( NAME_BERNIE );
	// Al		= EP_GetCharacter( NAME_AL );
	Arnold	= EP_GetCharacter( NAME_ARNOLD );

	// Ridah 5-8-99, modified this to prevent courtyard wierdness after touching reset

	if (Bernie)
	{
		if (Bernie->goal_ent == self)
		{
			Bernie->goal_ent = NULL;
			if (!Bernie->enemy)
				Bernie->cast_info.pausetime = level.time + self->speed;	// stick around for a bit
		}
		
		Bernie->cast_info.aiflags |= AI_TALK;
	}
/*
	if (Al && (Al->goal_ent == self))
	{
		Al->goal_ent = NULL;

		if (!Al->enemy)
			Al->cast_info.pausetime = level.time + self->speed;		// stick around for a bit
		
		Al->cast_info.aiflags |= AI_TALK;
	}
*/
	if (Arnold)
	{
		if (Arnold->goal_ent == self)
		{
			Arnold->goal_ent = NULL;
			if (!Arnold->enemy)
				Arnold->cast_info.pausetime = level.time + self->speed;		// stick around for a bit
		}
		
		Arnold->cast_info.aiflags |= AI_TALK;
	}

	self->think = EP_skidrow_radio_stop_discuss;
	self->nextthink = level.time + self->speed;
}

void EP_skidrow_radio_on (edict_t *self)
{
	edict_t	*Bernie/*, *Al*/, *Arnold;

	Bernie	= EP_GetCharacter( NAME_BERNIE );
	// Al		= EP_GetCharacter( NAME_AL );
	Arnold	= EP_GetCharacter( NAME_ARNOLD );


	if (	(Bernie)
		&&	!Bernie->enemy
		&&	(!Bernie->goal_ent || (Bernie->goal_ent->touch == path_corner_cast_touch))
		&&	(VectorDistance( Bernie->s.origin, self->s.origin ) < 1024))
	{
		Bernie->goal_ent = self;
		
		Bernie->cast_info.aiflags &= ~AI_TALK;		// don't talk while at radio

// Ridah, 5-8-99, we shouldn't need this anymore
	}
/*
	if (	(Al)
		&&	!Al->enemy
		&&	(!Al->goal_ent || (Al->goal_ent->touch == path_corner_cast_touch))
		&&	(VectorDistance( Al->s.origin, self->s.origin ) < 1024))
	{
		Al->goal_ent = self;
		
		Al->cast_info.aiflags &= ~AI_TALK;		// don't talk while at radio
	}
*/
	if (	(Arnold)
		&&	!Arnold->enemy
		&&	(!Arnold->goal_ent || (Arnold->goal_ent->touch == path_corner_cast_touch))
		&&	(VectorDistance( Arnold->s.origin, self->s.origin ) < 1024))
	{
		Arnold->goal_ent = self;
		
		Arnold->cast_info.aiflags &= ~AI_TALK;		// don't talk while at radio

// Ridah, 5-8-99, we shouldn't need this anymore
	}

	if (level.time > self->timestamp)
	{	// turn the radio off
		self->think = EP_skidrow_radio_off;
		self->nextthink = level.time + 0.1;
		return;
	}

	self->nextthink = level.time + 3;
/*
	Skidrow_Radio_Sound (self);
	
	{
		edict_t *repeater;

		repeater = G_Find ( self, FOFS(classname), "misc_skidrow_radio_repeater");
		
		if (repeater)
		  Skidrow_Radio_Sound (repeater);
	}
*/	
}

void EP_Radio_On_First_Time (edict_t *self)
{
	Skidrow_Radio_Sound (self);
/*	
	{
		edict_t *repeater;

		repeater = G_Find ( self, FOFS(classname), "misc_skidrow_radio_repeater");
		
		if (repeater)
		  Skidrow_Radio_Sound (repeater);
	}
*/	
	EP_skidrow_radio_on (self);

	self->think = EP_skidrow_radio_on;
}

void SP_misc_skidrow_radio_repeater (edict_t *self)
{
	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	gi.linkentity (self);
}

void SP_misc_skidrow_radio (edict_t *self)
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

	// self->think = EP_skidrow_radio_on;
	self->think = EP_Radio_On_First_Time;
	self->nextthink = level.time + self->delay;
	self->timestamp = self->nextthink + self->wait;		// set the time to stop playing

	self->cast_info.aiflags |= AI_GOALENT_MANUAL_CLEAR;		// don't clear it out when we get there
	self->cast_info.aiflags |= AI_GOAL_RUN;		// run to us

// just for testing we need a constant background sound for the radio
// self->s.sound = gi.soundindex ("world/baseball.wav");

	AI_Ent_droptofloor( self );

	Skidrow_Radio_Loop (self);
}


/*QUAKED misc_skidrow_ambush (.5 .5 1) (-16 -16 -24) (16 16 48)
Used to set ambush location for the 3 guards when the
player goes into the 2nd door.
*/

void SP_misc_skidrow_ambush (edict_t *self)
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

//==========================================================================================
//
// RESPONSES

// JOSEPH 23-MAR-99
void Resp_Lenny (edict_t *self, edict_t *other, response_t response)
{
	if (response == resp_yes)
	{
		Voice_Specific( self, other, player_answer, 1 );
		//Voice_Random( self, other, m_response, NUM_RESPONSE );
		Voice_Player_Specific (self, TT_POSITIVE);
	}
	else
	{
		Voice_Random( self, other, player_profanity_level1, NUM_PROFANITY_LEVEL1 );
		Voice_Player_Specific(self, TT_NEGATIVE);
	}

	self->response_ent = other;
	self->last_response_time = level.time;
	self->last_response = response;
}
// END JOSEPH


void Resp_MagicJ_GotDollar( edict_t *self, edict_t *other, response_t response )
{

	if (response == resp_yes)
	{
		Voice_Player_Specific(self, TT_YES);
		
		if (!(other->episode_flags & EP_SKIDROW_MAGICJ_GAVE_DOLLAR))
		{
			// have we really got a dollar to give?
			if (self->client->pers.currentcash >= 1)
			{
				Voice_Specific( self, other, specific, 5 );

				// give him the dollar
				
				self->client->pers.currentcash -= 1;
				other->currentcash += 1;

				other->episode_flags |= EP_SKIDROW_MAGICJ_GAVE_DOLLAR;

				// EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MAGICJ_GAVE_DOLLAR);
			}
			else
			{
				Voice_Specific( self, other, specific, 6 );
				// gi.cprintf( self, PRINT_HIGH, "You don't have a dollar to give.\n" );

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


void Resp_Rummy_GotWine ( edict_t *self, edict_t *other, response_t response )
{

	int     index;
	gitem_t *item;

	item = FindItem ("Whiskey");
	index = ITEM_INDEX (item);
			
	if (response == resp_yes)
	{
		Voice_Player_Specific(self, TT_YES);
		
		if (!(self->episode_flags & EP_SKIDROW_RUMMY_GAVE_WINE))
		{
			if (self->client->pers.inventory[index])
			{
				// gi.dprintf ("FIXME: heres your wine\n");
				Voice_Specific( self, other, player_whiskey, 0 );

				other->episode_flags |= EP_SKIDROW_RUMMY_GAVE_WINE;
				
				// EP_Skidrow_Register_EPFLAG (self, EP_SKIDROW_RUMMY_GAVE_WINE);
			}
			else
			{
				// gi.cprintf( self, PRINT_HIGH, "FIXME: You don't have any wine to give.\n" );
				
				Voice_Specific( self, other, player_whiskey, 1 );
				response = resp_no;
				
			}
		}
		else
		{
			// gi.cprintf( self, PRINT_HIGH, "FIXME: You don't have any wine to give.\n" );
			Voice_Specific( self, other, player_whiskey, 1 );
			response = resp_no;
		}
	}
	else if (response == resp_no)
	{
		//gi.cprintf( self, PRINT_HIGH, "FIXME: I aint go any drink to give.\n" );
		Voice_Specific( self, other, player_whiskey, 1 );
		Voice_Player_Specific(self, TT_NO);
	}

	// hack to get rummy to work
	other->cast_info.talk_ent = self;

	self->response_ent = other;
	self->last_response_time = level.time;
	self->last_response = response;

}

/*QUAKED misc_skidrow_afraid (.5 .5 1) (-16 -16 -24) (16 16 48)
used by actors to pick location where it is safer to run away from the player
*/

void SP_misc_skidrow_afraid (edict_t *self)
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


// Pull Alarm routines

void Pull_Alarm_Ring (edict_t *ent)
{
	edict_t			*Louie;	

	Louie = EP_GetCharacter( NAME_LOUIE );
	
	if ( Louie && ent->owner == Louie )
	{
		{
			edict_t	*entity = NULL;
			edict_t	*alarm = NULL;
				
			while(1)
			{
				entity = G_Find (NULL, FOFS(classname), "misc_alarm");
				if (!entity)
					break;
				if (VectorDistance( entity->s.origin, Louie->s.origin ) < 64)
				{
					alarm = entity;
					break;
				}
				
			}

			if (!alarm)
			{
				ent->nextthink = level.time + 0.1;
			}
			else 
			{
				Louie->cast_info.aiflags &= ~AI_GOAL_IGNOREENEMY;
				// Louie->cast_info.aiflags &= ~AI_GOAL_PULL_ALARM;
				alarm->use (alarm, Louie, Louie);
				G_FreeEdict(ent);
			}
		}
	}
}

void Pull_Alarm_Think (edict_t *ent)
{
	edict_t			*Louie;
	cast_memory_t	*mem;

	Louie = EP_GetCharacter( NAME_LOUIE );
	
	if ( Louie && ent->owner == Louie )
	{
		mem = level.global_cast_memory[ Louie->character_index ][ ent->enemy->character_index ];
		Louie->goal_ent = ent;
		ent->cast_info.aiflags |= AI_GOAL_RUN;	
		ent->nextthink = level.time + 0.1;
		ent->think = Pull_Alarm_Ring;
		return;
	}

	// the user must be dead so free it up
	G_FreeEdict (ent);

}
/*
edict_t *FindCastOrigin (edict_t *self)
{
	edict_t *ent = NULL;

	while(1)
	{
		ent = G_Find (ent, FOFS(classname), "cast_origin");
		if (!ent)
			break;
		if (ent->owner != self)
			continue;
		else 
			return ent;
	}

	return NULL;
}
*/
void EP_Skidrow_Reset( edict_t *self, edict_t *other )
{
	extern void AI_CreateCharacterMemory(edict_t *src, edict_t *dest);
	extern void AI_ReleaseCastMemory(edict_t *self, cast_memory_t *cast_memory);

	edict_t *Arnold, *Bernie;
	cast_memory_t	*mem;
	edict_t *Cast_Origin;

	if (!(other->client))
		return;

	Arnold = EP_GetCharacter( NAME_ARNOLD );
	Bernie = EP_GetCharacter( NAME_BERNIE );

	if (other->client && (other->client->pers.episode_flags & EP_SKIDROW_GOT_COIL))
		return;

	// both are still alive
	if (Arnold && Bernie)
	{

		// TBD:
		// actors need to go back to their start location
		if (Arnold && (mem = level.global_cast_memory[ Arnold->character_index ][ other->character_index ]))
		{

			// Ridah, 5-8-99, some modifications for courtyard problems..

			if (mem->memory_type == MEMORY_TYPE_ENEMY)
			{
				AI_ReleaseCastMemory( Arnold, Arnold->cast_info.enemy_memory );
				Arnold->cast_info.enemy_memory = NULL;
			}

// Ridah, 5-8-99, make it so we don't even remember the player
//				AI_CreateCharacterMemory (Arnold, other);

			// Ridah, DEMO: if they're currently in Louie's office, just spawn them back at the start pos
			if (ValidBoxAtLoc( Arnold->start_ent->s.origin, Arnold->mins, Arnold->maxs, Arnold, MASK_PLAYERSOLID ))
				VectorCopy( Arnold->start_ent->s.origin, Arnold->s.origin );
			else	// just run back there
				Arnold->start_ent->cast_info.aiflags |= AI_GOAL_RUN;

			Arnold->enemy = NULL;
			Cast_Origin = Arnold->start_ent;

			Arnold->goal_ent = Cast_Origin;
			Arnold->cast_info.currentmove = Arnold->cast_info.move_stand;
				
		}
		if (Bernie && (mem = level.global_cast_memory[ Bernie->character_index ][ other->character_index ]))
		{
			
			// Ridah, 5-8-99, some modifications for courtyard problems..

			if (mem->memory_type == MEMORY_TYPE_ENEMY)
			{
				AI_ReleaseCastMemory( Bernie, Bernie->cast_info.enemy_memory );
				Bernie->cast_info.enemy_memory = NULL;
			}

// Ridah, 5-8-99, make it so we don't even remember the player
//				AI_CreateCharacterMemory (Bernie, other);

			// Ridah, DEMO: if they're currently in Louie's office, just spawn them back at the start pos
			if (ValidBoxAtLoc( Bernie->start_ent->s.origin, Bernie->mins, Bernie->maxs, Bernie, MASK_PLAYERSOLID ))
				VectorCopy( Bernie->start_ent->s.origin, Bernie->s.origin );
			else	// just run back there
				Bernie->start_ent->cast_info.aiflags |= AI_GOAL_RUN;

			Bernie->enemy = NULL;
			Cast_Origin = Bernie->start_ent;

			Bernie->goal_ent = Cast_Origin;
			Bernie->cast_info.currentmove = Bernie->cast_info.move_stand;
				
		}
	}
}

// JOSEPH 17-MAR-99
int EP_skidrow_touch_motorcycle_that_needs_battery_to_start (edict_t *self, edict_t *trigger)
{
	
	
	// If the don't have the battery, then we don't get to go
	if (!(self->client->pers.inventory[ITEM_INDEX(FindItem("Battery"))]))
	{
		if (!(self->episode_flags & EP_SKIDROW_FOUND_BIKE))
		{
			gi.sound(self, CHAN_VOICE, gi.soundindex("scenaric/bikenobattery.wav"), 1, ATTN_NORM, 0);	
			EP_Skidrow_Register_EPFLAG (self, EP_SKIDROW_FOUND_BIKE);
		}		

		return 0;
	}

	// JOSEPH 5-JUN-99
	self->client->pers.inventory[ITEM_INDEX(FindItem("Battery"))] = 0;	
	// END JOSEPH

	// Trigger triggered
	G_UseTargets (trigger, self);

	// Delete old bike
	{	
		edict_t	*e;
		int		i;
		
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "props_motorcycle")))
			{
				G_FreeEdict(e);		
			}
		}
	}

	// New bike
	{
		edict_t	*moto = NULL;
		extern void SP_props_motorcycle_run (edict_t *self); 

		moto = G_Spawn();
	
		if (!moto)
			return 1;	
		
		SP_props_motorcycle_run(moto);	
	}
	
	// Do camera cut 

	// Delete trigger brush
	return 1;
}
// END JOSEPH

void Resp_Momo_GotMoney ( edict_t *self, edict_t *other, response_t response )
{
	cast_memory_t	*mem;
		
	if (self->episode_flags & EP_SKIDROW_MOMO_TOOK_MONEY)
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
qboolean ProcessMomo (edict_t *self, edict_t *other)			
{
	
	cast_memory_t	*mem;	

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];

	if (mem->flags & MEMORY_LASTWARNING)
	{
		Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (other->episode_flags & EP_SKIDROW_MOMO_TOOK_MONEY)
	{
		// Ridah, 5-8-99, we've already taken their money, so say one of the following..

		if (!(mem->flags & MEMORY_ASSHOLE))
			Voice_Random ( self, other, &momo_specific[12], 2);		// so what's it gonna be... in or out?
		else	// they've cussed us, don't act all happy to see them
			Voice_Random ( self, other, &momo_specific[13], 2);		// get the fuck out of my foyer

		return true;
	}

	if (!(other->episode_flags & EP_SKIDROW_MOMO_FIRST_TIME))
	{
		Voice_Specific (self, other, momo_specific, 0); // welcome.wav

//		mem->inc = 1;
		
//		other->episode_flags = other->client->pers.episode_flags |= EP_SKIDROW_MOMO_ASKED_MONEY;
//		mem->response = Resp_Momo_GotMoney;

		
		// other->episode_flags = other->client->pers.episode_flags |= EP_SKIDROW_MOMO_FIRST_TIME;
		EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MOMO_FIRST_TIME);

		return true;
	}

	// Ridah, 5-8-99, I changed this so it clears this flag in EP_CastSight() if Momo sees you after not having seen you for a while
	if (!(other->episode_flags & EP_SKIDROW_MOMO_ASKED_MONEY))
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

		// other->episode_flags = other->client->pers.episode_flags |= EP_SKIDROW_MOMO_ASKED_MONEY;

		EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MOMO_ASKED_MONEY);

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
				
				// other->episode_flags = other->client->pers.episode_flags |= EP_SKIDROW_MOMO_TOOK_MONEY;

				EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MOMO_TOOK_MONEY);

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
						if ((e->targetname) && (!strcmp(e->targetname, "bardoor_sr")))
						{
							// Unlock target door
							if (e->key == -1)
							{
								e->key = 0;	
								e->targetname = NULL;							
							}
						}
					}
					
					// other->episode_flags |= EP_SKIDROW_MOMO_TOOK_MONEY;
					// other->client->pers.episode_flags |= EP_SKIDROW_MOMO_TOOK_MONEY;

					EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_MOMO_TOOK_MONEY);
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
					mem->response = Resp_Momo_GotMoney;
				}

			}
		}
		else
		{
			Voice_Random (self, other, &momo_specific[12], 5); 

			if (momo_specific[12].last_played == level.time)
			{	// we just asked them if they wanna come in, so let them respond
				mem->response = Resp_Momo_GotMoney;
			}
		}

	}
			
	return true;
}
			
			
void EP_SkidrowFlags (edict_t *self)
{
	if (self->name_index == NAME_MOMO)
	{
		self->cast_info.aiflags |= AI_IMMORTAL;
		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
	}
}

/*UAKED immortal_hostility (.5 .5 1) (-16 -16 -24) (16 16 48)
	This is an entity that will let an immortal check for player
	hostility and take corresponding actions 

health = the distance to check for ei a health of 64 would have a 128 diameter
*/

#if 0
void immortal_hostile_think (edict_t *self)
{
	edict_t *player;
	vec3_t	vec;
	float	dist;

	player = &g_edicts[1];

	if (player->client->gun_noise)
	{

		VectorSubtract (self->s.origin, player->s.origin, vec);
		dist = VectorLength (vec);
	
		if (dist < self->health)
		{
			edict_t *dude;
			cast_memory_t	*mem;	

			{
				dude = G_PickTarget(self->target);	
				
				if (dude)
				{
					mem = level.global_cast_memory[ dude->character_index ][ player->character_index ];

					mem->flags |= MEMORY_LASTWARNING;
					// gi.dprintf ("%s heard the shot\n", dude->name);
				}
				else
					gi.dprintf ("player made gun noise in my detect zone!\n");
			}
		
		}
	}

	self->nextthink = level.time + 0.1;
}

void SP_immortal_hostility (edict_t *self)
{

	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs,  16,  16,  48);

	if (!(self->health))
	{
		gi.dprintf ("setting default radius of 128\n");
		self->health = 128;
	}

	self->think = immortal_hostile_think;
	self->nextthink = level.time + 0.1;
	
	AI_Ent_droptofloor( self );


}

#endif


/*QUAKED ep_skidrow_flag (.5 .5 0) ?
marks where the player can no longer fire his gun
*/

void ep_skidrow_flag_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{

	if (!(other->client))
		return;

	if (!(other->episode_flags & EP_SKIDROW_RATS_FIND))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_RATS_FIND);
		// EP_Skidrow_Register_EPFLAG (other, EP_SKIDROW_CUT_SCENE_TWO);
	}
	
}

void SP_ep_skidrow_flag ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ep_skidrow_flag_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);
	
}

/*
// Skidrow flags
#define	EP_SKIDROW_MAGICJ_ASKED_DOLLAR	0x00000001 //1
#define EP_SKIDROW_BETH_GIVES_HINT		0x00000002 //2
#define	EP_SKIDROW_AL_SAW_DEAD_LOUIE	0x00000004 //3
#define	EP_PAWNOMATIC_FIRST_TIME		0x00000008 //4
#define	EP_SKIDROW_GOT_COIL				0x00000010 //5
#define	EP_SKIDROW_MAGICJ_GAVE_DOLLAR	0x00000020 //6
#define	EP_SKIDROW_MOMO_ASKED_MONEY		0x00000040 //7
#define	EP_SKIDROW_MOMO_TOOK_MONEY		0x00000080 //8
#define	EP_SKIDROW_MOMO_FIRST_TIME		0x00000100 //9
#define EP_TALKED_TO_LENNY				0x00000200 //10
#define	EP_SKIDROW_MOMO_GAVE_MONEY		0x00000800 //11
#define	EP_BAR_FIRST_TIME				0x00001000 //12
#define EP_SKIDROW_LENNY_TOOK_WATCH		0x00002000 //13
#define	EP_SKIDROW_JOSEPH_WARNING_1		0x00004000 //16
#define EP_SKIDROW_JOSEPH_WARNING_2		0x00080000 //15
#define EP_SKIDROW_JOSEPH_WARNING_3		0x00100000 //16
#define EP_SKIDROW_RUMMY_GAVE_WINE		0x00200000 //17
#define EP_SKIDROW_RUMMY_ASKED_WINE		0x00400000 //18
#define	EP_SKIDROW_RATS_PISSED			0x00800000 //19
*/ 
#include "ep_log.h"

int	the_log_page = 0;

void EP_Skidrow_Player_Log (edict_t *self, int page)
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
	else if (the_log_page >= NUM_SKIDROW_PLAYER_LOG)
		the_log_page = 0;

	for (i=1; i<NUM_SKIDROW_PLAYER_LOG; i++)
	{
		if (self->client->pers.episode_flags & ep_skidrow_player_log[i].ep_flag)
			cnt++;

		if (cnt == the_log_page)
		{
			select = i;
			break;
		}
	}	

	if (!page || !the_log_page)
		for (i=0; i<NUM_SKIDROW_PLAYER_LOG; i++)
		{
			if (ep_skidrow_player_log[i].new_clue == true)
			{
				select = i;
				break;
			}
		}

	if (cnt == 0)
	{
		the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_skidrow_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcpy (game.helpmessage2, ep_skidrow_player_log[0].ep_text);
	}
	else
	{
		if (select == 0)
			the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_skidrow_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcat (game.helpmessage2, ep_skidrow_player_log[select].ep_text);
		if (page)
			gi.sound(self, CHAN_VOICE, gi.soundindex("world/pageturn.wav"), 1, ATTN_NONE, 0);
	}

	

}

void EP_Skidrow_Register_EPFLAG (edict_t *self, int ep_flag)
{
	if (self->client->pers.episode_flags & ep_flag)
		return;

	self->episode_flags = self->client->pers.episode_flags |= ep_flag;
		
	EP_Flash_Newflag (self, ep_flag);
}


void	EP_Skidrow_CheckMomo (edict_t *ent, cast_memory_t	*mem)
{
	if (ent->episode_flags & EP_SKIDROW_MOMO_ASKED_MONEY)
	 	mem->inc++;
				
}


qboolean EP_Skidrow_Flash_Newflag (edict_t *self, int ep_flag)
{
	int i;
	qboolean gotone = false;

	for (i=0; i<NUM_SKIDROW_PLAYER_LOG; i++)
	{
		if (ep_skidrow_player_log[i].ep_flag == ep_flag)
		{
			ep_skidrow_player_log[i].new_clue = true;
			gotone = true;
		}
		else
			ep_skidrow_player_log[i].new_clue = false;
	}

	return (gotone);
}
