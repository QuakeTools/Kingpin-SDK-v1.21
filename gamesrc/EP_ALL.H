/******************************************************************************

	GENERIC EPISODE DEFINES

******************************************************************************/

//.............................................................................
// Episode indexes
#define	EP_SKIDROW		1
#define EP_POISONVILLE  2
#define EP_SHIPYARDS	3
#define EP_STEELTOWN	4
#define EP_TRAINYARD	5
#define EP_RADIOCITY	6

//.............................................................................
// Special flags that AI will look at

// Skidrow flags
#define	EP_SKIDROW_MAGICJ_ASKED_DOLLAR	0x00000001 // 1
#define EP_SKIDROW_BETH_GIVES_HINT		0x00000002 // 2 
#define	EP_SKIDROW_AL_SAW_DEAD_LOUIE	0x00000004 // 3
#define	EP_PAWNOMATIC_FIRST_TIME		0x00000008 // 4
#define	EP_SKIDROW_GOT_COIL				0x00000010 // 5

#define	EP_SKIDROW_MAGICJ_GAVE_DOLLAR	0x00000020 // 6
#define	EP_SKIDROW_MOMO_ASKED_MONEY		0x00000040 // 7 
#define	EP_SKIDROW_MOMO_TOOK_MONEY		0x00000080 // 8
#define	EP_SKIDROW_MOMO_FIRST_TIME		0x00000100 // 9

#define EP_TALKED_TO_LENNY				0x00000200 // 10

#define	EP_SKIDROW_MOMO_GAVE_MONEY		0x00000800 // 11
#define	EP_BAR_FIRST_TIME				0x00001000 // 12
#define EP_SKIDROW_LENNY_TOOK_WATCH		0x00002000 // 13 

#define	EP_SKIDROW_NICK_WARNING_1		0x00004000 // 14
#define EP_SKIDROW_NICK_WARNING_2		0x00080000 // 15
#define EP_SKIDROW_NICK_WARNING_3		0x00100000 // 16

#define EP_SKIDROW_RUMMY_GAVE_WINE		0x00200000 // 17
#define EP_SKIDROW_RUMMY_ASKED_WINE		0x00400000 // 18 

#define	EP_SKIDROW_RATS_PISSED			0x00800000 // 19
#define	EP_SKIDROW_CUT_SCENE_TWO		0x01000000 // 20
#define EP_SKIDROW_MONA_FIRST_TIME		0x02000000 // 21 
#define EP_SKIDROW_NICK_TOLD_BIKE		0x04000000 // 22
#define EP_SKIDROW_FOUND_BIKE			0x08000000 // 23
#define	EP_SKIDROW_RATS_FIND			0x10000000 // 24
#define EP_SKIDROW_TALKED_TO_RUMMY		0x20000000 // 25

// Poisonville flags
#define	EP_PV_TALKED_LOUIE				0x00000001 // 1
#define EP_PV_OPEN_DOOR_LOUIE			0x00000002 // 2
#define EP_PV_SAFE_DOCS					0x00000004 // 3
#define EP_PV_SAFE_DOCS_DELIVERED		0x00000008 // 4

#define EP_PV_HIRED_SAFE_BOY			0x00000010 // 5
#define EP_PV_YOLANDA_DISTRACT			0x00000020 // 6
#define	EP_PV_MOMO_ASKED_MONEY			0x00000040 // 7
#define EP_PV_MOMO_TOOK_MONEY			0x00000080 // 8

#define	EP_PV_MOMO_FIRST_TIME			0x00000100 // 9
#define	EP_PV_MOMO_GAVE_MONEY			0x00000200 // 10
#define EP_PV_YOLANDA_TOOK_MONEY		0x00000400 // 11
#define	EP_PV_YOLANDA_ASKED_MONEY		0x00000800 // 12

#define EP_PV_PAWNOMATIC_FIRST_TIME		0x00001000 // 13
#define EP_PV_BAR_FIRST_TIME			0x00002000 // 14
#define EP_PV_OFFICE_FIRST_TIME			0x00004000 // 15
#define EP_PV_SENT_TO_GET_SAFEDOCS      0x00008000 // 16

#define	EP_PV_LOUIE_SPEACH_1			0x00010000 // 17
#define EP_PV_LOUIE_SPEACH_2			0x00020000 // 18 
#define EP_PV_TALKED_LOUIE_2			0x00040000 // 19

#define	EP_PV_TALKED_LOUIE2				0x00080000 // 20
#define	EP_PV_TALKED_LOUIE3				0x00100000 // 21 
#define	EP_PV_TALKED_LOUIE4				0x00200000 // 22
#define	EP_PV_TALKED_LOUIE5				0x00400000 // 23
#define EP_PV_LOUIE_KEY					0x00800000 // 24
#define EP_PV_FIND_LOUIE				0x01000000 // 25

#define EP_PV_BUSTERISDEAD				0x02000000
#define EP_PV_FINGERSISDEAD				0x04000000
#define EP_PV_SAFEDOORISOPEN			0x08000000

#define EP_PV_LOUIEPVB					0x10000000
#define EP_PV_FUSEISBLOWN1				0x20000000
#define EP_PV_ONEFUSE					0x40000000
#define EP_PV_FUSEISBLOWN2				0x80000000

// Crystal Palace flags
#define	EP_CP_KINGPIN_FIRSTSIGHT		0x00000001	// 01

// Train Yard flags
#define	EP_TY_LUKE_CLUE1				0x00000001
#define	EP_TY_LUKE_CLUE2				0x00000002

#define EP_TY_HANN_CLUE1				0x00000004
#define EP_TY_HANN_CLUE2				0x00000008
#define EP_TY_PAWNOMATIC_FIRST_TIME		0x00000010
#define EP_TY_TAKETHESEWER				0x00000020

#define EP_TY_FUSEBLOWN					0x00000040


// Shipyard flags
#define EP_SY_GOTO_SALTYDOG				0x00000001
#define EP_SY_SCREAMING_BITCH			0x00000002
#define EP_SY_FOUND_BITCH				0x00000004
#define EP_SY_BEEN_BAITSHOP				0x00000008

#define EP_SY_GETME_LURE				0x00000010
#define EP_SY_GOT_LURE					0x00000020
#define EP_SY_GOT_TOBEDETERMINED		0x00000040
#define EP_SY_GOFIND_BITCH				0x00000080

#define	EP_SY_MOMO_ASKED_MONEY			0x00000100
#define EP_SY_MOMO_TOOK_MONEY			0x00000200
#define EP_SY_MOMO_FIRST_TIME			0x00000400
#define EP_SY_GOFIND_BITCH_SAL			0x00000800

#define EP_SY_TACKLE					0x00001000
#define EP_SY_HIRED_SAL					0x00002000
#define EP_SY_SAL_SECONDLINE			0x00004000

#define EP_SY_MOE_FIRST_SIGHT			0x00008000
#define EP_SY_MOE_ESCALATE1				0x00010000
#define	EP_SY_MOE_ESCALATE2				0x00020000
#define EP_SY_MOE_ESCALATE3				0x00040000

#define EP_SY_MOE_FEAR1					0x00080000
#define EP_SY_MOE_FEAR2					0x00100000
#define EP_SY_MOE_FEAR3					0x00200000
#define EP_SY_BW_HIRED					0x00400000

#define EP_SY_BIGWILLIE_DEAD			0x00800000
#define EP_SY_SAL_DEAD					0x01000000
#define EP_SY_BIGWILLIE_REVENGE			0x02000000
#define EP_SY_LEFTY_HIRED				0x04000000
#define EP_SY_MOE_RUNAWAY				0x08000000
#define EP_SY_PAWNOMATIC_FIRST_TIME		0x10000000
#define EP_SY_POPEYE_LASTLINE			0x20000000
#define EP_SY_MOE_LASTLINE				0x40000000
#define EP_SY_GOTO_DOORSHUT				0x80000000

// Steeltown flags
#define EP_Steeltown_MOMO_TOOK_MONEY	0x00000001
#define	EP_Steeltown_MOMO_FIRST_TIME	0x00000002
#define	EP_Steeltown_MOMO_ASKED_MONEY	0x00000004

#define EP_Steeltown_KIDS_CLUE			0x00000008

#define	EP_Steeltown_MATHEW_CLUE1		0x00000010
#define	EP_Steeltown_MATHEW_CLUE2		0x00000020
#define EP_Steeltown_KROKER_SAY			0x00000040
#define EP_Steeltown_PAWNOMATIC_FIRST_TIME		0x00000080

#define EP_Steeltown_DAVID_DEAD			0x00000100
#define EP_Steeltown_DAVID_SAY1			0x00000200
#define EP_Steeltown_DAVID_SAY2			0x00000400
#define EP_Steeltown_DAVID_SAY3			0x00000800

#define EP_Steeltown_BAMBI_DONE			0x00001000
#define EP_Steeltown_BAMBI_LINE1		0x00002000
#define EP_Steeltown_MOKER_NOTINOFFICE	0x00004000

#define EP_Steeltown_MATHEW_LINE1		0x00008000
#define EP_Steeltown_BRITTANY_LINE1		0x00010000
#define	EP_Steeltown_BRITTANY_CLUE1		0x00020000

#define EP_Steeltown_KIDS_CLUE1			0x00040000
#define EP_Steeltown_KIDS_CLUE2			0x00080000
#define EP_Steeltown_KROKER_BOLT		0x00100000	

#define EP_Steeltown_DAVID_DEAD_A		0x00200000
#define EP_Steeltown_DAVID_DEAD_B		0x00400000

#define EP_Steeltown_DAVID_HIRED		0x00800000

// Radio City flags
#define EP_RC_MOMO_TOOK_MONEY			0x00000001
#define	EP_RC_MOMO_FIRST_TIME			0x00000002
#define	EP_RC_MOMO_ASKED_MONEY			0x00000004
#define EP_RC_OUTOFBRUSH				0x00000008
#define EP_RC_INTOBRUSH					0x00000010
#define	EP_RC_FAILED_TEST				0x00000020
#define EP_RC_PAWNOMATIC_FIRST_TIME		0x00000040

#define EP_RC_BUTCH_FIRST				0x00000080 
#define EP_RC_BUTCH_TALK1				0x00000100
#define EP_RC_BUTCH_TALK2				0x00000200

#define EP_RC_GROUCHO_DEAD				0x00000400
#define EP_RC_HARPO_DEAD				0x00000800
#define EP_RC_CHICO_DEAD				0x00001000

#define EP_RC_JOKERS_HIRED				0x00002000
#define EP_RC_PAY_500					0x00004000
#define EP_RC_BUTCH_500					0x00008000

#define EP_RC_SCALPER_ASKED_MONEY		0x00010000
#define EP_RC_TALKED_TO_SCALPER			0x00020000
#define EP_RC_SCALPER_GAVE_MONEY		0x00040000
#define EP_RC_SCALPER_LINE1				0x00080000

#define	EP_RC_LOLA_CLUE1				0x00100000
#define EP_RC_SCALPER_NOTEPAD			0x00200000
#define EP_RC_LOLA_NOTEBOOK				0x00400000
#define EP_RC_JOKERS_NOTEPAD			0x00800000	

#define EP_RC_SCALPER_RANDOM			0x01000000
#define EP_RC_THE_WARNING				0x02000000
//.............................................................................
// Names (might not be episode-specific)

//#define	NAME_BERNIE			0		// not allowed to have a 0 NAME_* (move Bernie down list)
#define	NAME_AL				1
#define	NAME_BETH			2
#define	NAME_MAGICJ			3
#define	NAME_LISA			4
#define	NAME_LOUIE			5
#define	NAME_FRANK			6
#define	NAME_BUTTMUNCH		7
#define	NAME_ARNOLD			8
#define	NAME_BREWSTER		9
#define	NAME_PUNKY			10
#define NAME_IGMO			11
#define	NAME_JOHNNY			12
#define	NAME_BETTY			13
#define NAME_LEROY			14
#define	NAME_JED			15		// Ridah, testing only (doors.bsp)
#define	NAME_BUSTER			16		// Ridah, testing only (doors.bsp)
#define NAME_BUBBA			17
#define NAME_MOMO			18
#define	NAME_MUTTSKI		19
#define	NAME_SPIKE			20
#define	NAME_TOUGHGUY1		21
#define	NAME_TOUGHGUY2		22
#define	NAME_INTROGUY1		23
#define	NAME_BERNIE			24

#define NAME_LAMONT			25
#define NAME_MONA			26
#define NAME_LENNY			27
#define NAME_CHICK			28

#define NAME_SLUGGO			29
#define NAME_ROCKO			30

#define	NAME_ROVER			31		// Lamont's mutt

#define NAME_JOSEPH			32
#define NAME_RUMMY			33
#define	NAME_NICK			34
#define NAME_JESUS			35	

#define NAME_YOLANDA		36

#define NAME_CARLTON		37
#define NAME_TINA			38
#define	NAME_HARDEY			39
#define NAME_LAUREL			40

#define NAME_HAROLD			41
#define NAME_DICK			42
#define NAME_BURT			43

#define NAME_FINGERS		44
#define NAME_DAN			45

#define NAME_CLARENCE		46
#define	NAME_ADOLF			47
#define NAME_CANDY			48

#define	NAME_SHARKY			49 // the pawn dude

#define	NAME_KINGPIN		50
#define NAME_BLUNT			51
#define NAME_NICKIBLANCO	52

#define NAME_MOE			53
#define NAME_LARRY			54
#define NAME_CURLY			55

#define NAME_ED				56

#define	NAME_POPEYE			57
#define NAME_DOGG			58 // this is the bartenders name... ?? (its what Rich wants)
#define NAME_SELMA			59
#define	NAME_JANE			60
#define NAME_BARNEY			61
#define	NAME_BIGWILLIE		62
#define	NAME_SAL			63
#define NAME_LEFTY			64
#define NAME_BWILLIE		65	// DO NOT CONFUSE THIS WITH BIGWILLIE

#define NAME_MUNG			66
#define NAME_TYRONE			67

#define NAME_LUKE			68	
#define NAME_HANN			69

// STEELTOWN
#define	NAME_KROKER			70

#define NAME_KID_1				71
#define	NAME_KID_2				72
#define NAME_KID_3				73
#define NAME_KID_4				74
#define NAME_KID_5				75
#define NAME_KID_6				76
#define NAME_KID_7				77
#define NAME_KID_8				78

#define NAME_OSCAR				79
#define NAME_DAVID				80
#define NAME_BAMBI				81
#define NAME_BRITTANY			82
#define NAME_MATHEW				83
#define	NAME_PETE				84

#define NAME_MOKER				85 // BOSS (STEELTOWN)

#define	NAME_HEILMAN			86
// RC
#define NAME_BUTCH				87
#define NAME_PATRICK			88
#define NAME_GROUCHO			89
#define NAME_HARPO				90
#define NAME_CHICO				91

#define NAME_BLEFTY				92
#define NAME_SCALPER			93
#define NAME_DUBS				94

#define NAME_ROCHELLE			95
#define NAME_LOLA				96

#define	NAME_DUDE				97
#define	NAME_WALTER				98
#define NAME_DONNY				99

//.............................................................................
// These must match the gang strings in ep_all.c !!

#define	GANG_NUETRAL	0
#define	GANG_PLAYER		1
#define	GANG_MAIN		2
#define	GANG_RATGANG	3

#define	NUM_GANGS		3

//.............................................................................
// General procedural defines

void		EP_SpawnFlags				( edict_t *self );

void		EP_SetNameIndex				( edict_t *self );
edict_t		*EP_GetCharacter			( int nameIndex );
edict_t		*EP_GetCharacterByName		( char *name );
char		*EP_GetGangName				( int cast_group );

qboolean	EP_CastSight				( edict_t *self, edict_t *other, cast_memory_t *cast_memory );
qboolean	EP_CastUse					( edict_t *self, edict_t *other, edict_t *activator );

qboolean	EP_EventSpeech				( edict_t *self, edict_t *other, int saywhat );
void		EP_ItemPickup				( edict_t *self, edict_t *other );
void		EP_EventScript				( edict_t *self, char *scriptname );

void		EP_Reset					( edict_t *self, edict_t *other );
void		EP_PlayerLog				( edict_t *self, int page );

int			EP_HiredGuys				( edict_t *player, edict_t *self );
void		EP_CheckMomo				( edict_t *ent, cast_memory_t	*mem );
qboolean	EP_DoKey					( edict_t *ent, edict_t *other );
void		EP_Check_DoKey				( edict_t *self, edict_t *ent );
void		EP_ReachedDoKey				( edict_t *self );
void		EP_EndDoKey					( edict_t *self );
qboolean	EP_UnlockDoorFlag			( edict_t *ent );
void		EP_HiredGuysRegisterFlags	( edict_t *ent, edict_t *other );
void		EP_SpecialEventDeath		( edict_t *self );


void		EP_Flash_Newflag			(edict_t *self, int ep_flag);
//.............................................................................
// Skidrow procedural defines

qboolean	EP_Skidrow_CastSight		( edict_t *self, edict_t *other, cast_memory_t *mem );
qboolean	EP_Skidrow_CastUse			( edict_t *self, edict_t *other, edict_t *activator );
qboolean	EP_Skidrow_EventSpeech		( edict_t *self, edict_t *other, int saywhat );
void		EP_Skidrow_ItemPickup		( edict_t *self, edict_t *other );
void		EP_Skidrow_Script			( edict_t *ent, char *scriptname );

void		EP_Skidrow_Reset			( edict_t *self, edict_t *other );

void		Resp_MagicJ_GotDollar		( edict_t *self, edict_t *other, response_t response );
void		Resp_Momo_GotMoney			( edict_t *self, edict_t *other, response_t response );
void		Resp_Betty_GetsPissed		( edict_t *self, edict_t *other, response_t response );
void		Resp_Lenny_Help				( edict_t *self, edict_t *other, response_t response );
void		Resp_Lenny_Killed_Target	( edict_t *self, edict_t *other, response_t response );
void		Resp_Rummy_GotWine			( edict_t *self, edict_t *other, response_t response );

void		EP_SkidrowFlags				( edict_t *self );
void		EP_Skidrow_Player_Log		( edict_t *self, int page );
void		EP_Skidrow_Register_EPFLAG	( edict_t *self, int ep_flag );
void		EP_Skidrow_CheckMomo		( edict_t *ent, cast_memory_t	*mem );
qboolean	EP_Skidrow_Flash_Newflag	(edict_t *self, int ep_flag);
//.............................................................................

// PoisonVille procedural defines

qboolean	EP_Poisonville_CastSight	( edict_t *self, edict_t *other, cast_memory_t *mem );
qboolean	EP_Poisonville_CastUse		( edict_t *self, edict_t *other, edict_t *activator );
qboolean	EP_Poisonville_EventSpeech	( edict_t *self, edict_t *other, int saywhat );
void		EP_Poisonville_ItemPickup	( edict_t *self, edict_t *other );
void		EP_Poisonville_Script		( edict_t *ent, char *scriptname );
//.............................................................................

// 
// PoisonVille procedural defines

int			EP_PV_HiredGuysFlags		( edict_t *player, edict_t *self );
void		EP_PVFlags					( edict_t *self );
void		Resp_PVMomo_GotMoney		( edict_t *self, edict_t *other, response_t response );
void		EP_PV_CheckMomo				( edict_t *ent, cast_memory_t	*mem );
qboolean	EP_PV_DoKey					( edict_t *ent, edict_t *other );
void		EP_PV_Check_DoKey			( edict_t *self, edict_t *ent );
void		EP_PV_ReachedDoKey			( edict_t *self );
void		EP_PV_EndDoKey				( edict_t *self );

qboolean	EP_PV_UnlockDoorFlag		( edict_t *ent );
void		EP_PV_HiredGuysRegisterFlags( edict_t *ent, edict_t *other );
void		EP_PV_Player_Log			( edict_t *self, int page );
void		EP_PV_SpecialEventDeath		( edict_t *self);
qboolean	EP_PV_Flash_Newflag			(edict_t *self, int ep_flag);

// Trainyard procedural defines
qboolean	EP_Trainyard_EventSpeech	( edict_t *self, edict_t *other, int saywhat );	
void		EP_Trainyard_ItemPickup		( edict_t *self, edict_t *other );
void		EP_Trainyard_Script			( edict_t *self, char *scriptname );
int			EP_Trainyard_HiredGuysFlags	( edict_t *player, edict_t *self );
// void		EP_Trainyard_SpecialEventDeath (edict_t *self );
qboolean	EP_Trainyard_CastSight		( edict_t *self, edict_t *other, cast_memory_t *mem );
qboolean	EP_Trainyard_CastUse		( edict_t *self, edict_t *other, edict_t *activator );
void		EP_Trainyard_Script			( edict_t *ent, char *scriptname );
void		EP_TrainyardFlags			( edict_t *self );

void		EP_Trainyard_Player_Log		( edict_t *self, int page );
qboolean	EP_TY_Flash_Newflag			(edict_t *self, int ep_flag);

// Shipyard procedural defines
qboolean	EP_SY_EventSpeech			( edict_t *self, edict_t *other, int saywhat );	
void		EP_SY_ItemPickup			( edict_t *self, edict_t *other );
void		EP_SY_Script				( edict_t *self, char *scriptname );
int			EP_SY_HiredGuysFlags		( edict_t *player, edict_t *self );
void		EP_SY_SpecialEventDeath		( edict_t *self );
qboolean	EP_SY_CastSight				( edict_t *self, edict_t *other, cast_memory_t *mem );
qboolean	EP_SY_CastUse				( edict_t *self, edict_t *other, edict_t *activator );
void		EP_SY_Script				( edict_t *ent, char *scriptname );
void		EP_SYFlags					( edict_t *self );
void		EP_SY_CheckMomo				( edict_t *ent, cast_memory_t	*mem );
void		EP_SY_SpecialEventDeath		( edict_t *self );
void		EP_SY_Player_Log			( edict_t *self, int page );
qboolean	EP_SY_Flash_Newflag			(edict_t *self, int ep_flag);


// Steeltown procedural defines
qboolean	EP_Steeltown_EventSpeech	(edict_t *self, edict_t *other, int saywhat );	
void		EP_Steeltown_ItemPickup		(edict_t *self, edict_t *other );
void		EP_Steeltown_Script			(edict_t *self, char *scriptname );
int			EP_Steeltown_HiredGuysFlags (edict_t *player, edict_t *self );
void		EP_Steeltown_SpecialEventDeath (edict_t *self );
qboolean	EP_Steeltown_CastSight		(edict_t *self, edict_t *other, cast_memory_t *mem );
qboolean	EP_Steeltown_CastUse		(edict_t *self, edict_t *other, edict_t *activator );
void		EP_Steeltown_Script			(edict_t *ent, char *scriptname );
void		EP_SteeltownFlags			(edict_t *self );
void		EP_Steeltown_CheckMomo		(edict_t *ent, cast_memory_t	*mem );
void		EP_Steeltown_SpecialEventDeath (edict_t *self );
qboolean	EP_Steeltown_DoKey			(edict_t *ent, edict_t *other );
void		EP_Steeltown_Check_DoKey	(edict_t *self, edict_t *ent );
void		EP_Steeltown_ReachedDoKey	(edict_t *self );
void		EP_Steeltown_EndDoKey		(edict_t *self );
qboolean	EP_Steeltown_UnlockDoorFlag (edict_t *ent );
void		EP_Steeltown_HiredGuysRegisterFlags (edict_t *ent, edict_t *other );
void		EP_Steeltown_Player_Log		( edict_t *self, int page );
qboolean	EP_Steeltown_Flash_Newflag			(edict_t *self, int ep_flag);

// RadioCity procedural defines
qboolean	EP_RC_EventSpeech			(edict_t *self, edict_t *other, int saywhat );	
void		EP_RC_ItemPickup			(edict_t *self, edict_t *other );
void		EP_RC_Script				(edict_t *self, char *scriptname );
int			EP_RC_HiredGuysFlags		(edict_t *player, edict_t *self );
void		EP_RC_SpecialEventDeath		(edict_t *self );
qboolean	EP_RC_CastSight				(edict_t *self, edict_t *other, cast_memory_t *mem );
qboolean	EP_RC_CastUse				(edict_t *self, edict_t *other, edict_t *activator );
void		EP_RC_Script				(edict_t *ent, char *scriptname );
void		EP_RCFlags					(edict_t *self );
void		EP_RC_CheckMomo				(edict_t *ent, cast_memory_t	*mem );
void		EP_RC_SpecialEventDeath		(edict_t *self );
qboolean	EP_RC_DoKey					(edict_t *ent, edict_t *other );
void		EP_RC_Check_DoKey			(edict_t *self, edict_t *ent );
void		EP_RC_ReachedDoKey			(edict_t *self );
void		EP_RC_EndDoKey				(edict_t *self );
qboolean	EP_RC_UnlockDoorFlag		(edict_t *ent );
void		EP_RC_HiredGuysRegisterFlags (edict_t *ent, edict_t *other );
void		EP_RC_Player_Log			( edict_t *self, int page );
void		Resp_Scalper_GotTicket		( edict_t *self, edict_t *other, response_t response );
qboolean	EP_RC_Flash_Newflag			(edict_t *self, int ep_flag);

typedef enum 
{
	say_neutral,
	say_asshole,
	say_hostile,
	say_flashlight,
	say_alisthatyou,
	say_behindthebarrel,
	say_forabuck,
	say_talktobetty
} saywhat_say;

typedef struct player_log_s player_log_t;

struct player_log_s
{
	char		*ep_text;
	int			ep_flag;
	int			clue_number;
	qboolean	new_clue;
};

