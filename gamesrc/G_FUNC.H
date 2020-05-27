// g_func.h

// defines

#define PLAT_LOW_TRIGGER	1

#define	STATE_TOP			0
#define	STATE_BOTTOM		1
#define STATE_UP			2
#define STATE_DOWN			3

#define DOOR_START_OPEN		1
#define DOOR_REVERSE		2
#define DOOR_CRUSHER		4
#define DOOR_NOMONSTER		8
#define DOOR_TOGGLE			32
#define DOOR_X_AXIS			64
#define DOOR_Y_AXIS			128
#define	DOOR_ROTATE_AWAY	256

// procedures

void Use_Plat (edict_t *ent, edict_t *other, edict_t *activator);