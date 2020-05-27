#if 0

/*
	fog.c
*/

/*QUAKED fog_brush (.5 .5 0) ?
  "angles" points into the fog brush
*/
#include "g_local.h"

void fog_brush_touch (edict_t *self, edict_t *other, cplane_t *plane, csurface_t *surf)
{
	vec3_t	vec;
	vec3_t	vars1, vars2;

	if (!(other->client))
		return;

	VectorSubtract( other->s.origin, self->pos1, vec );
	vec[2] = 0;
	VectorNormalize( vec );

	if (DotProduct( vec, self->movedir ) > 0)
	{	
		gi.dprintf ("going into fog brush\n");
		
		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_FOG_BRUSH);

		gi.WritePosition (vars1);
		gi.WritePosition (vars2);
		
		gi.multicast (other->s.origin, MULTICAST_PVS);
	}
	else 	
	{
		gi.dprintf ("going out of fog brush\n");

		gi.WriteByte (svc_temp_entity);
		gi.WriteByte (TE_FOG_BRUSH);

		gi.WritePosition (vars1);
		gi.WritePosition (vars2);
		
		gi.multicast (other->s.origin, MULTICAST_PVS);
	}

}


void SP_fog_brush (edict_t *ent)
{
	if (deathmatch->value)
	{
		G_FreeEdict(ent);
		return;
	}

	ent->solid = SOLID_TRIGGER;
	ent->touch = fog_brush_touch;

	ent->svflags |= SVF_NOCLIENT;

 	gi.setmodel (ent, ent->model);
	gi.linkentity (ent);

	// set the center pos
	VectorAdd( ent->absmin, ent->absmax, ent->pos1 );
	VectorScale( ent->pos1, 0.5, ent->pos1 );

	AngleVectors( ent->s.angles, ent->movedir, NULL, NULL );
}


#endif