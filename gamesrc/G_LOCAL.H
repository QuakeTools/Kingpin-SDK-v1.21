
// g_local.h -- local definitions for game module

#include "q_shared.h"

// define GAME_INCLUDE so that game.h does not define the
// short, server-visible gclient_t and edict_t structures,
// because we define the full size ones in this file
#define	GAME_INCLUDE
#include "game.h"

#include "g_nav.h"

#include "vehicles.h"

#include "g_teamplay.h"

// Ridah, new AI system defines
#include "g_ai.h"
#include "voice.h"

// Episode specific defines
#include "ep_all.h"

// the "gameversion" client command will print this plus compile date
#define	GAMEVERSION	"main"

// protocol bytes that can be directly added to messages
#define	svc_muzzleflash		1
#define	svc_muzzleflash2	2
#define	svc_muzzleflash3	3
#define	svc_temp_entity		4
#define	svc_layout			5
#define	svc_inventory		6
// JOSEPH 29-DEC-98
#define svc_hud				7

#define svc_stufftext		13

//==================================================================

// view pitching times
#define DAMAGE_TIME		0.5
#define	FALL_TIME		0.3


// edict->spawnflags
// these are set with checkboxes on each entity in the map editor
#define	SPAWNFLAG_NOT_EASY			0x00000100
#define	SPAWNFLAG_NOT_MEDIUM		0x00000200
#define	SPAWNFLAG_NOT_HARD			0x00000400
#define	SPAWNFLAG_NOT_DEATHMATCH	0x00000800
#define	SPAWNFLAG_NOT_COOP			0x00001000

// edict->flags
#define	FL_FLY					0x00000001
#define	FL_SWIM					0x00000002	// implied immunity to drowining
#define FL_IMMUNE_LASER			0x00000004
#define	FL_INWATER				0x00000008
#define	FL_GODMODE				0x00000010
#define	FL_NOTARGET				0x00000020
#define FL_IMMUNE_SLIME			0x00000040
#define FL_IMMUNE_LAVA			0x00000080
#define	FL_PARTIALGROUND		0x00000100	// not all corners are valid
#define	FL_WATERJUMP			0x00000200	// player jumping out of water
#define	FL_TEAMSLAVE			0x00000400	// not the first on the team
#define FL_NO_KNOCKBACK			0x00000800
#define FL_POWER_ARMOR			0x00001000	// power armor (if any) is active

// Ridah, Vehicles
#define FL_HOVERCAR				0x00002000	// this entity is currently using a Hovercar
#define FL_HOVERCAR_GROUND		0x00004000	// this entity is currently using a Grounded Hovercar
#define	FL_BIKE					0x00008000
#define	FL_CAR					0x00010000
// done.

#define	FL_SPAWNED_BLOODPOOL	0x00020000
#define	FL_FOLLOWING			0x00040000	// this character has followed us to the next level. so if we're
											// loading in a game as a result of changing levels, delete any
											// characters that have this flag set, since they've moved onto
											// the next level.
											//
											// If we're manually loading a level (not changing levels), leave
											// these characters in place, and clear the flag.

#define FL_CHASECAM				0x00100000	// entity is using chasecam
#define FL_MDXBBOX				0x00200000
#define FL_JETPACK				0x00400000	// Jet Pack enabled

#define FL_RESPAWN				0x80000000	// used for item respawning


#define	FRAMETIME		0.1

// memory tags to allow dynamic memory to be cleaned up
#define	TAG_GAME	765		// clear when unloading the dll
// *** RIDAH: do not change this, 766 is hardcoded into MDX_GetObjectBounds() ***
#define	TAG_LEVEL	766		// clear when loading a new level


#define MELEE_DISTANCE	80

#define BODY_QUEUE_SIZE		8

typedef enum
{
	DAMAGE_NO,
	DAMAGE_YES,			// will take damage if hit
	DAMAGE_AIM			// auto targeting recognizes this
} damage_t;

typedef enum 
{
	WEAPON_READY, 
	WEAPON_ACTIVATING,
	WEAPON_DROPPING,
	WEAPON_FIRING,
// RAFAEL 01-11-99
	WEAPON_RELOADING,
	WEAPON_RELOAD_CYCLE,
	WEAPON_RELOADING_SPISTOL
} weaponstate_t;

typedef enum
{
	AMMO_BULLETS,
	AMMO_SHELLS,
	AMMO_ROCKETS,
	AMMO_GRENADES,
	AMMO_CELLS,
	AMMO_SLUGS,
	AMMO_MAGSLUG,
	AMMO_TRAP
} ammo_t;

// RAFAEL
typedef enum
{
	CLIP_NONE,
	CLIP_PISTOL,
	CLIP_SHOTGUN,
	CLIP_TOMMYGUN,
	CLIP_SLUGS,
	CLIP_GRENADES,
	CLIP_ROCKETS,
	CLIP_FLAMEGUN
} clip_t;

//deadflag
#define DEAD_NO					0
#define DEAD_DYING				1
#define DEAD_DEAD				2
#define DEAD_RESPAWNABLE		3

//range
#define RANGE_MELEE				0
#define RANGE_NEAR				1
#define RANGE_MID				2
#define RANGE_FAR				3

//gib types
#define GIB_ORGANIC				0
#define GIB_METALLIC			1


// Ridah, MDX, simplify assigning model parts, this isn't needed by the engine
#define	PART_HEAD				0	// HEAD must ALWAYS use this index!
#define	PART_LEGS				1
#define	PART_BODY				2
#define	PART_GUN				3
// done.
#define	PART_GUN2				4
#define	PART_CIGAR				5
#define PART_HAT				6

//monster attack state
#define AS_STRAIGHT				1
#define AS_SLIDING				2
#define	AS_MELEE				3
#define	AS_MISSILE				4

// armor types
#define ARMOR_NONE				0
#define ARMOR_JACKET			1
#define ARMOR_COMBAT			2
#define ARMOR_BODY				3
#define ARMOR_SHARD				4

// power armor types
#define POWER_ARMOR_NONE		0
#define POWER_ARMOR_SCREEN		1
#define POWER_ARMOR_SHIELD		2

// handedness values
#define RIGHT_HANDED			0
#define LEFT_HANDED				1
#define CENTER_HANDED			2


// game.serverflags values
#define SFL_CROSS_TRIGGER_1		0x00000001
#define SFL_CROSS_TRIGGER_2		0x00000002
#define SFL_CROSS_TRIGGER_3		0x00000004
#define SFL_CROSS_TRIGGER_4		0x00000008
#define SFL_CROSS_TRIGGER_5		0x00000010
#define SFL_CROSS_TRIGGER_6		0x00000020
#define SFL_CROSS_TRIGGER_7		0x00000040
#define SFL_CROSS_TRIGGER_8		0x00000080
#define SFL_CROSS_TRIGGER_MASK	0x000000ff


// noise types for PlayerNoise
#define PNOISE_SELF				0
#define PNOISE_WEAPON			1
#define PNOISE_IMPACT			2


// edict->movetype values
typedef enum
{
MOVETYPE_NONE,			// never moves
MOVETYPE_NOCLIP,		// origin and angles change with no interaction
MOVETYPE_PUSH,			// no clip to world, push on box contact
MOVETYPE_STOP,			// no clip to world, stops on box contact

MOVETYPE_WALK,			// gravity
MOVETYPE_STEP,			// gravity, special edge handling
MOVETYPE_FLY,
MOVETYPE_TOSS,			// gravity
MOVETYPE_FLYMISSILE,	// extra size to monsters
MOVETYPE_BOUNCE,		// added this (the comma at the end of line)
MOVETYPE_WALLBOUNCE,
MOVETYPE_TOSS_SLIDE		// Ridah, testing
} movetype_t;



typedef struct
{
	int		base_count;
	int		max_count;
	float	normal_protection;
	float	energy_protection;
	int		armor;
} gitem_armor_t;


// gitem_t->flags
#define	IT_WEAPON		1		// use makes active weapon
#define	IT_AMMO			2
#define IT_ARMOR		4
#define IT_STAY_COOP	8
#define IT_KEY			16
#define IT_POWERUP		32

#define	IT_FLASHLIGHT	64

#define IT_SILENCER		128

#define IT_NOCHEATS		256

typedef struct gitem_s
{
	char		*classname;	// spawning name
	qboolean	(*pickup)(struct edict_s *ent, struct edict_s *other);
	void		(*use)(struct edict_s *ent, struct gitem_s *item);
	void		(*drop)(struct edict_s *ent, struct gitem_s *item);
	void		(*weaponthink)(struct edict_s *ent);
	char		*pickup_sound;
	char		*world_model;
	int			world_model_flags;
	char		*view_model;

	// client side info
	char		*icon;
	char		*pickup_name;	// for printing on pickup
	int			count_width;		// number of digits to display by icon

	int			quantity;		// for ammo how much, for weapons how much is used per shot
	char		*ammo;			// for weapons
	int			flags;			// IT_* flags

	void		*info;
	int			tag;

	char		*precaches;		// string of all models, sounds, and images this item will use


} gitem_t;



//
// this structure is left intact through an entire game
// it should be initialized at dll load time, and read/written to
// the server.ssv file for savegames
//
typedef struct
{
	char		helpmessage1[512];
	char		helpmessage2[512];
	int			helpchanged;	// flash F1 icon if non 0, play sound
								// and increment only if 1, 2, or 3

	gclient_t	*clients;		// [maxclients]

	// can't store spawnpoint in level, because
	// it would get overwritten by the savegame restore
	char		spawnpoint[512];	// needed for coop respawns

	// store latched cvars here that we want to get at often
	int			maxclients;
	int			maxentities;

	// cross level triggers
	int			serverflags;

	// items
	int			num_items;

	qboolean	autosaved;
} game_locals_t;


//
// this structure is cleared as each map is entered
// it is read/written to the level.sav file for savegames
//

#define	MAX_LIGHT_SOURCES	512

typedef struct
{
	int			framenum;
	float		time;

	char		level_name[MAX_QPATH];	// the descriptive name (Outer Base, etc)
	char		mapname[MAX_QPATH];		// the server name (base1, etc)
	char		nextmap[MAX_QPATH];		// go here when fraglimit is hit

	// intermission state
	float		intermissiontime;		// time the intermission was started
	char		*changemap;
	int			exitintermission;
	vec3_t		intermission_origin;
	vec3_t		intermission_angle;

	edict_t		*sight_client;	// changed once each frame for coop games

	edict_t		*sight_entity;
	int			sight_entity_framenum;
	edict_t		*sound_entity;
	int			sound_entity_framenum;
	edict_t		*sound2_entity;
	int			sound2_entity_framenum;

	int			pic_health;

	int			total_secrets;
	int			found_secrets;

	int			total_goals;
	int			found_goals;

	int			total_monsters;
	int			killed_monsters;

	edict_t		*current_entity;	// entity running from G_RunFrame
	int			body_que;			// dead bodies

	int			power_cubes;		// ugly necessity for coop

	// BEGIN:	Xatrix/Ridah/Navigator/19-mar-1998
	// this stores all the node data for the current level
	active_node_data_t	*node_data;
	// END:		Xatrix/Ridah/Navigator/19-mar-1998

	// Ridah
	int			num_characters;		// progressive total, updated each time a character enters or leaves the game
									// NOTE: includes players!

	edict_t		*characters[MAX_CHARACTERS];	// indexes in g_edicts to all characters in the game

	// Global Cast Memory - stores a lookup table pointing to character-character memories
	//
	//	This allows us to easily indentify whether a particular character can see another character
	//
	//                                 [    SOURCE    ][     DEST     ]
	cast_memory_t	*global_cast_memory[MAX_CHARACTERS][MAX_CHARACTERS];

	int			episode;			// current episode being played
	int			unit;				// current unit within the episode
	// Ridah, done.

	// RAFAEL 11-05-98
	vec3_t	light_orgs[MAX_LIGHT_SOURCES];
	vec3_t	light_colors[MAX_LIGHT_SOURCES];
	float	light_values[MAX_LIGHT_SOURCES];
	//float	light_radius[MAX_LIGHT_SOURCES];
	byte	light_styles[MAX_LIGHT_SOURCES];
	int		num_light_sources;
	// END 11-05-98

	// RAFAEL
	float	cut_scene_time;
	// int		exit_cut_scene;
	vec3_t	cut_scene_origin;
	vec3_t	cut_scene_angle;
	vec3_t	player_oldpos;
	vec3_t	player_oldang;

	float		pawn_time;
	vec3_t		pawn_origin;
	qboolean	pawn_exit;

	qboolean	bar_lvl;
	float		speaktime;
	// JOSEPH 24-FEB-99
	int         cut_scene_camera_switch;
	int			cut_scene_end_count;
	// END JOSEPH
	// JOSEPH 19-MAR-99-B
    float       fadeendtime;
	float       totalfade;
	int			inversefade;
	// END JOSEPH

	// JOSEPH 13-JUN-99
	int helpchange;	
	// END JOSEPH
} level_locals_t;


// spawn_temp_t is only used to hold entity field values that
// can be set from the editor, but aren't actualy present
// in edict_t during gameplay
typedef struct
{
	// world vars
	char		*sky;
	char		*nextmap;

	int			lip;
	int			distance;
	int			height;
	char		*noise;
	float		pausetime;
	char		*item;
	char		*gravity;

	float		minyaw;
	float		maxyaw;
	float		minpitch;
	float		maxpitch;

	float		fogdensity;
	vec3_t		fogval;
	float		fogdensity2;
	vec3_t		fogval2;
	
} spawn_temp_t;

// JOSEPH 7-OCT-98
typedef struct
{
	// fixed data
	vec3_t		start_origin;
	vec3_t		start_angles;
	vec3_t		end_origin;
	vec3_t		end_angles;

	int			sound_start;
	int			sound_middle;
	int			sound_end;
	int			sound_start2;
	int			sound_middle2;
	int			sound_end2;

	float		accel;
	float		speed;
	float		decel;
	float		distance;

	float		wait;

	// state data
	int			state;
	vec3_t		dir;
	float		current_speed;
	float		move_speed;
	float		next_speed;
	float		remaining_distance;
	float		decel_distance;
	void		(*endfunc)(edict_t *);
} moveinfo_t;
// END JOSEPH

typedef struct
{
	void	(*aifunc)(edict_t *self, float dist);
	float	dist;
	void	(*thinkfunc)(edict_t *self);
} mframe_t;

typedef struct
{
	int			firstframe;
	int			lastframe;
	mframe_t	*frame;
//	float		*lateral_array;
	void		(*endfunc)(edict_t *self);
} mmove_t;

typedef struct
{
	mmove_t		*currentmove;
	int			aiflags;
	int			nextframe;
	float		scale;

	void		(*idle)(edict_t *self);
	void		(*search)(edict_t *self);
	void		(*dodge)(edict_t *self, edict_t *other, float eta);

	qboolean	(*attack)(edict_t *self);		// standing attack
	void		(*long_attack)(edict_t *self);	// running attack (run, and attack if facing enemy and path is clear)

	void		(*sight)(edict_t *self, edict_t *other);
	qboolean	(*checkattack)(edict_t *self);

// Ridah, new AI system
	mmove_t		*oldcurrentmove;		// used for thug_sit

	void		(*duck)(edict_t *self);		// called when beginning to duck (may be part of normal movement)
	void		(*talk)(edict_t *self);		// will start a random talking animation, and play a sound

	void		(*avoid)(edict_t *self, edict_t *other, qboolean face);    // will start a random talking animation, and play a sound

	void		(*catch_fire)(edict_t *self, edict_t *other);

	float		last_talk_turn;
	edict_t		*talk_ent;					// person we are talking to

	float		max_attack_distance;		// try and move closer to enemy if outside this range
	float		max_sighting_distance;		// can't see things out of this range

	float		standing_max_z;				// set to self->maxs[2] upon spawning
	float		last_avoid, last_reverse;
	edict_t		*avoid_ent;

	float		goal_ent_pausetime;			// avoid goal_ent if > level.time

	int			last_side_attack;
	float		last_side_attack_time;

	cast_memory_t	*friend_memory;
	cast_memory_t	*enemy_memory;
	cast_memory_t	*neutral_memory;

	// these allow a generic AI system for all characters to interact with the animations
	mmove_t		*move_stand;
	mmove_t		*move_crstand;

	mmove_t		*move_run;
	mmove_t		*move_runwalk;
	mmove_t		*move_crwalk;

	mmove_t		*move_jump;

	mmove_t		*move_crouch_down;
	mmove_t		*move_stand_up;

	mmove_t		*move_avoid_walk;
	mmove_t		*move_avoid_run;
	mmove_t		*move_avoid_reverse_walk;
	mmove_t		*move_avoid_reverse_run;
	mmove_t		*move_avoid_crwalk;

	mmove_t		*move_lside_step;
	mmove_t		*move_rside_step;

	mmove_t		*move_start_climb;
	mmove_t		*move_end_climb;

	mmove_t		*move_evade;
	mmove_t		*move_stand_evade;		// not quite a hostile enemy yet, but they may have their weapon out
	void		(*backoff)(edict_t *self, edict_t *other);
// done.

	float		pausetime;

	vec3_t		saved_goal;
	vec3_t		last_sighting;
	float		idle_time;
	int			linkcount;

// Rafael
	// was missing this variable
	float		trail_time;

} cast_info_t;



extern	game_locals_t	game;
extern	level_locals_t	level;
extern	game_import_t	gi;
extern	game_export_t	globals;
extern	spawn_temp_t	st;

extern	int	sm_meat_index;
extern	int	snd_fry;






extern	int	jacket_armor_index;
extern	int	combat_armor_index;
extern	int	body_armor_index;


// Ridah, in-game effects
//extern	int	sp_blood1;


// means of death
#define MOD_UNKNOWN			0
#define MOD_BLASTER			1
#define MOD_SHOTGUN			2
#define MOD_SSHOTGUN		3
#define MOD_MACHINEGUN		4
#define MOD_CHAINGUN		5
#define MOD_GRENADE			6
#define MOD_G_SPLASH		7
#define MOD_ROCKET			8
#define MOD_R_SPLASH		9
#define MOD_HYPERBLASTER	10
#define MOD_RAILGUN			11
#define MOD_BFG_LASER		12
#define MOD_BFG_BLAST		13
#define MOD_BFG_EFFECT		14
#define MOD_HANDGRENADE		15
#define MOD_HG_SPLASH		16
#define MOD_WATER			17
#define MOD_SLIME			18
#define MOD_LAVA			19
#define MOD_CRUSH			20
#define MOD_TELEFRAG		21
#define MOD_FALLING			22
#define MOD_SUICIDE			23
#define MOD_HELD_GRENADE	24
#define MOD_EXPLOSIVE		25
#define MOD_BARREL			26
#define MOD_BOMB			27
#define MOD_EXIT			28
#define MOD_SPLASH			29
#define MOD_TARGET_LASER	30
#define MOD_TRIGGER_HURT	31
#define MOD_HIT				32
#define MOD_TARGET_BLASTER	33
#define MOD_RIPPER				34
#define MOD_PHALANX				35
#define MOD_BRAINTENTACLE		36
#define MOD_BLASTOFF			37
#define MOD_GEKK				38
#define MOD_TRAP				39
#define MOD_FLAMETHROWER		40
#define MOD_BLACKJACK			41
#define MOD_SILENCER			42
#define MOD_CROWBAR				43
#define MOD_DOGBITE				44
#define MOD_BLOWBACK			45
#define MOD_PISTOL				46
#define MOD_BARMACHINEGUN		47
#define MOD_SAFECAMPER			48


#define MOD_FRIENDLY_FIRE	0x8000000

extern	int	meansOfDeath;


extern	edict_t			*g_edicts;

extern	cast_memory_t	*g_cast_memory;
extern	cast_group_t	*g_cast_groups;

#define	FOFS(x) (int)&(((edict_t *)0)->x)
#define	STOFS(x) (int)&(((spawn_temp_t *)0)->x)
#define	LLOFS(x) (int)&(((level_locals_t *)0)->x)
#define	CLOFS(x) (int)&(((gclient_t *)0)->x)
#define	CMOFS(x) (int)&(((cast_memory_t *)0)->x)

#define random()	((rand () & 0x7fff) / ((float)0x7fff))
#define crandom()	(2.0 * (random() - 0.5))

extern	cvar_t	*maxentities;
extern	cvar_t	*deathmatch;

extern	cvar_t	*maxrate;

extern	cvar_t	*coop;
extern	cvar_t	*dmflags;
extern	cvar_t	*skill;
extern	cvar_t	*fraglimit;
extern	cvar_t	*timelimit;
extern	cvar_t	*cashlimit;
extern	cvar_t	*password;
extern	cvar_t	*g_select_empty;
extern	cvar_t	*dedicated;

extern	cvar_t	*filterban;

extern	cvar_t	*sv_gravity;
extern	cvar_t	*sv_maxvelocity;

extern	cvar_t	*gun_x, *gun_y, *gun_z;
extern	cvar_t	*sv_rollspeed;
extern	cvar_t	*sv_rollangle;

extern	cvar_t	*run_pitch;
extern	cvar_t	*run_roll;
extern	cvar_t	*bob_up;
extern	cvar_t	*bob_pitch;
extern	cvar_t	*bob_roll;

extern	cvar_t	*sv_cheats;
extern	cvar_t	*maxclients;

extern	cvar_t	*flood_msgs;
extern	cvar_t	*flood_persecond;
extern	cvar_t	*flood_waitdelay;

// Ridah, new cvar's
extern	cvar_t	*developer;

extern	cvar_t	*ai_debug_memory;

extern	cvar_t	*g_vehicle_test;

extern	cvar_t	*dm_locational_damage;

extern	cvar_t	*showlights;

extern	cvar_t	*r_directional_lighting;

extern	cvar_t	*sv_runscale;

extern	cvar_t	*burn_enabled;
extern	cvar_t	*burn_size;
extern	cvar_t	*burn_intensity;
extern	cvar_t	*burn_r;
extern	cvar_t	*burn_g;
extern	cvar_t	*burn_b;

extern	cvar_t	*timescale;

extern	cvar_t	*teamplay;
extern	cvar_t	*g_cashspawndelay;

extern	cvar_t	*cl_parental_lock;
extern	cvar_t	*cl_parental_override;

extern	cvar_t	*dm_realmode;

extern	cvar_t	*g_mapcycle_file;
// Ridah, done.

extern  cvar_t	*cl_captions;

#define world	(&g_edicts[0])

// item spawnflags
#define ITEM_TRIGGER_SPAWN		0x00000001
#define ITEM_NO_TOUCH			0x00000002
// 6 bits reserved for editor flags
// 8 bits used as power cube id bits for coop games
#define DROPPED_ITEM			0x00010000
#define	DROPPED_PLAYER_ITEM		0x00020000
#define ITEM_TARGETS_USED		0x00040000

//
// fields are needed for spawning from the entity string
// and saving / loading games
//
#define FFL_SPAWNTEMP		1
#define FFL_NOSPAWN			2

typedef enum {
	F_INT, 
	F_FLOAT,
	F_LSTRING,			// string on disk, pointer in memory, TAG_LEVEL
	F_GSTRING,			// string on disk, pointer in memory, TAG_GAME
	F_VECTOR,
	F_ANGLEHACK,
	F_EDICT,			// index on disk, pointer in memory
	F_ITEM,				// index on disk, pointer in memory
	F_CLIENT,			// index on disk, pointer in memory
	F_FUNCTION,
	F_MMOVE,
	F_CAST_MEMORY,
	F_IGNORE
} fieldtype_t;

typedef struct
{
	char	*name;
	int		ofs;
	fieldtype_t	type;
	int		flags;
} field_t;


extern	field_t fields[];
extern	gitem_t	itemlist[];


//
// g_cmds.c
//
void Cmd_Help_f (edict_t *ent, int page);
void Cmd_Score_f (edict_t *ent);

//
// g_items.c
//
void PrecacheItem (gitem_t *it);
void InitItems (void);
void SetItemNames (void);
gitem_t	*FindItem (char *pickup_name);
gitem_t	*FindItemByClassname (char *classname);
#define	ITEM_INDEX(x) ((x)-itemlist)
edict_t *Drop_Item (edict_t *ent, gitem_t *item);
void SetRespawn (edict_t *ent, float delay);
void ChangeWeapon (edict_t *ent);
void SpawnItem (edict_t *ent, gitem_t *item);
void Think_Weapon (edict_t *ent);
int ArmorIndex (edict_t *ent);
int PowerArmorType (edict_t *ent);
gitem_t	*GetItemByIndex (int index);
qboolean Add_Ammo (edict_t *ent, gitem_t *item, int count);
void Touch_Item (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf);
// JOSEPH 6-JAN-99
edict_t *Shot_Drop_Item (edict_t *ent, gitem_t *item, char* modeloverride);
void Think_FlashLight (edict_t *ent);
//
// g_utils.c
//

qboolean	KillBox (edict_t *ent);
void	G_ProjectSource (vec3_t point, vec3_t distance, vec3_t forward, vec3_t right, vec3_t result);
edict_t *G_Find (edict_t *from, int fieldofs, char *match);
edict_t *findradius (edict_t *from, vec3_t org, float rad);
edict_t *G_PickTarget (char *targetname);
void	G_UseTargets (edict_t *ent, edict_t *activator);
void	G_SetMovedir (vec3_t angles, vec3_t movedir);

void	G_InitEdict (edict_t *e);
edict_t	*G_Spawn (void);
void	G_FreeEdict (edict_t *e);

void	G_TouchTriggers (edict_t *ent);
void	G_TouchSolids (edict_t *ent);

char	*G_CopyString (char *in);

float	*tv (float x, float y, float z);
char	*vtos (vec3_t v);

float vectoyaw (vec3_t vec);
float	entyaw( edict_t *self, edict_t *other );

// Ridah, Surface Sprites
qboolean SurfaceSpriteEffect(	byte surf_sfx, byte width, byte height,
								edict_t *impact_ent, vec3_t pos, vec3_t normal );

qboolean SurfaceSpriteEffectRipple(	byte surf_sfx, byte width, byte height,
								edict_t *impact_ent, vec3_t pos, vec3_t normal );


// done.

// Ridah, moved vectoangles() to q_shared.c

//
// g_combat.c
//
qboolean OnSameTeam (edict_t *ent1, edict_t *ent2);
qboolean CanDamage (edict_t *targ, edict_t *inflictor);
void T_Damage (edict_t *targ, edict_t *inflictor, edict_t *attacker, vec3_t dir, vec3_t point, vec3_t normal, int damage, int knockback, int dflags, int mod);
void T_RadiusDamage (edict_t *inflictor, edict_t *attacker, float damage, edict_t *ignore, float radius, int mod);
// JOSEPH 21-APR-99
void T_RadiusDamage_Fire (edict_t *inflictor, edict_t *attacker, float damage, edict_t *ignore, float radius);
// END JOSEPH
// RAFAEL
void T_DamageMDX (edict_t *targ, edict_t *inflictor, edict_t *attacker, vec3_t dir, vec3_t 
point, vec3_t normal, int damage, int knockback, int dflags, int mod, int mdx_part, int mdx_subobject);

edict_t *SpawnTheWeapon (edict_t *self, char *itemname);

// damage flags
#define DAMAGE_RADIUS			0x00000001	// damage was indirect
#define DAMAGE_NO_ARMOR			0x00000002	// armour does not protect from this damage
#define DAMAGE_ENERGY			0x00000004	// damage is from an energy based weapon
#define DAMAGE_NO_KNOCKBACK		0x00000008	// do not affect velocity, just view angles
#define DAMAGE_BULLET			0x00000010  // damage is from a bullet (used for ricochets)
#define DAMAGE_NO_PROTECTION	0x00000020  // armor, shields, invulnerability, and godmode have no effect

#define DEFAULT_BULLET_HSPREAD	300
#define DEFAULT_BULLET_VSPREAD	500
#define DEFAULT_SHOTGUN_HSPREAD	1000
#define DEFAULT_SHOTGUN_VSPREAD	500
#define DEFAULT_DEATHMATCH_SHOTGUN_COUNT	12
#define DEFAULT_SHOTGUN_COUNT	6
#define DEFAULT_SSHOTGUN_COUNT	20

#define	DEFAULT_SAWED_SHOTGUN_COUNT		6

//
// g_cast.c
//
void cast_fire_bullet (edict_t *self, vec3_t start, vec3_t dir, int damage, int kick, int hspread, int vspread, int flashtype);
void cast_fire_shotgun (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int hspread, int vspread, int count, int flashtype);
void cast_fire_blaster (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int flashtype, int effect);
void cast_fire_grenade (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int flashtype);
void cast_fire_rocket (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int flashtype);
void cast_fire_railgun (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int flashtype);
void cast_fire_bfg (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int kick, float damage_radius, int flashtype);
void think_checkedges (edict_t *ent);
void think_slide (edict_t *ent);
void fire_fire (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int effect, qboolean hyper);
qboolean DeathByGib( edict_t *self, edict_t *inflictor, edict_t *attacker, float damage );

// RAFAEL
void cast_fire_ionripper (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int flashtype, int effect);
void cast_fire_heat (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int flashtype);
void cast_dabeam (edict_t *self);
void cast_fire_blueblaster (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, int flashtype, int effect);


void M_droptofloor (edict_t *ent);
void cast_think (edict_t *self);
void walking_cast_start (edict_t *self);
void swimming_cast_start (edict_t *self);
void flying_cast_start (edict_t *self);
void AttackFinished (edict_t *self, float time);
void cast_death_use (edict_t *self);
void M_CatagorizePosition (edict_t *ent);
void M_FlyCheck (edict_t *self);
void M_CheckGround (edict_t *ent);

//
// g_misc.c
//
void ThrowHead (edict_t *self, char *gibname, int damage, int type);
void ThrowClientHead (edict_t *self, int damage);
edict_t *ThrowGib (edict_t *self, char *gibname, int damage, int type);
// Ridah
void GibEntity( edict_t *self, edict_t *inflictor, float damage );
void BecomeExplosion1(edict_t *self);
// RAFAEL
void ThrowHeadACID (edict_t *self, char *gibname, int damage, int type);
void ThrowGibACID (edict_t *self, char *gibname, int damage, int type);

extern void path_corner_cast_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);

void AddLightSource(edict_t *self);
void UpdateDirLights( edict_t *self );
void UpdateLightVecs( edict_t *self );

//
// g_ai.c
//
void AI_SetSightClient (void);

void ai_stand (edict_t *self, float dist);
void ai_move (edict_t *self, float dist);
void ai_walk (edict_t *self, float dist);
void ai_turn (edict_t *self, float dist);
void ai_run (edict_t *self, float dist);
void ai_charge (edict_t *self, float dist);
int range (edict_t *self, edict_t *other);

void ai_runFLASHLIGHT (edict_t *self, float dist);
void ai_runDOKEY (edict_t *self, float dist);

// RAFAEL
void ai_turn2 (edict_t *self, float dist);

void FoundTarget (edict_t *self);
qboolean infront (edict_t *self, edict_t *other);
// Ridah, for more precise infront check
qboolean directly_infront (edict_t *self, edict_t *other);
// Ridah, done.
qboolean visible (edict_t *self, edict_t *other);
qboolean FacingIdeal(edict_t *self);
// RAFAEL
void SpawnBloodPool (edict_t *self);

//
// g_weapon.c
//
void ThrowDebris (edict_t *self, char *modelname, float speed, vec3_t origin);
// JOSEPH 1-JUN-99
void ThrowDebris_stuff (edict_t *self, char *modelname, float speed, vec3_t origin);
// END JOSEPH
qboolean fire_hit (edict_t *self, vec3_t aim, int damage, int kick);
void fire_bullet (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int hspread, int vspread, int mod);
void fire_shotgun (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int hspread, int vspread, int count, int mod);
void fire_blaster (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int effect, qboolean hyper);
void fire_grenade (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius);
// JOSEPH 19-MAY-99
void fire_dynamite (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius);
// END JOSEPH
void fire_grenade2 (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius, qboolean held);
void fire_rocket (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius, int radius_damage);
void fire_rail (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick);
void fire_bfg (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius);

void fire_barmachinegun (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick);
// RAFAEL
/*
void fire_ionripper (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int effect);
void fire_heat (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius, int radius_damage);
void fire_blueblaster (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, int effect);
void fire_plasma (edict_t *self, vec3_t start, vec3_t dir, int damage, int speed, float damage_radius, int radius_damage);
void fire_trap (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int speed, float timer, float damage_radius, qboolean held);
*/
void fire_flamethrower (edict_t *self, vec3_t start, vec3_t forward, int damage, int kick, int mod);
qboolean fire_blackjack (edict_t *self, vec3_t start, vec3_t forward, int damage, int kick, int mod);
// JOSEPH 19-JAN-99
qboolean fire_crowbar (edict_t *self, vec3_t start, vec3_t forward, int damage, int kick, int mod);
qboolean fire_dogbite (edict_t *self, vec3_t start, vec3_t aimdir, int damage, int kick, int mod);
// JOSEPH 30-APR-99
void fire_rat (edict_t *self, vec3_t start, vec3_t forward, int damage);
// END JOSEPH

//
// g_client.c
//
void respawn (edict_t *ent);
void BeginIntermission (edict_t *targ);
void PutClientInServer (edict_t *ent);
void InitClientPersistant (gclient_t *client);
void InitClientResp (gclient_t *client);
void InitBodyQue (void);
void ClientBeginServerFrame (edict_t *ent);

// RAFAEL
void BeginCutScene (edict_t *ent);
void EndCutScene (edict_t *ent);
// JOSEPH 16-DEC-98
void AdjustCutSceneCamera(edict_t *ent);
void NewCutSceneCamera (edict_t *ent);
// END JOSEPH

//
// g_player.c
//
void player_pain (edict_t *self, edict_t *other, float kick, int damage, int mdx_part, int mdx_subobject);
void player_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject);

//
// g_svcmds.c
//
void	ServerCommand (void);
qboolean SV_FilterPacket (char *from);

//
// p_view.c
//
void ClientEndServerFrame (edict_t *ent);

//
// p_hud.c
//
void MoveClientToIntermission (edict_t *client);
void G_SetStats (edict_t *ent);
void ValidateSelectedItem (edict_t *ent);
void DeathmatchScoreboardMessage (edict_t *client, edict_t *killer);

void MoveClientToCutScene (edict_t *camera);
// JOSEPH 22-FEB-99
void MoveClientToCutSceneCamera (edict_t *camera, int fov);
// END JOSEPH
//
// g_pweapon.c
//
void PlayerNoise(edict_t *who, vec3_t where, int type);

//
// m_move.c
//
qboolean M_CheckBottom (edict_t *ent);
qboolean M_walkmove (edict_t *ent, float yaw, float dist);
void M_MoveToGoal (edict_t *ent, float dist);
void M_ChangeYaw (edict_t *ent);
void M_ChangeYawOld (edict_t *ent);

//
// m_bbox.c
//
// RAFAEL
void MDX_Bbox_Init (void);
trace_t MDX_HitCheck (edict_t *targ, edict_t *inflictor, edict_t *attacker, vec3_t dir, vec3_t point, vec3_t normal, int damage, int knockback, int dflags, int mod, vec3_t end);
void MDX_Cleanup (void);

//
// g_phys.c
//
void G_RunEntity (edict_t *ent);

//
// g_main.c
//
void SaveClientData (void);
void FetchClientEntData (edict_t *ent);

// 
//	g_pawn.c
//
void PawnNext (edict_t *ent);
void PawnPrev (edict_t *ent);
void PawnBuy (edict_t *ent);
void PawnAgree (edict_t *ent);
void PawnDisagree (edict_t *ent);
void PawnLevelPrevious (edict_t *ent);
void PawnLeft (edict_t *ent);
void PawnRight (edict_t *ent);

//
// g_chase.c
//
void UpdateChaseCam(edict_t *ent);
void ChaseNext(edict_t *ent);
void ChasePrev(edict_t *ent);

//============================================================================

// client_t->anim_priority
#define	ANIM_ATTACK		0
#define	ANIM_BASIC		1		// stand / run
#define	ANIM_WAVE		2
#define	ANIM_JUMP		3
#define	ANIM_PAIN		4
#define	ANIM_REVERSE	5
#define	ANIM_DEATH		6

#define MAX_WEAPONS	10


// client data that stays across multiple level loads
typedef struct
{
	char		userinfo[MAX_INFO_STRING];
	char		netname[16];
	int			hand;
	int			version;		// collected from Userinfo, used to determine

	qboolean	connected;			// a loadgame will leave valid entities that
									// just don't have a connection yet

	// values saved and restored from edicts when changing levels
	int			health;
	int			max_health;
	int			savedFlags;

	int			selected_item;
	int			inventory[MAX_ITEMS];

	// ammo capacities
	int			max_bullets;
	int			max_shells;
	int			max_rockets;
	int			max_grenades;
	int			max_cells;
	int			max_slugs;
	// RAFAEL
	int			max_magslug;
	int			max_trap;

	gitem_t		*weapon;
	gitem_t		*lastweapon;

	// JOSEPH 25-SEP-98
	gitem_t  *holsteredweapon;

	// JOSEPH 3-FEB-99
	int			currentcash;
	// END JOSEPH

	int			power_cubes;	// used for tracking the cubes in coop games
	int			score;			// for calculating total unit score in coop games

	int			game_helpchanged;
	int			helpchanged;
	int			weapon_clip[MAX_WEAPONS];
	int			pistol_mods;
	
	// shared flags for episode
	int			episode_flags;
	int			silencer_shots;

	// number of hired guys
	int			friends;

	// teamplay
	int			team;
	int			bagcash;		// cash being held in bag

	int			hmg_shots;

	// bagman stuff
	float		timeatsafe;		// record how long we've been standing at the safe
	int			friendly_vulnerable;

} client_persistant_t;

// client data that stays across deathmatch respawns
typedef struct
{
	client_persistant_t	coop_respawn;	// what to set client->pers to on a respawn
	int			enterframe;			// level.framenum the client entered the game
	int			score;				// frags, etc
	vec3_t		cmd_angles;			// angles sent over in the last command
	int			game_helpchanged;
	int			helpchanged;

	// teamplay
	int			deposited;		// amount this player has deposited

	// voting system
	char		ban_id;			// so we only let them vote once
	float		last_ban;

} client_respawn_t;

// this structure is cleared on each PutClientInServer(),
// except for 'client->pers'
struct gclient_s
{
	// known to server
	player_state_t	ps;				// communicated by server to clients
	int				ping;

	// private to game
	client_persistant_t	pers;
	client_respawn_t	resp;
	pmove_state_t		old_pmove;	// for detecting out-of-pmove changes

	qboolean	showscores;			// set layout stat
	qboolean	showinventory;		// set layout stat
	qboolean	showhelp;
	qboolean	showhelpicon;

	int			ammo_index;

	int			buttons;
	int			oldbuttons;
	int			latched_buttons;

	qboolean	weapon_thunk;

	gitem_t		*newweapon;

	// sum up damage over an entire frame, so
	// shotgun blasts give a single big kick
	int			damage_armor;		// damage absorbed by armor
	int			damage_parmor;		// damage absorbed by power armor
	int			damage_blood;		// damage taken out of health
	int			damage_flame;		// Ridah, damage from flamethrower
	int			damage_knockback;	// impact damage
	vec3_t		damage_from;		// origin for vector calculation

	float		killer_yaw;			// when dead, look at killer

	weaponstate_t	weaponstate;
	vec3_t		kick_angles;	// weapon kicks
	vec3_t		kick_origin;
	float		v_dmg_roll, v_dmg_pitch, v_dmg_time;	// damage kicks
	float		fall_time, fall_value;		// for view drop on fall
	float		damage_alpha;
	float		bonus_alpha;
	// JOSEPH 6-JAN-99
	int			bonus_alpha_color;
	vec3_t		damage_blend;
	vec3_t		v_angle;			// aiming direction
	float		bobtime;			// so off-ground doesn't change it
	vec3_t		oldviewangles;
	vec3_t		oldvelocity;

	float		next_drown_time;
	int			old_waterlevel;
	int			breather_sound;

	int			machinegun_shots;	// not used anymore

	// animation vars
	int			anim_end;
	int			anim_priority;
	qboolean	anim_duck;
	qboolean	anim_run;
	qboolean	anim_reverse;		// Ridah, for running backwards
	qboolean	anim_slide;			// Ridah, strafing
	float		last_climb_anim_z;	// Z value at last climbing animation change
	int			last_weapontype;	// Ridah, so we change animations when they change weapons

	// powerup timers
	float		quad_framenum;
	float		invincible_framenum;
	float		breather_framenum;
	float		enviro_framenum;

	qboolean	grenade_blew_up;
	float		grenade_time;
	// RAFAEL
	float		quadfire_framenum;
	qboolean	trap_blew_up;
	float		trap_time;
	
	int			weapon_sound;

	float		pickup_msg_time;

	// JOSEPH 2-FEB-99
	float		hud_enemy_talk_time;
	float		hud_self_talk_time;
	// END JOSEPH

	float		flood_locktill;		// locked from talking
	float		flood_when[10];		// when messages were said
	int			flood_whenhead;		// head pointer for when said
	char		flood_lastmsg[160];	// so we don't repeat ourselves (annoying)

	float		respawn_time;		// can respawn when time > this

	qboolean	flashlight;

	// RAFAEL	28-dec-98
	qboolean	gun_noise;
	
	// Ridah	
	float		jetpack_power;		// recharges at 0.5 per second (while not in use), uses at 1.0 per second, maxes at 5.0 seconds of power
	qboolean	jetpack_warned;

// RAFAEL 01-11-99
	qboolean	reload_weapon;
	int			clip_index;

	float		last_wave;

	// chase
	edict_t		*chase_target;
	qboolean	update_chase;
};


// MORAL values
// these effect willingness to fight until death, attack unprovoked, etc
#define	MORAL_RANDOM	0			// engine will assign a random value upon spawning (using formula, so it's the same each time the level loads)
#define	MORAL_COWARD	1
#define	MORAL_HAPPY		2
#define	MORAL_NORMAL	3
#define	MORAL_AGGRESSIVE	4
#define	MORAL_BESERK	5
#define	MORAL_HEROIC	6
#define	MORAL_PSYCOTIC	7

#define	MORAL_MAX		7


#define	ACC_GREEN		0
#define	ACC_POOR		1
#define	ACC_NORMAL		2
#define	ACC_SEASONED	3
#define ACC_VETERAN		4
#define ACC_ELITE		5

#define	GENDER_NONE		0
#define	GENDER_MALE		1
#define	GENDER_FEMALE	2


struct edict_s
{
	entity_state_t	s;
	struct gclient_s	*client;	// NULL if not a player
									// the server expects the first part
									// of gclient_s to be a player_state_t
									// but the rest of it is opaque

	qboolean	inuse;
	int			linkcount;

	// FIXME: move these fields to a server private sv_entity_t
	link_t		area;				// linked to a division node or leaf
	
	int			num_clusters;		// if -1, use headnode instead
	int			clusternums[MAX_ENT_CLUSTERS];
	int			headnode;			// unused if num_clusters != -1
	int			areanum, areanum2;

	//================================

	int			svflags;
	vec3_t		mins, maxs;
	vec3_t		absmin, absmax, size;
	solid_t		solid;
	int			clipmask;
	edict_t		*owner;

	float		voice_pitch;		// used to pitch voices up/down, 1.0 = same, 2.0 = chipmunk (double speed)

	// DO NOT MODIFY ANYTHING ABOVE THIS, THE SERVER
	// EXPECTS THE FIELDS IN THAT ORDER!

	//================================
	int			movetype;
	int			flags;

	char		*model;
	float		freetime;			// sv.time when the object was freed
	
	//
	// only used locally in game, not by server
	//
	char		*message;
	char		*classname;
	int			spawnflags;

	float		timestamp;

	float		angle;			// set in qe3, -1 = up, -2 = down
	char		*target;
	char		*targetname;
	char		*killtarget;
	char		*team;
	char		*pathtarget;
	char		*deathtarget;
	char		*combattarget;
	edict_t		*target_ent;

	float		speed, accel, decel;
	vec3_t		movedir;
	vec3_t		pos1, pos2;

	vec3_t		velocity;
	vec3_t		avelocity;
	int			mass;
	float		air_finished;
	float		gravity;		// per entity gravity multiplier (1.0 is normal)
								// use for lowgrav artifact, flares

	edict_t		*goalentity;
	edict_t		*movetarget;
	float		yaw_speed;
	float		ideal_yaw;

	float		nextthink;
	void		(*prethink) (edict_t *ent);
	void		(*think)(edict_t *self);
	void		(*blocked)(edict_t *self, edict_t *other);	//move to moveinfo?
	void		(*touch)(edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);
	void		(*use)(edict_t *self, edict_t *other, edict_t *activator);
	void		(*pain)(edict_t *self, edict_t *other, float kick, int damage, int mdx_part, int mdx_subobject);
	void		(*die)(edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject);

	float		touch_debounce_time;		// are all these legit?  do we need more/less of them?
	float		pain_debounce_time;
	float		damage_debounce_time;
	float		fly_sound_debounce_time;	//move to clientinfo
	float		last_move_time;

	int			health;
	int			max_health;
	int			gib_health;
	int			deadflag;
	qboolean	show_hostile;

	float		powerarmor_time;

	char		*map;			// target_changelevel

	int			viewheight;		// height above origin where eyesight is determined
	int			takedamage;
	int			dmg;
	int			radius_dmg;
	float		dmg_radius;
	int			sounds;			//make this a spawntemp var?
	int			count;

	edict_t		*chain;
	edict_t		*enemy;
	edict_t		*oldenemy;
	edict_t		*activator;
	edict_t		*groundentity;
	int			groundentity_linkcount;
	edict_t		*teamchain;
	edict_t		*teammaster;

	edict_t		*mynoise;		// can go in client only
	edict_t		*mynoise2;

	int			noise_index;
	int			noise_index2;
	float		volume;
	float		attenuation;

	// timing variables
	float		wait;
	float		delay;			// before firing targets
	float		random;

	float		teleport_time;

	int			watertype;
	int			waterlevel;

	vec3_t		move_origin;
	vec3_t		move_angles;

	// move this to clientinfo?
	int			light_level;

	int			style;			// also used as areaportal number

	gitem_t		*item;			// for bonus items

	// common data blocks
	moveinfo_t		moveinfo;
	cast_info_t		cast_info;

// BEGIN:	Xatrix/Ridah/Navigator/17-mar-1998
	nav_data_t			nav_data;			// CNS-specific data, present for all entities
	nav_build_data_t	*nav_build_data;	// used only by entities that create nodes (clients)
	active_node_data_t	*active_node_data;	// points to the active node data of the current unit
// END:		Xatrix/Ridah/Navigator/17-mar-1998

// JOSEPH 19-MAR-99
	vec3_t  rotate;
    vec3_t  nodeorigin;
    vec3_t  angletarget;
	vec3_t  save_avel;
	vec3_t  savecameraorigin;
	vec3_t  cameraangle;
	vec3_t  cameraorigin;
	vec3_t  cameravel;
	vec3_t  cameravelrel;
	float  duration;	// Ridah, used this for Bike thruster
	float  lastduration;
	float  alphalevel;
	int   avelflag;
	int   durationflag;  // Ridah, used this for Thug reload checking
	int   firstnode;
	int   handleflag;
	int   handle2flag;
	int   doorflag;
	int   firetype;
	int   fallerflag;
	int	  fallingflag; 	
	int   footsteptype;
	int   fxdensity;
	int   currentcash;
	int   pullable;
	int		deadticks;
	int		healspeed;
	int		healtimer;
	int		nokickbackflag;
	int		thudsurf;
	int		thudsnd;
	int		misstime;
	int		missteam;
	int     debugprint;
	int	    onarampage;
	float   timemissing;
	char     *target2;
	edict_t	 *target2_ent;
	edict_t  *missent;
	edict_t  *handle;
	edict_t  *handle2;
	edict_t  *save_self;
	edict_t  *save_other;
	char     *type;
	char	*localteam;
	float	reactdelay;
	char	head;
	int		key; // Door key [-1 = trigger unlocked][0 = unlocked][1+ = key to unlock]
	int     lightit;
	int		option;
	int		noshadow;	
// JOSEPH 17-MAY-99
	int		monsterprop;
	solid_t	 savesolid;
	int     surfacetype;    
	int     pullingflag;
// END JOSEPH	

	// Flamethrower stuff
	char	onfiretime;
	edict_t	*onfireent;		// Ridah, added this so we can record the entity that set us on fire

// Ridah, new AI system
	edict_t		*leader;
	char		*leader_target;				// for setting up AI's to follow other AI's from in the .map
	edict_t		*last_goal;					// set each time we AI_Run(), was the last goal entity (eg. leader or enemy)

	int			order;						// last order issued
	float		order_timestamp;			// time of last order, so only followers that can see us will respond to the order
											// updated when the player issues an order, and when the AI character follows it

	edict_t		*moveout_ent;				// set to the target position when we have issued a "moveout" command

	int			cast_group;					// index of group in which this cast member belongs (set by .map)
	int			character_index;			// our position in the global character array

	float		last_talk_time;
	int			profanity_level;			// each time the profanity button is pressed, this is incremented
	voice_table_t	*last_voice;			// voice_table_t structure of last speech

	int			skin;						// set self->s.skinnum to this upon spawning

	int			moral;						// one of MORAL_* values, set in editor

	char		*guard_target;				// point this to the targetname of the guard_ent this character should guard
	int			guard_radius;				// deeemed to be guarding if inside this radius
	edict_t		*guard_ent;					// guard this if set

	char		*sight_target;				// will head for this entity upon sighting an enemy

	edict_t		*goal_ent;					// if this is set, we should ignore everything apart from an enemy, and head for it
	edict_t		*combat_goalent;			// we should go here instead of going straight to our enemy
	edict_t		*cover_ent;					// entity we are taking cover from
	char		*next_combattarget;
	float		last_getcombatpos;
	float		last_gethidepos;
	float		dont_takecover_time;

	// Ridah, this gets copied to the client.pers->episode_flags for client when they change maps
	int			episode_flags;				// up to 32 bit flags, that represent various things according to the episode being played

	char		*name;						// Special character name eg. "Bernie"
	int			name_index;					// Each name has a name_index (unique for each episode), for fast lookups
	char		*scriptname;				// used to identify hard-coded scripting events

	edict_t		*last_territory_touched;	// set when we touch an "ai_territory" brush, so gangs react when we're in there territory
	float		time_territory_touched;
	int			current_territory;

	edict_t		*response_ent;
	float		last_response_time;
	response_t	last_response;

	edict_t		*start_ent;					// entity marking our starting position

	vec3_t		last_step_pos;				// for AI footsteps
	float		last_step_time;
	float		last_stand_evade;

	int			noroute_count;
	int			last_rval;

	float		fall_height;				// max Z value of last jump
	float		last_offground, last_onground;

	// Ridah, 6-jun-99, so they know where to return to when done hiding
	edict_t		*holdpos_ent;

	// RAFAEL
	int			activate_flags;
	float		biketime;
	int			bikestate;

	// Ridah, Vehicles
	int			vehicle_index;				// references a vehicle_t structure in the global array

	int			acc;				// accuracy variable - troop quality variable	
	int			cal;				// damage caused by weapon - calibur

	char		*art_skins;			// holds 3-digit skins for head, torso and legs

	float		gun_noise_delay;

	float		noise_time;
	vec3_t		noise_pos;
	int			noise_type;
	vec3_t		noise_angles;

	int			gender;				// so we know what sorts of sounds to play, uses GENDER_*

	// combat AI stuff
	float		combat_last_visible;
	vec3_t		combat_last_visible_pos;
	int			combat_flags;

	float		take_cover_time;

	// so we can trigger an event when a character gets below a certain health value
	int			health_threshold;
	char		*health_target;
	int			health_threshold2;
	char		*health_target2;
	int			health_threshold3;
	char		*health_target3;

	float		stand_if_idle_time;		// stand if crouching and not doing much
};

// RAFAEL
#define ACTIVATE_GENERAL  1
#define	ACTIVATE_AND_OPEN 2

// Ridah, used for lightpainting
#define LP_SIZE		(12+2+1+1+1+1)
unsigned char		*lpbuf[0xFFFF];
int					num_lpbuf;


#define WEAPON_MOD_ROF		1
#define WEAPON_MOD_RELOAD	2
#define WEAPON_MOD_DAMAGE	4
#define	WEAPON_MOD_COOLING_JACKET	8

// Ridah, level -> level followers
typedef struct
{
	char	classname[64];
	char	name[64];
	char	art_skins[64];
	int		health, max_health;
	int		skinofs[MAX_MODEL_PARTS][MAX_MODELPART_OBJECTS];	// add to baseskin to get current skin
	int		head;
	float	scale;
	int		spawnflags;
	int		count;		// for the Runt
} follower_t;

#define		MAX_FOLLOWERS	2
follower_t	followers[MAX_FOLLOWERS];
extern int	num_followers;

// Ridah, object bounds data is now stored in a global array for indexing, to accomodate the save/loadgame system
#define	MAX_OBJECT_BOUNDS	2048
extern	int				num_object_bounds;
extern	object_bounds_t	*g_objbnds[MAX_OBJECT_BOUNDS];
