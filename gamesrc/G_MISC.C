// g_misc.c

#include "g_local.h"


/*QUAKED func_group (0 0 0) ?
Used to group brushes together just for editor convenience.
*/

//=====================================================

void Use_Areaportal (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->count ^= 1;		// toggle state
//	gi.dprintf ("portalstate: %i = %i\n", ent->style, ent->count);
	gi.SetAreaPortalState (ent->style, ent->count);
}

/*QUAKED func_areaportal (0 0 0) ?

This is a non-visible object that divides the world into
areas that are seperated when this portal is not activated.
Usually enclosed in the middle of a door.
*/
void SP_func_areaportal (edict_t *ent)
{
	ent->use = Use_Areaportal;
	ent->count = 0;		// always start closed;
}

//=====================================================


/*
=================
Misc functions
=================
*/
void VelocityForDamage (int damage, vec3_t v)
{
	v[0] = 300.0 * crandom();
	v[1] = 300.0 * crandom();
	v[2] = 200.0 + 400.0 * random();

	if (damage < 50)
		VectorScale (v, 0.7, v);
	else 
		VectorScale (v, 1.2, v);
}

void ClipGibVelocity (edict_t *ent)
{
	if (ent->velocity[0] < -400)
		ent->velocity[0] = -400;
	else if (ent->velocity[0] > 400)
		ent->velocity[0] = 400;
	if (ent->velocity[1] < -400)
		ent->velocity[1] = -400;
	else if (ent->velocity[1] > 400)
		ent->velocity[1] = 400;
	if (ent->velocity[2] < 200)
		ent->velocity[2] = 200;	// always some upwards
	else if (ent->velocity[2] > 500)
		ent->velocity[2] = 500;
}


/*
=================
gibs
=================
*/
void gib_think (edict_t *self)
{
	self->s.frame++;
	self->nextthink = level.time + FRAMETIME;

	if (self->s.frame == 10)
	{
		self->think = G_FreeEdict;
		self->nextthink = level.time + 8 + random()*10;
	}
}

void gib_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t	normal_angles, right;

	if (!self->groundentity)
		return;

	self->touch = NULL;

	if (plane)
	{
		// JOSEPH 29-MAR-99
		//gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/fhit3.wav"), 1, ATTN_NORM, 0);
		// END JOSEPH

		vectoangles (plane->normal, normal_angles);
		AngleVectors (normal_angles, NULL, right, NULL);
		vectoangles (right, self->s.angles);

		if (self->s.modelindex == sm_meat_index)
		{
			self->s.frame++;
			self->think = gib_think;
			self->nextthink = level.time + FRAMETIME;
		}
	}
}

// RAFAEL
/* Ridah, this has been diasabled in the latest code
void gib_touchacid (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t normal_angles, right;

	if (other->takedamage)
	{
		// T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0);
		T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);
		G_FreeEdict (self);
	}

	if (!self->groundentity)
		return;

	if (plane)
	{
		// JOSEPH 29-MAR-99
		gi.sound (self, CHAN_VOICE, gi.soundindex ("misc/fhit3.wav"), 1, ATTN_NORM, 0);
		// END JOSEPH

		vectoangles (plane->normal, normal_angles);
		AngleVectors (normal_angles, NULL, right, NULL);
		vectoangles (right, self->s.angles);

		if (self->s.modelindex == sm_meat_index)
		{
			self->s.frame++;
			self->think = gib_think;
			self->nextthink = level.time + FRAMETIME;
		}
	}
}
*/

void gib_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	G_FreeEdict (self);
}

edict_t *ThrowGib (edict_t *self, char *gibname, int damage, int type)
{
	edict_t *gib;
	vec3_t	vd;
	vec3_t	origin;
	vec3_t	size;
	float	vscale;

	gib = G_Spawn();

	VectorScale (self->size, 0.5, size);
	VectorAdd (self->absmin, size, origin);
	gib->s.origin[0] = origin[0] + crandom() * size[0];
	gib->s.origin[1] = origin[1] + crandom() * size[1];
	gib->s.origin[2] = origin[2] + crandom() * size[2];

	gi.setmodel (gib, gibname);
	gib->solid = SOLID_NOT;
	gib->s.effects |= EF_GIB;
	gib->flags |= FL_NO_KNOCKBACK;
	gib->takedamage = DAMAGE_YES;
	gib->s.renderfx2 |= RF2_NOSHADOW;
	gib->die = gib_die;

	if (type == GIB_ORGANIC)
	{
		gib->movetype = MOVETYPE_TOSS;
		gib->touch = gib_touch;
		vscale = 0.5;
	}
	else
	{
		gib->movetype = MOVETYPE_BOUNCE;
		vscale = 1.0;
	}

	VelocityForDamage (damage, vd);
	VectorMA (self->velocity, vscale, vd, gib->velocity);
	ClipGibVelocity (gib);
	gib->avelocity[0] = random()*600;
	gib->avelocity[1] = random()*600;
	gib->avelocity[2] = random()*600;

	gib->think = G_FreeEdict;
	gib->nextthink = level.time + 10 + random()*10;

	gi.linkentity (gib);

	return gib;
}



void ThrowHead (edict_t *self, char *gibname, int damage, int type)
{
	vec3_t	vd;
	float	vscale;

	self->s.skinnum = 0;
	self->s.frame = 0;
	VectorClear (self->mins);
	VectorClear (self->maxs);

//	self->s.modelindex2 = 0;
	gi.setmodel (self, gibname);
	self->solid = SOLID_NOT;
	self->s.effects |= EF_GIB;
	self->s.effects &= ~EF_FLIES;
	self->s.sound = 0;
	self->flags |= FL_NO_KNOCKBACK;
	self->svflags &= ~SVF_MONSTER;
	self->takedamage = DAMAGE_YES;
	self->die = gib_die;

	if (type == GIB_ORGANIC)
	{
		self->movetype = MOVETYPE_TOSS;
		self->touch = gib_touch;
		vscale = 0.5;
	}
	else
	{
		self->movetype = MOVETYPE_BOUNCE;
		vscale = 1.0;
	}

	VelocityForDamage (damage, vd);
	VectorMA (self->velocity, vscale, vd, self->velocity);
	ClipGibVelocity (self);

	self->avelocity[YAW] = crandom()*600;

	self->think = G_FreeEdict;
	self->nextthink = level.time + 10 + random()*10;

	gi.linkentity (self);
}





void ThrowClientHead (edict_t *self, int damage)
{
	vec3_t	vd;
	char	*gibname;
/*
	if (rand()&1)
	{
		gibname = "models/objects/gibs/head2/tris.md2";
		self->s.skinnum = 1;		// second skin is player
	}
	else
	{
		gibname = "models/objects/gibs/skull/tris.md2";
		self->s.skinnum = 0;
	}
*/
	gibname = "models/props/gibs/gib3.mdx";
	self->s.skinnum = 0;

	self->s.origin[2] += 32;
	self->s.frame = 0;

//	gi.setmodel (self, gibname);
	self->s.num_parts = 0;
	self->s.modelindex = gi.modelindex( gibname );

	VectorSet (self->mins, -16, -16, 0);
	VectorSet (self->maxs, 16, 16, 16);

	self->takedamage = DAMAGE_NO;
	self->solid = SOLID_NOT;
//	self->s.effects |= EF_GIB;
	self->s.sound = 0;
	self->flags |= FL_NO_KNOCKBACK;

	self->movetype = MOVETYPE_BOUNCE;
	VelocityForDamage (damage, vd);
	VectorAdd (self->velocity, vd, self->velocity);

	if (self->client)	// bodies in the queue don't have a client anymore
	{
		self->client->anim_priority = ANIM_DEATH;
		self->client->anim_end = self->s.frame;
	}
	else
	{
		self->think = NULL;
		self->nextthink = 0;
	}

	gi.linkentity (self);
}

/*
=============
GibEntity

  Gibs an entity.. can be used for client's or AI
=============
*/
void GibEntity( edict_t *self, edict_t *inflictor, float damage )
{
	vec3_t	dir, vel;
	int		m, n;

	// turn off flames
	if (self->onfiretime)
		self->onfiretime = 0;

	if (inflictor->client || VectorCompare( inflictor->velocity, vec3_origin) )
		VectorSubtract( self->s.origin, inflictor->s.origin, dir );
	else
		VectorCopy( inflictor->velocity, dir );

	VectorNormalize( dir );

	// JOSEPH 12-MAY-99-B
	// send the client-side gib message
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_GIBS);
	gi.WritePosition (self->s.origin);
	gi.WriteDir (dir);
	gi.WriteByte ( 16 );	// number of gibs
	gi.WriteByte ( (damage*2 > 128 ? 128 : (int)(damage*2)) );	// scale of direction to add to velocity
	gi.WriteByte ( 16 );	// random origin offset scale
	gi.WriteByte ( 100 );	// random velocity scale
	gi.multicast (self->s.origin, MULTICAST_PVS);
	// END JOSEPH

	for (n= 0; n < 6; n++)
	{

		VelocityForDamage (damage, vel);

		// spawn a decal in this direction
		for (m=0; m<4; m++)	// try 4 times with a different Z value
		{
			vec3_t	bdir;
			vec3_t	dorg;
			trace_t	tr;

			VectorCopy( vel, bdir );
			bdir[2] -= random()*bdir[2]*(1+4*random());

			VectorAdd( self->s.origin, bdir, dorg );

			tr = gi.trace( self->s.origin, NULL, NULL, dorg, self, MASK_SOLID );

			if (tr.fraction < 1 && tr.ent == &g_edicts[0] && !(tr.surface->flags & SURF_SKY))
			{
				float rnd;

				rnd = (1.5 + 5.0*random());
				if (SurfaceSpriteEffect(SFX_SPRITE_SURF_BLOOD1, (unsigned char)(SFX_BLOOD_WIDTH*rnd), (unsigned char)(SFX_BLOOD_HEIGHT*rnd),
										tr.ent, tr.endpos, tr.plane.normal))
				{
					break;
				}
			}

		}
	}

	if (!self->client)	// Ridah, added this check, since in deathmatch, the body is left there, just only clients with parental lock ENABLEd will see them, since they don't see the gibs
		ThrowClientHead (self, damage);

	self->takedamage = DAMAGE_NO;
}

/*
=================
debris
=================
*/
void debris_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	G_FreeEdict (self);
}

// JOSEPH 22-FEB-99
void Think_Debris (edict_t *ent)
{
	if (!ent->misstime--)
	{	
		ent->nextthink = 0;
		G_FreeEdict(ent);
	}
	else
	{
		if (ent->misstime <= 15)
		{
			if (ent->misstime == 15)
			{
				ent->s.renderfx2 |= RF2_PASSALPHA;
				ent->s.effects = 1;		// this is full alpha now
			}
			
			ent->s.effects += (255/15);
		
			if (ent->s.effects > 255)
				ent->s.effects = 255;
		}

		//ent->s.angles[1] += ent->avelocity[1];
		ent->nextthink = level.time + 0.1;
	}
}

void ThrowDebris (edict_t *self, char *modelname, float speed, vec3_t origin)
{
	edict_t	*chunk;
	vec3_t	v;

	chunk = G_Spawn();
	VectorCopy (origin, chunk->s.origin);
	gi.setmodel (chunk, modelname);
	v[0] = 50 * crandom();
	v[1] = 50 * crandom();
	v[2] = 50 + 50 * crandom();
	VectorMA (self->velocity, speed, v, chunk->velocity);
	chunk->movetype = MOVETYPE_BOUNCE;
	chunk->solid = SOLID_NOT;
	chunk->avelocity[0] = random()*600;
	chunk->avelocity[1] = random()*600;
	chunk->avelocity[2] = random()*600;
	chunk->think = G_FreeEdict;
	chunk->nextthink = level.time + 5 + random()*5;
	chunk->s.frame = 0;
	chunk->flags = 0;
	chunk->classname = "debris";
	chunk->takedamage = DAMAGE_YES;
	chunk->die = debris_die;
	
	chunk->think = Think_Debris;
	chunk->misstime = 20;
	chunk->nextthink = level.time + 0.1;
    chunk->s.renderfx2 |= RF2_NOSHADOW;
	chunk->avelocity[1] = ((rand()&15)-8);
	//chunk->s.angles[0] = 90;
	gi.linkentity (chunk);
}
// END JOSEPH

// JOSEPH 5-JUN-99-B
void ThrowDebris_stuff (edict_t *self, char *modelname, float speed, vec3_t origin)
{
	edict_t	*chunk;
	vec3_t	v;

	chunk = G_Spawn();
	VectorCopy (origin, chunk->s.origin);
	gi.setmodel (chunk, modelname);
	v[0] = 150 * crandom();
	v[1] = 150 * crandom();
	v[2] = 150 + 50 * crandom();
	VectorMA (self->velocity, speed, v, chunk->velocity);
	chunk->movetype = MOVETYPE_BOUNCE;
	chunk->solid = SOLID_NOT;
	chunk->avelocity[0] = random()*600;
	chunk->avelocity[1] = random()*600;
	chunk->avelocity[2] = random()*600;
	chunk->think = G_FreeEdict;
	chunk->nextthink = level.time + 5 + random()*5;
	chunk->s.frame = 0;
	chunk->flags = 0;
	chunk->classname = "debris";
	chunk->takedamage = DAMAGE_YES;
	chunk->die = debris_die;
	
	chunk->think = Think_Debris;
	chunk->misstime = 40;
	chunk->nextthink = level.time + 0.1;
    chunk->s.renderfx2 |= RF2_NOSHADOW;
	chunk->avelocity[1] = ((rand()&15)-8);
	chunk->lightit = 30;
	gi.linkentity (chunk);
}
// END JOSEPH

// JOSEPH 1-JUN-99
extern void rat_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject);

void BecomeExplosion1 (edict_t *self)
{
	if ((self->classname) && (!strcmp(self->classname, "props_rat")))
	{
		rat_die (self, NULL, NULL, 0, NULL, 0, 0);
	}
	else
	{
		vec3_t	vec;

		VectorClear(vec);
		vec[2] = 1;

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_EXPLOSION1);
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
		
		G_FreeEdict (self);
	}
}
// END JOSEPH

void BecomeExplosion2 (edict_t *self)
{
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_EXPLOSION2);
	gi.WritePosition (self->s.origin);
	gi.multicast (self->s.origin, MULTICAST_PVS);

	G_FreeEdict (self);
}




/*QUAKED path_corner_cast (.5 .3 0) (-16 -16 -24) (16 16 42) TELEPORT
Target: next path corner
Scriptname: hard-coded script to call when reaching this marker
Pathtarget: gets used when an entity that has
	this path_corner targeted touches it
	Could be used to trigger a button, or a character
Combattarget: when the cast reaches this marker,
	they'll take on this combattarget
*/

void path_corner_cast_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t		v;
	edict_t		*next;

	if ((other->goal_ent != self) && (other->combat_goalent != self))
		return;

	if (other->health < 0)
		return;
	
	if (self->pathtarget)
	{
		char *savetarget;

		savetarget = self->target;
		self->target = self->pathtarget;
		G_UseTargets (self, other);
		self->target = savetarget;
	}

	// play a sound if there is one
	if (self->name)
		gi.sound( other, CHAN_VOICE, gi.soundindex( self->name ), 1.0, 1, 0 );


	if (self->combattarget)
		other->next_combattarget = self->combattarget;

	if (self->target)
		next = G_PickTarget(self->target);
	else
		next = NULL;

	if ((next) && (next->spawnflags & 1))
	{
		VectorCopy (next->s.origin, v);
		v[2] += next->mins[2];
		v[2] -= other->mins[2];
		VectorCopy (v, other->s.origin);
		next = G_PickTarget(next->target);
	}

	if (other->goal_ent == self)
		other->goal_ent = next;
	else
		other->combat_goalent = next;

	if (self->wait)
	{
		other->cast_info.goal_ent_pausetime = level.time + self->wait;
		other->cast_info.currentmove = other->cast_info.move_stand;
		goto done;
	}

	if (!other->goal_ent && !other->combat_goalent)
	{
		// end of the line
		other->target = NULL;
		other->cast_info.currentmove = other->cast_info.move_stand;
	}
	else	// remember this marker
	{
		if (other->goal_ent == self)
		{
			other->target = other->goal_ent->target;
			VectorSubtract (other->goal_ent->s.origin, other->s.origin, v);
		}
		else	// combattarget
		{
			
			if (!(other->combat_goalent))
			{
				other->target = other->goal_ent->target;
				VectorSubtract (other->goal_ent->s.origin, other->s.origin, v);
			}
			else
			{
				VectorSubtract (other->combat_goalent->s.origin, other->s.origin, v);
				other->combat_goalent->cast_info.aiflags |= AI_GOAL_RUN;
			}

		}
		other->ideal_yaw = vectoyaw (v);
	}

done:

	// Ridah, hard-coded scripting
	if (self->scriptname)
		EP_EventScript( other, self->scriptname );

}

void SP_path_corner_cast (edict_t *self)
{
	if (!self->targetname)
	{
		gi.dprintf ("path_corner_cast with no targetname at %s\n", vtos(self->s.origin));
		G_FreeEdict (self);
		return;
	}

	strcpy(self->classname, "path_corner");		// so the existing code still works

	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 42);

	self->solid = SOLID_TRIGGER;
	self->touch = path_corner_cast_touch;
	self->svflags |= SVF_NOCLIENT;

	M_droptofloor(self);
	self->s.origin[2] += 4;

	gi.linkentity (self);
}

/*QUAKED path_corner (.5 .3 0) (-8 -8 -8) (8 8 8) TELEPORT
NOTE: Use path_corner_cast for character path's
Target: next path corner
Pathtarget: gets used when an entity that has
	this path_corner targeted touches it
*/

void path_corner_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t		v;
	edict_t		*next;

	if (other->movetarget != self)
		return;
	
	if (other->enemy)
		return;

	if (self->pathtarget)
	{
		char *savetarget;

		savetarget = self->target;
		self->target = self->pathtarget;
		G_UseTargets (self, other);
		self->target = savetarget;
	}

	if (self->target)
		next = G_PickTarget(self->target);
	else
		next = NULL;

	if ((next) && (next->spawnflags & 1))
	{
		VectorCopy (next->s.origin, v);
		v[2] += next->mins[2];
		v[2] -= other->mins[2];
		VectorCopy (v, other->s.origin);
		next = G_PickTarget(next->target);
	}

	other->goalentity = other->movetarget = next;

	if (self->wait)
	{
		other->cast_info.pausetime = level.time + self->wait;
//		other->cast_info.stand (other);
		return;
	}

	if (!other->movetarget)
	{
		other->cast_info.pausetime = level.time + 100000000;
//		other->cast_info.stand (other);
	}
	else
	{
		VectorSubtract (other->goalentity->s.origin, other->s.origin, v);
		other->ideal_yaw = vectoyaw (v);
	}

}

void SP_path_corner (edict_t *self)
{
	if (!self->targetname)
	{
		gi.dprintf ("path_corner with no targetname at %s\n", vtos(self->s.origin));
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_TRIGGER;
	self->touch = path_corner_touch;
	VectorSet (self->mins, -8, -8, -8);
	VectorSet (self->maxs, 8, 8, 8);
	self->svflags |= SVF_NOCLIENT;
	gi.linkentity (self);
}

// JOSEPH 8-FEB-99
/*UAKED viewthing (0 .5 .8) (-8 -8 -8) (8 8 8)
Just for the debugging level.  Don't use
*/
// END JOSEPH
void TH_viewthing(edict_t *ent)
{
	ent->s.frame = (ent->s.frame + 1) % 7;
	ent->nextthink = level.time + FRAMETIME;
}

void SP_viewthing(edict_t *ent)
{
	gi.dprintf ("viewthing spawned\n");

	ent->movetype = MOVETYPE_NONE;
	ent->solid = SOLID_BBOX;
	ent->s.renderfx = RF_FRAMELERP;
	VectorSet (ent->mins, -16, -16, -24);
	VectorSet (ent->maxs, 16, 16, 32);
	ent->s.modelindex = gi.modelindex ("models/objects/banner/tris.md2");
	gi.linkentity (ent);
	ent->nextthink = level.time + 0.5;
	ent->think = TH_viewthing;
	return;
}


/*QUAKED info_null (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for spotlights, etc.
*/
void SP_info_null (edict_t *self)
{
	if (!self->targetname)		// Ridah, 5-7-99, had to add this or the info_null behind the radio gets deleted
		G_FreeEdict (self);
};


/*QUAKED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for lightning.
*/
void SP_info_notnull (edict_t *self)
{
	VectorCopy (self->s.origin, self->absmin);
	VectorCopy (self->s.origin, self->absmax);
};


#define	MIN_LIGHT_VALUE		128
#define	MIN_LIGHT_INTENSITY	0.2

#define START_OFF		1
#define FLARE			2
#define DYNAMIC			8


void AddLightSource(edict_t *self)
{
	if (!(self->spawnflags & DYNAMIC))
		return;
	
	if (level.num_light_sources >= MAX_LIGHT_SOURCES)
	{
		gi.dprintf("Warning: MAX_LIGHT_SOURCES exceeded\n");
		return;
	}

	if (self->dmg_radius <= 0.0)
		self->dmg_radius = 1.0;

	if (self->light_level < MIN_LIGHT_VALUE)
		self->light_level = MIN_LIGHT_VALUE;

	VectorCopy( self->s.origin, level.light_orgs[level.num_light_sources] );
	VectorCopy( self->rotate, level.light_colors[level.num_light_sources] );
	// light_values[num_light_sources] = ((float) self->light_level) * 3.0;
	level.light_values[level.num_light_sources] = ((float) self->light_level * 1.5);
	// level.light_radius[level.num_light_sources] = self->dmg_radius;
	level.light_styles[level.num_light_sources] = self->style;

	level.num_light_sources++;

	self->svflags |= SVF_NOCLIENT;
}

void LightConfigstrings ()
{
	char	str[256];
	char	fullstr[256];
	int		i, inc, j;

	fullstr[0] = str[0] = '\0';
	inc = 0;
	j = 0;

	for (i=0; i<level.num_light_sources; i++)
	{

		sprintf( str, 
			"%5i %5i %5i %1.1f %1.1f %1.1f %4i %3i",		// "99999 99999 99999 9.9 9.9 9.9 9999 999"
			(int)level.light_orgs[i][0], (int)level.light_orgs[i][1], (int)level.light_orgs[i][2],
			level.light_colors[i][0], level.light_colors[i][1], level.light_colors[i][2],
			(int)level.light_values[i],
			(int)level.light_styles[i]);

		strcat( fullstr, str );

//		if (inc++)
		{
			gi.configstring (CS_JUNIORS + j++, fullstr );

			fullstr[0] = '\0';
			inc = 0;
		}
//		else	// add the seperator
//		{
//			strcat( fullstr, " : " );
//		}
	}

	i -= 1;

	if (inc)
		gi.configstring (CS_JUNIORS + (int)floor(i/2), fullstr );
}

void UpdateDirLights( edict_t *self )
{
	int	i, ent_lights=0;
	vec3_t	vec;
	int j;


	for (i=0; i<level.num_light_sources; i++)
	{
		
		VectorSubtract( level.light_orgs[i], self->s.origin, vec );

// trivia reject 

		// lights less that 100 are rejected by default done in sp_light

		{
			float length;

			length = VectorLength (vec);

			if (((level.light_values[i]) - length) < 0)
				continue;
		}

		if (!gi.inPVS(self->s.origin, level.light_orgs[i]))
			continue;

		{
			vec3_t	spot1;
			vec3_t	spot2;
			trace_t	trace;

			VectorCopy (self->s.origin, spot1);
			spot1[2] += self->viewheight;
			VectorCopy (level.light_orgs[i], spot2);
			trace = gi.trace (spot1, vec3_origin, vec3_origin, spot2, self, MASK_OPAQUE);
			
			if (trace.fraction != 1.0)
				continue;
		}

// passed normal tests. if we've used all lights, look for one to replace

		if (ent_lights >= MAX_MODEL_DIR_LIGHTS)
		{
			for (j=0; j<MAX_MODEL_DIR_LIGHTS; j++)
			{
				if (	(self->s.model_lighting.light_intensities[j] - VectorDistance( self->s.origin, self->s.model_lighting.light_orgs[j] ))
					<	(level.light_values[i] - VectorDistance( self->s.origin, level.light_orgs[i] )))
				{
					break;	// replace this light
				}
			}

			if (j == MAX_MODEL_DIR_LIGHTS)
				continue;		// no light to replace
		}
		else
		{
			j = ent_lights;
		}

// end reject test

		self->s.model_lighting.light_indexes[j] = i;

		self->s.model_lighting.light_intensities[j] = level.light_values[i];
		VectorCopy( level.light_colors[i], self->s.model_lighting.light_colors[j] );
		VectorCopy( level.light_orgs[i], self->s.model_lighting.light_orgs[j] );
		VectorNormalize( vec );
		VectorCopy( vec, self->s.model_lighting.light_vecs[j] );
		self->s.model_lighting.light_styles[j] = level.light_styles[i];

		if (showlights->value)
			NAV_DrawLine( self->s.origin, level.light_orgs[i] );

		if (ent_lights < MAX_MODEL_DIR_LIGHTS)
			ent_lights++;

	}

	if (showlights->value)
		gi.dprintf ("num lights %d\n", ent_lights);

	self->s.model_lighting.num_dir_lights = ent_lights;
}

/*QUAKED junior (0 1 0) (-8 -8 -8) (8 8 8) START_OFF
*/

static void junior_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (self->spawnflags & START_OFF)
	{
		gi.configstring (CS_LIGHTS+self->style, "m");
		self->spawnflags &= ~START_OFF;
	}
	else
	{
		gi.configstring (CS_LIGHTS+self->style, "a");
		self->spawnflags |= START_OFF;
	}
}

void SP_junior (edict_t *self )
{
	if (self->style >= 32)
	{
		self->use = junior_use;
		if (self->spawnflags & START_OFF)
			gi.configstring (CS_LIGHTS+self->style, "a");
		else
			gi.configstring (CS_LIGHTS+self->style, "m");
	}
	
	self->spawnflags |= DYNAMIC;
	
	if (!(self->light_level))
		self->light_level = 300;
	
	AddLightSource(self);

}


// -----------------------------------------------------------------------------

/*QUAKED lightflare (0 1 0) (-2 -2 -2) (2 2 2) START_OFF FLARE  NORESIZE DYNAMIC
Non-displayed light.
Default light value is 300.
Default style is 0.
If targeted, will toggle between on and off.
Default _cone value is 10 (used to set size of light for spotlights)
movedir will be the color of the flare
health is size for lightflare
dmg will specify the flare type
FLARE_NORMAL    0
FLARE_SUN		1
FLARE_AMBER		2
FLARE_RED		3
FLARE_BLUE		4
FLARE_GREEN		5
*/

/*QUAKED light (0 1 0) (-8 -8 -8) (8 8 8) START_OFF FLARE NORESIZE DYNAMIC
Non-displayed light.
Default light value is 300.
Default style is 0.
If targeted, will toggle between on and off.
Default _cone value is 10 (used to set size of light for spotlights)
movedir will be the color of the flare
health is size for lightflare
dmg will specify the flare type
FLARE_NORMAL    0
FLARE_SUN		1
FLARE_AMBER		2
FLARE_RED		3
FLARE_BLUE		4
FLARE_GREEN		5
*/

void SP_Flare (edict_t *self);

static void light_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (self->spawnflags & START_OFF)
	{
		gi.configstring (CS_LIGHTS+self->style, "m");
		self->spawnflags &= ~START_OFF;
	}
	else
	{
		gi.configstring (CS_LIGHTS+self->style, "a");
		self->spawnflags |= START_OFF;
	}
}

void SP_light (edict_t *self)
{
	if (self->style >= 32)
	{
		self->use = light_use;
		if (self->spawnflags & START_OFF)
			gi.configstring (CS_LIGHTS+self->style, "a");
		else
			gi.configstring (CS_LIGHTS+self->style, "m");
	}

	// RAFAEL
	if (self->spawnflags & FLARE)
	{
		SP_Flare (self);
	}
	// flares will never be a level.light_source
	else
	{
		if (!(self->light_level))
			self->light_level = 300;

		if (self->light_level > 100)
			AddLightSource(self);
	}
}

#define RESIZE 2

void SP_Flare (edict_t *self)
{
	lightflare_t	lf;
//	char			lf_str[256], temp_str[256], zero_str[256];//, numstr[2];
//	int				i,j;

	if (num_flares == MAX_LIGHTFLARES-1)
	{
		gi.dprintf("Too many light flares, num_flares == MAX_LIGHTFLARES\n");
		return;
	}

	if (!self->health)	// size
		self->health = 24;

	if (!self->dmg)		// type
		self->dmg = FLARE_NORMAL;

	if (self->dmg > 5)
	{
		gi.dprintf("Not a valid flare color 0,1,2,3,4,5 only\n");
		return;
	}

	lf.lightstyle = (char)self->style;

	if (self->spawnflags & 4)
		lf.lightstyle |= RESIZE;
	
	lf.type = (char) self->dmg;

	lf.size = (float) self->health;

	VectorCopy( self->s.origin, lf.pos );

// NOTE to Rafael this just shows what sort of values are required to define a Sun-Flare
/*
{
	static int done_sun=0;

	if (!done_sun)
	{
		lf.type = FLARE_SUN;					// use self->dmg in editor
		lf.size = 24;

		VectorSet( lf.pos, 1000, 1000, 3000 );	// if the mappers place the sunflare out near the extremes of the map, in the position of the sun, these values will be set accordingly (no need to specify manually)
		done_sun = true;
	}
}
*/

	if (lf.type == FLARE_SUN)
		VectorNormalize( lf.pos );

	// just send it as a formatted string
	{
		char	str[256];

		sprintf( str, 
			"%3i %1i %4.1f %4.1f %4.1f %3.0f",		// "999 9 9999.9 9999.9 9999.9 999" length = 30
			(int)lf.lightstyle,
			(int)lf.type,
			lf.pos[0], lf.pos[1], lf.pos[2],
			lf.size );

		gi.configstring (CS_LIGHTFLARES + num_flares, str );

		num_flares++;

//gi.dprintf( "game flares: %i\n", num_flares );
	}

}

// JOSEPH 12-MAY-99-B
#define LIGHTB	16
#define LIGHTG	32
#define LIGHTR	64
#define LIGHTY	128

/*QUAKED light_sconce (1 1 1) (-4 -4 -8) (4 4 8) START_OFF FLARE NORESIZE DYNAMIC LIGHTB LIGHTG LIGHTR LIGHTY

A sconce??

Non-displayed light.
Default light value is 300.
Default style is 0.
If targeted, will toggle between on and off.
Default _cone value is 10 (used to set size of light for spotlights)
movedir will be the color of the flare
health is size for lightflare
dmg will specify the flare type
FLARE_NORMAL    0
FLARE_SUN		1
FLARE_AMBER		2
FLARE_RED		3
FLARE_BLUE		4
FLARE_GREEN		5
  
model="models\props\sconce\light.md2"
*/

void SP_light_sconce (edict_t *self)
{
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (self->style >= 32)
	{
		self->use = light_use;
		if (self->spawnflags & START_OFF)
			gi.configstring (CS_LIGHTS+self->style, "a");
		else
			gi.configstring (CS_LIGHTS+self->style, "m");
	}

	if (self->spawnflags & FLARE)
	{
		SP_Flare (self);
	}
	// flares will never be a level.light_source
	else
	{
		if (!(self->light_level))
			self->light_level = 300;

		if (self->light_level > 100)
			AddLightSource(self);
	}

	if (self->spawnflags & LIGHTB)
	{
		self->model = "models/props/sconce/lightb.md2";
	}
	else if (self->spawnflags & LIGHTG)
	{
		self->model = "models/props/sconce/lightg.md2";
	}
	else if (self->spawnflags & LIGHTR)
	{
		self->model = "models/props/sconce/lightr.md2";
	}
	else if (self->spawnflags & LIGHTY)
	{
		self->model = "models/props/sconce/lighty.md2";
	}
	else
	{
		self->model = "models/props/sconce/light.md2";
	}	

	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;

	if ((self->light_level) && (!(self->spawnflags & LIGHTB)))
	{
		self->s.renderfx |= RF_FULLBRIGHT;
		self->flags |= RF_FULLBRIGHT;
	}

 	gi.linkentity (self);
}
// END JOSEPH

// JOSEPH 1-MAR-99
/*QUAKED light_bulb (1 1 1) (-2 -2 -5) (2 2 5) START_OFF FLARE NORESIZE DYNAMIC

A bulb that outputs light

Non-displayed light.
Default light value is 300.
Default style is 0.
If targeted, will toggle between on and off.
Default _cone value is 10 (used to set size of light for spotlights)
movedir will be the color of the flare
health is size for lightflare
dmg will specify the flare type
FLARE_NORMAL    0
FLARE_SUN		1
FLARE_AMBER		2
FLARE_RED		3
FLARE_BLUE		4
FLARE_GREEN		5
*/
// END JOSEPH
void SP_light_bulb (edict_t *self)
{
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (self->style >= 32)
	{
		self->use = light_use;
		if (self->spawnflags & START_OFF)
			gi.configstring (CS_LIGHTS+self->style, "a");
		else
			gi.configstring (CS_LIGHTS+self->style, "m");
	}

	if (self->spawnflags & FLARE)
	{
		SP_Flare (self);
	}
	// flares will never be a level.light_source
	else
	{
		if (!(self->light_level))
			self->light_level = 300;

		if (self->light_level > 100)
			AddLightSource(self);
	}

	self->model = "models/props/light/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;

	if (self->light_level)
	{
		self->s.renderfx |= RF_FULLBRIGHT;
		self->flags |= RF_FULLBRIGHT;
	}

 	gi.linkentity (self);
}
// END JOSEPH

// JOSEPH 16-APR-99
/*QUAKED light_deco_sconce (1 1 1) (-8 -8 -12) (8 8 12) START_OFF FLARE NORESIZE DYNAMIC

A deco sconce

Non-displayed light.
Default light value is 300.
Default style is 0.
If targeted, will toggle between on and off.
Default _cone value is 10 (used to set size of light for spotlights)
movedir will be the color of the flare
health is size for lightflare
dmg will specify the flare type
FLARE_NORMAL    0
FLARE_SUN		1
FLARE_AMBER		2
FLARE_RED		3
FLARE_BLUE		4
FLARE_GREEN		5
  
model="models\props\decosconce\tris.md2"
*/

void SP_light_deco_sconce (edict_t *self)
{
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (self->style >= 32)
	{
		self->use = light_use;
		if (self->spawnflags & START_OFF)
			gi.configstring (CS_LIGHTS+self->style, "a");
		else
			gi.configstring (CS_LIGHTS+self->style, "m");
	}

	if (self->spawnflags & FLARE)
	{
		SP_Flare (self);
	}
	// flares will never be a level.light_source
	else
	{
		if (!(self->light_level))
			self->light_level = 300;

		if (self->light_level > 100)
			AddLightSource(self);
	}

	self->model = "models/props/decosconce/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;

	if (self->light_level)
	{
		self->s.renderfx |= RF_FULLBRIGHT;
		self->flags |= RF_FULLBRIGHT;
	}

 	gi.linkentity (self);
}

// JOSEPH 3-JUN-99
/*QUAKED light_chandelier (1 1 1) (-36 -34 -32) (36 34 32) START_OFF FLARE NORESIZE DYNAMIC

A deco sconce

Non-displayed light.
Default light value is 300.
Default style is 0.
If targeted, will toggle between on and off.
Default _cone value is 10 (used to set size of light for spotlights)
movedir will be the color of the flare
health is size for lightflare
dmg will specify the flare type
FLARE_NORMAL    0
FLARE_SUN		1
FLARE_AMBER		2
FLARE_RED		3
FLARE_BLUE		4
FLARE_GREEN		5
  
model="models\props\chandelier\tris.md2"
*/

void SP_light_chandelier (edict_t *self)
{
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (self->style >= 32)
	{
		self->use = light_use;
		if (self->spawnflags & START_OFF)
			gi.configstring (CS_LIGHTS+self->style, "a");
		else
			gi.configstring (CS_LIGHTS+self->style, "m");
	}

	if (self->spawnflags & FLARE)
	{
		SP_Flare (self);
	}
	// flares will never be a level.light_source
	else
	{
		if (!(self->light_level))
			self->light_level = 300;

		if (self->light_level > 100)
			AddLightSource(self);
	}

	self->model = "models/props/chandelier/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;

	if (self->light_level)
	{
		self->s.renderfx |= RF_FULLBRIGHT;
		self->flags |= RF_FULLBRIGHT;
	}

 	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED light_pendant (1 1 1) (-16 -16 -4) (16 16 4) START_OFF FLARE NORESIZE DYNAMIC

A pendant light

Non-displayed light.
Default light value is 300.
Default style is 0.
If targeted, will toggle between on and off.
Default _cone value is 10 (used to set size of light for spotlights)
movedir will be the color of the flare
health is size for lightflare
dmg will specify the flare type
FLARE_NORMAL    0
FLARE_SUN		1
FLARE_AMBER		2
FLARE_RED		3
FLARE_BLUE		4
FLARE_GREEN		5
  
model="models\props\pendant\tris.md2"
*/

void SP_light_pendant (edict_t *self)
{
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (self->style >= 32)
	{
		self->use = light_use;
		if (self->spawnflags & START_OFF)
			gi.configstring (CS_LIGHTS+self->style, "a");
		else
			gi.configstring (CS_LIGHTS+self->style, "m");
	}

	if (self->spawnflags & FLARE)
	{
		SP_Flare (self);
	}
	// flares will never be a level.light_source
	else
	{
		if (!(self->light_level))
			self->light_level = 300;

		if (self->light_level > 100)
			AddLightSource(self);
	}

	self->model = "models/props/pendant/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;

	if (self->light_level)
	{
		self->s.renderfx |= RF_FULLBRIGHT;
		self->flags |= RF_FULLBRIGHT;
	}

 	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED func_wall (0 .5 .8) ? TRIGGER_SPAWN TOGGLE START_ON ANIMATED ANIMATED_FAST SURF2_ALPHA
This is just a solid wall if not inhibited

TRIGGER_SPAWN	the wall will not be present until triggered
				it will then blink in to existance; it will
				kill anything that was in it's way

TOGGLE			only valid for TRIGGER_SPAWN walls
				this allows the wall to be turned on and off

START_ON		only valid for TRIGGER_SPAWN walls
				the wall will initially be present
*/

void func_wall_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (self->solid == SOLID_NOT)
	{
		self->solid = SOLID_BSP;
		self->svflags &= ~SVF_NOCLIENT;
		KillBox (self);
	}
	else
	{
		self->solid = SOLID_NOT;
		self->svflags |= SVF_NOCLIENT;
	}
	gi.linkentity (self);

	if (!(self->spawnflags & 2))
		self->use = NULL;
}

void SP_func_wall (edict_t *self)
{
	self->movetype = MOVETYPE_PUSH;
	gi.setmodel (self, self->model);

	if (self->spawnflags & 8)
		self->s.effects |= EF_ANIM_ALL;
	if (self->spawnflags & 16)
		self->s.effects |= EF_ANIM_ALLFAST;

	// RAFAEL
	if (self->spawnflags & 32)
		self->s.renderfx2 |= RF2_SURF_ALPHA;

	// just a wall
	if ((self->spawnflags & 7) == 0)
	{
		self->solid = SOLID_BSP;
		gi.linkentity (self);
		return;
	}

	// it must be TRIGGER_SPAWN
	if (!(self->spawnflags & 1))
	{
//		gi.dprintf("func_wall missing TRIGGER_SPAWN\n");
		self->spawnflags |= 1;
	}

	// yell if the spawnflags are odd
	if (self->spawnflags & 4)
	{
		if (!(self->spawnflags & 2))
		{
			gi.dprintf("func_wall START_ON without TOGGLE\n");
			self->spawnflags |= 2;
		}
	}

	self->use = func_wall_use;
	if (self->spawnflags & 4)
	{
		self->solid = SOLID_BSP;
	}
	else
	{
		self->solid = SOLID_NOT;
		self->svflags |= SVF_NOCLIENT;
	}
		
	gi.linkentity (self);
}


/*QUAKED func_object (0 .5 .8) ? TRIGGER_SPAWN ANIMATED ANIMATED_FAST
This is solid bmodel that will fall if it's support it removed.
*/

void func_object_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	// only squash thing we fall on top of
	if (!plane)
		return;
	if (plane->normal[2] < 1.0)
		return;
	if (other->takedamage == DAMAGE_NO)
		return;
	T_Damage (other, self, self, vec3_origin, self->s.origin, vec3_origin, self->dmg, 1, 0, MOD_CRUSH);
}

void func_object_release (edict_t *self)
{
	self->movetype = MOVETYPE_TOSS;
	self->touch = func_object_touch;
}

void func_object_use (edict_t *self, edict_t *other, edict_t *activator)
{
	self->solid = SOLID_BSP;
	self->svflags &= ~SVF_NOCLIENT;
	self->use = NULL;
	KillBox (self);
	func_object_release (self);
}

void SP_func_object (edict_t *self)
{
	gi.setmodel (self, self->model);

	self->mins[0] += 1;
	self->mins[1] += 1;
	self->mins[2] += 1;
	self->maxs[0] -= 1;
	self->maxs[1] -= 1;
	self->maxs[2] -= 1;

	if (!self->dmg)
		self->dmg = 100;

	if (self->spawnflags == 0)
	{
		self->solid = SOLID_BSP;
		self->movetype = MOVETYPE_PUSH;
		self->think = func_object_release;
		self->nextthink = level.time + 2 * FRAMETIME;
	}
	else
	{
		self->solid = SOLID_NOT;
		self->movetype = MOVETYPE_PUSH;
		self->use = func_object_use;
		self->svflags |= SVF_NOCLIENT;
	}

	if (self->spawnflags & 2)
		self->s.effects |= EF_ANIM_ALL;
	if (self->spawnflags & 4)
		self->s.effects |= EF_ANIM_ALLFAST;

	self->clipmask = MASK_MONSTERSOLID;

	gi.linkentity (self);
}

// JOSEPH 18-FEB-99
/*QUAKED func_explosive (0 .5 .8) ? Trigger_Spawn ANIMATED ANIMATED_FAST SURF2_ALPHA
Any brush that you want to explode or break apart.  If you want an
explosion, set dmg and it will do a radius explosion of that amount
at the center of the bursh.

If targeted it will not be shootable.

health defaults to 100.

type - type of debris ("glass", "wood" or "metal")
 type default is "glass"

mass defaults to 75.  This determines how much debris is emitted when
it explodes.  You get one large chunk per 100 of mass (up to 8) and
one small chunk per 25 of mass (up to 16).  So 800 gives the most.

"dmg"  how much radius damage should be done, defaults to 0

"fxdensity" size of explosion 1 - 100 (default is 10)
*/
// END JOSEPH
void func_explosive_explode (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	vec3_t	origin;
	vec3_t	chunkorigin;
	vec3_t	size;
	int		count;
	int		mass;

	PlayerNoise( attacker, attacker->s.origin, PNOISE_WEAPON );

	// bmodel origins are (0 0 0), we need to adjust that here
	VectorScale (self->size, 0.5, size);
	VectorAdd (self->absmin, size, origin);
	VectorCopy (origin, self->s.origin);

	self->takedamage = DAMAGE_NO;

	if (self->dmg)
		T_RadiusDamage (self, attacker, self->dmg, NULL, self->dmg+40, MOD_EXPLOSIVE);

	VectorSubtract (self->s.origin, inflictor->s.origin, self->velocity);
	VectorNormalize (self->velocity);
	VectorScale (self->velocity, 250, self->velocity);

	// start chunks towards the center
	VectorScale (size, 0.5, size);

	mass = self->mass;
	if (!mass)
		mass = 75;

	// big chunks
	if (mass >= 100)
	{
		count = mass / 100;
		if (count > 8)
			count = 8;
		if ((!self->type) || ((self->type) && (!strcmp(self->type, "glass"))))
		{	
			while(count--)
			{
				chunkorigin[0] = origin[0] + crandom() * size[0];
				chunkorigin[1] = origin[1] + crandom() * size[1];
				chunkorigin[2] = origin[2] + crandom() * size[2];
				ThrowDebris (self, "models/props/glass/glass1.md2", 1, chunkorigin);
			}
		}
		else if (((self->type) && (!strcmp(self->type, "wood"))))
		{	
			while(count--)
			{
				chunkorigin[0] = origin[0] + crandom() * size[0];
				chunkorigin[1] = origin[1] + crandom() * size[1];
				chunkorigin[2] = origin[2] + crandom() * size[2];
				ThrowDebris (self, "models/props/wood/wood1.md2", 1, chunkorigin);
			}
		}
		else if (((self->type) && (!strcmp(self->type, "metal"))))
		{	
			while(count--)
			{
				chunkorigin[0] = origin[0] + crandom() * size[0];
				chunkorigin[1] = origin[1] + crandom() * size[1];
				chunkorigin[2] = origin[2] + crandom() * size[2];
				ThrowDebris (self, "models/props/metal/metal1.md2", 1, chunkorigin);
			}
		}
	}

	// small chunks
	count = mass / 25;
	if (count > 16)
		count = 16;
	if ((!self->type) || ((self->type) && (!strcmp(self->type, "glass"))))
	{		
		while(count--)
		{
			chunkorigin[0] = origin[0] + crandom() * size[0];
			chunkorigin[1] = origin[1] + crandom() * size[1];
			chunkorigin[2] = origin[2] + crandom() * size[2];
			ThrowDebris (self, "models/props/glass/glass2.md2", 2, chunkorigin);
		}
	}	
	else if (((self->type) && (!strcmp(self->type, "wood"))))
	{	
		while(count--)
		{	
			chunkorigin[0] = origin[0] + crandom() * size[0];
			chunkorigin[1] = origin[1] + crandom() * size[1];
			chunkorigin[2] = origin[2] + crandom() * size[2];
			ThrowDebris (self, "models/props/wood/wood2.md2", 2, chunkorigin);		
		}
	}
	else if (((self->type) && (!strcmp(self->type, "metal"))))
	{	
		while(count--)
		{
			chunkorigin[0] = origin[0] + crandom() * size[0];
			chunkorigin[1] = origin[1] + crandom() * size[1];
			chunkorigin[2] = origin[2] + crandom() * size[2];
			ThrowDebris (self, "models/props/metal/metal2.md2", 2, chunkorigin);		
		}
	}


	G_UseTargets (self, attacker);

	if (self->dmg)
		BecomeExplosion1 (self);
	else
		G_FreeEdict (self);
}
// END JOSEPH

void func_explosive_use(edict_t *self, edict_t *other, edict_t *activator)
{
	func_explosive_explode (self, self, other, self->health, vec3_origin, 0, 0);
}

// JOSEPH 7-MAR-99
void func_explosive_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!(other->svflags & SVF_MONSTER))
		return;

	if (!(other->onfiretime > 0))
		return;

	func_explosive_explode (self, self, other, self->health, vec3_origin, 0, 0);
}
// END JOSEPH

void func_explosive_spawn (edict_t *self, edict_t *other, edict_t *activator)
{
	self->solid = SOLID_BSP;
	self->svflags &= ~SVF_NOCLIENT;
	self->use = NULL;
	KillBox (self);
	gi.linkentity (self);
}

void SP_func_explosive (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->movetype = MOVETYPE_PUSH;

	// JOSEPH 10-FEB-99
	if (self->spawnflags & 8)
		self->s.renderfx2 |= RF2_SURF_ALPHA;
	// END JOSEPH

	gi.modelindex ("models/props/glass/glass1.md2");
	gi.modelindex ("models/props/glass/glass2.md2");

	gi.setmodel (self, self->model);

	if (self->spawnflags & 1)
	{
		self->svflags |= SVF_NOCLIENT;
		self->solid = SOLID_NOT;
		self->use = func_explosive_spawn;
	}
	else
	{
		self->solid = SOLID_BSP;
		if (self->targetname)
			self->use = func_explosive_use;
	}

	if (self->spawnflags & 2)
		self->s.effects |= EF_ANIM_ALL;
	if (self->spawnflags & 4)
		self->s.effects |= EF_ANIM_ALLFAST;

	if (self->use != func_explosive_use)
	{
		if (!self->health)
			self->health = 100;
		self->die = func_explosive_explode;
		self->takedamage = DAMAGE_YES;
	}

	// JOSEPH 7-MARCH-99
	self->touch = func_explosive_touch;
	// END JOSEPH

	gi.linkentity (self);
}

// JOSEPH 8-FEB-99
/*UAKED misc_explobox (0 .5 .8) (-16 -16 0) (16 16 40)
Large exploding box.  You can override its mass (100),
health (80), and dmg (150).
*/
// END JOSEPH
void barrel_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)

{
	float	ratio;
	vec3_t	v;

	if ((!other->groundentity) || (other->groundentity == self))
		return;

	ratio = (float)other->mass / (float)self->mass;
	VectorSubtract (self->s.origin, other->s.origin, v);
	M_walkmove (self, vectoyaw(v), 20 * ratio * FRAMETIME);
}

void barrel_explode (edict_t *self)
{
	vec3_t	org;
	float	spd;
	vec3_t	save;

	T_RadiusDamage (self, self->activator, self->dmg, NULL, self->dmg+40, MOD_BARREL);

	VectorCopy (self->s.origin, save);
	VectorMA (self->absmin, 0.5, self->size, self->s.origin);

	// a few big chunks
	spd = 1.5 * (float)self->dmg / 200.0;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass1.md2", spd, org);

	// bottom corners
	spd = 1.75 * (float)self->dmg / 200.0;
	VectorCopy (self->absmin, org);
	ThrowDebris (self, "models/props/glass/glass3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	ThrowDebris (self, "models/props/glass/glass3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/glass/glass3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/glass/glass3.md2", spd, org);

	// a bunch of little chunks
	spd = 2 * self->dmg / 200;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/glass/glass2.md2", spd, org);

	VectorCopy (save, self->s.origin);
	if (self->groundentity)
		BecomeExplosion2 (self);
	else
		BecomeExplosion1 (self);
}

void barrel_delay (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + 2 * FRAMETIME;
	self->think = barrel_explode;
	self->activator = attacker;
}

// JOSEPH 26-AUG-98
// JOSEPH TEMP
void SP_props_trashcanA (edict_t *self);

void SP_misc_explobox (edict_t *self)
{
	// JOSEPH TEMP
    SP_props_trashcanA (self);
	return;

// END JOSEPH	

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	gi.modelindex ("models/props/glass/glass1.md2");
	gi.modelindex ("models/props/glass/glass2.md2");
	gi.modelindex ("models/props/glass/glass3.md2");


	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_STEP;

	self->model = "models/objects/barrels/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -16, -16, 0);
	VectorSet (self->maxs, 16, 16, 40);

	if (!self->mass)
		self->mass = 400;
	if (!self->health)
		self->health = 10;
	if (!self->dmg)
		self->dmg = 150;

	self->die = barrel_delay;
	self->takedamage = DAMAGE_YES;
	self->cast_info.aiflags = AI_NOSTEP;

	self->touch = barrel_touch;

	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	gi.linkentity (self);
}

// JOSEPH 8-FEB-99
/*UAKED light_mine1 (0 1 0) (-2 -2 -12) (2 2 12)
*/
// END JOSEPH
void SP_light_mine1 (edict_t *ent)
{
	ent->movetype = MOVETYPE_NONE;
	ent->solid = SOLID_BBOX;
	ent->s.modelindex = gi.modelindex ("models/objects/minelite/light1/tris.md2");
	gi.linkentity (ent);
}

// JOSEPH 8-FEB-99
/*UAKED light_mine2 (0 1 0) (-2 -2 -12) (2 2 12)
*/
// END JOSEPH
void SP_light_mine2 (edict_t *ent)
{
	ent->movetype = MOVETYPE_NONE;
	ent->solid = SOLID_BBOX;
	ent->s.modelindex = gi.modelindex ("models/objects/minelite/light2/tris.md2");
	gi.linkentity (ent);
}

// JOSEPH 8-FEB-99
/*UAKED misc_gib_arm (1 0 0) (-8 -8 -8) (8 8 8)
Intended for use with the target_spawner
*/
// END JOSEPH
void SP_misc_gib_arm (edict_t *ent)
{
	gi.setmodel (ent, "models/objects/gibs/arm/tris.md2");
	ent->solid = SOLID_NOT;
	ent->s.effects |= EF_GIB;
	ent->takedamage = DAMAGE_YES;
	ent->die = gib_die;
	ent->movetype = MOVETYPE_TOSS;
	ent->svflags |= SVF_MONSTER;
	ent->deadflag = DEAD_DEAD;
	ent->avelocity[0] = random()*200;
	ent->avelocity[1] = random()*200;
	ent->avelocity[2] = random()*200;
	ent->think = G_FreeEdict;
	ent->nextthink = level.time + 30;
	gi.linkentity (ent);
}

// JOSEPH 8-FEB-99 
/*UAKED misc_gib_leg (1 0 0) (-8 -8 -8) (8 8 8)
Intended for use with the target_spawner
*/
// END JOSEPH
void SP_misc_gib_leg (edict_t *ent)
{
	gi.setmodel (ent, "models/objects/gibs/leg/tris.md2");
	ent->solid = SOLID_NOT;
	ent->s.effects |= EF_GIB;
	ent->takedamage = DAMAGE_YES;
	ent->die = gib_die;
	ent->movetype = MOVETYPE_TOSS;
	ent->svflags |= SVF_MONSTER;
	ent->deadflag = DEAD_DEAD;
	ent->avelocity[0] = random()*200;
	ent->avelocity[1] = random()*200;
	ent->avelocity[2] = random()*200;
	ent->think = G_FreeEdict;
	ent->nextthink = level.time + 30;
	gi.linkentity (ent);
}

// JOSEPH 8-FEB-99
/*UAKED misc_gib_head (1 0 0) (-8 -8 -8) (8 8 8)
Intended for use with the target_spawner
*/
// END JOSEPH
void SP_misc_gib_head (edict_t *ent)
{
	gi.setmodel (ent, "models/objects/gibs/head/tris.md2");
	ent->solid = SOLID_NOT;
	ent->s.effects |= EF_GIB;
	ent->takedamage = DAMAGE_YES;
	ent->die = gib_die;
	ent->movetype = MOVETYPE_TOSS;
	ent->svflags |= SVF_MONSTER;
	ent->deadflag = DEAD_DEAD;
	ent->avelocity[0] = random()*200;
	ent->avelocity[1] = random()*200;
	ent->avelocity[2] = random()*200;
	ent->think = G_FreeEdict;
	ent->nextthink = level.time + 30;
	gi.linkentity (ent);
}

//=====================================================

/*QUAKED target_character (0 0 1) ?
used with target_string (must be on same "team")
"count" is position in the string (starts at 1)
*/

void SP_target_character (edict_t *self)
{
	self->movetype = MOVETYPE_PUSH;
	gi.setmodel (self, self->model);
	self->solid = SOLID_BSP;
	self->s.frame = 12;
	gi.linkentity (self);
	return;
}


/*QUAKED target_string (0 0 1) (-8 -8 -8) (8 8 8)
*/

void target_string_use (edict_t *self, edict_t *other, edict_t *activator)
{
	edict_t *e;
	int		n, l;
	char	c;

	l = strlen(self->message);
	for (e = self->teammaster; e; e = e->teamchain)
	{
		if (!e->count)
			continue;
		n = e->count - 1;
		if (n > l)
		{
			e->s.frame = 12;
			continue;
		}

		c = self->message[n];
		if (c >= '0' && c <= '9')
			e->s.frame = c - '0';
		else if (c == '-')
			e->s.frame = 10;
		else if (c == ':')
			e->s.frame = 11;
		else
			e->s.frame = 12;
	}
}

void SP_target_string (edict_t *self)
{
	if (!self->message)
		self->message = "";
	self->use = target_string_use;
}


/*QUAKED func_clock (0 0 1) (-8 -8 -8) (8 8 8) TIMER_UP TIMER_DOWN START_OFF MULTI_USE
target a target_string with this

The default is to be a time of day clock

TIMER_UP and TIMER_DOWN run for "count" seconds and the fire "pathtarget"
If START_OFF, this entity must be used before it starts

"style"		0 "xx"
			1 "xx:xx"
			2 "xx:xx:xx"
*/

#define	CLOCK_MESSAGE_SIZE	16

// don't let field width of any clock messages change, or it
// could cause an overwrite after a game load

static void func_clock_reset (edict_t *self)
{
	self->activator = NULL;
	if (self->spawnflags & 1)
	{
		self->health = 0;
		self->wait = self->count;
	}
	else if (self->spawnflags & 2)
	{
		self->health = self->count;
		self->wait = 0;
	}
}

static void func_clock_format_countdown (edict_t *self)
{
	if (self->style == 0)
	{
		Com_sprintf (self->message, CLOCK_MESSAGE_SIZE, "%2i", self->health);
		return;
	}

	if (self->style == 1)
	{
		Com_sprintf(self->message, CLOCK_MESSAGE_SIZE, "%2i:%2i", self->health / 60, self->health % 60);
		if (self->message[3] == ' ')
			self->message[3] = '0';
		return;
	}

	if (self->style == 2)
	{
		Com_sprintf(self->message, CLOCK_MESSAGE_SIZE, "%2i:%2i:%2i", self->health / 3600, (self->health - (self->health / 3600) * 3600) / 60, self->health % 60);
		if (self->message[3] == ' ')
			self->message[3] = '0';
		if (self->message[6] == ' ')
			self->message[6] = '0';
		return;
	}
}

void func_clock_think (edict_t *self)
{
	if (!self->enemy)
	{
		self->enemy = G_Find (NULL, FOFS(targetname), self->target);
		if (!self->enemy)
			return;
	}

	if (self->spawnflags & 1)
	{
		func_clock_format_countdown (self);
		self->health++;
	}
	else if (self->spawnflags & 2)
	{
		func_clock_format_countdown (self);
		self->health--;
	}
	else
	{
		struct tm	*ltime;
		time_t		gmtime;

		time(&gmtime);
		ltime = localtime(&gmtime);
		Com_sprintf (self->message, CLOCK_MESSAGE_SIZE, "%2i:%2i:%2i", ltime->tm_hour, ltime->tm_min, ltime->tm_sec);
		if (self->message[3] == ' ')
			self->message[3] = '0';
		if (self->message[6] == ' ')
			self->message[6] = '0';
	}

	self->enemy->message = self->message;
	self->enemy->use (self->enemy, self, self);

	if (((self->spawnflags & 1) && (self->health > self->wait)) ||
		((self->spawnflags & 2) && (self->health < self->wait)))
	{
		if (self->pathtarget)
		{
			char *savetarget;
			char *savemessage;

			savetarget = self->target;
			savemessage = self->message;
			self->target = self->pathtarget;
			self->message = NULL;
			G_UseTargets (self, self->activator);
			self->target = savetarget;
			self->message = savemessage;
		}

		if (!(self->spawnflags & 8))
			return;

		func_clock_reset (self);

		if (self->spawnflags & 4)
			return;
	}

	self->nextthink = level.time + 1;
}

void func_clock_use (edict_t *self, edict_t *other, edict_t *activator)
{
	if (!(self->spawnflags & 8))
		self->use = NULL;
	if (self->activator)
		return;
	self->activator = activator;
	self->think (self);
}

void SP_func_clock (edict_t *self)
{
	if (!self->target)
	{
		gi.dprintf("%s with no target at %s\n", self->classname, vtos(self->s.origin));
		G_FreeEdict (self);
		return;
	}

	if ((self->spawnflags & 2) && (!self->count))
	{
		gi.dprintf("%s with no count at %s\n", self->classname, vtos(self->s.origin));
		G_FreeEdict (self);
		return;
	}

	if ((self->spawnflags & 1) && (!self->count))
		self->count = 60*60;;

	func_clock_reset (self);

	self->message = gi.TagMalloc (CLOCK_MESSAGE_SIZE, TAG_LEVEL);

	self->think = func_clock_think;

	if (self->spawnflags & 4)
		self->use = func_clock_use;
	else
		self->nextthink = level.time + 1;
}

//=================================================================================

void teleporter_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	edict_t		*dest;
	int			i;

	if (!(other->client))
		return;
	dest = G_Find (NULL, FOFS(targetname), self->target);
	if (!dest)
	{
		gi.dprintf ("Couldn't find destination\n");
		return;
	}

	// unlink to make sure it can't possibly interfere with KillBox
	gi.unlinkentity (other);

	VectorCopy (dest->s.origin, other->s.origin);
	VectorCopy (dest->s.origin, other->s.old_origin);
	other->s.origin[2] += 10;

	// clear the velocity and hold them in place briefly
	VectorClear (other->velocity);
	other->client->ps.pmove.pm_time = 160>>3;		// hold time
	other->client->ps.pmove.pm_flags |= PMF_TIME_TELEPORT;

	// draw the teleport splash at source and on the player
	self->owner->s.event = EV_PLAYER_TELEPORT;
	other->s.event = EV_PLAYER_TELEPORT;

	// set angles
	for (i=0 ; i<3 ; i++)
		other->client->ps.pmove.delta_angles[i] = ANGLE2SHORT(dest->s.angles[i] - other->client->resp.cmd_angles[i]);

	VectorClear (other->s.angles);
	VectorClear (other->client->ps.viewangles);
	VectorClear (other->client->v_angle);

	// kill anything at the destination
	KillBox (other);

	gi.linkentity (other);
}

/*QUAKED misc_teleporter (1 0 0) (-32 -32 -24) (32 32 -16)
Stepping onto this disc will teleport players to the targeted misc_teleporter_dest object.
*/
void SP_misc_teleporter (edict_t *ent)
{
	edict_t		*trig;

	if (!ent->target)
	{
		gi.dprintf ("teleporter without a target.\n");
		G_FreeEdict (ent);
		return;
	}

	gi.setmodel (ent, "models/objects/dmspot/tris.md2");
	ent->s.skinnum = 1;
	ent->s.effects = EF_TELEPORTER;
	ent->s.sound = gi.soundindex ("world/amb10.wav");
	ent->solid = SOLID_BBOX;

	VectorSet (ent->mins, -32, -32, -24);
	VectorSet (ent->maxs, 32, 32, -16);
	gi.linkentity (ent);

	trig = G_Spawn ();
	trig->touch = teleporter_touch;
	trig->solid = SOLID_TRIGGER;
	trig->target = ent->target;
	trig->owner = ent;
	VectorCopy (ent->s.origin, trig->s.origin);
	VectorSet (trig->mins, -8, -8, 8);
	VectorSet (trig->maxs, 8, 8, 24);
	gi.linkentity (trig);
	
}

/*QUAKED misc_teleporter_dest (1 0 0) (-32 -32 -24) (32 32 -16)
Point teleporters at these.
*/
void SP_misc_teleporter_dest (edict_t *ent)
{
	gi.setmodel (ent, "models/objects/dmspot/tris.md2");
	ent->s.skinnum = 0;
	ent->solid = SOLID_BBOX;
//	ent->s.effects |= EF_FLIES;
	VectorSet (ent->mins, -32, -32, -24);
	VectorSet (ent->maxs, 32, 32, -16);
	gi.linkentity (ent);
}

// JOSEPH 8-FEB-99
/*UAKED misc_amb4 (1 0 0) (-16 -16 -16) (16 16 16)
Mal's amb4 loop entity
*/
// END JOSEPH
static int amb4sound;

void amb4_think (edict_t *ent)
{
	ent->nextthink = level.time + 2.7;
	gi.sound(ent, CHAN_VOICE, amb4sound, 1, ATTN_NONE, 0);
}

void SP_misc_amb4 (edict_t *ent)
{
	ent->think = amb4_think;
	ent->nextthink = level.time + 1;
	amb4sound = gi.soundindex ("world/amb4.wav");
	gi.linkentity (ent);
}

// JOSEPH 8-FEB-99
/*UAKED misc_smoke (1 0 0) (-16 -16 -64) (16 16 64) ALPHA1 ALPHA2 ALPHA4 ALPHA6 ALPHA8 SCALE50 
ALPHA1 = 0.1
ALPHA8 = 0.8
SCALE 50 will scale it down 50 percent
*/
// END JOSEPH
void SP_misc_smoke (edict_t *ent)
{
	ent->s.modelindex = gi.modelindex ("sprites/s_smoke4.sp2");
	
	ent->s.effects |= EF_ANIM_ALLFAST;
	
	ent->s.renderfx |= RF_FACINGUP|RF_TRANSLUCENT;
	ent->s.renderfx2 |= ent->spawnflags;

	ent->movetype = MOVETYPE_NONE;
	//ent->solid = SOLID_BBOX;
	
	gi.linkentity (ent);
	
}


// Test vehicle models

void dodgeviper_think( edict_t *self)
{
if ((self->s.angles[1] += 8) > 360)
self->s.angles[1] -= 360;

	self->nextthink = level.time + 0.1;
}

void SP_misc_car (edict_t *self)
{
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 32);

// temp for E3 demo, KP2 has characters in the ground
while (!ValidBoxAtLoc(self->s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID))
{
self->s.origin[2] += 16;
gi.linkentity (self);
}

	self->s.modelindex = gi.modelindex("models/vehicles/cars/viper/tris.md2");

	self->s.renderfx |= RF_REFL_MAP;

	self->think = dodgeviper_think;
	self->nextthink = level.time + 0.1;
}

// JOSEPH 8-FEB-99
/*UAKED cast_punk_window (1 0 0) (-16 -16 -16) (16 16 16)
*/
// END JOSEPH
static int windowsound;

void usewindow (edict_t *ent, edict_t *other, edict_t *activator)
{
//	ent->use = NULL;
	gi.sound(ent, CHAN_VOICE, windowsound , 1, ATTN_NONE, 0);
}

void thinkdeadwindow (edict_t *ent)
{
	ent->s.frame++;
	if (ent->s.frame < 336)
		ent->nextthink = level.time + 0.1;	
}

void window_die (edict_t *ent, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	ent->takedamage = DAMAGE_NO;
	ent->nextthink = level.time + FRAMETIME;
	ent->think = thinkdeadwindow;
	ent->activator = attacker;
	ent->s.frame = 322;
}

void thinkwindow (edict_t *ent)
{
	ent->nextthink = level.time + 0.1;
	ent->s.frame++;
	if (ent->s.frame > 211)
		ent->s.frame = 0;
}

void SP_cast_punk_window (edict_t *ent)
{
	ent->s.modelindex = gi.modelindex ("models/actors/fidelC/tris.md2");
	ent->movetype =  MOVETYPE_STEP;
	ent->solid = SOLID_BBOX;
	gi.linkentity (ent);

	ent->takedamage = DAMAGE_YES;
	// ent->cast_info.aiflags = AI_NOSTEP;

	ent->health = 1;
	ent->use = usewindow;
	ent->think = thinkwindow;
	ent->nextthink = level.time + 0.1;

	windowsound = gi.soundindex ("actors/specific/spec3.wav");
	
	VectorSet (ent->mins, -16, -16, 0);
	VectorSet (ent->maxs, 16, 16, 40);

	ent->die = window_die;

}

/*QUAKED refl (1 0 0) (-16 -16 -16) (16 16 16)
*/

void SP_refl (edict_t *ent)
{
	ent->s.modelindex = gi.modelindex ("models/vehicles/cars/viper/tris.md2");
	
	ent->s.renderfx |= RF_REFL_MAP;

	ent->movetype = MOVETYPE_NONE;
	
	gi.linkentity (ent);
}


/*QUAKED elps (1 0 0) (-32 -32 -32) (32 32 32)
test entity for mdx bbox hit test
*/

void elpsthink (edict_t *self)
{
	self->nextthink = level.time + 0.1;
	self->s.angles[YAW] += 3.0;
	self->health = 1000;
}

void SP_elps (edict_t *self)
{
	int i;
	
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/elps_seg/up.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/elps_seg/up.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/elps_seg/rt.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/elps_seg/rt.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/elps_seg/fwd.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/elps_seg/fwd.mdx", &self->s.model_parts[PART_BODY] );

	self->s.num_parts++;
	self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/elps_seg/diag.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_GUN].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/elps_seg/diag.mdx", &self->s.model_parts[PART_GUN] );
	
	self->movetype =  MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	gi.linkentity (self);

	self->takedamage = DAMAGE_YES;
	
	self->health = 1000;
	self->think = elpsthink;
	self->nextthink = level.time + 0.1;

	VectorSet (self->mins, -64, -64, -64);
	VectorSet (self->maxs, 64, 64, 64);
	
}


/*QUAKED misc_caustic (1 0 0) (-16 -16 -64) (16 16 64) ALPHA1 ALPHA2 ALPHA4 ALPHA6 ALPHA8
ALPHA1 = 0.1
ALPHA8 = 0.8
*/
// Ridah, not used, removed RF2_CAUSTIC flag
/*
void SP_misc_caustic (edict_t *ent)
{
	ent->s.modelindex = gi.modelindex ("sprites/s_smoke4.sp2");
	
	ent->s.renderfx |= RF_TRANSLUCENT;
	ent->s.renderfx2 |= ent->spawnflags;
	ent->s.renderfx2 |= RF2_CAUSTIC;

	ent->movetype = MOVETYPE_NONE;
	
	gi.linkentity (ent);
	
}
*/
/*QUAKED misc_rosie (1 .5 0) (-16 -16 -24) (16 16 32)
*/

void rosie_think (edict_t *self)
{

	self->nextthink = level.time + 0.1;
	self->s.frame ++;

	if (self->s.frame > 390)
		self->s.frame = 0;
}

void SP_misc_rosie (edict_t *self)
{
	int i;

//self->s.origin[2] += 1;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/rosie_seg/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/rosie_seg/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/rosie_seg/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/rosie_seg/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/rosie_seg/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/rosie_seg/body.mdx", &self->s.model_parts[PART_BODY] );

	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	gi.linkentity (self);

	self->think = rosie_think;
	self->nextthink = level.time + 0.1;

}


/*QUAKED misc_fidelA (1 .5 0) (-16 -16 -24) (16 16 32)
*/

void fidelA_think (edict_t *self)
{
//return;
	self->nextthink = level.time + 0.1;
	self->s.frame ++;

	if (self->s.frame > 54)
		self->s.frame = 0;


	gi.dprintf ("frame: %d\n", self->s.frame);
}

void SP_misc_fidelA (edict_t *self)
{
	int i;
//return;
//self->s.origin[2] += 1;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/fidel_mdx/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_mdx/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/fidel_mdx/lower_body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_mdx/lower_body.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/fidel_mdx/upper_body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_mdx/upper_body.mdx", &self->s.model_parts[PART_BODY] );

	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	gi.linkentity (self);

	self->think = fidelA_think;
	self->nextthink = level.time + 0.1;

}


#define ALARM_ON	1
#define ALARM_OFF	2

void Think_Alarm (edict_t *ent)
{
	if (ent->wait < 0)
	{
		// just ring once
		/*
		if (ent->delay)
		{
			ent->delay --;
			ent->wait = ent->count;
		}
		else
		*/
			return;
	}

	gi.sound (ent, CHAN_VOICE, gi.soundindex ("world/alarm.wav"), 1, ATTN_NORM, 0);			
	ent->nextthink = level.time + 4.8;
	ent->wait -= 4.8; 
}

void Use_Alarm (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->nextthink = level.time + 3;
	ent->think = Think_Alarm;

	if (ent->moveinfo.state == ALARM_OFF)
	{
//		gi.dprintf ("turning alarm on\n");
		ent->moveinfo.state = ALARM_ON;
		ent->wait = ent->count;
		ent->delay = ent->speed;

		// Ridah, do some special handling here
		EP_EventScript( activator, "alarm" );
	}
	else
	{
//		gi.dprintf ("turning alarm off\n");
		ent->moveinfo.state = ALARM_OFF;
		ent->wait = -1;
		ent->delay = ent->speed;
	}
}

/*QUAKED misc_alarm (1 .5 0) (-8 -8 -8) (8 8 8) 
must be triggered to work
count is the duration of the alarm ringing default is 60 sec
*/
void SP_misc_alarm (edict_t *ent)
{
	ent->use = Use_Alarm;
	
	if (!(ent->count))
		ent->count = 60;

	if (!ent->speed || ent->speed < 0)
		ent->delay = ent->speed = 3;

	ent->moveinfo.state = ALARM_OFF;

	// Ridah, NAV code only understands func_button's
	ent->classname = "func_button";
	ent->name = "misc_alarm";
}






/*QUAKED misc_corky_rosie_mdx (0 0 1) (-16 -16 -24) (16 16 34)
*/

void SP_misc_corky_rosie_mdx (edict_t *self)
{

	int i;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bitch/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/bitch/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/bitch/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/body.mdx", &self->s.model_parts[PART_BODY] );

	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	gi.linkentity (self);
	
}


/*QUAKED misc_corky_fatguy_mdx (0 0 1) (-16 -16 -24) (16 16 34)
*/

void SP_misc_corky_fatguy_mdx (edict_t *self)
{

	int i;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/fatguy_mdx/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fatguy_mdx/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/fatguy_mdx/lower_body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fatguy_mdx/lower_body.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/fatguy_mdx/upper_body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fatguy_mdx/upper_body.mdx", &self->s.model_parts[PART_BODY] );

	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	gi.linkentity (self);
	
}


/*QUAKED misc_corky_fidel_mdx_pcx (0 0 1) (-16 -16 -24) (16 16 34)
*/
/*QUAKED misc_corky_fidel_mdx_tga (0 0 1) (-16 -16 -24) (16 16 34)
*/

void SP_misc_corky_fidel_mdx_tga (edict_t *self)
{
	int i;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/fidel_tga/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_tga/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/fidel_tga/lower_body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_tga/lower_body.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/fidel_tga/upper_body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_tga/upper_body.mdx", &self->s.model_parts[PART_BODY] );

	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	gi.linkentity (self);
	
}

void SP_misc_corky_fidel_mdx_pcx (edict_t *self)
{
	int i;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/thug/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/thug/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/thug/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/thug/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/thug/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/thug/body.mdx", &self->s.model_parts[PART_BODY] );

	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	gi.linkentity (self);
	

}

/*QUAKED misc_barry_fidelc_maya (0 0 1) (-16 -16 -24) (16 16 34)
*/
/*QUAKED misc_barry_bitch (0 0 1) (-16 -16 -24) (16 16 34)
*/

void misc_barry_fidelc_maya_think (edict_t *self)
{
	self->s.frame++;
	self->nextthink = level.time + 0.1;

	if (self->s.frame >= 761)
		self->s.frame = 0;

	gi.dprintf ("frame: %d\n", self->s.frame);
}

void SP_misc_barry_fidelc_maya (edict_t *self)
{
	int i;	

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bitch/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].baseskin = self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/bitch/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].baseskin = self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/bitch/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].baseskin = self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/body.mdx", &self->s.model_parts[PART_BODY] );

/*
	int i;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bitch/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/bitch/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/bitch/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/body.mdx", &self->s.model_parts[PART_BODY] );

	self->s.num_parts++;
	self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/bitch/gun.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bitch/gun.mdx", &self->s.model_parts[PART_GUN] );
*/
/*
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/fidel_seg/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].baseskin = self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_seg/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/fidel_seg/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].baseskin = self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_seg/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/fidel_seg/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].baseskin = self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_seg/body.mdx", &self->s.model_parts[PART_BODY] );

	self->s.num_parts++;
	self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/fidel_seg/gun.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/fidel_seg/gun.mdx", &self->s.model_parts[PART_GUN] );
*/
	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->think = misc_barry_fidelc_maya_think;
	self->nextthink = level.time + 0.1;
	gi.linkentity (self);
	
}

/*QUAKED misc_barry_cube_mdx (0 0 1) (-16 -16 -24) (16 16 34)
*/

void misc_barry_cube_mdx_think (edict_t *self)
{
	self->s.frame++;
	self->nextthink = level.time + 0.1;
	if (self->s.frame >= 20)
		self->s.frame = 0;
}

void SP_misc_barry_cube_mdx (edict_t *self)
{

	int i;

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/cube_mdx/cube.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/cube_mdx/cube.mdx", &self->s.model_parts[PART_HEAD] );

	self->movetype = MOVETYPE_NONE;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->think = misc_barry_cube_mdx_think;
	self->nextthink = level.time + 0.1;
	gi.linkentity (self);

}


/*QUAKED path_attractor (.4 .3 .8) (-16 -16 -24) (16 16 48)
When this is placed on the map it will attract actors by name
from the episodic ai routines

default delay is 10 sec.  
*/

void SP_path_attractor (edict_t *self)
{
	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_NOT;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs,  16,  16,  48);
	
	if (!self->delay)
		self->delay = 10;

	AI_Ent_droptofloor( self );
}


// JOSEPH 16-DEC-98

/*QUAKED misc_cut_scene (0 0 1) (-16 -16 -16) (16 16 16)
*/

/*void CutSceneThink (edict_t *ent)
{
	 ent->nextthink = level.time + 0.1;

	 //if (level.time > (ent->nextthink + ent->wait))
	 // JOSEPH 7-DEC-98
	 if (!ent->wait--)
	   EndCutScene (ent);
}

void CutSceneThinkEnd (edict_t *ent)
{
	EndCutScene (ent);
}

void CutSceneThinkStart (edict_t *ent)
{
	if (!ent->count)
		return;
	
	ent->count--;

	BeginCutScene (ent);

	// JOSEPH 7-DEC-98
	ent->think = CutSceneThink;
	ent->nextthink = level.time + 0.1;
}

void Touch_CutScene (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	ent->think = CutSceneThinkStart;
	ent->nextthink = level.time + 0.1;
}

void SP_misc_cut_scene (edict_t *self)
{
	
	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs,  16,  16,  16);

	self->solid = SOLID_TRIGGER;
	self->touch = Touch_CutScene;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
	
	if (!self->wait)
		self->wait = 60;

	self->wait=10; // just for now

	self->count = 1;

}*/

// JOSEPH 25-FEB-99
/*QUAKED misc_cutscene_trigger (0 0 1) ?

Targets a misc_cutscene_camera

  target - camera to target
  debugprint - set to 1 to print out camera end position and angles	
  duration - fade in time.	  
*/
// END JOSEPH

// JOSEPH 19-MAR-99-B
/*QUAKED misc_cutscene_camera (0 0 1) (-16 -16 -16) (16 16 16)
  
Camera to be targeted from a misc_cutscene_trigger		

  targetname - camera target ID 
  
  cameraorigin - X Y Z camera start position

  cameraangle - X Y Z start angles

  rotate - X Y Z rotational velocity during cut scene

  cameravel - [forward] [right] [up] speed to move from initial angle.	

  cameravelrel - [forward] [right] [up] speed to move relative to current frame angle.	

  wait - cut scene length in seconds (default 5)	

  target - next camera to target.	

  target2 - [NOT WORKING!!] camera angle points to this entity (overides other angle commands)	  

  deadticks - fov for this camera;

  duration - fade out time.
  
  reactdelay - time into camera to start fading out   
*/
// END JOSEPH
void CutSceneThink (edict_t *ent)
{
    if (!ent->wait--)
	{
		{
			edict_t	*e;
			int		i;
			int     found = 0;

			// Print end position if required
			if (ent->debugprint)
			{
				// JOSEPH 24-FEB-99
				vec3_t neworigin;
				
				VectorCopy(ent->target_ent->s.origin, neworigin);
				neworigin[2] += 40;
				gi.dprintf("Camera \"%s\" end position %s\n", ent->target_ent->targetname, vtos(neworigin));            
				gi.dprintf("Camera \"%s\" end angles %s\n", ent->target_ent->targetname, vtos(ent->target_ent->s.angles)); 
				// END JOSEPH
			}
			
			// Restore camera start position and angle
			VectorCopy(ent->target_ent->save_avel, ent->target_ent->s.angles);
	        VectorCopy(ent->target_ent->savecameraorigin, ent->target_ent->s.origin);
			
			// No more cameras
			if (!ent->target_ent->target)
				EndCutScene (ent->target_ent);			

			// Find next target entity camera
			if (ent->target_ent->target)
			{
				for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
				{
					if ((e->targetname) && (!strcmp(e->targetname, ent->target_ent->target)))
					{
						ent->target_ent = e;
						found = 1;
						break;	
					}
				}	
			}

			// Next camera
			if (found)
			{
				// See if a target2 can be found
				if (ent->target_ent->target2)
				{
					for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
					{
						if ((e->targetname) && (!strcmp(e->targetname, ent->target_ent->target2)))
						{
							ent->target_ent->target2_ent = e;
							break;	
						}
					}	
				}
				
				ent->wait = ent->target_ent->wait*10.0;
				if (!ent->wait)
					ent->wait = 5.0*10.0;
				NewCutSceneCamera (ent->target_ent);			
				ent->nextthink = level.time + 0.1;

				// Ridah, Camera accel/decel
				ent->target_ent->timestamp = level.time;
				ent->target_ent->speed = 0;

				// Ridah, play a sound if there is one
				if (ent->target_ent->name)
				{
					edict_t *talkent;

					if (!ent->target_ent->sight_target)
					{
						//gi.dprintf( "Warning: cutsecene camera has voice sound without a \"sight_target\" (speaking charecter's name)\n" );
						gi.positioned_sound( ent->target_ent->s.origin, ent->target_ent, CHAN_AUTO, gi.soundindex( ent->target_ent->name ), 1.0, ATTN_NONE, 0);
					}
					else
					{
						talkent = EP_GetCharacterByName( ent->target_ent->sight_target );
						gi.sound( talkent, CHAN_VOICE, gi.soundindex( ent->target_ent->name ), 1.0, 1, 0);
					}

				}

				// Ridah, scripting
				if (ent->target_ent->scriptname)
				{
					EP_EventScript( &g_edicts[1], ent->target_ent->scriptname );
				}
				
				return;
			}
		}


		// Ridah, scripting
		if (ent->scriptname)
		{
			EP_EventScript( &g_edicts[1], ent->scriptname );
		}

		// No more cameras or target camera not found
		ent->think = 0;
		EndCutScene (ent->target_ent);
	}	
	else
	{
		// Process camera frame
		AdjustCutSceneCamera(ent->target_ent);
	    ent->nextthink = level.time + 0.1;
	}	
}


void CutSceneThinkStart (edict_t *ent)
{
	edict_t	*e;
	int		i;
	
	if (!ent->count)
		return;
	
	// JOSEPH 19-MAR-99-B
	if (ent->duration)
	{
		level.inversefade = 0;
		level.totalfade = ent->duration;
		level.fadeendtime = level.time + level.totalfade;
	}	
	// END JOSEPH	

	ent->count--;

	// Find target entity
	ent->target_ent = 0;

	if (ent->target)
	{
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->targetname) && (!strcmp(e->targetname, ent->target)))
			{
				ent->target_ent = e;
				break;	
			}
		}	
	}

	if (!ent->target_ent)
		return;

	// See if a target2 can be found
	if (ent->target_ent->target2)
	{
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->targetname) && (!strcmp(e->targetname, ent->target_ent->target2)))
			{
				ent->target_ent->target2_ent = e;
				break;	
			}
		}	
	}

	// Ridah, Camera accel/decel
	ent->target_ent->timestamp = level.time;
	ent->target_ent->speed = 0;

	// Ridah, play a sound if there is one
	if (ent->target_ent->name)
	{
		edict_t *talkent;

		if (!ent->target_ent->sight_target)
		{
			//gi.dprintf( "Warning: cutsecene camera has voice sound without a \"sight_target\" (speaking charecter's name)\n" );
			gi.positioned_sound( ent->target_ent->s.origin, ent->target_ent, CHAN_AUTO, gi.soundindex( ent->target_ent->name ), 1.0, ATTN_NONE, 0);
		}
		else
		{
			talkent = EP_GetCharacterByName( ent->target_ent->sight_target );
			gi.sound( talkent, CHAN_VOICE, gi.soundindex( ent->target_ent->name ), 1.0, 1, 0);
		}

	}

	// Ridah, scripting
	if (ent->target_ent->scriptname)
	{
		EP_EventScript( &g_edicts[1], ent->target_ent->scriptname );
	}

	ent->wait = ent->target_ent->wait*10.0;
	
	if (!ent->wait)
		ent->wait = 5.0*5.0;
	
	BeginCutScene (ent->target_ent);
	
	ent->think = CutSceneThink;
	ent->nextthink = level.time + 0.1;
}

void Touch_CutScene (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	CutSceneThinkStart(ent);
}

// JOSEPH 17-MAR-99-B
void Use_CutScene (edict_t *self, edict_t *other, edict_t *activator)
{
	CutSceneThinkStart(self);
}
// END JOSEPH

// OLD
void SP_misc_cut_scene (edict_t *self)
{

}

// JOSEPH 2-MAR-99
void PrecacheCutStuff (char* s)
{
	char	*start;
	char	data[MAX_QPATH];
	int		len;

	if (!s || !s[0])
		return;

	// parse the space seperated precache string
	while (*s)
	{
		start = s;
		while (*s && *s != ' ')
			s++;

		len = s-start;
		if (len >= MAX_QPATH || len < 5)
			gi.error ("Bad precache string");
		memcpy (data, start, len);
		data[len] = 0;
		if (*s)
			s++;

		// determine type based on extension
		if (!strcmp(data+len-3, "md2"))
			gi.modelindex (data);
		else if (!strcmp (data+len-3, "mdx"))
			gi.modelindex (data);
		else if (!strcmp(data+len-3, "wav"))
			gi.soundindex (data);
		if (!strcmp(data+len-3, "pcx"))
			gi.imageindex (data);
	}
}

// JOSEPH 19-MAR-99-B
void SP_misc_cutscene_trigger (edict_t *self)
{
	self->solid = SOLID_TRIGGER;
	gi.setmodel (self, self->model);
    self->svflags |= SVF_NOCLIENT;

	if (self->targetname)
	{	
		self->use = Use_CutScene;
	}
	else
	{
	self->touch = Touch_CutScene;
	}

	if (self->duration)
	{
		level.inversefade = 0;
		level.totalfade = 60.0;
		level.fadeendtime = level.time + level.totalfade;
	}	
	
	gi.linkentity (self);
	self->count = 1;
    
	PrecacheCutStuff (self->name);
}
// END JOSEPH

// JOSEPH 19-MAR-99-B
/*QUAKED misc_use_cutscene (.5 .5 .5) (-8 -8 -8) (8 8 8)
This fixed size trigger targets a misc_cutscene_camera

  target - camera to target
  debugprint - set to 1 to print out camera end position and angles	
  duration - fade in time.	  
*/
void SP_misc_use_cutscene (edict_t *self)
{
	self->use = Use_CutScene;
	
	if (self->duration)
	{
		level.inversefade = 0;
		level.totalfade = 60.0;
		level.fadeendtime = level.time + level.totalfade;
	}	
	
	self->count = 1;
    
	PrecacheCutStuff (self->name);
}
// END JOSEPH

void SP_misc_cutscene_camera (edict_t *self)
{
	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs,  16,  16,  16);

	VectorClear(self->s.angles);

	if ((self->cameraorigin[0] != 0) || (self->cameraorigin[1] != 0) || (self->cameraorigin[2] != 0))
	{
		VectorCopy(self->cameraorigin, self->s.origin);
		self->s.origin[2] -= 40;
	}
	else
	{
		self->s.origin[0] += 8;
		self->s.origin[1] += 8;
		self->s.origin[2] += 8;
	}

	self->solid = SOLID_NOT;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);

	if (!self->deadticks)
		self->deadticks = 90;

	PrecacheCutStuff (self->name);
}
// END JOSEPH

/*QUAKED sfx_beacon (0 0 1) (-16 -16 -16) (16 16 16)
*/

void beacon_think (edict_t *ent)
{
	edict_t	*ignore;
	vec3_t	start;
	vec3_t	end;
	trace_t	tr;
	vec3_t	forward;

	ignore = ent;
 
	ent->s.angles[YAW] += anglemod(level.time * 0.1);
 
	AngleVectors (ent->s.angles, forward, NULL, NULL );

	VectorCopy (ent->s.origin, start);
	VectorMA (start, 2048, forward, end);

	VectorCopy (forward, ent->movedir);

	tr = gi.trace (start, NULL, NULL, end, ignore, CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_DEADMONSTER);
	
	VectorCopy (tr.endpos, ent->s.old_origin);

	ent->nextthink = level.time + FRAMETIME;
	
}

void SP_sfx_beacon (edict_t *ent)
{

	ent->movetype = MOVETYPE_NONE;
	ent->solid = SOLID_NOT;
	ent->s.modelindex = 1;			
	
	ent->s.renderfx |= RF_BEAM;
	ent->s.renderfx2 |= RF2_BEAM2;
	ent->s.frame = 64;
	ent->s.effects |= EF_ROTATE;
	ent->nextthink = level.time + 0.1;
	ent->think = beacon_think;
	ent->s.skinnum = 0xf2f2f0f0;

	gi.linkentity (ent);

}
