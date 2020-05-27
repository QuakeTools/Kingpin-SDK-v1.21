// *************************************
//	New AI system defines

#define MAX_CAST_GROUPS		16
#define MAX_CHARACTERS		64		// this includes players
#define	DEFAULT_MAX_ATTACK_DISTANCE		1024			// stand and attack enemies within this range
#define	DEFAULT_MAX_SIGHTING_DISTANCE	2048			// can't see things outside this range

#define	FACE_ANIM_DIST		2048	// AI will play an animation to straighten while attacking if beyind this distance

#define	AI_NOT_HOLSTERED_RANGE_1		200
#define	AI_NOT_HOLSTERED_RANGE_2		384
#define	AI_NOT_HOLSTERED_RANGE_3		800

#define	ENEMY_SIGHT_DURATION	3		// enemies sighted "less than this time" ago will be attacked

#define	SPAWNFLAG_IMMEDIATE_FOLLOW_PATH		32

// Cast Memory defines
#define NUM_MEMORY_TYPES		3

#define MEMORY_TYPE_FRIEND		0
#define MEMORY_TYPE_NEUTRAL		1
#define MEMORY_TYPE_ENEMY		2

// Pain orientation checks
#define	ORIENTATION_CENTER		0
#define	ORIENTATION_LEFT		1
#define	ORIENTATION_RIGHT		2

// Player order commands
#define ORDER_MOVE		1
#define ORDER_HOLD		2
#define ORDER_FOLLOWME	3	

// Side Trace
#define	SIDE_RANDOM		0
#define	SIDE_RIGHT		1
#define	SIDE_LEFT		-1

// General movement stuff
#define AI_TOO_CLOSE_DIST	48.0
#define AI_GUARDING_DIST	140.0

// ai flags
#define AI_NOWALK_FACE			0x00000001		// don't walk when turning to face
#define AI_TEMP_STAND_GROUND	0x00000002
#define	AI_NO_TALK				0x00000004		// prevent this character from talking (good for waiting in ambush)
#define	AI_GOAL_RUN				0x00000008		// set this for entities that the AI should run towards
#define	AI_FACE_ATTACK			0x00000010		// always face the enemy when attacking
#define	AI_MOVEOUT				0x00000020
#define	AI_MELEE				0x00000040		// this character can only do melee attacks
#define AI_GRENADE_GUY			0x00000080
#define	AI_DUCKATTACK			0x00000100		// only ducking for attack
#define	AI_GOAL_IGNOREENEMY		0x00000200
#define AI_NOSTEP				0x00000400
#define	AI_RELOAD				0x00000800		// need to reload before we can fire again
#define	AI_TAKECOVER_IGNOREHEALTH	0x00001000	// don't do health checks to see if we should resume attacking
#define	AI_GOALENT_MANUAL_CLEAR	0x00002000		// set this on the goal_ent if we should NOT set our ->goal_ent = NULL when we get there
#define	AI_DOKEY				0x00004000
#define	AI_IMMORTAL				0x00008000
#define AI_REPEAT_TALK_JESTURE	0x00010000		// keep making talking jesture
#define AI_SKILL_LADDER			0x00020000
#define AI_HOLD_POSITION		0x00040000
#define AI_TAKE_COVER			0x00080000
#define	AI_IGNORE_ENEMY			0x00100000
#define	AI_FASTWALK				0x00200000		// characters will WALK at twice the speed (including faster animation)
#define	AI_PLAYERCLIP			0x00400000		// uses PLAYERCLIP bounding instead of MONSTERCLIP
#define	AI_NO_TAKE_COVER		0x00800000		// don't take cover from anything
#define	AI_ADJUSTPITCH			0x01000000		// used for dogs so they angle up for stairs, ramps, etc
#define AI_TALK					0x02000000		// stop "avoid walking" when we're facing the character
#define	AI_SIDE_ATTACK			0x04000000
#define	AI_TURN_BLOCKED			0x08000000
#define AI_RUN_LIKE_HELL		0x10000000
#define AI_RUSH_THE_PLAYER		0x20000000
#define AI_HEARD_GUN_SHOT		0x40000000
#define AI_SIT_TALK				0x80000000


typedef enum
{
	resp_yes,
	resp_no
} response_t;


#define	STATE_NORMAL		0		// each character does their own thing
#define	STATE_FLEE			1		// abort attack, everyone flee
#define	STATE_CHARGE		2		// berzerk at charge_ent

// cast_group_t holds information relating to each team in the game, including fighting formations, etc

typedef struct
{
	int		state;
	int		charge_ent;				// index into g_edicts[]
} cast_group_t;

// Memory flags
#define	MEMORY_PERSONAL_OPINION		0x00000001		// set this if we have a personal vendetta on the character, which is not necessarily that of the group
#define	MEMORY_CONFIDENTIAL			0x00000002		// only share this information to a fellow group member, or under extreme conditions (like we are neutral and are bribed, or we are tortured)
#define MEMORY_HOSTILE_ENEMY		0x00000004		// attack upon sighting this character
#define	MEMORY_ASSHOLE				0x00000008		// we don't like this person, but they're not an enemy (just effects speech)
#define MEMORY_LASTWARNING			0x00000010		// we want to give a final warning to the player before we become hostile
#define	MEMORY_UPSET				0x00000020		// will use specific upset speech

#define MEMORY_AFRAID				0x00000040
#define MEMORY_TAUNT				0x00000080
#define	MEMORY_WARNED_BACKOFF		0x00000100		// we've warned this person to backoff already

#define	MEMORY_HIRE_FIRST_TIME		0x00000200
#define MEMORY_HIRE_ASK				0x00000400
#define MEMORY_HIRED				0x00000800
#define	MEMORY_NO_TALK				0x00001000		// don't talk to this person
#define	MEMORY_STARTED_ATTACK		0x00002000		// so AI friends only attack enemies that are attacking (and not evading)

// cast_memory_t stores a particular character's memory and opinion of another cast member, 
// for which it is aware of (has either seen, or is associated with)
typedef struct cast_memory_s
{
	int			cast_ent;		// "other" character index in the g_edicts[]

	vec3_t		last_known_origin;
	int			flags;			// deafult to 0, set various flags under certain conditions
	int			memory_type;	// one of MEMORY_TYPE_* constants, defines which cast_memory type this is in, for fast references

	float		timestamp;		// time that this information was updated 
											// (when gaining information from another character, 
											// this information is simply copied across, so we 
											// don't share information infinitely)
	float		timestamp_dist;	// distance at last sighting

	float		not_holstered_attack_time;
	float		ignore_time;	// pretend we can't see them until this time

	byte		inc;			// this can be used for anything, like counting the times we've warned this person, etc

	void		(*response)(edict_t *self, edict_t *other, response_t response);		// when a player talks to us, call this response routine

	short		last_known_closest_node;	// so we can speed things up

	struct cast_memory_s
				*next, *prev;
} cast_memory_t;

// *************************************

// New Procedure defines

// g_ai.c

void ai_onfire_run( edict_t *self, float dist );

void ai_sidestep( edict_t *self, float dist);

void AI_CheckEvade( edict_t *self );

qboolean AI_ClearSight ( edict_t *self, edict_t *other, qboolean boxtrace );

int AI_SideTrace( edict_t *self, float dist, float inyaw, int side );
int AI_YawTrace( edict_t *self, float dist, float inyaw );

void AI_MoveToPlatCenter( edict_t *self, edict_t *plat);
qboolean AI_TooClose(edict_t *self, edict_t *goal);
void AI_CheckStillInair(edict_t *self);
qboolean AI_CheckAttack(edict_t *self);
void AI_StartAttack(edict_t *self, edict_t *enemy);

void AI_StartRun( edict_t *self );

void AI_CheckStillClimbingLadder( edict_t *self );

void AI_EndAttack(edict_t *self);
void AI_EndJump(edict_t *self);
void AI_EndDeath(edict_t *self);
void AI_EndRun(edict_t *self);

void AI_End_CrouchStand_Down(edict_t *self);
void AI_End_CrouchStand_Up(edict_t *self);

int AI_GetOrientation( edict_t *self, edict_t *other );
qboolean AI_CheckTalk( edict_t *self );
void AI_TalkThink( edict_t *self, qboolean ismale );

qboolean ValidBoxAtLoc(vec3_t org, vec3_t mins, vec3_t maxs, edict_t *ignore, int mask);

qboolean AI_CheckTakeCover( edict_t *self );
qboolean AI_ForceTakeCover( edict_t *self, edict_t *enemy, qboolean ignorehealth );

// g_ai_fight.c

qboolean AI_Goto_CombatTarget( edict_t *self );
qboolean AI_BeginAttack( edict_t *self );
qboolean AI_HasLeaderButGoForEnemy( edict_t *self, edict_t *enemy );
void AI_CheckMakeEnemy( edict_t *self, edict_t *other );
void AI_AvoidDangerousEntity( edict_t *ent );

// g_ai_memory.c

qboolean AddCharacterToGame(edict_t *self);
void AI_RemoveFromMemory ( edict_t *self, cast_memory_t *memory );
void AI_AddToMemory ( edict_t *self, cast_memory_t *memory, int memory_type );
void AI_InitMemory( edict_t *self );
void AI_UnloadCastMemory (edict_t *self);

void AI_ShareEnemies ( edict_t *self, edict_t *other );
void AI_RecordSighting(edict_t *src, edict_t *dest, float dist);
void AI_UpdateCharacterMemories( int max_iterations );
void AI_MakeEnemy ( edict_t *self, edict_t *other, int memory_flags );

// g_ai_ents.c

void AI_Ent_droptofloor ( edict_t *self );
void ai_button_think (edict_t *self);
void ai_button_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf);



qboolean directly_infront_angle (vec3_t ang1, edict_t *self, edict_t *other);


