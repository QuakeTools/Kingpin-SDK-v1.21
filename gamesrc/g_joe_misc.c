// g_joe_misc.c

// JOSEPH 14-JUN-99 ALL

#include "g_local.h"

/*QUAKED props_hydrant (0 .5 .8) (-10 -10 -19) (10 10 19)

A hydrant that does jack

model="models\props\hydrant\"
*/

void metal_explode (edict_t *self)
{
	vec3_t	 org;
	float	 spd;
	vec3_t	 save;
	edict_t *breakit;
	extern void breakittrash_sound (edict_t *self);
	
	VectorCopy (self->s.origin, save);
	VectorMA (self->absmin, 0.5, self->size, self->s.origin);

	// a few big chunks
	spd = 1.5 * (float)self->dmg / 200.0;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	// bottom corners
	spd = 1.75 * (float)self->dmg / 200.0;
	VectorCopy (self->absmin, org);
	ThrowDebris (self, "models/props/metal/metal2.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	ThrowDebris (self, "models/props/metal/metal3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal4.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal5.md2", spd, org);

	// a bunch of little chunks
	spd = 2 * self->dmg / 200;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	breakit = NULL;
	
	breakit = G_Spawn();
	
	if (breakit)
	{
		breakit->think = breakittrash_sound;
		breakit->nextthink = level.time + 0.1;
		VectorCopy (self->s.origin, breakit->s.origin);
		gi.linkentity(breakit);
	}
	
	VectorCopy (save, self->s.origin);

	G_FreeEdict (self);
}

void metal_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = metal_explode;
}

void SP_props_hydrant (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/hydrant/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -10, -10, -19);
	VectorSet (self->maxs, 10, 10, 19);		
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_antenna1a (0 .5 .8) (-28 -22 -22) (28 22 22)

An antenna

model="models\props\antenna\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna1a (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antenna/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -28, -22, -22);
	VectorSet (self->maxs, 28, 22, 22);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/antenna/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/antenna/antenna.mdx", &self->s.model_parts[PART_HEAD]);	
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna2a (0 .5 .8) (-26 -30 -22) (26 30 22)

An antenna

model="models\props\ant2a\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna2a (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antenna2/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -26, -30, -22);
	VectorSet (self->maxs, 26, 30, 22);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant2a/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant2a/antenna.mdx", &self->s.model_parts[PART_HEAD]);	

	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna3a (0 .5 .8) (-14 -2 -22) (14 2 22)

An antenna

model="models\props\ant3a\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna3a (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antenna3/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -14, -2, -22);
	VectorSet (self->maxs, 14, 2, 22);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant3a/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant3a/antenna.mdx", &self->s.model_parts[PART_HEAD]);	
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna1b (0 .5 .8) (-41 -33 -32) (41 33 32)

An antenna

model="models\props\ant1b\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna1b (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antennab/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -41, -33, -32);
	VectorSet (self->maxs, 41, 33, 32);	

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant1b/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant1b/antenna.mdx", &self->s.model_parts[PART_HEAD]);	
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna2b (0 .5 .8) (-38 -45 -32) (38 45 32)

An antenna

model="models\props\ant2b\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna2b (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antenna2b/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -38, -45, -32);
	VectorSet (self->maxs, 38, 45, 32);	

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant2b/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant2b/antenna.mdx", &self->s.model_parts[PART_HEAD]);	
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna3b (0 .5 .8) (-21 -3 -33) (21 3 33)

An antenna

model="models\props\ant3b\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna3b (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antenna3b/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -21, -3, -33);
	VectorSet (self->maxs, 21, 3, 33);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant3b/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant3b/antenna.mdx", &self->s.model_parts[PART_HEAD]);	
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna1c (0 .5 .8) (-55 -44 -43) (55 44 43)

An antenna

model="models\props\ant1c\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna1c (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antennac/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -55, -44, -43);
	VectorSet (self->maxs, 55, 44, 43);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant1c/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant1c/antenna.mdx", &self->s.model_parts[PART_HEAD]);	

	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;	
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna2c (0 .5 .8) (-50 -60 -43) (60 50 43)

An antenna

model="models\props\ant2c\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna2c (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}	

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antenna2c/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -50, -60, -43);
	VectorSet (self->maxs, 50, 60, 43);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant2c/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant2c/antenna.mdx", &self->s.model_parts[PART_HEAD]);	
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_antenna3c (0 .5 .8) (-28 -3 -44) (28 3 44)

An antenna

model="models\props\ant3c\antenna.mdx"
skin="models\props\antenna\antenna.pcx"
*/

void SP_props_antenna3c (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}	

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	//self->model = "models/props/antenna3c/tris.md2";
	//self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -28, -3, -44);
	VectorSet (self->maxs, 28, 3, 44);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ant3c/antenna.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ant3c/antenna.mdx", &self->s.model_parts[PART_HEAD]);	
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}


/*QUAKED props_fan (0 .5 .8) (-8 -12 -16) (8 12 16)

A fan

model="models\props\fan\tris.md2"
*/

void think_fan (edict_t *self)
{
	if (self->s.frame < 18)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}

	self->nextthink = level.time + FRAMETIME;
}

void radio_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject);

void SP_props_fan (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/fan/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -8, -12, -16);
	VectorSet (self->maxs, 8, 12, 16);		

	self->die = radio_die;
	self->takedamage = DAMAGE_YES;
	
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);

	self->nextthink = level.time + FRAMETIME *2;
	self->think = think_fan;
}

/*QUAKED props_aircon (0 .5 .8) (-16 -16 -24) (16 16 24)

A cool box deluxe

model="models\props\aircon\tris.md2"
*/

void think_aircon (edict_t *self)
{
	if (self->s.frame < 18)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}

	self->nextthink = level.time + FRAMETIME;
}

void SP_props_aircon (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/aircon/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 24);		
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
	
	self->nextthink = level.time + FRAMETIME *2;
	self->think = think_aircon;
}

// JOSEPH 12-OCT-98
/*QUAKED props_phone (0 .5 .8) (-8 -8 -6) (8 8 6)

A phone (telephone)

model="models\props\phone\tris.md2"
*/

void SP_props_phone (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/phone/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -8, -8, -6);
	VectorSet (self->maxs, 8, 8, 6);		

	self->die = radio_die;
	self->takedamage = DAMAGE_YES;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

// JOSEPH 12-OCT-98

// JOSEPH 13-FEB-99
/*QUAKED props_tablesetA (0 .5 .8) (-26 -27 -6) (26 27 6)

Card-shark table setting

model="models\props\tablesets\set.mdx"
skin="models\props\tablesets\card_skin.pcx"
*/

void SP_props_tablesetA (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -26, -27, -6);
	VectorSet (self->maxs, 26, 27, 6);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/tablesets/set.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/tablesets/set.mdx", &self->s.model_parts[PART_HEAD]);
	
	// JOSEPH 24-JAN-99
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	// JOSEPH 5-FEB-99-B
	self->s.renderfx2 |= RF2_NOSHADOW;
	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

// END JOSEPH

/*QUAKED props_radio (0 .5 .8) (-8 -12 -8) (8 12 8)

A radio that will take damage and activate triggers on destruction

"health" - hit points (25 default)

model="models\props\radio\tris.md2"
*/

void radio_explode (edict_t *self)
{
	vec3_t	org;
	float	spd;
	vec3_t	save;

	VectorCopy (self->s.origin, save);
	VectorMA (self->absmin, 0.5, self->size, self->s.origin);

	// a few big chunks
	spd = 1.5 * (float)self->dmg / 200.0;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	// bottom corners
	spd = 1.75 * (float)self->dmg / 200.0;
	VectorCopy (self->absmin, org);
	ThrowDebris (self, "models/props/metal/metal2.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	ThrowDebris (self, "models/props/metal/metal3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal4.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal5.md2", spd, org);

	// a bunch of little chunks
	spd = 2 * self->dmg / 200;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	VectorCopy (save, self->s.origin);

	G_FreeEdict (self);
}

void radio_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = radio_explode;
	self->activator = attacker;

	G_UseTargets (self, inflictor);
	
	{
		vec3_t realorigin;

		VectorCopy(self->s.origin, realorigin);
		realorigin[2] += 8;

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_SPLASH);
		gi.WriteByte (25);
		gi.WritePosition (realorigin);
		gi.WriteDir (self->movedir);
		gi.WriteByte (1);
		gi.multicast (realorigin, MULTICAST_PVS);
	}
}

void SP_props_radio (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/radio/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -8, -12, -8);
	VectorSet (self->maxs, 8, 12, 8);		
	
	if (!(self->health == 666))
	{
		self->die = radio_die;
		self->takedamage = DAMAGE_YES;

		if (!self->health)
			self->health = 25;
	}

	self->surfacetype = SURF_METAL_L;	
	gi.linkentity (self);
}

/*QUAKED elements_raincloud (0 .5 .8) ?
Snow falls from this invisable cloud at random points   

center of cloud to ground trace determines the drop fall distance

cloud can be any recatangle size
  
fxdensity - total number of drops in the sky 1 - 1000 (default 400) 

firetype - type of drops, 0 = rain 1 = drip
*/

void think_new_first_raincloud (edict_t *self)
{
	vec3_t	neworigin, minmaxsize;
	int		effectsizex, effectsizey, effectsizez;
	
	// Find cloud size
	VectorSubtract(self->mins, self->maxs, minmaxsize);
	effectsizex = abs(minmaxsize[0])-2;
	effectsizey = abs(minmaxsize[1])-2;
	effectsizez = abs(minmaxsize[2])-2;

	// Find cloud center
	VectorCopy(self->mins, neworigin);
	neworigin[0] += (effectsizex >> 1);
	neworigin[1] += (effectsizey >> 1);
	neworigin[2] += (effectsizez >> 1);

	// Adjust rain density
	if (!self->fxdensity)
		self->fxdensity = 400;		 
	else if (self->fxdensity > 1000)
		self->fxdensity = 1000;	

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_RAIN);
	gi.WritePosition (neworigin);
	gi.WriteShort (self->fxdensity);
	gi.WriteShort (effectsizex);
	gi.WriteShort (effectsizey);
	gi.WriteShort (effectsizez);	
	gi.WriteShort (self->firetype);
	gi.multicast (neworigin, MULTICAST_ALL_R);	
}

void SP_elements_raincloud (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BSP;
	self->movetype = MOVETYPE_NONE;
	gi.setmodel (self, self->model);
	gi.linkentity (self);
	self->nextthink = level.time + (10 * FRAMETIME);
	self->think = think_new_first_raincloud;
	self->svflags |= SVF_NOCLIENT;
}
							
/*QUAKED elements_snowcloud (0 .5 .8) ?
Snow falls from this invisable cloud at random points   

center of cloud to ground trace determines the flake fall distance

cloud can be any recatangle size
  
fxdensity - total number of flakes in the sky 1 - 1000 (default 400) 
*/

void think_new_first_snowcloud (edict_t *self)
{
	vec3_t	neworigin, minmaxsize;
	int		effectsizex, effectsizey, effectsizez;

	// Find cloud size
	VectorSubtract(self->mins, self->maxs, minmaxsize);
	effectsizex = abs(minmaxsize[0])-2;
	effectsizey = abs(minmaxsize[1])-2;
	effectsizez = abs(minmaxsize[2])-2;

	// Find cloud center
	VectorCopy(self->mins, neworigin);
	neworigin[0] += (effectsizex >> 1);
	neworigin[1] += (effectsizey >> 1);
	neworigin[2] += (effectsizez >> 1);

	// Adjust snow density
	if (!self->fxdensity)
		self->fxdensity = 400;		 
	else if (self->fxdensity > 1000)
		self->fxdensity = 1000;	
	
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SNOW);
	gi.WritePosition (neworigin);
	gi.WriteShort (self->fxdensity);
	gi.WriteShort (effectsizex);
	gi.WriteShort (effectsizey);
	gi.WriteShort (effectsizez);	
	gi.multicast (neworigin, MULTICAST_ALL_R);	
}

void SP_elements_snowcloud (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BSP;
	self->movetype = MOVETYPE_NONE;
	gi.setmodel (self, self->model);
	gi.linkentity (self);
	self->nextthink = level.time + (10 * FRAMETIME);
	self->think = think_new_first_snowcloud;
	self->svflags |= SVF_NOCLIENT;
}

#define NON_MOVEABLE   2
#define TYPE_WOOD      4
#define TYPE_WOOD2     8
#define TYPE_METAL     16
#define TYPE_CARDBOARD 32

// JOSEPH 04-JAN-99
/*QUAKED props_trashcanA (0 .5 .8) (-16 -16 -21) (16 16 21) ? NON_MOVEABLE
Trash can you can push.  You can override its mass (400),
health (10).

"item" - Item to spawn on destruction 

model="models\props\t_can\"
*/

void trashcanA_check_sound (edict_t *ent)
{
	if (((ent->s.origin[1] == ent->save_avel[1]) && (ent->s.origin[0] == ent->save_avel[0])) ||
		(ent->groundentity == NULL)) 
	{
		ent->s.sound = 0;
	}
}


// JOSEPH 5-FEB-99-B
void trashcanA_explode (edict_t *self);

void trashcanA_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	float	ratio;
	vec3_t	v;

	if ((!other->groundentity) || (other->groundentity == self))
		return;

	self->pullingflag = 0;

	// If activate key is pressed
	if ((plane) && (plane->type == 123))
	{
		if ((other->s.origin[0] != other->s.old_origin[0]) || (other->s.origin[1] != other->s.old_origin[1]))
		{
			//vec3_t	 move;
			//float	 yaw, dist;
			
			self->pullingflag = 1;
			
			ratio = (float)other->mass / (float)self->mass;
			VectorSubtract (self->s.origin, other->s.origin, v);
			M_walkmove (self, 180+vectoyaw(v), 20 * ratio * FRAMETIME);
			
			/*yaw = vectoyaw(v);
			yaw = yaw*M_PI*2 / 360;
			dist = 20 * ratio * FRAMETIME;

			move[0] = cos(yaw)*dist;
			move[1] = sin(yaw)*dist;
			move[2] = 0;

			if (abs(other->client->ps.pmove.velocity[0]) > abs(move[0]))
				other->client->ps.pmove.velocity[0] = move[0];
			if (abs(other->client->ps.pmove.velocity[1]) > abs(move[1]))
				other->client->ps.pmove.velocity[1] = move[1];*/
			
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/trash1.wav");
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}
	else
	{	
		ratio = (float)other->mass / (float)self->mass;
		VectorSubtract (self->s.origin, other->s.origin, v);
		M_walkmove (self, vectoyaw(v), 20 * ratio * FRAMETIME);

		if (((self->s.origin[0] != self->s.old_origin[0]) || (self->s.origin[1] != self->s.old_origin[1])))
		{
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/trash1.wav");	
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}

	if (self->health <= 0)
      trashcanA_explode(self);
}	
// END JOSEPH

// JOSEPH 5-FEB-99-C
void breakittrash_sound (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, gi.soundindex("world/trash3.wav"), 1, ATTN_NORM, 0);
	self->think = G_FreeEdict;
	self->nextthink = level.time + 2.0;
}

void trashcanA_explode (edict_t *self)
{
	vec3_t	org;
	float	spd;
	vec3_t	save;
	edict_t *breakit;

	VectorCopy (self->s.origin, save);
	VectorMA (self->absmin, 0.5, self->size, self->s.origin);

	// a few big chunks
	spd = 1.5 * (float)self->dmg / 200.0;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	// bottom corners
	spd = 1.75 * (float)self->dmg / 200.0;
	VectorCopy (self->absmin, org);
	ThrowDebris (self, "models/props/metal/metal2.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	ThrowDebris (self, "models/props/metal/metal3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal4.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal5.md2", spd, org);

	// a bunch of little chunks
	spd = 2 * self->dmg / 200;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	if (self->item)
	{
		Drop_Item (self, self->item);
		self->item = NULL;
	}
	
	breakit = G_Spawn();
	
	if (breakit)
	{
		breakit->think = breakittrash_sound;
		breakit->nextthink = level.time + 0.1;
		VectorCopy (self->s.origin, breakit->s.origin);
		gi.linkentity(breakit);
	}

	VectorCopy (save, self->s.origin);
	G_FreeEdict (self);
}
// END JOSEPH

void crate_stuff (edict_t *self)
{
	vec3_t	org;
	float	spd;
	vec3_t	save;

	VectorCopy (self->s.origin, save);
	VectorMA (self->absmin, 0.5, self->size, self->s.origin);

	// a few big chunks
	spd = 7.0 * (float)self->dmg / 200.0;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);

	// bottom corners
	spd = 6.0 * (float)self->dmg / 200.0;
	VectorCopy (self->absmin, org);
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[1] += self->size[1];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	org[1] += self->size[1];
	ThrowDebris_stuff (self, "models/props/stuff/piece2.md2", spd, org);

	// a bunch of little chunks
	spd = 10 * self->dmg / 200;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece2.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece3.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris_stuff (self, "models/props/stuff/piece2.md2", spd, org);
}

/*QUAKED props_crate_bust_32 (0 .5 .8) (-16 -16 -16) (16 16 16) ? NON_MOVEABLE TYPE_WOOD TYPE_WOOD2 TYPE_METAL TYPE_CARDBOARD
Crate can bust and you can push
health (10).

"item" - Item to spawn on destruction 

model="models\props\crate\stillcrate32_1.mdx"
*/

/*QUAKED props_crate_bust_48 (0 .5 .8) (-24 -24 -24) (24 24 24) ? NON_MOVEABLE TYPE_WOOD TYPE_WOOD2 X TYPE_CARDBOARD
Crate can bust and you can push
health (10).

"item" - Item to spawn on destruction 

model="models\props\crate\stillcrate48_1.mdx"
*/

/*QUAKED props_crate_bust_64 (0 .5 .8) (-32 -32 -32) (32 32 32) ? X TYPE_WOOD TYPE_WOOD2 X TYPE_CARDBOARD 
Crate you can bust
health (10).

"item" - Item to spawn on destruction 

model="models\props\crate\stillcrate64_1.mdx"
*/

void crate_check_sound (edict_t *ent)
{
	if (((ent->s.origin[1] == ent->save_avel[1]) && (ent->s.origin[0] == ent->save_avel[0])) ||
		(ent->groundentity == NULL)) 
	{
		ent->s.sound = 0;
	}
}

void crate_explode (edict_t *self);

void breakit_sound (edict_t *self)
{
	gi.sound (self, CHAN_VOICE, gi.soundindex("world/boardbreak.wav"), 1, ATTN_NORM, 0);
	self->think = G_FreeEdict;
	self->nextthink = level.time + 2.0;
}

void crate_bust_final_32 (edict_t *self)
{
    if (self->s.frame < 19)
	{
		if (self->item)
		{
			Drop_Item (self, self->item);
			self->item = NULL;
		}
		else
		{
			if (self->s.frame == 0)
				crate_stuff (self);
		}
		
		self->s.frame++;
		
		self->nextthink = level.time + 0.1;
	}
	else if (self->misstime-- > 0)
	{
		if (self->misstime <= 20)
		{
			if (self->misstime == 20)
			{
				self->s.renderfx2 |= RF2_PASSALPHA;
				self->s.effects = 1;		// this is full alpha now
			}
			
			self->s.effects += (255/20);
		
			if (self->s.effects > 255)
				self->s.effects = 255;
		}
		
		self->nextthink = level.time + 0.1;
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void crate_bust_die_32 (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	int i;
	
	if (self->takedamage == DAMAGE_NO)
		return;
	
	self->s.sound = 0;

	self->think = crate_bust_final_32;
	self->nextthink = level.time + FRAMETIME;

 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	
	if (self->spawnflags & TYPE_CARDBOARD)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/cardboard32.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/cardboard32.mdx", &self->s.model_parts[PART_HEAD]);

		self->takedamage = DAMAGE_NO;
		self->think = NULL;
		self->nextthink = 0;
		gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitcboard.wav"), 1, ATTN_NORM, 0);
		return;
	}
	
	if (self->spawnflags & TYPE_WOOD2)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/crate32_2.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/crate32_2.mdx", &self->s.model_parts[PART_HEAD]);
	}		
	else
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/crate32_1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/crate32_1.mdx", &self->s.model_parts[PART_HEAD]);	
	}

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->solid = 0;
	self->touch = NULL;
	gi.sound (self, CHAN_AUTO, gi.soundindex ("world/crate2.wav"), 1, ATTN_NORM, 0);
}	

void crate_touch_32 (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	float	ratio;
	vec3_t	v;

	if ((!other->groundentity) || (other->groundentity == self))
		return;

	self->pullingflag = 0;

	// If activate key is pressed
	if ((plane) && (plane->type == 123))
	{
		if ((other->s.origin[0] != other->s.old_origin[0]) || (other->s.origin[1] != other->s.old_origin[1]))
		{
			self->pullingflag = 1;
			
			ratio = (float)other->mass / (float)self->mass;
			VectorSubtract (self->s.origin, other->s.origin, v);
			M_walkmove (self, 180+vectoyaw(v), 20 * ratio * FRAMETIME);
		
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/crate1.wav");
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}
	else
	{	
		ratio = (float)other->mass / (float)self->mass;
		VectorSubtract (self->s.origin, other->s.origin, v);
		M_walkmove (self, vectoyaw(v), 20 * ratio * FRAMETIME);

		if (((self->s.origin[0] != self->s.old_origin[0]) || (self->s.origin[1] != self->s.old_origin[1])))
		{
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/crate1.wav");	
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}

	if (!(self->spawnflags & TYPE_METAL))
	{	
	if (self->health <= 0)
			crate_bust_die_32(self, 0, 0, 0, vec3_origin, 0, 0);
	}
}

void SP_props_crate_bust_32 (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;

	if (self->spawnflags & NON_MOVEABLE)
		self->movetype = MOVETYPE_NONE;
	else
	self->movetype = MOVETYPE_STEP;
	
	self->svflags |= SVF_PROP;	

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;

	if (self->spawnflags & TYPE_METAL)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate32.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate32.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_WOOD;
	}
	else if (self->spawnflags & TYPE_CARDBOARD)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcard32.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcard32.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_FABRIC;
	}
	else if (self->spawnflags & TYPE_WOOD2)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate32_2.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate32_2.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_WOOD;
	}		
	else
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate32_1.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate32_1.mdx", &self->s.model_parts[PART_HEAD]);	
		self->surfacetype = SURF_WOOD;
	}
	
	if (!(self->spawnflags & NON_MOVEABLE))
	{
		self->pullable = 1;
		self->nokickbackflag = 1;
		self->fallerflag = 1;
	}

	if (!self->mass)
		self->mass = 400;
	if (!self->health)
		self->health = 10;
	if (!self->dmg)
		self->dmg = 0;

	if (self->spawnflags & TYPE_METAL)
	{
		if (self->pullable)
			self->touch = crate_touch_32;	
	}
	else 
	{
		self->die = crate_bust_die_32;
		self->takedamage = DAMAGE_YES;
		if (self->pullable)
			self->touch = crate_touch_32;	
	}

	self->cast_info.aiflags = AI_NOSTEP;	

	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->misstime = 21;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}

	gi.linkentity (self);
}


void crate_bust_final_48 (edict_t *self)
{
    if (self->s.frame < 28)
	{
		if (self->item)
		{
			Drop_Item (self, self->item);
			self->item = NULL;
		}
		else
		{
			if (self->s.frame == 0)
				crate_stuff (self);
		}
			
		self->s.frame++;
		
		self->nextthink = level.time + 0.1;
	}
	else if (self->misstime-- > 0)
	{
		if (self->misstime <= 20)
		{
			if (self->misstime == 20)
			{
				self->s.renderfx2 |= RF2_PASSALPHA;
				self->s.effects = 1;		// this is full alpha now
			}
			
			self->s.effects += (255/20);
		
			if (self->s.effects > 255)
				self->s.effects = 255;
		}
		
		self->nextthink = level.time + 0.1;
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void crate_bust_die_48 (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	int i;
	
	if (self->takedamage == DAMAGE_NO)
		return;
	
	self->s.sound = 0;

	self->think = crate_bust_final_48;
	self->nextthink = level.time + FRAMETIME;

 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	
	if (self->spawnflags & TYPE_CARDBOARD)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/cardboard48.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/cardboard48.mdx", &self->s.model_parts[PART_HEAD]);

		self->takedamage = DAMAGE_NO;
		self->think = NULL;
		self->nextthink = 0;

		gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitcboard.wav"), 1, ATTN_NORM, 0);		
		return;
	}
	
	if (self->spawnflags & TYPE_WOOD2)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/crate48_2.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/crate48_2.mdx", &self->s.model_parts[PART_HEAD]);
	}		
	else
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/crate48_1.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/crate48_1.mdx", &self->s.model_parts[PART_HEAD]);	
	}

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->solid = 0;
	self->touch = NULL;
	gi.sound (self, CHAN_AUTO, gi.soundindex ("world/crate2.wav"), 1, ATTN_NORM, 0);
}	

void crate_touch_48 (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	float	ratio;
	vec3_t	v;

	if ((!other->groundentity) || (other->groundentity == self))
		return;

	self->pullingflag = 0;

	// If activate key is pressed
	if ((plane) && (plane->type == 123))
	{
		if ((other->s.origin[0] != other->s.old_origin[0]) || (other->s.origin[1] != other->s.old_origin[1]))
		{
			self->pullingflag = 1;
			
			ratio = (float)other->mass / (float)self->mass;
			VectorSubtract (self->s.origin, other->s.origin, v);
			M_walkmove (self, 180+vectoyaw(v), 20 * ratio * FRAMETIME);
		
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/crate1.wav");
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}
	else
	{	
		ratio = (float)other->mass / (float)self->mass;
		VectorSubtract (self->s.origin, other->s.origin, v);
		M_walkmove (self, vectoyaw(v), 20 * ratio * FRAMETIME);

		if (((self->s.origin[0] != self->s.old_origin[0]) || (self->s.origin[1] != self->s.old_origin[1])))
		{
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/crate1.wav");	
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}

	if (!(self->spawnflags & TYPE_METAL))
	{	
		if (self->health <= 0)
			crate_bust_die_48(self, 0, 0, 0, vec3_origin, 0, 0);
	}
}

void SP_props_crate_bust_48 (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	
	if (self->spawnflags & NON_MOVEABLE)
		self->movetype = MOVETYPE_NONE;
	else
		self->movetype = MOVETYPE_STEP;
	
	self->svflags |= SVF_PROP;	

	VectorSet (self->mins, -24.1, -24.1, -24.1);
	VectorSet (self->maxs, 24.1, 24.1, 24.1);
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;

	if (self->spawnflags & TYPE_METAL)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate48.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate48.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_WOOD;
	}
	else if (self->spawnflags & TYPE_CARDBOARD)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcard48.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcard48.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_FABRIC;
	}
	else if (self->spawnflags & TYPE_WOOD2)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate48_2.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate48_2.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_WOOD;
	}		
	else
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate48_1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate48_1.mdx", &self->s.model_parts[PART_HEAD]);	
		self->surfacetype = SURF_WOOD;
	}

	if (!(self->spawnflags & NON_MOVEABLE))
	{
		self->pullable = 1;
		self->nokickbackflag = 1;
	  self->fallerflag = 1;
	}
	
	if (!self->mass)
		self->mass = 400;
	if (!self->health)
		self->health = 10;
	if (!self->dmg)
		self->dmg = 0;

	if (self->spawnflags & TYPE_METAL)
	{
		if (self->pullable)
			self->touch = crate_touch_48;	
	}
	else 
	{
		self->die = crate_bust_die_48;
	self->takedamage = DAMAGE_YES;
		if (self->pullable)
			self->touch = crate_touch_48;	
	}

	self->cast_info.aiflags = AI_NOSTEP;

	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->misstime = 21;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}

	gi.linkentity (self);
}

void crate_bust_final_64 (edict_t *self)
{
    if (self->s.frame < 39)
	{
		if (self->item)
		{
			Drop_Item (self, self->item);
			self->item = NULL;
		}
		else
		{
			if (self->s.frame == 0)
				crate_stuff (self);
		}
			
		self->s.frame++;
		
		self->nextthink = level.time + 0.1;
	}
	else if (self->misstime-- > 0)
	{
		if (self->misstime <= 20)
		{
			if (self->misstime == 20)
			{
				self->s.renderfx2 |= RF2_PASSALPHA;
				self->s.effects = 1;		// this is full alpha now
			}
			
			self->s.effects += (255/20);
		
			if (self->s.effects > 255)
				self->s.effects = 255;
		}
		
		self->nextthink = level.time + 0.1;
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void crate_bust_die_64 (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	int i;
	
	if (self->takedamage == DAMAGE_NO)
		return;
	
	self->s.sound = 0;

	self->think = crate_bust_final_64;
	self->nextthink = level.time + FRAMETIME;

 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	
	if (self->spawnflags & TYPE_CARDBOARD)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/cardboard64.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/cardboard64.mdx", &self->s.model_parts[PART_HEAD]);

		self->takedamage = DAMAGE_NO;
		self->think = NULL;
		self->nextthink = 0;

		gi.sound (self, CHAN_AUTO, gi.soundindex ("weapons/melee/pipehitcboard.wav"), 1, ATTN_NORM, 0);		
		return;
	}
	
	if (self->spawnflags & TYPE_WOOD2)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/crate64_2.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/crate64_2.mdx", &self->s.model_parts[PART_HEAD]);
	}		
	else
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/crate64_1.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/crate64_1.mdx", &self->s.model_parts[PART_HEAD]);	
	}

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->solid = 0;
	self->touch = NULL;
	gi.sound (self, CHAN_AUTO, gi.soundindex ("world/crate2.wav"), 1, ATTN_NORM, 0);
}	

void SP_props_crate_bust_64 (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;	

	VectorSet (self->mins, -32, -32, -32);
	VectorSet (self->maxs, 32, 32, 32);
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;

	if (self->spawnflags & TYPE_METAL)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate64.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate64.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_WOOD;
	}
	else if (self->spawnflags & TYPE_CARDBOARD)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcard64.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcard64.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_FABRIC;
	}
	else if (self->spawnflags & TYPE_WOOD2)
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate64_2.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate64_2.mdx", &self->s.model_parts[PART_HEAD]);
		self->surfacetype = SURF_WOOD;
	}		
	else
	{
		self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/crate/stillcrate64_1.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds("models/props/crate/stillcrate64_1.mdx", &self->s.model_parts[PART_HEAD]);	
		self->surfacetype = SURF_WOOD;
	}
	
	if (!self->mass)
		self->mass = 400;
	if (!self->health)
		self->health = 10;
	if (!self->dmg)
		self->dmg = 0;

	if (!(self->spawnflags & TYPE_METAL))
	{
		self->die = crate_bust_die_64;
		self->takedamage = DAMAGE_YES;
	}

	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->misstime = 21;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}

	gi.linkentity (self);
}

/*QUAKED props_ammocrate_bust (0 .5 .8) (-32 -16 -8) (32 16 8)
Crate you may bust.
health (10).

"item" - Item to spawn on destruction if hit by pipe or crowbar 

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\crate\crate_32_64.mdx"
skin="models\props\crate\crate_exp.tga"
*/

void ammocrate_bust_finalA (edict_t *self)
{
    if (self->s.frame < 15)
	{
		self->s.frame++;
		
		self->nextthink = level.time + 0.1;
	}
	else if (self->misstime-- > 0)
	{
		if (self->misstime <= 20)
		{
			if (self->misstime == 20)
			{
				self->s.renderfx2 |= RF2_PASSALPHA;
				self->s.effects = 1;		// this is full alpha now
			}
			
			self->s.effects += (255/20);
		
			if (self->s.effects > 255)
				self->s.effects = 255;
		}
		
		self->nextthink = level.time + 0.1;
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void ammocrate_bust_finalB (edict_t *self)
{
    if (self->s.frame < 7)
	{
			if (self->item)
			{
				Drop_Item (self, self->item);
				self->item = NULL;
			}
		
		self->s.frame++;
		
		self->nextthink = level.time + 0.1;
	}
	else if (self->misstime-- > 0)
	{
		if (self->misstime <= 20)
		{
			if (self->misstime == 20)
			{
				self->s.renderfx2 |= RF2_PASSALPHA;
				self->s.effects = 1;		// this is full alpha now
			}
			
			self->s.effects += (255/20);
		
			if (self->s.effects > 255)
				self->s.effects = 255;
		}
		
		self->nextthink = level.time + 0.1;
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void ammocrate_bust_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	if ((attacker->client) && (attacker->client->pers.weapon) &&
		((!strcmp(attacker->client->pers.weapon->pickup_name, "Crowbar")) ||	// Ridah, 12-may-99, added brackets to fix crash if Dog busts open crate while attacking player
		 (!strcmp(attacker->client->pers.weapon->pickup_name, "Pipe"))))
	{
		self->think = ammocrate_bust_finalB;
		self->nextthink = level.time + FRAMETIME;
	}
	else
	{
		vec3_t	vec;
		
		self->model = "models/props/crate/exp.md2";
		self->s.modelindex = gi.modelindex (self->model);
		self->think = ammocrate_bust_finalA;
		self->nextthink = level.time + FRAMETIME;

		{
			edict_t *breakit;
			
			breakit = G_Spawn();
			
			if (breakit)
			{
				VectorCopy (self->s.origin, breakit->s.origin);
				gi.linkentity(breakit);
				gi.sound (breakit, CHAN_VOICE, gi.soundindex("world/explosion1.wav"), 1, ATTN_NORM, 0);
				breakit->think = G_FreeEdict;
				breakit->nextthink = level.time + 5.0;
			}
		}

		{
			vec3_t neworigin;

			VectorCopy(self->s.origin, neworigin);
			neworigin[1] -= 48;
			neworigin[0] -= 32;
			neworigin[2] += 16;

			gi.WriteByte (svc_temp_entity);
			gi.WriteByte (TE_EXPLOSION1);
			gi.WritePosition (neworigin);
			gi.WriteDir( vec );
			gi.WriteByte( (int)(self->dmg / 2) );
			gi.WriteByte (self->fxdensity);
			gi.multicast (neworigin, MULTICAST_PVS);	
		}
	}
	
	self->s.renderfx2 |= RF2_NOSHADOW;
	self->solid = 0;
	self->touch = NULL;
	gi.sound (self, CHAN_AUTO, gi.soundindex ("world/crate2.wav"), 1, ATTN_NORM, 0);
}	

void SP_props_ammocrate_bust (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/crate/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -16, -32, -8);
		VectorSet (self->maxs, 16, 32, 8);	
	}
	else
	{
		VectorSet (self->mins, -32, -16, -8);
		VectorSet (self->maxs, 32, 16, 8);		
	}		
	
	if (!self->mass)
		self->mass = 400;
	if (!self->health)
		self->health = 10;
	if (!self->dmg)
		self->dmg = 0;

	self->die = ammocrate_bust_die;
	self->takedamage = DAMAGE_YES;

	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	self->misstime = 26;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}	
	
	self->surfacetype = SURF_WOOD;	
	gi.linkentity (self);
}

void trashcanA_delay (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + 2 * FRAMETIME;
	self->think = trashcanA_explode;
	self->activator = attacker;
}

void SP_props_trashcanA (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	VectorClear(self->s.angles);
	
	if (!(self->spawnflags & NON_MOVEABLE))
	  self->fallerflag = 1;

	self->pullable = 1;
	// JOSEPH 24-NOV-98
	self->nokickbackflag = 1;
	// END JOSEPH

	// JOSEPH 20-JAN-99
	gi.modelindex ("models/props/metal/metal1.md2");
	gi.modelindex ("models/props/metal/metal2.md2");
	gi.modelindex ("models/props/metal/metal3.md2");
	gi.modelindex ("models/props/metal/metal4.md2");
	gi.modelindex ("models/props/metal/metal5.md2");
	// END JOSEPH

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_STEP;
	self->svflags |= SVF_PROP;

	self->model = "models/props/t_can/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -16, -16, -21);
	VectorSet (self->maxs, 16, 16, 21);

	if (!self->mass)
		self->mass = 400;
	if (!self->health)
		self->health = 10;
	if (!self->dmg)
		self->dmg = 0;

	self->die = trashcanA_delay;
	self->takedamage = DAMAGE_YES;
	self->cast_info.aiflags = AI_NOSTEP;

	if (!(self->spawnflags & NON_MOVEABLE))
		self->touch = trashcanA_touch;

	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}

	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props_trashcan_fall (0 .5 .8) (-16 -16 -21) (16 16 21)
Trash can you can push.  You can override its mass (100),
health (80).

"item" - Item to spawn on push down or destruction 

model="models\props\t_can2\"
*/

// JOSEPH 9-FEB-99
void trashcan_fall_final (edict_t *self)
{
	float	ratio;
	vec3_t	forward;

    if (self->s.frame < 14)
	{
			if (self->item)
			{
				Drop_Item (self, self->item);
				self->item = NULL;
			}
		
		self->s.frame++;
		
		if ((self->s.frame > 2) && (self->s.frame < 12))
		{
			ratio = 500 / (float)self->mass;
			AngleVectors(self->s.angles, forward, NULL, NULL);
			M_walkmove (self, vectoyaw(forward), 20 * ratio * FRAMETIME);
		}
	}

	if (self->health <= 0)
		trashcanA_explode(self);
	else
		self->nextthink = level.time + 0.1;
}	
// END JOSEPH

void trashcan_fall_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	self->s.angles[1] = (other->s.angles[1] + 90);
	self->s.angles[1] += (((rand() / (float)RAND_MAX)*(float)180.0)-(float)90.0);

	self->touch = NULL;
	self->think = trashcan_fall_final;
	self->nextthink = level.time + FRAMETIME;

	gi.sound (self, CHAN_AUTO, gi.soundindex ("world/trash2.wav"), 1, ATTN_NORM, 0);
}	

void SP_props_trashcan_fall (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	VectorClear(self->s.angles);
	
	// JOSEPH 20-JAN-99
	gi.modelindex ("models/props/metal/metal1.md2");
	gi.modelindex ("models/props/metal/metal2.md2");
	gi.modelindex ("models/props/metal/metal3.md2");
	gi.modelindex ("models/props/metal/metal4.md2");
	gi.modelindex ("models/props/metal/metal5.md2");
	// END JOSEPH

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/t_can2/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -16, -16, -21);
	VectorSet (self->maxs, 16, 16, 21);

	if (!self->mass)
		self->mass = 400;
	if (!self->health)
		self->health = 10;
	if (!self->dmg)
		self->dmg = 0;

	self->die = trashcanA_delay;
	self->takedamage = DAMAGE_YES;

	self->touch = trashcan_fall_touch;

	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}

	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED light_fire_esm (1 0 0) (-8 -8 -8) (8 8 8) X X X DYNAMIC
Cool fire extra-small 

alphalevel 1 - 10 (default 5) 
*/

/*QUAKED light_fire_sm (1 0 0) (-16 -16 -16) (16 16 16) X X X DYNAMIC
Cool fire small

alphalevel 1 - 10 (default 5)
*/

/*QUAKED light_fire_med (1 0 0) (-24 -24 -24) (24 24 24) X X X DYNAMIC
Cool fire medium

alphalevel 1 - 10 (default 5)
*/

/*QUAKED light_fire_lg (1 0 0) (-32 -32 -32) (32 32 32) X X X DYNAMIC
Cool fire large

alphalevel 1 - 10 (default 5)
*/

/*QUAKED smoke_esm (1 0 0) (-8 -8 -8) (8 8 8) 
Cool smoke extra-small

alphalevel 1 - 10 (default 4)
*/

/*QUAKED smoke_sm (1 0 0) (-16 -16 -16) (16 16 16) 
Cool smoke small

alphalevel 1 - 10 (default 4)
*/

/*QUAKED smoke_med (1 0 0) (-24 -24 -24) (24 24 24) 
Cool smoke medium

alphalevel 1 - 10 (default 4)
*/

/*QUAKED smoke_lg (1 0 0) (-32 -32 -32) (32 32 32) 
Cool smoke large

alphalevel 1 - 10 (default 4)
*/

void light_fire_think( edict_t *ent)
{
	ent->nextthink = level.time + 0.1;

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SFXFIRE);
	gi.WritePosition (ent->s.origin);
//	gi.WriteDir (ent->s.angles);
	gi.WriteByte (ent->firetype);
	if (ent->alphalevel)
	{
		gi.WriteByte (ent->alphalevel);
	}
	else
	{
		gi.WriteByte (0);
	}
	gi.multicast (ent->s.origin, MULTICAST_PVS);
}

void smoke_think( edict_t *ent)
{
	ent->nextthink = level.time + 0.5;

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SFXSMOKE);
	gi.WritePosition (ent->s.origin);
//	gi.WriteDir (ent->s.angles);
	gi.WriteByte (ent->firetype);
	if (ent->alphalevel)
	{
		gi.WriteByte (ent->alphalevel);
	}
	else
	{
		gi.WriteByte (0);
	}
	gi.multicast (ent->s.origin, MULTICAST_PVS);
}

void SP_light_fire_esm (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = light_fire_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 8;
	gi.linkentity (ent);

	AddLightSource(ent);
}

void SP_light_fire_sm (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = light_fire_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 16;
	gi.linkentity (ent);

	AddLightSource(ent);
}

void SP_light_fire_med (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = light_fire_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 24;
	gi.linkentity (ent);

	AddLightSource(ent);
}

void SP_light_fire_lg (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = light_fire_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 32;
	gi.linkentity (ent);

	AddLightSource(ent);
}

void SP_smoke_esm (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = smoke_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 5;
	gi.linkentity (ent);
}

void SP_smoke_sm (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = smoke_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 10;
	gi.linkentity (ent);
}

void SP_smoke_med (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = smoke_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 20;
	gi.linkentity (ent);
}

void SP_smoke_lg (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	VectorSet (ent->movedir, 0.0, 1, 0.0);
	ent->think = smoke_think;
	ent->nextthink = level.time + 0.1;
	ent->firetype = 30;
	gi.linkentity (ent);
}

/*QUAKED cast_buma (1 .5 0) (-30 -16 -25) (31 43 13)
Bum 
model = "models\actors\bum_seg"
*/

/*QUAKED cast_bumb (1 .5 0) (-30 -16 -25) (31 43 13)
Bum 
model = "models\actors\bum_seg"
*/

void think_bum1b (edict_t *self);
void think_bum2b (edict_t *self);

void think_bum1a (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 17)
    {
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
  
		if (((float)rand() / (float)RAND_MAX) < (float)0.1)
		{
			self->think = think_bum1b;
			gi.sound ( self, CHAN_VOICE, gi.soundindex ("actors/bum/bum.wav"), 1, 3, 0);
			return;
		}
	}

	self->think = think_bum1a;
}

void think_bum1b (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 74)
    {
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
		self->think = think_bum1a;
		return;
	}

	self->think = think_bum1b;
}

void think_bum2a (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 117)
    {
	self->s.frame++;
	}
	else
	{
		self->s.frame = 75;
  
		if (((float)rand() / (float)RAND_MAX) < (float)0.1)
		{
			self->think = think_bum2b;
			gi.sound ( self, CHAN_VOICE, gi.soundindex ("actors/bum/bum.wav"), 1, 3, 0);
			return;
		}
	}

	self->think = think_bum2a;
}

void think_bum2b (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 218)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 75;
		self->think = think_bum2a;
		return;
	}

	self->think = think_bum2b;
}

// JOSEPH 24-JAN-99
void SP_cast_buma (edict_t *self)
{
	int i;

    if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;

	self->s.skinnum = self->skin;
 
	VectorSet (self->mins, -16, -30, -25);
	VectorSet (self->maxs, 43, 31, 13);
 
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bum_seg/parta.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bum_seg/parta.mdx", &self->s.model_parts[PART_HEAD] );
 
	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/bum_seg/partb.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bum_seg/partb.mdx", &self->s.model_parts[PART_BODY] );
	self->health = 100;
	self->gib_health = -40;
	self->mass = 100;

 //self->pain = bum_pain;
 //self->die = bum_die;

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	gi.linkentity (self);

	self->think = think_bum1a;
	self->nextthink = level.time + 2 * FRAMETIME;
}

void SP_cast_bumb (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
 
	self->s.skinnum = self->skin;
 
	VectorSet (self->mins, -16, -30, -25);
	VectorSet (self->maxs, 43, 31, 13);
 
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/actors/bum_seg/parta.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bum_seg/parta.mdx", &self->s.model_parts[PART_HEAD] );
 
	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/actors/bum_seg/partb.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/actors/bum_seg/partb.mdx", &self->s.model_parts[PART_BODY] );
 
	self->health = 100;
	self->gib_health = -40;
	self->mass = 100;

 //self->pain = bum_pain;
 //self->die = bum_die;

	gi.linkentity (self);

	self->s.renderfx2 |= RF2_DIR_LIGHTS;	// Ridah

	self->s.frame = 75;
	self->think = think_bum2b;
	self->nextthink = level.time + 2 * FRAMETIME;
}
// END JOSEPH

// JOSEPH 23-JAN-99-B
/*QUAKED props_chair (0 .5 .8) (-11 -13 -26) (11 13 26)

A chair

model="models\props\chair\chair.mdx"
skin="models\props\chair\chair1.tga"
*/

void SP_props_chair (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = 0; //SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -11, -13, -26);
	VectorSet (self->maxs, 11, 13, 26);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/chair/chair.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/chair/chair.mdx", &self->s.model_parts[PART_HEAD]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;	

	self->surfacetype = SURF_WOOD;
	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props2_chair_push (0 .5 .8) (-16 -16 -26) (16 16 26)

A pushable chair

"health" - default 25

model="models\props\chair\chair.mdx"
skin="models\props\chair\chair1.tga"
*/

void chair_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	float	ratio;
	vec3_t	v;

	if ((!other->groundentity) || (other->groundentity == self))
		return;

	self->pullingflag = 0;

	// If activate key is pressed
	if ((plane) && (plane->type == 123))
	{
		if ((other->s.origin[0] != other->s.old_origin[0]) || (other->s.origin[1] != other->s.old_origin[1]))
		{
			self->pullingflag = 1;
			
			ratio = (float)other->mass / (float)self->mass;
			VectorSubtract (self->s.origin, other->s.origin, v);
			M_walkmove (self, 180+vectoyaw(v), 20 * ratio * FRAMETIME);
		
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/crate1.wav");
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}
	else
	{	
		ratio = (float)other->mass / (float)self->mass;
		VectorSubtract (self->s.origin, other->s.origin, v);
		M_walkmove (self, vectoyaw(v), 20 * ratio * FRAMETIME);

		if (((self->s.origin[0] != self->s.old_origin[0]) || (self->s.origin[1] != self->s.old_origin[1])))
		{
			if (!self->s.sound)
				self->s.sound = gi.soundindex ("world/crate1.wav");	
			VectorCopy(self->s.origin, self->save_avel);
			self->think = trashcanA_check_sound;
			self->nextthink = level.time + (FRAMETIME * 1.1);
		}
	}

	if (self->health <= 0)
		trashcanA_delay(self, NULL, NULL, 0, vec3_origin, 0, 0);
}	

void SP_props2_chair_push (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_STEP;
	self->svflags |= SVF_PROP;

	self->pullable = 1;
	self->nokickbackflag = 1;

	gi.modelindex ("models/props/metal/metal1.md2");
	gi.modelindex ("models/props/metal/metal2.md2");
	gi.modelindex ("models/props/metal/metal3.md2");
	gi.modelindex ("models/props/metal/metal4.md2");
	gi.modelindex ("models/props/metal/metal5.md2");

	VectorSet (self->mins, -16, -16, -26);
	VectorSet (self->maxs, 16, 16, 0);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/chair/chair.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/chair/chair.mdx", &self->s.model_parts[PART_HEAD]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	if (!self->mass)
		self->mass = 400;	

	if (!self->health)
		self->health = 25;

	self->die = trashcanA_delay;
	self->takedamage = DAMAGE_YES;

	self->cast_info.aiflags = AI_NOSTEP;
	self->touch = chair_touch;
	
	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;	

	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}
// END JOSEPH

// JOSEPH 24-JAN-99
/*QUAKED props_extinguisherA (0 .5 .8) (-16 -16 -16) (16 16 16)

An extingusher

model="models\pu_icon\exting\ext1.md2"

dmg - damage an exploding extinguisher causes (default 25)
*/

/*QUAKED props_extinguisherB (0 .5 .8) (-16 -16 -16) (16 16 16)

An extingusher

dmg - damage an exploding extinguisher causes (default 25)

model="models\pu_icon\exting\ext2.md2"
*/

void exting_delay (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	vec3_t vec;
	
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = trashcanA_explode;
	self->activator = attacker;

	VectorClear(vec);
	vec[2] = 1;

	{
		edict_t *breakit;
		
		breakit = G_Spawn();
		
		if (breakit)
		{
			VectorCopy (self->s.origin, breakit->s.origin);
			gi.linkentity(breakit);
			gi.sound (breakit, CHAN_VOICE, gi.soundindex("world/explosion1.wav"), 1, ATTN_NORM, 0);
			breakit->think = G_FreeEdict;
			breakit->nextthink = level.time + 5.0;
		}
	}

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_EXPLOSION1);
	gi.WritePosition (self->s.origin);
	gi.WriteDir( vec );
	gi.WriteByte( (int)(self->dmg / 2) );
	gi.WriteByte (self->fxdensity);
	gi.multicast (self->s.origin, MULTICAST_PVS);	

	T_RadiusDamage (self, self->activator, self->dmg, NULL, self->dmg+40, MOD_EXPLOSIVE);
}

// JOSEPH 3-FEB-99
void SP_props_extinguisherA (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/pu_icon/exting/ext1.md2";
	self->s.modelindex = gi.modelindex (self->model);

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->die = exting_delay;
	self->takedamage = DAMAGE_YES;

	if (!self->dmg)
		self->dmg = 25;

	self->s.renderfx  |= RF_REFL_MAP;

	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

void SP_props_extinguisherB (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/pu_icon/exting/ext2.md2";
	self->s.modelindex = gi.modelindex (self->model);

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->die = exting_delay;
	self->takedamage = DAMAGE_YES;

	if (!self->dmg)
		self->dmg = 25;

	self->s.renderfx  |= RF_REFL_MAP;

	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}
// END JOSEPH

// JOSEPH 13-FEB-99
/*QUAKED props_motorcycle (0 .5 .8) (-60 -20 -26) (60 20 26)

A motorcycle

model="models\props\moto\moto.mdx;models\props\moto\chrome.mdx"
skin="models\props\moto\motoskin.tga;models\props\moto\motoskin_a.tga"
*/

void SP_props_motorcycle (edict_t *self)
{
	int i;
	//edict_t	*box = NULL;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/moto/moto.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/moto/moto.mdx", &self->s.model_parts[PART_HEAD]);	

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/props/moto/chrome.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/moto/chrome.mdx", &self->s.model_parts[PART_BODY] );

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx  |= RF_REFL_MAP;

	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_motorcycle_run (0 .5 .8) (-16 -16 -16) (16 16 16)

A motorcycle speeding away

model="models\props\ride\moto.mdx"
*/

void think_motorcycle_run (edict_t *self)
{
    if (self->s.frame < 111)
	{
		self->nextthink = level.time + 0.1;
		self->s.frame++;
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void SP_props_motorcycle_run (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.angles[0] = 0; 
	self->s.angles[1] = 270; 
	self->s.angles[2] = 0; 	

	self->s.origin[0] = -2368+16; 
	self->s.origin[1] = -880-16; 
	self->s.origin[2] = 48-16-5; 	

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/ride/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/ride/head.mdx", &self->s.model_parts[PART_HEAD]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/ride/moto.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/ride/moto.mdx", &self->s.model_parts[1] );

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/ride/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/ride/body.mdx", &self->s.model_parts[2] );

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/ride/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/ride/legs.mdx", &self->s.model_parts[3] );

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/ride/cigar.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/ride/cigar.mdx", &self->s.model_parts[4] );

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx  |= RF_REFL_MAP;

	self->think = think_motorcycle_run;
	self->nextthink = level.time + 2.0;

	gi.linkentity (self);
}

/*QUAKED props_motorcycle_runaway (0 .5 .8) (-16 -16 -16) (16 16 16)

A motorcycle riding in place

model="models\props\runaway\moto.mdx"
*/

void think_motorcycle_runaway (edict_t *self)
{
    if (self->s.frame < 55)
	{
		self->s.frame++;

		/*if (self->count)
		{
			edict_t *player;

			if (self->count > 10)
				self->count = 10;
			
			player = &g_edicts[1];
			
			player->client->ps.stats[STAT_ENDPIC] = self->count;

			self->count++;
		}
		else
		{
			edict_t *player;

			player = &g_edicts[1];
			
			player->client->ps.stats[STAT_ENDPIC] = 100;
		}*/
	}
	else
	{
		self->s.frame = 0;
		self->count++;
	}
	
	self->nextthink = level.time + 0.1;
}	

void SP_props_motorcycle_runaway (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/runaway/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/runaway/head.mdx", &self->s.model_parts[PART_HEAD]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/runaway/moto.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/runaway/moto.mdx", &self->s.model_parts[1] );

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/runaway/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/runaway/body.mdx", &self->s.model_parts[2] );

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/runaway/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/runaway/legs.mdx", &self->s.model_parts[3] );

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx  |= RF_REFL_MAP;

	self->think = think_motorcycle_runaway;
	self->nextthink = level.time + 0.1;
	self->count = 0;

	gi.linkentity (self);
}

// JOSEPH 13-FEB-99
/*QUAKED props_shelf (0 .5 .8) (-40 -85 -51) (40 85 51)

The pawn shop shelf 

model="models\props\shelf\flametank.mdx;models\props\shelf\pistol.mdx;models\props\shelf\shotgun.mdx;models\props\shelf\tomgun.mdx;models\props\shelf\sshell.mdx"
*/

void SP_props_shelf (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}	

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/shelf/flametank.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/flametank.mdx", &self->s.model_parts[PART_HEAD]);	

	self->s.num_parts++;
	self->s.model_parts[PART_BODY].modelindex = gi.modelindex("models/props/shelf/pistol.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_BODY].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/shelf/pistol.mdx", &self->s.model_parts[PART_BODY] );

	self->s.num_parts++;
	self->s.model_parts[PART_LEGS].modelindex = gi.modelindex("models/props/shelf/shotgun.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_LEGS].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/shelf/shotgun.mdx", &self->s.model_parts[PART_BODY] );

	self->s.num_parts++;
	self->s.model_parts[PART_GUN].modelindex = gi.modelindex("models/props/shelf/sshell.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_GUN].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/shelf/sshell.mdx", &self->s.model_parts[PART_BODY] );

	self->s.num_parts++;
	self->s.model_parts[PART_GUN2].modelindex = gi.modelindex("models/props/shelf/tomgun.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_GUN2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/shelf/tomgun.mdx", &self->s.model_parts[PART_BODY] );

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_mattressA (0 .5 .8) (-36 -28 -38) (36 28 38)
model="models/props/mattress/matt.md2"
A mattress

*/

void SP_props_mattressA (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/mattress/matt.md2";
	self->s.modelindex = gi.modelindex (self->model);

	VectorSet (self->mins, -36, -28, -38);
	VectorSet (self->maxs, 36, 28, 38);		

	self->s.renderfx2 |= RF2_NOSHADOW;	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props_mattressB (0 .5 .8) (-8 -34-38) (8 34 38)
A mattress
model="models/props/mattress/matt2.md2"
*/

void SP_props_mattressB (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/mattress/matt2.md2";
	self->s.modelindex = gi.modelindex (self->model);

	VectorSet (self->mins, -8, -34, -38);
	VectorSet (self->maxs, 8, 34, 38);		

	self->s.renderfx2 |= RF2_NOSHADOW;	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props_mattressC (0 .5 .8) (-34 -38 -8) (34 38 8)
A mattress
model="models/props/mattress/matt3.md2"
*/

void SP_props_mattressC (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/mattress/matt3.md2";
	self->s.modelindex = gi.modelindex (self->model);

	VectorSet (self->mins, -34, -38, -8);
	VectorSet (self->maxs, 34, 38, 8);		

	self->s.renderfx2 |= RF2_NOSHADOW;	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props_tv (0 .5 .8) (-8 -16 -22) (8 16 22)

A television

model="models\props\tv\tv.md2"
*/

void SP_props_tv (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}	

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/tv/tv.md2";
	self->s.modelindex = gi.modelindex (self->model);

	VectorSet (self->mins, -8, -16, -22);
	VectorSet (self->maxs, 8, 16, 22);		

	self->s.renderfx2 |= RF2_NOSHADOW;	
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props_steam_machine (0 .5 .8) (-8 -8 -8) (8 8 8)

A real steam producer  

"alphalevel" 1 - 10 (default 2)  
"firetype" length of steam 1 - 100 (default 15)
"thudsurf" start size of steam 1 - 10 (default 5)
"thudsnd" end size steam increase 1 - 10 (default 5)
"deadticks" number of steam puffs per length element 1- 10 (default 2)
*/

void steam_think( edict_t *ent)
{
	ent->nextthink = level.time + 0.5;
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SFXSTEAM);
	gi.WritePosition (ent->s.origin);
	gi.WriteDir (ent->s.angles);
	gi.WriteByte (ent->firetype); // length
	gi.WriteByte (ent->deadticks); // puffs
	gi.WriteByte (ent->thudsurf); // start size
	gi.WriteByte (ent->thudsnd); // end size
	if (ent->alphalevel)
		gi.WriteByte (ent->alphalevel);
	else
		gi.WriteByte (0);
	gi.multicast (ent->s.origin, MULTICAST_PVS);
}

void SP_props_steam_machine (edict_t *ent)
{
    if (ent->alphalevel > 10) ent->alphalevel = 10;
	if ((!ent->thudsurf) || (ent->thudsurf > 10))
		ent->thudsurf = 5;
	if ((!ent->thudsnd) || (ent->thudsnd > 10))
		ent->thudsnd = 5;
	if ((!ent->firetype) || (ent->firetype > 100))
		ent->firetype = 15;
	if ((!ent->deadticks) || (ent->deadticks > 10))
		ent->deadticks = 2;
	ent->think = steam_think;
	ent->nextthink = level.time + 0.1;
	gi.linkentity (ent);
}

// JOSEPH 24-FEB-99
/*QUAKED props_trash (0 .5 .8) (-64 -64 -4) (64 64 4)

Some trash

model="models\props\trash\tris.md2"
*/

void SP_props_trash (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -64, -64, -4);
	VectorSet (self->maxs, 64, 64, 4);		

	self->model = "models/props/trash/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;	

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}

	gi.linkentity (self);
}
// END JOSEPH

/*UAKED props_wall_fall_test (0 .5 .8) (-64 -26 -48) (64 26 48)

A test wall  

model="models\props\wall\testwall.mdx"
*/

/*QUAKED props_wall_fall (0 .5 .8) (-64 -26 -48) (64 26 48)

A wall that falls when trigered  

model="models\props\wall\wall.mdx"
*/
void wall_fall_final (edict_t *self)
{
    if (self->s.frame < 45)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	
	if (self->misstime-- > 0)
	{
		if (self->misstime <= 20)
		{
			if (self->misstime == 20)
			{
				self->s.renderfx2 |= RF2_PASSALPHA;
				self->s.effects = 1;		// this is full alpha now
			}
			
			self->s.effects += (255/20);
		
			if (self->s.effects > 255)
				self->s.effects = 255;
		}
		
		self->nextthink = level.time + 0.1;
	}
	else
	{
		G_FreeEdict (self);
	}
}	
// END JOSEPH

void wall_fall_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = wall_fall_final;
	ent->nextthink = level.time + FRAMETIME;
	gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props_wall_fall (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -64, -26, -48);
	VectorSet (self->maxs, 64, 26, 48);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/wall/wall.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/wall/wall.mdx", &self->s.model_parts[PART_HEAD]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = wall_fall_trigger;

	self->svflags |= SVF_NOCLIENT;

	self->misstime = 40;

	gi.linkentity (self);
}

/*QUAKED props_trashbottle (0 .5 .8) (-8 -2 -2) (8 2 2)

Some trash

model="models\props\trashbottle\tris.md2"
*/

void SP_props_trashbottle (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/trashbottle/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;	

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_trashpaper (0 .5 .8) (-18 -18 -2) (18 18 2)

Some trash

model="models\props\trashpaper\tris.md2"
*/

void SP_props_trashpaper (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/trashpaper/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;	

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_trashwall (0 .5 .8) (-70 -25 -10) (70 25 10)

Some trash

model="models\props\trashwall\tris.md2"
*/

void SP_props_trashwall (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/trashwall/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;	

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_trashcorner (0 .5 .8) (-40 -40 -8) (40 40 8)

Some trash

model="models\props\trashcorner\tris.md2"
*/

void SP_props_trashcorner (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/trashcorner/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;	

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_trashbottle_vert (0 .5 .8) (-2 -2 -8) (2 2 8)

A vertical trash bottle

model="models\props\trashbottle_vert\tris.md2"
*/

void SP_props_trashbottle_vert (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->model = "models/props/trashbottle_vert/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;	

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_shelf_fall (0 .5 .8) (-65 -13 -51) (65 13 51)

An falling shelf

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\shelf\shelf.mdx;models\props\shelf\top.mdx"
*/

void shelf_fall_final (edict_t *self)
{
    if (self->s.frame < 84)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;
		self->handle2->s.frame++;
	}
}	

void shelf_fall_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = shelf_fall_final;
}

void SP_props_shelf_fall (edict_t *self)
{
	int i;
	edict_t	*newent = NULL;	

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -20, -78, -52);
		VectorSet (self->maxs, 20, 78, 52);		
	}
	else
	{
		VectorSet (self->mins, -78, -20, -52);
		VectorSet (self->maxs, 78, 20, 52);		
	}
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/shelf/shelf.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/shelf.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/shelf/tops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/tops.mdx", &self->s.model_parts[1]);

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/shelf/barre0.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre0.mdx", &self->s.model_parts[2]);

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/shelf/barre1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre1.mdx", &self->s.model_parts[3]);

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/shelf/barre2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre2.mdx", &self->s.model_parts[4]);

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/shelf/barre3.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre3.mdx", &self->s.model_parts[5]);

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/shelf/barre4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre4.mdx", &self->s.model_parts[6]);


	newent = G_Spawn();
	
	if (!newent)
		return;

	self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_NOT;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = newent->skin;
 	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/shelf/barre5.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre5.mdx", &newent->s.model_parts[0]);

	newent->s.num_parts++;
	newent->s.model_parts[1].modelindex = gi.modelindex("models/props/shelf/barre6.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[1].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre6.mdx", &newent->s.model_parts[1]);

	newent->s.num_parts++;
	newent->s.model_parts[2].modelindex = gi.modelindex("models/props/shelf/barre7.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[2].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre7.mdx", &newent->s.model_parts[2]);

	newent->s.num_parts++;
	newent->s.model_parts[3].modelindex = gi.modelindex("models/props/shelf/barre8.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[3].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre8.mdx", &newent->s.model_parts[3]);

	newent->s.num_parts++;
	newent->s.model_parts[4].modelindex = gi.modelindex("models/props/shelf/barre9.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[4].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre9.mdx", &newent->s.model_parts[4]);

	newent->s.num_parts++;
	newent->s.model_parts[5].modelindex = gi.modelindex("models/props/shelf/barre10.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[5].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelf/barre10.mdx", &newent->s.model_parts[5]);

	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	self->die = shelf_fall_die;
	self->takedamage = DAMAGE_YES;

	newent->surfacetype = SURF_WOOD;
	self->surfacetype = SURF_WOOD;
	gi.linkentity (newent);
	gi.linkentity (self);
}


/*QUAKED props_shelfB_fall (0 .5 .8) (-65 -13 -51) (65 13 51)

Another falling shelf

model="models\props\shelftwo\shelf.mdx;models\props\shelftwo\top.mdx"
*/

void shelfB_fall_final (edict_t *self)
{
    if (self->s.frame < 75)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;
		self->handle->s.frame++;
		self->handle2->s.frame++;
	}
}	

void shelfB_fall_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = shelfB_fall_final;
}

void SP_props_shelfB_fall (edict_t *self)
{
	int i;
	edict_t	*newent = NULL;	
	edict_t	*newent2 = NULL;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -20, -78, -52);
		VectorSet (self->maxs, 20, 78, 52);		
	}
	else
	{
		VectorSet (self->mins, -78, -20, -52);
		VectorSet (self->maxs, 78, 20, 52);		
	}
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/shelftwo/shelf.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/shelf.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/shelftwo/tanktops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tanktops.mdx", &self->s.model_parts[1]);

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/shelftwo/barre0.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barre0.mdx", &self->s.model_parts[2]);

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/shelftwo/barre1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barre1.mdx", &self->s.model_parts[3]);

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/shelftwo/barre2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barre2.mdx", &self->s.model_parts[4]);

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/shelftwo/barre3.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barre3.mdx", &self->s.model_parts[5]);

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/shelftwo/barre4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barre4.mdx", &self->s.model_parts[6]);


	newent = G_Spawn();
	
	if (!newent)
		return;

	self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_NOT;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = newent->skin;
 	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/shelftwo/barre6.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barre6.mdx", &newent->s.model_parts[0]);

	newent->s.num_parts++;
	newent->s.model_parts[1].modelindex = gi.modelindex("models/props/shelftwo/barre8.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[1].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barre8.mdx", &newent->s.model_parts[1]);

	newent->s.num_parts++;
	newent->s.model_parts[2].modelindex = gi.modelindex("models/props/shelftwo/tank_lg.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[2].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tank_lg.mdx", &newent->s.model_parts[2]);

	newent->s.num_parts++;
	newent->s.model_parts[3].modelindex = gi.modelindex("models/props/shelftwo/tank_lg3.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[3].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tank_lg3.mdx", &newent->s.model_parts[3]);

	newent->s.num_parts++;
	newent->s.model_parts[4].modelindex = gi.modelindex("models/props/shelftwo/tank_lg1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[4].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tank_lg1.mdx", &newent->s.model_parts[4]);

	newent->s.num_parts++;
	newent->s.model_parts[5].modelindex = gi.modelindex("models/props/shelftwo/tank_lg2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[5].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tank_lg2.mdx", &newent->s.model_parts[5]);

	newent2 = G_Spawn();
	
	if (!newent2)
		return;

	self->handle = newent2;

	VectorCopy(self->s.origin, newent2->s.origin);
	VectorCopy(self->s.angles, newent2->s.angles);

	newent2->solid = SOLID_NOT;
	newent2->movetype = MOVETYPE_NONE;
	newent2->svflags |= SVF_PROP;

	newent2->s.skinnum = newent2->skin;
 	memset(&(newent2->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent2->s.num_parts++;
	newent2->s.model_parts[0].modelindex = gi.modelindex("models/props/shelftwo/tank_sm.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[0].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tank_sm.mdx", &newent2->s.model_parts[0]);

	newent2->s.num_parts++;
	newent2->s.model_parts[1].modelindex = gi.modelindex("models/props/shelftwo/tank_sm1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[1].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tank_sm1.mdx", &newent2->s.model_parts[1]);

	newent2->s.num_parts++;
	newent2->s.model_parts[2].modelindex = gi.modelindex("models/props/shelftwo/tank_sm2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[2].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/tank_sm2.mdx", &newent2->s.model_parts[2]);

	newent2->s.num_parts++;
	newent2->s.model_parts[3].modelindex = gi.modelindex("models/props/shelftwo/barreltops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[3].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelftwo/barreltops.mdx", &newent2->s.model_parts[3]);	

	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent2->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	self->die = shelfB_fall_die;
	self->takedamage = DAMAGE_YES;

	newent->surfacetype = SURF_WOOD;
	newent2->surfacetype = SURF_WOOD;
	self->surfacetype = SURF_WOOD;
	gi.linkentity (newent);
	gi.linkentity (newent2);
	gi.linkentity (self);
}

/*QUAKED props_rat (0 .5 .8) (-12 -12 0) (12 12 10)

A rat

"dmg" - rat bite damage (2 default)

"health" - heath of the rat (10 default)

*/

void rat_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	vec3_t realorigin;

	VectorCopy(self->s.origin, realorigin);
	realorigin[2] += 8;

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_GIBS);
	gi.WritePosition (realorigin);
	gi.WriteDir (vec3_origin);
	gi.WriteByte ( 1 );	// number of gibs
	gi.WriteByte ( 0 );	// scale of direction to add to velocity
	gi.WriteByte ( 0 );	// random offset scale
	gi.WriteByte ( 10 );	// random velocity scale
	gi.multicast (realorigin, MULTICAST_PVS);

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SPLASH);
	gi.WriteByte (50);
	gi.WritePosition (realorigin);
	gi.WriteDir (self->movedir);
	gi.WriteByte (6);
	gi.multicast (realorigin, MULTICAST_PVS);

	// If this rat was spawned - tell spawner to make a new one
	if (self->targetname)
	{
		int i;
		edict_t	*e = NULL;

		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "props_rat_spawner")) &&
			    (e->target) && (!strcmp(e->target, self->targetname)))
			{
				e->fxdensity++;	
				break;	
			}
		}	
	}

	G_FreeEdict (self);
}

int check_rat_hit_player(edict_t *ent)
{
	trace_t tr;
	vec3_t	endpos, forward;

	AngleVectors (ent->s.angles, forward, NULL, NULL);
	VectorMA(ent->s.origin, 32, forward, endpos);
	endpos[2] += 32;
	tr = gi.trace(ent->s.origin, NULL, NULL, endpos, ent, MASK_SHOT);

	if (tr.fraction < 1)
	{
		if ((tr.ent) && (tr.ent->client))
		{
			vec3_t	start, aimdir, dang;
		
			if (ent->timestamp > level.time)
				return false;

			ent->timestamp = level.time + 0.5;

			ent->debugprint = 1;
    
			//T_Damage (tr.ent, tr.ent, tr.ent, vec3_origin, tr.ent->s.origin, vec3_origin, ent->dmg, ent->dmg, 0, MOD_DOGBITE);

			VectorSubtract (tr.ent->s.origin, ent->s.origin, aimdir);
			vectoangles (aimdir, dang);
			AngleVectors (dang, forward, NULL, NULL);
			VectorMA (ent->s.origin, 16, forward, start);
		
			fire_rat (ent, start, forward, ent->dmg);

			return true;
		}
	}	

	return false;
}

void rat_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!other->client)
		return;

	if (self->timestamp > level.time)
		return;

	self->timestamp = level.time + 0.5;

	self->debugprint = 1;
    
	T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, self->dmg, 0, MOD_DOGBITE);	
}

void rat_go (edict_t *self)
{
	if (self->option)
	{	
		cvar_t	*props; 
		
		props = gi.cvar("props", "1", CVAR_ARCHIVE);
		
		if (!props->value)
		{
			self->nextthink = level.time + (FRAMETIME * 10);
			return;
		}
	}
	
	if (self->debugprint != 1)
	M_walkmove (self, self->healspeed, 20 * 5 * FRAMETIME);
	
	if (self->debugprint == 1)
	{
		if (self->s.frame < 8 || self->s.frame >= 17)
		{
			self->s.frame = 8;
		}
		else
	{
			self->s.frame++;

			if (self->s.frame == 17)
			{
				self->debugprint = 0;
			}
		}
	}
	else if (!VectorCompare(self->s.origin, self->s.old_origin))
	{
		if (self->s.frame <= 3)
		{
			self->s.frame++;
		}
		else
		{
			self->s.frame = 0;
	}
		
		if (self->fxdensity++ >= self->deadticks)
	{
		self->deadticks = rand()&7;
		self->healspeed += (rand()&31)-16;  
		if (self->healspeed > 360)
			self->healspeed = (self->healspeed - 360);
		if (self->healspeed < 0)
			self->healspeed = (self->healspeed + 360);
		self->s.angles[1] = self->healspeed; 
	}

		if ((rand()&127) == 4)
		{
			self->debugprint = 1;
		}
	}
	else
	{
		if (self->s.frame <= 7 && self->s.frame >= 4)
		{
			self->s.frame++;
		}
		else
		{
			self->s.frame = 4;
		}
		
		if (self->durationflag)
			self->healspeed += 16;
		else
			self->healspeed -= 16;

		if (self->healspeed > 360)
			self->healspeed = (self->healspeed - 360);
		if (self->healspeed < 0)
			self->healspeed = (self->healspeed + 360);
		self->s.angles[1] = self->healspeed; 

		M_walkmove (self, self->healspeed, 20 * 5 * FRAMETIME);	

		if (!VectorCompare(self->s.origin, self->s.old_origin))
		{
			self->deadticks = (rand()&3)+6;
		}
		else
		{
			if (check_rat_hit_player(self))
			{
				self->debugprint = 1;
			}
		}
	}

	self->nextthink = level.time + FRAMETIME;
}


void SP_props_rat (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_STEP;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -8, -8, 0);
	VectorSet (self->maxs, 8, 8, 10);		
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/actors/rat/rat.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/actors/rat/rat.mdx", &self->s.model_parts[0]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	// Note to Joseph: you can use AI_ADJUSTPITCH to keep them angled correctly on slopes

	self->monsterprop = 1;
	self->deadticks = 1;
	self->fxdensity = 0;
	self->healspeed = rand()&360;
	self->debugprint = 0;
	// Born left or right handed
	self->durationflag = rand()&1;

	self->die = rat_die;
	self->touch = rat_touch;
	self->takedamage = DAMAGE_YES;
	self->cast_info.aiflags = AI_NOSTEP;

	if (!self->dmg)
		self->dmg = 2;

	if (!self->health)
		self->health = 10;

	self->think = rat_go;
	self->nextthink = level.time + (FRAMETIME * 2);

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props_rat_trigger (0 .5 .8) (-12 -12 0) (12 12 10)

A rat that is spawned when triggered

"dmg" - rat bite damage (2 default)

"health" - heath of the rat (10 default)

"targetname" - target ID
*/

void rat_trigger_use  (edict_t *self, edict_t *other, edict_t *activator)
{
	self->svflags &= ~SVF_NOCLIENT;
	self->use = NULL;
	self->targetname = NULL;
	self->solid = SOLID_BBOX;
	self->think = rat_go;
	self->nextthink = level.time + FRAMETIME;
}

void SP_props_rat_trigger (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->movetype = MOVETYPE_STEP;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -8, -8, 0);
	VectorSet (self->maxs, 8, 8, 10);		
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/actors/rat/rat.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/actors/rat/rat.mdx", &self->s.model_parts[0]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->monsterprop = 1;
	self->deadticks = 1;
	self->fxdensity = 0;
	self->healspeed = rand()&360;
	self->debugprint = 0;
	// Born left or right handed
	self->durationflag = rand()&1;

	self->die = rat_die;
	self->touch = rat_touch;
	self->takedamage = DAMAGE_YES;
	self->cast_info.aiflags = AI_NOSTEP;

	if (!self->dmg)
		self->dmg = 2;

	if (!self->health)
		self->health = 10;

	if (self->targetname)
	{
		self->solid = SOLID_NOT;		
		self->use = rat_trigger_use;
		self->svflags |= SVF_NOCLIENT;	
	}
	else
	{
		gi.dprintf ("props_rat_trigger without a targetname at %s\n", vtos(self->absmin));
		G_FreeEdict (self);
		return;
	}

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props_rat_spawner (0 .5 .8) (-16 -16 -16) (16 16 16)

Base rat spawner

 props_rat_spawner_node  determine possible spawn point

 "dmg" - rat bite damage (2 default)

 "health" - heath of the rat (10 default)

 "deadticks" - total number of rats in level from spawner at a time (default 5)

 "target" - ID string for spawner 
*/

void rat_spawn_think (edict_t *self)
{
	if (self->fxdensity)
	{
		int i, tnode, node;
		edict_t	*e = NULL;
			
		if (self->option)
		{	
			cvar_t	*props; 
			
			props = gi.cvar("props", "1", CVAR_ARCHIVE);
			
			if (!props->value)
			{
				self->nextthink = level.time + FRAMETIME * 50;
				return;
			}
		}

		tnode = rand()%self->firetype;
		node = 0;

		// Find a spawner origin
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "props_rat_spawner_node")) &&
			    (e->targetname) && (self->target) && (!strcmp(e->targetname, self->target))
				// Ridah, added this so they don't spawn if you can see them
				&& (!gi.inPVS(g_edicts[1].s.origin, e->s.origin)))
			{
				if (node == tnode)
				{
					edict_t	*rat = NULL;
					
					rat = G_Spawn();
		
					if (!rat)
						return;
					
					// Spawn new rat
					VectorCopy(e->s.origin, rat->s.origin);
					rat->s.origin[2] -= 6;
					rat->targetname = self->target;
					rat->dmg = self->dmg;
					rat->health = self->health;
					rat->option = self->option;
					SP_props_rat(rat);
					self->fxdensity--;
					self->nextthink = level.time + FRAMETIME * 50;
					return;	
				}

				node++;
			}
		}	
	}
	
	self->nextthink = level.time + FRAMETIME * 50;	// Ridah, increased this
}

void rat_spawn_first_think (edict_t *self)
{
	int i;
	edict_t	*e = NULL;
	
	if (self->target)
	{
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "props_rat_spawner_node")) &&
				(e->targetname) && (!strcmp(e->targetname, self->target)))
			{
				self->firetype++;
			}
		}
		
		if (self->firetype)
		{
			self->think = rat_spawn_think;
			self->nextthink = level.time + FRAMETIME;	
		}
	}
	else
	{
		gi.dprintf ("props_rat_spawner without a target at %s\n", vtos(self->absmin));
	}
}

void SP_props_rat_spawner (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (!self->deadticks)
		self->deadticks = 5;

	self->fxdensity = self->deadticks; 

	if (!self->dmg)
		self->dmg = 2;

	if (!self->health)
		self->health = 10;

	self->firetype = 0;

	self->think = rat_spawn_first_think;
	self->nextthink = level.time + (FRAMETIME * 3);	

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props_rat_spawner_node (0 .5 .8) (-16 -16 -16) (16 16 16)

 Possible rat spawn point from props_rat_spawner

 "targetname" - ID string for spawner 	
*/

void SP_props_rat_spawner_node (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	gi.linkentity (self);
}

/*QUAKED props_blimp (0 .5 .8) (-140 -40 -58) (140 40 58)

A path corner blimp - trigger to make visable and start moving

"speed" speed of the blimp (20 default)
"target" target path corner ID

model="models\props\blimp\tris.md2"
*/

void train_use (edict_t *self, edict_t *other, edict_t *activator);
void func_train_find (edict_t *self);

void blimp_use  (edict_t *self, edict_t *other, edict_t *activator)
{
	self->svflags &= ~SVF_NOCLIENT;
	self->use = train_use;
	train_use (self, other, activator);
}

void SP_props_blimp (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	if (!self->target)
	{
		gi.dprintf ("props_blimp without a target at %s\n", vtos(self->absmin));
		G_FreeEdict (self);
		return;
	}

	if (!self->speed)
		self->speed = 20;

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_FLY;
	self->svflags |= SVF_PROP;

	self->model = "models/props/blimp/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	self->s.renderfx2 |= RF2_NOSHADOW;	
	
	self->think = func_train_find;
	self->nextthink = level.time + FRAMETIME;
	self->use = blimp_use;
	self->svflags |= SVF_NOCLIENT;
	self->moveinfo.accel = self->moveinfo.decel = self->moveinfo.speed = self->speed;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props_roof_vent (0 .5 .8) (-32 -36 -48) (32 36 48)

A moving roof vent

"health" - hit points (25 default)

model="models\props\roof_vent\tris.md2"
*/

void vent_explode (edict_t *self)
{
	vec3_t	org;
	float	spd;
	vec3_t	save;

	VectorCopy (self->s.origin, save);
	VectorMA (self->absmin, 0.5, self->size, self->s.origin);

	// a few big chunks
	spd = 1.5 * (float)self->dmg / 200.0;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	// bottom corners
	spd = 1.75 * (float)self->dmg / 200.0;
	VectorCopy (self->absmin, org);
	ThrowDebris (self, "models/props/metal/metal2.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	ThrowDebris (self, "models/props/metal/metal3.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal4.md2", spd, org);
	VectorCopy (self->absmin, org);
	org[0] += self->size[0];
	org[1] += self->size[1];
	ThrowDebris (self, "models/props/metal/metal5.md2", spd, org);

	// a bunch of little chunks
	spd = 2 * self->dmg / 200;
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);
	org[0] = self->s.origin[0] + crandom() * self->size[0];
	org[1] = self->s.origin[1] + crandom() * self->size[1];
	org[2] = self->s.origin[2] + crandom() * self->size[2];
	ThrowDebris (self, "models/props/metal/metal1.md2", spd, org);

	VectorCopy (save, self->s.origin);
}

void vent_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->s.frame = 0;
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = vent_explode;
	self->activator = attacker;

	self->model = "models/props/ventbroke/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
}

void think_roof_vent (edict_t *self)
{
	if (self->s.frame < 11)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}

	self->nextthink = level.time + FRAMETIME;
}

void SP_props_roof_vent (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/roof_vent/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -32, -36, -48);
	VectorSet (self->maxs, 32, 36, 48);		

	self->surfacetype = SURF_METAL_L;
	self->s.renderfx2 |= RF2_NOSHADOW;
	gi.linkentity (self);

	self->die = vent_die;
	self->takedamage = DAMAGE_YES;

	if (!self->health)
		self->health = 25;

	self->nextthink = level.time + FRAMETIME *2;
	self->think = think_roof_vent;
}

/*QUAKED props2_truck_die_TEST (0 .5 .8)  (-61 -148 -78) (61 148 78)

First and last frames of the truck

model="models\props\trucktest\1st.mdx;models\props\trucktest\last.mdx"
*/

/*QUAKED props2_truck_die (0 .5 .8)  (-61 -148 -78) (61 148 78)

A truck that becomes toast

model="models\props\truck\box.mdx;models\props\truck\tires.mdx;models\props\truck\wood.mdx;models\props\truck\c4.mdx;models\props\truck\m26y.mdx;models\props\truck\mn3.mdx;models\props\truck\mp1a.mdx;models\props\truck\v1a.mdx;models\props\truck\v1b.mdx;models\props\truck\v1c.mdx;"
*/

void truck_die_final (edict_t *self)
{
    if (self->s.frame < 59)
	{
		self->svflags &= ~SVF_NOCLIENT;
		self->handle2->svflags &= ~SVF_NOCLIENT;
		
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;
		self->handle2->s.frame++;
	}

	//self->s.origin[2] += 5;
	//gi.dprintf ("z: %5.3f\n", self->s.origin[2]);
}	

void truck_die_use (edict_t *self, edict_t *other, edict_t *activator)
{
	self->use = NULL;
	self->nextthink = level.time + FRAMETIME;
	self->think = truck_die_final;
}

void SP_props2_truck_die (edict_t *self)
{
	int i;
	edict_t	*newent = NULL;	

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.angles[1] = 270;
	
	//VectorSet (self->mins, -148, -61, -78);
	//VectorSet (self->maxs, 148, 61, 78);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/truck/box.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/truck/box.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/truck/c4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/truck/c4.mdx", &self->s.model_parts[1]);

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/truck/m26y.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/truck/m26y.mdx", &self->s.model_parts[2]);

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/truck/mn3.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/truck/mn3.mdx", &self->s.model_parts[3]);

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/truck/mp1a.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/truck/mp1a.mdx", &self->s.model_parts[4]);

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/truck/tires.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/truck/tires.mdx", &self->s.model_parts[5]);

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/truck/v1a.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/truck/v1a.mdx", &self->s.model_parts[6]);


	newent = G_Spawn();
	
	if (!newent)
		return;

	self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_NOT;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = newent->skin;
 	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/truck/v1b.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/truck/v1b.mdx", &newent->s.model_parts[0]);

	newent->s.num_parts++;
	newent->s.model_parts[1].modelindex = gi.modelindex("models/props/truck/v1c.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[1].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/truck/v1c.mdx", &newent->s.model_parts[1]);

	newent->s.num_parts++;
	newent->s.model_parts[2].modelindex = gi.modelindex("models/props/truck/wood.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[2].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/truck/wood.mdx", &newent->s.model_parts[2]);

	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	self->use = truck_die_use;

	self->s.renderfx2 |= RF2_NOSHADOW;	
	newent->s.renderfx2 |= RF2_NOSHADOW;	
	
	self->svflags |= SVF_NOCLIENT;
	newent->svflags |= SVF_NOCLIENT;

	gi.linkentity (newent);
	gi.linkentity (self);
}

/*QUAKED props_cola_machine (0 .5 .8) (-16 -24 -32) (24 32 32)

A cola machine

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\vending_mach\tris.md2"
*/

void SP_props_cola_machine (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/vending_mach/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -24, -16, -32);
		VectorSet (self->maxs, 24, 16, 32);		
	}
	else
	{
		VectorSet (self->mins, -16, -24, -32);
		VectorSet (self->maxs, 16, 24, 32);		
	}	

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props_cig_machine (0 .5 .8) (-16 -24 -32) (16 24 32)

A cigarette machine

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\cigmachine\tris.md2"
*/

void SP_props_cig_machine (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/cigmachine/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -24, -16, -32);
		VectorSet (self->maxs, 24, 16, 32);		
	}
	else
	{
		VectorSet (self->mins, -16, -24, -32);
		VectorSet (self->maxs, 16, 24, 32);		
	}	

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props2_barrels_fallA_TEST (0 .5 .8) (-69 -33 -49) (69 33 49)

First and last frame of barrels  

model="models\props\barl1test\1st.mdx;models\props\barl1test\last.mdx"
*/

/*QUAKED props2_barrels_fallA (0 .5 .8) (-69 -33 -49) (69 33 49)

A set of barrels that you can trigger to fall  

model="models\props\barl1\barrels.mdx;models\props\barl1\tops.mdx"
*/
void barrels_fallA (edict_t *self)
{
    if (self->s.frame < 28)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}	
	}
}	

void barrelsfallA_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = barrels_fallA;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_barrels_fallA (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -69, -33, -49);
	VectorSet (self->maxs, 69, 33, 49);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/barl1/barrels.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/barl1/barrels.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/barl1/tops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/barl1/tops.mdx", &self->s.model_parts[1]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallA_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props2_barrels_fallB_TEST (0 .5 .8) (-69 -33 -49) (69 33 49)

First and last frame of barrels  

model="models\props\barl2test\1st.mdx;models\props\barl2test\last.mdx"
*/

/*QUAKED props2_barrels_fallB (0 .5 .8) (-33 -81 -49) (33 81 49)

Another set of barrels that  you can trigger to fall  

model="models\props\barl2\barrels2.mdx;models\props\barl2\tops2.mdx"
*/
void barrels_fallB (edict_t *self)
{
    if (self->s.frame < 38)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}	
	}
}	

void barrelsfallB_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = barrels_fallB;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_barrels_fallB (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -33, -81, -49);
	VectorSet (self->maxs, 33, 81, 49);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/barl2/barrels2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/barl2/barrels2.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/barl2/tops2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/barl2/tops2.mdx", &self->s.model_parts[1]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallB_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props2_clubcouch (0 .5 .8) (-32 -64 -24) (32 64 24)

A couch

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\clubcouch\"
*/

void SP_props2_clubcouch (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/clubcouch/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -64, -32, -24);
		VectorSet (self->maxs, 64, 32, 24);		
	}
	else
	{
		VectorSet (self->mins, -32, -64, -24);
		VectorSet (self->maxs, 32, 64, 24);		
	}		
	
	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props2_clubchair (0 .5 .8) (-32 -32 -24) (32 32 24)

A pushable chair

model="models\props\clubchair\"
*/

void SP_props2_clubchair (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_STEP;
	self->svflags |= SVF_PROP;

	self->pullable = 1;
	self->nokickbackflag = 1;

	self->model = "models/props/clubchair/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -32, -32, -24);
	VectorSet (self->maxs, 32, 32, 24);		

	if (!self->mass)
		self->mass = 400;	

	if (!self->health)
		self->health = 25;

	//self->die = trashcanA_delay;
	//self->takedamage = DAMAGE_YES;

	self->cast_info.aiflags = AI_NOSTEP;
	self->touch = chair_touch;
	
	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	self->surfacetype = SURF_FABRIC;	
	gi.linkentity (self);
}

/*QUAKED props2_vaseA (0 .5 .8) (-16 -16 -24) (16 16 24)

A vase

model="models\props\vase1\"
*/

void SP_props2_vaseA (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/vase1/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 24);		

	if (!self->health)
		self->health = 25;

	self->die = metal_die;
	self->takedamage = DAMAGE_YES;

	self->surfacetype = SURF_TILE;
	gi.linkentity (self);
}

/*QUAKED props2_vaseB (0 .5 .8) (-16 -16 -24) (16 16 24)

A vase

model="models\props\vase2\"
*/

void SP_props2_vaseB (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/vase2/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -16, -16, -24);
	VectorSet (self->maxs, 16, 16, 24);		

	if (!self->health)
		self->health = 25;

	self->die = metal_die;
	self->takedamage = DAMAGE_YES;	
	
	self->surfacetype = SURF_TILE;
	gi.linkentity (self);
}

/*QUAKED props2_chair_conf (0 .5 .8) (-24 -24 -32) (24 24 32)

An pushable chair

model="models\props\confchair\"
*/

void SP_props2_chair_conf (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_STEP;
	self->svflags |= SVF_PROP;

	self->pullable = 1;
	self->nokickbackflag = 1;

	self->model = "models/props/confchair/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -24, -24, -32);
	VectorSet (self->maxs, 24, 24, 32);		

	if (!self->mass)
		self->mass = 400;	

	if (!self->health)
		self->health = 25;

	//self->die = trashcanA_delay;
	//self->takedamage = DAMAGE_YES;

	self->cast_info.aiflags = AI_NOSTEP;
	self->touch = chair_touch;
	
	self->think = M_droptofloor;
	self->nextthink = level.time + 2 * FRAMETIME;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props2_shelf_metal_A_fall (0 .5 .8) (-60 -20 -56) (60 20 66)

A falling metal shelf

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\shelfmetal1\shelf1.mdx;models\props\shelfmetal1\shelf2.mdx;models/props/shelfmetal1/barreltops.mdx;models/props/shelfmetal1/tanktops.mdx"
*/

void shelfA_fall_final_mb (edict_t *self)
{
    if (self->s.frame < 62)
	{
		self->solid = SOLID_NOT;
		
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;
		self->handle->s.frame++;
		self->handle2->s.frame++;
	}
}	

void shelfA_fall_die_mb (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = shelfA_fall_final_mb;
}

void SP_props2_shelf_metal_A_fall (edict_t *self)
{
	int i;
	edict_t	*newent = NULL;	
	edict_t	*newent2 = NULL;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -20, -60, -56);
		VectorSet (self->maxs, 20, 60, 66);		
	}
	else
	{
		VectorSet (self->mins, -60, -20, -56);
		VectorSet (self->maxs, 60, 20, 66);		
	}
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/shelfmetal1/shelf1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/shelf1.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/shelfmetal1/tanktops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/tanktops.mdx", &self->s.model_parts[1]);

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/shelfmetal1/shelf2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/shelf2.mdx", &self->s.model_parts[2]);

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/shelfmetal1/barre1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/barre1.mdx", &self->s.model_parts[3]);

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/shelfmetal1/barre2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/barre2.mdx", &self->s.model_parts[4]);

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/shelfmetal1/barre3.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/barre3.mdx", &self->s.model_parts[5]);

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/shelfmetal1/barre4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/barre4.mdx", &self->s.model_parts[6]);


	newent = G_Spawn();
	
	if (!newent)
		return;

	self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_NOT;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = newent->skin;
 	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	//newent->s.num_parts++;
	//newent->s.model_parts[0].modelindex = gi.modelindex("models/props/shelfmetal1/cartboard1.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	//gi.GetObjectBounds("models/props/shelfmetal1/cartboard1.mdx", &newent->s.model_parts[0]);

	//newent->s.num_parts++;
	//newent->s.model_parts[1].modelindex = gi.modelindex("models/props/shelfmetal1/cartboard2.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	newent->s.model_parts[1].skinnum[i] = newent->s.skinnum;
	//gi.GetObjectBounds("models/props/shelfmetal1/cartboard2.mdx", &newent->s.model_parts[1]);

	//newent->s.num_parts++;
	//newent->s.model_parts[2].modelindex = gi.modelindex("models/props/shelfmetal1/tank_lg.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	newent->s.model_parts[2].skinnum[i] = newent->s.skinnum;
	//gi.GetObjectBounds("models/props/shelfmetal1/tank_lg.mdx", &newent->s.model_parts[2]);

	newent->s.num_parts++;
	newent->s.model_parts[3].modelindex = gi.modelindex("models/props/shelfmetal1/tank_lg3.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[3].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/tank_lg3.mdx", &newent->s.model_parts[3]);

	newent->s.num_parts++;
	newent->s.model_parts[4].modelindex = gi.modelindex("models/props/shelfmetal1/tank_lg1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[4].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/tank_lg1.mdx", &newent->s.model_parts[4]);

	newent->s.num_parts++;
	newent->s.model_parts[5].modelindex = gi.modelindex("models/props/shelfmetal1/tank_lg2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[5].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/tank_lg2.mdx", &newent->s.model_parts[5]);

	newent2 = G_Spawn();
	
	if (!newent2)
		return;

	self->handle = newent2;

	VectorCopy(self->s.origin, newent2->s.origin);
	VectorCopy(self->s.angles, newent2->s.angles);

	newent2->solid = SOLID_NOT;
	newent2->movetype = MOVETYPE_NONE;
	newent2->svflags |= SVF_PROP;

	newent2->s.skinnum = newent2->skin;
 	memset(&(newent2->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent2->s.num_parts++;
	newent2->s.model_parts[0].modelindex = gi.modelindex("models/props/shelfmetal1/tank_sm.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[0].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/tank_sm.mdx", &newent2->s.model_parts[0]);

	newent2->s.num_parts++;
	newent2->s.model_parts[1].modelindex = gi.modelindex("models/props/shelfmetal1/tank_sm1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[1].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/tank_sm1.mdx", &newent2->s.model_parts[1]);

	newent2->s.num_parts++;
	newent2->s.model_parts[2].modelindex = gi.modelindex("models/props/shelfmetal1/tank_sm2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[2].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/tank_sm2.mdx", &newent2->s.model_parts[2]);

	newent2->s.num_parts++;
	newent2->s.model_parts[3].modelindex = gi.modelindex("models/props/shelfmetal1/barreltops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[3].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal1/barreltops.mdx", &newent2->s.model_parts[3]);	

	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent2->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	self->die = shelfA_fall_die_mb;
	self->takedamage = DAMAGE_YES;

	newent->surfacetype = SURF_METAL_L;
	newent2->surfacetype = SURF_METAL_L;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (newent);
	gi.linkentity (newent2);
	gi.linkentity (self);
}

/*QUAKED props2_shelf_metal_B_fall (0 .5 .8) (-60 -20 -56) (60 20 66)

Another falling metal shelf

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\shelfmetal2\shelf1.mdx;models\props\shelfmetal2\shelf2.mdx;models/props/shelfmetal2/barreltops.mdx;models/props/shelfmetal2/tanktops.mdx"
*/

void shelfB_fall_final_mb (edict_t *self)
{
    if (self->s.frame < 76)
	{
		self->solid = SOLID_NOT;
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;
		self->handle->s.frame++;
		self->handle2->s.frame++;
	}
}	

void shelfB_fall_die_mb (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	self->takedamage = DAMAGE_NO;
	self->nextthink = level.time + FRAMETIME;
	self->think = shelfB_fall_final_mb;
}

void SP_props2_shelf_metal_B_fall (edict_t *self)
{
	int i;
	edict_t	*newent = NULL;	
	edict_t	*newent2 = NULL;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -20, -60, -56);
		VectorSet (self->maxs, 20, 60, 66);		
	}
	else
	{
		VectorSet (self->mins, -60, -20, -56);
		VectorSet (self->maxs, 60, 20, 66);		
	}
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/shelfmetal2/shelf1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/shelf1.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/shelfmetal2/tanktops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/tanktops.mdx", &self->s.model_parts[1]);

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/shelfmetal2/shelf2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/shelf2.mdx", &self->s.model_parts[2]);

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/shelfmetal2/barre1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/barre1.mdx", &self->s.model_parts[3]);

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/shelfmetal2/barre2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/barre2.mdx", &self->s.model_parts[4]);

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/shelfmetal2/barre3.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/barre3.mdx", &self->s.model_parts[5]);

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/shelfmetal2/barre4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/barre4.mdx", &self->s.model_parts[6]);


	newent = G_Spawn();
	
	if (!newent)
		return;

	self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_NOT;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = newent->skin;
 	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/shelfmetal2/cartboard1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/cartboard1.mdx", &newent->s.model_parts[0]);

	newent->s.num_parts++;
	newent->s.model_parts[1].modelindex = gi.modelindex("models/props/shelfmetal2/cartboard2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[1].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/cartboard2.mdx", &newent->s.model_parts[1]);

	//newent->s.num_parts++;
	//newent->s.model_parts[2].modelindex = gi.modelindex("models/props/shelfmetal2/tank_lg.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	newent->s.model_parts[2].skinnum[i] = newent->s.skinnum;
	//gi.GetObjectBounds("models/props/shelfmetal2/tank_lg.mdx", &newent->s.model_parts[2]);

	//newent->s.num_parts++;
	//newent->s.model_parts[3].modelindex = gi.modelindex("models/props/shelfmetal2/tank_lg3.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	newent->s.model_parts[3].skinnum[i] = newent->s.skinnum;
	//gi.GetObjectBounds("models/props/shelfmetal2/tank_lg3.mdx", &newent->s.model_parts[3]);

	newent->s.num_parts++;
	newent->s.model_parts[4].modelindex = gi.modelindex("models/props/shelfmetal2/tank_lg1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[4].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/tank_lg1.mdx", &newent->s.model_parts[4]);

	newent->s.num_parts++;
	newent->s.model_parts[5].modelindex = gi.modelindex("models/props/shelfmetal2/tank_lg2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[5].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/tank_lg2.mdx", &newent->s.model_parts[5]);

	newent2 = G_Spawn();
	
	if (!newent2)
		return;

	self->handle = newent2;

	VectorCopy(self->s.origin, newent2->s.origin);
	VectorCopy(self->s.angles, newent2->s.angles);

	newent2->solid = SOLID_NOT;
	newent2->movetype = MOVETYPE_NONE;
	newent2->svflags |= SVF_PROP;

	newent2->s.skinnum = newent2->skin;
 	memset(&(newent2->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent2->s.num_parts++;
	newent2->s.model_parts[0].modelindex = gi.modelindex("models/props/shelfmetal2/tank_sm.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[0].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/tank_sm.mdx", &newent2->s.model_parts[0]);

	newent2->s.num_parts++;
	newent2->s.model_parts[1].modelindex = gi.modelindex("models/props/shelfmetal2/tank_sm1.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[1].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/tank_sm1.mdx", &newent2->s.model_parts[1]);

	newent2->s.num_parts++;
	newent2->s.model_parts[2].modelindex = gi.modelindex("models/props/shelfmetal2/tank_sm2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[2].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/tank_sm2.mdx", &newent2->s.model_parts[2]);

	newent2->s.num_parts++;
	newent2->s.model_parts[3].modelindex = gi.modelindex("models/props/shelfmetal2/barreltops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent2->s.model_parts[3].skinnum[i] = newent2->s.skinnum;
	gi.GetObjectBounds("models/props/shelfmetal2/barreltops.mdx", &newent2->s.model_parts[3]);	

	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent2->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	
	self->die = shelfB_fall_die_mb;
	self->takedamage = DAMAGE_YES;

	newent->surfacetype = SURF_METAL_L;
	newent2->surfacetype = SURF_METAL_L;
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (newent);
	gi.linkentity (newent2);
	gi.linkentity (self);
}

/*QUAKED props2_deadguy (0 .5 .8) (-40 -27 -9) (40 27 9)

An dead guy body you can shoot

The bounding box can be rotated in angles of 90 deg and block properly

"health" - pre-gib hit points for the dead body (50 default)

model="models\props\deadguy\body.mdx;models\props\deadguy\head.mdx;models\props\deadguy\legs.mdx"
*/

void body_gib (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	int i;
	vec3_t realorigin;

	VectorCopy(self->s.origin, realorigin);
	realorigin[2] += 8;

	for (i = 0; i < 20; i++)
	{
		realorigin[0] = (self->s.origin[0] + ((rand()&63) - 32));
		realorigin[1] = (self->s.origin[1] + ((rand()&63) - 31));			
		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_GIBS);
		gi.WritePosition (realorigin);
		gi.WriteDir (vec3_origin);
		gi.WriteByte ( 2 );	// number of gibs
		gi.WriteByte ( 0 );	// scale of direction to add to velocity
		gi.WriteByte ( 0 );	// random offset scale
		gi.WriteByte ( 10 );	// random velocity scale
		gi.multicast (realorigin, MULTICAST_PVS);

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_SPLASH);
		gi.WriteByte (4);
		gi.WritePosition (realorigin);
		gi.WriteDir (self->movedir);
		gi.WriteByte (6);
		gi.multicast (realorigin, MULTICAST_PVS);
	}

	if (self->item)
	{
		Drop_Item (self, self->item);
		self->item = NULL;
	}

	G_FreeEdict (self);
}

void SP_props2_deadguy (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->svflags |= SVF_DEADMONSTER;

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -27, -40, -9);
		VectorSet (self->maxs, 27, 40, 9);		
	}
	else
	{
		VectorSet (self->mins, -40, -27, -9);
		VectorSet (self->maxs, 40, 27, 9);		
	}

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/deadguy/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/deadguy/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/deadguy/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/deadguy/body.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/deadguy/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/deadguy/legs.mdx", &self->s.model_parts[2]);	

	self->die = body_gib;
	self->takedamage = DAMAGE_YES;

	if (!self->health)
		self->health = 50;
	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->surfacetype = SURF_FABRIC;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}	
	
	gi.linkentity (self);
}


/*QUAKED props2_deadguy_underwater (0 .5 .8) (-17 -50 0) (13 30 88)

An underwater dead guy in cement body you can shoot

The bounding box can be rotated in angles of 90 deg and block properly

"health" - pre-gib hit points for the dead body (50 default)

model="models\props\cementguy\body.mdx;models\props\cementguy\head.mdx;models\props\cementguy\legs.mdx"
*/

void think_deadguy_underwater (edict_t *self)
{
	if (self->s.frame < 39)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}

	self->nextthink = level.time + FRAMETIME;
}

void SP_props2_deadguy_underwater (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -64, -32, 0);
		VectorSet (self->maxs, 64, 32, 88);		
	}
	else
	{
		VectorSet (self->mins, -32, -64, -0);
		VectorSet (self->maxs, 32, 64, 88);		
	}

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/cementguy/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cementguy/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/cementguy/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cementguy/head.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/cementguy/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cementguy/legs.mdx", &self->s.model_parts[2]);	

	self->die = body_gib;
	self->takedamage = DAMAGE_YES;

	if (!self->health)
		self->health = 50;
	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->surfacetype = SURF_FABRIC;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}	
	
	gi.linkentity (self);

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->think = think_deadguy_underwater;
	self->nextthink = level.time + (FRAMETIME*3);
}

/*QUAKED props2_deadgal_headless (0 .5 .8) (-32 -26 -7) (32 26 7)

A female dead body you can shoot that has no head

The bounding box can be rotated in angles of 90 deg and block properly

"health" - pre-gib hit points for the dead body (50 default)

model="models\props\dead_fem\body.mdx;models\props\dead_fem\legs.mdx"
*/

void SP_props2_deadgal_headless (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->svflags |= SVF_DEADMONSTER;

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -26, -32, -7);
		VectorSet (self->maxs, 26, 32, 7);		
	}
	else
	{
		VectorSet (self->mins, -32, -26, -7);
		VectorSet (self->maxs, 32, 26, 7);		
	}

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/dead_fem/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/dead_fem/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/dead_fem/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/dead_fem/legs.mdx", &self->s.model_parts[1]);	

	self->die = body_gib;
	self->takedamage = DAMAGE_YES;

	if (!self->health)
		self->health = 50;
	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->surfacetype = SURF_FABRIC;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}	
	
	gi.linkentity (self);
}

#define FLAG1  2
#define FLAG2  4
#define FLAG3  8

/*QUAKED props2_flag (0 .5 .8) (-47 -6 -100) (47 6 100) ? FLAG1 FLAG2 FLAG3

A flag

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\flag\flag1.md2"
*/

void think_flag (edict_t *self)
{
	if (self->s.frame < 39)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}

	self->nextthink = level.time + FRAMETIME;
}

void SP_props2_flag (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (self->spawnflags & FLAG2)
	{
		self->model = "models/props/flag/flag1.md2";
	}
	else if (self->spawnflags & FLAG3)
	{
		self->model = "models/props/flag/flag2.md2";
	}
	else
	{
		self->model = "models/props/flag/flag3.md2";
	}

	self->s.modelindex = gi.modelindex (self->model);

	
	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -6, -47, -100);
		VectorSet (self->maxs, 6, 47, 100);		
	}
	else
	{
		VectorSet (self->mins, -47, -6, -100);
		VectorSet (self->maxs, 47, 6, 100);		
	}	
	
	self->s.renderfx2 |= RF2_NOSHADOW;
	
	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);

	self->nextthink = level.time + FRAMETIME *2;
	self->think = think_flag;
}

/*QUAKED props2_fish (0 .5 .8) (-12 -12 0) (12 12 10)

A fish

"dmg" - fish bite damage (2 default)

"health" - heath of the fish (10 default)

*/

void fish_die (edict_t *self, edict_t *inflictor, edict_t *attacker, int damage, vec3_t point, int mdx_part, int mdx_subobject)
{
	vec3_t realorigin;

	VectorCopy(self->s.origin, realorigin);
	realorigin[2] += 8;

	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_SPLASH);
	gi.WriteByte (15);
	gi.WritePosition (realorigin);
	gi.WriteDir (self->movedir);
	gi.WriteByte (6);
	gi.multicast (realorigin, MULTICAST_PVS);

	// If this fish was spawned - tell spawner to make a new one
	if (self->targetname)
	{
		int i;
		edict_t	*e = NULL;

		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "props2_fish_spawner")) &&
			    (e->target) && (!strcmp(e->target, self->targetname)))
			{
				e->fxdensity++;	
				break;	
			}
		}	
	}

	G_FreeEdict (self);
}

int check_fish_hit_player(edict_t *ent)
{
	trace_t tr;
	vec3_t	endpos, forward;

	AngleVectors (ent->s.angles, forward, NULL, NULL);
	VectorMA(ent->s.origin, 32, forward, endpos);
	endpos[2] += 32;
	tr = gi.trace(ent->s.origin, NULL, NULL, endpos, ent, MASK_SHOT);

	if (tr.fraction < 1)
	{
		if ((tr.ent) && (tr.ent->client))
		{
			vec3_t	start, aimdir, dang;
		
			if (ent->timestamp > level.time)
				return false;

			ent->timestamp = level.time + 0.5;

			ent->debugprint = 1;
    
			//T_Damage (tr.ent, tr.ent, tr.ent, vec3_origin, tr.ent->s.origin, vec3_origin, ent->dmg, ent->dmg, 0, MOD_DOGBITE);

			VectorSubtract (tr.ent->s.origin, ent->s.origin, aimdir);
			vectoangles (aimdir, dang);
			AngleVectors (dang, forward, NULL, NULL);
			VectorMA (ent->s.origin, 16, forward, start);
		
			fire_rat (ent, start, forward, ent->dmg);

			return true;
		}
	}	

	return false;
}

void fish_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	if (!other->client)
		return;

	if (self->timestamp > level.time)
		return;

	self->timestamp = level.time + 0.5;

	self->debugprint = 1;
    
	T_Damage (other, self, self, vec3_origin, other->s.origin, vec3_origin, self->dmg, self->dmg, 0, MOD_DOGBITE);	
}

void fish_go (edict_t *self)
{
	if (self->option)
	{	
		cvar_t	*props; 
		
		props = gi.cvar("props", "1", CVAR_ARCHIVE);
		
		if (!props->value)
		{
			self->nextthink = level.time + (FRAMETIME * 10);
			return;
		}
	}
	
	self->waterlevel = 3;
	M_walkmove (self, self->healspeed, 16 * FRAMETIME);

	if (!VectorCompare(self->s.origin, self->s.old_origin))
	{
		if (self->s.frame <= 1)
		{
			self->s.frame++;
		}
		else
		{
			self->s.frame = 0;
		}
	
	if (self->fxdensity++ >= self->deadticks)
	{
		vec3_t		point;
		int			cont;
		int			cangoup = 0;
		int			cangodown = 0;

		point[0] = self->s.origin[0];
		point[1] = self->s.origin[1];
		point[2] = self->s.origin[2] + self->maxs[2] - 2;	
		cont = gi.pointcontents (point);

		if (cont & MASK_WATER)
			cangoup = 1;

		point[0] = self->s.origin[0];
		point[1] = self->s.origin[1];
		point[2] = self->s.origin[2] + self->mins[2] - 4;	
		cont = gi.pointcontents (point);		

		if (cont & MASK_WATER)
			cangodown = 1;

		self->deadticks = rand()&7;
		self->healspeed += (rand()&7)-4;  
		
		if (self->deadticks > 3)
		{
			if (cangodown)
				self->s.origin[2] -= 0.5;
		}
		else
		{
			if (cangoup)
				self->s.origin[2] += 0.5;
		}
		
		if (self->healspeed > 360)
			self->healspeed = (self->healspeed - 360);
		if (self->healspeed < 0)
			self->healspeed = (self->healspeed + 360);
		
		self->s.angles[1] = self->healspeed; 
	}
	}
	else
	{
		if (self->s.frame <= 1)
		{
			self->s.frame++;
		}
		else
		{
			self->s.frame = 0;
		}
		
		if (self->durationflag)
			self->healspeed += 8;
		else
			self->healspeed -= 8;

		if (self->healspeed > 360)
			self->healspeed = (self->healspeed - 360);
		if (self->healspeed < 0)
			self->healspeed = (self->healspeed + 360);
		self->s.angles[1] = self->healspeed; 

		self->waterlevel = 3;
		M_walkmove (self, self->healspeed, 16 * FRAMETIME);	

		if (!VectorCompare(self->s.origin, self->s.old_origin))
		{
			self->deadticks = (rand()&7)+12;
		}
		else
		{
			check_fish_hit_player(self);
		}
	}

	self->nextthink = level.time + FRAMETIME;
}


void SP_props2_fish (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_FLY;
	self->svflags |= SVF_PROP;
	self->flags |= FL_FLY;
	self->waterlevel = 3;

	VectorSet (self->mins, -8, -8, 0);
	VectorSet (self->maxs, 8, 8, 10);		
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/actors/shrimp/shrimp.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/actors/shrimp/shrimp.mdx", &self->s.model_parts[0]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->monsterprop = 1;
	self->deadticks = 1;
	self->fxdensity = 0;
	self->healspeed = rand()&360;
	self->debugprint = 0;
	// Born left or right handed
	self->durationflag = rand()&1;

	self->die = fish_die;
	self->touch = fish_touch;
	self->takedamage = DAMAGE_YES;
	self->cast_info.aiflags = AI_NOSTEP;

	if (!self->dmg)
		self->dmg = 2;

	if (!self->health)
		self->health = 10;

	self->think = fish_go;
	self->nextthink = level.time + (FRAMETIME * 2);

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props2_fish_trigger (0 .5 .8) (-12 -12 0) (12 12 10)

A fish that is spawned when triggered

"dmg" - fish bite damage (2 default)

"health" - heath of the fish (10 default)

"targetname" - target ID
*/

void fish_trigger_use  (edict_t *self, edict_t *other, edict_t *activator)
{
	self->svflags &= ~SVF_NOCLIENT;
	self->use = NULL;
	self->targetname = NULL;
	self->solid = SOLID_BBOX;
	self->think = fish_go;
	self->nextthink = level.time + FRAMETIME;
}

void SP_props2_fish_trigger (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->movetype = MOVETYPE_FLY;
	self->svflags |= SVF_PROP;
	self->flags |= FL_FLY;
	self->waterlevel = 3;

	VectorSet (self->mins, -8, -8, 0);
	VectorSet (self->maxs, 8, 8, 10);		
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/actors/shrimp/shrimp.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/actors/shrimp/shrimp.mdx", &self->s.model_parts[0]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->monsterprop = 1;
	self->deadticks = 1;
	self->fxdensity = 0;
	self->healspeed = rand()&360;
	self->debugprint = 0;
	// Born left or right handed
	self->durationflag = rand()&1;

	self->die = fish_die;
	self->touch = fish_touch;
	self->takedamage = DAMAGE_YES;
	self->cast_info.aiflags = AI_NOSTEP;

	if (!self->dmg)
		self->dmg = 2;

	if (!self->health)
		self->health = 10;

	if (self->targetname)
	{
		self->solid = SOLID_NOT;		
		self->use = fish_trigger_use;
		self->svflags |= SVF_NOCLIENT;	
	}
	else
	{
		gi.dprintf ("props2_fish_trigger without a targetname at %s\n", vtos(self->absmin));
		G_FreeEdict (self);
		return;
	}

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props2_fish_spawner (0 .5 .8) (-16 -16 -16) (16 16 16)

Base fish spawner

 props2_fish_spawner_node  determine possible spawn point

 "dmg" - fish bite damage (2 default)

 "health" - heath of the fish (10 default)

 "deadticks" - total number of fishs in level from spawner at a time (default 5)

 "target" - ID string for spawner 
*/

void fish_spawn_think (edict_t *self)
{
	if (self->fxdensity)
	{
		int i, tnode, node;
		edict_t	*e = NULL;
			
		if (self->option)
		{	
			cvar_t	*props; 
			
			props = gi.cvar("props", "1", CVAR_ARCHIVE);
			
			if (!props->value)
			{
				self->nextthink = level.time + FRAMETIME * 50;
				return;
			}
		}

		tnode = rand()%self->firetype;
		node = 0;

		// Find a spawner origin
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "props2_fish_spawner_node")) &&
			    (e->targetname) && (self->target) && (!strcmp(e->targetname, self->target)))
			{
				if (node == tnode)
				{
					edict_t	*fish = NULL;
					
					fish = G_Spawn();
		
					if (!fish)
						return;
					
					// Spawn new fish
					VectorCopy(e->s.origin, fish->s.origin);
					fish->s.origin[2] -= 6;
					fish->targetname = self->target;
					fish->dmg = self->dmg;
					fish->health = self->health;
					fish->option = self->option;
					SP_props2_fish(fish);
					self->fxdensity--;
					self->nextthink = level.time + FRAMETIME * 50;
					return;	
				}

				node++;
			}
		}	
	}
	
	self->nextthink = level.time + FRAMETIME * 10;	
}

void fish_spawn_first_think (edict_t *self)
{
	int i;
	edict_t	*e = NULL;
	
	if (self->target)
	{
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((e->classname) && (!strcmp(e->classname, "props2_fish_spawner_node")) &&
				(e->targetname) && (!strcmp(e->targetname, self->target)))
			{
				self->firetype++;
			}
		}
		
		if (self->firetype)
		{
			self->think = fish_spawn_think;
			self->nextthink = level.time + FRAMETIME;	
		}
	}
	else
	{
		gi.dprintf ("props2_fish_spawner without a target at %s\n", vtos(self->absmin));
	}
}

void SP_props2_fish_spawner (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	if (!self->deadticks)
		self->deadticks = 5;
	
	self->fxdensity = self->deadticks; 

	if (!self->dmg)
		self->dmg = 2;

	if (!self->health)
		self->health = 10;

	self->firetype = 0;

	self->think = fish_spawn_first_think;
	self->nextthink = level.time + (FRAMETIME * 3);	

	gi.linkentity (self);
}
// END JOSEPH

/*QUAKED props2_fish_spawner_node (0 .5 .8) (-16 -16 -16) (16 16 16)

 Possible fish spawn point from props2_fish_spawner

 "targetname" - ID string for spawner 	
*/

void SP_props2_fish_spawner_node (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	gi.linkentity (self);
}

/*QUAKED props2_wall_fish (0 .5 .8) (-2 -40 -12) (2 40 12)

A fish on the wall 

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\fish\tris.md2"
*/

void SP_props2_wall_fish (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/fish/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -40, -2, -12);
		VectorSet (self->maxs, 40, 2, 12);	
	}
	else
	{
		VectorSet (self->mins, -2, -40, -12);
		VectorSet (self->maxs, 2, 40, 12);	
	}	

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->surfacetype = SURF_WOOD;	
	gi.linkentity (self);
}

/*QUAKED props2_barrels_fall_ST (0 .5 .8) (-89 -48 -56) (89 48 56)

A set of barrels that you can trigger to fall  

model="models\props\barl_steel\barrels.mdx;models\props\barl_steel\tops.mdx;models\props\barl_steel\door.mdx"
*/
void barrels_fallST (edict_t *self)
{
    if (self->s.frame < 37)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}	
	}
}	

void barrelsfallST_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = barrels_fallST;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_barrels_fall_ST (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -89, -48, -56);
	VectorSet (self->maxs, 89, 48, 56);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/barl_steel/barrels.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/barl_steel/barrels.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/barl_steel/door.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/barl_steel/door.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/barl_steel/tops.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/barl_steel/tops.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallST_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props2_sign (0 .5 .8) (-4 -44 -44) (4 44 44)

A sign  

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\sign\sign.mdx;models\props\sign\bar.mdx;models\props\sign\chain.mdx"
*/
void think_sign (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 40)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}
}

void SP_props2_sign (edict_t *self)
{
	int i;

    if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 
	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -44, -4, -44);
		VectorSet (self->maxs, 44, 4, 44);	
	}
	else
	{
		VectorSet (self->mins, -4, -44, -44);
		VectorSet (self->maxs, 4, 44, 44);	
	}
	
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/sign/sign.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/sign/sign.mdx", &self->s.model_parts[0] );
 
	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/sign/bar.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/sign/bar.mdx", &self->s.model_parts[1] );

 	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);

	self->think = think_sign;
	self->nextthink = level.time + 2 * FRAMETIME;
}

/*QUAKED props2_lighthouse_beam (0 .5 .8) (-16 -16 -88) (16 16 -40)

A light house light beam that rotates

-482 -25 -88, -85 25 -40

"reactdelay" light distance from center (default 40)

model="models\props\litecone\litecone.mdx"
*/
void think_lighthouse_beam (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	self->s.angles[1] += 3;

	if (self->handle)
	{
		vec3_t forward;

		AngleVectors(self->s.angles, forward, NULL, NULL);
		VectorMA(self->s.origin, self->reactdelay, forward, self->handle->s.origin);		
		self->handle->s.origin[2] -= 64;
	}
}

void SP_props2_lighthouse_beam (edict_t *self)
{
	int i;

    if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/litecone/litecone.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/litecone/litecone.mdx", &self->s.model_parts[0] );
 
	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_PASSALPHA;
	self->s.effects = 128+32;
	
	gi.linkentity (self);

	if (!self->reactdelay)
		self->reactdelay = 40;

	{
		edict_t	*newent = NULL;	
		vec3_t  forward;

		newent = G_Spawn();
	
		if (!newent)
			return;

		self->handle = newent;
	
		AngleVectors(self->s.angles, forward, NULL, NULL);
		VectorMA(self->s.origin, self->reactdelay, forward, newent->s.origin);				
		newent->s.origin[2] -= 64;
		newent->s.effects |= EF_BLUEHYPERBLASTER;
	
		newent->s.modelindex = gi.modelindex("models/weapons/sshell_md2/tris.md2");		

		gi.linkentity (newent);

		newent->s.renderfx |= RF_BEAM;

		newent->s.renderfx2 |= RF2_NOSHADOW;
	}

	self->think = think_lighthouse_beam;
	self->nextthink = level.time + 2 * FRAMETIME;
}

/*QUAKED props2_boat (0 .5 .8) (-80 -160 -38) (80 160 38)

A boat  

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\boat\boat.mdx;models\props\boat\glass.mdx"
*/

void SP_props2_boat (edict_t *self)
{
	int i;
	edict_t *newent = NULL;

    if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 
	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -160, -80, -38);
		VectorSet (self->maxs, 160, 80, 38);	
	}
	else
	{
		VectorSet (self->mins, -80, -160, -38);
		VectorSet (self->maxs, 80, 160, 38);	
	}
	
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/boat/boat.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/boat/boat.mdx", &self->s.model_parts[0] );
 
	newent = G_Spawn();
	
	if (!newent)
		return;

	//self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_BBOX;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = self->skin;
	
	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/boat/glass.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds( "models/props/boat/glass.mdx", &newent->s.model_parts[0] );

	newent->s.renderfx2 |= RF2_NOSHADOW;
	newent->s.renderfx2 |= RF2_PASSALPHA;
	newent->s.effects = 64;
	
	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent->surfacetype = SURF_METAL;
	gi.linkentity (newent);

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props2_buoy (0 .5 .8) (-41 -41 -75) (41 41 75)

A buoy

model="models\props\buoy\buoy.mdx"
*/

void SP_props2_buoy (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -41, -41, -75);
	VectorSet (self->maxs, 41, 41, 75);		
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/buoy/buoy.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/buoy/buoy.mdx", &self->s.model_parts[0]);

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/buoy/light.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/buoy/light.mdx", &self->s.model_parts[1]);	
	
	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);

	//AddLightSource(self);
}


/*QUAKED props2_buoy_side (1 0 0) (-81 -55 -64) (81 55 64)

A buoy on it's side

model="models\props\buoyside\buoy.mdx"
*/

void SP_props2_buoy_side (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -81, -55, -64);
	VectorSet (self->maxs, 81, 55, 64);	
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/buoyside/buoy.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/buoyside/buoy.mdx", &self->s.model_parts[0]);

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/buoyside/light.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/buoyside/light.mdx", &self->s.model_parts[1]);	

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);

	//AddLightSource(self);
}

/*QUAKED props2_buoy_animate (0 .5 .8) (-41 -41 -75) (41 41 75)

An animated buoy

model="models\props\buoya\buoy.mdx"
*/

void think_buoya (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 49)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}
}

void SP_props2_buoy_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -41, -41, -75);
	VectorSet (self->maxs, 41, 41, 75);		
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/buoya/buoy.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/buoy/buoy.mdx", &self->s.model_parts[0]);

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/buoya/light.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/buoy/light.mdx", &self->s.model_parts[1]);	
	
	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);

	self->think = think_buoya;
	self->nextthink = level.time + 2 * FRAMETIME;

	//AddLightSource(self);
}

/*QUAKED props2_gargoyle (0 .5 .8) (-47 -22 -50) (47 22 50)

A gargoyle

model="models\props\gargoyle\"
*/

void SP_props2_gargoyle (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->model = "models/props/gargoyle/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -47, -22, -50);
	VectorSet (self->maxs, 47, 22, 50);		

	self->surfacetype = SURF_METAL;
	self->s.renderfx2 |= RF2_NOSHADOW;
	gi.linkentity (self);
}

#define DONOTMOVE   2

/*QUAKED props2_clothesline (0 .5 .8) (-4 -85 -25) (4 85 25) ? DONOTMOVE

A clothes line

model="models\props\clothes\"
*/

void think_clothesline (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 19)
	{
		self->s.frame++;
	}
	else
	{
		self->s.frame = 0;
	}
}

void SP_props2_clothesline (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/clothes/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -4, -85, -25);
	VectorSet (self->maxs, 4, 85, 25);		

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);

	if (!(self->spawnflags & DONOTMOVE))
	{
		self->think = think_clothesline;
		self->nextthink = level.time + 2 * FRAMETIME;
	}
}


/*QUAKED props2_plant_XL (0 .5 .8) (-50 -46 -53) (50 46 53)

A plant

model="models\props\plants\plant_xl.md2"
*/

void SP_props2_plant_XL (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/plants/plant_xl.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -50, -46, -53);
	VectorSet (self->maxs, 50, 46, 53);		

	if (!self->health)
		self->health = 25;

	self->die = metal_die;
	self->takedamage = DAMAGE_YES;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props2_plant_SM (0 .5 .8) (-12 -9 -20) (12 9 20)

A plant

model="models\props\plants\plant_sm.md2"
*/

void SP_props2_plant_SM (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/plants/plant_sm.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -12, -9, -20);
	VectorSet (self->maxs, 12, 9, 20);		

	if (!self->health)
		self->health = 25;

	self->die = metal_die;
	self->takedamage = DAMAGE_YES;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props2_lunch (0 .5 .8) (-10 -7 -5) (10 7 5)

A lunch

model="models\props\lunch_set\tris.md2"
*/

void SP_props2_lunch (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/lunch_set/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -10, -7, -5);
	VectorSet (self->maxs, 10, 7, 5);		

	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props2_ashtray (0 .5 .8) (-12 -18 -4) (12 18 4)

An ashtray

model="models\props\ashtray_set\tris.md2"
*/

void SP_props2_ashtray (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/ashtray_set/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -12, -18, -4);
	VectorSet (self->maxs, 12, 18, 4);		

	self->surfacetype = SURF_TILE;
	gi.linkentity (self);
}

/*QUAKED props2_boatphone (0 .5 .8) (-5 -9 -12) (5 9 12)

A boat phone

model="models\props\boatphone\tris.md2"
*/

void SP_props2_boatphone (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/boatphone/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -5, -9, -12);
	VectorSet (self->maxs, 5, 9, 12);		

	self->surfacetype = SURF_METAL_L;
	gi.linkentity (self);
}

/*QUAKED props2_plant_bush (0 .5 .8) (-9 -11 -32) (9 11 32)

A bush like plant

model="models\props\bush\tris.md2"
*/

void SP_props2_plant_bush (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/bush/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -9, -11, -32);
	VectorSet (self->maxs, 9, 11, 32);		

	if (!self->health)
		self->health = 25;

	self->die = metal_die;
	self->takedamage = DAMAGE_YES;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props2_boat_animate (0 .5 .8) (-80 -160 -38) (80 160 38)

An animated boat

model="models\props\boata\boat.mdx"
*/

void think_boat_a (edict_t *self)
{
	self->nextthink = level.time + FRAMETIME;
 
	if (self->s.frame < 49)
	{
		self->s.frame++;
	
		if (self->handle)
			self->handle->s.frame++;
	}
	else
	{
		self->s.frame = 0;

		if (self->handle)
			self->handle->s.frame = 0;	
	}
}

void SP_props2_boat_animate (edict_t *self)
{
	int i;
	edict_t *newent = NULL;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -80, -160, -38);
	VectorSet (self->maxs, 80, 160, 38);		
	
	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/boata/boat.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/boata/boat.mdx", &self->s.model_parts[0]);

	newent = G_Spawn();
	
	if (!newent)
		return;

	self->handle = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_BBOX;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = self->skin;
	
	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/boata/window.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds( "models/props/boata/window.mdx", &newent->s.model_parts[0] );

	newent->s.renderfx2 |= RF2_NOSHADOW;
	newent->s.renderfx2 |= RF2_PASSALPHA;
	newent->s.effects = 64;
	
	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent->surfacetype = SURF_METAL;
	gi.linkentity (newent);

	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);

	self->think = think_boat_a;
	self->nextthink = level.time + 2 * FRAMETIME;
}

/*QUAKED props2_helicopter_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

A helicopter and actor that animate when trigered  

model="models\props\helicopter\helicopter.mdx;models\props\helicopter\rotor.mdx;models\props\helicopter\body.mdx;models\props\helicopter\foot.mdx;models\props\helicopter\legs.mdx;models\props\helicopter\head.mdx"
*/
void helicopter_a_final (edict_t *self)
{
    if (self->s.frame < 223)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
}	

void helicopter_a_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = helicopter_a_final;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_helicopter_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/helicopter/helicopter.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/helicopter/helicopter.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/helicopter/rotor.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/helicopter/rotor.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/helicopter/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/helicopter/legs.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/helicopter/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/helicopter/body.mdx", &self->s.model_parts[3]);	

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/helicopter/foot.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/helicopter/foot.mdx", &self->s.model_parts[4]);	

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/helicopter/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/helicopter/head.mdx", &self->s.model_parts[5]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = helicopter_a_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}


/*QUAKED props2_car_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

A car and actors that animate when trigered  

model="models\props\cars\car.mdx;models\props\cars\legs_boss.mdx;models\props\cars\body_boss.mdx;models\props\cars\head_boss.mdx;models\props\cars\legs_chick.mdx;models\props\cars\body_chick.mdx;models\props\cars\head_chick.mdx"
*/
void car_a_final (edict_t *self)
{
    if (self->s.frame < 85)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
}	
// END JOSEPH

void car_a_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = car_a_final;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_car_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/cars/car.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cars/car.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/cars/legs_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cars/legs_boss.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/cars/body_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cars/body_boss.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/cars/head_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cars/head_boss.mdx", &self->s.model_parts[3]);	

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/cars/legs_chick.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cars/legs_chick.mdx", &self->s.model_parts[4]);	

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/cars/body_chick.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cars/body_chick.mdx", &self->s.model_parts[5]);	

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/cars/head_chick.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cars/head_chick.mdx", &self->s.model_parts[6]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = car_a_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props2_car_topup (0 .5 .8) (-50 -102 -35) (50 102 35)

A car with top up

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\car\car_up.md2"
*/

void SP_props2_car_topup (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/car/car_up.md2";
	self->s.modelindex = gi.modelindex (self->model);

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -102, -50, -35);
		VectorSet (self->maxs, 102, 50, 35);	
	}
	else
	{
		VectorSet (self->mins, -50, -102, -35);
		VectorSet (self->maxs, 50, 102, 35);	
	}		

	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props2_car_topdown (0 .5 .8) (-50 -102 -33) (50 102 33)

A car with top down

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\car\car_td.md2"
*/

void SP_props2_car_topdown (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/car/car_td.md2";
	self->s.modelindex = gi.modelindex (self->model);

	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -102, -50, -33);
		VectorSet (self->maxs, 102, 50, 33);	
	}
	else
	{
		VectorSet (self->mins, -50, -102, -33);
		VectorSet (self->maxs, 50, 102, 33);	
	}	
	
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props2_plant_fern (0 .5 .8) (-50 -46 -40) (50 46 40)

A fern plant

model="models\props\fern\tris.md2"
*/

void SP_props2_plant_fern (edict_t *self)
{
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}
	
	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	self->model = "models/props/fern/tris.md2";
	self->s.modelindex = gi.modelindex (self->model);
	VectorSet (self->mins, -50, -46, -40);
	VectorSet (self->maxs, 50, 46, 40);		

	if (!self->health)
		self->health = 25;

	self->die = metal_die;
	self->takedamage = DAMAGE_YES;

	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

#define PINNUM1  2
#define PINNUM2  4
#define PINNUM3  8

/*QUAKED props2_pinball_machine (0 .5 .8) (-42 -18 -38) (42 18 38) ? PINNUM1 PINNUM2 PINNUM3

A pinball machine  

The bounding box can be rotated in angles of 90 deg and block properly

model="models\props\pinball\pinball_m.mdx;models\props\pinball\glass.mdx;models\props\pinball\ball.mdx"
*/

void pinball_go (edict_t *self)
{
    if (self->s.frame < 44)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->handle)
		{
			self->handle->s.frame++;
		}
	}
	else
	{
		self->s.frame = 0;

		if (self->handle)
		{
			self->handle->s.frame = 0;
		}
	}
}	

void pinball_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = pinball_go;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_pinball_machine (edict_t *self)
{
	int i;
	edict_t *newent = NULL;

    if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 
	if ((self->s.angles[1] == 90) || self->s.angles[1] == 270)
	{
		VectorSet (self->mins, -18, -42, -38);
		VectorSet (self->maxs, 18, 42, 38);	
	}
	else
	{
		VectorSet (self->mins, -42, -18, -38);
		VectorSet (self->maxs, 42, 18, 38);	
	}
	
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;

	if (self->spawnflags & PINNUM3)
	{
		self->s.model_parts[0].modelindex = gi.modelindex("models/props/pin3/pinball_m.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[0].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds( "models/props/pin3/pinball_m.mdx", &self->s.model_parts[0] );
	}
	else if (self->spawnflags & PINNUM2)
	{
		self->s.model_parts[0].modelindex = gi.modelindex("models/props/pin2/pinball_m.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[0].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds( "models/props/pin2/pinball_m.mdx", &self->s.model_parts[0] );
	}
	else 
	{
		self->s.model_parts[0].modelindex = gi.modelindex("models/props/pin1/pinball_m.mdx");
		for (i=0; i<MAX_MODELPART_OBJECTS; i++)
			self->s.model_parts[0].skinnum[i] = self->s.skinnum;
		gi.GetObjectBounds( "models/props/pin1/pinball_m.mdx", &self->s.model_parts[0] );
	}

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/pinball/ball.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/pinball/ball.mdx", &self->s.model_parts[1] );

	newent = G_Spawn();
	
	if (!newent)
		return;

	self->handle = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_BBOX;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = self->skin;
	
	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/pinball/glass.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds( "models/props/pinball/glass.mdx", &newent->s.model_parts[0] );

	newent->s.renderfx2 |= RF2_NOSHADOW;
	newent->s.renderfx2 |= RF2_PASSALPHA;
	newent->s.effects = 128;
	
	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent->surfacetype = SURF_WOOD;
	gi.linkentity (newent);

	self->use = pinball_trigger;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_WOOD;
	gi.linkentity (self);
}

/*QUAKED props2_barrels_PV_A (0 .5 .8) (-90 -32 -48) (90 32 48)

A set of barrels that you can trigger to fall  

model="models\props\pv_barl1\barrel_v4last.mdx;models\props\pv_barl1\barrel_v2.mdx;models\props\pv_barl1\barrel_v4.mdx;models\props\pv_barl1\top_barrel_v2.mdx;models\props\pv_barl1\top_barrel_v4.mdx"
*/

/*QUAKED props2_barrels_PV_B (0 .5 .8) (-17 -77 -49) (17 77 49)

A set of barrels that you can trigger to fall  

model="models\props\pv_barl7\barrel_v2.mdx;models\props\pv_barl7\barrel_v4.mdx;models\props\pv_barl7\top_barrel_v2.mdx;models\props\pv_barl7\top_barrel_v4.mdx"
*/

/*QUAKED props2_barrels_PV_C (0 .5 .8) (-68 -50 -48) (68 50 48)

A set of barrels that you can trigger to fall  

model="models\props\pv_barl3\barrel_v2.mdx;models\props\pv_barl3\barrel_v2.mdx;models\props\pv_barl3\barrel_v4.mdx;models\props\pv_barl3\top_barrel_v2.mdx;models\props\pv_barl3\top_barrel_v4.mdx"
*/

/*QUAKED props2_barrels_PV_D (0 .5 .8) (-20 -52 -48) (20 52 48)

A set of barrels that you can trigger to fall  

model="models\props\pv_barl4\barrel_v2.mdx;models\props\pv_barl4\barrel_v4.mdx;models\props\pv_barl4\top_barrel_v2.mdx;models\props\pv_barl4\top_barrel_v4.mdx"
*/

/*QUAKED props2_barrels_PV_E (0 .5 .8) (-24 -64 -48) (24 64 48)

A set of barrels that you can trigger to fall  

model="models\props\pv_barl5\barrel_v2.mdx;models\props\pv_barl5\barrel_v4.mdx;models\props\pv_barl5\top_barrel_v2.mdx;models\props\pv_barl5\top_barrel_v4.mdx"
*/

/*QUAKED props2_barrels_PV_F (0 .5 .8) (-20 -32 -24) (20 32 24)

A set of barrels that you can trigger to fall  

model="models\props\pv_barl6\barrel_v2.mdx;models\props\pv_barl6\top_barrel_v2.mdx"
*/

void barrels_fallPV (edict_t *self)
{
    if (self->s.frame < 37)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
		else if (self->s.frame == 13)
		{
			if (self->classname)
			{
				if (!(strcmp(self->classname, "props2_barrels_PV_B")))
				{
					self->s.model_parts[1].modelindex = 0;
					self->s.model_parts[3].modelindex = 0;
				}
			}	
		}
		else if (self->s.frame == 16)
		{
			if (self->classname)
			{
				if (!(strcmp(self->classname, "props2_barrels_PV_A")))
				{
					self->s.model_parts[1].modelindex = 0;
					self->s.model_parts[3].modelindex = 0;
				}
			}	
		}
		else if (self->s.frame == 17)
		{
			if (self->classname)
			{
				if (!(strcmp(self->classname, "props2_barrels_PV_D")))
				{
					self->s.model_parts[1].modelindex = 0;
					self->s.model_parts[3].modelindex = 0;
				}
				else if (!(strcmp(self->classname, "props2_barrels_PV_E")))
				{
					self->s.model_parts[1].modelindex = 0;
					self->s.model_parts[3].modelindex = 0;
				}
			}	
		}
		else if (self->s.frame == 37)
		{
			if (self->classname)
			{
				if (!(strcmp(self->classname, "props2_barrels_PV_F")))
				{
					self->s.model_parts[0].modelindex = 0;
					self->s.model_parts[1].modelindex = 0;
				}
			}	
		}
	}
}	

void barrels_fallPV_BlackSheep (edict_t *self)
{
    if (self->s.frame < 47)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
		else if (self->s.frame == (93/4))
		{
			if (self->classname)
			{
				if (!(strcmp(self->classname, "props2_barrels_PV_C")))
				{
					self->s.model_parts[1].modelindex = 0;
					self->s.model_parts[3].modelindex = 0;
				}
			}	
		}
	}
}	

void barrelsfallPV_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = barrels_fallPV;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void barrelsfallPV_trigger_BlackSheep (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = barrels_fallPV_BlackSheep;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_barrels_PV_A (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -90, -32, -48);
	VectorSet (self->maxs, 90, 32, 48);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	
	//self->s.num_parts++;
	//self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl1/barrel_v4last.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	//gi.GetObjectBounds("models/props/pv_barl1/barrel_v4last.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl1/top_barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl1/top_barrel_v4.mdx", &self->s.model_parts[0]);	
	
	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/pv_barl1/barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl1/barrel_v2.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/pv_barl1/barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl1/barrel_v4.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/pv_barl1/top_barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl1/top_barrel_v2.mdx", &self->s.model_parts[3]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallPV_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props2_barrels_PV_B (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -17, -77, -49);
	VectorSet (self->maxs, 17, 77, 49);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	
	//self->s.num_parts++;
	//self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl1/barrel_v4last.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	//gi.GetObjectBounds("models/props/pv_barl1/barrel_v4last.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl7/top_barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl7/top_barrel_v4.mdx", &self->s.model_parts[0]);	
	
	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/pv_barl7/barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl7/barrel_v2.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/pv_barl7/barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl7/barrel_v4.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/pv_barl7/top_barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl7/top_barrel_v2.mdx", &self->s.model_parts[3]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallPV_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props2_barrels_PV_C (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -68, -50, -48);
	VectorSet (self->maxs, 68, 50, 48);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	
	//self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl3/barrel_v4last.mdx");
	//for (i=0; i<MAX_MODELPART_OBJECTS; i++)
	//	self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	//gi.GetObjectBounds("models/props/pv_barl3/barrel_v4last.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl3/top_barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl3/top_barrel_v4.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/pv_barl3/barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl3/barrel_v2.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/pv_barl3/barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl3/barrel_v4.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/pv_barl3/top_barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl3/top_barrel_v2.mdx", &self->s.model_parts[3]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallPV_trigger_BlackSheep;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props2_barrels_PV_D (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -20, -52, -48);
	VectorSet (self->maxs, 20, 52, 48);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl4/top_barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl4/top_barrel_v4.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/pv_barl4/barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl4/barrel_v2.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/pv_barl4/barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl4/barrel_v4.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/pv_barl4/top_barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl4/top_barrel_v2.mdx", &self->s.model_parts[3]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallPV_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props2_barrels_PV_E (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -24, -64, -48);
	VectorSet (self->maxs, 24, 64, 48);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl5/top_barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl5/top_barrel_v4.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/pv_barl5/barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl5/barrel_v2.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/pv_barl5/barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl5/barrel_v4.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/pv_barl5/top_barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl5/top_barrel_v2.mdx", &self->s.model_parts[3]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallPV_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props2_barrels_PV_F (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -20, -32, -24);
	VectorSet (self->maxs, 20, 32, 24);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/pv_barl6/barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl6/barrel_v2.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/pv_barl6/top_barrel_v2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/pv_barl6/top_barrel_v2.mdx", &self->s.model_parts[1]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfallPV_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props2_air_train (0 .5 .8) (-65 -259 -129) (65 255 139)

An an train that animates when trigger  

model="models\props\air_train\beam.mdx;models\props\air_train\frontfront.mdx;models\props\air_train\bottom.mdx;models\props\air_train\frontside.mdx;models\props\air_train\middle.mdx;models\props\air_train\middle2.mdx;models\props\air_train\propeler.mdx;models\props\air_train\top.mdx"

*/

/*QUAKED props2_air_train_test (0 .5 .8) (-66 -257 -135) (66 257 135)

An an train that animates when trigger  

model="models\props\air_train\frontfront.mdx;models\props\air_train\bottom.mdx;models\props\air_train\frontside.mdx;models\props\air_train\middle.mdx;models\props\air_train\middle2.mdx;models\props\air_train\propeler.mdx;models\props\air_train\top.mdx;models\props\air_last\frontfront.mdx;models\props\air_last\bottom.mdx;models\props\air_last\frontside.mdx;models\props\air_last\middle.mdx;models\props\air_last\middle2.mdx;models\props\air_last\propeler.mdx;models\props\air_last\top.mdx"
*/

void air_train_go (edict_t *self)
{
    if (self->s.frame < 153)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}	
	}
}	

void air_train_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = air_train_go;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props2_air_train (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -66, -257, -135);
	VectorSet (self->maxs, 66, 257, 135);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);

	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/air_train/frontfront.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/frontfront.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/air_train/bottom.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/bottom.mdx", &self->s.model_parts[1]);	


	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/air_train/frontside.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/frontside.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/air_train/middle.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/middle.mdx", &self->s.model_parts[3]);	

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/air_train/middle2.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/middle2.mdx", &self->s.model_parts[4]);	

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/air_train/propeler.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/propeler.mdx", &self->s.model_parts[5]);	

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/air_train/top.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/top.mdx", &self->s.model_parts[6]);	

	self->s.num_parts++;
	self->s.model_parts[7].modelindex = gi.modelindex("models/props/air_train/beam.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[7].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/air_train/beam.mdx", &self->s.model_parts[7]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = air_train_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_dead_louie (0 .5 .8) (-40 -48 -14) (40 48 14)

An dead louie body you can shoot

"health" - pre-gib hit points for the dead body (50 default)

model="models\props\louie\body.mdx;models\props\louie\head.mdx;models\props\louie\legs.mdx"
*/

void SP_props3_dead_louie (edict_t *self)
{
	int i;

	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	self->svflags |= SVF_DEADMONSTER;

	VectorSet (self->mins, -40, -48, -14);
	VectorSet (self->maxs, 40, 48, 14);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/louie/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/louie/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/louie/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/louie/body.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/louie/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/louie/legs.mdx", &self->s.model_parts[2]);	

	self->die = body_gib;
	self->takedamage = DAMAGE_YES;

	if (!self->health)
		self->health = 50;
	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;

	self->surfacetype = SURF_FABRIC;

	if (st.item)
	{
		self->item = FindItemByClassname (st.item);
		if (!self->item)
			gi.dprintf("%s at %s has bad item: %s\n", self->classname, vtos(self->s.origin), st.item);
	}	
	
	gi.linkentity (self);
}

/*QUAKED props3_cut_boss_player_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

A boss and player that animate when trigered  

model="models\props\player\bodyP.mdx;models\props\player\legsP.mdx;models\props\player\headP.mdx;models\props\boss\body_boss.mdx;models\props\boss\legs_boss.mdx;models\props\boss\head_boss.mdx"
*/
void cutbossplayer_final (edict_t *self)
{
    if (self->s.frame < 137)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cutbossplayer_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cutbossplayer_final;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props3_cut_boss_player_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/boss/body_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/boss/body_boss.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/boss/head_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/boss/head_boss.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/boss/legs_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/boss/legs_boss.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/player/bodyP.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/player/bodyP.mdx", &self->s.model_parts[3]);	

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/player/headP.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/player/headP.mdx", &self->s.model_parts[4]);	

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/player/legsP.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/player/legsP.mdx", &self->s.model_parts[5]);

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cutbossplayer_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_deco_fixture (0 .5 .8) (-32 -8 -58) (32 8 58)

A deco fixture

model="models\props\deco_fixture\deco_fixture.mdx"
*/

void SP_props3_deco_fixture (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -32, -8, -58);
	VectorSet (self->maxs, 32, 8, 58);	

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/deco_fixture/deco_fixture.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/deco_fixture/deco_fixture.mdx", &self->s.model_parts[0]);	
	
	self->surfacetype = SURF_TILE;
	self->s.renderfx2 |= RF2_NOSHADOW;
	gi.linkentity (self);
}

/*QUAKED props3_cut_boss_chick_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

A boss and chick that animate on a balcony when trigered  

model="models\props\cutbc\body_chick.mdx;models\props\cutbc\legs_chick.mdx;models\props\cutbc\head_chick.mdx;models\props\cutbc\body.mdx;models\props\cutbc\legs.mdx;models\props\cutbc\head.mdx;models\props\cutbc\cigar.mdx"
*/
void cutbosschick_final (edict_t *self)
{
    if (self->s.frame < 210)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cutbosschick_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cutbosschick_final;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props3_cut_boss_chick_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/cutbc/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cutbc/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/cutbc/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cutbc/head.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/cutbc/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cutbc/legs.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/cutbc/body_chick.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cutbc/body_chick.mdx", &self->s.model_parts[3]);	

	self->s.num_parts++;
	self->s.model_parts[4].modelindex = gi.modelindex("models/props/cutbc/head_chick.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[4].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cutbc/head_chick.mdx", &self->s.model_parts[4]);	

	self->s.num_parts++;
	self->s.model_parts[5].modelindex = gi.modelindex("models/props/cutbc/legs_chick.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[5].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cutbc/legs_chick.mdx", &self->s.model_parts[5]);

	self->s.num_parts++;
	self->s.model_parts[6].modelindex = gi.modelindex("models/props/cutbc/cigar.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[6].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cutbc/cigar.mdx", &self->s.model_parts[6]);

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cutbosschick_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_cut_train_run_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

A guy that likes to run to trains  

model="models\props\train_jump\bodyP.mdx;models\props\train_jump\legsP.mdx;models\props\train_jump\headP.mdx;
*/
void cuttrainrun_final (edict_t *self)
{
    if (self->s.frame < 41)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cuttrainrun_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cuttrainrun_final;
	ent->nextthink = level.time + FRAMETIME;
	//gi.sound (ent, CHAN_AUTO, gi.soundindex ("world/brickfall.wav"), 1, ATTN_NORM, 0);
}	

void SP_props3_cut_train_run_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/train_jump/bodyP.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/train_jump/bodyP.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/train_jump/headP.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/train_jump/headP.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/train_jump/legsP.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/train_jump/legsP.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cuttrainrun_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_cut_A_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

A guy sitting on a chair  

model="models\props\kpcut1\body.mdx;models\props\kpcut1\legs.mdx;models\props\kpcut1\head.mdx;
*/

/*QUAKED props3_cut_B_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

model="models\props\kpcut2\body.mdx;models\props\kpcut2\legs.mdx;models\props\kpcut2\head.mdx;
*/

/*QUAKED props3_cut_C_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

model="models\props\kpcut3\body.mdx;models\props\kpcut3\legs.mdx;models\props\kpcut3\head.mdx;
*/

/*QUAKED props3_cut_D_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

model="models\props\kpcut4\body.mdx;models\props\kpcut4\legs.mdx;models\props\kpcut4\head.mdx;
*/

void cutA_A_final (edict_t *self)
{
    if (self->s.frame < 250)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cutB_A_final (edict_t *self)
{
    if (self->s.frame < 514)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cutC_A_final (edict_t *self)
{
    if (self->s.frame < 249)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cutD_A_final (edict_t *self)
{
    if (self->s.frame < 365)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cutA_A_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cutA_A_final;
	ent->nextthink = level.time + FRAMETIME;
}	

void cutB_A_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cutB_A_final;
	ent->nextthink = level.time + FRAMETIME;
}

void cutC_A_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cutC_A_final;
	ent->nextthink = level.time + FRAMETIME;
}

void cutD_A_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cutD_A_final;
	ent->nextthink = level.time + FRAMETIME;
}

void SP_props3_cut_A_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/kpcut1/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut1/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/kpcut1/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut1/head.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/kpcut1/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut1/legs.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cutA_A_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props3_cut_B_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/kpcut2/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut2/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/kpcut2/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut2/head.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/kpcut2/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut2/legs.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cutB_A_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props3_cut_C_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/kpcut3/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut3/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/kpcut3/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut3/head.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/kpcut3/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut3/legs.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cutC_A_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

void SP_props3_cut_D_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/kpcut4/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut4/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/kpcut4/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut4/head.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/kpcut4/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut4/legs.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cutD_A_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_cash_counter_animate (0 .5 .8) (-12 -14 -8) (12 18 7)

A cash counter machine that animates when triggered  

model="models\props\bill_counter\cashstack.mdx;models\props\bill_counter\numbers.mdx;models\props\bill_counter\machine.mdx;
*/
void cashcounter_final (edict_t *self)
{
    if (self->s.frame < 39)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;
	}
}	

void cashcounter_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cashcounter_final;
	ent->nextthink = level.time + FRAMETIME;
	ent->s.frame = 0;
}	

void SP_props3_cash_counter_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -14, -12, -8);
	VectorSet (self->maxs, 18, 12, 7);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/bill_counter/cashstack.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/bill_counter/cashstack.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/bill_counter/machine.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/bill_counter/machine.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/bill_counter/numbers.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/bill_counter/numbers.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cashcounter_trigger;

	gi.linkentity (self);
}

/*QUAKED props3_decanter (0 .5 .8) (-3 -5 -6) (3 5 6)

A decanter  

model="models\props\decanter\solid.mdx;models\props\decanter\glass.mdx"
*/

void SP_props3_decanter (edict_t *self)
{
	int i;
	edict_t *newent = NULL;

    if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 
	VectorSet (self->mins, -3, -5, -6);
	VectorSet (self->maxs, 3, 5, 6);	
	
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/decanter/solid.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/decanter/solid.mdx", &self->s.model_parts[0] );
 
	newent = G_Spawn();
	
	if (!newent)
		return;

	//self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_NOT;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = self->skin;
	
	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/decanter/glass.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds( "models/props/decanter/glass.mdx", &newent->s.model_parts[0] );

	newent->s.renderfx2 |= RF2_NOSHADOW;
	newent->s.renderfx2 |= RF2_PASSALPHA;
	newent->s.effects = 100;
	
	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent->surfacetype = SURF_METAL;
	gi.linkentity (newent);

	//self->s.renderfx2 |= RF2_PASSALPHA;
	//self->s.effects = 32;
	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props3_whiskey_glass (0 .5 .8) (-2 -2 -2) (2 2 2)

A decanter  

model="models\props\whiskeyglass\solid.mdx;models\props\whiskeyglass\glass.mdx"
*/

void SP_props3_whiskey_glass (edict_t *self)
{
	int i;
	edict_t *newent = NULL;

    if (deathmatch->value)
	{ // auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	self->s.skinnum = self->skin;
 
	VectorSet (self->mins, -2, -2, -2);
	VectorSet (self->maxs, 2, 2, 2);	
	
	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/whiskeyglass/solid.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds( "models/props/whiskeyglass/solid.mdx", &self->s.model_parts[0] );
 
	newent = G_Spawn();
	
	if (!newent)
		return;

	//self->handle2 = newent;

	VectorCopy(self->s.origin, newent->s.origin);
	VectorCopy(self->s.angles, newent->s.angles);

	newent->solid = SOLID_NOT;
	newent->movetype = MOVETYPE_NONE;
	newent->svflags |= SVF_PROP;

	newent->s.skinnum = self->skin;
	
	memset(&(newent->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	newent->s.num_parts++;
	newent->s.model_parts[0].modelindex = gi.modelindex("models/props/whiskeyglass/glass.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		newent->s.model_parts[0].skinnum[i] = newent->s.skinnum;
	gi.GetObjectBounds( "models/props/whiskeyglass/glass.mdx", &newent->s.model_parts[0] );

	newent->s.renderfx2 |= RF2_NOSHADOW;
	newent->s.renderfx2 |= RF2_PASSALPHA;
	newent->s.effects = 128;
	
	newent->s.renderfx2 |= RF2_DIR_LIGHTS;
	newent->surfacetype = SURF_METAL;
	gi.linkentity (newent);

	//self->s.renderfx2 |= RF2_PASSALPHA;
	//self->s.effects = 32;	
	self->s.renderfx2 |= RF2_NOSHADOW;
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_METAL;
	gi.linkentity (self);
}

/*QUAKED props3_barrels_fall_nikki_A (0 .5 .8) (-44 -60 -49) (44 60 49)

A set of barrels that you can trigger to fall  

model="models\props\nikki1\barrel_v4.mdx;models\props\nikki1\top_barrel_v4.mdx"
*/
void barrels_fall_nikki_A (edict_t *self)
{
    if (self->s.frame < 85)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}	
	}
}	

void barrelsfall_nikkiA_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = barrels_fall_nikki_A;
	ent->nextthink = level.time + FRAMETIME;
}	

void SP_props3_barrels_fall_nikki_A (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -44, -60, -49);
	VectorSet (self->maxs, 44, 60, 49);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/nikki1/barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/nikki1/barrel_v4.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/nikki1/top_barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/nikki1/top_barrel_v4.mdx", &self->s.model_parts[1]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfall_nikkiA_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_barrels_fall_nikki_B (0 .5 .8) (-24 -48 -24) (24 48 24)

A set of barrels that you can trigger to fall  

model="models\props\nikki2\barrel_v4.mdx;models\props\nikki2\top_barrel_v4.mdx"
*/
void barrels_fall_nikki_B (edict_t *self)
{
    if (self->s.frame < 90)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}	
	}
}	

void barrelsfall_nikkiB_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = barrels_fall_nikki_B;
	ent->nextthink = level.time + FRAMETIME;
}	

void SP_props3_barrels_fall_nikki_B (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;
	
	VectorSet (self->mins, -24, -48, -24);
	VectorSet (self->maxs, 24, 48, 24);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/nikki2/barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/nikki2/barrel_v4.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/nikki2/top_barrel_v4.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/nikki2/top_barrel_v4.mdx", &self->s.model_parts[1]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = barrelsfall_nikkiB_trigger;
	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_cut_run_to_car_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

An actor running to a car  

model="models\props\run_to_car\body_boss.mdx;models\props\run_to_car\legs_boss.mdx;models\props\run_to_car\head_boss.mdx"
*/

void cut_carrun_final (edict_t *self)
{
    if (self->s.frame < 44)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cut_carrun_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cut_carrun_final;
	ent->nextthink = level.time + FRAMETIME;
}	

void SP_props3_cut_run_to_car_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/run_to_car/body_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/run_to_car/body_boss.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/run_to_car/head_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/run_to_car/head_boss.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/run_to_car/legs_boss.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/run_to_car/legs_boss.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cut_carrun_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_cut_final_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

The final cut scene

model="models\props\finale\body_bossf.mdx;models\props\finale\legs_bossf.mdx;models\props\finale\head_bossf.mdx;models\props\finale\cigarf.mdx"
*/

void cut_final_final (edict_t *self)
{
    if (self->s.frame < 245)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cut_final_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cut_final_final;
	ent->nextthink = level.time + FRAMETIME;
}	

void SP_props3_cut_final_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/finale/body_bossf.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/finale/body_bossf.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/finale/head_bossf.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/finale/head_bossf.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/finale/legs_bossf.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/finale/legs_bossf.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/finale/cigarf.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/finale/cigarf.mdx", &self->s.model_parts[3]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cut_final_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_cash (0 .5 .8) (-12 -11 -5) (12 11 5)

Some cash

model="models\props\cash\cashstack.mdx"
*/

void SP_props3_cash (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_BBOX;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -12, -11, -5);
	VectorSet (self->maxs, 12, 11, 5);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[PART_HEAD].modelindex = gi.modelindex("models/props/cash/cashstack.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[PART_HEAD].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/cash/cashstack.mdx", &self->s.model_parts[PART_HEAD]);	
	
	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->surfacetype = SURF_FABRIC;
	gi.linkentity (self);
}

/*QUAKED props3_cut_truck_driver (0 .5 .8) (-67 -16 -58) (0 17 8)

The driver driving a truck

model="models\props\driver\body_driver.mdx;models\props\driver\legs_driver.mdx;models\props\driver\head_driver.mdx;models\props\driver\wheel.mdx"
*/

void cut_truckdriver_final (edict_t *self)
{
    if (self->s.frame < 20)
	{
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		self->s.frame = 0;
	}

	self->nextthink = level.time + 0.1;
}	

void cut_truckdriver_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cut_truckdriver_final;
	ent->nextthink = level.time + FRAMETIME;
}	

void SP_props3_cut_truck_driver (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -67, -16, -58);
	VectorSet (self->maxs, 0, 17, 8);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/driver/body_driver.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/driver/body_driver.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/driver/head_driver.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/driver/head_driver.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/driver/legs_driver.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/driver/legs_driver.mdx", &self->s.model_parts[2]);	

	self->s.num_parts++;
	self->s.model_parts[3].modelindex = gi.modelindex("models/props/driver/wheel.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[3].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/driver/wheel.mdx", &self->s.model_parts[3]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cut_truckdriver_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}

/*QUAKED props3_cut_pinball_guy_animate (0 .5 .8) (-16 -16 -16) (16 16 16)

A cut scene of a guy and his pinball machine

model="models\props\kpcut4_pinball\body.mdx;models\props\kpcut4_pinball\legs.mdx;models\props\kpcut4_pinball\head.mdx"
*/

void cut_pinballguy_final (edict_t *self)
{
    if (self->s.frame < 365)
	{
		self->nextthink = level.time + 0.1;
		
		self->s.frame++;

		if (self->s.frame == 1)
		{
			self->svflags &= ~SVF_NOCLIENT;
		}
	}
	else
	{
		G_FreeEdict (self);
	}
}	

void cut_pinballguy_trigger (edict_t *ent, edict_t *other, edict_t *activator)
{
	ent->think = cut_pinballguy_final;
	ent->nextthink = level.time + FRAMETIME;
}	

void SP_props3_cut_pinball_guy_animate (edict_t *self)
{
	int i;
	
	if (deathmatch->value)
	{	// auto-remove for deathmatch
		G_FreeEdict (self);
		return;
	}

	self->solid = SOLID_NOT;
	self->movetype = MOVETYPE_NONE;
	self->svflags |= SVF_PROP;

	VectorSet (self->mins, -16, -16, -16);
	VectorSet (self->maxs, 16, 16, 16);		

	self->s.skinnum = self->skin;
 	memset(&(self->s.model_parts[0]), 0, sizeof(model_part_t) * MAX_MODEL_PARTS);
	self->s.num_parts++;
	self->s.model_parts[0].modelindex = gi.modelindex("models/props/kpcut4_pinball/body.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[0].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut4_pinball/body.mdx", &self->s.model_parts[0]);	

	self->s.num_parts++;
	self->s.model_parts[1].modelindex = gi.modelindex("models/props/kpcut4_pinball/head.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[1].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut4_pinball/head.mdx", &self->s.model_parts[1]);	

	self->s.num_parts++;
	self->s.model_parts[2].modelindex = gi.modelindex("models/props/kpcut4_pinball/legs.mdx");
	for (i=0; i<MAX_MODELPART_OBJECTS; i++)
		self->s.model_parts[2].skinnum[i] = self->s.skinnum;
	gi.GetObjectBounds("models/props/kpcut4_pinball/legs.mdx", &self->s.model_parts[2]);	

	self->s.renderfx2 |= RF2_DIR_LIGHTS;
	self->s.renderfx2 |= RF2_NOSHADOW;

	self->use = cut_pinballguy_trigger;

	self->svflags |= SVF_NOCLIENT;

	gi.linkentity (self);
}
