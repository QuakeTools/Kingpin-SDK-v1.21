
#include "g_local.h"


/*
=================
check_dodge

This is a support routine used when a client is firing
a non-instant attack weapon.  It checks to see if a
monster's dodge function should be called.
=================
*/
static void check_dodge (edict_t *self, vec3_t start, vec3_t dir, int speed)
{
	vec3_t	end;
	vec3_t	v;
	trace_t	tr;
	float	eta;

	// easy mode only ducks one quarter the time
	if (skill->value == 0)
	{
		if (random() > 0.25)
			return;
	}
	VectorMA (start, 8192, dir, end);
	tr = gi.trace (start, NULL, NULL, end, self, MASK_SHOT);
	if ((tr.ent) && (tr.ent->svflags & SVF_MONSTER) && (tr.ent->health > 0) && (tr.ent->cast_info.dodge) && infront(tr.ent, self))
	{
		VectorSubtract (tr.endpos, start, v);
		eta = (VectorLength(v) - tr.ent->maxs[0]) / speed;
		tr.ent->cast_info.dodge (tr.ent, self, eta);
	}
}


/*
=================
fire_hit

Used for all impact (hit/punch/slash) attacks
=================
*/
qboolean fire_hit (edict_t *self, vec3_t aim, int damage, int kick)
{
	trace_t		tr;
	vec3_t		forward, right, up;
	vec3_t		v;
	vec3_t		point;
	float		range;
	vec3_t		dir;

	//see if enemy is in range
	VectorSubtract (self->enemy->s.origin, self->s.origin, dir);
	range = VectorLength(dir);
	if (range > aim[0])
		return false;

	if (aim[1] > self->mins[0] && aim[1] < self->maxs[0])
	{
		// the hit is straight on so back the range up to the edge of their bbox
		range -= self->enemy->maxs[0];
	}
	else
	{
		// this is a side hit so adjust the "right" value out to the edge of their bbox
		if (aim[1] < 0)
			aim[1] = self->enemy->mins[0];
		else
			aim[1] = self->enemy->maxs[0];
	}

	VectorMA (self->s.origin, range, dir, point);

	tr = gi.trace (self->s.origin, NULL, NULL, point, self, MASK_SHOT);
	if (tr.fraction < 1)
	{
		if (!tr.ent->takedamage)
			return false;
		// if it will hit any client/monster then hit the one we wanted to hit
		if ((tr.ent->svflags & SVF_MONSTER) || (tr.ent->client))
			tr.ent = self->enemy;
	}

	AngleVectors(self->s.angles, forward, right, up);
	VectorMA (self->s.origin, range, forward, point);
	VectorMA (point, aim[1], right, point);
	VectorMA (point, aim[2], up, point);
	VectorSubtract (point, self->enemy->s.origin, dir);

	// do the damage
	T_Damage (tr.ent, self, self, dir, point, vec3_origin, damage, kick/2, DAMAGE_NO_KNOCKBACK, MOD_HIT);

	if (!(tr.ent->svflags & SVF_MONSTER) && (!tr.ent->client))
		return false;

	// do our special form of knockback here
	VectorMA (self->enemy->absmin, 0.5, self->enemy->size, v);
	VectorSubtract (v, point, v);
	VectorNormalize (v);
	VectorMA (self->enemy->velocity, kick, v, self->enemy->velocity);
	if (self->enemy->velocity[2] > 0)
		self->enemy->groundentity = NULL;
	return true;
}


void ActorDamageSimpleSkinChangeCheck (edict_t *self, vec3_t hit)
{
	int baseskin, part, subobject;
	int	rval;

	if (cl_parental_lock->value && !cl_parental_override->value)
		return;

	rval = rand()%100;

	if (rval > 75)
	{
		part = PART_HEAD;
		subobject = 0;
	}
	else if (rval > 50)
	{
		part = PART_LEGS;
		subobject = rand()%7;
	}
	else
	{
		part = PART_BODY;
		subobject = rand()%7;
	}


	if (!self->s.model_parts[part].object_bounds[subobject] && !(self->s.model_parts[part].invisible_objects & (1<<subobject)))
	{
		gi.dprintf ("invalid request\n");
		return;
	}

//	gi.dprintf ("part: %d subobject: %d\n", part, subobject);

	if (self->art_skins)
	{
		baseskin = self->s.model_parts[part].baseskin;
						
		if (self->health < (self->max_health * 0.5))
		{
			self->s.model_parts[part].skinnum[subobject] =  baseskin + 2;
		}
		else if (self->health < (self->max_health * 0.75))
		{
			self->s.model_parts[part].skinnum[subobject] =  baseskin + 1;
		}
	}
}

// JOSEPH 14-JAN-99
/*
=================
fire_lead

This is an internal support routine used for bullet/pellet based weapons.
=================
*/
void M_ReactToDamage (edict_t *targ, edict_t *attacker, float damage);
// JOSEPH
static void fire_lead (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int te_impact, int hspread, int vspread, int mod)
{
	trace_t		tr, mdx_tr;
	vec3_t		dir;
	vec3_t		forward, right, up;
	vec3_t		end;
	float		r;
	float		u;
	vec3_t		water_start, alpha_start;
	qboolean	water = false;
	int			content_mask = MASK_SHOT | MASK_WATER | MASK_ALPHA;
	int			len;
	//int			NoBulletHole;
	int			pointblank = 0;
	int			nosmoke = 0;
	static float lastshotgun = 0;
	vec3_t		tempvec;
	int			conweap = 0;

	PlayerNoise(self, start, PNOISE_WEAPON);

	tr = gi.trace (self->s.origin, NULL, NULL, start, self, MASK_SHOT );
	if (!(tr.fraction < 1.0))
	{
		vectoangles (aimdir, dir);
		AngleVectors (dir, forward, right, up);

		if (deathmatch->value && (mod == MOD_PISTOL || mod == MOD_SILENCER))
		{
			r = 0.0;
			u = 0.0;
		}
		else
		{
			r = crandom()*hspread;
			u = crandom()*vspread;
		}

		VectorMA (start, 8192, forward, end);
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		if (gi.pointcontents (start) & MASK_WATER)
		{
			water = true;
			VectorCopy (start, water_start);
			content_mask &= ~MASK_WATER;
		}

		tr = gi.trace (start, NULL, NULL, end, self, content_mask);

		if (mod == MOD_BLACKJACK)
		{
			vec3_t newvec;

			VectorSubtract(start, tr.endpos, newvec);
			if (VectorLength(newvec) > 32) return;
			conweap = 1; 
		}

		// JOSEPH 19-JAN-99
		if ((mod == MOD_BLACKJACK) || (mod == MOD_CROWBAR))
		{
			vec3_t newvec;

			VectorSubtract(start, tr.endpos, newvec);
			if (VectorLength(newvec) > 32) return;
			conweap = 1; 
		}
		// END JOSEPH
		
		// JOSEPH 9-APR-99
        if ((tr.surface->flags & SURF_METAL) || (tr.surface->flags & SURF_METAL_L))
		{
			gi.WriteByte (svc_muzzleflash3);
			gi.WriteShort (self - g_edicts);
			gi.WriteByte (MZ3_LEADHIT_METAL);
			gi.multicast (start, MULTICAST_PVS);
		}
		else if (tr.surface->flags & SURF_WOOD)
		{
			switch (rand()%3)
			{
				case 0:
					gi.sound (self, CHAN_VOICE, gi.soundindex ("weapons/bullethit_wood1.wav"), 1, ATTN_NORM, 0);
					break;
				case 1:
					gi.sound (self, CHAN_VOICE, gi.soundindex ("weapons/bullethit_wood2.wav"), 1, ATTN_NORM, 0);
					break;
				case 2:
					gi.sound (self, CHAN_VOICE, gi.soundindex ("weapons/bullethit_wood3.wav"), 1, ATTN_NORM, 0);
					break;
			}
		}
		// END JOSEPH
		
		// JOSEPH
		// see if we hit an alpha surface
		if (((tr.ent) && (tr.ent->s.renderfx2 & RF2_SURF_ALPHA))
		   || ((tr.contents & MASK_ALPHA))) 
		{
		    if (crandom() < .93)
			{
				VectorCopy (tr.endpos, alpha_start);
				
				// Skip alpha surface
// Ridah, don't need these
//				VectorSubtract (end, start, dir);
//				vectoangles (dir, dir);
//				AngleVectors (dir, forward, right, up);
//				VectorMA (alpha_start, 8192, forward, end);
				if (tr.ent->s.renderfx2 & RF2_SURF_ALPHA)
				{
					VectorMA (alpha_start, 4*3, aimdir, alpha_start);
				}
				else
				{
					VectorMA (alpha_start, 4, aimdir, alpha_start);				
				}	
				// re-trace after alpha surface
				tr = gi.trace (alpha_start, NULL, NULL, end, self, MASK_SHOT);
			}
		}    
		
		// see if we hit water
		if (tr.contents & MASK_WATER)
		{
			int		color;

			water = true;
			VectorCopy (tr.endpos, water_start);

			if (!VectorCompare (start, tr.endpos))
			{
				if (tr.contents & CONTENTS_WATER)
				{
					if (strcmp(tr.surface->name, "*brwater") == 0)
						color = SPLASH_BROWN_WATER;
					else
						color = SPLASH_BLUE_WATER;
				}
				else if (tr.contents & CONTENTS_SLIME)
					color = SPLASH_SLIME;
				// JOSEPH 6-JUN-99
				else if (tr.contents & CONTENTS_LAVA)
					color = /*SPLASH_LAVA*/SPLASH_UNKNOWN;
				// END JOSEPH
				else
					color = SPLASH_UNKNOWN;

				if (color != SPLASH_UNKNOWN)
				{
					gi.WriteByte (svc_temp_entity);
					gi.WriteByte (TE_SPLASH);
					gi.WriteByte (8);
					gi.WritePosition (tr.endpos);
					gi.WriteDir (tr.plane.normal);
					gi.WriteByte (color);
					gi.multicast (tr.endpos, MULTICAST_PVS);

				}

				// if (color == SPLASH_BLUE_WATER)
				if (water)
				{
					static	float	last_ripple;
		
					if (last_ripple > level.time)
						last_ripple = 0;

					if (last_ripple < (level.time - 0.75))
					{
						// Ripple effect
						SurfaceSpriteEffectRipple(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH, SFX_RIPPLE_HEIGHT,
												tr.ent, tr.endpos, tr.plane.normal );

						if (!deathmatch->value)
						{
							SurfaceSpriteEffectRipple(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH<<1, SFX_RIPPLE_HEIGHT<<1,
													tr.ent, tr.endpos, tr.plane.normal );
							SurfaceSpriteEffectRipple(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH>>1, SFX_RIPPLE_HEIGHT>>1,
													tr.ent, tr.endpos, tr.plane.normal );
						}
					}

				}

				// change bullet's course when it enters water
				VectorSubtract (end, start, dir);
				vectoangles (dir, dir);
				AngleVectors (dir, forward, right, up);
				r = crandom()*hspread*2;
				u = crandom()*vspread*2;
				VectorMA (water_start, 8192, forward, end);
				VectorMA (end, r, right, end);
				VectorMA (end, u, up, end);
			}

			// re-trace ignoring water this time
			tr = gi.trace (water_start, NULL, NULL, end, self, MASK_SHOT);
		}
	}

	// send gun puff / flash
	if (!((tr.surface) && (tr.surface->flags & SURF_SKY)))
	{
		if (tr.fraction < 1.0)
		{
			
			// gi.dprintf ("hit: %s\n", tr.ent->classname);

			// Calculate shot distance
			VectorSubtract (tr.endpos, self->s.origin, tempvec);	
		    len = VectorNormalize (tempvec);

			// On smoke up close
			if ((te_impact == TE_GUNSHOT) && (len < 96) && (lastshotgun) && (lastshotgun > level.time))
			{
				nosmoke = 1;
			}
			else if (te_impact == TE_GUNSHOT)
			{
				lastshotgun = level.time + 0.10;
			}
			
			if (tr.ent->takedamage)
			{
			    // Point blank range shot gives more damage 
				if (len < 64)
				{
					damage *= 2;
					pointblank = 1;
				}

				// JOSEPH 18-FEB-99
				if ((tr.ent->svflags & SVF_PROP) || (!strcmp(tr.ent->classname,"func_explosive")))
				{
					if (!conweap)
					{
						extern int ClipVelocity (vec3_t in, vec3_t normal, vec3_t out, float overbounce);
						vec3_t dir;

						// Ridah, spawn metallic sparks on metal surfaces
						// JOSEPH 11-JUN-99-B
						if ((tr.ent->svflags & SVF_PROP) && (tr.ent->surfacetype & (SURF_METAL | SURF_METAL_L)))
						{
							te_impact = TE_METAL_SPARKS;
							ClipVelocity( aimdir, tr.plane.normal, dir, 1.5 );
						}
						else if (tr.surface->flags & (SURF_METAL | SURF_METAL_L))
						// END JOSEPH
						{
							te_impact = TE_METAL_SPARKS;
							ClipVelocity( aimdir, tr.plane.normal, dir, 1.5 );
						}
						else
						{
							VectorCopy( tr.plane.normal, dir );
						}

						if (!nosmoke)
						{
							gi.WriteByte (svc_temp_entity);
							gi.WriteByte (te_impact);
							gi.WritePosition (tr.endpos);
							gi.WriteDir (dir);
							gi.multicast (tr.endpos, MULTICAST_PVS);
						}
					}
					
					if (self->client)
						PlayerNoise(self, tr.endpos, PNOISE_IMPACT);
				}
				// END JOSEPH
				
				// Ridah, only do MDX bbox check if it's a client firing
				if (self->client && tr.ent->s.num_parts && (!deathmatch->value || dm_locational_damage->value))
				{
					// either way, react to this attempted hostility
					// JOSEPH 9-FEB-99
					if (!(tr.ent->svflags & SVF_PROP) && tr.ent->svflags & SVF_MONSTER)
					// either way, react to this attempted hostility
						M_ReactToDamage (tr.ent, self, damage ); 
					// END JOSEPH

					{
						#define	MAX_ITERATIONS	10
						trace_t		ignore;
						qboolean	is_mdx = false;
						int			iterations=10;	// FIXME: this is a hack
						edict_t		*ignored[MAX_ITERATIONS];
						int			num_ignored;

						ignore = tr;
						num_ignored = 0;

						while (iterations--)
						{
							mdx_tr = MDX_HitCheck (ignore.ent, self, self, aimdir, ignore.endpos, ignore.plane.normal, damage, kick, DAMAGE_BULLET, mod, end);
							
							if (mdx_tr.ent->flags & FL_MDXBBOX) // we hit an mdx_bbox
							{
								is_mdx = true;
								VectorCopy (mdx_tr.endpos, tr.endpos);
								break;
							}
							else if (mdx_tr.ent->takedamage && mdx_tr.ent->s.num_parts) // we missed the mdx_bbox but hit another mdx
							{
								is_mdx = true;
								ignore = mdx_tr;

								// ignore this entity from now on
								ignored[num_ignored++] = mdx_tr.ent;
								gi.unlinkentity( mdx_tr.ent );
							}
							else if (mdx_tr.ent->takedamage) // we hit an md2
							{
								is_mdx = false;
								VectorCopy (mdx_tr.endpos, tr.endpos);
								VectorCopy (mdx_tr.plane.normal, tr.plane.normal);
								tr.ent = mdx_tr.ent;
								break;
							}
							// JOSEPH 5-FEB-99-B
							else if (tr.ent->svflags & SVF_PROP)
							{
// Ridah, 25-may-99, Fixes Episode 5/6 invulnerable rats & crates bug. Old code commented out.
/*
								is_mdx = true;
								VectorCopy (mdx_tr.endpos, tr.endpos);
								break;
*/
								is_mdx = false;
								break;
							}
							// END JOSEPH
							else
							{
								// we missed
								VectorCopy (mdx_tr.endpos, tr.endpos);
								VectorCopy (mdx_tr.plane.normal, tr.plane.normal);

								// set all the ignored entities back
								for (iterations = 0; iterations < num_ignored; iterations++)
									gi.linkentity( ignored[iterations] );

								goto bolt;
							}
						}

						// set all the ignored entities back
						for (iterations = 0; iterations < num_ignored; iterations++)
							gi.linkentity( ignored[iterations] );

						if (is_mdx)
						{
							// Ridah, 18-mar-99, changed this, was causing damage to the wrong entity when dead bodies are close (gibs were spawning on wrong body)
							T_DamageMDX (ignore.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, kick, DAMAGE_BULLET, mod, mdx_tr.ent->count, mdx_tr.ent->dmg); 
						
							// Head shot blood on close wall 
							// JOSEPH 25-JAN-99
							if ((mdx_tr.ent->count == PART_HEAD) && (!(tr.ent->svflags & SVF_PROP)))
							// END JOSEPH
							{
								trace_t		tr2;
								vec3_t		newstart, newdir, newend, travelvec;
																
								VectorCopy (tr.endpos, newstart);
								VectorSubtract (end, start, newdir);
								vectoangles (newdir, newdir);
								AngleVectors (newdir, forward, NULL, NULL);
								
								do
								{
									VectorMA (newstart, 8192, forward, newend);
									VectorMA (newstart, 4, forward, newstart);

									tr2 = gi.trace (newstart, NULL, NULL, newend, self, MASK_SHOT);
								}
								while (tr2.ent == tr.ent);
								
								VectorSubtract(newstart, tr2.endpos, travelvec);
								len = VectorNormalize(travelvec);
								
							    // JOSEPH 8-JUN-99
								if ((len < 100.0) && (!tr2.ent->takedamage) &&
									(!((((int)(dmflags->value)) & DF_NO_FRIENDLY_FIRE))) &&
									((strncmp (tr2.surface->name, "sky", 3) != 0)))
								// END JOSEPH
								{
									if (pointblank)
									{
										SurfaceSpriteEffect(SFX_SPRITE_SURF_BLOOD1, SFX_BLOOD_WIDTH*4, 
															SFX_BLOOD_HEIGHT*4,
															tr2.ent, tr2.endpos, tr2.plane.normal );
									}
									else
									{
										char rnd;

										rnd = (char)(1 + rand()%4);

										SurfaceSpriteEffect(SFX_SPRITE_SURF_BLOOD1, (unsigned char)(SFX_BLOOD_WIDTH*rnd),
															(unsigned char)(SFX_BLOOD_HEIGHT*rnd),
															tr2.ent, tr2.endpos, tr2.plane.normal );
									}
								}
							}
						}
						else
							T_Damage (tr.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, kick, DAMAGE_BULLET, mod); 
					}
				}
				else
				{

					qboolean check_skin_change = false;

					if (self->svflags & SVF_MONSTER && tr.ent->svflags & SVF_MONSTER && self->cast_group != tr.ent->cast_group && tr.ent->cast_group != 1)
					{	// Tweak: do more damage when AI shooting AI, more realistic
						damage *= 2;

						if (tr.ent->gender && !tr.ent->client)
						{
							check_skin_change = true;
						}
					}

					T_Damage (tr.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, kick, DAMAGE_BULLET, mod);

					if (check_skin_change)
					{
						ActorDamageSimpleSkinChangeCheck (tr.ent, tr.endpos);
					}
				}

//				if (tr.ent->svflags & SVF_MONSTER)
//				{	// add some momentum
//					tr.ent->velocity[2] += kick*3;
//				}
			}
			else
			{
bolt:
				// JOSEPH
				if ((strncmp (tr.surface->name, "sky", 3) != 0) /*|| NoBulletHole*/)
				{
					if (!conweap)
					{
						extern int ClipVelocity (vec3_t in, vec3_t normal, vec3_t out, float overbounce);
						vec3_t dir;

						// Ridah, spawn metallic sparks on metal surfaces
						if (tr.surface->flags & (SURF_METAL | SURF_METAL_L))
						{
							te_impact = TE_METAL_SPARKS;
							ClipVelocity( aimdir, tr.plane.normal, dir, 1.5 );
						}
						else
						{
							VectorCopy( tr.plane.normal, dir );
						}

						if (deathmatch->value && te_impact == TE_GUNSHOT)
						{
							te_impact = TE_GUNSHOT_VISIBLE;
							ClipVelocity( aimdir, tr.plane.normal, dir, 1.5 );
						}

						if (!nosmoke)
						{
							gi.WriteByte (svc_temp_entity);
							gi.WriteByte (te_impact);
							gi.WritePosition (tr.endpos);
							gi.WriteDir (dir);
							gi.multicast (tr.endpos, MULTICAST_PVS);
						}
					}
					
					if (self->client)
						PlayerNoise(self, tr.endpos, PNOISE_IMPACT);

					// Ridah, surface sprites
					if (!(self->svflags & SVF_PROP) && !deathmatch->value && !water)	// Ridah, had to remove this in deathmatch, since it's bandwidth hungry
					{
						SurfaceSpriteEffect(	SFX_SPRITE_SURF_BULLET1, SFX_BULLET_WIDTH * 5, SFX_BULLET_HEIGHT * 5,
												tr.ent, tr.endpos, tr.plane.normal );
					}

//					SurfaceSpriteEffect(	SFX_SPRITE_SURF_BLOOD1, SFX_BLOOD_WIDTH, SFX_BLOOD_HEIGHT,
//											tr.ent, tr.endpos, tr.plane.normal );

					// done.
				}
			}
		}
	}

	// if went through water, determine where the end and make a bubble trail
	if (water)
	{
		vec3_t	pos;

		VectorSubtract (tr.endpos, water_start, dir);
		
		VectorNormalize (dir);
		VectorMA (tr.endpos, -2, dir, pos);
		if (gi.pointcontents (pos) & MASK_WATER)
			VectorCopy (pos, tr.endpos);
		else
			tr = gi.trace (pos, NULL, NULL, water_start, tr.ent, MASK_WATER);

		VectorAdd (water_start, tr.endpos, pos);
		VectorScale (pos, 0.5, pos);

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_BUBBLETRAIL);
		gi.WritePosition (water_start);
		gi.WritePosition (tr.endpos);
		gi.multicast (pos, MULTICAST_PVS);
	}
}
// END JOSEPH

/*
=================
fire_bullet

Fires a single round.  Used for machinegun and chaingun.  Would be fine for
pistols, rifles, etc....
=================
*/
void fire_bullet (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int hspread, int vspread, int mod)
{
	fire_lead (self, start, aimdir, damage, kick, TE_GUNSHOT, hspread, vspread, mod);
}


/*
=================
fire_shotgun

Shoots shotgun pellets.  Used by shotgun and super shotgun.
=================
*/
void fire_shotgun (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int hspread, int vspread, int count, int mod)
{
	int		i;

	for (i = 0; i < count; i++)
		// fire_lead (self, start, aimdir, damage, kick, TE_SHOTGUN, hspread, vspread, mod);
	fire_lead (self, start, aimdir, damage, kick, TE_GUNSHOT, hspread, vspread, mod);
}


/*
=================
fire_blaster

Fires a single blaster bolt.  Used by the blaster and hyper blaster.
=================
*/
void blaster_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	int		mod;

	if (other == self->owner)
		return;

	if (surf && (surf->flags & SURF_SKY))
	{
		G_FreeEdict (self);
		return;
	}

	if (self->owner->client)
		PlayerNoise(self->owner, self->s.origin, PNOISE_IMPACT);

	if (other->takedamage)
	{
		if (self->spawnflags & 1)
			mod = MOD_HYPERBLASTER;
		else
			mod = MOD_BLASTER;
		T_Damage (other, self, self->owner, self->velocity, self->s.origin, plane->normal, self->dmg, 1, DAMAGE_ENERGY, mod);
	}
	else
	{
		gi.WriteByte (svc_temp_entity);
		// RAFAEL
		//if (self->s.effects & TE_BLUEHYPERBLASTER)
		//	gi.WriteByte (TE_BLUEHYPERBLASTER);
		//else
			gi.WriteByte (TE_BLASTER);
		gi.WritePosition (self->s.origin);
		if (!plane)
			gi.WriteDir (vec3_origin);
		else
			gi.WriteDir (plane->normal);
		gi.multicast (self->s.origin, MULTICAST_PVS);
	}

	G_FreeEdict (self);
}

void fire_blaster (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int effect, qboolean hyper)
{
	edict_t	*bolt;
	trace_t	tr;

	VectorNormalize (dir);

	bolt = G_Spawn();
	bolt->svflags = SVF_DEADMONSTER;
	// yes, I know it looks weird that projectiles are deadmonsters
	// what this means is that when prediction is used against the object
	// (blaster/hyperblaster shots), the player won't be solid clipped against
	// the object.  Right now trying to run into a firing hyperblaster
	// is very jerky since you are predicted 'against' the shots.
	VectorCopy (start, bolt->s.origin);
	VectorCopy (start, bolt->s.old_origin);
	vectoangles (dir, bolt->s.angles);
	VectorScale (dir, speed, bolt->velocity);
	bolt->movetype = MOVETYPE_FLYMISSILE;
	bolt->clipmask = MASK_SHOT;
	bolt->solid = SOLID_BBOX;
	bolt->s.effects |= effect;
	VectorClear (bolt->mins);
	VectorClear (bolt->maxs);
	bolt->s.modelindex = gi.modelindex ("models/objects/laser/tris.md2");
	bolt->s.sound = gi.soundindex ("misc/lasfly.wav");
	bolt->owner = self;
	bolt->touch = blaster_touch;
	bolt->nextthink = level.time + 2;
	bolt->think = G_FreeEdict;
	bolt->dmg = damage;
	bolt->classname = "bolt";
	if (hyper)
		bolt->spawnflags = 1;
	gi.linkentity (bolt);

	if (self->client)
		check_dodge (self, bolt->s.origin, dir, speed);

	tr = gi.trace (self->s.origin, NULL, NULL, bolt->s.origin, bolt, MASK_SHOT);
	if (tr.fraction < 1.0)
	{
		VectorMA (bolt->s.origin, -10, dir, bolt->s.origin);
		bolt->touch (bolt, tr.ent, NULL, NULL);
	}
}	

// RAFAEL
void fire_blueblaster (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int effect)
{
	edict_t *bolt;
	trace_t tr;

	VectorNormalize (dir);

	bolt = G_Spawn ();
	VectorCopy (start, bolt->s.origin);
	VectorCopy (start, bolt->s.old_origin);
	vectoangles (dir, bolt->s.angles);
	VectorScale (dir, speed, bolt->velocity);
	bolt->movetype = MOVETYPE_FLYMISSILE;
	bolt->clipmask = MASK_SHOT;
	bolt->solid = SOLID_BBOX;
	bolt->s.effects |= effect;
	VectorClear (bolt->mins);
	VectorClear (bolt->maxs);

	bolt->s.modelindex = gi.modelindex ("models/objects/blaser/tris.md2");
	bolt->s.sound = gi.soundindex ("misc/lasfly.wav");
	bolt->owner = self;
	bolt->touch = blaster_touch;
	bolt->nextthink = level.time + 2;
	bolt->think = G_FreeEdict;
	bolt->dmg = damage;
	bolt->classname = "bolt";
	gi.linkentity (bolt);

	if (self->client)
		check_dodge (self, bolt->s.origin, dir, speed);

	tr = gi.trace (self->s.origin, NULL, NULL, bolt->s.origin, bolt, MASK_SHOT);

	if (tr.fraction < 1.0)
	{
		VectorMA (bolt->s.origin, -10, dir, bolt->s.origin);
		bolt->touch (bolt, tr.ent, NULL, NULL);
	}

}
/*
// JOSEPH
void fire_fire (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int effect, qboolean hyper)
{
	//fire_fire (ent, start, forward, damage, 50, EF_BLASTER, false);
	
	VectorNormalize (dir);
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SFXFIREGO);
	gi.WritePosition (start);
//	gi.WriteDir (dir);
	gi.multicast (start, MULTICAST_PVS);
}	
//END JOSEPH
*/





// JOSEPH 20-JAN-99
/*
=================
Grenade_Explode
=================
*/
/*static void Grenade_Explode (edict_t *ent)
{
	vec3_t		origin;
	int			mod;

	if (ent->owner->client)
		PlayerNoise(ent->owner, ent->s.origin, PNOISE_IMPACT);

	//FIXME: if we are onground then raise our Z just a bit since we are a point?
	if (ent->enemy)
	{
		float	points;
		vec3_t	v;
		vec3_t	dir;

		VectorAdd (ent->enemy->mins, ent->enemy->maxs, v);
		VectorMA (ent->enemy->s.origin, 0.5, v, v);
		VectorSubtract (ent->s.origin, v, v);
		points = ent->dmg - 0.5 * VectorLength (v);
		VectorSubtract (ent->enemy->s.origin, ent->s.origin, dir);
		if (ent->spawnflags & 1)
			mod = MOD_HANDGRENADE;
		else
			mod = MOD_GRENADE;
		T_Damage (ent->enemy, ent, ent->owner, dir, ent->s.origin, vec3_origin, (int)points, (int)points, DAMAGE_RADIUS, mod);
	}

	if (ent->spawnflags & 2)
		mod = MOD_HELD_GRENADE;
	else if (ent->spawnflags & 1)
		mod = MOD_HG_SPLASH;
	else
		mod = MOD_G_SPLASH;
	T_RadiusDamage(ent, ent->owner, ent->dmg, ent->enemy, ent->dmg_radius, mod);

	VectorMA (ent->s.origin, -0.02, ent->velocity, origin);
	gi.WriteByte (svc_temp_entity);
	if (ent->waterlevel)
	{
		if (ent->groundentity)
			gi.WriteByte (TE_GRENADE_EXPLOSION_WATER);
		else
			gi.WriteByte (TE_ROCKET_EXPLOSION_WATER);
	}
	else
	{
		if (ent->groundentity)
			gi.WriteByte (TE_GRENADE_EXPLOSION);
		else
			gi.WriteByte (TE_ROCKET_EXPLOSION);
	}
	gi.WritePosition (origin);
	gi.multicast (ent->s.origin, MULTICAST_PHS);

	G_FreeEdict (ent);
}*/

static void Grenade_Explode (edict_t *ent)
{
	vec3_t		origin, vec;
	int			mod;
	trace_t		tr;

	if (ent->owner->client)
		PlayerNoise(ent->owner, ent->s.origin, PNOISE_IMPACT);

	if (ent->enemy == ent->owner)
		ent->enemy = NULL;

	//FIXME: if we are onground then raise our Z just a bit since we are a point?
	/*
	if (ent->enemy)
	{
		float	points;
		vec3_t	v;
		vec3_t	dir;

		VectorAdd (ent->enemy->mins, ent->enemy->maxs, v);
		VectorMA (ent->enemy->s.origin, 0.5, v, v);
		VectorSubtract (ent->s.origin, v, v);
		points = ent->dmg - 0.5 * VectorLength (v);
		VectorSubtract (ent->enemy->s.origin, ent->s.origin, dir);
		if (ent->spawnflags & 1)
			mod = MOD_HANDGRENADE;
		else
			mod = MOD_GRENADE;
		T_Damage (ent->enemy, ent, ent->owner, dir, ent->s.origin, vec3_origin, (int)points, (int)points, DAMAGE_RADIUS, mod);
	}
	*/

	if (ent->spawnflags & 2)
		mod = MOD_HELD_GRENADE;
	else if (ent->spawnflags & 1)
		mod = MOD_HG_SPLASH;
	else
		mod = MOD_G_SPLASH;
	
	T_RadiusDamage(ent, ent->owner, ent->dmg, ent->enemy, ent->dmg_radius, mod);

	VectorMA (ent->s.origin, -0.02, ent->velocity, origin);

	// Ridah, trace a line to this "origin" to make sure it isn't in a solid (in which case the explosion won't show)
	if (!VectorCompare( ent->velocity, vec3_origin))
	{
		tr = gi.trace( ent->s.origin, NULL, NULL, origin, ent, MASK_SOLID );
		if (tr.fraction < 1)
			VectorCopy(ent->s.origin, origin);
	}

	gi.WriteByte (svc_temp_entity);

	if (!ent->enemy)
	{
		VectorClear( vec );
		vec[2] = 1;
	}
	else
	{
		VectorSubtract( ent->s.origin, ent->enemy->s.origin, vec );
		VectorNormalize( vec );
	}

	if (ent->waterlevel)
	{
		gi.WriteByte (TE_CONCUSSION_EXPLOSION_WATER);
	}
	else
	{
		gi.WriteByte (TE_CONCUSSION_EXPLOSION_BIG);
	}
	gi.WritePosition (origin);
	gi.WriteDir( vec );
	gi.WriteByte( (int)(ent->dmg) );
	gi.multicast (ent->s.origin, MULTICAST_PHS);

	G_FreeEdict (ent);
}
// END JOSEPH


// JOSEPH
static void Grenade_Touch (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	
	if (other == ent->owner)
		return;

	if (other->takedamage)
		return;

	if (surf && (surf->flags & SURF_SKY))
	{
		G_FreeEdict (ent);
		return;
	}

	if (surf && (surf->flags & SURF_ALPHA))
	{
		// Grenade gets stuck in alpha surface
		if (!(crandom() < .85))
        {
			ent->gravity = 0; 
			VectorClear (ent->velocity);
			VectorClear (ent->avelocity);
			return;
		}
	}

	if (!other->takedamage)
	{
		VectorSet (ent->avelocity, crandom()*1000, crandom()*1000, crandom()*1000);

		if ((rand()%100) > 66)
			gi.sound (ent, CHAN_VOICE, gi.soundindex ("weapons/grenade_launcher/grenade bounce1.wav"), 1, ATTN_NORM, 0);
		else if ((rand()%100) > 50)
			gi.sound (ent, CHAN_VOICE, gi.soundindex ("weapons/grenade_launcher/grenade bounce2.wav"), 1, ATTN_NORM, 0);
		else
			gi.sound (ent, CHAN_VOICE, gi.soundindex ("weapons/grenade_launcher/grenade bounce3.wav"), 1, ATTN_NORM, 0);

		// Ridah, Grenade Avoidance: notify AI of our existance
		AI_AvoidDangerousEntity( ent );
		// done.

		return;
	}


	ent->enemy = other;
	Grenade_Explode (ent);
}
// END JOSEPH


void fire_grenade (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius)
{
	edict_t	*grenade;
	vec3_t	dir;
	vec3_t	forward, right, up;

	vectoangles (aimdir, dir);
	AngleVectors (dir, forward, right, up);

	grenade = G_Spawn();
	VectorCopy (start, grenade->s.origin);
	VectorScale (aimdir, speed, grenade->velocity);
	VectorMA (grenade->velocity, 200 + crandom() * 10.0, up, grenade->velocity);
	VectorMA (grenade->velocity, crandom() * 10.0, right, grenade->velocity);
	VectorSet (grenade->avelocity, 150*(-1 + 2*(rand()%2)), 150*crandom(), 800);
	VectorCopy( dir, grenade->s.angles );

	// grenade->movetype = MOVETYPE_TOSS_SLIDE;//MOVETYPE_BOUNCE;
	
	// the movetype_toss_slide is crashing the game
	grenade->movetype = MOVETYPE_BOUNCE;

	grenade->clipmask = MASK_SHOT;
	grenade->solid = SOLID_BBOX;
	grenade->s.effects |= EF_GRENADE;
	VectorClear (grenade->mins);
	VectorClear (grenade->maxs);
	
	// JOSEPH 30-APR-99 
	grenade->s.modelindex = gi.modelindex ("models/weapons/grenade/tris.md2");
	// END JOSEPH

	grenade->owner = self;
	grenade->touch = Grenade_Touch;
	grenade->nextthink = level.time + timer;
	grenade->think = Grenade_Explode;
	grenade->dmg = damage;
	grenade->dmg_radius = damage_radius;
	grenade->classname = "grenade";

	grenade->s.renderfx2 |= RF2_NOSHADOW;	
	grenade->s.renderfx  |= RF_REFL_MAP;
	// END JOSEPH

	// Ridah, Grenade Avoidance: notify AI of our existance
/*
	{
		trace_t tr;

		VectorMA( grenade->s.origin, 800, forward, dir );

		tr = gi.trace( grenade->s.origin, NULL, NULL, dir, self, MASK_SHOT );

		VectorCopy( grenade->s.origin, dir );
		VectorCopy( tr.endpos, grenade->s.origin );
		VectorMA( grenade->s.origin, -16, forward, grenade->s.origin );
*/
		AI_AvoidDangerousEntity( self/*grenade*/ );
/*
		VectorCopy( dir, grenade->s.origin );
	}
*/
	// done.

	gi.linkentity (grenade);
}


// JOSEPH 19-MAY-99
void fire_dynamite (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius)
{
	edict_t	*grenade;
	vec3_t	dir;
	vec3_t	forward, right, up;

	vectoangles (aimdir, dir);
	AngleVectors (dir, forward, right, up);

	grenade = G_Spawn();
	VectorCopy (start, grenade->s.origin);
	VectorScale (aimdir, speed, grenade->velocity);
	VectorMA (grenade->velocity, 200 + crandom() * 10.0, up, grenade->velocity);
	VectorMA (grenade->velocity, crandom() * 10.0, right, grenade->velocity);

	// the movetype_toss_slide is crashing the game
	grenade->movetype = MOVETYPE_BOUNCE;

	grenade->clipmask = MASK_SHOT;
	grenade->solid = SOLID_BBOX;
	grenade->s.effects |= EF_GRENADE;
	VectorClear (grenade->mins);
	VectorClear (grenade->maxs);
	
	grenade->s.modelindex = gi.modelindex ("models/props/dynomite/tris.md2");

	grenade->owner = self;
	grenade->touch = Grenade_Touch;
	grenade->nextthink = level.time + timer;
	grenade->think = Grenade_Explode;
	grenade->dmg = damage;
	grenade->dmg_radius = damage_radius;
	grenade->classname = "grenade";

	grenade->s.renderfx2 |= RF2_NOSHADOW;	
	grenade->s.renderfx  |= RF_REFL_MAP;

	AI_AvoidDangerousEntity( self);

	gi.linkentity (grenade);
}
// END JOSEPH
	
void fire_grenade2 (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius, qboolean held)
{
	edict_t	*grenade;
	vec3_t	dir;
	vec3_t	forward, right, up;

	vectoangles (aimdir, dir);
	AngleVectors (dir, forward, right, up);

	grenade = G_Spawn();
	VectorCopy (start, grenade->s.origin);
	VectorScale (aimdir, speed, grenade->velocity);
	VectorMA (grenade->velocity, 200 + crandom() * 10.0, up, grenade->velocity);
	VectorMA (grenade->velocity, crandom() * 10.0, right, grenade->velocity);
	VectorSet (grenade->avelocity, 300, 300, 300);
	grenade->movetype = MOVETYPE_BOUNCE;
	grenade->clipmask = MASK_SHOT;
	grenade->solid = SOLID_BBOX;
	grenade->s.effects |= EF_GRENADE;
	VectorClear (grenade->mins);
	VectorClear (grenade->maxs);
	grenade->s.modelindex = gi.modelindex ("models/objects/grenade2/tris.md2");
	grenade->owner = self;
	grenade->touch = Grenade_Touch;
	grenade->nextthink = level.time + timer;
	grenade->think = Grenade_Explode;
	grenade->dmg = damage;
	grenade->dmg_radius = damage_radius;
	grenade->classname = "hgrenade";
	if (held)
		grenade->spawnflags = 3;
	else
		grenade->spawnflags = 1;
	grenade->s.sound = gi.soundindex("weapons/grenade_launcher/hgrenc1b.wav");

	if (timer <= 0.0)
		Grenade_Explode (grenade);
	else
	{
		gi.sound (self, CHAN_WEAPON, gi.soundindex ("weapons/grenade_launcher/hgrent1a.wav"), 1, ATTN_NORM, 0);
		gi.linkentity (grenade);
	}
}



/*
=================
fire_rocket
=================
*/
void rocket_touch (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t		origin, vec;

	if (other == ent->owner)
		return;

	if (surf && (surf->flags & SURF_SKY))
	{
		G_FreeEdict (ent);
		return;
	}

	if (ent->owner->client)
		PlayerNoise(ent->owner, ent->s.origin, PNOISE_IMPACT);

	// calculate position for the explosion entity
	VectorMA (ent->s.origin, -0.02, ent->velocity, origin);

	if (other->takedamage)
	{
		T_Damage (other, ent, ent->owner, ent->velocity, ent->s.origin, plane->normal, ent->dmg, ent->dmg, 0, MOD_ROCKET);
	}
	else
	{
/*
		// don't throw any debris in net games
		if (!deathmatch->value && !coop->value)
		{
			if ((surf) && !(surf->flags & (SURF_WARP|SURF_TRANS33|SURF_TRANS66|SURF_FLOWING)))
			{
				n = rand() % 5;
				while(n--)
					ThrowDebris (ent, "models/props/glass/glass2.md2", 2, ent->s.origin);
			}
		}
*/
	}

	T_RadiusDamage(ent, ent->owner, ent->radius_dmg, other, ent->dmg_radius, MOD_R_SPLASH);

	gi.WriteByte (svc_temp_entity);

	if (other->takedamage || !plane)
	{
		VectorSubtract( ent->s.origin, other->s.origin, vec );
		VectorNormalize( vec );
	}
	else
	{
		VectorCopy( plane->normal, vec );
	}

	if (ent->waterlevel)
	{
		gi.WriteByte (TE_CONCUSSION_EXPLOSION_WATER);
	}
	else
	{
		gi.WriteByte (TE_CONCUSSION_EXPLOSION);
	}
	gi.WritePosition (origin);
	gi.WriteDir( vec );
	gi.WriteByte( (int)(ent->dmg / 2) );
	gi.multicast (ent->s.origin, MULTICAST_PHS);
/*
	gi.WriteByte (svc_temp_entity);
	if (ent->waterlevel)
		gi.WriteByte (TE_ROCKET_EXPLOSION_WATER);
	else
		gi.WriteByte (TE_ROCKET_EXPLOSION);
	gi.WritePosition (origin);
	gi.multicast (ent->s.origin, MULTICAST_PHS);
*/
	G_FreeEdict (ent);
}

void rocket_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	rocket_touch( self, self, NULL, NULL );
}


void fire_rocket (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius, int radius_damage)
{
	edict_t	*rocket;

	rocket = G_Spawn();
	VectorCopy (start, rocket->s.origin);
	VectorCopy (dir, rocket->movedir);
	vectoangles (dir, rocket->s.angles);
	VectorScale (dir, speed, rocket->velocity);
	rocket->movetype = MOVETYPE_FLYMISSILE;
	rocket->clipmask = MASK_SHOT;
	rocket->solid = SOLID_BBOX;
	rocket->s.effects |= EF_ROCKET;
	VectorClear (rocket->mins);
	VectorClear (rocket->maxs);
	// JOSEPH 24-FEB-99
	rocket->s.modelindex = gi.modelindex ("models/weapons/shella/tris.md2");
	rocket->s.renderfx2 |= RF2_NOSHADOW;	
	// END JOSEPH
	rocket->owner = self;
	rocket->touch = rocket_touch;
	rocket->nextthink = level.time + 8000/speed;
	rocket->think = G_FreeEdict;
	rocket->dmg = damage;
	rocket->radius_dmg = radius_damage;
	rocket->dmg_radius = damage_radius;
	// JOSEPH 29-MAR-99
	//rocket->s.sound = gi.soundindex ("weapons/bazooka/rockfly.wav");
	// END JOSEPH
	rocket->classname = "rocket";

	rocket->health = 10;
	rocket->takedamage = DAMAGE_YES;
	rocket->die = rocket_die;

	PlayerNoise(self, start, PNOISE_WEAPON);

	// gi.sound (self, CHAN_WEAPON, gi.soundindex ("weapons/bazooka/baz_fire.wav"), 1, ATTN_NORM, 0);

	if (self->client)
		check_dodge (self, rocket->s.origin, dir, speed);

	gi.linkentity (rocket);
}


/*
=================
fire_rail
=================
*/
void fire_rail (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick)
{
	vec3_t		from;
	vec3_t		end;
	trace_t		tr;
	edict_t		*ignore;
	int			mask;
	qboolean	water;

	VectorMA (start, 8192, aimdir, end);
	VectorCopy (start, from);
	ignore = self;
	water = false;
	mask = MASK_SHOT|CONTENTS_SLIME|CONTENTS_LAVA;
	while (ignore)
	{
		tr = gi.trace (from, NULL, NULL, end, ignore, mask);

		if (tr.contents & (CONTENTS_SLIME|CONTENTS_LAVA))
		{
			mask &= ~(CONTENTS_SLIME|CONTENTS_LAVA);
			water = true;
		}
		else
		{
			if ((tr.ent->svflags & SVF_MONSTER) || (tr.ent->client))
				ignore = tr.ent;
			else
				ignore = NULL;

			if ((tr.ent != self) && (tr.ent->takedamage))
				T_Damage (tr.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, kick, 0, MOD_RAILGUN);
		}

		VectorCopy (tr.endpos, from);
	}

	// send gun puff / flash
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_RAILTRAIL);
	gi.WritePosition (start);
	gi.WritePosition (tr.endpos);
	gi.WriteDir (tr.plane.normal);
	gi.multicast (self->s.origin, MULTICAST_PHS);

	if (self->client)
		PlayerNoise(self, tr.endpos, PNOISE_IMPACT);
}


/*
=================
fire_bfg
=================
*/
void bfg_explode (edict_t *self)
{
	edict_t	*ent;
	float	points;
	vec3_t	v;
	float	dist;

	if (self->s.frame == 0)
	{
		// the BFG effect
		ent = NULL;
		while ((ent = findradius(ent, self->s.origin, self->dmg_radius)) != NULL)
		{
			if (!ent->takedamage)
				continue;
			if (ent == self->owner)
				continue;
			if (!CanDamage (ent, self))
				continue;
			if (!CanDamage (ent, self->owner))
				continue;

			VectorAdd (ent->mins, ent->maxs, v);
			VectorMA (ent->s.origin, 0.5, v, v);
			VectorSubtract (self->s.origin, v, v);
			dist = VectorLength(v);
			points = self->radius_dmg * (1.0 - sqrt(dist/self->dmg_radius));
			if (ent == self->owner)
				points = points * 0.5;

			gi.WriteByte (svc_temp_entity);
			gi.WriteByte (TE_BFG_EXPLOSION);
			gi.WritePosition (ent->s.origin);
			gi.multicast (ent->s.origin, MULTICAST_PHS);
			T_Damage (ent, self, self->owner, self->velocity, ent->s.origin, vec3_origin, (int)points, 0, DAMAGE_ENERGY, MOD_BFG_EFFECT);
		}
	}

	self->nextthink = level.time + FRAMETIME;
	self->s.frame++;
	if (self->s.frame == 5)
		self->think = G_FreeEdict;
}

void bfg_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (other == self->owner)
		return;

	if (surf && (surf->flags & SURF_SKY))
	{
		G_FreeEdict (self);
		return;
	}

	if (self->owner->client)
		PlayerNoise(self->owner, self->s.origin, PNOISE_IMPACT);

	// core explosion - prevents firing it into the wall/floor
	if (other->takedamage)
		T_Damage (other, self, self->owner, self->velocity, self->s.origin, plane->normal, 200, 0, 0, MOD_BFG_BLAST);
	T_RadiusDamage(self, self->owner, 200, other, 100, MOD_BFG_BLAST);

	gi.sound (self, CHAN_VOICE, gi.soundindex ("weapons/bfg__x1b.wav"), 1, ATTN_NORM, 0);
	self->solid = SOLID_NOT;
	self->touch = NULL;
	VectorMA (self->s.origin, -1 * FRAMETIME, self->velocity, self->s.origin);
	VectorClear (self->velocity);
	self->s.modelindex = gi.modelindex ("sprites/s_bfg3.sp2");
	self->s.frame = 0;
	self->s.sound = 0;
	self->s.effects &= ~EF_ANIM_ALLFAST;
	self->think = bfg_explode;
	self->nextthink = level.time + FRAMETIME;
	self->enemy = other;

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_BFG_BIGEXPLOSION);
	gi.WritePosition (self->s.origin);
	gi.multicast (self->s.origin, MULTICAST_PVS);
}


void bfg_think (edict_t *self)
{
	edict_t	*ent;
	edict_t	*ignore;
	vec3_t	point;
	vec3_t	dir;
	vec3_t	start;
	vec3_t	end;
	int		dmg;
	trace_t	tr;

	if (deathmatch->value)
		dmg = 5;
	else
		dmg = 10;

	ent = NULL;
	while ((ent = findradius(ent, self->s.origin, 256)) != NULL)
	{
		if (ent == self)
			continue;

		if (ent == self->owner)
			continue;

		if (!ent->takedamage)
			continue;

		if (!(ent->svflags & SVF_MONSTER) && (!ent->client) && (strcmp(ent->classname, "misc_explobox") != 0))
			continue;

		VectorMA (ent->absmin, 0.5, ent->size, point);

		VectorSubtract (point, self->s.origin, dir);
		VectorNormalize (dir);

		ignore = self;
		VectorCopy (self->s.origin, start);
		VectorMA (start, 2048, dir, end);
		while(1)
		{
			tr = gi.trace (start, NULL, NULL, end, ignore, CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_DEADMONSTER);

			if (!tr.ent)
				break;

			// hurt it if we can
			if ((tr.ent->takedamage) && !(tr.ent->flags & FL_IMMUNE_LASER) && (tr.ent != self->owner))
				T_Damage (tr.ent, self, self->owner, dir, tr.endpos, vec3_origin, dmg, 1, DAMAGE_ENERGY, MOD_BFG_LASER);

			// if we hit something that's not a monster or player we're done
			if (!(tr.ent->svflags & SVF_MONSTER) && (!tr.ent->client))
			{
				gi.WriteByte (svc_temp_entity);
				gi.WriteByte (TE_LASER_SPARKS);
				gi.WriteByte (4);
				gi.WritePosition (tr.endpos);
				gi.WriteDir (tr.plane.normal);
				gi.WriteByte (self->s.skinnum);
				gi.multicast (tr.endpos, MULTICAST_PVS);
				break;
			}

			ignore = tr.ent;
			VectorCopy (tr.endpos, start);
		}

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_BFG_LASER);
		gi.WritePosition (self->s.origin);
		gi.WritePosition (tr.endpos);
		gi.multicast (self->s.origin, MULTICAST_PHS);
	}

	self->nextthink = level.time + FRAMETIME;
}


void fire_bfg (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius)
{
	edict_t	*bfg;

	bfg = G_Spawn();
	VectorCopy (start, bfg->s.origin);
	VectorCopy (dir, bfg->movedir);
	vectoangles (dir, bfg->s.angles);
	VectorScale (dir, speed, bfg->velocity);
	bfg->movetype = MOVETYPE_FLYMISSILE;
	bfg->clipmask = MASK_SHOT;
	bfg->solid = SOLID_BBOX;
	bfg->s.effects |= EF_BFG | EF_ANIM_ALLFAST;
	VectorClear (bfg->mins);
	VectorClear (bfg->maxs);
	bfg->s.modelindex = gi.modelindex ("sprites/s_bfg1.sp2");
	bfg->owner = self;
	bfg->touch = bfg_touch;
	bfg->nextthink = level.time + 8000/speed;
	bfg->think = G_FreeEdict;
	bfg->radius_dmg = damage;
	bfg->dmg_radius = damage_radius;
	bfg->classname = "bfg blast";
	bfg->s.sound = gi.soundindex ("weapons/bfg__l1a.wav");

	bfg->think = bfg_think;
	bfg->nextthink = level.time + FRAMETIME;
	bfg->teammaster = bfg;
	bfg->teamchain = NULL;

	if (self->client)
		check_dodge (self, bfg->s.origin, dir, speed);

	gi.linkentity (bfg);
}


// RAFAEL

/*
	fire_ionripper
*/

void ionripper_sparks (edict_t *self)
{
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_WELDING_SPARKS);
	gi.WriteByte (0);
	gi.WritePosition (self->s.origin);
	gi.WriteDir (vec3_origin);
	gi.WriteByte (0xe4 + (rand()&3));
	gi.multicast (self->s.origin, MULTICAST_PVS);

	G_FreeEdict (self);
}

// RAFAEL
void ionripper_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (other == self->owner)
		return;

	if (surf && (surf->flags & SURF_SKY))
	{
		G_FreeEdict (self);
		return;
	}

	if (self->owner->client)
			PlayerNoise (self->owner, self->s.origin, PNOISE_IMPACT);

	if (other->takedamage)
	{
		T_Damage (other, self, self->owner, self->velocity, self->s.origin, plane->normal, self->dmg, 1, DAMAGE_ENERGY, MOD_RIPPER);

	}
	else
	{
		return;
	}

	G_FreeEdict (self);
}

/*
// RAFAEL
void fire_ionripper (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int effect)
{
	edict_t *ion;
	trace_t tr;

	VectorNormalize (dir);

	ion = G_Spawn ();
	VectorCopy (start, ion->s.origin);
	VectorCopy (start, ion->s.old_origin);
	vectoangles (dir, ion->s.angles);
	VectorScale (dir, speed, ion->velocity);

	ion->movetype = MOVETYPE_WALLBOUNCE;
	ion->clipmask = MASK_SHOT;
	ion->solid = SOLID_BBOX;
	ion->s.effects |= effect;

	ion->s.renderfx |= RF_FULLBRIGHT;

	VectorClear (ion->mins);
	VectorClear (ion->maxs);
	ion->s.modelindex = gi.modelindex ("models/objects/boomrang/tris.md2");
	ion->s.sound = gi.soundindex ("misc/lasfly.wav");
	ion->owner = self;
	ion->touch = ionripper_touch;
	ion->nextthink = level.time + 3;
	ion->think = ionripper_sparks;
	ion->dmg = damage;
	ion->dmg_radius = 100;
	gi.linkentity (ion);

	if (self->client)
		check_dodge (self, ion->s.origin, dir, speed);

	tr = gi.trace (self->s.origin, NULL, NULL, ion->s.origin, ion, MASK_SHOT);
	if (tr.fraction < 1.0)
	{
		VectorMA (ion->s.origin, -10, dir, ion->s.origin);
		ion->touch (ion, tr.ent, NULL, NULL);
	}

}
*/

// RAFAEL
/*
fire_heat
*/


void heat_think (edict_t *self)
{
	edict_t		*target = NULL;
	edict_t		*aquire = NULL;
	vec3_t		vec;
	vec3_t		oldang;
	int			len;
	int			oldlen = 0;

	VectorClear (vec);

	// aquire new target
	while (( target = findradius (target, self->s.origin, 1024)) != NULL)
	{
		
		if (self->owner == target)
			continue;
		// JOSEPH 14-MAY-99
		if (!(target->svflags & SVF_MONSTER))
			continue;
		// END JOSEPH
		if (!target->client)
			continue;
		if (target->health <= 0)
			continue;
		if (!visible (self, target))
			continue;
		
		// if we need to reduce the tracking cone
		/*
		{
			vec3_t	vec;
			float	dot;
			vec3_t	forward;
	
			AngleVectors (self->s.angles, forward, NULL, NULL);
			VectorSubtract (target->s.origin, self->s.origin, vec);
			VectorNormalize (vec);
			dot = DotProduct (vec, forward);
	
			if (dot > 0.6)
				continue;
		}
		*/

		if (!infront (self, target))
			continue;

		VectorSubtract (self->s.origin, target->s.origin, vec);
		len = VectorLength (vec);

		if (aquire == NULL || len < oldlen)
		{
			aquire = target;
			self->target_ent = aquire;
			oldlen = len;
		}
	}

	if (aquire != NULL)
	{
		VectorCopy (self->s.angles, oldang);
		VectorSubtract (aquire->s.origin, self->s.origin, vec);
		
		vectoangles (vec, self->s.angles);
		
		VectorNormalize (vec);
		VectorCopy (vec, self->movedir);
		VectorScale (vec, 500, self->velocity);
	}

	self->nextthink = level.time + 0.1;
}

// RAFAEL
void fire_heat (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius, int radius_damage)
{
	edict_t *heat;

	heat = G_Spawn();
	VectorCopy (start, heat->s.origin);
	VectorCopy (dir, heat->movedir);
	vectoangles (dir, heat->s.angles);
	VectorScale (dir, speed, heat->velocity);
	heat->movetype = MOVETYPE_FLYMISSILE;
	heat->clipmask = MASK_SHOT;
	heat->solid = SOLID_BBOX;
	heat->s.effects |= EF_ROCKET;
	VectorClear (heat->mins);
	VectorClear (heat->maxs);
	heat->s.modelindex = gi.modelindex ("models/objects/rocket/tris.md2");
	heat->owner = self;
	heat->touch = rocket_touch;

	heat->nextthink = level.time + 0.1;
	heat->think = heat_think;
	
	heat->dmg = damage;
	heat->radius_dmg = radius_damage;
	heat->dmg_radius = damage_radius;
	// JOSEPH 29-MAR-99
	//heat->s.sound = gi.soundindex ("weapons/rocket_launcher/rockfly.wav");
	// END JOSEPH

	if (self->client)
		check_dodge (self, heat->s.origin, dir, speed);

	gi.linkentity (heat);
}



// RAFAEL

/*
	fire_plasma
*/

void plasma_touch (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t		origin;

	if (other == ent->owner)
		return;

	if (surf && (surf->flags & SURF_SKY))
	{
		G_FreeEdict (ent);
		return;
	}

	if (ent->owner->client)
		PlayerNoise(ent->owner, ent->s.origin, PNOISE_IMPACT);

	// calculate position for the explosion entity
	VectorMA (ent->s.origin, -0.02, ent->velocity, origin);

	if (other->takedamage)
	{
		T_Damage (other, ent, ent->owner, ent->velocity, ent->s.origin, plane->normal, ent->dmg, 0, 0, MOD_PHALANX);
	}
	
	T_RadiusDamage(ent, ent->owner, ent->radius_dmg, other, ent->dmg_radius, MOD_PHALANX);

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_PLASMA_EXPLOSION);
	gi.WritePosition (origin);
	gi.multicast (ent->s.origin, MULTICAST_PVS);
	
	G_FreeEdict (ent);
}


// RAFAEL
void fire_plasma (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius, int radius_damage)
{
	edict_t *plasma;

	plasma = G_Spawn();
	VectorCopy (start, plasma->s.origin);
	VectorCopy (dir, plasma->movedir);
	vectoangles (dir, plasma->s.angles);
	VectorScale (dir, speed, plasma->velocity);
	plasma->movetype = MOVETYPE_FLYMISSILE;
	plasma->clipmask = MASK_SHOT;
	plasma->solid = SOLID_BBOX;

	VectorClear (plasma->mins);
	VectorClear (plasma->maxs);
	
	plasma->owner = self;
	plasma->touch = plasma_touch;
	plasma->nextthink = level.time + 8000/speed;
	plasma->think = G_FreeEdict;
	plasma->dmg = damage;
	plasma->radius_dmg = radius_damage;
	plasma->dmg_radius = damage_radius;
	// JOSEPH 29-MAR-99
	//plasma->s.sound = gi.soundindex ("weapons/rocket_launcher/rockfly.wav");
	// END JOSEPH
	
	plasma->s.modelindex = gi.modelindex ("sprites/s_photon.sp2");
	plasma->s.effects |= EF_PLASMA | EF_ANIM_ALLFAST;
	
	if (self->client)
		check_dodge (self, plasma->s.origin, dir, speed);

	gi.linkentity (plasma);

	
}

// RAFAEL
extern void SP_item_foodcube (edict_t *best);
// RAFAEL
static void Trap_Think (edict_t *ent)
{
	edict_t	*target = NULL;
	edict_t	*best = NULL;
	vec3_t	vec;
	int		len, i;
	int		oldlen = 8000;
	vec3_t	forward, right, up;
	
	if (ent->timestamp < level.time)
	{
		BecomeExplosion1(ent);
		// note to self
		// cause explosion damage???
		return;
	}
	
	ent->nextthink = level.time + 0.1;
	
	if (!ent->groundentity)
		return;

	// ok lets do the blood effect
	if (ent->s.frame > 4)
	{
		if (ent->s.frame == 5)
		{
			if (ent->wait == 64)
				gi.sound(ent, CHAN_VOICE, gi.soundindex ("weapons/trapdown.wav"), 1, ATTN_IDLE, 0);

			ent->wait -= 2;
			ent->delay += level.time;

			for (i=0; i<3; i++)
			{
				
				best = G_Spawn();

				if (strcmp (ent->enemy->classname, "monster_gekk") == 0)
				{
					best->s.modelindex = gi.modelindex ("models/objects/gekkgib/torso/tris.md2");	
					best->s.effects |= TE_GREENBLOOD;
				}
				else if (ent->mass > 200)
				{
					best->s.modelindex = gi.modelindex ("models/objects/gibs/chest/tris.md2");	
					best->s.effects |= TE_BLOOD;
				}
				else
				{
					best->s.modelindex = gi.modelindex ("models/objects/gibs/sm_meat/tris.md2");	
					best->s.effects |= TE_BLOOD;
				}

				AngleVectors (ent->s.angles, forward, right, up);
				
				RotatePointAroundVector( vec, up, right, ((360.0/3)* i)+ent->delay);
				VectorMA (vec, ent->wait/2, vec, vec);
				VectorAdd(vec, ent->s.origin, vec);
				VectorAdd(vec, forward, best->s.origin);
  
				best->s.origin[2] = ent->s.origin[2] + ent->wait;
				
				VectorCopy (ent->s.angles, best->s.angles);
  
				best->solid = SOLID_NOT;
				best->s.effects |= EF_GIB;
				best->takedamage = DAMAGE_YES;
		
				best->movetype = MOVETYPE_TOSS;
				best->svflags |= SVF_MONSTER;
				best->deadflag = DEAD_DEAD;
		  
				VectorClear (best->mins);
				VectorClear (best->maxs);

				best->watertype = gi.pointcontents(best->s.origin);
				if (best->watertype & MASK_WATER)
					best->waterlevel = 1;

				best->nextthink = level.time + 0.1;
				best->think = G_FreeEdict;
				gi.linkentity (best);
			}
				
			if (ent->wait < 19)
				ent->s.frame ++;

			return;
		}
		ent->s.frame ++;
		if (ent->s.frame == 8)
		{
			ent->nextthink = level.time + 1.0;
			ent->think = G_FreeEdict;

			best = G_Spawn ();
			SP_item_foodcube (best);
			VectorCopy (ent->s.origin, best->s.origin);
			best->s.origin[2]+= 16;
			best->velocity[2] = 400;
			best->count = ent->mass;
			gi.linkentity (best);
			return;
		}
		return;
	}
	
	ent->s.effects &= ~EF_TRAP;
	if (ent->s.frame >= 4)
	{
		ent->s.effects |= EF_TRAP;
		VectorClear (ent->mins);
		VectorClear (ent->maxs);

	}

	if (ent->s.frame < 4)
		ent->s.frame++;

	while ((target = findradius(target, ent->s.origin, 256)) != NULL)
	{
		if (target == ent)
			continue;
		if (!(target->svflags & SVF_MONSTER) && !target->client)
			continue;
		if (target == ent->owner)
			continue;
		if (target->health <= 0)
			continue;
		if (!visible (ent, target))
		 	continue;
		if (!best)
		{
			best = target;
			continue;
		}
		VectorSubtract (ent->s.origin, target->s.origin, vec);
		len = VectorLength (vec);
		if (len < oldlen)
		{
			oldlen = len;
			best = target;
		}
	}

	// pull the enemy in
	if (best)
	{
		vec3_t	forward;

		if (best->groundentity)
		{
			best->s.origin[2] += 1;
			best->groundentity = NULL;
		}
		VectorSubtract (ent->s.origin, best->s.origin, vec);
		len = VectorLength (vec);
		if (best->client)
		{
			VectorNormalize (vec);
			VectorMA (best->velocity, 250, vec, best->velocity);
		}
		else
		{
			best->ideal_yaw = vectoyaw(vec);	
			M_ChangeYaw (best);
			AngleVectors (best->s.angles, forward, NULL, NULL);
			VectorScale (forward, 256, best->velocity);
		}

		gi.sound(ent, CHAN_VOICE, gi.soundindex ("weapons/trapsuck.wav"), 1, ATTN_IDLE, 0);
		
		if (len < 32)
		{	
			if (best->mass < 400)
			{
				T_Damage (best, ent, ent, vec3_origin, best->s.origin, vec3_origin, 100000, 1, 0, MOD_TRAP);
				ent->enemy = best;
				ent->wait = 64;
				VectorCopy (ent->s.origin, ent->s.old_origin);
				ent->timestamp = level.time + 30;
				ent->mass = best->mass/4;
				// ok spawn the food cube
				ent->s.frame = 5;	
			}
			else
			{
				BecomeExplosion1(ent);
				// note to self
				// cause explosion damage???
				return;
			}
				
		}
	}

		
}


// RAFAEL
void fire_trap (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius, qboolean held)
{
	edict_t	*trap;
	vec3_t	dir;
	vec3_t	forward, right, up;

	vectoangles (aimdir, dir);
	AngleVectors (dir, forward, right, up);

	trap = G_Spawn();
	VectorCopy (start, trap->s.origin);
	VectorScale (aimdir, speed, trap->velocity);
	VectorMA (trap->velocity, 200 + crandom() * 10.0, up, trap->velocity);
	VectorMA (trap->velocity, crandom() * 10.0, right, trap->velocity);
	VectorSet (trap->avelocity, 0, 300, 0);
	trap->movetype = MOVETYPE_BOUNCE;
	trap->clipmask = MASK_SHOT;
	trap->solid = SOLID_BBOX;
//	VectorClear (trap->mins);
//	VectorClear (trap->maxs);
	VectorSet (trap->mins, -4, -4, 0);
	VectorSet (trap->maxs, 4, 4, 8);
	trap->s.modelindex = gi.modelindex ("models/weapons/z_trap/tris.md2");
	trap->owner = self;
	trap->nextthink = level.time + 1.0;
	trap->think = Trap_Think;
	trap->dmg = damage;
	trap->dmg_radius = damage_radius;
	trap->classname = "htrap";
	// RAFAEL 16-APR-98
	trap->s.sound = gi.soundindex ("weapons/traploop.wav");
	// END 16-APR-98
	if (held)
		trap->spawnflags = 3;
	else
		trap->spawnflags = 1;
	
	if (timer <= 0.0)
		Grenade_Explode (trap);
	else
	{
		// gi.sound (self, CHAN_WEAPON, gi.soundindex ("weapons/trapdown.wav"), 1, ATTN_NORM, 0);
		gi.linkentity (trap);
	}
	
	trap->timestamp = level.time + 30;

}

//----------------------------------------------------------------------------------------------------
// Flame-Thrower

// copied from CL_FlameEffects()
#define FLAME_SPEED			750.0		// increase to make it longer
#define FLAME_INC			0.6 	// decrease to spawn more flame sprites (more overlapping)
#define	FLAME_RAND_SIZE		0.3		// range from 0.0 -> 2.0
#define	FLAME_RAND_ALPHA	0.3		// range from 0.0 -> 2.0
#define	FLAME_START_OFFSET	24.0
#define	FLAME_LIFETIME		0.8
#define	FLAME_BLUE_LENGTH	42.0

static vec3_t	jmins = {-16, -16,   0};
static vec3_t	jmaxs = { 16,  16,  24};

void FlameJunc_Think( edict_t *self )
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
				if (VectorDistance( last_pos, tr.endpos ) < (32 * (deathmatch->value+1)))
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

//	if (self->biketime < level.time)
	{
		T_RadiusDamage( self, self->owner, self->dmg * (deathmatch->value ? 3 : 1), NULL, 128, MOD_FLAMETHROWER );
		self->biketime = level.time;
	}

	if (self->timestamp <= level.time)
	{
		G_FreeEdict( self );
		return;
	}

	self->nextthink = level.time + 0.1;
}

// JOSEPH 23-OCT-98
void fire_flamethrower (edict_t *self, vec3_t start, vec3_t forward, int damage, int kick, int mod)
{

	trace_t tr;
	vec3_t	end, xforward, xright, xup, dir;
	vec3_t	org, oldorg;
//	float r, u;
	edict_t	*junc;

	static vec3_t	mins = {-2, -2, -4};
	static vec3_t	maxs = { 2,  2,  4};


	if (self->waterlevel > 1)
	{
//		gi.dprintf( "SOUND TODO: Flamethrower under water\n" );
		return;
	}


	vectoangles (forward, dir);
	AngleVectors (dir, xforward, xright, xup);

	// find the start position (using same as CL_FlameEffects() )
	VectorCopy( self->s.origin, org );
	org[2] -= 32;
	VectorMA	( org, FLAME_START_OFFSET, forward, org );
	VectorMA	( org, 7, xright, org );
	org[2] += 64.5;
	VectorMA	( org, -5.5, xup, org );

	VectorCopy( org, start );
	VectorMA( start, 8, xup, start );
	VectorMA ( start, (FLAME_SPEED*FLAME_LIFETIME), xforward, end );

	
	tr = gi.trace (start, mins, maxs, end, self, MASK_SOLID);

	PlayerNoise(self, start, PNOISE_WEAPON);

	if (!(self->svflags & SVF_MONSTER))
	{
		if (tr.startsolid || tr.fraction * FLAME_SPEED * FLAME_LIFETIME < 32)	// hurt self
		{
			if (tr.ent->takedamage)
				T_Damage (tr.ent, self, self, forward, self->s.origin, vec3_origin, damage, kick, 10, mod);

			T_Damage (self, self, self, forward, self->s.origin, vec3_origin, damage, kick, 10, mod);
			gi.sound (self, CHAN_BODY, gi.soundindex ("world/fire.wav"), 1, ATTN_NORM, 0);
			return;
		}
	}

	// Spawn a junction
	junc = G_Spawn();
	VectorMA( org, 0, forward, junc->s.origin );
	VectorMA( junc->s.origin, -4, xup, junc->s.origin );
	VectorMA( junc->s.origin, 3, xright, junc->s.origin );
	VectorScale( forward, FLAME_SPEED, junc->velocity );
	VectorCopy( forward, junc->last_step_pos );			// last_step_pos is unit vel

	// move it to the fadein position
	VectorCopy( junc->s.origin, oldorg );
	VectorMA( junc->s.origin, (FLAME_BLUE_LENGTH/FLAME_SPEED) * 2.5, junc->velocity, junc->s.origin );

	// trace the spawning location
	tr = gi.trace ( oldorg, jmins, jmaxs, junc->s.origin, self, MASK_SOLID );

	VectorCopy( tr.endpos, junc->s.origin );

	junc->dmg = damage;
	junc->acc = 0;		// hit wall flag
	junc->biketime = 0;
	junc->owner = self;
	VectorCopy( junc->s.origin, junc->s.old_origin );

	junc->timestamp = level.time + FLAME_LIFETIME;

	junc->think = FlameJunc_Think;
	junc->nextthink = level.time + 0.1;


	if (self->svflags & SVF_MONSTER)
	{
		if (self->enemy) 
		{
			{
				float	dist;
				vec3_t	vec;

				VectorSubtract (self->s.origin, self->enemy->s.origin, vec);
				dist = VectorLength (vec);

				if (dist < 64)
					T_Damage (self->enemy, self, self, forward, self->s.origin, vec3_origin, 2, kick, 10, mod);
			}
		}
	}
/*
	if (!tr.ent->takedamage && (tr.fraction > 0.1))
	{
		trace_t	tr;
		vec3_t	mins, maxs;
		vec3_t	temp;

		VectorSet (mins, -16,-16,-16);
		VectorSet (maxs, 16,16,16);
		VectorCopy (self->s.origin, temp);
		temp[2] += 36;

		tr = gi.trace (temp, mins, maxs, end, self, MASK_SHOT);	

		if (strstr(tr.surface->name, "wood"))	// spawn some smoke
		{
			static vec3_t	last_pos;
			static float	last_time;

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
//			gi.WriteDir (tr.ent->s.angles);
			gi.WriteByte (48);
			gi.WriteByte (0);
			gi.multicast (tr.endpos, MULTICAST_PVS);
		}

skip_smoke:

		return;
	}
	else
	{
		gi.sound (self, CHAN_VOICE, gi.soundindex ("weapons/flame_thrower/flame_thr.wav"), 1, ATTN_NORM, 0);
	}

	if (tr.ent->health <= 0)
		return;

	// Ridah, no need to do area-based damage with Flamethrower (uses CPU and isn't as precise as a bullet is anyway)

	T_Damage (tr.ent, self, self, forward, tr.endpos, tr.plane.normal, damage, kick, 10, mod);

	if (tr.ent->svflags & SVF_MONSTER)
	{
		if (tr.ent->cast_info.catch_fire)
			tr.ent->cast_info.catch_fire( tr.ent, self );

		if (tr.ent->onfiretime < -20)
		{
			tr.ent->onfiretime = 1;

			if (!(strcmp (tr.ent->classname, "cast_bitch")))
				gi.sound(tr.ent, CHAN_VOICE, gi.soundindex("actors/bitch/death.wav"), 1, ATTN_NORM, 0);
			else
				gi.sound(tr.ent, CHAN_VOICE, gi.soundindex("actors/flamedeath2.wav"), 1, ATTN_NORM, 0);
		}

		if (tr.ent->onfiretime > 0)
		{
			if (self->client || self->svflags & SVF_MONSTER)
				tr.ent->onfireent = self;
			else
				tr.ent->onfireent = NULL;

			tr.ent->onfiretime = 100;
		}
		else
		{
			tr.ent->onfiretime -= 5;
		}
	}
*/
}
// END JOSEPH

static qboolean fire_concussion (edict_t *self, vec3_t start, vec3_t aimdir, float dist, int damage, int kick, int te_impact, int hspread, int vspread, int mod)
{
	trace_t		tr, mdx_tr;
	vec3_t		dir;
	vec3_t		forward, right, up;
	vec3_t		end;
	float		r;
	float		u;
	vec3_t		water_start/*, alpha_start*/;
	qboolean	water = false;
	// JOSEPH 10-JUN-99
	qboolean	water2 = false;
	// END JOSEPH
	int			content_mask = MASK_SHOT | MASK_WATER | MASK_ALPHA;
	int			len;
	//int			NoBulletHole;
	int			pointblank = 0;
//	vec3_t		tempvec;
	int			conweap = 0;
	qboolean	is_mdx = false;

	tr = gi.trace (self->s.origin, NULL, NULL, start, self, MASK_SHOT );
	if (!(tr.fraction < 1.0))
	{
		vectoangles (aimdir, dir);
		AngleVectors (dir, forward, right, up);

		r = crandom()*hspread;
		u = fabs(crandom()*vspread);

		VectorMA (start, dist, forward, end);
		VectorMA (end, r, right, end);
		VectorMA (end, u, up, end);

		if (gi.pointcontents (start) & MASK_WATER)
		{
			water = true;
			VectorCopy (start, water_start);
			content_mask &= ~MASK_WATER;
		}

		tr = gi.trace (start, NULL, NULL, end, self, content_mask);

		if (mod == MOD_BLACKJACK)
		{
			conweap = 1; 

			if (tr.ent->client)
			{
				if (infront( tr.ent, self ))
					tr.ent->client->kick_angles[0] = -damage;
				else	/// hit from behind
					tr.ent->client->kick_angles[0] =  damage;
			}
		}

		// JOSEPH 19-JAN-99
		if ((mod == MOD_BLACKJACK) || (mod == MOD_CROWBAR))
		{
			conweap = 1; 

			if (tr.ent->client)
			{
				if (infront( tr.ent, self ))
					tr.ent->client->kick_angles[0] = -damage;
				else	/// hit from behind
					tr.ent->client->kick_angles[0] =  damage;
			}
		}
		// END JOSEPH
		
		// see if we hit water
		if (tr.contents & MASK_WATER)
		{
			int		color;

			water = true;

			VectorCopy (tr.endpos, water_start);

			if (!VectorCompare (start, tr.endpos))
			{
				// JOSEPH 10-JUN-99
				water2 = true;
				// END JOSEPH				
				
				if (tr.contents & CONTENTS_WATER)
				{
					if (strcmp(tr.surface->name, "*brwater") == 0)
						color = SPLASH_BROWN_WATER;
					else
						color = SPLASH_BLUE_WATER;
				}
				else if (tr.contents & CONTENTS_SLIME)
					color = SPLASH_SLIME;
				else if (tr.contents & CONTENTS_LAVA)
					color = SPLASH_LAVA;
				else
					color = SPLASH_UNKNOWN;

				if (color != SPLASH_UNKNOWN)
				{
					gi.WriteByte (svc_temp_entity);
					gi.WriteByte (TE_SPLASH);
					gi.WriteByte (8);
					gi.WritePosition (tr.endpos);
					gi.WriteDir (tr.plane.normal);
					gi.WriteByte (color);
					gi.multicast (tr.endpos, MULTICAST_PVS);

				}

				if (color == SPLASH_BLUE_WATER)
				{
					// Ripple effect
					SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH, SFX_RIPPLE_HEIGHT,
											tr.ent, tr.endpos, tr.plane.normal );
					SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH<<1, SFX_RIPPLE_HEIGHT<<1,
											tr.ent, tr.endpos, tr.plane.normal );
					SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH>>1, SFX_RIPPLE_HEIGHT>>1,
											tr.ent, tr.endpos, tr.plane.normal );
				}
			}
		}
	}

	// send gun puff / flash
	if (!((tr.surface) && (tr.surface->flags & SURF_SKY)))
	{
		if (tr.fraction < 1.0)
		{
			
						// JOSEPH 4-DEC-98
			if (tr.ent->svflags & SVF_MONSTER || tr.ent->client)
			{

			}
			else if (mod != MOD_DOGBITE)
			{
				// JOSEPH 6-MAY-99
				if (tr.ent->svflags & SVF_PROP)
				{
					tr.surface->flags = tr.ent->surfacetype;
				}
				// END JOSEPH
				// JOSEPH 10-JUN-99
				if (water2)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("actors/player/male/watr_in.wav"), 1, ATTN_NORM, 0);
				}
				else if (tr.surface->flags & SURF_CONCRETE)
				// END JOSEPH	
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitcement.wav"), 1, ATTN_NORM, 0);			 
				}
				else if (tr.surface->flags & SURF_FABRIC)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitbody.wav"), 1, ATTN_NORM, 0);		 
				}
				else if (tr.surface->flags & SURF_GRAVEL)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitgravel.wav"), 1, ATTN_NORM, 0);		 
				}	
				else if (tr.surface->flags & SURF_METAL)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehittin.wav"), 1, ATTN_NORM, 0);		 
				}
				else if (tr.surface->flags & SURF_METAL_L)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehittin.wav"), 1, ATTN_NORM, 0);		 
				}
				else if (tr.surface->flags & SURF_SNOW)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehittin.wav"), 1, ATTN_NORM, 0);		 
				}	
				else if (tr.surface->flags & SURF_TILE)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehittile.wav"), 1, ATTN_NORM, 0); 
				}	
				else if (tr.surface->flags & SURF_WOOD)
				{
					gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitwood.wav"), 1, ATTN_NORM, 0);		 
				}	
				else
				{
					gi.sound (self, CHAN_VOICE, gi.soundindex ("weapons/melee/pipehitcement.wav"), 1, ATTN_NORM, 0);		 
				}

				PlayerNoise(self, start, PNOISE_WEAPON);

			}
			// END JOSEPH
		
			
			// NAV_DrawLine(start, tr.endpos);
			// gi.dprintf ("hit: %s\n", tr.ent->classname);
			
			if (tr.ent->takedamage)
			{
			    // Point blank range shot gives more damage 
				/*
				VectorSubtract (tr.endpos, self->s.origin, tempvec);	
		        len = VectorNormalize (tempvec);		
				if (len < 64)
				{
					damage *= 2;
					pointblank = 1;
				}
				*/

				// JOSEPH 11-APR-99
				if ((tr.ent->svflags & SVF_PROP) || (!strcmp(tr.ent->classname,"func_explosive")))
				{
						extern int ClipVelocity (vec3_t in, vec3_t normal, vec3_t out, float overbounce);
						vec3_t dir;

						VectorCopy( tr.plane.normal, dir );

						gi.WriteByte (svc_temp_entity);
						gi.WriteByte (TE_IMPACT_CONCUSSION);
						gi.WritePosition (tr.endpos);
						gi.WriteDir (dir);
						gi.multicast (tr.endpos, MULTICAST_PVS);
						
						if (self->client)
							PlayerNoise(self, tr.endpos, PNOISE_IMPACT);
				}
				// END JOSEPH

				// RAFAEL 7-30-98
				if (tr.ent->s.num_parts && !(tr.ent->client) && !(self->svflags & SVF_MONSTER))
				{
					// either way, react to this attempted hostility
					// JOSEPH 9-FEB-99
					if (!(tr.ent->svflags & SVF_PROP))
						M_ReactToDamage (tr.ent, self, damage ); 
					// END JOSEPH
					
					{
						trace_t		ignore;
						int			max_iterations=1;

						ignore = tr;
						
						while (max_iterations--)
						{

							mdx_tr = MDX_HitCheck (ignore.ent, self, self, aimdir, ignore.endpos, ignore.plane.normal, damage, kick, DAMAGE_BULLET, mod, end);
							
							if (mdx_tr.ent->flags & FL_MDXBBOX) // we hit an mdx_bbox
							{
								is_mdx = true;
								break;
							}
							else if (mdx_tr.ent->takedamage && mdx_tr.ent->s.num_parts) // we missed the mdx_bbox but hit another mdx
							{
								is_mdx = true;
								ignore = mdx_tr;
							}
							else if (mdx_tr.ent->takedamage) // we hit an md2
							{
								is_mdx = false;
								VectorCopy (mdx_tr.endpos, tr.endpos);
								VectorCopy (mdx_tr.plane.normal, tr.plane.normal);
								tr.ent = mdx_tr.ent;
								break;
							}
							// JOSEPH 5-FEB-99-B
							else if (tr.ent->svflags & SVF_PROP)
							{
								// this should fix the box episode 5/6 bug
								is_mdx = false;
								break;
							}
							// END JOSEPH
							else
							{
								// we missed
								VectorCopy (mdx_tr.endpos, tr.endpos);
								VectorCopy (mdx_tr.plane.normal, tr.plane.normal);
								goto bolt;
							}
						}
						if (is_mdx)
						{
							T_DamageMDX (tr.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, kick, DAMAGE_BULLET, mod, mdx_tr.ent->count, mdx_tr.ent->dmg); 
						
							gi.WriteByte (svc_muzzleflash);
							gi.WriteShort (self-g_edicts);
							gi.WriteByte (MZ_BLACKJACK_HIT);
							gi.multicast (self->s.origin, MULTICAST_PVS);

							// Head shot blood on close wall 
							// JOSEPH 25-JAN-99
							if ((mdx_tr.ent->count == PART_HEAD) && (!(tr.ent->svflags & SVF_PROP)))
							// END JOSEPH
							{
								trace_t		tr2;
								vec3_t		newstart, newdir, newend, travelvec;
																
								VectorCopy (tr.endpos, newstart);
								VectorSubtract (end, start, newdir);
								vectoangles (newdir, newdir);
								AngleVectors (newdir, forward, NULL, NULL);
								
								do
								{
									VectorMA (newstart, 8192, forward, newend);
									VectorMA (newstart, 4, forward, newstart);

									tr2 = gi.trace (newstart, NULL, NULL, newend, self, MASK_SHOT);
								}
								while (tr2.ent == tr.ent);
								
								VectorSubtract(newstart, tr2.endpos, travelvec);
								len = VectorNormalize(travelvec);
								
							    // this should be flaged not all concussion weapons will do this
								
								if ((len < 100.0) && (!tr2.ent->takedamage) &&
									((strncmp (tr2.surface->name, "sky", 3) != 0)))
								{
									if (pointblank)
									{
										SurfaceSpriteEffect(SFX_SPRITE_SURF_BLOOD1, SFX_BLOOD_WIDTH*4, 
															SFX_BLOOD_HEIGHT*4,
															tr2.ent, tr2.endpos, tr2.plane.normal );
									}
									else
									{
										SurfaceSpriteEffect(SFX_SPRITE_SURF_BLOOD1, SFX_BLOOD_WIDTH, 
															SFX_BLOOD_HEIGHT,
															tr2.ent, tr2.endpos, tr2.plane.normal );
									}
								}
							// JOSEPH 4-DEC-98
								gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehithead.wav"), 1, ATTN_NORM, 0);
							}
							else
							{
								gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitbody.wav"), 1, ATTN_NORM, 0);
							}
							// END JOSEPH
						}
						else
							T_Damage (tr.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, kick, DAMAGE_BULLET, mod); 
					}
					

				}
				else
				{
					
					qboolean check_skin_change = false;

					if (self->svflags & SVF_MONSTER && tr.ent->svflags & SVF_MONSTER && self->cast_group != tr.ent->cast_group)
					{	// Tweak: do more damage when AI shooting AI, more realistic
						damage *= 2;

						if (tr.ent->gender && !tr.ent->client)
						{
							check_skin_change = true;
						}
					}

					T_Damage (tr.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, kick, DAMAGE_BULLET, mod);

					if (check_skin_change)
					{
						ActorDamageSimpleSkinChangeCheck (tr.ent, tr.endpos);
					}

					if ((tr.ent->svflags & SVF_MONSTER || tr.ent->client))
					{
						if (mod != MOD_DOGBITE)
							gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitbody.wav"), 1, ATTN_NORM, 0);
// Ridah, 7-5-99, commented out for demo
//						else
//							gi.dprintf( "SOUND TODO: dog bite (flesh sound, not voice)\n" );
					}
				}
			}
			else
			{
bolt:
				// JOSEPH
				if ((strncmp (tr.surface->name, "sky", 3) != 0) /*|| NoBulletHole*/)
				{
					
					// JOSEPH 2-APR-99
					if (!is_mdx)
					{
						gi.WriteByte (svc_temp_entity);
						gi.WriteByte (TE_IMPACT_CONCUSSION);
						gi.WritePosition (tr.endpos);
						gi.WriteDir (tr.plane.normal);
						gi.multicast (tr.endpos, MULTICAST_PVS);
					}
					// END JOSEPH
					
					if (self->client)
						PlayerNoise(self, tr.endpos, PNOISE_IMPACT);

					// Ridah, surface sprites

					// SurfaceSpriteEffect(	SFX_SPRITE_SURF_BULLET1, SFX_BULLET_WIDTH * 5, SFX_BULLET_HEIGHT * 5,
					//						tr.ent, tr.endpos, tr.plane.normal );

//					SurfaceSpriteEffect(	SFX_SPRITE_SURF_BLOOD1, SFX_BLOOD_WIDTH, SFX_BLOOD_HEIGHT,
//											tr.ent, tr.endpos, tr.plane.normal );

					// we should leave a mark if it was the tire iron

					// done.
				}
			}
		}
	}


	// concussion can't possibly go through water rem out for now

	
	// if went through water, determine where the end and make a bubble trail

/*	
	if (water)
	{
		vec3_t	pos;

		VectorSubtract (tr.endpos, water_start, dir);
		
		VectorNormalize (dir);
		VectorMA (tr.endpos, -2, dir, pos);
		if (gi.pointcontents (pos) & MASK_WATER)
			VectorCopy (pos, tr.endpos);
		else
			tr = gi.trace (pos, NULL, NULL, water_start, tr.ent, MASK_WATER);

		VectorAdd (water_start, tr.endpos, pos);
		VectorScale (pos, 0.5, pos);

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_BUBBLETRAIL);
		gi.WritePosition (water_start);
		gi.WritePosition (tr.endpos);
		gi.multicast (pos, MULTICAST_PVS);
	}
*/

	if (is_mdx)
		return true;
	else 
		return false;

}

/*
=================
fire_dogbite
================
*/
qboolean fire_dogbite (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int mod)
{
	qboolean	rval;

	if (self->client)
		rval = fire_concussion (self, start, aimdir, 40, damage, kick, TE_GUNSHOT, 0, 0, mod);
	else
		rval = fire_concussion (self, start, aimdir, 40, damage, kick, TE_GUNSHOT, 0, 0, mod);

	return (rval);
}

// JOSEPH 30-APR-99
/*
=================
fire_rat
================
*/
void fire_rat (edict_t *self, vec3_t start, vec3_t aimdir, int damage)
{
	fire_concussion (self, start, aimdir, 40, damage, 1, TE_GUNSHOT, 0, 0, MOD_DOGBITE);
}
// END JOSEPH

/*
=================
fire_blackjack
================
*/
qboolean fire_blackjack (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int mod)
{
	qboolean	rval;

	if (self->client)
		rval = fire_concussion (self, start, aimdir, 48, damage, kick, TE_GUNSHOT, 0, 0, mod);
	else
		rval = fire_concussion (self, start, aimdir, 48, damage, kick, TE_GUNSHOT, 0, 0, mod);

	return (rval);
}

// JOSEPH 19-JAN-99
/*
=================
fire_crowbar
================
*/
qboolean fire_crowbar (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int mod)
{
	qboolean	rval;
	float		dist=48;

	if (deathmatch->value)	// Ridah, give it more range in deathmatch
		dist *= 1.5;

	if (self->client)
		rval = fire_concussion (self, start, aimdir, dist, damage, kick, TE_GUNSHOT, 0, 0, mod);
	else
		rval = fire_concussion (self, start, aimdir, dist, damage, kick, TE_GUNSHOT, 0, 0, mod);

	return (rval);
}
// END JOSEPH
