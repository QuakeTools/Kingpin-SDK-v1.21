#include "g_local.h"
#include "ai_runt.h"

#include "voice_punk.h"

void runt_end_kneel_attack( edict_t *self );
void runt_talk( edict_t *self );
void runt_end_stand( edict_t *self );
void runt_kneel_shoot( edict_t *self );
void runt_talk_think( edict_t *self );

void runt_firegun( edict_t *self, vec3_t ofs );
void runt_right_fire( edict_t *self );
void runt_left_fire( edict_t *self );
void runt_firegun_right( edict_t *self );
void runt_firegun_left( edict_t *self );

void runt_show_guns( edict_t *self );
void runt_climb_loop( edict_t *self );
void runt_melee( edict_t *self );

void runt_evade_amb( edict_t *self );
void runt_evade_adjust( edict_t *self );
void runt_evade_checkadjust( edict_t *self );

void runt_catch_fire( edict_t *self, edict_t *other );

// function that will bail out of the melee attack
// if runt doesnt stand a chance of hitting his enemy
void runt_melee_bail (edict_t *self);

#define	RUNT_MELEE		64	// spawnflag

// =========================================================================

#include "ai_runt_tables.h"

// =========================================================================

void runt_backoff( edict_t *self, edict_t *other )
{
	if (self->name_index == NAME_JESUS)
	{
		Voice_Random (self, self->enemy, &sr_jesus[6], 10); 
	}
	else if (self->name_index == NAME_KINGPIN)
		Voice_Random (self, self->enemy, &kingpin[6], 10); 
	else
		Voice_Random( self, other, m_backoff, NUM_BACKOFF );
}

void runt_catch_fire( edict_t *self, edict_t *other )
{
	self->enemy = NULL;		// stop attacking
	self->cast_info.currentmove = &runt_move_run_on_fire;
}

void runt_evade_amb( edict_t *self )
{
	if (self->enemy && self->moral > 2)
		self->cast_info.currentmove = &runt_move_melee_amb1;
	else
	self->cast_info.currentmove = &runt_move_evade_amb;
}

void runt_evade_checkadjust( edict_t *self )
{
	if (self->enemy && !directly_infront(self, self->enemy ))
		self->cast_info.currentmove = &runt_move_evade_adjust;
	else if (self->cast_info.avoid_ent && !directly_infront(self, self->cast_info.avoid_ent ))
		self->cast_info.currentmove = &runt_move_evade_adjust;
}

void runt_evade_adjust (edict_t *self )
{
	vec3_t vec;
	edict_t	*other;

	if (self->enemy)
		other = self->enemy;
	else if (self->cast_info.avoid_ent)
		other = self->cast_info.avoid_ent;
	else
		return;

	VectorSubtract( other->s.origin, self->s.origin, vec );
	VectorNormalize( vec );
	self->ideal_yaw = vectoyaw( vec );
}

void runt_end_kneel_attack( edict_t *self )
{
	AI_EndAttack(self);

	if (self->cast_info.currentmove == self->cast_info.move_stand)
		self->cast_info.currentmove = &runt_move_kneel_up;
}

void runt_talk_think( edict_t *self )
{
	AI_TalkThink( self, true );
}

void runt_talk( edict_t *self )
{
	int rnd;

	// only make talking gesture if we've recently said something
	if (!(self->cast_info.aiflags & AI_REPEAT_TALK_JESTURE) && self->last_talk_time < (level.time - 1.0))
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
		return;
	}

	if (self->cast_info.currentmove != self->cast_info.move_stand)
		return;

	rnd = rand() % 9;

	if (rnd < 1)
		self->cast_info.currentmove = &runt_move_talk1;
	else if (rnd < 2)
		self->cast_info.currentmove = &runt_move_talk2;
	else if (rnd < 3)
		self->cast_info.currentmove = &runt_move_talk3;
	else if (rnd < 4)
		self->cast_info.currentmove = &runt_move_talk4;
	else if (rnd < 5)
		self->cast_info.currentmove = &runt_move_talk5;
	else if (rnd < 6)
		self->cast_info.currentmove = &runt_move_talk6;
	else if (rnd < 7)
		self->cast_info.currentmove = &runt_move_talk7;
	else
		self->cast_info.currentmove = &runt_move_talk8;
}

void runt_avoid ( edict_t *self, edict_t *other, qboolean face )
{
	vec3_t	vec;

	if (self->health <= 0)
		return;

	if (!self->groundentity)
		return;

	self->cast_info.last_avoid = level.time;

	if (face)
	{	// turn to face them
		VectorSubtract( other->s.origin, self->s.origin, vec );
		self->cast_info.avoid_ent = other;
	}
	else
	{	// turn to face away from them
		VectorSubtract( self->s.origin, other->s.origin, vec );
		self->cast_info.avoid_ent = NULL;
	}
	VectorNormalize( vec );

	self->ideal_yaw = vectoyaw( vec );

	if (self->maxs[2] > DUCKING_MAX_Z)
	{

//#if 0	// Ridah, these don't look right, and translations are incorrect
		if (self->cast_info.aiflags & AI_NOWALK_FACE)
		{
			if (face)
			{
				int		side_result;

				side_result = AI_SideTrace( self, 48, 90, SIDE_RANDOM );

				if (side_result == AI_SideTrace( self, 48, 90 + (self->ideal_yaw - self->s.angles[YAW]), side_result ))
				{
					if (side_result < 0)
						self->cast_info.currentmove = &runt_move_lside_step;
					else
						self->cast_info.currentmove = &runt_move_rside_step;

					return;
				}

				// if no move set, just turn to face
				M_ChangeYaw( self );

				return;
			}
		}
//#endif

		if ((VectorDistance( self->s.origin, other->s.origin ) > 72) || !face)
			self->cast_info.currentmove = &runt_move_avoid_walk;
		else
			self->cast_info.currentmove = &runt_move_avoid_reverse_walk;

	}
	else
	{
		self->cast_info.currentmove = &runt_move_crouch_avoid_walk;
	}

}

void runt_end_stand( edict_t *self )
{
	if (self->cast_info.move_stand_evade && (self->last_stand_evade > (level.time - 3)))
		return;

	if (self->cast_info.currentmove == self->cast_info.move_crstand)
		return;


//	if (	((!self->cast_group) && (random() < 0.8))
//		||	((self->cast_group) && (random() < 0.3)))
	{	// stand normally

		self->cast_info.currentmove = self->cast_info.move_stand;

//		return;
	}

	AI_CheckTalk(self);
}

void runt_show_guns( edict_t *self )
{
	self->s.model_parts[PART_GUN].invisible_objects = 0;
	self->s.model_parts[PART_GUN2].invisible_objects = 0;
}

void runt_kneel_shoot( edict_t *self )
{
	self->cast_info.currentmove = &runt_move_knl_shoot;
}

void runt_long_attack( edict_t *self )
{
	// keep running, and try to fire if possible

	if (self->maxs[2] < self->cast_info.standing_max_z)
		return;

	if (self->s.model_parts[PART_GUN].invisible_objects)
	{	// pull guns out
		self->cast_info.currentmove = &runt_move_pull_guns;
		return;
	}

	self->cast_info.currentmove = &runt_move_run_shoot;
}

// runt_attack:
// returns TRUE if starting an attack
qboolean runt_attack( edict_t *self )
{
	vec3_t	vec;
	float dist;

	// this is where we would start some of the fancy side-ways or rolling attacks

	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		if ((self->cast_info.aiflags & AI_DUCKATTACK) && (rand()%20 < 1))
		{	// stop duck attacking
			self->cast_info.aiflags &= ~AI_DUCKATTACK;
			self->maxs[2] = self->cast_info.standing_max_z;
			if (ValidBoxAtLoc( self->s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID ))
			{
				self->cast_info.currentmove = self->cast_info.move_stand_up;
				self->s.frame = self->cast_info.move_stand_up->firstframe;
				return true;
			}
			else
			{
				self->maxs[2] = DUCKING_MAX_Z;
			}
		}

		if (self->cast_info.aiflags & AI_MELEE)
		{	// try to stand at all costs
			self->maxs[2] = self->cast_info.standing_max_z;

			if (ValidBoxAtLoc( self->s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID ))
				goto standing;

			self->maxs[2] = DUCKING_MAX_Z;
			// gi.dprintf( "ANIM TODO: crouch melee attack\n" );
			{
				int rval;

				rval = rand()%5;

				if (rval == 1)
					self->cast_info.currentmove = &runt_move_low_melee1;
				else if (rval == 2)
					self->cast_info.currentmove = &runt_move_low_melee2;
				else if (rval == 3)
					self->cast_info.currentmove = &runt_move_low_melee3;
				else if (rval == 4)
					self->cast_info.currentmove = &runt_move_low_melee4;
				else
					self->cast_info.currentmove = &runt_move_low_melee5;
			}

			return true;	// can't attack
		}
		
		// HACK TO SHOW THE GUNS
		self->s.model_parts[PART_GUN].invisible_objects = 0;
		self->s.model_parts[PART_GUN2].invisible_objects = 0;

		self->cast_info.currentmove = &runt_move_crch_shoot;
		return true;
	}
	else if (!(self->cast_info.aiflags & AI_MELEE) && (rand()%20 < 1))	// duck attack
	{

		self->viewheight = -4;

		if (AI_ClearSight( self, self->enemy, false ))
		{
//gi.dprintf("5\n");
			self->cast_info.aiflags |= AI_DUCKATTACK;
			self->maxs[2] = DUCKING_MAX_Z;
			self->cast_info.currentmove = self->cast_info.move_crouch_down;

			return true;
		}
	}

standing:

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	dist = VectorNormalize( vec );

	if (self->cast_info.aiflags & AI_MELEE)
	{
		qboolean attack=false;

		if (dist < 64)
		{
			attack = true;
		}
		else	// are they running towards us?
		{
			VectorSubtract( self->enemy->s.origin, self->s.origin, vec );

			if ((VectorLength(vec) < 200) && (DotProduct(vec, self->enemy->velocity) < 0))
			{
				attack = true;
			}
		}

		if (attack)
		{
			int rnd;

			self->ideal_yaw = vectoyaw(vec);

			M_ChangeYaw( self );

			// JOSEPH 12-MAR-99
			Voice_Random( self, self->enemy, grunting, 5);
			// END JOSEPH			
			
			if (self->maxs[2] > self->enemy->maxs[2])
			{
				self->cast_info.currentmove = &runt_move_low_melee1;
			}
			else
			{
				rnd = rand()%5;

				switch (rnd)
				{
				case 0 :
					self->cast_info.currentmove = &runt_move_melee1;
					break;
				case 1 :
					self->cast_info.currentmove = &runt_move_melee2;
					break;
				case 2 :
					self->cast_info.currentmove = &runt_move_melee3;
					break;
				case 3 :
					self->cast_info.currentmove = &runt_move_melee4;
					break;
				case 4 :
					self->cast_info.currentmove = &runt_move_melee5;
					break;
				}
			}	

			if (self->maxs[2] > self->enemy->maxs[2] || self->s.origin[2] > self->enemy->s.origin[2])
				self->cast_info.currentmove = &runt_move_low_melee1;

			self->cast_info.aiflags &=~ AI_RUSH_THE_PLAYER;
			return true;
		}
		else if (dist < 128)
		{
			self->ideal_yaw = vectoyaw(vec);
			M_ChangeYaw( self );

			self->cast_info.currentmove = &runt_move_run_melee;
			return true;
		}
		else if (dist < 400)
			self->cast_info.aiflags |= AI_RUSH_THE_PLAYER;

		return false;
	}

	if (self->s.model_parts[PART_GUN].invisible_objects)
	{	// pull guns out
		self->cast_info.currentmove = &runt_move_pull_guns;
		return true;
	}

	if (self->cast_info.currentmove == &runt_move_knl_shoot)
	{
		// HACK TO SHOW GUN
		self->s.model_parts[PART_GUN].invisible_objects = 0;
		self->s.model_parts[PART_GUN2].invisible_objects = 0;
		self->cast_info.currentmove = &runt_move_knl_shoot;

		return true;
	}


	// Special case: enemy has flamethrower, run backwards, keep firing
	if (	(dist < 384)				// they're close
		&&	(self->enemy->client)
		&&	(self->enemy->client->pers.weapon)
		&&	(stricmp(self->enemy->client->pers.weapon->classname, "weapon_flamethrower") == 0))
	{
		int		side_result;

		// see if we can go backwards
		if (side_result = AI_SideTrace( self, -64, 0, 1 ))
		{
			self->cast_info.currentmove = &runt_move_reverse_run_shoot;
			return true;
		}

	}

	// if just popped out from a corner, just stand here
	if (self->dont_takecover_time > (level.time - 2))
	{
		goto stand_shoot;
	}

	if ((skill->value > random()*2) && (self->cast_info.last_side_attack_time < (level.time - 1)) && (dist > 128))
	{
		int		side_result, side_result2;

		side_result = AI_SideTrace( self, 64, 90, -self->cast_info.last_side_attack );

		if (side_result)
		{
			side_result2 = AI_SideTrace( self, 96, 90, side_result );

			if (side_result2 == side_result)
			{
				if (side_result < 0)
					self->cast_info.currentmove = &runt_move_lside_run;
				else
					self->cast_info.currentmove = &runt_move_rside_run;

				self->ideal_yaw = vectoyaw(vec) + side_result * 90;

				M_ChangeYaw( self );

				self->cast_info.last_side_attack = side_result;
				self->cast_info.last_side_attack_time = level.time;

				return true;
			}
		}

	}

	if (		(self->cast_info.currentmove != &runt_move_shoot)
			&&	(dist > 512)
			&&	(random() < 0.5)
			&&	(directly_infront(self, self->enemy))
			&&	(self->s.model_parts[PART_GUN].invisible_objects))	// only kneel if we haven't drawn our guns yet
	{
		self->cast_info.currentmove = &runt_move_kneel;

		return true;
	}


	// walk shooting?
// Ridah, I don't like this animation
//	if ((dist > 512) && directly_infront( self, self->enemy ) && AI_SideTrace(self, 32, 0, 1 ) )
//	{
//		self->cast_info.currentmove = &runt_move_walk_shoot;
//		return true;
//	}
//	else
	if ((dist < 128) && AI_SideTrace(self, -32, 0, 1 ) )
	{
		self->cast_info.currentmove = &runt_move_reverse_walk_shoot;
		return true;
	}

stand_shoot:

	// normal attack

	self->ideal_yaw = vectoyaw(vec);

	M_ChangeYaw( self );

	self->cast_info.currentmove = &runt_move_shoot;

	return true;
}

void runt_climb_loop(edict_t *self)
{
	self->cast_info.currentmove = &runt_move_clmb_loop;
}


void runt_melee_bail (edict_t *self)
{
	vec3_t	vec;
	float	dist;

	if (self->enemy)
	{
		VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
		dist = VectorNormalize( vec );

		if (dist > 48)
		{
//			AI_EndAttack(self);
			self->cast_info.currentmove = &runt_move_run_melee;
			return;
		}
	}

}

void runt_melee( edict_t *self )
{
	vec3_t	start, offset;
	vec3_t	forward, right;

	float damage = 8;

	if (self->cast_info.currentmove == &runt_move_melee5)
		damage *= 2;		// double handed attack

	if (self->cast_info.currentmove == &runt_move_low_melee1)
		damage *= 3;

	// yell at them?
	if (self->last_talk_time < (level.time - TALK_FIGHTING_DELAY))
	{
		// we can't play any "eat lead" type sounds, because we're not firing lead..

		if (self->cast_group != 1)
			Voice_Random( self, self->enemy, grunting, 5);
		else
			Voice_Random(self, self->enemy, friendlycombat, NUM_FRIENDLYCOMBAT );
	}

	// VectorSet(offset, 0, 8,  self->viewheight - 4);
	VectorSet (offset, 0, 8,  16);

	AngleVectors (self->s.angles, forward, right, NULL);
	if (self->cast_info.currentmove == &runt_move_low_melee1)
		forward[2] -= 0.5;
	G_ProjectSource (self->s.origin, offset, forward, right, start);
	if (self->cast_info.currentmove == &runt_move_low_melee1)
		start[2] -= 8;

	// HACK, higher Moral does more damage
	if (self->moral > 4)
		damage *= 1.0 + (self->moral - 4)*0.25;

	fire_blackjack( self, start, forward, damage, 10, MOD_BLACKJACK );

}

void runt_firegun( edict_t *self, vec3_t ofs )
{
	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	target;
	vec3_t	aim;
	vec3_t	offset;
	int		flash_number;
	float	dist;

	if (self->cast_info.currentmove == &runt_move_knl_shoot)
	{
		if (!directly_infront( self, self->enemy ))
		{
			self->cast_info.currentmove = &runt_move_kneel_up;
			self->s.frame++;		// skip the firing frame since it might have a muzzle flash
			return;
		}

		self->cast_info.aiflags |= AI_FACE_ATTACK;
	}
	else
	{
		if (self->noise_time < (level.time - 1))
		{	// haven't fired for a while, prevent we reloaded
			self->duration = 0;
		}

		// check for reload
		if (	(self->maxs[2] == self->cast_info.standing_max_z)
			&&	!(self->cast_info.aiflags & AI_SIDE_ATTACK)
			&&	(self->duration++ > 20))
		{
			self->duration = 0;
			self->cast_info.currentmove = &runt_move_reload;
			self->s.frame++;		// skip the firing frame since it might have a muzzle flash
			return;
		}
	}

	if (!AI_BeginAttack( self ))
	{
		self->s.frame++;		// skip the firing frame since it might have a muzzle flash
		return;
	}

	self->cast_info.aiflags &= ~AI_FACE_ATTACK;

	// yell at them?
	if (self->last_talk_time < (level.time - TALK_FIGHTING_DELAY))
	{
		if (self->name_index == NAME_JESUS)
		{
			Voice_Random (self, self->enemy, &sr_jesus[6], 10); 
		}
		else if (self->name_index == NAME_KINGPIN)
			Voice_Random (self, self->enemy, &kingpin[6], 10); 
		else if (self->cast_group != 1)
			Voice_Random(self, self->enemy, fightsounds, NUM_FIGHTING);
		else
			Voice_Random(self, self->enemy, friendlycombat, NUM_FRIENDLYCOMBAT );
	}

	// fire the gun

	VectorSet(offset, 0 + ofs[0], 8 + ofs[1],  self->viewheight-8 + ofs[2]);

	AngleVectors (self->s.angles, forward, right, NULL);
	G_ProjectSource (self->s.origin, offset, forward, right, start);

	// project enemy back a bit and target there
	VectorCopy (self->enemy->s.origin, target);
	VectorMA (target, (-0.5 * (random()*0.8 + 0.2)) * (1.0 - (skill->value/4.0)), self->enemy->velocity, target);
	target[2] += self->enemy->viewheight;

	flash_number = MZ2_GUNNER_MACHINEGUN_1;

	VectorSubtract (target, start, aim);
	dist = VectorNormalize (aim);

	self->ideal_yaw = vectoyaw( aim );

	if (	(dist < self->cast_info.max_attack_distance)
		&&	(	((random() < 0.1) && (self->cast_info.last_side_attack_time < (level.time - 2)))
			 ||	(	(!(self->cast_info.aiflags & AI_SIDE_ATTACK) || (self->cast_info.last_side_attack_time < (level.time - 2)))
				 &&	(directly_infront( self->enemy, self))
				 &&	(self->enemy->client)
				 &&	(self->enemy->client->pers.weapon)
				 &&	(self->enemy->client->pers.weapon->ammo))))		// if we are directly infront of them, try to strafe
	{
		if (self->cast_info.aiflags & AI_SIDE_ATTACK)
			self->cast_info.currentmove = &runt_move_shoot;
		else
			self->cast_info.attack( self );
	}

	if (self->acc)
	{
// Ridah, 17-may-99, this was around the wrong way, which caused guys with "cal" set in the map to not do any damage
//		if (self->cal)
		if (!self->cal)
			cast_fire_bullet (self, start, aim, 6, 0, DEFAULT_BULLET_HSPREAD>>self->acc, DEFAULT_BULLET_VSPREAD>>self->acc, flash_number);
		else
			cast_fire_bullet (self, start, aim, self->cal, 0, DEFAULT_BULLET_HSPREAD>>self->acc, DEFAULT_BULLET_VSPREAD>>self->acc, flash_number);
	}
	else
	cast_fire_bullet (self, start, aim, 6, 0, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);

	gi.sound(self, CHAN_WEAPON, gi.soundindex("weapons/machinegun/machgf1b.wav"), 1, ATTN_NORM, 0);

}

void runt_right_fire( edict_t *self )
{
	static vec3_t	ofs = {4, 0, 0};
	runt_firegun( self, ofs );
}

void runt_left_fire( edict_t *self )
{
	static vec3_t	ofs = {-4, 0, 0};
	runt_firegun( self, ofs );
}

void runt_firegun_right( edict_t *self )
{
//	vec3_t	vec;
//	float	oldyaw;
	static vec3_t	ofs = {0,0,0};

	if (!self->enemy)
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
		return;
	}

	if (self->cast_info.aiflags & AI_TURN_BLOCKED)
	{	// abort the side run
		self->cast_info.aiflags &= ~AI_TURN_BLOCKED;
		AI_EndAttack(self);
		return;
	}

	// if the path ahead is not clear, abort
	if (!AI_SideTrace( self, 128, 90, 1 ))
	{
		AI_EndAttack(self);
		return;
	}

/*
	oldyaw = self->s.angles[YAW];

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	VectorNormalize( vec );

	self->s.angles[YAW] = vectoyaw( vec );
*/
	self->cast_info.aiflags |= AI_SIDE_ATTACK;
	runt_firegun(self, ofs);
	self->cast_info.aiflags &= ~AI_SIDE_ATTACK;
/*
	// keep running to the side
	self->ideal_yaw = self->s.angles[YAW] + 90;

	self->s.angles[YAW] = oldyaw;
*/
}

void runt_firegun_left( edict_t *self )
{
//	vec3_t	vec;
//	float	oldyaw;
	static vec3_t	ofs = {0,0,0};

	if (!self->enemy)
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
		return;
	}

	if (self->cast_info.aiflags & AI_TURN_BLOCKED)
	{	// abort the side run
		self->cast_info.aiflags &= ~AI_TURN_BLOCKED;
		AI_EndAttack(self);
		return;
	}

	// if the path ahead is not clear, abort
	if (!AI_SideTrace( self, 128, -90, 1 ))
	{
		AI_EndAttack(self);
		return;
	}

/*
	oldyaw = self->s.angles[YAW];

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	VectorNormalize( vec );

	self->s.angles[YAW] = vectoyaw( vec );
*/
	self->cast_info.aiflags |= AI_SIDE_ATTACK;
	runt_firegun(self, ofs);
	self->cast_info.aiflags &= ~AI_SIDE_ATTACK;
/*
	// keep running to the side
	self->ideal_yaw = self->s.angles[YAW] - 90;

	self->s.angles[YAW] = oldyaw;
*/
}

void think_playthud_runt( edict_t *self )
{
	char Temp[128];

#ifdef __linux__
return;	// linux can't handle this for some reason
#endif

	strcpy ((char*)Temp, "actors/player/bodyfalls/");
		
	if (self->thudsurf & SURF_FABRIC)
	{
		strcat((char*)&Temp[0], (char*)"rug");
	}
	else if (self->thudsurf & SURF_GRAVEL)
	{
		strcat((char*)&Temp[0], (char*)"gravel");
	}
	else if (self->thudsurf & SURF_METAL)
	{
		strcat((char*)&Temp[0], (char*)"metalh");
	}
	else if (self->thudsurf & SURF_METAL_L)
	{
		strcat((char*)&Temp[0], (char*)"metall");
	}
	else if (self->thudsurf & SURF_SNOW)
	{
		strcat((char*)&Temp[0], (char*)"tin");
	}
	else if (self->thudsurf & SURF_TILE)
	{
		strcat((char*)&Temp[0], (char*)"marble");
	}
	else if (self->thudsurf & SURF_WOOD)
	{
		strcat((char*)&Temp[0], (char*)"wood");
	}
	else 
	{
		strcat((char*)&Temp[0], (char*)"pavement");
	}	
	
	if (self->thudsnd == 1)
	{
		strcat((char*)&Temp[0], (char*)"d1.wav");
		gi.positioned_sound (self->s.origin, self, CHAN_VOICE|CHAN_RELIABLE, gi.soundindex((char*)&Temp[0]),
							 1.0, ATTN_NORM, 0);
	}
	else
	{
		strcat((char*)&Temp[0], (char*)"d2.wav");
		gi.positioned_sound (self->s.origin, self, CHAN_VOICE|CHAN_RELIABLE, gi.soundindex((char*)&Temp[0]),
							 1.0, ATTN_NORM, 0);
	}
	
	self->nextthink = level.time + (0.1*20.0);
	self->think = G_FreeEdict;
}

// JOSEPH 19-MAR-99
void runt_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	trace_t	tr;
	vec3_t	end;
	edict_t *playthud1, *playthud2;

	self->takedamage = DAMAGE_YES;

	if (DeathByGib(self, inflictor, attacker, damage))
	{	// gib
		self->deadflag = DEAD_DEAD;
		GibEntity( self, inflictor, damage );
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	if (!(self->cast_info.aiflags & AI_MELEE))
		SpawnTheWeapon (self, "weapon_pistol_e");

	// EP_SpecialEventDeath (self);

	if (!self->onfiretime)
	{
		if (self->name_index == NAME_JESUS)
			Voice_Random (self, self->enemy, &sr_jesus[0], 2); 
		else if (self->name_index == NAME_KINGPIN)
			Voice_Random (self, self->enemy, &kingpin[0], 2); 
		else if (self->name_index == NAME_POPEYE)
			Voice_Random (self, self->enemy, &sy_popeye[19], 3);
		else
			gi.sound (self, CHAN_VOICE, gi.soundindex(va("*death%i.wav", (rand()%4)+1)), 1, ATTN_NORM, 0);
	}

	// regular death
	self->deadflag = DEAD_DEAD;

	VectorCopy (self->s.origin, end);
	end[2] -= 64;
	tr = gi.trace (self->s.origin, self->mins, self->maxs, end, self, MASK_SHOT);

	self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
	self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);

	if (!strcmp(inflictor->classname, "rocket"))
	{
		self->cast_info.currentmove = &runt_move_crch_death1;

		// throw backwards
		VectorNormalize2(inflictor->velocity, self->velocity);

		VectorNegate( self->velocity, self->velocity );
		self->ideal_yaw = vectoyaw( self->velocity );
		VectorNegate( self->velocity, self->velocity );

		VectorMA( self->velocity, 500, self->velocity, self->velocity );
		self->gravity = 0.7;
		self->velocity[2] = 220;

		self->groundentity = NULL;

		playthud1 = G_Spawn();
		VectorCopy (self->s.origin, playthud1->s.origin);
		playthud1->thudsurf = tr.surface->flags;
		playthud1->thudsnd = 1; 
		playthud1->nextthink = level.time + (0.1*6.0);
		playthud1->think = think_playthud_runt;
		gi.linkentity (playthud1);
			
		playthud2 = G_Spawn();
		VectorCopy (self->s.origin, playthud2->s.origin);
		playthud2->thudsurf = tr.surface->flags;
		playthud2->thudsnd = 2; 
		playthud2->nextthink = level.time + (0.1*13.0);
		playthud2->think = think_playthud_runt;
		gi.linkentity (playthud2);				
	}
	else if (mdx_part == PART_HEAD)
	{
		self->cast_info.currentmove = &runt_move_death5;

		playthud1 = G_Spawn();
		VectorCopy (self->s.origin, playthud1->s.origin);
		playthud1->thudsurf = tr.surface->flags;
		playthud1->thudsnd = 1; 
		playthud1->nextthink = level.time + (0.1*7.0);
		playthud1->think = think_playthud_runt;
		gi.linkentity (playthud1);
			
		playthud2 = G_Spawn();
		VectorCopy (self->s.origin, playthud2->s.origin);
		playthud2->thudsurf = tr.surface->flags;
		playthud2->thudsnd = 2; 
		playthud2->nextthink = level.time + (0.1*11.0);
		playthud2->think = think_playthud_runt;
		gi.linkentity (playthud2);			
	}
	else if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		self->cast_info.currentmove = &runt_move_crch_death2;

		playthud1 = G_Spawn();
		VectorCopy (self->s.origin, playthud1->s.origin);
		playthud1->thudsurf = tr.surface->flags;
		playthud1->thudsnd = 1; 
		playthud1->nextthink = level.time + (0.1*6.0);
		playthud1->think = think_playthud_runt;
		gi.linkentity (playthud1);
			
		playthud2 = G_Spawn();
		VectorCopy (self->s.origin, playthud2->s.origin);
		playthud2->thudsurf = tr.surface->flags;
		playthud2->thudsnd = 2; 
		playthud2->nextthink = level.time + (0.1*9.0);
		playthud2->think = think_playthud_runt;
		gi.linkentity (playthud2);			
	}
	else
	{
		int n;

		n = rand() % 5;
		if (n == 0)
		{
			self->cast_info.currentmove = &runt_move_death1;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*7.0);
			playthud1->think = think_playthud_runt;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*14.0);
			playthud2->think = think_playthud_runt;
			gi.linkentity (playthud2);				
		}
		else if (n == 1)
		{
			self->cast_info.currentmove = &runt_move_death2;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*6.0);
			playthud1->think = think_playthud_runt;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*8.0);
			playthud2->think = think_playthud_runt;
			gi.linkentity (playthud2);					
		}
		else if (n == 2)
		{
			self->cast_info.currentmove = &runt_move_death3;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*8.0);
			playthud1->think = think_playthud_runt;
			gi.linkentity (playthud1);

			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*12.0);
			playthud2->think = think_playthud_runt;
			gi.linkentity (playthud2);			
		}
		else if (n == 3)
		{
			self->cast_info.currentmove = &runt_move_death4;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*7.0);
			playthud1->think = think_playthud_runt;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*10.0);
			playthud2->think = think_playthud_runt;
			gi.linkentity (playthud2);					
		}
		else
		{
			self->cast_info.currentmove = &runt_move_death5;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*7.0);
			playthud1->think = think_playthud_runt;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*11.0);
			playthud2->think = think_playthud_runt;
			gi.linkentity (playthud2);					
		}
	}
}
// END JOSEPH

void runt_pain (edict_t *self, edict_t *other, float kick, int damage, int mdx_part, int mdx_subobject)
{
	int		orientation;

	AI_CheckMakeEnemy( self, other );

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3 + random();

	if (skill->value >= 3)
		return;		// no pain anims in nightmare

	// faked client pain sound
	if (self->name_index == NAME_JESUS)
	{
		Voice_Random (self, self->enemy, &sr_jesus[2], 4); 
	}
	else if (self->name_index == NAME_KINGPIN)
		Voice_Random (self, self->enemy, &kingpin[2], 4); 
	else if (self->name_index == NAME_POPEYE)
		Voice_Random (self, self->enemy, &sy_popeye[19], 3);
	else
	{
		int r,l;

		r = 1 + (rand()&1);
		if (self->health < 25)
			l = 25;
		else if (self->health < 50)
			l = 50;
		else if (self->health < 75)
			l = 75;
		else
			l = 100;
		gi.sound (self, CHAN_BODY, gi.soundindex(va("*pain%i_%i.wav", l, r)), 1, ATTN_NORM, 0);
	}

	if (self->cast_info.currentmove == &runt_move_knl_shoot)
		return;		// no pain anim for crouch shoot



	// Ridah, randomly don't play an animation, since it' leaves them WAY open to be killed
	if (skill->value > 0 && rand()%2)
		return;


	if (other->client || (other->svflags & SVF_MONSTER))
	{
		orientation = AI_GetOrientation( self, other );
	}
	else
	{
		orientation = ORIENTATION_CENTER;
	}

	if ((self->maxs[2] < self->cast_info.standing_max_z))
	{	// crouching
		
		if ( mdx_part == PART_HEAD)
			self->cast_info.currentmove = &runt_move_c_pain_head;
		else
		
		switch (orientation)
		{
		case ORIENTATION_CENTER :
			{
				self->cast_info.currentmove = &runt_move_c_pain_chst;
				break;
			}
		case ORIENTATION_LEFT :
			{
				self->cast_info.currentmove = &runt_move_c_pain_Larm;
				break;
			}
		case ORIENTATION_RIGHT :
			{
				self->cast_info.currentmove = &runt_move_c_pain_Rarm;
				break;
			}
		}

	}
	else	// standing
	{

		if (	(mdx_part == PART_BODY)
			||	(other->client && other->client->pers.weapon && !(other->client->pers.weapon->ammo) && (orientation = rand()%2+1)))
		{
			switch (orientation)
			{
			case ORIENTATION_CENTER :
				{
					self->cast_info.currentmove = &runt_move_pain_chst;		
					break;
				}
			case ORIENTATION_LEFT :
				{
					self->cast_info.currentmove = &runt_move_pain_Larm;		
					break;
				}
			case ORIENTATION_RIGHT :
				{
					self->cast_info.currentmove = &runt_move_pain_Rarm;		
					break;
				}
			}
		}
		else if (mdx_part == PART_LEGS)
		{
			switch (orientation)
			{
			case ORIENTATION_CENTER :
				{
					if (infront(self, other))
					{
						self->cast_info.currentmove = &runt_move_pain_crch; 
					}
					else
					{
						self->cast_info.currentmove = &runt_move_pain_butt; 			
					}
					break;
				}
			case ORIENTATION_LEFT :
				{
					self->cast_info.currentmove = &runt_move_pain_Lleg; 			
					break;
				}
			case ORIENTATION_RIGHT :
				{
					self->cast_info.currentmove = &runt_move_pain_Rleg; 			
					break;
				}
			}
		}
		else if (mdx_part == PART_HEAD)
		{
			self->cast_info.currentmove = &runt_move_pain_head; 
		}

	}

}

// =========================================================================

/*QUAKED cast_runt (1 .5 0) (-16 -16 -24) (16 16 48) x TRIGGERED_START x x x IMMEDIATE_FOLLOW_PATH MELEE NOSHADOW
cast_group 0	neutral
cast_group 1	friendly	
cast_group 2 or greater	enemy
guy with the pistol

model="models\actors\runt\"
*/
void SP_cast_runt (edict_t *self)
{
	int i;
	char	*head_skin, *body_skin, *legs_skin;
	int	skin;

	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 48);

	self->s.skinnum = (self->skin-1) * 3;

	if (!self->art_skins)
	{	// use default skins
		self->art_skins = "001 001 001";
	}

	if (self->art_skins)
	{
		// convert spaces to NULL's
		for (i=0; i<11; i++)
			if (self->art_skins[i] == ' ')
				self->art_skins[i] = '\0';

		head_skin = &self->art_skins[0];
		body_skin = &self->art_skins[4];
		legs_skin = &self->art_skins[8];
	}
	else
	{
		head_skin = body_skin = legs_skin = NULL;
	}

	// ------------------------------------------------------------------------
	// initialize all model_part data
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/runt/head.mdx");
	if (head_skin)
	{
		skin = gi.skinindex( self->s.model_parts[PART_HEAD].modelindex, head_skin );
	}
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].baseskin = self->s.model_parts[PART_HEAD].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/runt/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/runt/legs.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_LEGS].modelindex, legs_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].baseskin = self->s.model_parts[PART_LEGS].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/runt/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/runt/body.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_BODY].modelindex, body_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].baseskin = self->s.model_parts[PART_BODY].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/runt/body.mdx", &self->s.model_parts[PART_BODY] );

	if (self->spawnflags & RUNT_MELEE)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/runt/pipe.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/runt/pipe.mdx", &self->s.model_parts[PART_GUN] );

		self->cast_info.aiflags |= AI_MELEE;
	}
	else
	{

		if (self->name_index == NAME_KINGPIN)
		{
			self->s.num_parts++;
			self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/runt/R_king_Pstl.mdx");
			for (i=0; i<MAX_MODELPART_OBJECTS; i++)
				self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;
			gi.GetObjectBounds( "models/actors/runt/R_pstl.mdx", &self->s.model_parts[PART_GUN] );

			// the guns should not be visible until we go to use them
			self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);

			self->s.num_parts++;
			self->s.model_parts[PART_GUN2].modelindex = gi.modelindex("models/actors/runt/L_king_Pstl.mdx");
			for (i=0; i<MAX_MODELPART_OBJECTS; i++)
				self->s.model_parts[PART_GUN2].baseskin = self->s.model_parts[PART_GUN2].skinnum[i] = 0;
			gi.GetObjectBounds( "models/actors/runt/L_pstl.mdx", &self->s.model_parts[PART_GUN2] );

			// the guns should not be visible until we go to use them
			self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
			self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
		}
		else
		{
			self->s.num_parts++;
			self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/runt/R_pstl.mdx");
			for (i=0; i<MAX_MODELPART_OBJECTS; i++)
				self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;
			gi.GetObjectBounds( "models/actors/runt/R_pstl.mdx", &self->s.model_parts[PART_GUN] );

			// the guns should not be visible until we go to use them
			self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);

			self->s.num_parts++;
			self->s.model_parts[PART_GUN2].modelindex = gi.modelindex("models/actors/runt/L_pstl.mdx");
			for (i=0; i<MAX_MODELPART_OBJECTS; i++)
				self->s.model_parts[PART_GUN2].baseskin = self->s.model_parts[PART_GUN2].skinnum[i] = 0;
			gi.GetObjectBounds( "models/actors/runt/L_pstl.mdx", &self->s.model_parts[PART_GUN2] );

			// the guns should not be visible until we go to use them
			self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
			self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);
		}
	}

	if (self->count & 1) // cigar
	{
		self->s.num_parts++;
		self->s.model_parts[PART_CIGAR].modelindex = gi.modelindex("models/actors/runt/cigar.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_CIGAR].baseskin = self->s.model_parts[PART_CIGAR].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/runt/cigar.mdx", &self->s.model_parts[PART_CIGAR] );
	}

	if (self->count & 2) // fedora hat
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/runt/fedora.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/runt/fedora.mdx", &self->s.model_parts[PART_HAT] );
	}
	else if (self->count & 4) // stetson hat
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/runt/stetson.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/runt/stetson.mdx", &self->s.model_parts[PART_HAT] );
	}
	else if (self->count & 8) // cap (hat)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/runt/cap.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/runt/cap.mdx", &self->s.model_parts[PART_HAT] );
	}
	
	// remove NULL's
	if (self->art_skins)
		self->art_skins[3] = self->art_skins[7] = ' ';

	// ------------------------------------------------------------------------

	if (!self->health)
		self->health = 100;

	self->gib_health = -200;
	self->mass = 200;

	self->gender = GENDER_MALE;

	self->pain = runt_pain;
	self->die = runt_die;

	self->cast_info.checkattack = AI_CheckAttack;

	self->cast_info.attack = runt_attack;
	self->cast_info.long_attack = runt_long_attack;
	self->cast_info.talk = runt_talk;
	self->cast_info.avoid = runt_avoid;
	self->cast_info.backoff = runt_backoff;

	self->cast_info.catch_fire = runt_catch_fire;

	self->cast_info.max_attack_distance = 2000;

	self->cast_info.move_stand = &runt_move_amb_stand;
	self->cast_info.move_crstand = &runt_move_crch_amb_sdt;

	self->cast_info.move_run = &runt_move_run_guns_dn;
	self->cast_info.move_runwalk = &runt_move_walk_guns_dn;
	self->cast_info.move_crwalk = &runt_move_crouch_walk;

	self->cast_info.move_jump = &runt_move_jump;

	self->cast_info.move_avoid_walk = &runt_move_avoid_walk;
	self->cast_info.move_avoid_run = &runt_move_avoid_run;
	self->cast_info.move_avoid_reverse_walk = &runt_move_avoid_reverse_walk;
	self->cast_info.move_avoid_reverse_run = &runt_move_avoid_reverse_run;
	self->cast_info.move_avoid_crwalk = &runt_move_crouch_avoid_walk;

	self->cast_info.move_crouch_down = &runt_move_crouch_dn;
	self->cast_info.move_stand_up = &runt_move_stand_up;

	self->cast_info.move_lside_step = &runt_move_lside_step;
	self->cast_info.move_rside_step = &runt_move_rside_step;

//	self->cast_info.move_start_climb = &runt_move_st_clmb;
	self->cast_info.move_start_climb = &runt_move_clmb_loop;
	self->cast_info.move_end_climb = &runt_move_clmb_jmp;

	self->cast_info.move_evade = &runt_move_evade;
	
	if (self->moral > 2)
		self->cast_info.move_stand_evade = &runt_move_evade_stand2;
	else
	self->cast_info.move_stand_evade = &runt_move_evade_stand;

	gi.linkentity (self);

	self->cast_info.currentmove = self->cast_info.move_stand;

	if (!self->cast_info.scale)
		self->cast_info.scale = MODEL_SCALE;

	self->s.scale = self->cast_info.scale - 1.0;

	// talk by default
	self->cast_info.aiflags |= AI_TALK;

	walking_cast_start (self);

	if (!self->acc)
		self->acc = 2;

	if (self->spawnflags & 128)
		self->s.renderfx2 |= RF2_NOSHADOW;	

}
