// dog
#include "g_local.h"
#include "ai_dog.h"

void dog_sound (edict_t *self);
void dog_end_stand (edict_t *self);
void dog_sound_think (edict_t *self);
void dog_melee (edict_t *self);
void dog_evade_amb (edict_t *self);
void dog_melee_bail (edict_t *self);
void dog_evade_checkadjust (edict_t *self);
void dog_evade_adjust (edict_t *self);
void dog_lick2( edict_t *self );
void dog_pounce (edict_t *self);
void dog_talk_think ( edict_t *self );
void dog_bite (edict_t *self);
void dog_bark (edict_t *self);
void dog_growl (edict_t *self);

#include "ai_dog_tables.h"

char *wuf[7] =
{
"actors/dog/dg_bark1.wav",
"actors/dog/dg_bark2.wav",
"actors/dog/dg_die.wav",
"actors/dog/dg_grwl1.wav",
"actors/dog/dg_grwl2.wav",
"actors/dog/dg_lunge.wav",
"actors/dog/dg_yelp.wav"
};

void dog_yelp (edict_t *self)
{
	self->last_talk_time = level.time;
	gi.sound( self, CHAN_VOICE, gi.soundindex( wuf[6] ), 1, ATTN_NORM, 0 );
}

void dog_bark (edict_t *self)
{
	self->last_talk_time = level.time;
	gi.sound( self, CHAN_VOICE, gi.soundindex( wuf[rand()%2] ), 1, ATTN_NORM, 0 );
}

void dog_growl (edict_t *self)
{
	self->last_talk_time = level.time + 0.5;	// growl lasts a bit longer
	gi.sound( self, CHAN_BODY, gi.soundindex( wuf[3+rand()%3] ), 1, ATTN_NORM, 0 );
}

void dog_talk_think ( edict_t *self )
{
	edict_t	*talk_ent;
	cast_memory_t	*mem;

	if (!(talk_ent = self->cast_info.talk_ent))
		return;

	if (VectorDistance( talk_ent->s.origin, self->s.origin ) > 600)
	{
		self->cast_info.talk_ent = NULL;
		return;
	}

	if (	(self->cast_info.talk_ent == &g_edicts[1])
		&&	(self->cast_info.talk_ent->last_talk_time < (level.time - TALK_OTHER_DELAY*2))
		&&	(self->last_talk_time > (level.time - TALK_SELF_DELAY)))
	{
		return;
	}

//	if (last_client_talk && last_client_talk > (level.time - TALK_OTHER_DELAY))
//		return;	// don't talk too much around the client

	if ((talk_ent->health <= 0) || !visible(self, talk_ent) || !infront(talk_ent, self))
	{
		self->cast_info.talk_ent = NULL;
		return;
	}

	mem = level.global_cast_memory[self->character_index][talk_ent->character_index];
	if (!mem || (mem->flags & MEMORY_NO_TALK))
		return;

	// say something!
	if (	(	(self->last_talk_time < (level.time - TALK_SELF_DELAY))			// we haven't spoken for a while
			 ||	(	(talk_ent->client || talk_ent->last_talk_time)		// if they haven't spoken yet, don't bother
				 &&	(talk_ent->last_talk_time > (level.time - TALK_OTHER_DELAY*1.5))	// or they've just said something, and we've allowed some time for them to finish saying it
				 &&	(talk_ent->cast_info.talk_ent == self)
				 &&	(self->last_talk_time < talk_ent->last_talk_time)
				 &&	(self->last_talk_time < (level.time - TALK_OTHER_DELAY))))
		&&	(talk_ent->last_talk_time < (level.time - TALK_OTHER_DELAY)))
	{
		if (talk_ent->client)
		{
			// should we be aggressive? or friendly?

			if ((self->moral < MORAL_AGGRESSIVE) || (!self->profanity_level && talk_ent->profanity_level && (self->moral < rand()%MORAL_MAX)))
			{		// friendly
				self->cast_info.currentmove = &dog_move_sniff;
				dog_bark( self );
			}
			else if (self->profanity_level)
			{	// attack!
				AI_MakeEnemy( self, talk_ent, 0 );
				dog_bark( self );
			}
			else	// ready to attack at any second
			{
				self->cast_info.currentmove = &dog_move_sniff;
				dog_growl (self);
				self->profanity_level = 3;
			}

			self->last_talk_time = level.time;

			if (!infront( self, talk_ent ))
			{
				self->cast_info.avoid( self, talk_ent, true );
			}
		}
	}
}

void dog_end_stand( edict_t *self )
{
	if (self->cast_info.move_stand_evade && (self->last_stand_evade > (level.time - 3)))
		return;

	if (random() <= 0.2)
	{
		self->cast_info.currentmove = &dog_move_sniff;
	}
	else if (random() <= 0.1)
	{
		self->cast_info.currentmove = &dog_move_bark;
		dog_bark (self);
	}
/*
	else if	(	(random() <= 0.1)
			&&	(AI_SideTrace( self, 32, 90, -1 )))
	{
		self->cast_info.currentmove = &dog_move_pee;
	}
*/
	else
	{
		self->cast_info.currentmove = self->cast_info.move_stand;
	}
}

void dog_backoff( edict_t *self, edict_t *other )
{

}

void dog_pain (edict_t *self, edict_t *other, float kick, int damage, int mdx_part, int mdx_subobject)
{
	int rnd;
	int baseskin;//, currentskin;

	baseskin = self->s.model_parts[mdx_part].baseskin;
						
	if (self->health < (self->max_health * 0.5))
	{
		self->s.model_parts[PART_HEAD].skinnum[0] =  baseskin + 2;
	}
	else if (self->health < (self->max_health * 0.75))
	{
		self->s.model_parts[PART_HEAD].skinnum[0] =  baseskin + 1;
	}

	AI_CheckMakeEnemy( self, other );

	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3 + random();

	if (skill->value >= 3)
		return;		// no pain anims in nightmare


	if (rand()%2)
		dog_yelp (self);


	// Ridah, randomly don't play an animation, since it' leaves them WAY open to be killed
	if (skill->value > 0 && rand()%2)
		return;

	rnd = rand()%3;

	switch (rnd)
	{
	case 0:
		self->cast_info.currentmove = &dog_move_pain1;
		break;
	case 1:
		self->cast_info.currentmove = &dog_move_pain2;
		break;
	case 2:
		self->cast_info.currentmove = &dog_move_pain3;
		break;
	}

}

void dog_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	int rnd;

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

//	if (!self->onfiretime)
		dog_yelp (self);

	rnd = rand()%1;

	switch (rnd)
	{
	case 0:
		self->cast_info.currentmove = &dog_move_death1;
		break;
	case 1:
		self->cast_info.currentmove = &dog_move_death2;
		break;
	}

}

qboolean dog_attack (edict_t *self)
{
	vec3_t	vec;
	float dist;

	self->cast_info.aiflags |= AI_RUN_LIKE_HELL;	// dog runs really fast

	VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
	dist = VectorNormalize( vec );

	// start panting now when we stop
	self->cast_info.move_stand = &dog_move_pant;

	// yell at them?
	if (self->last_talk_time < (level.time - 0.5*TALK_FIGHTING_DELAY))
	{
		if (rand()%2)
			dog_bark(self);
		else
			dog_growl(self);
	}

	{
		qboolean attack=false;

		if (dist < 48 && VectorLength( self->enemy->velocity ) < 250)
		{
			attack = true;
		}
		else if (dist < 64)
		{
			attack = false;	// so we do a high attack
		}
		else	// are they running towards us?
		{
			VectorSubtract( self->enemy->s.origin, self->s.origin, vec );
			VectorMA( vec, 0.5, self->enemy->velocity, vec );
			dist = VectorNormalize( vec );

			if (dist < 96)
			{
				attack = true;
			}
			
		}

		if (attack)
		{
			int rnd;

			self->ideal_yaw = vectoyaw(vec);

			M_ChangeYaw( self );

			if (vec[2] < -0.5)
			{
				self->cast_info.currentmove = &dog_move_low_atk;
			}
			else if (vec[2] < -0.1)
			{
				self->cast_info.currentmove = &dog_move_med_atk;
			}
			else if (vec[2] > 0.5)
			{
				self->cast_info.currentmove = &dog_move_upr_atk;
			}
			else if (self->enemy->maxs[2] < self->enemy->cast_info.standing_max_z)
			{
				self->cast_info.currentmove = &dog_move_med_atk;
			}
/*
			if (self->enemy->maxs[2] < 30)
			{
				if (rand()%10 < 8)
					self->cast_info.currentmove = &dog_move_med_atk;
				else
					self->cast_info.currentmove = &dog_move_low_atk;
			}
			else if (self->maxs[2] > self->enemy->maxs[2] || self->s.origin[2] > self->enemy->s.origin[2])
			{
				self->cast_info.currentmove = &dog_move_low_atk;
			}
			else if (self->s.origin[2] < self->enemy->s.origin[2])
			{
				self->cast_info.currentmove = &dog_move_upr_atk;
			}
*/
			else
			{
				rnd = rand()%10;

				if (dist < 48 && rnd < 4)
					self->cast_info.currentmove = &dog_move_low_atk;
				else if (rnd < 6)
					self->cast_info.currentmove = &dog_move_med_atk;
				else
					self->cast_info.currentmove = &dog_move_upr_atk;
			}	

			self->cast_info.aiflags &=~ AI_RUSH_THE_PLAYER;
			return true;
		}
		else if (dist < 180)	// Ridah, increased this to help SR4 dogs jump onto cars
		{
			self->ideal_yaw = vectoyaw(vec);
			M_ChangeYaw( self );

			self->cast_info.currentmove = &dog_move_upr_atk;
			return true;
		}
		else if (dist < 400)
			self->cast_info.aiflags |= AI_RUSH_THE_PLAYER;

	}

	return false;
}


void dog_bite (edict_t *self)
{
	vec3_t	start;//, offset;
	vec3_t	forward, right;

	float damage = 8;

	if (self->cast_info.currentmove == &dog_move_upr_atk)
		damage *= 2;		// double handed attack

	// yell at them?
	if (self->last_talk_time < (level.time - 1.0))
	{
		if (rand()%2)
			dog_bark(self);
		else
			dog_growl(self);
	}

	// VectorSet(offset, 0, 8,  self->viewheight - 4);
	//VectorSet (offset, 0, 8,  16);

	AngleVectors (self->s.angles, forward, right, NULL);

	//G_ProjectSource (self->s.origin, offset, forward, right, start);
	
	/*
	if (self->cast_info.currentmove == &dog_move_low_atk)
		start[2] -= 20;
	else if (self->cast_info.currentmove == &dog_move_med_atk)
		start[2] -= 8;
	else if (self->cast_info.currentmove == &dog_move_upr_atk)
		start[2] += 8;
	*/
	
	damage *= 0.5;	

	// fire_dogbite (self, start, forward, damage, 10, MOD_DOGBITE);
	if (self->enemy)
	{
//		trace_t		tr;
		vec3_t		aimdir, dang, end;

		VectorSubtract (self->enemy->s.origin, self->s.origin, aimdir);
		vectoangles (aimdir, dang);
		AngleVectors (dang, forward, NULL, NULL);
		VectorMA (self->s.origin, 16, forward, start);
		VectorMA (start, 32, forward, end);
		
		// ok it seems to line up with the head ok now
		// NAV_DrawLine (start, end);
		fire_blackjack( self, start, forward, damage, 0, MOD_DOGBITE );
		/*
		
		if (VectorLength (aimdir) < 96)
		{
			tr = gi.trace (start, NULL, NULL, end, self, MASK_SHOT );

			if (tr.ent->takedamage)
				T_Damage (tr.ent, self, self, aimdir, tr.endpos, tr.plane.normal, damage, 0, DAMAGE_BULLET, MOD_DOGBITE); 
		}
		// ok lets see why this isnt working
		else if (self->enemy->groundentity == self)
			T_Damage (self->enemy, self, self, aimdir, self->enemy->s.origin, vec3_origin, damage, 0, DAMAGE_BULLET, MOD_DOGBITE); 
		*/
	}
}

void dog_long_attack (edict_t *self)
{
}


void dog_pounce (edict_t *self)
{
	if (!self->enemy)
		return;

	self->ideal_yaw = entyaw( self, self->enemy );
	M_ChangeYaw( self );

	// leap if on ground
	if (self->groundentity)
	{
		AngleVectors( self->s.angles, self->velocity, NULL, NULL );
		VectorScale( self->velocity, 500, self->velocity );
		self->velocity[2] = 200;
		self->groundentity = NULL;
	}

}


void dog_avoid ( edict_t *self, edict_t *other, qboolean face )
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

	if (!AI_SideTrace( self, -64, 0, 1))
		self->cast_info.currentmove = &dog_move_avoid_reverse_walk;
	else
		self->cast_info.currentmove = &dog_move_avoid_walk;
}

void dog_catch_fire( edict_t *self, edict_t *other )
{
	self->enemy = NULL;		// stop attacking
	self->cast_info.currentmove = &dog_move_run_on_fire;
}

/*QUAKED cast_dog (1 .5 0) (-16 -16 -16) (16 16 22) x TRIGGERED_START x x x 
Dog 
cast_group defines which group the character is a member of
default cast_group is 0, which is neutral (won't help others out)
player's cast_group is 1 (friendly characters)
skin = 1 or 2
model="models\actors\dog\"
*/
void SP_cast_dog (edict_t *self)
{
	int i;
	int	skin;

//	return;

	if (deathmatch->value)
	{
		G_FreeEdict (self);
		return;
	}
	
	self->movetype = MOVETYPE_STEP;
	self->solid = SOLID_BBOX;
	
	skin = self->s.skinnum = (self->skin-1) * 3;
	
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs,  16,  16,  DUCKING_MAX_Z+2);

	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->art_skins = NULL;

	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/enemy_dog/enemy_dog.mdx");
	skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].baseskin = self->s.model_parts[PART_HEAD].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/enemy_dog/enemy_dog.mdx", &self->s.model_parts[PART_HEAD] );

	if (!self->health)
		self->health = 200;
	self->gib_health = -200;
	self->mass = 100;

	self->gender = GENDER_NONE;

	self->yaw_speed = 20;

	self->pain = dog_pain;
	self->die = dog_die;

	self->cast_info.checkattack = AI_CheckAttack;
	self->cast_info.attack = dog_attack;
	self->cast_info.long_attack = dog_long_attack;
	self->cast_info.talk = dog_end_stand;
	self->cast_info.avoid = dog_avoid;
	self->cast_info.backoff = dog_backoff;
	self->cast_info.catch_fire = dog_catch_fire;
	self->cast_info.max_attack_distance = 128;

	self->cast_info.move_stand = &dog_move_amb;
	self->cast_info.move_run = &dog_move_run;
	self->cast_info.move_runwalk = &dog_move_trot;
//	self->cast_info.move_jump = &dog_move_jump;		// Jumping animation screws up jump attacking, so don't do one

	self->cast_info.move_avoid_walk = &dog_move_avoid_walk;
	self->cast_info.move_avoid_run = &dog_move_avoid_run;
	self->cast_info.move_avoid_reverse_walk = &dog_move_avoid_reverse_walk;
	self->cast_info.move_avoid_reverse_run = &dog_move_avoid_reverse_run;

	self->cast_info.move_evade = &dog_move_growl;

	self->cast_info.currentmove = self->cast_info.move_stand;

	self->cast_info.aiflags |= AI_MELEE;
	self->cast_info.aiflags |= AI_NO_TALK;
	self->cast_info.aiflags |= AI_ADJUSTPITCH;
	
//	self->gravity = 0.7;

// Temp fix for Dog in SR2 that follows lamont
//if (self->leader_target)
//	self->target = NULL;
	
	// we're a dog, therefore we don't hide
	self->cast_info.aiflags |= AI_NO_TAKE_COVER;

	gi.linkentity (self);

	walking_cast_start (self);
}
