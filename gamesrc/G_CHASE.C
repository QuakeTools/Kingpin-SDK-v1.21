#include "g_local.h"

extern void DeathmatchScoreboard (edict_t *ent);

void UpdateChaseCam(edict_t *ent)
{
	static vec3_t	mins = {-10, -10, -10}, maxs = {10, 10, 10};
	vec3_t o, ownerv, goal;
	edict_t *targ;
	vec3_t forward, right, up;
	trace_t trace;
	int i;
	vec3_t oldgoal;
	vec3_t angles;

	// is our chase target gone?
	if (!ent->client->chase_target->inuse) {
		ent->client->chase_target = NULL;
		return;
	}

	targ = ent->client->chase_target;

	VectorCopy(targ->s.origin, ownerv);
	VectorCopy(ent->s.origin, oldgoal);

	ownerv[2] += targ->viewheight;

	VectorCopy(targ->client->v_angle, angles);
	if (angles[PITCH] > 56)
		angles[PITCH] = 56;
	AngleVectors (angles, forward, right, up);
	VectorNormalize(forward);
	VectorMA(ownerv, -64, forward, o);
	VectorMA(o, 24, up, o);

	if (o[2] < targ->s.origin[2] + 20)
		o[2] = targ->s.origin[2] + 20;

	// jump animation lifts
	if (!targ->groundentity)
		o[2] += 16;

	trace = gi.trace(ownerv, mins, maxs, o, targ, MASK_SOLID);

	VectorCopy(trace.endpos, goal);
/*
	VectorMA(goal, 2, forward, goal);

	// pad for floors and ceilings
	VectorCopy(goal, o);
	o[2] += 6;
	trace = gi.trace(goal, vec3_origin, vec3_origin, o, targ, MASK_SOLID);
	if (trace.fraction < 1) {
		VectorCopy(trace.endpos, goal);
		goal[2] -= 6;
	}

	VectorCopy(goal, o);
	o[2] -= 6;
	trace = gi.trace(goal, vec3_origin, vec3_origin, o, targ, MASK_SOLID);
	if (trace.fraction < 1) {
		VectorCopy(trace.endpos, goal);
		goal[2] += 6;
	}
*/
	ent->client->ps.pmove.pm_type = PM_FREEZE;

	VectorCopy(goal, ent->s.origin);
	for (i=0 ; i<3 ; i++)
		ent->client->ps.pmove.delta_angles[i] = ANGLE2SHORT(targ->client->v_angle[i] - ent->client->resp.cmd_angles[i]);

	VectorCopy(targ->client->v_angle, ent->client->ps.viewangles);
	VectorCopy(targ->client->v_angle, ent->client->v_angle);

	// Ridah, angle down a bit since we moved it up
	ent->client->v_angle[2] += 35;
	
	ent->viewheight = 0;
	ent->client->ps.pmove.pm_flags |= PMF_NO_PREDICTION;
	gi.linkentity(ent);
}

void ChaseNext(edict_t *ent)
{
	int i;
	edict_t *e;

	if (!ent->client->chase_target)
	{
		// select the first entity, then go from there
		ent->client->chase_target = &g_edicts[1];
	}

	i = ent->client->chase_target - g_edicts;
	do {
		i++;
		if (i > maxclients->value)
			i = 1;
		e = g_edicts + i;
		if (!e->inuse)
			continue;
		if (e->solid != SOLID_NOT)
			break;
	} while (e != ent->client->chase_target);

	if (e == ent)
	{
		ent->client->chase_target = NULL;
		return;
	}

	ent->client->chase_target = e;
	ent->client->update_chase = true;
	
	DeathmatchScoreboard(ent);
}

void ChasePrev(edict_t *ent)
{
	int i;
	edict_t *e;

	if (!ent->client->chase_target)
	{
		// select the first entity, then go from there
		ent->client->chase_target = &g_edicts[1];
	}

	i = ent->client->chase_target - g_edicts;
	do {
		i--;
		if (i < 1)
			i = maxclients->value;
		e = g_edicts + i;
		if (!e->inuse)
			continue;
		if (e->solid != SOLID_NOT)
			break;
	} while (e != ent->client->chase_target);

	if (e == ent)
	{
		ent->client->chase_target = NULL;
		return;
	}

	ent->client->chase_target = e;
	ent->client->update_chase = true;
	
	DeathmatchScoreboard(ent);
}
