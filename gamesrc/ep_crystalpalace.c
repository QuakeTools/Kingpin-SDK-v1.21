/******************************************************************************

  CRYSTALPALACE - Episode specific code

*******************************************************************************/

#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

void ProcessKingpin (edict_t *self, edict_t *other);
void misc_cp_afraid_think (edict_t *self);

qboolean EP_CrystalPalace_CastSight ( edict_t *self, edict_t *other, cast_memory_t *mem )
{
	return false;
}

qboolean EP_CrystalPalace_CastUse (edict_t *self, edict_t *other, edict_t *activator)
{
	return false;
}

qboolean EP_CrystalPalace_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{
	cast_memory_t	*mem;

	mem = level.global_cast_memory[ self->character_index ][ other->character_index ];
	
	switch (saywhat)
	{
	
	case say_neutral:
		if (self->name_index == NAME_KINGPIN && other->client)
		{
			if (!(other->episode_flags & EP_CP_KINGPIN_FIRSTSIGHT))
			{
				gi.dprintf ("there he is lets go!\n");
				EP_Skidrow_Register_EPFLAG (other, EP_CP_KINGPIN_FIRSTSIGHT);
				{
					// need to make blunt and kingpin leave through the elevator
					ProcessKingpin (self, other);
				}
			}
			return true;
		}
		return false;
		break;
	case say_hostile:
		if (self->name_index == NAME_KINGPIN)
		{
			if (!(other->episode_flags & EP_CP_KINGPIN_FIRSTSIGHT))
			{
				gi.dprintf ("there he is lets go!\n");
				EP_Skidrow_Register_EPFLAG (other, EP_CP_KINGPIN_FIRSTSIGHT);
				{
					// need to make blunt and kingpin leave through the elevator
					ProcessKingpin (self, other);
				}
			}
			return true;	
		}
		return false;
		break;
	}

	return false;
}

void EP_CrystalPalace_ItemPickup ( edict_t *self, edict_t *other )
{

}

void EP_CrystalPalace_Script( edict_t *ent, char *scriptname )
{

}

int	EP_CrystalPalace_HiredGuysFlags (edict_t *player, edict_t *self)
{
		
	if (self->gender == GENDER_MALE)
		Voice_Random (self, player, &hiredguy_ask[10], 4);
	else
		Voice_Random (self, player, &hiredgal_specific[12], 4);

	return (0);
}

void EP_CrystalPalaceFlags (edict_t *self)
{

}

qboolean EP_CrystalPalace_DoKey (edict_t *self, edict_t *other)
{
	return false;
}

void EP_CrystalPalace_Check_DoKey (edict_t *self, edict_t *ent)
{

}

void EP_CrystalPalace_ReachedDoKey (edict_t *self)
{

}

void EP_CrystalPalace_EndDoKey (edict_t *self)
{

}

qboolean EP_CrystalPalace_UnlockDoorFlag (edict_t *ent)
{
	return false;
}

void EP_CrystalPalace_HiredGuysRegisterFlags (edict_t *ent, edict_t *other)
{

}

void ProcessKingpin (edict_t *self, edict_t *other)
{
	edict_t *Blunt;
	edict_t *ent = NULL;

	Blunt = EP_GetCharacter (NAME_BLUNT);

	if (Blunt)
	{
		
		ent = G_Find (ent, FOFS(classname), "misc_cp_afraid");

		if (ent)
		{
			self->goal_ent = ent;
			ent->cast_info.aiflags |= AI_GOAL_RUN;
			ent->think = misc_cp_afraid_think;
			ent->nextthink = level.time + 0.1;
			self->cast_info.aiflags &= ~AI_TALK;
		}
		else
			gi.dprintf ("Kingpin missing misc_cp_afraid marker\n");

	}

	// todo
	// the doors to the escape elevator need to open

}

/*QUAKED misc_cp_afraid (.5 .5 1) (-16 -16 -24) (16 16 48)
used as the location mo will run to before larry and curly attack him
*/

void misc_cp_afraid_think (edict_t *self)
{
	edict_t *Kingpin;
	edict_t *Blunt;
	
	vec3_t	vec;
	float	dist;

	Kingpin = EP_GetCharacter (NAME_KINGPIN);
	Blunt = EP_GetCharacter (NAME_BLUNT);

	if (Kingpin)
	{
		
		VectorSubtract (Kingpin->s.origin, self->s.origin, vec);
		dist = VectorLength (vec);

		// gi.dprintf ("dist: %5.3f\n", dist);
		if (dist < 128)
		{
			
		}
		else
		self->nextthink = level.time + 0.1;

	}
	

}

void SP_misc_cp_afraid (edict_t *self)
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
