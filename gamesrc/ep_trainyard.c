/******************************************************************************

  TRAINYARD - Episode specific code

*******************************************************************************/

#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

void misc_ty_afraid_think (edict_t *self);

qboolean EP_Trainyard_CastSight ( edict_t *self, edict_t *other, cast_memory_t *mem )
{

	return false;
}

qboolean EP_Trainyard_CastUse (edict_t *self, edict_t *other, edict_t *activator)
{
	return false;
}

qboolean EP_Trainyard_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{
	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
	
	switch (saywhat)
	{
	
	case say_neutral:

		if (self->name_index == NAME_LUKE && other->client)
		{
			if (!(other->episode_flags & EP_TY_LUKE_CLUE1))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_TY_LUKE_CLUE1);
				EP_Skidrow_Register_EPFLAG (other, EP_TY_TAKETHESEWER);
				Voice_Specific (self, other, ty_luke, 0);
			}
			else if (!(other->episode_flags & EP_TY_LUKE_CLUE2))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_TY_LUKE_CLUE2);
				Voice_Specific (self, other, ty_luke, 1);
			}
			else
				Voice_Random (self, other, &ty_luke[2], 4); 

			return true;
			
		}
		
		if (self->name_index == NAME_HANN && other->client)
		{
			if (!(other->episode_flags & EP_TY_HANN_CLUE1))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_TY_HANN_CLUE1);
				EP_Skidrow_Register_EPFLAG (other, EP_TY_TAKETHESEWER);
				Voice_Specific (self, other, ty_hann, 0);
			}
			else if (!(other->episode_flags & EP_TY_HANN_CLUE2))
			{
				EP_Skidrow_Register_EPFLAG (other, EP_TY_HANN_CLUE2);
				Voice_Specific (self, other, ty_hann, 1);
			}
			else
				Voice_Random (self, other, &ty_hann[2], 4); 

			return true;
			
		}	
		return false;

		break;
	case say_hostile:
		
		if (self->name_index == NAME_LUKE && other->client)
		{
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
			
				Voice_Random (self, other, &ty_luke[2], 4);

				return true;
			}
			else
			{
				// just do a random curse at the player
				Voice_Random (self, other, &ty_luke[6], 3);	
				return true;
			}
		}
		
		if (self->name_index == NAME_HANN && other->client)
		{
			if (other->client->ps.stats[STAT_HUD_SELF_TALK] == TT_POSITIVE)
			{
				mem = level.global_cast_memory [self->character_index][other->character_index];
				mem->flags &= ~MEMORY_ASSHOLE;
			
				Voice_Random (self, other, &ty_hann[2], 4);

				return true;
			}
			else
			{
				// just do a random curse at the player
				Voice_Random (self, other, &ty_hann[6], 3);	
				return true;
			}
		}
		
		return false;
		
		break;
	}

	return false;
}

void EP_Trainyard_ItemPickup ( edict_t *self, edict_t *other )
{

}

void EP_Trainyard_Script( edict_t *ent, char *scriptname )
{

}

int	EP_Trainyard_HiredGuysFlags (edict_t *player, edict_t *self)
{
	return (1);
}

void EP_TrainyardFlags (edict_t *self)
{

}

qboolean EP_Trainyard_DoKey (edict_t *self, edict_t *other)
{
	return false;
}

void EP_Trainyard_Check_DoKey (edict_t *self, edict_t *ent)
{

}

void EP_Trainyard_ReachedDoKey (edict_t *self)
{

}

void EP_Trainyard_EndDoKey (edict_t *self)
{

}

qboolean EP_Trainyard_UnlockDoorFlag (edict_t *ent)
{
	return false;
}

void EP_Trainyard_HiredGuysRegisterFlags (edict_t *ent, edict_t *other)
{

}


extern mmove_t	punk_move_walk_dokey;
extern mmove_t	punk_move_crch_dokey;

extern mmove_t  runt_move_walk_dokey;
extern mmove_t	runt_move_crch_dokey;

extern mmove_t	bitch_move_walk_dokey;


/*QUAKED misc_ty_afraid (.5 .5 1) (-16 -16 -24) (16 16 48)
used as the location mo will run to before larry and curly attack him
*/
	 
void misc_ty_afraid_think (edict_t *self)
{
	
}

void SP_misc_ty_afraid (edict_t *self)
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

/*QUAKED ai_ty_mo_boundry (.5 .5 1) ?
touching this brush will cause mo larry and curly to attack
*/

void ai_mo_boundry_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
//	vec3_t	vec;

	// if (!(other->svflags & SVF_MONSTER) && !(other->client))
	if (!(other->client))
		return;
	
}

void SP_ty_mo_boundry ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_mo_boundry_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}

/*QUAKED ai_ty_fuseblown (.5 .5 1) ?
This will set the EP_TY_FUSEBLOWN flag
*/

void ai_ty_fuseblown_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!(other->client))
		return;

	if (!(other->episode_flags & EP_TY_FUSEBLOWN))
	{
		EP_Skidrow_Register_EPFLAG (other, EP_TY_FUSEBLOWN);
		gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/need_fuse.wav"), 1, ATTN_NORM, 0);
	}
	// FIXME
	// we need to play a wav file
	
}

void SP_ty_fuseblown ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_ty_fuseblown_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}

/*QUAKED ai_ty_valvehandle (.5 .5 1) ?
*/

void ai_ty_valvehandle_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	
	int     index;
	gitem_t *item;

	if (!(other->client))
		return;
	
	item = FindItem ("Valve");
	index = ITEM_INDEX (item);
	
	if (!(other->client->pers.inventory[ index ]))
	{	
		gi.sound(other, CHAN_VOICE, gi.soundindex("scenaric/need_valvehandle.wav"), 1, ATTN_NORM, 0);
	
		self->touch = NULL;
	}
	
}

void SP_ty_valvehandle ( edict_t *ent )
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = ai_ty_valvehandle_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

}



#include "ep_log.h"

extern int	the_log_page;

void EP_Trainyard_Player_Log (edict_t *self, int page)
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
	else if (the_log_page >= NUM_TY_PLAYER_LOG)
		the_log_page = 0;

	for (i=1; i<NUM_TY_PLAYER_LOG; i++)
	{
		if (self->client->pers.episode_flags & ep_ty_player_log[i].ep_flag)
			cnt++;

		if (cnt == the_log_page)
		{
			select = i;
			break;
		}
	}	

	if (!page || !the_log_page)
	for (i=0; i<NUM_TY_PLAYER_LOG; i++)
	{
		if (ep_ty_player_log[i].new_clue == true)
		{
			select = i;
			break;
		}
	}

	if (cnt == 0)
	{
		the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_ty_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcpy (game.helpmessage2, ep_ty_player_log[0].ep_text);
	}
	else
	{
		if (select == 0)
			the_log_page = 0;
		strcpy (game.helpmessage1, " ");
		
		if (ep_ty_player_log[select].new_clue)
			strcat (game.helpmessage1, "new entry");
		
		strcat (game.helpmessage2, ep_ty_player_log[select].ep_text);
		if (page)
			gi.sound(self, CHAN_VOICE, gi.soundindex("world/pageturn.wav"), 1, ATTN_NONE, 0);
	}
	
	

}

qboolean EP_TY_Flash_Newflag (edict_t *self, int ep_flag)
{
	int i;
	qboolean gotone = false;

	for (i=0; i<NUM_TY_PLAYER_LOG; i++)
	{
		if (ep_ty_player_log[i].ep_flag == ep_flag)
		{
			ep_ty_player_log[i].new_clue = true;
			gotone = true;
		}
		else
			ep_ty_player_log[i].new_clue = false;
	}

	return (gotone);

}
