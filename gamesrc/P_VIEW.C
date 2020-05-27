#include "g_local.h"
#include "m_player.h"


static	edict_t		*current_player;
static	gclient_t	*current_client;

static	vec3_t	forward, right, up;
float	xyspeed;

float	bobmove;
int		bobcycle;		// odd cycles are right foot going forward
float	bobfracsin;		// sin(bobfrac*M_PI)

/*
===============
SV_CalcRoll

===============
*/
float SV_CalcRoll (vec3_t angles, vec3_t velocity)
{
	float	sign;
	float	side;
	float	value;
	
	side = DotProduct (velocity, right);
	sign = side < 0 ? -1 : 1;
	side = fabs(side);
	
	value = sv_rollangle->value;

	if (side < sv_rollspeed->value)
		side = side * value / sv_rollspeed->value;
	else
		side = value;

	return side*sign;
	
}


/*
===============
P_DamageFeedback

Handles color blends and view kicks
===============
*/
void P_DamageFeedback (edict_t *player)
{
	gclient_t	*client;
	float	side;
	float	realcount, count, kick;
	vec3_t	v;
	int		r, l;
	static	vec3_t	power_color = {0.0, 1.0, 0.0};
	static	vec3_t	acolor = {1.0, 1.0, 1.0};
	static	vec3_t	bcolor = {1.0, 0.0, 0.0};
	static	vec3_t	fcolor = {0.9, 0.6, 0.0};

	client = player->client;

	// flash the backgrounds behind the status numbers
	client->ps.stats[STAT_FLASHES] = 0;
	if (client->damage_blood || client->damage_flame)
		client->ps.stats[STAT_FLASHES] |= 1;
	if (client->damage_armor && !(player->flags & FL_GODMODE) && (client->invincible_framenum <= level.framenum))
		client->ps.stats[STAT_FLASHES] |= 2;

	// total points of damage shot at the player this frame
	count = (client->damage_blood + client->damage_flame + client->damage_armor + client->damage_parmor);
	if (count == 0)
		return;		// didn't take any damage
/*
	// start a pain animation if still in the player model
	if (client->anim_priority < ANIM_PAIN && player->s.modelindex == 255)
	{
		static int		i;

		client->anim_priority = ANIM_PAIN;
		if (client->ps.pmove.pm_flags & PMF_DUCKED)
		{
			player->s.frame = FRAME_crpain1-1;
			client->anim_end = FRAME_crpain4;
		}
		else
		{
			i = (i+1)%3;
			switch (i)
			{
			case 0:
				player->s.frame = FRAME_pain101-1;
				client->anim_end = FRAME_pain104;
				break;
			case 1:
				player->s.frame = FRAME_pain201-1;
				client->anim_end = FRAME_pain204;
				break;
			case 2:
				player->s.frame = FRAME_pain301-1;
				client->anim_end = FRAME_pain304;
				break;
			}
		}
	}
*/
	realcount = count;
	if (count < 10)
		count = 10;	// always make a visible effect

	// play an apropriate pain sound
	if ((level.time > player->pain_debounce_time) && !(player->flags & FL_GODMODE) && (client->invincible_framenum <= level.framenum))
	{
		r = 1 + (rand()&1);
		player->pain_debounce_time = level.time + 0.7;
		if (player->health < 25)
			l = 25;
		else if (player->health < 50)
			l = 50;
		else if (player->health < 75)
			l = 75;
		else
			l = 100;
		gi.sound (player, CHAN_VOICE, gi.soundindex(va("*pain%i_%i.wav", l, r)), 1, ATTN_NORM, 0);
	}

	// the total alpha of the blend is always proportional to count
	if (client->damage_alpha < 0)
		client->damage_alpha = 0;
	client->damage_alpha += count*0.01;
	if (client->damage_alpha < 0.2)
		client->damage_alpha = 0.2;
	if (client->damage_alpha > 0.6)
		client->damage_alpha = 0.6;		// don't go too saturated

	// the color of the blend will vary based on how much was absorbed
	// by different armors
	VectorClear (v);
	if (client->damage_parmor)
		VectorMA (v, (float)client->damage_parmor/realcount, power_color, v);
	if (client->damage_armor)
		VectorMA (v, (float)client->damage_armor/realcount,  acolor, v);
	if (client->damage_blood)
		VectorMA (v, (float)client->damage_blood/realcount,  bcolor, v);
	if (client->damage_flame)
	{
		VectorMA (v, (float)client->damage_flame/realcount,  fcolor, v);
		client->damage_alpha = 1.0;
	}
	VectorCopy (v, client->damage_blend);


	//
	// calculate view angle kicks
	//
	kick = abs(client->damage_knockback);
	if (kick && player->health > 0)	// kick of 0 means no view adjust at all
	{
		kick = kick * 100 / player->health;

		if (kick < count*0.5)
			kick = count*0.5;
		if (kick > 50)
			kick = 50;

		VectorSubtract (client->damage_from, player->s.origin, v);
		VectorNormalize (v);
		
		side = DotProduct (v, right);
		client->v_dmg_roll = kick*side*0.3;
		
		side = -DotProduct (v, forward);
		client->v_dmg_pitch = kick*side*0.3;

		client->v_dmg_time = level.time + DAMAGE_TIME;
	}

	//
	// clear totals
	//
	client->damage_blood = 0;
	client->damage_flame = 0;
	client->damage_armor = 0;
	client->damage_parmor = 0;
	client->damage_knockback = 0;
}




/*
===============
SV_CalcViewOffset

Auto pitching on slopes?

  fall from 128: 400 = 160000
  fall from 256: 580 = 336400
  fall from 384: 720 = 518400
  fall from 512: 800 = 640000
  fall from 640: 960 = 

  damage = deltavelocity*deltavelocity  * 0.0001

===============
*/
void SV_CalcViewOffset (edict_t *ent)
{
	float		*angles;
	float		bob;
	float		ratio;
	float		delta;
	vec3_t		v;


//===================================

	// base angles
	angles = ent->client->ps.kick_angles;

	// if dead, fix the angle and don't add any kick
	if (ent->deadflag)
	{
		VectorClear (angles);

		ent->client->ps.viewangles[ROLL] = 40;
		ent->client->ps.viewangles[PITCH] = -15;
		ent->client->ps.viewangles[YAW] = ent->client->killer_yaw;
	}
	else
	{
		// add angles based on weapon kick

		VectorCopy (ent->client->kick_angles, angles);

		// add angles based on damage kick

		ratio = (ent->client->v_dmg_time - level.time) / DAMAGE_TIME;
		if (ratio < 0)
		{
			ratio = 0;
			ent->client->v_dmg_pitch = 0;
			ent->client->v_dmg_roll = 0;
		}
		angles[PITCH] += ratio * ent->client->v_dmg_pitch;
		angles[ROLL] += ratio * ent->client->v_dmg_roll;

		// add pitch based on fall kick

		ratio = (ent->client->fall_time - level.time) / FALL_TIME;
		if (ratio < 0)
			ratio = 0;
		angles[PITCH] += ratio * ent->client->fall_value;

		// add angles based on velocity

		delta = DotProduct (ent->velocity, forward);
		angles[PITCH] += delta*run_pitch->value;
		
		delta = DotProduct (ent->velocity, right);
		angles[ROLL] += delta*run_roll->value;

		// add angles based on bob

		delta = bobfracsin * bob_pitch->value * xyspeed;
		if (ent->client->ps.pmove.pm_flags & PMF_DUCKED)
			delta *= 6;		// crouching
		angles[PITCH] += delta;
		delta = bobfracsin * bob_roll->value * xyspeed;
		if (ent->client->ps.pmove.pm_flags & PMF_DUCKED)
			delta *= 6;		// crouching
		if (bobcycle & 1)
			delta = -delta;
		angles[ROLL] += delta;
	}

//===================================

	// base origin

	VectorClear (v);

	// add view height

	v[2] += ent->viewheight;

	// add fall height

	ratio = (ent->client->fall_time - level.time) / FALL_TIME;
	if (ratio < 0)
		ratio = 0;
	v[2] -= ratio * ent->client->fall_value * 0.4;

	// add bob height

	bob = bobfracsin * xyspeed * bob_up->value;
	if (bob > 6)
		bob = 6;
	//gi.DebugGraph (bob *2, 255);
	v[2] += bob;

	// add kick offset

	VectorAdd (v, ent->client->kick_origin, v);

	// absolutely bound offsets
	// so the view can never be outside the player box

	if (v[0] < -14)
		v[0] = -14;
	else if (v[0] > 14)
		v[0] = 14;
	if (v[1] < -14)
		v[1] = -14;
	else if (v[1] > 14)
		v[1] = 14;
	if (v[2] < -22)
		v[2] = -22;
	else if (v[2] > 50)
		v[2] = 50;

	VectorCopy (v, ent->client->ps.viewoffset);
}

/*
==============
SV_CalcGunOffset
==============
*/
void SV_CalcGunOffset (edict_t *ent)
{
	int		i;
//	float	delta;

	// gun angles from bobbing
	ent->client->ps.gunangles[ROLL] = xyspeed * bobfracsin * 0.005;
	ent->client->ps.gunangles[YAW] = xyspeed * bobfracsin * 0.01;
	if (bobcycle & 1)
	{
		ent->client->ps.gunangles[ROLL] = -ent->client->ps.gunangles[ROLL];
		ent->client->ps.gunangles[YAW] = -ent->client->ps.gunangles[YAW];
	}

	ent->client->ps.gunangles[PITCH] = xyspeed * bobfracsin * 0.005;

// Ridah, causes problems with flamethrower alignment
/*
	// gun angles from delta movement
	for (i=0 ; i<3 ; i++)
	{
		delta = ent->client->oldviewangles[i] - ent->client->ps.viewangles[i];
		if (delta > 180)
			delta -= 360;
		if (delta < -180)
			delta += 360;
		if (delta > 45)
			delta = 45;
		if (delta < -45)
			delta = -45;
		if (i == YAW)
			ent->client->ps.gunangles[ROLL] += 0.1*delta;
		ent->client->ps.gunangles[i] += 0.2 * delta;
	}
*/

	// gun height
	VectorClear (ent->client->ps.gunoffset);
//	ent->ps->gunorigin[2] += bob;

	// gun_x / gun_y / gun_z are development tools
	for (i=0 ; i<3 ; i++)
	{
		ent->client->ps.gunoffset[i] += forward[i]*(gun_y->value);
		ent->client->ps.gunoffset[i] += right[i]*gun_x->value;
		ent->client->ps.gunoffset[i] += up[i]* (-gun_z->value);
	}
}


/*
=============
SV_AddBlend
=============
*/
void SV_AddBlend (float r, float g, float b, float a, float *v_blend)
{
	float	a2, a3;

	if (a <= 0)
		return;
	a2 = v_blend[3] + (1-v_blend[3])*a;	// new total alpha
	a3 = v_blend[3]/a2;		// fraction of color from old

	v_blend[0] = v_blend[0]*a3 + r*(1-a3);
	v_blend[1] = v_blend[1]*a3 + g*(1-a3);
	v_blend[2] = v_blend[2]*a3 + b*(1-a3);
	v_blend[3] = a2;
}


/*
=============
SV_CalcBlend
=============
*/
void SV_CalcBlend (edict_t *ent)
{
	int		contents;
	vec3_t	vieworg;
	int		remaining;

	ent->client->ps.blend[0] = ent->client->ps.blend[1] = 
		ent->client->ps.blend[2] = ent->client->ps.blend[3] = 0;

	// add for contents
	VectorAdd (ent->s.origin, ent->client->ps.viewoffset, vieworg);
	contents = gi.pointcontents (vieworg);
	if (contents & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER) )
		ent->client->ps.rdflags |= RDF_UNDERWATER;
	else
		ent->client->ps.rdflags &= ~RDF_UNDERWATER;

	if (contents & (CONTENTS_SOLID|CONTENTS_LAVA))
		SV_AddBlend (1.0, 0.3, 0.0, 0.6, ent->client->ps.blend);
	else if (contents & CONTENTS_SLIME)
		SV_AddBlend (0.0, 0.1, 0.05, 0.6, ent->client->ps.blend);
	// JOSEPH 20-MAY-99
	else if (contents & CONTENTS_WATER)
		//SV_AddBlend (0.5, 0.3, 0.2, 0.4, ent->client->ps.blend);
		SV_AddBlend (0.03, 0.04, 0.03, 0.4, ent->client->ps.blend);
	// END JOSEPH	

	// add for powerups
	if (ent->client->quad_framenum > level.framenum)
	{
		remaining = ent->client->quad_framenum - level.framenum;
		if (remaining == 30)	// beginning to fade
			gi.sound(ent, CHAN_ITEM, gi.soundindex("items/damage2.wav"), 1, ATTN_NORM, 0);
		if (remaining > 30 || (remaining & 4) )
			SV_AddBlend (0, 0, 1, 0.08, ent->client->ps.blend);
	}
	// RAFAEL
	else if (ent->client->quadfire_framenum > level.framenum)
	{
		remaining = ent->client->quadfire_framenum - level.framenum;
		if (remaining == 30)	// beginning to fade
			gi.sound(ent, CHAN_ITEM, gi.soundindex("items/quadfire2.wav"), 1, ATTN_NORM, 0);
		if (remaining > 30 || (remaining & 4) )
			SV_AddBlend (1, 0.2, 0.5, 0.08, ent->client->ps.blend);
	}
	else if (ent->client->invincible_framenum > level.framenum)
	{
		remaining = ent->client->invincible_framenum - level.framenum;
		if (remaining == 30)	// beginning to fade
			gi.sound(ent, CHAN_ITEM, gi.soundindex("items/protect2.wav"), 1, ATTN_NORM, 0);
		if (remaining > 30 || (remaining & 4) )
			SV_AddBlend (1, 1, 0, 0.08, ent->client->ps.blend);
	}
	else if (ent->client->enviro_framenum > level.framenum)
	{
		remaining = ent->client->enviro_framenum - level.framenum;
		if (remaining == 30)	// beginning to fade
			gi.sound(ent, CHAN_ITEM, gi.soundindex("items/airout.wav"), 1, ATTN_NORM, 0);
		if (remaining > 30 || (remaining & 4) )
			SV_AddBlend (0, 1, 0, 0.08, ent->client->ps.blend);
	}
	else if (ent->client->breather_framenum > level.framenum)
	{
		remaining = ent->client->breather_framenum - level.framenum;
		if (remaining == 30)	// beginning to fade
			gi.sound(ent, CHAN_ITEM, gi.soundindex("items/airout.wav"), 1, ATTN_NORM, 0);
		if (remaining > 30 || (remaining & 4) )
			SV_AddBlend (0.4, 1, 0.4, 0.04, ent->client->ps.blend);
	}

	// JOSEPH 9-JUN-99-B
	if (level.fadeendtime > level.time)
	{
		float alpha;
		if (level.inversefade)
		{
			alpha = 1.0 - ((level.fadeendtime - level.time)*(1.0/level.totalfade));
		}
		else
		alpha = (level.fadeendtime - level.time)*(1.0/level.totalfade);
		
		SV_AddBlend (0.0, 0.0, 0.0, alpha, ent->client->ps.blend);
	}
	else
	{
		if (level.inversefade)
		{
			SV_AddBlend (0.0, 0.0, 0.0, 1.0, ent->client->ps.blend);	
			// JOSEPH 11-JUN-99-B
			//gi.StopRender();
			// END JOSEPH
		}
	}
	// END JOSEPH

	// add for damage
	if (ent->client->damage_alpha > 0)
		SV_AddBlend (ent->client->damage_blend[0],ent->client->damage_blend[1]
		,ent->client->damage_blend[2], ent->client->damage_alpha, ent->client->ps.blend);

	if (ent->client->bonus_alpha > 0)
		SV_AddBlend (0.85, 0.7, 0.3, ent->client->bonus_alpha, ent->client->ps.blend);

	// drop the damage value
	ent->client->damage_alpha -= 0.06;
	if (ent->client->damage_alpha < 0)
		ent->client->damage_alpha = 0;

	// drop the bonus value
	ent->client->bonus_alpha -= 0.1;
	if (ent->client->bonus_alpha < 0)
		ent->client->bonus_alpha = 0;
}



// JOSEPH 20-JAN-99
/*
=================
P_FallingDamage
=================
*/
void P_FallingDamage (edict_t *ent)
{
	float	delta;
	int		damage;
	vec3_t	dir;

//	if (ent->s.modelindex != 255)
//		return;		// not in the player model

	if (ent->movetype == MOVETYPE_NOCLIP)
		return;

	if ((ent->client->oldvelocity[2] < 0) && (ent->velocity[2] > ent->client->oldvelocity[2]) && (!ent->groundentity))
	{
		delta = ent->client->oldvelocity[2];
	}
	else
	{
		if (!ent->groundentity)
			return;
		delta = ent->velocity[2] - ent->client->oldvelocity[2];

		// Ridah, don't do damage so much as Q2 did
		if (deathmatch->value)// && ent->client->oldvelocity[2] > -400)
		{
			delta *= 0.9;
		}
	}
	delta = delta*delta * 0.0001;

	// never take falling damage if completely underwater
	if (ent->waterlevel == 3)
		return;
	if (ent->waterlevel == 2)
		delta *= 0.25;
	if (ent->waterlevel == 1)
		delta *= 0.5;

	if (delta < 1)
		return;

	if (delta < 15)
	{
		// Ridah, Hovercars, no footsteps
		if (!(ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE)))
		// done.
		// JOSEPH 1-SEP-98
		ent->s.event = EV_FOOTSTEP0 + ent->footsteptype;
		return;
	}

	ent->client->fall_value = delta*0.5;
	if (ent->client->fall_value > 40)
		ent->client->fall_value = 40;
	ent->client->fall_time = level.time + FALL_TIME;

	// JOSEPH 26-JAN-99-B
	if (delta > 30)
	//if (delta >= 15)
	// END JOSEPH
	{
		if (ent->health > 0)
		{
			if (delta >= 55)
				ent->s.event = EV_FALLFAR;
			else
				ent->s.event = EV_FALL;
		}
		ent->pain_debounce_time = level.time;	// no normal pain sound
		
		//damage = (delta-30)/2;
		damage = delta/2;
		
		if (damage < 1)
			damage = 1;
		VectorSet (dir, 0, 0, 1);

		if (!deathmatch->value || !((int)dmflags->value & DF_NO_FALLING) )
			T_Damage (ent, world, world, dir, ent->s.origin, vec3_origin, damage, 0, 0, MOD_FALLING);
	}
	else
	{
		// JOSEPH 1-SEP-98
		ent->s.event = EV_FALLSHORT0 + ent->footsteptype;
		return;
	}
}
// END JOSEPH


/*
=============
P_WorldEffects
=============
*/
void P_WorldEffects (void)
{
	qboolean	breather;
	qboolean	envirosuit;
	int			waterlevel, old_waterlevel;

	if (current_player->movetype == MOVETYPE_NOCLIP)
	{
		current_player->air_finished = level.time + 12;	// don't need air
		return;
	}

	waterlevel = current_player->waterlevel;
	old_waterlevel = current_client->old_waterlevel;
	current_client->old_waterlevel = waterlevel;

	breather = current_client->breather_framenum > level.framenum;
	envirosuit = current_client->enviro_framenum > level.framenum;

	//
	// if just entered a water volume, play a sound
	//
	if (!old_waterlevel && waterlevel)
	{
		PlayerNoise(current_player, current_player->s.origin, PNOISE_SELF);
		if (current_player->watertype & CONTENTS_LAVA)
			gi.sound (current_player, CHAN_BODY, gi.soundindex("actors/player/lava_in.wav"), 1, ATTN_NORM, 0);
		// JOSEPH 13-MAY-99
		else if (current_player->watertype & CONTENTS_SLIME)
			gi.sound (current_player, CHAN_BODY, gi.soundindex("actors/player/male/watr_in.wav"), 1, ATTN_NORM, 0);
		else if (current_player->watertype & CONTENTS_WATER)
			gi.sound (current_player, CHAN_BODY, gi.soundindex("actors/player/male/watr_in.wav"), 1, ATTN_NORM, 0);
		// END JOSEPH
		current_player->flags |= FL_INWATER;

		// clear damage_debounce, so the pain sound will play immediately
		current_player->damage_debounce_time = level.time - 1;
	}

	//
	// if just completely exited a water volume, play a sound
	//
	if (old_waterlevel && ! waterlevel)
	{
		PlayerNoise(current_player, current_player->s.origin, PNOISE_SELF);
		// JOSEPH 13-MAY-99 
		gi.sound (current_player, CHAN_BODY, gi.soundindex("actors/player/male/watr_out.wav"), 1, ATTN_NORM, 0);
		// END JOSEPH
		current_player->flags &= ~FL_INWATER;
	}

	//
	// check for head just going under water
	//
	if (old_waterlevel != 3 && waterlevel == 3)
	{
		// JOSEPH 24-NOV-98
		// FIXME : needs to find water to place splash sprite
		trace_t tr;
		vec3_t	start;
		int		color;
		int		content_mask = MASK_WATER;	

		// JOSEPH 13-MAY-99
		gi.sound (current_player, CHAN_BODY, gi.soundindex("actors/player/male/watr_un.wav"), 1, ATTN_NORM, 0);
		// END JOSEPH

		VectorCopy (current_player->s.origin, start);
		start[2] += 128;

		tr = gi.trace (start, NULL, NULL, current_player->s.origin, current_player, content_mask);
			
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
			static	float	last_ripple;

			if (last_ripple > level.time)
				last_ripple = 0;

			if (last_ripple < (level.time - 0.75))
			{
				// Ripple effect
				SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH, SFX_RIPPLE_HEIGHT,
										tr.ent, tr.endpos, tr.plane.normal );
				SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH<<2, SFX_RIPPLE_HEIGHT<<2,
										tr.ent, tr.endpos, tr.plane.normal );
				SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH<<1, SFX_RIPPLE_HEIGHT<<1,
										tr.ent, tr.endpos, tr.plane.normal );
			}

		}				
		// END JOSEPH	
	}

	//
	// check for head just coming out of water
	//
	if (old_waterlevel == 3 && waterlevel != 3)
	{
		// JOSEPH 24-NOV-98
		// FIXME : needs to find water to place splash sprite
		trace_t tr;
		vec3_t	start;
		int		color;
		int		content_mask = MASK_WATER;
		
		// JOSEPH 29-MAR-99
		if (current_player->air_finished < level.time)
		{	// gasp for air
			// Rafael-final
			gi.sound (current_player, CHAN_VOICE, gi.soundindex("*gasp1.wav"), 1, ATTN_NORM, 0);
			//gi.sound (current_player, CHAN_VOICE, gi.soundindex("actors/player/male/gasp1.wav"), 1, ATTN_NORM, 0);

			PlayerNoise(current_player, current_player->s.origin, PNOISE_SELF);
		}
		else  if (current_player->air_finished < level.time + 11)
		{	// just break surface
			// Rafael-final
			gi.sound (current_player, CHAN_VOICE, gi.soundindex("*gasp2.wav"), 1, ATTN_NORM, 0);
			// gi.sound (current_player, CHAN_VOICE, gi.soundindex("actors/player/male/gasp2.wav"), 1, ATTN_NORM, 0);

		}
		// END JOSEPH
		
		VectorCopy (current_player->s.origin, start);
		start[2] += 128;

		tr = gi.trace (start, NULL, NULL, current_player->s.origin, current_player, content_mask);
			
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
			static	float	last_ripple;

			if (last_ripple > level.time)
				last_ripple = 0;

			if (last_ripple < (level.time - 0.75))
			{
				// Ripple effect
				SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH, SFX_RIPPLE_HEIGHT,
										tr.ent, tr.endpos, tr.plane.normal );
				SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH<<2, SFX_RIPPLE_HEIGHT<<2,
										tr.ent, tr.endpos, tr.plane.normal );
				SurfaceSpriteEffect(	SFX_SPRITE_SURF_RIPPLE, SFX_RIPPLE_WIDTH<<1, SFX_RIPPLE_HEIGHT<<1,
										tr.ent, tr.endpos, tr.plane.normal );
			}

		}		
		// END JOSEPH
	}

	//
	// check for drowning
	//
	if (waterlevel == 3)
	{
		// breather or envirosuit give air
		if (breather || envirosuit)
		{
			current_player->air_finished = level.time + 10;

			if (((int)(current_client->breather_framenum - level.framenum) % 25) == 0)
			{
				// JOSEPH 29-MAR-99
				//if (!current_client->breather_sound)
				//	gi.sound (current_player, CHAN_AUTO, gi.soundindex("actors/player/u_breath1.wav"), 1, ATTN_NORM, 0);
				//else
				//	gi.sound (current_player, CHAN_AUTO, gi.soundindex("actors/player/u_breath2.wav"), 1, ATTN_NORM, 0);
				// END JOSEPH
				current_client->breather_sound ^= 1;
				PlayerNoise(current_player, current_player->s.origin, PNOISE_SELF);
				//FIXME: release a bubble?
			}
		}

		// if out of air, start drowning
		if (current_player->air_finished < level.time)
		{	// drown!
			if (current_player->client->next_drown_time < level.time 
				&& current_player->health > 0)
			{
				current_player->client->next_drown_time = level.time + 1;

				// take more damage the longer underwater
				current_player->dmg += 2;
				if (current_player->dmg > 15)
					current_player->dmg = 15;

				// play a gurp sound instead of a normal pain sound
				if (current_player->health <= current_player->dmg)
					gi.sound (current_player, CHAN_VOICE, gi.soundindex("actors/player/male/drown1.wav"), 1, ATTN_NORM, 0);
				else if (rand()&1)
					gi.sound (current_player, CHAN_VOICE, gi.soundindex("*gurp1.wav"), 1, ATTN_NORM, 0);
				else
					gi.sound (current_player, CHAN_VOICE, gi.soundindex("*gurp2.wav"), 1, ATTN_NORM, 0);

				current_player->pain_debounce_time = level.time;

				T_Damage (current_player, world, world, vec3_origin, current_player->s.origin, vec3_origin, current_player->dmg, 0, DAMAGE_NO_ARMOR, MOD_WATER);
			}
		}
	}
	else
	{
		current_player->air_finished = level.time + 12;
		current_player->dmg = 2;
	}

	//
	// check for sizzle damage
	//
	if (waterlevel && (current_player->watertype&(CONTENTS_LAVA|CONTENTS_SLIME)) )
	{
		if (current_player->watertype & CONTENTS_LAVA)
		{
			if (current_player->health > 0
				&& current_player->pain_debounce_time <= level.time
				&& current_client->invincible_framenum < level.framenum)
			{
				if (rand()&1)
					gi.sound (current_player, CHAN_VOICE, gi.soundindex("actors/player/burn1.wav"), 1, ATTN_NORM, 0);
				else
					gi.sound (current_player, CHAN_VOICE, gi.soundindex("actors/player/burn2.wav"), 1, ATTN_NORM, 0);
				current_player->pain_debounce_time = level.time + 1;
			}

			if (envirosuit)	// take 1/3 damage with envirosuit
				T_Damage (current_player, world, world, vec3_origin, current_player->s.origin, vec3_origin, 1*waterlevel, 0, 0, MOD_LAVA);
			else
				T_Damage (current_player, world, world, vec3_origin, current_player->s.origin, vec3_origin, 3*waterlevel, 0, 0, MOD_LAVA);
		}

		if (current_player->watertype & CONTENTS_SLIME)
		{
			if (!envirosuit)
			{	// no damage from slime with envirosuit
				T_Damage (current_player, world, world, vec3_origin, current_player->s.origin, vec3_origin, 1*waterlevel, 0, 0, MOD_SLIME);
			}
		}
	}
}


/*
===============
G_SetClientEffects
===============
*/
void G_SetClientEffects (edict_t *ent)
{
	int		pa_type;
	int		remaining;

	ent->s.effects = 0;
	ent->s.renderfx = 0;

	// RAFAEL
	if (level.cut_scene_time)
		return;
	else if (level.pawn_time)
		return;
	else if (level.intermissiontime)
		return;

	if (ent->onfiretime > 0)
	{
		ent->s.effects |= EF_FLAMETHROWER;

		if (ent->health <= 0)
			ent->onfiretime -= 1;
	}

	if (ent->health <= 0)
		return;

	if (ent->powerarmor_time > level.time)
	{
		pa_type = PowerArmorType (ent);
		if (pa_type == POWER_ARMOR_SCREEN)
		{
			ent->s.effects |= EF_POWERSCREEN;
		}
		else if (pa_type == POWER_ARMOR_SHIELD)
		{
			ent->s.effects |= EF_COLOR_SHELL;
			ent->s.renderfx |= RF_SHELL_GREEN;
		}
	}

	if (ent->client->quad_framenum > level.framenum)
	{
		remaining = ent->client->quad_framenum - level.framenum;
		if (remaining > 30 || (remaining & 4) )
			ent->s.effects |= EF_QUAD;
	}

	// RAFAEL
	if (ent->client->quadfire_framenum > level.framenum)
	{
		remaining = ent->client->quadfire_framenum - level.framenum;
		if (remaining > 30 || (remaining & 4) )
			ent->s.effects |= EF_QUAD;
	}

	
	if (ent->client->invincible_framenum > level.framenum)
	{
		remaining = ent->client->invincible_framenum - level.framenum;
		if (remaining > 30 || (remaining & 4) )
			ent->s.effects |= EF_PENT;
	}

	// show cheaters!!!
	if (ent->flags & FL_GODMODE)
	{
		ent->s.effects |= EF_COLOR_SHELL;
		ent->s.renderfx |= (RF_SHELL_RED|RF_SHELL_GREEN|RF_SHELL_BLUE);
	}

	if (deathmatch->value && teamplay->value && ent->client->pers.bagcash)
	{
		ent->s.renderfx2 |= RF2_MONEYBAG;
	}
	else
	{
		ent->s.renderfx2 &= ~RF2_MONEYBAG;
	}
}


// JOSEPH 27-JAN-99
/*
===============
G_SetClientEvent
===============
*/
void G_SetClientEvent (edict_t *ent)
{
	if (ent->s.event)
		return;

	if ( ent->groundentity && xyspeed > 270)
	{
		if ( (int)(current_client->bobtime+bobmove) != bobcycle )
			// Ridah, Hovercars, no footsteps
			if (!(ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE)))
			// done.
			// JOSEPH 1-SEP-98
			{
				if (ent->footsteptype == 8)
				{
					if (bobcycle & 1)
						ent->s.event = EV_FOOTSTEP0 + ent->footsteptype;
				}
				else
				{
					ent->s.event = EV_FOOTSTEP0 + ent->footsteptype;
				}
			}
	}
}
// END JOSEPH


/*
===============
G_SetClientSound
===============
*/
void G_SetClientSound (edict_t *ent)
{
	char	*weap;

	
	if (ent->client->pers.game_helpchanged != game.helpchanged)
	{
		ent->client->pers.game_helpchanged = game.helpchanged;
		ent->client->pers.helpchanged = 1;
	}
	

	// JOSEPH 29-MAR-99
	// help beep (no more than three times)
	/*if (ent->client->pers.helpchanged && ent->client->pers.helpchanged <= 3 && !(level.framenum&63) )
	{
		ent->client->pers.helpchanged++;
		gi.sound (ent, CHAN_VOICE, gi.soundindex ("misc/pc_up.wav"), 1, ATTN_STATIC, 0);
	}*/
	// END JOSEPH

	if (ent->client->pers.weapon)
		weap = ent->client->pers.weapon->classname;
	else
		weap = "";

	if (ent->waterlevel && (ent->watertype&(CONTENTS_LAVA|CONTENTS_SLIME)) )
		ent->s.sound = snd_fry;
	else if (strcmp(weap, "weapon_railgun") == 0)
		ent->s.sound = gi.soundindex("weapons/rg_hum.wav");
	else if (strcmp(weap, "weapon_bfg") == 0)
		ent->s.sound = gi.soundindex("weapons/bfg_hum.wav");
	// RAFAEL
	else if (strcmp (weap, "weapon_phalanx") == 0)
		ent->s.sound = gi.soundindex ("weapons/phaloop.wav");
	else if (ent->client->weapon_sound)
		ent->s.sound = ent->client->weapon_sound;
	else if (strcmp (weap, "weapon_flamethrower") == 0)
		ent->s.sound = gi.soundindex ("weapons/flame_thrower/flamepilot.wav");
	else
		ent->s.sound = 0;
}

/*
===============
G_SetClientFrame
===============
*/

void G_SetClientFrame (edict_t *ent)
{
#define WEAPON_NONE		0
#define WEAPON_MELEE	1
#define WEAPON_GENERIC	2
#define WEAPON_PISTOL	3

	gclient_t	*client;
	vec3_t		vel;
	float		side_dot, fwd_dot, speed;
	int			duck, run, slide;
	int			weapontype;
	int	oldframe, oldend;

// Ridah, Hovercars
	if (ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE))
	{	// always frame 0, use visiblity for model_parts to represent damage
		ent->s.frame = 0;
		return;
	}
// done.

//	if (ent->s.modelindex != 255)
//		return;		// not in the player model

	client = ent->client;

	if (client->ps.pmove.pm_flags & PMF_DUCKED)
		duck = true;
	else
		duck = false;

	VectorCopy( ent->velocity, vel );
	vel[2] = 0;
	speed = VectorNormalize( vel );

	run = 0;
	slide = 0;

	if (speed > 1)
	{
		side_dot = DotProduct( right, vel );
		fwd_dot = DotProduct( forward, vel );

		if (fwd_dot < -0.5)
			run = -1;
		else if (fwd_dot > 0.5)
			run = 1;

		if (side_dot < -0.5)
			slide = -1;
		else if (side_dot > 0.5)
			slide = 1;
	}

	run *= 1 + (speed > 200);

	if (client->pers.weapon && (ent->noise_time > (level.time + 1.5)))
	{
		if (strstr(client->pers.weapon->classname, "pistol"))
			weapontype = WEAPON_PISTOL;
		else if (!client->pers.weapon->ammo)
			weapontype = WEAPON_MELEE;
		else
			weapontype = WEAPON_GENERIC;
	}
	else
	{
		weapontype = WEAPON_NONE;
	}


	if (weapontype == WEAPON_MELEE)
	{

		// always use normal run if melee and moving
		if (run || slide)
		{
			if (!run)
				run = 1;

			run = 2 * (int)(run/fabs(run));

			slide = 0;
		}

	}

	if (client->anim_priority == ANIM_DEATH)
	{
		if (ent->s.frame < client->anim_end)
			ent->s.frame++;
		return;		// stay there
	}

	if ((client->anim_priority < ANIM_DEATH) && (client->last_weapontype != weapontype))
		goto newanim;

	// check for stand/duck and stop/go transitions
	if (duck != client->anim_duck && client->anim_priority < ANIM_DEATH)
		goto newanim;
	if (run != client->anim_run && client->anim_priority <= ANIM_BASIC)
		goto newanim;
	if (slide != client->anim_slide && !client->anim_run && client->anim_priority <= ANIM_BASIC)
		goto newanim;
	if (!ent->groundentity && client->anim_priority <= ANIM_WAVE)
		goto newanim;
	if (client->anim_priority == ANIM_JUMP && ent->groundentity)
		goto newanim;

	// attacking while standing?
	if (!client->anim_run && !client->anim_slide && (client->anim_priority == ANIM_BASIC) && (client->buttons & BUTTON_ATTACK))
		goto newanim;

	if ((client->anim_priority == ANIM_REVERSE) || client->anim_reverse)
	{
		if(ent->s.frame > client->anim_end)
		{
			ent->s.frame--;
			return;
		}
	}
	else if (ent->s.frame < client->anim_end)
	{	// continue an animation
		ent->s.frame++;
		return;
	}

	if (client->anim_priority == ANIM_JUMP)
	{
		if (!ent->groundentity)
		{
			trace_t tr;
			vec3_t	endpos;

			VectorMA( ent->s.origin, 1, forward, endpos );
			tr = gi.trace( ent->s.origin, ent->mins, ent->maxs, endpos, ent, CONTENTS_LADDER );

			if (tr.fraction < 1 && tr.contents & CONTENTS_LADDER)
			{	// climbing animation
				if (fabs(client->last_climb_anim_z - ent->s.origin[2]) > 1)
				{
					// JOSEPH 14-MAY-99
					if (ent->last_step_time < (level.time-0.2))
					{
						ent->s.event = EV_FOOTSTEP0 + 4;
						ent->last_step_time = level.time;
					}	
					// END JOSEPH
					
					if (ent->s.frame < FRAME_clmb_loop_01 || (ent->s.frame >= FRAME_clmb_loop_09))
					{
						ent->s.frame = FRAME_clmb_loop_01;
					}
					else
					{
						if (client->last_climb_anim_z > ent->s.origin[2])
							ent->s.frame--;
						else
							ent->s.frame++;
					}
					client->last_climb_anim_z = ent->s.origin[2];
				}
			}
			else
			{
				client->last_climb_anim_z = ent->s.origin[2];
			}

			return;		// stay there
		}

		ent->client->anim_priority = ANIM_WAVE;

//			ent->s.frame = FRAME_jump1_01;
		ent->client->anim_end = FRAME_jump_07;
		return;
	}

newanim:
	// return to either a running or standing frame
	client->anim_priority = ANIM_BASIC;
	client->anim_reverse = false;
	client->anim_duck = duck;
	client->anim_run = run;
	client->anim_slide = slide;

	client->last_weapontype = weapontype;


	oldframe = ent->s.frame;
	oldend = client->anim_end;

	if (!ent->groundentity)
	{
		client->anim_priority = ANIM_JUMP;
//		if (ent->s.frame != FRAME_jump_07)
			ent->s.frame = FRAME_jump_01;
		client->anim_end = FRAME_jump_07;
	}
	else if (run)
	{	// running
		if (duck)
		{
			if (run < 0)
			{
				client->anim_reverse = true;

				switch (weapontype)
				{
				case WEAPON_PISTOL:
					ent->s.frame = FRAME_p_crch_walk_06;
					client->anim_end = FRAME_p_crch_walk_01;
					break;

				case WEAPON_MELEE:
					// TODO: need crouch melee

				default:
					ent->s.frame = FRAME_crch_shuf_05;
					client->anim_end = FRAME_crch_shuf_01;
				}
			}
			else
			{
				switch (weapontype)
				{
				case WEAPON_PISTOL:
					ent->s.frame = FRAME_p_crch_walk_01;
					client->anim_end = FRAME_p_crch_walk_06;
					break;

				case WEAPON_MELEE:
					// TODO: need crouch melee

				default:
					ent->s.frame = FRAME_crch_shuf_01;
					client->anim_end = FRAME_crch_shuf_05;
				}
			}
		}
		else
		{
			if (run < 0)
			{
				if (fabs(run) < 2)	// walking backwards
				{
					client->anim_reverse = true;

					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_walk_sht_10;
						client->anim_end = FRAME_p_walk_sht_01;
						break;

					case WEAPON_MELEE:
						if (client->buttons & BUTTON_ATTACK)
						{
							ent->s.frame = FRAME_run_melee_06;
							client->anim_end = FRAME_run_melee_01;
						}
						else
						{
							ent->s.frame = FRAME_walk_gdown_10;
							client->anim_end = FRAME_walk_gdown_01;
						}
						break;

					case WEAPON_NONE:
						ent->s.frame = FRAME_walk_gdown_10;
						client->anim_end = FRAME_walk_gdown_01;
						break;

					default:
						ent->s.frame = FRAME_walk_tg_sht_10;
						client->anim_end = FRAME_walk_tg_sht_01;
					}
				}
				else	// running backwards
				{
					client->anim_reverse = true;

					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_run_shoot_06;
						client->anim_end = FRAME_p_run_shoot_01;
						break;

					case WEAPON_MELEE:
						if (client->buttons & BUTTON_ATTACK)
						{
							ent->s.frame = FRAME_run_melee_06;
							client->anim_end = FRAME_run_melee_01;
						}
						else
						{
							ent->s.frame = FRAME_run_gun_dn_06;
							client->anim_end = FRAME_run_gun_dn_01;
						}
						break;

					case WEAPON_NONE:
						ent->s.frame = FRAME_run_gun_dn_06;
						client->anim_end = FRAME_run_gun_dn_01;
						break;

					default:
						ent->s.frame = FRAME_run_tg_sht_06;
						client->anim_end = FRAME_run_tg_sht_01;
					}
				}
			}
			else
			{
				if (fabs(run) < 2)	// walking forwards
				{
					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_walk_sht_01;
						client->anim_end = FRAME_p_walk_sht_10;
						break;

					case WEAPON_MELEE:
						if (client->buttons & BUTTON_ATTACK)
						{
							ent->s.frame = FRAME_run_melee_01;
							client->anim_end = FRAME_run_melee_06;
						}
						else
						{
							ent->s.frame = FRAME_walk_gdown_01;
							client->anim_end = FRAME_walk_gdown_10;
						}
						break;

					case WEAPON_NONE:
						ent->s.frame = FRAME_walk_gdown_01;
						client->anim_end = FRAME_walk_gdown_10;
						break;

					default:
						ent->s.frame = FRAME_walk_tg_sht_01;
						client->anim_end = FRAME_walk_tg_sht_10;
					}
				}
				else // running forwards
				{
					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_run_shoot_01;
						client->anim_end = FRAME_p_run_shoot_06;
						break;

					case WEAPON_MELEE:
						if (client->buttons & BUTTON_ATTACK)
						{
							ent->s.frame = FRAME_run_melee_01;
							client->anim_end = FRAME_run_melee_06;
						}
						else
						{
							ent->s.frame = FRAME_run_gun_dn_01;
							client->anim_end = FRAME_run_gun_dn_06;
						}
						break;

					case WEAPON_NONE:
						ent->s.frame = FRAME_run_gun_dn_01;
						client->anim_end = FRAME_run_gun_dn_06;
						break;

					default:
						ent->s.frame = FRAME_run_tg_sht_01;
						client->anim_end = FRAME_run_tg_sht_06;
					}
				}
			}

			// keep smooth transitions between firing/firing+running
			if ((fabs(oldend - oldframe) <= fabs(ent->s.frame - client->anim_end)) && (fabs(ent->s.frame - client->anim_end) == 5))
			{
				int	diff;

				diff = fabs(ent->s.frame - client->anim_end);

				if (ent->s.frame < client->anim_end)
				{
					ent->s.frame += (diff - fabs(oldend - oldframe)) + 1;
					if (ent->s.frame > client->anim_end)
						ent->s.frame = client->anim_end - diff;
				}
				else
				{
					ent->s.frame -= (diff - fabs(oldend - oldframe)) + 1;
					if (ent->s.frame < client->anim_end)
						ent->s.frame = client->anim_end + diff;
				}
			}
		}
	}
	else if (slide)
	{	// strafing
		if (duck)
		{
			switch (weapontype)
			{
			case WEAPON_PISTOL:
				ent->s.frame = FRAME_p_crch_walk_01;
				client->anim_end = FRAME_p_crch_walk_06;
				break;

			default:
				ent->s.frame = FRAME_crch_shuf_01;
				client->anim_end = FRAME_crch_shuf_05;
			}
		}
		else
		{
			if (slide < 0)
			{
				if (	(client->anim_end == FRAME_rsd_tg_run_06)
					||	(client->anim_end == FRAME_p_rside_run_06))
				{	// changing from one side to the other, go to run first

					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_run_shoot_01;
						client->anim_end = FRAME_p_run_shoot_02;
						break;

					default:
						ent->s.frame = FRAME_run_tg_sht_01;
						client->anim_end = FRAME_run_tg_sht_02;
					}

				}
				else
				{
					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_lside_run_01;
						client->anim_end = FRAME_p_lside_run_06;
						break;

					default:
						ent->s.frame = FRAME_lsd_tg_run_01;
						client->anim_end = FRAME_lsd_tg_run_06;
					}

				}
			}
			else
			{
				if (	(client->anim_end == FRAME_lsd_tg_run_06)
					||	(client->anim_end == FRAME_p_lside_run_06))
				{	// changing from one side to the other, go to run first
					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_run_shoot_01;
						client->anim_end = FRAME_p_run_shoot_02;
						break;

					default:
						ent->s.frame = FRAME_run_tg_sht_01;
						client->anim_end = FRAME_run_tg_sht_02;
					}
				}
				else
				{
					switch (weapontype)
					{
					case WEAPON_PISTOL:
						ent->s.frame = FRAME_p_rside_run_01;
						client->anim_end = FRAME_p_rside_run_06;
						break;

					default:
						ent->s.frame = FRAME_rsd_tg_run_01;
						client->anim_end = FRAME_rsd_tg_run_06;
					}
				}
			}

		}
	}
	else if (client->buttons & BUTTON_ATTACK)
	{	// standing attack

		client->anim_priority = ANIM_ATTACK;

		if (duck)
		{
			switch (weapontype)
			{
			case WEAPON_MELEE:
				// TODO, crouch melee?
			case WEAPON_PISTOL:
				ent->s.frame = FRAME_p_crch_sht_01;
				client->anim_end = FRAME_p_crch_sht_05;
				break;

			case WEAPON_NONE:
			case WEAPON_GENERIC:
				ent->s.frame = FRAME_crouch_shoot_01;
				client->anim_end = FRAME_crouch_shoot_06;
				break;
			}
		}
		else
		{
			switch (weapontype)
			{
			case WEAPON_NONE:
			case WEAPON_GENERIC:
				ent->s.frame = FRAME_tg_shoot_01;
				client->anim_end = FRAME_tg_shoot_05;
				break;

			case WEAPON_MELEE:
				if (rand()%2)
				{
					ent->s.frame = FRAME_melee3_01;
					client->anim_end = FRAME_melee3_07;
				}
				else
				{
					ent->s.frame = FRAME_melee4_01;
					client->anim_end = FRAME_melee4_06;
				}
				break;

			case WEAPON_PISTOL:
				ent->s.frame = FRAME_p_std_shoot_01;
				client->anim_end = FRAME_p_std_shoot_04;
				break;
			}
		}
	}
	else
	{	// standing

		if (duck)
		{
			switch (weapontype)
			{
			case WEAPON_GENERIC:
				ent->s.frame = FRAME_tg_crch_rdy_01;
				client->anim_end = FRAME_tg_crch_rdy_27;
				break;

			default:
				ent->s.frame = FRAME_1p_crch_rdy_01;
				client->anim_end = FRAME_1p_crch_rdy_18;
			}
		}
		else
		{
			switch (weapontype)
			{
			case WEAPON_PISTOL:
				ent->s.frame = FRAME_1pstl_rdy_01;
				client->anim_end = FRAME_1pstl_rdy_23;
				break;

			case WEAPON_MELEE:
				ent->s.frame = FRAME_melee_rdy_01;
				client->anim_end = FRAME_melee_rdy_19;
				break;

			default:
				ent->s.frame = FRAME_tgun_rdy_01;
				client->anim_end = FRAME_tgun_rdy_32;
				break;

			}
		}
	}
}



/*
=================
ClientEndServerFrame

Called for each player at the end of the server frame
and right after spawning
=================
*/
void ClientEndServerFrame (edict_t *ent)
{
	float	bobtime;
	int		i;

	// Ridah, had to put this here so the AI can process a gunshot before it gets cleared
	ent->client->gun_noise = false;

	current_player = ent;
	current_client = ent->client;

	//
	// If the origin or velocity have changed since ClientThink(),
	// update the pmove values.  This will happen when the client
	// is pushed by a bmodel or kicked by an explosion.
	// 
	// If it wasn't updated here, the view position would lag a frame
	// behind the body position when pushed -- "sinking into plats"
	//
	for (i=0 ; i<3 ; i++)
	{
		current_client->ps.pmove.origin[i] = ent->s.origin[i]*8.0;
		current_client->ps.pmove.velocity[i] = ent->velocity[i]*8.0;
	}

	//
	// If the end of unit layout is displayed, don't give
	// the player any normal movement attributes
	//
	if (level.intermissiontime)
	{
		// FIXME: add view drifting here?
		current_client->ps.blend[3] = 0;
		current_client->ps.fov = 90;
		G_SetStats (ent);
		return;
	}

	// RAFAEL
	// JOSEPH 25-FEB-99
	if (level.cut_scene_time)
	{
		current_client->ps.blend[3] = 0;
		// note to self
		// we may want to script the fov to an event
		// Joseph 22-FEB-99
		//current_client->ps.fov = 90;
		// END JOSEPH
		SV_CalcBlend (ent);
		G_SetStats (ent);
		return;
	}
	// END JOSEPH
	else if (level.pawn_time)
	{
		current_client->ps.blend[3] = 0;
		
		G_SetStats (ent);
		return;
	}

	AngleVectors (ent->client->v_angle, forward, right, up);

	// burn from lava, etc
	P_WorldEffects ();

	//
	// set model angles from view angles so other things in
	// the world can tell which direction you are looking
	//

	// Ridah, Hovercars, handle angles differently
	if (ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE))
	{
		if (current_client->ps.fov < 105)
			current_client->ps.fov = 105;	// fix FOV while in Hovercar

		if (ent->client->v_angle[PITCH] > 180)
			ent->s.angles[PITCH] = (-360 + ent->client->v_angle[PITCH]);
		else
			ent->s.angles[PITCH] = ent->client->v_angle[PITCH];
	}
	else
	// done.
	{
		if (ent->client->v_angle[PITCH] > 180)
			ent->s.angles[PITCH] = (-360 + ent->client->v_angle[PITCH])/3;
		else
			ent->s.angles[PITCH] = ent->client->v_angle[PITCH]/3;

		// Ridah, snap the pitch so that it doesn't change as often (cut network bandwidth)
		ent->s.angles[PITCH] = (int)(((int)ent->s.angles[PITCH]) / 5) * 5;
	}
	ent->s.angles[YAW] = ent->client->v_angle[YAW];
	ent->s.angles[ROLL] = 0;
	ent->s.angles[ROLL] = SV_CalcRoll (ent->s.angles, ent->velocity)*4;
/*
	if (ent->client->anim_end == FRAME_lside_run_07)
		ent->s.angles[YAW] = anglemod(ent->s.angles[YAW] - 90);
	else if (ent->client->anim_end == FRAME_rside_run_07)
		ent->s.angles[YAW] = anglemod(ent->s.angles[YAW] + 90);
*/
	// Ridah, Hovercars
	if (ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE))
		ent->s.angles[ROLL] *= 0.5;
	// done.

	//
	// calculate speed and cycle to be used for
	// all cyclic walking effects
	//
	xyspeed = sqrt(ent->velocity[0]*ent->velocity[0] + ent->velocity[1]*ent->velocity[1]);

	if (xyspeed < 5)
	{
		bobmove = 0;
		current_client->bobtime = 0;	// start at beginning of cycle again
	}
	else if (ent->groundentity)
	{	// so bobbing only cycles when on ground
		if (xyspeed > 210)
			bobmove = 0.25;
		else if (xyspeed > 100)
			bobmove = 0.125;
		else
			bobmove = 0.0625;
	}
	
	bobtime = (current_client->bobtime += bobmove);

	if (current_client->ps.pmove.pm_flags & PMF_DUCKED)
		bobtime *= 4;

	bobcycle = (int)bobtime;
	bobfracsin = fabs(sin(bobtime*M_PI));

	// detect hitting the floor
// Ridah, Hovercars, no falling damage
if (!(ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE)))
// done.
	P_FallingDamage (ent);

	// apply all the damage taken this frame
// Ridah, doesn't work with new palette?
	P_DamageFeedback (ent);

	// determine the view offsets
// Ridah, Hovercars, no view offsets
if (ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE))
	ent->client->ps.viewoffset[2] = ent->viewheight;
else
// done.
	SV_CalcViewOffset (ent);


	// determine the gun offsets
// Ridah, Hovercars, no gun offsets
if (ent->flags & (FL_HOVERCAR | FL_HOVERCAR_GROUND | FL_BIKE))
// done.
	SV_CalcGunOffset (ent);

	// Ridah, fade out kicks, which are used for mono's
	if (ent->flags & (FL_BIKE))
	{
		if (ent->client->kick_angles[PITCH] > 0)
		{
			ent->client->kick_angles[PITCH] -= 5 * FRAMETIME;
			if (ent->client->kick_angles[PITCH] < 0)
				ent->client->kick_angles[PITCH] = 0;
		}
		else if (ent->client->kick_angles[PITCH] < 0)
		{
			ent->client->kick_angles[PITCH] += 5 * FRAMETIME;
			if (ent->client->kick_angles[PITCH] > 0)
				ent->client->kick_angles[PITCH] = 0;
		}

		VectorCopy( ent->client->kick_angles, ent->client->ps.kick_angles );
	}

	// determine the full screen color blend
	// must be after viewoffset, so eye contents can be
	// accurately determined
	// FIXME: with client prediction, the contents
	// should be determined by the client
	SV_CalcBlend (ent);

	G_SetStats (ent);

	G_SetClientEvent (ent);

	G_SetClientEffects (ent);

	G_SetClientSound (ent);

	G_SetClientFrame (ent);

	VectorCopy (ent->velocity, ent->client->oldvelocity);
	VectorCopy (ent->client->ps.viewangles, ent->client->oldviewangles);

	// clear weapon kicks
	VectorClear (ent->client->kick_origin);

	// Ridah, fade out kicks, which are used for mono's
	if (!(ent->flags & FL_BIKE))
	{
		VectorClear (ent->client->kick_angles);
	}

	// if the scoreboard is up, update it
	if (ent->client->showscores && !(level.framenum & 31) )
	{
		DeathmatchScoreboardMessage (ent, ent->enemy);
		gi.unicast (ent, false);
	}
}

