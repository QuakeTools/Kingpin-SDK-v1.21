
#include "g_local.h"

#define Function(f) {#f, f}

mmove_t mmove_reloc;

field_t fields[] = {
	{"classname", FOFS(classname), F_LSTRING},
	{"model", FOFS(model), F_LSTRING},
	{"spawnflags", FOFS(spawnflags), F_INT},
	{"speed", FOFS(speed), F_FLOAT},
	{"accel", FOFS(accel), F_FLOAT},
	{"decel", FOFS(decel), F_FLOAT},
	{"target", FOFS(target), F_LSTRING},
	{"targetname", FOFS(targetname), F_LSTRING},
	{"pathtarget", FOFS(pathtarget), F_LSTRING},
	{"deathtarget", FOFS(deathtarget), F_LSTRING},
	{"killtarget", FOFS(killtarget), F_LSTRING},
	{"combattarget", FOFS(combattarget), F_LSTRING},
	{"message", FOFS(message), F_LSTRING},
	{"team", FOFS(team), F_LSTRING},
	{"wait", FOFS(wait), F_FLOAT},
	{"delay", FOFS(delay), F_FLOAT},
	{"random", FOFS(random), F_FLOAT},
	{"move_origin", FOFS(move_origin), F_VECTOR},
	{"move_angles", FOFS(move_angles), F_VECTOR},
	{"style", FOFS(style), F_INT},
	{"count", FOFS(count), F_INT},
	{"health", FOFS(health), F_INT},
	{"sounds", FOFS(sounds), F_INT},

	{"light", FOFS(light_level), F_INT},	// Ridah, used by model lighting code
	{"_color", FOFS(rotate), F_VECTOR},		// Ridah, used by model lighting code
	{"radius", FOFS(dmg_radius), F_VECTOR},		// Ridah, used by model lighting code

	{"dmg", FOFS(dmg), F_INT},
	{"mass", FOFS(mass), F_INT},
	{"volume", FOFS(volume), F_FLOAT},
	{"attenuation", FOFS(attenuation), F_FLOAT},
	{"map", FOFS(map), F_LSTRING},
	{"origin", FOFS(s.origin), F_VECTOR},
	{"angles", FOFS(s.angles), F_VECTOR},
	{"angle", FOFS(s.angles), F_ANGLEHACK},

	{"objectbounds_filename1", FOFS(s.model_parts[0].objectbounds_filename), F_LSTRING},
	{"objectbounds_filename2", FOFS(s.model_parts[1].objectbounds_filename), F_LSTRING},
	{"objectbounds_filename3", FOFS(s.model_parts[2].objectbounds_filename), F_LSTRING},
	{"objectbounds_filename4", FOFS(s.model_parts[3].objectbounds_filename), F_LSTRING},
	{"objectbounds_filename5", FOFS(s.model_parts[4].objectbounds_filename), F_LSTRING},
	{"objectbounds_filename6", FOFS(s.model_parts[5].objectbounds_filename), F_LSTRING},
	{"objectbounds_filename7", FOFS(s.model_parts[6].objectbounds_filename), F_LSTRING},
	{"objectbounds_filename8", FOFS(s.model_parts[7].objectbounds_filename), F_LSTRING},

// JOSEPH 19-MAR-99
	{"rotate", FOFS(rotate), F_VECTOR},
	{"duration", FOFS(duration), F_FLOAT},
	{"alphalevel", FOFS(alphalevel), F_INT},
	{"fxdensity", FOFS(fxdensity), F_INT},
	{"healspeed", FOFS(healspeed), F_INT}, 
	{"deadticks", FOFS(deadticks), F_INT}, 
	{"missteam", FOFS(missteam), F_INT}, 
	{"misstime", FOFS(misstime), F_INT}, 
	{"cameraangle", FOFS(cameraangle), F_VECTOR}, 
	{"cameraorigin", FOFS(cameraorigin), F_VECTOR}, 
	{"cameravel", FOFS(cameravel), F_VECTOR},
	{"cameravelrel", FOFS(cameravelrel), F_VECTOR},
	{"debugprint", FOFS(debugprint), F_INT},
	{"target2", FOFS(target2), F_LSTRING},
	{"localteam", FOFS(localteam), F_LSTRING},
	{"reactdelay", FOFS(reactdelay), F_FLOAT}, 
	{"currentcash", FOFS(currentcash), F_INT},
	{"type", FOFS(type), F_LSTRING},
	{"head", FOFS(head), F_INT},
	{"key", FOFS(key), F_INT},
	{"target2_ent", FOFS(target2_ent), F_EDICT},
	{"missent", FOFS(missent), F_EDICT},
	{"handle", FOFS(handle), F_EDICT},
	{"handle2", FOFS(handle2), F_EDICT},
	{"save_self", FOFS(save_self), F_EDICT},
	{"save_other", FOFS(save_other), F_EDICT},
	{"deadticks", FOFS(deadticks), F_INT},
	{"thudsnd", FOFS(thudsnd), F_INT},
	{"head", FOFS(head), F_INT},
	{"firetype", FOFS(firetype), F_INT},
	{"thudsurf", FOFS(thudsurf), F_INT},
	{"lightit", FOFS(lightit), F_INT},
	{"option", FOFS(option), F_INT},
	{"noshadow", FOFS(noshadow), F_INT},
// END JOSEPH

	{"acc", FOFS (acc), F_INT},
	{"cal", FOFS (cal), F_INT},

	// Ridah, new stuff

	{"cast_group", FOFS(cast_group), F_INT},
	{"skin", FOFS(skin), F_INT},
	{"moral", FOFS(moral), F_INT},
	{"guard_radius", FOFS(guard_radius), F_INT},
	{"guard_target", FOFS(guard_target), F_LSTRING},
	{"name", FOFS(name), F_LSTRING},
	{"episode", FOFS(count), F_INT},				// used by worldspawn
	{"scriptname", FOFS(scriptname), F_LSTRING},

	{"onfireent", FOFS(onfireent), F_EDICT},
	{"leader", FOFS(leader), F_EDICT},
	{"leader_target", FOFS(leader_target), F_LSTRING},
	{"last_goal", FOFS(last_goal), F_EDICT},

	{"order", FOFS(order), F_INT},
	{"order_timestamp", FOFS(order_timestamp), F_FLOAT},
	{"moveout_ent", FOFS(moveout_ent), F_EDICT},
	{"character_index", FOFS(character_index), F_INT},
	{"last_talk_time", FOFS(last_talk_time), F_FLOAT},
	{"profanity_level", FOFS(profanity_level), F_INT},
	{"guard_ent", FOFS(guard_ent), F_EDICT},
	{"sight_target", FOFS(sight_target), F_LSTRING},
	{"goal_ent", FOFS(goal_ent), F_EDICT},
	{"combat_goalent", FOFS(combat_goalent), F_EDICT},
	{"cover_ent", FOFS(cover_ent), F_EDICT},
	
	{"episode_flags", FOFS(episode_flags), F_INT},

	{"name_index", FOFS(name_index), F_INT},
	{"last_territory_touched", FOFS(last_territory_touched), F_EDICT},
	{"response_ent", FOFS(response_ent), F_EDICT},
	{"last_response_time", FOFS(last_response_time), F_FLOAT},
	{"last_response", FOFS(last_response), F_INT},

	{"start_ent", FOFS(start_ent), F_EDICT},
	{"holdpos_ent", FOFS(holdpos_ent), F_EDICT},

	{"next_combattarget", FOFS(next_combattarget), F_LSTRING},

	{"activate_flags", FOFS(activate_flags), F_INT},
	{"biketime", FOFS(biketime), F_FLOAT},
	{"bikestate", FOFS(bikestate), F_INT},

	{"vehicle_index", FOFS(vehicle_index), F_INT},

	{"art_skins", FOFS(art_skins), F_LSTRING},

	{"aiflags", FOFS(cast_info.aiflags), F_INT},

	{"gun_noise_delay", FOFS(gun_noise_delay), F_FLOAT},

	{"scale", FOFS(cast_info.scale), F_FLOAT},

	{"voice_pitch", FOFS(voice_pitch), F_FLOAT},

	{"health_threshold", FOFS(health_threshold), F_INT},
	{"health_target", FOFS(health_target), F_LSTRING},
	{"health_threshold2", FOFS(health_threshold2), F_INT},
	{"health_target2", FOFS(health_target2), F_LSTRING},
	{"health_threshold3", FOFS(health_threshold3), F_INT},
	{"health_target3", FOFS(health_target3), F_LSTRING},
	// Ridah, done.

	
	{"goalentity", FOFS(goalentity), F_EDICT, FFL_NOSPAWN},
	{"movetarget", FOFS(movetarget), F_EDICT, FFL_NOSPAWN},
	{"enemy", FOFS(enemy), F_EDICT, FFL_NOSPAWN},
	{"oldenemy", FOFS(oldenemy), F_EDICT, FFL_NOSPAWN},
	{"activator", FOFS(activator), F_EDICT, FFL_NOSPAWN},
	{"groundentity", FOFS(groundentity), F_EDICT, FFL_NOSPAWN},
	{"teamchain", FOFS(teamchain), F_EDICT, FFL_NOSPAWN},
	{"teammaster", FOFS(teammaster), F_EDICT, FFL_NOSPAWN},
	{"owner", FOFS(owner), F_EDICT, FFL_NOSPAWN},
	{"mynoise", FOFS(mynoise), F_EDICT, FFL_NOSPAWN},
	{"mynoise2", FOFS(mynoise2), F_EDICT, FFL_NOSPAWN},
	{"target_ent", FOFS(target_ent), F_EDICT, FFL_NOSPAWN},
	{"chain", FOFS(chain), F_EDICT, FFL_NOSPAWN},

	{"prethink", FOFS(prethink), F_FUNCTION, FFL_NOSPAWN},
	{"think", FOFS(think), F_FUNCTION, FFL_NOSPAWN},
	{"blocked", FOFS(blocked), F_FUNCTION, FFL_NOSPAWN},
	{"touch", FOFS(touch), F_FUNCTION, FFL_NOSPAWN},
	{"use", FOFS(use), F_FUNCTION, FFL_NOSPAWN},
	{"pain", FOFS(pain), F_FUNCTION, FFL_NOSPAWN},
	{"die", FOFS(die), F_FUNCTION, FFL_NOSPAWN},

	{"idle", FOFS(cast_info.idle), F_FUNCTION, FFL_NOSPAWN},
	{"search", FOFS(cast_info.search), F_FUNCTION, FFL_NOSPAWN},
	{"dodge", FOFS(cast_info.dodge), F_FUNCTION, FFL_NOSPAWN},
	{"attack", FOFS(cast_info.attack), F_FUNCTION, FFL_NOSPAWN},
	{"long_attack", FOFS(cast_info.long_attack), F_FUNCTION, FFL_NOSPAWN},
	{"sight", FOFS(cast_info.sight), F_FUNCTION, FFL_NOSPAWN},
	{"duck", FOFS(cast_info.duck), F_FUNCTION, FFL_NOSPAWN},
	{"talk", FOFS(cast_info.talk), F_FUNCTION, FFL_NOSPAWN},
	{"avoid", FOFS(cast_info.avoid), F_FUNCTION, FFL_NOSPAWN},
	
	{"backoff", FOFS(cast_info.backoff), F_FUNCTION, FFL_NOSPAWN},
	
	{"catch_fire", FOFS(cast_info.catch_fire), F_FUNCTION, FFL_NOSPAWN},
	{"checkattack", FOFS(cast_info.checkattack), F_FUNCTION, FFL_NOSPAWN},
	{"currentmove", FOFS(cast_info.currentmove), F_MMOVE, FFL_NOSPAWN},
	
	{"oldcurrentmove", FOFS(cast_info.oldcurrentmove), F_MMOVE, FFL_NOSPAWN},

	{"move_stand", FOFS(cast_info.move_stand), F_MMOVE, FFL_NOSPAWN},
	{"move_crstand", FOFS(cast_info.move_crstand), F_MMOVE, FFL_NOSPAWN},
	{"move_run", FOFS(cast_info.move_run), F_MMOVE, FFL_NOSPAWN},
	{"move_runwalk", FOFS(cast_info.move_runwalk), F_MMOVE, FFL_NOSPAWN},
	{"move_crwalk", FOFS(cast_info.move_crwalk), F_MMOVE, FFL_NOSPAWN},
	{"move_jump", FOFS(cast_info.move_jump), F_MMOVE, FFL_NOSPAWN},
	{"move_crouch_down", FOFS(cast_info.move_crouch_down), F_MMOVE, FFL_NOSPAWN},
	{"move_stand_up", FOFS(cast_info.move_stand_up), F_MMOVE, FFL_NOSPAWN},
	{"move_avoid_walk", FOFS(cast_info.move_avoid_walk), F_MMOVE, FFL_NOSPAWN},
	{"move_avoid_run", FOFS(cast_info.move_avoid_run), F_MMOVE, FFL_NOSPAWN},
	{"move_avoid_reverse_walk", FOFS(cast_info.move_avoid_reverse_walk), F_MMOVE, FFL_NOSPAWN},
	{"move_avoid_reverse_run", FOFS(cast_info.move_avoid_reverse_run), F_MMOVE, FFL_NOSPAWN},
	{"move_avoid_crwalk", FOFS(cast_info.move_avoid_crwalk), F_MMOVE, FFL_NOSPAWN},
	{"move_lside_step", FOFS(cast_info.move_lside_step), F_MMOVE, FFL_NOSPAWN},
	{"move_rside_step", FOFS(cast_info.move_rside_step), F_MMOVE, FFL_NOSPAWN},
	{"move_start_climb", FOFS(cast_info.move_start_climb), F_MMOVE, FFL_NOSPAWN},
	{"move_end_climb", FOFS(cast_info.move_end_climb), F_MMOVE, FFL_NOSPAWN},
	{"move_evade", FOFS(cast_info.move_evade), F_MMOVE, FFL_NOSPAWN},
	{"move_stand_evade", FOFS(cast_info.move_stand_evade), F_MMOVE, FFL_NOSPAWN},
	

	{"avoid_ent", FOFS(cast_info.avoid_ent), F_EDICT, FFL_NOSPAWN},
	{"talk_ent", FOFS(cast_info.talk_ent), F_EDICT, FFL_NOSPAWN},

	{"friend_memory", FOFS(cast_info.friend_memory), F_CAST_MEMORY, FFL_NOSPAWN},
	{"neutral_memory", FOFS(cast_info.neutral_memory), F_CAST_MEMORY, FFL_NOSPAWN},
	{"enemy_memory", FOFS(cast_info.enemy_memory), F_CAST_MEMORY, FFL_NOSPAWN},

	{"endfunc", FOFS(moveinfo.endfunc), F_FUNCTION, FFL_NOSPAWN},


	// temp spawn vars -- only valid when the spawn function is called
	{"lip", STOFS(lip), F_INT, FFL_SPAWNTEMP},
	{"distance", STOFS(distance), F_INT, FFL_SPAWNTEMP},
	{"height", STOFS(height), F_INT, FFL_SPAWNTEMP},
	{"noise", STOFS(noise), F_LSTRING, FFL_SPAWNTEMP},
	{"pausetime", STOFS(pausetime), F_FLOAT, FFL_SPAWNTEMP},
	{"item", STOFS(item), F_LSTRING, FFL_SPAWNTEMP},

//need for item field in edict struct, FFL_SPAWNTEMP item will be skipped on saves
	{"item", FOFS(item), F_ITEM},

	{"gravity", STOFS(gravity), F_LSTRING, FFL_SPAWNTEMP},
	{"sky", STOFS(sky), F_LSTRING, FFL_SPAWNTEMP},
	{"minyaw", STOFS(minyaw), F_FLOAT, FFL_SPAWNTEMP},
	{"maxyaw", STOFS(maxyaw), F_FLOAT, FFL_SPAWNTEMP},
	{"minpitch", STOFS(minpitch), F_FLOAT, FFL_SPAWNTEMP},
	{"maxpitch", STOFS(maxpitch), F_FLOAT, FFL_SPAWNTEMP},
	{"nextmap", STOFS(nextmap), F_LSTRING, FFL_SPAWNTEMP},
	{"fogdensity", STOFS(fogdensity), F_FLOAT, FFL_SPAWNTEMP}, 
	{"fogval", STOFS(fogval), F_VECTOR, FFL_SPAWNTEMP},

	{"fogdensity2", STOFS(fogdensity2), F_FLOAT, FFL_SPAWNTEMP}, 
	{"fogval2", STOFS(fogval2), F_VECTOR, FFL_SPAWNTEMP},


	{0, 0, 0, 0}

};

field_t		levelfields[] =
{
	{"changemap", LLOFS(changemap), F_LSTRING},
                   
	{"sight_client", LLOFS(sight_client), F_EDICT},
	{"sight_entity", LLOFS(sight_entity), F_EDICT},
	{"sound_entity", LLOFS(sound_entity), F_EDICT},
	{"sound2_entity", LLOFS(sound2_entity), F_EDICT},

	{"characters", LLOFS(characters), F_IGNORE},

	{NULL, 0, F_INT}
};

field_t		clientfields[] =
{
	{"pers.weapon", CLOFS(pers.weapon), F_ITEM},
	{"pers.holsteredweapon", CLOFS(pers.holsteredweapon), F_ITEM},
	{"pers.lastweapon", CLOFS(pers.lastweapon), F_ITEM},
	{"newweapon", CLOFS(newweapon), F_ITEM},
	{NULL, 0, F_INT}
};

field_t		castmemoryfields[] =
{
	{"response", CMOFS(response), F_FUNCTION},
	{"next", CMOFS(next), F_CAST_MEMORY},
	{"prev", CMOFS(prev), F_CAST_MEMORY},

	{NULL, 0, F_INT}
};

/*
============
InitGame

This will be called when the dll is first loaded, which
only happens when a new game is started or a save game
is loaded.
============
*/
void InitGame (void)
{
	gi.dprintf ("==== InitGame ====\n");

	gun_x = gi.cvar ("gun_x", "0", 0);
	gun_y = gi.cvar ("gun_y", "0", 0);
	gun_z = gi.cvar ("gun_z", "0", 0);

	//FIXME: sv_ prefix is wrong for these
	sv_rollspeed = gi.cvar ("sv_rollspeed", "200", 0);
	sv_rollangle = gi.cvar ("sv_rollangle", "0", 0);
	sv_maxvelocity = gi.cvar ("sv_maxvelocity", "2000", 0);
	sv_gravity = gi.cvar ("sv_gravity", "800", 0);

	// noset vars
	dedicated = gi.cvar ("dedicated", "0", CVAR_NOSET);

	// latched vars
	sv_cheats = gi.cvar ("cheats", "0", CVAR_SERVERINFO|CVAR_LATCH);
	gi.cvar ("gamename", GAMEVERSION , CVAR_SERVERINFO | CVAR_LATCH);
	gi.cvar ("gamedate", __DATE__ , CVAR_SERVERINFO | CVAR_LATCH);

	maxclients = gi.cvar ("maxclients", "4", CVAR_SERVERINFO | CVAR_LATCH);
	deathmatch = gi.cvar ("deathmatch", "0", CVAR_LATCH);
	coop = gi.cvar ("coop", "0", CVAR_LATCH);
	skill = gi.cvar ("skill", "1", CVAR_LATCH);

	// JOSEPH 16-OCT-98
	maxentities = gi.cvar ("maxentities", /*"1024"*/"2048", CVAR_LATCH);

	// RAFAEL
//	marines = gi.cvar ("marines", "0", CVAR_ARCHIVE);

	// change anytime vars
	dmflags = gi.cvar ("dmflags", "0", CVAR_SERVERINFO|CVAR_ARCHIVE);
	fraglimit = gi.cvar ("fraglimit", "0", CVAR_SERVERINFO);
	timelimit = gi.cvar ("timelimit", "0", CVAR_SERVERINFO);
	cashlimit = gi.cvar ("cashlimit", "0", CVAR_SERVERINFO);
	password = gi.cvar ("password", "", CVAR_USERINFO);
	filterban = gi.cvar ("filterban", "1", 0);

	g_select_empty = gi.cvar ("g_select_empty", "0", CVAR_ARCHIVE);

	run_pitch = gi.cvar ("run_pitch", "0.002", 0);
	run_roll = gi.cvar ("run_roll", "0.005", 0);
	bob_up  = gi.cvar ("bob_up", "0.005", 0);
	bob_pitch = gi.cvar ("bob_pitch", "0.002", 0);
	bob_roll = gi.cvar ("bob_roll", "0.002", 0);

	// flood control
	flood_msgs = gi.cvar ("flood_msgs", "4", 0);
	flood_persecond = gi.cvar ("flood_persecond", "4", 0);
	flood_waitdelay = gi.cvar ("flood_waitdelay", "10", 0);

// Ridah, new cvar's
	developer = gi.cvar ("developer", "0", 0);

	maxrate = gi.cvar ("maxrate", "25000", CVAR_SERVERINFO);

	ai_debug_memory = gi.cvar ("ai_debug_memory", "0", 0);

	g_vehicle_test = gi.cvar ("g_vehicle_test", "0", CVAR_LATCH);	// Enables Hovercars for all players

	dm_locational_damage = gi.cvar ("dm_locational_damage", "0", CVAR_SERVERINFO);

	showlights =  gi.cvar ("showlights", "0", 0);

	r_directional_lighting = gi.cvar ("r_directional_lighting", "1", CVAR_ARCHIVE);

	cl_captions = gi.cvar ("cl_captions", "0", CVAR_ARCHIVE);	// Ridah, disabled this by default, is that cool?

	sv_runscale = gi.cvar ("sv_runscale", "1.0", 0);	// only effective in Deathmatch

	burn_enabled	= gi.cvar("burn_enabled", "0", 0);
	burn_size		= gi.cvar("burn_size", "48", 0);
	burn_intensity	= gi.cvar("burn_intensity", "0.03", 0);
	burn_r			= gi.cvar("burn_r", "1.0", 0);
	burn_g			= gi.cvar("burn_g", "1.0", 0);
	burn_b			= gi.cvar("burn_b", "1.0", 0);

	timescale		= gi.cvar("timescale", "1.0", 0);

	teamplay		= gi.cvar("teamplay", "0", CVAR_LATCH|CVAR_SERVERINFO);
	g_cashspawndelay = gi.cvar("g_cashspawndelay", "5", CVAR_ARCHIVE|CVAR_LATCH);

	// this is only used for single player games
	cl_parental_lock = gi.cvar( "cl_parental_lock", "0", CVAR_NOSET);
	cl_parental_override = gi.cvar( "cl_parental_override", "0", CVAR_NOSET);

	dm_realmode = gi.cvar( "dm_realmode", "0", CVAR_LATCH|CVAR_SERVERINFO);
	
	g_mapcycle_file = gi.cvar( "g_mapcycle_file", "", 0);
// Ridah, done.

	// items
	InitItems ();

	Com_sprintf (game.helpmessage1, sizeof(game.helpmessage1), "");

	Com_sprintf (game.helpmessage2, sizeof(game.helpmessage2), "");

	// initialize all entities for this game
	game.maxentities = maxentities->value;
	g_edicts =  gi.TagMalloc (game.maxentities * sizeof(g_edicts[0]), TAG_GAME);
	globals.edicts = g_edicts;
	globals.max_edicts = game.maxentities;

	g_cast_memory = gi.TagMalloc (MAX_CHARACTERS * MAX_CHARACTERS * sizeof(cast_memory_t), TAG_GAME );
	memset( g_cast_memory, 0, MAX_CHARACTERS * MAX_CHARACTERS * sizeof(cast_memory_t) );

	g_cast_groups = gi.TagMalloc (MAX_CAST_GROUPS * sizeof(cast_group_t), TAG_GAME );
	memset( g_cast_groups, 0, MAX_CAST_GROUPS * sizeof(cast_group_t) );

	// initialize all clients for this game
	game.maxclients = maxclients->value;
	game.clients = gi.TagMalloc (game.maxclients * sizeof(game.clients[0]), TAG_GAME);
	globals.num_edicts = game.maxclients+1;
}

//=========================================================

void WriteField1 (FILE *f, field_t *field, byte *base)
{
	void		*p;
	int			len;
	int			index;

	if (field->flags & FFL_SPAWNTEMP)
		return;

	p = (void *)(base + field->ofs);
	switch (field->type)
	{
	case F_INT:
	case F_FLOAT:
	case F_ANGLEHACK:
	case F_VECTOR:
	case F_IGNORE:
		break;

	case F_LSTRING:
	case F_GSTRING:
		if ( *(char **)p )
			len = strlen(*(char **)p) + 1;
		else
			len = 0;
		*(int *)p = len;
		break;
	case F_EDICT:
		if ( *(edict_t **)p == NULL)
			index = -1;
		else
			index = *(edict_t **)p - g_edicts;
		*(int *)p = index;
		break;
	case F_CLIENT:
		if ( *(gclient_t **)p == NULL)
			index = -1;
		else
			index = *(gclient_t **)p - game.clients;
		*(int *)p = index;
		break;
	case F_ITEM:
		if ( *(edict_t **)p == NULL)
			index = -1;
		else
			index = *(gitem_t **)p - itemlist;
		*(int *)p = index;
		break;

	case F_CAST_MEMORY:
		if ( *(cast_memory_t **)p == NULL)
			index = -1;
		else
			index = *(cast_memory_t **)p - g_cast_memory;
		*(int *)p = index;
		break;

	//relative to code segment
	case F_FUNCTION:
		if (*(byte **)p == NULL)
			index = 0;
		else
			index = *(byte **)p - ((byte *)InitGame);
		*(int *)p = index;
		break;

	//relative to data segment
	case F_MMOVE:
		if (*(byte **)p == NULL)
			index = 0;
		else
			index = *(byte **)p - (byte *)&mmove_reloc;
		*(int *)p = index;
		break;

	default:
		gi.error ("WriteEdict: unknown field type");
	}
}


void WriteField2 (FILE *f, field_t *field, byte *base)
{
	int			len;
	void		*p;

	if (field->flags & FFL_SPAWNTEMP)
		return;

	p = (void *)(base + field->ofs);
	switch (field->type)
	{
	case F_LSTRING:
		if ( *(char **)p )
		{
			len = strlen(*(char **)p) + 1;
			fwrite (*(char **)p, len, 1, f);
		}
		break;
	}
}

void ReadField (FILE *f, field_t *field, byte *base)
{
	void		*p;
	int			len;
	int			index;

	if (field->flags & FFL_SPAWNTEMP)
		return;

	p = (void *)(base + field->ofs);
	switch (field->type)
	{
	case F_INT:
	case F_FLOAT:
	case F_ANGLEHACK:
	case F_VECTOR:
	case F_IGNORE:
		break;

	case F_LSTRING:
		len = *(int *)p;
		if (!len)
			*(char **)p = NULL;
		else
		{
			*(char **)p = gi.TagMalloc (len, TAG_LEVEL);
			fread (*(char **)p, len, 1, f);
		}
		break;
	case F_EDICT:
		index = *(int *)p;
		if ( index == -1 )
			*(edict_t **)p = NULL;
		else
			*(edict_t **)p = &g_edicts[index];
		break;
	case F_CLIENT:
		index = *(int *)p;
		if ( index == -1 )
			*(gclient_t **)p = NULL;
		else
			*(gclient_t **)p = &game.clients[index];
		break;
	case F_ITEM:
		index = *(int *)p;
		if ( index == -1 )
			*(gitem_t **)p = NULL;
		else
			*(gitem_t **)p = &itemlist[index];
		break;

	case F_CAST_MEMORY:
		index = *(int *)p;
		if ( index == -1 )
			*(cast_memory_t **)p = NULL;
		else
			*(cast_memory_t **)p = &g_cast_memory[index];
		break;

	//relative to code segment
	case F_FUNCTION:
		index = *(int *)p;
		if ( index == 0 )
			*(byte **)p = NULL;
		else
			*(byte **)p = ((byte *)InitGame) + index;
		break;

	//relative to data segment
	case F_MMOVE:
		index = *(int *)p;
		if (index == 0)
			*(byte **)p = NULL;
		else
			*(byte **)p = (byte *)&mmove_reloc + index;
		break;

	default:
		gi.error ("ReadEdict: unknown field type");
	}
}

//=========================================================

/*
==============
WriteClient

All pointer variables (except function pointers) must be handled specially.
==============
*/
void WriteClient (FILE *f, gclient_t *client)
{
	field_t		*field;
	gclient_t	temp;
	
	// all of the ints, floats, and vectors stay as they are
	temp = *client;

	// change the pointers to lengths or indexes
	for (field=clientfields ; field->name ; field++)
	{
		WriteField1 (f, field, (byte *)&temp);
	}

	// write the block
	fwrite (&temp, sizeof(temp), 1, f);

	// now write any allocated data following the edict
	for (field=clientfields ; field->name ; field++)
	{
		WriteField2 (f, field, (byte *)client);
	}
}

/*
==============
ReadClient

All pointer variables (except function pointers) must be handled specially.
==============
*/
void ReadClient (FILE *f, gclient_t *client)
{
	field_t		*field;

	fread (client, sizeof(*client), 1, f);

	for (field=clientfields ; field->name ; field++)
	{
		ReadField (f, field, (byte *)client);
	}
}

/*
============
WriteGame

This will be called whenever the game goes to a new level,
and when the user explicitly saves the game.

Game information include cross level data, like multi level
triggers, help computer info, and all client states.

A single player death will automatically restore from the
last save position.
============
*/
void WriteGame (char *filename, qboolean autosave)
{
	FILE	*f;
	int		i;
	char	str[16];

	if (!autosave)
		SaveClientData ();

	f = fopen (filename, "wb");
	if (!f)
		gi.error ("Couldn't open %s", filename);

	memset (str, 0, sizeof(str));
	strcpy (str, __DATE__);
	fwrite (str, sizeof(str), 1, f);

	game.autosaved = autosave;
	fwrite (&game, sizeof(game), 1, f);
	game.autosaved = false;

	for (i=0 ; i<game.maxclients ; i++)
		WriteClient (f, &game.clients[i]);

	fclose (f);
}

void ReadGame (char *filename)
{
	FILE	*f;
	int		i;
	char	str[16];

	gi.FreeTags (TAG_GAME);

	f = fopen (filename, "rb");
	if (!f)
		gi.error ("Couldn't open %s", filename);

	fread (str, sizeof(str), 1, f);
	if (strcmp (str, __DATE__))
	{
		fclose (f);
		gi.error ("Savegame from an older version.\n");
	}

	g_edicts =  gi.TagMalloc (game.maxentities * sizeof(g_edicts[0]), TAG_GAME);
	globals.edicts = g_edicts;

	g_cast_memory = gi.TagMalloc (MAX_CHARACTERS * MAX_CHARACTERS * sizeof(cast_memory_t), TAG_GAME );
	memset( g_cast_memory, 0, MAX_CHARACTERS * MAX_CHARACTERS * sizeof(cast_memory_t) );

	g_cast_groups = gi.TagMalloc (MAX_CAST_GROUPS * sizeof(cast_group_t), TAG_GAME );
	memset( g_cast_groups, 0, MAX_CAST_GROUPS * sizeof(cast_group_t) );

	fread (&game, sizeof(game), 1, f);
	game.clients = gi.TagMalloc (game.maxclients * sizeof(game.clients[0]), TAG_GAME);
	for (i=0 ; i<game.maxclients ; i++)
		ReadClient (f, &game.clients[i]);

	fclose (f);
}

//==========================================================


/*
==============
WriteEdict

All pointer variables (except function pointers) must be handled specially.
==============
*/
void WriteEdict (FILE *f, edict_t *ent)
{
	field_t		*field;
	edict_t		temp;

	// all of the ints, floats, and vectors stay as they are
	temp = *ent;

	// change the pointers to lengths or indexes
	for (field=fields ; field->name ; field++)
	{
		WriteField1 (f, field, (byte *)&temp);
	}

	temp.last_voice = NULL;	// this can't be saved

	// write the block
	fwrite (&temp, sizeof(temp), 1, f);

	// now write any allocated data following the edict
	for (field=fields ; field->name ; field++)
	{
		WriteField2 (f, field, (byte *)ent);
	}

}

/*
==============
WriteLevelLocals

All pointer variables (except function pointers) must be handled specially.
==============
*/
void WriteLevelLocals (FILE *f)
{
	field_t		*field;
	level_locals_t		temp;

	// all of the ints, floats, and vectors stay as they are
	temp = level;

	// change the pointers to lengths or indexes
	for (field=levelfields ; field->name ; field++)
	{
		WriteField1 (f, field, (byte *)&temp);
	}

	// write the block
	fwrite (&temp, sizeof(temp), 1, f);

	// now write any allocated data following the edict
	for (field=levelfields ; field->name ; field++)
	{
		WriteField2 (f, field, (byte *)&level);
	}
}

/*
==============
WriteCastMemories
==============
*/
void WriteCastMemories (FILE *f)
{
	field_t		*field;
	cast_memory_t	temp;
	int			i, j, out;

	for (i=0; i<MAX_CHARACTERS; i++)
	{
		for (j=0; j<MAX_CHARACTERS; j++)
		{
			if (!g_cast_memory[i * MAX_CHARACTERS + j].cast_ent)
				continue;

			memcpy( &temp, &(g_cast_memory[i * MAX_CHARACTERS + j]), sizeof(cast_memory_t) );

			// write the index number
			out = i * MAX_CHARACTERS + j;
			fwrite (&out, sizeof(out), 1, f);

			// change the pointers to lengths or indexes
			for (field=castmemoryfields ; field->name ; field++)
			{
				WriteField1 (f, field, (byte *)(&temp));
			}

			// write the block
			fwrite (&temp, sizeof(cast_memory_t), 1, f);

			// now write any allocated data following the edict
			for (field=castmemoryfields ; field->name ; field++)
			{
				WriteField2 (f, field, (byte *)(&(g_cast_memory[i * MAX_CHARACTERS + j])));
			}

		}
	}

	out = -1;
	fwrite (&out, sizeof(out), 1, f);
}

/*
==============
WriteCastGroups
==============
*/
void WriteCastGroups (FILE *f)
{
	// write the block
	fwrite (g_cast_groups, sizeof(cast_group_t) * MAX_CAST_GROUPS, 1, f);
}

/*
==============
ReadCastGroups
==============
*/
void ReadCastGroups (FILE *f)
{
	// write the block
	fread (g_cast_groups, sizeof(cast_group_t) * MAX_CAST_GROUPS, 1, f);
}


/*
==============
ReadEdict

All pointer variables (except function pointers) must be handled specially.
==============
*/
void ReadEdict (FILE *f, edict_t *ent)
{
	field_t		*field;

	// Ridah, save the object_bounds
	int		object_bounds[MAX_MODEL_PARTS][MAX_MODELPART_OBJECTS];
	int		i;

	for (i=0; i<MAX_MODEL_PARTS; i++)
		memcpy( object_bounds[i], ent->s.model_parts[i].object_bounds, sizeof(int)*MAX_MODELPART_OBJECTS );

	fread (ent, sizeof(*ent), 1, f);

	for (field=fields ; field->name ; field++)
	{
		ReadField (f, field, (byte *)ent);
	}

	// Ridah, restore object_bounds
	for (i=0; i<MAX_MODEL_PARTS; i++)
		memcpy( ent->s.model_parts[i].object_bounds, object_bounds[i], sizeof(int)*MAX_MODELPART_OBJECTS );
}

/*
==============
ReadLevelLocals

All pointer variables (except function pointers) must be handled specially.
==============
*/
void ReadLevelLocals (FILE *f)
{
	field_t		*field;
	
	int			i, j;

	fread (&level, sizeof(level), 1, f);

	for (field=levelfields ; field->name ; field++)
	{
		ReadField (f, field, (byte *)&level);
	}

	// setup the global cast memory
	for (i=0; i<MAX_CHARACTERS; i++)
	{
		for (j=0; j<MAX_CHARACTERS; j++)
		{
			if (g_cast_memory[i * MAX_CHARACTERS + j].cast_ent)
			{
				level.global_cast_memory[i][j] = &(g_cast_memory[i * MAX_CHARACTERS + j]);
			}
		}
	}
}

/*
==============
ReadCastMemories

All pointer variables (except function pointers) must be handled specially.
==============
*/
void ReadCastMemories (FILE *f)
{
	field_t		*field;
	int			i;

	while (1)
	{
		fread (&i, sizeof(i), 1, f);

		if (i < 0)
			break;

		fread (&(g_cast_memory[i]), sizeof(cast_memory_t), 1, f);

		for (field=castmemoryfields ; field->name ; field++)
		{
			ReadField (f, field, (byte *)&(g_cast_memory[i]) );
		}
	}
}

/*
=================
WriteLevel

=================
*/
void WriteLevel (char *filename)
{
	int		i;
	edict_t	*ent;
	FILE	*f;
	void	*base;
// BEGIN:	Xatrix/Ridah/Navigator/18-apr-1998
	active_node_data_t *node_data;
// END:		Xatrix/Ridah/Navigator/18-apr-1998

	f = fopen (filename, "wb");
	if (!f)
		gi.error ("Couldn't open %s", filename);

// BEGIN:	Xatrix/Ridah/Navigator/18-apr-1998
	// don't save the nav data
	node_data = level.node_data;
	level.node_data = NULL;
// END:		Xatrix/Ridah/Navigator/18-apr-1998

	// write out edict size for checking
	i = sizeof(edict_t);
	fwrite (&i, sizeof(i), 1, f);

	// write out a function pointer for checking
	base = (void *)InitGame;
	fwrite (&base, sizeof(base), 1, f);

	// write the team data
	WriteCastGroups (f);

	// write out the cast_memory data
	WriteCastMemories (f);

	// write out level_locals_t
	WriteLevelLocals (f);

	// write out all the entities
	for (i=0 ; i<globals.num_edicts ; i++)
	{
		ent = &g_edicts[i];
		if (!ent->inuse)
			continue;
		fwrite (&i, sizeof(i), 1, f);
		WriteEdict (f, ent);
	}
	i = -1;
	fwrite (&i, sizeof(i), 1, f);


	// write the cast_memory data


	fclose (f);

// BEGIN:	Xatrix/Ridah/Navigator/18-apr-1998
	// restore the nav data
	level.node_data = node_data;
// END:		Xatrix/Ridah/Navigator/18-apr-1998

}


/*
=================
ReadLevel

SpawnEntities will allready have been called on the
level the same way it was when the level was saved.

That is necessary to get the baselines
set up identically.

The server will have cleared all of the world links before
calling ReadLevel.

No clients are connected yet.
=================
*/

qboolean	changing_levels=false;

void ReadLevel (char *filename)
{
	int		entnum;
	FILE	*f;
	int		i;
	void	*base;
	edict_t	*ent;

// BEGIN:	Xatrix/Ridah/Navigator/18-apr-1998
	// restore nav data
	active_node_data_t *node_data;
// END:		Xatrix/Ridah/Navigator/18-apr-1998

	f = fopen (filename, "rb");
	if (!f)
		gi.error ("Couldn't open %s", filename);

	// free any dynamic memory allocated by loading the level
	// base state
	gi.FreeTags (TAG_LEVEL);

	gi.ClearObjectBoundsCached();	// make sure we wipe the cached list

	num_object_bounds = 0;
	memset (g_objbnds, 0, sizeof(g_objbnds));

	// wipe all the entities
	memset (g_edicts, 0, game.maxentities*sizeof(g_edicts[0]));
	globals.num_edicts = maxclients->value+1;

	memset( g_cast_memory, 0, MAX_CHARACTERS * MAX_CHARACTERS * sizeof(cast_memory_t) );
	memset( g_cast_groups, 0, MAX_CAST_GROUPS * sizeof(cast_group_t) );

	// check edict size
	fread (&i, sizeof(i), 1, f);
	if (i != sizeof(edict_t))
	{
		fclose (f);
		gi.error ("ReadLevel: mismatched edict size");
	}

	// check function pointer base address
	fread (&base, sizeof(base), 1, f);
#ifdef _WIN32
	if (base != (void *)InitGame)
	{
		fclose (f);
		gi.error ("ReadLevel: function pointers have moved");
	}
#else
	gi.dprintf("Function offsets %d\n", ((byte *)base) - ((byte *)InitGame));
#endif

// BEGIN:	Xatrix/Ridah/Navigator/18-apr-1998
	// save nav data
	node_data = level.node_data;
	level.node_data = NULL;
// END:		Xatrix/Ridah/Navigator/18-apr-1998

	// read the team data
	ReadCastGroups (f);

	// load the cast memories
	ReadCastMemories (f);

	// load the level locals
	ReadLevelLocals (f);

// BEGIN:	Xatrix/Ridah/Navigator/18-apr-1998
	// restore nav data
	level.node_data = node_data;

	// upon changing levels, the nav data is cleared, but when loading or starting a new game,
	// the node data is loading in SpawnEntities()
	if (!node_data)
	{
		level.node_data = gi.TagMalloc (sizeof (active_node_data_t), TAG_GAME);
		NAV_ReadActiveNodes (level.node_data, level.mapname);
	}
// END:		Xatrix/Ridah/Navigator/18-apr-1998

	// load all the entities
	while (1)
	{

		if (fread (&entnum, sizeof(entnum), 1, f) != 1)
		{
			fclose (f);
			gi.error ("ReadLevel: failed to read entnum");
		}
		if (entnum == -1)
			break;
		if (entnum >= globals.num_edicts)
			globals.num_edicts = entnum+1;

		ent = &g_edicts[entnum];

		ReadEdict (f, ent);

		// Ridah, restore the object bounds data
		for (i=0; i<MAX_MODEL_PARTS; i++)
		{
			if (ent->s.model_parts[i].objectbounds_filename)
			{
				gi.GetObjectBounds( ent->s.model_parts[i].objectbounds_filename, &ent->s.model_parts[i] );
			}
		}

// BEGIN:	Xatrix/Ridah/Navigator/16-apr-1998
		// Init Navigational data for this entity
		ent->active_node_data = level.node_data;
		ent->nav_data.cache_node = -1;
		ent->nav_build_data = NULL;		// make sure it's null, since it'll be set in ClientConnect() anyway
// END:		Xatrix/Ridah/Navigator/16-apr-1998

		// let the server rebuild world links for this ent
		memset (&ent->area, 0, sizeof(ent->area));
		gi.linkentity (ent);
	}

	fclose (f);

	// mark all clients as unconnected
	for (i=0 ; i<maxclients->value ; i++)
	{
		ent = &g_edicts[i+1];
		ent->client = game.clients + i;
		ent->client->pers.connected = false;
	}

	// init the characters array (we'll set it manually
	memset( level.characters, 0, 4 * MAX_CHARACTERS );

	// always set the client first
	level.characters[0] = &g_edicts[1];

	// do any load time things at this point
	for (i=0 ; i<globals.num_edicts ; i++)
	{
		ent = &g_edicts[i];

		if (!ent->inuse)
			continue;

		// set the character array
		if (((ent->svflags & SVF_MONSTER) && (ent->character_index > 0)) || ent->client)
		{
			level.characters[ent->character_index] = ent;
		}

		// fire any cross-level triggers
		if (ent->classname)
			if (strcmp(ent->classname, "target_crosslevel_target") == 0)
				ent->nextthink = level.time + ent->delay;

		// JOSEPH 19-JAN-99
		// Restore rotating train absmax absmin
		if (!strcmp(ent->classname, "func_train_rotating"))
		{
			float		max, v;
			int			i;

			max = 0;
			for (i=0 ; i<3 ; i++)
			{
				v =fabs(ent->mins[i]);
				if (v > max)
					max = v;
				v =fabs(ent->maxs[i]);
				if (v > max)
					max = v;
			}
			for (i=0 ; i<3 ; i++)
			{
				ent->absmin[i] = ent->s.origin[i] - max;
				ent->absmax[i] = ent->s.origin[i] + max;
			}
		}
		// END JOSEPH		

		// Ridah, restore nextthink times for rain/snow clouds so they send the message to clients (this is ugly, but should work)
		if (	!strcmp( ent->classname, "elements_raincloud" )
			||	!strcmp( ent->classname, "elements_snowcloud" ))
		{
			ent->nextthink = level.time + (10 * FRAMETIME);
		}
	}


	if (changing_levels)
	{
		int	i;
		edict_t	*e;

		// kill any followers
		for (i=0; i<level.num_characters; i++)
		{
			e = level.characters[i];

			if (!e)
				continue;

			if (e->flags & FL_FOLLOWING)
			{
				// vanish!
				AI_UnloadCastMemory( e );
				G_FreeEdict( e );
			}
		}

	}
	else	// clear any following flags
	{
		int	i;
		edict_t	*e;

		// kill any followers
		for (i=0; i<level.num_characters; i++)
		{
			e = level.characters[i];

			if (!e)
				continue;

			e->flags &= ~FL_FOLLOWING;
		}
	}

}
