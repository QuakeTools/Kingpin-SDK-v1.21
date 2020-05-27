/******************************************************************************

	GENERIC EPISODE CODE

******************************************************************************/

#include "g_local.h"

/*
	case EP_SKIDROW :
	case EP_POISONVILLE :
	case EP_STEELTOWN:
	case EP_TRAINYARD:
	case EP_RADIOCITY:
	case EP_SHIPYARDS:
	case EP_CRYSTALPALACE:
*/
//............................................................................
// Character Names
//

// ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !
//
// Note, these must be in the same order as the defines in ep_all.h!
//
// ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !

char *ep_names[] =
{
	"--THIS SLOT MUST BE VACANT--",
	"Al",
	"Beth",
	"Magicj",
	"Lisa",
	"Louie",
	"Frank",
	"Buttmunch",
	"Arnold",
	"Brewster",
	"Punky",
	"Igmo",
	"Johnny",
	"Betty",
	"Leroy",
	"Jed",
	"Buster",
	"Bubba",
	"Momo",
	"Muttski",
	"Spike",
	"ToughGuy1",
	"ToughGuy2",
	"IntroGuy",
	"Bernie",
	"Lamont",
	"Mona",
	"Lenny",
	"Chick",
	"Sluggo",
	"Rocko",
	"Rover",
	"Joseph",
	"Rummy", // sr1 bum
	"Nick",  // sr2 bum
	"Jesus", // sr boss 
	"Yolanda",
	"Carlton",
	"Tina",
	"Hardey",
	"Laurel",
	"Harold",
	"Dick",
	"Burt",
	"Fingers",
	"Dan",
	"Clarence",
	"Adolf",
	"Candy",
	"Sharky",
	"Kingpin",
	"Blunt",
	"NikkiBlanco",
	"Moe",
	"Larry",
	"Curly",
	"Ed",
	"Popeye",
	"Dogg",
	"Selma",
	"Jane",
	"Barney",
	"BigWillie",
	"Sal",
	"Lefty",
	"Bwillie",
	"Mung",
	"Tyrone",
	"Luke",
	"Hann",
	"Kroker",
	"kid_1",
	"kid_2",
	"kid_3",
	"kid_4",
	"kid_5",
	"kid_6",
	"kid_7",
	"kid_8",
	"Oscar",
	"David",
	"Bambi",
	"Brittany",
	"Mathew",
	"Pete",
	"Moker",
	"Heilman",
	"Butch",
	"Patrick",
	"Groucho",
	"Harpo",
	"Chico",
	"Blefty",
	"Scalper",
	"Dubs",
	"Rochelle",
	"Lola",
	"Dude",
	"Walter",
	"Donny",
	NULL
};

//............................................................................

// This sets the self->name_index according to the list above
void	EP_SetNameIndex ( edict_t *self )
{
	int i;

	if (!self->name)
	{
		self->name_index = -1;
		return;
	}

	for (i=0; ep_names[i]; i++)
	{
		if (self->name)
			if (!Q_stricmp(self->name, ep_names[i]))
			{	// found a match
				self->name_index = i;
				return;
			}
	}

	// no match found!
	gi.dprintf( "EP_SetNameIndex: Un-matched \"name\" (%s)\n", self->name );
	self->name_index = -1;
}

// Given a NAME_*, returns the entity with the matching name
edict_t	*EP_GetCharacter ( int nameIndex )
{
	int i;

	for (i=0; i<level.num_characters; i++)
	{
		if (!level.characters[i])
			continue;

		if (level.characters[i]->name_index == nameIndex)
		{
			if ((level.characters[i]->inuse) && (level.characters[i]->svflags & SVF_MONSTER) && (level.characters[i]->health > 0))
				return level.characters[i];
			else
				return NULL;	// character has died
		}
	}

	// This is causing problems be cause the guy could get refrenced yet be on another map
	// gi.dprintf( "EP_GetCharacter: couldn't find %s\n", ep_names[nameIndex] );

	return NULL;	// couldn't find them
}

// Given a "name", returns the entity with the matching name
edict_t	*EP_GetCharacterByName ( char *name )
{
	int i;

	for (i=0; i<level.num_characters; i++)
	{
		if (!level.characters[i])
			continue;

		if (!Q_stricmp( level.characters[i]->name, name ))
		{
			if ((level.characters[i]->inuse) && (level.characters[i]->svflags & SVF_MONSTER) && (level.characters[i]->health > 0))
				return level.characters[i];
			else
				return NULL;	// character has died
		}
	}

	gi.dprintf( "EP_GetCharacter: couldn't find %s\n", name );

	return NULL;	// couldn't find them
}

//............................................................................
// Gang Names
//
// These will match the "cast_group" value for characters in the game
// Also must match the defines in ep_all.h !!

char *ep_gang_names[] =
{
	"(neutral)",
	"Our Gang(?)",
	"Main Gang(?)",
	"Rat-Gang",
	NULL
};

char	*EP_GetGangName ( int cast_group )
{
	static char	unknown_str[] = "**UNKNOWN**";

	if (cast_group >= NUM_GANGS)
		return unknown_str;

	return ep_gang_names[cast_group];
}

//=======================================================================================================


void EP_PlayerLog (edict_t *self, int page)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		EP_Skidrow_Player_Log	(self, page);
		break;
	case EP_POISONVILLE:
		EP_PV_Player_Log		(self, page);
		break;
	case EP_SHIPYARDS:
		EP_SY_Player_Log		(self, page);
		break;
	case EP_STEELTOWN:
		EP_Steeltown_Player_Log (self, page);
		break;
	case EP_TRAINYARD:
		EP_Trainyard_Player_Log	(self, page);
		break;
	case EP_RADIOCITY:
		EP_RC_Player_Log		(self, page);
		break;
	}
}


//............................................................................
// This gets called whenever an AI character has sighted another character
// (which will happen every frame while they are in view).

qboolean EP_CastSight ( edict_t *self, edict_t *other, cast_memory_t *cast_memory )
{
	switch (level.episode)
	{
	case EP_SKIDROW :
		return EP_Skidrow_CastSight ( self, other, cast_memory );
	case EP_POISONVILLE :
		return EP_Poisonville_CastSight ( self, other, cast_memory );
	
	case EP_STEELTOWN:
		return EP_Steeltown_CastSight ( self, other, cast_memory );
		break;
	case EP_TRAINYARD:
		break;
	case EP_RADIOCITY:
		return EP_RC_CastSight ( self, other, cast_memory );
		break;
	case EP_SHIPYARDS:
		return EP_SY_CastSight ( self, other, cast_memory );
	}

	return false;
}

//............................................................................
// This gets called whenever an AI character dies is "used" (like when they die and have a ->deathtarget)

qboolean EP_CastUse ( edict_t *self, edict_t *other, edict_t *activator )
{
	switch (level.episode)
	{
	case EP_SKIDROW :
		return EP_Skidrow_CastUse ( self, other, activator );
		break;
	case EP_POISONVILLE :
		return EP_Poisonville_CastUse ( self, other, activator );
		break;
	case EP_STEELTOWN:
		return EP_Steeltown_CastUse ( self, other, activator );
		break;
	case EP_TRAINYARD:
		break;
	case EP_RADIOCITY:
		return EP_RC_CastUse ( self, other, activator );
		break;
	case EP_SHIPYARDS:
		return EP_SY_CastUse ( self, other, activator );
	}

	return false;
}


//............................................................................
// Generic event based speech for episodes

qboolean EP_EventSpeech (edict_t *self, edict_t *other, int saywhat)
{

	switch (level.episode)
	{
	case EP_SKIDROW:
		return EP_Skidrow_EventSpeech (self, other, saywhat);
		break;
	case EP_POISONVILLE:
		return EP_Poisonville_EventSpeech (self, other, saywhat);
		break;
	case EP_TRAINYARD:
		return EP_Trainyard_EventSpeech (self, other, saywhat);	
		break;
	case EP_SHIPYARDS:
		return EP_SY_EventSpeech (self, other, saywhat);
		break;
	case EP_STEELTOWN:
		return EP_Steeltown_EventSpeech (self, other, saywhat);
		break;
	case EP_RADIOCITY:
		return EP_RC_EventSpeech (self, other, saywhat);
		break;
	}

	return false;
}

//............................................................................
// Called whenever an item is picked up

void EP_ItemPickup ( edict_t *self, edict_t *other )
{

	switch (level.episode)
	{
	case EP_SKIDROW:
		EP_Skidrow_ItemPickup( self, other );
		break;
	case EP_POISONVILLE:
		EP_Poisonville_ItemPickup( self, other );
		break;
	case EP_TRAINYARD:
		EP_Trainyard_ItemPickup( self, other );
		break;
	case EP_SHIPYARDS:
		EP_SY_ItemPickup( self, other );
		break;
	case EP_STEELTOWN:
		EP_Steeltown_ItemPickup (self, other);
		break;

	}

}


//............................................................................
// Called whenever a character reaches a path_corner_cast that has a "scriptname" set

void EP_EventScript ( edict_t *self, char *scriptname )
{

	switch (level.episode)
	{
	case EP_SKIDROW:
		EP_Skidrow_Script( self, scriptname );
		break;
	case EP_POISONVILLE:
		EP_Poisonville_Script( self, scriptname );
		break;
	case EP_TRAINYARD:
		EP_Trainyard_Script( self, scriptname );
		break;
	case EP_SHIPYARDS:
		EP_SY_Script( self, scriptname );
		break;
	case EP_STEELTOWN:
		EP_Steeltown_Script (self, scriptname);
		break;
	}

}


void EP_Reset (edict_t *self, edict_t *other)
{

	switch (level.episode)
	{
	case EP_SKIDROW:
		EP_Skidrow_Reset( self, other );
		break;
	case EP_POISONVILLE:
		// EP_Poisonville_Reset( self, other );
		break;
	}

}


void EP_SpawnFlags (edict_t *self)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		EP_SkidrowFlags (self);
		break;
	case EP_POISONVILLE:
		EP_PVFlags (self);
		break;
	case EP_SHIPYARDS:
		EP_SYFlags (self);
		break;
	case EP_STEELTOWN:
		EP_SteeltownFlags (self);
		break;
	case EP_RADIOCITY: 
		EP_RCFlags (self);
		break;
	}
}

int EP_HiredGuys (edict_t *self, edict_t *other)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		return (1);
	case EP_POISONVILLE:
		return (EP_PV_HiredGuysFlags (self, other));
	case EP_STEELTOWN:
		return (EP_Steeltown_HiredGuysFlags (self, other));
	case EP_TRAINYARD:
		return (EP_Trainyard_HiredGuysFlags (self, other));
	case EP_RADIOCITY:
		return (EP_RC_HiredGuysFlags (self, other));	
	case EP_SHIPYARDS:
		return (EP_SY_HiredGuysFlags (self, other));
	default:
		return (1);
	}

	// just to shut up the compiler
	return (0);
}

void EP_CheckMomo (edict_t *ent, cast_memory_t	*mem)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		EP_Skidrow_CheckMomo (ent, mem);
		break;
	case EP_POISONVILLE:
		EP_PV_CheckMomo (ent, mem);
		break;
	case EP_SHIPYARDS:
		EP_SY_CheckMomo (ent, mem);
		break;	
	case EP_STEELTOWN:
		EP_Steeltown_CheckMomo (ent, mem);
		break;
	case EP_RADIOCITY:
		EP_RC_CheckMomo (ent, mem);
		break;
	}
}

qboolean EP_DoKey (edict_t *ent, edict_t *other)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		return false;
		break;
	case EP_POISONVILLE:
		return (EP_PV_DoKey (ent, other));
		break;
	case EP_STEELTOWN:
		return (EP_Steeltown_DoKey (ent, other));
		break;
	}

	return false;
}

void EP_Check_DoKey (edict_t *self, edict_t *ent)
{

	switch (level.episode)
	{
	case EP_SKIDROW:
		break;
	case EP_POISONVILLE:
		EP_PV_Check_DoKey (self, ent);
		break;
	case EP_STEELTOWN:
		EP_Steeltown_Check_DoKey (self, ent);
		break;
	}

}

void EP_ReachedDoKey (edict_t *self)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		break;
	case EP_POISONVILLE:
		EP_PV_ReachedDoKey (self);
		break;
	case EP_STEELTOWN:
		EP_Steeltown_ReachedDoKey (self);
		break;
	}
}

void EP_EndDoKey (edict_t *self)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		break;
	case EP_POISONVILLE:
		EP_PV_EndDoKey (self);
		break;
	case EP_STEELTOWN:
		EP_Steeltown_EndDoKey (self);
		break;
	}
}


qboolean EP_UnlockDoorFlag (edict_t *ent)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		break;
	case EP_POISONVILLE:
		return (EP_PV_UnlockDoorFlag (ent));
		break;
	case EP_STEELTOWN:
		return (EP_Steeltown_UnlockDoorFlag (ent));
		break;
	}

	return false;
}

void EP_HiredGuysRegisterFlags (edict_t *ent, edict_t *other)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		break;
	case EP_POISONVILLE:
		EP_PV_HiredGuysRegisterFlags (ent, other);
		break;
	case EP_STEELTOWN:
		EP_Steeltown_HiredGuysRegisterFlags (ent, other);
		break;
	case EP_RADIOCITY:
		EP_RC_HiredGuysRegisterFlags (ent, other);
		break;
	}

}

void EP_SpecialEventDeath (edict_t *self)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		break;
	case EP_POISONVILLE:
		EP_PV_SpecialEventDeath (self);
		break;
	case EP_STEELTOWN:
		EP_Steeltown_SpecialEventDeath (self);
		break;
	case EP_TRAINYARD:
		// EP_Trainyard_SpecialEventDeath (self);
		break;
	case EP_RADIOCITY:
		EP_RC_SpecialEventDeath (self);
		break;
	case EP_SHIPYARDS:
		EP_SY_SpecialEventDeath (self);
		break;
	}
	
}

qboolean EP_Steeltown_UnlockDoorFlag (edict_t *ent)
{
	return false;
}

// JOSEPH 14-JUN-99
void Think_Help (edict_t *ent)
{
	if (!(level.helpchange))
	{
		level.helpchange = 0;
		G_FreeEdict(ent);
		return;
	}
	
	if (!ent->misstime )
	{
		level.helpchange = 0;
		G_FreeEdict(ent);
		return;
	}
	
	if (ent->misstime <= 15 && level.helpchange)
	{
		level.helpchange = ent->misstime*(255/15);
	}

	ent->misstime--;	

	ent->nextthink = level.time + 0.1;
}

void Show_Help (void)
{
	edict_t	*help = NULL;
	edict_t	*ent = NULL;

	ent = G_Find (NULL, FOFS(classname), "showhelp");
	if (ent)
	{
		G_FreeEdict(ent);
	}

	help = G_Spawn();
	
	if (!help)
		return;

	help->classname = "showhelp";
	help->think = Think_Help;
	help->misstime = 315;
	help->nextthink = level.time + 0.1;

	gi.linkentity (help);

	level.helpchange = 255;

	return;
}
// END JOSEPH

void EP_Flash_Newflag (edict_t *self, int ep_flag)
{

	qboolean rval = false;
	
	switch (level.episode)
	{
	case EP_SKIDROW:
		rval = EP_Skidrow_Flash_Newflag (self, ep_flag);
		break;
	case EP_POISONVILLE:
		rval = EP_PV_Flash_Newflag (self, ep_flag);
		break;
	case EP_STEELTOWN:
		rval = EP_Steeltown_Flash_Newflag (self, ep_flag);
		break;
	case EP_TRAINYARD:
		rval = EP_TY_Flash_Newflag (self, ep_flag);
		break;
	case EP_RADIOCITY:
		rval = EP_RC_Flash_Newflag (self, ep_flag);
		break;
	case EP_SHIPYARDS:
		rval = EP_SY_Flash_Newflag (self, ep_flag);
		break;
	}

	// joe flash the notepad help icon here
	if (rval)
		Show_Help ();
}
