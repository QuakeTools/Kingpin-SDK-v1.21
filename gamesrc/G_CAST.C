#include "g_local.h"


//
// cast weapons
//

//FIXME cast members should call these with a totally accurate direction
// and we can mess it up based on skill.  Spread should be for normal
// and we can tighten or loosen based on skill.  We could muck with
// the damages too, but I'm not sure that's such a good idea.
void cast_fire_bullet (edict_t *self, vec3_t start, vec3_t dir, int damage, int kick, int hspread, int vspread, int flashtype)
{
	fire_bullet (self, start, dir, damage, kick, hspread, vspread, MOD_UNKNOWN);

	gi.WriteByte (svc_muzzleflash2);
	gi.WriteShort (self - g_edicts);
	gi.WriteByte (flashtype);
	gi.multicast (start, MULTICAST_PVS);

}

void cast_fire_shotgun (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int hspread, int vspread, int count, int flashtype)
{
	fire_shotgun (self, start, aimdir, damage, kick, hspread, vspread, count, MOD_UNKNOWN);

	gi.WriteByte (svc_muzzleflash2);
	gi.WriteShort (self - g_edicts);
	gi.WriteByte (flashtype);
	gi.multicast (start, MULTICAST_PVS);
}

void cast_fire_blaster (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int flashtype, int effect)
{
	fire_blaster (self, start, dir, damage, speed, effect, false);

	gi.WriteByte (svc_muzzleflash2);
	gi.WriteShort (self - g_edicts);
	gi.WriteByte (flashtype);
	gi.multicast (start, MULTICAST_PVS);
}	

void cast_fire_grenade (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int flashtype)
{
	fire_grenade (self, start, aimdir, damage, speed, 2.5, damage+40);

	gi.WriteByte (svc_muzzleflash2);
	gi.WriteShort (self - g_edicts);
	gi.WriteByte (flashtype);
	gi.multicast (start, MULTICAST_PVS);
}

void cast_fire_rocket (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int flashtype)
{
	fire_rocket (self, start, dir, damage, speed, damage+20, damage);

	gi.WriteByte (svc_muzzleflash2);
	gi.WriteShort (self - g_edicts);
	gi.WriteByte (flashtype);
	gi.multicast (start, MULTICAST_PVS);
}	

void cast_fire_railgun (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int flashtype)
{
	fire_rail (self, start, aimdir, damage, kick);

	gi.WriteByte (svc_muzzleflash2);
	gi.WriteShort (self - g_edicts);
	gi.WriteByte (flashtype);
	gi.multicast (start, MULTICAST_PVS);
}

void cast_fire_bfg (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int kick, float damage_radius, int flashtype)
{
	fire_bfg (self, start, aimdir, damage, speed, damage_radius);

	gi.WriteByte (svc_muzzleflash2);
	gi.WriteShort (self - g_edicts);
	gi.WriteByte (flashtype);
	gi.multicast (start, MULTICAST_PVS);
}



//
// Cast utility functions
//

static void M_FliesOff (edict_t *self)
{
	self->s.effects &= ~EF_FLIES;
	self->s.sound = 0;
}

static void M_FliesOn (edict_t *self)
{
	if (self->waterlevel)
		return;
	self->s.effects |= EF_FLIES;
	self->s.sound = gi.soundindex ("infantry/inflies1.wav");
	self->think = M_FliesOff;
	self->nextthink = level.time + 60;
}

void M_FlyCheck (edict_t *self)
{
	if (self->waterlevel)
		return;

	if (random() > 0.5)
		return;

	self->think = M_FliesOn;
	self->nextthink = level.time + 5 + 10 * random();
}
/*
void AttackFinished (edict_t *self, float time)
{
	self->cast_info.attack_finished = level.time + time;
}
*/

void M_CheckGround (edict_t *ent)
{
	vec3_t		point;
	trace_t		trace;

	if (ent->flags & (FL_SWIM|FL_FLY))
		return;

	if (ent->velocity[2] > 100)
	{
		ent->groundentity = NULL;
		return;
	}

// if the hull point one-quarter unit down is solid the entity is on ground
	point[0] = ent->s.origin[0];
	point[1] = ent->s.origin[1];
	point[2] = ent->s.origin[2] - 0.25;

	trace = gi.trace (ent->s.origin, ent->mins, ent->maxs, point, ent, MASK_PLAYERSOLID | MASK_MONSTERSOLID);

	// check steepness
// Xatrix/Ridah, make sure we hit something
if ( trace.fraction < 1 && !trace.allsolid )
// Xatrix/Ridah, make sure we hit something

	if ( trace.plane.normal[2] < 0.5 && !trace.startsolid)
	{
		ent->groundentity = NULL;

// Xatrix/Ridah, added this to help monsters slide off steep walls
		VectorScale (trace.plane.normal, 200 * (trace.plane.normal[2] + 0.1), ent->velocity);

//		if (ent->velocity[2] < 120)
//			ent->velocity[2] = 120;
// Xatrix/Ridah, added this to fix ladder climbing problem

		return;
	}

// Xatrix/Ridah, added this to fix ladder climbing problems
	if ( trace.fraction == 1 )
	{
		// if we're stuck in a solid, try and move out of it
		if (trace.allsolid && ent->health > 0)
		{
			float x, y, z;
			float dist;
			vec3_t vec, dest;

			for (dist = 4; dist < 64; dist+= 24)
			{
				for (x=-1; x<2; x++)
					for (y=-1; y<2; y++)
						for (z=-1; z<2; z++)
						{
							VectorSet( vec, x, y, z );
							VectorNormalize( vec );
							VectorMA( ent->s.origin, dist, vec, dest );

							trace = gi.trace (dest, ent->mins, ent->maxs, dest, ent, MASK_PLAYERSOLID | MASK_MONSTERSOLID);

							if (!trace.allsolid)
							{
								VectorCopy( dest, ent->s.origin );
								goto foundspot;
							}
						}
			}

		}

foundspot:

		ent->groundentity = NULL;
		return;
	}
// Xatrix/Ridah, end.

	// Ridah
	if (trace.ent->svflags & SVF_MONSTER)
	{
		ent->groundentity = NULL;
		return;
	}

//	ent->groundentity = trace.ent;
//	ent->groundentity_linkcount = trace.ent->linkcount;
//	if (!trace.startsolid && !trace.allsolid)
//		VectorCopy (trace.endpos, ent->s.origin);

	// JOSEPH 2-MAY-99
	// Xatrix/Ridah, make sure we hit something
	if ( trace.fraction < 1 )
	{
		// Xatrix/Ridah, make sure we hit something
		if (!trace.startsolid && !trace.allsolid)
		{
			vec3_t move;

			VectorCopy (trace.endpos, ent->s.origin);
			ent->groundentity = trace.ent;
			ent->groundentity_linkcount = trace.ent->linkcount;
			ent->velocity[2] = 0;

			VectorSubtract( ent->last_step_pos, ent->s.origin, move );
			move[2] = 0;

			if (ent->last_step_time < (level.time-0.2) && VectorLength(move) > 40)
			{
				trace_t		trace2;
				
				// JOSEPH 5-JUN-99
				if (ent->classname && strcmp(ent->classname, "cast_dog"))
				{
					ent->s.event = EV_FOOTSTEP0 + ent->footsteptype;
				}
				// END JOSEPH

				VectorCopy( ent->s.origin, ent->last_step_pos );
				ent->last_step_time = level.time;

				trace2 = gi.trace (ent->s.origin, ent->mins, ent->maxs, point, ent, MASK_PLAYERSOLID | MASK_MONSTERSOLID | MASK_WATER);

				
				if (trace2.contents & MASK_WATER)
				{
					ent->footsteptype = 8; 
				}
				else if (trace2.surface->flags & SURF_CONCRETE)
				{
					ent->footsteptype = 0; 
				}
				else if (trace2.surface->flags & SURF_FABRIC)
				{
					ent->footsteptype = 1; 
				}
				else if (trace2.surface->flags & SURF_GRAVEL)
				{
					ent->footsteptype = 2; 
				}	
				else if (trace2.surface->flags & SURF_METAL)
				{
					ent->footsteptype = 3; 
				}
				else if (trace2.surface->flags & SURF_METAL_L)
				{
					ent->footsteptype = 4; 
				}
				else if (trace2.surface->flags & SURF_SNOW)
				{
					ent->footsteptype = 5; 
				}	
				else if (trace2.surface->flags & SURF_TILE)
				{
					ent->footsteptype = 6; 
				}	
				else if (trace2.surface->flags & SURF_WOOD)
				{
					ent->footsteptype = 7; 
				}	
				else if (trace2.surface->flags & SURF_WATER)
				{
					ent->footsteptype = 8; 
				}
				else
				{
					ent->footsteptype = 0; 
				}
			}

			// if standing on an AI, get off
			if (ent->groundentity->svflags & SVF_MONSTER)
			{
				ent->nav_data.goal_index = 0;

				VectorSet( ent->velocity, rand()%400 - 200, rand()%400 - 200, 200 );

				if (ent->groundentity->maxs[2] == ent->groundentity->cast_info.standing_max_z)
				{	// duck
					if (ent->groundentity->cast_info.move_crouch_down)
						ent->groundentity->cast_info.currentmove = ent->groundentity->cast_info.move_crouch_down;
					ent->groundentity->maxs[2] = DUCKING_MAX_Z;
				}

				// avoid
				ent->groundentity->cast_info.avoid( ent->groundentity, ent, false );

			}

		}
	// Xatrix/Ridah, didn't hit anything, so clear ->groundentity
	}
	else
	{
		ent->groundentity = NULL;
	}
	// Xatrix/Ridah, didn't hit anything, so clear ->groundentity
	// END JOSEPH

	// Ridah, do pitch adjustments
	if (ent->cast_info.aiflags & AI_ADJUSTPITCH && ent->health > 0)
	{
		static vec3_t	mins = {-4, -4, 0};
		static vec3_t	maxs = { 4,  4, 4};
		vec3_t	p1, p2;
		vec3_t	start, end;
		vec3_t	fwd, angles;
		float	pitch_diff;
		trace_t	tr;

		AngleVectors( ent->s.angles, fwd, NULL, NULL );

		VectorMA( ent->s.origin, ent->maxs[0]-maxs[0], fwd, start );
		VectorCopy( start, end );
		end[2] += ent->mins[2] - 32;

		tr = gi.trace( start, mins, maxs, end, ent, MASK_PLAYERSOLID | MASK_MONSTERSOLID );

		VectorCopy( tr.endpos, p1 );

		VectorMA( ent->s.origin, -(ent->maxs[0]-maxs[0]), fwd, start );
		VectorCopy( start, end );
		end[2] += ent->mins[2] - 32;

		tr = gi.trace( start, mins, maxs, end, ent, MASK_PLAYERSOLID | MASK_MONSTERSOLID );

		VectorCopy( tr.endpos, p2 );


		VectorSubtract( p1, p2, fwd );
		VectorNormalize( fwd );
		fwd[2] *= 0.5;
		vectoangles( fwd, angles );

		pitch_diff = AngleDiff( ent->s.angles[PITCH], angles[PITCH] );

		if (fabs(pitch_diff) > 120*FRAMETIME)
		{
			if (pitch_diff > 0)
				pitch_diff =  120*FRAMETIME;
			else
				pitch_diff = -120*FRAMETIME;
		}

//		if (pitch_diff)
//			gi.dprintf("PITCH: %f -> ", ent->s.angles[PITCH]);

		ent->s.angles[PITCH] += pitch_diff;

//		if (pitch_diff)
//			gi.dprintf("%f\n", ent->s.angles[PITCH]);
	}
}


void M_CatagorizePosition (edict_t *ent)
{
	vec3_t		point;
	int			cont;

//
// get waterlevel
//
	point[0] = ent->s.origin[0];
	point[1] = ent->s.origin[1];
	point[2] = ent->s.origin[2] + ent->mins[2] + 1;	
	cont = gi.pointcontents (point);

	if (!(cont & MASK_WATER))
	{
		ent->waterlevel = 0;
		ent->watertype = 0;
		return;
	}

	ent->watertype = cont;
	ent->waterlevel = 1;
	point[2] += 26;
	cont = gi.pointcontents (point);
	if (!(cont & MASK_WATER))
		return;

	ent->waterlevel = 2;
	point[2] += 22;
	cont = gi.pointcontents (point);
	if (cont & MASK_WATER)
		ent->waterlevel = 3;
}


void M_WorldEffects (edict_t *ent)
{
	int		dmg;

	if (ent->health > 0)
	{
		if (!(ent->flags & FL_SWIM))
		{
			if (ent->waterlevel < 3)
			{
				ent->air_finished = level.time + 12;
			}
			else if (ent->air_finished < level.time)
			{	// drown!
				if (ent->pain_debounce_time < level.time)
				{
					dmg = 2 + 2 * floor(level.time - ent->air_finished);
					if (dmg > 15)
						dmg = 15;
					T_Damage (ent, world, world, vec3_origin, ent->s.origin, vec3_origin, dmg, 0, DAMAGE_NO_ARMOR, MOD_WATER);
					ent->pain_debounce_time = level.time + 1;
				}
			}
		}
		else
		{
			if (ent->waterlevel > 0)
			{
				ent->air_finished = level.time + 9;
			}
			else if (ent->air_finished < level.time)
			{	// suffocate!
				if (ent->pain_debounce_time < level.time)
				{
					dmg = 2 + 2 * floor(level.time - ent->air_finished);
					if (dmg > 15)
						dmg = 15;
					T_Damage (ent, world, world, vec3_origin, ent->s.origin, vec3_origin, dmg, 0, DAMAGE_NO_ARMOR, MOD_WATER);
					ent->pain_debounce_time = level.time + 1;
				}
			}
		}
	}
	
	if (ent->waterlevel == 0)
	{
		if (ent->flags & FL_INWATER)
		{	
			// JOSEPH 13-MAY-99
			gi.sound (ent, CHAN_BODY, gi.soundindex("actors/player/male/watr_out.wav"), 1, ATTN_NORM, 0);
			// END JOSEPH
			ent->flags &= ~FL_INWATER;
		}
		return;
	}

	if ((ent->watertype & CONTENTS_LAVA) && !(ent->flags & FL_IMMUNE_LAVA))
	{
		if (ent->damage_debounce_time < level.time)
		{
			ent->damage_debounce_time = level.time + 0.2;
			T_Damage (ent, world, world, vec3_origin, ent->s.origin, vec3_origin, 10*ent->waterlevel, 0, 0, MOD_LAVA);
		}
	}
	if ((ent->watertype & CONTENTS_SLIME) && !(ent->flags & FL_IMMUNE_SLIME))
	{
		if (ent->damage_debounce_time < level.time)
		{
			ent->damage_debounce_time = level.time + 1;
			T_Damage (ent, world, world, vec3_origin, ent->s.origin, vec3_origin, 4*ent->waterlevel, 0, 0, MOD_SLIME);
		}
	}
	
	if ( !(ent->flags & FL_INWATER) )
	{	
		if (!(ent->svflags & SVF_DEADMONSTER))
		{
			// JOSEPH 29-MAR-99
			if (ent->watertype & CONTENTS_LAVA)
			{
				//if (random() <= 0.5)
				//	gi.sound (ent, CHAN_BODY, gi.soundindex("actors/player/lava1.wav"), 1, ATTN_NORM, 0);
				//else
				//	gi.sound (ent, CHAN_BODY, gi.soundindex("actors/player/lava2.wav"), 1, ATTN_NORM, 0);
			}
			// END JOSEPH
			// JOSEPH 13-MAY-99
			else if (ent->watertype & CONTENTS_SLIME)
				gi.sound (ent, CHAN_BODY, gi.soundindex("actors/player/male/watr_in.wav"), 1, ATTN_NORM, 0);
			else if (ent->watertype & CONTENTS_WATER)
				gi.sound (ent, CHAN_BODY, gi.soundindex("actors/player/male/watr_in.wav"), 1, ATTN_NORM, 0);
			// END JOSEPH
		}

		ent->flags |= FL_INWATER;
		ent->damage_debounce_time = 0;
	}
}


void M_droptofloor (edict_t *ent)
{
	vec3_t		end;
	trace_t		trace;

	ent->s.origin[2] += 1;
	VectorCopy (ent->s.origin, end);
	end[2] -= 256;
	
	trace = gi.trace (ent->s.origin, ent->mins, ent->maxs, end, ent, MASK_MONSTERSOLID);

	if (trace.fraction == 1 || trace.allsolid)
		return;

	VectorCopy (trace.endpos, ent->s.origin);

	if (ent->solid != SOLID_TRIGGER)
	{
		gi.linkentity (ent);
		M_CheckGround (ent);
		M_CatagorizePosition (ent);
	}
}


void M_SetEffects (edict_t *ent)
{
	ent->s.effects &= ~(EF_COLOR_SHELL|EF_POWERSCREEN);
	ent->s.renderfx &= ~(RF_SHELL_RED|RF_SHELL_GREEN|RF_SHELL_BLUE);

	if (ent->health <= 0)
		return;

}


void M_MoveFrame (edict_t *self)
{
	mmove_t	*move;
	int		index;

	// Ridah, allow for reverse animations
	qboolean	reverse_anim;
	int			lowest_frame, highest_frame;

	move = self->cast_info.currentmove;

	if (move->lastframe < move->firstframe)
	{
		reverse_anim = true;
		lowest_frame = move->lastframe;
		highest_frame = move->firstframe;
	}
	else
	{
		reverse_anim = false;
		lowest_frame = move->firstframe;
		highest_frame = move->lastframe;
	}

	self->nextthink = level.time + FRAMETIME;

	if ((self->cast_info.nextframe) && (self->cast_info.nextframe >= lowest_frame) && (self->cast_info.nextframe <= highest_frame))
	{
		self->s.frame = self->cast_info.nextframe;
		self->cast_info.nextframe = 0;
	}
	else
	{
		if (self->s.frame == move->lastframe)
		{
			if (move->endfunc)
			{
				move->endfunc (self);

				// regrab move, endfunc is very likely to change it
				move = self->cast_info.currentmove;

				if (move->lastframe < move->firstframe)
				{
					reverse_anim = true;
					lowest_frame = move->lastframe;
					highest_frame = move->firstframe;
				}
				else
				{
					reverse_anim = false;
					lowest_frame = move->firstframe;
					highest_frame = move->lastframe;
				}

				// check for death
				if (self->svflags & SVF_DEADMONSTER)
					return;
			}
		}

		if ((self->s.frame < lowest_frame) || (self->s.frame > highest_frame))
		{
			self->s.frame = move->firstframe;
		}
		else
		{
			if (reverse_anim)
			{
				self->s.frame--;

				if (self->s.frame < move->lastframe)
					self->s.frame = move->firstframe;
			}
			else
			{
				self->s.frame++;

				if (self->s.frame > move->lastframe)
					self->s.frame = move->firstframe;
			}
		}
	}

	if (!reverse_anim)
		index = self->s.frame - move->firstframe;
	else
		index = move->firstframe - self->s.frame;

	if (move->frame[index].aifunc)
	{
		move->frame[index].aifunc (self, move->frame[index].dist * self->cast_info.scale);

		// debugging
		if (!self->cast_info.currentmove)
		{	// we really shouldn't do this, but it's better than crashing
			// nasty fix to get the bum not to print this message
			if (strcmp (self->classname, "cast_bum_sit"))
				gi.dprintf( "M_MoveFrame: NULL currentmove\n" );
			self->cast_info.currentmove = move;
		}
	}

	if (move->frame[index].thinkfunc)
		move->frame[index].thinkfunc (self);
}

// thug2 HACK
extern mmove_t thug2_move_ambstand1;
extern void thug2_stand_up( edict_t *self );
extern void thug2_end_stand( edict_t *self );
extern void thug2_avoid ( edict_t *self, edict_t *other, qboolean face );

void cast_think (edict_t *self)
{
#include "ai_thug2.h"


	// Ridah, turn it off before each frame, so it's only on when being fired
	self->s.renderfx2 &= ~RF2_FLAMETHROWER;
	

	// Ridah, if in cutscene, only let those in the scene actually think
	if (level.cut_scene_time)
	{
//		if (!gi.inPVS(self->s.origin, level.cut_scene_origin))
		if (self->cast_group == 1)
		{
			self->nextthink = level.time + 0.3;
			return;
		}
	}

	if (self->enemy && (self->enemy->health <= 0))
	{
		self->enemy = NULL;

		// go back to the start pos if we're not doing anything
		if (	!(self->cast_info.aiflags & AI_TAKE_COVER)
			&&	!(self->goal_ent)
			&&	(self->cast_info.currentmove->frame->aifunc == ai_stand)
			&&	(self->start_ent)
			&&	(VectorDistance( self->s.origin, self->start_ent->s.origin) > 256))
		{
			self->goal_ent = self->start_ent;
		}
	}


	// HACK, make sure this gets cleared
	if ((self->cast_info.aiflags & AI_TAKECOVER_IGNOREHEALTH) && !(self->cast_info.aiflags & AI_TAKE_COVER))
		self->cast_info.aiflags &= ~AI_TAKECOVER_IGNOREHEALTH;

	// Another HACK, so thug_sit's do the proper sit -> stand animation when they need to
	if (	self->health > 0
		&&	self->cast_info.avoid == thug2_avoid
		&&	self->cast_info.move_stand != &thug2_move_ambstand1
		&&	(	(self->cast_info.currentmove->firstframe < FRAME_ambsit1_01)
			 ||	(self->cast_info.currentmove->firstframe > FRAME_cards7_18)))
	{	// they're doing something other than sitting, so clear the flag and prevent them from sitting again
		thug2_stand_up( self );
	}

	// so we know how far we've fallen from
	if (!self->groundentity)
	{
		if (self->last_offground < (level.time - 0.1))
			self->fall_height = self->s.origin[2];
		else if (self->fall_height < self->s.origin[2])
			self->fall_height = self->s.origin[2];

		self->last_offground = level.time;
	}
	else
	{
		self->last_onground = level.time;
	}

	if (self->cast_info.currentmove)
		M_MoveFrame (self);
	else
	{
		if (!strcmp (self->classname, "cast_bum_sit"))
		{
			self->health = 0;
			self->die (self, world, world, 10, self->s.origin, PART_BODY, 0);
			return;
		}
		else 
		// todo find out how the bum is getting here and causing the crash
		gi.dprintf ("classname:%s\n", self->classname);
	}

	if (self->linkcount != self->cast_info.linkcount)
	{
		self->cast_info.linkcount = self->linkcount;
		M_CheckGround (self);

		if (self->groundentity)
			VectorClear( self->velocity );
	}

	// make sure viewheight is correct
	self->viewheight = self->maxs[2] - 4;

	M_CatagorizePosition (self);

	M_WorldEffects (self);
	M_SetEffects (self);

	if (self->enemy && (self->enemy->health <= 0))
		self->enemy = NULL;

	// JOSEPH 30-NOV-98
	if (self->misstime && self->missent)
	{
		if (self->onarampage)
		{
			self->goal_ent = self->enemy;	
		}
		else if (visible(self, self->missent) && (self->timemissing <= self->misstime))
		{
			self->timemissing = 0;
		}
		else
		{
			self->timemissing += 1.0;

			if (self->timemissing > self->misstime)
			{
				if (visible(self, self->missent))
				{
					self->onarampage = 1;
				}
				else
				{
					self->goal_ent = self->missent;
				}
			}
		}
	}
	// END JOSEPH
/*
	// Ridah, HACK: character's that don't die after flamedeath, force them to die now
	if (	(self->health <= 0)
		&&	(self->cast_info.currentmove->endfunc != AI_EndDeath))
	{
		extern void Killed (edict_t *targ, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject);

		self->deadflag = 0;
		// self->die( self, world, world, 10, self->s.origin, PART_BODY, 0);
		Killed (self, self, self, 10, self->s.origin, PART_BODY, 0);
	}
*/
}


/*
================
cast_use

Using a cast member makes it:

  if it has a combattarget, will run to it,
  ELSE get angry at the current activator
================
*/
void cast_use (edict_t *self, edict_t *other, edict_t *activator)
{
	cast_memory_t	*mem;

	if (self->next_combattarget)
	{
		self->combattarget = self->next_combattarget;
		self->next_combattarget = NULL;
	}

	if (self->combattarget)
		AI_Goto_CombatTarget( self );

	if (self->health <= 0)
		return;

	if (self->enemy)
		return;
	if (self->health <= 0)
		return;

	// check for special Episode script handling
	if (EP_CastUse( self, other, activator ))
		return;

	mem = level.global_cast_memory[self->character_index][activator->character_index];

	if (!mem || (mem->memory_type == MEMORY_TYPE_FRIEND))
		return;

	AI_MakeEnemy ( self, activator, 0 );

}


void cast_start_go (edict_t *self);


void cast_triggered_spawn (edict_t *self)
{
	self->s.origin[2] += 1;
	KillBox (self);

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_STEP;
	self->svflags &= ~SVF_NOCLIENT;
	self->air_finished = level.time + 12;
	gi.linkentity (self);

	cast_start_go (self);

	// Ridah, changed this, must set (spawnflags & 1) to make the AI hostile at the activator

/*
	if (self->enemy && !(self->spawnflags & 1) && !(self->enemy->flags & FL_NOTARGET))
	{
		AI_StartAttack (self, self->enemy);
	}
	else
	{
		self->enemy = NULL;
	}
*/
}

void cast_triggered_spawn_use (edict_t *self, edict_t *other, edict_t *activator)
{
	// we have a one frame delay here so we don't telefrag the guy who activated us
	self->think = cast_triggered_spawn;
	self->nextthink = level.time + FRAMETIME;

// Ridah, try to add them to the character list
	if (!AddCharacterToGame(self))
	{
		G_FreeEdict (self);
		return;
	}
// Ridah, done.

	if (activator->client && (self->spawnflags & 1))
		AI_MakeEnemy (self, activator, 0);

	self->use = cast_use;
}

void cast_triggered_start (edict_t *self)
{
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_NOCLIENT;
	self->nextthink = 0;
	self->use = cast_triggered_spawn_use;
}


/*
================
cast_death_use

When a cast member dies, they fire all of their targets with the current
enemy as activator.
================
*/
void cast_death_use (edict_t *self)
{
	self->flags &= ~(FL_FLY|FL_SWIM);

	if (self->item)
	{
		Drop_Item (self, self->item);
		self->item = NULL;
	}

	if (self->deathtarget)
	{
		self->target = self->deathtarget;
	}
	else
	{
		// So we can process a death even if they don't have a ->deathtarget
		EP_CastUse( self, self, self->enemy );

		return;		// Ridah, added this since we don't clear the ->target at startup anymore, and we don't went to fire a path_corner when we die
	}

//	if (!self->target)
//		return;

	G_UseTargets (self, self->enemy);
}


//============================================================================

qboolean cast_start (edict_t *self)
{
	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return false;
	}

// Ridah, try to add them to the character list
	if (!(self->spawnflags & 2) && !AddCharacterToGame(self))
	{
		G_FreeEdict (self);
		return false;
	}
// Ridah, done.

	AI_InitMemory( self );
	EP_SetNameIndex( self );

	EP_SpawnFlags (self);

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
//self->s.renderfx2 |= RF2_FLAMETHROWER;

//self->flags |= FL_GODMODE;

	level.total_monsters++;

	self->cast_info.standing_max_z = self->maxs[2];

	if (!self->moral)
		self->moral = ((int)self->s.origin[0]) % MORAL_MAX;

	self->nextthink = level.time + FRAMETIME;
	self->svflags |= SVF_MONSTER;
	self->s.renderfx |= RF_FRAMELERP;
	self->takedamage = DAMAGE_AIM;
	self->air_finished = level.time + 12;
	self->use = cast_use;

	// Ridah, hired guys default to 200 health, so they don't die so quick
	if (self->cast_group == 1 && self->health == 100)
		self->health = 200;

	self->max_health = self->health;

	self->clipmask = MASK_MONSTERSOLID;

	self->s.skinnum = self->skin;
	self->deadflag = DEAD_NO;
	self->svflags &= ~SVF_DEADMONSTER;

	// talk by default
	self->cast_info.aiflags |= AI_TALK;

	if (!self->cast_info.checkattack)
		self->cast_info.checkattack = AI_CheckAttack;
	VectorCopy (self->s.origin, self->s.old_origin);

// Ridah, new AI system
	if (!self->cast_info.max_attack_distance)
		self->cast_info.max_attack_distance = DEFAULT_MAX_ATTACK_DISTANCE;

	if (!self->cast_info.max_sighting_distance)
		self->cast_info.max_sighting_distance = DEFAULT_MAX_SIGHTING_DISTANCE;
// Ridah, done.

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}

	// randomize what frame they start on
	if (self->cast_info.currentmove)
		self->s.frame = self->cast_info.currentmove->firstframe + (rand() % (self->cast_info.currentmove->lastframe - self->cast_info.currentmove->firstframe + 1));

//Xatrix/Ridah/Navigator: init nav data
	self->active_node_data = level.node_data;
	self->nav_data.cache_node = -1;
// END: Xatrix/Ridah/Navigator: init current node

	return true;
}

void cast_start_go (edict_t *self)
{
	vec3_t	v;

// Ridah, debugging ladders
//self->cast_group = 1;

	if (self->health <= 0)
		return;

/*
	// check for target to combat_point and change to combattarget
	if (self->target)
	{
		qboolean	notcombat;
		qboolean	fixup;
		edict_t		*target;

		target = NULL;
		notcombat = false;
		fixup = false;
		while ((target = G_Find (target, FOFS(targetname), self->target)) != NULL)
		{
			if (strcmp(target->classname, "point_combat") == 0)
			{
				self->combattarget = self->target;
				fixup = true;
			}
			else
			{
				notcombat = true;
			}
		}
		if (notcombat && self->combattarget)
			gi.dprintf("%s at %s has target with mixed types\n", self->classname, vtos(self->s.origin));
		if (fixup)
			self->target = NULL;
	}
*/
	// validate combattarget
	if (self->combattarget)
	{
		edict_t		*target;

		target = NULL;
		while ((target = G_Find (target, FOFS(targetname), self->combattarget)) != NULL)
		{
			if (strcmp(target->classname, "path_corner") != 0)
			{
				gi.dprintf("%s at (%i %i %i) has a bad combattarget %s : %s at (%i %i %i)\n",
					self->classname, (int)self->s.origin[0], (int)self->s.origin[1], (int)self->s.origin[2],
					self->combattarget, target->classname, (int)target->s.origin[0], (int)target->s.origin[1],
					(int)target->s.origin[2]);
			}
		}
	}

	// check for a guard_ent
	if (self->guard_target)
	{
		edict_t		*target;

		target = NULL;
		if ((target = G_Find (target, FOFS(targetname), self->guard_target)) != NULL)
		{
			self->guard_ent = target;
		}
		else
		{
			gi.dprintf("%s at (%i %i %i) has an un-matched guard_target (%s)\n",
				self->classname,
				(int)self->s.origin[0], (int)self->s.origin[1], (int)self->s.origin[2],
				self->guard_target );
		}
	}

	if (self->target)
	{
		self->goal_ent = G_PickTarget(self->target);
		if (!self->goal_ent)
		{
			gi.dprintf ("%s can't find target %s at %s\n", self->classname, self->target, vtos(self->s.origin));
			self->target = NULL;
		}
		else if (strcmp (self->goal_ent->classname, "path_corner") == 0)
		{
			VectorSubtract (self->goal_ent->s.origin, self->s.origin, v);
			self->ideal_yaw = self->s.angles[YAW] = vectoyaw(v);

// Ridah, 5-7-99, prevent guy at intro appearing upright after reloading SR1
			if (!(self->spawnflags & 2) && (!self->name || (strcmp(self->name, "IntroGuy") != 0)))
				self->cast_info.pausetime = level.time + 3;
			self->cast_info.currentmove = self->cast_info.move_stand;
		}
//		else
//		{
//			self->goal_ent = NULL;
//		}

		// so we actually start walking in ai_stand()
		self->goal_ent = NULL;
	}

	if (self->leader_target)
	{
		if (!(self->leader = G_Find( NULL, FOFS(name), self->leader_target )))
		{
			gi.dprintf( "%s has un-matched leader_target at: %s\n", self->classname, vtos( self->s.origin ));
		}
	}

//	if (!self->goal_ent)
	{	// make them return to this position in the future
		edict_t	*ent;

		ent = G_Spawn();
		VectorCopy( self->s.origin, ent->s.origin );
		VectorCopy( self->mins, ent->mins );
		VectorCopy( self->maxs, ent->maxs );
		ent->classname = "cast_origin";

		ent->owner = self;

		self->start_ent = ent;
	}

	// Health triggered events
	if (self->health_target)
	{
		if (!self->health_threshold)
			gi.dprintf( "Warning: %s has health_target without a health_threshold at %s\n", self->classname, vtos(self->s.origin) );
	}
	if (self->health_target2)
	{
		if (!self->health_threshold2)
			gi.dprintf( "Warning: %s has health_target2 without a health_threshold2 at %s\n", self->classname, vtos(self->s.origin) );
	}
	if (self->health_target3)
	{
		if (!self->health_threshold3)
			gi.dprintf( "Warning: %s has health_target3 without a health_threshold3 at %s\n", self->classname, vtos(self->s.origin) );
	}

	self->think = cast_think;
	self->nextthink = level.time + FRAMETIME;
}

void walking_cast_start_go (edict_t *self)
{
	if (!(self->spawnflags & 2) && level.time < 1)
	{
		M_droptofloor (self);

		if (self->groundentity)
			if (!M_walkmove (self, 0, 0))
				gi.dprintf ("%s in solid at %s\n", self->classname, vtos(self->s.origin));
	}
	
	if (!self->yaw_speed)
		self->yaw_speed = 40;
	self->viewheight = self->cast_info.standing_max_z - 4;

	cast_start_go (self);


	if (self->cast_group == 1 && !self->name)
	{
		gi.dprintf( "\n** WARNING: friendly %s without a NAME.\n  All friendly characters MUST have a name.\n\n", self->classname );
	}

	if (self->spawnflags & 2)
		cast_triggered_start (self);
}

void walking_cast_start (edict_t *self)
{

	if (!self->cast_info.scale)
		self->cast_info.scale = MODEL_SCALE;

	self->current_territory = self->cast_group;		// assume we start in our territory
	if (self->current_territory == 1)	// player's group doesn't have a territory as such
		self->current_territory = 0;

	self->s.scale = self->cast_info.scale - 1.0;
	
	self->think = walking_cast_start_go;
	cast_start (self);
}


void flying_cast_start_go (edict_t *self)
{
	if (!M_walkmove (self, 0, 0))
		gi.dprintf ("%s in solid at %s\n", self->classname, vtos(self->s.origin));

	if (!self->yaw_speed)
		self->yaw_speed = 10;
	self->viewheight = self->cast_info.standing_max_z - 4;

	cast_start_go (self);

	if (self->spawnflags & 2)
		cast_triggered_start (self);
}


void flying_cast_start (edict_t *self)
{
	self->flags |= FL_FLY;
	self->think = flying_cast_start_go;
	cast_start (self);
}


void swimming_cast_start_go (edict_t *self)
{
	if (!self->yaw_speed)
		self->yaw_speed = 10;
	self->viewheight = 10;

	cast_start_go (self);

	if (self->spawnflags & 2)
		cast_triggered_start (self);
}

void swimming_cast_start (edict_t *self)
{
	self->flags |= FL_SWIM;
	self->think = swimming_cast_start_go;
	cast_start (self);
}

qboolean DeathByGib( edict_t *self, edict_t *inflictor, edict_t *attacker, float damage )
{
	// Ridah, never show gibs if parental lock is on
	if (cl_parental_lock->value)
		return false;

	if (inflictor->client)
		return false;

	if (inflictor == attacker)
	{
		return (damage > 80);	// so pistol doesn't gib
	}
	else	// rocket or grenade
	{
		return (damage >= 50);
	}
}
