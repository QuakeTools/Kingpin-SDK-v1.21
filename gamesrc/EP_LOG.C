// ep_log.c
#include "g_local.h"

player_log_t ep_skidrow_player_log[] = 
{
	// 0
	// {"Nicki's boys roughed me\nup good left me in this\nshitty little alley in\nSkidrow. Gotta find a way\nback to Poisonville to pay\nthat little bastard back\nneed some wheels...\n",0},
	{"Nicki's boys roughed me\nup good left me in this\ndirty little alley in\nSkidrow. Gotta find a way\nback to Poisonville\n",0,0,true},
	// 1
	{"Fat guy will sell me a\ncrowbar for a buck...\n", EP_SKIDROW_MAGICJ_ASKED_DOLLAR,1,false},
	// 2
	{"Pawn dude will trade me a\npistol for a Heilman Coil\nCondenser says its in\nstoreroom B at warehouse\naround the corner...\n", EP_PAWNOMATIC_FIRST_TIME,2,false},
	// 3
	{"Looks like I stumbled into\nthe Sewer Rat gang's turf.\nGotta find a way into\ntheir HQ...\n",EP_SKIDROW_RATS_PISSED,3,false},
	// 4
	{"Overheard conversation\nbetween some Sewer Rats\nlooks like the Scorp gang\nswiped their moto battery.\nGuess I'll have to venture\ninto their turf to find it\nif I'm ever getting the\nhell out of here...\n", EP_SKIDROW_RATS_FIND,4,false},
	// 5
	// {"Chick by bar says I need\nto steer clear of\ncrazy mofo named Lamont\nguy named Lenny evicted\nhim. Says I should go into\nbar and talk to Lenny...\n", EP_SKIDROW_MONA_FIRST_TIME},
	{"Chick by bar says I need\nto steer clear of\ncrazy dude named Lamont\nSays I should go into\nbar and talk to Lenny...\n", EP_SKIDROW_MONA_FIRST_TIME,5,false},
	// 6
	{"Bum told me about a bike.\nmight be a way out...\n", EP_SKIDROW_NICK_TOLD_BIKE,6,false},
	// 7
	{"Lenny says he evicted\nLamont for not paying his\nrent.  Looks like this guy\nmight be able to help me\nout if I can get his Zolex\nwatch back from Lamont...\n", EP_TALKED_TO_LENNY,7,false},
	// 8
	{"Found the bike... Broken\ndown piece of junk doesn't\nhave a battery...\n", EP_SKIDROW_FOUND_BIKE,8,false},
	// 9
	{"Gotta find a way into\nSewer Rat HQ...\n", EP_SKIDROW_CUT_SCENE_TWO,9,false},
	// 10
	//{"Found Lenny in bar bathroom\nsays he'll help me get into\nSewer Rat hq if I'll take\ndust Lamont for him...\n", 0},
	{"Bum said he would tell\nme something good if I\nget him some booze", EP_SKIDROW_TALKED_TO_RUMMY,10,false},

	// Key to Storeroom
	{"Lenny gave me the key to\nthe storeroom.  From there\nI can reach the Sewer Rat\nHeadquarters...\n",EP_SKIDROW_LENNY_TOOK_WATCH,11,false},

	//Combo to Safe
	{"Bum gave me the combo to\nthe safe...\n", EP_SKIDROW_RUMMY_GAVE_WINE,12,false}
	
};

player_log_t ep_pv_player_log[] = 
{
	//Poisonville Intro
	{"Back in Poisonville.  As\nusual the stench of toxic\nwaste fills the air. Nicki\nwarned me never to show my\nface here again.  For the\nrest of his short life\nhe's gonna regret the day\nhe left me still breathing\n",0,0,true},
	//Talked to Hireling 
	{"The local muscle here all\nseem to be working for a\nguy named Louie.  I guess\nI better look him up.\n", EP_PV_FIND_LOUIE,1,false},
	//Talked to Louie
	{"Nicki's boys stole some of\nLouie's important things\nand stashed them in a safe\nin Nicki's warehouse.  If\nI can get them back, Louie\nwill let me hire some of\nhis local muscle.\n",EP_PV_TALKED_LOUIE2,2,false},
	//Hire Safe Dude
	{"I can hire either the\nsafecracker or the demo\nguy to open Nicki's safe.\n",EP_PV_LOUIE_SPEACH_1,3,false},
	//Give Key
	{"Louie gave me the key to\nNicki's chemical plant\n",EP_PV_LOUIE_KEY,4,false},
	//Yolanda Distraction
	{"For ten bucks Yolanda will\ndistract the two guards.\nShe works cheap...\n",EP_PV_YOLANDA_ASKED_MONEY,5,false},

	//Louie has key - Start of PV_B
	{"The two goons were yelling\nabout forgetting to swipe\na key.  I wonder if Louie\nstill has it on him?\n",EP_PV_LOUIEPVB,6,false},

	// Blown Fuse Pump
	{"I need some fuses to get\nthis pump started...\n",EP_PV_ONEFUSE,7,false},


// Nicky escapes - Voiceover
//{"Nicky got away... Time\nenough for him later.\n",},

};



player_log_t ep_sy_player_log[] =
{
	// Intro to Shipyard
	{"The Shipyards. The final\nresting place for rusty\nold hulks and a home to\nthe diseased rats and scum\neating wharf shrimp...\n",0,0,true},
	// Moe after first negative response
	{"This Moe guy really backed\ndown when I threw a scare\ninto him. I should keep it\nup...\n",EP_SY_MOE_LASTLINE,1,false},
	// Talked to Popeye
	{"The old man said to get\nhelp at a bar called the\nSalty Dog\n",EP_SY_GOTO_SALTYDOG,2,false},
	// Key to shipyard
	{"Heilman and his crew are\nat the shipyard. Before I\ncan take them on I need\nthe key to the gate.\n",EP_SY_POPEYE_LASTLINE,3,false},	

	{"The ship's door was rusted\nshut...\n", EP_SY_GOTO_DOORSHUT,4,false},

//Heilman kidnapped Lizzy
{"Heilman's crew just beat\nup Big Willy, kidnapped\nhis girl, and totally\ntrashed the place...\n", EP_SY_GOFIND_BITCH_SAL,5,false},

//Key to warehouse
{"Sal just gave me the key\nto the warehouse...\n",EP_SY_HIRED_SAL,6,false},

// Found Lizzy - Voiceover if no Sal
{"I gotta tell Big Willy we\nwere too late to save\nLizzy.  I should probably\nbring him back some proof.\nHmm, I wonder...\n",EP_SY_FOUND_BITCH,7,false},

//Big Willy gives key
{"Big Willy gave me the key\nto the shipyard gate. He's\nlooking to get payback for\nLizzy...\n",EP_SY_BW_HIRED,8,false},
// Found Barney - Voiceover
// {"I just found Barney.  I\nwonder if anyone picked\nhis pockets...\n",}

};


// Trainyard help
player_log_t ep_ty_player_log[] =
{
//Intro
{"The Trainyards.  An artery\nthrough which homeless\ndrifters, fugitive outlaws\nand illegal goods flow in\nand out of Radio City.  It\n is now blocked...\n",0,0,true},

// Get to Radio City via sewers
{"I'm gonna have to take the\nstinking sewers to get to\nRadio City... Yuchh!\n",EP_TY_TAKETHESEWER,1,false},

//Missing valve handle
{"Gotta find a valve handle\nfor the access panel...\n",EP_TY_HANN_CLUE2,2,false},

//Blown fuse
{"The fuse for the ladder is\nblown.  They gotta keep a\nspare one somewhere around\nhere...\n",EP_TY_FUSEBLOWN	,3,false}, 


};



player_log_t ep_st_player_log[] = 
{
// Intro
{"Steeltown.  The furnaces\nof Moker's steel mill burn\naround the clock.  Fueled\nwith the sweat of forced\nchild labor...\n",0,0,true},

//Moker not in office  *** First person voice over clue***
{"Moker's not in his office.\n",EP_Steeltown_MOKER_NOTINOFFICE,1,false},

// HMG clue
{"I gotta get my hands on\none of those new guns...\n",EP_Steeltown_KIDS_CLUE1,2,false},

// David a prisoner
{"Bambi's kid brother David\nis a prisoner in the steel\nmill...\n",EP_Steeltown_BAMBI_LINE1,3,false},

// Bambi the barmaid at the Boiler Room
{"A babe named Bambi waits\ntables down at the Boiler\nRoom. I hear she's in some\nkind of trouble...\n",EP_Steeltown_MATHEW_LINE1,4,false},

//Armor in the basement
{"Moker's got armor in the\nthe Pawnomatic basement.\n",EP_Steeltown_BRITTANY_LINE1,5,false},

//David good with lockpick
{"David's supposed to be\ngood with a lockpick...\n",EP_Steeltown_KIDS_CLUE2,6,false},

//HMG locked up
{"The new guns are locked\nup. But that doesn't seem\nto bother David much...\n",EP_Steeltown_DAVID_SAY3,7,false},

//David Dead - Bambi talk
{"David's Dead.  I better\ntell Bambi...\n", EP_Steeltown_DAVID_DEAD_A,8,false},

//David Dead - No Bambi talk
{"Some guy named David just\ngot clipped.  I guess I\nbetter tell someone...\n", EP_Steeltown_DAVID_DEAD_B,9,false},

//Bambi gives key
{"Bambi gave me the key to\nMoker's office building.\n", EP_Steeltown_DAVID_DEAD,10,false},
//Bambi gives key
{"Bambi gave me the key to\nMoker's office building.\n", EP_Steeltown_BAMBI_DONE,11,false}

};


player_log_t ep_rc_player_log[] = 
{
//Intro
{"Radio City at last.  The\nKingpin's stronghold.  The\ncapital city of a criminal\nempire.  Mine for taking\nif I've got the guts. Once\nI go forward, there's no\nturning back...\n",0,0,true},

//Butch and Patrick - clear out Tunnel freaks
{"To join their gang I gotta\nwaste three Tunnel Freaks\nwith nothing but a crowbar\nThese Jokers are hardcore.\n",EP_RC_BUTCH_FIRST,1,false},

//Scalper - Take Skytram to Central Tower
{"Just found out that I can\nonly get to Central Tower\nby Skytram...\n",EP_RC_SCALPER_NOTEPAD,2,false},

//Lola - Weapons stashed
{"There are supposed to be\nsome weapons hidden around\nhere somewhere.  I'll keep\nmy eyes open...\n",EP_RC_LOLA_NOTEBOOK,3,false},

// Talk to Butch and Patrick
{"I gotta go see Butch and\nPatrick if I want to join\nthe Jokers...\n", EP_RC_JOKERS_NOTEPAD,4,false},


//Hey I heard that
{"Ooops, had to use a gun. I\nwonder if they'll still\nlet me join?\n", EP_RC_FAILED_TEST,5,false}

};
