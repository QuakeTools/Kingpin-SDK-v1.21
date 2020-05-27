mframe_t	dog_frames_amb[] = 
{
	ai_stand,	  0.000, dog_talk_think,	// frame 0
	ai_stand,	  0.000, dog_talk_think,	// frame 1
	ai_stand,	  0.000, dog_talk_think,	// frame 2
	ai_stand,	  0.000, dog_talk_think,	// frame 3
	ai_stand,	  0.000, dog_talk_think,	// frame 4
	ai_stand,	  0.000, dog_talk_think,	// frame 5
	ai_stand,	  0.000, dog_talk_think,	// frame 6
	ai_stand,	  0.000, dog_talk_think,	// frame 7
	ai_stand,	  0.000, dog_talk_think,	// frame 8
	ai_stand,	  0.000, dog_talk_think,	// frame 9
	ai_stand,	  0.000, dog_talk_think,	// frame 10
	ai_stand,	  0.000, dog_talk_think,	// frame 11
};
mmove_t	dog_move_amb = {FRAME_amb_01, FRAME_amb_12, dog_frames_amb, dog_end_stand};

mframe_t	dog_frames_pant[] = 
{
	ai_stand,	  0.000, dog_talk_think,	// frame 0
	ai_stand,	  0.000, dog_talk_think,	// frame 1
	ai_stand,	  0.000, dog_talk_think,	// frame 2
	ai_stand,	  0.000, dog_talk_think,	// frame 3
	ai_stand,	  0.000, dog_talk_think,	// frame 4
	ai_stand,	  0.000, dog_talk_think,	// frame 5
	ai_stand,	  0.000, dog_talk_think,	// frame 6
	ai_stand,	  0.000, dog_talk_think,	// frame 7
	ai_stand,	  0.000, dog_talk_think,	// frame 8
	ai_stand,	  0.000, dog_talk_think,	// frame 9
	ai_stand,	  0.000, dog_talk_think,	// frame 10
	ai_stand,	  0.000, dog_talk_think,	// frame 11
	ai_stand,	  0.000, dog_talk_think,	// frame 12
	ai_stand,	  0.000, dog_talk_think,	// frame 13
};
mmove_t	dog_move_pant = {FRAME_pant_01, FRAME_pant_14, dog_frames_pant, dog_end_stand};

mframe_t	dog_frames_sniff[] = 
{
	ai_stand,	  0.000, dog_talk_think,	// frame 0
	ai_stand,	  0.000, dog_talk_think,	// frame 1
	ai_stand,	  0.000, dog_talk_think,	// frame 2
	ai_stand,	  0.000, dog_talk_think,	// frame 3
	ai_stand,	  0.000, dog_talk_think,	// frame 4
	ai_stand,	  0.000, dog_talk_think,	// frame 5
	ai_stand,	  0.000, dog_talk_think,	// frame 6
	ai_stand,	  0.000, dog_talk_think,	// frame 7
	ai_stand,	  0.000, dog_talk_think,	// frame 8
	ai_stand,	  0.000, dog_talk_think,	// frame 9
	ai_stand,	  0.000, dog_talk_think,	// frame 10
	ai_stand,	  0.000, dog_talk_think,	// frame 11
	ai_stand,	  0.000, dog_talk_think,	// frame 12
	ai_stand,	  0.000, dog_talk_think,	// frame 13
	ai_stand,	  0.000, dog_talk_think,	// frame 14
	ai_stand,	  0.000, dog_talk_think,	// frame 15
	ai_stand,	  0.000, dog_talk_think,	// frame 16
	ai_stand,	  0.000, dog_talk_think,	// frame 17
	ai_stand,	  0.000, dog_talk_think,	// frame 18
	ai_stand,	  0.000, dog_talk_think,	// frame 19
};
mmove_t	dog_move_sniff = {FRAME_sniff_01, FRAME_sniff_20, dog_frames_sniff, dog_end_stand};

mframe_t	dog_frames_bark[] = 
{
	ai_stand,	  0.000, dog_talk_think,	// frame 0
	ai_stand,	  0.000, dog_bark,	// frame 1
	ai_stand,	  0.000, dog_talk_think,	// frame 2
	ai_stand,	  0.000, dog_talk_think,	// frame 3
	ai_stand,	  0.000, dog_bark,	// frame 4
	ai_stand,	  0.000, dog_talk_think,	// frame 5
	ai_stand,	  0.000, dog_talk_think,	// frame 6
	ai_stand,	  0.000, dog_talk_think,	// frame 7
	ai_stand,	  0.000, dog_talk_think,	// frame 8
};
mmove_t	dog_move_bark = {FRAME_bark_01, FRAME_bark_09, dog_frames_bark, dog_end_stand};

mframe_t	dog_frames_growl[] = 
{
	ai_stand,	  0.000, dog_growl,	// frame 0
	ai_stand,	  0.000, NULL,	// frame 1
	ai_stand,	  0.000, NULL,	// frame 2
	ai_stand,	  0.000, NULL,	// frame 3
	ai_stand,	  0.000, NULL,	// frame 4
};
mmove_t dog_move_growl = {FRAME_growl_01, FRAME_growl_05, dog_frames_growl, dog_end_stand};

mframe_t	enemy_dog_frames_pee[] = 
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
	NULL,	  0.000, NULL,	// frame 11
};
mmove_t	enemy_dog_move_pee = {FRAME_pee_01, FRAME_pee_12, enemy_dog_frames_pee, dog_end_stand};

mframe_t	dog_frames_low_atk[] = 
{
	ai_turn2,	  0.000, NULL,	// frame 0
	ai_turn2,	  8.570, dog_bite,	// frame 1
	ai_turn2,	 11.397, dog_bite,	// frame 2
	ai_turn2,	  5.512, NULL,	// frame 3
	ai_turn2,	  1.776, dog_bite,	// frame 4
	ai_turn2,	 -0.788, dog_bite,	// frame 5
	ai_turn2,	  0.808, NULL,	// frame 6
	ai_turn2,	 -1.987, NULL,	// frame 7
};
mmove_t	dog_move_low_atk = {FRAME_low_atk_01, FRAME_low_atk_08, dog_frames_low_atk, AI_EndAttack};

mframe_t	dog_frames_med_atk[] = 
{
	ai_turn2,	  0.000, NULL,	// frame 0
	ai_turn2,	 16.169, NULL,	// frame 1
	ai_turn2,	  6.894, dog_bite,	// frame 2
	ai_turn2,	  3.803, dog_bite,	// frame 3
	ai_turn2,	 -4.625, dog_bite,	// frame 4
	ai_turn2,	  1.215, dog_bite,	// frame 5
	ai_turn2,	  0.501, NULL,	// frame 6
};
mmove_t	dog_move_med_atk = {FRAME_med_atk_01, FRAME_med_atk_07, dog_frames_med_atk, AI_EndAttack};

mframe_t	dog_frames_upr_atk[] = 
{
	NULL,	  0.004, NULL,	// frame 0
	NULL,	  5.304, dog_pounce,	// frame 1
	NULL,	  0.102, dog_pounce,	// frame 2
	NULL,	  8.523, dog_pounce,	// frame 3
	NULL,	 19.589, dog_bite,	// frame 4
	NULL,	  3.179, dog_pounce,	// frame 5
	NULL,	 18.590, dog_bite,	// frame 6
	NULL,	  4.629, dog_pounce,	// frame 7
	NULL,	 -4.434, dog_bite,	// frame 8
	NULL,	  3.514, dog_bite,	// frame 9
};
mmove_t	dog_move_upr_atk = {FRAME_upr_atk_01, FRAME_upr_atk_10, dog_frames_upr_atk, AI_EndAttack};

mframe_t	dog_frames_pain1[] = 
{
	ai_move,	  0.712, NULL,	// frame 0
	ai_move,	 -0.637, NULL,	// frame 1
	ai_move,	-35.731, NULL,	// frame 2
	ai_move,	-17.782, NULL,	// frame 3
	ai_move,	 -1.044, NULL,	// frame 4
};
mmove_t	dog_move_pain1 = {FRAME_pain1_01, FRAME_pain1_05, dog_frames_pain1, AI_EndAttack};

mframe_t	dog_frames_pain2[] = 
{
	ai_move,	 -0.405, NULL,	// frame 0
	ai_move,	 -2.011, NULL,	// frame 1
	ai_move,	-25.452, NULL,	// frame 2
	ai_move,	-24.575, NULL,	// frame 3
	ai_move,	 -3.124, NULL,	// frame 4
	ai_move,	 -2.106, NULL,	// frame 5
	ai_move,	  2.975, NULL,	// frame 6
};
mmove_t	dog_move_pain2 = {FRAME_pain2_01, FRAME_pain2_07, dog_frames_pain2, AI_EndAttack};

mframe_t	dog_frames_pain3[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	  0.000, NULL,	// frame 1
	ai_move,	  0.000, NULL,	// frame 2
	ai_move,	  0.000, NULL,	// frame 3
	ai_move,	  0.000, NULL,	// frame 4
};
mmove_t	dog_move_pain3 = {FRAME_pain3_01, FRAME_pain3_05, dog_frames_pain3, AI_EndAttack};

mframe_t	dog_frames_death1[] = 
{
	ai_move,	 -1.383, NULL,	// frame 0
	ai_move,	-23.848, NULL,	// frame 1
	ai_move,	-39.326, NULL,	// frame 2
	ai_move,	 -4.539, NULL,	// frame 3
	ai_move,	  5.228, NULL,	// frame 4
	ai_move,	 -1.049, NULL,	// frame 5
	ai_move,	 -1.829, NULL,	// frame 6
	ai_move,	  0.942, NULL,	// frame 7
	ai_move,	  1.584, NULL,	// frame 8
	ai_move,	  0.862, NULL,	// frame 9
	ai_move,	  0.140, NULL,	// frame 10
	ai_move,	  0.160, NULL,	// frame 11
	ai_move,	 -0.249, NULL,	// frame 12
	ai_move,	 -0.246, NULL,	// frame 12
	ai_move,	  0.217, NULL,	// frame 12
	ai_move,	  0.650, NULL,	// frame 12
	ai_move,	  0.000, NULL,	// frame 12
};
mmove_t	dog_move_death1 = {FRAME_death1_01, FRAME_death1_17, dog_frames_death1, AI_EndDeath};

mframe_t	dog_frames_death2[] = 
{
	ai_move,	  0.000, NULL,	// frame 0
	ai_move,	 -9.109, NULL,	// frame 1
	ai_move,	 -8.657, NULL,	// frame 2
	ai_move,	-10.863, NULL,	// frame 3
	ai_move,	 -2.848, NULL,	// frame 4
	ai_move,	 -0.382, NULL,	// frame 5
	ai_move,	  0.707, NULL,	// frame 6
	ai_move,	 -0.066, NULL,	// frame 7
	ai_move,	  0.067, NULL,	// frame 8
};
mmove_t	dog_move_death2 = {FRAME_death2_01, FRAME_death2_09, dog_frames_death2, AI_EndDeath};

mframe_t	dog_frames_walk[] = 
{
	ai_run,	  0.022, NULL,	// frame 0
	ai_run,	  0.120, NULL,	// frame 1
	ai_run,	  0.127, NULL,	// frame 2
	ai_run,	  0.026, NULL,	// frame 3
	ai_run,	 -0.324, NULL,	// frame 4
	ai_run,	 -0.720, NULL,	// frame 5
	ai_run,	 -0.664, NULL,	// frame 6
	ai_run,	 -0.627, NULL,	// frame 7
	ai_run,	 -0.346, NULL,	// frame 8
	ai_run,	  0.031, NULL,	// frame 9
	ai_run,	  0.408, NULL,	// frame 10
	ai_run,	  0.707, NULL,	// frame 11
	ai_run,	  0.761, NULL,	// frame 12
};
mmove_t	dog_move_walk = {FRAME_walk_01, FRAME_walk_13, dog_frames_walk, NULL};

mframe_t	dog_frames_trot[] = 
{
	ai_run,	  3.512, NULL,	// frame 0
	ai_run,	  6.911, NULL,	// frame 1
	ai_run,	  2.456, NULL,	// frame 2
	ai_run,	  4.272, NULL,	// frame 3
	ai_run,	  5.160, NULL,	// frame 4
	ai_run,	  4.942, NULL,	// frame 5
	ai_run,	  4.272, NULL,	// frame 6
	ai_run,	  6.615, NULL,	// frame 7
};
mmove_t	dog_move_trot = {FRAME_trot_01, FRAME_trot_08, dog_frames_trot, AI_EndRun};

mframe_t	dog_frames_run[] = 
{
	ai_run,	 11.155, NULL,	// frame 0
	ai_run,	 25.162, NULL,	// frame 1
	ai_run,	 27.589, NULL,	// frame 2
	ai_run,	 21.692, NULL,	// frame 3
};
mmove_t	dog_move_run = {FRAME_run_01, FRAME_run_04, dog_frames_run, AI_EndRun};

mframe_t	dog_frames_run_on_fire[] = 
{
	ai_onfire_run,	 11.155, NULL,	// frame 0
	ai_onfire_run,	 25.162, NULL,	// frame 1
	ai_onfire_run,	 27.589, NULL,	// frame 2
	ai_onfire_run,	 21.692, NULL,	// frame 3
};
mmove_t	dog_move_run_on_fire = {FRAME_run_01, FRAME_run_04, dog_frames_run_on_fire, NULL};


mframe_t	dog_frames_avoid_walk[] = 
{
	ai_turn,	  3.512, NULL,	// frame 0
	ai_turn,	  6.911, NULL,	// frame 1
	ai_turn,	  2.456, NULL,	// frame 2
	ai_turn,	  4.272, NULL,	// frame 3
	ai_turn,	  5.160, NULL,	// frame 4
	ai_turn,	  4.942, NULL,	// frame 5
	ai_turn,	  4.272, NULL,	// frame 6
	ai_turn,	  6.615, NULL,	// frame 7
};
mmove_t	dog_move_avoid_walk = {FRAME_trot_01, FRAME_trot_08, dog_frames_avoid_walk, AI_EndAttack};

mframe_t	dog_frames_avoid_reverse_walk[] = 
{
	ai_turn,	  6.615, NULL,	// frame 0
	ai_turn,	  4.272, NULL,	// frame 1
	ai_turn,	  4.942, NULL,	// frame 2
	ai_turn,	  5.160, NULL,	// frame 3
	ai_turn,	  4.272, NULL,	// frame 4
	ai_turn,	  2.456, NULL,	// frame 5
	ai_turn,	  6.911, NULL,	// frame 6
	ai_turn,	  3.512, NULL,	// frame 7
};
mmove_t	dog_move_avoid_reverse_walk = {FRAME_trot_08, FRAME_trot_01, dog_frames_avoid_reverse_walk, AI_EndAttack};

mframe_t	dog_frames_avoid_run[] = 
{
	ai_turn,	 11.155, NULL,	// frame 0
	ai_turn,	 25.162, NULL,	// frame 1
	ai_turn,	 27.589, NULL,	// frame 2
	ai_turn,	 21.692, NULL,	// frame 3
};
mmove_t	dog_move_avoid_run = {FRAME_run_01, FRAME_run_04, dog_frames_avoid_run, AI_EndAttack};

mframe_t	dog_frames_avoid_reverse_run[] = 
{
	ai_turn,	 21.692, NULL,	// frame 0
	ai_turn,	 27.589, NULL,	// frame 1
	ai_turn,	 25.162, NULL,	// frame 2
	ai_turn,	 11.155, NULL,	// frame 3
};
mmove_t	dog_move_avoid_reverse_run = {FRAME_run_04, FRAME_run_01, dog_frames_avoid_reverse_run, AI_EndAttack};

