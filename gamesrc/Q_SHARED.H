// q_shared.h -- included first by ALL program modules

#define		DEMO	0	// enable this when compiling a demo release

// RIDAH, DISABLE THIS BEFORE RELEASE!
#define USE_OLD_CHECKSUM

#ifdef _WIN32
// unknown pragmas are SUPPOSED to be ignored, but....
#pragma warning(disable : 4244)     // MIPS
#pragma warning(disable : 4136)     // X86
#pragma warning(disable : 4051)     // ALPHA

#pragma warning(disable : 4018)     // signed/unsigned mismatch
#pragma warning(disable : 4305)		// truncation from const double to float

#endif

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#if (defined _M_IX86 || defined __i386__) && !defined C_ONLY
#define id386	1
#else
#define id386	0
#endif

#if defined _M_ALPHA && !defined C_ONLY
#define idaxp	1
#else
#define idaxp	0
#endif

typedef unsigned char 		byte;
typedef enum {false, true}	qboolean;


#ifndef NULL
#define NULL ((void *)0)
#endif


#define	RANDOM	( ((float)(rand()) / RAND_MAX)*2.0 - 1.0)

// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_STRING_TOKENS	80		// max tokens resulting from Cmd_TokenizeString
#define	MAX_TOKEN_CHARS		128		// max length of an individual token

#define	MAX_QPATH			64		// max length of a quake game pathname
#define	MAX_OSPATH			128		// max length of a filesystem pathname

//
// per-level limits
//
#define	MAX_CLIENTS			256		// absolute limit
#define	MAX_EDICTS			2048	// must change protocol to increase more
#define	MAX_LIGHTSTYLES		256
#define	MAX_MODELS			256		// these are sent over the net as bytes
#define	MAX_SOUNDS			384		// so they cannot be blindly increased
#define	MAX_IMAGES			256
#define	MAX_ITEMS			256
#define MAX_LIGHTFLARES		128
#define MAX_JUNIOR_STRINGS	512
#define MAX_GENERAL			(MAX_CLIENTS*2)	// general config strings

// game print flags
#define	PRINT_LOW			0		// pickup messages
#define	PRINT_MEDIUM		1		// death messages
#define	PRINT_HIGH			2		// critical messages
#define	PRINT_CHAT			3		// chat messages



#define	ERR_FATAL			0		// exit the entire game with a popup window
#define	ERR_DROP			1		// print to console and disconnect from game
#define	ERR_DISCONNECT		2		// don't kill server

#define	PRINT_ALL			0
#define PRINT_DEVELOPER		1		// only print when "developer 1"
#define PRINT_ALERT			2		


// destination class for gi.multicast()
typedef enum
{
MULTICAST_ALL,
MULTICAST_PHS,
MULTICAST_PVS,
MULTICAST_ALL_R,
MULTICAST_PHS_R,
MULTICAST_PVS_R
} multicast_t;


/*
==============================================================

MATHLIB

==============================================================
*/

typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec5_t[5];

typedef	int	fixed4_t;
typedef	int	fixed8_t;
typedef	int	fixed16_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

struct cplane_s;

extern vec3_t vec3_origin;

#define	nanmask (255<<23)

#define	IS_NAN(x) (((*(int *)&x)&nanmask)==nanmask)

// microsoft's fabs seems to be ungodly slow...
//float Q_fabs (float f);
//#define	fabs(f) Q_fabs(f)
#if !defined C_ONLY && !defined __linux__
extern long Q_ftol( float f );
#else
#define Q_ftol( f ) ( long ) (f)
#endif

void vectoangles (vec3_t value1, vec3_t angles);

// JOSEPH 6-NOV-98
#ifdef _WIN32
_inline vec_t DotProduct(x,y)
{
  float dotprod;
  _asm
  {
    mov     ecx, x
    mov     eax, y

    ;optimized dot product; 15 cycles
    fld dword ptr   [eax+0]     ;starts & ends on cycle 0
    fmul dword ptr  [ecx+0]     ;starts on cycle 1
    fld dword ptr   [eax+4]     ;starts & ends on cycle 2
    fmul dword ptr  [ecx+4]     ;starts on cycle 3
    fld dword ptr   [eax+8]     ;starts & ends on cycle 4
    fmul dword ptr  [ecx+8]     ;starts on cycle 5
    fxch            st(1)       ;no cost
    faddp           st(2),st(0) ;starts on cycle 6, stalls for cycles 7-8
    faddp           st(1),st(0) ;starts on cycle 9, stalls for cycles 10-12
    fstp dword ptr  [dotprod]    ;starts on cycle 13, ends on cycle 14
  }
  return dotprod;
}
#else
#define DotProduct(x,y)			(x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#endif
// END JOSEPH

#define VectorSubtract(a,b,c)	(c[0]=a[0]-b[0],c[1]=a[1]-b[1],c[2]=a[2]-b[2])
#define VectorAdd(a,b,c)		(c[0]=a[0]+b[0],c[1]=a[1]+b[1],c[2]=a[2]+b[2])
#define VectorCopy(a,b)			(b[0]=a[0],b[1]=a[1],b[2]=a[2])
#define VectorClear(a)			(a[0]=a[1]=a[2]=0)
#define VectorNegate(a,b)		(b[0]=-a[0],b[1]=-a[1],b[2]=-a[2])
#define VectorSet(v, x, y, z)	(v[0]=(x), v[1]=(y), v[2]=(z))

void VectorMA (vec3_t veca, float scale, vec3_t vecb, vec3_t vecc);

// just in case you do't want to use the macros
vec_t _DotProduct (vec3_t v1, vec3_t v2);
void _VectorSubtract (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorAdd (vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorCopy (vec3_t in, vec3_t out);

void ClearBounds (vec3_t mins, vec3_t maxs);
void AddPointToBounds (vec3_t v, vec3_t mins, vec3_t maxs);
int VectorCompare (vec3_t v1, vec3_t v2);
vec_t VectorLength (vec3_t v);
float VectorDistance(vec3_t vec1, vec3_t vec2);
void CrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);
vec_t VectorNormalize (vec3_t v);		// returns vector length
vec_t VectorNormalize2 (vec3_t v, vec3_t out);
void VectorInverse (vec3_t v);
void VectorScale (vec3_t in, vec_t scale, vec3_t out);
int Q_log2(int val);

void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms (float in1[3][4], float in2[3][4], float out[3][4]);

void AngleVectors (vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *plane);
float	anglemod(float a);
float LerpAngle (float a1, float a2, float frac);
// Ridah
float AngleDiff (float a2, float a1);

#ifdef WIN32
#define BOX_ON_PLANE_SIDE(emins, emaxs, p)	\
	(((p)->type < 3)?						\
	(										\
		((p)->dist <= (emins)[(p)->type])?	\
			1								\
		:									\
		(									\
			((p)->dist >= (emaxs)[(p)->type])?\
				2							\
			:								\
				3							\
		)									\
	)										\
	:										\
		BoxOnPlaneSide( (emins), (emaxs), (p)))
#endif

void ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal );
void PerpendicularVector( vec3_t dst, const vec3_t src );
void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );


//=============================================

char *COM_SkipPath (char *pathname);
void COM_StripExtension (char *in, char *out);
void COM_FileBase (char *in, char *out);
void COM_FilePath (char *in, char *out);
void COM_DefaultExtension (char *path, char *extension);

char *COM_Parse (char **data_p);
char *COM_Parse256 (char **data_p);
// data is an in/out parm, returns a parsed out token

void Com_sprintf (char *dest, int size, char *fmt, ...);

void Com_PageInMemory (byte *buffer, int size);

//=============================================

// portable case insensitive compare
int Q_stricmp (char *s1, char *s2);
int Q_strcasecmp (char *s1, char *s2);
int Q_strncasecmp (char *s1, char *s2, int n);

//=============================================

short	BigShort(short l);
short	LittleShort(short l);
int		BigLong (int l);
int		LittleLong (int l);
float	BigFloat (float l);
float	LittleFloat (float l);

void	Swap_Init (void);
char	*va(char *format, ...);

char *kp_strlwr( char *name );

//=============================================

//
// key / value info strings
//
#define	MAX_INFO_KEY		64
#define	MAX_INFO_VALUE		64
#define	MAX_INFO_STRING		512

char *Info_ValueForKey (char *s, char *key);
void Info_RemoveKey (char *s, char *key);
void Info_SetValueForKey (char *s, char *key, char *value);
qboolean Info_Validate (char *s);

/*
==============================================================

SYSTEM SPECIFIC

==============================================================
*/

extern	int	curtime;		// time returned by last Sys_Milliseconds

int		Sys_Milliseconds (void);
void	Sys_Mkdir (char *path);

// large block stack allocation routines
void	*Hunk_Begin (int maxsize);
void	*Hunk_Alloc (int size);
void	Hunk_Free (void *buf);
int		Hunk_End (void);

// directory searching
#define SFF_ARCH    0x01
#define SFF_HIDDEN  0x02
#define SFF_RDONLY  0x04
#define SFF_SUBDIR  0x08
#define SFF_SYSTEM  0x10

/*
** pass in an attribute mask of things you wish to REJECT
*/
char	*Sys_FindFirst (char *path, unsigned musthave, unsigned canthave );
char	*Sys_FindNext ( unsigned musthave, unsigned canthave );
void	Sys_FindClose (void);


// this is only here so the functions in q_shared.c and q_shwin.c can link
void Sys_Error (char *error, ...);
void Com_Printf (char *msg, ...);


/*
==========================================================

CVARS (console variables)

==========================================================
*/

#ifndef CVAR
#define	CVAR

#define	CVAR_ARCHIVE	1	// set to cause it to be saved to vars.rc
#define	CVAR_USERINFO	2	// added to userinfo  when changed
#define	CVAR_SERVERINFO	4	// added to serverinfo when changed
#define	CVAR_NOSET		8	// don't allow change from console at all,
							// but can be set from the command line
#define	CVAR_LATCH		16	// save changes until server restart

// nothing outside the Cvar_*() functions should modify these fields!
typedef struct cvar_s
{
	char		*name;
	char		*string;
	char		*latched_string;	// for CVAR_LATCH vars
	int			flags;
	qboolean	modified;	// set each time the cvar is changed
	float		value;
	struct cvar_s *next;
} cvar_t;

#endif		// CVAR

/*
==============================================================

COLLISION DETECTION

==============================================================
*/

// lower bits are stronger, and will eat weaker brushes completely
#define	CONTENTS_SOLID			1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			2		// translucent, but not watery
#define	CONTENTS_AUX			4
#define	CONTENTS_LAVA			8
#define	CONTENTS_SLIME			16
#define	CONTENTS_WATER			32
#define	CONTENTS_MIST			64
// JOSEPH 
#define CONTENTS_ALPHA			128
#define	LAST_VISIBLE_CONTENTS	128
// END JOSEPH
// remaining contents are non-visible, and don't eat brushes

#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEADMONSTER	0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000


#define	SURF_LIGHT		0x1		// value will hold the light strength

#define	SURF_SLICK		0x2		// effects game physics

#define	SURF_SKY		0x4		// don't draw, but add to skybox
#define	SURF_WARP		0x8		// turbulent water warp
#define	SURF_TRANS33	0x10
#define	SURF_TRANS66	0x20
#define	SURF_FLOWING	0x40	// scroll towards angle
#define	SURF_NODRAW		0x80	// don't bother referencing the texture
#define	SURF_BURNT		0x100	// Ridah, used for rendering, marks this surface as having been burnt or charred
// JOSEPH 29-DEC-98
#define	SURF_SPECULAR		0x400		// Ridah, shows specular lighting from light flares
#define	SURF_DIFFUSE		0x800		// Ridah, used with specular lighting, makes it bigger and less intense
// END JOSEPH

// JOSEPH 26-JAN-99-C
#define SURF_ALPHA		0x1000	// wire fence effect flag
#define SURF_WATER      0x80000
#define SURF_CONCRETE	0x100000
#define SURF_FABRIC		0x200000
#define SURF_GRAVEL		0x400000
#define SURF_METAL		0x800000
#define SURF_METAL_L	0x1000000
#define SURF_SNOW		0x2000000
#define SURF_TILE		0x4000000
#define SURF_WOOD		0x8000000
// END JOSEPH

// Ridah
#define SURF_REFLECT_FAKE	0x10000000		// Ridah, uses fast (fake) reflections
#define SURF_REFLECT_LIGHT	0x20000000		// Ridah, only reflects SURF_LIGHT surfaces

// content masks
#define	MASK_ALL				(-1)
#define	MASK_SOLID				(CONTENTS_SOLID|CONTENTS_WINDOW)
#define	MASK_PLAYERSOLID		(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define	MASK_DEADSOLID			(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW)
#define	MASK_MONSTERSOLID		(CONTENTS_SOLID|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define	MASK_WATER				(CONTENTS_WATER|CONTENTS_LAVA|CONTENTS_SLIME)
#define	MASK_OPAQUE				(CONTENTS_SOLID|CONTENTS_SLIME|CONTENTS_LAVA)
#define	MASK_SHOT				(CONTENTS_SOLID|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEADMONSTER)
#define MASK_CURRENT			(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
// JOSEPH 
#define MASK_ALPHA				(CONTENTS_ALPHA)
// END JOSEPH


// gi.BoxEdicts() can return a list of either solid or trigger entities
// FIXME: eliminate AREA_ distinction?
#define	AREA_SOLID		1
#define	AREA_TRIGGERS	2


// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
typedef struct cplane_s
{
	vec3_t	normal;
	float	dist;
	byte	type;			// for fast side tests
	byte	signbits;		// signx + (signy<<1) + (signz<<1)
	byte	pad[2];
	// Ridah
	int		spec_updateframe;	// so we only do each plane once
	int		spec_updateframe_backface;
	byte	spec_render, spec_render_back;
} cplane_t;

// structure offset for asm code
#define CPLANE_NORMAL_X			0
#define CPLANE_NORMAL_Y			4
#define CPLANE_NORMAL_Z			8
#define CPLANE_DIST				12
#define CPLANE_TYPE				16
#define CPLANE_SIGNBITS			17
#define CPLANE_PAD0				18
#define CPLANE_PAD1				19

typedef struct cmodel_s
{
	vec3_t		mins, maxs;
	vec3_t		origin;		// for sounds or lights
	int			headnode;
} cmodel_t;

typedef struct csurface_s
{
	char		name[16];
	int			flags;
	int			value;
} csurface_t;

typedef struct mapsurface_s  // used internally due to name len probs //ZOID
{
	csurface_t	c;
	char		rname[32];
} mapsurface_t;

// a trace is returned when a box is swept through the world
typedef struct
{
	qboolean	allsolid;	// if true, plane is not valid
	qboolean	startsolid;	// if true, the initial point was in a solid area
	float		fraction;	// time completed, 1.0 = didn't hit anything
	vec3_t		endpos;		// final position
	cplane_t	plane;		// surface normal at impact
	csurface_t	*surface;	// surface hit
	int			contents;	// contents on other side of surface hit
	struct edict_s	*ent;		// not set by CM_*() functions
} trace_t;



// pmove_state_t is the information necessary for client side movement
// prediction
typedef enum 
{
	// can accelerate and turn
	PM_NORMAL,
	PM_NORMAL_WITH_JETPACK,

	// Ridah, vehicles
	PM_HOVERCAR,			// flying hovercar
	PM_HOVERCAR_GROUND,		// grounded hovercar
	PM_BIKE,				// motorcycle
	PM_CAR,					// uses vehicle code
	// done.

	PM_SPECTATOR,
	// no acceleration or turning
	PM_DEAD,
	PM_GIB,		// different bounding box
	PM_FREEZE
} pmtype_t;

// pmove->pm_flags
#define	PMF_DUCKED			1
#define	PMF_JUMP_HELD		2
#define	PMF_ON_GROUND		4
#define	PMF_TIME_WATERJUMP	8	// pm_time is waterjump
#define	PMF_TIME_LAND		16	// pm_time is time before rejump
#define	PMF_TIME_TELEPORT	32	// pm_time is non-moving time
#define PMF_NO_PREDICTION	64	// temporarily disables prediction (used for grappling hook)

// Ridah, chasecam
#define PMF_CHASECAM		128

// this structure needs to be communicated bit-accurate
// from the server to the client to guarantee that
// prediction stays in sync, so no floats are used.
// if any part of the game code modifies this struct, it
// will result in a prediction error of some degree.
typedef struct
{
	pmtype_t	pm_type;

	short		origin[3];		// 12.3
	short		velocity[3];	// 12.3
	byte		pm_flags;		// ducked, jump_held, etc
	byte		pm_time;		// each unit = 8 ms
	short		gravity;
	short		delta_angles[3];	// add to command angles to get view direction
									// changed by spawns, rotating objects, and teleporters

	byte		runscale;		// Ridah, so we can mess with the running speed
} pmove_state_t;


//
// button bits
//
#define	BUTTON_ATTACK		1
#define	BUTTON_USE			2
#define	BUTTON_ACTIVATE		4			// Joseph

#define	BUTTON_ANY			128			// any key whatsoever


// usercmd_t is sent to the server each client frame
typedef struct usercmd_s
{
	byte	msec;
	byte	buttons;
	short	angles[3];
	short	forwardmove, sidemove, upmove;
	byte	impulse;		// remove?
	byte	lightlevel;		// light level the player is standing on
} usercmd_t;


#define	MAXTOUCH	32
typedef struct
{
	// state (in / out)
	pmove_state_t	s;

	// command (in)
	usercmd_t		cmd;
	qboolean		snapinitial;	// if s has been changed outside pmove

	// results (out)
	int			numtouch;
	struct edict_s	*touchents[MAXTOUCH];

	vec3_t		viewangles;			// clamped
	float		viewheight;

	vec3_t		mins, maxs;			// bounding box size

	struct edict_s	*groundentity;
	int			watertype;
	int			waterlevel;

	// callbacks to test the world
	trace_t		(*trace) (vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end);
	int			(*pointcontents) (vec3_t point);

	// JOSEPH 1-SEP-98
	int			footsteptype;

	// Ridah, bike collisions
	int			wall_collision;

} pmove_t;


// entity_state_t->effects
// Effects are things handled on the client side (lights, particles, frame animations)
// that happen constantly on the given entity.
// An entity that has effects will be sent to the client
// even if it has a zero index model.
#define	EF_ROTATE			0x00000001		// rotate (bonus items)
#define	EF_GIB				0x00000002		// leave a trail
#define	EF_BLASTER			0x00000008		// redlight + trail
#define	EF_ROCKET			0x00000010		// redlight + trail
#define	EF_GRENADE			0x00000020
#define	EF_HYPERBLASTER		0x00000040
#define	EF_BFG				0x00000080
#define EF_COLOR_SHELL		0x00000100
#define EF_POWERSCREEN		0x00000200
#define	EF_ANIM01			0x00000400		// automatically cycle between frames 0 and 1 at 2 hz
#define	EF_ANIM23			0x00000800		// automatically cycle between frames 2 and 3 at 2 hz
#define EF_ANIM_ALL			0x00001000		// automatically cycle through all frames at 2hz
#define EF_ANIM_ALLFAST		0x00002000		// automatically cycle through all frames at 10hz
#define	EF_FLIES			0x00004000
#define	EF_QUAD				0x00008000
#define	EF_PENT				0x00010000
#define	EF_TELEPORTER		0x00020000		// particle fountain
#define EF_FLAG1			0x00040000
#define EF_FLAG2			0x00080000
#define EF_IONRIPPER		0x00100000
#define EF_FLASHLIGHT		0x00200000
#define	EF_BLUEHYPERBLASTER 0x00400000
#define EF_SPINNINGLIGHTS	0x00800000
#define EF_PLASMA			0x01000000
#define EF_TRAP				0x02000000
#define EF_REFL				0x04000000
#define	EF_FLAMETHROWER		0x08000000
#define EF_ANIM_ALLFAST_NEW	0x10000000		// automatically cycle through all frames at 10hz

// entity_state_t->renderfx flags
#define	RF_MINLIGHT			1		// allways have some light (viewmodel)
#define	RF_VIEWERMODEL		2		// don't draw through eyes, only mirrors
#define	RF_WEAPONMODEL		4		// only draw through eyes
#define	RF_FULLBRIGHT		8		// allways draw full intensity
#define	RF_DEPTHHACK		16		// for view weapon Z crunching
#define	RF_TRANSLUCENT		32
#define	RF_FRAMELERP		64
#define RF_BEAM				128
#define	RF_CUSTOMSKIN		256		// skin is an index in image_precache
#define	RF_GLOW				512		// pulse lighting for bonus items
#define RF_SHELL_RED		1024
#define	RF_SHELL_GREEN		2048
#define RF_SHELL_BLUE		4096
#define RF_REFL_MAP			8192    // (1<<13)
#define	RF_FACING			16384	// (1<<14)
#define RF_FACINGUP			32768	// (1<<15)
// JOSEPH 21-JAN-99
#define	RF_DIMLIGHT		    (1<<16) // allways draw dim light intensity
// END JOSEPH

// JOSEPH 20-MAY-99
// 1 - 16 must check that RF2_PASSLIGHT is not set 
#define RF2_FLAMESHOOTER		1
#define RF2_FLAMESHOOTER_MOD	2	
#define RF2_MODULUS_FRAME		4	// if the frame is higher than the max, just do a MODULUS on it
#define RF2_8					8
#define RF2_16					16
// END JOSEPH

#define RF2_ONLY_PARENTAL_LOCKED			32		// Ridah, this entity is visible only to clients who have the parental lock ENABLED (ie. if a player is gibbed, the body remains in the game, but is only visible to client's who can't see the gibs, since they are parental locked)
#define RF2_SCALE50			64		// .5
#define	RF2_SCALE25			128		// .25

#define RF2_MONEYBAG		256		// used for Teamplay, shows a moneybag on the player's back, automatically animated
#define	RF2_SURF_ALPHA		512
#define	RF2_DIR_LIGHTS		1024	// Uses new directional lighting code
#define	RF2_FLAMETHROWER	2048	// client-side flamthrower effects (damage done in game code)
#define RF2_PASSALPHA		4096
#define	RF2_NOSHADOW		8192
#define	RF2_BEAM2			16384
#define	RF2_PASSLIGHT		32768

	
// player_state_t->refdef flags
#define	RDF_UNDERWATER		1		// warp the screen as apropriate
#define RDF_NOWORLDMODEL	2		// used for player configuration screen

#define	RDF_PAUSED			4		// Ridah, so renderer knows if it's paused

// RAFAEL
#define	RDF_NOLERP			8
#define RDF_SKINPLUS		16
#define RDF_SKINPLUSPLUS	32

// JOSEPH 14-JAN-99
#define RDF_NOWORLDMODELALPHA 64	// used for inventory screen

//
// muzzle flashes / player effects
//
#define	MZ_BLASTER			0
#define MZ_MACHINEGUN		1
#define	MZ_SHOTGUN			2
#define	MZ_CHAINGUN1		3
#define	MZ_CHAINGUN2		4
#define	MZ_CHAINGUN3		5
#define	MZ_RAILGUN			6
#define	MZ_ROCKET			7
#define	MZ_GRENADE			8
#define	MZ_LOGIN			9
#define	MZ_LOGOUT			10
#define	MZ_RESPAWN			11
#define	MZ_BFG				12
#define	MZ_SSHOTGUN			13
#define	MZ_HYPERBLASTER		14
#define	MZ_ITEMRESPAWN		15
// RAFAEL
#define MZ_IONRIPPER		16
#define MZ_BLUEHYPERBLASTER 17
#define MZ_PHALANX			18
#define	MZ_PISTOL			19


#define MZ_BLACKJACK_SWING	20
#define MZ_BLACKJACK_HIT	21

#define MZ_SPISTOL			22
#define MZ_PISTOL_DAMAGE_MOD 23

// JOSEPH 19-JAN-99
#define MZ_CROWBAR_SWING	24
#define MZ_CROWBAR_HIT		25
// END JOSEPH

#define MZ_BARMACHINEGUN	26
#define MZ_BARMACHINEGUN2	27

#define MZ_SILENCED			128		// bit flag ORed with one of the above numbers

//
// monster muzzle flashes
//
#define MZ2_TANK_BLASTER_1				1
#define MZ2_TANK_BLASTER_2				2
#define MZ2_TANK_BLASTER_3				3
#define MZ2_TANK_MACHINEGUN_1			4
#define MZ2_TANK_MACHINEGUN_2			5
#define MZ2_TANK_MACHINEGUN_3			6
#define MZ2_TANK_MACHINEGUN_4			7
#define MZ2_TANK_MACHINEGUN_5			8
#define MZ2_TANK_MACHINEGUN_6			9
#define MZ2_TANK_MACHINEGUN_7			10
#define MZ2_TANK_MACHINEGUN_8			11
#define MZ2_TANK_MACHINEGUN_9			12
#define MZ2_TANK_MACHINEGUN_10			13
#define MZ2_TANK_MACHINEGUN_11			14
#define MZ2_TANK_MACHINEGUN_12			15
#define MZ2_TANK_MACHINEGUN_13			16
#define MZ2_TANK_MACHINEGUN_14			17
#define MZ2_TANK_MACHINEGUN_15			18
#define MZ2_TANK_MACHINEGUN_16			19
#define MZ2_TANK_MACHINEGUN_17			20
#define MZ2_TANK_MACHINEGUN_18			21
#define MZ2_TANK_MACHINEGUN_19			22
#define MZ2_TANK_ROCKET_1				23
#define MZ2_TANK_ROCKET_2				24
#define MZ2_TANK_ROCKET_3				25

#define MZ2_INFANTRY_MACHINEGUN_1		26
#define MZ2_INFANTRY_MACHINEGUN_2		27
#define MZ2_INFANTRY_MACHINEGUN_3		28
#define MZ2_INFANTRY_MACHINEGUN_4		29
#define MZ2_INFANTRY_MACHINEGUN_5		30
#define MZ2_INFANTRY_MACHINEGUN_6		31
#define MZ2_INFANTRY_MACHINEGUN_7		32
#define MZ2_INFANTRY_MACHINEGUN_8		33
#define MZ2_INFANTRY_MACHINEGUN_9		34
#define MZ2_INFANTRY_MACHINEGUN_10		35
#define MZ2_INFANTRY_MACHINEGUN_11		36
#define MZ2_INFANTRY_MACHINEGUN_12		37
#define MZ2_INFANTRY_MACHINEGUN_13		38

#define MZ2_SOLDIER_BLASTER_1			39
#define MZ2_SOLDIER_BLASTER_2			40
#define MZ2_SOLDIER_SHOTGUN_1			41
#define MZ2_SOLDIER_SHOTGUN_2			42
#define MZ2_SOLDIER_MACHINEGUN_1		43
#define MZ2_SOLDIER_MACHINEGUN_2		44

#define MZ2_GUNNER_MACHINEGUN_1			45
#define MZ2_GUNNER_MACHINEGUN_2			46
#define MZ2_GUNNER_MACHINEGUN_3			47
#define MZ2_GUNNER_MACHINEGUN_4			48
#define MZ2_GUNNER_MACHINEGUN_5			49
#define MZ2_GUNNER_MACHINEGUN_6			50
#define MZ2_GUNNER_MACHINEGUN_7			51
#define MZ2_GUNNER_MACHINEGUN_8			52
#define MZ2_GUNNER_GRENADE_1			53
#define MZ2_GUNNER_GRENADE_2			54
#define MZ2_GUNNER_GRENADE_3			55
#define MZ2_GUNNER_GRENADE_4			56

#define MZ2_CHICK_ROCKET_1				57

#define MZ2_FLYER_BLASTER_1				58
#define MZ2_FLYER_BLASTER_2				59

#define MZ2_MEDIC_BLASTER_1				60

#define MZ2_GLADIATOR_RAILGUN_1			61

#define MZ2_HOVER_BLASTER_1				62

#define MZ2_ACTOR_MACHINEGUN_1			63

#define MZ2_SUPERTANK_MACHINEGUN_1		64
#define MZ2_SUPERTANK_MACHINEGUN_2		65
#define MZ2_SUPERTANK_MACHINEGUN_3		66
#define MZ2_SUPERTANK_MACHINEGUN_4		67
#define MZ2_SUPERTANK_MACHINEGUN_5		68
#define MZ2_SUPERTANK_MACHINEGUN_6		69
#define MZ2_SUPERTANK_ROCKET_1			70
#define MZ2_SUPERTANK_ROCKET_2			71
#define MZ2_SUPERTANK_ROCKET_3			72

#define MZ2_BOSS2_MACHINEGUN_L1			73
#define MZ2_BOSS2_MACHINEGUN_L2			74
#define MZ2_BOSS2_MACHINEGUN_L3			75
#define MZ2_BOSS2_MACHINEGUN_L4			76
#define MZ2_BOSS2_MACHINEGUN_L5			77
#define MZ2_BOSS2_ROCKET_1				78
#define MZ2_BOSS2_ROCKET_2				79
#define MZ2_BOSS2_ROCKET_3				80
#define MZ2_BOSS2_ROCKET_4				81

#define MZ2_FLOAT_BLASTER_1				82

#define MZ2_SOLDIER_BLASTER_3			83
#define MZ2_SOLDIER_SHOTGUN_3			84
#define MZ2_SOLDIER_MACHINEGUN_3		85
#define MZ2_SOLDIER_BLASTER_4			86
#define MZ2_SOLDIER_SHOTGUN_4			87
#define MZ2_SOLDIER_MACHINEGUN_4		88
#define MZ2_SOLDIER_BLASTER_5			89
#define MZ2_SOLDIER_SHOTGUN_5			90
#define MZ2_SOLDIER_MACHINEGUN_5		91
#define MZ2_SOLDIER_BLASTER_6			92
#define MZ2_SOLDIER_SHOTGUN_6			93
#define MZ2_SOLDIER_MACHINEGUN_6		94
#define MZ2_SOLDIER_BLASTER_7			95
#define MZ2_SOLDIER_SHOTGUN_7			96
#define MZ2_SOLDIER_MACHINEGUN_7		97
#define MZ2_SOLDIER_BLASTER_8			98
#define MZ2_SOLDIER_SHOTGUN_8			99
#define MZ2_SOLDIER_MACHINEGUN_8		100

// --- Xian shit below ---
#define	MZ2_MAKRON_BFG					101
#define MZ2_MAKRON_BLASTER_1			102
#define MZ2_MAKRON_BLASTER_2			103
#define MZ2_MAKRON_BLASTER_3			104
#define MZ2_MAKRON_BLASTER_4			105
#define MZ2_MAKRON_BLASTER_5			106
#define MZ2_MAKRON_BLASTER_6			107
#define MZ2_MAKRON_BLASTER_7			108
#define MZ2_MAKRON_BLASTER_8			109
#define MZ2_MAKRON_BLASTER_9			110
#define MZ2_MAKRON_BLASTER_10			111
#define MZ2_MAKRON_BLASTER_11			112
#define MZ2_MAKRON_BLASTER_12			113
#define MZ2_MAKRON_BLASTER_13			114
#define MZ2_MAKRON_BLASTER_14			115
#define MZ2_MAKRON_BLASTER_15			116
#define MZ2_MAKRON_BLASTER_16			117
#define MZ2_MAKRON_BLASTER_17			118
#define MZ2_MAKRON_RAILGUN_1			119
#define	MZ2_JORG_MACHINEGUN_L1			120
#define	MZ2_JORG_MACHINEGUN_L2			121
#define	MZ2_JORG_MACHINEGUN_L3			122
#define	MZ2_JORG_MACHINEGUN_L4			123
#define	MZ2_JORG_MACHINEGUN_L5			124
#define	MZ2_JORG_MACHINEGUN_L6			125
#define	MZ2_JORG_MACHINEGUN_R1			126
#define	MZ2_JORG_MACHINEGUN_R2			127
#define	MZ2_JORG_MACHINEGUN_R3			128
#define	MZ2_JORG_MACHINEGUN_R4			129
#define MZ2_JORG_MACHINEGUN_R5			130
#define	MZ2_JORG_MACHINEGUN_R6			131
#define MZ2_JORG_BFG_1					132
#define MZ2_BOSS2_MACHINEGUN_R1			133
#define MZ2_BOSS2_MACHINEGUN_R2			134
#define MZ2_BOSS2_MACHINEGUN_R3			135
#define MZ2_BOSS2_MACHINEGUN_R4			136
#define MZ2_BOSS2_MACHINEGUN_R5			137

// JOSEPH 2-SEP-98
#define MZ3_LEADHIT_METAL				1

extern	vec3_t monster_flash_offset [];

// ----------------------------------------------------------------
// Ridah, Surface Sprite Effects
#define	SFX_SPRITE_SURF_BLOOD1		0
#define	SFX_SPRITE_SURF_BULLET1		1
#define	SFX_SPRITE_SURF_RIPPLE		2
#define SFX_SPRITE_SURF_BLOOD_POOL  5

// need these for each SFX_SPRITE_SURF, so the engine knows what dimensions they are
#define	SFX_BLOOD_WIDTH		16
#define	SFX_BLOOD_HEIGHT	16
#define	SFX_BULLET_WIDTH	1
#define	SFX_BULLET_HEIGHT	1
#define	SFX_RIPPLE_WIDTH	8
#define	SFX_RIPPLE_HEIGHT	8

// SFX flags
#define	SFX_FLAG_GRAVITY		1		// velocity is effected by gravity
#define	SFX_FLAG_SURFACE_EFFECT	2		// this is a surface effect, therefore velocity is the surface normal, and sprite will use alpha = 1 for "fadein_time"
#define	SFX_FLAG_NO_FLIP		4		// this SFX won't have it's S coordinate randomly flipped
#define	SFX_FLAG_LIGHTFLARE		8		// no depth checking, align with view
#define	SFX_FLAG_DEPTHHACK		16
#define	SFX_FLAG_UPRIGHT		32		// used for fire in barrel
#define SFX_FLAG_VEL_IS_ANGLES	64
#define	SFX_FLAG_ADDITIVE_BLEND	128
#define	SFX_FLAG_ALPHA_IS_FRAME	256
#define	SFX_FLAG_VEL_IS_COLOR_MODULATION	512
#define	SFX_FLAG_CLOSE_CULL		1024

#define	SFX_GRAVITY				100.0	// gravity value for all SFX effected by gravity

// temp entity events
//
// Temp entity events are for things that happen
// at a location seperate from any existing entity.
// Temporary entity messages are explicitly constructed
// and broadcast.
typedef enum
{
	TE_GUNSHOT,
	TE_GUNSHOT_VISIBLE,
	TE_BLOOD,
	TE_BLASTER,
	TE_RAILTRAIL,
	TE_SHOTGUN,
	TE_EXPLOSION1,
	TE_EXPLOSION2,
	TE_ROCKET_EXPLOSION,
	TE_GRENADE_EXPLOSION,
	TE_METAL_SPARKS,
	TE_SPARKS,
	TE_SPLASH,
	TE_BUBBLETRAIL,
	TE_SCREEN_SPARKS,
	TE_SHIELD_SPARKS,
	TE_BULLET_SPARKS,
	TE_LASER_SPARKS,
	TE_PARASITE_ATTACK,
	TE_ROCKET_EXPLOSION_WATER,
	TE_GRENADE_EXPLOSION_WATER,
	TE_MEDIC_CABLE_ATTACK,
	TE_BFG_EXPLOSION,
	TE_BFG_BIGEXPLOSION,
	TE_BOSSTPORT,			// used as '22' in a map, so DON'T RENUMBER!!!
	TE_BFG_LASER,
	TE_GRAPPLE_CABLE,
	// RAFAEL
	TE_WELDING_SPARKS,
	TE_GREENBLOOD,
	TE_BLUEHYPERBLASTER,
	TE_PLASMA_EXPLOSION,
	TE_TUNNEL_SPARKS,
	// JOSEPH 30-AUG-98
	TE_SFXFIRE,
	TE_SFXSMOKE,
	TE_SFXFIREGO,
	TE_SUN_FLARE,
	TE_GUN_FLARE,
	TE_SNOW,
	TE_RAIN,
	// END JOSEPH
	TE_LIGHT_FLARE,
	// Ridah, Surface Sprites
	// RAFAEL
	TE_BLOOD_DRIP,
	TE_BLOOD_SPLAT,
	TE_BLOOD_POOL,
	TE_SURFACE_SPRITE_ENTITY,
	TE_BURN_TO_A_CRISP,
	// JOSEPH 18-FEB-99
	TE_CONCUSSION_EXPLOSION,
	TE_CONCUSSION_EXPLOSION_WATER,
	TE_EXPLOSION1B,
	// END JOSEPH
	// JOSEPH 1-MAR-99
	TE_IMPACT,
	TE_EXPLOSION1C,
	// END JOSEPH
	// JOSEPH 19-FEB-99
	TE_SFXSTEAM,
	// END JOSEPH
	// JOSEPH 3-MAR-99
	TE_SFXSMOKE2,
	// END JOSEPH
	// JOSEPH 2-APR-99 
	TE_IMPACT_CONCUSSION,
	// END JOSEPH
	TE_ART_BURN,					// used to mark surfaces by artists
	TE_FOG_BRUSH,
	TE_GIBS,
	TE_CONCUSSION_EXPLOSION_BIG,
	// JOSEPH 9-APR-99
	TE_BARMACHINGUN,
	TE_SFXFIRET
	// END JOSEPH
} temp_event_t;

#define SPLASH_UNKNOWN		0
#define SPLASH_SPARKS		1
#define SPLASH_BLUE_WATER	2
#define SPLASH_BROWN_WATER	3
#define SPLASH_SLIME		4
#define	SPLASH_LAVA			5
#define SPLASH_BLOOD		6
// JOSEPH 17-MAY-99
#define SPLASH_SPARKS_P     7
// END JOSEPH

// sound channels
// channel 0 never willingly overrides
// other channels (1-7) allways override a playing sound on that channel
#define	CHAN_AUTO               0
#define	CHAN_WEAPON             1
#define	CHAN_VOICE              2
#define	CHAN_ITEM               3
#define	CHAN_BODY               4
#define	CHAN_SPECIAL			5
// modifier flags
#define	CHAN_NO_PHS_ADD			8	// send to all clients, not just ones in PHS (ATTN 0 will also do this)
#define	CHAN_RELIABLE			16	// send by reliable message, not datagram


// sound attenuation values
#define	ATTN_NONE               0	// full volume the entire level
#define	ATTN_NORM               1
#define	ATTN_IDLE               2
#define	ATTN_STATIC             3	// diminish very rapidly with distance


// player_state->stats[] indexes
#define STAT_CASH_PICKUP        0
#define	STAT_HEALTH				1
#define	STAT_AMMO_ICON			2
#define	STAT_AMMO				3

#define	STAT_ARMOR1             4   //previous STAT_ARMOR_ICON
#define	STAT_ARMOR2				5   //previous STAT_ARMOR
#define	STAT_ARMOR3				6   //previous STAT_SELECTED_ICON

#define	STAT_PICKUP_ICON		7
#define	STAT_PICKUP_STRING		8
// JOSEPH 12-MAY-99-B
#define	STAT_ENDPIC				9   //previous STAT_TIMER_ICON 
// END JOSEPH
#define	STAT_TIMER				10
#define	STAT_HELPICON			11
#define	STAT_SELECTED_ITEM		12
#define	STAT_LAYOUTS			13
#define	STAT_FRAGS				14
#define	STAT_FLASHES			15		// cleared each frame, 1 = health, 2 = armor
#define STAT_CASH				16
#define STAT_PICKUP_COUNT       17

// RAFAEL 01-11-99
#define STAT_CLIP				18
#define STAT_CLIP_ICON			19

// JOSEPH 26-JAN-99
#define STAT_HUD_INV			20
// END JOSEPH

// Following are duplicated for deathmatch, so beware if changing!
#define STAT_HUD_ENEMY_TALK      21
#define STAT_HUD_SELF_TALK       22
#define STAT_HUD_ENEMY_TALK_TIME 23
#define STAT_HUD_SELF_TALK_TIME  24
#define STAT_FORCE_HUD           25

#define STAT_HUD_HIRE1			 26
#define STAT_HUD_HIRE2			 27
#define STAT_HUD_HIRE1_CMD		 28
#define STAT_HUD_HIRE2_CMD		 29

// Ridah, duplicated these for use in teamplay, since they aren't used at all in multiplay
#define STAT_BAGCASH		      21
#define STAT_DEPOSITED        22
//#define STAT_HUD_ENEMY_TALK_TIME 23
//#define STAT_HUD_SELF_TALK_TIME  24

#define STAT_TEAM1_SCORE		 26
#define STAT_TEAM2_SCORE		 27
#define STAT_TEAM1_FLASH		 28		// 0 - no flash, 1 - green, 2 - red
#define STAT_TEAM2_FLASH		 29		// 0 - no flash, 1 - green, 2 - red
// done.


#define STAT_HIDE_HUD           30
#define STAT_SWITCH_CAMERA      31
#define	MAX_STATS				32


// dmflags->value flags
// Ridah, 26-may-99, disabled those that are not used in Kingpin
#define	DF_NO_HEALTH		1

// Ridah, 27-may-99, Not used anymore
//#define	DF_NO_ITEMS			2
#define	DF_AUTO_JOIN_TEAM	2

#define	DF_WEAPONS_STAY		4
#define	DF_NO_FALLING		8

// Ridah, 27-may-99, not used
//#define	DF_INSTANT_ITEMS	16

#define	DF_SAME_LEVEL		32

// Ridah, 27-may-99, not used (teams determined by model and skin
//#define DF_SKINTEAMS		64

#define DF_MODELTEAMS		128
#define DF_NO_FRIENDLY_FIRE	256
#define	DF_SPAWN_FARTHEST	512
#define DF_FORCE_RESPAWN	1024
#define DF_NO_ARMOR			2048
#define DF_ALLOW_EXIT		4096
#define DF_INFINITE_AMMO	8192

// Ridah, 27-may-99, not used
//#define DF_QUAD_DROP		16384

#define DF_FIXED_FOV		32768

// Ridah, 27-may-99, not used
//#define	DF_QUADFIRE_DROP	65536

/*
==========================================================

  ELEMENTS COMMUNICATED ACROSS THE NET

==========================================================
*/

#define	ANGLE2SHORT(x)	((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)	((x)*(360.0/65536))


//
// config strings are a general means of communication from
// the server to all connected clients.
// Each config string can be at most MAX_QPATH characters.
//
#define	CS_NAME				0
#define	CS_CDTRACK			1

#define CS_DENSITY			2
#define CS_FOGVAL			3

#define CS_DENSITY2			4
#define CS_FOGVAL2			5

#define	CS_SKY				6
#define	CS_STATUSBAR		7		// display program string

// RAFAEL
//#define CS_SKYBOX_ORIGIN		10
/*
#define	CS_SKY				2
#define	CS_SKYAXIS			3		// %f %f %f format
#define	CS_SKYROTATE		4
#define	CS_STATUSBAR		5		// display program string
*/

#define	CS_SERVER_VERSION	29		// so new clients can decide which version of download code to use

#define	CS_MAXCLIENTS		30
#define	CS_MAPCHECKSUM		31		// for catching cheater maps

#define	CS_MODELS			32
#define	CS_SOUNDS			(CS_MODELS+MAX_MODELS)
#define	CS_IMAGES			(CS_SOUNDS+MAX_SOUNDS)
#define CS_MODELSKINS		(CS_IMAGES+MAX_IMAGES)
#define	CS_LIGHTS			(CS_MODELSKINS+MAX_MODELS)
#define	CS_ITEMS			(CS_LIGHTS+MAX_LIGHTSTYLES)
#define	CS_PLAYERSKINS		(CS_ITEMS+MAX_ITEMS)
#define	CS_LIGHTFLARES		(CS_PLAYERSKINS+MAX_CLIENTS)
#define	CS_JUNIORS			(CS_LIGHTFLARES+MAX_LIGHTFLARES)
#define CS_GENERAL			(CS_JUNIORS+MAX_JUNIOR_STRINGS)
#define	MAX_CONFIGSTRINGS	(CS_GENERAL+MAX_GENERAL)


// Ridah, Lightflares
#define	FLARE_NORMAL	0
#define FLARE_SUN		1		// pos is actually the direction vector
#define FLARE_AMBER		2
#define	FLARE_RED		3
#define FLARE_BLUE		4
#define FLARE_GREEN		5

typedef struct
{
	char	lightstyle, type;
	vec3_t	pos;
	float	size;
} lightflare_t;

/*
typedef struct
{
	char	showflare;
	vec3_t	origin;
	vec3_t	angles;
} sunflare_t;
*/

char num_flares;		// this also goes into the configstring, at the start of the lightflare section
// done.

//==============================================


// entity_state_t->event values
// ertity events are for effects that take place reletive
// to an existing entities origin.  Very network efficient.
// All muzzle flashes really should be converted to events...

// JOSEPH 1-SEP-98
typedef enum
{
	EV_NONE,
	EV_ITEM_RESPAWN,
	EV_FOOTSTEP0,
	EV_FOOTSTEP1,
	EV_FOOTSTEP2,
	EV_FOOTSTEP3,
	EV_FOOTSTEP4,
	EV_FOOTSTEP5,
	EV_FOOTSTEP6,
	EV_FOOTSTEP7,
	// JOSEPH 26-JAN-99
	EV_FOOTSTEP8,
	// END JOSEPH
	EV_FALLSHORT0,
	EV_FALLSHORT1,
	EV_FALLSHORT2,
	EV_FALLSHORT3,
	EV_FALLSHORT4,
	EV_FALLSHORT5,
	EV_FALLSHORT6,
	EV_FALLSHORT7,
	// JOSEPH 26-JAN-99
	EV_FALLSHORT8,
	// END JOSEPH	
	EV_FALL,
	EV_FALLFAR,
	EV_PLAYER_TELEPORT,
	EV_OTHER_TELEPORT
} entity_event_t;
// END JOSEPH

// JOSEPH 18-FEB-99
typedef enum
{
	TT_NONE = 0,
	TT_POSITIVE,
	TT_FIGHT,
	TT_NEGATIVE,
	TT_QUESTION,
	TT_NEUTRAL,
	TT_NEWHUD,
	TT_NO,
	TT_YES,
	TT_COMMAND,
} talk_tone;
// END JOSEPH

// Ridah, MDX
typedef struct
{
	vec3_t	mins, maxs;
} object_bounds_t;

#define	MAX_MODEL_PARTS			8	// must change network code to increase this (also savegame code)
#define	MAX_MODELPART_OBJECTS	8	// absolutely do not change, bound by "invisible_objects" bit-flags

typedef struct model_part_s
{
// Ridah, MDX, ENABLE the following line when .mdx system goes online
	int		modelindex;					// leave as 0 if blank

//	int		invisible_objects;			// bit flags that define which sub-parts NOT to display when SET
	byte	invisible_objects;			// bit flags that define which sub-parts NOT to display when SET
	byte	skinnum[MAX_MODELPART_OBJECTS];

	// server-only data used for collision detection, etc
	int		object_bounds[MAX_MODELPART_OBJECTS];	// read in and allocated immediately after setting the modelindex
	char	*objectbounds_filename;			// so we can restore the object bounds data when loading a savegame

	int     baseskin;
	byte	hitpoints[MAX_MODELPART_OBJECTS];
	byte	hit_scale[MAX_MODELPART_OBJECTS]; // 0-250
} model_part_t;
// done.

// entity_state_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way

#define	MAX_MODEL_DIR_LIGHTS	3		// bound to 8 by network code

typedef struct
{
	int		light_indexes[MAX_MODEL_DIR_LIGHTS];	// so we can tell the client to use a certain light index, and it knows the details for that light

	vec3_t	light_vecs[MAX_MODEL_DIR_LIGHTS];		// static light directions that touch this model (dynamic are added in ref_gl)
	vec3_t	light_colors[MAX_MODEL_DIR_LIGHTS];
	float	light_intensities[MAX_MODEL_DIR_LIGHTS];	// 0.0 -> 1.0
	byte	light_styles[MAX_MODEL_DIR_LIGHTS];
	int		num_dir_lights;

	// below this doesn't get sent to client (only used at server side)
	vec3_t	light_orgs[MAX_MODEL_DIR_LIGHTS];

} model_lighting_t;

// Ridah, flamethrower
typedef struct flamejunc_s
{
	vec3_t	org, vel;
	float	start_width, end_width, start_height, end_height;	
	float	lifetime, fadein_time;
	float	start_alpha, end_alpha;

	// current values
	float	aged, alpha;
	float	width, height;

	vec3_t	unitvel;
	int		hit_wall;

	struct flamejunc_s	*next;
} flamejunc_t;

typedef struct entity_state_s
{
	int		number;			// edict index

	vec3_t	origin;
	vec3_t	angles;
	vec3_t	old_origin;		// for lerping
	int		modelindex;
//	int		modelindex2, modelindex3, modelindex4;	// weapons, CTF flags, etc
	int		frame;
	int		skinnum;
	int		effects;
	int		renderfx;
	int		solid;			// for client side prediction, 8*(bits 0-4) is x/y radius
							// 8*(bits 5-9) is z down distance, 8(bits10-15) is z up
							// gi.linkentity sets this properly
	int		sound;			// for looping sounds, to guarantee shutoff
	int		event;			// impulse events -- muzzle flashes, footsteps, etc
							// events only go out for a single frame, they
							// are automatically cleared each frame

	int		renderfx2;

	// Ridah, MDX, making way for .mdx system..
	int		num_parts;
	model_part_t	model_parts[MAX_MODEL_PARTS];
	// done.

	// Ridah, new lighting data
	model_lighting_t	model_lighting;

	vec3_t	last_lighting_update_pos;	// so we only calculate when a good distance from the last checked position
	vec3_t	last_lighting_vec_update_pos;	// set when we update the vecs

	// Ridah, flamethrower (only used on client-side)
	flamejunc_t	*flamejunc_head;
	// JOSEPH 15-APR-99
	flamejunc_t	*flamejunc_head2;
	// END JOSEPH
	int	last_time, prev_last_time;		// time of last call to CL_FlameEffects() for this entity
	byte		broken_flag;			// set if we release the trigger, so next time we fire, we can free all current flames

	float	alpha;			// set in CL_AddPacketEntities() from entity_state->effects

	float	scale;			// ranges from 0.0 -> 2.0

} entity_state_t;

//==============================================


// player_state_t is the information needed in addition to pmove_state_t
// to rendered a view.  There will only be 10 player_state_t sent each second,
// but the number of pmove_state_t changes will be reletive to client
// frame rates
typedef struct
{
	pmove_state_t	pmove;		// for prediction

	// these fields do not need to be communicated bit-precise

	vec3_t		viewangles;		// for fixed views
	vec3_t		viewoffset;		// add to pmovestate->origin
	vec3_t		kick_angles;	// add to view direction to get render angles
								// set by weapon kicks, pain effects, etc

	vec3_t		gunangles;
	vec3_t		gunoffset;
	int			gunindex;
	int			gunframe;

	float		blend[4];		// rgba full screen effect
	
	float		fov;			// horizontal field of view

	int			rdflags;		// refdef flags

	short		stats[MAX_STATS];		// fast status bar updates

 	// RAFAEL
 	// weapon mdx
 	int			num_parts;
 	model_part_t	model_parts[MAX_MODEL_PARTS];

	int			weapon_usage;
 	
} player_state_t;
