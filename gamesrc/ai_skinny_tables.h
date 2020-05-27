
//==================================================================================================
// standard moves

mframe_t	punk_frames_stand[] = 
{
	ai_stand,	  0.000, punk_talk_think,	// frame 0
	ai_stand,	  0.000, punk_talk_think,	// frame 1
	ai_stand,	  0.000, punk_talk_think,	// frame 2
	ai_stand,	  0.000, punk_talk_think,	// frame 3
	ai_stand,	  0.000, punk_talk_think,	// frame 4
	ai_stand,	  0.000, punk_talk_think,	// frame 5
	ai_stand,	  0.000, punk_talk_think,	// frame 6
	ai_stand,	  0.000, punk_talk_think,	// frame 7
	ai_stand,	  0.000, punk_talk_think,	// frame 8
	ai_stand,	  0.000, punk_talk_think,	// frame 9
	ai_stand,	  0.000, punk_talk_think,	// frame 10
	ai_stand,	  0.000, punk_talk_think,	// frame 11
	ai_stand,	  0.000, punk_talk_think,	// frame 12
	ai_stand,	  0.000, punk_talk_think,	// frame 13
	ai_stand,	  0.000, punk_talk_think,	// frame 14
	ai_stand,	  0.000, punk_talk_think,	// frame 15
	ai_stand,	  0.000, punk_talk_think,	// frame 16
	ai_stand,	  0.000, punk_talk_think,	// frame 17
	ai_stand,	  0.000, punk_talk_think,	// frame 18
	ai_stand,	  0.000, punk_talk_think,	// frame 19
	ai_stand,	  0.000, punk_talk_think,	// frame 20
	ai_stand,	  0.000, punk_talk_think,	// frame 21
	ai_stand,	  0.000, punk_talk_think,	// frame 22
	ai_stand,	  0.000, punk_talk_think,	// frame 23
	ai_stand,	  0.000, punk_talk_think,	// frame 24
	ai_stand,	  0.000, punk_talk_think,	// frame 25
	ai_stand,	  0.000, punk_talk_think,	// frame 26
	ai_stand,	  0.000, punk_talk_think,	// frame 27
	ai_stand,	  0.000, punk_talk_think,	// frame 28
	ai_stand,	  0.000, punk_talk_think,	// frame 29
	ai_stand,	  0.000, punk_talk_think,	// frame 30
};
mmove_t	punk_move_stand = {FRAME_stand_01, FRAME_stand_31, punk_frames_stand, punk_end_stand};

mframe_t	punk_frames_tg_shoot[] = 
{
	ai_charge,	  0.000, punk_firegun,	// frame 0
	ai_charge,	  0.000, punk_firegun,	// frame 1
	ai_charge,	  0.000, punk_firegun,	// frame 2
	ai_charge,	  0.000, punk_firegun,	// frame 3
	ai_charge,	  0.000, punk_firegun,	// frame 4
};
mmove_t	punk_move_tg_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_05, punk_frames_tg_shoot, AI_EndAttack};

mframe_t	punk_frames_hmg_shoot[] = 
{
	ai_charge,	  0.000, punk_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, punk_firegun,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, punk_firegun,	// frame 4
};
mmove_t	punk_move_hmg_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_05, punk_frames_hmg_shoot, AI_EndAttack};

mframe_t	punk_frames_bazooka_shoot[] = 
{
	ai_charge,	  0.000, punk_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
};
mmove_t	punk_move_bazooka_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_05, punk_frames_bazooka_shoot, AI_EndAttack};

mframe_t	punk_frames_grenade_shoot[] = 
{
	ai_charge,	  0.000, punk_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
};
mmove_t	punk_move_grenade_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_05, punk_frames_grenade_shoot, AI_EndAttack};


mframe_t	punk_frames_flamegun_shoot[] = 
{
	ai_charge,	  0.000, punk_firegun,	// frame 0
	ai_charge,	  0.000, punk_firegun,	// frame 1
	ai_charge,	  0.000, punk_firegun,	// frame 2
	ai_charge,	  0.000, punk_firegun,	// frame 3
	ai_charge,	  0.000, punk_firegun,	// frame 4
};
mmove_t	punk_move_flamegun_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_05, punk_frames_flamegun_shoot, AI_EndAttack};

mframe_t	punk_frames_shg_shoot[] = 
{
	ai_charge,	  0.000, punk_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, punk_shotgun_reload,	// frame 7
	ai_charge,	  0.000, NULL,	// frame 8
	ai_charge,	  0.000, NULL,	// frame 9
	ai_charge,	  0.000, NULL,	// frame 10
	ai_charge,	  0.000, NULL,	// frame 11
	ai_charge,	  0.000, NULL,	// frame 12
};
mmove_t	punk_move_shg_shoot = {FRAME_shg_shoot_01, FRAME_shg_shoot_13, punk_frames_shg_shoot, AI_EndAttack};

mframe_t	punk_frames_tg_reload[] = 
{
	ai_charge,	  0.000, NULL,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, NULL,	// frame 7
	ai_charge,	  0.000, punk_reload_snd,	// frame 8
	ai_charge,	  0.000, NULL,	// frame 9
	ai_charge,	  0.000, NULL,	// frame 10
	ai_charge,	  0.000, NULL,	// frame 11
	ai_charge,	  0.000, NULL,	// frame 12
	ai_charge,	  0.000, NULL,	// frame 13
	ai_charge,	  0.000, NULL,	// frame 14
	ai_charge,	  0.000, NULL,	// frame 15
};
mmove_t	punk_move_tg_reload = {FRAME_tg_reload_01, FRAME_tg_reload_16, punk_frames_tg_reload, AI_EndAttack};

mframe_t	punk_frames_talk1[] = 
{
	ai_stand,	  0.000, punk_talk_think,	// frame 0
	ai_stand,	  0.000, punk_talk_think,	// frame 1
	ai_stand,	  0.000, punk_talk_think,	// frame 2
	ai_stand,	  0.000, punk_talk_think,	// frame 3
	ai_stand,	  0.000, punk_talk_think,	// frame 4
	ai_stand,	  0.000, punk_talk_think,	// frame 5
	ai_stand,	  0.000, punk_talk_think,	// frame 6
	ai_stand,	  0.000, punk_talk_think,	// frame 7
	ai_stand,	  0.000, punk_talk_think,	// frame 8
	ai_stand,	  0.000, punk_talk_think,	// frame 9
	ai_stand,	  0.000, punk_talk_think,	// frame 10
	ai_stand,	  0.000, punk_talk_think,	// frame 11
	ai_stand,	  0.000, punk_talk_think,	// frame 12
	ai_stand,	  0.000, punk_talk_think,	// frame 13
	ai_stand,	  0.000, punk_talk_think,	// frame 14
	ai_stand,	  0.000, punk_talk_think,	// frame 15
	ai_stand,	  0.000, punk_talk_think,	// frame 16
	ai_stand,	  0.000, punk_talk_think,	// frame 17
	ai_stand,	  0.000, punk_talk_think,	// frame 18
	ai_stand,	  0.000, punk_talk_think,	// frame 19
	ai_stand,	  0.000, punk_talk_think,	// frame 20
	ai_stand,	  0.000, punk_talk_think,	// frame 21
	ai_stand,	  0.000, punk_talk_think,	// frame 22
	ai_stand,	  0.000, punk_talk_think,	// frame 23
	ai_stand,	  0.000, punk_talk_think,	// frame 24
	ai_stand,	  0.000, punk_talk_think,	// frame 25
};
mmove_t	punk_move_talk1 = {FRAME_talk1_01, FRAME_talk1_26, punk_frames_talk1, punk_end_stand};

mframe_t	punk_frames_talk2[] = 
{
	ai_stand,	  0.000, punk_talk_think,	// frame 0
	ai_stand,	  0.000, punk_talk_think,	// frame 1
	ai_stand,	  0.000, punk_talk_think,	// frame 2
	ai_stand,	  0.000, punk_talk_think,	// frame 3
	ai_stand,	  0.000, punk_talk_think,	// frame 4
	ai_stand,	  0.000, punk_talk_think,	// frame 5
	ai_stand,	  0.000, punk_talk_think,	// frame 6
	ai_stand,	  0.000, punk_talk_think,	// frame 7
	ai_stand,	  0.000, punk_talk_think,	// frame 8
	ai_stand,	  0.000, punk_talk_think,	// frame 9
	ai_stand,	  0.000, punk_talk_think,	// frame 10
	ai_stand,	  0.000, punk_talk_think,	// frame 11
	ai_stand,	  0.000, punk_talk_think,	// frame 12
	ai_stand,	  0.000, punk_talk_think,	// frame 13
	ai_stand,	  0.000, punk_talk_think,	// frame 14
	ai_stand,	  0.000, punk_talk_think,	// frame 15
	ai_stand,	  0.000, punk_talk_think,	// frame 16
	ai_stand,	  0.000, punk_talk_think,	// frame 17
	ai_stand,	  0.000, punk_talk_think,	// frame 18
	ai_stand,	  0.000, punk_talk_think,	// frame 19
};
mmove_t	punk_move_talk2 = {FRAME_talk2_01, FRAME_talk2_20, punk_frames_talk2, punk_end_stand};

mframe_t	punk_frames_talk3[] = 
{
	ai_stand,	  0.000, punk_talk_think,	// frame 0
	ai_stand,	  0.000, punk_talk_think,	// frame 1
	ai_stand,	  0.000, punk_talk_think,	// frame 2
	ai_stand,	  0.000, punk_talk_think,	// frame 3
	ai_stand,	  0.000, punk_talk_think,	// frame 4
	ai_stand,	  0.000, punk_talk_think,	// frame 5
	ai_stand,	  0.000, punk_talk_think,	// frame 6
	ai_stand,	  0.000, punk_talk_think,	// frame 7
	ai_stand,	  0.000, punk_talk_think,	// frame 8
	ai_stand,	  0.000, punk_talk_think,	// frame 9
	ai_stand,	  0.000, punk_talk_think,	// frame 10
	ai_stand,	  0.000, punk_talk_think,	// frame 11
	ai_stand,	  0.000, punk_talk_think,	// frame 12
	ai_stand,	  0.000, punk_talk_think,	// frame 13
	ai_stand,	  0.000, punk_talk_think,	// frame 14
	ai_stand,	  0.000, punk_talk_think,	// frame 15
	ai_stand,	  0.000, punk_talk_think,	// frame 16
	ai_stand,	  0.000, punk_talk_think,	// frame 17
	ai_stand,	  0.000, punk_talk_think,	// frame 18
	ai_stand,	  0.000, punk_talk_think,	// frame 19
	ai_stand,	  0.000, punk_talk_think,	// frame 20
};
mmove_t	punk_move_talk3 = {FRAME_talk3_01, FRAME_talk3_21, punk_frames_talk3, punk_end_stand};

mframe_t	punk_frames_talk4[] = 
{
	ai_stand,	  0.000, punk_talk_think,	// frame 0
	ai_stand,	  0.000, punk_talk_think,	// frame 1
	ai_stand,	  0.000, punk_talk_think,	// frame 2
	ai_stand,	  0.000, punk_talk_think,	// frame 3
	ai_stand,	  0.000, punk_talk_think,	// frame 4
	ai_stand,	  0.000, punk_talk_think,	// frame 5
	ai_stand,	  0.000, punk_talk_think,	// frame 6
	ai_stand,	  0.000, punk_talk_think,	// frame 7
	ai_stand,	  0.000, punk_talk_think,	// frame 8
	ai_stand,	  0.000, punk_talk_think,	// frame 9
	ai_stand,	  0.000, punk_talk_think,	// frame 10
	ai_stand,	  0.000, punk_talk_think,	// frame 11
	ai_stand,	  0.000, punk_talk_think,	// frame 12
	ai_stand,	  0.000, punk_talk_think,	// frame 13
	ai_stand,	  0.000, punk_talk_think,	// frame 14
	ai_stand,	  0.000, punk_talk_think,	// frame 15
	ai_stand,	  0.000, punk_talk_think,	// frame 16
	ai_stand,	  0.000, punk_talk_think,	// frame 17
	ai_stand,	  0.000, punk_talk_think,	// frame 18
	ai_stand,	  0.000, punk_talk_think,	// frame 19
	ai_stand,	  0.000, punk_talk_think,	// frame 20
	ai_stand,	  0.000, punk_talk_think,	// frame 21
	ai_stand,	  0.000, punk_talk_think,	// frame 22
	ai_stand,	  0.000, punk_talk_think,	// frame 23
	ai_stand,	  0.000, punk_talk_think,	// frame 24
	ai_stand,	  0.000, punk_talk_think,	// frame 25
	ai_stand,	  0.000, punk_talk_think,	// frame 26
	ai_stand,	  0.000, punk_talk_think,	// frame 27
	ai_stand,	  0.000, punk_talk_think,	// frame 28
	ai_stand,	  0.000, punk_talk_think,	// frame 29
	ai_stand,	  0.000, punk_talk_think,	// frame 30
	ai_stand,	  0.000, punk_talk_think,	// frame 31
	ai_stand,	  0.000, punk_talk_think,	// frame 32
};
mmove_t	punk_move_talk4 = {FRAME_talk4_01, FRAME_talk4_33, punk_frames_talk4, punk_end_stand};

mframe_t	punk_frames_talk5[] = 
{
	ai_stand,	  0.000, punk_talk_think,	// frame 0
	ai_stand,	  0.000, punk_talk_think,	// frame 1
	ai_stand,	  0.000, punk_talk_think,	// frame 2
	ai_stand,	  0.000, punk_talk_think,	// frame 3
	ai_stand,	  0.000, punk_talk_think,	// frame 4
	ai_stand,	  0.000, punk_talk_think,	// frame 5
	ai_stand,	  0.000, punk_talk_think,	// frame 6
	ai_stand,	  0.000, punk_talk_think,	// frame 7
	ai_stand,	  0.000, punk_talk_think,	// frame 8
	ai_stand,	  0.000, punk_talk_think,	// frame 9
	ai_stand,	  0.000, punk_talk_think,	// frame 10
	ai_stand,	  0.000, punk_talk_think,	// frame 11
	ai_stand,	  0.000, punk_talk_think,	// frame 12
	ai_stand,	  0.000, punk_talk_think,	// frame 13
	ai_stand,	  0.000, punk_talk_think,	// frame 14
	ai_stand,	  0.000, punk_talk_think,	// frame 15
	ai_stand,	  0.000, punk_talk_think,	// frame 16
	ai_stand,	  0.000, punk_talk_think,	// frame 17
	ai_stand,	  0.000, punk_talk_think,	// frame 18
	ai_stand,	  0.000, punk_talk_think,	// frame 19
	ai_stand,	  0.000, punk_talk_think,	// frame 20
	ai_stand,	  0.000, punk_talk_think,	// frame 21
	ai_stand,	  0.000, punk_talk_think,	// frame 22
	ai_stand,	  0.000, punk_talk_think,	// frame 23
	ai_stand,	  0.000, punk_talk_think,	// frame 24
	ai_stand,	  0.000, punk_talk_think,	// frame 25
	ai_stand,	  0.000, punk_talk_think,	// frame 26
	ai_stand,	  0.000, punk_talk_think,	// frame 27
	ai_stand,	  0.000, punk_talk_think,	// frame 28
};
mmove_t	punk_move_talk5 = {FRAME_talk5_01, FRAME_talk5_29, punk_frames_talk5, punk_end_stand};

mframe_t	punk_frames_talk6[] = 
{
	ai_stand,	  0.000, punk_talk_think,	// frame 0
	ai_stand,	  0.000, punk_talk_think,	// frame 1
	ai_stand,	  0.000, punk_talk_think,	// frame 2
	ai_stand,	  0.000, punk_talk_think,	// frame 3
	ai_stand,	  0.000, punk_talk_think,	// frame 4
	ai_stand,	  0.000, punk_talk_think,	// frame 5
	ai_stand,	  0.000, punk_talk_think,	// frame 6
	ai_stand,	  0.000, punk_talk_think,	// frame 7
	ai_stand,	  0.000, punk_talk_think,	// frame 8
	ai_stand,	  0.000, punk_talk_think,	// frame 9
	ai_stand,	  0.000, punk_talk_think,	// frame 10
	ai_stand,	  0.000, punk_talk_think,	// frame 11
	ai_stand,	  0.000, punk_talk_think,	// frame 12
	ai_stand,	  0.000, punk_talk_think,	// frame 13
	ai_stand,	  0.000, punk_talk_think,	// frame 14
	ai_stand,	  0.000, punk_talk_think,	// frame 15
	ai_stand,	  0.000, punk_talk_think,	// frame 16
	ai_stand,	  0.000, punk_talk_think,	// frame 17
	ai_stand,	  0.000, punk_talk_think,	// frame 18
	ai_stand,	  0.000, punk_talk_think,	// frame 19
	ai_stand,	  0.000, punk_talk_think,	// frame 20
	ai_stand,	  0.000, punk_talk_think,	// frame 21
	ai_stand,	  0.000, punk_talk_think,	// frame 22
	ai_stand,	  0.000, punk_talk_think,	// frame 23
	ai_stand,	  0.000, punk_talk_think,	// frame 24
	ai_stand,	  0.000, punk_talk_think,	// frame 25
	ai_stand,	  0.000, punk_talk_think,	// frame 26
	ai_stand,	  0.000, punk_talk_think,	// frame 27
	ai_stand,	  0.000, punk_talk_think,	// frame 28
	ai_stand,	  0.000, punk_talk_think,	// frame 29
	ai_stand,	  0.000, punk_talk_think,	// frame 30
	ai_stand,	  0.000, punk_talk_think,	// frame 31
	ai_stand,	  0.000, punk_talk_think,	// frame 32
	ai_stand,	  0.000, punk_talk_think,	// frame 33
	ai_stand,	  0.000, punk_talk_think,	// frame 34
	ai_stand,	  0.000, punk_talk_think,	// frame 35
	ai_stand,	  0.000, punk_talk_think,	// frame 36
	ai_stand,	  0.000, punk_talk_think,	// frame 37
	ai_stand,	  0.000, punk_talk_think,	// frame 38
	ai_stand,	  0.000, punk_talk_think,	// frame 39
	ai_stand,	  0.000, punk_talk_think,	// frame 40
	ai_stand,	  0.000, punk_talk_think,	// frame 41
	ai_stand,	  0.000, punk_talk_think,	// frame 42
	ai_stand,	  0.000, punk_talk_think,	// frame 43
	ai_stand,	  0.000, punk_talk_think,	// frame 44
	ai_stand,	  0.000, punk_talk_think,	// frame 45
	ai_stand,	  0.000, punk_talk_think,	// frame 46
};
mmove_t	punk_move_talk6 = {FRAME_talk6_01, FRAME_talk6_47, punk_frames_talk6, punk_end_stand};

mframe_t	punk_frames_head_wipe[] = 
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
mmove_t	punk_move_head_wipe = {FRAME_head_wipe_01, FRAME_head_wipe_28, punk_frames_head_wipe, punk_end_stand};

mframe_t	punk_frames_pain_Rarm[] = 
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
mmove_t	punk_move_pain_Rarm = {FRAME_pain_Rarm_01, FRAME_pain_Rarm_09, punk_frames_pain_Rarm, AI_EndAttack};

mframe_t	punk_frames_pain_Larm[] = 
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
mmove_t	punk_move_pain_Larm = {FRAME_pain_Larm_01, FRAME_pain_Larm_08, punk_frames_pain_Larm, AI_EndAttack};

mframe_t	punk_frames_pain_chest[] = 
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
mmove_t	punk_move_pain_chest = {FRAME_pain_chest_01, FRAME_pain_chest_10, punk_frames_pain_chest, AI_EndAttack};

mframe_t	punk_frames_pain_head[] = 
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
mmove_t	punk_move_pain_head = {FRAME_pain_head_01, FRAME_pain_head_08, punk_frames_pain_head, AI_EndAttack};

mframe_t	punk_frames_pain_Rleg[] = 
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
};
mmove_t	punk_move_pain_Rleg = {FRAME_pain_Rleg_01, FRAME_pain_Rleg_11, punk_frames_pain_Rleg, AI_EndAttack};

mframe_t	punk_frames_pain_Lleg[] = 
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
mmove_t	punk_move_pain_Lleg = {FRAME_pain_Lleg_01, FRAME_pain_Lleg_09, punk_frames_pain_Lleg, AI_EndAttack};

mframe_t	punk_frames_pain_crch[] = 
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
};
mmove_t	punk_move_pain_crch = {FRAME_pain_crch_01, FRAME_pain_crch_13, punk_frames_pain_crch, AI_EndAttack};

mframe_t	punk_frames_pain_butt[] = 
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
};
mmove_t	punk_move_pain_butt = {FRAME_pain_butt_01, FRAME_pain_butt_14, punk_frames_pain_butt, AI_EndAttack};

mframe_t	punk_frames_jump[] = 
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
mmove_t	punk_move_jump = {FRAME_jump_06, FRAME_jump_09, punk_frames_jump, AI_EndJump};

mframe_t	punk_frames_death1[] = 
{
	ai_move,	 -4.355, NULL,	// frame 0
	ai_move,	-12.373, NULL,	// frame 1
	ai_move,	 -4.930, NULL,	// frame 2
	ai_move,	 -2.820, NULL,	// frame 3
	ai_move,	 -7.905, NULL,	// frame 4
	ai_move,	-12.099, NULL,	// frame 5
	ai_move,	 -4.754, NULL,	// frame 6
	ai_move,	 -3.771, NULL,	// frame 7
	ai_move,	  1.005, NULL,	// frame 8
	ai_move,	 -0.313, NULL,	// frame 9
	ai_move,	  0.516, NULL,	// frame 10
	ai_move,	 -0.092, NULL,	// frame 11
	ai_move,	 -0.086, NULL,	// frame 12
	ai_move,	 -0.042, NULL,	// frame 13
	ai_move,	  0.032, NULL,	// frame 14
	ai_move,	 -0.026, NULL,	// frame 15
	ai_move,	  0.008, NULL,	// frame 16
	ai_move,	  0.017, NULL,	// frame 17
	ai_move,	 -0.003, NULL,	// frame 18
};
mmove_t	punk_move_death1 = {FRAME_death1_01, FRAME_death1_19, punk_frames_death1, AI_EndDeath};

mframe_t	punk_frames_death2[] = 
{
	ai_move,	 -5.523, NULL,	// frame 0
	ai_move,	-12.982, NULL,	// frame 1
	ai_move,	 -5.191, NULL,	// frame 2
	ai_move,	-12.765, NULL,	// frame 3
	ai_move,	-12.250, NULL,	// frame 4
	ai_move,	 -6.917, NULL,	// frame 5
	ai_move,	 -7.750, NULL,	// frame 6
	ai_move,	  0.493, NULL,	// frame 7
	ai_move,	  2.456, NULL,	// frame 8
	ai_move,	  0.524, NULL,	// frame 9
	ai_move,	  3.357, NULL,	// frame 10
	ai_move,	  1.128, NULL,	// frame 11
	ai_move,	 -0.663, NULL,	// frame 12
	ai_move,	 -0.169, NULL,	// frame 13
	ai_move,	 -0.012, NULL,	// frame 14
	ai_move,	 -0.017, NULL,	// frame 15
};
mmove_t	punk_move_death2 = {FRAME_death2_01, FRAME_death2_16, punk_frames_death2, AI_EndDeath};

mframe_t	punk_frames_death3[] = 
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
	ai_move,	  0.000, NULL,	// frame 19
	ai_move,	  0.000, NULL,	// frame 20
	ai_move,	  0.000, NULL,	// frame 21
	ai_move,	  0.000, NULL,	// frame 22
	ai_move,	  0.000, NULL,	// frame 23
	ai_move,	  0.000, NULL,	// frame 24
	ai_move,	  0.000, NULL,	// frame 25
	ai_move,	  0.000, NULL,	// frame 26
	ai_move,	  0.000, NULL,	// frame 27
};
mmove_t	punk_move_death3 = {FRAME_death3_01, FRAME_death3_28, punk_frames_death3, AI_EndDeath};

mframe_t	punk_frames_death4[] = 
{
	ai_move,	 -0.476, NULL,	// frame 0
	ai_move,	-15.310, NULL,	// frame 1
	ai_move,	 -5.952, NULL,	// frame 2
	ai_move,	 -7.488, NULL,	// frame 3
	ai_move,	-18.312, NULL,	// frame 4
	ai_move,	 -2.110, NULL,	// frame 5
	ai_move,	-11.255, NULL,	// frame 6
	ai_move,	 -1.091, NULL,	// frame 7
	ai_move,	  0.135, NULL,	// frame 8
	ai_move,	 -0.201, NULL,	// frame 9
	ai_move,	 -0.217, NULL,	// frame 10
	ai_move,	  0.002, NULL,	// frame 11
	ai_move,	  0.008, NULL,	// frame 12
};
mmove_t	punk_move_death4 = {FRAME_death4_01, FRAME_death4_13, punk_frames_death4, AI_EndDeath};

mframe_t	punk_frames_crh_shuf[] = 
{
	ai_run,	 -0.364, NULL,	// frame 0
	ai_run,	 15.133, NULL,	// frame 1
	ai_run,	  7.529, NULL,	// frame 2
	ai_run,	 11.337, NULL,	// frame 3
	ai_run,	 20.832, NULL,	// frame 4
};
mmove_t	punk_move_crh_shuf = {FRAME_crh_shuf_01, FRAME_crh_shuf_05, punk_frames_crh_shuf, NULL};

mframe_t	punk_frames_crouch_walk[] = 
{
	ai_run,	  5.383, NULL,	// frame 0
	ai_run,	  5.466, NULL,	// frame 1
	ai_run,	  3.693, NULL,	// frame 2
	ai_run,	  5.865, NULL,	// frame 3
	ai_run,	 13.852, NULL,	// frame 4
	ai_run,	  6.698, NULL,	// frame 5
	ai_run,	  3.743, NULL,	// frame 6
};
mmove_t	punk_move_crouch_walk = {FRAME_crouch_walk_01, FRAME_crouch_walk_07, punk_frames_crouch_walk, NULL};

mframe_t	punk_frames_crouch_painC[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
};
mmove_t	punk_move_crouch_painC = {FRAME_crouch_painC_01, FRAME_crouch_painC_07, punk_frames_crouch_painC, AI_EndAttack};

mframe_t	punk_frames_crouch_painL[] = 
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
mmove_t	punk_move_crouch_painL = {FRAME_crouch_painL_01, FRAME_crouch_painL_08, punk_frames_crouch_painL, AI_EndAttack};

mframe_t	punk_frames_crouch_painR[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
};
mmove_t	punk_move_crouch_painR = {FRAME_crouch_painR_01, FRAME_crouch_painR_07, punk_frames_crouch_painR, AI_EndAttack};

mframe_t	punk_frames_crouch_shoot[] = 
{
	ai_turn,	  0.000, punk_firegun,	// frame 0
	ai_turn,	  0.000, punk_firegun_cr,	// frame 1
	ai_turn,	  0.000, punk_firegun_cr,	// frame 2
	ai_turn,	  0.000, punk_firegun_cr,	// frame 3
	ai_turn,	  0.000, punk_firegun_cr,	// frame 4
	ai_turn,	  0.000, punk_firegun_cr,	// frame 5
};
mmove_t	punk_move_crouch_shoot = {FRAME_crouch_shoot_01, FRAME_crouch_shoot_06, punk_frames_crouch_shoot, AI_EndAttack};

mframe_t	punk_frames_crch_shg_sht[] = 
{
	ai_turn,	  0.000, punk_firegun,	// frame 0
	ai_turn,	  0.000, NULL,	// frame 1
	ai_turn,	  0.000, NULL,	// frame 2
	ai_turn,	  0.000, NULL,	// frame 3
	ai_turn,	  0.000, NULL,	// frame 4
	ai_turn,	  0.000, NULL,	// frame 5
	ai_turn,	  0.000, NULL,	// frame 6
	ai_turn,	  0.000, punk_shotgun_reload,	// frame 7
	ai_turn,	  0.000, NULL,	// frame 8
	ai_turn,	  0.000, NULL,	// frame 9
	ai_turn,	  0.000, NULL,	// frame 10
	ai_turn,	  0.000, NULL,	// frame 11
	ai_turn,	  0.000, NULL,	// frame 12
};
mmove_t	punk_move_crch_shg_sht = {FRAME_crch_shg_sht_01, FRAME_crch_shg_sht_13, punk_frames_crch_shg_sht, AI_EndAttack};

mframe_t	punk_frames_crouch_stand_down[] = 
{
	NULL,	  0.000, NULL,	// frame 0
	NULL,	  0.000, NULL,	// frame 1
	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
	NULL,	  0.000, NULL,	// frame 4
};
mmove_t	punk_move_crouch_stand_down = {FRAME_stand_crouch_01, FRAME_stand_crouch_05, punk_frames_crouch_stand_down, AI_End_CrouchStand_Down};

mframe_t	punk_frames_crouch_stand_up[] = 
{
	NULL,	  0.000, NULL,	// frame 0
	NULL,	  0.000, NULL,	// frame 1
	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
	NULL,	  0.000, NULL,	// frame 4
};
mmove_t	punk_move_crouch_stand_up = {FRAME_stand_crouch_05, FRAME_stand_crouch_01, punk_frames_crouch_stand_up, AI_End_CrouchStand_Up};

mframe_t	punk_frames_crch_astand[] = 
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
};
mmove_t	punk_move_crch_astand = {FRAME_crch_astand_01, FRAME_crch_astand_20, punk_frames_crch_astand, NULL};

mframe_t	punk_frames_crouch_death[] = 
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
};
mmove_t	punk_move_crouch_death = {FRAME_crouch_death_01, FRAME_crouch_death_12, punk_frames_crouch_death, AI_EndDeath};

/*
mframe_t	punk_frames_st_clmb[] = 
{
	ai_stand,	  0.000, NULL,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
};
mmove_t	punk_move_st_clmb = {FRAME_st_clmb_01, FRAME_st_clmb_02, punk_frames_st_clmb, NULL};
*/

mframe_t	punk_frames_clmb_loop[] = 
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
mmove_t	punk_move_clmb_loop = {FRAME_clmb_loop_01, FRAME_clmb_loop_09, punk_frames_clmb_loop, NULL};

mframe_t	punk_frames_clmb_over[] = 
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
mmove_t	punk_move_clmb_over = {FRAME_clmb_over_01, FRAME_clmb_over_10, punk_frames_clmb_over, AI_EndJump};
/*
mframe_t	punk_frames_lside_step[] = 
{
	ai_sidestep,	  0.215, NULL,	// frame 0
	ai_sidestep,	  0.721, NULL,	// frame 1
	ai_sidestep,	  2.871, NULL,	// frame 2
	ai_sidestep,	  4.372, NULL,	// frame 3
	ai_sidestep,	  2.453, NULL,	// frame 4
	ai_sidestep,	  2.358, NULL,	// frame 5
	ai_sidestep,	 -0.671, NULL,	// frame 6
};
mmove_t	punk_move_lside_step = {FRAME_lside_step_01, FRAME_lside_step_07, punk_frames_lside_step, NULL};

mframe_t	punk_frames_rside_step[] = 
{
	ai_sidestep,	   0.676, NULL,	// frame 0
	ai_sidestep,	  -0.261, NULL,	// frame 1
	ai_sidestep,	  -1.790, NULL,	// frame 2
	ai_sidestep,	  -1.300, NULL,	// frame 3
	ai_sidestep,	  -2.096, NULL,	// frame 4
	ai_sidestep,	  -3.586, NULL,	// frame 5
	ai_sidestep,	  -3.024, NULL,	// frame 6
};
mmove_t	punk_move_rside_step = {FRAME_rside_step_01, FRAME_rside_step_07, punk_frames_rside_step, NULL};
*/

mframe_t	punk_frames_lside_step[] = 
{
	ai_sidestep,	 -0.215, NULL,	// frame 0
	ai_sidestep,	 -0.721, NULL,	// frame 1
	ai_sidestep,	 -2.871, NULL,	// frame 2
	ai_sidestep,	 -4.372, NULL,	// frame 3
	ai_sidestep,	 -2.453, NULL,	// frame 4
	ai_sidestep,	 -2.358, NULL,	// frame 5
	ai_sidestep,	  0.671, NULL,	// frame 6
};
mmove_t	punk_move_lside_step = {FRAME_lside_step_01, FRAME_lside_step_07, punk_frames_lside_step, AI_EndAttack};

mframe_t	punk_frames_rside_step[] = 
{
	ai_sidestep,	-0.676, NULL,	// frame 0
	ai_sidestep,	 0.261, NULL,	// frame 1
	ai_sidestep,	 1.790, NULL,	// frame 2
	ai_sidestep,	 1.300, NULL,	// frame 3
	ai_sidestep,	 2.096, NULL,	// frame 4
	ai_sidestep,	 3.586, NULL,	// frame 5
	ai_sidestep,	 3.024, NULL,	// frame 6
};
mmove_t	punk_move_rside_step = {FRAME_rside_step_01, FRAME_rside_step_07, punk_frames_rside_step, AI_EndAttack};


mframe_t	punk_frames_walk_nw[] = 
{
	ai_run,	  9.849, NULL,	// frame 0
	ai_run,	 -1.401, NULL,	// frame 1
	ai_run,	  8.203, AI_EndRun,	// frame 2
	ai_run,	  7.614, NULL,	// frame 3
	ai_run,	  6.068, NULL,	// frame 4
	ai_run,	  7.790, NULL,	// frame 5
	ai_run,	 13.569, AI_EndRun,	// frame 6
	ai_run,	 10.150, NULL,	// frame 7
	ai_run,	  8.247, NULL,	// frame 8
	ai_run,	  6.745, NULL,	// frame 9
};
mmove_t	punk_move_walk_nw = {FRAME_walk_nw_01, FRAME_walk_nw_10, punk_frames_walk_nw, AI_EndRun};

mframe_t	punk_frames_walk_tg_sht[] = 
{
	ai_turn,	  11.306, punk_firegun,	// frame 0
	ai_turn,	   6.486, punk_firegun,	// frame 1
	ai_turn,	   6.159, punk_firegun,	// frame 2
	ai_turn,	   9.146, punk_firegun,	// frame 3
	ai_turn,	   9.527, punk_firegun,	// frame 4
	ai_turn,	   8.850, punk_firegun,	// frame 5
	ai_turn,	   8.214, punk_firegun,	// frame 6
	ai_turn,	   6.377, punk_firegun,	// frame 7
	ai_turn,	   5.029, punk_firegun,	// frame 8
	ai_turn,	   5.740, punk_firegun,	// frame 9
};
mmove_t	punk_move_walk_tg_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, punk_frames_walk_tg_sht, AI_EndAttack};

mframe_t	punk_frames_walk_hmg_sht[] = 
{
	ai_turn,	  11.306, punk_firegun,	// frame 0
	ai_turn,	   6.486, NULL,	// frame 1
	ai_turn,	   6.159, punk_firegun,	// frame 2
	ai_turn,	   9.146, NULL,	// frame 3
	ai_turn,	   9.527, punk_firegun,	// frame 4
	ai_turn,	   8.850, NULL,	// frame 5
	ai_turn,	   8.214, NULL,	// frame 6
	ai_turn,	   6.377, NULL,	// frame 7
	ai_turn,	   5.029, NULL,	// frame 8
	ai_turn,	   5.740, NULL,	// frame 9
};
mmove_t	punk_move_walk_hmg_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, punk_frames_walk_hmg_sht, AI_EndAttack};

mframe_t	punk_frames_walk_bazooka_sht[] = 
{
	ai_turn,	  11.306, punk_firegun,	// frame 0
	ai_turn,	   6.486, NULL,	// frame 1
	ai_turn,	   6.159, NULL,	// frame 2
	ai_turn,	   9.146, NULL,	// frame 3
	ai_turn,	   9.527, NULL,	// frame 4
	ai_turn,	   8.850, NULL,	// frame 5
	ai_turn,	   8.214, NULL,	// frame 6
	ai_turn,	   6.377, NULL,	// frame 7
	ai_turn,	   5.029, NULL,	// frame 8
	ai_turn,	   5.740, NULL,	// frame 9
};
mmove_t	punk_move_walk_bazooka_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, punk_frames_walk_bazooka_sht, AI_EndAttack};

mframe_t	punk_frames_walk_grenade_sht[] = 
{
	ai_turn,	  11.306, punk_firegun,	// frame 0
	ai_turn,	   6.486, NULL,	// frame 1
	ai_turn,	   6.159, NULL,	// frame 2
	ai_turn,	   9.146, NULL,	// frame 3
	ai_turn,	   9.527, NULL,	// frame 4
	ai_turn,	   8.850, NULL,	// frame 5
	ai_turn,	   8.214, NULL,	// frame 6
	ai_turn,	   6.377, NULL,	// frame 7
	ai_turn,	   5.029, NULL,	// frame 8
	ai_turn,	   5.740, NULL,	// frame 9
};
mmove_t	punk_move_walk_grenade_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, punk_frames_walk_grenade_sht, AI_EndAttack};

mframe_t	punk_frames_walk_flamegun_sht[] = 
{
	ai_turn,	  11.306, punk_firegun,	// frame 0
	ai_turn,	   6.486, punk_firegun,	// frame 1
	ai_turn,	   6.159, punk_firegun,	// frame 2
	ai_turn,	   9.146, punk_firegun,	// frame 3
	ai_turn,	   9.527, punk_firegun,	// frame 4
	ai_turn,	   8.850, punk_firegun,	// frame 5
	ai_turn,	   8.214, punk_firegun,	// frame 6
	ai_turn,	   6.377, punk_firegun,	// frame 7
	ai_turn,	   5.029, punk_firegun,	// frame 8
	ai_turn,	   5.740, punk_firegun,	// frame 9
};
mmove_t	punk_move_walk_flamegun_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, punk_frames_walk_flamegun_sht, AI_EndAttack};


mframe_t	punk_frames_walk_shg_sht[] = 
{
	ai_turn,	 13.194, punk_firegun,	// frame 0
	ai_turn,	  3.697, NULL,	// frame 1
	ai_turn,	  9.794, NULL,	// frame 2
	ai_turn,	  9.688, NULL,	// frame 3
	ai_turn,	  8.709, NULL,	// frame 4
	ai_turn,	  9.221, punk_shotgun_reload,	// frame 5
	ai_turn,	  7.405, NULL,	// frame 6
	ai_turn,	  7.594, NULL,	// frame 7
	ai_turn,	  2.303, NULL,	// frame 8
	ai_turn,	  5.228, NULL,	// frame 9
};
mmove_t	punk_move_walk_shg_sht = {FRAME_walk_shg_sht_01, FRAME_walk_shg_sht_10, punk_frames_walk_shg_sht, AI_EndAttack};

mframe_t	punk_frames_walk_gdown[] = 
{
	ai_run,	    3.636, NULL,	// frame 0
	ai_run,	    6.504, NULL,	// frame 1
	ai_run,	    3.111, NULL,	// frame 2
	ai_run,	    4.200, AI_EndRun,	// frame 3
	ai_run,	    8.913, NULL,	// frame 4
	ai_run,	    7.640, NULL,	// frame 5
	ai_run,	   11.360, AI_EndRun,	// frame 6
	ai_run,	    4.233, NULL,	// frame 7
	ai_run,	   12.047, NULL,	// frame 8
	ai_run,	   10.356, NULL,	// frame 9
};
mmove_t	punk_move_walk_gdown = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, punk_frames_walk_gdown, AI_EndRun};

mframe_t	punk_frames_run_nw[] = 
{
	ai_run,	 26.748, NULL,	// frame 0
	ai_run,	 17.188, NULL,	// frame 1
	ai_run,	 31.486, NULL,	// frame 2
	ai_run,	 31.052, NULL,	// frame 3
	ai_run,	 23.944, NULL,	// frame 4
	ai_run,	 24.549, NULL,	// frame 5
};
mmove_t	punk_move_run_nw = {FRAME_run_nw_01, FRAME_run_nw_06, punk_frames_run_nw, AI_EndRun};

mframe_t	punk_frames_run_tg_sht[] = 
{
	ai_charge,	 27.656, punk_firegun,	// frame 0
	ai_charge,	 17.929, NULL,	// frame 1
	ai_charge,	 33.470, punk_firegun,	// frame 2
	ai_charge,	 37.084, NULL,	// frame 3
	ai_charge,	 31.857, punk_firegun,	// frame 4
	ai_charge,	 24.969, NULL,	// frame 5
};
mmove_t	punk_move_run_tg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_tg_sht, AI_EndAttack};

mframe_t	punk_frames_run_reverse_tg_sht[] = 
{
	ai_charge,-	 24.969, punk_firegun,	// frame 5
	ai_charge,-	 31.857, NULL,	// frame 4
	ai_charge,-	 37.084, punk_firegun,	// frame 3
	ai_charge,-	 33.470, NULL,	// frame 2
	ai_charge,-	 17.929, punk_firegun,	// frame 1
	ai_charge,-	 27.656, NULL,	// frame 0
};
mmove_t	punk_move_run_reverse_tg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_reverse_tg_sht, AI_EndAttack};


mframe_t	punk_frames_run_hmg_sht[] = 
{
	ai_charge,	 27.656, punk_firegun,	// frame 0
	ai_charge,	 17.929, NULL,	// frame 1
	ai_charge,	 33.470, punk_firegun,	// frame 2
	ai_charge,	 37.084, NULL,	// frame 3
	ai_charge,	 31.857, punk_firegun,	// frame 4
	ai_charge,	 24.969, NULL,	// frame 5
};
mmove_t	punk_move_run_hmg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_hmg_sht, AI_EndAttack};

mframe_t	punk_frames_run_reverse_hmg_sht[] = 
{
	ai_charge,-	 24.969, punk_firegun,	// frame 5
	ai_charge,-	 31.857, NULL,	// frame 4
	ai_charge,-	 37.084, punk_firegun,	// frame 3
	ai_charge,-	 33.470, NULL,	// frame 2
	ai_charge,-	 17.929, punk_firegun,	// frame 1
	ai_charge,-	 27.656, NULL,	// frame 0
};
mmove_t	punk_move_run_reverse_hmg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_reverse_hmg_sht, AI_EndAttack};


mframe_t	punk_frames_run_bazooka_sht[] = 
{
	ai_charge,	 27.656, punk_firegun,	// frame 0
	ai_charge,	 17.929, NULL,	// frame 1
	ai_charge,	 33.470, NULL,	// frame 2
	ai_charge,	 37.084, NULL,	// frame 3
	ai_charge,	 31.857, NULL,	// frame 4
	ai_charge,	 24.969, NULL,	// frame 5
};
mmove_t	punk_move_run_bazooka_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_bazooka_sht, AI_EndAttack};

mframe_t	punk_frames_run_reverse_bazooka_sht[] = 
{
	ai_charge,-	 24.969, punk_firegun,	// frame 5
	ai_charge,-	 31.857, NULL,	// frame 4
	ai_charge,-	 37.084, NULL,	// frame 3
	ai_charge,-	 33.470, NULL,	// frame 2
	ai_charge,-	 17.929, NULL,	// frame 1
	ai_charge,-	 27.656, NULL,	// frame 0
};
mmove_t	punk_move_run_reverse_bazooka_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_reverse_bazooka_sht, AI_EndAttack};


mframe_t	punk_frames_run_grenade_sht[] = 
{
	ai_charge,	 27.656, punk_firegun,	// frame 0
	ai_charge,	 17.929, NULL,	// frame 1
	ai_charge,	 33.470, NULL,	// frame 2
	ai_charge,	 37.084, NULL,	// frame 3
	ai_charge,	 31.857, NULL,	// frame 4
	ai_charge,	 24.969, NULL,	// frame 5
};
mmove_t	punk_move_run_grenade_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_grenade_sht, AI_EndAttack};

mframe_t	punk_frames_run_reverse_grenade_sht[] = 
{
	ai_charge,-	 24.969, punk_firegun,	// frame 5
	ai_charge,-	 31.857, NULL,	// frame 4
	ai_charge,-	 37.084, NULL,	// frame 3
	ai_charge,-	 33.470, NULL,	// frame 2
	ai_charge,-	 17.929, NULL,	// frame 1
	ai_charge,-	 27.656, NULL,	// frame 0
};
mmove_t	punk_move_run_reverse_grenade_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_reverse_grenade_sht, AI_EndAttack};


mframe_t	punk_frames_run_flamegun_sht[] = 
{
	ai_charge,	 27.656, punk_firegun,	// frame 0
	ai_charge,	 17.929, punk_firegun,	// frame 1
	ai_charge,	 33.470, punk_firegun,	// frame 2
	ai_charge,	 37.084, punk_firegun,	// frame 3
	ai_charge,	 31.857, punk_firegun,	// frame 4
	ai_charge,	 24.969, punk_firegun,	// frame 5
};
mmove_t	punk_move_run_flamegun_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_flamegun_sht, AI_EndAttack};

mframe_t	punk_frames_run_reverse_flamegun_sht[] = 
{
	ai_charge,-	 24.969, punk_firegun,	// frame 5
	ai_charge,-	 31.857, punk_firegun,	// frame 4
	ai_charge,-	 37.084, punk_firegun,	// frame 3
	ai_charge,-	 33.470, punk_firegun,	// frame 2
	ai_charge,-	 17.929, punk_firegun,	// frame 1
	ai_charge,-	 27.656, punk_firegun,	// frame 0
};
mmove_t	punk_move_run_reverse_flamegun_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, punk_frames_run_reverse_flamegun_sht, AI_EndAttack};


mframe_t	punk_frames_run_shg_sht[] = 
{
	ai_charge,	 25.263, punk_firegun,	// frame 0
	ai_charge,	 15.586, NULL,	// frame 1
	ai_charge,	 37.674, NULL,	// frame 2
	ai_charge,	 32.187, punk_shotgun_reload,	// frame 3
	ai_charge,	 33.081, NULL,	// frame 4
	ai_charge,	 30.137, NULL,	// frame 5
};
mmove_t	punk_move_run_shg_sht = {FRAME_run_shg_sht_01, FRAME_run_shg_sht_06, punk_frames_run_shg_sht, AI_EndAttack};

mframe_t	punk_frames_run_gun_down[] = 
{
	ai_run,	 26.748, NULL,	// frame 0
	ai_run,	 17.188, NULL,	// frame 1
	ai_run,	 31.486, NULL,	// frame 2
	ai_run,	 31.052, NULL,	// frame 3
	ai_run,	 23.944, NULL,	// frame 4
	ai_run,	 24.549, NULL,	// frame 5
};
mmove_t	punk_move_run_gun_down = {FRAME_run_gun_down_01, FRAME_run_gun_down_06, punk_frames_run_gun_down, AI_EndRun};

mframe_t	punk_frames_run_on_fire[] = 
{
	ai_onfire_run,	26.846, NULL,	// frame 0
	ai_onfire_run,	20.973, NULL,	// frame 1
	ai_onfire_run,	44.080, NULL,	// frame 2
	ai_onfire_run,	30.029, NULL,	// frame 3
	ai_onfire_run,	25.538, NULL,	// frame 4
	ai_onfire_run,	26.007, NULL,	// frame 5
};
mmove_t	punk_move_run_on_fire = {FRAME_run_on_fire_01, FRAME_run_on_fire_06, punk_frames_run_on_fire, NULL};

mframe_t	punk_frames_lsd_tg_run[] = 
{
	ai_sidestep,-	23.733*0.75, punk_firegun_left,	// frame 0
	ai_sidestep,-	18.601*0.75, punk_firegun_left,	// frame 1
	ai_sidestep,-   31.336*0.75, punk_firegun_left,	// frame 2
	ai_sidestep,-   39.244*0.75, punk_firegun_left,	// frame 3
	ai_sidestep,-   26.961*0.75, punk_firegun_left,	// frame 4
	ai_sidestep,-   23.858*0.75, punk_firegun_left,	// frame 5
};
mmove_t	punk_move_lsd_tg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, punk_frames_lsd_tg_run, NULL};

mframe_t	punk_frames_rsd_tg_run[] = 
{
	ai_sidestep,	  19.829*0.75, punk_firegun_right,	// frame 0
	ai_sidestep,	  17.364*0.75, punk_firegun_right,	// frame 1
	ai_sidestep,	  32.611*0.75, punk_firegun_right,	// frame 2
	ai_sidestep,	  37.973*0.75, punk_firegun_right,	// frame 3
	ai_sidestep,	  32.279*0.75, punk_firegun_right,	// frame 4
	ai_sidestep,	  24.741*0.75, punk_firegun_right,	// frame 5
};
mmove_t	punk_move_rsd_tg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, punk_frames_rsd_tg_run, NULL};


mframe_t	punk_frames_lsd_hmg_run[] = 
{
	ai_sidestep,-	23.733*0.75, punk_firegun_left,	// frame 0
	ai_sidestep,-	18.601*0.75, NULL,	// frame 1
	ai_sidestep,-   31.336*0.75, punk_firegun,	// frame 2
	ai_sidestep,-   39.244*0.75, NULL,	// frame 3
	ai_sidestep,-   26.961*0.75, punk_firegun,	// frame 4
	ai_sidestep,-   23.858*0.75, NULL,	// frame 5
};
mmove_t	punk_move_lsd_hmg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, punk_frames_lsd_hmg_run, NULL};

mframe_t	punk_frames_rsd_hmg_run[] = 
{
	ai_sidestep,	  19.829*0.75, punk_firegun_right,	// frame 0
	ai_sidestep,	  17.364*0.75, NULL,	// frame 1
	ai_sidestep,	  32.611*0.75, punk_firegun,	// frame 2
	ai_sidestep,	  37.973*0.75, NULL,	// frame 3
	ai_sidestep,	  32.279*0.75, punk_firegun,	// frame 4
	ai_sidestep,	  24.741*0.75, NULL,	// frame 5
};
mmove_t	punk_move_rsd_hmg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, punk_frames_rsd_hmg_run, NULL};


mframe_t	punk_frames_lsd_bazooka_run[] = 
{
	ai_sidestep,-	23.733*0.75, punk_firegun_left,	// frame 0
	ai_sidestep,-	18.601*0.75, NULL,	// frame 1
	ai_sidestep,-   31.336*0.75, NULL,	// frame 2
	ai_sidestep,-   39.244*0.75, NULL,	// frame 3
	ai_sidestep,-   26.961*0.75, NULL,	// frame 4
	ai_sidestep,-   23.858*0.75, NULL,	// frame 5
};
mmove_t	punk_move_lsd_bazooka_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, punk_frames_lsd_bazooka_run, NULL};

mframe_t	punk_frames_rsd_bazooka_run[] = 
{
	ai_sidestep,	  19.829*0.75, punk_firegun_right,	// frame 0
	ai_sidestep,	  17.364*0.75, NULL,	// frame 1
	ai_sidestep,	  32.611*0.75, NULL,	// frame 2
	ai_sidestep,	  37.973*0.75, NULL,	// frame 3
	ai_sidestep,	  32.279*0.75, NULL,	// frame 4
	ai_sidestep,	  24.741*0.75, NULL,	// frame 5
};
mmove_t	punk_move_rsd_bazooka_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, punk_frames_rsd_bazooka_run, NULL};


mframe_t	punk_frames_lsd_grenade_run[] = 
{
	ai_sidestep,-	23.733*0.75, punk_firegun_left,	// frame 0
	ai_sidestep,-	18.601*0.75, NULL,	// frame 1
	ai_sidestep,-   31.336*0.75, NULL,	// frame 2
	ai_sidestep,-   39.244*0.75, NULL,	// frame 3
	ai_sidestep,-   26.961*0.75, NULL,	// frame 4
	ai_sidestep,-   23.858*0.75, NULL,	// frame 5
};
mmove_t	punk_move_lsd_grenade_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, punk_frames_lsd_grenade_run, NULL};

mframe_t	punk_frames_rsd_grenade_run[] = 
{
	ai_sidestep,	  19.829*0.75, punk_firegun_right,	// frame 0
	ai_sidestep,	  17.364*0.75, NULL,	// frame 1
	ai_sidestep,	  32.611*0.75, NULL,	// frame 2
	ai_sidestep,	  37.973*0.75, NULL,	// frame 3
	ai_sidestep,	  32.279*0.75, NULL,	// frame 4
	ai_sidestep,	  24.741*0.75, NULL,	// frame 5
};
mmove_t	punk_move_rsd_grenade_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, punk_frames_rsd_grenade_run, NULL};


mframe_t	punk_frames_lsd_flamegun_run[] = 
{
	ai_sidestep,-	23.733*0.75, punk_firegun_left,	// frame 0
	ai_sidestep,-	18.601*0.75, punk_firegun_left,	// frame 1
	ai_sidestep,-   31.336*0.75, punk_firegun_left,	// frame 2
	ai_sidestep,-   39.244*0.75, punk_firegun_left,	// frame 3
	ai_sidestep,-   26.961*0.75, punk_firegun_left,	// frame 4
	ai_sidestep,-   23.858*0.75, punk_firegun_left,	// frame 5
};
mmove_t	punk_move_lsd_flamegun_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, punk_frames_lsd_flamegun_run, NULL};

mframe_t	punk_frames_rsd_flamegun_run[] = 
{
	ai_sidestep,	  19.829*0.75, punk_firegun_right,	// frame 0
	ai_sidestep,	  17.364*0.75, punk_firegun_right,	// frame 1
	ai_sidestep,	  32.611*0.75, punk_firegun_right,	// frame 2
	ai_sidestep,	  37.973*0.75, punk_firegun_right,	// frame 3
	ai_sidestep,	  32.279*0.75, punk_firegun_right,	// frame 4
	ai_sidestep,	  24.741*0.75, punk_firegun_right,	// frame 5
};
mmove_t	punk_move_rsd_flamegun_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, punk_frames_rsd_flamegun_run, NULL};

mframe_t	punk_frames_lsd_shg_run[] = 
{
	ai_sidestep,-	  24.221*0.75, NULL,	// frame 0
	ai_sidestep,-	  20.466*0.75, punk_firegun_left,	// frame 1
	ai_sidestep,-	  32.136*0.75, NULL,	// frame 2
	ai_sidestep,-	  39.252*0.75, punk_shotgun_reload,	// frame 3
	ai_sidestep,-	  29.464*0.75, NULL,	// frame 4
	ai_sidestep,-	  23.279*0.75, NULL,	// frame 5
};
mmove_t	punk_move_lsd_shg_run = {FRAME_rsd_shg_run_01, FRAME_rsd_shg_run_06, punk_frames_lsd_shg_run, NULL};

mframe_t	punk_frames_rsd_shg_run[] = 
{
	ai_sidestep,	  26.812*0.75, NULL,	// frame 0
	ai_sidestep,	  18.773*0.75, punk_firegun_right,	// frame 1
	ai_sidestep,	  34.600*0.75, NULL,	// frame 2
	ai_sidestep,	  36.035*0.75, punk_shotgun_reload,	// frame 3
	ai_sidestep,	  31.354*0.75, NULL,	// frame 4
	ai_sidestep,	  23.697*0.75, NULL,	// frame 5
};
mmove_t	punk_move_rsd_shg_run = {FRAME_lsd_shg_run_01, FRAME_lsd_shg_run_06, punk_frames_rsd_shg_run, NULL};

//================================================================================================================
// created moves
mframe_t	punk_frames_avoid_walk[] = 
{
	ai_turn,	  3.636, NULL,	// frame 0
	ai_turn,	  6.504, NULL,	// frame 1
	ai_turn,	  3.111, NULL,	// frame 2
	ai_turn,	  4.200, NULL,	// frame 3
	ai_turn,	  8.913, NULL,	// frame 4
	ai_turn,	  7.640, NULL,	// frame 5
};
mmove_t	punk_move_avoid_walk = {FRAME_walk_gdown_01, FRAME_walk_gdown_06, punk_frames_avoid_walk, AI_EndAttack};

mframe_t	punk_frames_avoid_crouch_walk[] = 
{
	ai_turn,	  5.383, NULL,	// frame 0
	ai_turn,	  5.466, NULL,	// frame 1
	ai_turn,	  3.693, NULL,	// frame 2
	ai_turn,	  5.865, NULL,	// frame 3
	ai_turn,	 13.852, NULL,	// frame 4
	ai_turn,	  6.698, NULL,	// frame 5
	ai_turn,	  3.743, NULL,	// frame 6
};
mmove_t	punk_move_avoid_crouch_walk = {FRAME_crouch_walk_01, FRAME_crouch_walk_07, punk_frames_avoid_crouch_walk, AI_EndAttack};

mframe_t	punk_frames_walk_gdownFLASHLIGHT[] = 
{
	ai_runFLASHLIGHT,	 12.686, NULL,	// frame 0
	ai_runFLASHLIGHT,	  6.612, NULL,	// frame 1
	ai_runFLASHLIGHT,	  4.302, NULL,	// frame 2
	ai_runFLASHLIGHT,	  8.823, AI_EndRun,	// frame 3
	ai_runFLASHLIGHT,	  7.734, NULL,	// frame 4
	ai_runFLASHLIGHT,	  9.099, NULL,	// frame 5
	ai_runFLASHLIGHT,	  9.405, AI_EndRun,	// frame 6
	ai_runFLASHLIGHT,	  5.060, NULL,	// frame 7
	ai_runFLASHLIGHT,	  4.412, NULL,	// frame 8
	ai_runFLASHLIGHT,	  8.700, NULL,	// frame 9
};
mmove_t	punk_move_walk_gdownFLASHLIGHT = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, punk_frames_walk_gdownFLASHLIGHT, AI_EndRun };

mframe_t	punk_frames_avoid_run[] = 
{
	ai_turn,	 26.748, NULL,	// frame 0
	ai_turn,	 17.188, NULL,	// frame 1
	ai_turn,	 31.486, NULL,	// frame 2
	ai_turn,	 31.052, NULL,	// frame 3
	ai_turn,	 23.944, NULL,	// frame 4
	ai_turn,	 24.549, NULL,	// frame 5	
};
mmove_t	punk_move_avoid_run = {FRAME_run_gun_down_01, FRAME_run_gun_down_06, punk_frames_avoid_run, AI_EndAttack};

mframe_t	punk_frames_avoid_reverse_walk[] = 
{
	ai_turn,	-7.640, NULL,	// frame 5
	ai_turn,	-8.913, NULL,	// frame 4
	ai_turn,	-4.200, NULL,	// frame 3
	ai_turn,	-3.111, NULL,	// frame 2
	ai_turn,	-6.504, NULL,	// frame 1
	ai_turn,	-3.636, NULL,	// frame 0
};
mmove_t	punk_move_avoid_reverse_walk = {FRAME_walk_gdown_06, FRAME_walk_gdown_01, punk_frames_avoid_reverse_walk, AI_EndAttack};

mframe_t	punk_frames_avoid_reverse_run[] = 
{
	ai_turn,	- 24.549, NULL,	// frame 5
	ai_turn,	- 23.944, NULL,	// frame 4
	ai_turn,	- 31.052, NULL,	// frame 3
	ai_turn,	- 31.486, NULL,	// frame 2
	ai_turn,	- 17.188, NULL,	// frame 1
	ai_turn,	- 26.748, NULL,	// frame 0
};
mmove_t	punk_move_avoid_reverse_run = {FRAME_run_gun_down_06, FRAME_run_gun_down_03, punk_frames_avoid_reverse_run, AI_EndAttack};

mframe_t punk_frames_sg_stand[] = 
{
 ai_stand,   0.000, punk_talk_think, // frame 0
 ai_stand,   0.000, punk_talk_think, // frame 1
 ai_stand,   0.000, punk_talk_think, // frame 2
 ai_stand,   0.000, punk_talk_think, // frame 3
 ai_stand,   0.000, punk_talk_think, // frame 4
 ai_stand,   0.000, punk_talk_think, // frame 5
 ai_stand,   0.000, punk_talk_think, // frame 6
 ai_stand,   0.000, punk_talk_think, // frame 7
 ai_stand,   0.000, punk_talk_think, // frame 8
 ai_stand,   0.000, punk_talk_think, // frame 9
 ai_stand,   0.000, punk_talk_think, // frame 10
 ai_stand,   0.000, punk_talk_think, // frame 11
 ai_stand,   0.000, punk_talk_think, // frame 12
 ai_stand,   0.000, punk_talk_think, // frame 13
 ai_stand,   0.000, punk_talk_think, // frame 14
 ai_stand,   0.000, punk_talk_think, // frame 15
 ai_stand,   0.000, punk_talk_think, // frame 16
 ai_stand,   0.000, punk_talk_think, // frame 17
 ai_stand,   0.000, punk_talk_think, // frame 18
 ai_stand,   0.000, punk_talk_think, // frame 19
 ai_stand,   0.000, punk_talk_think, // frame 20
 ai_stand,   0.000, punk_talk_think, // frame 21
 ai_stand,   0.000, punk_talk_think, // frame 22
 ai_stand,   0.000, punk_talk_think, // frame 23
 ai_stand,   0.000, punk_talk_think, // frame 24
 ai_stand,   0.000, punk_talk_think, // frame 25
 ai_stand,   0.000, punk_talk_think, // frame 26
 ai_stand,   0.000, punk_talk_think, // frame 27
 ai_stand,   0.000, punk_talk_think, // frame 28
 ai_stand,   0.000, punk_talk_think, // frame 29
 ai_stand,   0.000, punk_talk_think, // frame 30
};
mmove_t punk_move_sg_stand = {FRAME_sg_stand_01, FRAME_sg_stand_31, punk_frames_sg_stand, punk_end_stand};

mframe_t punk_frames_sg_talk1[] = 
{
 ai_stand,   0.000, punk_talk_think, // frame 0
 ai_stand,   0.000, punk_talk_think, // frame 1
 ai_stand,   0.000, punk_talk_think, // frame 2
 ai_stand,   0.000, punk_talk_think, // frame 3
 ai_stand,   0.000, punk_talk_think, // frame 4
 ai_stand,   0.000, punk_talk_think, // frame 5
 ai_stand,   0.000, punk_talk_think, // frame 6
 ai_stand,   0.000, punk_talk_think, // frame 7
 ai_stand,   0.000, punk_talk_think, // frame 8
 ai_stand,   0.000, punk_talk_think, // frame 9
 ai_stand,   0.000, punk_talk_think, // frame 10
 ai_stand,   0.000, punk_talk_think, // frame 11
 ai_stand,   0.000, punk_talk_think, // frame 12
 ai_stand,   0.000, punk_talk_think, // frame 13
 ai_stand,   0.000, punk_talk_think, // frame 14
 ai_stand,   0.000, punk_talk_think, // frame 15
 ai_stand,   0.000, punk_talk_think, // frame 16
 ai_stand,   0.000, punk_talk_think, // frame 17
 ai_stand,   0.000, punk_talk_think, // frame 18
 ai_stand,   0.000, punk_talk_think, // frame 19
 ai_stand,   0.000, punk_talk_think, // frame 20
 ai_stand,   0.000, punk_talk_think, // frame 21
 ai_stand,   0.000, punk_talk_think, // frame 22
 ai_stand,   0.000, punk_talk_think, // frame 23
 ai_stand,   0.000, punk_talk_think, // frame 24
 ai_stand,   0.000, punk_talk_think, // frame 25
};
mmove_t punk_move_sg_talk1 = {FRAME_sg_talk1_01, FRAME_sg_talk1_26, punk_frames_sg_talk1, punk_end_stand};

mframe_t punk_frames_sg_talk2[] = 
{
 ai_stand,   0.000, punk_talk_think, // frame 0
 ai_stand,   0.000, punk_talk_think, // frame 1
 ai_stand,   0.000, punk_talk_think, // frame 2
 ai_stand,   0.000, punk_talk_think, // frame 3
 ai_stand,   0.000, punk_talk_think, // frame 4
 ai_stand,   0.000, punk_talk_think, // frame 5
 ai_stand,   0.000, punk_talk_think, // frame 6
 ai_stand,   0.000, punk_talk_think, // frame 7
 ai_stand,   0.000, punk_talk_think, // frame 8
 ai_stand,   0.000, punk_talk_think, // frame 9
 ai_stand,   0.000, punk_talk_think, // frame 10
 ai_stand,   0.000, punk_talk_think, // frame 11
 ai_stand,   0.000, punk_talk_think, // frame 12
 ai_stand,   0.000, punk_talk_think, // frame 13
 ai_stand,   0.000, punk_talk_think, // frame 14
 ai_stand,   0.000, punk_talk_think, // frame 15
 ai_stand,   0.000, punk_talk_think, // frame 16
 ai_stand,   0.000, punk_talk_think, // frame 17
 ai_stand,   0.000, punk_talk_think, // frame 18
 ai_stand,   0.000, punk_talk_think, // frame 19
};
mmove_t punk_move_sg_talk2 = {FRAME_sg_talk2_01, FRAME_sg_talk2_20, punk_frames_sg_talk2, punk_end_stand};

mframe_t punk_frames_sg_talk3[] = 
{
 ai_stand,   0.000, punk_talk_think, // frame 0
 ai_stand,   0.000, punk_talk_think, // frame 1
 ai_stand,   0.000, punk_talk_think, // frame 2
 ai_stand,   0.000, punk_talk_think, // frame 3
 ai_stand,   0.000, punk_talk_think, // frame 4
 ai_stand,   0.000, punk_talk_think, // frame 5
 ai_stand,   0.000, punk_talk_think, // frame 6
 ai_stand,   0.000, punk_talk_think, // frame 7
 ai_stand,   0.000, punk_talk_think, // frame 8
 ai_stand,   0.000, punk_talk_think, // frame 9
 ai_stand,   0.000, punk_talk_think, // frame 10
 ai_stand,   0.000, punk_talk_think, // frame 11
 ai_stand,   0.000, punk_talk_think, // frame 12
 ai_stand,   0.000, punk_talk_think, // frame 13
 ai_stand,   0.000, punk_talk_think, // frame 14
 ai_stand,   0.000, punk_talk_think, // frame 15
 ai_stand,   0.000, punk_talk_think, // frame 16
 ai_stand,   0.000, punk_talk_think, // frame 17
 ai_stand,   0.000, punk_talk_think, // frame 18
 ai_stand,   0.000, punk_talk_think, // frame 19
 ai_stand,   0.000, punk_talk_think, // frame 20
};
mmove_t punk_move_sg_talk3 = {FRAME_sg_talk3_01, FRAME_sg_talk3_21, punk_frames_sg_talk3, punk_end_stand};

mframe_t punk_frames_sg_talk4[] = 
{
 ai_stand,   0.000, punk_talk_think, // frame 0
 ai_stand,   0.000, punk_talk_think, // frame 1
 ai_stand,   0.000, punk_talk_think, // frame 2
 ai_stand,   0.000, punk_talk_think, // frame 3
 ai_stand,   0.000, punk_talk_think, // frame 4
 ai_stand,   0.000, punk_talk_think, // frame 5
 ai_stand,   0.000, punk_talk_think, // frame 6
 ai_stand,   0.000, punk_talk_think, // frame 7
 ai_stand,   0.000, punk_talk_think, // frame 8
 ai_stand,   0.000, punk_talk_think, // frame 9
 ai_stand,   0.000, punk_talk_think, // frame 10
 ai_stand,   0.000, punk_talk_think, // frame 11
 ai_stand,   0.000, punk_talk_think, // frame 12
 ai_stand,   0.000, punk_talk_think, // frame 13
 ai_stand,   0.000, punk_talk_think, // frame 14
 ai_stand,   0.000, punk_talk_think, // frame 15
 ai_stand,   0.000, punk_talk_think, // frame 16
 ai_stand,   0.000, punk_talk_think, // frame 17
 ai_stand,   0.000, punk_talk_think, // frame 18
 ai_stand,   0.000, punk_talk_think, // frame 19
 ai_stand,   0.000, punk_talk_think, // frame 20
 ai_stand,   0.000, punk_talk_think, // frame 21
 ai_stand,   0.000, punk_talk_think, // frame 22
 ai_stand,   0.000, punk_talk_think, // frame 23
 ai_stand,   0.000, punk_talk_think, // frame 24
 ai_stand,   0.000, punk_talk_think, // frame 25
 ai_stand,   0.000, punk_talk_think, // frame 26
 ai_stand,   0.000, punk_talk_think, // frame 27
 ai_stand,   0.000, punk_talk_think, // frame 28
 ai_stand,   0.000, punk_talk_think, // frame 29
 ai_stand,   0.000, punk_talk_think, // frame 30
 ai_stand,   0.000, punk_talk_think, // frame 31
 ai_stand,   0.000, punk_talk_think, // frame 32
};
mmove_t punk_move_sg_talk4 = {FRAME_sg_talk4_01, FRAME_sg_talk4_33, punk_frames_sg_talk4, punk_end_stand};

mframe_t punk_frames_sg_talk5[] = 
{
 ai_stand,   0.000, punk_talk_think, // frame 0
 ai_stand,   0.000, punk_talk_think, // frame 1
 ai_stand,   0.000, punk_talk_think, // frame 2
 ai_stand,   0.000, punk_talk_think, // frame 3
 ai_stand,   0.000, punk_talk_think, // frame 4
 ai_stand,   0.000, punk_talk_think, // frame 5
 ai_stand,   0.000, punk_talk_think, // frame 6
 ai_stand,   0.000, punk_talk_think, // frame 7
 ai_stand,   0.000, punk_talk_think, // frame 8
 ai_stand,   0.000, punk_talk_think, // frame 9
 ai_stand,   0.000, punk_talk_think, // frame 10
 ai_stand,   0.000, punk_talk_think, // frame 11
 ai_stand,   0.000, punk_talk_think, // frame 12
 ai_stand,   0.000, punk_talk_think, // frame 13
 ai_stand,   0.000, punk_talk_think, // frame 14
 ai_stand,   0.000, punk_talk_think, // frame 15
 ai_stand,   0.000, punk_talk_think, // frame 16
 ai_stand,   0.000, punk_talk_think, // frame 17
 ai_stand,   0.000, punk_talk_think, // frame 18
 ai_stand,   0.000, punk_talk_think, // frame 19
 ai_stand,   0.000, punk_talk_think, // frame 20
 ai_stand,   0.000, punk_talk_think, // frame 21
 ai_stand,   0.000, punk_talk_think, // frame 22
 ai_stand,   0.000, punk_talk_think, // frame 23
 ai_stand,   0.000, punk_talk_think, // frame 24
 ai_stand,   0.000, punk_talk_think, // frame 25
 ai_stand,   0.000, punk_talk_think, // frame 26
 ai_stand,   0.000, punk_talk_think, // frame 27
 ai_stand,   0.000, punk_talk_think, // frame 28
};
mmove_t punk_move_sg_talk5 = {FRAME_sg_talk5_01, FRAME_sg_talk5_29, punk_frames_sg_talk5, punk_end_stand};

mframe_t punk_frames_sg_talk6[] = 
{
 ai_stand,   0.000, punk_talk_think, // frame 0
 ai_stand,   0.000, punk_talk_think, // frame 1
 ai_stand,   0.000, punk_talk_think, // frame 2
 ai_stand,   0.000, punk_talk_think, // frame 3
 ai_stand,   0.000, punk_talk_think, // frame 4
 ai_stand,   0.000, punk_talk_think, // frame 5
 ai_stand,   0.000, punk_talk_think, // frame 6
 ai_stand,   0.000, punk_talk_think, // frame 7
 ai_stand,   0.000, punk_talk_think, // frame 8
 ai_stand,   0.000, punk_talk_think, // frame 9
 ai_stand,   0.000, punk_talk_think, // frame 10
 ai_stand,   0.000, punk_talk_think, // frame 11
 ai_stand,   0.000, punk_talk_think, // frame 12
 ai_stand,   0.000, punk_talk_think, // frame 13
 ai_stand,   0.000, punk_talk_think, // frame 14
 ai_stand,   0.000, punk_talk_think, // frame 15
 ai_stand,   0.000, punk_talk_think, // frame 16
 ai_stand,   0.000, punk_talk_think, // frame 17
 ai_stand,   0.000, punk_talk_think, // frame 18
 ai_stand,   0.000, punk_talk_think, // frame 19
 ai_stand,   0.000, punk_talk_think, // frame 20
 ai_stand,   0.000, punk_talk_think, // frame 21
 ai_stand,   0.000, punk_talk_think, // frame 22
 ai_stand,   0.000, punk_talk_think, // frame 23
 ai_stand,   0.000, punk_talk_think, // frame 24
 ai_stand,   0.000, punk_talk_think, // frame 25
 ai_stand,   0.000, punk_talk_think, // frame 26
 ai_stand,   0.000, punk_talk_think, // frame 27
 ai_stand,   0.000, punk_talk_think, // frame 28
 ai_stand,   0.000, punk_talk_think, // frame 29
 ai_stand,   0.000, punk_talk_think, // frame 30
 ai_stand,   0.000, punk_talk_think, // frame 31
 ai_stand,   0.000, punk_talk_think, // frame 32
 ai_stand,   0.000, punk_talk_think, // frame 33
 ai_stand,   0.000, punk_talk_think, // frame 34
 ai_stand,   0.000, punk_talk_think, // frame 35
 ai_stand,   0.000, punk_talk_think, // frame 36
 ai_stand,   0.000, punk_talk_think, // frame 37
 ai_stand,   0.000, punk_talk_think, // frame 38
 ai_stand,   0.000, punk_talk_think, // frame 39
 ai_stand,   0.000, punk_talk_think, // frame 40
 ai_stand,   0.000, punk_talk_think, // frame 41
 ai_stand,   0.000, punk_talk_think, // frame 42
 ai_stand,   0.000, punk_talk_think, // frame 43
 ai_stand,   0.000, punk_talk_think, // frame 44
 ai_stand,   0.000, punk_talk_think, // frame 45
 ai_stand,   0.000, punk_talk_think, // frame 46
};
mmove_t punk_move_sg_talk6 = {FRAME_sg_talk6_01, FRAME_sg_talk6_47, punk_frames_sg_talk6, punk_end_stand};


mframe_t	punk_frames_walk_dokey[] = 
{
	ai_runDOKEY,	 12.686, EP_ReachedDoKey,	// frame 0
	ai_runDOKEY,	  6.612, EP_ReachedDoKey,	// frame 1
	ai_runDOKEY,	  4.302, EP_ReachedDoKey,	// frame 2
	ai_runDOKEY,	  8.823, EP_ReachedDoKey,	// frame 3
	ai_runDOKEY,	  7.734, EP_ReachedDoKey,	// frame 4
	ai_runDOKEY,	  9.099, EP_ReachedDoKey,	// frame 5
	ai_runDOKEY,	  9.405, EP_ReachedDoKey,	// frame 6
	ai_runDOKEY,	  5.060, EP_ReachedDoKey,	// frame 7
	ai_runDOKEY,	  4.412, EP_ReachedDoKey,	// frame 8
	ai_runDOKEY,	  8.700, EP_ReachedDoKey,	// frame 9
};
mmove_t	punk_move_walk_dokey = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, punk_frames_walk_dokey, EP_ReachedDoKey};

mframe_t	punk_frames_crch_dokey[] = 
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
};
mmove_t	punk_move_crch_dokey = {FRAME_crch_astand_01, FRAME_crch_astand_20, punk_frames_crch_dokey, EP_EndDoKey};
