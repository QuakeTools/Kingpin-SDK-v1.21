
//==============================================================
// g_ai_memory.c
//
// Character memory related AI routines
//==============================================================

#include "g_local.h"

#include "voice_punk.h"
#include "voice_bitch.h"

//============================================================================

/*
=================
AddCharacterToGame

  Called whenever a character enters the game (whether AI or client)

  returns FALSE if the character is not allowed to enter the game
=================
*/
qboolean AddCharacterToGame(edict_t *self)
{
	int i;


	if (level.num_characters == MAX_CHARACTERS)
	{
		gi.dprintf("\nMAX_CHARACTERS exceeded, new character rejected.\n\n");
		return false;
	}

	// client is always first
	if ((level.characters[0] != &g_edicts[1]) || self->client)
	{
		level.characters[0] = &g_edicts[1];
		g_edicts[1].character_index = 0;

		if (self->client)
			return true;
	}

	// look for them already in the list
	for (i=0; i<level.num_characters; i++)
	{
		if (level.characters[i] == self)
		{
			self->character_index = i;
			return true;
		}
	}

	if (level.num_characters < 1)
		level.num_characters = 1;

	// add them to the list
	self->character_index = level.num_characters++;
	level.characters[self->character_index] = self;

	return true;
}

/*
==============
AI_RelaseCastMemory

  Release all memory associated to this memory block
==============
*/
void AI_ReleaseCastMemory(edict_t *self, cast_memory_t *cast_memory)
{
	cast_memory_t *next_memory, *this_memory;

	this_memory = cast_memory;

	while (this_memory)
	{
		next_memory = this_memory->next;

		level.global_cast_memory[self->character_index][g_edicts[cast_memory->cast_ent].character_index] = NULL;
		memset( this_memory, 0, sizeof(cast_memory_t) );

		this_memory = next_memory;
	}
}

/*
==============
AI_InitMemory
==============
*/
void AI_InitMemory( edict_t *self )
{
	self->cast_info.friend_memory = NULL;
	self->cast_info.enemy_memory = NULL;
	self->cast_info.neutral_memory = NULL;
}

/*
==============
AI_UnloadCastMemory

  Clears all memory associated with the cast member
==============
*/
void AI_UnloadCastMemory (edict_t *self)
{
	int i;
	edict_t	*trav;
	cast_memory_t	*other_memory;

	if (deathmatch->value)
		return;
	if (!(self->svflags & SVF_MONSTER || self->client))	// <- Note to Rafael: the lack of this line was causing memory problems (hopefully all of them..)
		return;

	// delete all our memories
	AI_ReleaseCastMemory( self, self->cast_info.friend_memory );
	self->cast_info.friend_memory = NULL;
	AI_ReleaseCastMemory( self, self->cast_info.neutral_memory );
	self->cast_info.neutral_memory = NULL;
	AI_ReleaseCastMemory( self, self->cast_info.enemy_memory );
	self->cast_info.enemy_memory = NULL;

	// initialize the global memory list, and delete all other memories of us
	for ( i=0; i<level.num_characters; i++ )
	{
		if (!level.characters[i])
			continue;

		level.global_cast_memory[self->character_index][i] = NULL;	// since this doesn't exist anymore..

		// unload this other character's memory of us

		trav = level.characters[i];

		if (trav->client)
			continue;

		if (!(other_memory = level.global_cast_memory[i][self->character_index]))
			continue;

		AI_RemoveFromMemory ( trav, other_memory );

		level.global_cast_memory[i][self->character_index] = NULL;
	}
}

/*
===========
AI_RemoveFromMemory
===========
*/
void AI_RemoveFromMemory ( edict_t *self, cast_memory_t *memory )
{
	if (memory->prev)
		memory->prev->next = memory->next;

	if (memory->next)
		memory->next->prev = memory->prev;

	if (self->cast_info.friend_memory == memory)
		self->cast_info.friend_memory = memory->next;
	else if (self->cast_info.neutral_memory == memory)
		self->cast_info.neutral_memory = memory->next;
	else if (self->cast_info.enemy_memory == memory)
		self->cast_info.enemy_memory = memory->next;

}

/*
===========
AI_AddToMemory
===========
*/
void AI_AddToMemory ( edict_t *self, cast_memory_t *memory, int memory_type )
{
	cast_memory_t **head=NULL;

	switch (memory_type)
	{
	case MEMORY_TYPE_FRIEND :
		head = &self->cast_info.friend_memory;
		break;
	case MEMORY_TYPE_NEUTRAL :
		head = &self->cast_info.neutral_memory;
		break;
	case MEMORY_TYPE_ENEMY :
		head = &self->cast_info.enemy_memory;
		break;
	}

	if (*head)
	{
		(*head)->prev = memory;
		memory->next = *head;
	}
	else
	{
		memory->next = NULL;
	}

	*head = memory;
	memory->prev = NULL;

	memory->memory_type = memory_type;
	memory->timestamp = level.time;
}

/*
===========
AI_CreateCharacterMemory

  Creates a Character Memory association between 2 characters
===========
*/
void AI_CreateCharacterMemory(edict_t *src, edict_t *dest)
{
	cast_memory_t *new_memory, **head;
	int			memory_type = MEMORY_TYPE_NEUTRAL;	// default to neutral

	if (ai_debug_memory->value)
	{
		gi.dprintf("ai_debug_memory: #%i sighted #%i", src->character_index, dest->character_index);
	}

	head = &src->cast_info.neutral_memory;

	// first, create the cast_memory structure
//	new_memory = gi.TagMalloc(sizeof(cast_memory_t), TAG_LEVEL);
	new_memory = &(g_cast_memory[src->character_index * MAX_CHARACTERS + dest->character_index]);
	memset( new_memory, 0, sizeof(cast_memory_t));

	// set variables
	new_memory->cast_ent = (int) (dest - g_edicts);
	new_memory->flags = 0;
	new_memory->timestamp = -1;

	// determine relationship between us and this character

	if (dest->cast_group)
	{
		if (dest->cast_group == src->cast_group)
		{	// we're in the same group, so we're mates
			memory_type = MEMORY_TYPE_FRIEND;
			head = &src->cast_info.friend_memory;

			if (ai_debug_memory->value)
				gi.dprintf(" - FRIEND");
		}
		else if (src->cast_group)
		{	// rival groups

			// FIXME: check for inter-group relationships? (some groups may have an agreement?)

			memory_type = MEMORY_TYPE_ENEMY;
			head = &src->cast_info.enemy_memory;

			if (ai_debug_memory->value)
				gi.dprintf(" - ENEMY");
		}
	}

	if (ai_debug_memory->value)
		gi.dprintf("\n");

	// never start off as enemies, for now

	// place this memory chunk into the SRC's memory

	if (!(*head))
	{
		*head = new_memory;
	}
	else	 // add to the start of the current list
	{
		(*head)->prev = new_memory;
		new_memory->next = *head;

		*head = new_memory;
	}

	new_memory->memory_type = memory_type;
	new_memory->prev = NULL;

	// set the global memory
	level.global_cast_memory[src->character_index][dest->character_index] = new_memory;
}

/*
===========
AI_CreateCopyMemory

  creates a memory slot, and copies the given memory information into it
===========
*/
cast_memory_t *AI_CreateCopyMemory ( edict_t *src, edict_t *dest, cast_memory_t *cast_memory )
{
	cast_memory_t *new_memory;

	// first, create the cast_memory structure
//	new_memory = gi.TagMalloc(sizeof(cast_memory_t), TAG_LEVEL);
	new_memory = &(g_cast_memory[src->character_index * MAX_CHARACTERS + dest->character_index]);

	// copy the information across
	memcpy( new_memory, cast_memory, sizeof(cast_memory_t) );

	new_memory->prev = new_memory->next = NULL;
	new_memory->cast_ent = (int) (dest - g_edicts);

	return new_memory;
}

/*
===========
AI_ShareEnemies

  spreads our list of enemies with other
===========
*/
void AI_ShareEnemies ( edict_t *self, edict_t *other )
{
	cast_memory_t	*self_memory, *other_memory;

	// Ridah, 18-may-99, cast_group 1 guys shouldn't help other group 1's if they haven't been hired yet
	if ((other->cast_group == 1) && !other->leader)
		return;
	if ((self->cast_group == 1) && !self->leader)
		return;

	// see if any of self's enemies aren't an enemy of other

	self_memory = self->cast_info.enemy_memory;

	while (self_memory)
	{
		// is this character an enemy to other?
		if (	(self_memory->cast_ent != (int) (other - g_edicts))
			&&	!(self_memory->flags & MEMORY_PERSONAL_OPINION))
		{
			if	(	!(other_memory = level.global_cast_memory[other->character_index][g_edicts[self_memory->cast_ent].character_index])
				 ||	(other_memory->memory_type != MEMORY_TYPE_ENEMY))
			{
				if (!other_memory)
				{	// create the memory of them
					other_memory = AI_CreateCopyMemory( other, &g_edicts[self_memory->cast_ent], self_memory);
					level.global_cast_memory[other->character_index][g_edicts[self_memory->cast_ent].character_index] = other_memory;
				}
				else	// remove them from whereever they are
				{
					AI_RemoveFromMemory(other, other_memory);
				}

				// make an enemy
				AI_AddToMemory(other, other_memory, MEMORY_TYPE_ENEMY);

				if (ai_debug_memory->value)
				{
					gi.dprintf("ai_debug_memory: #%i is now an enemy of #%i (copied from #%i)\n", 
									g_edicts[self_memory->cast_ent].character_index, other->character_index, self->character_index);
				}

			}

			// make sure we share any flags necessary
			other_memory->flags |= (self_memory->flags & MEMORY_HOSTILE_ENEMY);
		}

		self_memory = self_memory->next;
	}
}


// JOSEPH 28-DEC-98
void AI_Think_MakeEnemy_Timer (edict_t *ent)
{
	cast_memory_t *cast_memory;
    
	ent->reactdelay -= 0.1;
	
	if (ent->reactdelay <= 0)
	{	
		if ((ent->handle) && (ent->handle2) && (!ent->handle->deadflag) && (!ent->handle2->deadflag))
		{
	        if ((!(cast_memory = level.global_cast_memory[ent->handle->character_index][ent->handle2->character_index])) ||
			   (!(cast_memory->flags & MEMORY_HOSTILE_ENEMY)))
			{
			   AI_MakeEnemy(ent->handle, ent->handle2, ent->avelflag);
			}
		}

		ent->nextthink = 0;
		G_FreeEdict(ent);
	}
	else
	{
		ent->nextthink = level.time + 0.1;
	}
}

void AI_MakeEnemy_Timer (edict_t *self, edict_t *other, int flags, float delay)
{
	edict_t	*timer;

	timer = G_Spawn();
	
	timer->think = AI_Think_MakeEnemy_Timer;
	timer->nextthink = level.time + 0.1;
	timer->reactdelay = delay;
	timer->handle = self;
	timer->handle2 = other;
	timer->avelflag = flags;
	gi.linkentity (timer);

	return;
}
// END JOSEPH

/*
===========
AI_MakeEnemy

  other becomes an enemy of self, and we get hostile at them

  memory_flags get carried through to the cast_memory->flags variable
===========
*/
void AI_MakeEnemy ( edict_t *self, edict_t *other, int memory_flags )
{
	cast_memory_t *cast_memory;

	// JOSEPH 28-DEC-98
	edict_t	*e;
	int		i;

//if (self->name_index == NAME_LISA)
//self = self;

if (other->client)// && other->client->gun_noise)
	// Find all members of the local team and hostilize them
	if (self->localteam)
	{
		for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
		{
			if ((!e->deadflag) && (e->localteam) && (e->localteam != self->localteam) &&
				(!strcmp(e->localteam, self->localteam)))
			{
	            if ((!(cast_memory = level.global_cast_memory[self->character_index][other->character_index])) ||
				   (!(cast_memory->flags & MEMORY_HOSTILE_ENEMY)))
				{
					e->localteam = NULL;
					
					if (e->reactdelay)
					{
						AI_MakeEnemy_Timer(e, other, memory_flags, e->reactdelay);
					}
					else
					{
						AI_MakeEnemy(e, other, memory_flags);
					}
				}
			}
		}	

		self->localteam = NULL;	
	}
	// END JOSEPH
	
	if ( ! (cast_memory = level.global_cast_memory[self->character_index][other->character_index] ) )
	{	// we are not aware of this person, so create the memory

		AI_RecordSighting ( self, other, VectorDistance(self->s.origin, other->s.origin) );
		cast_memory = level.global_cast_memory[self->character_index][other->character_index];

	}

	if (cast_memory->memory_type != MEMORY_TYPE_ENEMY)
	{	// make them one

		AI_RemoveFromMemory( self, cast_memory );
		AI_AddToMemory ( self, cast_memory, MEMORY_TYPE_ENEMY );

	}

	cast_memory->flags |= memory_flags;
	cast_memory->flags |= MEMORY_HOSTILE_ENEMY;
}


/*
===========
AI_RecordSighting

  Updates SRC's memory of DEST
===========
*/
void AI_RecordSighting(edict_t *src, edict_t *dest, float dist)
{
	cast_memory_t *cast_memory, *dest_enemy_memory, *dest_to_dest_enemy_memory;
	qboolean	processed=false;

	if (ai_debug_memory->value)
	{
		// draw a line to show that we can see them
		NAV_DrawLine( src->s.origin, dest->s.origin );
	}

	cast_memory = level.global_cast_memory[src->character_index][dest->character_index];

	if (!cast_memory)
	{	// we need to create the memory of this character
		AI_CreateCharacterMemory(src, dest);
		cast_memory = level.global_cast_memory[src->character_index][dest->character_index];
	}

	// do we have a sight target?
	if (	(cast_memory->memory_type == MEMORY_TYPE_ENEMY)
		&&	(src->sight_target)
		&&	(!src->goal_ent)
		&&	(cast_memory->timestamp < (level.time - 10)))	// we haven't seen them in a while
	{
		edict_t	*targ;

		targ = NULL;
		if (targ = G_Find (NULL, FOFS(targetname), src->sight_target))
		{
			src->goal_ent = targ;
			src->cast_info.aiflags |= AI_GOAL_IGNOREENEMY;
			gi.dprintf( "AI: Going for sight_target\n");
		}
	}


	// Check for special events
	processed = EP_CastSight ( src, dest, cast_memory );


	// update the memory of this character

	VectorCopy(dest->s.origin, cast_memory->last_known_origin);
	cast_memory->timestamp = level.time;
	cast_memory->timestamp_dist = dist;

	cast_memory->last_known_closest_node = dest->nav_data.cache_node;


	// if they're a friend, share enemy information
	if (	(cast_memory->memory_type == MEMORY_TYPE_FRIEND)
		&&	(	(src->cast_group != 1)
			 ||	(!dest->client && dest->leader)	// if not a client, only help if they've been hired
			 ||	(cast_memory->flags & MEMORY_HIRED)))
	{

		AI_ShareEnemies( src, dest );

	}

	else if (processed)		// EP_CastSight() has processed the reactions of this AI character
	{

		return;

	}

	/*
	else if (cast_memory->flags & MEMORY_TAUNT)
	{
		src->cast_info.currentmove = src->cast_info.move_stand;
	}
	*/
	
	// Below checks for making them HOSTILE
	
	else if (cast_memory->flags & MEMORY_HOSTILE_ENEMY)
	{

		// already hostile

		// if currently hiding from someone else, then abort hiding
		if (	(src->cast_info.aiflags & AI_TAKE_COVER)
			&&	(dest != src->cover_ent))
		{
			src->cast_info.aiflags &= ~AI_TAKE_COVER;
			src->cast_info.aiflags &= ~AI_TAKECOVER_IGNOREHEALTH;
		}

		// if we've been told to hold position, and we're melee, then hide
		else if (	!(src->cast_info.aiflags & AI_TAKE_COVER)
				&&	(src->cast_info.aiflags & AI_HOLD_POSITION)
				&&	(src->cast_info.aiflags & AI_MELEE))
		{
			AI_ForceTakeCover( src, dest, true );
		}


	}

	// If our leader has just issued a Moveout order, then we should attack it
	else if (	(src->leader)
			&&	(src->cast_info.aiflags & AI_MOVEOUT)
			&&	(src->leader->order == ORDER_MOVE)
			&&	(src->leader->moveout_ent == dest)
			&&	(dest->health > 0))
	{

		AI_MakeEnemy( src, dest, 0 );
		src->enemy = dest;

// Ridah, changed this, they should keep taking moveout orders until we tell them otherwise
//		src->cast_info.aiflags &= ~AI_MOVEOUT;

	}

	// Are they in our territory?
	else if (	(dest->last_territory_touched)
			 &&	(dest->last_territory_touched->cast_group == src->cast_group)
			 &&	(dest->last_territory_touched->moral > MORAL_HAPPY))
	{

		//  the player can have some time to get out of the
		//  territory if his weapon is holstered		

		if (	(	(dest->noise_time > (level.time - 1))
				 &&	(dest->noise_type == PNOISE_WEAPON))

			||	( VectorDistance(dest->s.origin, dest->last_territory_touched->pos1) > dest->last_territory_touched->dmg_radius )

			// problem with the ai_territory
			// ||	(dest->client && !(dest->client->pers.holsteredweapon) && dest->client->pers.weapon)
			// && (dist < AI_NOT_HOLSTERED_RANGE_2)

			||	(	(dist < AI_NOT_HOLSTERED_RANGE_1)
				 &&	(!(cast_memory->flags & MEMORY_HOSTILE_ENEMY))
				 &&	(	(!dest->client)
					 ||	(	(!dest->client->pers.holsteredweapon)
						 &&	(dest->client->pers.weapon)))))
		{	// always attack
			AI_MakeEnemy( src, dest, 0 );

			if	(dest->client && !(dest->client->pers.holsteredweapon) && dest->client->pers.weapon)
			{
				if (src->gender == GENDER_FEMALE)
					Voice_Random( src, dest, f_profanity_level3, F_NUM_PROFANITY_LEVEL3 );
				else
					Voice_Random( src, dest, fightsounds, 10 );
			}
			else
			{
				if (src->gender == GENDER_FEMALE)
					Voice_Specific( src, dest, f_fightsounds, 1 );	// FUCKER!!
				else
					Voice_Specific( src, dest, fightsounds, 9 );	// FUCKER!!
			}

			if (ai_debug_memory->value)
			{
				gi.dprintf("AI_RecordSighting: Weapon not holstered, attacking!\n");
			}
		}
		else if (dist < AI_NOT_HOLSTERED_RANGE_3)
		{	// let them know we're aware of them

			#define	TIME_TO_COMPLY	4.0

			if (!(cast_memory->flags & MEMORY_HOSTILE_ENEMY))
			{
				if (	(level.time > cast_memory->not_holstered_attack_time)
					&&	(level.time < (cast_memory->not_holstered_attack_time+5)))
				{	// attack, we've already warned them
					AI_MakeEnemy( src, dest, 0 );

					if (ai_debug_memory->value)
					{
						gi.dprintf("AI_RecordSighting: Weapon not holstered, attacking!\n");
					}
				}
				else if (level.time > cast_memory->not_holstered_attack_time)
				{

					//gi.dprintf( "SOUND TODO: GET OUT OF OUR TERRITORY PUNK!\n" );

					// FIXME: we need a list of voices to choose from here

					// there sounds should only play is dest can see src

					if (visible (src, dest) && infront (src, dest))
					{
					if (src->gender == GENDER_FEMALE)
					{
						//extern voice_table_t f_backoff[];
						Voice_Random(src, dest, f_backoff, 3);
					}
					else
					{
						//extern voice_table_t m_backoff[];
						
						// JOSEPH 26-MAY-99
						if (src->name_index == NAME_NICKIBLANCO)
						{
							Voice_Specific(src, src->cast_info.talk_ent, nickiblanco, 10);							
						}						
						else if (src->name_index == NAME_TYRONE)
						{
							Voice_Specific(src, src->cast_info.talk_ent, ty_tyrone, 10);							
						}	
						else if (src->name_index == NAME_MOKER)
						{
							Voice_Specific(src, src->cast_info.talk_ent, steeltown_moker, 10);							
						}							
						else if (src->name_index == NAME_JESUS)
						{
							Voice_Specific(src, src->cast_info.talk_ent, sr_jesus, 10);							
						}	
						else if (src->name_index == NAME_HEILMAN)
						{
							Voice_Specific(src, src->cast_info.talk_ent, heilman, 10);							
						}	
						else if (src->name_index == NAME_BLUNT)
						{
							Voice_Specific(src, src->cast_info.talk_ent, blunt, 10);							
						}	
						else if (src->name_index == NAME_KINGPIN)
						{
							Voice_Specific(src, src->cast_info.talk_ent, kingpin, 10);							
						}	
						else
							Voice_Random(src, dest, specific, 2);
						// END JOSEPH
					}
					}

					// give them some "time to comply"
					cast_memory->not_holstered_attack_time = level.time + TIME_TO_COMPLY;

					if (ai_debug_memory->value)
					{
						gi.dprintf("AI_RecordSighting: Weapon not holstered, you have %i seconds to comply\n", (int) TIME_TO_COMPLY);
					}

					// if we're standing around, turn to face them
					if (	(src->cast_info.currentmove->frame->aifunc == ai_stand)
						&&	(src->cast_info.move_avoid_walk && src->cast_info.move_avoid_crwalk))
					{
						vec3_t vec;

						VectorSubtract( dest->s.origin, src->s.origin, vec );
						VectorNormalize( vec );
						src->ideal_yaw = vectoyaw( vec );

						if (src->maxs[2] < src->cast_info.standing_max_z)
							src->cast_info.currentmove = src->cast_info.move_avoid_crwalk;
						else
							src->cast_info.currentmove = src->cast_info.move_avoid_walk;
					}

				}
			}

			// if we're standing around, turn to face them
			if (src->cast_info.currentmove->frame->aifunc == ai_stand)
			{
				vec3_t vec;

				VectorSubtract( dest->s.origin, src->s.origin, vec );
				VectorNormalize( vec );
				src->ideal_yaw = vectoyaw( vec );

				M_ChangeYaw( src );
			}
		}
/*
		else if (dist < AI_NOT_HOLSTERED_RANGE_3)
		{	// if walking, ignore, if running, turn to face them, ready for attack if they get within range

			if (VectorLength( dest->velocity ) > 210)
			{	// running
				
				// if we're standing around, turn to face them
				if (src->cast_info.currentmove->frame->aifunc == ai_stand)
				{
					vec3_t vec;

					VectorSubtract( dest->s.origin, src->s.origin, vec );
					VectorNormalize( vec );
					src->ideal_yaw = vectoyaw( vec );

					M_ChangeYaw( src );
				}

			}

		}
*/
		if (ai_debug_memory->value)
		{
			gi.dprintf("AI_RecordSighting: Get the FUCK off my street!\n");
		}

	}

	// are they attacking one of our friends (client only)?
	else if (	(dest->enemy)
			 &&	(dest->enemy->client)
			 &&	(dest->enemy->health > 0)
			 &&	(dest_to_dest_enemy_memory = level.global_cast_memory[dest->character_index][dest->enemy->character_index])
			 &&	(dest_to_dest_enemy_memory->flags & MEMORY_STARTED_ATTACK)
			 &&	(dest_enemy_memory = level.global_cast_memory[src->character_index][dest->enemy->character_index])
			 &&	(	(src->cast_group != 1)
				 ||	(!dest->enemy->client && dest->enemy->leader)	// if not a client, only help if they've been hired
				 ||	(dest_enemy_memory->flags & MEMORY_HIRED))
			 &&	(dest_enemy_memory->memory_type == MEMORY_TYPE_FRIEND))
	{	// hey, leave our homie alone!

		AI_MakeEnemy( src, dest, 0 );

		if (ai_debug_memory->value)
		{
			gi.dprintf("AI_RecordSighting: Hey, leave our homie alone!\n");
		}

	}

	// if they have recently fired a weapon, we should get outta here (since we don't want to get involved)
	else if (	!src->enemy
			&&	(!src->cast_group || (dest->current_territory != src->cast_group))
			&&	(src->moral < MORAL_PSYCOTIC)
			&&	(dest->noise_time > (level.time - 3) && dest->noise_type == PNOISE_WEAPON)
			&&	(!src->leader || (src->cast_info.aiflags & AI_HOLD_POSITION))
			&&	!src->goal_ent
			&&	(!(src->cast_info.aiflags & AI_TAKE_COVER) || (VectorDistance(src->s.origin, src->combat_goalent->s.origin) < 256))
			&&	(!directly_infront_angle(dest->noise_angles, dest, src)))
//			&&	(AI_ClearSight(src, dest, false)))
	{

		if (AI_ForceTakeCover( src, dest, true ))
		{
		}
		else if (src->maxs[2] > DUCKING_MAX_Z && src->cast_info.move_evade && src->cast_info.currentmove != src->cast_info.move_evade
			&&	(src->cast_info.currentmove->endfunc != AI_CheckEvade))	// evade
		{

			src->cast_info.currentmove = src->cast_info.move_evade;
			src->cast_info.avoid_ent = dest;
			src->cast_info.last_avoid = level.time;

			if (src->cast_info.backoff)
				src->cast_info.backoff( src, dest );
		}

	}

	// if they just fired in our direction, attack
	else if	(	(dest->noise_time > (level.time - 1))
			 && (src->cast_info.currentmove->frame->aifunc == ai_stand)
			 &&	(dest->noise_type == PNOISE_WEAPON)
			 &&	(dest->client && dest->client->pers.weapon && (dest->client->pers.weapon->ammo))	// ignore if melee
			 &&	(cast_memory->memory_type != MEMORY_TYPE_FRIEND)
			 &&	(directly_infront_angle( dest->noise_angles, dest, src ))
			 &&	(AI_ClearSight(dest, src, false)))
	{
		AI_MakeEnemy( src, dest, 0 );
	}

	else if (	 (dest->client)
			 &&	!(dest->client->pers.holsteredweapon)
			 &&	 (cast_memory->memory_type != MEMORY_TYPE_FRIEND)
			 &&	 (dest->client->pers.weapon))
	{	// get mad, they have a weapon raised

		if (	(dist < AI_NOT_HOLSTERED_RANGE_1)
			&&	!(cast_memory->flags & MEMORY_HOSTILE_ENEMY))

		{	// always attack
			AI_MakeEnemy( src, dest, 0 );

			if (ai_debug_memory->value)
			{
				gi.dprintf("AI_RecordSighting: Weapon not holstered, attacking!\n");
			}
		}
		else if (dist < AI_NOT_HOLSTERED_RANGE_2)
		{	// let them know we're aware of them

			#define	TIME_TO_COMPLY	4.0

			if (!(cast_memory->flags & MEMORY_HOSTILE_ENEMY))
			{
				if (	(level.time > cast_memory->not_holstered_attack_time)
					&&	(level.time < (cast_memory->not_holstered_attack_time+5)))
				{	// attack, we've already warned them
					AI_MakeEnemy( src, dest, 0 );

					if (ai_debug_memory->value)
					{
						gi.dprintf("AI_RecordSighting: Weapon not holstered, attacking!\n");
					}
				}
				else if (level.time > cast_memory->not_holstered_attack_time)
				{
					if (	!(cast_memory->flags & MEMORY_WARNED_BACKOFF)
						&&	(infront(src, dest) && visible (src, dest)))
					{
						cast_memory->flags |= MEMORY_WARNED_BACKOFF;

						if (src->gender == GENDER_FEMALE)
						{
							extern voice_table_t f_backoff[];
							Voice_Random(src, src->cast_info.talk_ent, f_backoff, 3);
						}
						else
						{
							extern voice_table_t m_backoff[];

							// JOSEPH 26-MAY-99
							if (src->name_index == NAME_JESUS)
								Voice_Random(src, src->cast_info.talk_ent, &sr_jesus[6], 10);
							else if (src->name_index == NAME_KINGPIN)
								Voice_Random(src, src->cast_info.talk_ent, &kingpin[6], 10);
							else if (src->name_index == NAME_HEILMAN)
								Voice_Specific (src, src->cast_info.talk_ent, heilman, 11);
							else if (src->name_index == NAME_NICKIBLANCO)
								Voice_Specific (src, src->cast_info.talk_ent, nickiblanco, 11);
							else
								Voice_Random(src, src->cast_info.talk_ent, m_backoff, 3);
							// END JOSEPH
						}
					}
					// gi.sound( src, CHAN_VOICE, gi.soundindex( "actors/profanity/level2/cuss2-3.wav" ), 1, 2, 0 );

					// give them some "time to comply"
					cast_memory->not_holstered_attack_time = level.time + TIME_TO_COMPLY;
					
					// gi.dprintf("SOUND TODO: Drop your weapon biatch!\n");

					if (ai_debug_memory->value)
					{
						gi.dprintf("AI_RecordSighting: Weapon not holstered, you have %i seconds to comply\n", (int) TIME_TO_COMPLY);
					}

					// if we're standing around, turn to face them
					if (	(src->cast_info.currentmove->frame->aifunc == ai_stand)
						&&	(src->cast_info.move_avoid_walk && src->cast_info.move_avoid_crwalk))
					{
						src->cast_info.avoid( src, dest, true );
					}

				}
			}

			// if we're standing around, turn to face them
			if (src->cast_info.currentmove->frame->aifunc == ai_stand)
			{
				vec3_t vec;

				VectorSubtract( dest->s.origin, src->s.origin, vec );
				VectorNormalize( vec );
				src->ideal_yaw = vectoyaw( vec );

				M_ChangeYaw( src );
			}

			// evade?
			if (src->cast_info.currentmove->frame->aifunc == ai_stand && src->cast_info.move_stand_evade && (src->moral < MORAL_AGGRESSIVE))
			{
				src->cast_info.currentmove = src->cast_info.move_stand_evade;
				src->last_stand_evade = level.time;
			}

		}
		else if (dist < AI_NOT_HOLSTERED_RANGE_3)
		{	// if walking, ignore, if running, turn to face them, ready for attack if they get within range

			if (VectorLength( dest->velocity ) > 210)
			{	// running
				
				// if we're standing around, turn to face them
				if (src->cast_info.currentmove->frame->aifunc == ai_stand)
				{
					vec3_t vec;

					VectorSubtract( dest->s.origin, src->s.origin, vec );
					VectorNormalize( vec );
					src->ideal_yaw = vectoyaw( vec );

					M_ChangeYaw( src );
				}

			}

		}

	}

}


void AI_CheckRecordMemory( edict_t *src, edict_t *dest )
{
	vec3_t		dest_vec;
	float		length;
	int			i;
	cast_memory_t	*memory;
	vec3_t		src_org, dest_org;

	if (dest->health <= 0)
		return;

	if (!dest->solid)
		return;

	if (dest->flags & FL_NOTARGET)
		return;

	memory = NULL;

	// check for sight by noise
	if (	(dest->noise_time > level.time)
		//&&	(level.global_cast_memory[src->character_index][dest->character_index])
		&&	(gi.inPVS( src->s.origin, dest->noise_pos )))
	{
		// update the memory of this character
		AI_RecordSighting(src, dest, VectorDistance(src->s.origin, dest->s.origin) );
		return;
	}

	if (dest->client && (dest->light_level < 5))
		return;

	// do a faster distance check, without sqrt'ing
	VectorSubtract(dest->s.origin, src->s.origin, dest_vec);

	length = 0;
	for (i=0 ; i< 3 ; i++)
		length += dest_vec[i]*dest_vec[i];

	if (length > (src->cast_info.max_sighting_distance * src->cast_info.max_sighting_distance))
		return;

	memory = level.global_cast_memory[src->character_index][dest->character_index];

	if (memory && (memory->ignore_time > level.time))
		return;	// we are currently ignoring this entity

	if (	(	(length > 65535)	// 256^2, since length is the squared distance
			 ||	(	(dest->client) 
				 &&	(VectorLength(dest->velocity) < 210)))		// out of "close" range
		&&	(	(	!memory
				 ||	(memory->timestamp < (level.time - 10)))		// not aware of this person
			 && (!infront(src, dest))))
	{
		return;
	}

	VectorCopy( src->s.origin, src_org );
	src_org[2] += src->viewheight;
	VectorCopy( dest->s.origin, dest_org );
	dest_org[2] += dest->viewheight;

	if (!gi.inPVS(src_org, dest_org) /*&& !gi.inPHS(src_org, dest_org)*/)
		return;

	if (	!memory
		 ||	(memory->timestamp < (level.time - 5))	// haven't seen them for a while
		 ||	(memory->ignore_time > level.time))
	{	// do a thorough test
		if (!AI_ClearSight(src, dest, false))
			return;

		// move the box around a bit
	}

	// SRC can see DEST

	// update the memory of this character
	AI_RecordSighting(src, dest, sqrt(length));
}

/*
===========
AI_UpdateCharacterMemories

  Called once per frame, this handles all AI character sightings, updating their memories
  as we go.
  
  The individual characters can then evaluate their memory when idle, to see if there's
  something they can do.
===========
*/
void AI_UpdateCharacterMemories( int max_iterations )
{

	// For each character, check all other characters to see if we can see and recognise them

	// Reasons for failing a sighting (in order for speed purposes):
	//
	//	1. Enemy is too dark (can't see or recognise)
	//	2. Enemy is a NOTARGET
	//	3. Enemy is too far away to recognise
	//	4. Enemy is not infront of us
	//  5. We can't physically see them

	static int src_index, dest_index;
	int			num_iterations=0;
	edict_t		*src, *dest;
	int			i;

	if (deathmatch->value)
		return;

	if (level.cut_scene_time)
		return;

	// first check client sightings
	dest = level.characters[0];

	if (dest && !(dest->flags & FL_NOTARGET))
	{
		for (i=1; i<level.num_characters; i++)
		{
			src = level.characters[i];

			if (!src)
				continue;

			if (src->health <= 0)
				continue;

			if (src->client)
				continue;

			if (src->cast_group < 2)
				continue;

			AI_CheckRecordMemory( src, dest );
		}
	}

	if (src_index >= level.num_characters)
		src_index = 0;

	for ( ; src_index < level.num_characters; src_index++)
	{
		if (!level.characters[src_index])
			continue;

		src = level.characters[src_index];

		if (src->health <= 0)
			continue;

		if (src->client)
			continue;

		for ( ; dest_index < level.num_characters; dest_index++ )
		{
			if (!level.characters[dest_index])
				continue;

			dest = level.characters[dest_index];

			if (src == dest)
				continue;

			if (dest->client && (src->cast_group >= 2))
				continue;		// already processed above

			if (num_iterations++ > max_iterations)
				return;

			AI_CheckRecordMemory( src, dest );
		}

		dest_index = 0;
	}

	src_index = 0;
}


void AI_ReactDelayThink (edict_t *ent)
{
	if (ent->enemy && ent->owner)
	{
		AI_MakeEnemy (ent->owner, ent->enemy, 0);				
		ent->cast_info.aiflags &= ~AI_HEARD_GUN_SHOT;
	}

	G_FreeEdict (ent);

}

// RAFAEL	28-dec-98
void AI_ReactDelay (edict_t *self, edict_t *player)
{
	edict_t *ent;

	ent = G_Spawn();

	ent->enemy = player;
	ent->owner = self;
	ent->nextthink = level.time + self->gun_noise_delay;
	ent->think = AI_ReactDelayThink;

	gi.linkentity (self);
}


// RAFAEL	28-dec-98
/*
AI_HearPlayer

Returns TRUE if the player and self are in the same PVS and the player has made a hostile sound
*/
qboolean AI_HearPlayer (edict_t *self)
{
	edict_t			*player;
	float			dist;
	vec3_t			vec;
	
	if (self->cast_info.aiflags & AI_IMMORTAL)
		return false;
	
	if (self->cast_group == 1)
		return false;

	if (self->cast_group == 0) // neutral will try to take cover
		return false;

	if (self->cast_info.aiflags & AI_HEARD_GUN_SHOT)
		return false;

	// this will cause a problem with scripted characters so
	// if (!EP_GetCharacter ( self->name_index ))
	//	return false;
	
	player = &g_edicts[1];
	
	if (!player->client)
		return false;

	if (player->client->gun_noise)
	{
		if (	(self->cast_group || directly_infront(player, self))
			&&	gi.inPVS (player->s.origin, self->s.origin))
		{
			VectorSubtract (player->s.origin, self->s.origin, vec);
			dist = VectorLength (vec);

			// if (self->moral > MORAL_HAPPY)
			if (dist < 1538)
			{
				if (self->gun_noise_delay)
				{
					self->cast_info.aiflags |= AI_HEARD_GUN_SHOT;
					AI_ReactDelay (self, player);
				}
				else 
					AI_MakeEnemy (self, player, 0);			
				return true;
			}
			/*
			else
			{
				gi.dprintf ("Player fired a shot but my moral is %d\n", self->moral);
				return false;
			}
			*/
		}
	}

	return false;

}

/*
===========
AI_HasLeaderButGoForEnemy
===========
*/
qboolean AI_HasLeaderButGoForEnemy( edict_t *self, edict_t *enemy )
{
	float	leader_dist;

	if (!(		(self->leader)
			&&	(self->leader->order == ORDER_FOLLOWME)))
	{
		return true;
	}

	leader_dist = VectorDistance( self->s.origin, self->leader->s.origin );

	// if we're out of range, go to them
	if (leader_dist > 512)
	{
		return false;
	}

/*
	// if they've just ordered it, go to them at all costs
	if (enemy->leader->order_timestamp > (level.time - 5))
	{
		return false;
	}
*/

	// if we're a Melee and the enemy is out of a reasonable range, don't bother
	if (self->cast_info.aiflags & AI_MELEE)
	{
		if (VectorDistance( self->leader->s.origin, enemy->s.origin ) > 256)
		{
			return false;
		}
	}

	// if we're shooting, and they're not clearly visible (shootable from here), then fail
	else
	{
		if (!AI_ClearSight( self, enemy, false ))
		{
			return false;
		}
	}

	return true;
}

/*
===========
AI_FindTarget

Self is currently not attacking anything, so try to find a target

Returns TRUE if an enemy is available (has been sighted, and we should engage)
============
*/
qboolean AI_FindTarget (edict_t *self)
{
	cast_memory_t	*cast_memory;
	edict_t			*enemy, *best;
	float			best_dist;
	int				i;

	if (self->cast_info.aiflags & AI_IMMORTAL)
		return false;

	// Ridah, Changed this 28-Mar-99, so if even a slight memory bug won't cause them to ignore you if under attack

	// traverse our enemy list for something to attack
	//cast_memory = self->cast_info.enemy_memory;

	best = NULL;

	i = 0;

	for (i = 0; i < level.num_characters; i++)
	{
		cast_memory = level.global_cast_memory[self->character_index][i];

		if (!cast_memory || cast_memory->memory_type != MEMORY_TYPE_ENEMY || g_edicts[cast_memory->cast_ent].health <= 0)
			continue;

		if (	(cast_memory->timestamp > (level.time - ENEMY_SIGHT_DURATION))
			&&	(cast_memory->flags & MEMORY_HOSTILE_ENEMY)
			&&	(cast_memory->ignore_time < level.time))
		{
			enemy = &g_edicts[cast_memory->cast_ent];

			if (enemy->flags & FL_NOTARGET)
				goto failed;

			if (!enemy->inuse)
				goto failed;

			if (enemy->health <= 0)
				goto failed;

			if (!AI_HasLeaderButGoForEnemy( self, enemy ))
				goto failed;

			if (self->cast_info.aiflags & AI_TAKE_COVER)
			{	// make sure we can see them before we attack
				if (!AI_ClearSight( self, enemy, false ))
				{
					goto failed;
				}
				else if (cast_memory->timestamp_dist < 128)	// allow some time to attack
				{
					self->cast_info.aiflags &= ~AI_TAKE_COVER;
					self->combat_goalent = NULL;
					self->dont_takecover_time = 99999;	// attack for a few second
				}
				else	// too far away, just go for another hiding pos
				{
					self->cast_info.aiflags &= ~AI_TAKE_COVER;
					self->combat_goalent = NULL;
//					goto failed;
				}
			}

			// found an enemy

			if (!best || (cast_memory->timestamp_dist < best_dist))
			{
				best = enemy;
				best_dist = cast_memory->timestamp_dist;
			}

		}

failed:

		cast_memory = cast_memory->next;
	}

	if (best)
	{
		enemy = best;

		if (	(enemy->client)
			&&	(self->cast_info.move_evade)
			&&	(!self->cast_group)
			&&	(self->moral < MORAL_AGGRESSIVE)
			&&	(!self->pain_debounce_time))	// if we've been hurt, go bezerk (don't evade)
		{
			if (	(!enemy->client->pers.holsteredweapon)
				&&	(enemy->client->pers.weapon))
			{
				vec3_t	vec;
				float	len;

				VectorSubtract (self->s.origin, enemy->s.origin, vec);
				len = VectorLength (vec);

				self->enemy = enemy;
				if (len < AI_NOT_HOLSTERED_RANGE_1 && self->moral > MORAL_HAPPY)
				{
					AI_StartAttack( self, enemy );

					if (self->cast_info.sight)
						self->cast_info.sight ( self, self->enemy );
				}
				else if (len > AI_NOT_HOLSTERED_RANGE_3)
				{
					self->cast_info.currentmove = self->cast_info.move_stand;
				}
				else if (self->maxs[2] > DUCKING_MAX_Z)
					self->cast_info.currentmove = self->cast_info.move_evade;
				else if (self->cast_info.move_stand_up)
					self->cast_info.currentmove = self->cast_info.move_stand_up;

				self->maxs[2] = self->cast_info.standing_max_z;
			}
			else
			{
				return false;
			}
		}
		else
		{
			AI_StartAttack( self, enemy );

			if (self->cast_info.sight)
				self->cast_info.sight ( self, self->enemy );

			// Ridah, 7-5-99, If they've been ordered to attack us by a client, get mad at them also
			if (enemy->leader)
				AI_MakeEnemy( self, enemy->leader, 0 );
		}

		return true;
	}

	return false;
}
