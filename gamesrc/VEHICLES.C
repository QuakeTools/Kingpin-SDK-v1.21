//======================================================================
// Vehicle Physics/Simulation

#include "g_local.h"
#include "veh_defs.h"


/*
Veh_ProcessFrame

  Handles everything from input acceleration/braking, through world physics and dynamics.
*/
void Veh_ProcessFrame( edict_t *ent, usercmd_t *ucmd, pmove_t *pm )
{
	vehicle_t	*vehicle;

	// find the vehicle structure

	if (ent->vehicle_index)
	{
		vehicle = &global_vehicles[ent->vehicle_index - 1];
	}
	else // need to assign them one
	{
		int i;
		for (i=0; i< MAX_VEHICLES; i++)
		{
			if (!global_vehicles[i].driver)
			{
				vehicle = &global_vehicles[i];
				ent->vehicle_index = i + 1;

				vehicle->driver	= ent;

				// this will eventually be setup inside the map, but for now just do it here
				vehicle->def	= &vehicle_defines[0];

				Veh_InitVehicle( vehicle );
			}
		}
	}


	VectorCopy( vehicle->origin, vehicle->oldorigin );
	VectorCopy( vehicle->angles, vehicle->oldangles );


	// Process the controls
	Veh_ProcessControls( vehicle, ucmd );


	// Set steering avelocity
	Veh_SetSteeringAngleVelocity( vehicle );

	// Do Angular Velocities
	Veh_PerformAngleVelocity( vehicle, 0.001 * ((float)ucmd->msec), pm );


	// Move the vehicle according to it's velocity
	Veh_PerformMove( vehicle, pm );


	// Examine movement, adjusting velocity accordingly

	
	// Set the position of the owner to the middle of the front and rear positions, with angles:

		// PITCH:	according to front/rear positions
		// ROLL:	use interpolated roll angles from downward traces at each wheel(??)


	// Show the vehicle
	Veh_PositionModels( vehicle );
}

/*
==================
Veh_InitVehicle

  Initializes a vehicle ready for placing into the game
==================
*/
void Veh_InitVehicle ( vehicle_t *vehicle )
{

	vehicle->front_traction	= 1.0;
	vehicle->rear_traction	= 1.0;

	vehicle->front_weight_ratio = 0.5;

	vehicle->front_onground = true;
	vehicle->rear_onground = true;

	VectorClear( vehicle->velocity );
	VectorClear( vehicle->avelocity );
	VectorCopy( vehicle->driver->s.origin, vehicle->origin );
	VectorCopy( vehicle->driver->s.angles, vehicle->angles );

	vehicle->gear = 1;		// neutral
	vehicle->rpm = 0;
	vehicle->throttle = 0;
	vehicle->steer_yaw = 0;

	vehicle->fl = G_Spawn();
	vehicle->fl->s.modelindex = gi.modelindex( vehicle->def->wheel_model );
	vehicle->fr = G_Spawn();
	vehicle->fr->s.modelindex = gi.modelindex( vehicle->def->wheel_model );
	vehicle->rl = G_Spawn();
	vehicle->rl->s.modelindex = gi.modelindex( vehicle->def->wheel_model );
	vehicle->rr = G_Spawn();
	vehicle->rr->s.modelindex = gi.modelindex( vehicle->def->wheel_model );
}	

/*
=====================
Veh_ProcessControls

  Process all inputs and adjust velocities and traction levels
=====================
*/
void Veh_ProcessControls ( vehicle_t *vehicle, usercmd_t *ucmd )
{

#define THROTTLE_ACCELERATION	20000.0		// increase this amount per second
#define	THROTTLE_DECCELERATION	20000.0
#define	STEERING_ACCELERATION	75.0

	float	throttle_add, throttle_ideal, throttle_max, throttle_rate;
	float	steering_ideal, steering_add, steering_max, steer_rate;
	vec3_t	forward, unit_vel;
	float	frametime;
	float	current_speed;
	float	new_rpm;

	float	wheel_torque, max_wheel_torque;
	float	ideal_speed, rear_speed;

	float	accel_force		= 0;	// force applied by ground
	float	accel_speed		= 0;	// transferred velocity increase to vehicle


	AngleVectors( vehicle->angles, forward, NULL, NULL );

	if (vehicle->velocity[0] || vehicle->velocity[1] || vehicle->velocity[2])
	{
		current_speed = VectorNormalize2( vehicle->velocity, unit_vel );
	}
	else
	{
		VectorCopy( forward, unit_vel );
		current_speed = 0;
	}

	frametime = (0.001 * ucmd->msec);


	// adjust throttle
	
	throttle_ideal = ((float)(ucmd->forwardmove) / 400.0) * (THROTTLE_MAX - IDLE_THROTTLE) + IDLE_THROTTLE;

	if (throttle_ideal < 0)
		throttle_ideal = 0;		// TODO: this would be brakes

	throttle_add = throttle_ideal - vehicle->throttle;

	if ((throttle_add < 0) && (ucmd->forwardmove >= 0) && (vehicle->gear == 1))
		throttle_rate = THROTTLE_DECCELERATION;
	else
		throttle_rate = THROTTLE_ACCELERATION;

	if (fabs( throttle_add ) > (throttle_max = (throttle_rate * frametime) ) )
	{
		if (throttle_add < 0)
			throttle_add = -throttle_max;
		else
			throttle_add =  throttle_max;
	}

	vehicle->throttle = vehicle->throttle + throttle_add;

	Veh_Debug( "Thr=%4i ", (int)vehicle->throttle );

	// adjust steering

	steering_ideal = -((float)(ucmd->sidemove) / 400.0) * vehicle->def->max_steer * (0.5 + 0.5 * ((VEH_MAX_SPEED - current_speed) / VEH_MAX_SPEED));

	// turn faster if changing directions
	steer_rate = STEERING_ACCELERATION;

	if (steering_ideal == 0)
		steer_rate *= 2;

	if (steering_ideal < 0)
	{
		if (vehicle->steer_yaw > 0)
			steer_rate *= 2;
	}
	else
	{
		if (vehicle->steer_yaw < 0)
			steer_rate *= 2;
	}

	steering_add = steering_ideal - vehicle->steer_yaw;

	if (fabs( steering_add ) > (steering_max = (steer_rate * frametime) ) )
	{
		if (steering_add < 0)
			steering_add = -steering_max;
		else
			steering_add =  steering_max;
	}

	vehicle->steer_yaw += steering_add;

	Veh_Debug( "Str=%2i ", (int)vehicle->steer_yaw );


	Veh_Debug( "G=%s ", vehicle->def->gearbox->gears[vehicle->gear].name );

	// Do engine acceleration

//	if (vehicle->throttle > vehicle->rpm)
	{

		// Get the new engine RPM, which is effected by the current throttle, and drivetrain resistance

		if (vehicle->def->gearbox->gears[vehicle->gear].ratio)	// current gear isn't neutral
		{

			// Get the "force" applied by the acceleration on the drivetrain
			// We use this to determine whether or not the rear wheels will hold traction

			// get the amount of torque applied at the rear wheels

			wheel_torque = Veh_WheelTorqueAtRPM( vehicle, vehicle->throttle - vehicle->rpm );

			Veh_Debug( "Tw=%i ", (int)wheel_torque );


			// get the maximum amount of torque the rear wheels will take

			max_wheel_torque =

				(1.0 - vehicle->front_weight_ratio)
			*	(vehicle->def->weight * KG_TO_LBS)
			*	((vehicle->rear_traction + 1.0) / 2.0);

			Veh_Debug( "TwM=%i ", (int)max_wheel_torque );

			
			// get the speed we should be doing at the new rpm

			ideal_speed = Veh_SpeedAtRPM( vehicle, vehicle->throttle );

			Veh_Debug( "iSpd=%i ", (int)ideal_speed );


			rear_speed = current_speed;
			if (rear_speed > 0)
//				rear_speed *= ((fabs(DotProduct( forward, unit_vel )) + 1.0) / 2.0);
				rear_speed *= DotProduct( forward, unit_vel );

			Veh_Debug( "cSpd=%i ", (int)rear_speed );

			
			if (	((ideal_speed > 0) && (ideal_speed > rear_speed))
				||	((ideal_speed < 0) && (ideal_speed < rear_speed)))
			{
				if (wheel_torque > max_wheel_torque)
				{
					vehicle->rear_traction -= (wheel_torque / max_wheel_torque) * frametime;
				}
				else if (vehicle->rear_traction < 1.0)
				{
					vehicle->rear_traction += ((max_wheel_torque - wheel_torque) / max_wheel_torque) * frametime * 7.0;

					if (vehicle->rear_traction > 1.0)
						vehicle->rear_traction = 1.0;
				}

				// cap min traction (TODO: use current surface as factor of minimum)
				if (vehicle->rear_traction < 0.1)	// HACK
					vehicle->rear_traction = 0.1;

				// get the amount of force applied to the vehicle at the new throttle

				accel_force =
					
					(wheel_torque) * LBS_TO_KG
				*	FT_TO_CM * CM_TO_UNITS
				*	vehicle->rear_traction
				*	2.0						// HACK, fudge factor
				/	frametime;				// convert to force per second

				if (ideal_speed < 0)
					accel_force *= -1;

			}
			else	// slowing down
			{

				// if we're going faster than the maximum revs of the engine will take us
				if ( Veh_SpeedAtRPM( vehicle, THROTTLE_MAX ) < rear_speed )
				{
					// lose traction, but still grip
					vehicle->rear_traction -= 2 * frametime;		// ???

					// cap min traction (TODO: use current surface as factor of minimum)
					if (vehicle->rear_traction < 0.5)	// HACK
						vehicle->rear_traction = 0.5;
				}
				else if (vehicle->rear_traction < 1.0)
				{
					// regain traction
					vehicle->rear_traction += 5 * frametime;		// ???

					if (vehicle->rear_traction > 1.0)
						vehicle->rear_traction = 1.0;
				}

				// Decompression braking!
				wheel_torque = Veh_WheelTorqueAtRPM( vehicle, vehicle->rpm );
				
				accel_force =
					
					(wheel_torque) * LBS_TO_KG
				*	-0.5
				*	FT_TO_CM * CM_TO_UNITS
				*	vehicle->rear_traction
				/	frametime;				// convert to force per second
			}

			Veh_Debug( "Tr=%1.2f ", vehicle->rear_traction );


			Veh_Debug( "Af=%i ", (int)accel_force );


			accel_speed = accel_force / vehicle->def->weight;

			// factor in rolling resistance
			accel_speed -= current_speed * 0.0007656;

			// factor in drag resistance
			accel_speed -= (0.5 * 0.3 * 20 * 0.00025 * ((current_speed*UNITS_TO_CM*CM_TO_FT) * (current_speed*UNITS_TO_CM*CM_TO_FT))) * FT_TO_CM * CM_TO_UNITS
							* 0.05;	// Fudge factor

			Veh_Debug( "As=%i ", (int)accel_speed );
		}

	}


	// Calculate the transferred velocity to the vehicle

	VectorMA( vehicle->velocity, accel_speed * frametime, forward, vehicle->velocity );

	current_speed = VectorLength( vehicle->velocity );

	Veh_Debug( "Spd=%i ", (int)current_speed );

	// get the new engine RPM
	if (vehicle->gear != 1)
	{
		rear_speed = current_speed;
		if (rear_speed > 0)
			rear_speed *= ((fabs(DotProduct( forward, unit_vel )) + 1.0) / 2.0);

		new_rpm = Veh_RPMatSpeed( vehicle, rear_speed );
		if (new_rpm > THROTTLE_MAX)
			new_rpm = THROTTLE_MAX;

		if (vehicle->rear_traction >= 1)
		{
			vehicle->rpm = new_rpm;

			if (vehicle->rear_traction > 1.0)
				vehicle->rear_traction = 1.0;
		}
		else	// use new_rpm, but adjust for throttle
		{
			vehicle->rpm = new_rpm + (vehicle->throttle - new_rpm) * (1.0 - vehicle->rear_traction);
		}
	}
	else
	{
		vehicle->rpm = vehicle->throttle;
	}

	Veh_Debug( "Erpm=%4.0f ", vehicle->rpm );


	Veh_Debug( "\n" );
}

/*
=================
Veh_Debug
=================
*/
void	Veh_Debug( char *fmt, ...)
{
	int		len;
	va_list		argptr;
	char	bigbuffer[0x10000];

	va_start (argptr,fmt);
	len = vsprintf (bigbuffer,fmt,argptr);
	va_end (argptr);

	gi.dprintf( bigbuffer );
}

/*
=================
Veh_SpeedAtRPM
=================
*/
float	Veh_SpeedAtRPM( vehicle_t *veh, float rpm )
{
	float	speed;
	
	speed =

		(rpm)
	*	(1.0 / veh->def->gearbox->gears[veh->gear].ratio)
	*	(1.0 / veh->def->diff_ratio)
	*	(M_PI * veh->def->wheels->radius * 2 * CM_TO_UNITS)
	*	MIN_PER_SEC;

	return speed;
}

/*
=================
Veh_RPMatSpeed
=================
*/
float	Veh_RPMatSpeed( vehicle_t *veh, float speed )
{
	float	rpm;
	
	rpm =

		(speed)
	*	(veh->def->gearbox->gears[veh->gear].ratio)
	*	(veh->def->diff_ratio)
	*	(1.0 / (M_PI * veh->def->wheels->radius * 2 * CM_TO_UNITS))
	*	SEC_PER_MIN;

	if (rpm < 0)	// reversing
		rpm = -rpm;

	return rpm;
}

/*
=================
Veh_SpeedAtRPM
=================
*/
float	Veh_WheelTorqueAtRPM( vehicle_t *veh, float rpm )
{
	float	torque;
	
	torque =

		(veh->def->engine_power * 1.5)		// translate roughly to foot-pounds of engine torque
	*	(rpm / THROTTLE_MAX)
	*	(veh->def->gearbox->gears[veh->gear].ratio)
	*	(veh->def->gearbox->gears[veh->gear].ratio)			// Fudge factor
	*	(veh->def->diff_ratio)
	*	(1.0 / (veh->def->wheels->radius * CM_TO_FT));

	return torque;
}


/*
=================
Veh_PerformMove
=================
*/
void	Veh_PerformMove( vehicle_t *vehicle, pmove_t *pm )
{
	int i;
	gclient_t	*client;
	edict_t		*ent;

	ent = vehicle->driver;
	client = vehicle->driver->client;

	for (i=0 ; i<3 ; i++)
	{
		pm->s.origin[i] = vehicle->origin[i]*8;
		pm->s.velocity[i] = vehicle->velocity[i]*8;
	}

	// perform a pmove
	gi.Pmove (pm);

	// save results of pmove
	client->ps.pmove = pm->s;
	client->old_pmove = pm->s;

	for (i=0 ; i<3 ; i++)
	{
		vehicle->origin[i] = pm->s.origin[i]*0.125;
		vehicle->velocity[i] = pm->s.velocity[i]*0.125;
	}

//	VectorCopy (pm->mins, ent->mins);
//	VectorCopy (pm->maxs, ent->maxs);

//	client->resp.cmd_angles[0] = SHORT2ANGLE(ucmd->angles[0]);
//	client->resp.cmd_angles[1] = SHORT2ANGLE(ucmd->angles[1]);
//	client->resp.cmd_angles[2] = SHORT2ANGLE(ucmd->angles[2]);

	VectorCopy( vehicle->angles, client->ps.viewangles );
	VectorCopy( vehicle->angles, client->v_angle );

	client->ps.pmove.pm_type = PM_FREEZE;

	ent->viewheight = pm->viewheight;
	ent->waterlevel = pm->waterlevel;
	ent->watertype = pm->watertype;
	ent->groundentity = pm->groundentity;
	if (pm->groundentity)
		ent->groundentity_linkcount = pm->groundentity->linkcount;

	VectorCopy( vehicle->origin, ent->s.origin );
}


void	Veh_PerformAngleVelocity( vehicle_t *vehicle, float frametime, pmove_t *pm )
{
	float speed;
	vec3_t	unitvel, forward, up;

	VectorMA( vehicle->angles, frametime, vehicle->avelocity, vehicle->angles );

	// adjust velocity
	if (vehicle->velocity[0] || vehicle->velocity[1] || vehicle->velocity[2])
	{
		AngleVectors( vehicle->angles, forward, NULL, up );
		speed = VectorNormalize2( vehicle->velocity, unitvel );

		VectorScale( forward, speed * (vehicle->rear_traction + vehicle->front_traction) / 2.0, vehicle->velocity );
		VectorMA( vehicle->velocity, speed * (1.0 - ((vehicle->rear_traction + vehicle->front_traction) / 2.0)), unitvel, vehicle->velocity );
	}

	// According to traction levels, we should move the CG (center of gravity), such that:
	//
	// * Under FULL traction of the REAR wheels, rotate about the rear axle center
	// * Under ZERO traction of the REAR wheels, rotate about the front axle center

	// Just calculate this as a movement of the center of the vehicle / second, and add to velocity

	if (vehicle->avelocity[YAW])
	{
		vec3_t	dst, pnt, rear_pnt, move;
		vec3_t	velback;

		VectorMA( vehicle->origin, (-vehicle->def->wheelspan_length*0.5 + (vehicle->def->wheelspan_length * (1.0 - vehicle->rear_traction) * (vehicle->front_traction*0.5 + 0.5))), forward, rear_pnt );
		VectorSubtract( vehicle->origin, rear_pnt, pnt );

		RotatePointAroundVector( dst, up, pnt, vehicle->avelocity[YAW] * frametime );

		VectorSubtract( dst, pnt, move );
		// convert to per second, since it'll get converted back in Pmove();
		VectorScale( move, 0.3 / frametime, move );	// 0.3 is a HACK, should be 1.0

		// save the velocity
		VectorCopy( vehicle->velocity, velback );

		VectorCopy( move, vehicle->velocity );

		// move the vehicle to account for the change in CG
		Veh_PerformMove( vehicle, pm );

		// set the velocity back
		VectorCopy( velback, vehicle->velocity );

		Veh_Debug( "YawAdjust=%3.0f ", VectorLength(move) );
	}

}

void	Veh_SetSteeringAngleVelocity( vehicle_t *vehicle )
{
	float	speed, dot, yaw_change;
	vec3_t	forward, unitvel;

	AngleVectors( vehicle->angles, forward, NULL, NULL );

	if (vehicle->velocity[0] || vehicle->velocity[1] || vehicle->velocity[2])
	{
		speed = VectorNormalize2( vehicle->velocity, unitvel );

		yaw_change =

			(	(vehicle->steer_yaw)
			 *	(speed / (vehicle->def->wheelspan_length * CM_TO_UNITS))
			 *	(vehicle->front_traction))

			-	vehicle->avelocity[YAW];

		dot = DotProduct( forward, unitvel );

		yaw_change *= dot;		// this works for reverse, since yaw is just the opposite
	}
	else
	{
		speed = 0;
		VectorClear( unitvel );

		yaw_change = -vehicle->avelocity[YAW] * vehicle->front_traction;
	}

	vehicle->avelocity[YAW] += yaw_change;

	Veh_Debug( "YawVel=%3.0f\n", vehicle->avelocity[YAW] );
}


void	Veh_HoldRearWheels( vehicle_t *vehicle )
{
	vec3_t	old_rear, new_rear;
	vec3_t	old_fwd, new_fwd;
	vec3_t	ideal_rear, ideal_vec, end_rear;
	vec3_t	new_vec, old_vec;

	AngleVectors( vehicle->oldangles, old_fwd, NULL, NULL );
	VectorMA( vehicle->oldorigin, -vehicle->def->wheelspan_length * 0.5, old_fwd, old_rear );

	AngleVectors( vehicle->angles, new_fwd, NULL, NULL );
	VectorMA( vehicle->origin, -vehicle->def->wheelspan_length * 0.5, new_fwd, new_rear );

	VectorSubtract( old_rear, vehicle->origin, old_vec );
	VectorNormalize( old_vec );
	VectorMA( vehicle->origin, vehicle->def->wheelspan_length * 0.5, old_vec, ideal_rear );

	// now move to it depending on traction
	VectorSubtract( ideal_rear, new_rear, ideal_vec );
	VectorMA( new_rear, vehicle->rear_traction, ideal_vec, end_rear );

	VectorSubtract( vehicle->origin, end_rear, new_vec );
	VectorNormalize( new_vec );

	vehicle->angles[YAW] = vectoyaw( new_vec );
}

// this is hacked together just for debugging
void	Veh_PositionModels( vehicle_t *vehicle )
{
	vec3_t	fwd, right, up;

	AngleVectors( vehicle->angles, fwd, right, up );

	VectorMA( vehicle->origin,			 0.5 * CM_TO_UNITS * vehicle->def->wheelspan_length,	fwd,	vehicle->fl->s.origin );
	VectorMA( vehicle->fl->s.origin,	-0.5 * CM_TO_UNITS * vehicle->def->wheelspan_width,	right,	vehicle->fl->s.origin );
	VectorMA( vehicle->fl->s.origin,	-24 + CM_TO_UNITS * vehicle->def->wheels->radius,		up,		vehicle->fl->s.origin );
	VectorCopy( vehicle->angles, vehicle->fl->s.angles );
	vehicle->fl->s.angles[YAW] += vehicle->steer_yaw;
	gi.linkentity( vehicle->fl );

	VectorMA( vehicle->origin,			 0.5 * CM_TO_UNITS * vehicle->def->wheelspan_length,	fwd,	vehicle->fr->s.origin );
	VectorMA( vehicle->fr->s.origin,	 0.5 * CM_TO_UNITS * vehicle->def->wheelspan_width,	right,	vehicle->fr->s.origin );
	VectorMA( vehicle->fr->s.origin,	-24 + CM_TO_UNITS * vehicle->def->wheels->radius,		up,		vehicle->fr->s.origin );
	VectorCopy( vehicle->angles, vehicle->fr->s.angles );
	vehicle->fr->s.angles[YAW] += vehicle->steer_yaw;
	gi.linkentity( vehicle->fr );

	VectorMA( vehicle->origin,			-0.5 * CM_TO_UNITS * vehicle->def->wheelspan_length,	fwd,	vehicle->rl->s.origin );
	VectorMA( vehicle->rl->s.origin,	-0.5 * CM_TO_UNITS * vehicle->def->wheelspan_width,	right,	vehicle->rl->s.origin );
	VectorMA( vehicle->rl->s.origin,	-24 + CM_TO_UNITS * vehicle->def->wheels->radius,		up,		vehicle->rl->s.origin );
	VectorCopy( vehicle->angles, vehicle->rl->s.angles );
	gi.linkentity( vehicle->rl );

	VectorMA( vehicle->origin,			-0.5 * CM_TO_UNITS * vehicle->def->wheelspan_length,	fwd,	vehicle->rr->s.origin );
	VectorMA( vehicle->rr->s.origin,	 0.5 * CM_TO_UNITS * vehicle->def->wheelspan_width,	right,	vehicle->rr->s.origin );
	VectorMA( vehicle->rr->s.origin,	-24 + CM_TO_UNITS * vehicle->def->wheels->radius,		up,		vehicle->rr->s.origin );
	VectorCopy( vehicle->angles, vehicle->rr->s.angles );
	gi.linkentity( vehicle->rr );

}