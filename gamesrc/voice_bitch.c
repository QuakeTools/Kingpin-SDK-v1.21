
// JOSEPH 16-MAR-99 ALL
#include "g_local.h"

extern voice_table_t f_neutral_talk[];
extern voice_table_t f_neutral_talk_player[];
extern voice_table_t f_neutral_converse[];

// Conversation:
// The neutrals would say to you
// 20

// the response choices haven't been updated

voice_table_t f_neutral_talk[] =
{
	{f_neutral_talk_player, "You're new around here huh?",		"You're new around here huh?",				"actors/female/neutral/new.wav",			3, {0,1,2,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "So what's going on?",				"So what's going on?",						"actors/female/neutral/goingon.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "You must be new around here",		"You must be new around here",				"actors/female/neutral/new2.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "I ain't seen nothin'",				"I ain't seen nothin'",						"actors/female/neutral/seennothing.wav",	3, {6,3,5,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "No shit",							"No @*%$#!",								"actors/female/neutral/noshit.wav",			1, {3,0,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "I don't know shit",				"I don't know @*%$#!",						"actors/female/neutral/knowshit.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Shit baby",						"baby",										"actors/female/neutral/shitbaby.wav",		5, {2,4,7,8,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Just hanging man",					"Just hanging man",							"actors/female/neutral/hanging.wav",		5, {11,18,19,11,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "umhmm",							"umhmm",									"actors/female/neutral/umhmm.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Hey baby",							"Hey baby",									"actors/female/neutral/heybaby.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "Yo, that's it",					"Yo, that's it",							"actors/female/neutral/thatsit.wav",		3, {2,1,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Cool",								"Cool",										"actors/female/neutral/cool.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Alright",							"Alright",									"actors/female/neutral/alright.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Yeah",								"Yeah",										"actors/female/neutral/yeah.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Yeah",								"Yeah",										"actors/female/neutral/yeah2.wav",			2, {6,3,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "uhuh",								"uhuh",										"actors/female/neutral/uhuh.wav",			3, {18,0,6,0,0},0, 0 , TT_NEUTRAL},
};

voice_table_t f_neutral_asshole_talk[] =
{
	
//	{NULL, "infacemf",											"infacemf",									"actors/bitch/infacemf.wav",				0, {0,0,0,0,0},0, false , TT_NEUTRAL},
//	{NULL, "mf",												"mf",										"actors/bitch/mf.wav",						0, {0,0,0,0,0},0, false , TT_NEUTRAL},
//	{NULL, "takethatmf",										"takethatmf",								"actors/bitch/takethatmf.wav",				0, {0,0,0,0,0},0, false , TT_NEUTRAL},

	{NULL, "In your face motherfucker",							"In your face @*%$#!",						"actors/female/fighting/infacemf.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "Die you son of a bitch",							"Die you son of a @*%$#!",					"actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "Die you motherfucker",								"Die you @*%$#!",							"actors/female/fighting/f_die2.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "I'll fuck you up you son of a bitch",				"I'll @*%$#! you up you son of a @*%$#!",	"actors/female/fighting/f_die3.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "Take that you motherfucker",						"Take that you @*%$#!",						"actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL}

};

// Player talk to a neutral

// 10

voice_table_t f_neutral_talk_player[] =
{
	/*
	{f_neutral_talk, "Hey bud",									"Hey bud",									"actors/male/neutral/play1.wav",	0, {0,0,0,0,0},0, true},
	{f_neutral_talk, "Yo",										"Yo",										"actors/male/neutral/play2.wav",	0, {0,0,0,0,0},0, true},
	{f_neutral_talk, "Whats up",								"Whats up",									"actors/male/neutral/play3.wav",	3, {9,5,11,0,0},0, 0},
	{f_neutral_talk, "So what's all the commotion",				"So what's all the commotion",				"actors/male/neutral/play4.wav",	3, {8,11,14,0,0},0, 0},
	{f_neutral_talk, "Fuck me, Freddy is it you?",				"@*%$#! me, Freddy is it you?",				"actors/male/neutral/play5.wav",	4, {0,9,12,13,0},0, 0},

	{f_neutral_talk, "Seen Pauly around?",						"Seen Pauly around?",						"actors/male/neutral/play6.wav",	2, {4,1,0,0,0},0, 0},
	{f_neutral_talk, "That fuckin cop",							"That @*%$#!in cop",						"actors/male/neutral/play7.wav",	2, {8,14,0,0,0},0, true},
	{f_neutral_talk, "Shove off...",							"Shove off...",								"actors/male/neutral/play8.wav",	3, {11,6,4,0,0},0, true},
	{f_neutral_talk, "Hit the dust",							"Hit the dust",								"actors/male/neutral/play9.wav",	3, {11,6,4,0,0},0, true},
	{f_neutral_talk, "Get lost",								"Get lost",									"actors/male/neutral/play10.wav",	3, {11,6,4,0,0},0, true}
	*/
	{f_neutral_talk, "um hmm",									"um hmm",									"actors/skidrow/leroy/conv6.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Yeah I heard that baby",					"Yeah I heard that baby",					"actors/skidrow/leroy/conv7.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Yeah that's cool",						"Yeah that's cool",							"actors/skidrow/leroy/cool.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
}; 

// Neutrals converse among themselves

// 20
voice_table_t f_neutral_converse[] = 
{
	{f_neutral_talk, "Yo, that's it",							"Yo, that's it",							"actors/female/neutral/thatsit.wav",		3, {2,1,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Shit baby",								"baby",										"actors/female/neutral/shitbaby.wav",		5, {2,4,7,8,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "No shit",									"No @*%$#!",								"actors/female/neutral/noshit.wav",			1, {3,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "You're new around here huh?",				"You're new around here huh?",				"actors/female/neutral/new.wav",			3, {0,1,2,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "You must be new around here",				"You must be new around here",				"actors/female/neutral/new2.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "Cool",									"Cool",										"actors/female/neutral/cool.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Alright",									"Alright",									"actors/female/neutral/alright.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Yeah",									"Yeah",										"actors/female/neutral/yeah.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Yeah",									"Yeah",										"actors/female/neutral/yeah2.wav",			2, {6,3,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "I ain't seen nothin'",					"I ain't seen nothin'",						"actors/female/neutral/seennothing.wav",	3, {6,3,5,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "umhmm",									"umhmm",									"actors/female/neutral/umhmm.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Hey baby",								"Hey baby",									"actors/female/neutral/heybaby.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "So what's going on?",						"So what's going on?",						"actors/female/neutral/goingon.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "I don't know shit",						"I don't know @*%$#!",						"actors/female/neutral/knowshit.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Just hanging man",						"Just hanging man",							"actors/female/neutral/hanging.wav",		5, {11,18,19,11,9},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "uhuh",									"uhuh",										"actors/female/neutral/uhuh.wav",			3, {18,0,6,0,0},0, 0 , TT_NEUTRAL},
};

// profanity
// 20

voice_table_t f_profanity_level1[] =
{
	{f_neutral_asshole_talk, "You talkin' to me?",				"You talkin' to me?",						"actors/female/profanity/level1/f_cuss1-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "back your ugly ass up",			"back your ugly @*%$#! up",					"actors/female/profanity/level1/f_cuss1-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "piss the fuck off",				"piss the @*%$#! off",						"actors/female/profanity/level1/f_cuss1-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "I'll bust a cap in yo ass",		"I'll bust a cap in yo @*%$#!",				"actors/female/profanity/level1/f_cuss1-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "Your mama made that?",			"Your mama made that?",						"actors/female/profanity/level1/f_cuss1-5.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}

};
//20

voice_table_t f_profanity_level2[] =
{
	{NULL, "motherfucker what you lookin at?",					"what are You lookin at?",					"actors/female/profanity/level2/f_cuss2-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "eat me you asshole",								"@*%$#! me you @*%$#!",						"actors/female/profanity/level2/f_cuss2-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "keep talkin' asshole",								"keep talkin' @*%$#!",						"actors/female/profanity/level2/f_cuss2-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "I'll bust your face",								"I'll bust your face",						"actors/female/profanity/level2/f_cuss2-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
};

//3
voice_table_t f_profanity_level3[] =
{
	{NULL, "Yo, fuck you man",									"Yo, @*%$#! you man",						"actors/female/profanity/level3/f_cuss3-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "back the fuck up bitch",							"back the @*%$#! up @*%$#!",				"actors/female/profanity/level3/f_cuss3-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fuck you you motherfucker",							"@*%$#! you @*%$#!",						"actors/female/profanity/level3/f_cuss3-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
};

//===================================================================================

voice_table_t f_followme[] = 

// GARY 11-MAR-99

{
	{NULL, "Let's go",											"Let's go",									"actors/player/male/followme/follow1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Come on",											"Come on",									"actors/player/male/followme/follow2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's go this way",									"Let's go this way",						"actors/player/male/followme/follow3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Follow me",											"Follow me",								"actors/player/male/followme/follow4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's blow",										"Let's blow",								"actors/player/male/followme/follow5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}
};
// END GARY

voice_table_t f_moveout[] = 
{

// we need to get Drew to give move out orders so this is placeholder
    // Gary
	{NULL, "Alright, let's move out",							"Alright, let's move out",					"actors/player/male/moveout/moveout1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Alright, move it",									"Alright, move it",							"actors/player/male/moveout/moveout2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's head out",									"Let's head out",							"actors/player/male/moveout/moveout3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's get the fuck out of here",					"Let's get the @*%$#! out of here",			"actors/player/male/moveout/moveout4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "C'mon let's go",									"C'mon let's go",							"actors/player/male/moveout/moveout5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},

};

voice_table_t f_holdposition[] =
{

// we need to get Drew to give hold position orders so this is just the responses
    // Gary
	{NULL, "Stop here",											"Stop here",								"actors/player/male/hold/hold1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Wait here",											"Wait here",								"actors/player/male/hold/hold2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Stay right here",									"Stay right here",							"actors/player/male/hold/hold3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Don't move",										"Don't move",								"actors/player/male/hold/hold4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Park your ass",										"Park your @*%$#!",							"actors/player/male/hold/hold5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};

//===================================================================================

voice_table_t f_fightsounds[] =
{
	{NULL, "In your face motherfucker",							"In your face @*%$#!",						"actors/female/fighting/infacemf.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Die you son of a bitch",							"Die you son of a @*%$#!",					"actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Take that you motherfucker",						"Take that you @*%$#!",						"actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},

	{NULL, "back the fuck off asshole",							"back the @*%$#!",							"actors/female/fighting/f_backoff.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Die you son of a bitch",							"Die you son of a @*%$#!",					"actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Die you motherfucker",								"Die you @*%$#!",							"actors/female/fighting/f_die2.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "I'll fuck you up you son of a bitch",				"I'll @*%$#! you up you son of a @*%$#!",	"actors/female/fighting/f_die3.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "take that you motherfucker",						"take that you @*%$#!",						"actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
	
};

// These are used for all specific speech functions throughout the game
// NOTE: Altering the order of these items will cause problems
voice_table_t f_specific[] =
{
	{NULL, "motherfucker what you lookin at?",					"what are You lookin at?",			"actors/female/profanity/level2/f_cuss2-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// first time they see you
	{NULL, "eat me you asshole",								"@*%$#! me you @*%$#!",				"actors/female/profanity/level2/f_cuss2-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// if you leave
	{NULL, "keep talkin' asshole",								"keep talkin' @*%$#!",				"actors/female/profanity/level2/f_cuss2-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// if you come back after leaving
	{NULL, "I'll bust your face",								"I'll bust your face",				"actors/female/profanity/level2/f_cuss2-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// profanity level 3
};


voice_table_t f_backoff[] =
{
	{NULL, "Yo put that away man",								"Yo put that away man",						"actors/female/beth_specific/putaway.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Back off motherfucker",								"Back off @*%$#!",							"actors/female/beth_specific/backoff.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Yo, drop that shit motherfucker",					"Yo, drop that @*%$#! @*%$#!",				"actors/female/beth_specific/droppiece.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Don't be pulling that shit on me",					"Don't be pulling that @*%$#! on me",		"actors/female/beth_specific/pullshit.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
};


voice_table_t lisa_specific[] =
{
	{NULL, "You might want to try Pawn-o-Matic",					"You might want to try Pawn-o-Matic",					"actors/female/lisa_specific/pawnomatic1.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE},	// profanity level 3
	{NULL, "Try that Pawn-o-Matic down the street",					"Try that Pawn-o-Matic down the street",				"actors/female/lisa_specific/pawnomatic2.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
//2
	{NULL, "Yo man, you'd best find a piece",						"Yo man, you'd best find a piece",						"actors/female/lisa_specific/findpiece.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE }, // first time they see you
	{NULL, "You'd best get strapped",								"You'd best get strapped",								"actors/female/lisa_specific/getstrapped.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE},	// if you leave
	{NULL, "You gonna need a gun",									"You gonna need a gun",									"actors/female/lisa_specific/needgun.wav",			0, {0,0,0,0,0},0, 0 , TT_POSITIVE},	// if you come back after leaving
//5
	{NULL, "You betta back off, those guys'll rip you to shreds",	"You betta back off, those guys'll rip you to shreds",	"actors/female/lisa_specific/ripshreds.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "They'll tear you up",									"They'll tear you up",									"actors/female/lisa_specific/tearup.wav",			0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "There's some tough motherfuckers back there",			"There's some tough @*%$#!s back there",				"actors/female/lisa_specific/toughbastards.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	
};

voice_table_t beth_specific[] =
{
	{NULL, "Wait 'til they're disctracted by the radio",		"Wait 'til they're disctracted by the radio",		"actors/female/beth_specific/distracted.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, // first time they see you
	{NULL, "You best wait 'til that game is goin'!",			"You best wait 'til that game is goin'!",			"actors/female/beth_specific/gamegoing.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},	// if you leave
	{NULL, "You better not go back there",						"You better not go back there",						"actors/female/beth_specific/notgoback.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},	// if you come back after leaving
	{NULL, "Make your move when the radio's loud",				"Make your move when the radio's loud",				"actors/female/beth_specific/radioloud.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},	// profanity level 3

// note to self
// place holders for three more generic sounds

	{NULL, "You betta back off, those guys'll rip you to shreds",				"You betta back off, those guys'll rip you to shreds",	"actors/female/lisa_specific/ripshreds.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "They'll tear you up",												"They'll tear you up",									"actors/female/lisa_specific/tearup.wav",			0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "There's some tough motherfuckers back there",						"There's some tough @*%$#!s back there",				"actors/female/lisa_specific/toughbastards.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},

	{NULL, "back off motherfucker",								"back off @*%$#!",							"actors/female/beth_specific/backoff.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "Yo put that away man",								"Yo put that away man",						"actors/female/beth_specific/putaway.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
};


// JOSEPH 7-MAR-99
voice_table_t mona_specific[] =
{

    // JOSEPH 19-MAR-99
	// 0, Lamont alive - random
	{NULL, "What up sugar?",													"What up sugar?",													"actors/female/mona/nobar1.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "You been in the bar yet?",											"You been in the bar yet?",											"actors/female/mona/nobar2.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "Go in the bar and talk to Lenny",									"Go in the bar and talk to Lenny",									"actors/female/mona/nobar4.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "I hear you looking to get outta here",								"I hear you looking to get outta here",								"actors/female/mona/nobar6.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	// 4, Be careful of Lamont
	{NULL, "Lamont's gonnna kill Lenny if he comes out",						"Lamont's gonnna kill Lenny if he comes out",						"actors/female/mona/lamont1.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "Good thing they won't let Lamont's crazy ass in that bar",			"Good thing they won't let Lamont's crazy @*%$#! in that bar",		"actors/female/mona/lamont3.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "Yeah, Lenny threw Lamont outta his apartment",						"Yeah, Lenny threw Lamont outta his apartment",						"actors/female/mona/lamont4.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "You best stay away from Lamont if you know what's good for you",	"You best stay away from Lamont if you know what's good for you",	"actors/female/mona/lamont6.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	// 8, Been in bar
	{NULL, "That bar is happenin' huh",											"That bar is happenin' huh",										"actors/female/mona/bar1.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "I hope you talked to the right people in there",					"I hope you talked to the right people in there",					"actors/female/mona/bar2.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	// 10, Talk to Lenny
	{NULL, "So you talk to Lenny yet?",											"So you talk to Lenny yet?",										"actors/female/mona/lenny1.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "I hope Lenny set you straight",										"I hope Lenny set you straight",									"actors/female/mona/lenny3.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "Did Lenny give you some good information?",							"Did Lenny give you some good information?",						"actors/female/mona/lenny4.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	// 13, You killed Lamont
	{NULL, "Damn, you one badass motherfucker",									"Damn, you one bad@*%$#!",											"actors/female/mona/badass.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "Shit man, you took Lamont out!",									"Man, you took Lamont out!",										"actors/female/mona/badass2.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	// 15, You pissed off Mona
	{NULL, "Hey motherfucker, don't be pullin' no piece out on me!",			"Hey @*%$#!, don't be pullin' no piece out on me!",					"actors/female/mona/angry1.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "I will bust a cap in yo ass, you do understand",					"I will bust a cap in yo @*%$#!, you do understand",				"actors/female/mona/angry2.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "Now that's it motherfucker",										"Now that's it @*%$#!",												"actors/female/mona/angry3.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "I can get down with yo ass",										"I can get down with yo @*%$#!",									"actors/female/mona/angry4.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
	{NULL, "Yeah, fuck you too",												"Yeah, @*%$#! you too",												"actors/female/mona/angry5.wav",	0, {0,0,0,0,0},0, 0 , TT_POSITIVE},
    // END JOSEPH
};
// END JOSEPH

// JOSEPH 29-MAY-99
voice_table_t female_specific[] = 
{
	// pain
	{NULL, "",		"",			"actors/female/pain1.wav",			0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",			"actors/female/pain2.wav",			0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",			"actors/female/pain3.wav",			0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",			"actors/female/pain4.wav",			0, {0,0,0,0,0},0,0 , TT_NONE},
	// death
	{NULL, "",		"",			"actors/female/death1.wav",			0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",			"actors/female/death2.wav",			0, {0,0,0,0,0},0,0 , TT_NONE},
	// fire death
	{NULL, "",		"",			"actors/female/f_flamedeath1.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",			"actors/female/f_flamedeath2.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",			"actors/female/f_flamedeath2.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
};
// END JOSEPH

// JOSEPH 12-MAR-99
voice_table_t f_grunting[] =
{
	{NULL, " ",		" ",		"actors/female/fighting/grunt1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, " ",		" ",		"actors/female/fighting/grunt2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, " ",		" ",		"actors/female/fighting/grunt3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, " ",		" ",		"actors/female/fighting/grunt4.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, " ",		" ",		"actors/female/fighting/grunt5.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};
// END JOSEPH

voice_table_t yolanda_specific[] =
{
	{NULL, "Don't go back there... Nicki's boys'll fuck you up",	"Don't go back there... Nicki's boys'll @*%$#! you up",		"actors/female/yolanda/backthere.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 
	{NULL, "Those are Nicki Blanco's boys",							"Those are Nicki Blanco's boys",							"actors/female/yolanda/blancoboys.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 
	{NULL, "You gonna need a BIGGER gun baby",						"You gonna need a BIGGER gun baby",							"actors/female/yolanda/biggergun.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 

	{NULL, "Hey you been to pawnomatic yet?",						"Hey you been to pawnomatic yet?",							"actors/female/yolanda/pawnomatic.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, // first time they see you
	{NULL, "Been to club swank?",									"Been to club swank?",										"actors/female/yolanda/swank.wav",			0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 
	{NULL, "You one bad-assed motherfucker...",						"You one bad @*%$#!",										"actors/female/yolanda/badass.wav",			0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 

	{NULL, "Hey... gimme 10 bucks and I'll distract 'em for you",	"Hey... gimme 10 bucks and I'll distract 'em for you",		"actors/female/yolanda/distract1.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 
	{NULL, "Hey... gimme 20 bucks and I'll distract 'em for you",	"Hey... gimme 20 bucks and I'll distract 'em for you",		"actors/female/yolanda/distract2.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 
	{NULL, "Come back later	then",									"Come back later then",										"actors/female/yolanda/later.wav",			0, {0,0,0,0,0},0, 0 , TT_QUESTION}, 

	{NULL, "Hey... you ready for me now?",							"Hey... you ready for me now?",								"actors/female/yolanda/readynow.wav",		0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 
	{NULL, "Let's do it",											"Let's do it",												"actors/female/yolanda/doit.wav",			0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 
	{NULL, "Here I go",												"Here I go",												"actors/female/yolanda/herego.wav",			0, {0,0,0,0,0},0, 0 , TT_POSITIVE}, 

	{NULL, "Wassup?",												"Wassup?",													"actors/female/yolanda/wassup.wav",			0, {0,0,0,0,0},0, 0 , TT_NONE},
	{NULL, "Hey boys, wass shakin'",								"Hey boys, wass shakin'",									"actors/female/yolanda/shakin.wav",			0, {0,0,0,0,0},0, 0 , TT_NONE}, 
	{NULL, "Ooohh... How y'all doin'",								"Ooohh... How y'all doin'",									"actors/female/yolanda/howall.wav",			0, {0,0,0,0,0},0, 0 , TT_NONE}, 

	{NULL, "Hey, y'all want to party?",								"Hey, y'all want to party?",								"actors/female/yolanda/party.wav",			0, {0,0,0,0,0},0, 0 , TT_NONE}, 
	{NULL, "Mmmmmm-Hmmmmmmm",										"Mmmmmm-Hmmmmmmm",											"actors/female/yolanda/mmhmm.wav",			0, {0,0,0,0,0},0, 0 , TT_NONE},
	{NULL, "Fuck you, I ain't helpin' you asshole...",				"I ain't helpin' you @*%$#!...",							"actors/female/yolanda/asshole.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 

	{NULL, "Hey, fuck you motherfucker!",							"Hey, @*%$#! you @*%$#!!",									"actors/female/yolanda/fuckyou.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 
	{NULL, "Go do it yourself, shithead",							"Go do it yourself, @*%$#!",								"actors/female/yolanda/shithead.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 
	{NULL, "Piss off...",											"@*%$#! off...",											"actors/female/yolanda/pissoff.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 

	{NULL, "Don't pull a fuckin' piece on me...",					"Don't pull a @*%$#! piece on me...",						"actors/female/yolanda/piece.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 
	{NULL, "Drop it",												"Drop it",													"actors/female/yolanda/dropit.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 
	{NULL, "Fuckin' die!",											"Die!",														"actors/female/yolanda/die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 

	{NULL, "That's it, motherfucker!",								"That's it, @*%$#!!",										"actors/female/yolanda/mf.wav",				0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}, 
	{NULL, "Shit... you ain't got any money!",						"@*%$#!... you ain't got any money!",						"actors/female/yolanda/nomoney.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
};

// todo: Gary sound todo
// new sounds for yolanda
// sounds for a female friendly hire
// momo welcome to swank


// hiredgal_specific is missing 3 hired wav files

voice_table_t hiredgal_specific[] =
{
	{NULL, "you got the cash?",										"you got the cash?",									"actors/female/hiredgirl/gotcash1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "So, you got the money?",								"So, you got the money?",								"actors/female/hiredgirl/gotcash2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "No?  I'll be here if you change your mind",				"No?  I'll be here if you change your mind",			"actors/female/hiredgirl/changemind.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "come back when you got the money",						"come back when you got the money",						"actors/female/hiredgirl/comeback1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll be right here waitin'",							"I'll be right here waitin'",							"actors/female/hiredgirl/waiting1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll be right here waitin'",							"I'll be right here waitin'",							"actors/female/hiredgirl/waiting2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},

	{NULL, "Come see me when your gang's not full up",				"Come see me when your gang's not full up",				"actors/female/hiredgirl/full1.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "Your gang's full",										"Your gang's full",										"actors/female/hiredgirl/full2.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{NULL, "Alright, let's go",										"Alright, let's go",									"actors/female/hiredgirl/hired1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Alright, I'm all yours",								"Alright, I'm all yours",								"actors/female/hiredgirl/hired2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
    {NULL, "I'm hired",												"I'm hired",											"actors/female/hiredgirl/hired3.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
																	
	{NULL, "when you got the money, come back and see me",			"when you got the money, come back and see me",			"actors/female/hiredgirl/comeback2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
																	
	{NULL, "FIXME:Sorry, I can't run with you...",					"FIXME:Sorry, I can't run with you...",					"actors/male/hiredguy/louiesorry.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME:Hey, I'm working for Louie right now",			"FIXME:Hey, I'm working for Louie right now",			"actors/male/hiredguy/louiework.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME:Hey, talked to Louie yet?",						"FIXME:Hey, talked to Louie yet?",						"actors/male/hiredguy/louietalked.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME:Talk to the boss",								"FIXME:Talk to the boss",								"actors/male/hiredguy/louieboss.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};																	

voice_table_t hiredgal_ask[] =
{
	{NULL, "I'll run with you for 10 bucks",						"I'll run with you for 10 bucks",			"actors/female/hiredgirl/10bucks1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "$10 I'm all yours",										"$10 I'm all yours",						"actors/female/hiredgirl/10bucks2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll watch your back for 25 bucks",						"I'll watch your back for 25 bucks",		"actors/female/hiredgirl/25bucks1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll run with you for 25 bucks",						"I'll run with you for 25 bucks",			"actors/female/hiredgirl/25bucks2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll join your crew for 50 bucks",						"I'll join your crew for 50 bucks",			"actors/female/hiredgirl/50bucks1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "You want me?  50 bucks",								"You want me?  50 bucks",					"actors/female/hiredgirl/50bucks2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "You want me?  $75",										"You want me?  $75",						"actors/female/hiredgirl/75bucks1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "You want me... $75",									"You want me... $75",						"actors/female/hiredgirl/75bucks2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll join your crew... for $100",						"I'll join your crew... for $100",			"actors/female/hiredgirl/100bucks1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll join your gang for 100 bucks",						"I'll join your gang for 100 bucks",		"actors/female/hiredgirl/100bucks2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};

voice_table_t steeltown_brittany[]= 
{
	// clue about armor
	{NULL, "there's new package for Moker ordered in the pawnomatic basement.  It's that fancy new armor he ordered",	"there's new package for Moker ordered in the pawnomatic basement.  It's that fancy new armor he ordered",					"actors/female/brittany/clue1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	
	{NULL, "Who needs your sorry ass around here?",																		"Who needs your sorry @*%$#! around here?",															"actors/female/brittany/curse1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Okay, be like that",																						"Okay, be like that"		,																		"actors/female/brittany/curse2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Up yours you foul mouth little creep",																		"Up yours you foul mouth little creep",																"actors/female/brittany/curse3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "It's 2 for 1 ladies night down at the Boiler Room",															"It's 2 for 1 ladies night down at the Boiler Room",												"actors/female/brittany/amb1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Just got through talking with Bambi...  She's feeling pretty low",											"Just got through talking with Bambi...  She's feeling pretty low",									"actors/female/brittany/amb2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Seems like Moker get's a new shipment almost every day now.  He must be planning something big",			"Seems like Moker get's a new shipment almost every day now.  He must be planning something big",	"actors/female/brittany/amb3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};



voice_table_t steeltown_bambi[]=
{
	{NULL,"Mister, can you help me out?  It's my brother David.  He's a prisoner at Moker's steel mill",		"Mister, can you help me out?  It's my brother David.  He's a prisoner at Moker's steel mill",	"actors/female/bambi/clue.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	//3 back without David
	{NULL,"I thought you were gonna bring David back",															"I thought you were gonna bring David back",								"actors/female/bambi/scold1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL,"Didn't you find him yet?",																			"Didn't you find him yet?",													"actors/female/bambi/scold2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,"You didn't rescue David?  What are you doing back here?",											"You didn't rescue David?  What are you doing back here?",					"actors/female/bambi/scold3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	//3 you're not gonna find him here
	{NULL,"Please mister. You've got to hurry. That mill is really dangerous",									"Please mister. You've got to hurry. That mill is really dangerous",		"actors/female/bambi/hurry1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,"Well, he isn't likely to walk in here on his own.  Go get him",										"Well, he isn't likely to walk in here on his own.  Go get him",			"actors/female/bambi/hurry2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,"What are you waiting for?  I told you he's at the mill",												"What are you waiting for?  I told you he's at the mill",					"actors/female/bambi/hurry3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	//3 hostile
	{NULL,"Fuck off, you prick",																				"@*%$#! off, you @*%$#!",													"actors/female/bambi/curse1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL,"Some help you are.  What a loser",																	"Some help you are.  What a loser",											"actors/female/bambi/curse2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL,"Piss off.  I don't have time for your shit",															"@*%$#! off.  I don't have time for your @*%$#!",							"actors/female/bambi/curse3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	//Thanks for saving my brother
	{NULL,"You saved him.  How can I ever thank you?   Here, one of Moker's thugs left his keys",				"You saved him.  How can I ever thank you?   Here, one of Moker's thugs left his keys",	"actors/female/bambi/success.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	//Couldn't save David
	{NULL,"David dead?  I can't believe it... Here, one of Moker's thugs left his keys",						"David dead?  I can't believe it... Here, one of Moker's thugs left his keys",	"actors/female/bambi/failure.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	{NULL,"Those guys are over at Moker's right now.  You better hurry",										"Those guys are over at Moker's right now.  You better hurry",				"actors/female/bambi/getgoin1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,"I thought you were going after Moker and his gang",													"I thought you were going after Moker and his gang",						"actors/female/bambi/getgoin2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,"Well, if you're gonna stick around here, at least buy a drink",										"Well, if you're gonna stick around here, at least buy a drink",			"actors/female/bambi/getgoin3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};


/////////////////////////////////////////////////////////////////////////////////////////
// radio city
/////////////////////////

voice_table_t rc_f_neutral_talk[] =
{
	{f_neutral_talk_player, "This your first time in RC?",				"This your first time in RC?",					"rc/actors/female/neutral/new.wav",			3, {0,1,2,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Some serious shit's going down",			"Some serious @*%$#!'s going down",				"rc/actors/female/neutral/goingon.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "You must be the hardcore motherfucker",	"You must be the hardcore xxx",					"rc/actors/female/neutral/new2.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Fuckin' Dragons are gettin' worked",		"@*%$#! Dragons are gettin' worked",			"rc/actors/female/neutral/seennothing.wav",	3, {6,3,5,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "I heard that",								"I heard that",									"rc/actors/female/neutral/noshit.wav",			1, {3,0,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "I ain't got nothin' to do with that shit",	"I ain't got nothin' to do with that @*%$#!",	"rc/actors/female/neutral/knowshit.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "So what you got in mind baby?",			"So what you got in mind baby?",				"rc/actors/female/neutral/shitbaby.wav",		5, {2,4,7,8,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Just layin' low 'til this shit blows over","Just layin' low 'til this @*%$#! blows over",	"rc/actors/female/neutral/hanging.wav",		5, {11,18,19,11,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Fuckin' Jokers are out for blood",			"@*%$#! Jokers are out for blood",				"rc/actors/female/neutral/umhmm.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Hey baby, you for real?",					"Hey baby, you for real?",						"rc/actors/female/neutral/heybaby.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "You got that shit right",					"You got that @*%$#! right",					"rc/actors/female/neutral/thatsit.wav",		3, {2,1,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "That's Kool and the Gang",					"That's Kool and the Gang",						"rc/actors/female/neutral/cool.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Fuckin' aye man",							"@*%$#! aye man",								"rc/actors/female/neutral/alright.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Fuck yeah",								"@*%$#! Yeah",									"rc/actors/female/neutral/yeah.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "Yeah",										"Yeah",											"rc/actors/female/neutral/yeah2.wav",			2, {6,3,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "uhuh",										"uhuh",											"rc/actors/female/neutral/uhuh.wav",			3, {18,0,6,0,0},0, 0 , TT_NEUTRAL},
/*
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/new.wav",			3, {0,1,2,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/goingon.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/new2.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/seennothing.wav",	3, {6,3,5,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/noshit.wav",			1, {3,0,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/knowshit.wav",	4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/shitbaby.wav",	5, {2,4,7,8,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/hanging.wav",		5, {11,18,19,11,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/umhmm.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/heybaby.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/thatsit.wav",		3, {2,1,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/cool.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/alright.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/yeah.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/yeah2.wav",		2, {6,3,0,0,0},0, 0 , TT_NEUTRAL},
																											
	{f_neutral_talk_player, "FIXME",		"FIXME",			"rc/actors/female/neutral/uhuh.wav",		3, {18,0,6,0,0},0, 0 , TT_NEUTRAL},
*/
};

voice_table_t rc_f_neutral_asshole_talk[] =
{
	{NULL, "In your face motherfucker",							"In your face @*%$#!",						"rc/actors/female/fighting/infacemf.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "Die you son of a bitch",							"Die you son of a @*%$#!",					"rc/actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "Die you motherfucker",								"Die you @*%$#!",							"rc/actors/female/fighting/f_die2.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "I'll fuck you up you son of a bitch",				"I'll @*%$#! you up you son of a @*%$#!",	"rc/actors/female/fighting/f_die3.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "Take that you motherfucker",						"Take that you @*%$#!",						"rc/actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL}
	
/*
//	{NULL, "infacemf",			"infacemf",						"actors/bitch/infacemf.wav",				0, {0,0,0,0,0},0, false , TT_NEUTRAL},
//	{NULL, "mf",				"mf",							"actors/bitch/mf.wav",						0, {0,0,0,0,0},0, false , TT_NEUTRAL},
//	{NULL, "takethatmf",		"takethatmf",					"actors/bitch/takethatmf.wav",				0, {0,0,0,0,0},0, false , TT_NEUTRAL},

	{NULL, "FIXME",				"FIXME",						"rc/actors/female/fighting/infacemf.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "FIXME",				"FIXME",						"rc/actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "FIXME",				"FIXME",						"rc/actors/female/fighting/f_die2.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "FIXME",				"FIXME",						"rc/actors/female/fighting/f_die3.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{NULL, "FIXME",				"FIXME",						"rc/actors/female/fighting/f_takethat.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL}
*/
};

voice_table_t rc_f_neutral_talk_player[] =
{
	{f_neutral_talk, "um hmm",									"um hmm",									"rc/actors/skidrow/leroy/conv6.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Yeah I heard that baby",					"Yeah I heard that baby",					"rc/actors/skidrow/leroy/conv7.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Yeah that's cool",						"Yeah that's cool",							"rc/actors/skidrow/leroy/cool.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
/*	/*
	{f_neutral_talk, "Hey bud",							"Hey bud",						"actors/male/neutral/play1.wav",	0, {0,0,0,0,0},0, true},
	{f_neutral_talk, "Yo",								"Yo",							"actors/male/neutral/play2.wav",	0, {0,0,0,0,0},0, true},
	{f_neutral_talk, "Whats up",						"Whats up",						"actors/male/neutral/play3.wav",	3, {9,5,11,0,0},0, 0},
	{f_neutral_talk, "So what's all the commotion",		"So what's all the commotion",	"actors/male/neutral/play4.wav",	3, {8,11,14,0,0},0, 0},
	{f_neutral_talk, "Fuck me, Freddy is it you?",		"@*%$#! me, Freddy is it you?",	"actors/male/neutral/play5.wav",	4, {0,9,12,13,0},0, 0},

	{f_neutral_talk, "Seen Pauly around?",				"Seen Pauly around?",			"actors/male/neutral/play6.wav",	2, {4,1,0,0,0},0, 0},
	{f_neutral_talk, "That fuckin cop",					"That @*%$#!in cop",			"actors/male/neutral/play7.wav",	2, {8,14,0,0,0},0, true},
	{f_neutral_talk, "Shove off...",					"Shove off...",					"actors/male/neutral/play8.wav",	3, {11,6,4,0,0},0, true},
	{f_neutral_talk, "Hit the dust",					"Hit the dust",					"actors/male/neutral/play9.wav",	3, {11,6,4,0,0},0, true},
	{f_neutral_talk, "Get lost",						"Get lost",						"actors/male/neutral/play10.wav",	3, {11,6,4,0,0},0, true}
	* /
	{f_neutral_talk, "FIXME",							"FIXME",						"rc/actors/skidrow/leroy/conv6.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",							"FIXME",						"rc/actors/skidrow/leroy/conv7.wav",	0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",							"FIXME",						"rc/actors/skidrow/leroy/cool.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
*/
}; 

// Neutrals converse among themselves






// 20
voice_table_t rc_f_neutral_converse[] = 
{
	{f_neutral_talk, "You got that shit right",						"You got that @*%$#! right",					"rc/actors/female/neutral/thatsit.wav",			3, {2,1,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "So what you got in mind baby?",				"So what you got in mind baby?",				"rc/actors/female/neutral/shitbaby.wav",		5, {2,4,7,8,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "I heard that",								"I heard that",									"rc/actors/female/neutral/noshit.wav",			1, {3,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "This your first time in RC?",					"This your first time in RC?",					"rc/actors/female/neutral/new.wav",				3, {0,1,2,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "You must be the hardcore motherfucker",		"You must be the hardcore xxx",					"rc/actors/female/neutral/new2.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "That's Kool and the Gang",					"That's Kool and the Gang",						"rc/actors/female/neutral/cool.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Fuckin' aye man",								"@*%$#! aye man",								"rc/actors/female/neutral/alright.wav",			3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Fuck yeah",									"@*%$#! Yeah",									"rc/actors/female/neutral/yeah.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Yeah",										"Yeah",											"rc/actors/female/neutral/yeah2.wav",			2, {6,3,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Fuckin' Dragons are gettin' worked",			"@*%$#! Dragons are gettin' worked",			"rc/actors/female/neutral/seennothing.wav",		3, {6,3,5,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "Fuckin' Jokers are out for blood",			"@*%$#! Jokers are out for blood",				"rc/actors/female/neutral/umhmm.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Hey baby, you for real?",						"Hey baby, you for real?",						"rc/actors/female/neutral/heybaby.wav",			0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Some serious shit's going down",				"Some serious @*%$#!'s going down",				"rc/actors/female/neutral/goingon.wav",			4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "I ain't got nothin' to do with that shit",	"I ain't got nothin' to do with that @*%$#!",	"rc/actors/female/neutral/knowshit.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "Just layin' low 'til this shit blows over",	"Just layin' low 'til this @*%$#! blows over",	"rc/actors/female/neutral/hanging.wav",			5, {11,18,19,11,9},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "uhuh",										"uhuh",											"rc/actors/female/neutral/uhuh.wav",			3, {18,0,6,0,0},0, 0 , TT_NEUTRAL},


/*
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/thatsit.wav",		3, {2,1,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/shitbaby.wav",	5, {2,4,7,8,9},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/noshit.wav",		1, {3,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/new.wav",			3, {0,1,2,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/new2.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/cool.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/alright.wav",		3, {7,8,9,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/yeah.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/yeah2.wav",		2, {6,3,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/seennothing.wav",	3, {6,3,5,0,0},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/umhmm.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/heybaby.wav",		0, {0,0,0,0,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/goingon.wav",		4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/knowshit.wav",	4, {4,7,8,9,0},0, 0 , TT_NEUTRAL},
	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/hanging.wav",		5, {11,18,19,11,9},0, 0 , TT_NEUTRAL},

	{f_neutral_talk, "FIXME",		"FIXME",				"rc/actors/female/neutral/uhuh.wav",		3, {18,0,6,0,0},0, 0 , TT_NEUTRAL},
*/
};

// profanity
// 20

voice_table_t rc_f_profanity_level1[] =
{
	{f_neutral_asshole_talk, "You talkin' to me?",				"You talkin' to me?",						"rc/actors/female/profanity/level1/f_cuss1-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "back your ugly ass up",			"back your ugly @*%$#! up",					"rc/actors/female/profanity/level1/f_cuss1-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "piss the fuck off",				"piss the @*%$#! off",						"rc/actors/female/profanity/level1/f_cuss1-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "I'll bust a cap in yo ass",		"I'll bust a cap in yo @*%$#!",				"rc/actors/female/profanity/level1/f_cuss1-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "Your mama made that?",			"Your mama made that?",						"rc/actors/female/profanity/level1/f_cuss1-5.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}

/*
	{f_neutral_asshole_talk, "FIXME",		"FIXME",		"rc/actors/female/profanity/level1/f_cuss1-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "FIXME",		"FIXME",		"rc/actors/female/profanity/level1/f_cuss1-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "FIXME",		"FIXME",		"rc/actors/female/profanity/level1/f_cuss1-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "FIXME",		"FIXME",		"rc/actors/female/profanity/level1/f_cuss1-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{f_neutral_asshole_talk, "FIXME",		"FIXME",		"rc/actors/female/profanity/level1/f_cuss1-5.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
*/
};
//20

voice_table_t rc_f_profanity_level2[] =
{
	{NULL, "motherfucker what you lookin at?",					"what are You lookin at?",					"rc/actors/female/profanity/level2/f_cuss2-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "eat me you asshole",								"@*%$#! me you @*%$#!",						"rc/actors/female/profanity/level2/f_cuss2-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "keep talkin' asshole",								"keep talkin' @*%$#!",						"rc/actors/female/profanity/level2/f_cuss2-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "I'll bust your face",								"I'll bust your face",						"rc/actors/female/profanity/level2/f_cuss2-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
/*
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/profanity/level2/f_cuss2-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/profanity/level2/f_cuss2-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/profanity/level2/f_cuss2-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/profanity/level2/f_cuss2-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
*/
};

//3
voice_table_t rc_f_profanity_level3[] =
{
	{NULL, "Yo, fuck you man",									"Yo, @*%$#! you man",						"rc/actors/female/profanity/level3/f_cuss3-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "back the fuck up bitch",							"back the @*%$#! up @*%$#!",				"rc/actors/female/profanity/level3/f_cuss3-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fuck you you motherfucker",							"@*%$#! you @*%$#!",						"rc/actors/female/profanity/level3/f_cuss3-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
/*
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/profanity/level3/f_cuss3-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/profanity/level3/f_cuss3-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/profanity/level3/f_cuss3-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
*/
};

voice_table_t rc_f_fightsounds[] =
{
	{NULL, "In your face motherfucker",							"In your face @*%$#!",						"rc/actors/female/fighting/infacemf.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Die you son of a bitch",							"Die you son of a @*%$#!",					"rc/actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Take that you motherfucker",						"Take that you @*%$#!",						"rc/actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},

	{NULL, "back the fuck off asshole",							"back the @*%$#!",							"rc/actors/female/fighting/f_backoff.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Die you son of a bitch",							"Die you son of a @*%$#!",					"rc/actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Die you motherfucker",								"Die you @*%$#!",							"rc/actors/female/fighting/f_die2.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "I'll fuck you up you son of a bitch",				"I'll @*%$#! you up you son of a @*%$#!",	"rc/actors/female/fighting/f_die3.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "take that you motherfucker",						"take that you @*%$#!",						"rc/actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
/*
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/infacemf.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/f_backoff.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/f_die.wav",			0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/f_die2.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/f_die3.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/fighting/f_takethat.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE}
*/	
};

// These are used for all specific speech functions throughout the game
// NOTE: Altering the order of these items will cause problems
voice_table_t rc_f_specific[] =
{
	{NULL, "motherfucker what you lookin at?",					"what are You lookin at?",				"actors/female/profanity/level2/f_cuss2-1.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// first time they see you
	{NULL, "eat me you asshole",								"@*%$#! me you @*%$#!",					"actors/female/profanity/level2/f_cuss2-2.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// if you leave
	{NULL, "keep talkin' asshole",								"keep talkin' @*%$#!",					"actors/female/profanity/level2/f_cuss2-3.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// if you come back after leaving
	{NULL, "I'll bust your face",								"I'll bust your face",					"actors/female/profanity/level2/f_cuss2-4.wav", 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// profanity level 3
/*
	{NULL, "FIXME",			"FIXME",					NULL, 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// first time they see you
	{NULL, "FIXME",			"FIXME",					NULL, 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// if you leave
	{NULL, "FIXME",			"FIXME",					NULL, 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// if you come back after leaving
	{NULL, "FIXME",			"FIXME",					NULL, 0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},	// profanity level 3
*/
};


voice_table_t rc_f_backoff[] =
{
	{NULL, "Yo put that away man",								"Yo put that away man",						"rc/actors/female/beth_specific/putaway.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Back off motherfucker",								"Back off @*%$#!",							"rc/actors/female/beth_specific/backoff.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Yo, drop that shit motherfucker",					"Yo, drop that @*%$#! @*%$#!",				"rc/actors/female/beth_specific/droppiece.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Don't be pulling that shit on me",					"Don't be pulling that @*%$#! on me",		"rc/actors/female/beth_specific/pullshit.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
/*	{NULL, "FIXME",		"FIXME",							"rc/actors/female/beth_specific/putaway.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/beth_specific/backoff.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/beth_specific/droppiece.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",		"FIXME",							"rc/actors/female/beth_specific/pullshit.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
*/
};





voice_table_t rc_female_specific[] = 
{
	// pain
	{NULL, "",		"",		"rc/actors/female/pain1.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "",		"",		"rc/actors/female/pain2.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "",		"",		"rc/actors/female/pain3.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "",		"",		"rc/actors/female/pain4.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	// death
	{NULL, "",		"",		"rc/actors/female/death1.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "",		"",		"rc/actors/female/death2.wav",			0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	// fire death
	{NULL, "",		"",		"rc/actors/female/f_flamedeath1.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",		"rc/actors/female/f_flamedeath2.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL, "",		"",		"rc/actors/female/f_flamedeath2.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
};

voice_table_t rc_f_grunting[] =
{
	{NULL, "",		" ",	"rc/actors/female/fighting/grunt1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		" ",	"rc/actors/female/fighting/grunt2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		" ",	"rc/actors/female/fighting/grunt3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		" ",	"rc/actors/female/fighting/grunt4.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		" ",	"rc/actors/female/fighting/grunt5.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};

voice_table_t rc_lola[]=
{
	{NULL, "I think they got some weapons stashed around here somewhere",	"I think they got some weapons stashed around here somewhere",	"actors/female/lola/clue.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	
	{NULL, "man, this gang war's fuckin' everything up",					"man, this gang war's @*%$#! everything up",					"actors/female/lola/amb1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "goddam dragons are tearin' this city up",						"@*%$#! dragons are tearin' this city up",						"actors/female/lola/amb2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "they're really trashin' the place",								"they're really trashin' the place",							"actors/female/lola/amb3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "hey motherfucker!",												"hey @*%$#!!",													"actors/female/lola/curse1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "yo!",															"yo!",															"actors/female/lola/curse2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "be cool bitch!",												"be cool @*%$#!!",												"actors/female/lola/curse3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

};

voice_table_t blunt[] = 
{
	{NULL, "",															"",													"actors/female/blunt/death1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",															"",													"actors/female/blunt/death1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
																															
	{NULL, "Oh, I gotta go pee",										"Oh, I gotta go pee",								"actors/female/blunt/pain1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",															"",													"actors/female/blunt/pain2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",															"",													"actors/female/blunt/pain3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",															"",													"actors/female/blunt/pain4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
																															
	{NULL, "You hurt him, you die!",									"You hurt him, you die!",							"actors/female/blunt/fight1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Let's dance, motherfucker!",								"Let's dance, @*%$#!",								"actors/female/blunt/fight2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm gonna unload in your fucking face!",					"I'm gonna unload in your @*%$#! face!",			"actors/female/blunt/fight3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You like to watch? Well, watch this!",						"You like to watch? Well, watch this!",				"actors/female/blunt/fight4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
																															
	{NULL, "I'll execute you motherfucker!",							"I'll execute you @*%$#!!",							"actors/female/blunt/funny1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Let's do it... right here, right now!",						"Let's do it... right here, right now!",			"actors/female/blunt/funny2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Are you gonna give me a fuckin' problem?",					"Are you gonna give me a @*%$#! problem?",			"actors/female/blunt/funny3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You're getting me all worked up!",							"You're getting me all worked up!",					"actors/female/blunt/funny4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm talking to you, motherfucker!",							"I'm talking to you, @*%$#!",						"actors/female/blunt/funny5.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I never thanked you for dinner!",							"I never thanked you for dinner!",					"actors/female/blunt/funny6.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
		
};
