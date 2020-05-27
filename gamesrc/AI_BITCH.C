#include "g_local.h"
#include "ai_bitch.h"

#include "voice_bitch.h"

void bitch_end_kneel_attack( edict_t *self );
void bitch_talk( edict_t *self );
void bitch_end_stand( edict_t *self );
void bitch_kneel_shoot( edict_t *self );
void bitch_talk_think( edict_t *self );

void bitch_firegun( edict_t *self, vec3_t ofs );
void bitch_right_fire( edict_t *self );
void bitch_left_fire( edict_t *self );
void bitch_firegun_right( edict_t *self );
void bitch_firegun_left( edict_t *self );

void bitch_show_guns( edict_t *self );
void bitch_climb_loop( edict_t *self );
void bitch_melee( edict_t *self );

void bitch_evade_amb( edict_t *self );

void bitch_melee_bail (edict_t *self);
void bitch_evade_checkadjust (edict_t *self);
void bitch_evade_adjust( edict_t *self );

#define	BITCH_MELEE		64	// spawnflag
#define BITCH_NOWEAPON	128

// =========================================================================

#include "ai_bitch_tables.h"

// =========================================================================

void bitch_backoff( edict_t *self, edict_t *other )
{
	Voice_Random( self, other, f_backoff, F_NUM_BACKOFF );
}

void bitch_catch_fire( edict_t *self, edict_t *other )
{
	self->enemy = NULL;		// stop attacking
	self->cast_info.currentmove = &bitch_move_run_on_fire;
}

void bitch_evade_amb( edict_t *self )
{
	// self->cast_info.currentmove = &bitch_move_evade_amb;
	self->cast_info.currentmove = &bitch_move_evd_amb;
}

void bitch_evade_checkadjust( edict_t *self )
{
	if (self->enemy && !directly_infront(self, self->enemy ))
		self->cast_info.currentmove = &bitch_move_evade_adjust;
}

void bitch_evade_adjust (edict_t *self )
{
	vec3_t vec;

	if (!self->enemy)
		return;

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	VectorNormalize( vec );
	self->ideal_yaw = vectoyaw( vec );
}


void bitch_end_kneel_attack( edict_t *self )
{
	AI_EndAttack(self);

	if (self->cast_info.currentmove == self->cast_info.move_stand)
		// self->cast_info.currentmove = &bitch_move_kneel_up;
		// we dont have a crouch kneel up
		self->cast_info.currentmove = &bitch4_move_crch_amb_std;
}


void bitch_talk_think( edict_t *self )
{
	AI_TalkThink( self, false );
}

void bitch_talk( edict_t *self )
{
	float rnd;

	// only make talking gesture if we've recently said something
	if (!(self->cast_info.aiflags & AI_REPEAT_TALK_JESTURE) && self->last_talk_time < (level.time - 1.0))
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
		return;
	}

	if (self->cast_info.currentmove != self->cast_info.move_stand)
		return;

	rnd = random() * 10;

	if (rnd < 1)
		self->cast_info.currentmove = &bitch_move_leanlook;
	else if (rnd < 2)
		self->cast_info.currentmove = &bitch_move_whatsup;
	else if (rnd < 3)
		self->cast_info.currentmove = &bitch_move_talkme;
	else if (rnd < 4)
		self->cast_info.currentmove = &bitch_move_nonono;
	else if (rnd < 5)
		self->cast_info.currentmove = &bitch_move_comeon;
	else if (rnd < 6)
		self->cast_info.currentmove = &bitch_move_getdown;
	else if (rnd < 7)
		self->cast_info.currentmove = &bitch_move_whomw;
	else if (rnd < 8)
		self->cast_info.currentmove = &bitch_move_lookself;
	else // if (rnd < 9)
		self->cast_info.currentmove = &bitch_move_flirt;
}


void bitch_avoid ( edict_t *self, edict_t *other, qboolean face )
{
	vec3_t	vec;

	if (self->health <= 0)
		return;

	if (!self->groundentity)
		return;

	self->cast_info.last_avoid = level.time;
	self->cast_info.avoid_ent = NULL;

	if (face)
	{	// turn to face them
		VectorSubtract( other->s.origin, self->s.origin, vec );
		self->cast_info.avoid_ent = other;
	}
	else
	{	// turn to face away from them
		VectorSubtract( self->s.origin, other->s.origin, vec );
	}
	VectorNormalize( vec );

	self->ideal_yaw = vectoyaw( vec );

	if (self->maxs[2] > DUCKING_MAX_Z)
	{
		if (self->cast_info.aiflags & AI_NOWALK_FACE)
		{
//			if (face)
			{
				int		side_result;

				side_result = AI_SideTrace( self, 48, 90, SIDE_RANDOM );

				if (side_result == AI_SideTrace( self, 48, 90 + (self->ideal_yaw - self->s.angles[YAW]), side_result ))
				{
					if (side_result < 0)
						self->cast_info.currentmove = &bitch4_move_lside_step;
					else
						self->cast_info.currentmove = &bitch4_move_rside_step;

					return;
				}

				// if no move set, just turn to face
				M_ChangeYaw( self );

				return;
			}
		}

		if ((VectorDistance( self->s.origin, other->s.origin ) > 72) || !face)
			self->cast_info.currentmove = &bitch_move_avoid_walk;
		else
			self->cast_info.currentmove = &bitch_move_avoid_reverse_walk;
	}
	else
	{
		self->cast_info.currentmove = &bitch_move_crch_avoid_walk;
	}

}

void bitch_end_stand( edict_t *self )
{

	if (self->cast_info.move_stand_evade && (self->last_stand_evade > (level.time - 3)))
		return;

	//if (self->cast_info.currentmove == self->cast_info.move_crstand)
	//	return;

//	if (	((!self->cast_group) && (random() < 0.8))
//		||	((self->cast_group) && (random() < 0.3)))
	{	// stand normally

		self->cast_info.currentmove = self->cast_info.move_stand;

//		return;
	}

	AI_CheckTalk(self);
}

void bitch_show_guns( edict_t *self )
{
	self->s.model_parts[PART_GUN].invisible_objects = 0;
}


void bitch_kneel_shoot( edict_t *self )
{
	// self->cast_info.currentmove = &bitch_move_knl_shoot;
	self->cast_info.currentmove = &bitch4_move_crch_shoot;	
}

void bitch_melee_bail (edict_t *self)
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
			self->cast_info.currentmove = &bitch4_move_run_melee;
			return;
		}
	}

}

void bitch_long_attack( edict_t *self )
{
	int	rnd;
	
	// keep running, and try to fire if possible

	if (self->maxs[2] < self->cast_info.standing_max_z)
		return;

	if (self->s.model_parts[PART_GUN].invisible_objects)
	{	// pull guns out

		// note to self dont have this animation yet

		self->cast_info.currentmove = &bitch_move_pull_gun;
		return;
	}
	
	//if (self->moral > MORAL_NORMAL)
	rnd = rand()%10;


	if (rnd > 8)
		self->cast_info.currentmove = &bitch_move_shoot_stand;
	else
		self->cast_info.currentmove = &bitch_move_run_shoot;
}

qboolean bitch_attack( edict_t *self )
{
	vec3_t	vec;
	float dist;

	int rnd;

	// this is where we would start some of the fancy side-ways or rolling attacks

	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		if (self->cast_info.aiflags & AI_MELEE)
		{	// try to stand at all costs
			self->maxs[2] = self->cast_info.standing_max_z;

			if (ValidBoxAtLoc( self->s.origin, self->mins, self->maxs, self, MASK_PLAYERSOLID ))
				goto standing;

			self->maxs[2] = DUCKING_MAX_Z;
			return false;	// can't attack
		}

		if (self->s.model_parts[PART_GUN].invisible_objects)
		{	// pull guns out
			self->s.model_parts[PART_GUN].invisible_objects = 0;
		}

		self->cast_info.currentmove = &bitch4_move_crch_shoot;

		return true;
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
			VectorMA( vec, 0.5, self->enemy->velocity, vec );
			dist = VectorNormalize( vec );

			if (dist < 64)
			{
				attack = true;
			}
		}

		if (attack)
		{
			int rnd;

			self->ideal_yaw = vectoyaw(vec);
			M_ChangeYaw( self );

			Voice_Random( self, self->enemy, f_grunting, 5);
			
			rnd = rand()%4;

			switch (rnd)
			{
			case 0 :
				self->cast_info.currentmove = &bitch4_move_melee1;
				break;
			case 1 :
				self->cast_info.currentmove = &bitch4_move_melee3;
				break;
			/*
			// moves are messed up
			case 2 :
				self->cast_info.currentmove = &bitch4_move_melee2;
				break;
			case 3 :
				self->cast_info.currentmove = &bitch4_move_melee3;
				break;
			*/
			}

			if (self->maxs[2] > self->enemy->maxs[2] || self->s.origin[2] > self->enemy->s.origin[2])
				self->cast_info.currentmove = &bitch4_move_low_melee1;

			return true;
		}
		else if (dist < 128)
		{
			self->ideal_yaw = vectoyaw(vec);
			M_ChangeYaw( self );

			self->cast_info.currentmove = &bitch4_move_run_melee;
			return true;
		}
		else if (dist < 400)
			self->cast_info.aiflags |= AI_RUSH_THE_PLAYER;

		return false;
	}


	// we can shoot and gun (not melee)

	if (self->s.model_parts[PART_GUN].invisible_objects)
	{	// pull guns out
		self->cast_info.currentmove = &bitch_move_pull_gun;
		return true;
	}

	if (	(dist < 384)				// they're close
		&&	(self->enemy->client)
		&&	(self->enemy->client->pers.weapon)
		&&	(stricmp(self->enemy->client->pers.weapon->classname, "weapon_flamethrower") == 0))
	{
		int		side_result;

		// see if we can go backwards
		if (side_result = AI_SideTrace( self, -64, 0, 1 ))
		{
			self->cast_info.currentmove = &bitch_move_reverse_run_shoot;
			return true;
		}

	}

	// if just popped out from a corner, just stand here
	if (self->dont_takecover_time > (level.time - 2))
	{
		goto stand_shoot;
	}


	rnd = rand()%10;
/*
	if (dist > AI_NOT_HOLSTERED_RANGE_1 && rnd < 9)
	{
		self->cast_info.currentmove = &bitch_move_shoot_stand;
		return true;
	}
	else
*/
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
					self->cast_info.currentmove = &bitch_move_lside_run;
				else
					self->cast_info.currentmove = &bitch_move_rside_run;

				self->ideal_yaw = vectoyaw(vec) + side_result * 90;

				M_ChangeYaw( self );

				self->cast_info.last_side_attack = side_result;
				self->cast_info.last_side_attack_time = level.time;

				return true;
			}
		}

	}

	if (	(dist > 512)
		&&	(rnd < 9)
		&&	(infront(self, self->enemy)))
	{
		self->cast_info.currentmove = &bitch_move_walk_shoot;

		return true;
	}
	else
	{

stand_shoot:

		self->ideal_yaw = vectoyaw(vec);

		M_ChangeYaw( self );

		self->cast_info.currentmove = &bitch_move_shoot_stand;
//		self->cast_info.currentmove = &bitch_move_walk_shoot;

		return true;
	}

	return false;
}


void bitch_climb_loop(edict_t *self)
{
	self->cast_info.currentmove = &bitch4_move_clmb_loop;
}


void bitch_melee( edict_t *self )
{
	vec3_t	start, offset;
	vec3_t	forward, right;

	float damage = 10;

	if (self->cast_info.currentmove == &bitch4_move_low_melee1)
	 	damage *= 2;		// double handed attack


	// yell at them?
	if (self->last_talk_time < (level.time - TALK_FIGHTING_DELAY))
			Voice_Random( self, self->enemy, f_grunting, 5);

	
	// VectorSet(offset, 0, 8,  self->viewheight - 4);
	VectorSet(offset, 0, 8, 16);

	AngleVectors (self->s.angles, forward, right, NULL);
	if (self->cast_info.currentmove == &bitch4_move_low_melee1)
		forward[2] = -0.5;
	G_ProjectSource (self->s.origin, offset, forward, right, start);

	if (self->cast_info.currentmove == &bitch4_move_low_melee1)
		start[2] -= 8;

	// HACK, higher Moral does more damage
	if (self->moral > 4)
		damage *= 1.0 + (self->moral - 4)*0.25;

	fire_blackjack( self, start, forward, damage, 10, MOD_BLACKJACK );
}


void bitch_firegun( edict_t *self, vec3_t ofs )
{
	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	target;
	vec3_t	aim;
	vec3_t	offset;
	int		flash_number;
	float	dist;


	if (self->cast_info.currentmove == &bitch4_move_crch_shoot)
	{
/*
		if (!directly_infront( self, self->enemy ))
		{
			self->cast_info.currentmove = &bitch4_move_crch_amb_std;
			self->s.frame++;		// skip the firing frame since it might have a muzzle flash
			return;
		}

		self->cast_info.aiflags |= AI_FACE_ATTACK;
*/
	}
	else
	{
		// check for reload
		if (self->duration++ > 12)
		{
			self->duration = 0;
			self->cast_info.currentmove = &bitch_move_reload;
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
		Voice_Random(self, self->enemy, f_fightsounds, F_NUM_FIGHTING);

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

	if ( dist > AI_NOT_HOLSTERED_RANGE_1)
	if (	(dist < self->cast_info.max_attack_distance)
		&&	(	((random() < 0.1) && (self->cast_info.last_side_attack_time < (level.time - 2)))
			 ||	(	(!(self->cast_info.aiflags & AI_SIDE_ATTACK) || (self->cast_info.last_side_attack_time < (level.time - 2)))
				 &&	(directly_infront( self->enemy, self))
				 &&	(self->enemy->client)
				 &&	(self->enemy->client->pers.weapon)
				 &&	(self->enemy->client->pers.weapon->ammo))))		// if we are directly infront of them, try to strafe
	{
		if (self->cast_info.aiflags & AI_SIDE_ATTACK)
			self->cast_info.currentmove = &bitch_move_run_shoot;
		else
			self->cast_info.attack( self );
	}

	/*
	if (self->acc > ACC_NORMAL)
		cast_fire_bullet (self, start, aim, self->cal, 0, 0.0, 0.0, flash_number);
	else
		cast_fire_bullet (self, start, aim, self->cal, 0, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
	*/
	
	if (self->acc)
		cast_fire_bullet (self, start, aim, self->cal, 0, DEFAULT_BULLET_HSPREAD>>self->acc, DEFAULT_BULLET_VSPREAD>>self->acc, flash_number);
	else
		cast_fire_bullet (self, start, aim, self->cal, 0, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);

	gi.sound(self, CHAN_WEAPON, gi.soundindex("weapons/machinegun/machgf1b.wav"), 1, ATTN_NORM, 0);

}

void bitch_right_fire( edict_t *self )
{
	static vec3_t	ofs = {4, 0, 0};
	bitch_firegun( self, ofs );
}

void bitch_left_fire( edict_t *self )
{
	static vec3_t	ofs = {-4, 0, 0};
	bitch_firegun( self, ofs );
}

void bitch_firegun_right( edict_t *self )
{
	vec3_t	vec;
	float	oldyaw;
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
	if (!AI_SideTrace( self, 96, 0, 1 ))
	{
		AI_EndAttack(self);
		return;
	}


	oldyaw = self->s.angles[YAW];

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	VectorNormalize( vec );

	self->s.angles[YAW] = vectoyaw( vec );

	self->cast_info.aiflags |= AI_SIDE_ATTACK;
	bitch_firegun(self, ofs);
	self->cast_info.aiflags &= ~AI_SIDE_ATTACK;

	// keep running to the side
	self->ideal_yaw = self->s.angles[YAW] + 90;

	self->s.angles[YAW] = oldyaw;
}

void bitch_firegun_left( edict_t *self )
{
	vec3_t	vec;
	float	oldyaw;
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
	if (!AI_SideTrace( self, 96, 0, 1 ))
	{
		AI_EndAttack(self);
		return;
	}


	oldyaw = self->s.angles[YAW];

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	VectorNormalize( vec );

	self->s.angles[YAW] = vectoyaw( vec );

	self->cast_info.aiflags |= AI_SIDE_ATTACK;
	bitch_firegun(self, ofs);
	self->cast_info.aiflags &= ~AI_SIDE_ATTACK;

	// keep running to the side
	self->ideal_yaw = self->s.angles[YAW] - 90;

	self->s.angles[YAW] = oldyaw;
}


// JOSEPH 17-NOV-98

void think_playthud_bitch( edict_t *self )
{
	char Temp[128];

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
// END JOSEPH


// JOSEPH 11-JUN-99-B
void bitch_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	trace_t	tr;
	vec3_t	end;
 	edict_t *playthud1, *playthud2;

//	self->s.modelindex2 = 0;

	// regular death
	self->takedamage = DAMAGE_YES;

	if (DeathByGib(self, inflictor, attacker, damage))
	{	// gib
		self->deadflag = DEAD_DEAD;
		GibEntity( self, inflictor, damage );
		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	self->deadflag = DEAD_DEAD;

	if (!(self->cast_info.aiflags & AI_MELEE))
		SpawnTheWeapon (self, "weapon_pistol_e");

	// EP_SpecialEventDeath (self);

	VectorCopy (self->s.origin, end);
	end[2] -= 64;
	tr = gi.trace (self->s.origin, self->mins, self->maxs, end, self, MASK_SHOT);

	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		if ((rand()%100) > 50)
		{
			self->cast_info.currentmove = &bitch4_move_crch_dth1;
		
			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*6.0);
			playthud1->think = think_playthud_bitch;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*9.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);		
		}
		else if ((rand()%100) > 50)
		{
			self->cast_info.currentmove = &bitch4_move_crch_dth2;
		
			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*7.0);
			playthud1->think = think_playthud_bitch;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*11.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);				
		}
		else
		{
			self->cast_info.currentmove = &bitch4_move_crch_dth4;
		
			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*6.0);
			playthud1->think = think_playthud_bitch;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*20.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);				
		}

		// !!! TODO: use all 4 crouching deaths (which ones are played when?)
	}
	else if (mdx_part == PART_HEAD)
	{
		self->cast_info.currentmove = &bitch_move_death5;

		playthud1 = G_Spawn();
		VectorCopy (self->s.origin, playthud1->s.origin);
		playthud1->thudsurf = tr.surface->flags;
		playthud1->thudsnd = 1; 
		playthud1->nextthink = level.time + (0.1*7.0);
		playthud1->think = think_playthud_bitch;
		gi.linkentity (playthud1);
			
		playthud2 = G_Spawn();
		VectorCopy (self->s.origin, playthud2->s.origin);
		playthud2->thudsurf = tr.surface->flags;
		playthud2->thudsnd = 2; 
		playthud2->nextthink = level.time + (0.1*18.0);
		playthud2->think = think_playthud_bitch;
		gi.linkentity (playthud2);		

	}
	//else if (self->maxs[2] < self->cast_info.standing_max_z)
	//{
	//	self->cast_info.currentmove = &bitch_move_crch_dth;
	//}
	else
	{
		int n;

		n = rand() % 5;
		if (n == 0)
		{
			self->cast_info.currentmove = &bitch_move_death1;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*7.0);
			playthud1->think = think_playthud_bitch;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*11.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);			

		}
		else if (n == 1)
		{
			self->cast_info.currentmove = &bitch_move_death2;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*6.0);
			playthud1->think = think_playthud_bitch;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*8.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);				

		}
		else if (n == 2)
		{
			self->cast_info.currentmove = &bitch_move_death3;

			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*6.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);				

			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*9.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);		
		}
		else if (n == 3)
		{
			self->cast_info.currentmove = &bitch_move_death4;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*7.0);
			playthud1->think = think_playthud_bitch;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*15.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);				

		}
		else
		{
			self->cast_info.currentmove = &bitch_move_death5;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*7.0);
			playthud1->think = think_playthud_bitch;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();	
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*18.0);
			playthud2->think = think_playthud_bitch;
			gi.linkentity (playthud2);				

		}
	}

//	gi.sound (self, CHAN_VOICE, gi.soundindex(va("*death%i.wav", (rand()%4)+1)), 1, ATTN_NORM, 0);
	if (!self->onfiretime)
		Voice_Random (self, attacker, &female_specific[4], 2);

	// RAFAEL 01-25-99
	self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
}
// END JOSEPH

void bitch_pain (edict_t *self, edict_t *other, float kick, int damage, int mdx_part, int mdx_subobject)
{
	int		orientation;


	AI_CheckMakeEnemy( self, other );

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3 + random();

	if (skill->value >= 3)
		return;		// no pain anims in nightmare

	/*
	if (rand() % 100 > 50)
		gi.sound (self, CHAN_VOICE, gi.soundindex("actors/bitch/pain1.wav"), 1, ATTN_NORM, 0);
	else
		gi.sound (self, CHAN_VOICE, gi.soundindex("actors/bitch/pain2.wav"), 1, ATTN_NORM, 0);
	*/

	if (self->health < 25)
		Voice_Specific (self, other, female_specific, 4);
	else if (self->health < 50)
		Voice_Specific (self, other, female_specific, 3);
	else if (self->health < 75)
		Voice_Specific (self, other, female_specific, 2);
	else
		Voice_Specific (self, other, female_specific, 1);

	// Ridah, randomly don't play an animation, since it' leaves them WAY open to be killed
	if (skill->value > 0 && rand()%2)
		return;


	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		self->cast_info.currentmove = &bitch_move_p_pain_crch;
		return;
	}

	if (other->client || (other->svflags & SVF_MONSTER))
	{
		orientation = AI_GetOrientation( self, other );
	}
	else
	{
		orientation = ORIENTATION_CENTER;
	}


	if (	(mdx_part == PART_BODY)
		||	(other->client && other->client->pers.weapon && !(other->client->pers.weapon->ammo) && (orientation = rand()%2+1)))
	{
		int rnd;
		
		rnd = rand () % 2;

		switch (orientation)
		{
		case ORIENTATION_CENTER :
			{
				self->cast_info.currentmove = &bitch_move_p_pain_chst;		
				break;
			}
		case ORIENTATION_LEFT :
			{
				if (rnd)
					self->cast_info.currentmove = &bitch_move_p_pain_lshd;		
				else
					self->cast_info.currentmove = &bitch_move_p_pain_lshd2; 
				break;
			}
		case ORIENTATION_RIGHT :
			{
				if (rnd)
					self->cast_info.currentmove = &bitch_move_p_pain_rshd;
				else
					self->cast_info.currentmove = &bitch_move_p_pain_rshd2;		
				break;
			}
		}
	}
	else if (mdx_part == PART_LEGS)
	{
		int rnd;

		switch (orientation)
		{
		case ORIENTATION_CENTER :
			{
				rnd = rand() % 2;

				if (infront(self, other))
				{
					if (rnd == 1)
						self->cast_info.currentmove = &bitch_move_p_pain_crch; 
					else
						self->cast_info.currentmove = &bitch_move_p_pain_crch2; 
				}
				else
				{
					if (rnd == 2)
						self->cast_info.currentmove = &bitch_move_p_pain_butt; 
					else
						self->cast_info.currentmove = &bitch_move_p_pain_butt2; 			
				}
				break;
			}
		case ORIENTATION_LEFT :
			{
				rnd = rand() * 2;
				if (rnd)
					self->cast_info.currentmove = &bitch_move_p_pain_lleg; 			
				else
					self->cast_info.currentmove = &bitch_move_p_pain_lleg2; 
				break;
			}
		case ORIENTATION_RIGHT :
			{
				rnd = rand() * 2;
				if (rnd)
					self->cast_info.currentmove = &bitch_move_p_pain_rleg; 	
				else
					self->cast_info.currentmove = &bitch_move_p_pain_rleg2; 			
				break;
			}
		}
	}
	else if (mdx_part == PART_HEAD)
	{
		self->cast_info.currentmove = &bitch_move_p_pain_head2; 
	}
//	else
//		gi.dprintf ("what the fuck\n");
	

}

// =========================================================================

/*QUAKED cast_bitch (1 .5 0) (-16 -16 -24) (16 16 48) x TRIGGERED_START x x x IMMEDIATE_FOLLOW_PATH MELEE NOSHADOW
cast_group 0	neutral
cast_group 1	friendly	
cast_group 2 or greater	enemy
bitch with the pistol

head 1 = bald 2 = pony tail 0 or anything else is default

model="models\actors\bitch\"

*/
void SP_cast_bitch(edict_t *self)
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
	switch (self->head)
	{
		case 1:
			self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bitch/bald_head.mdx");
			break;
		case 2:
			self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bitch/pony_head.mdx");
			break;
		default:
			self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bitch/head.mdx");
			break;
	}
	if (head_skin)
	{
		skin = gi.skinindex( self->s.model_parts[PART_HEAD].modelindex, head_skin );
	}
	else
		skin = self->s.skinnum;
	
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].baseskin = self->s.model_parts[PART_HEAD].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/bitch/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/bitch/legs.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_LEGS].modelindex, legs_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].baseskin = self->s.model_parts[PART_LEGS].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/bitch/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/bitch/body.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_BODY].modelindex, body_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].baseskin = self->s.model_parts[PART_BODY].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/bitch/body.mdx", &self->s.model_parts[PART_BODY] );

	if (self->spawnflags & BITCH_MELEE)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/bitch/pipe.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0; // self->s.skinnum;
		gi.GetObjectBounds( "models/actors/bitch/pipe.mdx", &self->s.model_parts[PART_GUN] );

		self->cast_info.aiflags |= AI_MELEE;
	}
	else 
	{
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/bitch/gun.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/bitch/gun.mdx", &self->s.model_parts[PART_GUN] );

		self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
	}
	
	// remove NULL's
	if (self->art_skins)
		self->art_skins[3] = self->art_skins[7] = ' ';

	// ------------------------------------------------------------------------

	if (!self->health)
		self->health = 100;
	self->gib_health = -200;
	self->mass = 200;

	self->gender = GENDER_FEMALE;

	self->pain = bitch_pain;
	self->die = bitch_die;

	self->cast_info.checkattack = AI_CheckAttack;

	self->cast_info.attack = bitch_attack;
	self->cast_info.long_attack = bitch_long_attack;
	self->cast_info.talk = bitch_talk;
	self->cast_info.avoid = bitch_avoid;
	self->cast_info.backoff = bitch_backoff;

	self->cast_info.catch_fire = bitch_catch_fire;
	
	self->cast_info.max_attack_distance = 2000;

	self->cast_info.move_stand = &bitch_move_boredA; // ok
	
	self->cast_info.move_crstand = &bitch4_move_crch_amb_std;

	self->cast_info.move_run = &bitch_move_run_guns_dn; // ok
	self->cast_info.move_runwalk = &bitch_move_walk_guns_dn; // ok

	self->cast_info.move_crwalk = &bitch4_move_crch_walk;

	self->cast_info.move_jump = &bitch4_move_jump;

	// Betty walks away from you since she doesn't want to start any trouble
	if (self->name && !stricmp( self->name, "Betty"))
		self->cast_info.move_avoid_walk = &bitch_move_evd_walk;
	else	
		self->cast_info.move_avoid_walk = &bitch_move_avoid_walk;
	
	self->cast_info.move_avoid_run = &bitch_move_avoid_run;
	self->cast_info.move_avoid_reverse_walk = &bitch_move_avoid_reverse_walk;
	self->cast_info.move_avoid_reverse_run = &bitch_move_avoid_reverse_run;
	//self->cast_info.move_avoid_crwalk = &bitch_move_crouch_avoid_walk;

	self->cast_info.move_crouch_down = &bitch4_move_crch_knl_dn;
	self->cast_info.move_stand_up = &bitch4_move_stand_up;

	self->cast_info.move_lside_step = &bitch4_move_lside_step;
	self->cast_info.move_rside_step = &bitch4_move_rside_step;

	self->cast_info.move_start_climb = &bitch4_move_clmb_loop;

	self->cast_info.move_end_climb = &bitch4_move_clmb_jmp;
	//self->cast_info.move_end_climb = NULL;

	self->cast_info.move_evade = &bitch_move_evd_walk;
	self->cast_info.move_stand_evade = &bitch_move_evd_stand;

	gi.linkentity (self);

	self->cast_info.currentmove = self->cast_info.move_stand;


	if (!self->cast_info.scale)
		self->cast_info.scale = MODEL_SCALE;

	self->s.scale = self->cast_info.scale - 1.0;


	walking_cast_start (self);

	// HACK THE BITCHES TO SEASONED
	/*
	if (!self->acc)
		self->acc = ACC_NORMAL;
	*/
	if (!self->acc)
		self->acc = 2;

	// talk by default
	self->cast_info.aiflags |= AI_TALK;

	if (!self->cal) // weapon calibur
		self->cal = 3;

	if (self->spawnflags & 128)
		self->s.renderfx2 |= RF2_NOSHADOW;	

}
