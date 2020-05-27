
// Voice System defines

typedef struct voice_table_s voice_table_t;

// JOSEPH 11-MAR-99
struct voice_table_s
{
	voice_table_t	*response_table;		// match responses to this table
	char *text;
	char *text2;
	char *filename;
	int num_responses;	// 0 for anything
	int responses[5];	// list of indexes of sounds that would possibly match this comment
						// NOTE: these could reference sounds in other tables!
	float	last_played;
	qboolean	response;	// set if this "response" can only be played after another comment

	int	type;

	int	soundindex;		// for faster playing of sounds that have already been played this level
	int	gameinc_soundindex;	// so we can reset soundindexes on a new level
};
// END JOSEPH

extern int gameinc;

#define TALK_SELF_DELAY		9
#define TALK_OTHER_DELAY	1.6
#define	TALK_FIGHTING_DELAY	4

float	last_client_talk;		// records the last time the client was spoken to, so AI characters don't all respond at once

// this list is kept so we can make sure the soundindex of each voice item is cleared when starting a new level
voice_table_t *precached_voices[MAX_SOUNDS];
extern int	num_precached_voices;

void Voice_Random( edict_t *self, edict_t *other, voice_table_t *voice_table, int num_entries );
void Voice_Specific( edict_t *self, edict_t *other, voice_table_t *voice_table, int entry );
// JOSEPH 13-FEB-99
void Voice_Player_Specific( edict_t *player, int entry );
// END JOSEPH
