
// g_teamplay.c - teamplay oriented code

#include "g_local.h"

// current teamplay mode (set by "level.style")
teamplay_mode_t	teamplay_mode;

#define	CASH_ROLL			10
#define	CASH_BAG			25

#define	MAX_CASH_ITEMS		10		// never spawn more than this many cash items at once
int		num_cash_items;

char *team_names[] = {
	"(spectator)",
	"Dragons",
	"Nikki's Boyz",
	NULL
};


int	team_cash[3];	// cash per team, 0 is neutral so just ignore

float	last_safe_withdrawal[3];
float	last_safe_deposit[3];

//=====================================================================
// Entity spawn functions

// ....................................................................
// Cash Spawning during GRAB DA LOOT

void cash_touch( edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	float speed;

	if (surf && plane && plane->normal[2] > 0.5)
	{	// let it rest here

		if ((speed = VectorLength( self->velocity )) > 10)
		{
			self->s.angles[ROLL]	= 0;
			self->s.angles[PITCH]	= 0;
			self->avelocity[PITCH]	= 0;
			self->avelocity[ROLL]	= 0;
			self->avelocity[YAW]	*= 0.5;

			// randomize bounce
			VectorAdd( self->velocity, tv( crandom()*speed*0.3, crandom()*speed*0.3, random()*speed*0.15 ), self->velocity );
		}
		else
		{
			VectorClear( self->velocity );
			VectorClear( self->avelocity );
			self->s.angles[PITCH] = 0;
			self->s.angles[ROLL] = 0;

			self->movetype = MOVETYPE_NONE;
		}

		return;
	}

	if (other->client)
	{
		if (other->client->pers.currentcash < MAX_CASH_PLAYER)
		{	// they can hold the cash

			if ((self->currentcash == CASH_BAG) || (self->movetype != MOVETYPE_NONE) || (other->client->ps.pmove.pm_flags & PMF_DUCKED))
			{	// they can pick it up

				Touch_Item( self, other, plane, surf );

				num_cash_items--;

				G_FreeEdict( self );
				return;
			}

		}
	}
}

void cash_kill( edict_t *self )
{
	num_cash_items--;
	G_FreeEdict( self );
}

void cashroll_animate( edict_t *self )
{
	// reduce XY velocity (air friction)
	self->velocity[0] *= 0.9;
	self->velocity[1] *= 0.9;

	if (level.time > (self->timestamp))
	{
		cash_kill( self );
		return;
	}

	if (self->movetype != MOVETYPE_NONE)
	{

		if (VectorDistance( self->s.origin, self->pos1 ) < 1)
			self->count++;
		else
			self->count = 0;

		VectorCopy( self->s.origin, self->pos1 );

		if (self->count > 2)	// rested for 2 frames
		{
			VectorClear( self->velocity );
			VectorClear( self->avelocity );
			self->s.angles[PITCH] = 0;
			self->s.angles[ROLL] = 0;

			self->movetype = MOVETYPE_NONE;
		}
	}

	self->nextthink = level.time + 0.1;
}

void cashspawn_think( edict_t *self )
{
	edict_t	*cash;

	if (num_cash_items > MAX_CASH_ITEMS)
	{
		self->nextthink = level.time + self->delay;
		return;
	}

	// spawn some money
	cash = G_Spawn();

	VectorCopy( self->s.origin, cash->s.origin );
	cash->movetype = MOVETYPE_BOUNCE;
	cash->solid = SOLID_TRIGGER;

	AngleVectors( self->s.angles, cash->velocity, NULL, NULL );
	VectorScale( cash->velocity, self->speed, cash->velocity );

	// randomize the velocity a bit
	VectorAdd( cash->velocity, tv( crandom()*self->speed*0.3, crandom()*self->speed*0.3, crandom()*self->speed*0.15 ), cash->velocity );

	cash->s.renderfx2 |= RF2_NOSHADOW;

	// FIXME: doh this doesn't work, need to spawn actual item's, so the HUD is updated automatically when picking up

	if (!strcmp(self->type, "cashroll"))
	{	// small dollar notes
		cash->s.modelindex = gi.modelindex( "models/pu_icon/cash/tris.md2" );
		cash->gravity = 0.1 + random()*0.5;

		cash->think = cashroll_animate;
		cash->nextthink = level.time + 0.1;
		cash->s.angles[PITCH] = 10;
		VectorSet( cash->avelocity, 0, 10000 * cash->gravity, 0 );

		VectorSet( cash->mins, -4, -4, -15 );
		VectorSet( cash->maxs,  4,  4, -13 );

		cash->item = FindItem("Cash");

		cash->currentcash = CASH_ROLL;
		cash->touch = cash_touch;

		cash->timestamp = level.time + 60;

		cash->think = cashroll_animate;
		cash->nextthink = level.time + 0.1;
	}
	else
	{
		cash->s.modelindex = gi.modelindex( "models/pu_icon/money/money_sm.md2" );
		cash->gravity = 1.0;

		VectorSet( cash->mins, -12, -12, -15 );
		VectorSet( cash->maxs,  12,  12,  10 );

		cash->item = FindItem("Small Cash Bag");

		cash->currentcash = CASH_BAG;
		cash->touch = cash_touch;

		cash->think = cash_kill;
		cash->nextthink = level.time + 60;
	}

	num_cash_items++;

	self->nextthink = level.time + self->delay;

}

/*QUAKED dm_cashspawn (0.5 0 1) (-16 -16 -16) (16 16 16)
Spawn location for cash during "Grab da Loot" games

  angle - direction to project cash upon spawning
  speed - speed of projection
  type	- "cashroll" or "cashbag" (more money, longer delay)
*/
void SP_dm_cashspawn( edict_t *self )
{
	if (!teamplay->value || ((int)teamplay->value != TM_AUTO && (int)teamplay->value != TM_GRABDALOOT))
		return;

	// set the game to "Grab da Loot"
	teamplay_mode = TM_GRABDALOOT;
	num_cash_items = 0;

	if (!strcmp(self->type, "cashroll"))
	{
		self->delay = (float)g_cashspawndelay->value;
	}
	else	// bag, so longer delay
	{
		self->delay = (float)g_cashspawndelay->value * (CASH_BAG / CASH_ROLL);
	}

	if (!self->speed)
		self->speed = 10;

	self->think = cashspawn_think;
	self->nextthink = level.time + self->delay;
}

// ....................................................................
// Safe Bag, used for Grab Da Loot and teamplay Cash-Match 

void safebag_touch( edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	static float	last_touch_time;
	static edict_t	*last_touch_ent;
	static int		last_touch_count = 0;

	if (!other->client)
		return;

	if ((level.time < last_touch_time) || (last_touch_time && (last_touch_time < (level.time - 2.0))) || (last_touch_ent && (last_touch_ent != other)))
	{	// reset
		last_touch_time = 0;
		last_touch_ent = NULL;
		last_touch_count = 0;
	}
	else if (last_touch_time > (level.time - 0.1))
	{
		return;
	}
	else
	{
		last_touch_count++;
		last_touch_time = level.time;

		if (last_touch_count > (int)(50.0 * (1.0 + (0.5*(other->client->pers.team == self->style)))))
		{
			// let them go away on their own terms
			T_Damage( other, other, other, vec3_origin, other->s.origin, vec3_origin, 9999, 0, 0, MOD_SAFECAMPER );
			last_touch_count = 0;
		}
	}

	last_touch_ent = other;

	if (self->timestamp > (level.time - 1.0))
		return;

	self->timestamp = level.time;

	// depositing, or withdrawing?

	if (other->client->pers.team == self->style)
	{	// deposit
		
		if (other->client->pers.currentcash > 0 || other->client->pers.bagcash > 0)
		{
			int	precash, amount;

			precash = team_cash[self->style];

			team_cash[self->style] += other->client->pers.currentcash;
			team_cash[self->style] += other->client->pers.bagcash;

			other->client->resp.deposited += other->client->pers.currentcash;
			other->client->resp.deposited += other->client->pers.bagcash;

			other->client->pers.currentcash = 0;
			other->client->pers.bagcash = 0;

			gi.sound(other, CHAN_ITEM, gi.soundindex("world/pickups/cash.wav"), 1, 3, 0);

			// make a droping sound
			gi.positioned_sound(self->s.origin, self, CHAN_ITEM, gi.soundindex("world/doors/dr1_end.wav"), 1, 1, 0);

			// let everyone know how much was deposited
			amount = team_cash[self->style] - precash;
			gi.bprintf( PRINT_MEDIUM, "%s deposited $%i\n", other->client->pers.netname, amount );

			last_safe_deposit[self->style] = level.time;
		}

	}
	else if (team_cash[self->style] > 0)
	{	// withdrawal

		if (other->client->pers.bagcash < MAX_BAGCASH_PLAYER)
		{
			int	precash, amount;

			precash = team_cash[self->style];

			team_cash[self->style] -= (MAX_BAGCASH_PLAYER - other->client->pers.bagcash);
			other->client->pers.bagcash += (MAX_BAGCASH_PLAYER - other->client->pers.bagcash);

			if (team_cash[self->style] < 0)
			{	// don't take more than they have
				other->client->pers.bagcash += team_cash[self->style];
				team_cash[self->style] = 0;
			}

			gi.sound(other, CHAN_ITEM, gi.soundindex("world/pickups/cash.wav"), 1, 3, 0);

			// alarm!
			gi.positioned_sound(self->s.origin, self, CHAN_ITEM, gi.soundindex("misc/cashmatch_alarm.wav"), 1, 1, 0);

			// let everyone know how much was stolen
			amount = precash - team_cash[self->style];
			gi.bprintf( PRINT_MEDIUM, "%s stole $%i from %s's safe!\n", other->client->pers.netname, amount, team_names[self->style] );

			last_safe_withdrawal[self->style] = level.time;
		}

	}
}

// Safebag think, if a friendly guy has been standing near us for more than a few seconds, make them vulnerable to friendly fire
void safebag_think(edict_t *self)
{
	int	i;
	edict_t *trav;
	qboolean	noenemies = true;
	#define	SAFE_CLOSE_DIST		128
	#define	MAX_TIMEATSAFE		8.0

	// first, check if we have any unwanted enemies around, if so, don't count
	for (i=0; i<maxclients->value; i++)
	{
		trav = &g_edicts[i+1];

		if (!trav->inuse || !trav->client)
			continue;

		if (trav->health <= 0)
			continue;

		if (!trav->client->pers.team || (trav->client->pers.team == self->style))
			continue;

		if (VectorDistance( self->s.origin, trav->s.origin ) > 512)
			continue;

		if (!gi.inPVS( self->s.origin, trav->s.origin ))
			continue;

		noenemies = false;
	}

	for (i=0; i<maxclients->value; i++)
	{
		trav = &g_edicts[i+1];

		if (!trav->inuse || !trav->client)
			continue;

		if (trav->health <= 0)
			continue;

		if (!trav->client->pers.team || (trav->client->pers.team != self->style))
			continue;

		if (noenemies)
		{

			if (VectorDistance( self->s.origin, trav->s.origin ) > SAFE_CLOSE_DIST)
			{
				trav->client->pers.timeatsafe -= 0.2;

				if (trav->client->pers.timeatsafe < 0)
					trav->client->pers.timeatsafe = 0;
			}
			else
			{
				trav->client->pers.timeatsafe += 0.2;

				if (trav->client->pers.timeatsafe > MAX_TIMEATSAFE)
					trav->client->pers.timeatsafe = MAX_TIMEATSAFE;
			}

			if (trav->client->pers.timeatsafe >= MAX_TIMEATSAFE)
				trav->client->pers.friendly_vulnerable = true;
			else
				trav->client->pers.friendly_vulnerable = false;

		}
		else	// turn off vulnerability, there is an enemy in range
		{
			trav->client->pers.friendly_vulnerable = false;
		}
	}

	self->nextthink = level.time + 0.2;
}

/*QUAKED dm_safebag (0.5 0 1) (-12 -12 -16) (12 12 12)
Bag that holds the money in the safe.

  style - team that this bag belongs to (1 or 2)
*/
void SP_dm_safebag( edict_t *self )
{
	if (!teamplay->value)
	{
		G_FreeEdict( self );
		return;
	}

	if (self->style < 1 || self->style > 2)
	{
		gi.dprintf( "dm_safebag has invalid \"style\" at %s, should be 1 or 2.\n", vtos(self->s.origin));
		G_FreeEdict( self );
		return;
	}

	self->s.modelindex = gi.modelindex("models/pu_icon/money/money_lg.md2");
	VectorSet( self->mins, -12, -12, -16 );
	VectorSet( self->maxs,  12,  12,  12 );

	self->movetype = MOVETYPE_NONE;
	self->solid = SOLID_TRIGGER;

	gi.linkentity( self );

	self->touch = safebag_touch;
	self->currentcash = 0;	// start with no cash

	self->think = safebag_think;
	self->nextthink = level.time + 2;
}


/*QUAKED dm_props_banner (.5 0 1) (-4 -4 -4) (4 4 4)
Temp banner for teamplay

 style = team (1 / 2)
 scale = scale the size up/down (2 = double size)

model="models\props\temp\triangle\small.md2"
*/
void SP_dm_props_banner (edict_t *self)
{
//	vec3_t	end, bestnorm, bestend;
//	float bestdist;
//	int	x,y;
//	trace_t tr;

	if (!deathmatch->value || !teamplay->value)
	{	// remove
		G_FreeEdict (self);
		return;
	}
	
	if (!self->style)
	{
		gi.dprintf( "%s has invalid style (should be 1 or 2) at %s\n", self->classname, vtos(self->s.origin) );
		G_FreeEdict (self);
		return;
	}
/*
	// trace a line back, to get the wall, then go out
	{
		bestdist = 9999;

		for (x=-256; x<300; x+= 256)
		{
			VectorCopy( self->s.origin, end );
			end[0] = self->s.origin[0] + x;
			tr = gi.trace( self->s.origin, NULL, NULL, end, NULL, MASK_SOLID );
			if (tr.fraction < bestdist)
			{
				VectorCopy( tr.plane.normal, bestnorm );
				VectorCopy( tr.endpos, bestend );
				bestdist = tr.fraction;
			}
		}
		for (y=-256; y<300; y+= 256)
		{
			VectorCopy( self->s.origin, end );
			end[1] = self->s.origin[1] + y;
			tr = gi.trace( self->s.origin, NULL, NULL, end, NULL, MASK_SOLID );
			if (tr.fraction < bestdist)
			{
				VectorCopy( tr.plane.normal, bestnorm );
				VectorCopy( tr.endpos, bestend );
				bestdist = tr.fraction;
			}
		}

		vectoangles( bestnorm, self->s.angles );

		VectorMA( bestend, 40 * self->cast_info.scale, bestnorm, self->s.origin );
	}

*/
// Ridah, 1-jun-99, use flag models for now
#if 1
	{
		void think_flag (edict_t *self);

//		self->solid = SOLID_BBOX;
		self->movetype = MOVETYPE_NONE;

		if (self->style == 2)
		{
			self->model = "models/props/flag/flag1.md2";
		}
		else
		{
			self->model = "models/props/flag/flag3.md2";
		}

		self->s.modelindex = gi.modelindex (self->model);

		self->s.renderfx2 |= RF2_NOSHADOW;
		self->s.renderfx |= RF_MINLIGHT;

		if (!self->cast_info.scale)
			self->cast_info.scale = 1;

		self->s.scale = (self->cast_info.scale - 1);

//		VectorMA( bestend, 40 * self->cast_info.scale, bestnorm, self->s.origin );

		self->cast_info.scale *= 0.3;

		gi.linkentity (self);

		self->s.effects |= EF_ANIM_ALLFAST_NEW;
		self->s.renderfx2 |= RF2_MODULUS_FRAME;
		self->s.renderfx2 |= RDF_NOLERP;

// Disabled, doesn't animate much, and uses bandwidth
//		self->nextthink = level.time + FRAMETIME *2;
//		self->think = think_flag;
	}

#else // TRIANGULAR ROTATING ICONS

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;

	self->s.skinnum = self->style - 1;

	self->s.renderfx2 |= RF2_NOSHADOW;	
	self->s.renderfx |= RF_MINLIGHT;

	if (!self->cast_info.scale)
		self->cast_info.scale = 1;

	self->s.scale = self->cast_info.scale - 1;

	self->s.modelindex = gi.modelindex ("models/props/temp/triangle/small.md2");

	gi.linkentity (self);

	{
		edict_t *arm;

		arm = G_Spawn();
		arm->solid = self->solid;
		arm->movetype = self->movetype;
		arm->s.renderfx2 |= RF2_NOSHADOW;
		arm->s.scale = self->s.scale;

		VectorCopy( self->s.origin, arm->s.origin );
		VectorCopy( self->s.angles, arm->s.angles );

		arm->s.modelindex = gi.modelindex ("models/props/temp/triangle/arm.md2");
		gi.linkentity (arm);
	}

	VectorCopy( self->s.angles, self->last_step_pos );
	VectorClear( self->move_angles );
#endif
}

// ....................................................................

void Teamplay_ValidateSkin( edict_t *self )
{
	// TODO: we need color coded skins, for now, just use any skin
}

extern void ClientUserinfoChanged (edict_t *ent, char *userinfo);

qboolean Teamplay_ValidateJoinTeam( edict_t *self, int teamindex )
{
	// NOTE: this is called by each player on level change, as well as when a player issues a "join XXX" command

	// TODO: player limit per team? cvar?


	// setup client stuff
	self->movetype = MOVETYPE_WALK;
	self->solid = SOLID_BBOX;
	self->svflags &= ~SVF_NOCLIENT;

	Teamplay_ValidateSkin( self );

//	InitClientPersistant (self->client);

	self->client->pers.team = teamindex;

/*
	// Validate skins
	{
		char *str[256];

		strcpy( str, self->client->pers.userinfo );
		ClientUserinfoChanged ( self, str );
	}
*/

	self->health = 0;	// so we're not counted in spawn point checking
	self->client->resp.enterframe = level.framenum;
	InitClientResp( self->client );
	PutClientInServer( self );	// find a new spawn point
	gi.bprintf( PRINT_HIGH, "%s joined %s\n", self->client->pers.netname, team_names[teamindex] );

	return true;
}

void Teamplay_AutoJoinTeam( edict_t *self )
{
	int	team_count[2];
	int	i;

	// count number of players on each team, assign the team with least players

	team_count[0] = 0;
	team_count[1] = 0;

	for (i=1; i<maxclients->value; i++)
	{
		if (g_edicts[i].client && g_edicts[i].client->pers.team)
			team_count[g_edicts[i].client->pers.team - 1]++;
	}

	if (team_count[0] > team_count[1])
		self->client->pers.team = 2;
	else
		self->client->pers.team = 1;

	Teamplay_ValidateJoinTeam( self, self->client->pers.team );
}


void Teamplay_InitTeamplay (void)
{
	num_cash_items = 0;
	memset( team_cash, 0, sizeof(int) * 3 );
	memset( last_safe_withdrawal, 0, sizeof(float) * 3 );
	memset( last_safe_deposit, 0, sizeof(float) * 3 );

	last_safe_deposit[0] = last_safe_deposit[1] = 0;
	last_safe_withdrawal[0] = last_safe_withdrawal[1] = 0;
}
