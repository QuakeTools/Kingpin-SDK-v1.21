#include "g_local.h"
#include "ai_punk.h"

#include "voice_punk.h"

void punk_end_stand( edict_t *self );
void punk_firegun( edict_t *self );
void punk_firegun_left( edict_t *self );
void punk_firegun_right( edict_t *self );
void punk_talk_think( edict_t *self );
// Joseph 20-NOV-98
void think_killedict( edict_t *self );
void think_playthud( edict_t *self );
// END JOSEPH

void punk_firegun_cr (edict_t *self);
void punk_shotgun_reload( edict_t *self );

void punk_reload_snd (edict_t *self);

void punk_firehmg( edict_t *self );
void punk_firehmg_delay (edict_t *self);
void punk_firebazooka_delay (edict_t *self);
void punk_hmg_avoid (edict_t *self);

// =========================================================================

#include "ai_punk_tables.h"

// =========================================================================

#define PUNK_FLAMEGUN		4
#define	PUNK_BAZOOKA		8
#define PUNK_HMG			16

#define	PUNK_TOMMYGUN		64	// spawnflag

#define PUNK_GRENADE		128
#define PUNK_SHOTGUN		8192


int	tommy_soundindex;
int	shotgun_soundindex;
int	shotgun_reload_soundindex;
int	heavymachinegun_soundindex;
int	rocketgun_soundindex;

void punk_reload_snd (edict_t *self)
{
	if (self->spawnflags & PUNK_TOMMYGUN)
		gi.sound(self, CHAN_VOICE, gi.soundindex("weapons/machinegun/machgcock.wav"), 1, ATTN_NORM, 0);
	else if (self->spawnflags &	PUNK_HMG)
		gi.sound(self, CHAN_VOICE, gi.soundindex("weapons/machinegun/machgcock.wav"), 1, ATTN_NORM, 0);
	else if (self->spawnflags & PUNK_BAZOOKA)
		gi.sound(self, CHAN_VOICE, gi.soundindex("weapons/rocket_launcher/reload.wav"), 1, ATTN_NORM, 0);
	else if (self->spawnflags & PUNK_GRENADE)
		gi.sound(self, CHAN_VOICE, gi.soundindex("weapons/grenade_launcher/reload.wav"), 1, ATTN_NORM, 0);
}

void punk_catch_fire( edict_t *self, edict_t *other )
{
	self->enemy = NULL;		// stop attacking
	self->cast_info.currentmove = &punk_move_run_on_fire;
}

void punk_talk_think( edict_t *self )
{
	AI_TalkThink( self, true );
}

void punk_talk( edict_t *self )
{
	float rnd;

	rnd = random() * 7;

	// only make talking jester if we've recently said something
	if (!(self->cast_info.aiflags & AI_REPEAT_TALK_JESTURE) && self->last_talk_time < (level.time - 1.0))
	{
		self->cast_info.currentmove = self->cast_info.move_stand;

		return;
	}

	if (self->cast_info.currentmove != self->cast_info.move_stand)
		return;

	if (self->spawnflags & PUNK_SHOTGUN)
	{
		if (rnd < 1)
			self->cast_info.currentmove = &punk_move_sg_stand;
		else if (rnd < 2)
			self->cast_info.currentmove = &punk_move_sg_talk1;
		else if (rnd < 3)
			self->cast_info.currentmove = &punk_move_sg_talk2;
		else if (rnd < 4)
			self->cast_info.currentmove = &punk_move_sg_talk3;
		else if (rnd < 5)
			self->cast_info.currentmove = &punk_move_sg_talk4;
		else if (rnd < 6)
			self->cast_info.currentmove = &punk_move_sg_talk5;
		else
			self->cast_info.currentmove = &punk_move_sg_talk6;
	}
	else
	{
	if (rnd < 1)
		self->cast_info.currentmove = &punk_move_talk1;
	else if (rnd < 2)
		self->cast_info.currentmove = &punk_move_talk2;
	else if (rnd < 3)
		self->cast_info.currentmove = &punk_move_talk3;
	else if (rnd < 4)
		self->cast_info.currentmove = &punk_move_talk4;
	else if (rnd < 5)
		self->cast_info.currentmove = &punk_move_talk5;
	else if (rnd < 6)
		self->cast_info.currentmove = &punk_move_talk6;
	else
		self->cast_info.currentmove = &punk_move_head_wipe;
	}
}

void punk_avoid ( edict_t *self, edict_t *other, qboolean face )
{
	vec3_t	vec;

	if (self->health <= 0)
		return;

	if (!self->groundentity)
		return;

	if (!other)
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
		return;
	}

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
						self->cast_info.currentmove = &punk_move_lside_step;
					else
						self->cast_info.currentmove = &punk_move_rside_step;

					return;
				}

				// if no move set, just turn to face
				M_ChangeYaw( self );

				return;
			}
		}

		if ((VectorDistance( self->s.origin, other->s.origin ) > 72) || !face)
			self->cast_info.currentmove = &punk_move_avoid_walk;
		else
			self->cast_info.currentmove = &punk_move_avoid_reverse_walk;
	}
	else
	{
		self->cast_info.currentmove = &punk_move_avoid_crouch_walk;
	}

}

void punk_end_stand( edict_t *self )
{
	if (self->cast_info.move_stand_evade && (self->last_stand_evade > (level.time - 3)))
		return;

	if (self->cast_info.currentmove == self->cast_info.move_crstand)
		return;

//	if (	((!self->cast_group) && (random() < 0.8))
//		||	((self->cast_group) && (random() < 0.3)))
	{	// stand normally

		if (	(self->cast_info.currentmove != &punk_move_head_wipe)
			&&	(random() < 0.3) && self->spawnflags & PUNK_TOMMYGUN)
		{	// randomly wipe our face
			self->cast_info.currentmove = &punk_move_head_wipe;
		}
		else
		{
			self->cast_info.currentmove = self->cast_info.move_stand;
		}

//		return;
	}

	AI_CheckTalk(self);
}

void punk_long_attack( edict_t *self )
{
	// keep running, and try to fire if possible

	if (self->maxs[2] < self->cast_info.standing_max_z)
		return;

	// self->cast_info.currentmove = &punk_move_run_shoot;
	
	if (self->spawnflags & PUNK_TOMMYGUN)
		self->cast_info.currentmove = &punk_move_run_tg_sht;
	else if (self->spawnflags & PUNK_SHOTGUN)
		self->cast_info.currentmove = &punk_move_run_shg_sht;
	else if (self->spawnflags & PUNK_HMG)
		self->cast_info.currentmove = &punk_move_run_hmg_sht;
	else if (self->spawnflags & PUNK_BAZOOKA)
		self->cast_info.currentmove = &punk_move_run_bazooka_sht;
	else if (self->spawnflags & PUNK_FLAMEGUN)
		self->cast_info.currentmove = &punk_move_run_flamegun_sht;
	else if (self->spawnflags & PUNK_GRENADE)
		self->cast_info.currentmove = &punk_move_run_grenade_sht;
	else
	{
		gi.dprintf ("actor is missing weapon spawnflag\n");
		self->cast_info.currentmove = &punk_move_run_shg_sht;
	}
}

qboolean punk_attack( edict_t *self )
{

	if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		self->cast_info.currentmove = &punk_move_crouch_shoot;
		return true;
	}
	else
	{
		vec3_t	vec;
		float dist;


		VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
		dist = VectorNormalize( vec );

		// Special case: enemy has flamethrower, run backwards, keep firing
		if (	(dist < 384)				// they're close
			&&	(self->spawnflags & PUNK_TOMMYGUN)
			&&	(self->enemy->client)
			&&	(self->enemy->client->pers.weapon)
			&&	(stricmp(self->enemy->client->pers.weapon->classname, "weapon_flamethrower") == 0))
		{
			int		side_result;

			// see if we can go backwards
			if (side_result = AI_SideTrace( self, -64, 0, 1 ))
			{
				self->cast_info.currentmove = &punk_move_run_reverse_tg_sht;
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
			// attempt a side-ways attack

			int		side_result, side_result2;

			side_result = AI_SideTrace( self, 64, 90, -self->cast_info.last_side_attack );

			if (side_result)
			{
				side_result2 = AI_SideTrace( self, 128, 90, side_result );

				if (side_result2 == side_result)
				{
					/*
					if (side_result < 0)
						self->cast_info.currentmove = &punk_move_lside_run;
					else
						self->cast_info.currentmove = &punk_move_rside_run;
					*/
					if (side_result < 0)
					{
						if (self->spawnflags & PUNK_TOMMYGUN)
							self->cast_info.currentmove = &punk_move_lsd_tg_run;
						else if (self->spawnflags & PUNK_SHOTGUN)
							self->cast_info.currentmove = &punk_move_lsd_shg_run;
						else if (self->spawnflags & PUNK_HMG)
							// self->cast_info.currentmove = &punk_move_lsd_hmg_run;
							self->cast_info.currentmove = &punk_move_walk_hmg_sht;
						else if (self->spawnflags & PUNK_BAZOOKA)
							self->cast_info.currentmove = &punk_move_lsd_bazooka_run;
						else if (self->spawnflags & PUNK_FLAMEGUN)
							self->cast_info.currentmove = &punk_move_lsd_flamegun_run;
						else if (self->spawnflags & PUNK_GRENADE)
							self->cast_info.currentmove = &punk_move_lsd_grenade_run;
						else
						{
							gi.dprintf ("missing weapon spawnflag\n");
							self->cast_info.currentmove = &punk_move_lsd_shg_run;
						}
					}
					else
					{
						if (self->spawnflags & PUNK_TOMMYGUN)
							self->cast_info.currentmove = &punk_move_rsd_tg_run;
						else if (self->spawnflags & PUNK_SHOTGUN)
							self->cast_info.currentmove = &punk_move_rsd_shg_run;
						else if (self->spawnflags & PUNK_HMG)
							// self->cast_info.currentmove = &punk_move_rsd_hmg_run;
							self->cast_info.currentmove = &punk_move_walk_hmg_sht;
						else if (self->spawnflags & PUNK_BAZOOKA)
							self->cast_info.currentmove = &punk_move_rsd_bazooka_run;
						else if (self->spawnflags & PUNK_FLAMEGUN)
							self->cast_info.currentmove = &punk_move_rsd_flamegun_run;
						else if (self->spawnflags & PUNK_GRENADE)
							self->cast_info.currentmove = &punk_move_rsd_grenade_run;
						else
						{
							gi.dprintf ("missing weapon spawnflag\n");
						}
					}


					self->ideal_yaw = vectoyaw(vec) + side_result * 90;

					M_ChangeYaw( self );

					self->cast_info.last_side_attack = side_result;
					self->cast_info.last_side_attack_time = level.time;

					return true;
				}
			}

		}

		self->ideal_yaw = vectoyaw(vec);

		M_ChangeYaw( self );

		// just shoot like normal

		// walk shooting?
		if ((dist > 256) && directly_infront( self, self->enemy ) && AI_SideTrace(self, 32, 0, 1 ) )
		{
			if (self->spawnflags & PUNK_TOMMYGUN)
				self->cast_info.currentmove = &punk_move_walk_tg_sht;
			else if (self->spawnflags & PUNK_HMG)
				self->cast_info.currentmove = &punk_move_walk_hmg_sht;
			else if (self->spawnflags & PUNK_BAZOOKA)
				self->cast_info.currentmove = &punk_move_walk_bazooka_sht;
			else if (self->spawnflags & PUNK_FLAMEGUN)
				self->cast_info.currentmove = &punk_move_walk_flamegun_sht;
			else if (self->spawnflags & PUNK_GRENADE)
				self->cast_info.currentmove = &punk_move_walk_grenade_sht;
			else if (self->spawnflags & PUNK_SHOTGUN)
			{
				if (dist > 800)	// shotgun dude should get closer
					self->cast_info.currentmove = &punk_move_walk_shg_sht;
				else
					self->cast_info.currentmove = &punk_move_run_shg_sht;
			}

			return true;
		}
/* TODO: Reverse walking anim table
		else if ((dist < 128) && AI_SideTrace(self, -32, 0, 1 ) )
		{
			self->cast_info.currentmove = &thug_move_reverse_walk_shoot;
			return true;
		}
*/
		// normal attack

stand_shoot:

		self->ideal_yaw = vectoyaw(vec);

		M_ChangeYaw( self );

		if (self->spawnflags & PUNK_TOMMYGUN)
			self->cast_info.currentmove = &punk_move_tg_shoot;
		else if (self->spawnflags & PUNK_SHOTGUN)
			self->cast_info.currentmove = &punk_move_shg_shoot;
		else if (self->spawnflags & PUNK_HMG)
			self->cast_info.currentmove = &punk_move_hmg_shoot;
		else if (self->spawnflags & PUNK_BAZOOKA)
			self->cast_info.currentmove = &punk_move_bazooka_shoot;
		else if (self->spawnflags & PUNK_FLAMEGUN)
			self->cast_info.currentmove = &punk_move_flamegun_shoot;
		else if (self->spawnflags & PUNK_GRENADE)
			self->cast_info.currentmove = &punk_move_grenade_shoot;
		else
		{
			gi.dprintf ("missing weapon spawnflag\n");
			self->cast_info.currentmove = &punk_move_shg_shoot;
		}

		return true;
	}

	return false;
}

void punk_firegun_cr ( edict_t *self )
{
	if (self->spawnflags & PUNK_SHOTGUN)
		return;
	else if (self->spawnflags & PUNK_HMG)
		return;
	else if (self->spawnflags & PUNK_BAZOOKA)
		return;
	else if (self->spawnflags &	PUNK_FLAMEGUN)
		return;
	else if (self->spawnflags & PUNK_GRENADE)
		return;
	else if (self->spawnflags & PUNK_TOMMYGUN)
		punk_firegun (self);
	else
		gi.dprintf ("error : not tagged right!\n");
}

void punk_hmg_avoid (edict_t *self)
{
	if (self->s.frame == FRAME_tg_shoot_05)
		self->cast_info.avoid(self, self->enemy, true);
	else
		self->cast_info.avoid(self, self->enemy, false);
}

void punk_firehmg_delay (edict_t *self)
{

	if (self->s.frame == FRAME_tg_shoot_05)
		self->cast_info.currentmove = &punk_move_hmg_shoot2;
	else if (self->s.frame == FRAME_walk_tg_sht_10)
		self->cast_info.currentmove = &punk_move_walk_hmg_sht2;
	else
		self->cast_info.currentmove = &punk_move_run_hmg_sht2;
}

void punk_firebazooka_delay (edict_t *self)
{
	if (self->s.frame == FRAME_tg_shoot_05)
		self->cast_info.currentmove = &punk_move_bazooka_shoot2;
	else if (self->s.frame == FRAME_walk_tg_sht_10)
		self->cast_info.currentmove = &punk_move_walk_bazooka_shoot2;
	else
		self->cast_info.currentmove = &punk_move_run_bazooka_shoot2;
}

void punk_firehmg( edict_t *self )
{

	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	target;
	vec3_t	aim;
	vec3_t	offset;
	int		flash_number;
	float	dist;

	if (!AI_BeginAttack( self ))
	{
		// self->s.frame++;		// skip the firing frame since it might have a muzzle flash
		self->cast_info.currentmove = self->cast_info.move_stand;
		
		// may need to hack this
		// self->s.frame == standframe;
		return;
	}
	
	if (self->duration++ > 30)
	{
		self->duration = 0;
		self->cast_info.currentmove = &punk_move_tg_reload;
		self->s.frame++;		// skip the firing frame since it might have a muzzle flash
		return;
	}
		
	// JOSEPH 26-MAY-99
	// yell at them?
	if (self->last_talk_time < (level.time - TALK_FIGHTING_DELAY))
	{
		if (self->name_index == NAME_NICKIBLANCO)
		{
			Voice_Random (self, self->enemy, &nickiblanco[6], 10);
		}
		else if (self->cast_group != 1)
			Voice_Random(self, self->enemy, fightsounds, NUM_FIGHTING);
		else
			Voice_Random(self, self->enemy, friendlycombat, NUM_FRIENDLYCOMBAT );
	}
	// END JOSEPH

	{
		VectorSet(offset, 0, 8,  self->viewheight-8);

		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, offset, forward, right, start);

		// project enemy back a bit and target there
		VectorCopy (self->enemy->s.origin, target);
		VectorMA (target, (-0.5 * (crandom())) * (1.0 - (skill->value/4.0)), self->enemy->velocity, target);

		if (self->enemy->maxs[2] < self->cast_info.standing_max_z)
			target[2] += - ( 8 * random());
		else
			target[2] += self->enemy->viewheight - 4 - (16 * random());

		flash_number = MZ2_GUNNER_MACHINEGUN_1;

		VectorSubtract (target, start, aim);
		dist = VectorNormalize (aim);
	}

	self->ideal_yaw = vectoyaw( aim );

	{
		fire_bullet (self, start, aim, 15, 50, DEFAULT_BULLET_HSPREAD>>self->acc, DEFAULT_BULLET_VSPREAD>>self->acc, MOD_BARMACHINEGUN);
		{
			//if (self->lastduration == 1)
			if (self->s.frame == FRAME_tg_shoot_01
				|| self->s.frame == FRAME_walk_tg_sht_01
				|| self->s.frame == FRAME_run_tg_sht_01)
			{
				gi.sound(self, CHAN_WEAPON, gi.soundindex("weapons/hmg/hmg.wav"), 1, ATTN_NORM, 0);
			}
			
			//if (self->lastduration == 0)
			//	self->durationflag = 1;
		}
	}
	
};


void punk_firegun( edict_t *self )
{
	vec3_t	start;
	vec3_t	forward, right;
	vec3_t	target;
	vec3_t	aim;
	vec3_t	offset;
	int		flash_number;
	float	dist;


	if (self->name_index == NAME_DAVID)
	{
		self->s.model_parts[PART_GUN].invisible_objects = 0;
		self->s.model_parts[PART_GUN2].invisible_objects = 0;
	}

	if (self->cast_info.aiflags & AI_RELOAD)
	{	// we need to reload first, just do it now (since it's a similar motion)
		punk_shotgun_reload( self );
		self->s.frame++;		// skip the firing frame since it might have a muzzle flash
		return;
	}

	if (self->spawnflags & PUNK_TOMMYGUN)
	{
		if (	(self->maxs[2] == self->cast_info.standing_max_z)
			&&	!(self->cast_info.aiflags & AI_SIDE_ATTACK)
			&&	(self->duration++ > 40))
		{

				self->duration = 0;
				self->cast_info.currentmove = &punk_move_tg_reload;
				self->s.frame++;		// skip the firing frame since it might have a muzzle flash
				return;
		}
	}
	else if (self->spawnflags & PUNK_BAZOOKA)
	{
		if (	(self->maxs[2] == self->cast_info.standing_max_z)
			&&	!(self->cast_info.aiflags & AI_SIDE_ATTACK)
			&&	(self->duration++ > 3))
		{

				self->duration = 0;
				self->cast_info.currentmove = &punk_move_tg_reload;
				self->s.frame++;		// skip the firing frame since it might have a muzzle flash
				return;
		}
	}
	else if (self->spawnflags & PUNK_GRENADE)
	{
		if (	(self->maxs[2] == self->cast_info.standing_max_z)
			&&	!(self->cast_info.aiflags & AI_SIDE_ATTACK)
			&&	(self->duration++ > 2))
		{

				self->duration = 0;
				self->cast_info.currentmove = &punk_move_tg_reload;
				self->s.frame++;		// skip the firing frame since it might have a muzzle flash
				return;
		}
	}


	if (!AI_BeginAttack( self ))
	{
		self->s.frame++;		// skip the firing frame since it might have a muzzle flash
		return;
	}

	// JOSEPH 26-MAY-99
	// yell at them?
	if (self->last_talk_time < (level.time - TALK_FIGHTING_DELAY))
	{
		if (self->name_index == NAME_NICKIBLANCO)
		{
			Voice_Random (self, self->enemy, &nickiblanco[6], 10);
		}
		if (self->name_index == NAME_NICKIBLANCO)
		{
			Voice_Random (self, self->enemy, &nickiblanco[6], 10);
		}
		else if (self->name_index == NAME_TYRONE)
		{
			Voice_Random (self, self->enemy, &ty_tyrone[6], 10); 
		}
		else if (self->name_index == NAME_MOKER)
		{
			Voice_Random (self, self->enemy, &steeltown_moker[6], 10);
		}
		else if (self->cast_group != 1)
			Voice_Random(self, self->enemy, fightsounds, NUM_FIGHTING);
		else
			Voice_Random(self, self->enemy, friendlycombat, NUM_FRIENDLYCOMBAT );
	}
	// END JOSEPH

	// fire the gun
	if (self->spawnflags & PUNK_BAZOOKA)
	{
		VectorSet(offset, 0, 8,  self->viewheight-8);

		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, offset, forward, right, start);

		// project enemy back a bit and target there
		VectorCopy (self->enemy->s.origin, target);
		
		target[2] -= 24; // this will help create more splash damage

		VectorMA (target, (-0.5 * (crandom())) * (1.0 - (skill->value/4.0)), self->enemy->velocity, target);

		if (self->enemy->maxs[2] < self->cast_info.standing_max_z)
			target[2] += - ( 8 * random());
		else
			target[2] += self->enemy->viewheight - 4 - (16 * random());

		flash_number = MZ2_GUNNER_MACHINEGUN_1;

		VectorSubtract (target, start, aim);
		dist = VectorNormalize (aim);

		// idiot check
		{
			// clean shot???
			trace_t tr;
			vec3_t mins;
			vec3_t maxs;
			vec3_t origin;
			vec3_t destination;

			VectorCopy (self->s.origin, origin);
			origin[2] += self->viewheight;

			VectorCopy (self->enemy->s.origin, destination);
			destination[2] += self->enemy->viewheight;

			VectorSet (mins, -8, -8, -8);
			VectorSet (maxs,  8,  8,  8);
			
			tr = gi.trace (origin, mins, maxs, destination, self, MASK_SHOT);

			if (tr.ent != self->enemy)
			{
				if (!(AI_ForceTakeCover (self, self->enemy, false)))
				{
					self->cast_info.avoid(self, self->enemy, false);				
				}
				
				if (self->duration)
					self->duration--;

				// NAV_DrawLine (origin, destination);
				return;
			}
			goto skipbail; // causes bazooka dude to shoot twice
		}
	}
	else
	{
		VectorSet(offset, 0, 8,  self->viewheight-8);

		AngleVectors (self->s.angles, forward, right, NULL);
		G_ProjectSource (self->s.origin, offset, forward, right, start);

		// project enemy back a bit and target there
		VectorCopy (self->enemy->s.origin, target);
		VectorMA (target, (-0.5 * (crandom())) * (1.0 - (skill->value/4.0)), self->enemy->velocity, target);

		if (self->enemy->maxs[2] < self->cast_info.standing_max_z)
			target[2] += - ( 8 * random());
		else
			target[2] += self->enemy->viewheight - 4 - (16 * random());

		flash_number = MZ2_GUNNER_MACHINEGUN_1;

		VectorSubtract (target, start, aim);
		dist = VectorNormalize (aim);
	}
	
	// look for a new attack?
	if (	(dist < self->cast_info.max_attack_distance)
		&&	(	((random() < 0.1) && (self->cast_info.last_side_attack_time < (level.time - 2)))
			 ||	(	(!(self->cast_info.aiflags & AI_SIDE_ATTACK) || (self->cast_info.last_side_attack_time < (level.time - 2)))
				 &&	(directly_infront( self->enemy, self))
				 &&	(self->enemy->client)
				 &&	(self->enemy->client->pers.weapon)
				 &&	(self->enemy->client->pers.weapon->ammo))))		// if we are directly infront of them, try to strafe
	{
		if (self->cast_info.aiflags & AI_SIDE_ATTACK)
		{
			// self->cast_info.currentmove = &punk_move_shoot;
			if (self->spawnflags & PUNK_TOMMYGUN)
				self->cast_info.currentmove = &punk_move_run_tg_sht;
			else if (self->spawnflags & PUNK_SHOTGUN)
				self->cast_info.currentmove = &punk_move_run_shg_sht;
			else if (self->spawnflags & PUNK_HMG)
				self->cast_info.currentmove = &punk_move_run_hmg_sht;
			else if (self->spawnflags & PUNK_BAZOOKA)
				self->cast_info.currentmove = &punk_move_run_bazooka_sht;
			else if (self->spawnflags & PUNK_FLAMEGUN)
				self->cast_info.currentmove = &punk_move_run_flamegun_sht;
			else if (self->spawnflags & PUNK_GRENADE)
				self->cast_info.currentmove = &punk_move_run_grenade_sht;
			else
			{
				gi.dprintf ("missing weapon spawnflag\n");
				self->cast_info.currentmove = &punk_move_run_shg_sht;
			}
		}
		else
			self->cast_info.attack( self );
	}

skipbail:

	self->ideal_yaw = vectoyaw( aim );

	if (self->spawnflags & PUNK_TOMMYGUN)
	{
		if (self->acc)
			cast_fire_bullet (self, start, aim, 4, 0, DEFAULT_BULLET_HSPREAD>>self->acc, DEFAULT_BULLET_VSPREAD>>self->acc, flash_number);
		else
		cast_fire_bullet (self, start, aim, 4, 0, DEFAULT_BULLET_HSPREAD, DEFAULT_BULLET_VSPREAD, flash_number);
		gi.sound(self, CHAN_WEAPON, tommy_soundindex, 1, ATTN_NORM, 0);
	}
	else if (self->spawnflags & PUNK_SHOTGUN)
	{
		// tweeking the damage
		cast_fire_shotgun (self, start, aim, 6, 0, DEFAULT_SHOTGUN_HSPREAD, DEFAULT_SHOTGUN_VSPREAD, DEFAULT_SHOTGUN_COUNT, flash_number); 
		gi.sound(self, CHAN_WEAPON, shotgun_soundindex, 1, ATTN_NORM, 0);
		self->cast_info.aiflags |= AI_RELOAD;
	}
	else if (self->spawnflags & PUNK_HMG)
	{
		fire_bullet (self, start, aim, 15, 50, DEFAULT_BULLET_HSPREAD>>self->acc, DEFAULT_BULLET_VSPREAD>>self->acc, MOD_BARMACHINEGUN);
		{
			if (self->lastduration == 1)
			{
				gi.sound(self, CHAN_WEAPON, gi.soundindex("weapons/hmg/hmg.wav"), 1, ATTN_NORM, 0);
			}
			
			if (self->lastduration == 0)
				self->durationflag = 1;
		}
	}
	else if (self->spawnflags & PUNK_BAZOOKA)
	{
		{
			int damage = 100;
			int	speed = 900;

			cast_fire_rocket (self, start, aim, damage, speed, MOD_ROCKET);
			gi.sound (self, CHAN_WEAPON, rocketgun_soundindex, 1, ATTN_NORM, 0);
		}
	}
	else if (self->spawnflags & PUNK_FLAMEGUN)
	{
		int damage = 1;
		int	kick = 4;
		static int flamesnd = 0;
		
		extern void fire_target_flamethrower (edict_t *self, vec3_t start, vec3_t forward, int damage, int kick, int mod);

		fire_flamethrower(self, start, aim, damage, 0, MOD_FLAMETHROWER);
		self->s.renderfx2 |= RF2_FLAMETHROWER;
//		fire_target_flamethrower(self, start, aim, damage, 0, MOD_FLAMETHROWER);
//		self->s.renderfx2 = RF2_FLAMESHOOTER;

		flamesnd++;
		
		if (flamesnd > 2)
			flamesnd = 0;

		if (flamesnd == 1)
			gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/flame_thrower/flame2.wav"), 1, ATTN_NORM, 0);
		else if (flamesnd == 2)
			gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/flame_thrower/flame3.wav"), 1, ATTN_NORM, 0);
		else
			gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/flame_thrower/flame1.wav"), 1, ATTN_NORM, 0);

	}
	else if (self->spawnflags & PUNK_GRENADE)
	{
		// Ridah, lob it higher if they're further away
		if (VectorDistance(self->s.origin, self->enemy->s.origin) > 512)
			aim[2] += 0.4;

		fire_grenade (self, start, aim, 150, 450, 2.0, 256);
		gi.sound(self, CHAN_AUTO, gi.soundindex("weapons/grenade_launcher/gl_fire.wav"), 1, ATTN_NORM, 0);
	}
	else
	{
		gi.dprintf ("Error: Bang Bang not tagged right\n");
	}

}

void punk_shotgun_reload( edict_t *self )
{
	if (self->cast_info.aiflags & AI_TURN_BLOCKED)
	{	// abort the side run
		self->cast_info.aiflags &= ~AI_TURN_BLOCKED;
		AI_EndAttack(self);
	}

	if (!(self->spawnflags & PUNK_SHOTGUN))
	{	// no need to reload
		return;
	}

	gi.sound(self, CHAN_AUTO, shotgun_reload_soundindex, 1, ATTN_NORM, 0);
	self->cast_info.aiflags &= ~AI_RELOAD;
}

void punk_firegun_right( edict_t *self )
{
//	vec3_t	vec;
//	float	oldyaw;

	if (!self->enemy || (self->enemy->health <= 0))
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

/*
	oldyaw = self->s.angles[YAW];

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	VectorNormalize( vec );

	self->s.angles[YAW] = vectoyaw( vec );
*/
	self->cast_info.aiflags |= AI_SIDE_ATTACK;
	punk_firegun(self);
	self->cast_info.aiflags &= ~AI_SIDE_ATTACK;
/*
	// keep running to the side
	self->ideal_yaw = self->s.angles[YAW] + 90;

	self->s.angles[YAW] = oldyaw;
*/
}

void punk_firegun_left( edict_t *self )
{
//	vec3_t	vec;
//	float	oldyaw;

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

/*
	oldyaw = self->s.angles[YAW];

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	VectorNormalize( vec );

	self->s.angles[YAW] = vectoyaw( vec );
*/
	self->cast_info.aiflags |= AI_SIDE_ATTACK;
	punk_firegun(self);
	self->cast_info.aiflags &= ~AI_SIDE_ATTACK;
/*
	// keep running to the side
	self->ideal_yaw = self->s.angles[YAW] - 90;

	self->s.angles[YAW] = oldyaw;
*/
}

void punk_pain (edict_t *self, edict_t *other, float kick, int damage, int mdx_part, int mdx_subobject)
{
	int		orientation;

	if (self->s.renderfx2 & RF2_FLAMETHROWER)
		self->s.renderfx2 &= ~RF2_FLAMETHROWER;
	
	AI_CheckMakeEnemy( self, other );

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3 + random();

	if (skill->value >= 3)
		return;		// no pain anims in nightmare

	// faked client pain sound

	// JOSEPH 26-MAY-99
	if (self->name_index == NAME_NICKIBLANCO)
	{
		Voice_Random (self, self->enemy, &nickiblanco[2], 4);
	}
	else if (self->name_index == NAME_TYRONE)
	{
		Voice_Random (self, self->enemy, &ty_tyrone[2], 4); 
	}
	else if (self->name_index == NAME_MOKER)
	{
		Voice_Random (self, self->enemy, &steeltown_moker[2], 4);
	}
	// END JOSEPH
	
	// gi.sound (self, CHAN_VOICE, gi.soundindex(va("*pain%i_%i.wav", l, r)), 1, ATTN_NORM, 0);
	

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

	if (self->maxs[2] < self->cast_info.standing_max_z)
	{	// crouching
		
		switch (orientation)
		{
		case ORIENTATION_CENTER :
			{
				self->cast_info.currentmove = &punk_move_crouch_painC;
				break;
			}
		case ORIENTATION_LEFT :
			{
				self->cast_info.currentmove = &punk_move_crouch_painL;
				break;
			}
		case ORIENTATION_RIGHT :
			{
				self->cast_info.currentmove = &punk_move_crouch_painR;
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
						self->cast_info.currentmove = &punk_move_pain_chest;		
						break;
					}
				case ORIENTATION_LEFT :
					{
						self->cast_info.currentmove = &punk_move_pain_Larm;		
						break;
					}
				case ORIENTATION_RIGHT :
					{
						self->cast_info.currentmove = &punk_move_pain_Rarm;		
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
							self->cast_info.currentmove = &punk_move_pain_crch; 
						}
						else
						{
							self->cast_info.currentmove = &punk_move_pain_butt; 			
						}
						break;
					}
				case ORIENTATION_LEFT :
					{
						self->cast_info.currentmove = &punk_move_pain_Lleg; 			
						break;
					}
				case ORIENTATION_RIGHT :
					{
						self->cast_info.currentmove = &punk_move_pain_Rleg; 			
						break;
					}
				}
			}
			else if (mdx_part == PART_HEAD)
			{
				self->cast_info.currentmove = &punk_move_pain_head; 
			}

	}

}

// JOSEPH 26-FEB-99
void punk_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	trace_t	tr;
	vec3_t	end;
	edict_t *playthud1, *playthud2;

	if (self->s.renderfx2 & RF2_FLAMETHROWER)
		self->s.renderfx2 &= ~RF2_FLAMETHROWER;

	self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
	self->s.model_parts[PART_GUN2].invisible_objects = (1<<0 | 1<<1);

// regular death
	self->takedamage = DAMAGE_YES;

	if (DeathByGib(self, inflictor, attacker, damage))
	{	// gib
		self->deadflag = DEAD_DEAD;
		GibEntity( self, inflictor, damage );
		return;
	}

	if (self->deadflag == DEAD_DEAD)
		return;

	self->deadflag = DEAD_DEAD;

	// JOSEPH 7-MAY-99
	if (!(self->cast_info.aiflags & AI_MELEE))
	{
		if (self->spawnflags & PUNK_SHOTGUN)
			SpawnTheWeapon (self, "weapon_shotgun_e");
		else if (self->spawnflags &	PUNK_HMG)
			SpawnTheWeapon (self, "weapon_heavymachinegun_e");
		else if (self->spawnflags & PUNK_BAZOOKA)
			SpawnTheWeapon (self, "weapon_bazooka_e");
		else if (self->spawnflags & PUNK_FLAMEGUN)
			SpawnTheWeapon (self, "weapon_flamethrower_e");
		else if (self->spawnflags & PUNK_GRENADE)
			SpawnTheWeapon (self, "weapon_grenadelauncher_e");
		else
			SpawnTheWeapon (self, "weapon_tommygun_e");
	}
	// END JOSEPH

	// EP_SpecialEventDeath (self);

	VectorCopy (self->s.origin, end);
	end[2] -= 64;
	tr = gi.trace (self->s.origin, self->mins, self->maxs, end, self, MASK_SHOT);
	
	if (mdx_part == PART_HEAD)
	{	// probably head impact, we should really be passing in the model_part here
		self->cast_info.currentmove = &punk_move_death3;

		playthud1 = G_Spawn();
		VectorCopy (self->s.origin, playthud1->s.origin);
		playthud1->thudsurf = tr.surface->flags;
		playthud1->thudsnd = 1; 
		playthud1->nextthink = level.time + (0.1*9.0);
		playthud1->think = think_playthud;
		gi.linkentity (playthud1);

		playthud2 = G_Spawn();
		VectorCopy (self->s.origin, playthud2->s.origin);
		playthud2->thudsurf = tr.surface->flags;
		playthud2->thudsnd = 2; 
		playthud2->nextthink = level.time + (0.1*20.0);
		playthud2->think = think_playthud;
		gi.linkentity (playthud2);		
	}
	else if (self->maxs[2] < self->cast_info.standing_max_z)
	{
		self->cast_info.currentmove = &punk_move_crouch_death;

		playthud1 = G_Spawn();
		VectorCopy (self->s.origin, playthud1->s.origin);
		playthud1->thudsurf = tr.surface->flags;
		playthud1->thudsnd = 1; 
		playthud1->nextthink = level.time + (0.1*6.0);
		playthud1->think = think_playthud;
		gi.linkentity (playthud1);
			
		playthud2 = G_Spawn();
		VectorCopy (self->s.origin, playthud2->s.origin);
		playthud2->thudsurf = tr.surface->flags;
		playthud2->thudsnd = 2; 
		playthud2->nextthink = level.time + (0.1*9.0);
		playthud2->think = think_playthud;
		gi.linkentity (playthud2);			
	}
	else
	{
		int n;

		n = rand() % 4;
		if (n == 0)
		{
			self->cast_info.currentmove = &punk_move_death1;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*6.0);
			playthud1->think = think_playthud;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*9.0);
			playthud2->think = think_playthud;
			gi.linkentity (playthud2);				
		}
		else if (n == 1)
		{
			self->cast_info.currentmove = &punk_move_death2;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*5.0);
			playthud1->think = think_playthud;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*9.0);
			playthud2->think = think_playthud;
			gi.linkentity (playthud2);				
		}
		else if (n == 2)
		{
			self->cast_info.currentmove = &punk_move_death3;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*9.0);
			playthud1->think = think_playthud;
			gi.linkentity (playthud1);

			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*20.0);
			playthud2->think = think_playthud;
			gi.linkentity (playthud2);			
		}
		else
		{
			self->cast_info.currentmove = &punk_move_death4;

			playthud1 = G_Spawn();
			VectorCopy (self->s.origin, playthud1->s.origin);
			playthud1->thudsurf = tr.surface->flags;
			playthud1->thudsnd = 1; 
			playthud1->nextthink = level.time + (0.1*6.0);
			playthud1->think = think_playthud;
			gi.linkentity (playthud1);
				
			playthud2 = G_Spawn();
			VectorCopy (self->s.origin, playthud2->s.origin);
			playthud2->thudsurf = tr.surface->flags;
			playthud2->thudsnd = 2; 
			playthud2->nextthink = level.time + (0.1*8.0);
			playthud2->think = think_playthud;
			gi.linkentity (playthud2);				
		}
	}

	// JOSEPH 7-DEC-98
    //if (!(self->spawnflags & PUNK_MELEE))
	//{
		//self->s.model_parts[PART_GUN].invisible_objects = (1<<0 | 1<<1);
		//Shot_Drop_Item(self, FindItem("Tommygun"), "models/weapons/g_tomgun/tomgun_pu.mdx");
	//}
	// END JOSEPH	
	
	// JOSEPH 26-MAY-99
	if (!self->onfiretime)
	{
		if (self->name_index == NAME_NICKIBLANCO)
			Voice_Random (self, self->enemy, nickiblanco, 2);
		else if (self->name_index == NAME_TYRONE)
			Voice_Random (self, attacker, &ty_tyrone[0], 2);
		else if (self->name_index == NAME_MOKER)
			Voice_Random (self, attacker, &steeltown_moker[0], 2);
		else
			Voice_Random (self, attacker, &male_specific[8], 2);
	}
	// END JOSEPH
	
	// gi.sound (self, CHAN_VOICE, gi.soundindex(va("*death%i.wav", (rand()%4)+1)), 1, ATTN_NORM, 0);
}
// END JOSEPH


// =========================================================================

/*QUAKED cast_punk (1 .5 0) (-16 -16 -24) (16 16 48) FLASH_LIGHT TRIGGERED_START FLAM_BE BAZOOKA HMG IMMEDIATE_FOLLOW_PATH TOMMYGUN GRENADE 
Fidel Character
cast_group defines which group the character is a member of
default cast_group is 0, which is neutral (won't help others out)
player's cast_group is 1 (friendly characters)

The default weapon for a punk is the shotgun

model="models\actors\punk\"


*/
void SP_cast_punk(edict_t *self)
{
	int i;
	char	*head_skin, *body_skin, *legs_skin;
	int	skin;

	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}

	if (!(self->spawnflags & (PUNK_FLAMEGUN|PUNK_BAZOOKA|PUNK_HMG|PUNK_TOMMYGUN|PUNK_GRENADE)))
	{
		self->spawnflags |= PUNK_SHOTGUN;
	}

//self->spawnflags &= ~(PUNK_FLAMEGUN|PUNK_BAZOOKA|PUNK_HMG|PUNK_TOMMYGUN|PUNK_GRENADE);
//self->spawnflags |= PUNK_FLAMEGUN;

	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	self->s.skinnum = (self->skin-1) * 3;

	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs,  16,  16,  48);

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

	tommy_soundindex = gi.soundindex("weapons/machinegun/machgf1b.wav");
	shotgun_soundindex = gi.soundindex("weapons/shotgun/shotgf1b.wav");
	shotgun_reload_soundindex = gi.soundindex("weapons/shotgun/shotgr1b.wav");
	heavymachinegun_soundindex = gi.soundindex ("weapons/hmg/single.wav");
	rocketgun_soundindex = gi.soundindex ("weapons/rocket_launcher/rl_fire.wav");

	// ------------------------------------------------------------------------
	// initialize all model_part data
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;

	switch (self->head)
	{
		case 1:
			self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/punk/bald_head.mdx");
			break;
		case 2:
			self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/punk/ski_head.mdx");
			break;
		case 3:
			self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/punk/weld_head.mdx");
			break;
		default:
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/punk/head.mdx");
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
	gi.GetObjectBounds( "models/actors/punk/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/punk/legs.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_LEGS].modelindex, legs_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].baseskin = self->s.model_parts[PART_LEGS].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/punk/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/punk/body.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_BODY].modelindex, body_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].baseskin = self->s.model_parts[PART_BODY].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/punk/body.mdx", &self->s.model_parts[PART_BODY] );

	if (self->spawnflags & PUNK_TOMMYGUN)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/punk/tommygun.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/punk/tommygun.mdx", &self->s.model_parts[PART_GUN] );
	}
	else if (self->spawnflags & PUNK_SHOTGUN)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/punk/shotgun.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/punk/shotgun.mdx", &self->s.model_parts[PART_GUN] );
	}
	else if (self->spawnflags & PUNK_HMG)
	{
		// NOTE TO SELF: tell Jason to make a gun.mdx for this weapon
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/punk/hmg.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/punk/hmg.mdx", &self->s.model_parts[PART_GUN] );
	}
	else if (self->spawnflags & PUNK_BAZOOKA)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/punk/rocket_lnch.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/punk/rocket_lnch.mdx", &self->s.model_parts[PART_GUN] );
	}
	else if (self->spawnflags & PUNK_FLAMEGUN)
	{
		// NOTE TO SELF: tell Jason to make a gun.mdx for this weapon
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/punk/flamethrower.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/punk/flamethrower.mdx", &self->s.model_parts[PART_GUN] );
	}	
	else if (self->spawnflags & PUNK_GRENADE)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/punk/grenade_lnch.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/punk/grenade_lnch.mdx", &self->s.model_parts[PART_GUN] );

		self->cast_info.aiflags |= AI_GRENADE_GUY;
	}
	else
	{
		gi.dprintf ("error no weapon spawnflag\n");

		self->s.num_parts++;
		self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/actors/punk/shotgun.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_GUN].baseskin = self->s.model_parts[PART_GUN].skinnum[i] = 0;// self->s.skinnum;
		gi.GetObjectBounds( "models/actors/punk/shotgun.mdx", &self->s.model_parts[PART_GUN] );
	}

	if (self->count & 1) // cigar
	{
		self->s.num_parts++;
		self->s.model_parts[PART_CIGAR].modelindex = gi.modelindex("models/actors/punk/cigar.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_CIGAR].baseskin = self->s.model_parts[PART_CIGAR].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/punk/cigar.mdx", &self->s.model_parts[PART_CIGAR] );
	}

	if (self->count & 2) // fedora hat
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/punk/fedora.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/punk/fedora.mdx", &self->s.model_parts[PART_HAT] );
	}
	else if (self->count & 4) // stetson hat
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/punk/stetson.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/punk/stetson.mdx", &self->s.model_parts[PART_HAT] );
	}
	else if (self->count & 8) // cap (hat)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/punk/cap.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/punk/cap.mdx", &self->s.model_parts[PART_HAT] );
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

	self->pain = punk_pain;
	self->die = punk_die;

	self->cast_info.checkattack = AI_CheckAttack;

	self->cast_info.attack = punk_attack;
	self->cast_info.long_attack = punk_long_attack;
	self->cast_info.talk = punk_talk;
	self->cast_info.avoid = punk_avoid;

	self->cast_info.catch_fire = punk_catch_fire;

// Ridah, new AI system stuff!
	self->cast_info.max_attack_distance = 2000;

	// Ridah, so they don't shoot the flamegun from too far away
	if (self->spawnflags & PUNK_FLAMEGUN)
		self->cast_info.max_attack_distance = 384;

	if (self->spawnflags & PUNK_SHOTGUN)
		self->cast_info.move_stand = &punk_move_sg_stand;
	else
		self->cast_info.move_stand = &punk_move_stand;

// 	self->cast_info.move_crstand = &punk_move_crouch_stand;
	self->cast_info.move_crstand = &punk_move_crch_astand;

	self->cast_info.move_run = &punk_move_run_gun_down;
	
	// RAFAEL
	if (self->spawnflags & 1)
		self->cast_info.move_runwalk = &punk_move_walk_gdownFLASHLIGHT;
	else
		self->cast_info.move_runwalk = &punk_move_walk_gdown;

	self->cast_info.move_crwalk = &punk_move_crh_shuf;

	self->cast_info.move_jump = &punk_move_jump;

	self->cast_info.move_avoid_walk = &punk_move_avoid_walk;
	self->cast_info.move_avoid_run = &punk_move_avoid_run;
	self->cast_info.move_avoid_reverse_walk = &punk_move_avoid_reverse_walk;
	self->cast_info.move_avoid_reverse_run = &punk_move_avoid_reverse_run;
	self->cast_info.move_avoid_crwalk = &punk_move_avoid_crouch_walk;

	self->cast_info.move_crouch_down = &punk_move_crouch_stand_down;
	self->cast_info.move_stand_up = &punk_move_crouch_stand_up;

	self->cast_info.move_lside_step = &punk_move_lside_step;
	self->cast_info.move_rside_step = &punk_move_rside_step;

	self->cast_info.move_start_climb = &punk_move_clmb_loop;
	self->cast_info.move_end_climb = &punk_move_clmb_over;

// Ridah, done.

	gi.linkentity (self);

	self->cast_info.currentmove = self->cast_info.move_stand;

	if (!self->cast_info.scale)
		self->cast_info.scale = MODEL_SCALE;

	self->s.scale = self->cast_info.scale - 1.0;

	// talk by default
	self->cast_info.aiflags |= AI_TALK;

	if (!self->acc)
		self->acc = 2;

	walking_cast_start (self);
}
