
#include "g_local.h"


qboolean	Pickup_Weapon (edict_t *ent, edict_t *other);
void		Use_Weapon (edict_t *ent, gitem_t *inv);
void		Use_Weapon2 (edict_t *ent, gitem_t *inv);
void		Drop_Weapon (edict_t *ent, gitem_t *inv);

// JOSEPH 12-OCT-98
void Weapon_Blackjack (edict_t *ent);
// JOSEPH 19-JAN-99
void Weapon_Crowbar (edict_t *ent);

// RAFAEL
void Weapon_SPistol (edict_t *ent);
void Weapon_Pistol (edict_t *ent);
void Weapon_Tommygun (edict_t *ent);

void Weapon_Blaster (edict_t *ent);
void Weapon_Shotgun (edict_t *ent);
void Weapon_SuperShotgun (edict_t *ent);
void Weapon_Machinegun (edict_t *ent);
void Weapon_Chaingun (edict_t *ent);
void Weapon_HyperBlaster (edict_t *ent);
void Weapon_RocketLauncher (edict_t *ent);
void Weapon_Grenade (edict_t *ent);
void Weapon_GrenadeLauncher (edict_t *ent);
void Weapon_Railgun (edict_t *ent);
void Weapon_BFG (edict_t *ent);
// RAFAEL
void Weapon_Ionripper (edict_t *ent);
void Weapon_Phalanx (edict_t *ent);
void Weapon_Trap (edict_t *ent);

void Weapon_FlameThrower (edict_t *ent);

void Weapon_Barmachinegun (edict_t *ent);

gitem_armor_t jacketarmor_info	= { 25,  50, .30, .00, ARMOR_JACKET};
gitem_armor_t combatarmor_info	= { 50, 100, .60, .30, ARMOR_COMBAT};
gitem_armor_t bodyarmor_info	= {100, 200, .80, .60, ARMOR_BODY};

static int	jacket_armor_index;
static int	combat_armor_index;
static int	body_armor_index;
static int	power_screen_index;
static int	power_shield_index;

#define HEALTH_IGNORE_MAX	1
#define HEALTH_TIMED		2

void Use_Quad (edict_t *ent, gitem_t *item);
// RAFAEL
void Use_QuadFire (edict_t *ent, gitem_t *item);

static int	quad_drop_timeout_hack;
// RAFAEL
static int	quad_fire_drop_timeout_hack;

//======================================================================

/*
===============
GetItemByIndex
===============
*/
gitem_t	*GetItemByIndex (int index)
{
	if (index == 0 || index >= game.num_items)
		return NULL;

	return &itemlist[index];
}


/*
===============
FindItemByClassname

===============
*/
gitem_t	*FindItemByClassname (char *classname)
{
	int		i;
	gitem_t	*it;

	it = itemlist;
	for (i=0 ; i<game.num_items ; i++, it++)
	{
		if (!it->classname)
			continue;
		if (!Q_stricmp(it->classname, classname))
			return it;
	}

	return NULL;
}

/*
===============
FindItem

===============
*/
gitem_t	*FindItem (char *pickup_name)
{
	int		i;
	gitem_t	*it;

	it = itemlist;
	for (i=0 ; i<game.num_items ; i++, it++)
	{
		if (!it->pickup_name)
			continue;
		if (!Q_stricmp(it->pickup_name, pickup_name))
			return it;
	}

	return NULL;
}

//======================================================================

void DoRespawn (edict_t *ent)
{
	if (ent->team)
	{
		edict_t	*master;
		int	count;
		int choice;

		master = ent->teammaster;

		for (count = 0, ent = master; ent; ent = ent->chain, count++)
			;

		choice = rand() % count;

		for (count = 0, ent = master; count < choice; ent = ent->chain, count++)
			;
	}

	ent->svflags &= ~SVF_NOCLIENT;
	ent->solid = SOLID_TRIGGER;
	gi.linkentity (ent);

	// send an effect
	ent->s.event = EV_ITEM_RESPAWN;
}

void SetRespawn (edict_t *ent, float delay)
{
	ent->flags |= FL_RESPAWN;
	ent->svflags |= SVF_NOCLIENT;
	ent->solid = SOLID_NOT;
	ent->nextthink = level.time + delay;
	ent->think = DoRespawn;
	gi.linkentity (ent);
}


//======================================================================

qboolean Pickup_Powerup (edict_t *ent, edict_t *other)
{
	int		quantity;

	quantity = other->client->pers.inventory[ITEM_INDEX(ent->item)];
	if ((skill->value == 1 && quantity >= 2) || (skill->value >= 2 && quantity >= 1))
		return false;

	// Rafael no coop
	if ((coop->value) && (ent->item->flags & IT_STAY_COOP) && (quantity > 0))
		return false;

	other->client->pers.inventory[ITEM_INDEX(ent->item)]++;

	if (deathmatch->value)
	{
		if (!(ent->spawnflags & DROPPED_ITEM) )
			SetRespawn (ent, ent->item->quantity);

// Ridah, 27-may-99, not used
/*
		if (((int)dmflags->value & DF_INSTANT_ITEMS) || ((ent->item->use == Use_Quad) && (ent->spawnflags & DROPPED_PLAYER_ITEM)))
		{
			if ((ent->item->use == Use_Quad) && (ent->spawnflags & DROPPED_PLAYER_ITEM))
				quad_drop_timeout_hack = (ent->nextthink - level.time) / FRAMETIME;
			ent->item->use (other, ent->item);
		}
		// RAFAEL
		else if (((int)dmflags->value & DF_INSTANT_ITEMS) || ((ent->item->use == Use_QuadFire) && (ent->spawnflags & DROPPED_PLAYER_ITEM)))
		{
			if ((ent->item->use == Use_QuadFire) && (ent->spawnflags & DROPPED_PLAYER_ITEM))
				quad_fire_drop_timeout_hack = (ent->nextthink - level.time) / FRAMETIME;
			ent->item->use (other, ent->item);
		}
*/
	}

	return true;
}

void Drop_General (edict_t *ent, gitem_t *item)
{
	Drop_Item (ent, item);
	ent->client->pers.inventory[ITEM_INDEX(item)]--;
	ValidateSelectedItem (ent);
}


//======================================================================

// JOSEPH 23-APR-99
qboolean Pickup_Adrenaline (edict_t *ent, edict_t *other)
{
	//if (!deathmatch->value)
	//	other->max_health += 1;

	if (other->health < other->max_health)
		other->health = other->max_health;

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, ent->item->quantity);

	return true;
}
// END JOSEPH

qboolean Pickup_AncientHead (edict_t *ent, edict_t *other)
{
	other->max_health += 2;

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, ent->item->quantity);

	return true;
}

qboolean Pickup_Bandolier (edict_t *ent, edict_t *other)
{
	gitem_t	*item;
	int		index;

	if (other->client->pers.max_bullets < 250)
		other->client->pers.max_bullets = 250;
	if (other->client->pers.max_shells < 150)
		other->client->pers.max_shells = 150;
	if (other->client->pers.max_cells < 250)
		other->client->pers.max_cells = 250;
	if (other->client->pers.max_slugs < 120)
		other->client->pers.max_slugs = 120;
	// RAFAEL
	if (other->client->pers.max_magslug < 75)
		other->client->pers.max_magslug = 75;

	item = FindItem("Bullets");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_bullets)
			other->client->pers.inventory[index] = other->client->pers.max_bullets;
	}

	item = FindItem("Shells");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_shells)
			other->client->pers.inventory[index] = other->client->pers.max_shells;
	}

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, ent->item->quantity);

	return true;
}

qboolean Pickup_Pack (edict_t *ent, edict_t *other)
{
	gitem_t	*item;
	int		index;

	if (other->client->pers.max_bullets < 300)
		other->client->pers.max_bullets = 300;
	if (other->client->pers.max_shells < 200)
		other->client->pers.max_shells = 200;
	if (other->client->pers.max_rockets < 100)
		other->client->pers.max_rockets = 100;
	if (other->client->pers.max_grenades < 15)
		other->client->pers.max_grenades = 15;
	if (other->client->pers.max_cells < 300)
		other->client->pers.max_cells = 300;
	if (other->client->pers.max_slugs < 120)
		other->client->pers.max_slugs = 120;
	// RAFAEL
	if (other->client->pers.max_magslug < 100)
		other->client->pers.max_magslug = 100;

	item = FindItem("Bullets");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_bullets)
			other->client->pers.inventory[index] = other->client->pers.max_bullets;
	}

	item = FindItem("Shells");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_shells)
			other->client->pers.inventory[index] = other->client->pers.max_shells;
	}

	item = FindItem("Gas");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_cells)
			other->client->pers.inventory[index] = other->client->pers.max_cells;
	}

	item = FindItem("Grenades");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_grenades)
			other->client->pers.inventory[index] = other->client->pers.max_grenades;
	}

	item = FindItem("Rockets");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_rockets)
			other->client->pers.inventory[index] = other->client->pers.max_rockets;
	}

	// JOSEPH 11-APR-99
	item = FindItem("308cal");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_slugs)
			other->client->pers.inventory[index] = other->client->pers.max_slugs;
	}
	// END JOSEPH

	// RAFAEL
	item = FindItem ("Mag Slug");
	if (item)
	{
		index = ITEM_INDEX(item);
		other->client->pers.inventory[index] += item->quantity;
		if (other->client->pers.inventory[index] > other->client->pers.max_magslug)
			other->client->pers.inventory[index] = other->client->pers.max_magslug;
	}

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, ent->item->quantity);

	return true;
}

//======================================================================

void Use_Quad (edict_t *ent, gitem_t *item)
{
	int		timeout;

	ent->client->pers.inventory[ITEM_INDEX(item)]--;
	ValidateSelectedItem (ent);

	if (quad_drop_timeout_hack)
	{
		timeout = quad_drop_timeout_hack;
		quad_drop_timeout_hack = 0;
	}
	else
	{
		timeout = 300;
	}

	if (ent->client->quad_framenum > level.framenum)
		ent->client->quad_framenum += timeout;
	else
		ent->client->quad_framenum = level.framenum + timeout;

	// JOSEPH 29-MAR-99
	//gi.sound(ent, CHAN_ITEM, gi.soundindex("items/damage.wav"), 1, ATTN_NORM, 0);
	// END JOSEPH
}


// =====================================================================

// RAFAEL
void Use_QuadFire (edict_t *ent, gitem_t *item)
{
	int		timeout;

	ent->client->pers.inventory[ITEM_INDEX(item)]--;
	ValidateSelectedItem (ent);

	if (quad_fire_drop_timeout_hack)
	{
		timeout = quad_fire_drop_timeout_hack;
		quad_fire_drop_timeout_hack = 0;
	}
	else
	{
		timeout = 300;
	}

	if (ent->client->quadfire_framenum > level.framenum)
		ent->client->quadfire_framenum += timeout;
	else
		ent->client->quadfire_framenum = level.framenum + timeout;

	// JOSEPH 29-MAR-99
	//gi.sound(ent, CHAN_ITEM, gi.soundindex("items/damage.wav"), 1, ATTN_NORM, 0);
	// END JOSEPH
}


//======================================================================

void Use_Breather (edict_t *ent, gitem_t *item)
{
	ent->client->pers.inventory[ITEM_INDEX(item)]--;
	ValidateSelectedItem (ent);

	if (ent->client->breather_framenum > level.framenum)
		ent->client->breather_framenum += 300;
	else
		ent->client->breather_framenum = level.framenum + 300;

//	gi.sound(ent, CHAN_ITEM, gi.soundindex("items/damage.wav"), 1, ATTN_NORM, 0);
}

//======================================================================

void Use_Envirosuit (edict_t *ent, gitem_t *item)
{
	ent->client->pers.inventory[ITEM_INDEX(item)]--;
	ValidateSelectedItem (ent);

	if (ent->client->enviro_framenum > level.framenum)
		ent->client->enviro_framenum += 300;
	else
		ent->client->enviro_framenum = level.framenum + 300;

//	gi.sound(ent, CHAN_ITEM, gi.soundindex("items/damage.wav"), 1, ATTN_NORM, 0);
}

//======================================================================

void	Use_Invulnerability (edict_t *ent, gitem_t *item)
{
	ent->client->pers.inventory[ITEM_INDEX(item)]--;
	ValidateSelectedItem (ent);

	if (ent->client->invincible_framenum > level.framenum)
		ent->client->invincible_framenum += 300;
	else
		ent->client->invincible_framenum = level.framenum + 300;

	// JOSEPH 29-MAR-99 
	//gi.sound(ent, CHAN_ITEM, gi.soundindex("items/protect.wav"), 1, ATTN_NORM, 0);
	// END JOSEPH
}

//======================================================================

void	Use_Silencer (edict_t *ent, gitem_t *item)
{
	// do not use anymore
	return;

//	ent->client->pers.inventory[ITEM_INDEX(item)]--;
//	ValidateSelectedItem (ent);
//	ent->client->pers.silencer_shots += 30;

//	gi.sound(ent, CHAN_ITEM, gi.soundindex("items/damage.wav"), 1, ATTN_NORM, 0);
}

//======================================================================

qboolean Pickup_Key (edict_t *ent, edict_t *other)
{
	// JOSEPH 26-JAN-99
	//ent->item->pickup_sound = "world/pickups/keys.wav";
	// END JOSEPH
	
	// Rafael no coop
	if (coop->value)
	{
		if (strcmp(ent->classname, "key_fuse") == 0)
		{
			if (other->client->pers.power_cubes & ((ent->spawnflags & 0x0000ff00)>> 8))
				return false;
			other->client->pers.inventory[ITEM_INDEX(ent->item)]++;
			other->client->pers.power_cubes |= ((ent->spawnflags & 0x0000ff00) >> 8);
		}
		else
		{
			if (other->client->pers.inventory[ITEM_INDEX(ent->item)])
				return false;
			other->client->pers.inventory[ITEM_INDEX(ent->item)] = 1;
		}
		return true;
	}
	
	other->client->pers.inventory[ITEM_INDEX(ent->item)]++;
	return true;
}

//======================================================================

qboolean Add_Ammo (edict_t *ent, gitem_t *item, int count)
{
	int			index;
	int			max;

	if (!ent->client)
		return false;

	if (item->tag == AMMO_BULLETS)
		max = ent->client->pers.max_bullets;
	else if (item->tag == AMMO_SHELLS)
		max = ent->client->pers.max_shells;
	else if (item->tag == AMMO_ROCKETS)
		max = ent->client->pers.max_rockets;
	else if (item->tag == AMMO_GRENADES)
		max = ent->client->pers.max_grenades;
	else if (item->tag == AMMO_CELLS)
		max = ent->client->pers.max_cells;
	else if (item->tag == AMMO_SLUGS)
		max = ent->client->pers.max_slugs;
	else if (item->tag == AMMO_MAGSLUG)
		max = ent->client->pers.max_magslug;
	else if (item->tag == AMMO_TRAP)
		max = ent->client->pers.max_trap;
	else
		return false;

	index = ITEM_INDEX(item);

	if (ent->client->pers.inventory[index] == max)
		return false;

	ent->client->pers.inventory[index] += count;

	if (ent->client->pers.inventory[index] > max)
		ent->client->pers.inventory[index] = max;

	return true;
}

qboolean Pickup_Ammo_Cylinder (edict_t *ent, edict_t *other)
{
	gitem_t	*it;
	int		index;

	it = FindItem("Bullets");
	if (it)
	{
		index = ITEM_INDEX(it);
		if (other->client->pers.inventory[index] >= other->client->pers.max_bullets)
			return false;

		other->client->pers.inventory[index] += ent->item->quantity; // get the cylinder quantity
		if (other->client->pers.inventory[index] > other->client->pers.max_bullets)
			other->client->pers.inventory[index] = other->client->pers.max_bullets;
	}

	if (!(ent->spawnflags & (DROPPED_ITEM | DROPPED_PLAYER_ITEM)) && (deathmatch->value))
		SetRespawn (ent, 30);
	
	return true;
}

qboolean Pickup_Ammo (edict_t *ent, edict_t *other)
{
	int			oldcount;
	int			count;
	qboolean	weapon;

	weapon = (ent->item->flags & IT_WEAPON);
	if ( (weapon) && deathmatch->value && ( (int)dmflags->value & DF_INFINITE_AMMO ) )
		count = 1000;
	else if (ent->count)
		count = ent->count;
	else
		count = ent->item->quantity;

	oldcount = other->client->pers.inventory[ITEM_INDEX(ent->item)];

	if (!Add_Ammo (other, ent->item, count))
		return false;

	if (weapon && !oldcount)
	{
		if (other->client->pers.weapon != ent->item && ( !deathmatch->value || other->client->pers.weapon == FindItem("blaster") ) )
			other->client->newweapon = ent->item;
	}

	if (!(ent->spawnflags & (DROPPED_ITEM | DROPPED_PLAYER_ITEM)) && (deathmatch->value))
		SetRespawn (ent, 30);
	return true;
}

void Drop_Ammo (edict_t *ent, gitem_t *item)
{
	edict_t	*dropped;
	int		index;

	index = ITEM_INDEX(item);
	
	if (ent->client->pers.inventory[index] <= 0)
		return;
	
	dropped = Drop_Item (ent, item);
	if (ent->client->pers.inventory[index] >= item->quantity)
		dropped->count = item->quantity;
	else
		dropped->count = ent->client->pers.inventory[index];

	if (ent->client->pers.weapon && 
		ent->client->pers.weapon->tag == AMMO_GRENADES &&
		item->tag == AMMO_GRENADES &&
		ent->client->pers.inventory[index] - dropped->count <= 0) {
		gi.cprintf (ent, PRINT_HIGH, "Can't drop current weapon\n");
		G_FreeEdict(dropped);
		return;
	}

	ent->client->pers.inventory[index] -= dropped->count;
	ValidateSelectedItem (ent);
}


// JOSEPH 18-MAR-99
qboolean Pickup_Cash (edict_t *ent, edict_t *other)
{

	if (!ent->currentcash)
	//	gi.cprintf (other, PRINT_HIGH, "%i dollars found\n", ent->currentcash);
	//else
		gi.cprintf (other, PRINT_HIGH, "Counterfeit money! 0 dollars found\n", ent->currentcash);


	if (ent->currentcash > 0)
	{
		if (teamplay->value && (teamplay_mode == TM_GRABDALOOT))
		{
			if (other->client->pers.currentcash > MAX_CASH_PLAYER)
				return false;
		}

		other->client->ps.stats[STAT_CASH_PICKUP] = ent->currentcash;
		other->client->pers.currentcash += ent->currentcash;

		if (teamplay->value && (teamplay_mode == TM_GRABDALOOT))
		{
			if (other->client->pers.currentcash > MAX_CASH_PLAYER)
				other->client->pers.currentcash = MAX_CASH_PLAYER;
		}
	}
	else	// negative money is bagged money (used in Teamplay)
	{
		if (teamplay->value && (teamplay_mode == TM_GRABDALOOT))
		{
			if (other->client->pers.bagcash > MAX_BAGCASH_PLAYER)
				other->client->pers.bagcash = MAX_BAGCASH_PLAYER;
		}

		ent->currentcash = -ent->currentcash;
		other->client->pers.bagcash += ent->currentcash;

		if (teamplay->value && (teamplay_mode == TM_GRABDALOOT))
		{
			if (other->client->pers.bagcash > MAX_BAGCASH_PLAYER)
			{
				edict_t *cash;

				// leave the left-over money here in a smaller bag
				if ((other->client->pers.bagcash - MAX_BAGCASH_PLAYER) > 100)
					cash = SpawnTheWeapon( other, "item_cashbaglarge" );
				else
					cash = SpawnTheWeapon( other, "item_cashbagsmall" );

				cash->currentcash = -(other->client->pers.bagcash - MAX_BAGCASH_PLAYER);

				other->client->pers.bagcash = MAX_BAGCASH_PLAYER;
			}
		}
	}

	// flash the screen green
	other->client->bonus_alpha_color = 2;	

	return true;
}
// END JOSEPH

//======================================================================

void MegaHealth_think (edict_t *self)
{
	if (self->owner->health > self->owner->max_health)
	{
		self->nextthink = level.time + 1;
		self->owner->health -= 1;
		return;
	}

	if (!(self->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (self, 20);
	else
		G_FreeEdict (self);
}

qboolean Pickup_Pistol_Mods (edict_t *ent, edict_t *other)
{

	if (ent->count == 1)
	{
		other->client->pers.pistol_mods |= WEAPON_MOD_ROF;
		//gi.dprintf ("Pistol Mod: Faster ROF\n");
	}
	else if (ent->count == 2)
	{
		other->client->pers.pistol_mods |= WEAPON_MOD_RELOAD;
		//gi.dprintf ("Pistol Mod: Faster Reload\n");
	}
	else if (ent->count == 3)
	{
		other->client->pers.pistol_mods |= WEAPON_MOD_DAMAGE;
		//gi.dprintf ("Pistol Mod: Damage x 2\n");
	
	}
	else if (ent->count == 4)
	{
		other->client->pers.pistol_mods |= WEAPON_MOD_COOLING_JACKET;
		other->client->pers.hmg_shots = 30;
	}
	else
	{
		gi.dprintf ("error in pickup pistol mods\n");
		return false;
	}

	if (ent->count <= 3)
	{
	if (other->client->pers.weapon == FindItem ("SPistol") || other->client->pers.weapon == FindItem("Pistol"))
	{
		other->client->newweapon = other->client->pers.weapon;
		ChangeWeapon (other);
	}
	}
	else if (ent->count == 4)
	{
		if (other->client->pers.weapon == FindItem ("Heavy machinegun") )
		{
			other->client->newweapon = other->client->pers.weapon;
			ChangeWeapon (other);
		}
	}

	// ent->item->pickup_sound = "items/pistolmod1.wav";

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
			SetRespawn (ent, 30);

	return true;
}

qboolean Pickup_Health (edict_t *ent, edict_t *other)
{
	if (!(ent->style & HEALTH_IGNORE_MAX))
		if (other->health >= other->max_health)
			return false;

	other->health += ent->count;

	if (ent->count == 2)
		ent->item->pickup_sound = "items/s_health.wav";
	else if (ent->count == 10)
		ent->item->pickup_sound = "items/n_health.wav";
	else if (ent->count == 25)
		ent->item->pickup_sound = "items/l_health.wav";
	else // (ent->count == 100)
		ent->item->pickup_sound = "items/m_health.wav";

	if (!(ent->style & HEALTH_IGNORE_MAX))
	{
		if (other->health > other->max_health)
			other->health = other->max_health;
	}

	if (ent->style & HEALTH_TIMED)
	{
		ent->think = MegaHealth_think;
		ent->nextthink = level.time + 5;
		ent->owner = other;
		ent->flags |= FL_RESPAWN;
		ent->svflags |= SVF_NOCLIENT;
		ent->solid = SOLID_NOT;
	}
	else
	{
		if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
			SetRespawn (ent, 30);
	}

	return true;
}

//======================================================================

int ArmorIndex (edict_t *ent)
{
	// JOSEPH 1-APR-99
	/*if (!ent->client)
		return 0;

	if (ent->client->pers.inventory[jacket_armor_index] > 0)
		return jacket_armor_index;

	if (ent->client->pers.inventory[combat_armor_index] > 0)
		return combat_armor_index;

	if (ent->client->pers.inventory[body_armor_index] > 0)
		return body_armor_index;*/
	// END JOSEPH

	return 0;
}

// JOSEPH 2-APR-99
qboolean Pickup_Armor (edict_t *ent, edict_t *other)
{
	if (strcmp(ent->classname, "item_armor_helmet") == 0)
	{
		gitem_t *itemh = FindItem("Helmet Armor");
		gitem_t *itemhh = FindItem("Helmet Armor Heavy");
		
		if ((other->client->pers.inventory[ITEM_INDEX(itemh)] == 100) ||
		   (other->client->pers.inventory[ITEM_INDEX(itemhh)] == 100))
			return false;
		
		if (other->client->pers.inventory[ITEM_INDEX(itemhh)])
		{
			other->client->pers.inventory[ITEM_INDEX(itemhh)] += 25;
			if (other->client->pers.inventory[ITEM_INDEX(itemhh)] > 100)
				other->client->pers.inventory[ITEM_INDEX(itemhh)] = 100;
		}
		else
		{
			other->client->pers.inventory[ITEM_INDEX(itemh)] += 50;
			if (other->client->pers.inventory[ITEM_INDEX(itemh)] > 100)
				other->client->pers.inventory[ITEM_INDEX(itemh)] = 100;
		}
	}
	else if (strcmp(ent->classname, "item_armor_jacket") == 0)
	{
		gitem_t *itemj = FindItem("Jacket Armor");
		gitem_t *itemjh = FindItem("Jacket Armor Heavy");
		
		if ((other->client->pers.inventory[ITEM_INDEX(itemj)] == 100) ||
		   (other->client->pers.inventory[ITEM_INDEX(itemjh)] == 100))
			return false;

		if (other->client->pers.inventory[ITEM_INDEX(itemjh)])
		{
			other->client->pers.inventory[ITEM_INDEX(itemjh)] += 25;
			if (other->client->pers.inventory[ITEM_INDEX(itemjh)] > 100)
				other->client->pers.inventory[ITEM_INDEX(itemjh)] = 100;
		}
		else
		{
			other->client->pers.inventory[ITEM_INDEX(itemj)] += 50;
			if (other->client->pers.inventory[ITEM_INDEX(itemj)] > 100)
				other->client->pers.inventory[ITEM_INDEX(itemj)] = 100;
		}
	}
	else if (strcmp(ent->classname, "item_armor_legs") == 0)
	{
		gitem_t *iteml = FindItem("Legs Armor");
		gitem_t *itemlh = FindItem("Legs Armor Heavy");	
		
		if ((other->client->pers.inventory[ITEM_INDEX(iteml)] == 100) ||
		   (other->client->pers.inventory[ITEM_INDEX(itemlh)] == 100))
			return false;

		if (other->client->pers.inventory[ITEM_INDEX(itemlh)])
		{
			other->client->pers.inventory[ITEM_INDEX(itemlh)] += 25;
			if (other->client->pers.inventory[ITEM_INDEX(itemlh)] > 100)
				other->client->pers.inventory[ITEM_INDEX(itemlh)] = 100;
		}
		else
		{
			other->client->pers.inventory[ITEM_INDEX(iteml)] += 50;
			if (other->client->pers.inventory[ITEM_INDEX(iteml)] > 100)
				other->client->pers.inventory[ITEM_INDEX(iteml)] = 100;
		}
	}
	else if (strcmp(ent->classname, "item_armor_helmet_heavy") == 0)
	{
		gitem_t *itemh = FindItem("Helmet Armor");
		gitem_t *itemhh = FindItem("Helmet Armor Heavy");
		
		if (other->client->pers.inventory[ITEM_INDEX(itemhh)] == 100)
			return false;
		
		if (other->client->pers.inventory[ITEM_INDEX(itemh)])
			other->client->pers.inventory[ITEM_INDEX(itemh)] = 0;			

		other->client->pers.inventory[ITEM_INDEX(itemhh)] = 100;
	}
	else if (strcmp(ent->classname, "item_armor_jacket_heavy") == 0)
	{
		gitem_t *itemj = FindItem("Jacket Armor");
		gitem_t *itemjh = FindItem("Jacket Armor Heavy");
		
		if (other->client->pers.inventory[ITEM_INDEX(itemjh)] == 100)
			return false;		

		if (other->client->pers.inventory[ITEM_INDEX(itemj)])
			other->client->pers.inventory[ITEM_INDEX(itemj)] = 0;			

		other->client->pers.inventory[ITEM_INDEX(itemjh)] = 100;
	}
	else if (strcmp(ent->classname, "item_armor_legs_heavy") == 0)
	{
		gitem_t *iteml = FindItem("Legs Armor");
		gitem_t *itemlh = FindItem("Legs Armor Heavy");	
		
		if (other->client->pers.inventory[ITEM_INDEX(itemlh)] == 100)
			return false;

		if (other->client->pers.inventory[ITEM_INDEX(iteml)])
			other->client->pers.inventory[ITEM_INDEX(iteml)] = 0;			

		other->client->pers.inventory[ITEM_INDEX(itemlh)] = 100;
	}
	
	
	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, 45);	// Ridah, armor shouldn't respawn so often

/*	int				old_armor_index;
	gitem_armor_t	*oldinfo;
	gitem_armor_t	*newinfo;
	int				newcount;
	float			salvage;
	int				salvagecount;

	// get info on new armor
	newinfo = (gitem_armor_t *)ent->item->info;

	old_armor_index = ArmorIndex (other);

	// handle armor shards specially
	if (ent->item->tag == ARMOR_SHARD)
	{
		if (!old_armor_index)
			other->client->pers.inventory[jacket_armor_index] = 2;
		else
			other->client->pers.inventory[old_armor_index] += 2;
	}

	// if player has no armor, just use it
	else if (!old_armor_index)
	{
		other->client->pers.inventory[ITEM_INDEX(ent->item)] = newinfo->base_count;
	}

	// use the better armor
	else
	{
		// get info on old armor
		if (old_armor_index == jacket_armor_index)
			oldinfo = &jacketarmor_info;
		else if (old_armor_index == combat_armor_index)
			oldinfo = &combatarmor_info;
		else // (old_armor_index == body_armor_index)
			oldinfo = &bodyarmor_info;

		if (newinfo->normal_protection > oldinfo->normal_protection)
		{
			// calc new armor values
			salvage = oldinfo->normal_protection / newinfo->normal_protection;
			salvagecount = salvage * other->client->pers.inventory[old_armor_index];
			newcount = newinfo->base_count + salvagecount;
			if (newcount > newinfo->max_count)
				newcount = newinfo->max_count;

			// zero count of old armor so it goes away
			other->client->pers.inventory[old_armor_index] = 0;

			// change armor to new item with computed value
			other->client->pers.inventory[ITEM_INDEX(ent->item)] = newcount;
		}
		else
		{
			// calc new armor values
			salvage = newinfo->normal_protection / oldinfo->normal_protection;
			salvagecount = salvage * newinfo->base_count;
			newcount = other->client->pers.inventory[old_armor_index] + salvagecount;
			if (newcount > oldinfo->max_count)
				newcount = oldinfo->max_count;

			// if we're already maxed out then we don't need the new armor
			if (other->client->pers.inventory[old_armor_index] >= newcount)
				return false;

			// update current armor value
			other->client->pers.inventory[old_armor_index] = newcount;
		}
	}

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, 20);*/

	return true;
}
// END JOSEPH

//======================================================================

int PowerArmorType (edict_t *ent)
{
	if (!ent->client)
		return POWER_ARMOR_NONE;

	if (!(ent->flags & FL_POWER_ARMOR))
		return POWER_ARMOR_NONE;

	if (ent->client->pers.inventory[power_shield_index] > 0)
		return POWER_ARMOR_SHIELD;

	if (ent->client->pers.inventory[power_screen_index] > 0)
		return POWER_ARMOR_SCREEN;

	return POWER_ARMOR_NONE;
}

void Use_PowerArmor (edict_t *ent, gitem_t *item)
{
	int		index;

	if (ent->flags & FL_POWER_ARMOR)
	{
		ent->flags &= ~FL_POWER_ARMOR;
		gi.sound(ent, CHAN_AUTO, gi.soundindex("misc/power2.wav"), 1, ATTN_NORM, 0);
	}
	else
	{
		index = ITEM_INDEX(FindItem("gas"));
		if (!ent->client->pers.inventory[index])
		{
			gi.cprintf (ent, PRINT_HIGH, "No cells for power armor.\n");
			return;
		}
		ent->flags |= FL_POWER_ARMOR;
		gi.sound(ent, CHAN_AUTO, gi.soundindex("misc/power1.wav"), 1, ATTN_NORM, 0);
	}
}

qboolean Pickup_PowerArmor (edict_t *ent, edict_t *other)
{
	int		quantity;

	quantity = other->client->pers.inventory[ITEM_INDEX(ent->item)];

	other->client->pers.inventory[ITEM_INDEX(ent->item)]++;

	if (deathmatch->value)
	{
		if (!(ent->spawnflags & DROPPED_ITEM) )
			SetRespawn (ent, ent->item->quantity);
		// auto-use for DM only if we didn't already have one
		if (!quantity)
			ent->item->use (other, ent->item);
	}

	return true;
}

void Drop_PowerArmor (edict_t *ent, gitem_t *item)
{
	if ((ent->flags & FL_POWER_ARMOR) && (ent->client->pers.inventory[ITEM_INDEX(item)] == 1))
		Use_PowerArmor (ent, item);
	Drop_General (ent, item);
}

//======================================================================

void Use_JetPack (edict_t *ent, gitem_t *item)
{
	if (ent->flags & FL_JETPACK)
	{
		ent->flags &= ~FL_JETPACK;

		gi.dprintf( "SOUND TODO: JetPack disabled\n" );
		gi.sound(ent, CHAN_AUTO, gi.soundindex("misc/jetpack_off.wav"), 1, ATTN_NORM, 0);
	}
	else
	{
		ent->flags |= FL_JETPACK;

		gi.dprintf( "SOUND TODO: JetPack enabled\n" );
		gi.sound(ent, CHAN_AUTO, gi.soundindex("misc/jetpack_on.wav"), 1, ATTN_NORM, 0);
	}
}

qboolean Pickup_JetPack (edict_t *ent, edict_t *other)
{
	int		quantity;

	quantity = other->client->pers.inventory[ITEM_INDEX(ent->item)];

	other->client->pers.inventory[ITEM_INDEX(ent->item)]++;

	if (deathmatch->value)
	{
		if (!(ent->spawnflags & DROPPED_ITEM) )
			SetRespawn (ent, ent->item->quantity);
		// auto-use for DM only if we didn't already have one
		if (!quantity)
			ent->item->use (other, ent->item);
	}

	other->client->jetpack_power = 2.5;

	return true;
}

// JOSEPH 12-MAR-99-B
qboolean Pickup_Health_Large (edict_t *ent, edict_t *other)
{
	
	if (other->health >= other->max_health)
		return false;

	other->health += 25;

	if (other->health > other->max_health)
			other->health = other->max_health;

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, 30);

	return true;
}

qboolean Pickup_Health_Small (edict_t *ent, edict_t *other)
{
	if (other->health >= other->max_health)
		return false;

	other->health += 15;

	if (other->health > other->max_health)
			other->health = other->max_health;

	if (!(ent->spawnflags & DROPPED_ITEM) && (deathmatch->value))
		SetRespawn (ent, 30);

	return true;
}
// END JOSEPH


//======================================================================

/*
===============
Touch_Item
===============
*/
void Touch_Item (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	qboolean	taken;

	if (!(other->client))
		return;
	if (other->health < 1)
		return;		// dead people can't pickup
	if (!ent->item->pickup)
		return;		// not a grabbable item?

	taken = ent->item->pickup(ent, other);

	// Do Episode specific handling
	EP_ItemPickup( ent, other );


	if (taken)
	{
		// flash the screen
		other->client->bonus_alpha = 0.25;	

		// JOSEPH 2-MAR-99
		if (!Q_stricmp(ent->item->pickup_name, "Pistol_Mods"))
		{
			if (ent->count == 1)
			{
				ent->item->icon = "/pics/h_pistol_rof.tga";
			}
			else if (ent->count == 2)
			{
				ent->item->icon = "/pics/h_pistol_rl.tga";
			}
			else if (ent->count == 3)
			{
				ent->item->icon = "/pics/h_pistol_mag.tga";
			}	
		}
		// END JOSEPH

		// show icon and name on status bar
		other->client->ps.stats[STAT_PICKUP_ICON] = gi.imageindex(ent->item->icon);
		other->client->ps.stats[STAT_PICKUP_STRING] = CS_ITEMS+ITEM_INDEX(ent->item);
		// JOSEPH 25-JAN-99
		other->client->pickup_msg_time = level.time + 5.5;
		// END JOSEPH
		// change selected item
		if (ent->item->use)
			other->client->pers.selected_item = other->client->ps.stats[STAT_SELECTED_ITEM] = ITEM_INDEX(ent->item);

		gi.sound(other, CHAN_ITEM, gi.soundindex(ent->item->pickup_sound), 1, ATTN_NORM, 0);
	}

	if (!(ent->spawnflags & ITEM_TARGETS_USED))
	{
		G_UseTargets (ent, other);
		ent->spawnflags |= ITEM_TARGETS_USED;
	}

	if (!taken)
		return;

	if (!((coop->value) &&  (ent->item->flags & IT_STAY_COOP)) || (ent->spawnflags & (DROPPED_ITEM | DROPPED_PLAYER_ITEM)))
	{
		if (ent->flags & FL_RESPAWN)
			ent->flags &= ~FL_RESPAWN;
		else
			G_FreeEdict (ent);
	}
	
}

//======================================================================

static void drop_temp_touch (edict_t *ent, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (other == ent->owner)
		return;

	Touch_Item (ent, other, plane, surf);
}

static void drop_make_touchable (edict_t *ent)
{
	ent->touch = Touch_Item;
	if (deathmatch->value)
	{
		ent->nextthink = level.time + 30;
		ent->think = G_FreeEdict;
	}
	// Xatrix/Ridah/Navigator/17-mar-1998
	ent->nav_data.flags |= ND_STATIC;
	// END:		Xatrix/Ridah/Navigator/17-mar-1998

}

edict_t *Drop_Item (edict_t *ent, gitem_t *item)
{
	edict_t	*dropped;
	vec3_t	forward, right;
	vec3_t	offset;

	dropped = G_Spawn();

	dropped->classname = item->classname;
	dropped->item = item;
	dropped->spawnflags = DROPPED_ITEM;
	dropped->s.effects = item->world_model_flags;
	dropped->s.renderfx = RF_GLOW;
	// JOSEPH 15-MAR-99	
	dropped->s.renderfx2 = RF2_NOSHADOW; 	
	// END JOSEPH
	VectorSet (dropped->mins, -15, -15, -15);
	VectorSet (dropped->maxs, 15, 15, 15);
	gi.setmodel (dropped, dropped->item->world_model);
	dropped->solid = SOLID_TRIGGER;
	dropped->movetype = MOVETYPE_TOSS;  
	dropped->touch = drop_temp_touch;
	dropped->owner = ent;

	if (ent->client)
	{
		trace_t	trace;

		AngleVectors (ent->client->v_angle, forward, right, NULL);
		VectorSet(offset, 24, 0, -16);
		G_ProjectSource (ent->s.origin, offset, forward, right, dropped->s.origin);
		trace = gi.trace (ent->s.origin, dropped->mins, dropped->maxs,
			dropped->s.origin, ent, CONTENTS_SOLID);
		VectorCopy (trace.endpos, dropped->s.origin);
	}
	else
	{
		AngleVectors (ent->s.angles, forward, right, NULL);
		VectorCopy (ent->s.origin, dropped->s.origin);
	}

	// JOSEPH 28-APR-99
	if (!(ent->svflags & SVF_PROP))
	{
	VectorScale (forward, 100, dropped->velocity);
	dropped->velocity[2] = 300;
	}
	else
	{
		dropped->s.origin[2] += 8;
		dropped->velocity[2] = 200;		
	}
	// END JOSEPH

	dropped->think = drop_make_touchable;
	dropped->nextthink = level.time + 1;

	gi.linkentity (dropped);

	return dropped;
}

void Use_Item (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->svflags &= ~SVF_NOCLIENT;
	ent->use = NULL;

	if (ent->spawnflags & ITEM_NO_TOUCH)
	{
		ent->solid = SOLID_BBOX;
		ent->touch = NULL;
	}
	else
	{
		ent->solid = SOLID_TRIGGER;
		ent->touch = Touch_Item;
	}

	gi.linkentity (ent);
}

//======================================================================

// JOSEPH 7-DEC-98
edict_t *Shot_Drop_Item (edict_t *ent, gitem_t *item, char* modeloverride)
{
	edict_t	*dropped;
	vec3_t	forward, right;
	vec3_t	offset;

	dropped = G_Spawn();

	dropped->classname = item->classname;
	dropped->item = item;
	dropped->spawnflags = DROPPED_ITEM;
	dropped->s.effects = item->world_model_flags;
	dropped->s.renderfx = RF_GLOW;
	VectorSet (dropped->mins, -15, -15, -15);
	VectorSet (dropped->maxs, 15, 15, 15);
	
	if (modeloverride)
	{
		gi.setmodel (dropped, modeloverride);
	}
	else
	{	
		gi.setmodel (dropped, dropped->item->world_model);
    }

	dropped->solid = SOLID_TRIGGER;
	dropped->movetype = MOVETYPE_TOSS;  
	dropped->touch = drop_temp_touch;
	dropped->owner = ent;

	if (ent->client)
	{
		trace_t	trace;

		AngleVectors (ent->client->v_angle, forward, right, NULL);
		VectorSet(offset, 24, 0, -16);
		G_ProjectSource (ent->s.origin, offset, forward, right, dropped->s.origin);
		trace = gi.trace (ent->s.origin, dropped->mins, dropped->maxs,
			dropped->s.origin, ent, CONTENTS_SOLID);
		VectorCopy (trace.endpos, dropped->s.origin);
	}
	else
	{
		AngleVectors (ent->s.angles, forward, right, NULL);
		VectorCopy (ent->s.origin, dropped->s.origin);
	}

	VectorScale (forward, 250, dropped->velocity);
	
	if ((rand()&1) == 1)
	{
	    VectorScale (right, 150, dropped->velocity);
	}
	else
	{
	    VectorScale (right, -150, dropped->velocity);
	}

	dropped->velocity[2] = 350;

	dropped->think = drop_make_touchable;
	dropped->nextthink = level.time + 1;

	gi.linkentity (dropped);

	return dropped;
}
// END JOSEPH

/*
================
droptofloor
================
*/
void droptofloor (edict_t *ent)
{
	trace_t		tr;
	vec3_t		dest;
	float		*v;

	v = tv(-15,-15,-15);
	VectorCopy (v, ent->mins);
	v = tv(15,15,15);
	VectorCopy (v, ent->maxs);

	if (ent->model)
		gi.setmodel (ent, ent->model);
	else
		gi.setmodel (ent, ent->item->world_model);
	ent->solid = SOLID_TRIGGER;
	ent->movetype = MOVETYPE_TOSS;  
	ent->touch = Touch_Item;

	v = tv(0,0,-128);
	VectorAdd (ent->s.origin, v, dest);

	tr = gi.trace (ent->s.origin, ent->mins, ent->maxs, dest, ent, MASK_SOLID);
	if (tr.startsolid)
	{
		// RAFAEL
		if (strcmp (ent->classname, "foodcube") == 0)
		{
			VectorCopy (ent->s.origin, tr.endpos);
			ent->velocity[2] = 0;
		}
		// JOSEPH 7-MAY-99
		else if (strcmp(ent->classname, "key_fuse") == 0)
		{
			v = tv(-7,-7,-16);
			VectorCopy (v, ent->mins);
			v = tv(7, 7, 16);
			VectorCopy (v, ent->maxs);
			ent->movetype = MOVETYPE_NONE; 
			ent->velocity[2] = 0;
			ent->s.origin[2] += 1;
			goto SkipFall;
		}
		// END JOSEPH
		else
		{
			gi.dprintf ("droptofloor: %s startsolid at %s\n", ent->classname, vtos(ent->s.origin));
			G_FreeEdict (ent);
			return;
		}
	}

	VectorCopy (tr.endpos, ent->s.origin);

// JOSEPH 7-MAY-99
SkipFall:
// END JOSEPH

	if (ent->team)
	{
		ent->flags &= ~FL_TEAMSLAVE;
		ent->chain = ent->teamchain;
		ent->teamchain = NULL;

		ent->svflags |= SVF_NOCLIENT;
		ent->solid = SOLID_NOT;
		if (ent == ent->teammaster)
		{
			ent->nextthink = level.time + FRAMETIME;
			ent->think = DoRespawn;
		}
	}

	if (ent->spawnflags & ITEM_NO_TOUCH)
	{
		ent->solid = SOLID_BBOX;
		ent->touch = NULL;
		ent->s.effects &= ~EF_ROTATE;
		ent->s.renderfx &= ~RF_GLOW;
	}

	if (ent->spawnflags & ITEM_TRIGGER_SPAWN)
	{
		ent->svflags |= SVF_NOCLIENT;
		ent->solid = SOLID_NOT;
		ent->use = Use_Item;
	}

	gi.linkentity (ent);
}


/*
===============
PrecacheItem

Precaches all data needed for a given item.
This will be called for each item spawned in a level,
and for each item in each client's inventory.
===============
*/
void PrecacheItem (gitem_t *it)
{
	char	*s, *start;
	char	data[MAX_QPATH];
	int		len;
	gitem_t	*ammo;

	if (!it)
		return;

	if (it->pickup_sound)
		gi.soundindex (it->pickup_sound);
	if (it->world_model)
		gi.modelindex (it->world_model);
	if (it->view_model)
		gi.modelindex (it->view_model);
	if (it->icon)
		gi.imageindex (it->icon);

	// parse everything for its ammo
	if (it->ammo && it->ammo[0])
	{
		ammo = FindItem (it->ammo);
		if (ammo != it)
			PrecacheItem (ammo);
	}

	// parse the space seperated precache string for other items
	s = it->precaches;
	if (!s || !s[0])
		return;

	while (*s)
	{
		start = s;
		while (*s && *s != ' ')
			s++;

		len = s-start;
		if (len >= MAX_QPATH || len < 5)
			gi.error ("PrecacheItem: %s has bad precache string", it->classname);
		memcpy (data, start, len);
		data[len] = 0;
		if (*s)
			s++;

		// determine type based on extension
		if (!strcmp(data+len-3, "md2"))
			gi.modelindex (data);
		
		// RAFAEL
		// weapon mdx
		else if (!strcmp (data+len-3, "mdx"))
		{
			gi.modelindex (data);
		}
		else if (!strcmp(data+len-3, "sp2"))
			gi.modelindex (data);
		else if (!strcmp(data+len-3, "wav"))
			gi.soundindex (data);
		if (!strcmp(data+len-3, "pcx"))
			gi.imageindex (data);
	}
}

/*
============
SpawnItem

Sets the clipping size and plants the object on the floor.

Items can't be immediately dropped to floor, because they might
be on an entity that hasn't spawned yet.
============
*/
void SpawnItem (edict_t *ent, gitem_t *item)
{
	if (!item)
		return;

	PrecacheItem (item);

	if (ent->spawnflags)
	{
		if (strcmp(ent->classname, "key_fuse") != 0)
		{
			ent->spawnflags = 0;
			gi.dprintf("%s at %s has invalid spawnflags set\n", ent->classname, vtos(ent->s.origin));
		}
	}

	// some items will be prevented in deathmatch
	if (deathmatch->value)
	{
		if ( (int)dmflags->value & DF_NO_ARMOR )
		{
			if (item->pickup == Pickup_Armor || item->pickup == Pickup_PowerArmor)
			{
				G_FreeEdict (ent);
				return;
			}
		}
/*
		if ( (int)dmflags->value & DF_NO_ITEMS )
		{
			if (item->pickup == Pickup_Powerup)
			{
				G_FreeEdict (ent);
				return;
			}
		}
*/
		if ( (int)dmflags->value & DF_NO_HEALTH )
		{
			if (item->pickup == Pickup_Health || item->pickup == Pickup_Adrenaline || item->pickup == Pickup_AncientHead 
				|| item->pickup == Pickup_Health_Large || item->pickup == Pickup_Health_Small)
			{
				G_FreeEdict (ent);
				return;
			}
		}
		if ( (int)dmflags->value & DF_INFINITE_AMMO && deathmatch->value )
		{
			if ( (item->flags == IT_AMMO) || (strcmp(ent->classname, "ammo_cylinder") == 0) )
			{
				G_FreeEdict (ent);
				return;
			}
		}

		// Ridah, realmode only has pistol, tommy and shotgun
		if (deathmatch->value && dm_realmode->value && item->classname)
		{
			if (	(item->pickup == Pickup_Weapon)
//				&&	(strstr(item->classname, "weapon") == item->classname)
				&&	(item->ammo && strcmp(item->ammo, "Bullets") && strcmp(item->ammo, "Shells")))
			{
				int	y;

				y = ((int)item->classname[7]) % 3;

				// select another valid weapon to use here
				if (y == 0)
				{
					item = FindItem("Shotgun");
				}
				else if (y == 1)
				{
					item = FindItem("Tommygun");
				}
				else
				{
					item = FindItem("Pistol_Mods");
					ent->model = "models/pu_icon/magmod/tris.md2";
					ent->count = 3;	//magnum mod
				}

			}
			else if (	(item->pickup == Pickup_Ammo)
					&&	((item->tag != AMMO_BULLETS) && (item->tag != AMMO_SHELLS)))
			{
				// select another valid weapon to use here
				if (((int)item->classname[5]) % 2)
				{
					item = FindItem("Bullets");
				}
				else
				{
					item = FindItem("Shells");
				}
			}


			// no armor
			if (item->classname && strstr(item->classname, "item_armor") == item->classname)
			{
				G_FreeEdict (ent);
				return;
			}
/*
			// no health
			if (strstr(item->classname, "item_health") == item->classname)
			{
				G_FreeEdict (ent);
				return;
			}
*/
		}
	}
			
// Ridah, no coop
/*
	if (coop->value && (strcmp(ent->classname, "key_power_cube") == 0))
	{
		ent->spawnflags |= (1 << (8 + level.power_cubes));
		level.power_cubes++;
	}

	// don't let them drop items that stay in a coop game
	if ((coop->value) && (item->flags & IT_STAY_COOP))
	{
		item->drop = NULL;
	}
*/
	// JOSEPH 22-JAN-99
	ent->item = item;
	ent->nextthink = level.time + 2 * FRAMETIME;    // items start after other solids
	ent->think = droptofloor;
	ent->s.effects = item->world_model_flags;
	ent->s.renderfx = RF_GLOW;
	ent->s.renderfx2 = RF2_NOSHADOW; 
	// END JOSEPH
	
	
	if (!(strcmp(ent->classname, "item_lizzyhead")))
	{
		int i;
		memset(&(ent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
		ent->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/pu_icon/head/head.mdx");
		ent->s.num_parts++;
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			ent->s.model_parts[PART_HEAD].baseskin = ent->s.model_parts[PART_HEAD].skinnum[i] = 0;
		gi.GetObjectBounds( "models/pu_icon/head/head.mdx", &ent->s.model_parts[PART_HEAD] );
	}	
	else if (ent->model)
		gi.modelindex (ent->model);

	// Xatrix/Ridah/Navigator/17-mar-1998
	ent->nav_data.flags |= ND_STATIC;
	// END:		Xatrix/Ridah/Navigator/17-mar-1998

}

// JOSEPH 13-FEB-99
void Use_Null (edict_t *ent, gitem_t *item)
{

}
// END JOSEPH

//======================================================================

// JOSEPH 21-APR-99
gitem_t	itemlist[] = 
{
	{
		NULL
	},	// leave index 0 alone

	//
	// ARMOR
	//


// JOSEPH 19-APR-99
/*QUAKED item_armor_helmet (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/armor_head/armor_head.md2" 
*/
	{
		"item_armor_helmet", 
		Pickup_Armor,
		NULL,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/armor_head/armor_head.md2", 0,
		NULL,
/* icon */		"/pics/h_helmet_lt.tga",
/* pickup */	"Helmet Armor",
/* width */		3,
		0,
		NULL,
		IT_ARMOR,
		&bodyarmor_info,
		ARMOR_COMBAT,
/* precache */ ""
	},

/*QUAKED item_armor_jacket (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/armor/tris.md2" 
*/
	{
		"item_armor_jacket", 
		Pickup_Armor,
		NULL,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/armor/tris.md2", 0,
		NULL,
/* icon */		"/pics/h_chest_lt.tga",
/* pickup */	"Jacket Armor",
/* width */		3,
		0,
		NULL,
		IT_ARMOR,
		&combatarmor_info,
		ARMOR_JACKET,
/* precache */ ""
	},

/*QUAKED item_armor_legs (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/armor_lo/armor_lo.md2" 
*/
	{
		"item_armor_legs", 
		Pickup_Armor,
		NULL,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/armor_lo/armor_lo.md2", 0,
		NULL,
/* icon */		"/pics/h_pants_lt.tga",
/* pickup */	"Legs Armor",
/* width */		3,
		0,
		NULL,
		IT_ARMOR,
		&jacketarmor_info,
		ARMOR_BODY,
/* precache */ ""
	},


/*QUAKED item_armor_helmet_heavy (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/armor_head/armor_head_hd.md2"
*/
	{
		"item_armor_helmet_heavy", 
		Pickup_Armor,
		NULL,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/armor_head/armor_head_hd.md2", 0,
		NULL,
/* icon */		"/pics/h_helmet_hvy.tga",
/* pickup */	"Helmet Armor Heavy",
/* width */		3,
		0,
		NULL,
		IT_ARMOR,
		&bodyarmor_info,
		ARMOR_COMBAT,
/* precache */ ""
	},

/*QUAKED item_armor_jacket_heavy (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/armor/armorhdtop.md2"
*/
	{
		"item_armor_jacket_heavy", 
		Pickup_Armor,
		NULL,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/armor/armorhdtop.md2", 0,
		NULL,
/* icon */		"/pics/h_chest_hvy.tga",
/* pickup */	"Jacket Armor Heavy",
/* width */		3,
		0,
		NULL,
		IT_ARMOR,
		&combatarmor_info,
		ARMOR_JACKET,
/* precache */ ""
	},

/*QUAKED item_armor_legs_heavy (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/armor_lo/armor_lo_hd.md2"
*/
	{
		"item_armor_legs_heavy", 
		Pickup_Armor,
		NULL,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/armor_lo/armor_lo_hd.md2", 0,
		NULL,
/* icon */		"/pics/h_pants_hvy.tga",
/* pickup */	"Legs Armor Heavy",
/* width */		3,
		0,
		NULL,
		IT_ARMOR,
		&jacketarmor_info,
		ARMOR_BODY,
/* precache */ ""
	},

	//
	// WEAPONS 
	//

/* weapon_blackjack (.3 .3 1) (-16 -16 -16) (16 16 16)
always owned, never in the world
*/
	{
		"weapon_blackjack", 
		NULL,
		Use_Weapon2,
		NULL,
		Weapon_Blackjack,
		"misc/w_pkup.wav",
		NULL, 0,
		"models/weapons/blakjak/blakjak.mdx",
/* icon */		"h_pipe",
/* pickup */	"Pipe",
		0,
		0,
		NULL,
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "weapons/melee/swing.wav" 
	},

// JOSEPH 14-APR-99
/*QUAKED weapon_crowbar (.3 .3 1) (-16 -16 -16) (16 16 16)

model="models/weapons/g_crowbar/tris.md2"  
*/
	{
		"weapon_crowbar", 
		Pickup_Weapon,
		Use_Weapon2,
		Drop_Weapon,
		Weapon_Crowbar,
		"misc/w_pkup.wav",
		"models/weapons/g_crowbar/tris.md2", EF_REFL,
		"models/weapons/crowbar/crowbar.mdx",
/* icon */		"/pics/h_cbar.tga",
/* pickup */	"Crowbar",
		0,
		0,
		NULL,
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "weapons/melee/swing.wav" 
	},
// END JOSEPH
	
/*QUAKED weapon_pistol (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/weapons/g_pistol/tris.md2"  
*/
	{
		"weapon_pistol", 
		Pickup_Weapon,
		Use_Weapon2,
		Drop_Weapon,
		Weapon_Pistol,
		"misc/w_pkup.wav",
		// note to Jason 
		// we need a pistol pickup icon
		"models/weapons/g_pistol/tris.md2", EF_REFL,
		"models/weapons/v_colt/pistol.mdx",
/* icon */		"/pics/h_pistol.tga",
/* pickup */	"Pistol",
		0,
		1,
		"Bullets",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},

/* weapon_pistol_s (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/weapons/silencer_mdx/pistol.mdx"
*/
	{
		"weapon_spistol", 
		Pickup_Weapon,
		Use_Weapon2,
		Drop_Weapon,
		Weapon_SPistol,
		"misc/w_pkup.wav",
		// note to Jason 
		// we need a pistol pickup icon
		"models/weapons/silencer_mdx/pistol.mdx", EF_REFL,
		"models/weapons/silencer_mdx/pistol.mdx",
/* icon */		"/pics/h_silencer.tga",
/* pickup */	"SPistol",
		0,
		1,
		"Bullets",
		IT_WEAPON|IT_STAY_COOP|IT_SILENCER,
		NULL,
		0,
/* precache */ "weapons/pistol/silencer.wav weapons/pistol/silencerattatch.wav"
	},

/*QUAKED weapon_shotgun (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/weapons/g_shotgun/tris.md2"  
*/
	{
		"weapon_shotgun", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_Shotgun,
		"misc/w_pkup.wav",
		"models/weapons/g_shotgun/tris.md2", EF_REFL,
		"models/weapons/shotgun/shotgun.mdx",
/* icon */		"/pics/h_shotgun.tga",
/* pickup */	"Shotgun",
		0,
		1,
		"Shells",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "weapons/shotgun/shotgf1b.wav weapons/shotgun/shotgr1b.wav"
	},

/*QUAKED weapon_tommygun (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/weapons/g_tomgun/tris.md2"  
*/
	{
		"weapon_tommygun", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_Tommygun,
		"misc/w_pkup.wav",
		"models/weapons/g_tomgun/tris.md2", EF_REFL,
		"models/weapons/v_tomgun/tomgun.mdx",
/* icon */		"/pics/h_tgun.tga",
/* pickup */	"Tommygun",
		0,
		1,
		"Bullets",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "weapons/machinegun/machgf1b.wav"
	},

// JOSEPH 16-APR-99
/*QUAKED weapon_heavymachinegun (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/weapons/g_hmg/tris.md2"  
*/
{
		"weapon_heavymachinegun", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_Barmachinegun,
		"misc/w_pkup.wav",
		"models/weapons/g_hmg/tris.md2", EF_REFL,
		"models/weapons/v_hmg/hmg.mdx",
/* icon */		"/pics/h_hmg.tga",
/* pickup */	"Heavy machinegun",
		0,
		1,
		"308cal",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

/*QUAKED weapon_grenadelauncher (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/weapons/g_grenade_launcher/tris.md2"    
*/
	{
		"weapon_grenadelauncher",
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_GrenadeLauncher,
		"misc/w_pkup.wav",
		"models/weapons/g_grenade_launcher/tris.md2", EF_REFL,
		"models/weapons/v_grenade_launcher/grenade_launcher.mdx",
/* icon */		"/pics/h_grenade_l.tga",
/* pickup */	"Grenade Launcher",
		0,
		1,
		"Grenades",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},

// JOSEPH 28-APR-99
/*QUAKED weapon_bazooka (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/weapons/g_rocket_launcher/tris.md2"  
*/
	{
		"weapon_bazooka",
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_RocketLauncher,
		"misc/w_pkup.wav",
		"models/weapons/g_rocket_launcher/tris.md2", EF_REFL,
		"models/weapons/v_rocket_launcher/rlaunch.mdx",
/* icon */		"/pics/h_bazooka.tga",
/* pickup */	"Bazooka",
		0,
		1,
		"Rockets",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "models/props/glass/glass2.md2"
	},
// END JOSEPH

/*QUAKED weapon_flamethrower (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/flame_shell/tris.md2"    
*/
	{
		"weapon_flamethrower", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_FlameThrower,
		"misc/w_pkup.wav",
		//"models/weapons/g_shotg2/tris.md2", EF_ROTATE,
		"models/pu_icon/flame_shell/tris.md2", EF_REFL,
		"models/weapons/v_flamegun/flamegun.mdx",
/* icon */		"/pics/h_flamethrower.tga",
/* pickup */	"FlameThrower",
		0,
		2,
		"Gas",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

#if 0
// JOSEPH 7-MAY-99
// ENEMY WEAPONS
	{
		"weapon_shotgun_e", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_Shotgun,
		"misc/w_pkup.wav",
		"models/weapons/e_shtgun/tris.md2", EF_REFL,
		"models/weapons/shotgun/shotgun.mdx",
/* icon */		"/pics/h_shotgun.tga",
/* pickup */	"Shotgun",
		0,
		1,
		"Shells",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "weapons/shotgun/shotgf1b.wav weapons/shotgun/shotgr1b.wav"
	},

	{
		"weapon_heavymachinegun_e", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_Barmachinegun,
		"misc/w_pkup.wav",
		"models/weapons/e_hmg/tris.md2", EF_REFL,
		"models/weapons/v_hmg/hmg.mdx",
/* icon */		"/pics/h_hmg.tga",
/* pickup */	"Heavy machinegun",
		0,
		1,
		"308cal",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},	

	{
		"weapon_bazooka_e",
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_RocketLauncher,
		"misc/w_pkup.wav",
		"models/weapons/e_rocket_launcher/tris.md2", EF_REFL,
		"models/weapons/v_rocket_launcher/rlaunch.mdx",
/* icon */		"/pics/h_bazooka.tga",
/* pickup */	"Bazooka",
		0,
		1,
		"Rockets",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "models/props/glass/glass2.md2"
	},	

	{
		"weapon_flamethrower_e", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_FlameThrower,
		"misc/w_pkup.wav",
		"models/weapons/e_flamegun/tris.md2", EF_REFL,
		"models/weapons/v_flamegun/flamegun.mdx",
/* icon */		"/pics/h_flamethrower.tga",
/* pickup */	"FlameThrower",
		0,
		2,
		"Gas",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},	

	{
		"weapon_grenadelauncher_e",
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_GrenadeLauncher,
		"misc/w_pkup.wav",
		"models/weapons/e_grenade_launcher/tris.md2", EF_REFL,
		"models/weapons/v_grenade_launcher/grenade_launcher.mdx",
/* icon */		"/pics/h_grenade_l.tga",
/* pickup */	"Grenade Launcher",
		0,
		1,
		"Grenades",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},	

	{
		"weapon_pistol_e", 
		Pickup_Weapon,
		Use_Weapon2,
		Drop_Weapon,
		Weapon_Pistol,
		"misc/w_pkup.wav",
		"models/weapons/e_pistol/tris.md2", EF_REFL,
		"models/weapons/v_colt/pistol.mdx",
/* icon */		"/pics/h_pistol.tga",
/* pickup */	"Pistol",
		0,
		1,
		"Bullets",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ ""
	},	

	{
		"weapon_tommygun_e", 
		Pickup_Weapon,
		Use_Weapon,
		Drop_Weapon,
		Weapon_Tommygun,
		"misc/w_pkup.wav",
		"models/weapons/e_tomgun/tris.md2", EF_REFL,
		"models/weapons/v_tomgun/tomgun.mdx",
/* icon */		"/pics/h_tgun.tga",
/* pickup */	"Tommygun",
		0,
		1,
		"Bullets",
		IT_WEAPON|IT_STAY_COOP,
		NULL,
		0,
/* precache */ "weapons/machinegun/machgf1b.wav"
	},	
	// END JOSEPH
#endif

	//
	// AMMO ITEMS
	//

/*QUAKED ammo_grenades (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/grenade/tris.md2"  
*/
	{
		"ammo_grenades",
		Pickup_Ammo,
		Use_Null,
		Drop_Ammo,
		NULL,
		"world/pickups/ammo.wav",
		"models/pu_icon/grenade/tris.md2", 0,
        NULL,
/* icon */		"/pics/h_grenade.tga",
/* pickup */	"Grenades",
/* width */		3,
		3,
		NULL,
		IT_AMMO,
		NULL,
		AMMO_GRENADES,
/* precache */ ""
	},

/*QUAKED ammo_shells (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/shotgun_shell/tris.md2"  
*/
	{
		"ammo_shells",
		Pickup_Ammo,
		Use_Null,
		Drop_Ammo,
		NULL,
		"world/pickups/ammo.wav",
		"models/pu_icon/shotgun_shell/tris.md2", 0,		
		NULL,
/* icon */		"/pics/h_shots.tga",
/* pickup */	"Shells",
/* width */		3,
		10,
		NULL,
		IT_AMMO,
		NULL,
		AMMO_SHELLS,
/* precache */ ""
	},

// JOSEPH 3-MAR-99
/*QUAKED ammo_bullets (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/pclip/tris.md2"  
*/
	{
		"ammo_bullets",
		Pickup_Ammo,
		Use_Null,
		Drop_Ammo,
		NULL,
		"world/pickups/ammo.wav",
		"models/pu_icon/pclip/tris.md2", 0,
		NULL,
/* icon */		"/pics/h_bullet.tga",
/* pickup */	"Bullets",
/* width */		3,
		20,
		NULL,
		IT_AMMO,
		NULL,
		AMMO_BULLETS,
/* precache */ ""
	},
// END JOSEPH


// JOSEPH 1-APR-99
/*QUAKED ammo_rockets (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/rocket/tris.md2" 
*/
	{
		"ammo_rockets",
		Pickup_Ammo,
		Use_Null,
		Drop_Ammo,
		NULL,
		"world/pickups/ammo.wav",
		"models/pu_icon/rocket/tris.md2", 0,
		NULL,
/* icon */		"/pics/h_missle.tga",
/* pickup */	"Rockets",
/* width */		3,
		5,
		NULL,
		IT_AMMO,
		NULL,
		AMMO_ROCKETS,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 28-APR-99
/*QUAKED ammo_308 (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/hmgclip/tris.md2" 
*/
	{
		"ammo_308",
		Pickup_Ammo,
		Use_Null,
		Drop_Ammo,
		NULL,
		"misc/w_pkup.wav",
		"models/pu_icon/hmgclip/tris.md2", 0,
		NULL,
/* icon */		"/pics/h_hmg_clip.tga",
/* pickup */	"308cal",
/* width */		3,
		30,
		NULL,
		IT_AMMO,
		NULL,
		AMMO_SLUGS,
/* precache */ ""
	},
// END JOSEPH

/*QUAKED ammo_cylinder (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/tgclip/tris.md2"  
*/
	{
		"ammo_cylinder",
		Pickup_Ammo_Cylinder,
		Use_Null,
		Drop_Ammo,
		NULL,
		"world/pickups/ammo.wav",
		"models/pu_icon/tgclip/tris.md2", 0,
		NULL,
/* icon */		"/pics/h_tclip.tga",
/* pickup */	"Cylinder",
/* width */		3,
		50,
		NULL,
		IT_AMMO|IT_NOCHEATS,
		NULL,
		AMMO_BULLETS,
/* precache */ ""
	},

/*QUAKED ammo_flametank (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/flametank/tris.md2"  
*/
	{
		"ammo_flametank",
		Pickup_Ammo,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/ammo.wav",
		"models/pu_icon/flametank/tris.md2", 0,
		NULL,
		"/pics/h_ftank.tga",
		"Gas",
		2,
		50,
		NULL,
		IT_AMMO,
		NULL,
		AMMO_CELLS,
/* precache */ ""
	},		

	//
	// KINGPIN items
	//

	
// JOSEPH 22-FEB-99	
/*QUAKED item_coil (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/coil/tris.md2"  
*/
	{
		"item_coil",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/coil.wav",
		"models/pu_icon/coil/tris.md2", 0,
		NULL,
		"/pics/h_coil.tga",
		"Coil",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 5-JUN-99
/*QUAKED item_lizzyhead (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/head/tris.md2"  
*/
	{
		"item_lizzyhead",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/lizzyhead.wav",
		"models/pu_icon/head/head.mdx", 0,
		NULL,
		"/pics/h_lizzyhead.tga",
		"Lizzy Head",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

/*QUAKED item_cashroll (.3 .3 1) (-16 -16 -16) (16 16 16)
currentcash - set amount of cash in roll  
model="models/pu_icon/cash/tris.md2"  
*/
	{
		"item_cashroll",
		Pickup_Cash,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/cash.wav",
		"models/pu_icon/cash/tris.md2", 0,
		NULL,
		// JOSEPH 26-JAN-99-C
		"/pics/hh_money.tga",
		"Cash",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},	

// JOSEPH 2-MAR-99
/*QUAKED item_cashbaglarge (.3 .3 1) (-16 -16 -16) (16 16 16)
currentcash - set amount of cash in the bag  
model="models/pu_icon/money/money_lg.md2"  
*/
	{
		"item_cashbaglarge",
		Pickup_Cash,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/cash.wav",
		"models/pu_icon/money/money_lg.md2", 0,
		NULL,
		// JOSEPH 26-JAN-99-C
		"/pics/hh_money.tga",
		"Large Cash Bag",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},	

/*QUAKED item_cashbagsmall (.3 .3 1) (-16 -16 -16) (16 16 16)
currentcash - set amount of cash in the bag  
model="models/pu_icon/money/money_sm.md2"  
*/
	{
		"item_cashbagsmall",
		Pickup_Cash,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/cash.wav",
		"models/pu_icon/money/money_sm.md2", 0,
		NULL,
		// JOSEPH 26-JAN-99-C
		"/pics/hh_money.tga",
		"Small Cash Bag",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},	
// END JOSEPH
	

/*QUAKED item_battery (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/battery/tris.md2"  
*/
	{
		"item_battery",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/battery/tris.md2", 0,
		NULL,
		"/pics/h_bat.tga",
		"Battery",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},		


// JOSEPH 2-MAR-99
/*QUAKED item_jetpack (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/items/misc/jetpack/jetpack.mdx"
*/
	{
		"item_jetpack",
		Pickup_JetPack,
		Use_JetPack,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/items/misc/jetpack/jetpack.mdx", 0,
		NULL,
/* icon */		"/pics/h_jetpack.tga",
		"Jet Pack",
		0,
		0,
		NULL,
		IT_STAY_COOP|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},			
// END JOSEPH

// JOSEPH 10-FEB-99
/*QUAKED item_health_sm (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/health_s/tris.md2"  
*/
	{
		"item_health_sm",
		Pickup_Health_Small,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/health.wav",
		"models/pu_icon/health_s/tris.md2", 0,
		NULL,
		"/pics/h_smed.tga",
		"Small Health",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},			
	
/*QUAKED item_health_lg (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/health/tris.md2"  
*/
	{
		"item_health_lg",
		Pickup_Health_Large,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/health.wav",
		"models/pu_icon/health/tris.md2", 0,
		NULL,
		"/pics/h_lmed.tga",
		"Large Health",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},		
// END JOSEPH


/*QUAKED item_flashlight (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/f_light/tris.md2"  
*/
	{
		"item_flashlight",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/f_light/tris.md2", 0,
		NULL,
		"/pics/h_flashl.tga",
		"Flashlight",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_FLASHLIGHT,
		NULL,
		0,
/* precache */ ""
	},		

// JOSEPH 12-MAR-99	
/*QUAKED item_watch (.3 .3 1) (-16 -16 -16) (16 16 16)

Watch for Lenny
  
model="models/pu_icon/watch/tris.md2"  
*/
	{
		"item_watch",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/watch/tris.md2", 0,
		NULL,
		"/pics/h_watch.tga",
		"Watch",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 24-MAR-99	
/*QUAKED item_whiskey (.3 .3 1) (-16 -16 -16) (16 16 16)

model="models/pu_icon/whiskey/tris.md2"  

Whiskey for the bum
  
*/
	{
		"item_whiskey",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/whiskey/tris.md2", 0,
		NULL,
		"/pics/h_bottle.tga",
		"Whiskey",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 30-MAY-99
/*QUAKED item_pack (.3 .3 1) (-16 -16 -16) (16 16 16)
model="models/pu_icon/backpack/tris.md2"
*/
	{
		"item_pack",
		Pickup_Pack,
		NULL,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/backpack/tris.md2", 0,
		NULL,
/* icon */		"/pics/h_backpack.tga",
/* pickup */	"Ammo Pack",
/* width */		2,
		180,
		NULL,
		IT_NOCHEATS|IT_FLASHLIGHT,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 29-MAY-99
/*QUAKED item_adrenaline (.3 .3 1) (-16 -16 -16) (16 16 16)
gives +1 to maximum health
model="models/pu_icon/adrenaline/tris.md2"
*/
	{
		"item_adrenaline",
		Pickup_Adrenaline,
		NULL,
		NULL,
		NULL,
		"world/pickups/health.wav",
		"models/pu_icon/adrenaline/tris.md2", 0,
		NULL,
		"/pics/h_smed.tga",
/* pickup */	"Adrenaline",
/* width */		2,
		60,
		NULL,
		IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 7-MAY-99
/*QUAKED key_fuse (0 .5 .8) (-8 -8 -16) (8 8 16) TRIGGER_SPAWN NO_TOUCH
*/
	{
		"key_fuse",
		Pickup_Key,
		NULL,
		NULL,
		NULL,
		"world/pickups/coil.wav",
		"models/pu_icon/fuse/tris.md2", 0,
		NULL,
		"/pics/h_fuse.tga",
		"Fuse",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 4-MAY-99
/*QUAKED item_safedocs (.3 .3 1) (-16 -16 -16) (16 16 16)
Safe docs for the louie in PV
model="models/pu_icon/folder/tris.md2"  
*/
	{
		"item_safedocs",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/folder/tris.md2", 0,
		NULL,
		"/pics/h_safedocs.tga",
		"Safe docs",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

/*QUAKED item_valve (.3 .3 1) (-16 -16 -16) (16 16 16)
A valve dial turn key
model="models/pu_icon/valve/tris.md2" 
*/
	{
		"item_valve",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/valve/tris.md2", 0,
		NULL,
		"/pics/h_valve.tga",
		"Valve",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

// JOSEPH 25-MAY-99
/*QUAKED item_oilcan (.3 .3 1) (-16 -16 -16) (16 16 16)
An oil can
model="models/pu_icon/oilcan/tris.md2" 
*/
	{
		"item_oilcan",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
		"world/pickups/generic.wav",
		"models/pu_icon/oilcan/tris.md2", 0,
		NULL,
		"/pics/h_oilcan.tga",
		"Oil Can",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

	// Kingpin keys


// JOSEPH 16-MAR-99

/*QUAKED key_key1 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 1
model="models/pu_icon/key/key_a.md2"  
*/
	{
		"key_key1",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_a.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"StoreRoomKey",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

/*QUAKED key_key2 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 2
model="models/pu_icon/key/key_b.md2" 
*/
	{
		"key_key2",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_b.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Electrical_Room",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

/*QUAKED key_key3 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 3
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key3",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Chem_Plant_Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

/*QUAKED key_key4 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 4
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key4",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Bridge_Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

/*QUAKED key_key5 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 5
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key5",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Shipyard_Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

/*QUAKED key_key6 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 6
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key6",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Warehouse_Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

/*QUAKED key_key7 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 7
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key7",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Shop_Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

// JOSEPH 6-JUN-99
/*QUAKED key_key8 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 8
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key8",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_ticket.tga",
		"Ticket",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH

/*QUAKED key_key9 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 9
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key9",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Office_Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

/*QUAKED key_key10 (0 .5 .8) (-16 -16 -16) (16 16 16)
key 10
model="models/pu_icon/key/key_c.md2" 
*/
	{
		"key_key10",
		Pickup_Key,
		Use_Null,
		NULL,
		NULL,
        "world/pickups/keys.wav",
		"models/pu_icon/key/key_c.md2", 0,
		NULL,
		"/pics/h_key.tga",
		"Key10",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY|IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},
// END JOSEPH


	//==========================================================================================
	// OLD QUAKE2 ITEMS

	//
	// POWERUP ITEMS
	//
#if 0
/*UAKED item_quad (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_quad", 
		Pickup_Powerup,
		Use_Quad,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/quaddama/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"p_quad",
/* pickup */	"Quad Damage",
/* width */		2,
		60,
		NULL,
		IT_POWERUP,
		NULL,
		0,
/* precache */ "items/damage.wav items/damage2.wav items/damage3.wav"
	},

/*UAKED item_quadfire (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_quadfire", 
		Pickup_Powerup,
		Use_QuadFire,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/quadfire/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"p_quadfire",
/* pickup */	"QuadFire Damage",
/* width */		2,
		60,
		NULL,
		IT_POWERUP,
		NULL,
		0,
/* precache */ "items/damage.wav items/damage2.wav items/damage3.wav"
	},

	
/*UAKED item_invulnerability (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_invulnerability",
		Pickup_Powerup,
		Use_Invulnerability,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/invulner/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"p_invulnerability",
/* pickup */	"Invulnerability",
/* width */		2,
		300,
		NULL,
		IT_POWERUP,
		NULL,
		0,
/* precache */ "items/protect.wav items/protect2.wav items/protect4.wav"
	},

/*UAKED item_silencer (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_silencer",
		Pickup_Powerup,
		Use_Silencer,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/pu_icon/silencer/tris.md2", 0,
		NULL,
/* icon */		"p_silencer",
/* pickup */	"Silencer",
/* width */		2,
		60,
		NULL,
		IT_POWERUP,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED item_breather (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_breather",
		Pickup_Powerup,
		Use_Breather,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/breather/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"p_rebreather",
/* pickup */	"Rebreather",
/* width */		2,
		60,
		NULL,
		IT_STAY_COOP|IT_POWERUP,
		NULL,
		0,
/* precache */ "items/airout.wav"
	},

/*UAKED item_enviro (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_enviro",
		Pickup_Powerup,
		Use_Envirosuit,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/enviro/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"p_envirosuit",
/* pickup */	"Environment Suit",
/* width */		2,
		60,
		NULL,
		IT_STAY_COOP|IT_POWERUP,
		NULL,
		0,
/* precache */ "items/airout.wav"
	},

/*UAKED item_ancient_head (.3 .3 1) (-16 -16 -16) (16 16 16)
Special item that gives +2 to maximum health
*/
	{
		"item_ancient_head",
		Pickup_AncientHead,
		NULL,
		NULL,
		NULL,
		"items/pkup.wav",
		"models/items/c_head/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"i_fixme",
/* pickup */	"Ancient Head",
/* width */		2,
		60,
		NULL,
		0,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED item_bandolier (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_bandolier",
		Pickup_Bandolier,
		NULL,
		NULL,
		NULL,
		"items/pkup.wav",
		"models/items/band/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"p_bandolier",
/* pickup */	"Bandolier",
/* width */		2,
		60,
		NULL,
		0,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED item_pack (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
	{
		"item_pack",
		Pickup_Pack,
		NULL,
		NULL,
		NULL,
		"items/pkup.wav",
		"models/items/pack/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"i_pack",
/* pickup */	"Ammo Pack",
/* width */		2,
		180,
		NULL,
		0,
		NULL,
		0,
/* precache */ ""
	},

	//
	// KEYS
	//
/*UAKED key_data_cd (0 .5 .8) (-16 -16 -16) (16 16 16)
key for computer centers
*/
	{
		"key_data_cd",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/data_cd/tris.md2", EF_ROTATE,
		NULL,
		"k_datacd",
		"Data CD",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

// JOSEPH 30-APR-99
/*UAKED key_fuse (0 .5 .8) (-16 -16 -16) (16 16 16) TRIGGER_SPAWN NO_TOUCH
warehouse circuits
*/
// END JOSEPH
	{
		"key_fuse",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"world/pickups/coil.wav",
		"models/pu_icon/coil/tris.md2", EF_ROTATE,
		NULL,
		"/pics/h_coil.tga",
		"Fuse",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED key_pyramid (0 .5 .8) (-16 -16 -16) (16 16 16)
key for the entrance of jail3
*/
	{
		"key_pyramid",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/pyramid/tris.md2", EF_ROTATE,
		NULL,
		"k_pyramid",
		"Pyramid Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED key_data_spinner (0 .5 .8) (-16 -16 -16) (16 16 16)
key for the city computer
*/
	{
		"key_data_spinner",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/spinner/tris.md2", EF_ROTATE,
		NULL,
		"k_dataspin",
		"Data Spinner",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED key_pass (0 .5 .8) (-16 -16 -16) (16 16 16)
security pass for the security level
*/
	{
		"key_pass",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/pass/tris.md2", EF_ROTATE,
		NULL,
		"k_security",
		"Security Pass",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED key_blue_key (0 .5 .8) (-16 -16 -16) (16 16 16)
normal door key - blue
*/
	{
		"key_blue_key",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/key/tris.md2", EF_ROTATE,
		NULL,
		"k_bluekey",
		"Blue Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},


/*UAKED key_red_key (0 .5 .8) (-16 -16 -16) (16 16 16)
normal door key - red
*/
	{
		"key_red_key",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/red_key/tris.md2", EF_ROTATE,
		NULL,
		"k_redkey",
		"Red Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},


// RAFAEL
/*UAKED key_green_key (0 .5 .8) (-16 -16 -16) (16 16 16)
normal door key - blue
*/
	{
		"key_green_key",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/green_key/tris.md2", EF_ROTATE,
		NULL,
		"k_green",
		"Green Key",
		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED key_commander_head (0 .5 .8) (-16 -16 -16) (16 16 16)
tank commander's head
*/
	{
		"key_commander_head",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/monsters/commandr/head/tris.md2", EF_GIB,
		NULL,
/* icon */		"k_comhead",
/* pickup */	"Commander's Head",
/* width */		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

/*UAKED key_airstrike_target (0 .5 .8) (-16 -16 -16) (16 16 16)
tank commander's head
*/
	{
		"key_airstrike_target",
		Pickup_Key,
		NULL,
		Drop_General,
		NULL,
		"items/pkup.wav",
		"models/items/keys/target/tris.md2", EF_ROTATE,
		NULL,
/* icon */		"i_airstrike",
/* pickup */	"Airstrike Marker",
/* width */		2,
		0,
		NULL,
		IT_STAY_COOP|IT_KEY,
		NULL,
		0,
/* precache */ ""
	},

	{
		NULL,
		Pickup_Health,
		NULL,
		NULL,
		NULL,
		"items/pkup.wav",
		NULL, 0,
		NULL,
/* icon */		"i_health",
/* pickup */	"Health",
/* width */		3,
		0,
		NULL,
		0,
		NULL,
		0,
/* precache */ ""
	},
#endif
	{
		NULL,
		Pickup_Pistol_Mods,
		NULL,
		NULL,
		NULL,
		"misc/w_pkup.wav",
		NULL, 0,
		NULL,
/* icon */		NULL,//"i_pistol_mods",
/* pickup */	"Pistol_Mods",
/* width */		3,
		0,
		NULL,
		IT_NOCHEATS,
		NULL,
		0,
/* precache */ ""
	},

	// end of list marker
	{NULL}
};
// END JOSEPH


// JOSEPH 13-JUN-99
/*QUAKED hmg_mod_cooling (.7 .3 .4) (-16 -16 -16) (16 16 16)
model="models/pu_icon/modcool/tris.md2" 
*/
void SP_hmg_mod_cooling (edict_t *self)
{
	self->model = "models/pu_icon/coolmod/tris.md2";
	self->count = 4;
	SpawnItem (self, FindItem ("Pistol_Mods"));
	self->item->icon = "/pics/h_heavymachinegun_cooling.tga";
	//gi.soundindex ("items/pistol_mods.wav");
}
// END JOSEPH

// JOSEPH 1-APR-99
/*QUAKED pistol_mod_rof (.7 .3 .4) (-16 -16 -16) (16 16 16)
model="models/pu_icon/ro_fire_mod/tris.md2" 
*/
void SP_pistol_mod_rof (edict_t *self)
{
	self->model = "models/pu_icon/ro_fire_mod/tris.md2";
	self->count = 1;
	SpawnItem (self, FindItem ("Pistol_Mods"));
	//gi.soundindex ("items/pistol_mods.wav");
}

/*QUAKED pistol_mod_reload (.7 .3 .4) (-16 -16 -16) (16 16 16)
model="models/pu_icon/reload_mod/tris.md2" 
model="models/pu_icon/reload_mod/tris.md2" 
*/
void SP_pistol_mod_reload (edict_t *self)
{
	self->model = "models/pu_icon/reload_mod/tris.md2";
	self->count = 2;
	SpawnItem (self, FindItem ("Pistol_Mods"));
	//gi.soundindex ("items/pistol_mods.wav");
}

/*QUAKED pistol_mod_damage (.7 .3 .4) (-16 -16 -16) (16 16 16)
model="models/pu_icon/magmod/tris.md2" 
*/
void SP_pistol_mod_damage (edict_t *self)
{
	self->model = "models/pu_icon/magmod/tris.md2";
	self->count = 3;
	SpawnItem (self, FindItem ("Pistol_Mods"));
	//gi.soundindex ("items/pistol_mods.wav");
}
// END JOSEPH

/*UAKED item_health (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
void SP_item_health (edict_t *self)
{
	if ( deathmatch->value && ((int)dmflags->value & DF_NO_HEALTH) )
	{
		G_FreeEdict (self);
		return;
	}

	self->model = "models/items/healing/medium/tris.md2";
	self->count = 10;
	SpawnItem (self, FindItem ("Health"));
	gi.soundindex ("items/n_health.wav");
}

/*UAKED item_health_small (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
void SP_item_health_small (edict_t *self)
{
	if ( deathmatch->value && ((int)dmflags->value & DF_NO_HEALTH) )
	{
		G_FreeEdict (self);
		return;
	}

	self->model = "models/items/healing/stimpack/tris.md2";
	self->count = 2;
	SpawnItem (self, FindItem ("Health"));
	self->style = HEALTH_IGNORE_MAX;
	gi.soundindex ("items/s_health.wav");
}

/*UAKED item_health_large (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
void SP_item_health_large (edict_t *self)
{
	if ( deathmatch->value && ((int)dmflags->value & DF_NO_HEALTH) )
	{
		G_FreeEdict (self);
		return;
	}

	self->model = "models/items/healing/large/tris.md2";
	self->count = 25;
	SpawnItem (self, FindItem ("Health"));
	gi.soundindex ("items/l_health.wav");
}

/*UAKED item_health_mega (.3 .3 1) (-16 -16 -16) (16 16 16)
*/
void SP_item_health_mega (edict_t *self)
{
	if ( deathmatch->value && ((int)dmflags->value & DF_NO_HEALTH) )
	{
		G_FreeEdict (self);
		return;
	}

	self->model = "models/items/mega_h/tris.md2";
	self->count = 100;
	SpawnItem (self, FindItem ("Health"));
	gi.soundindex ("items/m_health.wav");
	self->style = HEALTH_IGNORE_MAX|HEALTH_TIMED;
}

// RAFAEL
void SP_item_foodcube (edict_t *self)
{
	if ( deathmatch->value && ((int)dmflags->value & DF_NO_HEALTH) )
	{
		G_FreeEdict (self);
		return;
	}

	self->model = "models/objects/trapfx/tris.md2";
	SpawnItem (self, FindItem ("Health"));
	self->spawnflags |= DROPPED_ITEM;
	self->style = HEALTH_IGNORE_MAX;
	gi.soundindex ("items/s_health.wav");
	self->classname = "foodcube";
}

void InitItems (void)
{
	game.num_items = sizeof(itemlist)/sizeof(itemlist[0]) - 1;
}



/*
===============
SetItemNames

Called by worldspawn
===============
*/
void SetItemNames (void)
{
	int		i;
	gitem_t	*it;

	for (i=0 ; i<game.num_items ; i++)
	{
		it = &itemlist[i];
		gi.configstring (CS_ITEMS+i, it->pickup_name);
	}

	jacket_armor_index = ITEM_INDEX(FindItem("Jacket Armor"));
	combat_armor_index = ITEM_INDEX(FindItem("Combat Armor"));
	body_armor_index   = ITEM_INDEX(FindItem("Body Armor"));
	power_screen_index = ITEM_INDEX(FindItem("Power Screen"));
	power_shield_index = ITEM_INDEX(FindItem("Power Shield"));
}
