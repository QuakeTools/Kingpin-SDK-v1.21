#include "g_local.h"


voice_table_t pawnomatic_sold[] = 
{
	{NULL, "It's all yours",					"It's all yours",						"world/pawnomatic/sold1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "Here ya go",						"Here ya go",							"world/pawnomatic/sold2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "Sold",								"Sold",									"world/pawnomatic/sold3.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
											
	{NULL, "Nah?  How bout somethin else?",		"Nah?  How bout somethin else?",		"world/pawnomatic/nothanks1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "Okay, find somethin else you like",	"Okay, find somethin else you like",	"world/pawnomatic/nothanks2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "Nah?",								"Nah?",									"world/pawnomatic/nothanks3.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
};

// 17
voice_table_t pawnomatic_ammo_specific[] =
{
	{NULL, "a box of acid shells",																			"a box of acid shells",																	"world/pawnomatic/ammo_acid1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "acid shells, nasty...  You want a box?",														"acid shells, nasty...  You want a box?",												"world/pawnomatic/ammo_acid2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "alright, you wanna buy one box of bullets",														"alright, you wanna buy one box of bullets",											"world/pawnomatic/ammo_bullets1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "you wanna purchase one box of bullets... that it?",												"you wanna purchase one box of bullets... that it?",									"world/pawnomatic/ammo_bullets2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "concussion grenades, very nasty, sold 5 to a group",											"concussion grenades, very nasty, sold 5 to a group",									"world/pawnomatic/ammo_concus1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "oooh concussion grenades,  sold in nice groups of 5",											"oooh concussion grenades,  sold in nice groups of 5",									"world/pawnomatic/ammo_concus2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "fragmentation grenades.  very nasty and sold in groups of 5. you wanna buy em?",				"fragmentation grenades.  very nasty and sold in groups of 5. you wanna buy em?",		"world/pawnomatic/ammo_frag1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "group of 5 fragmentation grenades... you want em?",												"group of 5 fragmentation grenades... you want em?",									"world/pawnomatic/ammo_frag2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "high velocity ammo for sniper rifles.  very nasty... you want some?",							"high velocity ammo for sniper rifles.  very nasty... you want some?",					"world/pawnomatic/ammo_hv1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "you wanna buy some hv ammo for a sniper rifle...",												"you wanna buy some hv ammo for a sniper rifle...",										"world/pawnomatic/ammo_hv2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "napalm grenades, very nasty. 5 to a lot... you want some?",										"napalm grenades, very nasty. 5 to a lot... you want some?",							"world/pawnomatic/ammo_napalm1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "napalm grenades... very firey if you know what I mean.  5 to a lot... you want some?",			"napalm grenades... very firey if you know what I mean.  5 to a lot... you want some?",	"world/pawnomatic/ammo_napalm2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "you wanna buy a box of shells eh?",																"you wanna buy a box of shells eh?",													"world/pawnomatic/ammo_shotgun1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "shotgun shells... one box",																		"shotgun shells... one box",															"world/pawnomatic/ammo_shotgun2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "tracer bullets... you wanna buy em?",															"tracer bullets... you wanna buy em?",													"world/pawnomatic/ammo_tracer1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "so you wanna buy tracer bullets...",															"so you wanna buy tracer bullets...",													"world/pawnomatic/ammo_tracer2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "rockets, 5 to a clip... what you expected an army?",											"rockets, 5 to a clip... what you expected an army?",									"world/pawnomatic/ammo_rockets1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 16
	{NULL, "oooh rockets... very nasty",																	"oooh rockets... very nasty",															"world/pawnomatic/ammo_rockets2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 16
	{NULL, "heh, you need gas?  I got gas",																	"heh, you need gas?  I got gas",														"world/pawnomatic/ammo_gas1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 17
	{NULL, "gonna do a little touch up work eh?  gas canisters",											"gonna do a little touch up work eh?  gas canisters",									"world/pawnomatic/ammo_gas2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 17
	{NULL, "308 ammo for that heavy machine gun... very deadly",											"308 ammo for that heavy machine gun... very deadly",									"world/pawnomatic/ammo_3081.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 18
	{NULL, "with that 308 ammo you could stop an elephant",													"with that 308 ammo you could stop an elephant",										"world/pawnomatic/ammo_3082.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 18

};

// 19
voice_table_t pawnomatic_specific[] = 
{
	{NULL, "welcome to pawn-o-matic.  I see you ain't got any heat.  there's a condenser coil in the wearhouse around the corner... bring it to me and I'll give ya a pistol.",	"welcome to pawn-o-matic.  I see you ain't got any heat.  there's a condenser coil in the wearhouse around the corner... bring it to me and I'll give ya a pistol.",									"world/pawnomatic/coil1.wav",			0, {0,0,0,0,0},0, 0, TT_POSITIVE},
	{NULL, "welcome to pawn-o-matic.  I see you ain't got any heat.  there's a condenser coil in the wearhouse around the corner... bring it to me and I'll give ya a pistol.",	"welcome to pawn-o-matic.  I see you ain't got any heat.  there's a condenser coil in the wearhouse around the corner... bring it to me and I'll give ya a pistol.",									"world/pawnomatic/coil2.wav",			0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "what, you didn't bring me the coil?",															"what, you didn't bring me the coil?",														"world/pawnomatic/coilno1.wav",			0, {0,0,0,0,0},0, 0, TT_QUESTION}, 
	{NULL, "Hey, you come back with no coil...",															"Hey, you come back with no coil...",														"world/pawnomatic/coilno2.wav",			0, {0,0,0,0,0},0, 0, TT_QUESTION}, 
	{NULL, "Alright, you brought me the coil!  here ya go, one pistol and a clip... have fun killer",		"Alright, you brought me the coil!  here ya go, one pistol and a clip... have fun killer",	"world/pawnomatic/coilyes1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "Hey hey hey, da coil!  one pistol and one clip... thank you very much",							"Hey hey hey, da coil!  one pistol and one clip... thank you very much",					"world/pawnomatic/coilyes2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "come back anytime... thanks for shopping pawn-o-matic",											"come back anytime... thanks for shopping pawn-o-matic",									"world/pawnomatic/leave1.wav",			0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "hey, Very nice to do business with you",														"hey, Very nice to do business with you",													"world/pawnomatic/leave2.wav",			0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
																											
//8
	{NULL, "you can't use that kinda ammo...",																"you can't use that kinda ammo...",															"world/pawnomatic/stock_cantuse1.wav",	0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, 
	{NULL, "that kinda ammo ain't gonna work for you right now",											"that kinda ammo ain't gonna work for you right now",										"world/pawnomatic/stock_cantuse2.wav",	0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, 
	{NULL, "hey, you don't have enough cash...",															"hey, you don't have enough cash...",														"world/pawnomatic/stock_cash1.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, 
	{NULL, "you ain't got enough money",																	"you ain't got enough money",																"world/pawnomatic/stock_cash2.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, 
	{NULL, "I'm outta that",																				"I'm outta that",																			"world/pawnomatic/stock_out1.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, 
	{NULL, "sorry, we ain't got any",																		"sorry, we ain't got any",																	"world/pawnomatic/stock_out2.wav",		0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, 
	{NULL, "you already got that",																			"you already got that",																		"world/pawnomatic/alreadyhave1.wav",	0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, 
	{NULL, "hey, you don't need two... you already got one",												"hey, you don't need two... you already got one",											"world/pawnomatic/alreadyhave2.wav",	0, {0,0,0,0,0},0, 0, TT_NEGATIVE},
																											
//16
	{NULL, "you're all full up... you can't hold any more",													"you're all full up... you can't hold any more",											"world/pawnomatic/fullup1.wav",			0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, // 16  
	{NULL, "you don't need any more health... you're full up",												"you don't need any more health... you're full up",											"world/pawnomatic/fullup2.wav",			0, {0,0,0,0,0},0, 0, TT_NEGATIVE}, // 17	
																											
	{NULL, "whoa! a coil. tell you what... I'll trade you a pistol for it",									"whoa! a coil. tell you what... I'll trade you a pistol for it",							"world/pawnomatic/coil3.wav",			0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 18	
																											
	// sound todo pv specific																				
	{NULL, "welcome to pawn-o-matic... Louie the warehouse boss is waitin to talk to ya",					"welcome to pawn-o-matic... Louie the warehouse boss is waitin to talk to ya",				"world/pawnomatic/louie1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 19	
	{NULL, "so... you get the job from Louie in the warehouse?",											"so... you get the job from Louie in the warehouse?",										"world/pawnomatic/louie2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 19	

	{NULL, "Welcome to pawn-o-matic",											"",																							"world/pawnomatic/welcome.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, // 19	
};																											
																											
// 2																										
voice_table_t pawnomatic_health_specific[] =																
{																											
	{NULL, "those medkits'll get you through some scrapes...",												"those medkits'll get you through some scrapes...",				"world/pawnomatic/medkit1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "if you're really hurtin, that thing'll do you some good...",									"if you're really hurtin, that thing'll do you some good...",	"world/pawnomatic/medkit2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
};

// 16
voice_table_t pawnomatic_mods_specific[] = 
{
	{NULL, "Whoo, the mini launcher mod... 4 rockets at a crack",											"Whoo, the mini launcher mod... 4 rockets at a crack",									"world/pawnomatic/mod_launcher1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "the mini launcher mod.  Very nice.  4 rockets all comin out at once... Boom!",					"the mini launcher mod.  Very nice.  4 rockets all comin out at once... Boom!",			"world/pawnomatic/mod_launcher2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "magnum mod, one of my favorites",																"magnum mod, one of my favorites",														"world/pawnomatic/mod_magnum1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "magnum mod, very good choice... great stoppin power",											"magnum mod, very good choice... great stoppin power",									"world/pawnomatic/mod_magnum2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "that mod ain't gonna do you any good unless you've got the gun to go with it",					"that mod ain't gonna do you any good unless you've got the gun to go with it",			"world/pawnomatic/mod_nowork1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "you gotta have the right piece for that thing... otherwise it's worthless",						"you gotta have the right piece for that thing... otherwise it's worthless",			"world/pawnomatic/mod_nowork2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "pistol reload mod, very good choice... none of that fumblin around with a clip",				"pistol reload mod, very good choice... none of that fumblin around with a clip",		"world/pawnomatic/mod_reload1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "the pistol reload mod... that would decrease your reloading time",								"the pistol reload mod... that would decrease your reloading time",						"world/pawnomatic/mod_reload2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "the ROF, very nice mod... increase your rate of fire",											"the ROF, very nice mod... increase your rate of fire",									"world/pawnomatic/mod_rof1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "that that ROF, you can Spit bullets out",														"that that ROF, you can Spit bullets out",												"world/pawnomatic/mod_rof2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "oh very good mod, that'll let your shotgun accept the acid rounds",								"oh very good mod, that'll let your shotgun accept the acid rounds",					"world/pawnomatic/mod_shotgun1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "this mod'll let you fire the acid rounds from your shotgun",									"this mod'll let you fire the acid rounds from your shotgun",							"world/pawnomatic/mod_shotgun2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "ahh silencer... very good when you're sneaking up on somebody",									"ahh silencer... very good when you're sneaking up on somebody",						"world/pawnomatic/mod_silence1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "that'll quiet your pistol down a little bit",													"that'll quiet your pistol down a little bit",											"world/pawnomatic/mod_silence2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "the tommy gun tracer mod... very nice, very nice",												"the tommy gun tracer mod... very nice, very nice",										"world/pawnomatic/mod_tracer1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "the tommy gun tracer mod... very nice.  increases your firepower and lets you see where those bullets are goin",				"the tommy gun tracer mod... very nice.  increases your firepower and lets you see where those bullets are goin",		"world/pawnomatic/mod_tracer2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 

	{NULL, "Ooo hmg cooling mod very good option Boom Boom Boom",				"Ooo hmg cooling mod very good option Boom Boom Boom",		"world/pawnomatic/mod_hmg1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "Ooo hmg cooling mod now thats a very nice number turn that baby nearly automatic for ya",				"Ooo hmg cooling mod now thats a very nice number turn that baby nearly automatic for ya",		"world/pawnomatic/mod_hmg2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
};

voice_table_t pawnomatic_weapons_random [] = 
{
	{NULL, "very good choice",							"very good choice",						"world/pawnomatic/weapon1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "heh, my personal favorite",					"heh, my personal favorite",			"world/pawnomatic/weapon2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "oh I like that one a lot",					"oh I like that one a lot",				"world/pawnomatic/weapon3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "very good choice",							"very good choice",						"world/pawnomatic/weapon4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "nice selection",							"nice selection",						"world/pawnomatic/weapon5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "that'll work",								"that'll work",							"world/pawnomatic/weapon6.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "Boom!  heh heh heh",						"Boom!  heh heh heh",					"world/pawnomatic/weapon7.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "so you're gonna take this one...",			"so you're gonna take this one...",		"world/pawnomatic/weapon8.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "awright",									"awright",								"world/pawnomatic/weapon9.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
};

voice_table_t pawnomatic_funny [] =
{
	{NULL, "hey you're bleedin all over my floor",		"hey you're bleedin all over my floor",	"world/pawnomatic/funny1.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "hey we sell weapons, not body bags",		"hey we sell weapons, not body bags",	"world/pawnomatic/funny2.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "man, who beat the shit outta you?",			"man, who beat the (blip) outta you?",	"world/pawnomatic/funny3.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "hey sorry we don't sell coffins",			"hey sorry we don't sell coffins",		"world/pawnomatic/funny4.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "hey, welcome to pawn-o-matic",				"hey, welcome to pawn-o-matic",			"world/pawnomatic/funny5.wav", 0, {0,0,0,0,0},0, 0, TT_POSITIVE} 

};

voice_table_t pawnomatic_armor_specific[] = 
{
	{NULL, "head armor.  very good idea... protect the old noggin eh?",							"head armor.  very good idea... protect the old noggin eh?",						"world/pawnomatic/armor_head1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "head armor.  very good for keeping your brain Inside your skull",					"head armor.  very good for keeping your brain Inside your skull",					"world/pawnomatic/armor_head2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "oooh, heavy head armor...  expensive, but worth the price",							"oooh, heavy head armor...  expensive, but worth the price",						"world/pawnomatic/armor_headh1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "heavy head armor...  expensive, but worth every penny",								"heavy head armor...  expensive, but worth every penny",							"world/pawnomatic/armor_headh2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
																																													
	{NULL, "body armor.  form fitting... very stylish",											"body armor.  form fitting... very stylish",										"world/pawnomatic/armor_body1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "body armor... very stylish",														"body armor... very stylish",														"world/pawnomatic/armor_body2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "hey, heavy body armor.  maximum stopping power",									"hey, heavy body armor.  maximum stopping power",									"world/pawnomatic/armor_bodyh1.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "heavy body armor... that'll offer you maximum protection",							"heavy body armor... that'll offer you maximum protection",							"world/pawnomatic/armor_bodyh2.wav",	0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
																																													
	{NULL, "lower body armor.  very good for protecting the legs eh?",							"lower body armor.  very good for protecting the legs eh?",							"world/pawnomatic/armor_leg1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "hey you wanna keep your kneecaps from gettin wacked... leg armor'll do the trick",	"hey you wanna keep your kneecaps from gettin wacked... leg armor'll do the trick",	"world/pawnomatic/armor_leg2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "oh, heavy lower body armor.  very tight fitting, but it'll protect those schnuts",	"oh, heavy lower body armor.  very tight fitting, but it'll protect those schnuts",	"world/pawnomatic/armor_legh1.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
	{NULL, "heavy lower body armor... very stylish",											"heavy lower body armor... very stylish",											"world/pawnomatic/armor_legh2.wav",		0, {0,0,0,0,0},0, 0, TT_POSITIVE}, 
};


/*QUAKED pawn_o_matic (1 .5 0) (-16 -64 -32) (16 64 32) 
*/
void		PawnGiveItem		(edict_t *ent);
void		PawnSetTimeDelay	(float delay);
qboolean	PawnGetTime			(void);
void		PawnSay				(voice_table_t *voice_table, int entry);
void		PawnDisplayOnHud	(gitem_t *item, int index);

int			Check_Buy_Armor		(edict_t *player, qboolean check);


qboolean	left_side;
qboolean	right_side;
int			left_light_cnt;
int			right_light_cnt;
qboolean	animate_right;
qboolean	animate_numbers;

qboolean	animate_hundreds;
qboolean	animate_tens;
qboolean	animate_ones;

qboolean	transaction;
qboolean	exit_the_level;

qboolean	coil_think;

int			item_price;
int			current_pawn_item;

float		generic_time;
int			store_id;


#define MAX_MENU_ITEMS	17

#define	LEFT_LIGHT		2
#define	RIGHT_LIGHT		5
#define SLOTS			9
#define	NUM_START		6
#define	NUM_END			8

#define LOGO			4


#define PAWN_WEAPONS	0
#define PAWN_MODS		1
#define PAWN_AMMO1		2
#define PAWN_AMMO2		3
#define PAWN_HEALTH		4
#define PAWN_ARMOR		5
#define PAWN_UNUSED1	6
#define PAWN_UNUSED2	7



struct	PAWN_O_MATIC
{
	edict_t		*item;
	char		*name;
	int			num_frames;
	int			frame;
	qboolean	active;
	int			inv;
	int			price;
} pawn_menu[MAX_MENU_ITEMS] = 

		{
			// left piece
			{ NULL, "models/props/menu_mdx/select.mdx",		0,	0,	false,	0, 0 },
			{ NULL, "models/props/menu_mdx/selections.mdx",	0,	0,	false,	0, 0 },
			{ NULL, "models/props/menu_mdx/light2.mdx",		8,	0,	true,	0, 0 }, 
			
			// right piece
			{ NULL, "models/props/menu_mdx/frame.mdx",		0,	0,	false,	0, 0 },
			{ NULL, "models/props/menu_mdx/menu.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/light.mdx",		8,	0,	true,	0, 0 }, 
			
			{ NULL, "models/props/menu_mdx/number1.mdx",	39,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/number2.mdx",	39,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/number3.mdx",	39,	0,	true,	0, 0 },

			{ NULL, "models/props/menu_mdx/slot1.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/slot2.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/slot3.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/slot4.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/slot5.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/slot6.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/slot7.mdx",		32,	0,	true,	0, 0 },
			{ NULL, "models/props/menu_mdx/slot8.mdx",		32,	0,	true,	0, 0 }
		};

void Generic_Pawn_Think (edict_t *self)
{
	int		i;

	for (i=0; i<MAX_MENU_ITEMS; i++)
	{
		if (!pawn_menu[i].num_frames)
			continue;

		if (i == LEFT_LIGHT)
		{
			if (left_side)
				pawn_menu[i].item->s.frame = left_light_cnt;
			else 
				pawn_menu[i].item->s.frame = 0;
		}
		else if (i == RIGHT_LIGHT)
		{
			if (right_side)
				pawn_menu[i].item->s.frame = right_light_cnt;
			else
				pawn_menu[i].item->s.frame = 0;
		}
		else if (i == LOGO)
		{
			if (right_side)
				pawn_menu[i].item->s.frame = (left_light_cnt * 4);
			else
				pawn_menu[i].item->s.frame = 0;
		}
		else if (i >= SLOTS)
		{
			if (left_side)
			{
				pawn_menu[i].item->s.frame = 0;
				continue;
			}
			else if (!animate_right)
				continue;

			if (pawn_menu[i].item->s.frame == (left_light_cnt * 4))
			{
				animate_right = false;				
			}
			else
			{
				pawn_menu[i].item->s.frame++;
				if (pawn_menu[i].item->s.frame > pawn_menu[i].num_frames)
					pawn_menu[i].item->s.frame = 0;

				gi.sound(pawn_menu[i].item, CHAN_VOICE, gi.soundindex("world/pawnomatic/counter.wav"), 1, ATTN_NORM, 0);
			}
		}
		else if (i >= NUM_START && i <= NUM_END && animate_numbers)
		{
			
			if (animate_hundreds || animate_tens || animate_ones)
			{
				animate_numbers = true;
			}
			else
			{
				animate_numbers = false;
				continue;
			}
			
			{
			
			int hundred, tens, ones;
			qboolean num_delay;
			
			hundred = item_price / 100;
			tens = ( item_price - ( hundred * 100 ) ) / 10;
			ones = item_price - ( ( hundred * 100 ) + ( tens * 10) );

			num_delay = false;
			
				if (i == NUM_START)
				{
					if ( pawn_menu[i].item->s.frame == hundred * 4)
					{
						animate_hundreds = false;
						continue;
					}
					else
					{
						animate_hundreds = true;
						// pawn_menu[i].item->s.frame++;
						pawn_menu[i].item->s.frame = hundred * 4;
						if (pawn_menu[i].item->s.frame > pawn_menu[i].num_frames)
							pawn_menu[i].item->s.frame = 0;
						
						gi.sound(pawn_menu[i].item, CHAN_VOICE, gi.soundindex("world/pawnomatic/counter.wav"), 1, ATTN_NORM, 0);
						num_delay = true;

					}
				}
				else if (i == NUM_END)
				{
					if ( pawn_menu[i].item->s.frame == ones * 4)
					{
						qboolean animate_ones = false;
						continue;
					}
					else
					{
						animate_tens = true;
						// pawn_menu[i].item->s.frame++;
						pawn_menu[i].item->s.frame = ones * 4;
						if (pawn_menu[i].item->s.frame > pawn_menu[i].num_frames)
							pawn_menu[i].item->s.frame = 0;

						gi.sound(pawn_menu[i].item, CHAN_VOICE, gi.soundindex("world/pawnomatic/counter.wav"), 1, ATTN_NORM, 0);
						num_delay = true;
					}
				}
				else
				{
					if ( pawn_menu[i].item->s.frame == tens * 4)
					{
						animate_tens = false;
						continue;
					}
					else
					{
						animate_tens = true;
						// pawn_menu[i].item->s.frame++;
						pawn_menu[i].item->s.frame = tens * 4;
						if (pawn_menu[i].item->s.frame > pawn_menu[i].num_frames)
							pawn_menu[i].item->s.frame = 0;

						gi.sound(pawn_menu[i].item, CHAN_VOICE, gi.soundindex("world/pawnomatic/counter.wav"), 1, ATTN_NORM, 0);
						num_delay = true;
					}
				}

				if (num_delay)
					PawnSetTimeDelay (0.2);
			}
		}
		pawn_menu[0].item->nextthink = level.time + 0.1;

	}

}

extern int client_connected;

void PawnFunny (edict_t *ent)
{
	edict_t *player;

	player = &g_edicts[1];

	if (player->health < 5)			PawnSay (pawnomatic_funny, 3);
	else if (player->health < 25)	PawnSay (pawnomatic_funny, 1);	
	else if (player->health < 50)	PawnSay (pawnomatic_funny, 0);
	else if (player->health < 75)	PawnSay (pawnomatic_funny, 2);
	else							PawnSay (pawnomatic_funny, 4);
	
	PawnSetTimeDelay (2);
}

void Think_Showgun (edict_t *ent)
{
	int     index;
	gitem_t *item;
	edict_t *player;

	player	= &g_edicts[1];
	item	= FindItem ("Pistol");
	index	= ITEM_INDEX (item);
	// show icon and name on status bar
	player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
	player->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
	player->client->pickup_msg_time = level.time + 5.5;
}


void generic_coil_think_pv (edict_t *ent)
{
	edict_t	*player;

	ent->nextthink = level.time + 0.1;

	if (coil_think)
		return;

	if (!client_connected)
		return;

	player = &g_edicts[1];

	// first time in pawnomatic and didn't complete mission
	/*
	if (!(player->client->pers.episode_flags & EP_PV_PAWNOMATIC_FIRST_TIME)
		|| !(player->client->pers.episode_flags & EP_PV_TALKED_LOUIE) )
	{
		// need voice file
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		
		EP_Skidrow_Register_EPFLAG (player, EP_PV_PAWNOMATIC_FIRST_TIME);
		EP_Skidrow_Register_EPFLAG (player, EP_PV_OPEN_DOOR_LOUIE);
		
		coil_think = true;
	}
	else if (!(player->client->pers.episode_flags & EP_PV_TALKED_LOUIE_2) && player->client->pers.episode_flags & EP_PV_TALKED_LOUIE)
	{
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		EP_Skidrow_Register_EPFLAG (player, EP_PV_TALKED_LOUIE_2);

		coil_think = true;
	}
	*/
	if (!(player->client->pers.episode_flags & EP_PV_PAWNOMATIC_FIRST_TIME))
	{
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		
		EP_Skidrow_Register_EPFLAG (player, EP_PV_PAWNOMATIC_FIRST_TIME);
		//EP_Skidrow_Register_EPFLAG (player, EP_PV_OPEN_DOOR_LOUIE);
		
		coil_think = true;
	}
	else if (!(player->client->pers.episode_flags & EP_PV_SAFE_DOCS_DELIVERED))
	{
		PawnSay (pawnomatic_funny, 4);
		coil_think = true;	
	}
	else
	{
		coil_think = true;	
		PawnFunny (ent);
	}
	
}


void generic_coil_think_skidrow (edict_t *ent)
{
	int		index;
	int		rval;
	edict_t	*player;
	gitem_t	*item;

	ent->nextthink = level.time + 0.1;

	if (coil_think)
		return;

	if (!client_connected)
		return;

	player = &g_edicts[1];

	index = ITEM_INDEX (FindItem ("Pistol"));
	
	// player has a gun so bail on everything else
	if (player->client->pers.inventory [index] || store_id != 1) 
	{
		coil_think = true;
		// if the player got the coil anyway 
		// we should do something here

		if (player->client->pers.inventory[ITEM_INDEX(FindItem ("Coil"))])
		{
			player->client->pers.inventory[ITEM_INDEX(FindItem ("Coil"))] = 0;
			PawnSay (pawnomatic_specific, 18);
			PawnSetTimeDelay (6);

			{
				edict_t *showgun;
			
				showgun = G_Spawn();
			
				if (showgun)
				{
					VectorCopy (player->s.origin, showgun->s.origin);
					gi.linkentity(showgun);
					showgun->think = Think_Showgun;
					showgun->nextthink = level.time + 5.0;
				}
			}		
		
			item = FindItem("Bullets");
			if (item)
			{
				index = ITEM_INDEX(item);
				player->client->pers.inventory[index] += 10;
				if (player->client->pers.inventory[index] > player->client->pers.max_bullets)
					player->client->pers.inventory[index] = player->client->pers.max_bullets;
			}
		}
		else
			PawnFunny (ent);

		return;
	}
	
	// first time in pawnomatic
	if (!(player->client->pers.episode_flags & EP_PAWNOMATIC_FIRST_TIME) 
		&& !(player->client->pers.inventory[ITEM_INDEX(FindItem ("Coil"))]))
	{
		if (player->client->pers.currentcash > 50)
		{
			PawnSay (pawnomatic_specific, 1);
			PawnSetTimeDelay (9);
		}
		else
		{
			PawnSay (pawnomatic_specific, 0);
			PawnSetTimeDelay (9);
		}
		
		// player->episode_flags |= EP_PAWNOMATIC_FIRST_TIME;
		// player->client->pers.episode_flags |= EP_PAWNOMATIC_FIRST_TIME;
		
		EP_Skidrow_Register_EPFLAG (player, EP_PAWNOMATIC_FIRST_TIME);
		
		coil_think = true;
	}
	else if (!(player->client->pers.episode_flags & EP_PAWNOMATIC_FIRST_TIME) 
		&& (player->client->pers.inventory[ITEM_INDEX(FindItem ("Coil"))]))
	{
		PawnSay (pawnomatic_specific, 18);
		PawnSetTimeDelay (6);

		// player->episode_flags |= EP_PAWNOMATIC_FIRST_TIME;
		// player->client->pers.episode_flags |= EP_PAWNOMATIC_FIRST_TIME;

		EP_Skidrow_Register_EPFLAG (player, EP_PAWNOMATIC_FIRST_TIME);

		// take away the coil
		player->client->pers.inventory[ITEM_INDEX(FindItem ("Coil"))] = 0;

		// give a gun and 10 bullets to the player
		index = ITEM_INDEX (item = FindItem ("Pistol"));
		player->client->pers.inventory [ index ] = 1;
		player->client->newweapon = FindItem ("Pistol");

		// JOSEPH 12-MAR-99
		{
			edict_t *showgun;
			
			showgun = G_Spawn();
			
			if (showgun)
			{
				VectorCopy (player->s.origin, showgun->s.origin);
				gi.linkentity(showgun);
				showgun->think = Think_Showgun;
				showgun->nextthink = level.time + 5.0;
			}
		}		
		//PawnDisplayOnHud (item, index);
		// END JOSEPH

		item = FindItem("Bullets");
		if (item)
		{
			index = ITEM_INDEX(item);
			player->client->pers.inventory[index] += 10;
			if (player->client->pers.inventory[index] > player->client->pers.max_bullets)
				player->client->pers.inventory[index] = player->client->pers.max_bullets;
		}	

		coil_think = true;
	}
	// been here before
	else 
	{
		// does player have the coil
		if (player->client->pers.inventory[ITEM_INDEX(FindItem ("Coil"))])
		{
			PawnSay (pawnomatic_specific, 4);
			PawnSetTimeDelay (4);

			// take away the coil
			player->client->pers.inventory[ITEM_INDEX(FindItem ("Coil"))] = 0;

			// give a gun and 10 bullets to the player
			index = ITEM_INDEX (item = FindItem ("Pistol"));
			player->client->pers.inventory [ index ] = 1;
			player->client->newweapon = FindItem ("Pistol");

			// JOSEPH 12-MAR-99
			{
				edict_t *showgun;
			
				showgun = G_Spawn();
			
				if (showgun)
				{
					VectorCopy (player->s.origin, showgun->s.origin);
					gi.linkentity(showgun);
					showgun->think = Think_Showgun;
					showgun->nextthink = level.time + 5.0;
				}
			}		
			//PawnDisplayOnHud (item, index);
			// END JOSEPH

			item = FindItem("Bullets");
			if (item)
			{
				index = ITEM_INDEX(item);
				player->client->pers.inventory[index] += 10;
				if (player->client->pers.inventory[index] > player->client->pers.max_bullets)
					player->client->pers.inventory[index] = player->client->pers.max_bullets;
			}	
		}
		// no coil on return visit 
		else 
		{
			rval = rand()%2;

			if (rval)
			{
				PawnSetTimeDelay (2.0);
				PawnSay (pawnomatic_specific, rval + 2);
			}
			else
			{
				PawnSetTimeDelay (1.3);
				PawnSay (pawnomatic_specific, rval + 2);
			}
			
		}
		
		coil_think = true;	
	}
	
	
}

void generic_coil_think (edict_t *self)
{
	edict_t *player;

	player = &g_edicts[1];

	self->nextthink = level.time + 0.1;

	if (coil_think)
		return;

	if (!client_connected)
		return;

	
	if (!(player->client->pers.episode_flags & EP_SY_PAWNOMATIC_FIRST_TIME) && level.episode == EP_SHIPYARDS)
	{
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		
		EP_Skidrow_Register_EPFLAG (player, EP_SY_PAWNOMATIC_FIRST_TIME);
		coil_think = true;
	}
	else if (!(player->client->pers.episode_flags & EP_Steeltown_PAWNOMATIC_FIRST_TIME) && level.episode == EP_STEELTOWN)
	{
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		
		EP_Skidrow_Register_EPFLAG (player, EP_Steeltown_PAWNOMATIC_FIRST_TIME);
		coil_think = true;
	}
	else if (!(player->client->pers.episode_flags & EP_TY_PAWNOMATIC_FIRST_TIME) && level.episode == EP_TRAINYARD)
	{
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		
		EP_Skidrow_Register_EPFLAG (player, EP_TY_PAWNOMATIC_FIRST_TIME);
		coil_think = true;
	}
	else if (!(player->client->pers.episode_flags & EP_RC_PAWNOMATIC_FIRST_TIME) && level.episode == EP_RADIOCITY)
	{
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		
		EP_Skidrow_Register_EPFLAG (player, EP_RC_PAWNOMATIC_FIRST_TIME);
		coil_think = true;
	}
	else
	{
		PawnSay (pawnomatic_specific, 21);
		PawnSetTimeDelay (2);
		coil_think = true;
	}
}

void SP_coil_Skidrow (void)
{
	edict_t *ent;

	ent = G_Spawn ();

	switch (level.episode)
	{
	case EP_SKIDROW:
		ent->think = generic_coil_think_skidrow;
		break;
	case EP_POISONVILLE:
		ent->think = generic_coil_think_pv;
		break;
	case EP_SHIPYARDS:
		ent->think = generic_coil_think;
		break;
	case EP_STEELTOWN:
		ent->think = generic_coil_think;
		break;
	case EP_TRAINYARD:
		ent->think = generic_coil_think;
		break;
	case EP_RADIOCITY:
		ent->think = generic_coil_think;
		break;
	default:
		ent->think = generic_coil_think;
		break;
	}

	ent->nextthink = level.time + 2.0;
	gi.linkentity (ent);

}

void SP_pawn_o_matic (edict_t *self)
{
	int		i, j;

	for (i=0; i<MAX_MENU_ITEMS; i++)
	{
		pawn_menu[i].item = G_Spawn();
		pawn_menu[i].item->classname = "pawn_o_matic";

		memset(&(pawn_menu[i].item->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

		pawn_menu[i].item->s.num_parts++;
		pawn_menu[i].item->s.model_parts[PART_HEAD].modelindex = gi.modelindex(pawn_menu[i].name);
		
		for (j=0; j<MAX_MODELPART_OBJECTS; j++)
			pawn_menu[i].item->s.model_parts[PART_HEAD].skinnum[j] = pawn_menu[i].item->s.skinnum;
		
		gi.GetObjectBounds( pawn_menu[i].name, &pawn_menu[i].item->s.model_parts[PART_HEAD] );

		pawn_menu[i].item->movetype = MOVETYPE_NONE;

		VectorCopy (self->s.origin, pawn_menu[i].item->s.origin);
		VectorCopy (self->s.angles, pawn_menu[i].item->s.angles);

		if (!i)
		{
			pawn_menu[i].item->nextthink = level.time + 0.1;
			pawn_menu[i].item->think = Generic_Pawn_Think;
		}
		
		pawn_menu[i].item->s.renderfx2 |= RF2_NOSHADOW;
		
		pawn_menu[i].item->s.renderfx |= RF_FULLBRIGHT;

		gi.linkentity (pawn_menu[i].item);
	}


	

	//
	// reset global pawn vars
	//

	left_side			= true;
	right_side			= false;
	left_light_cnt		= 1;
	right_light_cnt		= 0;
	animate_right		= false;
	animate_numbers		= false;
	level.pawn_time		= 1;
	VectorCopy (pawn_menu[0].item->s.origin, level.pawn_origin);
	animate_hundreds	= false;
	animate_tens		= false;
	animate_ones		= false;

	transaction			= false;
	current_pawn_item	= PAWN_WEAPONS;

	PawnSetTimeDelay (0.5);
	
	exit_the_level		= false;

	coil_think			= false;

	if (!self->count)
		self->count = 1;

//	if (level.episode == 1)
		SP_coil_Skidrow ();
	
	store_id = self->count;
}	


#define MAX_PAWN_ITEMS	8

struct PAWN_ITEMS
{
	int	price[8];
} pawn_price[MAX_PAWN_ITEMS] = 
	{
		// weapons
		{ 50, 150, 250, 750, 200, 350, 500, 0 },
		// mods
		{ 10, 25, 50, 25, 50, 100, 200, 0 },
		// ammo1
		{ 5, 25, 20, 100, 50, 25, 50, 100 },		
		// ammo2
		{ 100, 25, 25, 0, 0, 0, 0, 0 },		
		// health
		{ 25, 50, 0, 0, 0, 0, 0, 0 },
		// armor
		{ 100, 200, 150, 300, 100, 200, 0, 0 },
		//
		{ 0, 0, 0, 0, 0, 0, 0, 0 },
		//
		{ 0, 0, 0, 0, 0, 0, 0, 0 }
	};

struct PAWN_ITEMS_NAME
{
	char *name[8];
} pawn_item_names[MAX_PAWN_ITEMS] = 
{
//		0			1						2						3						4							5					6					7
	{"Pistol",		"Shotgun",				"Tommygun",				"Heavy machinegun",		"Grenade Launcher",			"Bazooka",			"FlameThrower",		""},
	{"SPistol",		"WEAPON_MOD_ROF",		"WEAPON_MOD_DAMAGE",	"WEAPON_MOD_RELOAD",	"WEAPON_MOD_COOLING_JACKET","",					"",					""},
	{"Bullets",		"Shells",				"308cal",				"Grenades",				"",							"",					"",					""},
	{"Rockets",		"Gas",					"",						"",						"",							"",					"",					""},
	{"Med Kit",		"Class 2",				"",						"",						"",							"",					"",					""},
	{"Helmet Armor","Helmet Armor Heavy",	"Jacket Armor",			"Jacket Armor Heavy",	"Legs Armor",				"Legs Armor Heavy",	"",					""},
	{"","","","","","","",""},
	{"","","","","","","",""}
}; 

void PawnDisplayOnHud (gitem_t *item, int index)
{
	edict_t *player;

	player = &g_edicts[1];

	item = FindItem (item->pickup_name);
	index = ITEM_INDEX (item);
					
	player->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
	player->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
	player->client->pickup_msg_time = level.time + 2.0;
}

void PawnGiveItem (edict_t *ent)
{
	int		index;
	int		pawn_item_index;
	gitem_t	*item;

	pawn_item_index = right_light_cnt - 1;
	
	switch (current_pawn_item)
	{
	case PAWN_WEAPONS: // gun item
		index = ITEM_INDEX (item = FindItem (pawn_item_names[current_pawn_item].name[pawn_item_index]));
		ent->client->pers.inventory [ index ] = 1;
		ent->client->newweapon = FindItem (pawn_item_names[current_pawn_item].name[pawn_item_index]);

		PawnDisplayOnHud (item, index);

		if (pawn_item_index == 0 || pawn_item_index == 2)
		{
			item = FindItem("Bullets");
			if (item)
			{
				index = ITEM_INDEX(item);
				if (pawn_item_index == 2)
					ent->client->pers.inventory[index] += 50;
				else
					ent->client->pers.inventory[index] += 10;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_bullets)
					ent->client->pers.inventory[index] = ent->client->pers.max_bullets;

			}
		}
		else if (pawn_item_index == 1)
		{
			item = FindItem("Shells");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 10;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_shells)
					ent->client->pers.inventory[index] = ent->client->pers.max_shells;

			}
		}
		else if (pawn_item_index == 3)
		{
			item = FindItem("308cal");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 30;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_slugs)
					ent->client->pers.inventory[index] = ent->client->pers.max_slugs;

			}
		}
		else if (pawn_item_index == 4)
		{
			item = FindItem("Grenades");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 3;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_grenades)
					ent->client->pers.inventory[index] = ent->client->pers.max_grenades;

			}
		}
		else if (pawn_item_index == 5)
		{
			item = FindItem ("Rockets");
			if (item)
			{
				index = ITEM_INDEX (item);
				ent->client->pers.inventory [index] += 5;

				if (ent->client->pers.inventory [index] > ent->client->pers.max_rockets)
					ent->client->pers.inventory [index] = ent->client->pers.max_rockets;
			}
		}
		else if (pawn_item_index == 6)
		{
			item = FindItem("Gas");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 100;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_cells)
					ent->client->pers.inventory[index] = ent->client->pers.max_cells;
				
			}
		}
		break;
	case PAWN_MODS: // special handling
		if (!pawn_item_index) // SPistol weapon
		{
			index = ITEM_INDEX (item = FindItem (pawn_item_names[current_pawn_item].name[pawn_item_index]));
			ent->client->pers.inventory [ index ] = 1;
			ent->client->newweapon = FindItem (pawn_item_names[current_pawn_item].name[pawn_item_index]);
			ent->client->pers.silencer_shots = 20;
			PawnDisplayOnHud (item, index);
		}
		else if (pawn_item_index >= 1 && pawn_item_index <= 3) // for pistol mods
		{

			index = ITEM_INDEX (item = FindItem ("Pistol_Mods"));

			if (pawn_item_index == 1)
			{
				ent->client->pers.pistol_mods |= WEAPON_MOD_ROF;
				item->icon = "/pics/h_pistol_rof.tga";
			}
			else if (pawn_item_index == 2)
			{
				ent->client->pers.pistol_mods |= WEAPON_MOD_DAMAGE;
				item->icon = "/pics/h_pistol_mag.tga";
			}
			else if (pawn_item_index == 3)
			{
				ent->client->pers.pistol_mods |= WEAPON_MOD_RELOAD;
				item->icon = "/pics/h_pistol_rl.tga";
			}

			ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
			ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
			ent->client->pickup_msg_time = level.time + 2.0;
		}
		// cooling jacket for heavy machinegun
// TBD: need the following items for this pickup and hud icons, need to make modifications to Pistol_Mods
		else if (pawn_item_index == 4)
		{
			index = ITEM_INDEX (item = FindItem ("Pistol_Mods"));

			ent->client->pers.pistol_mods |= WEAPON_MOD_COOLING_JACKET;
			item->icon = "/pics/h_heavymachinegun_cooling.tga";

			ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
			ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
			ent->client->pickup_msg_time = level.time + 2.0;

		}
		
		break;
	case PAWN_AMMO1: // ammo
		if (pawn_item_index == 0)
		{
			item = FindItem("Bullets");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 10;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_bullets)
					ent->client->pers.inventory[index] = ent->client->pers.max_bullets;

				PawnDisplayOnHud (item, index);
			}
		}
		else if (pawn_item_index == 1)
		{
			item = FindItem("Shells");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 5;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_shells)
					ent->client->pers.inventory[index] = ent->client->pers.max_shells;

				PawnDisplayOnHud (item, index);
			}
		}
		else if (pawn_item_index == 2)
		{
			item = FindItem("308cal");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 30;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_slugs)
					ent->client->pers.inventory[index] = ent->client->pers.max_slugs;

				PawnDisplayOnHud (item, index);
			}
		}
		else if (pawn_item_index == 3)
		{
			item = FindItem("Grenades");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 3;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_grenades)
					ent->client->pers.inventory[index] = ent->client->pers.max_grenades;

				PawnDisplayOnHud (item, index);
			}
		}
		break;
	case PAWN_AMMO2:	// ammo
		if (pawn_item_index == 0)
		{
			item = FindItem("Rockets");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 5;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_rockets)
					ent->client->pers.inventory[index] = ent->client->pers.max_rockets;

				PawnDisplayOnHud (item, index);
			}
		}
		else if (pawn_item_index == 1)
		{
			item = FindItem("Gas");
			if (item)
			{
				index = ITEM_INDEX(item);
				ent->client->pers.inventory[index] += 100;

				if (ent->client->pers.inventory[index] > ent->client->pers.max_cells)
					ent->client->pers.inventory[index] = ent->client->pers.max_cells;

				PawnDisplayOnHud (item, index);
			}
		}
		break;
	// JOSEPH 12-MAR-99-B
	case PAWN_HEALTH: // health
		if (pawn_item_index)
		{
			int     index;
			gitem_t *item;

			item = FindItem ("Large Health");
			index = ITEM_INDEX (item);
			ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
			ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
			ent->client->pickup_msg_time = level.time + 5.5;
			
			ent->health += 25;
		}
		else 
		{
			int     index;
			gitem_t *item;
	
			item = FindItem ("Small Health");
			index = ITEM_INDEX (item);
			ent->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(item->icon);
			ent->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+index;
			ent->client->pickup_msg_time = level.time + 5.5;
			
			ent->health += 10;
		}

		if (ent->health > ent->max_health)
			ent->health = ent->max_health;
	
		// PawnDisplayOnHud (item, index);

		break;
	case PAWN_ARMOR:
		{
			int		rval;
			int     index;
			gitem_t *item;

			rval = Check_Buy_Armor (ent, false);
		
			index = ITEM_INDEX (item = FindItem (pawn_item_names[current_pawn_item].name[pawn_item_index]));
		
			PawnDisplayOnHud (item, index);
		}

		break;
	}
	// END JOSEPH
}	

void PawnItemPrice (int item)
{
	current_pawn_item = item - 1;
	item_price = pawn_price[current_pawn_item].price[right_light_cnt - 1];			
}



qboolean ValidateItemFor_Skidrow_Shop (int item, int index)
{
	if (store_id == 1)
	{
		switch (item)
		{
		case PAWN_WEAPONS:
			if (index == 0)		// pistol
				return true;
			break;
		case PAWN_MODS:
			if (index == 1			// mod rate of fire
				|| index == 2)		// magnum mod
				return true;
			break;
		case PAWN_AMMO1:
			if (index == 0)		// bullets
				return true;
			break;
		case PAWN_AMMO2:
			if (index == 1)		// gas
				return true;
			break;
		case PAWN_HEALTH:
			if (index == 0		// small med kit
				|| index == 1)	// large med kit
				return true;
			break;
		case PAWN_ARMOR:
			if (index == 0)		// Helmet
				return true;
			break;
		case PAWN_UNUSED1:
			// not used yet implants etc
			break;
		case PAWN_UNUSED2:
			// to sell stuff
			break;
		}
	}
	else if (store_id == 2)
	{
		switch (item)
		{
		case PAWN_WEAPONS:
			if (index == 0		// pistol
				|| index == 1)	// shotgun
				return true;
			break;
		case PAWN_MODS:
			if (index == 0		// mod silencer
				|| index == 1	// mod rate of fire
				|| index == 2	// magnum mode
				|| index == 3)	// mod reload
				return true;
			break;
		case PAWN_AMMO1:
			if (index == 0		// bullets
				|| index == 1)	// shells
				return true;
			break;
		case PAWN_AMMO2:
			break;
		case PAWN_HEALTH:
			if (index == 0		// small med kit
				|| index == 1)	// large med kit
				return true;
			break;
		case PAWN_ARMOR:
			if (index == 0		// Helmet
				|| index == 2)	// Jacket
				return true;
			break;
		case PAWN_UNUSED1:
			// not used yet implants etc
			break;
		case PAWN_UNUSED2:
			// to sell stuff
			break;
		}

	}

	return false;
}


qboolean ValidateItemFor_PoisonVille_Shop (int item, int index)
{
	switch (item)
	{
	case PAWN_WEAPONS:
		if (index == 0		// pistol
			|| index == 1)	// shotgun
			return true;
		break;
	case PAWN_MODS:
		if (index == 0		// mod silencer
			|| index == 1	// mod rate of fire
			|| index == 2   // mod damage
			|| index == 3)	// mod reload
			return true;
		break;
	case PAWN_AMMO1:
		if (index == 0		// bullets
			|| index == 1)	// shells
			return true;
		break;
	case PAWN_AMMO2:
		if (index == 0)		// rockets
			return true;
		break;
	case PAWN_HEALTH:
		if (index == 0		// small med kit
			|| index == 1)	// large med kit
			return true;
		break;
	case PAWN_ARMOR:
		if (index == 0		// Helmet Armor
			|| index == 2	// Jacket Armor
			|| index == 4)	// Legs	Armor
			return true;
		break;
	case PAWN_UNUSED1:
		// not used yet implants etc
		break;
	case PAWN_UNUSED2:
		// to sell stuff
		break;
	}

	return false;
}


qboolean ValidateItemFor_Shipyard_Shop (int item, int index)
{
	switch (item)
	{
	case PAWN_WEAPONS:
		if (index == 0		// pistol
			|| index == 1	// shotgun
			|| index == 2	// tommygun
			|| index == 6)	// flamethrower
			return true;
		break;
	case PAWN_MODS:
		if (index == 0		// silencer
			|| index == 1	// ROF
			|| index == 2	// magnum
			|| index == 3	// reload
			|| index == 4)	// cooling jacket
			return true;
		break;
	case PAWN_AMMO1:
		if (index == 0		// bullets
			|| index == 1	// shells
			|| index == 2)	// 308
			return true;
		break;
	case PAWN_AMMO2:
		break;
	case PAWN_HEALTH:
		if (index == 0		// small health
			|| index == 1)	// large health
			return true;
		break;
	case PAWN_ARMOR:
		if (index == 0		// helmet
			|| index == 2	// jacket
			|| index == 4)	// pants
			return true;
		break;
	case PAWN_UNUSED1:
		// not used yet implants etc
		break;
	case PAWN_UNUSED2:
		// to sell stuff
		break;
	}

	return false;
}


qboolean ValidateItemFor_Steeltown_Shop (int item, int index)
{
	switch (item)
	{
	case PAWN_WEAPONS:
		if (index == 0		// pistol
			|| index == 1	// shotgun
			|| index == 2	// tommygun
			|| index == 4	// grenade launcher
			|| index == 6)	// flamethrower
			return true;
		break;
	case PAWN_MODS:
		if (index == 0		// silencer
			|| index == 1	// ROF
			|| index == 2	// magnum
			|| index == 3)	// reload
			return true;
		break;
	case PAWN_AMMO1:
		if (index == 0		// bullets
			|| index == 1	// shells
			|| index == 2)	// 308
			return true;
		break;
	case PAWN_AMMO2:
		if (index == 0)		// rockets
			return true;
		break;
	case PAWN_HEALTH:
		if (index == 0		// small health
			|| index == 1)	// large health
			return true;
		break;
	case PAWN_ARMOR:
		if (index == 0		// helmet
			|| index == 1	// heavy helmet
			|| index == 2	// jacket
			|| index == 4)	// pants
			return true;
		break;
	case PAWN_UNUSED1:
		// not used yet implants etc
		break;
	case PAWN_UNUSED2:
		// to sell stuff
		break;
	}

	return false;
}


qboolean ValidateItemFor_Radiocity_Shop (int item, int index)
{
	switch (item)
	{
	case PAWN_WEAPONS:
		if (index == 0		// pistol
			|| index == 1	// shotgun
			|| index == 2	// tommygun
			|| index == 3	// HMG
			|| index == 4	// grenade launcher
			|| index == 5	// rocket launcher
			|| index == 6)	// flamethrower
			return true;
		break;
	case PAWN_MODS:
		if (index == 0		// silencer
			|| index == 1	// ROF
			|| index == 2	// magnum
			|| index == 3	// reload
			|| index == 4)	// cooling jacket
			return true;
		break;
	case PAWN_AMMO1:
		if (index == 0		// bullets
			|| index == 1	// shells
			|| index == 2	// 308
			|| index == 3)	// grenades
			return true;
		break;
	case PAWN_AMMO2:
		if (index == 0		// rockets
			|| index == 1)	// gas
			return true;
		break;
	case PAWN_HEALTH:
		if (index == 0		// small health
			|| index == 1)	// large health
			return true;
		break;
	case PAWN_ARMOR:
		if (index == 0		// helmet
			|| index == 1	// heavy helmet
			|| index == 2	// jacket
			|| index == 3	// heavy jacket
			|| index == 4	// pants
			|| index == 5)	// heavy pants
			return true;
		break;
	case PAWN_UNUSED1:
		// not used yet implants etc
		break;
	case PAWN_UNUSED2:
		// to sell stuff
		break;
	}

	return false;
}




// all pawnomatics will have a selective inventory
qboolean PawnItemHack (int item, int index)
{
	switch (level.episode)
	{
	case EP_SKIDROW:
		return ValidateItemFor_Skidrow_Shop (item, index);
		break;
	case EP_POISONVILLE :
		return ValidateItemFor_PoisonVille_Shop (item, index);
		break;
	case EP_SHIPYARDS:
		return ValidateItemFor_Shipyard_Shop (item, index);
		break;
	case EP_STEELTOWN:
		return ValidateItemFor_Steeltown_Shop (item, index);
		break;
	case EP_RADIOCITY:
		return ValidateItemFor_Radiocity_Shop (item, index);
		break;
	}
	return false;
}

void PawnSay (voice_table_t *voice_table, int entry)
{
	edict_t *dude = NULL;
	edict_t *player;

	player = &g_edicts[1];

	dude = G_Find (NULL, FOFS (classname), "cast_runt");

	if (!dude)
		gi.dprintf ("this pawnomatic does not have a correct vendor\n");

	gi.sound( dude, CHAN_VOICE, gi.soundindex ( voice_table[ entry ].filename ), 1, ATTN_NORM, 0 );
	
	
	if (cl_captions->value)
		gi.dprintf ("Sharky : %s\n", voice_table[entry].text);

	player->client->ps.stats[STAT_HUD_ENEMY_TALK] = voice_table[ entry ].type;
	player->client->hud_enemy_talk_time = level.time + 2.0;

	voice_table[ entry ].last_played = level.time;


}

// TBD: Need to do voice tables and change return val to int to index what sound to play
qboolean PawnItemPriceSay (int item)
{
	edict_t *player;
	int		pawn_item_index;
	qboolean demo_hack;
	qboolean special_handle = false;

	pawn_item_index = right_light_cnt - 1;

	player = &g_edicts[1];

	demo_hack = PawnItemHack (current_pawn_item, pawn_item_index);
	if (!demo_hack)
	{
		PawnSay (pawnomatic_specific, (pawnomatic_specific[13].last_played < pawnomatic_specific[12].last_played) + 12); // out of stock
		return false;
	}

	// need to special handle mods
	
	if (current_pawn_item == PAWN_MODS)
	{
		if (pawn_item_index <= 3) // player wants a mod for pistol
		{
			if (!player->client->pers.inventory[ITEM_INDEX(FindItem("Pistol"))])  // no pistol	
			{
				PawnSay (pawnomatic_mods_specific, (pawnomatic_mods_specific[5].last_played < pawnomatic_mods_specific[4].last_played) + 4);  
				demo_hack = false;
			}
			else if (player->client->pers.inventory[ITEM_INDEX(FindItem("SPistol"))] && pawn_item_index == 0)
			{
				PawnSay (pawnomatic_specific, (pawnomatic_specific[15].last_played < pawnomatic_specific[14].last_played) + 14);  
				demo_hack = false;
			}
			else if (player->client->pers.inventory[ITEM_INDEX(FindItem("SPistol"))] && pawn_item_index == 0)
			{
				PawnSay (pawnomatic_specific, (pawnomatic_specific[15].last_played < pawnomatic_specific[14].last_played) + 14);  
				demo_hack = false;
			}
			else if (pawn_item_index == 1 && player->client->pers.pistol_mods & WEAPON_MOD_ROF)
			{
				PawnSay (pawnomatic_specific, (pawnomatic_specific[15].last_played < pawnomatic_specific[14].last_played) + 14);  
				demo_hack = false;
			}
			else if (pawn_item_index == 2 && player->client->pers.pistol_mods & WEAPON_MOD_DAMAGE)
			{
				PawnSay (pawnomatic_specific, (pawnomatic_specific[15].last_played < pawnomatic_specific[14].last_played) + 14);  
				demo_hack = false;
			}
			else if (pawn_item_index == 3 && player->client->pers.pistol_mods & WEAPON_MOD_RELOAD)
			{
				PawnSay (pawnomatic_specific, (pawnomatic_specific[15].last_played < pawnomatic_specific[14].last_played) + 14);  
				demo_hack = false;
			}
		}
		else if (pawn_item_index == 4) // player wants to buy the cooling jacket for hmg
		{
			if (!player->client->pers.inventory[ITEM_INDEX(FindItem("Heavy machinegun"))])	// no hmg
			{
				PawnSay (pawnomatic_mods_specific, (pawnomatic_mods_specific[5].last_played < pawnomatic_mods_specific[4].last_played) + 4);  
				demo_hack = false;
			}
			else if (player->client->pers.pistol_mods & WEAPON_MOD_COOLING_JACKET)
			{
				PawnSay (pawnomatic_specific, (pawnomatic_specific[15].last_played < pawnomatic_mods_specific[14].last_played) + 14);  
				demo_hack = false;
			}
		}
		special_handle = true;
	}
	
	
if (!demo_hack)
	return false;

	
	if (!special_handle) // not a mod
	{
		gitem_t	*foundit = FindItem (pawn_item_names[current_pawn_item].name[pawn_item_index]);	// for "player already has" below (SA)

		if (current_pawn_item == PAWN_AMMO1 || current_pawn_item == PAWN_AMMO2)
		{
			int		idx;
			gitem_t	*it;
			
			
			switch (pawn_item_index)
			{
			case 0:
				if (current_pawn_item == PAWN_AMMO1)
				{
					it = FindItem("Bullets");
					if (it)
					{
						idx = ITEM_INDEX(it);
						if (player->client->pers.inventory[idx] >= player->client->pers.max_bullets)
						{
							PawnSay (pawnomatic_specific, 16);
							return false;
						}
					}
					PawnSay (pawnomatic_ammo_specific, (pawnomatic_ammo_specific[3].last_played < pawnomatic_ammo_specific[2].last_played) + 2);
				}
				else
				{
					it = FindItem ("Rockets");
					if (it)
					{
						idx = ITEM_INDEX (it);
						if (player->client->pers.inventory [idx] >= player->client->pers.max_rockets)
						{
							PawnSay (pawnomatic_specific, 16);
							return false;
						}
					}
					PawnSay (pawnomatic_ammo_specific, (pawnomatic_ammo_specific[17].last_played < pawnomatic_ammo_specific[16].last_played) + 16);
				}
				break;
			case 1:
				if (current_pawn_item == PAWN_AMMO1)
				{
					it = FindItem("Shells");
					if (it)
					{
						idx = ITEM_INDEX(it);
						if (player->client->pers.inventory[idx] >= player->client->pers.max_shells)
						{
							PawnSay (pawnomatic_specific, 16);
							return false;
						}
					}
					PawnSay (pawnomatic_ammo_specific, (pawnomatic_ammo_specific[13].last_played < pawnomatic_ammo_specific[12].last_played) + 12);
				}
				else 
				{
					it = FindItem("Gas");
					if (it)
					{
						idx = ITEM_INDEX(it);
						if (player->client->pers.inventory[idx] >= player->client->pers.max_cells)
						{
							PawnSay (pawnomatic_specific, 16);
							return false;
						}
					}
					PawnSay (pawnomatic_ammo_specific, (pawnomatic_ammo_specific[19].last_played < pawnomatic_ammo_specific[18].last_played) + 18);
				}
				break;
			case 2:
					it = FindItem("308cal");
					if (it)
					{
						idx = ITEM_INDEX(it);
						if (player->client->pers.inventory[idx] >= player->client->pers.max_slugs)
						{
							PawnSay (pawnomatic_specific, 16);
							return false;
						}
					}
					PawnSay (pawnomatic_ammo_specific, (pawnomatic_ammo_specific[21].last_played < pawnomatic_ammo_specific[20].last_played) + 20);
				break;
			case 3:
					it = FindItem("Grenades");
					if (it)
					{
						idx = ITEM_INDEX(it);
						if (player->client->pers.inventory[idx] >= player->client->pers.max_grenades)
						{
							PawnSay (pawnomatic_specific, 16);
							return false;
					}
				}
					PawnSay (pawnomatic_ammo_specific, (pawnomatic_ammo_specific[7].last_played < pawnomatic_ammo_specific[6].last_played) + 6);
				break;
			}
		}
		else if (current_pawn_item == PAWN_HEALTH)
		{
			if (player->health == player->max_health)
			{
				PawnSay (pawnomatic_specific, 17);
				return false;
			}
			
			if (pawn_item_index) 	PawnSay ( pawnomatic_health_specific, 1);
			else					PawnSay ( pawnomatic_health_specific, 0);
		}
		else if (current_pawn_item == PAWN_ARMOR)
		{
			int rval = Check_Buy_Armor (player, true);

			if (rval != -1)
				PawnSay (pawnomatic_armor_specific, (pawnomatic_armor_specific[rval+1].last_played < pawnomatic_armor_specific[rval].last_played) + rval);
			else 
			{
				PawnSay (pawnomatic_specific, 14);  // I only play the first "don't have it" because the second implies you don't need two.  with armor, you might
				return false;
			}
		}
		else if (foundit && player->client->pers.inventory [ITEM_INDEX(foundit)] && current_pawn_item != 1) // player already has
		{
			PawnSay (pawnomatic_specific, (pawnomatic_specific[15].last_played < pawnomatic_specific[14].last_played) + 14);
			return false;
		}
		else
		{
			if (current_pawn_item == PAWN_WEAPONS)
			{
				PawnSay (pawnomatic_weapons_random, rand()%9);
			}
		}
	}

	else 
	{
		if (current_pawn_item == PAWN_MODS)
		{
			int rval = 0;

			switch (pawn_item_index)
			{
			case 0:			// Silencer
				if (player->client->pers.inventory [ITEM_INDEX (FindItem ("Pistol"))])
					rval = 12;
				else
				{
					PawnSay (pawnomatic_mods_specific, 3);
					return false;
				}
				break;
			case 1:			// ROF
				rval = 8;
				break;
			case 2:			// Magnum
				rval = 2;
				break;
			case 3:			// Reload
				rval = 6;
				break;

			case 4:			// HMG cooling mod
				rval = 16;
				break;
			}
			PawnSay (pawnomatic_mods_specific, (pawnomatic_mods_specific[rval+1].last_played < pawnomatic_mods_specific[rval].last_played) + rval);
		}
		else 
			gi.dprintf ("missed %d\n", current_pawn_item);
	}

			
	
	return true;
}

void PawnNext (edict_t *ent)
{
	int old_right_light_cnt;
	
	if (!PawnGetTime())
		return;

	PawnSetTimeDelay (0.2);

	gi.sound(ent, CHAN_VOICE, gi.soundindex("world/pawnomatic/menu.wav"), 1, ATTN_NORM, 0);

	old_right_light_cnt = right_light_cnt;

	if (left_side)
	{
		left_light_cnt++;
		if (left_light_cnt > pawn_menu[LEFT_LIGHT].num_frames)
			left_light_cnt = 1;
	}
	else
	{
		right_light_cnt++;
		if (right_light_cnt > pawn_menu[RIGHT_LIGHT].num_frames)
			right_light_cnt = 1;
	}

	if (old_right_light_cnt != right_light_cnt)
	{
		animate_hundreds = animate_tens = animate_ones = animate_numbers = true;
		PawnItemPrice (left_light_cnt);
	}

	if (transaction)
	{
		transaction = false;
		PawnSay (pawnomatic_sold, (rand()%3) + 3);
	}
}

void PawnPrev (edict_t *ent)
{
	int old_right_light_cnt;
	
	if (!PawnGetTime())
		return;

	PawnSetTimeDelay (0.2);

	gi.sound(ent, CHAN_VOICE, gi.soundindex("world/pawnomatic/menu.wav"), 1, ATTN_NORM, 0);

	old_right_light_cnt = right_light_cnt;

	if (left_side)
	{
		left_light_cnt--;
		if (left_light_cnt < 1)
			left_light_cnt = pawn_menu[LEFT_LIGHT].num_frames;
	}
	else
	{
		right_light_cnt--;
		if (right_light_cnt < 1)
			right_light_cnt = pawn_menu[RIGHT_LIGHT].num_frames;
	}

	if (old_right_light_cnt != right_light_cnt)
	{
		animate_hundreds = animate_tens = animate_ones = animate_numbers = true;
		PawnItemPrice (left_light_cnt);
	}

	if (transaction)
	{
		transaction = false;
		PawnSay (pawnomatic_sold, (rand()%3) + 3);
	}
}


void ThinkerPawnLevelPrevious (edict_t *ent)
{
	edict_t *owner;

	if (left_light_cnt == pawn_menu[LEFT_LIGHT].num_frames)
	{
		owner = ent->owner;
		G_FreeEdict( ent );

		PawnLevelPrevious (owner);
		return;
	}

	G_FreeEdict( ent );
}

void PawnBuy (edict_t *ent)
{
	
	if (!PawnGetTime())
		return;

	if (!exit_the_level)
		PawnSetTimeDelay (0.2);
	
	gi.sound(ent, CHAN_VOICE, gi.soundindex("world/pawnomatic/menu.wav"), 1, ATTN_NORM, 0);


	if (left_light_cnt == pawn_menu[LEFT_LIGHT].num_frames)
	{
		if (exit_the_level)
		{
			PawnLevelPrevious (ent);
		}	
		else
		{
			edict_t *thinker;

			PawnSetTimeDelay (2.0);
			PawnSay (pawnomatic_specific, 6);
			exit_the_level = true;

			thinker = G_Spawn();
			thinker->owner = ent;
			thinker->nextthink = level.time + 3.5;
			thinker->think = ThinkerPawnLevelPrevious;
		}
		return;
	}

	if (right_side && !transaction)
	{
		PawnItemPrice (left_light_cnt);
		transaction = PawnItemPriceSay (left_light_cnt);
		if (transaction)
			gi.dprintf ("so do we have a deal?\n");
	}
	// note to self
	// added this for blank item
	else if (left_side && left_light_cnt == pawn_menu[LEFT_LIGHT].num_frames - 1)
	{
		return;
	}
	else if (left_side && !exit_the_level)
	{
		right_side = true;
		left_side = false;
		right_light_cnt = 1;
		animate_right = true;
		animate_hundreds = animate_tens = animate_ones = animate_numbers = true;
		PawnItemPrice (left_light_cnt);
	}
	else if (transaction) // the player can purchase here as well
	{
		PawnAgree (ent);
	}

	
}

void PawnLeft (edict_t *ent)
{
	if (!PawnGetTime())
		return;

	PawnSetTimeDelay (0.2);

	gi.sound(ent, CHAN_VOICE, gi.soundindex("world/pawnomatic/menu.wav"), 1, ATTN_NORM, 0);
	
	right_side = false;
	left_side = true;

	if (transaction)
	{
		transaction = false;
		PawnSay (pawnomatic_sold, (rand()%3) + 3);
	}
}

void PawnRight (edict_t *ent)
{
	if (!PawnGetTime())
		return;

	PawnSetTimeDelay (0.2);

	// note to self
	// added this for blank space
	if (left_side && left_light_cnt >= pawn_menu[LEFT_LIGHT].num_frames - 1)
	{
		return;
	}
	
	gi.sound(ent, CHAN_VOICE, gi.soundindex("world/pawnomatic/menu.wav"), 1, ATTN_NORM, 0);

	right_side = true;
	left_side = false;

	right_light_cnt = 1;

	animate_right = true;
	animate_hundreds = animate_tens = animate_ones = animate_numbers = true;
	PawnItemPrice (left_light_cnt);

	if (transaction)
	{
		transaction = false;
		PawnSay (pawnomatic_sold, (rand()%3) + 3);
	}
}

void PawnAgree (edict_t *ent)
{
	if (!PawnGetTime() && !transaction)
		return;

	PawnSetTimeDelay (0.2);
	
	if (transaction)
		transaction = false;
	else
	{
		gi.dprintf ("yo select something first\n");
		return;
	}

	if (ent->client->pers.currentcash >= item_price)
	{
//		gi.dprintf ("agree!\n");	
		
		PawnSay (pawnomatic_sold, rand()%3 );

		ent->client->pers.currentcash -= item_price;
		
		PawnGiveItem (ent);
		
	}
	else
	{
//		gi.dprintf ("you don't have enough cash\n");
		PawnSay ( pawnomatic_specific, 11);
	}
}

void PawnDisagree (edict_t *ent)
{
	
	if (!PawnGetTime())
		return;

	PawnSetTimeDelay (0.2);

	transaction = false;
	// gi.dprintf ("disagree!\n");
	PawnSay (pawnomatic_sold, (rand()%3) + 3);
}


void PawnSetTimeDelay (float delay)
{	
	generic_time = level.time + delay;
	exit_the_level = false;
}

qboolean PawnGetTime (void)
{
	if (generic_time < level.time)
		return true;

	return false;
}

void PawnLevelPrevious (edict_t *ent)
{
	edict_t *lvl;
	edict_t *player;

	player = &g_edicts[1];

	lvl = G_Find (ent, FOFS (classname), "trigger_multiple");

	if (lvl)
		lvl->touch( lvl, player, NULL, NULL );
	else
		gi.dprintf ("error\n");

	level.pawn_time = 0;

	
}


int Check_Buy_Armor (edict_t *player, qboolean check)
{
	int		pawn_item_index;

	pawn_item_index = right_light_cnt - 1;

	if (pawn_item_index == 0)
	{
		gitem_t *itemh = FindItem("Helmet Armor");
		gitem_t *itemhh = FindItem("Helmet Armor Heavy");

		if ((player->client->pers.inventory[ITEM_INDEX(itemh)] == 100) ||
		   (player->client->pers.inventory[ITEM_INDEX(itemhh)] == 100))
			return (-1);
		else if (check)
			return (0);
		
		if (player->client->pers.inventory[ITEM_INDEX(itemhh)])
		{
			player->client->pers.inventory[ITEM_INDEX(itemhh)] += 25;
			if (player->client->pers.inventory[ITEM_INDEX(itemhh)] > 100)
				player->client->pers.inventory[ITEM_INDEX(itemhh)] = 100;
		}
		else
		{
			player->client->pers.inventory[ITEM_INDEX(itemh)] += 50;
			if (player->client->pers.inventory[ITEM_INDEX(itemh)] > 100)
				player->client->pers.inventory[ITEM_INDEX(itemh)] = 100;
		}
	}
	else if (pawn_item_index == 2)
	{

		gitem_t *itemj = FindItem("Jacket Armor");
		gitem_t *itemjh = FindItem("Jacket Armor Heavy");
		
		if ((player->client->pers.inventory[ITEM_INDEX(itemj)] == 100) ||
		   (player->client->pers.inventory[ITEM_INDEX(itemjh)] == 100))
			return (-1);
		else if (check)
			return (4);

		if (player->client->pers.inventory[ITEM_INDEX(itemjh)])
		{
			player->client->pers.inventory[ITEM_INDEX(itemjh)] += 25;
			if (player->client->pers.inventory[ITEM_INDEX(itemjh)] > 100)
				player->client->pers.inventory[ITEM_INDEX(itemjh)] = 100;
		}
		else
		{
			player->client->pers.inventory[ITEM_INDEX(itemj)] += 50;
			if (player->client->pers.inventory[ITEM_INDEX(itemj)] > 100)
				player->client->pers.inventory[ITEM_INDEX(itemj)] = 100;
		}
	}
	else if (pawn_item_index == 4)
	{
		gitem_t *iteml = FindItem("Legs Armor");
		gitem_t *itemlh = FindItem("Legs Armor Heavy");	
		
		if ((player->client->pers.inventory[ITEM_INDEX(iteml)] == 100) ||
		   (player->client->pers.inventory[ITEM_INDEX(itemlh)] == 100))
			return (-1);
		else if (check)
			return (8);

		if (player->client->pers.inventory[ITEM_INDEX(itemlh)])
		{
			player->client->pers.inventory[ITEM_INDEX(itemlh)] += 25;
			if (player->client->pers.inventory[ITEM_INDEX(itemlh)] > 100)
				player->client->pers.inventory[ITEM_INDEX(itemlh)] = 100;
		}
		else
		{
			player->client->pers.inventory[ITEM_INDEX(iteml)] += 50;
			if (player->client->pers.inventory[ITEM_INDEX(iteml)] > 100)
				player->client->pers.inventory[ITEM_INDEX(iteml)] = 100;
		}
	}
	else if (pawn_item_index == 1)
	{
		gitem_t *itemh = FindItem("Helmet Armor");
		gitem_t *itemhh = FindItem("Helmet Armor Heavy");
		
		if (player->client->pers.inventory[ITEM_INDEX(itemhh)] == 100)
			return (-1);
		else if (check)
			return (2);
		
		if (player->client->pers.inventory[ITEM_INDEX(itemh)])
			player->client->pers.inventory[ITEM_INDEX(itemh)] = 0;			

		player->client->pers.inventory[ITEM_INDEX(itemhh)] = 100;
	}
	else if (pawn_item_index == 3)
	{
		gitem_t *itemj = FindItem("Jacket Armor");
		gitem_t *itemjh = FindItem("Jacket Armor Heavy");
		
		if (player->client->pers.inventory[ITEM_INDEX(itemjh)] == 100)
			return (-1);		
		else if (check)
			return (6);

		if (player->client->pers.inventory[ITEM_INDEX(itemj)])
			player->client->pers.inventory[ITEM_INDEX(itemj)] = 0;			

		player->client->pers.inventory[ITEM_INDEX(itemjh)] = 100;
	}
	else if (pawn_item_index == 5)
	{
		gitem_t *iteml = FindItem("Legs Armor");
		gitem_t *itemlh = FindItem("Legs Armor Heavy");	
		
		if (player->client->pers.inventory[ITEM_INDEX(itemlh)] == 100)
			return (-1);
		else if (check)
			return (10);

		if (player->client->pers.inventory[ITEM_INDEX(iteml)])
			player->client->pers.inventory[ITEM_INDEX(iteml)] = 0;			

		player->client->pers.inventory[ITEM_INDEX(itemlh)] = 100;
	}

	return (-1);
}

