#include "g_local.h"
#include "ai_bum_sit.h"
#include "voice_punk.h"

void bum_sit_talk (edict_t *self);
void bum_sit_end_sit (edict_t *self);
void bum_talk_think( edict_t *self );

void ai_stand_onfire (edict_t *self, float dist);

mframe_t	bum_sit_frames_amb_sit[] = 
{
	ai_stand,	  0.000, bum_talk_think,	// frame 0
	ai_stand,	  0.000, bum_talk_think,	// frame 1
	ai_stand,	  0.000, bum_talk_think,	// frame 2
	ai_stand,	  0.000, bum_talk_think,	// frame 3
	ai_stand,	  0.000, bum_talk_think,	// frame 4
	ai_stand,	  0.000, bum_talk_think,	// frame 5
	ai_stand,	  0.000, bum_talk_think,	// frame 6
	ai_stand,	  0.000, bum_talk_think,	// frame 7
	ai_stand,	  0.000, bum_talk_think,	// frame 8
	ai_stand,	  0.000, bum_talk_think,	// frame 9
	ai_stand,	  0.000, bum_talk_think,	// frame 10
	ai_stand,	  0.000, bum_talk_think,	// frame 11
	ai_stand,	  0.000, bum_talk_think,	// frame 12
	ai_stand,	  0.000, bum_talk_think,	// frame 13
	ai_stand,	  0.000, bum_talk_think,	// frame 14
	ai_stand,	  0.000, bum_talk_think,	// frame 15
	ai_stand,	  0.000, bum_talk_think,	// frame 16
	ai_stand,	  0.000, bum_talk_think,	// frame 17
	ai_stand,	  0.000, bum_talk_think,	// frame 18
	ai_stand,	  0.000, bum_talk_think,	// frame 19
	ai_stand,	  0.000, bum_talk_think,	// frame 20
	ai_stand,	  0.000, bum_talk_think,	// frame 21
	ai_stand,	  0.000, bum_talk_think,	// frame 22
	ai_stand,	  0.000, bum_talk_think,	// frame 23
	ai_stand,	  0.000, bum_talk_think,	// frame 24
	ai_stand,	  0.000, bum_talk_think,	// frame 25
	ai_stand,	  0.000, bum_talk_think,	// frame 26
	ai_stand,	  0.000, bum_talk_think,	// frame 27
	ai_stand,	  0.000, bum_talk_think,	// frame 28
	ai_stand,	  0.000, bum_talk_think,	// frame 29
	ai_stand,	  0.000, bum_talk_think,	// frame 30
	ai_stand,	  0.000, bum_talk_think,	// frame 31
	ai_stand,	  0.000, bum_talk_think,	// frame 32
	ai_stand,	  0.000, bum_talk_think,	// frame 33
	ai_stand,	  0.000, bum_talk_think,	// frame 34
	ai_stand,	  0.000, bum_talk_think,	// frame 35
	ai_stand,	  0.000, bum_talk_think,	// frame 36
	ai_stand,	  0.000, bum_talk_think,	// frame 37
	ai_stand,	  0.000, bum_talk_think,	// frame 38
	ai_stand,	  0.000, bum_talk_think,	// frame 39
	ai_stand,	  0.000, bum_talk_think,	// frame 40
	ai_stand,	  0.000, bum_talk_think,	// frame 41
	ai_stand,	  0.000, bum_talk_think,	// frame 42
	ai_stand,	  0.000, bum_talk_think,	// frame 43
	ai_stand,	  0.000, bum_talk_think,	// frame 44
	ai_stand,	  0.000, bum_talk_think,	// frame 45
	ai_stand,	  0.000, bum_talk_think,	// frame 46
	ai_stand,	  0.000, bum_talk_think,	// frame 47
	ai_stand,	  0.000, bum_talk_think,	// frame 48
	ai_stand,	  0.000, bum_talk_think,	// frame 49
	ai_stand,	  0.000, bum_talk_think,	// frame 50
	ai_stand,	  0.000, bum_talk_think,	// frame 51
};
mmove_t	bum_sit_move_amb_sit = {FRAME_amb_sit_01, FRAME_amb_sit_52, bum_sit_frames_amb_sit, bum_sit_end_sit};

mframe_t	bum_sit_frames_leg_shuf[] = 
{
	ai_stand,	  0.000, bum_talk_think,	// frame 0
	ai_stand,	  0.000, bum_talk_think,	// frame 1
	ai_stand,	  0.000, bum_talk_think,	// frame 2
	ai_stand,	  0.000, bum_talk_think,	// frame 3
	ai_stand,	  0.000, bum_talk_think,	// frame 4
	ai_stand,	  0.000, bum_talk_think,	// frame 5
	ai_stand,	  0.000, bum_talk_think,	// frame 6
	ai_stand,	  0.000, bum_talk_think,	// frame 7
	ai_stand,	  0.000, bum_talk_think,	// frame 8
	ai_stand,	  0.000, bum_talk_think,	// frame 9
	ai_stand,	  0.000, bum_talk_think,	// frame 10
	ai_stand,	  0.000, bum_talk_think,	// frame 11
	ai_stand,	  0.000, bum_talk_think,	// frame 12
	ai_stand,	  0.000, bum_talk_think,	// frame 13
	ai_stand,	  0.000, bum_talk_think,	// frame 14
	ai_stand,	  0.000, bum_talk_think,	// frame 15
	ai_stand,	  0.000, bum_talk_think,	// frame 16
	ai_stand,	  0.000, bum_talk_think,	// frame 17
	ai_stand,	  0.000, bum_talk_think,	// frame 18
	ai_stand,	  0.000, bum_talk_think,	// frame 19
	ai_stand,	  0.000, bum_talk_think,	// frame 20
	ai_stand,	  0.000, bum_talk_think,	// frame 21
	ai_stand,	  0.000, bum_talk_think,	// frame 22
	ai_stand,	  0.000, bum_talk_think,	// frame 23
	ai_stand,	  0.000, bum_talk_think,	// frame 24
	ai_stand,	  0.000, bum_talk_think,	// frame 25
	ai_stand,	  0.000, bum_talk_think,	// frame 26
	ai_stand,	  0.000, bum_talk_think,	// frame 27
	ai_stand,	  0.000, bum_talk_think,	// frame 28
	ai_stand,	  0.000, bum_talk_think,	// frame 29
	ai_stand,	  0.000, bum_talk_think,	// frame 30
	ai_stand,	  0.000, bum_talk_think,	// frame 31
	ai_stand,	  0.000, bum_talk_think,	// frame 32
};
mmove_t	bum_sit_move_leg_shuf = {FRAME_leg_shuf_01, FRAME_leg_shuf_33, bum_sit_frames_leg_shuf, bum_sit_end_sit};

mframe_t	bum_sit_frames_swat_fly[] = 
{
	ai_stand,	  0.000, bum_talk_think,	// frame 0
	ai_stand,	  0.000, bum_talk_think,	// frame 1
	ai_stand,	  0.000, bum_talk_think,	// frame 2
	ai_stand,	  0.000, bum_talk_think,	// frame 3
	ai_stand,	  0.000, bum_talk_think,	// frame 4
	ai_stand,	  0.000, bum_talk_think,	// frame 5
	ai_stand,	  0.000, bum_talk_think,	// frame 6
	ai_stand,	  0.000, bum_talk_think,	// frame 7
	ai_stand,	  0.000, bum_talk_think,	// frame 8
	ai_stand,	  0.000, bum_talk_think,	// frame 9
	ai_stand,	  0.000, bum_talk_think,	// frame 10
	ai_stand,	  0.000, bum_talk_think,	// frame 11
	ai_stand,	  0.000, bum_talk_think,	// frame 12
	ai_stand,	  0.000, bum_talk_think,	// frame 13
	ai_stand,	  0.000, bum_talk_think,	// frame 14
	ai_stand,	  0.000, bum_talk_think,	// frame 15
	ai_stand,	  0.000, bum_talk_think,	// frame 16
	ai_stand,	  0.000, bum_talk_think,	// frame 17
	ai_stand,	  0.000, bum_talk_think,	// frame 18
	ai_stand,	  0.000, bum_talk_think,	// frame 19
	ai_stand,	  0.000, bum_talk_think,	// frame 20
	ai_stand,	  0.000, bum_talk_think,	// frame 21
	ai_stand,	  0.000, bum_talk_think,	// frame 22
	ai_stand,	  0.000, bum_talk_think,	// frame 23
	ai_stand,	  0.000, bum_talk_think,	// frame 24
	ai_stand,	  0.000, bum_talk_think,	// frame 25
	ai_stand,	  0.000, bum_talk_think,	// frame 26
	ai_stand,	  0.000, bum_talk_think,	// frame 27
	ai_stand,	  0.000, bum_talk_think,	// frame 28
	ai_stand,	  0.000, bum_talk_think,	// frame 29
	ai_stand,	  0.000, bum_talk_think,	// frame 30
	ai_stand,	  0.000, bum_talk_think,	// frame 31
	ai_stand,	  0.000, bum_talk_think,	// frame 32
	ai_stand,	  0.000, bum_talk_think,	// frame 33
	ai_stand,	  0.000, bum_talk_think,	// frame 34
	ai_stand,	  0.000, bum_talk_think,	// frame 35
	ai_stand,	  0.000, bum_talk_think,	// frame 36
	ai_stand,	  0.000, bum_talk_think,	// frame 37
	ai_stand,	  0.000, bum_talk_think,	// frame 38
	ai_stand,	  0.000, bum_talk_think,	// frame 39
	ai_stand,	  0.000, bum_talk_think,	// frame 40
	ai_stand,	  0.000, bum_talk_think,	// frame 41
	ai_stand,	  0.000, bum_talk_think,	// frame 42
	ai_stand,	  0.000, bum_talk_think,	// frame 43
	ai_stand,	  0.000, bum_talk_think,	// frame 44
	ai_stand,	  0.000, bum_talk_think,	// frame 45
	ai_stand,	  0.000, bum_talk_think,	// frame 46
	ai_stand,	  0.000, bum_talk_think,	// frame 47
	ai_stand,	  0.000, bum_talk_think,	// frame 48
	ai_stand,	  0.000, bum_talk_think,	// frame 49
	ai_stand,	  0.000, bum_talk_think,	// frame 50
	ai_stand,	  0.000, bum_talk_think,	// frame 51
	ai_stand,	  0.000, bum_talk_think,	// frame 52
	ai_stand,	  0.000, bum_talk_think,	// frame 53
	ai_stand,	  0.000, bum_talk_think,	// frame 54
};
mmove_t	bum_sit_move_swat_fly = {FRAME_swat_fly_01, FRAME_swat_fly_55, bum_sit_frames_swat_fly, bum_sit_end_sit};

mframe_t	bum_sit_frames_swat_fly_onfire[] = 
{
	ai_stand_onfire,	  0.000, NULL,	// frame 0
	ai_stand_onfire,	  0.000, NULL,	// frame 1
	ai_stand_onfire,	  0.000, NULL,	// frame 2
	ai_stand_onfire,	  0.000, NULL,	// frame 3
	ai_stand_onfire,	  0.000, NULL,	// frame 4
	ai_stand_onfire,	  0.000, NULL,	// frame 5
	ai_stand_onfire,	  0.000, NULL,	// frame 6
	ai_stand_onfire,	  0.000, NULL,	// frame 7
	ai_stand_onfire,	  0.000, NULL,	// frame 8
	ai_stand_onfire,	  0.000, NULL,	// frame 9
	ai_stand_onfire,	  0.000, NULL,	// frame 10
	ai_stand_onfire,	  0.000, NULL,	// frame 11
	ai_stand_onfire,	  0.000, NULL,	// frame 12
	ai_stand_onfire,	  0.000, NULL,	// frame 13
	ai_stand_onfire,	  0.000, NULL,	// frame 14
	ai_stand_onfire,	  0.000, NULL,	// frame 15
	ai_stand_onfire,	  0.000, NULL,	// frame 16
	ai_stand_onfire,	  0.000, NULL,	// frame 17
	ai_stand_onfire,	  0.000, NULL,	// frame 18
	ai_stand_onfire,	  0.000, NULL,	// frame 19
	ai_stand_onfire,	  0.000, NULL,	// frame 20
	ai_stand_onfire,	  0.000, NULL,	// frame 21
	ai_stand_onfire,	  0.000, NULL,	// frame 22
	ai_stand_onfire,	  0.000, NULL,	// frame 23
	ai_stand_onfire,	  0.000, NULL,	// frame 24
	ai_stand_onfire,	  0.000, NULL,	// frame 25
	ai_stand_onfire,	  0.000, NULL,	// frame 26
	ai_stand_onfire,	  0.000, NULL,	// frame 27
	ai_stand_onfire,	  0.000, NULL,	// frame 28
	ai_stand_onfire,	  0.000, NULL,	// frame 29
	ai_stand_onfire,	  0.000, NULL,	// frame 30
	ai_stand_onfire,	  0.000, NULL,	// frame 31
	ai_stand_onfire,	  0.000, NULL,	// frame 32
	ai_stand_onfire,	  0.000, NULL,	// frame 33
	ai_stand_onfire,	  0.000, NULL,	// frame 34
	ai_stand_onfire,	  0.000, NULL,	// frame 35
	ai_stand_onfire,	  0.000, NULL,	// frame 36
	ai_stand_onfire,	  0.000, NULL,	// frame 37
	ai_stand_onfire,	  0.000, NULL,	// frame 38
	ai_stand_onfire,	  0.000, NULL,	// frame 39
	ai_stand_onfire,	  0.000, NULL,	// frame 40
	ai_stand_onfire,	  0.000, NULL,	// frame 41
	ai_stand_onfire,	  0.000, NULL,	// frame 42
	ai_stand_onfire,	  0.000, NULL,	// frame 43
	ai_stand_onfire,	  0.000, NULL,	// frame 44
	ai_stand_onfire,	  0.000, NULL,	// frame 45
	ai_stand_onfire,	  0.000, NULL,	// frame 46
	ai_stand_onfire,	  0.000, NULL,	// frame 47
	ai_stand_onfire,	  0.000, NULL,	// frame 48
	ai_stand_onfire,	  0.000, NULL,	// frame 49
	ai_stand_onfire,	  0.000, NULL,	// frame 50
	ai_stand_onfire,	  0.000, NULL,	// frame 51
	ai_stand_onfire,	  0.000, NULL,	// frame 52
	ai_stand_onfire,	  0.000, NULL,	// frame 53
	ai_stand_onfire,	  0.000, NULL,	// frame 54
};
mmove_t	bum_sit_move_swat_fly_onfire = {FRAME_swat_fly_01, FRAME_swat_fly_55, bum_sit_frames_swat_fly_onfire, NULL};

mframe_t	bum_sit_frames_cough_l[] = 
{
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 0
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 1
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 2
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 3
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 4
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 5
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 6
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 7
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 8
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 9
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 10
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 11
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 12
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 13
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 14
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 15
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 16
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 17
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 18
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 19
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 20
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 21
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 22
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 23
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 24
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 25
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 26
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 27
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 28
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 29
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 30
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 31
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 32
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 33
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 34
};
mmove_t	bum_sit_move_cough_l = {FRAME_cough_l_01, FRAME_cough_l_35, bum_sit_frames_cough_l, bum_sit_end_sit};

mframe_t	bum_sit_frames_pain_r[] = 
{
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 0
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 1
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 2
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 3
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 4
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 5
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 6
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 7
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 8
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 9
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 10
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 11
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 12
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 13
};
mmove_t	bum_sit_move_pain_r = {FRAME_pain_r_01, FRAME_pain_r_14, bum_sit_frames_pain_r, bum_sit_end_sit};

mframe_t	bum_sit_frames_pain_l[] = 
{
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 0
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 1
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 2
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 3
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 4
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 5
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 6
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 7
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 8
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 9
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 10
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 11
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 12
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 13
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 14
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 15
};
mmove_t	bum_sit_move_pain_l = {FRAME_pain_l_01, FRAME_pain_l_16, bum_sit_frames_pain_l, bum_sit_end_sit};

mframe_t	bum_sit_frames_death_r[] = 
{
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 0
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 1
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 2
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 3
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 4
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 5
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 6
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 7
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 8
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 9
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 10
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 11
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 12
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 13
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 14
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 15
};
mmove_t	bum_sit_move_death_r = {FRAME_death_r_01, FRAME_death_r_16, bum_sit_frames_death_r, AI_EndDeath};

mframe_t	bum_sit_frames_death_l[] = 
{
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 0
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 1
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 2
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 3
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 4
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 5
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 6
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 7
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 8
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 9
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 10
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 11
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 12
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 13
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 14
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 15
	/*ai_stand*/ NULL,	  0.000, NULL,	// frame 16
};
mmove_t	bum_sit_move_death_l = {FRAME_death_l_01, FRAME_death_l_17, bum_sit_frames_death_l, AI_EndDeath};


void ai_stand_onfire (edict_t *self, float dist)
{

	if (self->onfiretime <= 0)
	{	// stopping running around
		self->cast_info.currentmove = self->cast_info.move_stand;
		return;
	}

	if (!self->groundentity)
		return;

}

void bum_talk_think (edict_t *self)
{
	AI_TalkThink (self, true);
}

void bum_sit_end_sit (edict_t *self)
{
	int		rnd;

	if (self->cast_info.currentmove == &bum_sit_move_cough_l)
		rnd = rand() % 3;
	else
		rnd = rand() % 5;

	if (rnd < 1)
		self->cast_info.currentmove = &bum_sit_move_amb_sit;
	else if (rnd < 2)
		self->cast_info.currentmove = &bum_sit_move_leg_shuf;
	else if (rnd < 3)
		self->cast_info.currentmove = &bum_sit_move_swat_fly;
	else 
	{
		if (self->name_index == NAME_RUMMY || self->name_index == NAME_NICK)
			self->cast_info.currentmove = &bum_sit_move_amb_sit;
		else
			self->cast_info.currentmove = &bum_sit_move_cough_l;
	}
	
}

void bum_sit_pain (edict_t *self, edict_t *other, float kick, int damage, int mdx_part, int mdx_subobject)
{
	
	if (level.time < self->pain_debounce_time)
		return;

	self->pain_debounce_time = level.time + 3 + random();

	gi.sound ( self, CHAN_VOICE, gi.soundindex ("actors/bum/pain.wav"), 1, 3, 0);	

	if (rand()%100 > 50)
		self->cast_info.currentmove = &bum_sit_move_pain_r;
	else
		self->cast_info.currentmove = &bum_sit_move_pain_l;
	
}

void bum_sit_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
//	self->s.modelindex2 = 0;

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

	gi.sound ( self, CHAN_VOICE, gi.soundindex ("actors/bum/death.wav"), 1, 3, 0);	

	if (rand()%100 > 50)
		self->cast_info.currentmove = &bum_sit_move_death_r;
	else
		self->cast_info.currentmove = &bum_sit_move_death_l;
}

void bum_avoid (edict_t *self, edict_t *other, qboolean face)
{
	self->cast_info.currentmove = &bum_sit_move_swat_fly;
}

void bum_backoff (edict_t *self, edict_t *other )
{
	Voice_Random (self, other, rummy, 0);
}

void bum_catch_on_fire (edict_t *self, edict_t *other)
{
	self->enemy = NULL;		// stop attacking
	self->cast_info.currentmove = &bum_sit_move_swat_fly_onfire;
}


/*QUAKED cast_bum_sit (1 .5 0) (-24 -24 -24) (24 24 48) x TRIGGERED_START x x x 
cast_group 0	neutral
They should only be neutrals
model="models\actors\bum_sit\"
*/
void SP_cast_bum_sit (edict_t *self)
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
	VectorSet (self->mins, -24, -24, -24);
	VectorSet (self->maxs, 24, 24, 48);

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
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bum_sit/head.mdx");
	if (head_skin)
	{
		skin = gi.skinindex( self->s.model_parts[PART_HEAD].modelindex, head_skin );
	}
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].baseskin = self->s.model_parts[PART_HEAD].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/bum_sit/head.mdx", &self->s.model_parts[PART_HEAD] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/actors/bum_sit/legs.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_LEGS].modelindex, legs_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].baseskin = self->s.model_parts[PART_LEGS].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/bum_sit/legs.mdx", &self->s.model_parts[PART_LEGS] );

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/bum_sit/body.mdx");
	if (head_skin)
		skin = gi.skinindex( self->s.model_parts[PART_BODY].modelindex, body_skin );
	else
		skin = self->s.skinnum;
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].baseskin = self->s.model_parts[PART_BODY].skinnum[i] = skin;
	gi.GetObjectBounds( "models/actors/bum_sit/body.mdx", &self->s.model_parts[PART_BODY] );

	if (self->count & 1) // cigar
	{
		self->s.num_parts++;
		self->s.model_parts[PART_CIGAR].modelindex = gi.modelindex("models/actors/bum_sit/cigar.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_CIGAR].baseskin = self->s.model_parts[PART_CIGAR].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/runt/cigar.mdx", &self->s.model_parts[PART_CIGAR] );
	}

	if (self->count & 2) // fedora hat
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/bum_sit/fedora.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/bum_sit/fedora.mdx", &self->s.model_parts[PART_HAT] );
	}
	else if (self->count & 4) // stetson hat
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/bum_sit/stetson.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/bum_sit/stetson.mdx", &self->s.model_parts[PART_HAT] );
	}
	else if (self->count & 8) // cap (hat)
	{
		self->s.num_parts++;
		self->s.model_parts[PART_HAT].modelindex = gi.modelindex("models/actors/bum_sit/cap.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HAT].baseskin = self->s.model_parts[PART_HAT].skinnum[i] = 0;
		gi.GetObjectBounds( "models/actors/bum_sit/cap.mdx", &self->s.model_parts[PART_HAT] );
	}

	// remove NULL's
	if (self->art_skins)
		self->art_skins[3] = self->art_skins[7] = ' ';

	// ------------------------------------------------------------------------

	if (!(self->health))
	self->health = 100;

	self->gib_health = -200;
	self->mass = 200;

	self->gender = GENDER_MALE;

	self->pain = bum_sit_pain;
	self->die = bum_sit_die;

	self->cast_info.checkattack = NULL;

	self->cast_info.attack = NULL;
	self->cast_info.long_attack = NULL;
	self->cast_info.talk = bum_sit_end_sit;
	self->cast_info.avoid = bum_avoid;
	self->cast_info.backoff = bum_backoff;

	self->cast_info.catch_fire = bum_catch_on_fire;

	self->cast_info.max_attack_distance = 64;

	self->cast_info.move_stand = &bum_sit_move_amb_sit;
	self->cast_info.move_crstand = NULL;

	self->cast_info.move_run = NULL;
	self->cast_info.move_runwalk = NULL;
	self->cast_info.move_crwalk = NULL;

	self->cast_info.move_jump = NULL;

	self->cast_info.move_avoid_walk = NULL; 
	self->cast_info.move_avoid_run = NULL;
	self->cast_info.move_avoid_reverse_walk = NULL;
	self->cast_info.move_avoid_reverse_run = NULL;
	self->cast_info.move_avoid_crwalk = NULL;

	self->cast_info.move_crouch_down = NULL;
	self->cast_info.move_stand_up = NULL;
	self->cast_info.move_lside_step = NULL;
	self->cast_info.move_rside_step = NULL;
	self->cast_info.move_start_climb = NULL;
	self->cast_info.move_end_climb = NULL;
	self->cast_info.move_evade = NULL;
	self->cast_info.move_stand_evade = NULL; 

	gi.linkentity (self);

	self->cast_info.currentmove = self->cast_info.move_stand;


	if (!self->cast_info.scale)
		self->cast_info.scale = MODEL_SCALE;

	self->s.scale = self->cast_info.scale - 1.0;

	// talk by default
// 	self->cast_info.aiflags |= AI_NO_TALK;
	self->cast_info.aiflags |= (AI_TALK | AI_NOWALK_FACE);

	walking_cast_start (self);

}
