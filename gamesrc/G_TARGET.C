
#include "g_local.h"

/*QUAKED target_temp_entity (1 0 0) (-8 -8 -8) (8 8 8)
Fire an origin based temp entity event to the clients.
"style"		type byte
*/
void Use_Target_Tent (edict_t *ent, edict_t *other, edict_t *activator)
{
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (ent->style);
	gi.WritePosition (ent->s.origin);
	gi.multicast (ent->s.origin, MULTICAST_PVS);
}

void SP_target_temp_entity (edict_t *ent)
{
	ent->use = Use_Target_Tent;
}


//==========================================================

//==========================================================

/*QUAKED target_speaker (1 0 0) (-8 -8 -8) (8 8 8) looped-on looped-off reliable
"noise"		wav file to play
"attenuation"
-1 = none, send to whole level
1 = normal fighting sounds
2 = idle sound level
3 = ambient sound level
"volume"	0.0 to 1.0

Normal sounds play each time the target is used.  The reliable flag can be set for crucial voiceovers.

Looped sounds are always atten 3 / vol 1, and the use function toggles it on/off.
Multiple identical looping sounds will just increase volume without any speed cost.
*/
void Use_Target_Speaker (edict_t *ent, edict_t *other, edict_t *activator)
{
	int		chan;

	if (ent->spawnflags & 3)
	{	// looping sound toggles
		if (ent->s.sound)
			ent->s.sound = 0;	// turn it off
		else
			ent->s.sound = ent->noise_index;	// start it
	}
	else
	{	// normal sound
		if (ent->spawnflags & 4)
			chan = CHAN_VOICE|CHAN_RELIABLE;
		else
			chan = CHAN_VOICE;
		// use a positioned_sound, because this entity won't normally be
		// sent to any clients because it is invisible
		gi.positioned_sound (ent->s.origin, ent, chan, ent->noise_index, ent->volume, ent->attenuation, 0);
	}
}

void SP_target_speaker (edict_t *ent)
{
	char	buffer[MAX_QPATH];

	if(!st.noise)
	{
		gi.dprintf("target_speaker with no noise set at %s\n", vtos(ent->s.origin));
		return;
	}
	if (!strstr (st.noise, ".wav"))
		Com_sprintf (buffer, sizeof(buffer), "%s.wav", st.noise);
	else
		strncpy (buffer, st.noise, sizeof(buffer));
	ent->noise_index = gi.soundindex (buffer);

	if (!ent->volume)
		ent->volume = 1.0;

	if (!ent->attenuation)
		ent->attenuation = 1.0;
	else if (ent->attenuation == -1)	// use -1 so 0 defaults to 1
		ent->attenuation = 0;

	// check for prestarted looping sound
	if (ent->spawnflags & 1)
		ent->s.sound = ent->noise_index;

	ent->use = Use_Target_Speaker;

	// must link the entity so we get areas and clusters so
	// the server can determine who to send updates to
	gi.linkentity (ent);
}


//==========================================================

#if 0
void Use_Target_Help (edict_t *ent, edict_t *other, edict_t *activator)
{
	if (ent->spawnflags & 1)
		strncpy (game.helpmessage1, ent->message, sizeof(game.helpmessage2)-1);
	else
		strncpy (game.helpmessage2, ent->message, sizeof(game.helpmessage1)-1);

	game.helpchanged++;
}

/*QUAKED target_help (1 0 1) (-16 -16 -24) (16 16 24) help1
When fired, the "message" key becomes the current personal computer string, and the message light will be set on all clients status bars.
*/
void SP_target_help(edict_t *ent)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (ent);
		return;
	}

	if (!ent->message)
	{
		gi.dprintf ("%s with no message at %s\n", ent->classname, vtos(ent->s.origin));
		G_FreeEdict (ent);
		return;
	}
	ent->use = Use_Target_Help;
}
#endif

//==========================================================

/*QUAKED target_secret (1 0 1) (-8 -8 -8) (8 8 8)
Counts a secret found.
These are single use targets.
*/
void use_target_secret (edict_t *ent, edict_t *other, edict_t *activator)
{
	gi.sound (ent, CHAN_VOICE, ent->noise_index, 1, ATTN_NORM, 0);

	level.found_secrets++;

	G_UseTargets (ent, activator);
	G_FreeEdict (ent);
}

void SP_target_secret (edict_t *ent)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (ent);
		return;
	}

	ent->use = use_target_secret;
	if (!st.noise)
		st.noise = "misc/secret.wav";
	ent->noise_index = gi.soundindex (st.noise);
	ent->svflags = SVF_NOCLIENT;
	level.total_secrets++;
	// map bug hack
	if (!stricmp(level.mapname, "mine3") && ent->s.origin[0] == 280 && ent->s.origin[1] == -2048 && ent->s.origin[2] == -624)
		ent->message = "You have found a secret area.";
}

//==========================================================

/*QUAKED target_goal (1 0 1) (-8 -8 -8) (8 8 8)
Counts a goal completed.
These are single use targets.
*/
void use_target_goal (edict_t *ent, edict_t *other, edict_t *activator)
{
	gi.sound (ent, CHAN_VOICE, ent->noise_index, 1, ATTN_NORM, 0);

	level.found_goals++;

	if (level.found_goals == level.total_goals)
		gi.configstring (CS_CDTRACK, "0");

	G_UseTargets (ent, activator);
	G_FreeEdict (ent);
}

void SP_target_goal (edict_t *ent)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (ent);
		return;
	}

	ent->use = use_target_goal;
	if (!st.noise)
		st.noise = "misc/secret.wav";
	ent->noise_index = gi.soundindex (st.noise);
	ent->svflags = SVF_NOCLIENT;
	level.total_goals++;
}

//==========================================================

// JOSEPH 23-FEB-99
/*QUAKED target_explosion (1 0 0) (-8 -8 -8) (8 8 8)
Spawns an explosion temporary entity when used.

"delay"		wait this long before going off
"dmg"		how much radius damage should be done, defaults to 0
"fxdensity" size of explosion 1 - 100 (default is 10)
*/
void target_explosion_explode (edict_t *self)
{
	float		save;
	vec3_t	vec;

	VectorClear(vec);
	vec[2] = 1;

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_EXPLOSION1B);
	gi.WritePosition (self->s.origin);
	gi.WriteDir( vec );
	gi.WriteByte( (int)(self->dmg / 2) );
	gi.WriteByte (self->fxdensity);
	gi.multicast (self->s.origin, MULTICAST_PVS);

	{
		edict_t *breakit;
		
		breakit = G_Spawn();
		
		if (breakit)
		{
			VectorCopy (self->s.origin, breakit->s.origin);
			gi.linkentity(breakit);
			gi.sound (breakit, CHAN_VOICE, gi.soundindex("world/explosion1.wav"), 1, ATTN_NORM, 0);
			breakit->think = G_FreeEdict;
			breakit->nextthink = level.time + 5.0;
		}
	}

	T_RadiusDamage (self, self->activator, self->dmg, NULL, self->dmg+40, MOD_EXPLOSIVE);

	save = self->delay;
	self->delay = 0;
	G_UseTargets (self, self->activator);
	self->delay = save;
}
// END JOSEPH

void use_target_explosion (edict_t *self, edict_t *other, edict_t *activator)
{
	self->activator = activator;

	if (!self->delay)
	{
		target_explosion_explode (self);
		return;
	}

	self->think = target_explosion_explode;
	self->nextthink = level.time + self->delay;
}

void SP_target_explosion (edict_t *ent)
{
	ent->use = use_target_explosion;
	ent->svflags = SVF_NOCLIENT;
}

// JOSEPH 22-APR-99
/*QUAKED target_flamethrower (1 0 0) (-8 -8 -8) (8 8 8)
Shoots flame when triggered on, does not when triggered off.

"dmg" damage the flame does per frame (default 2)
"fxdensity 1" starts flame on
"deadticks" angle adjustment up and down -90 to +90 (deafult 0) 
*/
// END JOSEPH

// copied from CL_FlameEffects()
#define FLAME_SPEED			100.0		// increase to make it longer
#define	FLAME_LIFETIME		0.3

static vec3_t	jmins = {-16, -16,   0};
static vec3_t	jmaxs = { 16,  16,  24};

void FlameJunc_think__target_flamethrower( edict_t *self )
{
	vec3_t	oldorg;
	trace_t tr;

	VectorCopy( self->s.origin, oldorg );

	// move it
	VectorMA( self->s.origin, FRAMETIME, self->velocity, self->s.origin );

	tr = gi.trace( oldorg, jmins, jmaxs, self->s.origin, NULL, MASK_SOLID );

	if (tr.fraction < 1)
	{	// copied from ClipVelocity()
		#define	STOP_EPSILON	0.1

		float	backoff;
		float	change;
		int		i;

		// go through alpha surfaces
		if (tr.contents & MASK_ALPHA)
		{
			vec3_t	start, unitvel;
			float	maxdist, dist;

			if (tr.startsolid)
				maxdist = VectorLength( self->velocity ) * FRAMETIME;
			else
				maxdist = VectorLength( self->velocity ) * (1 - tr.fraction) * FRAMETIME;

			VectorNormalize2( self->velocity, unitvel );

			VectorCopy( tr.endpos, start );
			dist = 4;
			VectorMA( start, dist, unitvel, start );
			tr.startsolid = 1;		// to get us started

			while ((dist < maxdist) && tr.startsolid && (tr.contents & MASK_ALPHA))
			{
				tr = gi.trace ( start, jmins, jmaxs, self->s.origin, NULL, MASK_SOLID );

				dist += 4;
				VectorMA( start, 4, unitvel, start );
			}

			if (dist >= maxdist || tr.fraction == 1)
			{
				tr.fraction = 1;
				goto skip_clip;
			}
		}

		backoff = DotProduct (self->velocity, tr.plane.normal) * 1.5;	//slide

		for (i=0 ; i<3 ; i++)
		{
			change = tr.plane.normal[i]*backoff;
			self->velocity[i] = self->velocity[i] - change;
			if (self->velocity[i] > -STOP_EPSILON && self->velocity[i] < STOP_EPSILON)
				self->velocity[i] = 0;
		}

		VectorCopy( tr.endpos, self->s.origin );
		VectorMA( self->s.origin, 4, tr.plane.normal, self->s.origin );
		VectorNormalize2( self->velocity, self->last_step_pos );

		if (!self->acc)
		{
			// slow it down
			VectorScale( self->velocity, 0.5, self->velocity );
		}

		self->acc = true;

		if (strstr(tr.surface->name, "wood"))	// spawn some smoke
		{
			static vec3_t	last_pos;
			static float	last_time;
			vec3_t			sm_pos;

			// so we don't spawn too many sprites over each other
			if (last_time > (level.time - 0.5))
			{
				if (VectorDistance( last_pos, tr.endpos ) < 32)
					goto skip_smoke;
			}

			last_time = level.time;
			VectorCopy( tr.endpos, last_pos );

			VectorMA( tr.endpos, 16, tr.plane.normal, sm_pos );
			sm_pos[2] -= 12;

			gi.WriteByte (svc_temp_entity);
			gi.WriteByte (TE_SFXSMOKE);
			gi.WritePosition (sm_pos);
			gi.WriteByte (48);
			gi.WriteByte (0);
			gi.multicast (tr.endpos, MULTICAST_PVS);
		}

skip_smoke:;

	}

skip_clip:

	//NAV_DrawLine( self->s.old_origin, self->s.origin );

	// Now do the damage
	T_RadiusDamage_Fire( self, self->owner, self->dmg, NULL, 128);
	self->biketime = level.time;

	if (self->timestamp <= level.time)
	{
		G_FreeEdict( self );
		return;
	}

	self->nextthink = level.time + 0.1;
}

// JOSEPH 22-MAY-99
void fire_target_flamethrower (edict_t *self, vec3_t start, vec3_t forward, int damage, int kick, int mod)
{
	trace_t tr;
	vec3_t	end, xforward, xright, xup, dir;
	vec3_t	oldorg;
	edict_t	*junc;

	static vec3_t	mins = {-2, -2, -4};
	static vec3_t	maxs = { 2,  2,  4};

	vectoangles (forward, dir);
	AngleVectors (dir, xforward, xright, xup);
	VectorMA ( start, (FLAME_SPEED*FLAME_LIFETIME), xforward, end );

	tr = gi.trace (start, mins, maxs, end, self, MASK_SOLID);

	// Spawn a junction
	junc = G_Spawn();

	if (self->svflags & SVF_MONSTER)
		VectorCopy(start, junc->s.origin);
	else
		VectorCopy(self->s.origin, junc->s.origin);

	VectorScale( forward, FLAME_SPEED, junc->velocity );
	VectorCopy( forward, junc->last_step_pos );			// last_step_pos is unit vel

	// move it to the fadein position
	VectorCopy( junc->s.origin, oldorg );
	VectorMA( junc->s.origin, 1, junc->velocity, junc->s.origin );

	// trace the spawning location
	tr = gi.trace ( oldorg, jmins, jmaxs, junc->s.origin, self, MASK_SOLID );

	VectorCopy( tr.endpos, junc->s.origin );

	junc->acc = 0;		// hit wall flag
	junc->biketime = 0;
	junc->owner = self;
	VectorCopy( junc->s.origin, junc->s.old_origin );

	junc->timestamp = level.time + FLAME_LIFETIME;

	junc->think = FlameJunc_think__target_flamethrower;
	junc->dmg  = damage;
	junc->nextthink = level.time + 0.1;
}

void target_flamethrower (edict_t *self)
{
	if (self->fxdensity)
	{
		vec3_t forward;
			
		AngleVectors (self->s.angles, forward, NULL, NULL);
		fire_target_flamethrower(self, self->s.origin, forward, self->dmg, 0, MOD_FLAMETHROWER);

		self->s.renderfx2 = RF2_FLAMESHOOTER;
		self->s.renderfx2 |= RF2_FLAMESHOOTER_MOD;

		self->healspeed++;
		
		if (self->healspeed > 2)
			self->healspeed = 0;

		if (self->healspeed == 1)
			gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/flame_thrower/flame2.wav"), 1, ATTN_NORM, 0);
		else if (self->healspeed == 2)
			gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/flame_thrower/flame3.wav"), 1, ATTN_NORM, 0);
		else
			gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/flame_thrower/flame1.wav"), 1, ATTN_NORM, 0);

		self->think = target_flamethrower;
		self->nextthink = level.time + FRAMETIME;
	}
}

void use_target_flamethrower (edict_t *self, edict_t *other, edict_t *activator)
{
	self->activator = activator;
	
	if (!self->fxdensity)
	{
		self->fxdensity = 1;
		target_flamethrower(self);
	}
	else
	{	
		self->s.renderfx2 = 0;
		self->fxdensity = 0;
	}
}
// END JOSEPH

// JOSEPH 11-MAY-99
void SP_target_flamethrower (edict_t *ent)
{
	ent->use = use_target_flamethrower;
	
	ent->s.modelindex = gi.modelindex("models/weapons/sshell_md2/tris.md2");

	ent->s.renderfx |= RF_BEAM;

	gi.linkentity (ent);	

	if (!ent->dmg)
		ent->dmg = 2;
	
	ent->s.angles[0] = ent->deadticks;

	if (ent->fxdensity)
	{
		ent->think = target_flamethrower;
		ent->nextthink = level.time + (FRAMETIME*2);
	}
}
// END JOSEPH

// JOSEPH 19-APR-99
/*QUAKED target_fire (1 0 0) (-8 -8 -8) (8 8 8)

Spawns a fire.

"fxdensity"  size of fire 1 - 100 (default is 10)
"deadticks"  random fire sections per frame (deafult 3) 
"duration "  seconds fire lasts (default 5.0) (-1 keeps on going and going)
"dmg"        damage per second (default = fxdensity)
"reactdelay" fire spread factor 0.0 - 10.0 (default 1.0)
*/
// END JOSEPH

// JOSEPH 21-APR-99
void t_hurt_fire (edict_t *self)
{
	if (self->timestamp > level.time)
		return;

	self->timestamp = level.time + 1;

	T_RadiusDamage_Fire (self, self, self->dmg, NULL, self->firetype);
	//T_RadiusDamage (self, self, self->dmg, NULL, self->firetype, MOD_LAVA);
}
// END JOSEPH

void t_fire_think( edict_t *ent)
{
	int i;
	
	ent->nextthink = level.time + 0.1;
	ent->lastduration += 0.1;	

	for (i = 0; i < ent->deadticks; i++)
	{
		vec3_t neworigin;

		VectorCopy(ent->s.origin, neworigin);
		neworigin[0] += ent->reactdelay * ((rand()&3) * ((0.20*ent->firetype)-(0.10*ent->firetype))); 
		neworigin[1] += ent->reactdelay * ((rand()&3) * ((0.20*ent->firetype)-(0.10*ent->firetype))); 
		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_SFXFIRET);
		gi.WritePosition (neworigin);
		gi.WriteByte (ent->firetype);
		gi.WriteByte (ent->alphalevel);
		gi.multicast (neworigin, MULTICAST_PVS);
	}
	
	// JOSEPH 16-APR-99
	if (ent->dmg)
	t_hurt_fire(ent);
	// END JOSEPH

	// JOSEPH 19-APR-99
	if ((ent->duration != -1.0) && (ent->lastduration >= ent->duration)) 
		G_FreeEdict(ent);
	// END JOSEPH
}

// JOSEPH 4-MAY-99
void t_start_fire (edict_t *ent, edict_t *other, edict_t *activator)
{
	if (ent->nextthink)
	{
		ent->think = NULL;
		ent->nextthink = 0;
	}
	else
	{
	if (!ent->fxdensity)
		ent->fxdensity = 10;
	if (!ent->deadticks)
		ent->deadticks = 3;
    ent->alphalevel = 5;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->firetype = ent->fxdensity;
    ent->lastduration = 0;
	if (!ent->duration)
		ent->duration = 5.0;
	if (!ent->dmg)
		ent->dmg = ent->fxdensity;
	if (!ent->reactdelay)
		ent->reactdelay = 1.0;
	ent->s.origin[2] += ((float)ent->fxdensity) * 0.6;
	gi.linkentity (ent);
	ent->think = t_fire_think;
	ent->nextthink = level.time + 0.1;
	AddLightSource(ent);
		G_UseTargets (ent, ent->activator);
	}
}

void SP_target_fire (edict_t *self)
{
	if (self->targetname)
	{
		self->use = t_start_fire;
	}

	t_start_fire(self, NULL, NULL);
}
// END JOSEPH

//==========================================================

/*QUAKED target_changelevel (1 0 0) (-8 -8 -8) (8 8 8)
Changes level to "map" when fired
*/

extern qboolean	changing_levels;

// Ridah 5-8-99
extern char	last_changelevel[];

void use_target_changelevel (edict_t *self, edict_t *other, edict_t *activator)
{
	int	i, j, k;
	edict_t	*e;

	if (level.intermissiontime)
		return;		// already activated

	if (!deathmatch->value && !coop->value)
	{
		if (g_edicts[1].health <= 0)
			return;
	}

	// if noexit, do a ton of damage to other
	if (deathmatch->value && !( (int)dmflags->value & DF_ALLOW_EXIT) && other != world)
	{
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, 10 * other->max_health, 1000, 0, MOD_EXIT);
		return;
	}

	// if multiplayer, let everyone know who hit the exit
	if (deathmatch->value)
	{
		if (activator && activator->client)
			gi.bprintf (PRINT_HIGH, "%s exited the level.\n", activator->client->pers.netname);
	}

	// if going to a new unit, clear cross triggers
	if (strstr(self->map, "*"))	
		game.serverflags &= ~(SFL_CROSS_TRIGGER_MASK);

	// Ridah, 5-8-99, save this mapname for "pawn_" checking
	strcpy( last_changelevel, level.mapname );

	// Ridah, copy the episode_flags over
	if (activator->client)
	{
		activator->client->pers.episode_flags |= activator->episode_flags;
	}
	else // something has gone very wrong
	{
		{
			edict_t *player;

			player = &g_edicts[1];

			activator = player;
			activator->client->pers.episode_flags |= activator->episode_flags;	
		}
	}

if (!deathmatch->value)
{
	
	// Ridah, save any followers temporarily so we can carry them through to the next level
	changing_levels = true;

	// Ridah, 7-5-99, prevent friendly's following into pawn-o-matic
	if (strstr( self->map, "pawn" ) != self->map)
	{
		for (i=0; i<level.num_characters; i++)
		{
			if (!level.characters[i])
				continue;

			e = level.characters[i];

			if (!e || e->client || e->health <= 0)
				continue;

			if (!e->leader)
				continue;

			if (e->leader != activator)
				continue;

			if (VectorDistance( e->s.origin, activator->s.origin ) > 512)
				continue;

			// mark them as followers
			e->flags |= FL_FOLLOWING;

			// save this dude
			strcpy( followers[num_followers].classname, e->classname );
			if (e->name)
				strcpy( followers[num_followers].name, e->name );
			else
				memset( followers[num_followers].name, 0, sizeof(followers[num_followers].name) );

			if (e->art_skins)
				strcpy( followers[num_followers].art_skins, e->art_skins );
			else
				memset( followers[num_followers].art_skins, 0, sizeof(followers[num_followers].art_skins) );

			followers[num_followers].health = e->health;
			followers[num_followers].max_health = e->max_health;
			followers[num_followers].head = e->head;
			followers[num_followers].scale = e->cast_info.scale;
			followers[num_followers].spawnflags = e->spawnflags;
			followers[num_followers].count = e->count;	// for the Runt

			for (j=0; j<e->s.num_parts; j++)
			{
				for (k=0; k<MAX_MODELPART_OBJECTS; k++)
				{
					followers[num_followers].skinofs[j][k] = ((int)e->s.model_parts[j].skinnum[k]) - e->s.model_parts[j].baseskin;
				}
			}

			num_followers++;

			if (num_followers > MAX_FOLLOWERS)
				break;
		}
	}
	
}

	BeginIntermission (self);
}

void SP_target_changelevel (edict_t *ent)
{
	if (!ent->map)
	{
		gi.dprintf("target_changelevel with no map at %s\n", vtos(ent->s.origin));
		G_FreeEdict (ent);
		return;
	}

	// ugly hack because *SOMEBODY* screwed up their map
//   if((stricmp(level.mapname, "fact1") == 0) && (stricmp(ent->map, "fact3") == 0))
//	   ent->map = "fact3$secret1";

	ent->use = use_target_changelevel;
	ent->svflags = SVF_NOCLIENT;
}


//==========================================================

// JOSEPH 7-MAR-99
/*QUAKED target_splash (1 0 0) (-8 -8 -8) (8 8 8)
Creates a particle splash effect when used.

Set "sounds" to one of the following:
  1) sparks
  2) blue water
  3) brown water
  4) slime
  5) lava
  6) blood
  7) fireworks	
  8) smoke

FOR SMOKE
	"alphalevel" 1 - 10 (default 4)
	"firetype"   smoke size (5 - 32) 5 = extra small
	   10 = small 24 = med 32 = large (default 24)
	"deadticks"  life in seconds 1 - 60 (default 6)
	"fxdensity"  speed of rising smoke 1 - 100  (default 24)
	"count"      puffs of smoke 1 - 10;  (default 3)
	"rotate"     X Y Z velocity to project smoke (up is default)
END SMOKE
"count"	how many pixels in the splash
"dmg"	if set, does a radius damage at this location when it splashes
		useful for lava/sparks
*/

void use_target_splash (edict_t *self, edict_t *other, edict_t *activator)
{
	if (self->sounds == 8)
	{
		int		i;
		vec3_t	vec;
		vec3_t	origin;

		VectorClear(vec);
		vec[2] = 1;

		if (!self->firetype)
			self->firetype = 24;
		else
		{
			if (self->firetype < 5)
				self->firetype = 5;

			if (self->firetype > 32)
				self->firetype = 32;
		}
		
		if (!self->deadticks)
			self->deadticks = 6;
		else
		{
			if (self->deadticks < 1)
				self->deadticks = 1;

			if (self->deadticks > 60)
				self->deadticks = 60;
		}
		
		if (!self->fxdensity)
			self->fxdensity = 24;		
		else
		{
			if (self->fxdensity < 1)
				self->fxdensity = 1;

			if (self->fxdensity > 100)
				self->fxdensity = 100;
		}

		if (!self->count)
			self->count = 3;
		else
		{
			if (self->count < 1)
				self->count = 1;

			if (self->count > 10)
				self->count = 10;
		}

		for (i=0; i < self->count; i++)
		{
			VectorCopy(self->s.origin, origin);
			
			if ((!self->rotate[0]) && (!self->rotate[1]) && (!self->rotate[2]))
			{
			origin[0] += (rand()&15)-8;
			origin[1] += (rand()&15)-8;
				origin[2] += (rand()&7)-4;
			}
			else
			{
				origin[0] += (rand()&7)-4;
				origin[1] += (rand()&7)-4;
				origin[2] += (rand()&7)-4;
			}

			gi.WriteByte (svc_temp_entity);
			gi.WriteByte (TE_SFXSMOKE2);
			gi.WritePosition (origin);
			gi.WritePosition (self->rotate);
			gi.WriteByte (self->firetype);
			gi.WriteByte (self->deadticks);
			gi.WriteByte (self->fxdensity);
			if (self->alphalevel)
			{
				gi.WriteByte (self->alphalevel);
			}
			else
			{
				gi.WriteByte (0);
			}
			gi.multicast (self->s.origin, MULTICAST_PVS);
		}
	}
	else if (self->sounds == 7)
	{
		vec3_t	vec;

		VectorClear(vec);
		vec[2] = 1;

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_EXPLOSION1C);
		gi.WritePosition (self->s.origin);
		gi.WriteDir( vec );
		gi.WriteByte( (int)(self->count) );
		gi.WriteByte (self->fxdensity);
		gi.multicast (self->s.origin, MULTICAST_PVS);
	}
	else
	{
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SPLASH);
	gi.WriteByte (self->count);
	gi.WritePosition (self->s.origin);
	gi.WriteDir (self->movedir);
	gi.WriteByte (self->sounds);
	gi.multicast (self->s.origin, MULTICAST_PVS);
	}

	if (self->dmg)
		T_RadiusDamage (self, activator, self->dmg, NULL, self->dmg+40, MOD_SPLASH);
}
// END JOSEPH

void SP_target_splash (edict_t *self)
{
	self->use = use_target_splash;
	G_SetMovedir (self->s.angles, self->movedir);

	if (!self->count)
		self->count = 32;

	self->svflags = SVF_NOCLIENT;
}


//==========================================================

/*QUAKED target_spawner (1 0 0) (-8 -8 -8) (8 8 8) 1 2 3 4 5 6
Set target to the type of entity you want spawned.
Useful for spawning monsters and gibs in the factory levels.

For monsters:
	Set direction to the facing you want it to have.

For gibs:
	Set direction if you want it moving and
	speed how fast it should be moving otherwise it
	will just be dropped
*/
void ED_CallSpawn (edict_t *ent);

void use_target_spawner (edict_t *self, edict_t *other, edict_t *activator)
{
	edict_t	*ent;

	ent = G_Spawn();
	ent->classname = self->target;
	ent->flags = self->flags;
	VectorCopy (self->s.origin, ent->s.origin);
	VectorCopy (self->s.angles, ent->s.angles);
	ED_CallSpawn (ent);
	gi.unlinkentity (ent);
	KillBox (ent);
	gi.linkentity (ent);
	if (self->speed)
		VectorCopy (self->movedir, ent->velocity);
}

void SP_target_spawner (edict_t *self)
{
	self->use = use_target_spawner;
	self->svflags = SVF_NOCLIENT;
	if (self->speed)
	{
		G_SetMovedir (self->s.angles, self->movedir);
		VectorScale (self->movedir, self->speed, self->movedir);
	}
}

//==========================================================

// JOSEPH 8-FEB-99
/*UAKED target_blaster (1 0 0) (-8 -8 -8) (8 8 8) NOTRAIL NOEFFECTS
Fires a blaster bolt in the set direction when triggered.

dmg		default is 15
speed	default is 1000
*/

void use_target_blaster (edict_t *self, edict_t *other, edict_t *activator)
{
	int effect;

	if (self->spawnflags & 2)
		effect = 0;
	else if (self->spawnflags & 1)
		effect = EF_HYPERBLASTER;
	else
		effect = EF_BLASTER;

	fire_blaster (self, self->s.origin, self->movedir, self->dmg, self->speed, EF_BLASTER, MOD_TARGET_BLASTER);
	gi.sound (self, CHAN_VOICE, self->noise_index, 1, ATTN_NORM, 0);
}

void SP_target_blaster (edict_t *self)
{
	self->use = use_target_blaster;
	G_SetMovedir (self->s.angles, self->movedir);
	self->noise_index = gi.soundindex ("weapons/laser2.wav");

	if (!self->dmg)
		self->dmg = 15;
	if (!self->speed)
		self->speed = 1000;

	self->svflags = SVF_NOCLIENT;
}


//==========================================================

/*QUAKED target_crosslevel_trigger (.5 .5 .5) (-8 -8 -8) (8 8 8) trigger1 trigger2 trigger3 trigger4 trigger5 trigger6 trigger7 trigger8
Once this trigger is touched/used, any trigger_crosslevel_target with the same trigger number is automatically used when a level is started within the same unit.  It is OK to check multiple triggers.  Message, delay, target, and killtarget also work.
*/
void trigger_crosslevel_trigger_use (edict_t *self, edict_t *other, edict_t *activator)
{
	game.serverflags |= self->spawnflags;
	G_FreeEdict (self);
}

void SP_target_crosslevel_trigger (edict_t *self)
{
	self->svflags = SVF_NOCLIENT;
	self->use = trigger_crosslevel_trigger_use;
}

/*QUAKED target_crosslevel_target (.5 .5 .5) (-8 -8 -8) (8 8 8) trigger1 trigger2 trigger3 trigger4 trigger5 trigger6 trigger7 trigger8
Triggered by a trigger_crosslevel elsewhere within a unit.  If multiple triggers are checked, all must be true.  Delay, target and
killtarget also work.

"delay"		delay before using targets if the trigger has been activated (default 1)
*/
void target_crosslevel_target_think (edict_t *self)
{
	if (self->spawnflags == (game.serverflags & SFL_CROSS_TRIGGER_MASK & self->spawnflags))
	{
		G_UseTargets (self, self);
		G_FreeEdict (self);
	}
}

void SP_target_crosslevel_target (edict_t *self)
{
	if (! self->delay)
		self->delay = 1;
	self->svflags = SVF_NOCLIENT;

	self->think = target_crosslevel_target_think;
	self->nextthink = level.time + self->delay;
}

//==========================================================

// JOSEPH 8-FEB-99
/*UAKED target_laser (0 .5 .8) (-8 -8 -8) (8 8 8) START_ON RED GREEN BLUE YELLOW ORANGE FAT
When triggered, fires a laser.  You can either set a target
or a direction.
*/

void target_laser_think (edict_t *self)
{
	edict_t	*ignore;
	vec3_t	start;
	vec3_t	end;
	trace_t	tr;
	vec3_t	point;
	vec3_t	last_movedir;
	int		count;

	if (self->spawnflags & 0x80000000)
		count = 8;
	else
		count = 4;

	if (self->enemy)
	{
		VectorCopy (self->movedir, last_movedir);
		VectorMA (self->enemy->absmin, 0.5, self->enemy->size, point);
		VectorSubtract (point, self->s.origin, self->movedir);
		VectorNormalize (self->movedir);
		if (!VectorCompare(self->movedir, last_movedir))
			self->spawnflags |= 0x80000000;
	}

	ignore = self;
	VectorCopy (self->s.origin, start);
	VectorMA (start, 2048, self->movedir, end);
	while(1)
	{
		tr = gi.trace (start, NULL, NULL, end, ignore, CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_DEADMONSTER);

		if (!tr.ent)
			break;

		// hurt it if we can
		if ((tr.ent->takedamage) && !(tr.ent->flags & FL_IMMUNE_LASER))
			T_Damage (tr.ent, self, self->activator, self->movedir, tr.endpos, vec3_origin, self->dmg, 1, DAMAGE_ENERGY, MOD_TARGET_LASER);

		// if we hit something that's not a monster or player or is immune to lasers, we're done
		if (!(tr.ent->svflags & SVF_MONSTER) && (!tr.ent->client))
		{
			if (self->spawnflags & 0x80000000)
			{
				self->spawnflags &= ~0x80000000;
				gi.WriteByte (svc_temp_entity);
				gi.WriteByte (TE_LASER_SPARKS);
				gi.WriteByte (count);
				gi.WritePosition (tr.endpos);
				gi.WriteDir (tr.plane.normal);
				gi.WriteByte (self->s.skinnum);
				gi.multicast (tr.endpos, MULTICAST_PVS);
			}
			break;
		}

		ignore = tr.ent;
		VectorCopy (tr.endpos, start);
	}

	VectorCopy (tr.endpos, self->s.old_origin);

	self->nextthink = level.time + FRAMETIME;
}

void target_laser_on (edict_t *self)
{
	if (!self->activator)
		self->activator = self;
	self->spawnflags |= 0x80000001;
	self->svflags &= ~SVF_NOCLIENT;
	target_laser_think (self);
}

void target_laser_off (edict_t *self)
{
	self->spawnflags &= ~1;
	self->svflags |= SVF_NOCLIENT;
	self->nextthink = 0;
}

void target_laser_use (edict_t *self, edict_t *other, edict_t *activator)
{
	self->activator = activator;
	if (self->spawnflags & 1)
		target_laser_off (self);
	else
		target_laser_on (self);
}

void target_laser_start (edict_t *self)
{
	edict_t *ent;

	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	self->s.renderfx |= RF_BEAM|RF_TRANSLUCENT;
	self->s.modelindex = 1;			// must be non-zero

	// set the beam diameter
	if (self->spawnflags & 64)
		self->s.frame = 16;
	else
		self->s.frame = 4;

	// set the color
	if (self->spawnflags & 2)
		self->s.skinnum = 0xf2f2f0f0;
	else if (self->spawnflags & 4)
		self->s.skinnum = 0xd0d1d2d3;
	else if (self->spawnflags & 8)
		self->s.skinnum = 0xf3f3f1f1;
	else if (self->spawnflags & 16)
		self->s.skinnum = 0xdcdddedf;
	else if (self->spawnflags & 32)
		self->s.skinnum = 0xe0e1e2e3;

	if (!self->enemy)
	{
		if (self->target)
		{
			ent = G_Find (NULL, FOFS(targetname), self->target);
			if (!ent)
				gi.dprintf ("%s at %s: %s is a bad target\n", self->classname, vtos(self->s.origin), self->target);
			self->enemy = ent;
		}
		else
		{
			G_SetMovedir (self->s.angles, self->movedir);
		}
	}
	self->use = target_laser_use;
	self->think = target_laser_think;

	if (!self->dmg)
		self->dmg = 1;

	VectorSet (self->mins, -8, -8, -8);
	VectorSet (self->maxs, 8, 8, 8);
	gi.linkentity (self);

	if (self->spawnflags & 1)
		target_laser_on (self);
	else
		target_laser_off (self);
}

void SP_target_laser (edict_t *self)
{
	// let everything else get spawned before we start firing
	self->think = target_laser_start;
	self->nextthink = level.time + 1;
}


// JOSEPH 8-FEB-99
/*UAKED target_mal_laser (1 0 0) (-4 -4 -4) (4 4 4) START_ON RED GREEN BLUE YELLOW ORANGE FAT
Mal's laser
*/
void target_mal_laser_on (edict_t *self)
{
	if (!self->activator)
		self->activator = self;
	self->spawnflags |= 0x80000001;
	self->svflags &= ~SVF_NOCLIENT;
	// target_laser_think (self);
	self->nextthink = level.time + self->wait + self->delay;
}

void target_mal_laser_off (edict_t *self)
{
	self->spawnflags &= ~1;
	self->svflags |= SVF_NOCLIENT;
	self->nextthink = 0;
}

void target_mal_laser_use (edict_t *self, edict_t *other, edict_t *activator)
{
	self->activator = activator;
	if (self->spawnflags & 1)
		target_mal_laser_off (self);
	else
		target_mal_laser_on (self);
}

void mal_laser_think (edict_t *self)
{
	target_laser_think (self);
	self->nextthink = level.time + self->wait + 0.1;
	self->spawnflags |= 0x80000000;
}

void SP_target_mal_laser (edict_t *self)
{
	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	self->s.renderfx |= RF_BEAM|RF_TRANSLUCENT;
	self->s.modelindex = 1;			// must be non-zero

	// set the beam diameter
	if (self->spawnflags & 64)
		self->s.frame = 16;
	else
		self->s.frame = 4;

	// set the color
	if (self->spawnflags & 2)
		self->s.skinnum = 0xf2f2f0f0;
	else if (self->spawnflags & 4)
		self->s.skinnum = 0xd0d1d2d3;
	else if (self->spawnflags & 8)
		self->s.skinnum = 0xf3f3f1f1;
	else if (self->spawnflags & 16)
		self->s.skinnum = 0xdcdddedf;
	else if (self->spawnflags & 32)
		self->s.skinnum = 0xe0e1e2e3;

	G_SetMovedir (self->s.angles, self->movedir);
	
	if (!self->delay)
		self->delay = 0.1;

	if (!self->wait)
		self->wait = 0.1;

	if (!self->dmg)
		self->dmg = 5;

	VectorSet (self->mins, -8, -8, -8);
	VectorSet (self->maxs, 8, 8, 8);
	
	self->nextthink = level.time + self->delay;
	self->think = mal_laser_think;

	self->use = target_mal_laser_use;

	gi.linkentity (self);

	if (self->spawnflags & 1)
		target_mal_laser_on (self);
	else
		target_mal_laser_off (self);
}
// END	15-APR-98

//==========================================================

/*QUAKED target_lightramp (0 .5 .8) (-8 -8 -8) (8 8 8) TOGGLE
speed		How many seconds the ramping will take
message		two letters; starting lightlevel and ending lightlevel
*/

void target_lightramp_think (edict_t *self)
{
	char	style[2];

	style[0] = 'a' + self->movedir[0] + (level.time - self->timestamp) / FRAMETIME * self->movedir[2];
	style[1] = 0;
	gi.configstring (CS_LIGHTS+self->enemy->style, style);

	if ((level.time - self->timestamp) < self->speed)
	{
		self->nextthink = level.time + FRAMETIME;
	}
	else if (self->spawnflags & 1)
	{
		char	temp;

		temp = self->movedir[0];
		self->movedir[0] = self->movedir[1];
		self->movedir[1] = temp;
		self->movedir[2] *= -1;
	}
	// JOSEPH 16-OCT-98
	else
	{
		self->movedir[2] *= -1;
	}
	// END JOSEPH
}

void target_lightramp_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (!self->enemy)
	{
		edict_t		*e;

		// check all the targets
		e = NULL;
		while (1)
		{
			e = G_Find (e, FOFS(targetname), self->target);
			if (!e)
				break;
			if (strcmp(e->classname, "light") != 0)
			{
				gi.dprintf("%s at %s ", self->classname, vtos(self->s.origin));
				gi.dprintf("target %s (%s at %s) is not a light\n", self->target, e->classname, vtos(e->s.origin));
			}
			else
			{
				self->enemy = e;
			}
		}

		if (!self->enemy)
		{
			gi.dprintf("%s target %s not found at %s\n", self->classname, self->target, vtos(self->s.origin));
			G_FreeEdict (self);
			return;
		}
	}

	self->timestamp = level.time;
	target_lightramp_think (self);
}

void SP_target_lightramp (edict_t *self)
{
	if (!self->message || strlen(self->message) != 2 || self->message[0] < 'a' || self->message[0] > 'z' || self->message[1] < 'a' || self->message[1] > 'z' || self->message[0] == self->message[1])
	{
		gi.dprintf("target_lightramp has bad ramp (%s) at %s\n", self->message, vtos(self->s.origin));
		G_FreeEdict (self);
		return;
	}

	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	if (!self->target)
	{
		gi.dprintf("%s with no target at %s\n", self->classname, vtos(self->s.origin));
		G_FreeEdict (self);
		return;
	}

	self->svflags |= SVF_NOCLIENT;
	self->use = target_lightramp_use;
	self->think = target_lightramp_think;

	self->movedir[0] = self->message[0] - 'a';
	self->movedir[1] = self->message[1] - 'a';
	self->movedir[2] = (self->movedir[1] - self->movedir[0]) / (self->speed / FRAMETIME);
}

//==========================================================

/*QUAKED target_earthquake (1 0 0) (-8 -8 -8) (8 8 8)
When triggered, this initiates a level-wide earthquake.
All players and monsters are affected.
"speed"		severity of the quake (default:200)
"count"		duration of the quake (default:5)
*/

void target_earthquake_think (edict_t *self)
{
	int		i;
	edict_t	*e;

	if (self->last_move_time < level.time)
	{
		gi.positioned_sound (self->s.origin, self, CHAN_AUTO, self->noise_index, 1.0, ATTN_NONE, 0);
		self->last_move_time = level.time + 0.5;
	}

	for (i=1, e=g_edicts+i; i < globals.num_edicts; i++,e++)
	{
		if (!e->inuse)
			continue;
		if (!e->client)
			continue;
		if (!e->groundentity)
			continue;

		e->groundentity = NULL;
		e->velocity[0] += crandom()* 150;
		e->velocity[1] += crandom()* 150;
		e->velocity[2] = self->speed * (100.0 / e->mass);
	}

	if (level.time < self->timestamp)
		self->nextthink = level.time + FRAMETIME;
}

void target_earthquake_use (edict_t *self, edict_t *other, edict_t *activator)
{
	self->timestamp = level.time + self->count;
	self->nextthink = level.time + FRAMETIME;
	self->activator = activator;
	self->last_move_time = 0;
}

void SP_target_earthquake (edict_t *self)
{
	if (!self->targetname)
		gi.dprintf("untargeted %s at %s\n", self->classname, vtos(self->s.origin));

	if (!self->count)
		self->count = 5;

	if (!self->speed)
		self->speed = 200;

	self->svflags |= SVF_NOCLIENT;
	self->think = target_earthquake_think;
	self->use = target_earthquake_use;

	self->noise_index = gi.soundindex ("world/quake.wav");
}
