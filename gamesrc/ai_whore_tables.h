
//==================================================================================================
// standard moves

mframe_t	whore_frames_stand[] = 
{
	ai_stand,	  0.000, whore_talk_think,	// frame 0
	ai_stand,	  0.000, whore_talk_think,	// frame 1
	ai_stand,	  0.000, whore_talk_think,	// frame 2
	ai_stand,	  0.000, whore_talk_think,	// frame 3
	ai_stand,	  0.000, whore_talk_think,	// frame 4
	ai_stand,	  0.000, whore_talk_think,	// frame 5
	ai_stand,	  0.000, whore_talk_think,	// frame 6
	ai_stand,	  0.000, whore_talk_think,	// frame 7
	ai_stand,	  0.000, whore_talk_think,	// frame 8
	ai_stand,	  0.000, whore_talk_think,	// frame 9
	ai_stand,	  0.000, whore_talk_think,	// frame 10
	ai_stand,	  0.000, whore_talk_think,	// frame 11
	ai_stand,	  0.000, whore_talk_think,	// frame 12
	ai_stand,	  0.000, whore_talk_think,	// frame 13
	ai_stand,	  0.000, whore_talk_think,	// frame 14
	ai_stand,	  0.000, whore_talk_think,	// frame 15
	ai_stand,	  0.000, whore_talk_think,	// frame 16
	ai_stand,	  0.000, whore_talk_think,	// frame 17
	ai_stand,	  0.000, whore_talk_think,	// frame 18
	ai_stand,	  0.000, whore_talk_think,	// frame 19
	ai_stand,	  0.000, whore_talk_think,	// frame 20
	ai_stand,	  0.000, whore_talk_think,	// frame 21
	ai_stand,	  0.000, whore_talk_think,	// frame 22
	ai_stand,	  0.000, whore_talk_think,	// frame 23
	ai_stand,	  0.000, whore_talk_think,	// frame 24
	ai_stand,	  0.000, whore_talk_think,	// frame 25
	ai_stand,	  0.000, whore_talk_think,	// frame 26
	ai_stand,	  0.000, whore_talk_think,	// frame 27
	
};
mmove_t	whore_move_stand = {FRAME_stand_01, FRAME_stand_28, whore_frames_stand, whore_end_stand};

mframe_t	whore_frames_tg_shoot[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	  0.000, whore_firegun,	// frame 1
	ai_charge,	  0.000, whore_firegun,	// frame 2
	ai_charge,	  0.000, whore_firegun,	// frame 3
	ai_charge,	  0.000, whore_firegun,	// frame 4
	ai_charge,	  0.000, whore_firegun,	// frame 5
	ai_charge,	  0.000, whore_firegun,	// frame 6
	ai_charge,	  0.000, whore_firegun,	// frame 7
	ai_charge,	  0.000, whore_firegun,	// frame 8
	ai_charge,	  0.000, whore_firegun,	// frame 9
	ai_charge,	  0.000, whore_firegun,	// frame 10
	ai_charge,	  0.000, whore_firegun,	// frame 11
	ai_charge,	  0.000, whore_firegun,	// frame 12
	ai_charge,	  0.000, whore_firegun,	// frame 13
};
mmove_t	whore_move_tg_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_14, whore_frames_tg_shoot, AI_EndAttack};

mframe_t	whore_frames_hmg_shoot[] = 
{
	ai_charge,	  0.000, whore_firehmg,	// frame 0
	ai_charge,	  0.000, whore_firehmg,	// frame 1
	ai_charge,	  0.000, whore_firehmg,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, NULL,	// frame 7
	ai_charge,	  0.000, NULL,	// frame 8
	ai_charge,	  0.000, NULL,	// frame 9
	ai_charge,	  0.000, NULL,	// frame 10
	ai_charge,	  0.000, NULL,	// frame 11
	ai_charge,	  0.000, NULL,	// frame 12
	ai_charge,	  0.000, whore_firehmg_delay,	// frame 13
};
mmove_t	whore_move_hmg_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_14, whore_frames_hmg_shoot, AI_EndAttack};

mframe_t	whore_frames_bazooka_shoot[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, NULL,	// frame 7
	ai_charge,	  0.000, NULL,	// frame 8
	ai_charge,	  0.000, NULL,	// frame 9
	ai_charge,	  0.000, NULL,	// frame 10
	ai_charge,	  0.000, NULL,	// frame 11
	ai_charge,	  0.000, NULL,	// frame 12
	ai_charge,	  0.000, whore_bazooka_delay,	// frame 13
};
mmove_t	whore_move_bazooka_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_14, whore_frames_bazooka_shoot, AI_EndAttack};

mframe_t	whore_frames_grenade_shoot[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, NULL,	// frame 7
	ai_charge,	  0.000, NULL,	// frame 8
	ai_charge,	  0.000, NULL,	// frame 9
	ai_charge,	  0.000, NULL,	// frame 10
	ai_charge,	  0.000, NULL,	// frame 11
	ai_charge,	  0.000, NULL,	// frame 12
	ai_charge,	  0.000, NULL,	// frame 13
};
mmove_t	whore_move_grenade_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_14, whore_frames_grenade_shoot, AI_EndAttack};


mframe_t	whore_frames_flamegun_shoot[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	  0.000, whore_firegun,	// frame 1
	ai_charge,	  0.000, whore_firegun,	// frame 2
	ai_charge,	  0.000, whore_firegun,	// frame 3
	ai_charge,	  0.000, whore_firegun,	// frame 4
	ai_charge,	  0.000, whore_firegun,	// frame 5
	ai_charge,	  0.000, whore_firegun,	// frame 6
	ai_charge,	  0.000, whore_firegun,	// frame 7
	ai_charge,	  0.000, whore_firegun,	// frame 8
	ai_charge,	  0.000, whore_firegun,	// frame 9
	ai_charge,	  0.000, whore_firegun,	// frame 10
	ai_charge,	  0.000, whore_firegun,	// frame 11
	ai_charge,	  0.000, whore_firegun,	// frame 12
	ai_charge,	  0.000, whore_firegun,	// frame 13
};
mmove_t	whore_move_flamegun_shoot = {FRAME_tg_shoot_01, FRAME_tg_shoot_14, whore_frames_flamegun_shoot, AI_EndAttack};

mframe_t	whore_frames_shg_shoot[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, whore_shotgun_reload,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, NULL,	// frame 7
	ai_charge,	  0.000, NULL,	// frame 8
};
mmove_t	whore_move_shg_shoot = {FRAME_shg_shoot_01, FRAME_shg_shoot_09, whore_frames_shg_shoot, AI_EndAttack};

mframe_t	whore_frames_tg_reload[] = 
{
	ai_charge,	  0.000, NULL,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
	ai_charge,	  0.000, NULL,	// frame 3
	ai_charge,	  0.000, NULL,	// frame 4
	ai_charge,	  0.000, NULL,	// frame 5
	ai_charge,	  0.000, NULL,	// frame 6
	ai_charge,	  0.000, NULL,	// frame 7
	ai_charge,	  0.000, whore_reload_snd,	// frame 8
	ai_charge,	  0.000, NULL,	// frame 9
	ai_charge,	  0.000, NULL,	// frame 10
	ai_charge,	  0.000, NULL,	// frame 11
	ai_charge,	  0.000, NULL,	// frame 12
	ai_charge,	  0.000, NULL,	// frame 13
	ai_charge,	  0.000, NULL,	// frame 14
	ai_charge,	  0.000, NULL,	// frame 15
	ai_charge,	  0.000, NULL,	// frame 16
};
mmove_t	whore_move_tg_reload = {FRAME_tg_reload_01, FRAME_tg_reload_17, whore_frames_tg_reload, AI_EndAttack};

mframe_t	whore_frames_talk1[] = 
{
	ai_stand,	  0.000, whore_talk_think,	// frame 0
	ai_stand,	  0.000, whore_talk_think,	// frame 1
	ai_stand,	  0.000, whore_talk_think,	// frame 2
	ai_stand,	  0.000, whore_talk_think,	// frame 3
	ai_stand,	  0.000, whore_talk_think,	// frame 4
	ai_stand,	  0.000, whore_talk_think,	// frame 5
	ai_stand,	  0.000, whore_talk_think,	// frame 6
	ai_stand,	  0.000, whore_talk_think,	// frame 7
	ai_stand,	  0.000, whore_talk_think,	// frame 8
	ai_stand,	  0.000, whore_talk_think,	// frame 9
	ai_stand,	  0.000, whore_talk_think,	// frame 10
	ai_stand,	  0.000, whore_talk_think,	// frame 11
	ai_stand,	  0.000, whore_talk_think,	// frame 12
	ai_stand,	  0.000, whore_talk_think,	// frame 13
	ai_stand,	  0.000, whore_talk_think,	// frame 14
	ai_stand,	  0.000, whore_talk_think,	// frame 15
	ai_stand,	  0.000, whore_talk_think,	// frame 16
};
mmove_t	whore_move_talk1 = {FRAME_talk1_01, FRAME_talk1_17, whore_frames_talk1, whore_end_stand};

mframe_t	whore_frames_talk2[] = 
{
	ai_stand,	  0.000, whore_talk_think,	// frame 0
	ai_stand,	  0.000, whore_talk_think,	// frame 1
	ai_stand,	  0.000, whore_talk_think,	// frame 2
	ai_stand,	  0.000, whore_talk_think,	// frame 3
	ai_stand,	  0.000, whore_talk_think,	// frame 4
	ai_stand,	  0.000, whore_talk_think,	// frame 5
	ai_stand,	  0.000, whore_talk_think,	// frame 6
	ai_stand,	  0.000, whore_talk_think,	// frame 7
	ai_stand,	  0.000, whore_talk_think,	// frame 8
	ai_stand,	  0.000, whore_talk_think,	// frame 9
	ai_stand,	  0.000, whore_talk_think,	// frame 10
	ai_stand,	  0.000, whore_talk_think,	// frame 11
	ai_stand,	  0.000, whore_talk_think,	// frame 12
	ai_stand,	  0.000, whore_talk_think,	// frame 13
	ai_stand,	  0.000, whore_talk_think,	// frame 14
	ai_stand,	  0.000, whore_talk_think,	// frame 15
	ai_stand,	  0.000, whore_talk_think,	// frame 16
	ai_stand,	  0.000, whore_talk_think,	// frame 17
	ai_stand,	  0.000, whore_talk_think,	// frame 18
	ai_stand,	  0.000, whore_talk_think,	// frame 19
	ai_stand,	  0.000, whore_talk_think,	// frame 20
	ai_stand,	  0.000, whore_talk_think,	// frame 21
	ai_stand,	  0.000, whore_talk_think,	// frame 22
	ai_stand,	  0.000, whore_talk_think,	// frame 23
	ai_stand,	  0.000, whore_talk_think,	// frame 24
	ai_stand,	  0.000, whore_talk_think,	// frame 25
	ai_stand,	  0.000, whore_talk_think,	// frame 26
};
mmove_t	whore_move_talk2 = {FRAME_talk2_01, FRAME_talk2_27, whore_frames_talk2, whore_end_stand};

mframe_t	whore_frames_talk3[] = 
{
	ai_stand,	  0.000, whore_talk_think,	// frame 0
	ai_stand,	  0.000, whore_talk_think,	// frame 1
	ai_stand,	  0.000, whore_talk_think,	// frame 2
	ai_stand,	  0.000, whore_talk_think,	// frame 3
	ai_stand,	  0.000, whore_talk_think,	// frame 4
	ai_stand,	  0.000, whore_talk_think,	// frame 5
	ai_stand,	  0.000, whore_talk_think,	// frame 6
	ai_stand,	  0.000, whore_talk_think,	// frame 7
};
mmove_t	whore_move_talk3 = {FRAME_talk3_01, FRAME_talk3_08, whore_frames_talk3, whore_end_stand};

mframe_t	whore_frames_talk4[] = 
{
	ai_stand,	  0.000, whore_talk_think,	// frame 0
	ai_stand,	  0.000, whore_talk_think,	// frame 1
	ai_stand,	  0.000, whore_talk_think,	// frame 2
	ai_stand,	  0.000, whore_talk_think,	// frame 3
	ai_stand,	  0.000, whore_talk_think,	// frame 4
	ai_stand,	  0.000, whore_talk_think,	// frame 5
	ai_stand,	  0.000, whore_talk_think,	// frame 6
	ai_stand,	  0.000, whore_talk_think,	// frame 7
	ai_stand,	  0.000, whore_talk_think,	// frame 8
	ai_stand,	  0.000, whore_talk_think,	// frame 9
	ai_stand,	  0.000, whore_talk_think,	// frame 10
	ai_stand,	  0.000, whore_talk_think,	// frame 11
	ai_stand,	  0.000, whore_talk_think,	// frame 12
	ai_stand,	  0.000, whore_talk_think,	// frame 13
	ai_stand,	  0.000, whore_talk_think,	// frame 14
	ai_stand,	  0.000, whore_talk_think,	// frame 15
	ai_stand,	  0.000, whore_talk_think,	// frame 16
	ai_stand,	  0.000, whore_talk_think,	// frame 17
	ai_stand,	  0.000, whore_talk_think,	// frame 18
	ai_stand,	  0.000, whore_talk_think,	// frame 19
	ai_stand,	  0.000, whore_talk_think,	// frame 20
	ai_stand,	  0.000, whore_talk_think,	// frame 21
	ai_stand,	  0.000, whore_talk_think,	// frame 22
	ai_stand,	  0.000, whore_talk_think,	// frame 23
};
mmove_t	whore_move_talk4 = {FRAME_talk4_01, FRAME_talk4_24, whore_frames_talk4, whore_end_stand};

mframe_t	whore_frames_talk5[] = 
{
	ai_stand,	  0.000, whore_talk_think,	// frame 0
	ai_stand,	  0.000, whore_talk_think,	// frame 1
	ai_stand,	  0.000, whore_talk_think,	// frame 2
	ai_stand,	  0.000, whore_talk_think,	// frame 3
	ai_stand,	  0.000, whore_talk_think,	// frame 4
	ai_stand,	  0.000, whore_talk_think,	// frame 5
	ai_stand,	  0.000, whore_talk_think,	// frame 6
	ai_stand,	  0.000, whore_talk_think,	// frame 7
	ai_stand,	  0.000, whore_talk_think,	// frame 8
	ai_stand,	  0.000, whore_talk_think,	// frame 9
	ai_stand,	  0.000, whore_talk_think,	// frame 10
	ai_stand,	  0.000, whore_talk_think,	// frame 11
	ai_stand,	  0.000, whore_talk_think,	// frame 12
	ai_stand,	  0.000, whore_talk_think,	// frame 13
	ai_stand,	  0.000, whore_talk_think,	// frame 14
	ai_stand,	  0.000, whore_talk_think,	// frame 15
	ai_stand,	  0.000, whore_talk_think,	// frame 16
	ai_stand,	  0.000, whore_talk_think,	// frame 17
	ai_stand,	  0.000, whore_talk_think,	// frame 18
	ai_stand,	  0.000, whore_talk_think,	// frame 19
	ai_stand,	  0.000, whore_talk_think,	// frame 20
};
mmove_t	whore_move_talk5 = {FRAME_talk5_01, FRAME_talk5_21, whore_frames_talk5, whore_end_stand};

/*
mframe_t	whore_frames_talk6[] = 
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
};
mmove_t	whore_move_talk6 = {FRAME_talk6_01, FRAME_talk6_21, whore_frames_talk6, whore_end_stand};
*/

mframe_t	whore_frames_pain_Rarm[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
	ai_move,	  0.000, NULL,	// frame 6
};
mmove_t	whore_move_pain_Rarm = {FRAME_pain_Rarm_01, FRAME_pain_Rarm_07, whore_frames_pain_Rarm, AI_EndAttack};

mframe_t	whore_frames_pain_Larm[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
};
mmove_t	whore_move_pain_Larm = {FRAME_pain_Larm_01, FRAME_pain_Larm_06, whore_frames_pain_Larm, AI_EndAttack};

mframe_t	whore_frames_pain_chest[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
};
mmove_t	whore_move_pain_chest = {FRAME_pain_chest_01, FRAME_pain_chest_06, whore_frames_pain_chest, AI_EndAttack};

mframe_t	whore_frames_pain_head[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
	ai_move,	  0.000, NULL,	// frame 5
};
mmove_t	whore_move_pain_head = {FRAME_pain_head_01, FRAME_pain_head_06, whore_frames_pain_head, AI_EndAttack};

mframe_t	whore_frames_pain_Rleg[] = 
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
mmove_t	whore_move_pain_Rleg = {FRAME_pain_Rleg_01, FRAME_pain_Rleg_09, whore_frames_pain_Rleg, AI_EndAttack};

mframe_t	whore_frames_pain_Lleg[] = 
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
mmove_t	whore_move_pain_Lleg = {FRAME_pain_Lleg_01, FRAME_pain_Lleg_09, whore_frames_pain_Lleg, AI_EndAttack};

mframe_t	whore_frames_pain_crch[] = 
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
mmove_t	whore_move_pain_crch = {FRAME_pain_crch_01, FRAME_pain_crch_08, whore_frames_pain_crch, AI_EndAttack};

mframe_t	whore_frames_pain_butt[] = 
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
mmove_t	whore_move_pain_butt = {FRAME_pain_butt_01, FRAME_pain_butt_10, whore_frames_pain_butt, AI_EndAttack};

mframe_t	whore_frames_jump[] = 
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
mmove_t	whore_move_jump = {FRAME_jump_06, FRAME_jump_09, whore_frames_jump, AI_EndJump};

mframe_t	whore_frames_death1[] = 
{
	ai_move, -2.902, NULL,	// frame 0
	ai_move, -0.664, NULL,	// frame 1
	ai_move,-14.584, NULL,	// frame 2
	ai_move,-17.393, NULL,	// frame 3
	ai_move,-28.195, NULL,	// frame 4
	ai_move,  9.304, NULL,	// frame 5
	ai_move, -6.112, NULL,	// frame 6
	ai_move, -0.394, NULL,	// frame 7
	ai_move, -0.618, NULL,	// frame 8
	ai_move,  1.842, NULL,	// frame 9
	ai_move,  1.468, NULL,	// frame 10
	ai_move, -4.435, NULL,	// frame 11
	ai_move, -8.503, NULL,	// frame 12
	ai_move, -3.642, NULL,	// frame 13
	ai_move,  0.104, NULL,	// frame 14
};
mmove_t	whore_move_death1 = {FRAME_death1_01, FRAME_death1_15, whore_frames_death1, AI_EndDeath};

mframe_t	whore_frames_death2[] = 
{
	ai_move,	  0.271, NULL,	// frame 0
	ai_move,	 -1.254, NULL,	// frame 1
	ai_move,	 -7.892, NULL,	// frame 2
	ai_move,	-21.044, NULL,	// frame 3
	ai_move,	-10.949, NULL,	// frame 4
	ai_move,	-19.873, NULL,	// frame 5
	ai_move,	 -6.772, NULL,	// frame 6
	ai_move,	  1.508, NULL,	// frame 7
	ai_move,	  2.394, NULL,	// frame 8
	ai_move,	  4.865, NULL,	// frame 9
	ai_move,	 -3.174, NULL,	// frame 10
	ai_move,	 -0.039, NULL,	// frame 11
	ai_move,	  0.694, NULL,	// frame 12
	ai_move,	  0.036, NULL,	// frame 13
	ai_move,	 -0.467, NULL,	// frame 14
	ai_move,	  0.096, NULL,	// frame 15
};
mmove_t	whore_move_death2 = {FRAME_death2_01, FRAME_death2_16, whore_frames_death2, AI_EndDeath};

mframe_t	whore_frames_death3[] = 
{
	ai_move,	    2.578, NULL,	// frame 0
	ai_move,	    9.487, NULL,	// frame 1
	ai_move,	    8.104, NULL,	// frame 2
	ai_move,	    7.801, NULL,	// frame 3
	ai_move,	    4.730, NULL,	// frame 4
	ai_move,	   10.007, NULL,	// frame 5
	ai_move,	    1.971, NULL,	// frame 6
	ai_move,	    0.830, NULL,	// frame 7
	ai_move,	   -0.488, NULL,	// frame 8
	ai_move,	    0.076, NULL,	// frame 9
	ai_move,	    0.033, NULL,	// frame 10
	ai_move,	   -0.045, NULL,	// frame 11
	ai_move,	   -0.006, NULL,	// frame 12
	ai_move,	    0.017, NULL,	// frame 13
	ai_move,	   -0.006, NULL,	// frame 14
	ai_move,	    0.002, NULL,	// frame 15
};
mmove_t	whore_move_death3 = {FRAME_death3_01, FRAME_death3_16, whore_frames_death3, AI_EndDeath};

mframe_t	whore_frames_death4[] = 
{
	ai_move,  0.040, NULL,	// frame 0
	ai_move,  0.468, NULL,	// frame 1
	ai_move,  1.581, NULL,	// frame 2
	ai_move,  3.461, NULL,	// frame 3
	ai_move,  3.338, NULL,	// frame 4
	ai_move,  4.240, NULL,	// frame 5
	ai_move, 11.085, NULL,	// frame 6
	ai_move,  0.212, NULL,	// frame 7
	ai_move, -0.200, NULL,	// frame 8
	ai_move,  0.730, NULL,	// frame 9
	ai_move,  2.632, NULL,	// frame 10
	ai_move,  4.002, NULL,	// frame 11
	ai_move, 10.135, NULL,	// frame 12
	ai_move,  6.510, NULL,	// frame 13
	ai_move,  5.890, NULL,	// frame 14
	ai_move,  0.438, NULL,	// frame 15
	ai_move,  0.487, NULL,	// frame 16
	ai_move,  1.542, NULL,	// frame 17
	ai_move,  0.243, NULL,	// frame 18
	ai_move, -0.291, NULL,	// frame 19
	ai_move, -0.144, NULL,	// frame 20
	ai_move,  0.045, NULL,	// frame 21
};
mmove_t	whore_move_death4 = {FRAME_death4_01, FRAME_death4_22, whore_frames_death4, AI_EndDeath};

mframe_t	whore_frames_death5[] = 
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
	ai_move,	  0.008, NULL,	// frame 13
	ai_move,	  0.008, NULL,	// frame 14
	ai_move,	  0.008, NULL,	// frame 15
	ai_move,	  0.008, NULL,	// frame 16
	ai_move,	  0.008, NULL,	// frame 17
	ai_move,	  0.008, NULL,	// frame 18
	ai_move,	  0.008, NULL,	// frame 19
	ai_move,	  0.008, NULL,	// frame 20
	ai_move,	  0.008, NULL,	// frame 21
	ai_move,	  0.008, NULL,	// frame 22
	ai_move,	  0.008, NULL,	// frame 23
	ai_move,	  0.008, NULL,	// frame 24
	ai_move,	  0.008, NULL,	// frame 25
	ai_move,	  0.008, NULL,	// frame 26
	ai_move,	  0.008, NULL,	// frame 27
	ai_move,	  0.008, NULL,	// frame 28
	ai_move,	  0.008, NULL,	// frame 29
	ai_move,	  0.008, NULL,	// frame 30
	ai_move,	  0.008, NULL,	// frame 31
	ai_move,	  0.008, NULL,	// frame 32
};
mmove_t	whore_move_death5 = {FRAME_death5_01, FRAME_death5_33, whore_frames_death4, AI_EndDeath};

mframe_t	whore_frames_crh_shuf[] = 
{
	ai_run,	  5.383, NULL,	// frame 0
	ai_run,	  5.466, NULL,	// frame 1
	ai_run,	  3.693, NULL,	// frame 2
	ai_run,	  5.865, NULL,	// frame 3
	ai_run,	 13.852, NULL,	// frame 4
	ai_run,	  6.698, NULL,	// frame 5
	ai_run,	  3.743, NULL,	// frame 6
	ai_run,	  3.743, NULL,	// frame 7
	ai_run,	  3.743, NULL,	// frame 8
	ai_run,	  3.743, NULL,	// frame 9
	ai_run,	  3.743, NULL,	// frame 10
	ai_run,	  3.743, NULL,	// frame 11
	ai_run,	  3.743, NULL,	// frame 12
	ai_run,	  3.743, NULL,	// frame 13
};
mmove_t	whore_move_crh_shuf = {FRAME_crouch_walk_01, FRAME_crouch_walk_14, whore_frames_crh_shuf, NULL};

mframe_t	whore_frames_crouch_walk[] = 
{
	ai_run,	  5.383, NULL,	// frame 0
	ai_run,	  5.466, NULL,	// frame 1
	ai_run,	  3.693, NULL,	// frame 2
	ai_run,	  5.865, NULL,	// frame 3
	ai_run,	 13.852, NULL,	// frame 4
	ai_run,	  6.698, NULL,	// frame 5
	ai_run,	  3.743, NULL,	// frame 6
	ai_run,	  3.743, NULL,	// frame 7
	ai_run,	  3.743, NULL,	// frame 8
	ai_run,	  3.743, NULL,	// frame 9
	ai_run,	  3.743, NULL,	// frame 10
	ai_run,	  3.743, NULL,	// frame 11
	ai_run,	  3.743, NULL,	// frame 12
	ai_run,	  3.743, NULL,	// frame 13
};
mmove_t	whore_move_crouch_walk = {FRAME_crouch_walk_01, FRAME_crouch_walk_14, whore_frames_crouch_walk, NULL};

mframe_t	whore_frames_crouch_painC[] = 
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
mmove_t	whore_move_crouch_painC = {FRAME_crouch_painC_01, FRAME_crouch_painC_10, whore_frames_crouch_painC, AI_EndAttack};

mframe_t	whore_frames_crouch_painL[] = 
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
mmove_t	whore_move_crouch_painL = {FRAME_crouch_painL_01, FRAME_crouch_painL_11, whore_frames_crouch_painL, AI_EndAttack};

mframe_t	whore_frames_crouch_painR[] = 
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
mmove_t	whore_move_crouch_painR = {FRAME_crouch_painR_01, FRAME_crouch_painR_11, whore_frames_crouch_painR, AI_EndAttack};

mframe_t	whore_frames_crouch_shoot[] = 
{
	ai_turn,	  0.000, whore_firegun,	// frame 0
	ai_turn,	  0.000, whore_firegun_cr,	// frame 1
	ai_turn,	  0.000, whore_firegun_cr,	// frame 2
	ai_turn,	  0.000, whore_firegun_cr,	// frame 3
	ai_turn,	  0.000, whore_firegun_cr,	// frame 4
	ai_turn,	  0.000, whore_firegun_cr,	// frame 5
	ai_turn,	  0.000, whore_firegun_cr,	// frame 6
	ai_turn,	  0.000, whore_firegun_cr,	// frame 7
	ai_turn,	  0.000, whore_firegun_cr,	// frame 8
	ai_turn,	  0.000, whore_firegun_cr,	// frame 9
	ai_turn,	  0.000, whore_firegun_cr,	// frame 10
	ai_turn,	  0.000, whore_firegun_cr,	// frame 11
	ai_turn,	  0.000, whore_firegun_cr,	// frame 12
	ai_turn,	  0.000, whore_firegun_cr,	// frame 13
	ai_turn,	  0.000, whore_firegun_cr,	// frame 14
	ai_turn,	  0.000, whore_firegun_cr,	// frame 15
	ai_turn,	  0.000, whore_firegun_cr,	// frame 16
};
mmove_t	whore_move_crouch_shoot = {FRAME_crouch_shoot_01, FRAME_crouch_shoot_17, whore_frames_crouch_shoot, AI_EndAttack};

mframe_t	whore_frames_crch_shg_sht[] = 
{
	ai_turn,	  0.000, whore_firegun,	// frame 0
	ai_turn,	  0.000, NULL,	// frame 1
	ai_turn,	  0.000, NULL,	// frame 2
	ai_turn,	  0.000, NULL,	// frame 3
	ai_turn,	  0.000, NULL,	// frame 4
	ai_turn,	  0.000, whore_shotgun_reload,	// frame 5
	ai_turn,	  0.000, NULL,	// frame 6
	ai_turn,	  0.000, NULL,	// frame 7
	ai_turn,	  0.000, NULL,	// frame 8
	ai_turn,	  0.000, NULL,	// frame 9
	ai_turn,	  0.000, NULL,	// frame 10
	
};
mmove_t	whore_move_crch_shg_sht = {FRAME_crch_shg_sht_01, FRAME_crch_shg_sht_11, whore_frames_crch_shg_sht, AI_EndAttack};

mframe_t	whore_frames_crouch_stand_down[] = 
{
//	NULL,	  0.000, NULL,	// frame 0
//	NULL,	  0.000, NULL,	// frame 1
//	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
	NULL,	  0.000, NULL,	// frame 4
	NULL,	  0.000, NULL,	// frame 5
	NULL,	  0.000, NULL,	// frame 6
//	NULL,	  0.000, NULL,	// frame 7
//	NULL,	  0.000, NULL,	// frame 8
//	NULL,	  0.000, NULL,	// frame 9
//	NULL,	  0.000, NULL,	// frame 10
};
mmove_t	whore_move_crouch_stand_down = {FRAME_stand_crouch_04, FRAME_stand_crouch_07, whore_frames_crouch_stand_down, AI_End_CrouchStand_Down};

mframe_t	whore_frames_crouch_stand_up[] = 
{
//	NULL,	  0.000, NULL,	// frame 0
//	NULL,	  0.000, NULL,	// frame 1
//	NULL,	  0.000, NULL,	// frame 2
	NULL,	  0.000, NULL,	// frame 3
	NULL,	  0.000, NULL,	// frame 4
	NULL,	  0.000, NULL,	// frame 5
	NULL,	  0.000, NULL,	// frame 6
//	NULL,	  0.000, NULL,	// frame 7
//	NULL,	  0.000, NULL,	// frame 8
//	NULL,	  0.000, NULL,	// frame 9
//	NULL,	  0.000, NULL,	// frame 10
};
mmove_t	whore_move_crouch_stand_up = {FRAME_stand_crouch_07, FRAME_stand_crouch_04, whore_frames_crouch_stand_up, AI_End_CrouchStand_Up};

mframe_t	whore_frames_crch_astand[] = 
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
	ai_stand,	  0.000, NULL,	// frame 28
	ai_stand,	  0.000, NULL,	// frame 29
};
mmove_t	whore_move_crch_astand = {FRAME_crch_astand_01, FRAME_crch_astand_30, whore_frames_crch_astand, NULL};

mframe_t	whore_frames_crouch_death1[] = 
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
};
mmove_t	whore_move_crouch_death1 = {FRAME_crch_death1_01, FRAME_crch_death1_16, whore_frames_crouch_death1, AI_EndDeath};

mframe_t	whore_frames_crouch_death2[] = 
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
};
mmove_t	whore_move_crouch_death2 = {FRAME_crch_death2_01, FRAME_crch_death2_23, whore_frames_crouch_death2, AI_EndDeath};

/*
mframe_t	whore_frames_st_clmb[] = 
{
	ai_stand,	  0.000, NULL,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
};
mmove_t	whore_move_st_clmb = {FRAME_st_clmb_01, FRAME_st_clmb_02, whore_frames_st_clmb, NULL};
*/

mframe_t	whore_frames_clmb_loop[] = 
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
	NULL,	  0.000, NULL,	// frame 10
};
mmove_t	whore_move_clmb_loop = {FRAME_clmb_loop_01, FRAME_clmb_loop_11, whore_frames_clmb_loop, AI_CheckStillClimbingLadder};

mframe_t	whore_frames_clmb_over[] = 
{
//	NULL,	  0.000, NULL,	// frame 0
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
mmove_t	whore_move_clmb_over = {FRAME_clmb_over_02, FRAME_clmb_over_10, whore_frames_clmb_over, AI_EndJump};

/*
mframe_t	whore_frames_lside_step[] = 
{
	ai_sidestep,	  0.215, NULL,	// frame 0
	ai_sidestep,	  0.721, NULL,	// frame 1
	ai_sidestep,	  2.871, NULL,	// frame 2
	ai_sidestep,	  4.372, NULL,	// frame 3
	ai_sidestep,	  2.453, NULL,	// frame 4
	ai_sidestep,	  2.358, NULL,	// frame 5
	ai_sidestep,	 -0.671, NULL,	// frame 6
};
mmove_t	whore_move_lside_step = {FRAME_lside_step_01, FRAME_lside_step_07, whore_frames_lside_step, NULL};

mframe_t	whore_frames_rside_step[] = 
{
	ai_sidestep,	   0.676, NULL,	// frame 0
	ai_sidestep,	  -0.261, NULL,	// frame 1
	ai_sidestep,	  -1.790, NULL,	// frame 2
	ai_sidestep,	  -1.300, NULL,	// frame 3
	ai_sidestep,	  -2.096, NULL,	// frame 4
	ai_sidestep,	  -3.586, NULL,	// frame 5
	ai_sidestep,	  -3.024, NULL,	// frame 6
};
mmove_t	whore_move_rside_step = {FRAME_rside_step_01, FRAME_rside_step_07, whore_frames_rside_step, NULL};
*/

mframe_t	whore_frames_lside_step[] = 
{
	ai_sidestep,	 -0.215, NULL,	// frame 0
	ai_sidestep,	 -0.721, NULL,	// frame 1
	ai_sidestep,	 -2.871, NULL,	// frame 2
	ai_sidestep,	 -4.372, NULL,	// frame 3
	ai_sidestep,	 -2.453, NULL,	// frame 4
	ai_sidestep,	 -2.358, NULL,	// frame 5
	ai_sidestep,	  0.671, NULL,	// frame 6
};
mmove_t	whore_move_lside_step = {FRAME_lside_step_01, FRAME_lside_step_07, whore_frames_lside_step, AI_EndAttack};

/*
mframe_t	whore_frames_rside_step[] = 
{
	ai_sidestep,	-0.676, NULL,	// frame 0
	ai_sidestep,	 0.261, NULL,	// frame 1
	ai_sidestep,	 1.790, NULL,	// frame 2
	ai_sidestep,	 1.300, NULL,	// frame 3
	ai_sidestep,	 2.096, NULL,	// frame 4
	ai_sidestep,	 3.586, NULL,	// frame 5
	ai_sidestep,	 3.024, NULL,	// frame 6
};
mmove_t	whore_move_rside_step = {FRAME_rside_step_01, FRAME_rside_step_07, whore_frames_rside_step, AI_EndAttack};
*/

mframe_t	whore_frames_walk_nw[] = 
{
	ai_run,	 16.781, NULL,	// frame 0
	ai_run,	 14.098, NULL,	// frame 1
	ai_run,	  7.220, NULL,	// frame 2
	ai_run,	  1.106, NULL,	// frame 3
	ai_run,	 -0.983, NULL,	// frame 4
	ai_run,	 -0.107, NULL,	// frame 5
	ai_run,	  5.744, NULL,	// frame 6
	ai_run,	  5.101, NULL,	// frame 7
	ai_run,	  3.955, NULL,	// frame 8
	ai_run,	  6.993, NULL,	// frame 9
	ai_run,	  5.951, NULL,	// frame 10
};
mmove_t	whore_move_walk_nw = {FRAME_walk_nw_01, FRAME_walk_nw_11, whore_frames_walk_nw, AI_EndRun};

mframe_t	whore_frames_walk_tg_sht[] = 
{
	ai_turn,	  11.306, whore_firegun,	// frame 0
	ai_turn,	   6.486, whore_firegun,	// frame 1
	ai_turn,	   6.159, whore_firegun,	// frame 2
	ai_turn,	   9.146, whore_firegun,	// frame 3
	ai_turn,	   9.527, whore_firegun,	// frame 4
	ai_turn,	   8.850, whore_firegun,	// frame 5
	ai_turn,	   8.214, whore_firegun,	// frame 6
	ai_turn,	   6.377, whore_firegun,	// frame 7
	ai_turn,	   5.029, whore_firegun,	// frame 8
	ai_turn,	   5.740, whore_firegun,	// frame 9
};
mmove_t	whore_move_walk_tg_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, whore_frames_walk_tg_sht, AI_EndAttack};

mframe_t	whore_frames_walk_hmg_sht[] = 
{
	ai_turn,	  11.306, whore_firehmg,	// frame 0
	ai_turn,	   6.486, whore_firehmg,	// frame 1
	ai_turn,	   6.159, whore_firehmg,	// frame 2
	ai_turn,	   9.146, NULL,	// frame 3
	ai_turn,	   9.527, NULL,	// frame 4
	ai_turn,	   8.850, NULL,	// frame 5
	ai_turn,	   8.214, NULL,	// frame 6
	ai_turn,	   6.377, NULL,	// frame 7
	ai_turn,	   5.029, NULL,	// frame 8
	ai_turn,	   5.740, whore_firehmg_delay,	// frame 9
};
mmove_t	whore_move_walk_hmg_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, whore_frames_walk_hmg_sht, AI_EndAttack};

mframe_t	whore_frames_walk_bazooka_sht[] = 
{
	ai_turn,	  11.306, whore_firegun,	// frame 0
	ai_turn,	   6.486, NULL,	// frame 1
	ai_turn,	   6.159, NULL,	// frame 2
	ai_turn,	   9.146, NULL,	// frame 3
	ai_turn,	   9.527, NULL,	// frame 4
	ai_turn,	   8.850, NULL,	// frame 5
	ai_turn,	   8.214, NULL,	// frame 6
	ai_turn,	   6.377, NULL,	// frame 7
	ai_turn,	   5.029, NULL,	// frame 8
	ai_turn,	   5.740, whore_bazooka_delay,	// frame 9
};
mmove_t	whore_move_walk_bazooka_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, whore_frames_walk_bazooka_sht, AI_EndAttack};

mframe_t	whore_frames_walk_grenade_sht[] = 
{
	ai_turn,	  11.306, whore_firegun,	// frame 0
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
mmove_t	whore_move_walk_grenade_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, whore_frames_walk_grenade_sht, AI_EndAttack};

mframe_t	whore_frames_walk_flamegun_sht[] = 
{
	ai_turn,	  11.306, whore_firegun,	// frame 0
	ai_turn,	   6.486, whore_firegun,	// frame 1
	ai_turn,	   6.159, whore_firegun,	// frame 2
	ai_turn,	   9.146, whore_firegun,	// frame 3
	ai_turn,	   9.527, whore_firegun,	// frame 4
	ai_turn,	   8.850, whore_firegun,	// frame 5
	ai_turn,	   8.214, whore_firegun,	// frame 6
	ai_turn,	   6.377, whore_firegun,	// frame 7
	ai_turn,	   5.029, whore_firegun,	// frame 8
	ai_turn,	   5.740, whore_firegun,	// frame 9
};
mmove_t	whore_move_walk_flamegun_sht = {FRAME_walk_tg_sht_01, FRAME_walk_tg_sht_10, whore_frames_walk_flamegun_sht, AI_EndAttack};


mframe_t	whore_frames_walk_shg_sht[] = 
{
	ai_turn,	 13.194, whore_firegun,	// frame 0
	ai_turn,	  3.697, NULL,	// frame 1
	ai_turn,	  9.794, NULL,	// frame 2
	ai_turn,	  9.688, NULL,	// frame 3
	ai_turn,	  8.709, NULL,	// frame 4
	ai_turn,	  9.221, whore_shotgun_reload,	// frame 5
	ai_turn,	  7.405, NULL,	// frame 6
	ai_turn,	  7.594, NULL,	// frame 7
	ai_turn,	  2.303, NULL,	// frame 8
	ai_turn,	  5.228, NULL,	// frame 9
};
mmove_t	whore_move_walk_shg_sht = {FRAME_walk_shg_sht_01, FRAME_walk_shg_sht_10, whore_frames_walk_shg_sht, AI_EndAttack};

mframe_t	whore_frames_walk_gdown[] = 
{
	ai_run,	    3.636, NULL,	// frame 0
	ai_run,	    6.504, NULL,	// frame 1
	ai_run,	    3.111, NULL,	// frame 2
	ai_run,	    4.200, NULL,	// frame 3
	ai_run,	    8.913, NULL,	// frame 4
	ai_run,	    7.640, NULL,	// frame 5
	ai_run,	   11.360, NULL,	// frame 6
	ai_run,	    4.233, NULL,	// frame 7
	ai_run,	   12.047, NULL,	// frame 8
	ai_run,	   10.356, NULL,	// frame 9
};
mmove_t	whore_move_walk_gdown = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, whore_frames_walk_gdown, NULL};

mframe_t	whore_frames_run_nw[] = 
{
	ai_run,	  1.956, NULL,	// frame 0
	ai_run,	 15.182, NULL,	// frame 1
	ai_run,	  3.415, NULL,	// frame 2
	ai_run,	 15.985, NULL,	// frame 3
	ai_run,	 39.101, NULL,	// frame 4
	ai_run,	  7.988, NULL,	// frame 5
	ai_run,  24.122, NULL,  // frame 6
};
mmove_t	whore_move_run_nw = {FRAME_run_nw_01, FRAME_run_nw_07, whore_frames_run_nw, AI_EndRun};

mframe_t	whore_frames_run_tg_sht[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	 18.721, NULL,	// frame 1
	ai_charge,	 11.416, whore_firegun,	// frame 2
	ai_charge,	 22.838, NULL,	// frame 3
	ai_charge,	 19.254, whore_firegun,	// frame 4
	ai_charge,	 14.931, NULL,	// frame 5
	ai_charge,	 24.714, whore_firegun,	// frame 6
};
mmove_t	whore_move_run_tg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_07, whore_frames_run_tg_sht, AI_EndAttack};

mframe_t	whore_frames_run_reverse_tg_sht[] = 
{
	ai_charge,-	 24.714, NULL,	// frame 0
	ai_charge,-	 14.931, whore_firegun,	// frame 5
	ai_charge,-	 19.254, NULL,	// frame 4
	ai_charge,-	 22.838, whore_firegun,	// frame 3
	ai_charge,-	 11.416, NULL,	// frame 2
	ai_charge,-	 18.721, whore_firegun,	// frame 1
	ai_charge,		0.0, NULL,	// frame 0
	
};
mmove_t	whore_move_run_reverse_tg_sht = {FRAME_run_tg_sht_07, FRAME_run_tg_sht_01, whore_frames_run_reverse_tg_sht, AI_EndAttack};


mframe_t	whore_frames_run_hmg_sht[] = 
{
	ai_charge,	  0.000, whore_firehmg,	// frame 0
	ai_charge,	 18.721, whore_firehmg,	// frame 1
	ai_charge,	 11.416, whore_firehmg,	// frame 2
	ai_charge,	 22.838, NULL,	// frame 3
	ai_charge,	 19.254, NULL,	// frame 4
	ai_charge,	 14.931, NULL,	// frame 5
	ai_charge,	 24.714, whore_firehmg_delay,
};
mmove_t	whore_move_run_hmg_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_07, whore_frames_run_hmg_sht, AI_EndAttack};

mframe_t	whore_frames_run_reverse_hmg_sht[] = 
{
	ai_charge,-	 24.714, whore_firehmg,
	ai_charge,-	 14.931, whore_firehmg,	// frame 5
	ai_charge,-	 19.254, whore_firehmg,	// frame 4
	ai_charge,-	 22.838, NULL,	// frame 3
	ai_charge,-	 11.416, NULL,	// frame 2
	ai_charge,-	 18.721, NULL,	// frame 1
	ai_charge,		0.0, NULL,	// frame 0
};
mmove_t	whore_move_run_reverse_hmg_sht = {FRAME_run_tg_sht_07, FRAME_run_tg_sht_01, whore_frames_run_reverse_hmg_sht, AI_EndAttack};


mframe_t	whore_frames_run_bazooka_sht[] = 
{
	ai_charge,	   0.000, whore_firegun,	// frame 0
	ai_charge,	  18.721, NULL,	// frame 1
	ai_charge,	  11.416, NULL,	// frame 2
	ai_charge,	  22.838, NULL,	// frame 3
	ai_charge,	  19.254, NULL,	// frame 4
	ai_charge,	  14.931, NULL,	// frame 5
	ai_charge,	  24.714, whore_bazooka_delay,	// frame 6
};
mmove_t	whore_move_run_bazooka_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_07, whore_frames_run_bazooka_sht, AI_EndAttack};

mframe_t	whore_frames_run_reverse_bazooka_sht[] = 
{
	ai_charge,-	 24.714, whore_firegun,	// frame 5
	ai_charge,-	 14.931, NULL,	// frame 5
	ai_charge,-	 19.254, NULL,	// frame 4
	ai_charge,-	 22.838, NULL,	// frame 3
	ai_charge,-	 11.416, NULL,	// frame 2
	ai_charge,-	 18.721, NULL,	// frame 1
	ai_charge,		0.0, NULL,	// frame 0
};
mmove_t	whore_move_run_reverse_bazooka_sht = {FRAME_run_tg_sht_07, FRAME_run_tg_sht_01, whore_frames_run_reverse_bazooka_sht, AI_EndAttack};


mframe_t	whore_frames_run_grenade_sht[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	 18.721, NULL,	// frame 1
	ai_charge,	 11.416, NULL,	// frame 2
	ai_charge,	 22.838, NULL,	// frame 3
	ai_charge,	 19.254, NULL,	// frame 4
	ai_charge,	 14.931, NULL,	// frame 5
	ai_charge,	 24.714, NULL,	// frame 6
};
mmove_t	whore_move_run_grenade_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_07, whore_frames_run_grenade_sht, AI_EndAttack};

mframe_t	whore_frames_run_reverse_grenade_sht[] = 
{
	ai_charge,-	 24.714, whore_firegun,	// frame 5
	ai_charge,-	 14.931, NULL,	// frame 5
	ai_charge,-	 19.254, NULL,	// frame 4
	ai_charge,-	 22.838, NULL,	// frame 3
	ai_charge,-	 11.416, NULL,	// frame 2
	ai_charge,-	 18.721, NULL,	// frame 1
	ai_charge,		0.0, NULL,	// frame 0
};
mmove_t	whore_move_run_reverse_grenade_sht = {FRAME_run_tg_sht_07, FRAME_run_tg_sht_01, whore_frames_run_reverse_grenade_sht, AI_EndAttack};


mframe_t	whore_frames_run_flamegun_sht[] = 
{
	ai_charge,	 27.656, whore_firegun,	// frame 0
	ai_charge,	 17.929, whore_firegun,	// frame 1
	ai_charge,	 33.470, whore_firegun,	// frame 2
	ai_charge,	 37.084, whore_firegun,	// frame 3
	ai_charge,	 31.857, whore_firegun,	// frame 4
	ai_charge,	 24.969, whore_firegun,	// frame 5
};
mmove_t	whore_move_run_flamegun_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, whore_frames_run_flamegun_sht, AI_EndAttack};

mframe_t	whore_frames_run_reverse_flamegun_sht[] = 
{
	ai_charge,-	 24.969, whore_firegun,	// frame 5
	ai_charge,-	 31.857, whore_firegun,	// frame 4
	ai_charge,-	 37.084, whore_firegun,	// frame 3
	ai_charge,-	 33.470, whore_firegun,	// frame 2
	ai_charge,-	 17.929, whore_firegun,	// frame 1
	ai_charge,-	 27.656, whore_firegun,	// frame 0
};
mmove_t	whore_move_run_reverse_flamegun_sht = {FRAME_run_tg_sht_01, FRAME_run_tg_sht_06, whore_frames_run_reverse_flamegun_sht, AI_EndAttack};


mframe_t	whore_frames_run_shg_sht[] = 
{
	ai_charge,	  0.000, whore_firegun,	// frame 0
	ai_charge,	 15.902, NULL,	// frame 1
	ai_charge,	 14.235, NULL,	// frame 2
	ai_charge,	 17.221, whore_shotgun_reload,	// frame 3
	ai_charge,	 19.659, NULL,	// frame 4
	ai_charge,	 18.310, NULL,	// frame 5
	ai_charge,	 26.546, NULL
};
mmove_t	whore_move_run_shg_sht = {FRAME_run_shg_sht_01, FRAME_run_shg_sht_07, whore_frames_run_shg_sht, AI_EndAttack};

mframe_t	whore_frames_run_gun_down[] = 
{
	ai_run,	  1.956, NULL,	// frame 0
	ai_run,	 15.182, NULL,	// frame 1
	ai_run,	  3.415, NULL,	// frame 2
	ai_run,	 15.985, NULL,	// frame 3
	ai_run,	 39.101, NULL,	// frame 4
	ai_run,	  7.988, NULL,	// frame 5
	ai_run,  24.122, NULL,	// frame 6
};
mmove_t	whore_move_run_gun_down = {FRAME_run_gun_down_01, FRAME_run_gun_down_07, whore_frames_run_gun_down, AI_EndRun};

mframe_t	whore_frames_run_on_fire[] = 
{
	ai_onfire_run,	 8.376, NULL,	// frame 0
	ai_onfire_run,	20.175, NULL,	// frame 1
	ai_onfire_run,	 1.329, NULL,	// frame 2
	ai_onfire_run,	31.146, NULL,	// frame 3
	ai_onfire_run,	24.144, NULL,	// frame 4
	ai_onfire_run,	 8.606, NULL,	// frame 5
	ai_onfire_run,	19.366, NULL,	// frame 6
	ai_onfire_run,	17.079, NULL,	// frame 7
	ai_onfire_run,	 9.276, NULL,	// frame 8
	ai_onfire_run,	25.777, NULL,	// frame 9
	ai_onfire_run,	22.222, NULL,	// frame 10
	ai_onfire_run,	12.728, NULL,	// frame 11
	ai_onfire_run,	24.948, NULL,	// frame 12
};
mmove_t	whore_move_run_on_fire = {FRAME_run_on_fire_01, FRAME_run_on_fire_13, whore_frames_run_on_fire, NULL};

mframe_t	whore_frames_lsd_tg_run[] = 
{
	ai_sidestep,  0.000, whore_firegun_left,	// frame 0
	ai_sidestep,-15.496, whore_firegun_left,	// frame 1
	ai_sidestep,-19.304, whore_firegun_left,	// frame 2
	ai_sidestep,-15.863, whore_firegun_left,	// frame 3
	ai_sidestep,-22.482, whore_firegun_left,	// frame 4
	ai_sidestep,-17.608, whore_firegun_left,	// frame 5
	ai_sidestep,-18.113, whore_firegun_left,	// frame 6

};
mmove_t	whore_move_lsd_tg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_07, whore_frames_lsd_tg_run, NULL};

mframe_t	whore_frames_rsd_tg_run[] = 
{
	ai_sidestep, 0.000, whore_firegun_right,	// frame 0
	ai_sidestep,22.407, whore_firegun_right,	// frame 1
	ai_sidestep,17.900, whore_firegun_right,	// frame 2
	ai_sidestep,14.898, whore_firegun_right,	// frame 3
	ai_sidestep,18.887, whore_firegun_right,	// frame 4
	ai_sidestep,17.189, whore_firegun_right,	// frame 5
	ai_sidestep,17.301, whore_firegun_right,	// frame 6
};
mmove_t	whore_move_rsd_tg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_07, whore_frames_rsd_tg_run, NULL};

/*
mframe_t	whore_frames_lsd_hmg_run[] = 
{
	ai_sidestep,-	23.733*0.75, whore_firegun_left,	// frame 0
	ai_sidestep,-	18.601*0.75, NULL,	// frame 1
	ai_sidestep,-   31.336*0.75, whore_firegun,	// frame 2
	ai_sidestep,-   39.244*0.75, NULL,	// frame 3
	ai_sidestep,-   26.961*0.75, whore_firegun,	// frame 4
	ai_sidestep,-   23.858*0.75, NULL,	// frame 5
};
mmove_t	whore_move_lsd_hmg_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_06, whore_frames_lsd_hmg_run, NULL};

mframe_t	whore_frames_rsd_hmg_run[] = 
{
	ai_sidestep,	  19.829*0.75, whore_firegun_right,	// frame 0
	ai_sidestep,	  17.364*0.75, NULL,	// frame 1
	ai_sidestep,	  32.611*0.75, whore_firegun,	// frame 2
	ai_sidestep,	  37.973*0.75, NULL,	// frame 3
	ai_sidestep,	  32.279*0.75, whore_firegun,	// frame 4
	ai_sidestep,	  24.741*0.75, NULL,	// frame 5
};
mmove_t	whore_move_rsd_hmg_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_06, whore_frames_rsd_hmg_run, NULL};
*/

mframe_t	whore_frames_lsd_bazooka_run[] = 
{
	ai_sidestep,  0.000, whore_firegun_left,	// frame 0
	ai_sidestep,-15.496, NULL,	// frame 1
	ai_sidestep,-19.304, NULL,	// frame 2
	ai_sidestep,-15.863, NULL,	// frame 3
	ai_sidestep,-22.482, NULL,	// frame 4
	ai_sidestep,-17.608, NULL,	// frame 5
	ai_sidestep,-18.113, NULL,	// frame 6
};
mmove_t	whore_move_lsd_bazooka_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_07, whore_frames_lsd_bazooka_run, NULL};

mframe_t	whore_frames_rsd_bazooka_run[] = 
{
	ai_sidestep, 0.000, whore_firegun_right,	// frame 0
	ai_sidestep,22.407, NULL,	// frame 1
	ai_sidestep,17.900, NULL,	// frame 2
	ai_sidestep,14.898, NULL,	// frame 3
	ai_sidestep,18.887, NULL,	// frame 4
	ai_sidestep,17.189, NULL,	// frame 5
	ai_sidestep,17.301, NULL,	// frame 6
};
mmove_t	whore_move_rsd_bazooka_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_07, whore_frames_rsd_bazooka_run, NULL};


mframe_t	whore_frames_lsd_grenade_run[] = 
{
	ai_sidestep,  0.000, whore_firegun_left,	// frame 0
	ai_sidestep,-15.496, NULL,	// frame 1
	ai_sidestep,-19.304, NULL,	// frame 2
	ai_sidestep,-15.863, NULL,	// frame 3
	ai_sidestep,-22.482, NULL,	// frame 4
	ai_sidestep,-17.608, NULL,	// frame 5
	ai_sidestep,-18.113, NULL,	// frame 6
};
mmove_t	whore_move_lsd_grenade_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_07, whore_frames_lsd_grenade_run, NULL};

mframe_t	whore_frames_rsd_grenade_run[] = 
{
	ai_sidestep, 0.000, whore_firegun_right,	// frame 0
	ai_sidestep,22.407, NULL,	// frame 1
	ai_sidestep,17.900, NULL,	// frame 2
	ai_sidestep,14.898, NULL,	// frame 3
	ai_sidestep,18.887, NULL,	// frame 4
	ai_sidestep,17.189, NULL,	// frame 5
	ai_sidestep,17.301, NULL,	// frame 6
};
mmove_t	whore_move_rsd_grenade_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_07, whore_frames_rsd_grenade_run, NULL};


mframe_t	whore_frames_lsd_flamegun_run[] = 
{
	ai_sidestep,  0.000, whore_firegun_left,	// frame 0
	ai_sidestep,-15.496, whore_firegun_left,	// frame 1
	ai_sidestep,-19.304, whore_firegun_left,	// frame 2
	ai_sidestep,-15.863, whore_firegun_left,	// frame 3
	ai_sidestep,-22.482, whore_firegun_left,	// frame 4
	ai_sidestep,-17.608, whore_firegun_left,	// frame 5
	ai_sidestep,-18.113, whore_firegun_left,	// frame 6
};
mmove_t	whore_move_lsd_flamegun_run = {FRAME_rsd_tg_run_01, FRAME_rsd_tg_run_07, whore_frames_lsd_flamegun_run, NULL};

mframe_t	whore_frames_rsd_flamegun_run[] = 
{
	ai_sidestep, 0.000, whore_firegun_right,	// frame 0
	ai_sidestep,22.407, whore_firegun_right,	// frame 1
	ai_sidestep,17.900, whore_firegun_right,	// frame 2
	ai_sidestep,14.898, whore_firegun_right,	// frame 3
	ai_sidestep,18.887, whore_firegun_right,	// frame 4
	ai_sidestep,17.189, whore_firegun_right,	// frame 5
	ai_sidestep,17.301, whore_firegun_right,	// frame 6
};
mmove_t	whore_move_rsd_flamegun_run = {FRAME_lsd_tg_run_01, FRAME_lsd_tg_run_07, whore_frames_rsd_flamegun_run, NULL};

mframe_t	whore_frames_lsd_shg_run[] = 
{
	ai_sidestep,  0.000, NULL,	// frame 0
	ai_sidestep,-15.072, whore_firegun_left,	// frame 1
	ai_sidestep,-19.236, NULL,	// frame 2
	ai_sidestep,-16.334, whore_shotgun_reload,	// frame 3
	ai_sidestep,-22.102, NULL,	// frame 4
	ai_sidestep,-17.517, NULL,	// frame 5
	ai_sidestep,-18.783, NULL,	// frame 6
};
mmove_t	whore_move_lsd_shg_run = {FRAME_rsd_shg_run_01, FRAME_rsd_shg_run_07, whore_frames_lsd_shg_run, NULL};

mframe_t	whore_frames_rsd_shg_run[] = 
{
	ai_sidestep, 0.000, NULL,	// frame 0
	ai_sidestep,21.514, whore_firegun_right,	// frame 1
	ai_sidestep,18.794, NULL,	// frame 2
	ai_sidestep,14.898, whore_shotgun_reload,	// frame 3
	ai_sidestep,19.542, NULL,	// frame 4
	ai_sidestep,16.533, NULL,	// frame 5
	ai_sidestep,17.042, NULL,	// frame 6
};
mmove_t	whore_move_rsd_shg_run = {FRAME_lsd_shg_run_01, FRAME_lsd_shg_run_07, whore_frames_rsd_shg_run, NULL};

//================================================================================================================
// created moves
mframe_t	whore_frames_avoid_walk[] = 
{
	ai_turn,	  3.636, NULL,	// frame 0
	ai_turn,	  6.504, NULL,	// frame 1
	ai_turn,	  3.111, NULL,	// frame 2
	ai_turn,	  4.200, NULL,	// frame 3
	ai_turn,	  8.913, NULL,	// frame 4
	ai_turn,	  7.640, NULL,	// frame 5
};
mmove_t	whore_move_avoid_walk = {FRAME_walk_gdown_01, FRAME_walk_gdown_06, whore_frames_avoid_walk, AI_EndAttack};

mframe_t	whore_frames_avoid_crouch_walk[] = 
{
	ai_turn,	  5.383, NULL,	// frame 0
	ai_turn,	  5.466, NULL,	// frame 1
	ai_turn,	  3.693, NULL,	// frame 2
	ai_turn,	  5.865, NULL,	// frame 3
	ai_turn,	 13.852, NULL,	// frame 4
	ai_turn,	  6.698, NULL,	// frame 5
	ai_turn,	  3.743, NULL,	// frame 6
};
mmove_t	whore_move_avoid_crouch_walk = {FRAME_crouch_walk_01, FRAME_crouch_walk_07, whore_frames_avoid_crouch_walk, AI_EndAttack};

mframe_t	whore_frames_walk_gdownFLASHLIGHT[] = 
{
	ai_runFLASHLIGHT,	 12.686, NULL,	// frame 0
	ai_runFLASHLIGHT,	  6.612, NULL,	// frame 1
	ai_runFLASHLIGHT,	  4.302, NULL,	// frame 2
	ai_runFLASHLIGHT,	  8.823, NULL,	// frame 3
	ai_runFLASHLIGHT,	  7.734, NULL,	// frame 4
	ai_runFLASHLIGHT,	  9.099, NULL,	// frame 5
	ai_runFLASHLIGHT,	  9.405, NULL,	// frame 6
	ai_runFLASHLIGHT,	  5.060, NULL,	// frame 7
	ai_runFLASHLIGHT,	  4.412, NULL,	// frame 8
	ai_runFLASHLIGHT,	  8.700, NULL,	// frame 9
};
mmove_t	whore_move_walk_gdownFLASHLIGHT = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, whore_frames_walk_gdownFLASHLIGHT, AI_EndRun };

mframe_t	whore_frames_avoid_run[] = 
{
	ai_turn,	 26.748, NULL,	// frame 0
	ai_turn,	 17.188, NULL,	// frame 1
	ai_turn,	 31.486, NULL,	// frame 2
	ai_turn,	 31.052, NULL,	// frame 3
	ai_turn,	 23.944, NULL,	// frame 4
	ai_turn,	 24.549, NULL,	// frame 5	
};
mmove_t	whore_move_avoid_run = {FRAME_run_gun_down_01, FRAME_run_gun_down_06, whore_frames_avoid_run, AI_EndAttack};

mframe_t	whore_frames_avoid_reverse_walk[] = 
{
	ai_turn,	-7.640, NULL,	// frame 5
	ai_turn,	-8.913, NULL,	// frame 4
	ai_turn,	-4.200, NULL,	// frame 3
	ai_turn,	-3.111, NULL,	// frame 2
	ai_turn,	-6.504, NULL,	// frame 1
	ai_turn,	-3.636, NULL,	// frame 0
};
mmove_t	whore_move_avoid_reverse_walk = {FRAME_walk_gdown_06, FRAME_walk_gdown_01, whore_frames_avoid_reverse_walk, AI_EndAttack};

mframe_t	whore_frames_avoid_reverse_run[] = 
{
	ai_turn,	- 24.549, NULL,	// frame 5
	ai_turn,	- 23.944, NULL,	// frame 4
	ai_turn,	- 31.052, NULL,	// frame 3
	ai_turn,	- 31.486, NULL,	// frame 2
	ai_turn,	- 17.188, NULL,	// frame 1
	ai_turn,	- 26.748, NULL,	// frame 0
};
mmove_t	whore_move_avoid_reverse_run = {FRAME_run_gun_down_06, FRAME_run_gun_down_03, whore_frames_avoid_reverse_run, AI_EndAttack};

mframe_t whore_frames_sg_stand[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
 ai_stand,   0.000, whore_talk_think, // frame 16
};
mmove_t whore_move_sg_stand = {FRAME_sg_stand_01, FRAME_sg_stand_17, whore_frames_sg_stand, whore_end_stand};

mframe_t whore_frames_sg_talk1[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
 ai_stand,   0.000, whore_talk_think, // frame 16
 ai_stand,   0.000, whore_talk_think, // frame 17
 ai_stand,   0.000, whore_talk_think, // frame 18
 ai_stand,   0.000, whore_talk_think, // frame 19
 ai_stand,   0.000, whore_talk_think, // frame 20
 ai_stand,   0.000, whore_talk_think, // frame 21
 ai_stand,   0.000, whore_talk_think, // frame 22
 ai_stand,   0.000, whore_talk_think, // frame 23
 ai_stand,   0.000, whore_talk_think, // frame 24
 ai_stand,   0.000, whore_talk_think, // frame 25
 ai_stand,   0.000, whore_talk_think, // frame 26
 ai_stand,   0.000, whore_talk_think, // frame 27
 ai_stand,   0.000, whore_talk_think, // frame 28
 ai_stand,   0.000, whore_talk_think, // frame 29
 ai_stand,   0.000, whore_talk_think, // frame 30
 ai_stand,   0.000, whore_talk_think, // frame 31
 ai_stand,   0.000, whore_talk_think, // frame 32
 ai_stand,   0.000, whore_talk_think, // frame 33
 ai_stand,   0.000, whore_talk_think, // frame 34
 ai_stand,   0.000, whore_talk_think, // frame 35
 ai_stand,   0.000, whore_talk_think, // frame 36
 ai_stand,   0.000, whore_talk_think, // frame 37
};
mmove_t whore_move_sg_talk1 = {FRAME_sg_talk1_01, FRAME_sg_talk1_38, whore_frames_sg_talk1, whore_end_stand};

mframe_t whore_frames_sg_talk2[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
 ai_stand,   0.000, whore_talk_think, // frame 16
 ai_stand,   0.000, whore_talk_think, // frame 17
 ai_stand,   0.000, whore_talk_think, // frame 18
 ai_stand,   0.000, whore_talk_think, // frame 19
 ai_stand,   0.000, whore_talk_think, // frame 20
 ai_stand,   0.000, whore_talk_think, // frame 21
 ai_stand,   0.000, whore_talk_think, // frame 22
 ai_stand,   0.000, whore_talk_think, // frame 23
 ai_stand,   0.000, whore_talk_think, // frame 24
 ai_stand,   0.000, whore_talk_think, // frame 25
 ai_stand,   0.000, whore_talk_think, // frame 26
 ai_stand,   0.000, whore_talk_think, // frame 27
 ai_stand,   0.000, whore_talk_think, // frame 28
 ai_stand,   0.000, whore_talk_think, // frame 29
 ai_stand,   0.000, whore_talk_think, // frame 30
 ai_stand,   0.000, whore_talk_think, // frame 31
 ai_stand,   0.000, whore_talk_think, // frame 32
 ai_stand,   0.000, whore_talk_think, // frame 33
 ai_stand,   0.000, whore_talk_think, // frame 34
 ai_stand,   0.000, whore_talk_think, // frame 35
 ai_stand,   0.000, whore_talk_think, // frame 36
 ai_stand,   0.000, whore_talk_think, // frame 37
};
mmove_t whore_move_sg_talk2 = {FRAME_sg_talk2_01, FRAME_sg_talk2_38, whore_frames_sg_talk2, whore_end_stand};

mframe_t whore_frames_sg_talk3[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
 ai_stand,   0.000, whore_talk_think, // frame 16
 ai_stand,   0.000, whore_talk_think, // frame 17
 ai_stand,   0.000, whore_talk_think, // frame 18
 ai_stand,   0.000, whore_talk_think, // frame 19
 ai_stand,   0.000, whore_talk_think, // frame 20
 ai_stand,   0.000, whore_talk_think, // frame 21
 ai_stand,   0.000, whore_talk_think, // frame 22
};
mmove_t whore_move_sg_talk3 = {FRAME_sg_talk3_01, FRAME_sg_talk3_23, whore_frames_sg_talk3, whore_end_stand};
/*
mframe_t whore_frames_sg_talk4[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
};
mmove_t whore_move_sg_talk4 = {FRAME_sg_talk4_01, FRAME_sg_talk4_15, whore_frames_sg_talk4, whore_end_stand};
*/
mframe_t whore_frames_sg_talk5[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
};
mmove_t whore_move_sg_talk5 = {FRAME_sg_talk5_01, FRAME_sg_talk5_16, whore_frames_sg_talk5, whore_end_stand};

mframe_t whore_frames_sg_talk6[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
 ai_stand,   0.000, whore_talk_think, // frame 16
 ai_stand,   0.000, whore_talk_think, // frame 17
 ai_stand,   0.000, whore_talk_think, // frame 18
 ai_stand,   0.000, whore_talk_think, // frame 19
};
mmove_t whore_move_sg_talk6 = {FRAME_sg_talk6_01, FRAME_sg_talk6_20, whore_frames_sg_talk6, whore_end_stand};

mframe_t whore_frames_sg_talk7[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
 ai_stand,   0.000, whore_talk_think, // frame 16
 ai_stand,   0.000, whore_talk_think, // frame 17
 ai_stand,   0.000, whore_talk_think, // frame 18
 ai_stand,   0.000, whore_talk_think, // frame 19
 ai_stand,   0.000, whore_talk_think, // frame 20
};
mmove_t whore_move_sg_talk7 = {FRAME_sg_talk7_01, FRAME_sg_talk7_21, whore_frames_sg_talk7, whore_end_stand};

mframe_t whore_frames_sg_talk8[] = 
{
 ai_stand,   0.000, whore_talk_think, // frame 0
 ai_stand,   0.000, whore_talk_think, // frame 1
 ai_stand,   0.000, whore_talk_think, // frame 2
 ai_stand,   0.000, whore_talk_think, // frame 3
 ai_stand,   0.000, whore_talk_think, // frame 4
 ai_stand,   0.000, whore_talk_think, // frame 5
 ai_stand,   0.000, whore_talk_think, // frame 6
 ai_stand,   0.000, whore_talk_think, // frame 7
 ai_stand,   0.000, whore_talk_think, // frame 8
 ai_stand,   0.000, whore_talk_think, // frame 9
 ai_stand,   0.000, whore_talk_think, // frame 10
 ai_stand,   0.000, whore_talk_think, // frame 11
 ai_stand,   0.000, whore_talk_think, // frame 12
 ai_stand,   0.000, whore_talk_think, // frame 13
 ai_stand,   0.000, whore_talk_think, // frame 14
 ai_stand,   0.000, whore_talk_think, // frame 15
 ai_stand,   0.000, whore_talk_think, // frame 16
 ai_stand,   0.000, whore_talk_think, // frame 17
 ai_stand,   0.000, whore_talk_think, // frame 18
 ai_stand,   0.000, whore_talk_think, // frame 19
 ai_stand,   0.000, whore_talk_think, // frame 20
};
mmove_t whore_move_sg_talk8 = {FRAME_sg_talk8_01, FRAME_sg_talk8_19, whore_frames_sg_talk8, whore_end_stand};

mframe_t	whore_frames_walk_dokey[] = 
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
mmove_t	whore_move_walk_dokey = {FRAME_walk_gdown_01, FRAME_walk_gdown_10, whore_frames_walk_dokey, EP_ReachedDoKey};

mframe_t	whore_frames_crch_dokey[] = 
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
mmove_t	whore_move_crch_dokey = {FRAME_crch_astand_01, FRAME_crch_astand_20, whore_frames_crch_dokey, EP_EndDoKey};


/*
custom moves to allow hmg sound to and visuals to behave as player hmg
*/
 
mframe_t	whore_frames_hmg_shoot2[] = 
{
	ai_charge,	  0.000, NULL,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, whore_hmg_avoid,	// frame 2
};
mmove_t	whore_move_hmg_shoot2 = {FRAME_hmg_std_01, FRAME_hmg_std_03, whore_frames_hmg_shoot2, AI_EndAttack};

mframe_t	whore_frames_walk_hmg_sht2[] = 
{
	ai_turn,	0.049 , NULL,	// frame 0
	ai_turn,	6.533 , NULL,	// frame 1
	ai_turn,	5.211 , NULL,	// frame 2
	ai_turn,	6.256 , NULL,	// frame 3
	ai_turn,	7.597 , NULL,	// frame 4
	ai_turn,	6.603 , NULL,	// frame 5
	ai_turn,	7.558 , NULL,	// frame 6
	ai_turn,	6.896 , NULL,	// frame 7
	ai_turn,	3.916 , NULL,	// frame 8
	ai_turn,	5.127 , NULL,	// frame 9
	ai_turn,	3.965 , whore_hmg_avoid,	// frame 10
};
mmove_t	whore_move_walk_hmg_sht2 = {FRAME_hmg_wlk_01, FRAME_hmg_wlk_11, whore_frames_walk_hmg_sht2, AI_EndAttack};

mframe_t	whore_frames_run_hmg_sht2[] = 
{
	ai_charge,	  0.000 , NULL,	// frame 0
	ai_charge,	 16.658 , NULL,	// frame 1
	ai_charge,	  9.637 , NULL,	// frame 2
	ai_charge,	 27.670 , NULL,	// frame 3
	ai_charge,	 18.670 , NULL,	// frame 4
	ai_charge,	 14.250 , NULL,	// frame 5
	ai_charge,	 23.489 , whore_hmg_avoid,	// frame 6
};
mmove_t	whore_move_run_hmg_sht2 = {FRAME_hmg_run_01, FRAME_hmg_run_07, whore_frames_run_hmg_sht2, AI_EndAttack};


mframe_t	whore_frames_bazooka_shoot2[] = 
{
	ai_charge,	  0.000, NULL,	// frame 0
	ai_charge,	  0.000, NULL,	// frame 1
	ai_charge,	  0.000, NULL,	// frame 2
};
mmove_t	whore_move_bazooka_shoot2 = {FRAME_hmg_std_01, FRAME_hmg_std_03, whore_frames_bazooka_shoot2, AI_EndAttack};

mframe_t	whore_frames_walk_bazooka_shoot2[] = 
{
	ai_turn,	0.049 , NULL,	// frame 0
	ai_turn,	6.533 , NULL,	// frame 1
	ai_turn,	5.211 , NULL,	// frame 2
	ai_turn,	6.256 , NULL,	// frame 3
	ai_turn,	7.597 , NULL,	// frame 4
	ai_turn,	6.603 , NULL,	// frame 5
	ai_turn,	7.558 , NULL,	// frame 6
	ai_turn,	6.896 , NULL,	// frame 7
	ai_turn,	3.916 , NULL,	// frame 8
	ai_turn,	5.127 , NULL,	// frame 9
	ai_turn,	3.965 , NULL,	// frame 10
};
mmove_t	whore_move_walk_bazooka_shoot2 = {FRAME_hmg_wlk_01, FRAME_hmg_wlk_11, whore_frames_walk_bazooka_shoot2, AI_EndAttack};

mframe_t	whore_frames_run_bazooka_shoot2[] = 
{
	ai_charge,	  0.000 , NULL,	// frame 0
	ai_charge,	 16.658 , NULL,	// frame 1
	ai_charge,	  9.637 , NULL,	// frame 2
	ai_charge,	 27.670 , NULL,	// frame 3
	ai_charge,	 18.670 , NULL,	// frame 4
	ai_charge,	 14.250 , NULL,	// frame 5
	ai_charge,	 23.489 , NULL,	// frame 6
};
mmove_t	whore_move_run_bazooka_shoot2 = {FRAME_hmg_run_01, FRAME_hmg_run_07, whore_frames_run_bazooka_shoot2, AI_EndAttack};
