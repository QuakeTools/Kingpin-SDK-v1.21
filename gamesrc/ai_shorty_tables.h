// ai_shorty_tables.h

//==================================================================================================
// standard moves

mframe_t	shorty_frames_stand[] = 
{
	ai_stand,	  0.000, shorty_talk_think,	// frame 0
	ai_stand,	  0.000, shorty_talk_think,	// frame 1
	ai_stand,	  0.000, shorty_talk_think,	// frame 2
	ai_stand,	  0.000, shorty_talk_think,	// frame 3
	ai_stand,	  0.000, shorty_talk_think,	// frame 4
	ai_stand,	  0.000, shorty_talk_think,	// frame 5
	ai_stand,	  0.000, shorty_talk_think,	// frame 6
	ai_stand,	  0.000, shorty_talk_think,	// frame 7
	ai_stand,	  0.000, shorty_talk_think,	// frame 8
	ai_stand,	  0.000, shorty_talk_think,	// frame 9
	ai_stand,	  0.000, shorty_talk_think,	// frame 10
	ai_stand,	  0.000, shorty_talk_think,	// frame 11
	ai_stand,	  0.000, shorty_talk_think,	// frame 12
	ai_stand,	  0.000, shorty_talk_think,	// frame 13
	ai_stand,	  0.000, shorty_talk_think,	// frame 14
	ai_stand,	  0.000, shorty_talk_think,	// frame 15
	ai_stand,	  0.000, shorty_talk_think,	// frame 16
	ai_stand,	  0.000, shorty_talk_think,	// frame 17
	ai_stand,	  0.000, shorty_talk_think,	// frame 18
	ai_stand,	  0.000, shorty_talk_think,	// frame 19
	ai_stand,	  0.000, shorty_talk_think,	// frame 20
	ai_stand,	  0.000, shorty_talk_think,	// frame 21
	
};
mmove_t	shorty_move_stand = {FRAME_stand_01, FRAME_stand_22, shorty_frames_stand, shorty_end_stand};

mframe_t	shorty_frames_tg_shoot[] = 
{
	ai_charge,	  0.000, shorty_firegun,	// frame 0
	ai_charge,	  0.000, shorty_firegun,	// frame 1
	ai_charge,	  0.000, shorty_firegun,	// frame 2
	ai_charge,	  0.000, shorty_firegun,	// frame 3
	ai_charge,	  0.000, shorty_firegun,	// frame 4
	ai_charge,	  0.000, shorty_firegun,	// frame 5
	ai_charge,	  0.000, shorty_firegun,	// frame 6
};
mmove_t	shorty_move_tg_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_07, shorty_frames_tg_shoot, AI_EndAttack};

mframe_t	shorty_frames_hmg_shoot[] = 
{
	ai_charge,	  0.000, shorty_firehmg,	// frame 0
	ai_charge,	  0.000, shorty_firehmg,	// frame 1
	ai_charge,	  0.000, shorty_firehmg,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, shorty_firehmg_delay,	// frame 6
};
mmove_t	shorty_move_hmg_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_07, shorty_frames_hmg_shoot, AI_EndAttack};

mframe_t	shorty_frames_bazooka_shoot[] = 
{
	ai_charge,	  0.000, shorty_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4

	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, shorty_bazooka_delay,	// frame 6
};
mmove_t	shorty_move_bazooka_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_07, shorty_frames_bazooka_shoot, AI_EndAttack};

mframe_t	shorty_frames_grenade_shoot[] = 
{
	ai_charge,	  0.000, shorty_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
};
mmove_t	shorty_move_grenade_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_07, shorty_frames_grenade_shoot, AI_EndAttack};


mframe_t	shorty_frames_flamegun_shoot[] = 
{
	ai_charge,	  0.000, shorty_firegun,	// frame 0
	ai_charge,	  0.000, shorty_firegun,	// frame 1
	ai_charge,	  0.000, shorty_firegun,	// frame 2
	ai_charge,	  0.000, shorty_firegun,	// frame 3
	ai_charge,	  0.000, shorty_firegun,	// frame 4
	ai_charge,	  0.000, shorty_firegun,	// frame 3
	ai_charge,	  0.000, shorty_firegun,	// frame 4
};
mmove_t	shorty_move_flamegun_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_07, shorty_frames_flamegun_shoot, AI_EndAttack};

mframe_t	shorty_frames_shg_shoot[] = 
{
	ai_charge,	  0.000, shorty_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, shorty_shotgun_reload,	// frame 7
	ai_charge,	  0.000, NULL,	// frame 8
	ai_charge,	  0.000, NULL,	// frame 9
	ai_charge,	  0.000, NULL,	// frame 10
	ai_charge,	  0.000, NULL,	// frame 11
	ai_charge,	  0.000, NULL,	// frame 12
};
mmove_t	shorty_move_shg_shoot = {FRAME_shg_shoot_01, FRAME_shg_shoot_13, shorty_frames_shg_shoot, AI_EndAttack};

mframe_t	shorty_frames_tg_reload[] = 
{
	ai_charge,	  0.000, NULL,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, shorty_reload_snd,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, NULL,	// frame 7
	ai_charge,	  0.000, NULL,	// frame 8
	
};
mmove_t	shorty_move_tg_reload = {FRAME_tg_reload_01, FRAME_tg_reload_09, shorty_frames_tg_reload, AI_EndAttack};

mframe_t	shorty_frames_talk1[] = 
{
	ai_stand,	  0.000, shorty_talk_think,	// frame 0
	ai_stand,	  0.000, shorty_talk_think,	// frame 1
	ai_stand,	  0.000, shorty_talk_think,	// frame 2
	ai_stand,	  0.000, shorty_talk_think,	// frame 3
	ai_stand,	  0.000, shorty_talk_think,	// frame 4
	ai_stand,	  0.000, shorty_talk_think,	// frame 5
	ai_stand,	  0.000, shorty_talk_think,	// frame 6
	ai_stand,	  0.000, shorty_talk_think,	// frame 7
	ai_stand,	  0.000, shorty_talk_think,	// frame 8
	ai_stand,	  0.000, shorty_talk_think,	// frame 9
	ai_stand,	  0.000, shorty_talk_think,	// frame 10
	ai_stand,	  0.000, shorty_talk_think,	// frame 11
	ai_stand,	  0.000, shorty_talk_think,	// frame 12
	ai_stand,	  0.000, shorty_talk_think,	// frame 13
	ai_stand,	  0.000, shorty_talk_think,	// frame 14
	ai_stand,	  0.000, shorty_talk_think,	// frame 15
	ai_stand,	  0.000, shorty_talk_think,	// frame 16
	
};
mmove_t	shorty_move_talk1 = {FRAME_talk1_01, FRAME_talk1_17, shorty_frames_talk1, shorty_end_stand};

mframe_t	shorty_frames_talk2[] = 
{
	ai_stand,	  0.000, shorty_talk_think,	// frame 0
	ai_stand,	  0.000, shorty_talk_think,	// frame 1
	ai_stand,	  0.000, shorty_talk_think,	// frame 2
	ai_stand,	  0.000, shorty_talk_think,	// frame 3
	ai_stand,	  0.000, shorty_talk_think,	// frame 4
	ai_stand,	  0.000, shorty_talk_think,	// frame 5
	ai_stand,	  0.000, shorty_talk_think,	// frame 6
	ai_stand,	  0.000, shorty_talk_think,	// frame 7
	ai_stand,	  0.000, shorty_talk_think,	// frame 8
	ai_stand,	  0.000, shorty_talk_think,	// frame 9
	ai_stand,	  0.000, shorty_talk_think,	// frame 10
	ai_stand,	  0.000, shorty_talk_think,	// frame 11
	ai_stand,	  0.000, shorty_talk_think,	// frame 12
	ai_stand,	  0.000, shorty_talk_think,	// frame 13
	ai_stand,	  0.000, shorty_talk_think,	// frame 14
	ai_stand,	  0.000, shorty_talk_think,	// frame 15
	ai_stand,	  0.000, shorty_talk_think,	// frame 16
	
};
mmove_t	shorty_move_talk2 = {FRAME_talk2_01, FRAME_talk2_17, shorty_frames_talk2, shorty_end_stand};

mframe_t	shorty_frames_talk3[] = 
{
	ai_stand,	  0.000, shorty_talk_think,	// frame 0
	ai_stand,	  0.000, shorty_talk_think,	// frame 1
	ai_stand,	  0.000, shorty_talk_think,	// frame 2
	ai_stand,	  0.000, shorty_talk_think,	// frame 3
	ai_stand,	  0.000, shorty_talk_think,	// frame 4
	ai_stand,	  0.000, shorty_talk_think,	// frame 5
	ai_stand,	  0.000, shorty_talk_think,	// frame 6
	ai_stand,	  0.000, shorty_talk_think,	// frame 7
	ai_stand,	  0.000, shorty_talk_think,	// frame 8
	ai_stand,	  0.000, shorty_talk_think,	// frame 9
	ai_stand,	  0.000, shorty_talk_think,	// frame 10
	ai_stand,	  0.000, shorty_talk_think,	// frame 11
	ai_stand,	  0.000, shorty_talk_think,	// frame 12
	ai_stand,	  0.000, shorty_talk_think,	// frame 13
	ai_stand,	  0.000, shorty_talk_think,	// frame 14
	ai_stand,	  0.000, shorty_talk_think,	// frame 15
	ai_stand,	  0.000, shorty_talk_think,	// frame 16
	ai_stand,	  0.000, shorty_talk_think,	// frame 17
	ai_stand,	  0.000, shorty_talk_think,	// frame 18
	
};
mmove_t	shorty_move_talk3 = {FRAME_talk3_01, FRAME_talk3_19, shorty_frames_talk3, shorty_end_stand};

mframe_t	shorty_frames_talk4[] = 
{
	ai_stand,	  0.000, shorty_talk_think,	// frame 0
	ai_stand,	  0.000, shorty_talk_think,	// frame 1
	ai_stand,	  0.000, shorty_talk_think,	// frame 2
	ai_stand,	  0.000, shorty_talk_think,	// frame 3
	ai_stand,	  0.000, shorty_talk_think,	// frame 4
	ai_stand,	  0.000, shorty_talk_think,	// frame 5
	ai_stand,	  0.000, shorty_talk_think,	// frame 6
	ai_stand,	  0.000, shorty_talk_think,	// frame 7
	ai_stand,	  0.000, shorty_talk_think,	// frame 8
	ai_stand,	  0.000, shorty_talk_think,	// frame 9
	ai_stand,	  0.000, shorty_talk_think,	// frame 10
	ai_stand,	  0.000, shorty_talk_think,	// frame 11
	ai_stand,	  0.000, shorty_talk_think,	// frame 12
	ai_stand,	  0.000, shorty_talk_think,	// frame 13
	ai_stand,	  0.000, shorty_talk_think,	// frame 14
	ai_stand,	  0.000, shorty_talk_think,	// frame 15
	ai_stand,	  0.000, shorty_talk_think,	// frame 16
	ai_stand,	  0.000, shorty_talk_think,	// frame 17
	ai_stand,	  0.000, shorty_talk_think,	// frame 18
	ai_stand,	  0.000, shorty_talk_think,	// frame 19
	
};
mmove_t	shorty_move_talk4 = {FRAME_talk4_01, FRAME_talk4_20, shorty_frames_talk4, shorty_end_stand};

mframe_t	shorty_frames_talk5[] = 
{
	ai_stand,	  0.000, shorty_talk_think,	// frame 0
	ai_stand,	  0.000, shorty_talk_think,	// frame 1
	ai_stand,	  0.000, shorty_talk_think,	// frame 2
	ai_stand,	  0.000, shorty_talk_think,	// frame 3
	ai_stand,	  0.000, shorty_talk_think,	// frame 4
	ai_stand,	  0.000, shorty_talk_think,	// frame 5
	ai_stand,	  0.000, shorty_talk_think,	// frame 6
	ai_stand,	  0.000, shorty_talk_think,	// frame 7
	ai_stand,	  0.000, shorty_talk_think,	// frame 8
	ai_stand,	  0.000, shorty_talk_think,	// frame 9
	ai_stand,	  0.000, shorty_talk_think,	// frame 10
	ai_stand,	  0.000, shorty_talk_think,	// frame 11
	ai_stand,	  0.000, shorty_talk_think,	// frame 12
	ai_stand,	  0.000, shorty_talk_think,	// frame 13
	ai_stand,	  0.000, shorty_talk_think,	// frame 14
	ai_stand,	  0.000, shorty_talk_think,	// frame 15
	ai_stand,	  0.000, shorty_talk_think,	// frame 16
	ai_stand,	  0.000, shorty_talk_think,	// frame 17
	ai_stand,	  0.000, shorty_talk_think,	// frame 18
	
};
mmove_t	shorty_move_talk5 = {FRAME_talk5_01, FRAME_talk5_19, shorty_frames_talk5, shorty_end_stand};

mframe_t	shorty_frames_talk6[] = 
{
	ai_stand,	  0.000, shorty_talk_think,	// frame 0
	ai_stand,	  0.000, shorty_talk_think,	// frame 1
	ai_stand,	  0.000, shorty_talk_think,	// frame 2
	ai_stand,	  0.000, shorty_talk_think,	// frame 3
	ai_stand,	  0.000, shorty_talk_think,	// frame 4
	ai_stand,	  0.000, shorty_talk_think,	// frame 5
	ai_stand,	  0.000, shorty_talk_think,	// frame 6
	ai_stand,	  0.000, shorty_talk_think,	// frame 7
	ai_stand,	  0.000, shorty_talk_think,	// frame 8
	ai_stand,	  0.000, shorty_talk_think,	// frame 9
	ai_stand,	  0.000, shorty_talk_think,	// frame 10
	ai_stand,	  0.000, shorty_talk_think,	// frame 11
	ai_stand,	  0.000, shorty_talk_think,	// frame 12
	ai_stand,	  0.000, shorty_talk_think,	// frame 13
	ai_stand,	  0.000, shorty_talk_think,	// frame 14
	ai_stand,	  0.000, shorty_talk_think,	// frame 15
	ai_stand,	  0.000, shorty_talk_think,	// frame 16
	ai_stand,	  0.000, shorty_talk_think,	// frame 17
	ai_stand,	  0.000, shorty_talk_think,	// frame 18
	ai_stand,	  0.000, shorty_talk_think,	// frame 19
	ai_stand,	  0.000, shorty_talk_think,	// frame 20
	ai_stand,	  0.000, shorty_talk_think,	// frame 21
	ai_stand,	  0.000, shorty_talk_think,	// frame 22
	ai_stand,	  0.000, shorty_talk_think,	// frame 23
	ai_stand,	  0.000, shorty_talk_think,	// frame 24
	ai_stand,	  0.000, shorty_talk_think,	// frame 25
	ai_stand,	  0.000, shorty_talk_think,	// frame 26
	ai_stand,	  0.000, shorty_talk_think,	// frame 27
	ai_stand,	  0.000, shorty_talk_think,	// frame 28
	ai_stand,	  0.000, shorty_talk_think,	// frame 29
	ai_stand,	  0.000, shorty_talk_think,	// frame 30
	
};
mmove_t	shorty_move_talk6 = {FRAME_talk6_01, FRAME_talk6_31, shorty_frames_talk6, shorty_end_stand};

mframe_t	shorty_frames_talk7[] = 
{
	ai_stand,	  0.000, NULL,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
	ai_stand,	  0.000, NULL,	// frame 2
	ai_stand,	  0.000, NULL,	// frame 3
	ai_stand,	  0.000, NULL,	// frame 4
	ai_stand,	  0.000, NULL,	// frame 5
	ai_stand,	  0.000, NULL,	// frame 6
	ai_stand,	  0.000, NULL,	// frame 7
	ai_stand,	  0.000, NULL,	// frame 8
	ai_stand,	  0.000, NULL,	// frame 9
	ai_stand,	  0.000, NULL,	// frame 10
	ai_stand,	  0.000, NULL,	// frame 11
	ai_stand,	  0.000, NULL,	// frame 12
	ai_stand,	  0.000, NULL,	// frame 13
	ai_stand,	  0.000, NULL,	// frame 14
	ai_stand,	  0.000, NULL,	// frame 15
	ai_stand,	  0.000, NULL,	// frame 16
	
};
mmove_t	shorty_move_talk7 = {FRAME_talk7_01, FRAME_talk7_17, shorty_frames_talk7, shorty_end_stand};

/*
mframe_t	shorty_frames_head_wipe[] = 
{
	ai_stand,	  0.000, NULL,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
	ai_stand,	  0.000, NULL,	// frame 2
	ai_stand,	  0.000, NULL,	// frame 3
	ai_stand,	  0.000, NULL,	// frame 4
	ai_stand,	  0.000, NULL,	// frame 5
	ai_stand,	  0.000, NULL,	// frame 6
	ai_stand,	  0.000, NULL,	// frame 7
	ai_stand,	  0.000, NULL,	// frame 8
	ai_stand,	  0.000, NULL,	// frame 9
	ai_stand,	  0.000, NULL,	// frame 10
	ai_stand,	  0.000, NULL,	// frame 11
	ai_stand,	  0.000, NULL,	// frame 12
	ai_stand,	  0.000, NULL,	// frame 13
	ai_stand,	  0.000, NULL,	// frame 14
	ai_stand,	  0.000, NULL,	// frame 15
	ai_stand,	  0.000, NULL,	// frame 16
	ai_stand,	  0.000, NULL,	// frame 17
	ai_stand,	  0.000, NULL,	// frame 18
	ai_stand,	  0.000, NULL,	// frame 19
	ai_stand,	  0.000, NULL,	// frame 20
	ai_stand,	  0.000, NULL,	// frame 21
	ai_stand,	  0.000, NULL,	// frame 22
	ai_stand,	  0.000, NULL,	// frame 23
	ai_stand,	  0.000, NULL,	// frame 24
	ai_stand,	  0.000, NULL,	// frame 25
	ai_stand,	  0.000, NULL,	// frame 26
	ai_stand,	  0.000, NULL,	// frame 27
};
mmove_t	shorty_move_head_wipe = {FRAME_head_wipe_01, FRAME_head_wipe_28, shorty_frames_head_wipe, shorty_end_stand};
*/

mframe_t	shorty_frames_pain_Rarm[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	ai_move,	  0.000, NULL,	// frame 8
};
mmove_t	shorty_move_pain_Rarm = {FRAME_pain_Rarm_01, FRAME_pain_Rarm_09, shorty_frames_pain_Rarm, AI_EndAttack};

mframe_t	shorty_frames_pain_Larm[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
};
mmove_t	shorty_move_pain_Larm = {FRAME_pain_Larm_01, FRAME_pain_Larm_08, shorty_frames_pain_Larm, AI_EndAttack};

mframe_t	shorty_frames_pain_chest[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	ai_move,	  0.000, NULL,	// frame 8
	ai_move,	  0.000, NULL,	// frame 9
};
mmove_t	shorty_move_pain_chest = {FRAME_pain_chest_01, FRAME_pain_chest_10, shorty_frames_pain_chest, AI_EndAttack};

mframe_t	shorty_frames_pain_head[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
};
mmove_t	shorty_move_pain_head = {FRAME_pain_head_01, FRAME_pain_head_08, shorty_frames_pain_head, AI_EndAttack};

mframe_t	shorty_frames_pain_Rleg[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	
};
mmove_t	shorty_move_pain_Rleg = {FRAME_pain_Rleg_01, FRAME_pain_Rleg_08, shorty_frames_pain_Rleg, AI_EndAttack};

mframe_t	shorty_frames_pain_Lleg[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	ai_move,	  0.000, NULL,	// frame 8
	ai_move,	  0.000, NULL,	// frame 9
};
mmove_t	shorty_move_pain_Lleg = {FRAME_pain_Lleg_01, FRAME_pain_Lleg_10, shorty_frames_pain_Lleg, AI_EndAttack};

mframe_t	shorty_frames_pain_crch[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	ai_move,	  0.000, NULL,	// frame 8
	
};
mmove_t	shorty_move_pain_crch = {FRAME_pain_crch_01, FRAME_pain_crch_09, shorty_frames_pain_crch, AI_EndAttack};

mframe_t	shorty_frames_pain_butt[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	
};
mmove_t	shorty_move_pain_butt = {FRAME_pain_butt_01, FRAME_pain_butt_08, shorty_frames_pain_butt, AI_EndAttack};

mframe_t	shorty_frames_jump[] = 
{
//	ai_stand,	  0.000, NULL,	// frame 0
//	ai_stand,	  0.000, NULL,	// frame 1
//	ai_stand,	  0.000, NULL,	// frame 2
//	ai_stand,	  0.000, NULL,	// frame 3
//	ai_stand,	  0.000, NULL,	// frame 4

	NULL,	  0.000, NULL,	// frame 5
	NULL,	  0.000, NULL,	// frame 6
	NULL,	  0.000, AI_CheckStillInair,	// frame 7
	NULL,	  0.000, NULL,	// frame 8

//	ai_stand,	  0.000, NULL,	// frame 9
//	ai_stand,	  0.000, NULL,	// frame 10
//	ai_stand,	  0.000, NULL,	// frame 11
};
mmove_t	shorty_move_jump = {FRAME_jump_06, FRAME_jump_09, shorty_frames_jump, AI_EndJump};

mframe_t	shorty_frames_death1[] = 
{
	ai_move,	  5.538, NULL,	// frame 0
	ai_move,	-11.159, NULL,	// frame 1
	ai_move,	 -2.126, NULL,	// frame 2
	ai_move,	  2.642, NULL,	// frame 3
	ai_move,	  7.539, NULL,	// frame 4
	ai_move,	  8.717, NULL,	// frame 5
	ai_move,	 -0.335, NULL,	// frame 6
	ai_move,	  1.315, NULL,	// frame 7
	ai_move,	 -9.381, NULL,	// frame 8
	ai_move,	  3.059, NULL,	// frame 9
	ai_move,	  4.369, NULL,	// frame 10
	ai_move,	 17.348, NULL,	// frame 11
	ai_move,	 13.971, NULL,	// frame 12
	ai_move,	  9.086, NULL,	// frame 13
	ai_move,	  1.221, NULL,	// frame 14
	ai_move,	 -1.728, NULL,	// frame 15
	ai_move,	 -0.284, NULL,	// frame 16
	ai_move,	 -0.076, NULL,	// frame 17
	ai_move,	 -0.188, NULL,	// frame 18
	ai_move,	 -0.075, NULL,	// frame 19
	ai_move,	  0.052, NULL,	// frame 20
	ai_move,	  0.015, NULL,	// frame 21

};
mmove_t	shorty_move_death1 = {FRAME_death1_01, FRAME_death1_22, shorty_frames_death1, AI_EndDeath};

mframe_t	shorty_frames_death2[] = 
{
	ai_move,	  3.400, NULL,	// frame 0
	ai_move,	 -5.462, NULL,	// frame 1
	ai_move,	 -8.080, NULL,	// frame 2
	ai_move,	  6.676, NULL,	// frame 3
	ai_move,	  8.716, NULL,	// frame 4
	ai_move,	  6.521, NULL,	// frame 5
	ai_move,	  6.836, NULL,	// frame 6
	ai_move,	  2.100, NULL,	// frame 7
	ai_move,	 10.029, NULL,	// frame 8
	ai_move,	 19.021, NULL,	// frame 9
	ai_move,	  4.883, NULL,	// frame 10
	ai_move,	  4.209, NULL,	// frame 11
	ai_move,	 -8.390, NULL,	// frame 12
	ai_move,	 -1.513, NULL,	// frame 13
	ai_move,	  1.113, NULL,	// frame 14
	ai_move,	  0.017, NULL,	// frame 15
	ai_move,	  0.020, NULL,	// frame 16
	ai_move,	 -0.036, NULL,	// frame 17
	ai_move,	 -0.012, NULL,	// frame 18
};
mmove_t	shorty_move_death2 = {FRAME_death2_01, FRAME_death2_19, shorty_frames_death2, AI_EndDeath};

mframe_t	shorty_frames_death3[] = 
{
	ai_move,	    4.775, NULL,	// frame 0
	ai_move,	  -19.169, NULL,	// frame 1
	ai_move,	   -3.797, NULL,	// frame 2
	ai_move,	    1.160, NULL,	// frame 3
	ai_move,	   15.269, NULL,	// frame 4
	ai_move,	   23.089, NULL,	// frame 5
	ai_move,	   19.805, NULL,	// frame 6
	ai_move,	    4.425, NULL,	// frame 7
	ai_move,	    5.173, NULL,	// frame 8
	ai_move,	   -0.740, NULL,	// frame 9
	ai_move,	    0.000, NULL,	// frame 10
	ai_move,	    0.203, NULL,	// frame 11
	ai_move,	    0.266, NULL,	// frame 12
	ai_move,	    0.086, NULL,	// frame 13
	ai_move,	   -0.015, NULL,	// frame 14
	ai_move,	    0.027, NULL,	// frame 15
	ai_move,	    0.024, NULL,	// frame 16
	
};
mmove_t	shorty_move_death3 = {FRAME_death3_01, FRAME_death3_17, shorty_frames_death3, AI_EndDeath};

mframe_t	shorty_frames_death4[] = 
{
	ai_move,	  3.890, NULL,	// frame 0
	ai_move,	  6.990, NULL,	// frame 1
	ai_move,	 -8.191, NULL,	// frame 2
	ai_move,	 14.215, NULL,	// frame 3
	ai_move,	 17.146, NULL,	// frame 4
	ai_move,	  9.714, NULL,	// frame 5
	ai_move,	  1.483, NULL,	// frame 6
	ai_move,	  6.178, NULL,	// frame 7
	ai_move,	  1.228, NULL,	// frame 8
	ai_move,	 -0.240, NULL,	// frame 9
	ai_move,	 -0.790, NULL,	// frame 10
	ai_move,	 -0.521, NULL,	// frame 11
	ai_move,	  0.484, NULL,	// frame 12
	ai_move,	 -0.410, NULL,	// frame 13
	ai_move,	  0.459, NULL,	// frame 14
	ai_move,	 -0.009, NULL,	// frame 15

};
mmove_t	shorty_move_death4 = {FRAME_death4_01, FRAME_death4_16, shorty_frames_death4, AI_EndDeath};

mframe_t	shorty_frames_death5[] = 
{
	ai_move,	 6.268, NULL,	// frame 0
	ai_move,	12.423, NULL,	// frame 1
	ai_move,	 5.181, NULL,	// frame 2
	ai_move,	10.112, NULL,	// frame 3
	ai_move,	 5.047, NULL,	// frame 4
	ai_move,	16.568, NULL,	// frame 5
	ai_move,	 7.034, NULL,	// frame 6
	ai_move,	 2.520, NULL,	// frame 7
	ai_move,	-2.414, NULL,	// frame 8
	ai_move,	-0.397, NULL,	// frame 9
	ai_move,	-0.583, NULL,	// frame 10
	ai_move,	-0.332, NULL,	// frame 11
	ai_move,	-0.128, NULL,	// frame 12
	
};
mmove_t	shorty_move_death5 = {FRAME_death5_01, FRAME_death5_13, shorty_frames_death5, AI_EndDeath};

mframe_t	shorty_frames_death6[] = 
{
	ai_move,	 -6.192, NULL,	// frame 0
	ai_move,	 -5.745, NULL,	// frame 1
	ai_move,	  0.539, NULL,	// frame 2
	ai_move,	-10.390, NULL,	// frame 3
	ai_move,	 -0.039, NULL,	// frame 4
	ai_move,	  0.036, NULL,	// frame 5
	ai_move,	 -4.263, NULL,	// frame 6
	ai_move,	 -0.696, NULL,	// frame 7
	ai_move,	  1.591, NULL,	// frame 8
	ai_move,	 -0.695, NULL,	// frame 9
	ai_move,	 -0.362, NULL,	// frame 10
	ai_move,	  0.276, NULL,	// frame 11
	
};
mmove_t	shorty_move_death6 = {FRAME_death6_01, FRAME_death6_12, shorty_frames_death6, AI_EndDeath};

mframe_t	shorty_frames_death7[] = 
{
	ai_move,	 -3.027, NULL,	// frame 0
	ai_move,	 -9.123, NULL,	// frame 1
	ai_move,	 -2.839, NULL,	// frame 2
	ai_move,	-15.739, NULL,	// frame 3
	ai_move,	 -2.845, NULL,	// frame 4
	ai_move,	 -5.223, NULL,	// frame 5
	ai_move,	 -1.970, NULL,	// frame 6
	ai_move,	 -1.052, NULL,	// frame 7
	ai_move,	  2.239, NULL,	// frame 8
	ai_move,	  6.121, NULL,	// frame 9
	ai_move,	 -0.037, NULL,	// frame 10
	ai_move,	 -0.012, NULL,	// frame 11
	ai_move,	  0.009, NULL,	// frame 12
	
};
mmove_t	shorty_move_death7 = {FRAME_death7_01, FRAME_death7_13, shorty_frames_death7, AI_EndDeath};

mframe_t	shorty_frames_death8[] = 
{
	ai_move,	  2.131, NULL,	// frame 0
	ai_move,	 -2.581, NULL,	// frame 1
	ai_move,	-10.245, NULL,	// frame 2
	ai_move,	 -4.453, NULL,	// frame 3
	ai_move,	 -9.977, NULL,	// frame 4
	ai_move,	 -2.910, NULL,	// frame 5
	ai_move,	 -6.631, NULL,	// frame 6
	ai_move,	 -2.800, NULL,	// frame 7
	ai_move,	  1.224, NULL,	// frame 8
	ai_move,	 -0.100, NULL,	// frame 9
	ai_move,	  0.105, NULL,	// frame 10
	
};
mmove_t	shorty_move_death8 = {FRAME_death8_01, FRAME_death8_11, shorty_frames_death8, AI_EndDeath};


mframe_t	shorty_frames_crh_shuf[] = 
{
	ai_run,	 6.362, NULL,	// frame 0
	ai_run,	 5.393, NULL,	// frame 1
	ai_run,	 5.862, NULL,	// frame 2
	ai_run,	 8.591, NULL,	// frame 3
	ai_run,	 5.853, NULL,	// frame 4
	ai_run,	 5.498, NULL,	// frame 5
	ai_run,	 5.083, NULL,	// frame 6
	ai_run,	 5.991, NULL,	// frame 7
	ai_run,	 6.440, NULL,	// frame 8

};
mmove_t	shorty_move_crh_shuf = {FRAME_crouch_walk_01, FRAME_crouch_walk_09, shorty_frames_crh_shuf, NULL};


mframe_t	shorty_frames_crouch_walk[] = 
{
	ai_run,	 6.362, NULL,	// frame 0
	ai_run,	 5.393, NULL,	// frame 1
	ai_run,	 5.862, NULL,	// frame 2
	ai_run,	 8.591, NULL,	// frame 3
	ai_run,	 5.853, NULL,	// frame 4
	ai_run,	 5.498, NULL,	// frame 5
	ai_run,	 5.083, NULL,	// frame 6
	ai_run,	 5.991, NULL,	// frame 7
	ai_run,	 6.440, NULL,	// frame 8
	
};
mmove_t	shorty_move_crouch_walk = {FRAME_crouch_walk_01, FRAME_crouch_walk_09, shorty_frames_crouch_walk, NULL};

mframe_t	shorty_frames_crouch_painC[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
};
mmove_t	shorty_move_crouch_painC = {FRAME_crouch_painC_01, FRAME_crouch_painC_07, shorty_frames_crouch_painC, AI_EndAttack};

mframe_t	shorty_frames_crouch_painL[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
};
mmove_t	shorty_move_crouch_painL = {FRAME_crouch_painL_01, FRAME_crouch_painL_08, shorty_frames_crouch_painL, AI_EndAttack};

mframe_t	shorty_frames_crouch_painR[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
};
mmove_t	shorty_move_crouch_painR = {FRAME_crouch_painR_01, FRAME_crouch_painR_07, shorty_frames_crouch_painR, AI_EndAttack};

mframe_t	shorty_frames_crouch_shoot[] = 
{
	ai_turn,	  0.000, shorty_firegun,	// frame 0
	ai_turn,	  0.000, shorty_firegun_cr,	// frame 1
	ai_turn,	  0.000, shorty_firegun_cr,	// frame 2
	ai_turn,	  0.000, shorty_firegun_cr,	// frame 3
	ai_turn,	  0.000, shorty_firegun_cr,	// frame 4
	ai_turn,	  0.000, shorty_firegun_cr,	// frame 5
};
mmove_t	shorty_move_crouch_shoot = {FRAME_crouch_shoot_01, FRAME_crouch_shoot_06, shorty_frames_crouch_shoot, AI_EndAttack};

mframe_t	shorty_frames_crch_shg_sht[] = 
{
	ai_turn,	  0.000, shorty_firegun,	// frame 0
	ai_turn,	  0.000, NULL,	// frame 1
	ai_turn,	  0.000, NULL,	// frame 2
	ai_turn,	  0.000, NULL,	// frame 3
	ai_turn,	  0.000, NULL,	// frame 4
	ai_turn,	  0.000, NULL,	// frame 5
	ai_turn,	  0.000, NULL,	// frame 6
	ai_turn,	  0.000, shorty_shotgun_reload,	// frame 7
	ai_turn,	  0.000, NULL,	// frame 8
	ai_turn,	  0.000, NULL,	// frame 9
	ai_turn,	  0.000, NULL,	// frame 10
	ai_turn,	  0.000, NULL,	// frame 11
	ai_turn,	  0.000, NULL,	// frame 12
};
mmove_t	shorty_move_crch_shg_sht = {FRAME_crch_shg_sht_01, FRAME_crch_shg_sht_13, shorty_frames_crch_shg_sht, AI_EndAttack};

mframe_t	shorty_frames_crouch_stand_down[] = 
{
	NULL,	  0.000, NULL,	// frame 0
	NULL,	  0.000, NULL,	// frame 1
	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
//	NULL,	  0.000, NULL,	// frame 4
};
mmove_t	shorty_move_crouch_stand_down = {FRAME_stand_crouch_01, FRAME_stand_crouch_04, shorty_frames_crouch_stand_down, AI_End_CrouchStand_Down};

mframe_t	shorty_frames_crouch_stand_up[] = 
{
//	NULL,	  0.000, NULL,	// frame 0
	NULL,	  0.000, NULL,	// frame 1
	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
	NULL,	  0.000, NULL,	// frame 4
};
mmove_t	shorty_move_crouch_stand_up = {FRAME_stand_crouch_04, FRAME_stand_crouch_01, shorty_frames_crouch_stand_up, AI_End_CrouchStand_Up};

mframe_t	shorty_frames_crch_astand[] = 
{
	ai_stand,	  0.000, NULL,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
	ai_stand,	  0.000, NULL,	// frame 2
	ai_stand,	  0.000, NULL,	// frame 3
	ai_stand,	  0.000, NULL,	// frame 4
	ai_stand,	  0.000, NULL,	// frame 5
	ai_stand,	  0.000, NULL,	// frame 6
	ai_stand,	  0.000, NULL,	// frame 7
	ai_stand,	  0.000, NULL,	// frame 8
	ai_stand,	  0.000, NULL,	// frame 9
	ai_stand,	  0.000, NULL,	// frame 10
	ai_stand,	  0.000, NULL,	// frame 11
	ai_stand,	  0.000, NULL,	// frame 12
	ai_stand,	  0.000, NULL,	// frame 13
	ai_stand,	  0.000, NULL,	// frame 14
	ai_stand,	  0.000, NULL,	// frame 15
	
};
mmove_t	shorty_move_crch_astand = {FRAME_crch_astand_01, FRAME_crch_astand_16, shorty_frames_crch_astand, NULL};

mframe_t	shorty_frames_crouch_death1[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	ai_move,	  0.000, NULL,	// frame 8
	ai_move,	  0.000, NULL,	// frame 9
	ai_move,	  0.000, NULL,	// frame 10
	ai_move,	  0.000, NULL,	// frame 11
	ai_move,	  0.000, NULL,	// frame 12
	ai_move,	  0.000, NULL,	// frame 13
	ai_move,	  0.000, NULL,	// frame 14
	ai_move,	  0.000, NULL,	// frame 15
	ai_move,	  0.000, NULL,	// frame 16
	ai_move,	  0.000, NULL,	// frame 17
	ai_move,	  0.000, NULL,	// frame 18

};
mmove_t	shorty_move_crouch_death1 = {FRAME_crch_death1_01, FRAME_crch_death1_19, shorty_frames_crouch_death1, AI_EndDeath};

mframe_t	shorty_frames_crouch_death2[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
	ai_move,	  0.000, NULL,	// frame 7
	ai_move,	  0.000, NULL,	// frame 8
	ai_move,	  0.000, NULL,	// frame 9
	ai_move,	  0.000, NULL,	// frame 10
	ai_move,	  0.000, NULL,	// frame 11
	ai_move,	  0.000, NULL,	// frame 12
	ai_move,	  0.000, NULL,	// frame 13
	ai_move,	  0.000, NULL,	// frame 14
	
};
mmove_t	shorty_move_crouch_death2 = {FRAME_crch_death2_01, FRAME_crch_death2_15, shorty_frames_crouch_death2, AI_EndDeath};

/*
mframe_t	shorty_frames_st_clmb[] = 
{
	ai_stand,	  0.000, NULL,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
};
mmove_t	shorty_move_st_clmb = {FRAME_st_clmb_01, FRAME_st_clmb_02, shorty_frames_st_clmb, NULL};
*/

mframe_t	shorty_frames_clmb_loop[] = 
{
	NULL,	  0.000, NULL,	// frame 0
	NULL,	  0.000, NULL,	// frame 1
	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
	NULL,	  0.000, NULL,	// frame 4
	NULL,	  0.000, NULL,	// frame 5
	NULL,	  0.000, NULL,	// frame 6
	NULL,	  0.000, NULL,	// frame 7
	NULL,	  0.000, NULL,	// frame 8
};
mmove_t	shorty_move_clmb_loop = {FRAME_clmb_loop_01, FRAME_clmb_loop_09, shorty_frames_clmb_loop, AI_CheckStillClimbingLadder};

mframe_t	shorty_frames_clmb_over[] = 
{
	NULL,	  0.000, NULL,	// frame 0
	NULL,	  0.000, NULL,	// frame 1
	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
	NULL,	  0.000, NULL,	// frame 4
	NULL,	  0.000, NULL,	// frame 5
	NULL,	  0.000, NULL,	// frame 6
	NULL,	  0.000, NULL,	// frame 7
	NULL,	  0.000, NULL,	// frame 8
	NULL,	  0.000, NULL,	// frame 9
//	NULL,	  0.000, NULL,	// frame 10
//	NULL,	  0.000, NULL,	// frame 11
//	NULL,	  0.000, NULL,	// frame 12
//	NULL,	  0.000, NULL,	// frame 13
//	NULL,	  0.000, NULL,	// frame 14
};
mmove_t	shorty_move_clmb_over = {FRAME_clmb_over_01, FRAME_clmb_over_10, shorty_frames_clmb_over, AI_EndJump};
/*
mframe_t	shorty_frames_lside_step[] = 
{
	ai_sidestep,	  0.215, NULL,	// frame 0
	ai_sidestep,	  0.721, NULL,	// frame 1
	ai_sidestep,	  2.871, NULL,	// frame 2
	ai_sidestep,	  4.372, NULL,	// frame 3
	ai_sidestep,	  2.453, NULL,	// frame 4
	ai_sidestep,	  2.358, NULL,	// frame 5
	ai_sidestep,	 -0.671, NULL,	// frame 6
};
mmove_t	shorty_move_lside_step = {FRAME_lside_step_01, FRAME_lside_step_07, shorty_frames_lside_step, NULL};

mframe_t	shorty_frames_rside_step[] = 
{
	ai_sidestep,	   0.676, NULL,	// frame 0
	ai_sidestep,	  -0.261, NULL,	// frame 1
	ai_sidestep,	  -1.790, NULL,	// frame 2
	ai_sidestep,	  -1.300, NULL,	// frame 3
	ai_sidestep,	  -2.096, NULL,	// frame 4
	ai_sidestep,	  -3.586, NULL,	// frame 5
	ai_sidestep,	  -3.024, NULL,	// frame 6
};
mmove_t	shorty_move_rside_step = {FRAME_rside_step_01, FRAME_rside_step_07, shorty_frames_rside_step, NULL};
*/

mframe_t	shorty_frames_lside_step[] = 
{
	ai_sidestep,	   0.193, NULL,	// frame 0
	ai_sidestep,	   0.145, NULL,	// frame 1
	ai_sidestep,	  -0.441, NULL,	// frame 2
	ai_sidestep,	  -3.371, NULL,	// frame 3
	ai_sidestep,	 -11.950, NULL,	// frame 4
	ai_sidestep,	 -11.676, NULL,	// frame 5
	ai_sidestep,	  -8.798, NULL,	// frame 6
	ai_sidestep,	  -3.155, NULL,	// frame 7
	ai_sidestep,	  -3.032, NULL,	// frame 8
};
mmove_t	shorty_move_lside_step = {FRAME_lside_step_01, FRAME_lside_step_09, shorty_frames_lside_step, AI_EndAttack};

mframe_t	shorty_frames_rside_step[] = 
{
	ai_sidestep,	 0.267, NULL,	// frame 0
	ai_sidestep,	 5.044, NULL,	// frame 1
	ai_sidestep,	12.985, NULL,	// frame 2
	ai_sidestep,	 5.358, NULL,	// frame 3
	ai_sidestep,	 4.552, NULL,	// frame 4
	ai_sidestep,	10.731, NULL,	// frame 5
	ai_sidestep,	 3.606, NULL,	// frame 6
	ai_sidestep,	 0.040, NULL,	// frame 5
	ai_sidestep,	 1.343, NULL,	// frame 6
};
mmove_t	shorty_move_rside_step = {FRAME_rside_step_01, FRAME_rside_step_09, shorty_frames_rside_step, AI_EndAttack};


mframe_t	shorty_frames_walk_nw[] = 
{
	ai_run,	   1.235, NULL,	// frame 0
	ai_run,	   7.009, NULL,	// frame 1
	ai_run,	   7.589, AI_EndRun,	// frame 2
	ai_run,	  13.206, NULL,	// frame 3
	ai_run,	   3.028, NULL,	// frame 4
	ai_run,	   2.102, NULL,	// frame 5
	ai_run,	  24.908, AI_EndRun,	// frame 6
	ai_run,	  11.297, NULL,	// frame 7
	ai_run,	  11.088, NULL,	// frame 8
	ai_run,	   7.711, NULL,	// frame 9
};
mmove_t	shorty_move_walk_nw = {FRAME_walk_nw_01, FRAME_walk_nw_10, shorty_frames_walk_nw, AI_EndRun};

mframe_t	shorty_frames_walk_tg_sht[] = 
{
	ai_turn,	   7.963, shorty_firegun,	// frame 0
	ai_turn,	   3.735, shorty_firegun,	// frame 1
	ai_turn,	   9.088, shorty_firegun,	// frame 2
	ai_turn,	  11.945, shorty_firegun,	// frame 3
	ai_turn,	   6.984, shorty_firegun,	// frame 4
	ai_turn,	   3.927, shorty_firegun,	// frame 5
	ai_turn,	  16.424, shorty_firegun,	// frame 6
	ai_turn,	   4.464, shorty_firegun,	// frame 7
	ai_turn,	  15.347, shorty_firegun,	// frame 8
	ai_turn,	   8.590, shorty_firegun,	// frame 9
};
mmove_t	shorty_move_walk_tg_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, shorty_frames_walk_tg_sht, AI_EndAttack};

mframe_t	shorty_frames_walk_hmg_sht[] = 
{
	ai_turn,	   7.963, shorty_firehmg,	// frame 0
	ai_turn,	   3.735, shorty_firehmg,	// frame 1
	ai_turn,	   9.088, shorty_firehmg,	// frame 2
	ai_turn,	  11.945, NULL,	// frame 3
	ai_turn,	   6.984, NULL,	// frame 4
	ai_turn,	   3.927, NULL,	// frame 5
	ai_turn,	  16.424, NULL,	// frame 6
	ai_turn,	   4.464, NULL,	// frame 7
	ai_turn,	  15.347, NULL,	// frame 8
	ai_turn,	   8.590, shorty_firehmg_delay,	// frame 9
};
mmove_t	shorty_move_walk_hmg_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, shorty_frames_walk_hmg_sht, AI_EndAttack};

mframe_t	shorty_frames_walk_bazooka_sht[] = 
{
	ai_turn,	   7.963, shorty_firegun,	// frame 0
	ai_turn,	   3.735, NULL,	// frame 1
	ai_turn,	   9.088, NULL,	// frame 2
	ai_turn,	  11.945, NULL,	// frame 3
	ai_turn,	   6.984, NULL,	// frame 4
	ai_turn,	   3.927, NULL,	// frame 5
	ai_turn,	  16.424, NULL,	// frame 6
	ai_turn,	   4.464, NULL,	// frame 7
	ai_turn,	  15.347, NULL,	// frame 8
	ai_turn,	   8.590, shorty_bazooka_delay,	// frame 9
};
mmove_t	shorty_move_walk_bazooka_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, shorty_frames_walk_bazooka_sht, AI_EndAttack};

mframe_t	shorty_frames_walk_grenade_sht[] = 
{
	ai_turn,	   7.963, shorty_firegun,	// frame 0
	ai_turn,	   3.735, NULL,	// frame 1
	ai_turn,	   9.088, NULL,	// frame 2
	ai_turn,	  11.945, NULL,	// frame 3
	ai_turn,	   6.984, NULL,	// frame 4
	ai_turn,	   3.927, NULL,	// frame 5
	ai_turn,	  16.424, NULL,	// frame 6
	ai_turn,	   4.464, NULL,	// frame 7
	ai_turn,	  15.347, NULL,	// frame 8
	ai_turn,	   8.590, NULL,	// frame 9
};
mmove_t	shorty_move_walk_grenade_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, shorty_frames_walk_grenade_sht, AI_EndAttack};

mframe_t	shorty_frames_walk_flamegun_sht[] = 
{
	ai_turn,	   7.963, shorty_firegun,	// frame 0
	ai_turn,	   3.735, shorty_firegun,	// frame 1
	ai_turn,	   9.088, shorty_firegun,	// frame 2
	ai_turn,	  11.945, shorty_firegun,	// frame 3
	ai_turn,	   6.984, shorty_firegun,	// frame 4
	ai_turn,	   3.927, shorty_firegun,	// frame 5
	ai_turn,	  16.424, shorty_firegun,	// frame 6
	ai_turn,	   4.464, shorty_firegun,	// frame 7
	ai_turn,	  15.347, shorty_firegun,	// frame 8
	ai_turn,	   8.590, shorty_firegun,	// frame 9
};
mmove_t	shorty_move_walk_flamegun_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, shorty_frames_walk_flamegun_sht, AI_EndAttack};


mframe_t	shorty_frames_walk_shg_sht[] = 
{
	ai_turn,	 -2.719, shorty_firegun,	// frame 0
	ai_turn,	 16.444, NULL,	// frame 1
	ai_turn,	  6.570, NULL,	// frame 2
	ai_turn,	 11.042, NULL,	// frame 3
	ai_turn,	  3.100, NULL,	// frame 4
	ai_turn,	  5.307, shorty_shotgun_reload,	// frame 5
	ai_turn,	 16.312, NULL,	// frame 6
	ai_turn,	  9.812, NULL,	// frame 7
	ai_turn,	 13.933, NULL,	// frame 8
	ai_turn,	  8.408, NULL,	// frame 9
};
mmove_t	shorty_move_walk_shg_sht = {FRAME_walk_shg_sht_01, FRAME_walk_shg_sht_10, shorty_frames_walk_shg_sht, AI_EndAttack};

mframe_t	shorty_frames_walk_gdown[] = 
{
	ai_run,	     6.758, NULL,	// frame 0
	ai_run,	     5.223, NULL,	// frame 1
	ai_run,	     4.615, NULL,	// frame 2
	ai_run,	    14.711, AI_EndRun,	// frame 3
	ai_run,	     5.692, NULL,	// frame 4
	ai_run,	     7.645, NULL,	// frame 5
	ai_run,	    12.492, AI_EndRun,	// frame 6
	ai_run,	     6.806, NULL,	// frame 7
	ai_run,	    12.816, NULL,	// frame 8
	ai_run,	    12.048, NULL,	// frame 9
};
mmove_t	shorty_move_walk_gdown = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, shorty_frames_walk_gdown, AI_EndRun};

mframe_t	shorty_frames_run_nw[] = 
{
	ai_run,	 13.390, NULL,	// frame 0
	ai_run,	 20.672, NULL,	// frame 1
	ai_run,	 23.981, NULL,	// frame 2
	ai_run,	 21.476, NULL,	// frame 3
	ai_run,	  1.388, NULL,	// frame 4
	ai_run,	 24.850, NULL,	// frame 5
};
mmove_t	shorty_move_run_nw = {FRAME_run_nw_01, FRAME_run_nw_06, shorty_frames_run_nw, AI_EndRun};

mframe_t	shorty_frames_run_tg_sht[] = 
{
	ai_charge,	 18.527, shorty_firegun,	// frame 0
	ai_charge,	  5.820, NULL,	// frame 1
	ai_charge,	 38.453, shorty_firegun,	// frame 2
	ai_charge,	  6.628, NULL,	// frame 3
	ai_charge,	 22.021, shorty_firegun,	// frame 4
	ai_charge,	 14.366, NULL,	// frame 5
};
mmove_t	shorty_move_run_tg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_tg_sht, AI_EndAttack};

mframe_t	shorty_frames_run_reverse_tg_sht[] = 
{
	ai_charge,-14.366, shorty_firegun,	// frame 5
	ai_charge,-22.021, NULL,	// frame 4
	ai_charge, -6.628, shorty_firegun,	// frame 3
	ai_charge,-38.453, NULL,	// frame 2
	ai_charge, -5.820, shorty_firegun,	// frame 1
	ai_charge,-18.527, NULL,	// frame 0
};
mmove_t	shorty_move_run_reverse_tg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_reverse_tg_sht, AI_EndAttack};

mframe_t	shorty_frames_run_hmg_sht[] = 
{
	ai_charge,	 18.527, shorty_firehmg,	// frame 0
	ai_charge,	  5.820, shorty_firehmg,	// frame 1
	ai_charge,	 38.453, shorty_firehmg,	// frame 2
	ai_charge,	  6.628, NULL,	// frame 3
	ai_charge,	 22.021, NULL,	// frame 4
	ai_charge,	 14.366, shorty_firehmg_delay,	// frame 5
};
mmove_t	shorty_move_run_hmg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_hmg_sht, AI_EndAttack};

mframe_t	shorty_frames_run_reverse_hmg_sht[] = 
{
	ai_charge,-14.366, shorty_firehmg,	// frame 5
	ai_charge,-22.021, shorty_firehmg,	// frame 4
	ai_charge, -6.628, shorty_firehmg,	// frame 3
	ai_charge,-38.453, NULL,	// frame 2
	ai_charge, -5.820, NULL,	// frame 1
	ai_charge,-18.527, NULL,	// frame 0
};
mmove_t	shorty_move_run_reverse_hmg_sht = {FRAME_run_tg_sht_06, FRAME_run_tg_sht_01, shorty_frames_run_reverse_hmg_sht, AI_EndAttack};


mframe_t	shorty_frames_run_bazooka_sht[] = 
{
	ai_charge,	 18.527, shorty_firegun,	// frame 0
	ai_charge,	  5.820, NULL,	// frame 1
	ai_charge,	 38.453, NULL,	// frame 2
	ai_charge,	  6.628, NULL,	// frame 3
	ai_charge,	 22.021, NULL,	// frame 4
	ai_charge,	 14.366, shorty_bazooka_delay,	// frame 5
};
mmove_t	shorty_move_run_bazooka_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_bazooka_sht, AI_EndAttack};

mframe_t	shorty_frames_run_reverse_bazooka_sht[] = 
{
	ai_charge,-14.366, shorty_firegun,	// frame 5
	ai_charge,-22.021, NULL,	// frame 4
	ai_charge, -6.628, NULL,	// frame 3
	ai_charge,-38.453, NULL,	// frame 2
	ai_charge, -5.820, NULL,	// frame 1
	ai_charge,-18.527, NULL,	// frame 0
};
mmove_t	shorty_move_run_reverse_bazooka_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_reverse_bazooka_sht, AI_EndAttack};


mframe_t	shorty_frames_run_grenade_sht[] = 
{
	ai_charge,	 18.527, shorty_firegun,	// frame 0
	ai_charge,	  5.820, NULL,	// frame 1
	ai_charge,	 38.453, NULL,	// frame 2
	ai_charge,	  6.628, NULL,	// frame 3
	ai_charge,	 22.021, NULL,	// frame 4
	ai_charge,	 14.366, NULL,	// frame 5
};
mmove_t	shorty_move_run_grenade_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_grenade_sht, AI_EndAttack};

mframe_t	shorty_frames_run_reverse_grenade_sht[] = 
{
	ai_charge,-14.366, shorty_firegun,	// frame 5
	ai_charge,-22.021, NULL,	// frame 4
	ai_charge, -6.628, NULL,	// frame 3
	ai_charge,-38.453, NULL,	// frame 2
	ai_charge, -5.820, NULL,	// frame 1
	ai_charge,-18.527, NULL,	// frame 0
};
mmove_t	shorty_move_run_reverse_grenade_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_reverse_grenade_sht, AI_EndAttack};


mframe_t	shorty_frames_run_flamegun_sht[] = 
{
	ai_charge,	 18.527, shorty_firegun,	// frame 0
	ai_charge,	  5.820, shorty_firegun,	// frame 1
	ai_charge,	 38.453, shorty_firegun,	// frame 2
	ai_charge,	  6.628, shorty_firegun,	// frame 3
	ai_charge,	 22.021, shorty_firegun,	// frame 4
	ai_charge,	 14.366, shorty_firegun,	// frame 5
};
mmove_t	shorty_move_run_flamegun_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_flamegun_sht, AI_EndAttack};

mframe_t	shorty_frames_run_reverse_flamegun_sht[] = 
{
	ai_charge,-14.366, shorty_firegun,	// frame 5
	ai_charge,-22.021, shorty_firegun,	// frame 4
	ai_charge, -6.628, shorty_firegun,	// frame 3
	ai_charge,-38.453, shorty_firegun,	// frame 2
	ai_charge, -5.820, shorty_firegun,	// frame 1
	ai_charge,-18.527, shorty_firegun,	// frame 0
};
mmove_t	shorty_move_run_reverse_flamegun_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, shorty_frames_run_reverse_flamegun_sht, AI_EndAttack};


mframe_t	shorty_frames_run_shg_sht[] = 
{
	ai_charge,	 18.527, shorty_firegun,	// frame 0
	ai_charge,	 -1.017, NULL,	// frame 1
	ai_charge,	 37.949, NULL,	// frame 2
	ai_charge,	 10.778, shorty_shotgun_reload,	// frame 3
	ai_charge,	 16.787, NULL,	// frame 4
	ai_charge,	 22.273, NULL,	// frame 5
};
mmove_t	shorty_move_run_shg_sht = {FRAME_run_shg_sht_01, FRAME_run_shg_sht_06, shorty_frames_run_shg_sht, AI_EndAttack};

mframe_t	shorty_frames_run_gun_down[] = 
{
	ai_run,	 14.752, NULL,	// frame 0
	ai_run,	 12.524, NULL,	// frame 1
	ai_run,	 31.706, NULL,	// frame 2
	ai_run,	 13.085, NULL,	// frame 3
	ai_run,	 17.995, NULL,	// frame 4
	ai_run,	 16.366, NULL,	// frame 5
};
mmove_t	shorty_move_run_gun_down = {FRAME_run_gun_down_01, FRAME_run_gun_down_06, shorty_frames_run_gun_down, AI_EndRun};

mframe_t	shorty_frames_run_on_fire[] = 
{
	ai_onfire_run,	15.378, NULL,	// frame 0
	ai_onfire_run,	26.701, NULL,	// frame 1
	ai_onfire_run,	18.632, NULL,	// frame 2
	ai_onfire_run,	18.586, NULL,	// frame 3
	ai_onfire_run,	19.691, NULL,	// frame 4
	ai_onfire_run,	 6.251, NULL,	// frame 5
};
mmove_t	shorty_move_run_on_fire = {FRAME_run_on_fire_01, FRAME_run_on_fire_06, shorty_frames_run_on_fire, NULL};

mframe_t	shorty_frames_lsd_tg_run[] = 
{
	ai_sidestep,-17.749, shorty_firegun_left,	// frame 0
	ai_sidestep, -7.890, shorty_firegun_left,	// frame 1
	ai_sidestep,-32.494, shorty_firegun_left,	// frame 2
	ai_sidestep,-13.723, shorty_firegun_left,	// frame 3
	ai_sidestep,-17.575, shorty_firegun_left,	// frame 4
	ai_sidestep,-18.599, shorty_firegun_left,	// frame 5
};
mmove_t	shorty_move_lsd_tg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_lsd_tg_run, NULL};
//mmove_t	shorty_move_rsd_tg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_lsd_tg_run, NULL};

mframe_t	shorty_frames_rsd_tg_run[] = 
{
	ai_sidestep,16.578, shorty_firegun_right,	// frame 0
	ai_sidestep, 6.597, shorty_firegun_right,	// frame 1
	ai_sidestep,31.200, shorty_firegun_right,	// frame 2
	ai_sidestep,16.163, shorty_firegun_right,	// frame 3
	ai_sidestep,12.506, shorty_firegun_right,	// frame 4
	ai_sidestep,22.445, shorty_firegun_right,	// frame 5
};
mmove_t	shorty_move_rsd_tg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_rsd_tg_run, NULL};
//mmove_t	shorty_move_lsd_tg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_rsd_tg_run, NULL};




mframe_t	shorty_frames_lsd_hmg_run[] = 
{
	ai_sidestep,-17.749, shorty_firegun_left,	// frame 0
	ai_sidestep, -7.890, NULL,	// frame 1
	ai_sidestep,-32.494, shorty_firegun,	// frame 2
	ai_sidestep,-13.723, NULL,	// frame 3
	ai_sidestep,-17.575, shorty_firegun,	// frame 4
	ai_sidestep,-18.599, NULL,	// frame 5
};
mmove_t	shorty_move_lsd_hmg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_lsd_hmg_run, NULL};
//mmove_t	shorty_move_rsd_hmg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_lsd_hmg_run, NULL};

mframe_t	shorty_frames_rsd_hmg_run[] = 
{
	ai_sidestep,16.578, shorty_firegun_right,	// frame 0
	ai_sidestep, 6.597, NULL,	// frame 1
	ai_sidestep,31.200, shorty_firegun,	// frame 2
	ai_sidestep,16.163, NULL,	// frame 3
	ai_sidestep,12.506, shorty_firegun,	// frame 4
	ai_sidestep,22.445, NULL,	// frame 5
};
mmove_t	shorty_move_rsd_hmg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_rsd_hmg_run, NULL};
//mmove_t	shorty_move_lsd_hmg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_rsd_hmg_run, NULL};

mframe_t	shorty_frames_lsd_bazooka_run[] = 
{
	ai_sidestep,-17.749, shorty_firegun_left,	// frame 0
	ai_sidestep, -7.890, NULL,	// frame 1
	ai_sidestep,-32.494, NULL,	// frame 2
	ai_sidestep,-13.723, NULL,	// frame 3
	ai_sidestep,-17.575, NULL,	// frame 4
	ai_sidestep,-18.599, NULL,	// frame 5
};
mmove_t	shorty_move_lsd_bazooka_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_lsd_bazooka_run, NULL};
//mmove_t	shorty_move_rsd_bazooka_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_lsd_bazooka_run, NULL};

mframe_t	shorty_frames_rsd_bazooka_run[] = 
{
	ai_sidestep,16.578, shorty_firegun_right,	// frame 0
	ai_sidestep, 6.597, NULL,	// frame 1
	ai_sidestep,31.200, NULL,	// frame 2
	ai_sidestep,16.163, NULL,	// frame 3
	ai_sidestep,12.506, NULL,	// frame 4
	ai_sidestep,22.445, NULL,	// frame 5
};
mmove_t	shorty_move_rsd_bazooka_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_rsd_bazooka_run, NULL};
//mmove_t	shorty_move_lsd_bazooka_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_rsd_bazooka_run, NULL};

mframe_t	shorty_frames_lsd_grenade_run[] = 
{
	ai_sidestep,-17.749, shorty_firegun_left,	// frame 0
	ai_sidestep, -7.890, NULL,	// frame 1
	ai_sidestep,-32.494, NULL,	// frame 2
	ai_sidestep,-13.723, NULL,	// frame 3
	ai_sidestep,-17.575, NULL,	// frame 4
	ai_sidestep,-18.599, NULL,	// frame 5
};
mmove_t	shorty_move_lsd_grenade_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_lsd_grenade_run, NULL};
//mmove_t	shorty_move_rsd_grenade_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_lsd_grenade_run, NULL};

mframe_t	shorty_frames_rsd_grenade_run[] = 
{
	ai_sidestep,16.578, shorty_firegun_right,	// frame 0
	ai_sidestep, 6.597, NULL,	// frame 1
	ai_sidestep,31.200, NULL,	// frame 2
	ai_sidestep,16.163, NULL,	// frame 3
	ai_sidestep,12.506, NULL,	// frame 4
	ai_sidestep,22.445, NULL,	// frame 5
};
mmove_t	shorty_move_rsd_grenade_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_rsd_grenade_run, NULL};
//mmove_t	shorty_move_lsd_grenade_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_rsd_grenade_run, NULL};

mframe_t	shorty_frames_lsd_flamegun_run[] = 
{
	ai_sidestep,-17.749, shorty_firegun_left,	// frame 0
	ai_sidestep, -7.890, shorty_firegun_left,	// frame 1
	ai_sidestep,-32.494, shorty_firegun_left,	// frame 2
	ai_sidestep,-13.723, shorty_firegun_left,	// frame 3
	ai_sidestep,-17.575, shorty_firegun_left,	// frame 4
	ai_sidestep,-18.599, shorty_firegun_left,	// frame 5
};
mmove_t	shorty_move_lsd_flamegun_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_lsd_flamegun_run, NULL};
//mmove_t	shorty_move_rsd_flamegun_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_lsd_flamegun_run, NULL};

mframe_t	shorty_frames_rsd_flamegun_run[] = 
{
	ai_sidestep,16.578, shorty_firegun_right,	// frame 0
	ai_sidestep, 6.597, shorty_firegun_right,	// frame 1
	ai_sidestep,31.200, shorty_firegun_right,	// frame 2
	ai_sidestep,16.163, shorty_firegun_right,	// frame 3
	ai_sidestep,12.506, shorty_firegun_right,	// frame 4
	ai_sidestep,22.445, shorty_firegun_right,	// frame 5
};
mmove_t	shorty_move_rsd_flamegun_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, shorty_frames_rsd_flamegun_run, NULL};
//mmove_t	shorty_move_lsd_flamegun_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, shorty_frames_rsd_flamegun_run, NULL};

mframe_t	shorty_frames_lsd_shg_run[] = 
{
	ai_sidestep,-	  24.221*0.75, NULL,	// frame 0
	ai_sidestep,-	  20.466*0.75, shorty_firegun_left,	// frame 1
	ai_sidestep,-	  32.136*0.75, NULL,	// frame 2
	ai_sidestep,-	  39.252*0.75, shorty_shotgun_reload,	// frame 3
	ai_sidestep,-	  29.464*0.75, NULL,	// frame 4
	ai_sidestep,-	  23.279*0.75, NULL,	// frame 5
};
//mmove_t	shorty_move_lsd_shg_run = {FRAME_rsd_shg_run_01, FRAME_rsd_shg_run_06, shorty_frames_lsd_shg_run, NULL};
mmove_t	shorty_move_rsd_shg_run = {FRAME_lsd_shg_run_01, FRAME_lsd_shg_run_06, shorty_frames_lsd_shg_run, NULL};

mframe_t	shorty_frames_rsd_shg_run[] = 
{
	ai_sidestep,	  26.812*0.75, NULL,	// frame 0
	ai_sidestep,	  18.773*0.75, shorty_firegun_right,	// frame 1
	ai_sidestep,	  34.600*0.75, NULL,	// frame 2
	ai_sidestep,	  36.035*0.75, shorty_shotgun_reload,	// frame 3
	ai_sidestep,	  31.354*0.75, NULL,	// frame 4
	ai_sidestep,	  23.697*0.75, NULL,	// frame 5
};
//mmove_t	shorty_move_rsd_shg_run = {FRAME_lsd_shg_run_01, FRAME_lsd_shg_run_06, shorty_frames_rsd_shg_run, NULL};
mmove_t	shorty_move_lsd_shg_run = {FRAME_rsd_shg_run_01, FRAME_rsd_shg_run_06, shorty_frames_rsd_shg_run, NULL};

//================================================================================================================
// created moves
mframe_t	shorty_frames_avoid_walk[] = 
{
	ai_turn,	   6.758, NULL,	// frame 0
	ai_turn,	   5.223, NULL,	// frame 1
	ai_turn,	   4.615, NULL,	// frame 2
	ai_turn,	  14.711, NULL,	// frame 3
	ai_turn,	   5.692, NULL,	// frame 4
	ai_turn,	   7.645, NULL,	// frame 5
	ai_turn,	  12.492, NULL,	// frame 6
	ai_turn,	   6.806, NULL,	// frame 7
	ai_turn,	  12.816, NULL,	// frame 8
	ai_turn,	  12.048, NULL,	// frame 9
};
mmove_t	shorty_move_avoid_walk = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, shorty_frames_avoid_walk, AI_EndAttack};

mframe_t	shorty_frames_avoid_crouch_walk[] = 
{
	ai_turn,	  5.383, NULL,	// frame 0
	ai_turn,	  5.466, NULL,	// frame 1
	ai_turn,	  3.693, NULL,	// frame 2
	ai_turn,	  5.865, NULL,	// frame 3
	ai_turn,	 13.852, NULL,	// frame 4
	ai_turn,	  6.698, NULL,	// frame 5
	ai_turn,	  3.743, NULL,	// frame 6
};
mmove_t	shorty_move_avoid_crouch_walk = {FRAME_crouch_walk_01, FRAME_crouch_walk_07, shorty_frames_avoid_crouch_walk, AI_EndAttack};

mframe_t	shorty_frames_walk_gdownFLASHLIGHT[] = 
{
	ai_runFLASHLIGHT,	  6.758, NULL,	// frame 0
	ai_runFLASHLIGHT,	  5.223, NULL,	// frame 1
	ai_runFLASHLIGHT,	  4.615, NULL,	// frame 2
	ai_runFLASHLIGHT,	 14.711, AI_EndRun,	// frame 3
	ai_runFLASHLIGHT,	  5.692, NULL,	// frame 4
	ai_runFLASHLIGHT,	  7.645, NULL,	// frame 5
	ai_runFLASHLIGHT,	 12.492, AI_EndRun,	// frame 6
	ai_runFLASHLIGHT,	  6.806, NULL,	// frame 7
	ai_runFLASHLIGHT,	 12.816, NULL,	// frame 8
	ai_runFLASHLIGHT,	 12.048, NULL,	// frame 9
};
mmove_t	shorty_move_walk_gdownFLASHLIGHT = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, shorty_frames_walk_gdownFLASHLIGHT, AI_EndRun };

mframe_t	shorty_frames_avoid_run[] = 
{
	ai_turn,	 26.748, NULL,	// frame 0
	ai_turn,	 17.188, NULL,	// frame 1
	ai_turn,	 31.486, NULL,	// frame 2
	ai_turn,	 31.052, NULL,	// frame 3
	ai_turn,	 23.944, NULL,	// frame 4
	ai_turn,	 24.549, NULL,	// frame 5	
};
mmove_t	shorty_move_avoid_run = {FRAME_run_gun_down_01, FRAME_run_gun_down_06, shorty_frames_avoid_run, AI_EndAttack};

mframe_t	shorty_frames_avoid_reverse_walk[] = 
{
	ai_turn,	-7.640, NULL,	// frame 5
	ai_turn,	-8.913, NULL,	// frame 4
	ai_turn,	-4.200, NULL,	// frame 3
	ai_turn,	-3.111, NULL,	// frame 2
	ai_turn,	-6.504, NULL,	// frame 1
	ai_turn,	-3.636, NULL,	// frame 0
};
mmove_t	shorty_move_avoid_reverse_walk = {FRAME_walk_gdown_06, FRAME_walk_gdown_01, shorty_frames_avoid_reverse_walk, AI_EndAttack};

mframe_t	shorty_frames_avoid_reverse_run[] = 
{
	ai_turn,	- 24.549, NULL,	// frame 5
	ai_turn,	- 23.944, NULL,	// frame 4
	ai_turn,	- 31.052, NULL,	// frame 3
	ai_turn,	- 31.486, NULL,	// frame 2
	ai_turn,	- 17.188, NULL,	// frame 1
	ai_turn,	- 26.748, NULL,	// frame 0
};
mmove_t	shorty_move_avoid_reverse_run = {FRAME_run_gun_down_06, FRAME_run_gun_down_03, shorty_frames_avoid_reverse_run, AI_EndAttack};


mframe_t	shorty_frames_walk_dokey[] = 
{
	ai_runDOKEY,	  6.758, EP_ReachedDoKey,	// frame 0
	ai_runDOKEY,	  5.223, EP_ReachedDoKey,	// frame 1
	ai_runDOKEY,	  4.615, EP_ReachedDoKey,	// frame 2
	ai_runDOKEY,	 14.711, EP_ReachedDoKey,	// frame 3
	ai_runDOKEY,	  5.692, EP_ReachedDoKey,	// frame 4
	ai_runDOKEY,	  7.645, EP_ReachedDoKey,	// frame 5
	ai_runDOKEY,	 12.492, EP_ReachedDoKey,	// frame 6
	ai_runDOKEY,	  6.806, EP_ReachedDoKey,	// frame 7
	ai_runDOKEY,	 12.816, EP_ReachedDoKey,	// frame 8
	ai_runDOKEY,	 12.048, EP_ReachedDoKey,	// frame 9
};
mmove_t	shorty_move_walk_dokey = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, shorty_frames_walk_dokey, EP_ReachedDoKey};

mframe_t	shorty_frames_crch_dokey[] = 
{
	ai_stand,	  0.000, NULL,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
	ai_stand,	  0.000, NULL,	// frame 2
	ai_stand,	  0.000, NULL,	// frame 3
	ai_stand,	  0.000, NULL,	// frame 4
	ai_stand,	  0.000, NULL,	// frame 5
	ai_stand,	  0.000, NULL,	// frame 6
	ai_stand,	  0.000, NULL,	// frame 7
	ai_stand,	  0.000, NULL,	// frame 8
	ai_stand,	  0.000, NULL,	// frame 9
	ai_stand,	  0.000, NULL,	// frame 10
	ai_stand,	  0.000, NULL,	// frame 11
	ai_stand,	  0.000, NULL,	// frame 12
	ai_stand,	  0.000, NULL,	// frame 13
	ai_stand,	  0.000, NULL,	// frame 14
	ai_stand,	  0.000, NULL,	// frame 15
	
};
mmove_t	shorty_move_crch_dokey = {FRAME_crch_astand_01, FRAME_crch_astand_16, shorty_frames_crch_dokey, EP_EndDoKey};

/*
custom moves to allow hmg sound to and visuals to behave as player hmg
*/
 
mframe_t	shorty_frames_hmg_shoot2[] = 
{
	ai_charge,	  0.000, NULL,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, shorty_hmg_avoid,	// frame 4
};
mmove_t	shorty_move_hmg_shoot2 = {FRAME_hmg_std_01, FRAME_hmg_std_05, shorty_frames_hmg_shoot2, AI_EndAttack};

mframe_t	shorty_frames_walk_hmg_sht2[] = 
{
	ai_turn,	   7.963, NULL,	// frame 0
	ai_turn,	   3.735, NULL,	// frame 1
	ai_turn,	   9.088, NULL,	// frame 2
	ai_turn,	  11.945, NULL,	// frame 3
	ai_turn,	   6.984, NULL,	// frame 4
	ai_turn,	   3.927, NULL,	// frame 5
	ai_turn,	  16.424, NULL,	// frame 6
	ai_turn,	   4.464, NULL,	// frame 7
	ai_turn,	  15.347, NULL,	// frame 8
	ai_turn,	   8.590, shorty_hmg_avoid,	// frame 9
};
mmove_t	shorty_move_walk_hmg_sht2 = {FRAME_hmg_wlk_01, FRAME_hmg_wlk_10, shorty_frames_walk_hmg_sht2, AI_EndAttack};

mframe_t	shorty_frames_run_hmg_sht2[] = 
{
	ai_charge,	 18.527, NULL,	// frame 0
	ai_charge,	  5.820, NULL,	// frame 1
	ai_charge,	 38.453, NULL,	// frame 2
	ai_charge,	  6.628, NULL,	// frame 3
	ai_charge,	 22.021, NULL,	// frame 4
	ai_charge,	 14.366, shorty_hmg_avoid,	// frame 5
};
mmove_t	shorty_move_run_hmg_sht2 = {FRAME_hmg_run_01, FRAME_hmg_run_06, shorty_frames_run_hmg_sht2, AI_EndAttack};


mframe_t	shorty_frames_bazooka_shoot2[] = 
{
	ai_charge,	  0.000, NULL,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
};
mmove_t	shorty_move_bazooka_shoot2 = {FRAME_hmg_std_01, FRAME_hmg_std_05, shorty_frames_bazooka_shoot2, AI_EndAttack};

mframe_t	shorty_frames_walk_bazooka_shoot2[] = 
{
	ai_turn,	   7.963, NULL,	// frame 0
	ai_turn,	   3.735, NULL,	// frame 1
	ai_turn,	   9.088, NULL,	// frame 2
	ai_turn,	  11.945, NULL,	// frame 3
	ai_turn,	   6.984, NULL,	// frame 4
	ai_turn,	   3.927, NULL,	// frame 5
	ai_turn,	  16.424, NULL,	// frame 6
	ai_turn,	   4.464, NULL,	// frame 7
	ai_turn,	  15.347, NULL,	// frame 8
	ai_turn,	   8.590, NULL,	// frame 9
};
mmove_t	shorty_move_walk_bazooka_shoot2 = {FRAME_hmg_wlk_01, FRAME_hmg_wlk_10, shorty_frames_walk_bazooka_shoot2, AI_EndAttack};

mframe_t	shorty_frames_run_bazooka_shoot2[] = 
{
	ai_charge,	 18.527, NULL,	// frame 0
	ai_charge,	  5.820, NULL,	// frame 1
	ai_charge,	 38.453, NULL,	// frame 2
	ai_charge,	  6.628, NULL,	// frame 3
	ai_charge,	 22.021, NULL,	// frame 4
	ai_charge,	 14.366, NULL,	// frame 5
};
mmove_t	shorty_move_run_bazooka_shoot2 = {FRAME_hmg_run_01, FRAME_hmg_run_06, shorty_frames_run_bazooka_shoot2, AI_EndAttack};
