
#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

char	stranger_str[] = "(Stranger)";

int	num_precached_voices = 0;

void Voice_Random_rc( edict_t *self, edict_t *other, voice_table_t *voice_table, int num_entries );
void Voice_Specific_rc( edict_t *self, edict_t *other, voice_table_t *voice_table, int entry );

void Voice_Random( edict_t *self, edict_t *other, voice_table_t *voice_table, int num_entries )
{
	int entry=-1, best_entry=-1, count=0;
	int	i;

	if (self->cast_info.aiflags & AI_NO_TALK)
		return;

	if (self->health <= 0)
		return;

	if ( !(self->client) )
	{
		if ( level.episode == EP_RADIOCITY && (self->gender == GENDER_MALE || self->gender == GENDER_FEMALE) )
		{
			Voice_Random_rc (self, other, voice_table, num_entries);
			return;
		}
	}

again:

	if (	!deathmatch->value
		&&	(other)
		&&	(other->last_talk_time > (level.time - 5))
		&&	(other->last_voice)
		&&	(other->last_voice->response_table == voice_table)
		&&	(other->last_voice->num_responses))
	{
		// we should pick a specific response
		i = (int)floor( random()*other->last_voice->num_responses );

		while ((entry < 0) || (voice_table[entry].last_played > 0.1))
		{
			entry = other->last_voice->responses[ i++ ];

			if ((best_entry < 0) || (voice_table[entry].last_played < voice_table[best_entry].last_played))
			{
				best_entry = entry;
			}
			else if (voice_table[ entry ].last_played > level.time)
			{	// still set from a previous level
				voice_table[ entry ].last_played = 0;
			}

			if (i >= other->last_voice->num_responses)
				i = 0;

			if (count++ > other->last_voice->num_responses)
				break;
		}

		entry = best_entry;

	}
	else	// not responding, just pick any non-response
	{

		entry = (int)floor( random()*num_entries );

		while (count++ < num_entries)
		{
			if (	(!voice_table[ entry ].response)
				&&	(self->last_voice != &voice_table[ entry ])
				&&	(	(best_entry < 0)
					 ||	(voice_table[ entry ].last_played < voice_table[ best_entry ].last_played)))
			{
				best_entry = entry;
			}
			else if (voice_table[ entry ].last_played > level.time)
			{	// still set from a previous level
				voice_table[ entry ].last_played = 0;
			}

			entry++;

			if (entry >= num_entries)
				entry = 0;
		}

		if (best_entry < 0)
			best_entry = (int)floor( random()*num_entries );

		entry = best_entry;
	}

	// HACK, don't say "Fuck me, Freddy is it you?" to the bitch (we need a better way to handle things like this)
	if (	self->client
		&&	other
		&&	other->gender == GENDER_FEMALE
		&&	voice_table == neutral_talk_player
		&&	entry == 4)
	{
		voice_table[ entry ].last_played = level.time;
		entry=-1;
		best_entry=-1;
		count=0;
		goto again;
	}

	// the popeye hack
	if (	self->name_index == NAME_POPEYE
		&&  (	voice_table == fightsounds
			||	voice_table == grunting 
			||  voice_table == m_backoff )
		)
	{
		voice_table = sy_popeye;
		entry = 19 + (rand()%3);
	}

	if (voice_table[ entry ].filename)
	{
		if (!voice_table[ entry ].last_played || (voice_table[ entry ].last_played > level.time)
			|| (voice_table[ entry ].gameinc_soundindex != gameinc))
		{
			voice_table[ entry ].soundindex = 0;
		}

		if (deathmatch->value || VectorDistance( g_edicts[1].s.origin, self->s.origin ) < 1024)
		{
			if ((other && other->client) || self->client)
				gi.sound( self, CHAN_VOICE | CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 1.0, 1, 0 );
			else
				gi.sound( self, CHAN_VOICE | CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 0.2, 1, 0 );
			
			voice_table[ entry ].gameinc_soundindex = gameinc;

			if (cl_captions->value && strlen(voice_table[entry].text) > 0)
			{
				if (cl_parental_lock->value && !cl_parental_override->value)
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text2);
					else if (other && other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text2);
				}
				else
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text);
					else if (other && other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text);
				}
			}
		}
	}
	else
	{
		if (cl_parental_lock->value && !cl_parental_override->value)
			gi.dprintf("VOICE TODO: %s\n", voice_table[ entry ].text2);
		else
			gi.dprintf("VOICE TODO: %s\n", voice_table[ entry ].text);
	}

	if (self->client || (other && other->client))
	{
		if (other && other->client)	// tell this client to talk back to us next time they chat
			other->cast_info.talk_ent = self;

		self->cast_info.talk_ent = other;

		last_client_talk = level.time;
	}

	self->last_voice = &( voice_table[ entry ] );
	voice_table[ entry ].last_played = level.time;

	self->last_talk_time = level.time;

// JOSEPH 2-FEB-99 
	if (other && other->client)
	{
		other->client->ps.stats[STAT_HUD_ENEMY_TALK] = voice_table[ entry ].type;
		other->client->hud_enemy_talk_time = level.time + 2.0;
	}
	// END JOSEPH

}

void Voice_Specific( edict_t *self, edict_t *other, voice_table_t *voice_table, int entry )
{

	if (self->cast_info.aiflags & AI_NO_TALK)
		return;

	if (self->health <= 0)
		return;

	if (!(self->client))
	{
		if (level.episode == EP_RADIOCITY && (self->gender == GENDER_MALE || self->gender == GENDER_FEMALE))
		{
			Voice_Specific_rc (self, other, voice_table, entry);
			return;
		}
	}

	// JOSEPH 2-FEB-99 
	if (other && other->client)
	{
		other->client->ps.stats[STAT_HUD_ENEMY_TALK] = voice_table[ entry ].type;
		other->client->hud_enemy_talk_time = level.time + 2.0;
	}
	// END JOSEPH
	
	if (voice_table[ entry ].filename)
	{
		if (!voice_table[ entry ].last_played || (voice_table[ entry ].last_played > level.time)
			|| (voice_table[ entry ].gameinc_soundindex != gameinc))
		{
			voice_table[ entry ].soundindex = 0;
		}

		if (VectorDistance( g_edicts[1].s.origin, self->s.origin ) < 1024)
		{
			if ((other && other->client) || self->client)
				gi.sound( self, CHAN_VOICE + CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 1.0, 1, 0 );
			else
				gi.sound( self, CHAN_VOICE + CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 0.2, 1, 0 );

			voice_table[ entry ].gameinc_soundindex = gameinc;

			if (cl_captions->value && strlen(voice_table[entry].text) > 0)
			{
				if (cl_parental_lock->value && !cl_parental_override->value)
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text2);
					else if (other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text2);
				}
				else
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text);
					else if (other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text);
				}
			}
	
		}
	}
	else
	{
		if (cl_parental_lock->value && !cl_parental_override->value)
			gi.dprintf("VOICE: %s\n", voice_table[ entry ].text2);
		else
			gi.dprintf("VOICE: %s\n", voice_table[ entry ].text);
	}

	if (self->client || (other && other->client))
	{
		if (other && other->client)	// tell this client to talk back to us next time they chat
			other->cast_info.talk_ent = self;

		last_client_talk = level.time;
	}

	self->last_voice = &( voice_table[ entry ] );
	voice_table[ entry ].last_played = level.time;

	self->last_talk_time = level.time;
}

// JOSEPH 13-FEB-99
void Voice_Player_Specific( edict_t *player, int entry )
{

	if (player->health <= 0)
		return;

	// JOSEPH 2-FEB-99 
	if (player && player->client)
	{
		player->client->ps.stats[STAT_HUD_SELF_TALK] = entry;
		player->client->hud_self_talk_time = level.time + 2.0;
	}
	// END JOSEPH

	last_client_talk = level.time;
	player->last_talk_time = level.time;
}
// END JOSEPH


//////////////////////////////////////
// radio city voice_routines
//////////////////////////////////////

void Voice_Random_rc( edict_t *self, edict_t *other, voice_table_t *voice_table, int num_entries )
{
	int entry=-1, best_entry=-1, count=0;
	int	i;
	int offset;

	if (self->cast_info.aiflags & AI_NO_TALK)
		return;

	if (self->health <= 0)
		return;

	{
		// voice_table conversion
		if (self->name_index == NAME_KINGPIN)
			voice_table = voice_table;
		else if (self->name_index == NAME_BLUNT)
			voice_table = voice_table;
		else if (self->name_index == NAME_NICKIBLANCO)
			voice_table = voice_table;
		else if (self->name_index == NAME_BUTCH)
			voice_table = voice_table;
		else if (self->name_index == NAME_PATRICK)
			voice_table = voice_table;
		else if (self->name_index == NAME_MOMO)
			voice_table = voice_table;
		else if (self->name_index == NAME_SCALPER)
			voice_table = voice_table;
		else if (self->gender == GENDER_MALE)
		{
			qboolean is_rc = true;
			
			if (voice_table >= rc_joker && voice_table <= &rc_joker[9])
				voice_table = voice_table;
			else if (self->cast_group == 1)
				voice_table = voice_table;
			else if (voice_table >= neutral_talk && voice_table <= &neutral_talk[15])
			{
				offset = voice_table - neutral_talk;
				voice_table = rc_neutral_talk + offset;
			}
			else if (voice_table >= neutral_asshole_talk && voice_table <= &neutral_asshole_talk[1])
			{
				offset = voice_table - neutral_talk;
				voice_table = rc_neutral_asshole_talk + offset;
			}
			else if (voice_table >= neutral_talk_player && voice_table <= &neutral_talk_player[9])
			{
				offset = voice_table - neutral_talk_player;
				voice_table = rc_neutral_talk_player + offset;
			}
			else if (voice_table >= neutral_converse && voice_table <= &neutral_converse[19])
			{
				offset = voice_table - neutral_converse;
				voice_table = rc_neutral_converse + offset;
			}
			else if (voice_table >= neutral_converse_to_female && voice_table <= &neutral_converse_to_female[10])
			{
				offset = voice_table - neutral_converse_to_female;
				voice_table = rc_neutral_converse_to_female + offset;
			}
			else if (voice_table >= profanity_level1 && voice_table <= &profanity_level1[10])
			{
				offset = voice_table - profanity_level1;
				voice_table = rc_profanity_level1 + offset;
			}
			else if (voice_table >= profanity_level2 && voice_table <= &profanity_level2[16])
			{
				offset = voice_table - profanity_level2;
				voice_table = rc_profanity_level2 + offset;
			}
			else if (voice_table >= profanity_level3 && voice_table <= &profanity_level3[1])
			{
				offset = voice_table - profanity_level3;
				voice_table = rc_profanity_level3 + offset;
			}
			else if (voice_table >= friendlycombat && voice_table <= &friendlycombat[4])
			{
				offset = voice_table - friendlycombat;
				voice_table = rc_friendlycombat + offset;
			}
			else if (voice_table >= friendlypain && voice_table <= &friendlypain[1])
			{
				offset = voice_table - friendlypain;
				voice_table = rc_friendlypain + offset;
			}
			else if (voice_table >= friendlyhurt && voice_table <= &friendlyhurt[1])
			{
				offset = voice_table - friendlyhurt;
				voice_table = rc_friendlyhurt + offset;
			}
			else if (voice_table >= fightsounds && voice_table <= &fightsounds[9])
			{
				offset = voice_table - fightsounds;
				voice_table = rc_fightsounds + offset;
			}
			else if (voice_table >= specific && voice_table <= &specific[29])
			{
				offset = voice_table - specific;
				voice_table = rc_specific + offset;
			}
			else if (voice_table >= m_backoff && voice_table <= &m_backoff[2])
			{
				offset = voice_table - m_backoff;
				voice_table = rc_m_backoff + offset;
			}
			else if (voice_table >= male_specific && voice_table <= &male_specific[12])
			{
				offset = voice_table - male_specific;
				voice_table = rc_male_specific + offset;
			}
			else if (voice_table >= grunting && voice_table <= &grunting[4])
			{
				offset = voice_table - grunting;
				voice_table = rc_grunting + offset;
			}
			else
			{
				gi.dprintf ("ERROR: Random missing conversion for male %s\n", voice_table[0].text);
				return;
			}
			
		}
		else if (self->gender == GENDER_FEMALE)
		{
			if (self->name_index == NAME_LOLA)
				voice_table = voice_table;
			else if (voice_table >= f_neutral_talk && voice_table <= &f_neutral_talk[15])
			{
				offset = voice_table - f_neutral_talk;
				voice_table = rc_f_neutral_talk + offset;
			}
			else if (voice_table >= f_neutral_asshole_talk && voice_table <= &f_neutral_asshole_talk[4])
			{
				offset = voice_table - f_neutral_asshole_talk;
				voice_table = rc_f_neutral_asshole_talk + offset;
			}
			else if (voice_table >= f_neutral_talk_player && voice_table <= &f_neutral_talk_player[3])
			{
				offset = voice_table - f_neutral_talk_player;
				voice_table = rc_f_neutral_talk_player + offset;
			}
			else if (voice_table >= f_neutral_converse && voice_table <= &f_neutral_converse[15])
			{
				offset = voice_table - f_neutral_converse;
				voice_table = rc_f_neutral_converse + offset;
			}
			else if (voice_table >= f_profanity_level1 && voice_table <= &f_profanity_level1[4])
			{
				offset = voice_table - f_profanity_level1;
				voice_table = rc_f_profanity_level1 + offset;
			}
			else if (voice_table >= f_profanity_level2 && voice_table <= &f_profanity_level2[3])
			{
				offset = voice_table - f_profanity_level2;
				voice_table = rc_f_profanity_level2 + offset;
			}
			else if (voice_table >= f_profanity_level3 && voice_table <= &f_profanity_level3[2])
			{
				offset = voice_table - f_profanity_level3;
				voice_table = rc_f_profanity_level3 + offset;
			}
			else if (voice_table >= f_fightsounds && voice_table <= &f_fightsounds[7])
			{
				offset = voice_table - f_fightsounds;
				voice_table = rc_f_fightsounds + offset;
			}
			else if (voice_table >= f_specific && voice_table <= &f_specific[3])
			{
				offset = voice_table - f_specific;
				voice_table = rc_f_specific + offset;
			}
			else if (voice_table >= f_backoff && voice_table <= &f_backoff[3])
			{
				offset = voice_table - f_backoff;
				voice_table = rc_f_backoff + offset;
			}
			else if (voice_table >= female_specific && voice_table <= &female_specific[8])
			{
				offset = voice_table - female_specific;
				voice_table = rc_female_specific + offset;
			}
			else if (voice_table >= f_grunting && voice_table <= &f_grunting[4])
			{
				offset = voice_table - f_grunting;
				voice_table = rc_f_grunting + offset;
			}
			else
			{
				gi.dprintf ("ERROR: Random missing conversion for female %s\n", voice_table[0].text);
				return;
			}
		}

	}

again:

	if (	(other)
		&&	(other->last_talk_time > (level.time - 5))
		&&	(other->last_voice)
		&&	(other->last_voice->response_table == voice_table)
		&&	(other->last_voice->num_responses))
	{
		// we should pick a specific response
		i = (int)floor( random()*other->last_voice->num_responses );

		while ((entry < 0) || (voice_table[entry].last_played > 0.1))
		{
			entry = other->last_voice->responses[ i++ ];

			if ((best_entry < 0) || (voice_table[entry].last_played < voice_table[best_entry].last_played))
			{
				best_entry = entry;
			}
			else if (voice_table[ entry ].last_played > level.time)
			{	// still set from a previous level
				voice_table[ entry ].last_played = 0;
			}

			if (i >= other->last_voice->num_responses)
				i = 0;

			if (count++ > other->last_voice->num_responses)
				break;
		}

		entry = best_entry;

	}
	else	// not responding, just pick any non-response
	{

		entry = (int)floor( random()*num_entries );

		while (count++ < num_entries)
		{
			if (	(!voice_table[ entry ].response)
				&&	(self->last_voice != &voice_table[ entry ])
				&&	(	(best_entry < 0)
					 ||	(voice_table[ entry ].last_played < voice_table[ best_entry ].last_played)))
			{
				best_entry = entry;
			}
			else if (voice_table[ entry ].last_played > level.time)
			{	// still set from a previous level
				voice_table[ entry ].last_played = 0;
			}

			entry++;

			if (entry >= num_entries)
				entry = 0;
		}

		if (best_entry < 0)
			best_entry = (int)floor( random()*num_entries );

		entry = best_entry;
	}

	// HACK, don't say "Fuck me, Freddy is it you?" to the bitch (we need a better way to handle things like this)
	if (	self->client
		&&	other
		&&	other->gender == GENDER_FEMALE
		&&	voice_table == neutral_talk_player
		&&	entry == 4)
	{
		voice_table[ entry ].last_played = level.time;
		entry=-1;
		best_entry=-1;
		count=0;
		goto again;
	}

	// the popeye hack
	if (	self->name_index == NAME_POPEYE
		&&  (	voice_table == fightsounds
			||	voice_table == grunting 
			||  voice_table == m_backoff )
		)
	{
		voice_table = sy_popeye;
		entry = 19 + (rand()%3);
	}

	if (voice_table[ entry ].filename)
	{
		if (!voice_table[ entry ].last_played || (voice_table[ entry ].last_played > level.time)
			|| (voice_table[ entry ].gameinc_soundindex != gameinc))
		{
			voice_table[ entry ].soundindex = 0;
		}

		if (VectorDistance( g_edicts[1].s.origin, self->s.origin ) < 1024)
		{
			if ((other && other->client) || self->client)
				gi.sound( self, CHAN_VOICE | CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 1.0, 1, 0 );
			else
				gi.sound( self, CHAN_VOICE | CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 0.2, 1, 0 );
			
			voice_table[ entry ].gameinc_soundindex = gameinc;

			if (cl_captions->value && strlen(voice_table[entry].text) > 0)
			{
				if (cl_parental_lock->value && !cl_parental_override->value)
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text2);
					else if (other && other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text2);
				}
				else
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text);
					else if (other && other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text);
				}
			}
		}
	}
	else
	{
		if (cl_parental_lock->value && !cl_parental_override->value)
			gi.dprintf("VOICE TODO: %s\n", voice_table[ entry ].text2);
		else
			gi.dprintf("VOICE TODO: %s\n", voice_table[ entry ].text);
	}

	if (self->client || (other && other->client))
	{
		if (other && other->client)	// tell this client to talk back to us next time they chat
			other->cast_info.talk_ent = self;

		self->cast_info.talk_ent = other;

		last_client_talk = level.time;
	}

	self->last_voice = &( voice_table[ entry ] );
	voice_table[ entry ].last_played = level.time;

	self->last_talk_time = level.time;

// JOSEPH 2-FEB-99 
	if (other && other->client)
	{
		other->client->ps.stats[STAT_HUD_ENEMY_TALK] = voice_table[ entry ].type;
		other->client->hud_enemy_talk_time = level.time + 2.0;
	}
	// END JOSEPH

}

void Voice_Specific_rc( edict_t *self, edict_t *other, voice_table_t *voice_table, int entry )
{

	if (self->cast_info.aiflags & AI_NO_TALK)
		return;

	if (self->health <= 0)
		return;

	{
		// voice_table conversion
		if (self->name_index == NAME_KINGPIN)
			voice_table = voice_table;
		else if (self->name_index == NAME_BLUNT)
			voice_table = voice_table;
		else if (self->name_index == NAME_NICKIBLANCO)
			voice_table = voice_table;
		else if (self->name_index == NAME_BUTCH)
			voice_table = voice_table;
		else if (self->name_index == NAME_PATRICK)
			voice_table = voice_table;
		else if (self->name_index == NAME_MOMO)
			voice_table = voice_table;
		else if (self->name_index == NAME_SCALPER)
			voice_table = voice_table;
		else if (self->gender == GENDER_MALE)
		{
			if (voice_table == rc_joker)
				voice_table = voice_table;
			else if (self->cast_group == 1)
				voice_table = voice_table;
			else if (voice_table == neutral_talk)
				voice_table = rc_neutral_talk;
			else if (voice_table == neutral_asshole_talk)
				voice_table = rc_neutral_asshole_talk;
			else if (voice_table == neutral_talk_player)
				voice_table = rc_neutral_talk_player;
			else if (voice_table == neutral_converse)
				voice_table = rc_neutral_converse;
			else if (voice_table == neutral_converse_to_female)
				voice_table = rc_neutral_converse_to_female;
			else if (voice_table == profanity_level1)
				voice_table = rc_profanity_level1;
			else if (voice_table == profanity_level2)
				voice_table = rc_profanity_level2;
			else if (voice_table == profanity_level3)
				voice_table = rc_profanity_level3;
			else if (voice_table == friendlycombat)
				voice_table = rc_friendlycombat;
			else if (voice_table == friendlypain)
				voice_table = rc_friendlypain;
			else if (voice_table == friendlyhurt)
				voice_table = rc_friendlyhurt;
			else if (voice_table == fightsounds)
				voice_table = rc_fightsounds;
			else if (voice_table == specific)
				voice_table = rc_specific;
			else if (voice_table == m_backoff)
				voice_table = rc_m_backoff;
			else if (voice_table == male_specific)
				voice_table = rc_male_specific;
			else if (voice_table == grunting)
				voice_table = rc_grunting;
			else
			{
				gi.dprintf ("ERROR: Specific missing voice table conversion for %s", voice_table[0].text);
				return;
			}
		}
		else if (self->gender == GENDER_FEMALE)
		{
			if (self->name_index == NAME_LOLA)
				voice_table = voice_table;
			else if (voice_table == f_neutral_talk)
				voice_table = rc_f_neutral_talk;
			else if (voice_table == f_neutral_asshole_talk)
				voice_table = rc_f_neutral_asshole_talk;
			else if (voice_table == f_neutral_talk_player)
				voice_table = rc_f_neutral_talk_player;
			else if (voice_table == f_neutral_converse)
				voice_table = rc_f_neutral_converse;
			else if (voice_table == f_profanity_level1)
				voice_table = rc_f_profanity_level1;
			else if (voice_table == f_profanity_level2)
				voice_table = rc_f_profanity_level2;
			else if (voice_table == f_profanity_level3)
				voice_table = rc_f_profanity_level3;
			else if (voice_table == f_fightsounds)
				voice_table = rc_f_fightsounds;
			else if (voice_table == f_specific)
				voice_table = rc_f_specific;
			else if (voice_table == f_backoff)
				voice_table = rc_f_backoff;
			else if (voice_table == female_specific)
				voice_table = rc_female_specific;
			else if (voice_table == f_grunting)
				voice_table = rc_f_grunting;
			else
			{
				gi.dprintf ("ERROR: Specific missing voice table conversion for %s", voice_table[0].text);
				return;
			}
		}

	}
	// JOSEPH 2-FEB-99 
	if (other && other->client)
	{
		other->client->ps.stats[STAT_HUD_ENEMY_TALK] = voice_table[ entry ].type;
		other->client->hud_enemy_talk_time = level.time + 2.0;
	}
	// END JOSEPH
	
	if (voice_table[ entry ].filename)
	{
		if (!voice_table[ entry ].last_played || (voice_table[ entry ].last_played > level.time)
			|| (voice_table[ entry ].gameinc_soundindex != gameinc))
		{
			voice_table[ entry ].soundindex = 0;
		}

		if (VectorDistance( g_edicts[1].s.origin, self->s.origin ) < 1024)
		{
			if ((other && other->client) || self->client)
				gi.sound( self, CHAN_VOICE + CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 1.0, 1, 0 );
			else
				gi.sound( self, CHAN_VOICE + CHAN_RELIABLE, (voice_table[ entry ].soundindex ? voice_table[ entry ].soundindex - 1 : (voice_table[ entry ].soundindex = 1 + gi.soundindex ( voice_table[ entry ].filename )) - 1 ), 0.2, 1, 0 );

			voice_table[ entry ].gameinc_soundindex = gameinc;

			if (cl_captions->value && strlen(voice_table[entry].text) > 0)
			{
				if (cl_parental_lock->value && !cl_parental_override->value)
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text2);
					else if (other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text2);
				}
				else
				{
					if (self->client)
						gi.dprintf ("player : %s\n", voice_table[entry].text);
					else if (other->client)		// Ridah, 5-8-99, had to do this otherwise too much text comes up, and you can't see which of it's yours
						gi.dprintf ("%s : %s\n", self->name ? self->name : stranger_str, voice_table[entry].text);
				}
			}
	
		}
	}
	else
	{
		if (cl_parental_lock->value && !cl_parental_override->value)
			gi.dprintf("VOICE: %s\n", voice_table[ entry ].text2);
		else
			gi.dprintf("VOICE: %s\n", voice_table[ entry ].text);
	}

	if (self->client || (other && other->client))
	{
		if (other && other->client)	// tell this client to talk back to us next time they chat
			other->cast_info.talk_ent = self;

		last_client_talk = level.time;
	}

	self->last_voice = &( voice_table[ entry ] );
	voice_table[ entry ].last_played = level.time;

	self->last_talk_time = level.time;
}
