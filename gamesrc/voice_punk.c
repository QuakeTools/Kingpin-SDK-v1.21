#include "g_local.h"

extern voice_table_t neutral_talk[];
extern voice_table_t neutral_talk_player[];
extern voice_table_t neutral_converse[];

// Conversation:
// The neutrals would say to you

voice_table_t neutral_talk[] =
{
	{neutral_talk_player, "Hey buddy, what's on your mind?",			"Hey buddy, what's on your mind?",					"actors/male/neutral/talk1.wav",	3, {2,1,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "You lookin' for trouble?",					"You lookin' for trouble?",							"actors/male/neutral/talk2.wav",	5, {2,4,7,8,9},0, 0, TT_NONE},
	{neutral_talk_player, "What can I do you for?",						"What can I do you for?",							"actors/male/neutral/talk3.wav",	1, {3,0,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Hey sport, lookin' for some action?",		"Hey sport, lookin' for some action?",				"actors/male/neutral/talk4.wav",	3, {0,1,2,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Fo'gettaboutit",								"Fo'gettaboutit",									"actors/male/neutral/talk5.wav",	3, {7,8,9,0,0},0, true, TT_NONE},
																															
	{neutral_talk_player, "What time you got?",							"What time you got?",								"actors/male/neutral/talk6.wav",	3, {7,8,9,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "What the fuck's up with you?",				"What the @*%$#!'s up with you?",					"actors/male/neutral/talk7.wav",	3, {7,8,9,0,0},0, true, TT_NONE},
	{neutral_talk_player, "Another freekin night and no pussy",			"Another freekin night and no @*%$#!",				"actors/male/neutral/talk8.wav",	0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk_player, "Fuckin' cop can kiss my ass",				"@*%$#! cop can kiss my @*%$#!",					"actors/male/neutral/talk9.wav",	2, {6,3,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Yo man, what the fuck",						"Yo man, what the @*%$#!",							"actors/male/neutral/talk10.wav",	3, {6,3,5,0,0},0, 0, TT_NONE},

	{neutral_talk_player, "Hey man, you hang around here much?",		"Hey man, you hang around here much?",				"actors/male/neutral/talk11.wav",	0, {0,0,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Yo man, this street ain't safe no more",		"Yo man, this street ain't safe no more",			"actors/male/neutral/talk12.wav",	0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk_player, "Lemme bum a smoke man",						"Lemme bum a smoke man",							"actors/male/neutral/talk13.wav",	4, {4,7,8,9,0},0, 0, TT_NONE},
	{neutral_talk_player, "You gotta match?",							"You gotta match?",									"actors/male/neutral/talk14.wav",	4, {4,7,8,9,0},0, 0, TT_NONE},
	/*
	{neutral_talk_player, "It was a hit alright... Big time!",			"It was a hit alright... Big time!",				"actors/male/ambient/conv15.wav",	5, {11,18,19,11,9},0, 0, TT_NONE},
																															
	{neutral_talk_player, "It's a damn shame I tell ya",				"It's a damn shame I tell ya",						"actors/male/ambient/conv19.wav",	3, {18,0,6,0,0},0, 0, TT_NONE}
	*/
	{neutral_talk_player, "It was a hit alright... Big time!",			"It was a hit alright... Big time!",				"actors/male/ambient/conv15.wav",	5, {0,0,0,0,0},0, 0, TT_NONE},
																															
	{neutral_talk_player, "It's a damn shame I tell ya",				"It's a damn shame I tell ya",						"actors/male/ambient/conv19.wav",	3, {0,0,0,0,0},0, 0, TT_NONE}
};

voice_table_t neutral_asshole_talk[] =
{
	{NULL, "Fo'gettaboutit",					"Fo'gettaboutit",						"actors/male/neutral/talk5.wav", 0, {0,0,0,0,0},0, false, TT_NEGATIVE},
	{NULL, "What the fuck's up with you?",		"What the @*%$#! up with you?",			"actors/male/neutral/talk7.wav", 0, {0,0,0,0,0},0, false, TT_NEGATIVE},
};

// Player talk to a neutral

voice_table_t neutral_talk_player[] =
{
	/*
	{neutral_talk, "Hey",								"Hey",									"actors/player/male/neutral/play1.wav", 0, {0,0,0,0,0},0, false, TT_NONE},
	{neutral_talk, "So what the fuck's goin' on man?",	"So what the @*%$#!'s goin' on man?",	"actors/player/male/neutral/play2.wav", 0, {0,0,0,0,0},0, false, TT_NONE},
	{neutral_talk, "So what's up?",						"So what's up?",						"actors/player/male/neutral/play3.wav", 4, {9,5,11,7,0},0, false, TT_NONE},
	{neutral_talk, "So what's all the commotion?"	,	"So what's all the commotion?",			"actors/player/male/neutral/play4.wav", 3, {8,11,14,0,0},0, false, TT_NONE},
	{neutral_talk, "What's happening?",					"What's happening?",					"actors/player/male/neutral/play5.wav", 5, {0,9,12,13,7},0, false, TT_NONE},

	{neutral_talk, "No shit",							"No @*%$#!",							"actors/player/male/neutral/play6.wav", 2, {4,1,0,0,0},0, true, TT_NONE},
	{neutral_talk, "So what's going on?",				"So what's going on?",					"actors/player/male/neutral/play7.wav", 3, {8,14,7,0,0},0, false, TT_NONE},
	{neutral_talk, "Hey, piss off man",					"Hey, @*%$#! off man?",					"actors/player/male/neutral/play8.wav", 3, {11,6,4,0,0},0, true, TT_NONE},
	{neutral_talk, "Got any information?",				"Got any information?",					"actors/player/male/neutral/play9.wav", 3, {11,6,4,0,0},0, false, TT_NONE},
	{neutral_talk, "Know anything good?",				"Know anything good?",					"actors/player/male/neutral/play10.wav", 3, {11,6,4,0,0},0, false, TT_NONE}
	*/
	{neutral_talk, "Hey",								"Hey",									"actors/player/male/neutral/play1.wav", 0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk, "So what the fuck's goin' on man?",	"So what the @*%$#!'s goin' on man?",	"actors/player/male/neutral/play2.wav", 0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk, "So what's up?",						"So what's up?",						"actors/player/male/neutral/play3.wav", 4, {9,5,11,7,0},0, 0, TT_NONE},
	{neutral_talk, "So what's all the commotion?"	,	"So what's all the commotion?",			"actors/player/male/neutral/play4.wav", 3, {8,11,14,0,0},0, 0, TT_NONE},
	{neutral_talk, "What's happening?",					"What's happening?",					"actors/player/male/neutral/play5.wav", 5, {0,9,12,13,7},0, 0, TT_NONE},

	{neutral_talk, "No shit",							"No @*%$#!",							"actors/player/male/neutral/play6.wav", 2, {4,1,0,0,0},0, true, TT_NONE},
	{neutral_talk, "So what's going on?",				"So what's going on?",					"actors/player/male/neutral/play7.wav", 3, {8,14,7,0,0},0, true, TT_NONE},
	{neutral_talk, "So what's up?",						"So what's up?",						"actors/player/male/neutral/play3.wav", 3, {11,6,4,0,0},0, true, TT_NONE},
	{neutral_talk, "Got any information?",				"Got any information?",					"actors/player/male/neutral/play9.wav", 3, {11,6,4,0,0},0, true, TT_NONE},
	{neutral_talk, "Know anything good?",				"Know anything good?",					"actors/player/male/neutral/play10.wav", 3, {11,6,4,0,0},0, true, TT_NONE}
}; 

// Neutrals converse among themselves

voice_table_t neutral_converse[] = 
{
	{neutral_converse, "Fo'gettaboutit",												"Fo'gettaboutit",												"actors/male/ambient/conv0.wav", 5, {7,8,3,18,19},0, true, TT_NEUTRAL},
	{neutral_converse, "Two points over the vig?... You gotta be crazy!",				"Two points over the vig?... You gotta be crazy!",				"actors/male/ambient/conv1.wav", 1, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "She had a setta knockers on her like out to here!",				"She had a setta knockers on her like out to here!",			"actors/male/ambient/conv2.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Listen to me, will ya?",										"Listen to me, will ya?",										"actors/male/ambient/conv3.wav", 5, {5,7,18,4,2},0, true, TT_NEUTRAL},
	{neutral_converse, "What can I do?... He's my wife's brother",						"What can I do?... He's my wife's brother",						"actors/male/ambient/conv4.wav", 3, {0,5,13,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "He's gonna get clipped if he don't watch himself",				"He's gonna get clipped if he don't watch himself",				"actors/male/ambient/conv5.wav", 1, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Yeah, let's put twenty on Blueboy to show in the third",		"Yeah, let's put twenty on Blueboy to show in the third",		"actors/male/ambient/conv6.wav", 1, {3,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Let's get started already",										"Let's get started already",									"actors/male/ambient/conv7.wav", 3, {8,13,16,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "What time you got?",											"What time you got?",											"actors/male/ambient/conv8.wav", 4, {0,3,12,18,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "He's doin' a three to five stretch up at Big Rock",				"He's doin' a three to five stretch up at Big Rock",			"actors/male/ambient/conv9.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "The Feds shut that down weeks ago",								"The Feds shut that down weeks ago",							"actors/male/ambient/conv10.wav", 1, {11,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "No kiddin'?",													"No kiddin'?",													"actors/male/ambient/conv11.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "What's it to ya?",												"What's it to ya?",												"actors/male/ambient/conv12.wav", 3, {0,3,18,0,0},0, true, TT_NEUTRAL},
	{neutral_converse, "He better pay up... or else",									"He better pay up... or else",									"actors/male/ambient/conv13.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "If I gotta show up in person, someone ain't gonna like it",		"If I gotta show up in person, someone ain't gonna like it",	"actors/male/ambient/conv14.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "It was a hit alright... Big time!",								"It was a hit alright... Big time!",							"actors/male/ambient/conv15.wav", 5, {11,18,19,11,9},0, 0, TT_NEUTRAL},
	{neutral_converse, "A hundred cases of the real stuff comin' in from up North",		"A hundred cases of the real stuff comin' in from up North",	"actors/male/ambient/conv16.wav", 2, {11,13,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "They got him... but good!",										"They got him... but good!",									"actors/male/ambient/conv17.wav", 4, {9,19,15,11,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Don't worry 'bout it... the fix is in",							"Don't worry 'bout it... the fix is in",						"actors/male/ambient/conv18.wav", 1, {16,0,0,0,0},0, true, TT_NEUTRAL},
	{neutral_converse, "It's a damn shame I tell ya",									"It's a damn shame I tell ya",									"actors/male/ambient/conv19.wav", 3, {18,0,6,0,0},0, 0, TT_NEUTRAL}
};

voice_table_t neutral_converse_to_female[] =
{
	{neutral_converse, "hey baby. it's cool, we're gonna go over there later, you know",					"hey baby, it's cool, we're gonna go over there later, you know",						"actors/skidrow/leroy/conv1.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "man you shouldn't be hanging out with Nokia no more, that bitch trouble",			"man you shouldn't be hanging out with Nokia no more, that @*%$#! trouble",			"actors/skidrow/leroy/conv2.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "yeah I saw him last night man, it was cool",										"yeah I saw him last night man, it was cool",											"actors/skidrow/leroy/conv3.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "yeah yeah, we were there, we were there till about 2:00 am",						"yeah yeah, we were there, we were there till about 2:00 am",								"actors/skidrow/leroy/conv4.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "that motherfucker's had that shit back up in there till like 5:00 in the morning",	"that @*%$#!'s had that @*%$#! back up in there till like 5:00 in the morning",			"actors/skidrow/leroy/conv5.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},

	{neutral_converse, "umm hmm",																			"umm hmm",																				"actors/skidrow/leroy/conv6.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "yeah I heard that baby",															"yeah I heard that baby",																"actors/skidrow/leroy/conv7.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "hell yeah",																			"@*%$#! yeah",																					"actors/skidrow/leroy/conv8.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "hey man, don't be getting' yourself all fucked up over it",							"hey man, don't be getting' yourself all @*%$#!ed up over it",							"actors/skidrow/leroy/conv9.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "Yo bitch, don't be getting' all like that with me.  fuck wrong wit' you?",			"Yo @*%$#!, don't be getting' all like that with me.  @*%$#! wrong wit' you?",									"actors/skidrow/leroy/conv10.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
																																																	
	{neutral_converse, "shit...",																			"@*%$#!...",																			"actors/skidrow/leroy/conv11.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
};


// profanity

voice_table_t profanity_level1[] =
{
	{neutral_asshole_talk, "What the fuck you lookin' at?",	"What you lookin' at?",					"actors/male/profanity/level1/cuss1-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You talkin to me?",				"You talkin to me?",					"actors/male/profanity/level1/cuss1-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You wanna throw?",				"You wanna throw?",						"actors/male/profanity/level1/cuss1-3.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You gonna stand there all day?","You gonna stand there all day?",		"actors/male/profanity/level1/cuss1-4.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You want some of me?",			"You want some of me?",					"actors/male/profanity/level1/cuss1-5.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "I will bury you",				"I will bury you",						"actors/male/profanity/level1/cuss1-6.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Turn around asswipe",			"Turn around @*%$#!wipe",				"actors/male/profanity/level1/cuss1-7.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You piece of crap",				"You piece of @*%$#!",					"actors/male/profanity/level1/cuss1-8.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Hey, what'd you say?",			"Hey, what'd you say?",					"actors/male/profanity/level1/cuss1-9.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Kiss my ass",					"Kiss my @*%$#!",						"actors/male/profanity/level1/cuss1-10.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "Hey, beat it",					"Hey, beat it",							"actors/male/profanity/level1/beatit.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
};

voice_table_t profanity_level2[] =
{
	{NULL, "What are you lookin' at asshole?",			"What are you lookin' at @*%$#!?",				"actors/male/profanity/level2/cuss2-1.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You fuckin' talkin to me?",					"You talkin to me?",							"actors/male/profanity/level2/cuss2-2.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You wanna throw me motherfucker?",			"You wanna throw me @*%$#!?",					"actors/male/profanity/level2/cuss2-3.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You gonna fuckin' stand there all day?",	"You gonna @*%$#! stand there all day?",		"actors/male/profanity/level2/cuss2-4.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You want some of me asshole?",				"You want some of me @*%$#!?",					"actors/male/profanity/level2/cuss2-5.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "I will fuckin' bury you",					"I will @*%$#! bury you",						"actors/male/profanity/level2/cuss2-6.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Fuck me? Fuck you you piece of shit",		"@*%$#! me? @*%$#! you you piece of @*%$#!",	"actors/male/profanity/level2/cuss2-7.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You gonna fuck with my boys?",				"You gonna @*%$#! with my boys?",				"actors/male/profanity/level2/cuss2-8.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "What are you doin' on my fuckin' street",	"What are you doin' on my @*%$#! street",		"actors/male/profanity/level2/cuss2-9.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Turn around shit for brains",				"Turn around @*%$#! for brains",				"actors/male/profanity/level2/cuss2-10.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "I will fuckin' end you",					"I will end you",								"actors/male/profanity/level2/cuss2-11.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You piece of shit",							"You piece of @*%$#!",							"actors/male/profanity/level2/cuss2-12.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You fuckin' piece of shit",					"You @*%$#!",									"actors/male/profanity/level2/cuss2-13.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "What did you say motherfucker",				"What did you say @*%$#!",						"actors/male/profanity/level2/cuss2-14.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Fuck you, you fuckin' piece of shit",		"@*%$#! you, you @*%$#! piece of @*%$#!",		"actors/male/profanity/level2/cuss2-15.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "You fuckin' whore",							"You @*%$#!",									"actors/male/profanity/level2/cuss2-16.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Kiss my ass you piece of shit",				"Kiss my @*%$#! you piece of @*%$#!",			"actors/male/profanity/level2/cuss2-17.wav", 0, {0,0,0,0,0},0, 0},
};

voice_table_t profanity_level3[] =
{
	{NULL, "You punk mother fuckin' piece of shit",		"You punk @*%$#! piece of @*%$#!",				"actors/male/profanity/level3/cuss3-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "I'm gonna fade your ass motherfucker",		"I'm gonna fade your @*%$#! @*%$#!",			"actors/male/profanity/level3/cuss3-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
};


voice_table_t player_profanity_level1[] =
{														
	{neutral_asshole_talk, "What the fuck are you lookin' at?",		"What the @*%$#! are you lookin' at?",		"actors/player/male/profanity/level1/cuss1-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You're not talkin to me are you?",		"You're not talkin to me are you?",			"actors/player/male/profanity/level1/cuss1-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Hey you fuckin' want some of this?",	"Hey you @*%$#! want some of this?",		"actors/player/male/profanity/level1/cuss1-3.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "So you gonna fuckin' stand there?",		"So you gonna @*%$#! stand there?",			"actors/player/male/profanity/level1/cuss1-4.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Hey you fuckin' want some of me?",		"Hey you @*%$#! want some of me?",			"actors/player/male/profanity/level1/cuss1-5.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "I will fuckin' bury you",				"I will @*%$#! bury you",					"actors/player/male/profanity/level1/cuss1-6.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Turn the fuck around",					"Turn the @*%$#! around",					"actors/player/male/profanity/level1/cuss1-7.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Hey fuck you piece of shit",			"Hey @*%$#! you piece of @*%$#!",			"actors/player/male/profanity/level1/cuss1-8.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "What the fuck did you say to me?",		"What'd you say to me?",					"actors/player/male/profanity/level1/cuss1-9.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Hey fuckin' kiss my ass",				"Hey @*%$#! kiss my @*%$#!",				"actors/player/male/profanity/level1/cuss1-10.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "Hey fuckin' piss off",					"Hey @*%$#! piss off",						"actors/player/male/profanity/level1/beatit.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
};

voice_table_t player_profanity_level2[] =
{
	{NULL, "What the fuck are you lookin' at asshole?",				"What the @*%$#! are you lookin' at @*%$#!?",			"actors/player/male/profanity/level2/cuss2-1.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Hey I know you're not fuckin' talkin to me",			"Hey I know you're not @*%$#! talkin to me",			"actors/player/male/profanity/level2/cuss2-2.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Hey you wanna fuckin' throw me motherfucker?",			"Hey you wanna @*%$#! throw me @*%$#!?",				"actors/player/male/profanity/level2/cuss2-3.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "So what are you gonna fuckin' stand there all day?",	"So what are you gonna @*%$#! stand there all day?",	"actors/player/male/profanity/level2/cuss2-4.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Hey you fuckin' want some of me asshole?",				"Want some of me @*%$#!?",								"actors/player/male/profanity/level2/cuss2-5.wav", 0, {0,0,0,0,0},0, 0},
															
	{NULL, "I will fucking bury you",								"I will @*%$#! bury you",								"actors/player/male/profanity/level2/cuss2-6.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Fuck me?  Fuck you, you piece of shit",					"@*%$#! me?  @*%$#! you, you piece of @*%$#!",			"actors/player/male/profanity/level2/cuss2-7.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Are you fuckin' talkin to me?",							"Are you @*%$#! talkin to me?",							"actors/player/male/profanity/level2/cuss2-8.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Hey fuckin' turn around",								"Hey @*%$#! turn around",								"actors/player/male/profanity/level2/cuss2-9.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Turn the fuck around",									"Turn the @*%$#! around",								"actors/player/male/profanity/level2/cuss2-10.wav", 0, {0,0,0,0,0},0, 0},
																
	{NULL, "I will fucking end you",								"I will @*%$#! end you",								"actors/player/male/profanity/level2/cuss2-11.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You fuckin' piece of shit",								"You @*%$#! piece of @*%$#!",							"actors/player/male/profanity/level2/cuss2-12.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You fuckin' piece of shit",								"You @*%$#! piece of @*%$#!",							"actors/player/male/profanity/level2/cuss2-13.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "What the fuck did you say motherfucker?",				"What the @*%$#! did you say @*%$#!?",					"actors/player/male/profanity/level2/cuss2-14.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Fuck you, you piece of shit",							"@*%$#! you, you piece of @*%$#!",						"actors/player/male/profanity/level2/cuss2-15.wav", 0, {0,0,0,0,0},0, 0},
																
	{NULL, "You fuckin' whore",										"You @*%$#!",											"actors/player/male/profanity/level2/cuss2-16.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Fuckin' kiss my ass you piece of shit",					"@*%$#! kiss my @*%$#! you piece of @*%$#!",			"actors/player/male/profanity/level2/cuss2-17.wav", 0, {0,0,0,0,0},0, 0},
};

voice_table_t player_profanity_level3[] =
{
	{NULL, "You fuckin' piece of shit!",							"You @*%$#! piece of @*%$#!!",							"actors/player/male/profanity/level3/cuss3-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "You fuckin' want some of this fuck?",					"You @*%$#! want some of this @*%$#!?",					"actors/player/male/profanity/level3/cuss3-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
};

//===================================================================================

voice_table_t followme[] = 
{
	{NULL, "Let's go",						"Let's go",						"actors/player/male/followme/follow1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Come on",						"Come on",						"actors/player/male/followme/follow2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's go this way",				"Let's go this way",			"actors/player/male/followme/follow3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Follow me",						"Follow me",					"actors/player/male/followme/follow4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's blow",					"Let's blow",					"actors/player/male/followme/follow5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}
};

voice_table_t moveout[] = 
{
	{NULL, "Alright, let's move out",			"Alright, let's move out",				"actors/player/male/moveout/moveout1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Alright, move it",					"Alright, move it",						"actors/player/male/moveout/moveout2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's head out",					"Let's head out",						"actors/player/male/moveout/moveout3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Let's get the fuck out of here",	"Let's get the @*%$#! out of here",		"actors/player/male/moveout/moveout4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "C'mon let's go",					"C'mon let's go",						"actors/player/male/moveout/moveout5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};

voice_table_t holdposition[] =
{
	{NULL, "Stop here",						"Stop here",				"actors/player/male/hold/hold1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Wait here",						"Wait here",				"actors/player/male/hold/hold2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Stay right here",				"Stay right here",			"actors/player/male/hold/hold3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Don't move",					"Don't move",				"actors/player/male/hold/hold4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Park your ass",					"Park your @*%$#!",			"actors/player/male/hold/hold5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};


// Ridah, using this for general chatting now..
voice_table_t m_response[] =
{
	{NULL, "No problem",					"No problem",				"actors/male/hiredguy/orders/response1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "OK",							"OK",						"actors/male/hiredguy/orders/response2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey whatever",					"Hey whatever",				"actors/male/hiredguy/orders/response3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Sure thing",					"Sure thing",				"actors/male/hiredguy/orders/response4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "You got it",					"You got it",				"actors/male/hiredguy/orders/response5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};



voice_table_t friendlycombat[] =
{
	{NULL, "C'mon punk!",					"C'mon punk!",				"actors/male/hiredguy/fighting/fight1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Yeah, you scared huh?",			"Yeah, you scared huh?",	"actors/male/hiredguy/fighting/fight2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "die you fuck!",					"die you @*%$#!!",			"actors/male/hiredguy/fighting/fight3.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "eat lead you fuck!",			"eat lead you @*%$#!!",		"actors/male/hiredguy/fighting/fight4.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Die fuck!",						"Die @*%$#!!",				"actors/male/hiredguy/fighting/fight5.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};

voice_table_t friendlypain[] =
{
	{NULL, "done shootin' me?",					"done shootin' me?",		"actors/male/hiredguy/wounded/friendlyfire1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "Hey quit shootin' me",				"Hey quit shootin' me",		"actors/male/hiredguy/wounded/friendlyfire2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
};												
												
voice_table_t friendlyhurt[] =					
{												
	{NULL, "boss I'm all fucked up here",		"boss I'm all @*%$#!ed up here",	"actors/male/hiredguy/wounded/fuckedup.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "boss I'm hurt bad",					"boss I'm hurt bad",				"actors/male/hiredguy/wounded/hurtbad.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};

voice_table_t hiredguy_ask[] =
{
	{NULL, "Hey I'll follow you for 10 bucks",								"Hey I'll follow you for 10 bucks",								"actors/male/hiredguy/10bucks1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey 10 bucks? I'll run with ya",								"Hey 10 bucks? I'll run with ya",								"actors/male/hiredguy/10bucks2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey 25 bucks, I'll follow you anywhere",						"Hey 25 bucks, I'll follow you anywhere",						"actors/male/hiredguy/25bucks1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey, for 25 bucks I'll watch your back",						"Hey, for 25 bucks I'll watch your back",						"actors/male/hiredguy/25bucks2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "$50, I'm all yours",											"$50, I'm all yours",											"actors/male/hiredguy/50bucks1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey wanna hire me, it's 50 bucks",								"Hey wanna hire me, it's 50 bucks",								"actors/male/hiredguy/50bucks2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "I'll run with you for 75 bucks",								"I'll run with you for 75 bucks",								"actors/male/hiredguy/75bucks1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey you want me? 75 bucks I'm your man",						"Hey you want me? 75 bucks I'm your man",						"actors/male/hiredguy/75bucks2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "For $100, I'm all yours",										"For $100, I'm all yours",										"actors/male/hiredguy/100bucks1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Want somebody to watch your back? $100 I'll run with you",		"Want somebody to watch your back? $100 I'll run with you",		"actors/male/hiredguy/100bucks2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},

	{NULL, "Sorry, I can't run with you...",								"Sorry, I can't run with you...",								"actors/male/hiredguy/louiesorry.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey, I'm working for Louie right now",							"Hey, I'm working for Louie right now",							"actors/male/hiredguy/louiework.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Hey, talked to Louie yet?",										"Hey, talked to Louie yet?",									"actors/male/hiredguy/louietalked.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Talk to the boss...",											"Talk to the boss...",											"actors/male/hiredguy/louieboss.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},

	// buster lines
	{NULL, "I hear your lookin' to blow a safe. 50 bucks and I'll do it",	"I hear your lookin' to blow a safe. 50 bucks and I'll do it",	"actors/male/hiredguy/buster1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "We're hot, get the fuck out of here!",							"We're, hot get the @*%$#! out of here!",						"actors/male/hiredguy/buster2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	// finger lines
	{NULL, "Name's Fingers.  200 bucks, I'll open any safe for ya",			"Name's Fingers.  200 bucks, I'll open any safe for ya",		"actors/male/hiredguy/fingers1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Voila... Easy money",											"Voila... Easy money",											"actors/male/hiredguy/fingers2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	
	{NULL, "Hey, Sorry I work alone",										"Hey, Sorry I work alone ",										"actors/male/hiredguy/workalone.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
};

voice_table_t hiredguy_combat_moveout[] =
{
	{NULL, "Alright, take this motherfucker out",		"Alright, take this @*%$#! out",			"actors/player/male/combat/combat1.wav", 0, {0,0,0,0,0},0, 0, TT_NONE},
	{NULL, "Let's do it",								"Let's do it",								"actors/player/male/combat/combat2.wav", 0, {0,0,0,0,0},0, 0, TT_NONE},
	{NULL, "Time for you to do it",						"Time for you to do it",					"actors/player/male/combat/combat3.wav", 0, {0,0,0,0,0},0, 0, TT_NONE},
	{NULL, "Do your thing",								"Do your thing",							"actors/player/male/combat/combat4.wav", 0, {0,0,0,0,0},0, 0, TT_NONE},
	{NULL, "Go to it man",								"Go to it man",								"actors/player/male/combat/combat5.wav", 0, {0,0,0,0,0},0, 0, TT_NONE},
};

voice_table_t hiredguy_specific[] =
{
	{NULL, "so, you got the money?",							"so, you got the money?",							"actors/male/hiredguy/gotcash1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "you got the bucks or what?",						"you got the bucks or what?",						"actors/male/hiredguy/gotcash2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "hey, you change your mind, I'll be here",			"hey, you change your mind, I'll be here",			"actors/male/hiredguy/changemind.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "hey, come back to me when you got the money",		"hey, come back to me when you got the money",		"actors/male/hiredguy/comeback.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "hey, I'll be waitin' for you man",					"hey, I'll be waitin' for you man",					"actors/male/hiredguy/waiting1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "hey buddy, I'll be waitin' for you",				"hey buddy, I'll be waitin' for you",				"actors/male/hiredguy/waiting2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	
	{NULL, "I can't run with you, your crew's full",			"I can't run with you, your crew's full",			"actors/male/hiredguy/full1.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "I can't run with you unless you make room for me",	"I can't run with you unless you make room for me",	"actors/male/hiredguy/full2.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{NULL, "Alright, let's go",									"Alright, let's go",								"actors/male/hiredguy/hired1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Alright, I'm all yours",							"Alright, I'm all yours",							"actors/male/hiredguy/hired2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
    {NULL, "I'm hired",											"I'm hired",										"actors/male/hiredguy/hired3.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},

	{NULL, "when you got the cash, come see me",				"when you got the cash, come see me",				"actors/male/hiredguy/comeback2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "come back when you got the money",					"hey, come back to me when you got the money",		"actors/male/hiredguy/comeback.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "when you got the dough, I'll go",					"when you got the dough, I'll go",					"actors/male/hiredguy/comeback3.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},

};

//===================================================================================

voice_table_t fightsounds[] =
{
	{NULL, "Take some!",			"Take some!",			"actors/male/fighting/takesome.wav",	0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "Eat lead!",				"Eat lead!",			"actors/male/fighting/eatlead1.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Yo eat lead man!",		"Yo eat lead man!",		"actors/male/fighting/eatlead2.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "die you fuck",			"die you @*%$#!",		"actors/male/fighting/diefuck.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "die rat fuck",			"die rat @*%$#!",		"actors/male/fighting/ratfuck.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "piece of shit",			"piece of @*%$#!",		"actors/male/fighting/pieceshit.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "die die die",			"die die die",			"actors/male/fighting/diediedie.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fuck you",				"@*%$#! you",			"actors/male/fighting/fuckyou1.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fuck you fuck",			"@*%$#! you @*%$#!",	"actors/male/fighting/fuckyou2.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fucker!",				"@*%$#!er!",			"actors/male/fighting/fucker.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}
};


//
// These are used for all specific speech functions throughout the game
// NOTE: Altering the order of these items will cause problems
//

voice_table_t specific[] =
{
	{NULL, "What the fuck are you doin' back here?",		"What the @*%$#! are you doin' back here?",				"actors/male/specific/spec1.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, // first time they see you
	{NULL, "Fuckin' pussy ass",								"@*%$#! @*%$#! @*%$#!",									"actors/male/specific/spec2.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// if you leave
	{NULL, "What are you fuckin' doin'g back here?",		"What are you @*%$#! doin'g back here?",				"actors/male/specific/spec3.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// if you come back after leaving
	{NULL, "Kill that motherfucker",						"Kill that @*%$#!",										"actors/male/specific/spec4.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// profanity level 3
	{NULL, "Yo man you got a dollar?",						"Yo man you got a dollar?",								"actors/skidrow/magicj/holdbuck.wav",	0, {0,0,0,0,0},0,0, TT_QUESTION},
	{NULL, "Here's your fuckin' dollar",					"Here's your @*%$#! dollar",							"actors/player/male/p_heresdollar.wav",	0, {0,0,0,0,0},0,0, TT_NONE},
	{NULL, "Nah I ain't got a dollar",						"Nah I ain't got a dollar",								"actors/player/male/p_nodollar.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
		
	{NULL, "A'right cool, here's your crowbar",				"A'right cool, here's your crowbar",					"actors/skidrow/magicj/crowbar.wav",	0, {0,0,0,0,0},0,0, TT_POSITIVE},
	{NULL, "get back to me when you got a dollar",			"get back to me when you got a dollar",					"actors/skidrow/magicj/getbacktome.wav",0, {0,0,0,0,0},0,0, TT_POSITIVE},
	{NULL, "I'll give you a crowbar for a dollar...",		"I'll give you a crowbar for a dollar...",				"actors/skidrow/magicj/gotdollar.wav",	0, {0,0,0,0,0},0,0, TT_QUESTION},
	{NULL, "That's cool",									"That's cool",											"actors/skidrow/leroy/cool.wav",		0, {0,0,0,0,0},0,0, TT_NEUTRAL},	// 10

// 10
	{NULL, "What the fuck's up?",							"What the @*%$#!'s up?",								"actors/skidrow/leroy/whatsup.wav",		0, {0,0,0,0,0},0,0 , TT_NEUTRAL},	// 11
	{NULL, "Yo Fuck you man",								"Yo @*%$#! you man",									"actors/skidrow/leroy/fuckyou.wav",		0, {0,0,0,0,0},0,0 , TT_NEUTRAL},	// 12
	{NULL, "Man don't be lookin' at my bitch motherfucker",	"Man don't be lookin' at my @*%$#! @*%$#!",				"actors/skidrow/leroy/mybitch1.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},	// 13	
	{NULL, "Hey motherfucker don't be talkin' to my bitch",	"Hey @*%$#! don't be talkin' to my @*%$#!",				"actors/skidrow/leroy/mybitch2.wav",	0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 14
	{NULL, "better step the fuck off man",					"better step the @*%$#! off man",						"actors/skidrow/leroy/stepoff.wav",		0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 15
	{NULL, "Man I warned your punk ass bitch, motherfucker","Man I warned your punk @*%$#! @*%$#! @*%$#!",			"actors/skidrow/leroy/warned.wav",		0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 16
	{NULL, "Fuckin' die you piece of shit",					"@*%$#! die you piece of @*%$#!",						"actors/skidrow/leroy/die.wav",			0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 17
	{NULL, "Shit... Louie, you a'ight?... who did this?!",	"@*%$#!... Louie, you a'ight?... who did this?!",		NULL,									0, {0,0,0,0,0},0,0, TT_NONE},
	{NULL, "We'll get that fucker",							"We'll get that @*%$#!er",								NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "Hold on boss, you're gonna be ok",				"Hold on boss, you're gonna be ok",						NULL,									0, {0,0,0,0,0},0,0, TT_NONE},

// 20
	{NULL, "Damn, that punk's gonna pay",					"Damn, that punk's gonna pay",							NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "yo man put that pipe down",						"yo man put that pipe down",							"actors/skidrow/magicj/pipedown.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "hey man I'll fuck you up good now",				"hey man I'll @*%$#! you up good now",					"actors/skidrow/magicj/fuckup.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "Fuck that",										"@*%$#! that",											"actors/skidrow/magicj/fuckthat.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "i'll be back motherfucker",						"i'll be back @*%$#!",									"actors/skidrow/magicj/beback.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},

// 26: SR1 intro voices
	{NULL, "don't fuck with us punk",						"don't @*%$#! with us punk",							NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "those fuckin' punks are gonna pay",				"those @*%$#! punks are gonna pay",						NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "this pipe should come in handy",				"this pipe should come in handy",						NULL,									0, {0,0,0,0,0},0,0, TT_NEUTRAL},
	
	{NULL, "Fuck this shit",								"@*%$#! this @*%$#!",									"actors/skidrow/magicj/fuckshit.wav",	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
};

voice_table_t m_backoff[] =
{
	{NULL, "Drop your fucking weapon",									"Drop your @*%$#! weapon",											"actors/male/specific/weapon1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Put that fucking thing away before I stick it up your ass",	"Put that @*%$#! thing away before I stick it up your @*%$#!",		"actors/male/specific/weapon2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Put that shit down",										"Put that @*%$#! down",												"actors/male/specific/weapon3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE}
};

voice_table_t momo_specific [] =
{
	{NULL, "Hey welcome to jax... how ya doin'?",									"Hey welcome to jax... how ya doin'?",										"actors/male/momo/welcome.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																						
//1
	{NULL, "10 dollar cover charge gets you right in",								"10 dollar cover charge gets you right in",									"actors/male/momo/cover1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_QUESTION},
	{NULL, "You got the ten bucks?",												"You got the ten bucks?",													"actors/male/momo/cover2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_QUESTION},
	{NULL, "10 dollar cover charge gets you right in the door",						"10 dollar cover charge gets you right in the door",						"actors/male/momo/cover3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_QUESTION},

//4
	{NULL, "scram you fuckin' bum.  You aint gettin in here for nuttin'",			"scram you @*%$#! bum.  You aint gettin in here for nuttin'",				"actors/male/momo/scram.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "fuck me? no, fuck you, you piece of shit. now its 20 for you to get in you cock suck",	"@*%$#! me? No @*%$#! you, you piece of @*%$#!. now its 20 for you to get in, you @*%$#!",	"actors/male/momo/hostile1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "oh, fuck me again huh? now its 30 fuckin' dollars you fuckin' ingrate",	"oh, @*%$#! me again huh? now its 30 @*%$#! dollars you @*%$#! ingrate",	"actors/male/momo/hostile2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

//7
	{NULL, "you ain't got the money? come back and see me later",					"you ain't got the money? come back and see me later",						"actors/male/momo/comeback1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "come back when you got some money you fuckin' dead beat",				"come back when you got some money you @*%$#! dead beat",					"actors/male/momo/comeback2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

//9
	{NULL, "you're back eh...  you got the dough?",									"you're back eh...  you got the dough?",									"actors/male/momo/iamback.wav",		0, {0,0,0,0,0}, 0, 0 , TT_QUESTION},
	{NULL, "all right have a good time. go on in",									"all right have a good time. go on in",										"actors/male/momo/goin.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "and stay out of the ladies bathroom you fuckin' pervert",				"and stay out of the ladies bathroom you @*%$#! pervert",					"actors/male/momo/ladiesroom.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

//12
	{NULL, "so what's it gonna be... you coming in or what?",						"so what's it gonna be... you coming in or what?",							"actors/male/momo/idle1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_QUESTION},
	{NULL, "so what... you gonna fuckin' hang out all day?",						"so what... you gonna @*%$#! hang out all day?",							"actors/male/momo/idle2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "get the fuck out of my foyer",											"get the @*%$#! out of my foyer",											"actors/male/momo/idle3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "why don't you go cap somebody and get some dough off em?",				"why don't you go cap somebody and get some dough off em?",					"actors/male/momo/idle4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

// Ridah, had to duplicate this down here for code simplicity (can't delete from above since it'll screw up the order)
	{NULL, "scram you fuckin' bum, you ain't gettin in here for nuttin'",			"scram you @*%$#! bum, you ain't gettin in here for nuttin'",				"actors/male/momo/scram.wav",				0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "Hey... c'mon in, this is club swank.  How ya doin?",					"Hey... c'mon in, this is club swank.  How ya doin?",						"actors/male/momo/welcome_swank.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Yes, you did the right thing by comin' to the boilerroom... c'mon in",	"Yes, you did the right thing by comin' to the boilerroom... c'mon in",		"actors/male/momo/welcome_boilerroom.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Hey look, this is the Salty dog... gimme your money and come on in",	"Hey look, this is the Salty dog... gimme your money and come on in",		"actors/male/momo/welcome_saltydog.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Welcome to the Typhoon... come on in",									"Welcome to the Typhoon... come on in",										"actors/male/momo/welcome_typhoon.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},


};



voice_table_t mj_random [] =
{
	{NULL, "What's goin' on?",					"What's goin' on?",					"actors/skidrow/magicj/idle1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Man, I ain't seen shit",			"Man, I ain't seen @*%$#!",			"actors/skidrow/magicj/idle2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "I don't know nothin'",				"I don't know nothin'",				"actors/skidrow/magicj/idle3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "What's up man?",					"What's up man?",					"actors/skidrow/magicj/idle4.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};


// JOSEPH 29-MAY-99
voice_table_t male_specific[] = 
{
	// pain
	{NULL,	"",		"",		"actors/male/pain100_1.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/pain100_2.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/pain75_1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/pain75_2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/pain50_1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/pain50_2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/pain25_1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/pain25_2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	// death						
	{NULL,	"",		"",		"actors/male/death1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"actors/male/death2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	// fire death					
	{NULL,	"",		"",		"actors/male/flamedeath1.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL,	"",		"",		"actors/male/flamedeath2.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL,	"",		"",		"actors/male/flamedeath3.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
};
// END JOSEPH

voice_table_t player_answer[] =
{
	{NULL, "no",			"no",			"actors/player/male/no.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "yes",			"yes",			"actors/player/male/yes.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
};

voice_table_t lamont_random[] = 
{
	{NULL, "why you come around lookin' ...",											"why you come around lookin' ...",										"actors/male/lamont/babble1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "motherfucker is gonna be dead...",											"@*%$#! is gonna be dead...",											"actors/male/lamont/babble2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "motherfucker's gonna come out...",											"@*%$#!s gonna come out...",											"actors/male/lamont/mfcomeout.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
//3																					
	{NULL, "I swear I'm gonna kill him...",												"I swear I'm gonna kill him...",										"actors/male/lamont/killem.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "lenny gonna get my shit out there",											"lenny gonna get my @*%$#! out there",									"actors/male/lamont/lenny1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "I tell you lenny ain't gonna do that shit to me",							"I tell you lenny ain't gonna do that @*%$#! to me",					"actors/male/lamont/lenny2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
//6
	{NULL, "motherfuckin' get me in that bar I'm gonna get that Lenny...",				"goin get me in that bar... I'm gonna get that Lenny...",				"actors/male/lamont/lenny3.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "kill that motherfucker I swear to god... What the Fuck you lookin' at?",	"kill that @*%$#! I swear to god... What the @*%$#! you lookin' at?",	"actors/male/lamont/lookin'at2.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "fuck you motherfuckers",													"@*%$#! you @*%$#!",													"actors/male/lamont/fuckyou.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
//9																					
	{NULL, "you think you're gonna get somma dat out there...",							"you think you're gonna get somma dat out there...",					"actors/male/lamont/getsome.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "what the fuck you lookin' at?",												"what the @*%$#! you lookin' at?",										"actors/male/lamont/lookin'at1.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
//11																				
	{NULL, "you got a fuckin' problem?",												"you got a @*%$#! problem?",											"actors/male/lamont/fuckinprob.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "man get the fuck off my street",											"man get the @*%$#! off my street",										"actors/male/lamont/offstreet1.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "you better get the fuck off my street",										"you better get the @*%$#! off my street",								"actors/male/lamont/offstreet2.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "Man, get the fuck out my face motherfucker",								"Man, get the @*%$#! out my face @*%$#!",								"actors/male/lamont/outofface.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
};

voice_table_t lenny_table[] =
{
//0 - straight after they come back with watch
	{NULL, "ah christ, you got my watch! holy god... that's fuckin' great man",								"ah christ, you got my watch! holy god... that's @*%$#! great man",									"actors/male/lenny/gotwatch.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "oh... that's great!",																			"oh... that's great!",																				"actors/male/lenny/great.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//2 - give them the key straight after saying one of the above
	{NULL, "hey, here's the key to the store room... you can go in there, and go into those headquarters",	"hey, here's the key to the store room... you can go in there, and go into those headquarters",		"actors/male/lenny/key.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//3 - play first time
	{NULL, "hey, you're the guy that wasted all them sewer rats ain't ya?",									"hey, you're the guy that wasted all them sewer rats ain't ya?",									"actors/male/lenny/idle1.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//4 - random idle, haven't got watch
	{NULL, "damn Lamont didn't pay his rent I threw his ass out",											"damn Lamont didn't pay his rent I threw his @*%$#! out",											"actors/male/lenny/intro2.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "If you could take care of him, I... I could do somethin' for ya",									"If you could take care of him, I... I could do somethin' for ya",								"actors/male/lenny/idle6.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "If you're gonna do it, you bring my watch back, that way I know he's fuckin' dead",				"If you're gonna do it, you bring my watch back, that way I know he's dead",						"actors/male/lenny/killhim.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "If you could take care of my little Lamont problem, I might be able to help you out, ya know",	"If you could take care of my little Lamont problem, I might be able to help you out, ya know",		"actors/male/lenny/lamont1.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "Christ sakes the guy's tryin' to fuckin' kill me now",											"the guy's tryin' to @*%$#! kill me now",															"actors/male/lenny/killme.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
//SA
//	{NULL, "He didn't pay his rent for 6 months, now the guy's tryin' to fuckin' kill me",					"He didn't pay his rent for 6 months, now the guy's tryin' to @*%$#! kill me",						"actors/male/lenny/killme2.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "that fucker Lamont didn't pay his rent for 6 months, now he's gonna try and kill me",			"that @*%$#!er Lamont didn't pay his rent for 6 months, now he's gonna try and kill me",			"actors/male/lenny/killme2.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "yeh that son of a bitch stole my zolex",														"yeh that son of a @*%$#! stole my zolex",															"actors/male/lenny/stole1.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "that's a genuine immitation zolex the fucker took from me",										"that's a genuine immitation zolex the @*%$#!er took from me",										"actors/male/lenny/stole2.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "got my fuckin' watch",																			"got my @*%$#! watch",																				"actors/male/lenny/stole3.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//13 - been around for a while
	{NULL, "you ought to leave now, frankly we been in here too long... I don't want anybody gettin the wrong idea...",	"you ought to leave now, frankly we been in here too long... I don't want anybody gettin the wrong idea...",	"actors/male/lenny/leave.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//14
	{NULL, "thanks again, you're jake man",																"thanks again, you're jake man",											"actors/male/lenny/thanks1.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "thanks again, that's jake what ya did for me",												"thanks again, that's jake what ya did for me",								"actors/male/lenny/thanks2.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
																																									
	// Note to self: cloned this line for now need to remove the safe line from the code																			
	{NULL, "thanks again, you're jake man",																"thanks again, you're jake man",											"actors/male/lenny/thanks1.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	// {NULL, "they don't know I know, but they got a safe up there behind one of their pictures",		"actors/male/lenny/wallsafe.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//17 - after cuss, also play "jesus christ" after first time
	{NULL, "Jesus Christ",																				"Jesus...",																	"actors/male/lenny/idle2.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "hey, I'm just tryin' to make a livin' here ya know",										"hey, I'm just tryin' to make a livin' here ya know",						"actors/male/lenny/idle4.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "I'm just tryin' to make a livin'",															"I'm just tryin' to make a livin'",											"actors/male/lenny/idle5.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//20
	{NULL, "yeh, I was the super in the building",														"yeh, I was the super in the building",										"actors/male/lenny/intro.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "hey, you wanna get those motherfuckers, they owe me rent for a fuckin' year",				"hey, you wanna get those @*%$#!s, they owe me rent for a @*%$#! year",		"actors/male/lenny/idle3.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},

//22 - came back without watch
	{NULL, "if you could take out Lamont... I'll do somethin' for ya",									"if you could take out Lamont... I'll do somethin' for ya",					"actors/male/lenny/watch1.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "what, you didn't bring me my watch?",														"what, you didn't bring me my watch?",										"actors/male/lenny/watch2.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "hey I told you I'd do somethin' for ya if you'd get my watch back",							"hey I told you I'd do somethin' for ya if you'd get my watch back",		"actors/male/lenny/watch3.wav", 0, {0,0,0,0,0},0,0 , TT_POSITIVE},
};


voice_table_t grunting[] =
{
	{NULL, "",	"",	"actors/male/fighting/grunt1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",	"",	"actors/male/fighting/grunt2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",	"",	"actors/male/fighting/grunt3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",	"",	"actors/male/fighting/grunt4.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",	"",	"actors/male/fighting/grunt5.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};


voice_table_t nick[] = 
{																			
	{NULL, "better keep your ass out of there if you know what's good for you",	"better keep your @*%$#! out of there if you know what's good for you",	"actors/male/joseph/keepout.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "hey them scorps will rip you a new asshole",						"hey them scorps will rip you a new @*%$#!",							"actors/male/joseph/ripass.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "you go in there they will bring you out in a body bag",				"you go in there they will bring you out in a body bag",				"actors/male/joseph/bodybag.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "that's all I know",													"that's all I know",													"actors/male/joseph/alliknow.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "sorry, that's all I got to say",									"sorry, that's all I got to say",										"actors/male/joseph/alltosay.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "hey ask me again I tell you the same you fuckin' motard",			"hey ask me again I tell you the same you @*%$#! motard",				"actors/male/joseph/motard.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},

	{NULL, "that bike the sewer rats got is the only way outta skidrow",			"that bike the sewer rats got is the only way outta skidrow",											"actors/male/joseph/outofskidrow.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE}
};


voice_table_t rummy [] = 
{
	// 0
	{NULL, "swat",			"swat",			"actors/bum/swat.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "shuffle",		"shuffle",		"actors/bum/shuffle.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "sit",			"sit",			"actors/bum/sit.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "bum",			"bum",			"actors/bum/bum.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},

	// 4
	{NULL, "the combination to the safe is 36 26 36.  left right left",			"the combination to the safe is 36 26 36.  left right left",				"actors/male/rummy/combo1.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "Here's the combination to the safe",								"Here's the combination to the safe",										"actors/male/rummy/combo2.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},	

	// 6
	{NULL, "hey fuck y'all over there motherfuckers",							"hey @*%$#! y'all over there @*%$#!s",										"actors/male/rummy/fuckthem1.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "yeah fuck them motherfuckers at the warehouse",						"yeah @*%$#! them @*%$#!s at the warehouse",								"actors/male/rummy/fuckthem2.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},

	// 8
	{NULL, "get me something to drink and I'll tell you somethin'",				"get me something to drink and I'll tell you somethin'",					"actors/male/rummy/getme1.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "you find me something to drink I might tell you somethin' good",	"you find me something to drink I might tell you somethin' good",		"actors/male/rummy/getme2.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
																			
	// 10																	
	{NULL, "I thought you were gonna get me somethin to drink motherfucker",	"I thought you were gonna get me somethin to drink",						"actors/male/rummy/nogot1.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "hey fuck you man, where's my drink at?",							"hey @*%$#! you man, where's my drink at?",									"actors/male/rummy/nogot2.wav",		0, {0,0,0,0,0},0,0 , TT_POSITIVE},
																			
	// 12																	
	{NULL, "I used to work in the warehouse over there...",						"I used to work in the warehouse over there...",							"actors/male/rummy/worked1.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "I used to work in the warehouse over there...",						"I used to work in the warehouse over there...",							"actors/male/rummy/worked2.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
																			
	// 14																	
	{NULL, "aww that's good man.  much obliged to ya",							"aww that's good man.  much obliged to ya",									"actors/male/rummy/yesgot1.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "aw yeah man, that's right!",										"aw yeah man, that's right!",												"actors/male/rummy/yesgot2.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE}
		
};


voice_table_t player_money_yes[] =
{
	{NULL, "here's your dough",					"here's your dough",					"actors/player/male/money1.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "here's your fuckin' money",			"here's your @*%$#! money",				"actors/player/male/money2.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
};


voice_table_t player_money_no[] =
{
	{NULL, "nah, I ain't got enough",			"nah, I ain't got enough",				"actors/player/male/nomoney1.wav", 0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL, "I ain't got that much",				"I ain't got that much",				"actors/player/male/nomoney2.wav", 0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
};

voice_table_t sr_jesus[] = 
{
	{NULL, "",											"",												"actors/male/jesus/death1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",											"",												"actors/male/jesus/death1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
																										
	{NULL, "Ahh!  God dammit!",							"Ahh!  Dammit!",								"actors/male/jesus/pain1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",											"",												"actors/male/jesus/pain2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Ow!  mutha fucka!",							"Ow!  @*%$#!",									"actors/male/jesus/pain3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",											"",												"actors/male/jesus/pain4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
																										
	{NULL, "Let's go motherfucker!",					"Let's go @*%$#!",								"actors/male/jesus/fight1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Is that what you got pendejo?",				"Is that what you got @*%$#!?",					"actors/male/jesus/fight2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Fuckin' eat shit motherfucker!",			"@*%$#! eat @*%$#! @*%$#!!",					"actors/male/jesus/fight3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'll fuck you in the ass man!",				"I'l @*%$#! you in the @*%$#! man",				"actors/male/jesus/fight4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
															
	{NULL, "Are you ready to be fucked man?",			"Are you ready to be @*%$#! man?",				"actors/male/jesus/funny1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You don't Fuck with the Jesus, man",		"You don't @*%$#! with the Jesus, man",			"actors/male/jesus/funny2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I will Fuck you in the ass motherfucker",	"I will @*%$#! you in the @*%$#! @*%$#!",		"actors/male/jesus/funny3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Nobody fucks with the Jesus",				"Nobody @*%$#! with the Jesus",					"actors/male/jesus/funny4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Whooo!",									"Whooo!",										"actors/male/jesus/funny5.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'll stick that thing up your ass and pull the fucking trigger till it goes click",			"I'll stick that thing up your @*%$#! and pull the @*%$#! trigger till it goes click",	"actors/male/jesus/funny6.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	
	{NULL, "Leave that battery alone muthafucka",		"Leave that battery alone @*%$#!",				"actors/male/jesus/battery.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
};


voice_table_t ty_mo[] = 
{
	// 0
	{NULL, "Hey this is our turf asshole... turn around",	"Hey this is our turf @*%$#!... turn around",		"actors/male/moe/moe1.wav",			0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	
	// 1
	{NULL, "get the fuck outta here",						"get the @*%$#! outta here",						"actors/male/moe/aggressive1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I said beat it",								"I said beat it",									"actors/male/moe/aggressive2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "what, are you deaf?  get lost",					"what, are you deaf?  get lost",					"actors/male/moe/aggressive3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "blow, you fuck",								"blow, you @*%$#!",									"actors/male/moe/aggressive4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	// 5
	{NULL, "yeah... well fuck you too",						"yeah... well @*%$#! you too",						"actors/male/moe/cowar1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "man... you better get the fuck outta here",		"man... you better get the @*%$#! outta here",		"actors/male/moe/cowar2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I... it's cool man, it's cool!",				"I... it's cool man, it's cool!",					"actors/male/moe/cowar3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	// 8												
	{NULL, "kill that fucker",								"kill that @*%$#!er",								"actors/male/moe/killhim.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE}
};


voice_table_t ty_larry[] = 
{
	// 0
	{NULL, "You fuckin' looser",							"You @*%$#! looser",								"actors/male/hiredguy/larry.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};


voice_table_t sy_popeye[] =
{

	{NULL, "Heilman's boys just dragged some dame into that warehouse... she was screamin' er head off a minute ago",	"Heilman's boys just dragged some dame into that warehouse... she was screamin' er head off a minute ago",	"actors/male/popeye/dragged.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	
	{NULL, "don't try to tackle those goons yourself... you won't stand a chance",			"don't try to tackle those goons yourself... you won't stand a chance",			"actors/male/popeye/tackle.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "you ought to go down to the salty dog saloon and get a little help",			"you ought to go down to the salty dog saloon and get a little help",			"actors/male/popeye/saltydog.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	
	{NULL, "ahh, that Heilman's a piece of work, isn't he",									"ahh, that Heilman's a piece of work, isn't he",								"actors/male/popeye/prefind1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "son of a bitch has got these docks sewn up tight",								"son of a @*%$#! has got these docks sewn up tight",							"actors/male/popeye/prefind2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "you want to work steady, you gotta kick back half your dough",					"you want to work steady, you gotta kick back half your dough",					"actors/male/popeye/prefind3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "you give the big guy any lip and his goons do a number on yeh",					"you give the big guy any lip and his goons do a number on yeh",				"actors/male/popeye/prefind4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "I guess she musta talked outta turn",											"I guess she musta talked outta turn",											"actors/male/popeye/prefind5.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "uuuurrp",																		"uuuurrp",																		"actors/male/popeye/burp.wav",			0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "poor dame, they really did a number on her",									"poor dame, they really did a number on her",									"actors/male/popeye/postfind1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Heilman and the rest of his goons are holed up over by the shipyard",			"Heilman and the rest of his goons are holed up over by the shipyard",			"actors/male/popeye/postfind2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "they're all armed to the teeth... you better get some more help",				"they're all armed to the teeth... you better get some more help",				"actors/male/popeye/postfind3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "somebody's got to open up the gate for yeh",									"somebody's got to open up the gate for yeh",									"actors/male/popeye/postfind4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Heilman sure ain't gonna like hearin how you iced his boys",					"Heilman sure ain't gonna like hearin how you iced his boys",					"actors/male/popeye/postfind5.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "poor Barney...  he's sleepin with the wharf shrimp",							"poor Barney...  he's sleepin with the wharf shrimp",							"actors/male/popeye/barny.wav",			0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "you go in the water... wharf shrimp in the water...",							"you go in the water... wharf shrimp in the water...",							"actors/male/popeye/wharfshrimp.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "Don't talk to me like that ya young punk!",										"Don't talk to me like that ya young punk!",									"actors/male/popeye/hostile1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Whattaya barking at me for?  I didn't do nothin'",								"Whattaya barking at me for?  I didn't do nothin'",								"actors/male/popeye/hostile2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Ah so go fuck yourself, I was just tryin' ta help",								"Ah so go @*%$#! yourself, I was just tryin' ta help",					"actors/male/popeye/hostile3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	
	{NULL, "arrrrh",																		"arrrrh",																		"actors/male/popeye/argh1.wav",			0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "nnaarrahh",																		"nnaarrahh",																	"actors/male/popeye/argh2.wav",			0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "nahrrnn",																		"nahrrnn",																		"actors/male/popeye/argh3.wav",			0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "",																				"",																				"actors/male/popeye/whistle.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

};


voice_table_t sy_barney[] =
{
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																		
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
																																
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "FIXME",														"FIXME",			"actors/male/barney/wav1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};


voice_table_t sy_sal[] =
{
	{NULL, "somebody just kidnapped big willie's girl",					"somebody just kidnapped big willie's girl",				"actors/male/sal/kidnapped.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "yeah, that's him lyin on the floor",						"yeah, that's him lyin on the floor",						"actors/male/sal/onfloor.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "let's get her back before it's too late",					"let's get her back before it's too late",					"actors/male/sal/getherback.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "man, look what they did to her... better go tell willie",	"man, look what they did to her... better go tell willie",	"actors/male/sal/didtoher.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "man, we gonna need shotguns for this kinda deal",			"man, we gonna need shotguns for this kinda deal",			"actors/male/sal/shotguns.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

};


voice_table_t sy_bigwillie[] = 
{
	{NULL,	"ughhhh, my achin' head",									"ughhhh, my achin' head",											"actors/male/willy/onfloor1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"what fell on me?",											"what fell on me?",													"actors/male/willy/onfloor2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"somebody turn on the lights",								"somebody turn on the lights",										"actors/male/willy/onfloor3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"where's lizzy?",											"where's lizzy?",													"actors/male/willy/onfloor4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"What'd they do to her?",									"What'd they do to her?",											"actors/male/willy/onfloor5.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL,	"Lizzy... I'm gonna take it outta their fuckin' hides!",	"Lizzy... I'm gonna take it outta their @*%$#! hides!",				"actors/male/willy/lizzy1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,	"I got the key with me... let's go",						"I got the key with me... let's go",								"actors/male/willy/lizzy2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	
	{NULL,	"Payback time motherfuckers!",								"Payback time @*%$#!!",												"actors/male/willy/fight1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"This is for you Lizzy!",									"This is for you Lizzy!",											"actors/male/willy/fight2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"You murderin' bastards!",									"You murderin' @*%$#!!",											"actors/male/willy/fight3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"Die you fuckin' scum!",									"Die you @*%$#! scum!",												"actors/male/willy/fight4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"Straight to hell motherfucker!",							"Straight to hell @*%$#!!",											"actors/male/willy/fight5.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};


voice_table_t sy_dogg[] = 
{
	{NULL,	"man, Heilman's boys sure fucked this joint up",									"man, Heilman's boys sure @*%$#! this joint up",								"actors/male/dogg/dogg1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"What the hell is up with you, stupid?",											"What the @*%$#! is up with you, stupid?",										"actors/male/dogg/dogg2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"I don't like no goons breakin' heads in my place",									"I don't like no goons breakin' heads in my place",								"actors/male/dogg/dogg3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"ahh, little wreckage that's all, no problem, just watch the broken glass eh?",		"ahh, little wreckage that's all, no problem, just watch the broken glass eh?",	"actors/male/dogg/dogg4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"one grain alcohol and rain water, comin' up",										"one grain alcohol and rain water, comin' up",									"actors/male/dogg/dogg5.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	
};


voice_table_t sy_lefty[] = 
{
	{NULL,	"what we standin' around for?  time's a wastin'",			"what we standin' around for?  time's a wastin'",		"actors/male/lefty/random1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,	"get a move on will ya?",									"get a move on will ya?",								"actors/male/lefty/random2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,	"get goin' or you'll never find her",						"get goin' or you'll never find her",					"actors/male/lefty/random3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,	"hey I gotta stay put and look after big Willi",			"hey I gotta stay put and look after big Willi",		"actors/male/lefty/nohire1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL,	"I can't leave big Willie in this shape",					"I can't leave big Willie in this shape",				"actors/male/lefty/nohire2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};




voice_table_t pv_louie[] =
{
	{NULL, "So, Nicki didn't kill you after all",																							"So, Nicki didn't kill you after all",																								"actors/male/louie/didntkill.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Nicki's got some of my personal shit in a safe in his warehouse... I need somebody to get it back for me",						"Nicki's got some of my personal @*%$#! in a safe in his warehouse... I need somebody to get it back for me",				"actors/male/louie/safe.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "FIXME:",																														"FIXME:xxx",																														"",										0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "You'll need some muscle... I got all the local guys tied up right now",															"You'll need some muscle... I got all the local guys tied up right now",															"actors/male/louie/muscle.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Man, I'll bet your lookin' to pay him back",																					"Man, I'll bet your lookin' to pay him back",																						"actors/male/louie/payback.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "No?  Heh, good luck asshole... see you in the morgue",																			"No?  Heh, good luck @*%$#!... see you in the morgue",																	"actors/male/louie/morgue.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Why don't you turn around and get the fuck outta here",																			"Why don't you turn around and get the @*%$#! outta here",																"actors/male/louie/getout1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Yeah?  Well piss off you fuck",																									"Yeah?  Well piss off you @*%$#!",																						"actors/male/louie/getout2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Well fuck you too.  Get outta my face",																							"Well @*%$#! you too.  Get outta my face",																				"actors/male/louie/getout3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You know what to do... get going",																								"You know what to do... get going",																									"actors/male/louie/getgoing.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "What are you hangin' around here for?",																							"What are you hangin' around here for?",																							"actors/male/louie/hangaround.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You ain't gonna find any safe in here...",																						"You ain't gonna find any safe in here...",																							"actors/male/louie/findsafe.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Good luck",																														"Good luck",																														"actors/male/louie/goodluck.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Hey, there's a couple of freelancers you might want to talk to downstairs...  Demo guy and a safecracker",						"Hey, there's a couple of freelancers you might want to talk to downstairs...  Demo guy and a safecracker",							"actors/male/louie/buster.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "The entrance his warehouse is over by my place.  Watch yourself, he's got a couple of tough nuts parked out front",				"The entrance his warehouse is over by my place.  Watch yourself, he's got a couple of tough nuts parked out front",				"actors/male/louie/entrance.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Jezus, you made it!  Pretty impressive... now that I've got my shit back I'm blowin' this burg.  Local muscle's all yours pal",	"@*%$#!, you made it!  Pretty impressive... now that I've got my @*%$#! back I'm blowin' this burg.  Local muscle's all yours pal",	"actors/male/louie/madeit.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "here's the key to Nicki's production facility.  Well, see ya round",															"here's the key to Nicki's production facility.  Well, see ya round",																"actors/male/louie/key.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "No luck eh?",																													"No luck eh?",																														"actors/male/louie/noluck.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You do that for me, I'll let you hire some of my muscle... deal?",																"You do that for me, I'll let you hire some of my muscle... deal?",																	"actors/male/louie/favor.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "So, you understand?",																											"So, you understand?",																												"actors/male/louie/questions.wav",		0, {0,0,0,0,0}, 0, 0 , TT_QUESTION},
};


voice_table_t ty_tyrone[] = 
{
	{NULL, "",		"",		"actors/male/tyrone/death1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/tyrone/death1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/tyrone/pain1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/tyrone/pain2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/tyrone/pain3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/tyrone/pain4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},


	{NULL, "Les go!  Come on!",											"Les go!  Come on!",							"actors/male/tyrone/fight1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Bring it motherfucker!",									"Bring it @*%$#!!",								"actors/male/tyrone/fight2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Be cool bitch!",											"Be cool @*%$#!!",								"actors/male/tyrone/fight3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Bring it motherfucker!",									"Bring it @*%$#!!",								"actors/male/tyrone/fight4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "I'm sorry, did I break your concentration?",				"I'm sorry, did I break your concentration?",	"actors/male/tyrone/funny1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Do I look like a bitch, motherfucker?",						"Do I look like a @*%$#!, @*%$#!?",				"actors/male/tyrone/funny2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm the guns of the Navarone!",								"I'm the guns of the Navarone!",				"actors/male/tyrone/funny3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm superfly TNT!",											"I'm superfly TNT!",							"actors/male/tyrone/funny4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm a mushroom cloud layin' motherfucker, motherfucker!",	"I'm a mushroom cloud layin' @*%$#!, @*%$#!!",	"actors/male/tyrone/funny5.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I will lay my vengeance down upon thee!",					"I will lay my vengeance down upon thee!",		"actors/male/tyrone/funny6.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE}
	
};


voice_table_t ty_luke[] = 
{
	{NULL, "If you wanna get to Radio City, you should, like, go in the sewers",			"If you wanna get to Radio City, you should, like, go in the sewers",				"actors/male/luke/clue1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "I dunno how to get the door open, but you can",									"I dunno how to get the door open, but you can",									"actors/male/luke/clue2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	{NULL, "Were you on the train to Radio City that just crashed?  You should be dead",	"Were you on the train to Radio City that just crashed?  You should be dead",		"actors/male/luke/rand1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "The trainyard guys are everywhere",												"The trainyard guys are everywhere",												"actors/male/luke/rand2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Yeah, it's pretty dangerous around here",										"Yeah, it's pretty dangerous around here",											"actors/male/luke/rand3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Train guys have got this joint locked up man",									"Train guys have got this joint locked up man",										"actors/male/luke/rand4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "Hey, why are you fucking with us man?",											"Hey, why are you @*%$#! with us man?",												"actors/male/luke/hostile1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "You should not do that!",														"You should not do that!",															"actors/male/luke/hostile2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Hey... what's wrong with you?",													"Hey... what's wrong with you?",													"actors/male/luke/hostile3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},

};

voice_table_t ty_hann[] = 
{
	{NULL, "Now that the tunnels are blocked off you'll have to use the sewers",							"Now that the tunnels are blocked off you'll have to use the sewers",							"actors/male/hann/clue1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Somebody busted the valve handle right off the access panel.  Can't get out without that...",	"Somebody busted the valve handle right off the access panel.  Can't get out without that...",	"actors/male/hann/clue2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	{NULL, "There's nothin' but union train boys around here",										"There's nothin' but union train boys around here",										"actors/male/hann/rand1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "They're some tough motherfuckers",																"They're some tough @*%$#!",																	"actors/male/hann/rand2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "That was a hell of a wreck... you should be a grease spot",										"That was a @*%$#! of a wreck... you should be a grease spot",									"actors/male/hann/rand3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "I wish we could help you get out but... I don't know how to open that last door",				"I wish we could help you get out but... I don't know how to open that last door",				"actors/male/hann/rand4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "Hey, we didn't do nothin' to you!",																"Hey, we didn't do nothin' to you!",															"actors/male/hann/hostile1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Hey, back up with that shit!",																	"Hey, back up with that @*%$#!!",																"actors/male/hann/hostile2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Fuck you!",																						"@*%$#! you!",																					"actors/male/hann/hostile3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};


voice_table_t steeltown_moker[] = 
{
	{NULL, "",								"",					"actors/male/moker/death1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",								"",					"actors/male/moker/death1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "",								"",					"actors/male/moker/pain1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",								"",					"actors/male/moker/pain2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",								"",					"actors/male/moker/pain3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",								"",					"actors/male/moker/pain4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "Ahh, moving up the ladder!",									"Ahh, moving up the ladder!",												"actors/male/moker/fight1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Heh heh hehehe!",												"Heh heh hehehe!",															"actors/male/moker/fight2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "C'mon girlie man!",												"C'mon girlie man!",														"actors/male/moker/fight3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Moker will eat you for breakfast and shit you the next day!",	"Moker will eat you for breakfast and @*%$#! you the next day!",	"actors/male/moker/fight4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "Moker will eat you for breakfast and crap you out!",			"Moker will eat you for breakfast and @*%$#! you out!",			"actors/male/moker/funny1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'll eat you up and shit you out!",								"I'll eat you up and @*%$#! you out!",							"actors/male/moker/funny2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You think you're tough?",										"You think you're tough?",													"actors/male/moker/funny3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Let's go girlie man",											"Let's go girlie man",														"actors/male/moker/funny4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "How's that for a strike breaker?",								"How's that for a strike breaker?",											"actors/male/moker/funny5.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I have chunks of guys bigger than you in my stool!",			"I have chunks of guys bigger than you in my stool!",						"actors/male/moker/funny6.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE}
};


voice_table_t steeltown_kids[]=
{
	// 4 clues about david
	{NULL, "I just saw David a minute ago",												"I just saw David a minute ago",												"actors/male/steelkids/david_clue1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You need help taking Moker down, David's your man",							"You need help taking Moker down, David's your man",							"actors/male/steelkids/david_clue2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "David's looking to put some serious hurt on Moker",							"David's looking to put some serious hurt on Moker",							"actors/male/steelkids/david_clue3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "That David's one handy motherfucker with a lockpick",						"That David's one handy @*%$#! with a lockpick",						"actors/male/steelkids/david_clue4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	// 4 clues about hmg
	{NULL, "Moker's main job is moving weapons for the kingpin",						"Moker's main job is moving weapons for the kingpin",							"actors/male/steelkids/hmg_clue1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Moker's gang got some shiny new toys...  came from the big man himself",	"Moker's gang got some shiny new toys...  came from the big man himself",		"actors/male/steelkids/hmg_clue2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "That new gun packs some serious firepower... a real hand cannon",			"That new gun packs some serious firepower... a real hand cannon",				"actors/male/steelkids/hmg_clue3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "A whole shitload of those new guns just came in",							"A whole @*%$#!load of those new guns just came in",					"actors/male/steelkids/hmg_clue4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	// 4 random i'm out of here
	{NULL, "I'm outta here",															"I'm outta here",						"actors/male/steelkids/afraid1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Catch ya later",															"Catch ya later",						"actors/male/steelkids/afraid2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Sorry, gotta go",															"Sorry, gotta go",						"actors/male/steelkids/afraid3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "I'm gone",																	"I'm gone",								"actors/male/steelkids/afraid4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

};

voice_table_t steeltown_mathew[]=
{
	// clue talk to bambi
	{NULL, "Bambi waits tables down at the boiler room.  Poor girl's worried sick about her brother",	"Bambi waits tables down at the boiler room.  Poor girl's worried sick about her brother",	"actors/male/mathew/bambi.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	// he work in the mill
	{NULL, "He works in the mill... rough way to earn a living",										"He works in the mill... rough way to earn a living",										"actors/male/mathew/mill.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	// 4 ambs
	{NULL, "That Moker's one heartless son of a bitch, I'll tell ya",									"That Moker's one heartless son of a @*%$#!, I'll tell ya",						"actors/male/mathew/amb1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "He works those young fellas at the mill day and night",										"He works those young fellas at the mill day and night",									"actors/male/mathew/amb2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Poor devils don't last long there",															"Poor devils don't last long there",														"actors/male/mathew/amb3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Little David was lookin awful sickly today",												"Little David was lookin awful sickly today",												"actors/male/mathew/amb4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	// 3 curses
	{NULL, "Hey, people loose their teeth talkin like that",											"Hey, people loose their teeth talkin like that",											"actors/male/mathew/curse1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "The cheaper the hood, the gaudier the patter",												"The cheaper the hood, the gaudier the patter",												"actors/male/mathew/curse2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Crawl back in the gutter where you belong",													"Crawl back in the gutter where you belong",												"actors/male/mathew/curse3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
};


voice_table_t heilman[] =
{
	{NULL, "Mein Fuhrer, I can't walk!",			"Mein Fuhrer, I can't walk!",				"actors/male/heilman/death1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Ich bin fertig!",						"Ich bin fertig!",							"actors/male/heilman/death1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "Ach mein lieben!",						"Ach mein lieben!",							"actors/male/heilman/pain1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",										"",											"actors/male/heilman/pain2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",										"",											"actors/male/heilman/pain3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Gaaouch!",								"Gaaouch!",									"actors/male/heilman/pain4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "I'm hitting you!",						"I'm hitting you!",							"actors/male/heilman/fight1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "How you like zem apples?",				"How you like zem apples?",					"actors/male/heilman/fight2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You are making me sooo angry!",			"You are making me sooo angry!",			"actors/male/heilman/fight3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Take zat you little sheiter!",			"Take zat you little @*%$#!!",				"actors/male/heilman/fight4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "Ve have meat here in the building!",	"Ve have meat here in the building!",		"actors/male/heilman/funny1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I have vays of making you hurt!",		"I have vays of making you hurt!",			"actors/male/heilman/funny2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Pain is instructive!",					"Pain is instructive!",						"actors/male/heilman/funny3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I have five times your strength!",		"I have five times your strength!",			"actors/male/heilman/funny4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Time to nip this in the bud!",			"Time to nip this in the bud!",				"actors/male/heilman/funny5.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Stop fighting back, it's not fair!",	"Stop fighting back, it's not fair!",		"actors/male/heilman/funny6.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'll cut off your johnson!",			"I'll cut off your @*%$#!!",				"actors/male/heilman/funny7.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE}

};

// JOSEPH 26-MAY-99
voice_table_t nickiblanco[] =
{
	{NULL, "I'll... remember you...",							"I'll... remember you...",									"actors/male/nicki/death1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "Okay, I'm licked...",								"Okay, I'm licked...",										"actors/male/nicki/death1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "",		"",		"actors/male/nicki/pain1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/nicki/pain2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/nicki/pain3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",		"",		"actors/male/nicki/pain4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NONE},

	{NULL, "What... you think I'm just one of the guys?",		"What... you think I'm just one of the guys?",				"actors/male/nicki/fight1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Your ass is mine you hear me?  It's Mine!",			"Your @*%$#! is mine you hear me?  It's Mine!",				"actors/male/nicki/fight2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "C'mon... C'mon!",									"C'mon... C'mon!",											"actors/male/nicki/fight3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You like that?!",									"You like that?!",											"actors/male/nicki/fight4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},

	{NULL, "You dug your grave, go fall in it",					"You dug your grave, go fall in it",						"actors/male/nicki/funny1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You're gonna talk yourself right into the river",	"You're gonna talk yourself right into the river",			"actors/male/nicki/funny2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "So, fucking with us makes you a bigshot eh?",		"So, @*%$#! with us makes you a bigshot eh?",				"actors/male/nicki/funny3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Nobody Fucks with our operation!",					"Nobody @*%$#! with our operation!",						"actors/male/nicki/funny4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "C'mere punk, I wanna chastise you!",				"C'mere punk, I wanna chastise you!",						"actors/male/nicki/funny5.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Where you gonna run to now tough guy?!",			"Where you gonna run to now tough guy?!",					"actors/male/nicki/funny6.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
};
// END JOSEPH

voice_table_t steeltown_david[]=
{
	{NULL, "Thanks a lot for coming to get me man",									"Thanks a lot for coming to get me man",									"actors/male/david/david1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Okay man, I'm stickin' with you now",									"Okay man, I'm stickin' with you now",										"actors/male/david/david2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Moker's got one of the new guns locked up... but I can get it for ya",	"Moker's got one of the new guns locked up... but I can get it for ya",		"actors/male/david/david3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};


voice_table_t steeltown_pete[]=
{
	{NULL, "...don't serve me drinks no more",										"...don't serve me drinks no more",								"actors/male/pete/rand1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "wy doesn... everbody just...",											"wy doesn... everbody just...",									"actors/male/pete/rand2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You drove me to... drink an I never thanked ya",						"You drove me to... drink an I never thanked ya",				"actors/male/pete/rand3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Got me a can of eight year old Sterno... back in muh box",				"Got me a can of eight year old Sterno... back in muh box",		"actors/male/pete/rand4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	{NULL, "Gahhh...  get away from me!",											"Gahhh...  get away from me!",									"actors/male/pete/curse1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You... fuckin' devil.  Get outta here",									"You... @*%$#! devil.  Get outta here",							"actors/male/pete/curse2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Nu... nooo, ya can't have muh soul!",									"Nu... nooo, ya can't have muh soul!",							"actors/male/pete/curse3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You don't fool me... you spawn of hell!",								"You don't fool me... you spawn of @*%$#!!",					"actors/male/pete/curse4.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
};


voice_table_t steeltown_kroker[]=
{
	{NULL, "Don't kill me!  I'll open the safe",				"Don't kill me!  I'll open the safe",					"actors/male/kroker/opensafe.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Get the fuck outta my office!",						"Get the @*%$#! outta my office!",						"actors/male/kroker/getout.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
};


voice_table_t rc_scalper[]=
{
	// 0
	{NULL, "I'll sell you a Sky Tram ticket for $50",														"I'll sell you a Sky Tram ticket for $50",													"actors/male/scalper/buyticket1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Want to take the Sky Tram to Central Tower? It'll cost you $50",								"Want to take the Sky Tram to Central Tower? It'll cost you $50",							"actors/male/scalper/buyticket2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	// 2	
	{NULL, "There you go my man",																			"There you go my man",																		"actors/male/scalper/yes1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Have a good trip",																				"Have a good trip",																			"actors/male/scalper/yes2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	// 4																																																			
	{NULL, "Sorry, you need $50",																			"Sorry, you need $50",																		"actors/male/scalper/no1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Like I said, the price is $50",																	"Like I said, the price is $50",															"actors/male/scalper/no2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	{NULL, "The Sky Tram's the only way to get to the tower",												"The Sky Tram's the only way to get to the tower",											"actors/male/scalper/amb1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "The gang violence in RC is gettin' way out of hand",											"The gang violence in RC is gettin' way out of hand",										"actors/male/scalper/amb2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "With them Jokers and Dragons goin' at it, it ain't safe to walk the streetsno more",			"With them Jokers and Dragons goin' at it, it ain't safe to walk the streets no more",		"actors/male/scalper/amb3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																					
	{NULL, "I don't care what you say... It's still gonna cost you $50",									"I don't care what you say... It's still gonna cost you $50",								"actors/male/scalper/curse1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Go flap your wings and fly to Central Tower, cause you ain't gettin' there any other way",		"Go flap your wings and fly to Central Tower, cause you ain't gettin' there any other way",	"actors/male/scalper/curse2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Fine. Be that way. I'll just sell it to somebody else...",										"Fine. Be that way. I'll just sell it to somebody else...",									"actors/male/scalper/curse3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
};



//////////////////////////////////////////////////////////////////////////////////////
// radio city
//////////////////////// 

voice_table_t rc_neutral_talk[] =
{
	{neutral_talk_player, "Hey buddy, what's on your mind?",			"Hey buddy, what's on your mind?",					"rc/actors/male/neutral/talk1.wav",	3, {2,1,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "You lookin' for trouble?",					"You lookin' for trouble?",							"rc/actors/male/neutral/talk2.wav",	5, {2,4,7,8,9},0, 0, TT_NONE},
	{neutral_talk_player, "What can I do you for?",						"What can I do you for?",							"rc/actors/male/neutral/talk3.wav",	1, {3,0,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Hey sport, lookin' for some action?",		"Hey sport, lookin' for some action?",				"rc/actors/male/neutral/talk4.wav",	3, {0,1,2,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Fo'gettaboutit",								"Fo'gettaboutit",									"rc/actors/male/neutral/talk5.wav",	3, {7,8,9,0,0},0, true, TT_NONE},
																															
	{neutral_talk_player, "What time you got?",							"What time you got?",								"rc/actors/male/neutral/talk6.wav",	3, {7,8,9,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "What the fuck's up with you?",				"What the @*%$#!'s up with you?",					"rc/actors/male/neutral/talk7.wav",	3, {7,8,9,0,0},0, true, TT_NONE},
	{neutral_talk_player, "Another freekin night and no pussy",			"Another freekin night and no @*%$#!",				"rc/actors/male/neutral/talk8.wav",	0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk_player, "Fuckin' cop can kiss my ass",				"@*%$#! cop can kiss my @*%$#!",					"rc/actors/male/neutral/talk9.wav",	2, {6,3,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Yo man, what the fuck",						"Yo man, what the @*%$#!",							"rc/actors/male/neutral/talk10.wav",	3, {6,3,5,0,0},0, 0, TT_NONE},

	{neutral_talk_player, "Hey man, you hang around here much?",		"Hey man, you hang around here much?",				"rc/actors/male/neutral/talk11.wav",	0, {0,0,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "Yo man, this street ain't safe no more",		"Yo man, this street ain't safe no more",			"rc/actors/male/neutral/talk12.wav",	0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk_player, "Lemme bum a smoke man",						"Lemme bum a smoke man",							"rc/actors/male/neutral/talk13.wav",	4, {4,7,8,9,0},0, 0, TT_NONE},
	{neutral_talk_player, "You gotta match?",							"You gotta match?",									"rc/actors/male/neutral/talk14.wav",	4, {4,7,8,9,0},0, 0, TT_NONE},

	{neutral_talk_player, "It was a hit alright... Big time!",			"It was a hit alright... Big time!",				"rc/actors/male/ambient/conv15.wav",	5, {0,0,0,0,0},0, 0, TT_NONE},
																														
	{neutral_talk_player, "It's a damn shame I tell ya",				"It's a damn shame I tell ya",						"rc/actors/male/ambient/conv19.wav",	3, {0,0,0,0,0},0, 0, TT_NONE}
/*
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk1.wav",	3, {2,1,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk2.wav",	5, {2,4,7,8,9},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk3.wav",	1, {3,0,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk4.wav",	3, {0,1,2,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk5.wav",	3, {7,8,9,0,0},0, true, TT_NONE},
																															
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk6.wav",	3, {7,8,9,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk7.wav",	3, {7,8,9,0,0},0, true, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk8.wav",	0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk9.wav",	2, {6,3,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk10.wav",	3, {6,3,5,0,0},0, 0, TT_NONE},

	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk11.wav",	0, {0,0,0,0,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk12.wav",	0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk13.wav",	4, {4,7,8,9,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/neutral/talk14.wav",	4, {4,7,8,9,0},0, 0, TT_NONE},
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/ambient/conv15.wav",	5, {11,18,19,11,9},0, 0, TT_NONE},
																															
	{neutral_talk_player, "FIXME",			"FIXME",		"rc/actors/male/ambient/conv19.wav",	3, {18,0,6,0,0},0, 0, TT_NONE}
*/
};

voice_table_t rc_neutral_asshole_talk[] =
{
	{NULL, "Fo'gettaboutit",					"Fo'gettaboutit",						"rc/actors/male/neutral/talk5.wav", 0, {0,0,0,0,0},0, false, TT_NEGATIVE},
	{NULL, "What the fuck's up with you?",		"What the @*%$#! up with you?",			"rc/actors/male/neutral/talk7.wav", 0, {0,0,0,0,0},0, false, TT_NEGATIVE},
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/neutral/talk5.wav", 0, {0,0,0,0,0},0, false, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/neutral/talk7.wav", 0, {0,0,0,0,0},0, false, TT_NEGATIVE},
*/
};

voice_table_t rc_neutral_talk_player[] =
{
	{neutral_talk, "Hey",								"Hey",									"rc/actors/player/male/neutral/play1.wav", 0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk, "So what the fuck's goin' on man?",	"So what the @*%$#!'s goin' on man?",	"rc/actors/player/male/neutral/play2.wav", 0, {0,0,0,0,0},0, true, TT_NONE},
	{neutral_talk, "So what's up?",						"So what's up?",						"rc/actors/player/male/neutral/play3.wav", 4, {9,5,11,7,0},0, 0, TT_NONE},
	{neutral_talk, "So what's all the commotion?"	,	"So what's all the commotion?",			"rc/actors/player/male/neutral/play4.wav", 3, {8,11,14,0,0},0, 0, TT_NONE},
	{neutral_talk, "What's happening?",					"What's happening?",					"rc/actors/player/male/neutral/play5.wav", 5, {0,9,12,13,7},0, 0, TT_NONE},

	{neutral_talk, "No shit",							"No @*%$#!",							"rc/actors/player/male/neutral/play6.wav", 2, {4,1,0,0,0},0, true, TT_NONE},
	{neutral_talk, "So what's going on?",				"So what's going on?",					"rc/actors/player/male/neutral/play7.wav", 3, {8,14,7,0,0},0, true, TT_NONE},
	{neutral_talk, "Hey, piss off man",					"Hey, @*%$#! off man?",					"rc/actors/player/male/neutral/play8.wav", 3, {11,6,4,0,0},0, true, TT_NONE},
	{neutral_talk, "Got any information?",				"Got any information?",					"rc/actors/player/male/neutral/play9.wav", 3, {11,6,4,0,0},0, true, TT_NONE},
	{neutral_talk, "Know anything good?",				"Know anything good?",					"rc/actors/player/male/neutral/play10.wav", 3, {11,6,4,0,0},0, true, TT_NONE}
/*
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play1.wav", 0, {0,0,0,0,0},0, false, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play2.wav", 0, {0,0,0,0,0},0, false, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play3.wav", 4, {9,5,11,7,0},0, false, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play4.wav", 3, {8,11,14,0,0},0, false, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play5.wav", 5, {0,9,12,13,7},0, false, TT_NONE},

	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play6.wav", 2, {4,1,0,0,0},0, true, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play7.wav", 3, {8,14,7,0,0},0, false, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play8.wav", 3, {11,6,4,0,0},0, true, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play9.wav", 3, {11,6,4,0,0},0, false, TT_NONE},
	{neutral_talk, "FIXME",			"FIXME",				"rc/actors/player/male/neutral/play10.wav", 3, {11,6,4,0,0},0, false, TT_NONE}
*/
}; 

voice_table_t rc_neutral_converse[] = 
{
	{neutral_converse, "Fo'gettaboutit",												"Fo'gettaboutit",												"rc/actors/male/ambient/conv0.wav", 5, {7,8,3,18,19},0, true, TT_NEUTRAL},
	{neutral_converse, "Two points over the vig?... You gotta be crazy!",				"Two points over the vig?... You gotta be crazy!",				"rc/actors/male/ambient/conv1.wav", 1, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "She had a setta knockers on her like out to here!",				"She had a setta knockers on her like out to here!",			"rc/actors/male/ambient/conv2.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Listen to me, will ya?",										"Listen to me, will ya?",										"rc/actors/male/ambient/conv3.wav", 5, {5,7,18,4,2},0, true, TT_NEUTRAL},
	{neutral_converse, "What can I do?... He's my wife's brother",						"What can I do?... He's my wife's brother",						"rc/actors/male/ambient/conv4.wav", 3, {0,5,13,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "He's gonna get clipped if he don't watch himself",				"He's gonna get clipped if he don't watch himself",				"rc/actors/male/ambient/conv5.wav", 1, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Yeah, let's put twenty on Blueboy to show in the third",		"Yeah, let's put twenty on Blueboy to show in the third",		"rc/actors/male/ambient/conv6.wav", 1, {3,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Let's get started already",										"Let's get started already",									"rc/actors/male/ambient/conv7.wav", 3, {8,13,16,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "What time you got?",											"What time you got?",											"rc/actors/male/ambient/conv8.wav", 4, {0,3,12,18,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "He's doin' a three to five stretch up at Big Rock",				"He's doin' a three to five stretch up at Big Rock",			"rc/actors/male/ambient/conv9.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "The Feds shut that down weeks ago",								"The Feds shut that down weeks ago",							"rc/actors/male/ambient/conv10.wav", 1, {11,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "No kiddin'?",													"No kiddin'?",													"rc/actors/male/ambient/conv11.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "What's it to ya?",												"What's it to ya?",												"rc/actors/male/ambient/conv12.wav", 3, {0,3,18,0,0},0, true, TT_NEUTRAL},
	{neutral_converse, "He better pay up... or else",									"He better pay up... or else",									"rc/actors/male/ambient/conv13.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "If I gotta show up in person, someone ain't gonna like it",		"If I gotta show up in person, someone ain't gonna like it",	"rc/actors/male/ambient/conv14.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "It was a hit alright... Big time!",								"It was a hit alright... Big time!",							"rc/actors/male/ambient/conv15.wav", 5, {11,18,19,11,9},0, 0, TT_NEUTRAL},
	{neutral_converse, "A hundred cases of the real stuff comin' in from up North",		"A hundred cases of the real stuff comin' in from up North",	"rc/actors/male/ambient/conv16.wav", 2, {11,13,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "They got him... but good!",										"They got him... but good!",									"rc/actors/male/ambient/conv17.wav", 4, {9,19,15,11,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "Don't worry 'bout it... the fix is in",							"Don't worry 'bout it... the fix is in",						"rc/actors/male/ambient/conv18.wav", 1, {16,0,0,0,0},0, true, TT_NEUTRAL},
	{neutral_converse, "It's a damn shame I tell ya",									"It's a damn shame I tell ya",									"rc/actors/male/ambient/conv19.wav", 3, {18,0,6,0,0},0, 0, TT_NEUTRAL}
/*
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv0.wav", 5, {7,8,3,18,19},0, true, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv1.wav", 1, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv2.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv3.wav", 5, {5,7,18,4,2},0, true, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv4.wav", 3, {0,5,13,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv5.wav", 1, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv6.wav", 1, {3,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv7.wav", 3, {8,13,16,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv8.wav", 4, {0,3,12,18,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv9.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv10.wav", 1, {11,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv11.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv12.wav", 3, {0,3,18,0,0},0, true, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv13.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv14.wav", 0, {0,0,0,0,0},0, 0, TT_NEUTRAL},
																						
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv15.wav", 5, {11,18,19,11,9},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv16.wav", 2, {11,13,0,0,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv17.wav", 4, {9,19,15,11,0},0, 0, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv18.wav", 1, {16,0,0,0,0},0, true, TT_NEUTRAL},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/male/ambient/conv19.wav", 3, {18,0,6,0,0},0, 0, TT_NEUTRAL}
*/
};

voice_table_t rc_neutral_converse_to_female[] =
{
	{neutral_converse, "hey baby. it's cool, we're gonna go over there later, you know",					"hey baby, it's cool, we're gonna go over there later, you know",						"rc/actors/skidrow/leroy/conv1.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "man you shouldn't be hanging out with Nokia no more, that bitch trouble",			"man you shouldn't be hanging out with Nokia no more, that @*%$#! trouble",				"rc/actors/skidrow/leroy/conv2.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "yeah I saw him last night man, it was cool",										"yeah I saw him last night man, it was cool",											"rc/actors/skidrow/leroy/conv3.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "yeah yeah, we were there, we were there till about 2:00 am",						"yeah yeah, we were there, we were there till about 2:00 am",							"rc/actors/skidrow/leroy/conv4.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "that motherfucker's had that shit back up in there till like 5:00 in the morning",	"that @*%$#!'s had that @*%$#! back up in there till like 5:00 in the morning",			"rc/actors/skidrow/leroy/conv5.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},

	{neutral_converse, "umm hmm",																			"umm hmm",																				"rc/actors/skidrow/leroy/conv6.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "yeah I heard that baby",															"yeah I heard that baby",																"rc/actors/skidrow/leroy/conv7.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "hell yeah",																			"@*%$#! yeah",																			"rc/actors/skidrow/leroy/conv8.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "hey man, don't be getting' yourself all fucked up over it",							"hey man, don't be getting' yourself all @*%$#!ed up over it",							"rc/actors/skidrow/leroy/conv9.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "Yo bitch, don't be getting' all like that with me.  fuck wrong wit' you?",			"Yo @*%$#!, don't be getting' all like that with me.  @*%$#! wrong wit' you?",			"rc/actors/skidrow/leroy/conv10.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
																																																	
	{neutral_converse, "shit...",																			"@*%$#!...",																			"rc/actors/skidrow/leroy/conv11.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
/*
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv1.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv2.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv3.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv4.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv5.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},

	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv6.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv7.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv8.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv9.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv10.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
																																																	
	{neutral_converse, "FIXME",			"FIXME",			"rc/actors/skidrow/leroy/conv11.wav", 3, {18,0,6,0,0},0, 0, TT_NONE},
*/
};

voice_table_t rc_profanity_level1[] =
{
	{neutral_asshole_talk, "What the fuck you lookin' at?",	"What you lookin' at?",					"rc/actors/male/profanity/level1/cuss1-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You talkin to me?",				"You talkin to me?",					"rc/actors/male/profanity/level1/cuss1-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You wanna throw?",				"You wanna throw?",						"rc/actors/male/profanity/level1/cuss1-3.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You gonna stand there all day?","You gonna stand there all day?",		"rc/actors/male/profanity/level1/cuss1-4.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You want some of me?",			"You want some of me?",					"rc/actors/male/profanity/level1/cuss1-5.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "I will bury you",				"I will bury you",						"rc/actors/male/profanity/level1/cuss1-6.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Turn around asswipe",			"Turn around @*%$#!wipe",				"rc/actors/male/profanity/level1/cuss1-7.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "You piece of crap",				"You piece of @*%$#!",					"rc/actors/male/profanity/level1/cuss1-8.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Hey, what'd you say?",			"Hey, what'd you say?",					"rc/actors/male/profanity/level1/cuss1-9.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "Kiss my ass",					"Kiss my @*%$#!",						"rc/actors/male/profanity/level1/cuss1-10.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "Hey, beat it",					"Hey, beat it",							"rc/actors/male/profanity/level1/beatit.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
/*
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-3.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-4.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-5.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-6.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-7.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-8.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-9.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/cuss1-10.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},

	{neutral_asshole_talk, "FIXME",			"FIXME",		"rc/actors/male/profanity/level1/beatit.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
*/
};

voice_table_t rc_profanity_level2[] =
{
	{NULL, "What are you lookin' at asshole?",			"What are you lookin' at @*%$#!?",				"rc/actors/male/profanity/level2/cuss2-1.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You fuckin' talkin to me?",					"You talkin to me?",							"rc/actors/male/profanity/level2/cuss2-2.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You wanna throw me motherfucker?",			"You wanna throw me @*%$#!?",					"rc/actors/male/profanity/level2/cuss2-3.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You gonna fuckin' stand there all day?",	"You gonna @*%$#! stand there all day?",		"rc/actors/male/profanity/level2/cuss2-4.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You want some of me asshole?",				"You want some of me @*%$#!?",					"rc/actors/male/profanity/level2/cuss2-5.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "I will fuckin' bury you",					"I will @*%$#! bury you",						"rc/actors/male/profanity/level2/cuss2-6.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Fuck me? Fuck you you piece of shit",		"@*%$#! me? @*%$#! you you piece of @*%$#!",	"rc/actors/male/profanity/level2/cuss2-7.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You gonna fuck with my boys?",				"You gonna @*%$#! with my boys?",				"rc/actors/male/profanity/level2/cuss2-8.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "What are you doin' on my fuckin' street",	"What are you doin' on my @*%$#! street",		"rc/actors/male/profanity/level2/cuss2-9.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Turn around shit for brains",				"Turn around @*%$#! for brains",				"rc/actors/male/profanity/level2/cuss2-10.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "I will fuckin' end you",					"I will end you",								"rc/actors/male/profanity/level2/cuss2-11.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You piece of shit",							"You piece of @*%$#!",							"rc/actors/male/profanity/level2/cuss2-12.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "You fuckin' piece of shit",					"You @*%$#!",									"rc/actors/male/profanity/level2/cuss2-13.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "What did you say motherfucker",				"What did you say @*%$#!",						"rc/actors/male/profanity/level2/cuss2-14.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Fuck you, you fuckin' piece of shit",		"@*%$#! you, you @*%$#! piece of @*%$#!",		"rc/actors/male/profanity/level2/cuss2-15.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "You fuckin' whore",							"You @*%$#!",									"rc/actors/male/profanity/level2/cuss2-16.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "Kiss my ass you piece of shit",				"Kiss my @*%$#! you piece of @*%$#!",			"rc/actors/male/profanity/level2/cuss2-17.wav", 0, {0,0,0,0,0},0, 0},
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-1.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-2.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-3.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-4.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-5.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-6.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-7.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-8.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-9.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-10.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-11.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-12.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-13.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-14.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-15.wav", 0, {0,0,0,0,0},0, 0},
														
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-16.wav", 0, {0,0,0,0,0},0, 0},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level2/cuss2-17.wav", 0, {0,0,0,0,0},0, 0},
*/
};

voice_table_t rc_profanity_level3[] =
{
	{NULL, "You punk mother fuckin' piece of shit",		"You punk @*%$#! piece of @*%$#!",				"rc/actors/male/profanity/level3/cuss3-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "I'm gonna fade your ass motherfucker",		"I'm gonna fade your @*%$#! @*%$#!",			"rc/actors/male/profanity/level3/cuss3-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level3/cuss3-1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/profanity/level3/cuss3-2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
*/
};

voice_table_t rc_friendlycombat[] =
{
	{NULL, "C'mon punk!",					"C'mon punk!",				"rc/actors/male/hiredguy/fighting/fight1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Yeah, you scared huh?",			"Yeah, you scared huh?",	"rc/actors/male/hiredguy/fighting/fight2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "die you fuck!",					"die you @*%$#!!",			"rc/actors/male/hiredguy/fighting/fight3.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "eat lead you fuck!",			"eat lead you @*%$#!!",		"rc/actors/male/hiredguy/fighting/fight4.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "Die fuck!",						"Die @*%$#!!",				"rc/actors/male/hiredguy/fighting/fight5.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/fighting/fight1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/fighting/fight2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/fighting/fight3.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/fighting/fight4.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/fighting/fight5.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
*/
};

voice_table_t rc_friendlypain[] =
{
	{NULL, "done shootin' me?",					"done shootin' me?",		"rc/actors/male/hiredguy/wounded/friendlyfire1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "Hey quit shootin' me",				"Hey quit shootin' me",		"rc/actors/male/hiredguy/wounded/friendlyfire2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/wounded/friendlyfire1.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/wounded/friendlyfire2.wav", 0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
*/
};												
												
voice_table_t rc_friendlyhurt[] =					
{												
	{NULL, "boss I'm all fucked up here",		"boss I'm all @*%$#!ed up here",	"rc/actors/male/hiredguy/wounded/fuckedup.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "boss I'm hurt bad",					"boss I'm hurt bad",				"rc/actors/male/hiredguy/wounded/hurtbad.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/wounded/fuckedup.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/hiredguy/wounded/hurtbad.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE},
*/
};

voice_table_t rc_fightsounds[] =
{
	{NULL, "Take some!",			"Take some!",			"rc/actors/male/fighting/takesome.wav",	0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "Eat lead!",				"Eat lead!",			"rc/actors/male/fighting/eatlead1.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "Yo eat lead man!",		"Yo eat lead man!",		"rc/actors/male/fighting/eatlead2.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "die you fuck",			"die you @*%$#!",		"rc/actors/male/fighting/diefuck.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "die rat fuck",			"die rat @*%$#!",		"rc/actors/male/fighting/ratfuck.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "piece of shit",			"piece of @*%$#!",		"rc/actors/male/fighting/pieceshit.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "die die die",			"die die die",			"rc/actors/male/fighting/diediedie.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fuck you",				"@*%$#! you",			"rc/actors/male/fighting/fuckyou1.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fuck you fuck",			"@*%$#! you @*%$#!",	"rc/actors/male/fighting/fuckyou2.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "fucker!",				"@*%$#!er!",			"rc/actors/male/fighting/fucker.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/takesome.wav",	0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/eatlead1.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/eatlead2.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/diefuck.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/ratfuck.wav",		0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/pieceshit.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/diediedie.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/fuckyou1.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/fuckyou2.wav",	0, {0,0,0,0,0},0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/fighting/fucker.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}
*/
};

voice_table_t rc_specific[] =
{
	{NULL, "What the fuck are you doin' back here?",		"What the @*%$#! are you doin' back here?",				"rc/actors/male/specific/spec1.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, // first time they see you
	{NULL, "Fuckin' pussy ass",								"@*%$#! @*%$#! @*%$#!",									"rc/actors/male/specific/spec2.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// if you leave
	{NULL, "What are you fuckin' doin'g back here?",		"What are you @*%$#! doin'g back here?",				"rc/actors/male/specific/spec3.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// if you come back after leaving
	{NULL, "Kill that motherfucker",						"Kill that @*%$#!",										"rc/actors/male/specific/spec4.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// profanity level 3
	{NULL, "Yo man you got a dollar?",						"Yo man you got a dollar?",								"rc/actors/skidrow/magicj/holdbuck.wav",	0, {0,0,0,0,0},0,0, TT_QUESTION},
	{NULL, "Here's your fuckin' dollar",					"Here's your @*%$#! dollar",							"rc/actors/player/male/p_heresdollar.wav",	0, {0,0,0,0,0},0,0, TT_NONE},
	{NULL, "Nah I ain't got a dollar",						"Nah I ain't got a dollar",								"rc/actors/player/male/p_nodollar.wav",		0, {0,0,0,0,0},0,0 , TT_NONE},
		
	{NULL, "A'right cool, here's your crowbar",				"A'right cool, here's your crowbar",					"rc/actors/skidrow/magicj/crowbar.wav",		0, {0,0,0,0,0},0,0, TT_POSITIVE},
	{NULL, "get back to me when you got a dollar",			"get back to me when you got a dollar",					"rc/actors/skidrow/magicj/getbacktome.wav",	0, {0,0,0,0,0},0,0, TT_POSITIVE},
	{NULL, "I'll give you a crowbar for a dollar...",		"I'll give you a crowbar for a dollar...",				"rc/actors/skidrow/magicj/gotdollar.wav",	0, {0,0,0,0,0},0,0, TT_QUESTION},
	{NULL, "That's cool",									"That's cool",											"rc/actors/skidrow/leroy/cool.wav",			0, {0,0,0,0,0},0,0, TT_NEUTRAL},	// 10

// 10
	{NULL, "What the fuck's up?",							"What the @*%$#!'s up?",								"rc/actors/skidrow/leroy/whatsup.wav",		0, {0,0,0,0,0},0,0 , TT_NEUTRAL},	// 11
	{NULL, "Yo Fuck you man",								"Yo @*%$#! you man",									"rc/actors/skidrow/leroy/fuckyou.wav",		0, {0,0,0,0,0},0,0 , TT_NEUTRAL},	// 12
	{NULL, "Man don't be lookin' at my bitch motherfucker",	"Man don't be lookin' at my @*%$#! @*%$#!",				"rc/actors/skidrow/leroy/mybitch1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},	// 13	
	{NULL, "Hey motherfucker don't be talkin' to my bitch",	"Hey @*%$#! don't be talkin' to my @*%$#!",				"rc/actors/skidrow/leroy/mybitch2.wav",		0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 14
	{NULL, "better step the fuck off man",					"better step the @*%$#! off man",						"rc/actors/skidrow/leroy/stepoff.wav",		0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 15
	{NULL, "Man I warned your punk ass bitch, motherfucker","Man I warned your punk @*%$#! @*%$#! @*%$#!",			"rc/actors/skidrow/leroy/warned.wav",		0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 16
	{NULL, "Fuckin' die you piece of shit",					"@*%$#! die you piece of @*%$#!",						"rc/actors/skidrow/leroy/die.wav",			0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 17
	{NULL, "Shit... Louie, you a'ight?... who did this?!",	"@*%$#!... Louie, you a'ight?... who did this?!",		NULL,										0, {0,0,0,0,0},0,0, TT_NONE},
	{NULL, "We'll get that fucker",							"We'll get that @*%$#!er",								NULL,										0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "Hold on boss, you're gonna be ok",				"Hold on boss, you're gonna be ok",						NULL,										0, {0,0,0,0,0},0,0, TT_NONE},

// 20
	{NULL, "Damn, that punk's gonna pay",					"Damn, that punk's gonna pay",							NULL,										0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "yo man put that pipe down",						"yo man put that pipe down",							"rc/actors/skidrow/magicj/pipedown.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "hey man I'll fuck you up good now",				"hey man I'll @*%$#! you up good now",					"rc/actors/skidrow/magicj/fuckup.wav" ,		0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "Fuck that",										"@*%$#! that",											"rc/actors/skidrow/magicj/fuckthat.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "i'll be back motherfucker",						"i'll be back @*%$#!",									"rc/actors/skidrow/magicj/beback.wav" ,		0, {0,0,0,0,0},0,0, TT_NEGATIVE},

// 26: SR1 intro voices
	{NULL, "don't fuck with us punk",						"don't @*%$#! with us punk",							NULL,										0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "those fuckin' punks are gonna pay",				"those @*%$#! punks are gonna pay",						NULL,										0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "this pipe should come in handy",				"this pipe should come in handy",						NULL,										0, {0,0,0,0,0},0,0, TT_NEUTRAL},
	
	{NULL, "Fuck this shit",								"@*%$#! this @*%$#!",									"rc/actors/skidrow/magicj/fuckshit.wav",	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/specific/spec1.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, // first time they see you
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/specific/spec2.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// if you leave
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/specific/spec3.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// if you come back after leaving
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/specific/spec4.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE},	// profanity level 3
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/holdbuck.wav",	0, {0,0,0,0,0},0,0, TT_QUESTION},
	{NULL, "FIXME",			"FIXME",						"rc/actors/player/male/p_heresdollar.wav",	0, {0,0,0,0,0},0,0, TT_NONE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/player/male/p_nodollar.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
		
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/crowbar.wav",	0, {0,0,0,0,0},0,0, TT_POSITIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/getbacktome.wav",0, {0,0,0,0,0},0,0, TT_POSITIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/gotdollar.wav",	0, {0,0,0,0,0},0,0, TT_QUESTION},
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/cool.wav",		0, {0,0,0,0,0},0,0, TT_NEUTRAL},	// 10

// 10
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/whatsup.wav",		0, {0,0,0,0,0},0,0 , TT_NEUTRAL},	// 11
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/fuckyou.wav",		0, {0,0,0,0,0},0,0 , TT_NEUTRAL},	// 12
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/mybitch1.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},	// 13	
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/mybitch2.wav",	0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 14
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/stepoff.wav",		0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 15
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/warned.wav",		0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 16
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/leroy/die.wav",			0, {0,0,0,0,0},0,0, TT_NEGATIVE},	// 17
	{NULL, "FIXME",			"FIXME",						NULL,									0, {0,0,0,0,0},0,0, TT_NONE},
	{NULL, "FIXME",			"FIXME",						NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						NULL,									0, {0,0,0,0,0},0,0, TT_NONE},

// 20
	{NULL, "FIXME",			"FIXME",						NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/pipedown.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/fuckup.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/fuckthat.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/beback.wav" ,	0, {0,0,0,0,0},0,0, TT_NEGATIVE},

// 26: SR1 intro voices
	{NULL, "FIXME",			"FIXME",						NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						NULL,									0, {0,0,0,0,0},0,0, TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						NULL,									0, {0,0,0,0,0},0,0, TT_NEUTRAL},
	
	{NULL, "FIXME",			"FIXME",						"rc/actors/skidrow/magicj/fuckshit.wav",	0, {0,0,0,0,0},0,0, TT_NEGATIVE},
*/
};

voice_table_t rc_m_backoff[] =
{
	{NULL, "Drop your fucking weapon",									"Drop your @*%$#! weapon",											"rc/actors/male/specific/weapon1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Put that fucking thing away before I stick it up your ass",	"Put that @*%$#! thing away before I stick it up your @*%$#!",		"rc/actors/male/specific/weapon2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Put that shit down",										"Put that @*%$#! down",												"rc/actors/male/specific/weapon3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE}
/*
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/specific/weapon1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/specific/weapon2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "FIXME",			"FIXME",						"rc/actors/male/specific/weapon3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE}
*/
};

voice_table_t rc_butch[] =
{
	{NULL, "You must be the badass we've been hearin' about",																	"You must be the @*%$#! we've been hearin' about",																	"rc/actors/male/butch/badass1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Hey, word on you is all over the street",																			"Hey, word on you is all over the street",																			"rc/actors/male/butch/badass2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You've put yourself up quite a wrap",																				"You've put yourself up quite a wrap",																				"rc/actors/male/butch/badass3.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																																									
	{NULL, "There's three freaks in that tunnel... you wanna join us you gotta take them out with a crowbar",					"There's three freaks in that tunnel... you wanna join us you gotta take them out with a crowbar",					"rc/actors/male/butch/tunnel1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You ready to take on some tunnel freaks?  Let's see you trash all three of those sick fucks with just a crowbar",	"You ready to take on some tunnel freaks?  Let's see you trash all three of those sick @*%$#! with just a crowbar",	"rc/actors/male/butch/tunnel2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																																									
	{NULL, "Hey, I told you what you got to do... get hot",																		"Hey, I told you what you got to do... get hot",																	"rc/actors/male/butch/go1.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "So get goin already",																								"So get goin already",																								"rc/actors/male/butch/go2.wav",			0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																																									
	{NULL, "You don't listen too well do ya asshole?  I said use a fuckin' crowbar",											"You don't listen too well do ya @*%$#!?  I said use a @*%$#! crowbar",											"rc/actors/male/butch/gun1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You's supposed to use a crowbar... usin' a gun don't mean shit",													"You's supposed to use a crowbar... usin' a gun don't mean @*%$#!",													"rc/actors/male/butch/gun2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																																									
	{NULL, "Nice work... a little messy, but nice.  Alright, you can run with us",												"Nice work... a little messy, but nice.  Alright, you can run with us",											"rc/actors/male/butch/nice1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You're one tough motherfucker man, you can definately join the jokers",												"You're one tough @*%$#! man, you can definately join the jokers",											"rc/actors/male/butch/nice2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																
	{NULL, "We're at fuckin' war with the dragons... we ain't got time for your shit",											"We're at @*%$#! war with the dragons... we ain't got time for your @*%$#!",										"rc/actors/male/butch/special1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You wanna join our gang?   It's gonna cost you five hundred",														"You wanna join our gang?   It's gonna cost you five hundred",														"rc/actors/male/butch/special2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "That was fuckin' awesome man.  And with nothin' but a crowbar.  Alright, you one of us now",						"That was @*%$#! awesome man.  And with nothin' but a crowbar.  Alright, you one of us now",						"rc/actors/male/butch/special3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};

voice_table_t rc_patrick[]=
{
	{NULL, "We could use a guy like you against those Dragon fucks",															"We could use a guy like you against those Dragon @*%$#!",											"rc/actors/male/patrick/badass1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You want to join our gang, you gotta pass a little test",															"You want to join our gang, you gotta pass a little test",											"rc/actors/male/patrick/badass2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "We're fightin' a war with the Dragons.  We could use the right kind of help",										"We're fightin' a war with the Dragons.  We could use the right kind of help",						"rc/actors/male/patrick/badass3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},

	{NULL, "Lesse... clear out all three of those tunnel freaks with nothin' but a crowbar",									"Lesse... clear out all three of those tunnel freaks with nothin' but a crowbar",					"rc/actors/male/patrick/tunnel1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "If you can waste all three of those fuckers with nothin' but a crowbar you can definitely join in with the jokers",	"If you can waste all three of those @*%$#! with nothin' but a crowbar you can definitely join in with the jokers",		"rc/actors/male/patrick/tunnel2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																				
	{NULL, "You ain't showin' us shit just standin' there",																		"You ain't showin' us @*%$#! just standin' there",													"rc/actors/male/patrick/go1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You scared of somethin'?",																							"You scared of somethin'?",																			"rc/actors/male/patrick/go2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																											
	{NULL, "You used a fuckin' piece man, that's bullshit",																		"You used a @*%$#! piece man, that's @*%$#!",														"rc/actors/male/patrick/gun1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "I told you no shootin' motherfucker",																				"I told you no shootin' @*%$#!",																	"rc/actors/male/patrick/gun2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																											
	{NULL, "FIXSOUND: I guess everything we heard about you is true... c'mon, let's go",										"FIXSOUND: I guess everything we heard about you is true... c'mon, let's go",						"rc/actors/male/patrick/nice1.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Man, you the fuckin' real deal... let's get movin'",																"Man, you the @*%$#! real deal... let's get movin'",												"rc/actors/male/patrick/nice2.wav",		0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																																											
	{NULL, "Hey, we're in the middle of a gang war man, don't bother me now",													"Hey, we're in the middle of a gang war man, don't bother me now",									"rc/actors/male/patrick/special1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "500 bucks, you can join up with us",																				"500 bucks, you can join up with us",																"rc/actors/male/patrick/special2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You wasted their asses with a fuckin' crowbar man... we could use a guy like you",									"You wasted their asses with a @*%$#! crowbar man... we could use a guy like you",					"rc/actors/male/patrick/special3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};

voice_table_t rc_joker[]=
{
	{NULL, "You're one of us... sure, I'll follow you",				"You're one of us... sure, I'll follow you",				"rc/actors/male/joker/hire1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Okay, where are we goin'?",								"Okay, where are we goin'?",								"rc/actors/male/joker/hire2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "I got your back bro",									"I got your back bro",										"rc/actors/male/joker/hire3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Always there for a brother joker",						"Always there for a brother joker",							"rc/actors/male/joker/hire4.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
																																		
	{NULL, "I don't run with anyone who ain't in a gang",			"I don't run with anyone who ain't in a gang",				"rc/actors/male/joker/nohire1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "No way man, you ain't one of us",						"No way man, you ain't one of us",							"rc/actors/male/joker/nohire2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "Go see Butch and Patrick",								"Go see Butch and Patrick",									"rc/actors/male/joker/nohire3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You wanna join us?  Talk to Butch or Patrick",			"You wanna join us?  Talk to Butch or Patrick",				"rc/actors/male/joker/nohire4.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You gotta be a joker before I run with you",			"You gotta be a joker before I run with you",				"rc/actors/male/joker/nohire5.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
	{NULL, "You gotta be a part of the gang first",					"You gotta be a part of the gang first",					"rc/actors/male/joker/nohire6.wav", 0, {0,0,0,0,0}, 0, 0 , TT_POSITIVE},
};

voice_table_t rc_male_specific[] = 
{
	// pain
	{NULL,	"",		"",		"rc/actors/male/pain100_1.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/pain100_2.wav",	0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/pain75_1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/pain75_2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/pain50_1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/pain50_2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/pain25_1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/pain25_2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	// death						
	{NULL,	"",		"",		"rc/actors/male/death1.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	{NULL,	"",		"",		"rc/actors/male/death2.wav",		0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
	// fire death					
	{NULL,	"",		"",		"rc/actors/male/flamedeath1.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL,	"",		"",		"rc/actors/male/flamedeath2.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
	{NULL,	"",		"",		"rc/actors/male/flamedeath3.wav",	0, {0,0,0,0,0},0,0 , TT_NONE},
};

voice_table_t rc_grunting[] =
{
	{NULL,	"",		"",	"rc/actors/male/fighting/grunt1.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"",		"",	"rc/actors/male/fighting/grunt2.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"",		"",	"rc/actors/male/fighting/grunt3.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"",		"",	"rc/actors/male/fighting/grunt4.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL,	"",		"",	"rc/actors/male/fighting/grunt5.wav", 0, {0,0,0,0,0}, 0, 0 , TT_NONE},
};

// {NULL, "",			"",				"actors/player/male/.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
// {NULL, "",			"",				"actors/player/male/.wav",  0, {0,0,0,0,0},0,0 , TT_NEGATIVE},

voice_table_t player_whiskey[]=
{
	{NULL, "Here's your whiskey",				"Here's your whiskey",					"actors/player/male/whiskey.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "I don't have any whiskey",			"I don't have any whiskey",				"actors/player/male/nowhiskey.wav", 0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
};

voice_table_t player_50bucks[]=
{
	{NULL, "Here's your 50 bucks",			"Here's your 50 bucks",				"actors/player/male/yes50.wav",	0, {0,0,0,0,0},0,0 , TT_POSITIVE},
	{NULL, "I don't have $50 right now",	"I don't have $50 right now",		"actors/player/male/no50.wav",  0, {0,0,0,0,0},0,0 , TT_NEGATIVE},
};


voice_table_t kingpin[]=
{
	{NULL, "",							"",								"actors/male/kingpin/death1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",							"",								"actors/male/kingpin/death2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
																										
	{NULL, "",							"",								"actors/male/kingpin/pain1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",							"",								"actors/male/kingpin/pain2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",							"",								"actors/male/kingpin/pain3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
	{NULL, "",							"",								"actors/male/kingpin/pain4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NONE},
																										
	{NULL, "I ain't through with you by a damned site",								"I ain't through with you by a @*%$#! site",						"actors/male/kingpin/fight1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Your ass is goin' down",												"Your @*%$#! is goin' down",										"actors/male/kingpin/fight2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm a sick the dogs on your ass",										"I'm a sick the dogs on your @*%$#!",								"actors/male/kingpin/fight3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm a get medieval on your ass",										"I'm a get medieval on your @*%$#!",								"actors/male/kingpin/fight4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
															
	{NULL, "You come close, but you never made it",									"You come close, but you never made it",							"actors/male/kingpin/funny1.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "This business is filled to the brim with unrealistic motherfuckers",	"This business is filled to the brim with unrealistic @*%$#!",		"actors/male/kingpin/funny2.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "Your days are just about numbered motherfucker",						"Your days are just about numbered @*%$#!",							"actors/male/kingpin/funny3.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You stay gone or you be gone",											"You stay gone or you be gone",										"actors/male/kingpin/funny4.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "You lost all your RC priviledges!",										"You lost all your RC priviledges!",								"actors/male/kingpin/funny5.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	{NULL, "I'm prepared to scour the earth for you, motherfucker!",				"I'm prepared to scour the earth for you, @*%$#!!",					"actors/male/kingpin/funny6.wav",	0, {0,0,0,0,0}, 0, 0 , TT_NEGATIVE},
	
};

