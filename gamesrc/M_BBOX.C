#include "g_local.h"

//
// M_BBOX.C
//
#define		MAX_MDX_BBOX_ENTITIES	32	// theoretically, this should be MAX_MODEL_PARTS * MAX_MODELPART_OBJECTS
										// but that would be too many, so we have to compromise

edict_t		*mdx_bbox[MAX_MDX_BBOX_ENTITIES];

void MDX_Bbox_Init (void)
{
	int		i;

	for (i = 0; i < (MAX_MDX_BBOX_ENTITIES); i++)
	{
		mdx_bbox[i] = G_Spawn();
		mdx_bbox[i]->classname = "mdx_bbox";
		mdx_bbox[i]->s.modelindex = 0;
		mdx_bbox[i]->takedamage = DAMAGE_NO;	// don't take damage from explosions, we'll do all damage testing manually
		
//		mdx_bbox[i]->svflags |= SVF_MONSTER;
		
		mdx_bbox[i]->solid |= SOLID_BBOX;
		
		mdx_bbox[i]->flags |= FL_MDXBBOX;

	}

}

int			bbox_cnt;

trace_t MDX_HitCheck (edict_t *targ, edict_t *inflictor, edict_t *attacker, vec3_t dir, vec3_t point, vec3_t normal, int damage, int knockback, int dflags, int mod, vec3_t end)
{
	trace_t		tr;
	vec3_t		forward, right, up;
	int			sub_object;
	int			i;
	vec3_t		rmins, rmaxs;	// rotated mins/maxs positions
	vec3_t		pmins, pmaxs;	// perpendicular with world axis
	vec3_t		org;

	bbox_cnt = 0;

	AngleVectors (mdx_bbox[bbox_cnt]->s.angles, forward, right, up);
	VectorCopy (targ->s.origin, org);

	if (targ->cast_info.scale != 1.0)
	{
		VectorScale( forward, targ->cast_info.scale, forward );
		VectorScale( right, targ->cast_info.scale, right );
		VectorScale( up, targ->cast_info.scale, up );

		org[2] -= 24 * (1.0 - targ->cast_info.scale);
	}

	for (i=0; i<MAX_MODEL_PARTS; i++)
	{
		sub_object = 0;
	
		// Ridah, can't shoot the gun, so ignore it, or it'll prevent us from shooting the arm holding it
		if (i == PART_GUN)
			continue;

		while (targ->s.model_parts[i].modelindex)
		{
			
			if (!targ->s.model_parts[i].object_bounds[sub_object])
				break;

			// Ridah, only check visible sub-objects
			if (!(targ->s.model_parts[i].invisible_objects & (1<<sub_object)))
			{

				VectorCopy (org, mdx_bbox[bbox_cnt]->s.origin);
				VectorCopy (targ->s.angles, mdx_bbox[bbox_cnt]->s.angles);
				
				VectorCopy (g_objbnds[-1+targ->s.model_parts[i].object_bounds[sub_object]][targ->s.frame].mins, mdx_bbox[bbox_cnt]->mins);
				VectorCopy (g_objbnds[-1+targ->s.model_parts[i].object_bounds[sub_object]][targ->s.frame].maxs, mdx_bbox[bbox_cnt]->maxs);

				if (targ->cast_info.scale != 1.0)
				{
					VectorScale( mdx_bbox[bbox_cnt]->mins, targ->cast_info.scale, mdx_bbox[bbox_cnt]->mins );
					VectorScale( mdx_bbox[bbox_cnt]->maxs, targ->cast_info.scale, mdx_bbox[bbox_cnt]->maxs );
				}

				VectorMA (mdx_bbox[bbox_cnt]->s.origin, ((mdx_bbox[bbox_cnt]->mins[0] + mdx_bbox[bbox_cnt]->maxs[0]) * 0.5), forward, mdx_bbox[bbox_cnt]->s.origin);
				VectorMA (mdx_bbox[bbox_cnt]->s.origin, -((mdx_bbox[bbox_cnt]->mins[1] + mdx_bbox[bbox_cnt]->maxs[1]) * 0.5), right, mdx_bbox[bbox_cnt]->s.origin);
				VectorMA (mdx_bbox[bbox_cnt]->s.origin, (mdx_bbox[bbox_cnt]->mins[2] + mdx_bbox[bbox_cnt]->maxs[2]) * 0.5, up, mdx_bbox[bbox_cnt]->s.origin);

				// find rotated positions of mins/maxs, and then build the new min/max
				VectorScale ( forward, mdx_bbox[bbox_cnt]->mins[0], rmins);
				VectorMA (rmins, -mdx_bbox[bbox_cnt]->mins[1], right, rmins);
				VectorMA (rmins, mdx_bbox[bbox_cnt]->mins[2], up, rmins);

				VectorScale ( forward, mdx_bbox[bbox_cnt]->maxs[0], rmaxs);
				VectorMA (rmaxs, -mdx_bbox[bbox_cnt]->maxs[1], right, rmaxs);
				VectorMA (rmaxs, mdx_bbox[bbox_cnt]->maxs[2], up, rmaxs);

				pmins[0] = (rmins[0] < rmaxs[0] ? rmins[0] : rmaxs[0]);
				pmins[1] = (rmins[1] < rmaxs[1] ? rmins[1] : rmaxs[1]);
				pmins[2] = (rmins[2] < rmaxs[2] ? rmins[2] : rmaxs[2]);

				pmaxs[0] = (rmins[0] > rmaxs[0] ? rmins[0] : rmaxs[0]);
				pmaxs[1] = (rmins[1] > rmaxs[1] ? rmins[1] : rmaxs[1]);
				pmaxs[2] = (rmins[2] > rmaxs[2] ? rmins[2] : rmaxs[2]);

				// now align the mins/maxs with the origin
				mdx_bbox[bbox_cnt]->mins[0] = pmins[0] - (0.5*(pmaxs[0] + pmins[0]));
				mdx_bbox[bbox_cnt]->mins[1] = pmins[1] - (0.5*(pmaxs[1] + pmins[1]));
				mdx_bbox[bbox_cnt]->mins[2] = pmins[2] - (0.5*(pmaxs[2] + pmins[2]));
				mdx_bbox[bbox_cnt]->maxs[0] = pmaxs[0] - (0.5*(pmaxs[0] + pmins[0]));
				mdx_bbox[bbox_cnt]->maxs[1] = pmaxs[1] - (0.5*(pmaxs[1] + pmins[1]));
				mdx_bbox[bbox_cnt]->maxs[2] = pmaxs[2] - (0.5*(pmaxs[2] + pmins[2]));

				mdx_bbox[bbox_cnt]->count = i;			// record model part
				mdx_bbox[bbox_cnt]->dmg = sub_object;	// record sub_object

				if (damage > 0)
				{
					mdx_bbox[bbox_cnt]->solid = SOLID_BBOX;
					gi.linkentity (mdx_bbox[bbox_cnt]);
				}

				bbox_cnt++;
			}

			sub_object++;

			if (bbox_cnt > (MAX_MDX_BBOX_ENTITIES))
			{
				gi.error ("MDX_HitCheck: too many bbox parts: %d\n", bbox_cnt);
			}

			if (sub_object == MAX_MODELPART_OBJECTS)
				break;
		}
	}

	if (damage > 0)
	{
		tr = gi.trace (point, NULL, NULL, end, targ, MASK_SHOT );
		MDX_Cleanup();
	}
	else
	{
		memset( &tr, 0, sizeof(trace_t));
	}
	
/*
	// just to see where the hit occured
	{
		edict_t *e;
		e = G_Spawn();
		e->s.modelindex = 98; 
		gi.linkentity(e);
		VectorCopy (tr.endpos, e->s.origin);
		e->think = G_FreeEdict;
		e->nextthink = level.time + 1.0;

		// Ridah, debugging, change the skin on this sub-object
		if (tr.fraction < 1 && tr.ent->flags & FL_MDXBBOX)
			if (++targ->s.model_parts[tr.ent->count].skinnum[tr.ent->dmg] > 4)
				targ->s.model_parts[tr.ent->count].skinnum[tr.ent->dmg] = 0;

	}
*/
	
	return tr;

}

void MDX_Cleanup (void)
{
	int		i;
	
	for (i = 0; i < (MAX_MDX_BBOX_ENTITIES); i++)
	{
		if (mdx_bbox[i]->solid)
		{
			gi.unlinkentity (mdx_bbox[i]);
			mdx_bbox[i]->solid = 0;
		}
	}
}
