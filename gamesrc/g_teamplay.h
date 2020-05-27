// ....................................................................

// teamplay.h - teamplay defines

typedef enum
{
	TM_NONE,
	TM_AUTO,
	TM_CASHMATCH,
	TM_GRABDALOOT,
	TM_GANGBANG		// Ridah, 27-may-99, just normal deathmatch, but with Kings/Pins teams
} teamplay_mode_t;


typedef enum
{
	TEAM_NONE,
	TEAM_1,
	TEAM_2,
} teams_t;


#define	MAX_CASH_PLAYER		150		// make this a cvar?
#define	MAX_BAGCASH_PLAYER	200		// make this a cvar?

// ....................................................................

extern char *team_names[];

extern teamplay_mode_t	teamplay_mode;
extern int		num_cash_items;

extern int	team_cash[3];	// cash per team, 0 is neutral so just ignore

extern float	last_safe_withdrawal[3];
extern float	last_safe_deposit[3];

// ....................................................................
// Spawn functions
void SP_dm_cashspawn( edict_t *self );
void SP_dm_safebag( edict_t *self );
void SP_dm_props_banner (edict_t *self);

// ....................................................................
// Other declarations
void Teamplay_ValidateSkin( edict_t *self );
qboolean Teamplay_ValidateJoinTeam( edict_t *self, int teamindex );
void Teamplay_InitTeamplay (void);
