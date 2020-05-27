
#include "g_local.h"
#include "m_player.h"

#include "voice_punk.h"
#include "voice_bitch.h"

//------------------------------------------------------------------------------------

edict_t *ban_target, *ban_source, *ban_thinker;
int		ban_count;
char	ban_ip[MAX_QPATH];	// make sure we don't kick a different user
float	last_ban_time;
char	ban_id;		// so we only allow each person to vote once per ban
char	last_kick_ip[MAX_QPATH];
int		ban_player_count=0;

void Cmd_Players_f (edict_t *ent);

qboolean BanEnoughVotes(void)
{
	edict_t *trav;
	int	need;

	trav = &g_edicts[1];

	while (trav <= &g_edicts[(int)maxclients->value])
	{
		if (trav->inuse && trav->client /*&& (trav != ban_target)*/
			&&	(!teamplay->value || !ban_target->client || !ban_target->client->pers.team || (ban_target->client->pers.team == trav->client->pers.team)))
		{
			ban_player_count++;
		}

		trav++;
	}

//	if (teamplay->value)
//		need = (int)floor(ban_player_count / 2);
//	else
		need = (int)ceil(ban_player_count / 2);

	if (need < 3)
		need = 3;

	return (ban_count >= need);
}

void BanThink(edict_t *ent)
{
	char	*ip;

	if (!ban_target || !ban_target->inuse || !ban_target->client)
	{
		ban_target = NULL;
		G_FreeEdict(ent);
		return;
	}

	if (ban_id != ent->count)
	{
		// another ban has formed
		G_FreeEdict(ent);
		return;
	}

	// check the IP is the same
	ip = Info_ValueForKey( ban_target->client->pers.userinfo, "ip" );
	if (ip && ip[0])
	{
		if (strcmp(ip, ban_ip))
		{
			ban_target = NULL;
			G_FreeEdict(ent);
			return;
		}
	}
			
	// if we have enough, cancel the kick request
	if (!BanEnoughVotes())
	{
		if (ban_source->inuse)
			gi.cprintf( ban_source, PRINT_HIGH, "Vote did not succeed.\n" );
		ban_target = NULL;
		G_FreeEdict(ent);
		return;
	}

	// kick them
	gi.bprintf( PRINT_HIGH, "%s was kicked by unanimous vote (next time they will be banned).\n", ban_target->client->pers.netname );

	if (!strcmp(ban_ip, last_kick_ip))
	{	// ban them
		gi.bprintf( PRINT_HIGH, "Blocking %s from returning to game.\n", ban_target->client->pers.netname );
		gi.AddCommandString(va("sv addip %s\n", ban_ip));
	}

	gi.AddCommandString(va("kick %i\n", (int)(ban_target - g_edicts - 1)));

	strcpy( last_kick_ip, ban_ip );

	ban_target = NULL;
	G_FreeEdict(ent);
}

void Cmd_Response_f (edict_t *ent)
{
	char	*ip;

	if (!ban_target)
	{
		gi.cprintf( ent, PRINT_HIGH, "Nothing to \"%s\" with.\n", gi.argv(0) );
		return;
	}

	if (ent == ban_target)
		return;

	if (ent->client->resp.ban_id == ban_id)
	{
		gi.cprintf( ent, PRINT_HIGH, "You've already voted once.\n" );
		return;
	}

	if (!ban_target->inuse || !ban_target->client)
	{
		gi.cprintf( ent, PRINT_HIGH, "The player has already left.\n" );
		ban_target = NULL;
		return;
	}

	if (teamplay->value && ban_target->client->pers.team && (ban_target->client->pers.team != ent->client->pers.team))
	{
		gi.cprintf( ent, PRINT_HIGH, "You cannot vote, %s is not on your team.\n", ban_target->client->pers.netname );
		return;
	}

	// don't let us vote if we were just kicked
	ip = Info_ValueForKey( ent->client->pers.userinfo, "ip" );
	if (ip && ip[0])
	{
		if (!strcmp(ip, last_kick_ip))
		{
			gi.cprintf( ent, PRINT_HIGH, "You cannot vote.\n" );
			return;
		}
	}


	ip = Info_ValueForKey( ban_target->client->pers.userinfo, "ip" );
	if (!ip)
	{
		gi.cprintf( ent, PRINT_HIGH, "%s has an unknown IP address\n", ban_target->client->pers.netname );
		ban_target = NULL;
		return;
	}
	if (strcmp(ip, ban_ip))
	{
		gi.cprintf( ent, PRINT_HIGH, "The player has left or been replaced with another player\n" );
		ban_target = NULL;
		return;
	}

	if (!strcmp(gi.argv(0), "no"))
	{
		if (ban_source->inuse)
			gi.cprintf( ban_source, PRINT_HIGH, "The vote did not succeed.\n" );

		gi.cprintf(ent, PRINT_HIGH, "Objection noted.\n" );

		ent->client->resp.ban_id = ban_id;
		ban_count--;
		return;
	}

	ent->client->resp.ban_id = ban_id;
	ban_count++;

	if (BanEnoughVotes())
	{
		ban_thinker->think(ban_thinker);
	}
	else
	{
		gi.cprintf(ent, PRINT_HIGH, "Vote recorded, awaiting votes from other players.\n" );
	}

}

void Vote_Ban( edict_t *ent, char *name )
{
	edict_t *target;
	int		i;
	char	*ip;

	if (ent->client->resp.last_ban && (ent->client->resp.last_ban > (level.time - 60)))
	{
		gi.cprintf( ent, PRINT_HIGH, "You can only VOTE once per 60 seconds\n" );
		return;
	}

	if (last_ban_time)
	{
		if (last_ban_time > level.time)
		{
			last_ban_time = 0;
		}

		if (last_ban_time > (level.time - 20))
		{
			gi.cprintf( ent, PRINT_HIGH, "Only one VOTE per 20 seconds allowed\n" );
			return;
		}
	}

	// find the player
	if (((i = atoi(name)) > 0) && i <= maxclients->value)
	{
		if (!g_edicts[i].inuse || !g_edicts[i].client)
		{	// fail
			gi.cprintf( ent, PRINT_HIGH, "\nUnable to match id '%i' with a current player.\n\nValid player id's are:\n\n", i );
			Cmd_Players_f(ent);
			return;
		}

		target = &g_edicts[i];
	}
	else	// scan for the name
	{
		for (i=1; i<=maxclients->value; i++)
		{
			target = &g_edicts[i];

			if (!target->inuse)
				continue;
			if (!target->client)
				continue;

			if (!Q_strcasecmp( target->client->pers.netname, name ))
				break;
		}

		if (i>maxclients->value)
		{
			gi.cprintf( ent, PRINT_HIGH, "\nUnable to match '%s' with a current player.\n\nTry using a player id from the following list (eg. 'vote ban 4'):\n\n", name );
			Cmd_Players_f(ent);
			return;
		}
	}
	
	// can't kick someone on the other team
	if (teamplay->value && target->client->pers.team && (target->client->pers.team != ent->client->pers.team))
	{
		gi.cprintf( ent, PRINT_HIGH, "You cannot kick a member of the other team.\n" );
		return;
	}


	// vote for them
	ip = Info_ValueForKey( target->client->pers.userinfo, "ip" );
	if (!ip || !ip[0])
	{
		gi.cprintf( ent, PRINT_HIGH, "%s has an unknown IP address\n", name );
		return;
	}
	if (!strcmp(ip, "loopback"))
	{
		gi.cprintf( ent, PRINT_HIGH, "%s is running the server, cannot BAN host\n", name );
		return;
	}

	strcpy( ban_ip, ip );

	ent->client->resp.ban_id = ++ban_id;
	ent->client->resp.last_ban = level.time;
	last_ban_time = level.time;
	ban_count = 1;

	ban_source = ent;
	ban_target = target;

	gi.cprintf( ent, PRINT_HIGH, "You have voted to kick/ban %s.\nAwaiting responses from other players.\n", ban_target->client->pers.netname );

	gi.dprintf( "%s formed a vote to kick/ban %s.\n", ent->client->pers.netname, ban_target->client->pers.netname );
		
	// start the thinker
	target = G_Spawn();
	target->owner = ban_target;
	target->think = BanThink;
	target->nextthink = level.time + 15;
	target->count = ban_id;

	ban_thinker = target;

	BanEnoughVotes();

	// now tell everyone except this player
	for (i=1; i<=(int)maxclients->value; i++)
	{
		if (!g_edicts[i].client)
			continue;
		if (!g_edicts[i].inuse)
			continue;
		if (&g_edicts[i] == ent)
			continue;
		if (&g_edicts[i] == ban_target)
			continue;
		if (teamplay->value && ban_target->client->pers.team && (ban_target->client->pers.team != g_edicts[i].client->pers.team))
			continue;

		gi.cprintf( &g_edicts[i], PRINT_CHAT, ">> %s has voted to BAN %s. Type 'yes' in the consol if you agree, 'no' if you disagree. %i votes required.", ent->client->pers.netname, ban_target->client->pers.netname, ban_player_count );
	}
}

void Cmd_Vote_f (edict_t *ent)
{
	char	*cmd, *name;

	cmd = gi.argv(1);

	if (!strcmp( cmd, "ban" ))
	{
		name = gi.argv(2);

		if (!name[0])
		{
			gi.cprintf( ent, PRINT_HIGH, "You must supply a name\n" );
			return;
		}

		Vote_Ban( ent, name );
	}
	else
	{
		gi.cprintf( ent, PRINT_HIGH, "Unknown voting command.\n" );
	}

}

//------------------------------------------------------------------------------------

// BEGIN:	Xatrix/Ridah/Navigator/23-mar-1998
int		showpath_on=false;
edict_t	*showpath_ent;

void Cmd_NavDebugDest_f (edict_t *ent)
{
	if (deathmatch->value)
	{
		gi.cprintf(ent, PRINT_HIGH, "This command only available when deathmatch = 0\n");
		return;
	}

	if (!showpath_ent)
	{	// spawn it
		showpath_ent = G_Spawn();
		showpath_ent->s.modelindex = 255;
	}

	VectorCopy( ent->s.origin, showpath_ent->s.origin );
	gi.linkentity(showpath_ent);
}

void Cmd_NavDebugShowPath_f (edict_t *ent)
{
	if (deathmatch->value)
	{
		gi.cprintf(ent, PRINT_HIGH, "This command only available when deathmatch = 0\n");
		return;
	}
/*
	if (!ent->nav_build_data)
	{
		gi.cprintf(ent, PRINT_HIGH, "nav_dynamic 1 must be set to use this command\n");
		return;
	}
*/
	if (!(showpath_on))
	{		// enable path

//		if (!ent->nav_build_data->debug_dest)
		{	// create it
			Cmd_NavDebugDest_f (ent);
		}

		showpath_on = true;
//		ent->nav_build_data->flags |= NBD_SHOWPATH;
	}
	else	// disable path
	{
		showpath_on = false;
//		ent->nav_build_data->flags &= ~NBD_SHOWPATH;

		// kill the destination entity
		G_FreeEdict(showpath_ent);
		showpath_ent = NULL;
	}
}

// Clears the nav_data for the current level
void Cmd_NavClear_f ( edict_t *self )
{
	if (deathmatch->value)
	{
		gi.cprintf(self, PRINT_HIGH, "This command only available when deathmatch = 0\n");
		return;
	}

	// clear the current nodes
	level.node_data->modified = false;
	NAV_PurgeActiveNodes ( level.node_data );

	// create the node data structure
	level.node_data = gi.TagMalloc (sizeof (active_node_data_t), TAG_GAME);
	NAV_InitActiveNodes	( level.node_data );
	NAV_WriteActiveNodes ( level.node_data, level.mapname );

	gi.AddCommandString( "echo \necho Cleared Navigational Data, closing down server.\necho \ndisconnect\n" );
}

// END:		Xatrix/Ridah/Navigator/23-mar-1998

//--------------------------------------------------------
// TEAMPLAY commands
extern void ClientBeginDeathmatch (edict_t *ent);

void Cmd_Spec_f (edict_t *self)
{
	if (!teamplay->value)
	{
		gi.cprintf(self, PRINT_HIGH, "This command only available when teamplay is enabled\n");
		return;
	}
	
	if (!self->client->pers.team)
		return;

	self->client->pers.team = 0;
	
	self->flags &= ~FL_GODMODE;
	self->health = 0;
	meansOfDeath = MOD_SUICIDE;
	player_die (self, self, self, 1, vec3_origin, 0, 0);

	ClientBeginDeathmatch( self );	
}

void Cmd_Join_f (edict_t *self, char *teamcmd)
{
	int	i;
	char str1[MAX_QPATH], varteam[MAX_QPATH];

	if (!teamplay->value)
	{
		gi.cprintf(self, PRINT_HIGH, "This command only available when teamplay is enabled\n");
		return;
	}

	strcpy( varteam, teamcmd );

	// search for the team-name

	if (varteam && varteam[0])
	{
		for (i=1; team_names[i]; i++)
		{
			strcpy(str1, team_names[i]);
			kp_strlwr(str1);
			kp_strlwr(varteam);

			if (strstr( str1, varteam ) == str1)
			{	// found a match

				if (self->client->pers.team == i)
				{
					gi.cprintf( self, PRINT_HIGH, "Already a member of %s\n", team_names[i] );
				}
				else
				{
					// kill us if currently in game
					if (self->client->pers.team)
					{
						self->flags &= ~FL_GODMODE;
						self->health = 0;
						meansOfDeath = MOD_SUICIDE;
						player_die (self, self, self, 1, vec3_origin, 0, 0);
					}

					if (!Teamplay_ValidateJoinTeam( self, i ))
					{
						gi.cprintf( self, PRINT_HIGH, "Unable to join %s\n", team_names[i] );
					}
				}

				return;
			}
		}

		gi.cprintf( self, PRINT_HIGH, "Un-matched team: %s\n", varteam );
	}
}

//--------------------------------------------------------

void Cmd_GetTexture_f (edict_t *self)
{
	vec3_t	start, end;
	vec3_t	fwd;
	trace_t	tr;

	if (deathmatch->value)
	{
		gi.cprintf(self, PRINT_HIGH, "This command only available when deathmatch = 0\n");
		return;
	}

	// trace a line and print the texture we hit
	AngleVectors( self->client->v_angle, fwd, NULL, NULL );
	VectorCopy( self->s.origin, start );
	start[2] += self->viewheight;

	VectorMA( start, 2048, fwd, end );

	tr = gi.trace( start, NULL, NULL, end, self, MASK_SOLID - CONTENTS_MONSTER );

	if (tr.fraction < 1 && tr.surface && tr.surface->name)
	{
		if (tr.surface->value > ((int)(level.time*10) - 3))
		{
			gi.cprintf( self, PRINT_HIGH, "Saving texture: %s\n", tr.surface->name );

			{
				cvar_t	*game_dir, *base_dir;
				char	filename[MAX_QPATH], dir[MAX_QPATH];
				FILE	*f;

				game_dir = gi.cvar("game", "", 0);
				base_dir = gi.cvar("basedir", "", 0);

				// dir, eg: .\main\maps
				strcpy( dir, base_dir->string);
				strcat( dir, DIR_SLASH);

				strcat( dir, "source");
				strcat( dir, DIR_SLASH);
				strcat( dir, "ref_gl");

				// filename, eg: .\main\maps\skidrow.pnt
				strcpy( filename, dir);
				strcat( filename, DIR_SLASH);
				strcat( filename, "specular_textures.h");

				// try and open the file for writing
				f = fopen ( filename, "a+b");
				if (!f)
				{
					gi.cprintf ( self, PRINT_HIGH, "Couldn't open %s for writing.\n", filename);
					return;
				}

				fprintf( f, "\"%s\",\n", tr.surface->name );

				fclose( f );

				gi.cprintf ( self, PRINT_HIGH, "Saved.\n" );
			}
		}
		else
		{
			gi.cprintf( self, PRINT_HIGH, "Hit texture: %s\n", tr.surface->name );
		}

		tr.surface->value = (int)(level.time*10);
	}
}

void Cmd_GearUp_f (edict_t *self)
{
	vehicle_t *vehicle;

	if (!self->vehicle_index)
	{
		gi.cprintf( self, PRINT_HIGH, "You aren't in a vehicle, can't change gears.\n");
		return;
	}

	vehicle = &global_vehicles[self->vehicle_index - 1];

	vehicle->gear++;
	if (vehicle->gear == vehicle->def->gearbox->num_gears)
		vehicle->gear--;

}

void Cmd_GearDown_f (edict_t *self)
{
	vehicle_t *vehicle;

	if (!self->vehicle_index)
	{
		gi.cprintf( self, PRINT_HIGH, "You aren't in a vehicle, can't change gears.\n");
		return;
	}

	vehicle = &global_vehicles[self->vehicle_index - 1];

	vehicle->gear--;
	if (vehicle->gear < 0)
		vehicle->gear = vehicle->def->gearbox->num_gears - 1;
}

// Saves the current LightPaint data
void Cmd_BurnSave_f (edict_t *self)
{
	cvar_t	*game_dir, *base_dir;
	char	filename[MAX_QPATH], dir[MAX_QPATH];
	int		i;
	FILE	*f;

	if (deathmatch->value)
	{
		gi.cprintf(self, PRINT_HIGH, "This command only available when deathmatch = 0\n");
		return;
	}

	game_dir = gi.cvar("game", "", 0);
	base_dir = gi.cvar("basedir", "", 0);

	// dir, eg: .\main\maps
	strcpy( dir, base_dir->string);
	strcat( dir, DIR_SLASH);

	if (strlen(game_dir->string) == 0)
		strcat( dir, "main");
	else
		strcat( dir, game_dir->string);

	strcat( dir, DIR_SLASH);
	strcat( dir, "maps");

	// filename, eg: .\main\maps\skidrow.pnt
	strcpy( filename, dir);
	strcat( filename, DIR_SLASH);
	strcat( filename, level.mapname);
	strcat( filename, ".pnt");

	// try and open the file for writing
	f = fopen ( filename, "a+b");
	if (!f)
	{
		gi.cprintf ( self, PRINT_HIGH, "Couldn't open %s for writing.\n", filename);
		return;
	}

	for (i=0; i<num_lpbuf; i++)
	{
		fwrite( lpbuf[i], LP_SIZE, 1, f );

		free( lpbuf[i] );
	}

	num_lpbuf = 0;

	fclose( f );

	gi.cprintf ( self, PRINT_HIGH, "Saved LightPaint to %s.\n", filename);
}

#if 0	// turn this off once we have the tables (not used by actual game code)

//-------------------------------------------------------------
// Ridah, only used to calculate the new x_anorms.h
void Cmd_Anorms_f (void)
{
	#define	NUM_PITCH_STEPS	8

	vec3_t	angles;
	int		step, yawstep;
	int		step_sections[9] = {32,28,24,20,16,12,8,4};

	vec3_t	out_normals[256];
	int		count=0;

	if (maxclients->value > 1)
		return;

	VectorClear( angles );

	// do the positive pitch step
	for (step=0; step < NUM_PITCH_STEPS; step++)
	{

		angles[PITCH] = ((90.0 / NUM_PITCH_STEPS) * (float)step);

		// go around the Z axis

		for (yawstep=0; yawstep < step_sections[step]; yawstep++)
		{

			angles[YAW] = ((360.0 / step_sections[step]) * (float)yawstep);

			AngleVectors( angles, out_normals[count++], NULL, NULL );

		}

	}

	// do the negative pitch step
	for (step=1; step < NUM_PITCH_STEPS; step++)
	{

		angles[PITCH] = ((90.0 / NUM_PITCH_STEPS) * (float)(-step));

		// go around the Z axis

		for (yawstep=0; yawstep < step_sections[step]; yawstep++)
		{

			angles[YAW] = ((360.0 / step_sections[step]) * (float)yawstep);

			AngleVectors( angles, out_normals[count++], NULL, NULL );

		}

	}

	gi.dprintf( "Anorm calculation completed, %i normals produced\n", count );

	{
		char	filename[MAX_QPATH];
		int		i;
		char	str[256];
		FILE	*f;

		// filename, eg: .\gamedir\routes\map01.nav
		strcpy( filename, "\\kingpin\\source\\ref_gl\\x_anorms.h");

		// try and open the file for writing
		f = fopen ( filename, "wb");
		if (!f) gi.error ("Couldn't open %s for writing.", filename);

		for (i=0; i<count; i++)
		{
			sprintf( str, "{%f, %f, %f},\n", out_normals[i][0], out_normals[i][1], out_normals[i][2] );

			fwrite( str, strlen(str), 1, f );
		}

		fclose(f);

		gi.dprintf( "%s saved\n", filename );

	}

}

#define	NUM_ANORMS	162		// old table only has 162

vec3_t	anorms[NUM_ANORMS] = {
#include "../client/anorms.h"
};

void Cmd_Adots_f (void)
{
	int	i, j;
	float	adots[NUM_ANORMS][NUM_ANORMS];

	for (i=0; i<NUM_ANORMS; i++)
	{
		for (j=0; j<NUM_ANORMS; j++)
		{
			adots[i][j] = DotProduct( anorms[i], anorms[j] );
		}
	}

	gi.dprintf( "Adot calculation completed.\n" );

	{
		char	filename[MAX_QPATH];
		int		i;
		char	str[256];
		FILE	*f;

		// filename, eg: .\gamedir\routes\map01.nav
		strcpy( filename, "\\kingpin\\source\\ref_gl\\x_adots.h");

		// try and open the file for writing
		f = fopen ( filename, "wb");
		if (!f) gi.error ("Couldn't open %s for writing.", filename);

		sprintf( str, "{\n" );
		fwrite( str, strlen(str), 1, f );

		for (i=0; i<NUM_ANORMS; i++)
		{

			sprintf( str, "{" );
			fwrite( str, strlen(str), 1, f );

			for (j=0; j<NUM_ANORMS; j++)
			{
				if (j > 0)
				{
					sprintf( str, ", " );
					fwrite( str, strlen(str), 1, f );
				}

				sprintf( str, "%f", adots[i][j] );
				fwrite( str, strlen(str), 1, f );
			}

			sprintf( str, "},\n" );
			fwrite( str, strlen(str), 1, f );

		}

		sprintf( str, "}\n" );
		fwrite( str, strlen(str), 1, f );

		fclose(f);

		gi.dprintf( "%s saved\n", filename );

	}

}

//-------------------------------------------------------------
#endif

// Ridah
extern void ED_CallSpawn (edict_t *ent);

// Caution: if using this to spawn an entity that hasn't been precached, this will cause problems
void Cmd_Spawn_f (edict_t *ent)
{
	edict_t *spawn;
	char *name;
	vec3_t	forward;

	spawn = G_Spawn();

	name = gi.args ();
	spawn->classname = gi.TagMalloc(sizeof(name)+1, TAG_LEVEL);
	strcpy( spawn->classname, name );

	AngleVectors( ent->s.angles, forward, NULL, NULL);
	VectorScale( forward, 64, forward );
	forward[2] += 16;

	VectorAdd( ent->s.origin, forward, spawn->s.origin );
	VectorCopy( ent->s.angles, spawn->s.angles );

	ED_CallSpawn (spawn);
}

//-------------------------------------------------------------

void P_ClearProfanity ( edict_t *ent )
{
	ent->owner->profanity_level = 0;

	G_FreeEdict( ent );
}

void Cmd_Speech_f (edict_t *ent, edict_t *other, char *cmd)
{
	static		float speechtime=0;
	edict_t		*best=NULL;
	cast_memory_t	*mem;

	if (deathmatch->value)
	{
		gi.cprintf (ent, PRINT_HIGH, "No speech in deathmatch\n");
		return;
	}

	if (speechtime > (level.time - TALK_OTHER_DELAY) && speechtime < level.time)
		return;

	if (Q_stricmp (cmd, "key1") == 0)		// NEUTRAL
	{
		// JOSEPH 4-FEB-99 
		ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_POSITIVE;
		ent->client->hud_self_talk_time = level.time + 2.0;
		// END JOSEPH	
		
		if ((other->svflags & SVF_MONSTER) && (other->cast_info.talk))
			best = other;

		if (best)
		{
			mem = level.global_cast_memory[best->character_index][ent->character_index];

			if (!mem)
			{
				AI_RecordSighting( best, ent, VectorDistance( best->s.origin, ent->s.origin ) );
			}

//			if (strcmp (best->classname, "cast_bitch") == 0)
//				Voice_Random( ent, best, f_neutral_talk_player, F_NUM_NEUTRAL_TALK_PLAYER );
//			else
				// Voice_Random( ent, best, neutral_talk_player, NUM_NEUTRAL_TALK_PLAYER );
			Voice_Random( ent, best, neutral_talk_player, 5 );


			// character should turn to us
			best->cast_info.last_talk_turn = level.time;
			best->cast_info.talk_ent = ent;

			AI_CheckTalk( best );
		}
		else
		{
			gi.cprintf(ent, PRINT_HIGH, "No-one to talk to.\n");
		}
	}
	else if (Q_stricmp (cmd, "key3") == 0)		// AGGRESSIVE
	{
		// JOSEPH 4-FEB-99 
		ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_NEGATIVE;
		ent->client->hud_self_talk_time = level.time + 2.0;
		// END JOSEPH
		
		if (	(other->svflags & SVF_MONSTER) 
			&&	(other->cast_info.talk)
			&&	(other->cast_group != ent->cast_group))
		{
			best = other;
		}

		if (best)
		{

			mem = level.global_cast_memory[best->character_index][ent->character_index];

			if (!mem)
			{
				AI_RecordSighting( best, ent, VectorDistance( best->s.origin, ent->s.origin ) );
			}

			mem->flags |= MEMORY_ASSHOLE;

			// Ridah, hack so Momo knows if we swear at him twice
			if (best->name_index == NAME_MOMO)
			{
				if (mem->inc < 3)
				{
					mem->flags &= ~MEMORY_UPSET;	// clear it so we charge them 30 bucks
				}

				// if (ent->episode_flags & EP_SKIDROW_MOMO_ASKED_MONEY)
				// 	mem->inc++;
				EP_CheckMomo (ent, mem);

			}

			if (best->cast_group)
			{
				if (ent->profanity_level == 0)
					Voice_Random( ent, best, player_profanity_level1, NUM_PLAYER_PROFANITY_LEVEL1 );
				else if (ent->profanity_level == 1)
					Voice_Random( ent, best, player_profanity_level2, NUM_PLAYER_PROFANITY_LEVEL2 );
				else
					Voice_Random( ent, best, player_profanity_level3, NUM_PLAYER_PROFANITY_LEVEL3 );

				if (ent->profanity_level < 3)
					ent->profanity_level++;

				if (ent->profanity_level == 3)
				{	// spawn an entity, that will return us to normal profanity in a second
					edict_t *thinkent;

					thinkent = G_Spawn();
					thinkent->think = P_ClearProfanity;
					thinkent->nextthink = level.time + 4.0;
					thinkent->owner = ent;
				}
			}
			else
			{
				Voice_Random( ent, best, player_profanity_level1, NUM_PLAYER_PROFANITY_LEVEL1 );
			}

			// character should turn to us
			best->cast_info.last_talk_turn = level.time;	// so they don't look for AI characters
			best->cast_info.talk_ent = ent;

			AI_CheckTalk( best );
		}
		else
		{
			gi.cprintf(ent, PRINT_HIGH, "No-one to abuse.\n");
		}
	}
	else
	{
//		gi.cprintf( ent, PRINT_HIGH, "Unknown Speech command\n" );
		return;
	}

	speechtime = level.time;

}

/*
==================
Cmd_Order_f

1. hold = Hold Position
2. move = Move Out
3. converge = Converge on my position
===================
*/
edict_t *Order_MoveOut (edict_t *ent);

qboolean FullGang (edict_t *player)
{
	edict_t	*ent;
	cast_memory_t *mem;
	int		i;
	int		cnt = 0;
	
	for (i=1, ent=g_edicts+i ; i < globals.num_edicts ; i++,ent++)
	{
		if (ent->client)
			continue;
		if (!(ent->inuse))
			continue;
		if (ent->deadflag == DEAD_DEAD)
			continue;
		if (ent->cast_group != 1)
			continue;
		
		mem = level.global_cast_memory [ent->character_index][player->character_index];
		
		if (mem && mem->flags & MEMORY_HIRED)
			cnt++;

		if (cnt == 2)
			return true;

	}

	return false;
}


void Cmd_Order_f (edict_t *ent, edict_t *other, char *cmd)
{
	int			flags = 0;
	static		float ordertime=0;
	static		int last_voice;
	qboolean	firstime = false;
	
	if (deathmatch->value)
	{
		gi.cprintf (ent, PRINT_HIGH, "No orders in deathmatch\n");
		return;
	}

	if (Q_stricmp (cmd, "key1") == 0)		// Stay Here
		flags = ORDER_FOLLOWME;
	else if (Q_stricmp (cmd, "key2") == 0)	// Attack
		flags = ORDER_MOVE;
	else if (Q_stricmp (cmd, "key3") == 0)	// Follow
		flags = ORDER_HOLD;

	ent->order = flags;
	ent->order_timestamp = level.time;

//	if (other->cast_info.aiflags & AI_TAKE_COVER)
//		return;	// can't order a hiding dude

	if (ent->client)
	{
		cast_memory_t *cast_memory;

		cast_memory = level.global_cast_memory[other->character_index][ent->character_index];

		if (!EP_HiredGuys (ent, other))
		{
			// Ridah, 21-may-99, so they make a talking jesture if they just said something
			if (other->last_talk_time == level.time)
				other->cast_info.talk( other );

			return;
		}

		if (other->gender == GENDER_MALE)
		{

		// RAFAEL 02-18-99	
		if (!(cast_memory->flags & MEMORY_HIRED)) // if the dude is not hired
		{
			if (flags == ORDER_MOVE)	// not a valid command
				return;

			// if (FullGang (ent)) // if the gang is full
			if (ent->client->pers.friends >= 2)
			{
				if (other->last_talk_time < (level.time - 2) || last_voice != 6)
					Voice_Random (other, ent, &hiredguy_specific[6], 2);

				other->cast_info.talk( other );
				last_voice = 6;
				return;
			}
		}


		if (!(cast_memory->flags & MEMORY_HIRE_FIRST_TIME))
		{
			cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
			{
				int rval;
				rval = abs (other->currentcash);

				// JOSEPH 19-FEB-99
				if (flags == ORDER_FOLLOWME)
				{
					ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_YES;
					ent->client->hud_self_talk_time = level.time + 2.0;
				}
				else if (flags == ORDER_HOLD)
				{
					ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_NO;
					ent->client->hud_self_talk_time = level.time + 2.0;
				}
				// END JOSEPH
				
				// gi.dprintf ("yo man I'll follow ya fer %d bucks\n", rval);

				if (other->last_talk_time < (level.time - 2) || last_voice != 1)
					// this line chooses the correct sound to play.. (even switches between the first and second for consecutive calls)
					Voice_Specific( other, ent, hiredguy_ask, ((rval / 25) * 2) + (hiredguy_ask[((rval / 25) * 2)].last_played > hiredguy_ask[((rval / 25) * 2) + 1].last_played) );


				other->cast_info.talk( other );

				last_voice = 1;

				return;
			}
		}
		
		else if (!(cast_memory->flags & MEMORY_HIRE_ASK))
		{
			// JOSEPH 19-FEB-99
			if (flags == ORDER_FOLLOWME)
			{
				ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_YES;
				ent->client->hud_self_talk_time = level.time + 2.0;
			}
			else if (flags == ORDER_HOLD)
			{
				ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_NO;
				ent->client->hud_self_talk_time = level.time + 2.0;
			}
			// END JOSEPH
			
			if (ent->client->pers.currentcash >= abs (other->currentcash))
			{
				if (flags == ORDER_FOLLOWME)
				{
					cast_memory->flags |= MEMORY_HIRE_ASK;

	//					gi.dprintf ("so ya got the money?\n", abs (other->currentcash));

					if (other->last_talk_time < (level.time - 2) || last_voice != 2)
						// Voice_Specific( other, ent, hiredguy_specific, 0 + (hiredguy_specific[0].last_played > hiredguy_specific[1].last_played) );
						Voice_Random (other, ent, hiredguy_specific, 2);


					other->cast_info.talk( other );
					last_voice = 2;

					return;
				}
				else if (flags == ORDER_HOLD)
				{
	//					gi.dprintf ("yo man I'll be waiting for ya\n");
					if (other->last_talk_time < (level.time - 2) || last_voice != 3)
						// Voice_Specific( other, ent, hiredguy_specific, 4 + (hiredguy_specific[4].last_played > hiredguy_specific[5].last_played) );
						Voice_Random (other, ent, &hiredguy_specific[4], 2);

					other->cast_info.talk( other );
					last_voice = 3;
					return;
				}
				else	// invalid response
				{
					gi.dprintf( "\nInvalid response.\nkey1 = YES\nkey3 = NO\n" );
					return;
				}
			}
			else
			{
	//				gi.dprintf ("yo man come to me when you got %d bucks\n", abs (other->currentcash));
				if (other->last_talk_time < (level.time - 2) || last_voice != 4)
					Voice_Random( other, ent, &hiredguy_specific[11], 3 );

				other->cast_info.talk( other );
				last_voice = 4;
				return;
			}
		}
		
		else if (!(cast_memory->flags & MEMORY_HIRED))
		{
			// JOSEPH 19-FEB-99
			if (flags == ORDER_HOLD)
			{
				ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_NO;
				ent->client->hud_self_talk_time = level.time + 2.0;
			}
			else if (flags == ORDER_FOLLOWME)
			{
				ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_YES;
				ent->client->hud_self_talk_time = level.time + 2.0;
			}
			// END JOSEPH
			
			// JOSEPH 3-FEB-99 
			if (ent->client->pers.currentcash >= abs (other->currentcash))
			{
				if (flags == ORDER_FOLLOWME)
				{	// give them the money
					extern mmove_t	thug_move_crch_grab;

					cast_memory->flags |= MEMORY_HIRED;
					ent->client->pers.currentcash -= abs (other->currentcash);
					
					// other->currentcash = abs(other->currentcash);
					other->currentcash = 0;

					ent->client->pers.friends++;

					if (!strcmp(other->classname, "cast_thug"))
					{
						other->cast_info.currentmove = &thug_move_crch_grab;
					}

					other->cast_info.aiflags |= AI_NOWALK_FACE;

					// we just hired them, by default they should follow us
					flags = ORDER_FOLLOWME;
					firstime = true;

					EP_HiredGuysRegisterFlags (ent, other);
				}
				else if (flags == ORDER_HOLD)
				{
	//					gi.dprintf ("yo man I'll be here if you change your mind\n");
					
					cast_memory->flags &= ~MEMORY_HIRE_ASK;

					if (other->last_talk_time < (level.time - 2) || last_voice != 5)
						Voice_Specific( other, ent, hiredguy_specific, 2 );
					other->cast_info.talk( other );
					last_voice = 5;
					return;
				}
			}
			// END JOSEPH
			else
			{
	//				gi.dprintf ("yo man come to me when you got %d bucks\n", abs (other->currentcash));
				if (other->last_talk_time < (level.time - 2) || last_voice != 6)
					Voice_Specific( other, ent, hiredguy_specific, 3 );
				other->cast_info.talk( other );
				last_voice = 6;
				return;
			}
		}
	}
		else // GENDER_FEMALE
		{
					// RAFAEL 02-18-99	
			if (!(cast_memory->flags & MEMORY_HIRED)) // if the dude is not hired
			{
				if (flags == ORDER_MOVE)	// not a valid command
					return;

				// if (FullGang (ent)) // if the gang is full
				if (ent->client->pers.friends >= 2)
				{
					if (other->last_talk_time < (level.time - 2) || last_voice != 6)
						Voice_Random (other, ent, &hiredgal_specific[6], 2);

					other->cast_info.talk( other );
					last_voice = 6;
					return;
				}
			}


			if (!(cast_memory->flags & MEMORY_HIRE_FIRST_TIME))
			{
				cast_memory->flags |= MEMORY_HIRE_FIRST_TIME;
				{
					int rval;
					rval = abs (other->currentcash);

					// JOSEPH 19-FEB-99
					if (flags == ORDER_FOLLOWME)
					{
						ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_YES;
						ent->client->hud_self_talk_time = level.time + 2.0;
					}
					else if (flags == ORDER_HOLD)
					{
						ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_NO;
						ent->client->hud_self_talk_time = level.time + 2.0;
					}
					// END JOSEPH
					
					// gi.dprintf ("yo man I'll follow ya fer %d bucks\n", rval);

					if (other->last_talk_time < (level.time - 2) || last_voice != 1)
						// this line chooses the correct sound to play.. (even switches between the first and second for consecutive calls)
						Voice_Specific( other, ent, hiredgal_ask, ((rval / 25) * 2) + (hiredgal_ask[((rval / 25) * 2)].last_played > hiredgal_ask[((rval / 25) * 2) + 1].last_played) );


					other->cast_info.talk( other );

					last_voice = 1;

					return;
				}
			}
			
			else if (!(cast_memory->flags & MEMORY_HIRE_ASK))
			{
				// JOSEPH 19-FEB-99
				if (flags == ORDER_FOLLOWME)
				{
					ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_YES;
					ent->client->hud_self_talk_time = level.time + 2.0;
				}
				else if (flags == ORDER_HOLD)
				{
					ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_NO;
					ent->client->hud_self_talk_time = level.time + 2.0;
				}
				// END JOSEPH
				
				if (ent->client->pers.currentcash >= abs (other->currentcash))
				{
					if (flags == ORDER_FOLLOWME)
					{
						cast_memory->flags |= MEMORY_HIRE_ASK;

	//					gi.dprintf ("so ya got the money?\n", abs (other->currentcash));

						if (other->last_talk_time < (level.time - 2) || last_voice != 2)
							// Voice_Specific( other, ent, hiredguy_specific, 0 + (hiredguy_specific[0].last_played > hiredguy_specific[1].last_played) );
							Voice_Random (other, ent, hiredgal_specific, 2);


						other->cast_info.talk( other );
						last_voice = 2;

						return;
					}
					else if (flags == ORDER_HOLD)
					{
	//					gi.dprintf ("yo man I'll be waiting for ya\n");
						if (other->last_talk_time < (level.time - 2) || last_voice != 3)
							// Voice_Specific( other, ent, hiredguy_specific, 4 + (hiredguy_specific[4].last_played > hiredguy_specific[5].last_played) );
							Voice_Random (other, ent, &hiredgal_specific[4], 2);

						other->cast_info.talk( other );
						last_voice = 3;
						return;
					}
					else	// invalid response
					{
						gi.dprintf( "\nInvalid response.\nkey1 = YES\nkey3 = NO\n" );
						return;
					}
				}
				else
				{
	//				gi.dprintf ("yo man come to me when you got %d bucks\n", abs (other->currentcash));
					if (other->last_talk_time < (level.time - 2) || last_voice != 4)
						Voice_Specific( other, ent, hiredgal_specific, 3 );

					other->cast_info.talk( other );
					last_voice = 4;
					return;
				}
			}
			
			else if (!(cast_memory->flags & MEMORY_HIRED))
			{
				// JOSEPH 19-FEB-99
				if (flags == ORDER_HOLD)
				{
					ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_NO;
					ent->client->hud_self_talk_time = level.time + 2.0;
				}
				else if (flags == ORDER_FOLLOWME)
				{
					ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_YES;
					ent->client->hud_self_talk_time = level.time + 2.0;
				}
				// END JOSEPH
				
				// JOSEPH 3-FEB-99 
				if (ent->client->pers.currentcash >= abs (other->currentcash))
				{
					if (flags == ORDER_FOLLOWME)
					{	// give them the money
						extern mmove_t	thug_move_crch_grab;

						cast_memory->flags |= MEMORY_HIRED;
						ent->client->pers.currentcash -= abs (other->currentcash);
						
						// other->currentcash = abs(other->currentcash);
						other->currentcash = 0;

						ent->client->pers.friends++;

						/*
						if (!strcmp(other->classname, "cast_thug"))
						{
							other->cast_info.currentmove = &thug_move_crch_grab;
						}
						*/

						other->cast_info.aiflags |= AI_NOWALK_FACE;

						// we just hired them, by default they should follow us
						flags = ORDER_FOLLOWME;
						firstime = true;


						EP_HiredGuysRegisterFlags (ent, other);
					}
					else if (flags == ORDER_HOLD)
					{
	//					gi.dprintf ("yo man I'll be here if you change your mind\n");
						
						cast_memory->flags &= ~MEMORY_HIRE_ASK;

						if (other->last_talk_time < (level.time - 2) || last_voice != 5)
							Voice_Specific( other, ent, hiredgal_specific, 2 );
						other->cast_info.talk( other );
						last_voice = 5;
						return;
					}
				}
				// END JOSEPH
				else
				{
	//				gi.dprintf ("yo man come to me when you got %d bucks\n", abs (other->currentcash));
					if (other->last_talk_time < (level.time - 2) || last_voice != 6)
						Voice_Specific( other, ent, hiredgal_specific, 3 );
					other->cast_info.talk( other );
					last_voice = 6;
					return;
				}
			}
		}
	}

	// if in bar, don't allow killing
	if (flags == ORDER_MOVE && level.bar_lvl)
	{
		// gi.dprintf("SOUND TODO: No killing in the bar\n");
		return;
	}

	// this should help with the friendly guys not showing up when you change level
	other->spawnflags &= ~2; 
	other->currentcash = 0;
	other->leader = ent;

	other->cast_info.aiflags &= ~(AI_MOVEOUT | AI_HOLD_POSITION);
	other->cast_info.aiflags &= ~AI_NOWALK_FACE;

	if (other->holdpos_ent)
	{
		G_FreeEdict( other->holdpos_ent );
		other->holdpos_ent = NULL;
	}

	if (flags == ORDER_MOVE)
	{
		if (EP_DoKey (ent, other))
		{
			ent->cast_info.aiflags |= AI_DOKEY;
			other->cast_info.aiflags |= AI_DOKEY;
		}
		else
		{
		ent->cast_info.aiflags |= AI_MOVEOUT;
		other->cast_info.aiflags |= AI_MOVEOUT;

		if (ent->moveout_ent)
		{	// in case it was set before, kill it
			ent->moveout_ent = NULL;
		}
	}
	}

	if (ordertime > level.time)		// changed levels
		ordertime = 0;

	switch (flags)
	{
	case ORDER_MOVE :
		{
			if (ordertime < (level.time - 0.5))
			{
				Voice_Random( ent, other, m_response, NUM_MOVEOUT );
			}
			break;
		}
	case ORDER_HOLD :
		{
			if (ordertime < (level.time - 0.5))
				Voice_Random( ent, other, holdposition, NUM_HOLDPOSITION );
			other->cast_info.aiflags |= AI_HOLD_POSITION;
			other->cast_info.aiflags |= AI_NOWALK_FACE;

			// remember this position
			if (!other->holdpos_ent)
				other->holdpos_ent = G_Spawn();

			VectorCopy( other->s.origin, other->holdpos_ent->s.origin );

			break;
		}
	case ORDER_FOLLOWME :
		{
			if (firstime)
			{
				if (other->gender == GENDER_FEMALE)
					Voice_Random( other, ent, &hiredgal_specific[8], 3);
				else
					Voice_Specific( other, ent, hiredguy_specific, (rand()%3) + 8 );
//				gi.dprintf ("ok I'll go with ya\n");
			}
			else if (ordertime < (level.time - 0.5))
				Voice_Random( ent, other, followme, NUM_FOLLOWME );

			if (other->cast_info.aiflags & AI_TAKE_COVER)
			{
				other->cast_info.aiflags &= ~(AI_TAKE_COVER|AI_TAKECOVER_IGNOREHEALTH);
			}

			break;
		}
		
		// JOSEPH 19-FEB-99 
		if ((flags) && (!ent->client->hud_self_talk_time == (level.time + 2.0)) &&
			(!((ent->client->ps.stats[STAT_HUD_SELF_TALK] == TT_YES) || 
			(ent->client->ps.stats[STAT_HUD_SELF_TALK] == TT_NO))))
		{
		ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_COMMAND;
		ent->client->hud_self_talk_time = level.time + 2.0;
		}
		// END JOSEPH	
	}

	if (ordertime < (level.time - 0.5))
		ordertime = level.time;
}

//-------------------------------------------------------------------------
// Generic "3-key" system

edict_t *key_ent;

// JOSEPH 8-FEB-99
edict_t	*GetKeyEnt( edict_t *ent )
{
	vec3_t	dir;
	vec3_t	start, end;
	trace_t	tr;

	AngleVectors( ent->client->ps.viewangles, dir, NULL, NULL );

	VectorCopy( ent->s.origin, start );
	start[2] += ent->viewheight;

	if (deathmatch->value)
		VectorMA( start, 4000, dir, end );
	else
		VectorMA( start, 384, dir, end );

	tr = gi.trace( start, NULL, NULL, end, ent, CONTENTS_MONSTER );

	if ((tr.fraction < 1) && ((deathmatch->value && tr.ent->client) || (tr.ent->svflags & SVF_MONSTER)) && (tr.ent->name_index == NAME_MOMO))
	{
		return tr.ent;
	}

	tr = gi.trace( start, NULL, NULL, end, ent, MASK_SHOT );

	if ((tr.fraction < 1) && ((deathmatch->value && tr.ent->client) || (tr.ent->svflags & SVF_MONSTER)))
	{
		return tr.ent;
	}

	return NULL;
}
// END JOSEPH

void Cmd_Key_f (edict_t *ent)
{
	char		*cmd;

	
	if (level.speaktime > level.time)
		return;
	
	cmd = gi.argv (0);

	if (key_ent = GetKeyEnt( ent ))
	{
		void Cmd_Wave_f (edict_t *ent, edict_t *other);
		cast_memory_t *mem;

		if (deathmatch->value)
		{
			Cmd_Wave_f( ent, key_ent );
			return;
		}

		// JOSEPH 18-FEB-99 
		ent->client->ps.stats[STAT_HUD_SELF_TALK] = TT_COMMAND;
		ent->client->hud_self_talk_time = level.time + 2.0;
		// END JOSEPH	

		mem = level.global_cast_memory[key_ent->character_index][ent->character_index];

		if (!mem)
			return;

		if (mem->memory_type == MEMORY_TYPE_FRIEND)
		{	// issuing an order

			Cmd_Order_f( ent, key_ent, cmd );

			if (key_ent->targetname)
				key_ent->targetname = 0;
			if (key_ent->spawnflags & 2)
				key_ent->spawnflags &=~ 2;
			
		}
		else if (mem->response)		// we're responding to a question
		{
			response_t resp;

			if (Q_stricmp (cmd, "key1") == 0)
				resp = resp_yes;
			else if (Q_stricmp (cmd, "key3") == 0)
				resp = resp_no;

			mem->response( ent, key_ent, resp );

		}
		else	// normal discussion
		{
	
			Cmd_Speech_f ( ent, key_ent, cmd );

		}

	}
	else	// noone to talk to, so make it an order in case anyone's listening
	{
		int flags;

		if (Q_stricmp (cmd, "key1") == 0)		// Stay Here
			flags = ORDER_FOLLOWME;
		else if (Q_stricmp (cmd, "key2") == 0)	// Attack
			flags = ORDER_MOVE;
		else if (Q_stricmp (cmd, "key3") == 0)	// Follow
			flags = ORDER_HOLD;
			

		ent->order = flags;
		ent->order_timestamp = level.time;
	}


	level.speaktime = level.time + 1.0;

}

//-------------------------------------------------------------------------

// Ridah, Chasecam
void Cmd_ToggleCam_f ( edict_t *ent )
{
	if (ent->flags & FL_CHASECAM)
	{
		ent->flags -= FL_CHASECAM;
	}
	else
	{
		ent->flags += FL_CHASECAM;

		gi.centerprintf( ent, "Chasecam is incomplete, and therefore\nunsupported at this stage\n" );
	}
}
// done.

// JOSEPH 13-APR-99
void Cmd_SetProps_f (int status)
{
	edict_t	*e;
	int		i;
					
	for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
	{
		if ((e->svflags & SVF_PROP) && (e->option))
		{
			if (status)
			{
				e->svflags |= SVF_NOCLIENT;
				e->solid = SOLID_NOT;
			}
			else
			{
				e->svflags &= ~SVF_NOCLIENT;	
				e->solid = e->savesolid;
			}
		}
	}
}
// END JOSEPH

// JOSEPH 23-MAR-99
void Cmd_FryAll_f (edict_t *ent)
{
	edict_t	*e = NULL;

	if (deathmatch->value)
		return;

	while (e = findradius(e, ent->s.origin, 512))
	{
		if (e->svflags & SVF_MONSTER)
		{
			e->onfiretime = 100;
			e->onfireent = e;

			if (e->gender == GENDER_FEMALE)
			{
				Voice_Random (e, e, &female_specific[6], 2); 
			}
			else if (e->gender == GENDER_MALE)
			{
				Voice_Random (e, e, &male_specific[10], 2); 
			}

			e->pain_debounce_time = level.time + 5;

			if (e->cast_info.catch_fire)
			{
				e->cast_info.catch_fire(e, e);
			}

			e->s.renderfx2 &= ~RF2_DIR_LIGHTS;		
		}
	}
}
// END JOSEPH

// ==============================================================================
// Quake2 code follows:

char *ClientTeam (edict_t *ent)
{
	char		*p;
	static char	value[512];
	
	value[0] = 0;

	if (!ent->client)
		return value;

	strcpy(value, Info_ValueForKey (ent->client->pers.userinfo, "skin"));
	p = strchr(value, '/');
	if (!p)
		return value;

	if ((int)(dmflags->value) & DF_MODELTEAMS)
	{
// Ridah, disabled this, teams are determined by model and skin (since that's the only way to make sure they appear the same
//		*p = 0;
		return value;
	}

	// if ((int)(dmflags->value) & DF_SKINTEAMS)
	return ++p;
}

qboolean OnSameTeam (edict_t *ent1, edict_t *ent2)
{
	char	ent1Team [512];
	char	ent2Team [512];

	if (teamplay->value)
	{
		if (ent1 && ent2 && ent1->client && ent2->client && ent1->client->pers.team && (ent1->client->pers.team == ent2->client->pers.team))
			return true;
		else
			return false;
	}

	if (!((int)(dmflags->value) & (DF_MODELTEAMS /*| DF_SKINTEAMS*/)))
		return false;

	strcpy (ent1Team, ClientTeam (ent1));
	strcpy (ent2Team, ClientTeam (ent2));

	if (strcmp(ent1Team, ent2Team) == 0)
		return true;
	return false;

}


void SelectNextItem (edict_t *ent, int itflags)
{
	gclient_t	*cl;
//	int			i, index;
//	gitem_t		*it;

	cl = ent->client;
	
	if (cl->chase_target)
	{
		ChaseNext(ent);
		return;
	}
/*
	// scan  for the next valid one
	for (i=1 ; i<=MAX_ITEMS ; i++)
	{
		index = (cl->pers.selected_item + i)%MAX_ITEMS;
		if (!cl->pers.inventory[index])
			continue;
		it = &itemlist[index];
		if (!it->use)
			continue;
		if (!(it->flags & itflags))
			continue;

		cl->pers.selected_item = index;
		return;
	}

	cl->pers.selected_item = -1;
*/
}

void SelectPrevItem (edict_t *ent, int itflags)
{
	gclient_t	*cl;
//	int			i, index;
//	gitem_t		*it;

	cl = ent->client;

	if (cl->chase_target)
	{
		ChasePrev(ent);
		return;
	}
/*
	// scan  for the next valid one
	for (i=1 ; i<=MAX_ITEMS ; i++)
	{
		index = (cl->pers.selected_item + MAX_ITEMS - i)%MAX_ITEMS;
		if (!cl->pers.inventory[index])
			continue;
		it = &itemlist[index];
		if (!it->use)
			continue;
		if (!(it->flags & itflags))
			continue;

		cl->pers.selected_item = index;
		return;
	}

	cl->pers.selected_item = -1;
*/
}

void ValidateSelectedItem (edict_t *ent)
{
	gclient_t	*cl;

	cl = ent->client;

	if (cl->pers.inventory[cl->pers.selected_item])
		return;		// valid

	SelectNextItem (ent, -1);
}

/*
==================
Cmd_Give_f

Give items to a client
==================
*/
void Cmd_Give_f (edict_t *ent)
{
	char		*name;
	gitem_t		*it;
	int			index;
	int			i;
	qboolean	give_all;
	edict_t		*it_ent;

	if (!developer->value)
		return;

	if (deathmatch->value && !sv_cheats->value)
	{
		gi.cprintf (ent, PRINT_HIGH, "You must run the server with '+set cheats 1' to enable this command.\n");
		return;
	}

	name = gi.args();

	if (Q_stricmp(name, "all") == 0)
		give_all = true;
	else
		give_all = false;

	// JOSEPH 15-FEB-99
	if (Q_stricmp(gi.argv(1), "cash") == 0)
	{
		if (gi.argc() == 3)
			ent->client->pers.currentcash += atoi(gi.argv(2));
		else
			ent->client->pers.currentcash += 100;

		gi.sound (ent, CHAN_AUTO, gi.soundindex("world/pickups/cash.wav"), 1, ATTN_NORM, 0);
		
		if (!give_all)
			return;
	}
	// END JOSEPH
	
	if (give_all || Q_stricmp(gi.argv(1), "health") == 0)
	{
		if (gi.argc() == 3)
			ent->health = atoi(gi.argv(2));
		else
			ent->health = ent->max_health;
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp (gi.argv(1), "mods") == 0)
	{
		ent->client->pers.pistol_mods |= WEAPON_MOD_ROF;
		
		ent->client->pers.pistol_mods |= WEAPON_MOD_RELOAD;
		
		ent->client->pers.pistol_mods |= WEAPON_MOD_DAMAGE;
		
		ent->client->pers.pistol_mods |= WEAPON_MOD_COOLING_JACKET;

		ent->client->pers.hmg_shots = 30;

		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "weapons") == 0)
	{
		for (i=0 ; i<game.num_items ; i++)
		{
			it = itemlist + i;
			if (!it->pickup)
				continue;
			if (!(it->flags & IT_WEAPON))
				continue;
			
			// ent->client->pers.inventory[i] += 1;
			ent->client->pers.inventory[i] = 1;
			if (it->flags & IT_SILENCER)
			{
				ent->client->pers.silencer_shots = 20;
			}
		}
		if (!give_all)
			return;
	}

	if (give_all || Q_stricmp(name, "ammo") == 0)
	{
		for (i=0 ; i<game.num_items ; i++)
		{
			it = itemlist + i;
			if (!it->pickup)
				continue;
			if (!(it->flags & IT_AMMO))
				continue;
			if (it->flags & IT_NOCHEATS)
				continue;
			Add_Ammo (ent, it, 1000);
		}
		if (!give_all)
			return;
	}

	// JOSEPH 30-APR-99
	if (Q_stricmp(name, "armor") == 0)
	{
		gitem_t	*it;

		it = FindItem("Jacket Armor Heavy");
		ent->client->pers.inventory[ITEM_INDEX(it)] = 100;

		it = FindItem("Legs Armor Heavy");
		ent->client->pers.inventory[ITEM_INDEX(it)] = 100;

		it = FindItem("Helmet Armor Heavy");
		ent->client->pers.inventory[ITEM_INDEX(it)] = 100;

			return;
	}

	/*if (give_all || Q_stricmp(name, "Power Shield") == 0)
	{
		it = FindItem("Power Shield");
		it_ent = G_Spawn();
		it_ent->classname = it->classname;
		SpawnItem (it_ent, it);
		Touch_Item (it_ent, ent, NULL, NULL);
		if (it_ent->inuse)
			G_FreeEdict(it_ent);

		if (!give_all)
			return;
	}*/
	// END JOSEPH

	if (give_all)
	{
		for (i=0 ; i<game.num_items ; i++)
		{
			it = itemlist + i;
			if (!it->pickup)
				continue;
			if (it->flags & (IT_ARMOR|IT_WEAPON|IT_AMMO))
				continue;
			if (it->flags & IT_NOCHEATS)
				continue;
			ent->client->pers.inventory[i] = 1;
		}
		return;
	}

	it = FindItem (name);
	if (!it)
	{
		name = gi.argv(1);
		it = FindItem (name);
		if (!it)
		{
			gi.cprintf (ent, PRINT_HIGH, "not a valid item\n");
			return;
		}
	}

	if (!it->pickup)
	{
		gi.cprintf (ent, PRINT_HIGH, "non-pickup item\n");
		return;
	}

	index = ITEM_INDEX(it);

	if (it->flags & IT_AMMO)
	{
		if (gi.argc() == 3)
			ent->client->pers.inventory[index] = atoi(gi.argv(2));
		else
			ent->client->pers.inventory[index] += it->quantity;
	}
	else
	{
		it_ent = G_Spawn();
		it_ent->classname = it->classname;
		SpawnItem (it_ent, it);
		Touch_Item (it_ent, ent, NULL, NULL);
		if (it->flags & IT_SILENCER)
			ent->client->pers.silencer_shots = 20;
		if (it_ent->inuse)
			G_FreeEdict(it_ent);
		
	}
}


/*
==================
Cmd_God_f

Sets client to godmode

argv(0) god
==================
*/
void Cmd_God_f (edict_t *ent)
{
	char	*msg;

	if (!developer->value)
		return;

	if (deathmatch->value && !sv_cheats->value)
	{
		gi.cprintf (ent, PRINT_HIGH, "You must run the server with '+set cheats 1' to enable this command.\n");
		return;
	}

	ent->flags ^= FL_GODMODE;
	if (!(ent->flags & FL_GODMODE) )
		msg = "Immortal OFF\n";
	else
		msg = "Immortal ON\n";

	gi.cprintf (ent, PRINT_HIGH, msg);
}


/*
==================
Cmd_Notarget_f

Sets client to notarget

argv(0) notarget
==================
*/
void Cmd_Notarget_f (edict_t *ent)
{
	char	*msg;

	if (!developer->value)
		return;

	if (deathmatch->value && !sv_cheats->value)
	{
		gi.cprintf (ent, PRINT_HIGH, "You must run the server with '+set cheats 1' to enable this command.\n");
		return;
	}

	ent->flags ^= FL_NOTARGET;
	if (!(ent->flags & FL_NOTARGET) )
		msg = "notarget OFF\n";
	else
		msg = "notarget ON\n";

	gi.cprintf (ent, PRINT_HIGH, msg);
}


/*
==================
Cmd_Noclip_f

argv(0) noclip
==================
*/
void Cmd_Noclip_f (edict_t *ent)
{
	char	*msg;

	if (!developer->value)
		return;

	if (deathmatch->value && !sv_cheats->value)
	{
		gi.cprintf (ent, PRINT_HIGH, "You must run the server with '+set cheats 1' to enable this command.\n");
		return;
	}

	if (ent->movetype == MOVETYPE_NOCLIP)
	{
		ent->movetype = MOVETYPE_WALK;
		msg = "noclip OFF\n";
	}
	else
	{
		ent->movetype = MOVETYPE_NOCLIP;
		msg = "noclip ON\n";
	}

	gi.cprintf (ent, PRINT_HIGH, msg);
}


/*
==================
Cmd_Use_f

Use an inventory item
==================
*/
void Cmd_Use_f (edict_t *ent)
{
	int			index;
	gitem_t		*it;
	char		*s;

	s = gi.args();

	// Teamplay
	if (teamplay->value && !ent->client->pers.team)
	{
		if (s)
		{
			if (!strcmp(s, "pipe"))
			{	// Kings
				Cmd_Join_f( ent, team_names[1] );
			}
			else if (!strcmp(s, "pistol"))
			{	// Pins
				Cmd_Join_f( ent, team_names[2] );
			}
		}

		return;
	}

	it = FindItem (s);
	if (!it)
	{
		gi.cprintf (ent, PRINT_HIGH, "not a valid item: %s\n", s);
		return;
	}
	if (!it->use)
	{
		gi.cprintf (ent, PRINT_HIGH, "Item is not usable.\n");
		return;
	}

	index = ITEM_INDEX(it);
	if (!ent->client->pers.inventory[index])
	{
		
		if (strcmp (it->pickup_name, "Pistol") == 0)
		{
			gi.dprintf ("silencer_shots: %d\n", ent->client->pers.silencer_shots);
			if (!ent->client->pers.silencer_shots)
			{
				gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
				return;
			}
			it = FindItem ("SPistol");
			index = ITEM_INDEX (it);
			if (!ent->client->pers.inventory[index])
			{
				gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
				return;
			}
		}
		else 
		{
			gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
			return;
		}
	}

	if (ent->client->pers.holsteredweapon)
	{
		if (level.bar_lvl)
			return;
		
		if (ent->client->pers.holsteredweapon == it)
		{
			ent->client->newweapon = ent->client->pers.holsteredweapon;
			ChangeWeapon (ent);
			ent->client->pers.holsteredweapon = 0;
			return;	
		}
		else
		{
			ent->client->pers.weapon = ent->client->pers.holsteredweapon; 
			ent->client->pers.holsteredweapon = NULL;
		}
	}

	it->use (ent, it);

	if (!ent->client->pers.holsteredweapon && !ent->client->pers.weapon && ent->client->newweapon)
	{
		ChangeWeapon (ent);
	}
}


/*
==================
Cmd_Drop_f

Drop an inventory item
==================
*/
void Cmd_Drop_f (edict_t *ent)
{
	int			index;
	gitem_t		*it;
	char		*s;

	s = gi.args();
	it = FindItem (s);
	if (!it)
	{
		gi.cprintf (ent, PRINT_HIGH, "not a valid item: %s\n", s);
		return;
	}
	if (!it->drop)
	{
		gi.cprintf (ent, PRINT_HIGH, "Item is not dropable.\n");
		return;
	}

	index = ITEM_INDEX(it);
	if (!ent->client->pers.inventory[index])
	{
		if (strcmp (it->pickup_name, "Pistol") == 0)
		{
			gi.dprintf ("silencer_shots: %d\n", ent->client->pers.silencer_shots);

			if (!ent->client->pers.silencer_shots)
			{
				gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
				return;
			}
			
			it = FindItem ("SPistol");
			index = ITEM_INDEX (it);
			if (!ent->client->pers.inventory[index])
			{
				gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
				return;
			}
		}
		else 
		{
			gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
			return;
		}
	}

	it->drop (ent, it);
}


/*
=================
Cmd_Inven_f
=================
*/
void Cmd_Inven_f (edict_t *ent)
{
	int			i;
	gclient_t	*cl;

	cl = ent->client;

	cl->showscores = false;
	cl->showhelp = false;

	if (cl->showinventory)
	{
		cl->showinventory = false;
		return;
	}

	cl->showinventory = true;

	gi.WriteByte (svc_inventory);
	for (i=0 ; i<MAX_ITEMS ; i++)
	{
		gi.WriteShort (cl->pers.inventory[i]);
	}
	gi.unicast (ent, true);
}

/*
=================
Cmd_InvUse_f
=================
*/
void Cmd_InvUse_f (edict_t *ent)
{
	gitem_t		*it;

	ValidateSelectedItem (ent);

	if (ent->client->pers.selected_item == -1)
	{
		gi.cprintf (ent, PRINT_HIGH, "No item to use.\n");
		return;
	}

	it = &itemlist[ent->client->pers.selected_item];
	if (!it->use)
	{
		gi.cprintf (ent, PRINT_HIGH, "Item is not usable.\n");
		return;
	}
	it->use (ent, it);
}

/*
=================
Cmd_WeapPrev_f
=================
*/
void Cmd_WeapPrev_f (edict_t *ent)
{
	gclient_t	*cl;
	int			i, index;
	gitem_t		*it;
	int			selected_weapon;

	cl = ent->client;

	// JOSEPH 10-FEB-99
	if (cl->pers.holsteredweapon)
	{
		if (level.bar_lvl)
			return;

		cl->newweapon = cl->pers.holsteredweapon;
		ChangeWeapon (ent);
		cl->pers.holsteredweapon = 0;
		return;
	}
	// END JOSEPH

	if (!cl->pers.weapon)
		return;

	// Ridah, if already changing weapons, start from the next weapon, for faster cycling
	if (ent->client->weaponstate == WEAPON_DROPPING)
		selected_weapon = ITEM_INDEX(cl->newweapon);
	else
		selected_weapon = ITEM_INDEX(cl->pers.weapon);

	// scan  for the next valid one
	for (i=1 ; i<=MAX_ITEMS ; i++)
	{
		index = (selected_weapon + i)%MAX_ITEMS;
		if (!cl->pers.inventory[index])
			continue;
		it = &itemlist[index];
		if (!it->use)
			continue;
		if (! (it->flags & IT_WEAPON) )
			continue;
		if (selected_weapon == ITEM_INDEX(it) && cl->newweapon)
		{
			// Ridah, show the current weapon on the hud, for easy scrolling
			if (deathmatch->value && !strstr(cl->newweapon->icon, "pipe"))
			{
				it = cl->newweapon;
				ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(it->icon);
				ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+ITEM_INDEX(it);
				ent->client->pickup_msg_time = level.time + 5.5;
			}

			return;	// successful
		}
		else
		{
			it->use (ent, it);
		}
	}
}

#define DREWACTIVATEDISTANCE	96

// JOSEPH 11-MAY-99
qboolean infront_angle_activate (vec3_t selfang, vec3_t selforg, vec3_t otherorg)
{
	vec3_t	vec;
	float	dot;
	vec3_t	forward;

	AngleVectors (selfang, forward, NULL, NULL);
	VectorSubtract (otherorg, selforg, vec);
	VectorNormalize (vec);
	dot = DotProduct (vec, forward);
	
	if (dot > 0.95)
		return true;
	return false;
}
// END JOSEPH

// JOSEPH 21-SEP-98
void Cmd_Activate_f (edict_t *ent)
{
	edict_t		*trav, *best;
	float		best_dist=9999, this_dist;

	if (ent->movetype == MOVETYPE_NOCLIP)
	{
		if (maxclients->value > 1)
		{
			if (!ent->client->chase_target)
				ChaseNext(ent);
			else	// disable it
			{
				ent->client->chase_target = NULL;
				ent->client->ps.pmove.pm_flags &= ~PMF_NO_PREDICTION;
			}
		}

		return;
	}

	// if we are ducking
	if (ent->client->ps.pmove.pm_flags & PMF_DUCKED)
	{
		// find the near enemy 
		trav = best = NULL;
		// JOSEPH 13-MAY-99
		while (trav = findradius( trav, ent->s.origin, 80 ))
		// END JOSEPH
		{
			// JOSEPH 14-MAY-99
			if (!(trav->svflags & SVF_MONSTER))
				continue;
			// END JOSEPH
			// JOSEPH 6-JAN-99
			if (trav == ent)
				continue;
			// END JOSEPH
			//if (!infront(ent, trav))
			//	continue;
			//if (!visible(ent, trav))
			//	continue;
			if (((this_dist = VectorDistance(ent->s.origin, trav->s.origin)) > best_dist) && (this_dist > 32))
				continue;
			
			best = trav;
			best_dist = this_dist;
		}

		// if the enemy has cash - then take it
		// Joseph 14-MAY-99
		if ((best) && (best->currentcash > 0) && best->health <= 0)
		// END JOSEPH
		{
			int     index;
			gitem_t *item;
			
			ent->client->pers.currentcash += best->currentcash;
			//gi.cprintf (ent, PRINT_HIGH, "%i dollars found\n", best->currentcash);
			ent->client->ps.stats[STAT_CASH_PICKUP] = best->currentcash;
			best->currentcash = 0;
			// flash the screen green
			ent->client->bonus_alpha = 0.25;	
			ent->client->bonus_alpha_color = 2;	
			gi.sound (ent, CHAN_AUTO, gi.soundindex("world/pickups/cash.wav"), 1, ATTN_NORM, 0);		

			item = FindItem ("Cash");
			index = ITEM_INDEX (item);
			// show icon and name on status bar
			ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
			ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
			ent->client->pickup_msg_time = level.time + 5.5;		
		}
	}

	// JOSEPH 1-OCT-98
	// Work in progress
	/*{
	edict_t		*trav, *best;
	float		best_dist=9999, this_dist;
	
		// find the nearest pull-enabled object 
		trav = best = NULL;
		while (trav = findradius( trav, ent->s.origin, 128 ))
		{
			if (!trav->pullable)
				continue;
			//if (!infront(ent, trav))
			//	continue;
			//if (!visible(ent, trav))
			//	continue;
			if (((this_dist = VectorDistance(ent->s.origin, trav->s.origin)) > best_dist) && (this_dist > 64))
				continue;
			
			best = trav;
			best_dist = this_dist;
		}

		// If we find something to drag
		if (best)
		{
			vec3_t	up, forward;
						
			AngleVectors(ent->s.angles, forward, NULL, up);
			//VectorScale (forward, 50, best->velocity);
			VectorMA (best->velocity, 400, up, best->velocity);
			best->movetype = MOVETYPE_TOSS;
			best->groundentity = NULL;
		}
	}*/
	// END JOSEPH

	// JOSEPH 11-MAY-99
	// find a usable brush entity and tag it as such
	{
		edict_t		*target, *toptarget;
		vec3_t		dest;
		trace_t		trace, tr;
		vec3_t		dir, neworigin, endorg;	
		float       topdistance;
		int			directtarget;

		target = NULL;
		toptarget = NULL;
		topdistance = 10000;
		directtarget = 0;

		while (((target = findradius(target, ent->s.origin, DREWACTIVATEDISTANCE * (1 + (deathmatch->value != 0)))) || toptarget) && !directtarget)
		{
			if (!target)
				goto startyourtriggers;
			if (!(target->activate_flags & ACTIVATE_GENERAL))
				continue;
			if (target->targetname && target->key != -1)
				continue;
			
			VectorCopy(ent->s.origin, neworigin);
			neworigin[2] += ent->viewheight;
			
			AngleVectors( ent->client->ps.viewangles, dir, NULL, NULL );
			VectorMA (neworigin, DREWACTIVATEDISTANCE * (1 + (deathmatch->value != 0)), dir, dest);

			trace = gi.trace (neworigin, vec3_origin, vec3_origin, dest, ent, MASK_SOLID);
			
			// JOSEPH 19-MAY-99
			if (trace.ent && trace.ent->classname && (!strcmp(trace.ent->classname, "func_lift")))
			{
				edict_t		*targetL;

				targetL = NULL;

				while (((targetL = findradius(targetL, trace.endpos, 16))))
				{
					if (!(targetL->activate_flags & ACTIVATE_GENERAL))
						continue;			
					if (targetL->targetname && targetL->key != -1)
						continue;
					if (targetL->classname && (!strcmp(targetL->classname, "func_button")))
					{
						toptarget = targetL;
						goto startyourtriggers;
					}
				}
			}
			// END JOSEPH
			
			// JOSEPH 14-MAY-99
			if (trace.ent == target)
			{
				directtarget = 1;	
				
				if ((strcmp (target->classname, "func_door") == 0) ||
					(strcmp (target->classname, "func_door_rotating") == 0))
				{
					if ((target->team) && (target->teammaster))
					{
						toptarget = target->teammaster;
						goto startyourtriggers;
					}
				}

				toptarget = target;
				goto startyourtriggers;
			}
			// END JOSEPH

			VectorAdd (target->absmin, target->absmax, endorg);				
			VectorScale (endorg, 0.5, endorg);

			if (!(infront_angle_activate(ent->client->v_angle, neworigin, endorg)))
				continue;

			if (VectorDistance(trace.endpos, dest ) > topdistance)
				continue;
			
			tr = gi.trace(neworigin, NULL, NULL, endorg, ent, MASK_SOLID);

			// Ridah, added this since it's frustrating hitting the switches in deathmatch
			if (!deathmatch->value || (!Q_stricmp(target->classname, "func_button") && !Q_stricmp(target->target, "safe2")))
			if (tr.ent != target)
				continue;

			topdistance = VectorDistance(trace.endpos, dest);
			toptarget = target;
			continue;

startyourtriggers:			

			target = toptarget;	
			toptarget = NULL;
	
	// END JOSEPH

	/*{
		edict_t		*target;
		vec3_t		dest, src;
		trace_t		trace;
		vec3_t		dir;	


		target = NULL;
		
		while (target = findradius ( target, ent->s.origin, DREWACTIVATEDISTANCE))
		{
			if (!(target->activate_flags & ACTIVATE_GENERAL))
				continue;
			if (target->targetname && target->key != -1)
				continue;

			if (strcmp (target->classname, "func_door") == 0)
			{
				AngleVectors( ent->client->ps.viewangles, dir, NULL, NULL );
				VectorMA (ent->s.origin, DREWACTIVATEDISTANCE, dir, dest);
			}
			else if (strcmp (target->classname, "misc_cut_scene") == 0)
			{
				AngleVectors( ent->client->ps.viewangles, dir, NULL, NULL );
				VectorMA (ent->s.origin, DREWACTIVATEDISTANCE, dir, dest);
			}
			else
			{
				VectorAdd (target->absmin, target->absmax, dest);
				VectorScale (dest, 0.5, dest);
			}


			// Ridah, fix close to buttons not working
			VectorCopy( ent->s.origin, src );
			if (	(dest[2] > (ent->s.origin[2] + ent->mins[2]))
				&&	(dest[2] < (ent->s.origin[2] + ent->maxs[2])))
			{
				src[2] = dest[2];
			}

			trace = gi.trace (ent->s.origin, vec3_origin, vec3_origin, dest, ent, MASK_SOLID);

			// Rafael
			if (trace.ent != target)
			{
				// Ridah, fix close to buttons not working
				if (VectorDistance( trace.endpos, dest ) > 32)
					continue;
			}*/
	
			// JOSEPH 12-MAR-99-B
			// If it must be trigger unlocked
			if (target->key < 0)
			{
				gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);
				continue;
			}
			// END JOSEPH

			// JOSEPH 19-MAR-99-B
			// Kingpin keys must be placed here to open doors
			if (target->key > 0)
			{
				switch(target->key)
				{
					case 1:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("StoreRoomKey"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);
							continue;
						}
					}
					break;			

					case 2:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Electrical_Room"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);
							continue;
						}
					}
					break;	
					
					case 3:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Chem_Plant_Key"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);			
							continue;
						}
					}
					break;	

					case 4:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Bridge_Key"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
					}
					break;	

					case 5:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Shipyard_Key"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
					}
					break;	

					case 6:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Warehouse_Key"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
					}
					break;	

					case 7:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Shop_Key"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
					}
					break;
					
					case 8:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Ticket"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
						else
							ent->client->pers.inventory[ITEM_INDEX(FindItem("Ticket"))] = 0;
					}
					break;	

					case 9:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("Office_Key"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
					}
					break;	

					case 10:
					{
						if (!ent->client->pers.inventory[ITEM_INDEX(FindItem("key10"))])
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
					}
					break;					

					case 11:
					{
						if (!(EP_UnlockDoorFlag (ent)))
						{
							gi.sound (ent, CHAN_AUTO, gi.soundindex("world/doors/dr_locked.wav"), 1, ATTN_NORM, 0);					
							continue;
						}
					}
				}

				// Ridah, once unlocked, stay unlocked
				target->key = 0;
			}
			// END JOSEPH			

			// we have a valid one so lets flag it
			target->activate_flags |= ACTIVATE_AND_OPEN;
			break;
		}
		
		if (target)
			if (target->activate_flags & ACTIVATE_AND_OPEN)
				if (target->use)
				{
//					gi.dprintf( "%s, %s\n", target->classname, target->target );
					target->use (target, ent, ent);
				}
	}

	// Ridah, moveout command
 	if ((ent->cast_info.aiflags & AI_DOKEY || ent->cast_info.aiflags & AI_MOVEOUT) && ent->client->pers.friends > 0)
	{
		vec3_t	start, end, dir;
		trace_t tr;

		AngleVectors( ent->client->ps.viewangles, dir, NULL, NULL );

		VectorCopy( ent->s.origin, start );
		start[2] += ent->viewheight;

		VectorMA( start, 2048, dir, end );

		tr = gi.trace( start, NULL, NULL, end, ent, MASK_SHOT );

		if (	(tr.fraction < 1)
			&&	(tr.ent->svflags & SVF_MONSTER)
			&&	(tr.ent->health > 0)
			&&	(tr.ent->cast_group != ent->cast_group))
		{
			int i;

			ent->moveout_ent = tr.ent;

			// look for a friend to say this to
			for (i=0; i<level.num_characters; i++)
			{
				if (!level.characters[i])
					continue;
				if (level.characters[i]->health <= 0)
					continue;
				if (level.characters[i]->leader != ent)
					continue;

				if (!(level.characters[i]->cast_info.aiflags & AI_MOVEOUT))
					continue;
				
				Voice_Random( ent, level.characters[i], hiredguy_combat_moveout, NUM_HIREDGUY_COMBAT_MOVEOUT );
				break;
			}
		}

		else if (ent->cast_info.aiflags & AI_DOKEY)
		{
			EP_Check_DoKey (ent, tr.ent);
			// gi.dprintf ("gave a go do key order\n");
		}
	}

}
// END JOSEPH

// RAFAEL 01-11-99
void Cmd_Reload_f (edict_t *ent)
{
	gclient_t	*cl;

	cl = ent->client;
	
	if (!cl->pers.weapon)
		return;

	// Ridah, fixes Tommygun reloading twice, if hit "reload" as it starts to auto-reload when out of ammo
	if (ent->client->weaponstate == WEAPON_RELOADING)
		return;

	if (ent->client->weaponstate != WEAPON_READY)
		return;

	ent->client->reload_weapon = true;
}
// END 01-11-99


// JOSEPH 6-FEB-99
void Cmd_Holster_f (edict_t *ent)
{
	gclient_t *cl;

	if (deathmatch->value)
		return;

	if (level.bar_lvl)
	{
		gi.dprintf ("no weapons on this level\n");
		return;
	}

	cl = ent->client;

	if (!cl->pers.holsteredweapon)
	{
		if (!cl->pers.weapon)
			return;

		cl->pers.holsteredweapon = cl->pers.weapon;
		cl->newweapon = NULL;
		cl->weaponstate = WEAPON_DROPPING;

		if (ent->s.renderfx2 & RF2_FLAMETHROWER)
			ent->s.renderfx2 &= ~RF2_FLAMETHROWER;
	}
	else
	{
		if (cl->ps.gunindex != 0)
			return;
  
		cl->newweapon = cl->pers.holsteredweapon;
		ChangeWeapon (ent);
		cl->pers.holsteredweapon = 0;  
	}
}

void Cmd_HolsterBar_f (edict_t *ent)
{
	gclient_t *cl;

	cl = ent->client;

	if (deathmatch->value)
		return;

	if (level.bar_lvl)
	{
		if (!cl->pers.holsteredweapon)
		{
			if (!cl->pers.weapon)
				return;

			cl->pers.holsteredweapon = cl->pers.weapon;
			//cl->newweapon = NULL;
			//cl->weaponstate = WEAPON_DROPPING;
			cl->ps.gunindex = 0;
		}
	}
	
	else
	{
		if (cl->ps.gunindex != 0)
			return;
  
		cl->newweapon = cl->pers.holsteredweapon;
		ChangeWeapon (ent);
		cl->pers.holsteredweapon = 0;  
	}
	
	
}
// END JOSEPH

// JOSEPH 29-DEC-98
void Cmd_Hud_f (edict_t *ent)
{
	gi.WriteByte (svc_hud);
	gi.unicast (ent, true);
}
// END JOSEPH

void Cmd_Flashlight_f (edict_t *ent)
{
	if (!ent->client->flashlight && ent->client->pers.inventory[ITEM_INDEX(FindItem("Flashlight"))])
		ent->client->flashlight = true;
	else
		ent->client->flashlight = false;
}


/*
=================
Cmd_WeapNext_f
=================
*/
void Cmd_WeapNext_f (edict_t *ent)
{
	gclient_t	*cl;
	int			i, index;
	gitem_t		*it;
	int			selected_weapon;

	cl = ent->client;

	// JOSEPH 10-FEB-99
	if (cl->pers.holsteredweapon)
	{
		if (level.bar_lvl)
			return;
		
		cl->newweapon = cl->pers.holsteredweapon;
		ChangeWeapon (ent);
		cl->pers.holsteredweapon = 0;
		return;
	}
	// END JOSEPH

	if (!cl->pers.weapon)
		return;

	// Ridah, if already changing weapons, start from the next weapon, for faster cycling
	if (ent->client->weaponstate == WEAPON_DROPPING)
	{
		selected_weapon = ITEM_INDEX(cl->newweapon);
	}
	else
	{
		selected_weapon = ITEM_INDEX(cl->pers.weapon);
	}

	// scan  for the next valid one
	for (i=1 ; i<=MAX_ITEMS ; i++)
	{
		index = (selected_weapon + MAX_ITEMS - i)%MAX_ITEMS;
		
		if (!cl->pers.inventory[index])
			continue;
		it = &itemlist[index];
		if (!it->use)
			continue;
		if (! (it->flags & IT_WEAPON) )
			continue;
		if (selected_weapon == ITEM_INDEX(it) && cl->newweapon)
		{
			// Ridah, show the current weapon on the hud, for easy scrolling
			if (deathmatch->value && !strstr(cl->newweapon->icon, "pipe"))
			{
				it = cl->newweapon;
				ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(it->icon);
				ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+ITEM_INDEX(it);
				ent->client->pickup_msg_time = level.time + 5.5;
			}

			return;	// successful
		}
		else
		{
			it->use (ent, it);
		}
	}
}

/*
=================
Cmd_WeapLast_f
=================
*/
void Cmd_WeapLast_f (edict_t *ent)
{
	gclient_t	*cl;
	int			index;
	gitem_t		*it;

	cl = ent->client;

	if (!cl->pers.weapon || !cl->pers.lastweapon)
		return;

	index = ITEM_INDEX(cl->pers.lastweapon);
	if (!cl->pers.inventory[index])
		return;
	it = &itemlist[index];
	if (!it->use)
		return;
	if (! (it->flags & IT_WEAPON) )
		return;
	it->use (ent, it);

	// Ridah, show the current weapon on the hud, for easy scrolling
	if (deathmatch && !strstr(it->icon, "pipe"))
	{
		ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(it->icon);
		ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+ITEM_INDEX(it);
		ent->client->pickup_msg_time = level.time + 5.5;
	}
}

/*
=================
Cmd_InvDrop_f
=================
*/
void Cmd_InvDrop_f (edict_t *ent)
{
	gitem_t		*it;
	int		index;
	char		*s;

	s = gi.args();

	ValidateSelectedItem (ent);

	if (ent->client->pers.selected_item == -1)
	{
		gi.cprintf (ent, PRINT_HIGH, "No item to drop.\n");
		return;
	}

	it = &itemlist[ent->client->pers.selected_item];
	if (!it->drop)
	{
		gi.cprintf (ent, PRINT_HIGH, "Item is not dropable.\n");
		return;
	}

	index = ITEM_INDEX(it);
	if (!ent->client->pers.inventory[index])
	{
		gi.cprintf (ent, PRINT_HIGH, "Out of item: %s\n", s);
		return;
	}

	it->drop (ent, it);
}

/*
=================
Cmd_Kill_f
=================
*/
void Cmd_Kill_f (edict_t *ent)
{
	// don't let spectators kill themselves
	if (ent->solid == SOLID_NOT)
		return;

	if((level.time - ent->client->respawn_time) < 5)
		return;
	ent->flags &= ~FL_GODMODE;
	ent->health = 0;
	meansOfDeath = MOD_SUICIDE;
	player_die (ent, ent, ent, 1, vec3_origin, 0, 0);
}

/*
=================
Cmd_PutAway_f
=================
*/
void Cmd_PutAway_f (edict_t *ent)
{
	ent->client->showscores = false;
	ent->client->showhelp = false;
	ent->client->showinventory = false;
}

int PlayerSort (void const *a, void const *b)
{
	int		anum, bnum;

	anum = *(int *)a;
	bnum = *(int *)b;

	anum = game.clients[anum].ps.stats[STAT_FRAGS];
	bnum = game.clients[bnum].ps.stats[STAT_FRAGS];

	if (anum < bnum)
		return -1;
	if (anum > bnum)
		return 1;
	return 0;
}

/*
=================
Cmd_Players_f
=================
*/
void Cmd_Players_f (edict_t *ent)
{
	int		i;
	int		count;
	char	small[64];
	char	large[1280];
	int		index[256];

	count = 0;
	for (i = 0 ; i < maxclients->value ; i++)
		if (game.clients[i].pers.connected)
		{
			index[count] = i;
			count++;
		}

	// sort by frags
// Ridah, disabled, so we can use this to list players we might want to "vote ban"
//	qsort (index, count, sizeof(index[0]), PlayerSort);

	// print information
	large[0] = 0;

	for (i = 0 ; i < count ; i++)
	{
		Com_sprintf (small, sizeof(small), "%3i - %s (%i frags)\n",
			index[i] + 1,
			game.clients[index[i]].pers.netname,
			game.clients[index[i]].ps.stats[STAT_FRAGS] );
		if (strlen (small) + strlen(large) > sizeof(large) - 100 )
		{	// can't print all of them in one packet
			strcat (large, "...\n");
			break;
		}
		strcat (large, small);
	}

	gi.cprintf (ent, PRINT_HIGH, "%s\n%i players\n", large, count);
}

/*
=================
Cmd_Wave_f
=================
*/
void Cmd_Wave_f (edict_t *ent, edict_t *other)
{
	char *cmd;
	int	rnd;

	cmd = gi.argv(0);

	if (!other->client)
		return;

	if (!ent->solid)
		return;

	// can't wave when ducked
	if (ent->client->ps.pmove.pm_flags & PMF_DUCKED)
		return;

	if (ent->client->last_wave > (level.time - 2) && (ent->client->last_wave <= level.time))
		return;

	ent->client->last_wave = level.time;

	// say something
	{

		if (!teamplay->value || (ent->client->pers.team != other->client->pers.team))
		{
			if (strstr(cmd, "key1"))
			{
				if (ent->gender == GENDER_MALE)
					Voice_Random(ent, other, player_profanity_level2, NUM_PLAYER_PROFANITY_LEVEL2);
				else if (ent->gender == GENDER_FEMALE)
					Voice_Random(ent, other, f_profanity_level2, F_NUM_PROFANITY_LEVEL2);
			}
			else	// profanity 3
			{
				if (ent->gender == GENDER_MALE)
					Voice_Random(ent, other, player_profanity_level3, NUM_PLAYER_PROFANITY_LEVEL3);
				else if (ent->gender == GENDER_FEMALE)
					Voice_Random(ent, other, f_profanity_level3, F_NUM_PROFANITY_LEVEL3);
			}
		}
		else	// stay here/moving out
		{
			if (strstr(cmd, "key3"))
			{		// hold
				if (ent->gender == GENDER_MALE)
					Voice_Random(ent, other, holdposition, NUM_HOLDPOSITION);
				else if (ent->gender == GENDER_FEMALE)
//					Voice_Random(ent, other, f_holdposition, F_NUM_HOLDPOSITION);
					Voice_Random(ent, other, rc_f_profanity_level1, 5);
			}
			else if (strstr(cmd, "key2"))	// lets go
			{
				if (ent->gender == GENDER_MALE)
					Voice_Random(ent, other, followme, NUM_FOLLOWME);
				else if (ent->gender == GENDER_FEMALE)
//					Voice_Random(ent, other, f_followme, F_NUM_FOLLOWME);
					Voice_Random(ent, other, rc_lola, 7);
			}
			else // converse
			{
				if (ent->gender == GENDER_MALE)
				{
					if (other->gender == GENDER_FEMALE)
						Voice_Random(ent, other, f_neutral_talk_player, F_NUM_NEUTRAL_TALK_PLAYER);
					else
						Voice_Random(ent, other, neutral_talk_player, NUM_NEUTRAL_TALK_PLAYER);
				}
				else if (ent->gender == GENDER_FEMALE)
				{
					Voice_Random(ent, other, f_neutral_talk, F_NUM_NEUTRAL_TALK);
				}
			}
		}
	}

	if (ent->client->anim_priority > ANIM_WAVE)
		return;

	ent->client->anim_priority = ANIM_WAVE;

	rnd = rand() % 3;

	switch (rnd)
	{
	case 0:
//		gi.cprintf (ent, PRINT_HIGH, "flipoff\n");
		ent->s.frame = FRAME_tg_bird_01-1;
		ent->client->anim_end = FRAME_tg_bird_10;
		break;
	case 1:
//		gi.cprintf (ent, PRINT_HIGH, "salute\n");
		ent->s.frame = FRAME_tg_crch_grab_01-1;
		ent->client->anim_end = FRAME_tg_crch_grab_16;
		break;
	case 2:
//		gi.cprintf (ent, PRINT_HIGH, "taunt\n");
		ent->s.frame = FRAME_tg_chin_flip_01-1;
		ent->client->anim_end = FRAME_tg_chin_flip_15;
		break;
	}

}

/*
==================
Cmd_Say_f
==================
*/
void Cmd_Say_f (edict_t *ent, qboolean team, qboolean arg0)
{
	int		i, j;
	edict_t	*other;
	char	*p;
	char	text[2048];
	gclient_t *cl;
	char	*ip;

	if (gi.argc () < 2 && !arg0)
		return;

	// don't let us talk if we were just kicked
	ip = Info_ValueForKey( ent->client->pers.userinfo, "ip" );
	if (ip && ip[0])
	{
		if (!strcmp(ip, last_kick_ip))
		{
			gi.cprintf( ent, PRINT_HIGH, "You cannot talk.\n" );
			return;
		}
	}

	if (!teamplay->value && !((int)(dmflags->value) & (DF_MODELTEAMS /*| DF_SKINTEAMS*/)))
		team = false;

	if (team)
		Com_sprintf (text, sizeof(text), ":(%s): ", ent->client->pers.netname);
	else
		Com_sprintf (text, sizeof(text), ":%s: ", ent->client->pers.netname);

	if (arg0)
	{
		strcat (text, gi.argv(0));
		strcat (text, " ");
		strcat (text, gi.args());
	}
	else
	{
		p = gi.args();

		if (*p == '"')
		{
			p++;
			p[strlen(p)-1] = 0;
		}
		strcat(text, p);
	}

	// don't let text be too long for malicious reasons
	if (strlen(text) > 150)
		text[150] = 0;

	strcat(text, "\n");

	if (flood_msgs->value) {
		cl = ent->client;

      if (level.time < cl->flood_locktill) {
			gi.cprintf(ent, PRINT_HIGH, "You can't talk for %d more seconds\n",
				(int)(cl->flood_locktill - level.time));
            return;
      }
      i = cl->flood_whenhead - flood_msgs->value + 1;
      if (i < 0)
          i = (sizeof(cl->flood_when)/sizeof(cl->flood_when[0])) + i;
		if (cl->flood_when[i] && 
			level.time - cl->flood_when[i] < flood_persecond->value) {
			cl->flood_locktill = level.time + flood_waitdelay->value;
			gi.cprintf(ent, PRINT_CHAT, "Flood protection:  You can't talk for %d seconds.\n",
				(int)flood_waitdelay->value);
         return;
      }

      // if they repeat themselves really quickly, bitch-slap time
		if (cl->flood_when[cl->flood_whenhead] && (cl->flood_when[cl->flood_whenhead] > level.time - 1) &&
			!strcmp( ent->client->flood_lastmsg, text ))
		{
			cl->flood_locktill = level.time + flood_waitdelay->value;
			gi.cprintf(ent, PRINT_CHAT, "Flood protection:  You can't talk for %d seconds.\n",
				(int)flood_waitdelay->value);
         return;
		}

		cl->flood_whenhead = (cl->flood_whenhead + 1) %
			(sizeof(cl->flood_when)/sizeof(cl->flood_when[0]));
		cl->flood_when[cl->flood_whenhead] = level.time;
	}

	strcpy( ent->client->flood_lastmsg, text );
	
	if (dedicated->value)
		gi.cprintf(NULL, PRINT_CHAT, "%s", text);

	for (j = 1; j <= game.maxclients; j++)
	{
		other = &g_edicts[j];
		if (!(other->inuse))
			continue;
		if (!(other->client))
			continue;
		if (team)
		{
			if (!OnSameTeam(ent, other))
				continue;
			if ((ent->client->pers.team == 0) != (other->client->pers.team == 0))
				continue;
		}
		gi.cprintf(other, PRINT_CHAT, "%s", text);
	}
}

/*
=================
ClientCommand
=================
*/
void ClientCommand (edict_t *ent)
{
	char	*cmd;

	if (!ent->client)
		return;		// not fully in game yet

	if (!ent->inuse)
		return;
		
	cmd = gi.argv(0);

	if (Q_stricmp (cmd, "players") == 0)
	{
		Cmd_Players_f (ent);
		return;
	}
	if (Q_stricmp (cmd, "say") == 0)
	{
		Cmd_Say_f (ent, false, false);
		return;
	}
	if (Q_stricmp (cmd, "say_team") == 0)
	{
		Cmd_Say_f (ent, true, false);
		return;
	}
	if (Q_stricmp (cmd, "score") == 0)
	{
		Cmd_Score_f (ent);
		return;
	}

	if (Q_stricmp (cmd, "help") == 0)
	{
		Cmd_Help_f (ent, 0);
		return;
	}
	else if (Q_stricmp (cmd, "invnext") == 0)
	{
		if (!ent->client->chase_target)		
			Cmd_Help_f (ent, 1);
		else
			SelectNextItem (ent, -1);
			
		return;
	}
	else if (Q_stricmp (cmd, "invprev") == 0)
	{
		if (!ent->client->chase_target)		
			Cmd_Help_f (ent, -1);
		else
			SelectPrevItem (ent, -1);
			
		return;
	}


	if (level.intermissiontime)
		return;

	// RAFAEL
	if (level.cut_scene_time)
		return;
	
	else if (level.pawn_time)
	{
	
		if (Q_stricmp (cmd, "invuse") == 0)
			PawnBuy (ent);

		else if (Q_stricmp (cmd, "leftarrow") == 0)
			PawnLeft (ent);
		else if (Q_stricmp (cmd, "rightarrow") == 0)
			PawnRight (ent);
		// JOSEPH 6-FEB-99
		else if (Q_stricmp (cmd, "uparrow") == 0)
			PawnPrev (ent);
		else if (Q_stricmp (cmd, "downarrow") == 0)
			PawnNext (ent);		
		// END JOSEPH
		else if (Q_stricmp (cmd, "key1") == 0)
			PawnAgree (ent);
		else if (Q_stricmp (cmd, "key3") == 0)
			PawnDisagree (ent);

		else if (Q_stricmp (cmd, "inven") == 0)
			Cmd_Inven_f (ent);
		// not sure if we are going to have a sell key
		// else if (Q_stricmp (cmd, "invnextw") == 0)
		//	PawnSell (ent);
		return;
	}

	// JOSEPH 6-FEB-99
	if (Q_stricmp (cmd, "leftarrow") == 0)
		;
	else if (Q_stricmp (cmd, "rightarrow") == 0)
		;
	else if (Q_stricmp (cmd, "uparrow") == 0)
		;
	else if (Q_stricmp (cmd, "downarrow") == 0)
		;		
	else if (Q_stricmp (cmd, "use") == 0)
		Cmd_Use_f (ent);
	// END JOSEPH
	else if (Q_stricmp (cmd, "drop") == 0)
		Cmd_Drop_f (ent);
	else if (Q_stricmp (cmd, "give") == 0)
		Cmd_Give_f (ent);
	else if (Q_stricmp (cmd, "immortal") == 0)
		Cmd_God_f (ent);
	else if (Q_stricmp (cmd, "notarget") == 0)
		Cmd_Notarget_f (ent);
	else if (Q_stricmp (cmd, "noclip") == 0)
		Cmd_Noclip_f (ent);
	else if (Q_stricmp (cmd, "inven") == 0)
		Cmd_Inven_f (ent);
	
	else if (Q_stricmp (cmd, "invnextw") == 0)
		SelectNextItem (ent, IT_WEAPON);
	else if (Q_stricmp (cmd, "invprevw") == 0)
		SelectPrevItem (ent, IT_WEAPON);
	else if (Q_stricmp (cmd, "invnextp") == 0)
		SelectNextItem (ent, IT_POWERUP);
	else if (Q_stricmp (cmd, "invprevp") == 0)
		SelectPrevItem (ent, IT_POWERUP);
	else if (Q_stricmp (cmd, "invuse") == 0)
		Cmd_InvUse_f (ent);
	else if (Q_stricmp (cmd, "invdrop") == 0)
		Cmd_InvDrop_f (ent);
	else if (Q_stricmp (cmd, "weapprev") == 0)
		Cmd_WeapPrev_f (ent);
	else if (Q_stricmp (cmd, "weapnext") == 0)
		Cmd_WeapNext_f (ent);
	// JOSEPH 29-DEC-98
	else if (Q_stricmp (cmd, "+activate") == 0)
		Cmd_Activate_f (ent);
	else if (Q_stricmp (cmd, "holster") == 0)
		Cmd_Holster_f (ent);
	else if (Q_stricmp (cmd, "hud") == 0)
		Cmd_Hud_f (ent);
	// END JOSEPH
	
	// RAFAEL
	else if (Q_stricmp (cmd, "flashlight") == 0)
		Cmd_Flashlight_f (ent);
	// RAFAEL 01-11-99
	else if (Q_stricmp (cmd, "reload") == 0)
		Cmd_Reload_f (ent);
	// END 01-11-99	
	else if (Q_stricmp (cmd, "weaplast") == 0)
		Cmd_WeapLast_f (ent);
	else if (Q_stricmp (cmd, "kill") == 0)
		Cmd_Kill_f (ent);
	else if (Q_stricmp (cmd, "putaway") == 0)
		Cmd_PutAway_f (ent);
//	else if (Q_stricmp (cmd, "wave") == 0)
//		Cmd_Wave_f (ent);
// BEGIN:	Xatrix/Ridah/Navigator/23-mar-1998
	else if (Q_stricmp (cmd, "nav_debug_dest") == 0)
		Cmd_NavDebugDest_f (ent);
	else if (Q_stricmp (cmd, "nav_debug_showpath") == 0)
		Cmd_NavDebugShowPath_f (ent);
	else if (Q_stricmp (cmd, "nav_showpath") == 0)
		Cmd_NavDebugShowPath_f (ent);
	else if (Q_stricmp (cmd, "nav_save") == 0)
		NAV_WriteActiveNodes ( ent->active_node_data, level.mapname );
	else if (Q_stricmp (cmd, "nav_clear") == 0)
		Cmd_NavClear_f ( ent );
	else if (Q_stricmp (cmd, "nav_rebuild") == 0)
		NAV_RebuildRoutes( level.node_data );
// END:		Xatrix/Ridah/Navigator/23-mar-1998

	else if (Q_stricmp (cmd, "spawn") == 0)
		Cmd_Spawn_f (ent);

	// Ridah, new 3 key command system
	else if (strstr (cmd, "key") == cmd)
		Cmd_Key_f (ent);

	// Ridah, Chasecam
	else if (Q_stricmp (cmd, "togglecam") == 0)
		Cmd_ToggleCam_f (ent);

	// Ridah, Lightpaint
	else if (Q_stricmp (cmd, "burn_save") == 0)
		Cmd_BurnSave_f (ent);

	// Ridah, Vehicles
	else if (Q_stricmp (cmd, "gear_up") == 0)
		Cmd_GearUp_f (ent);
	else if (Q_stricmp (cmd, "gear_down") == 0)
		Cmd_GearDown_f (ent);

//	else if (Q_stricmp (cmd, "gettexture") == 0)
//		Cmd_GetTexture_f (ent);

	// JOSEPH 23-MAR-99
	else if (Q_stricmp (cmd, "hideprops") == 0)
		Cmd_SetProps_f (0);
	else if (Q_stricmp (cmd, "showprops") == 0)
		Cmd_SetProps_f (1);
	else if (Q_stricmp (cmd, "extracrispy") == 0)
		Cmd_FryAll_f (ent);
	// END JOSEPH

//	else if (Q_stricmp (cmd, "gibtest") == 0)
//		Cmd_GibTest_f (ent);

	// Teamplay commands
	else if ((Q_stricmp (cmd, "join") == 0) || (Q_stricmp (cmd, "team") == 0))
		Cmd_Join_f (ent, gi.argv (1));
	else if ((Q_stricmp (cmd, "spec") == 0) || (Q_stricmp (cmd, "spectator") == 0))
		Cmd_Spec_f (ent);

	// voting system
	else if (Q_stricmp (cmd, "vote") == 0)
		Cmd_Vote_f (ent);
	else if ((Q_stricmp (cmd, "yes") == 0) || (Q_stricmp (cmd, "no") == 0))
		Cmd_Response_f (ent);
		
#if 0	// turn this off once we have the tables (not used by actual game code)
	// Ridah, new anorm calculations
	else if (Q_stricmp (cmd, "calc_anorms") == 0)
		Cmd_Anorms_f ();
	else if (Q_stricmp (cmd, "calc_adots") == 0)
		Cmd_Adots_f ();
	// done.
#endif

	else	// anything that doesn't match a command will be a chat
    Cmd_Say_f (ent, false, true);

}
