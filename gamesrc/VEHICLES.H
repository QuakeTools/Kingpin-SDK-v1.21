// Vehicle defines


#define	THROTTLE_MAX			8000.0
#define	IDLE_THROTTLE			1000.0
#define	DEFAULT_VEHICLE_WEIGHT	1650.0
#define	VEH_MAX_SPEED			1500.0

// these could be replaced with constants to speed things up
#define	UNITS_TO_CM				4.0
#define	CM_TO_UNITS				(1.0/UNITS_TO_CM)
#define	MIN_PER_SEC				(1.0 / 60.0)
#define	SEC_PER_MIN				(60.0)
#define	LBS_TO_KG				(12.5/28.0)
#define	KG_TO_LBS				(28.0/12.5)
#define	FT_TO_CM				(2.5*12.0)
#define	CM_TO_FT				(1.0/(2.5*12.0))

#define	MAX_VEHICLES	64


// Static

typedef struct
{
	float	concrete, fabric, gravel, metal, snow, tile, wood;
} wheel_traction_table_t;

typedef struct
{
	float	radius;
	wheel_traction_table_t	*whl_trac;		// how the wheel grips to each surface type
} wheel_t;

typedef struct
{
	char	*name;
	int		index;
	float	ratio;		// effects acceleration, top speed, etc. we could make these configurable
						// e.g. a ratio of 0.5 means the drive wheels will spin 0.5 of a revolution
						//	for each engine revolution
} gear_t;

typedef struct
{
	int		num_gears;
	gear_t	gears[8];			//  0 = reverse, 1 = neutral
} gearbox_t;

typedef struct
{
	char		*name;

	// mechanics
	gearbox_t	*gearbox;		// stores all gears for this vehicle
	wheel_t		*wheels;
	float		wheelspan_width;
	float		wheelspan_length;

	float		weight;			// effects acceleration, traction, braking, etc
	float		max_steer;		// maximum angle of steering
	float		engine_power;	// engine power output (kW)
	float		diff_ratio;		// usually 3 : 1

	// visuals
	char		*body_model;
	int			body_skin;

	char		*wheel_model;
	int			wheel_skin;

	// sounds
	char		*shift_sound;
	
} vehicle_define_t;

// Run-time

// This stores the information pertaining to an active vehicle in the game.
typedef struct
{
	edict_t				*driver;

	vehicle_define_t	*def;

	float	front_traction, rear_traction;	// 0.0 (no traction) -> 1.0 (full traction)

	float	front_weight_ratio;		// at rest, this should be 0.5.
									// when accelerating, this will decrease as weight is transferred
									// to the rear wheels.
									// vice versa for braking/decelleration

	qboolean	front_onground;
	qboolean	rear_onground;

	int		gear;					// current gear, 0 = reverse, 1 = neutral
	float	rpm;
	float	throttle;				// 0 (none) -> THROTTLE_MAX (full)
									// This will effect RPM by increasing
									// fuel intake. If drive wheels have full traction, RPM
									// will be limited to the RPM of the drive wheels (which is
									// determined by applying a formula to the current rear velocity).

									// If this is lower then the current RPM, decceleration will
									// occur, depending on rear wheel traction and the current RPM
									// (higher RPM will induce more decompression braking on rear wheels).

									// if Negative, brakes will be applied in same scale (0 - THROTTLE_MAX).

	float	steer_yaw;

	vec3_t	angles, origin;
	vec3_t	oldorigin, oldangles;
	vec3_t	velocity;				// overall velocity
	vec3_t	avelocity;				// angular velocity (only used when in air?)


	edict_t	*fl, *fr, *rl, *rr;

} vehicle_t;

//=============================================================================
// Vars

extern vehicle_t	global_vehicles[MAX_VEHICLES];


void	Veh_ProcessFrame( edict_t *ent, usercmd_t *ucmd, pmove_t *pm );
void	Veh_InitVehicle ( vehicle_t *vehicle );
void	Veh_ProcessControls ( vehicle_t *vehicle, usercmd_t *ucmd );
void	Veh_Debug( char *fmt, ...);
float	Veh_SpeedAtRPM( vehicle_t *veh, float rpm );
float	Veh_WheelTorqueAtRPM( vehicle_t *veh, float rpm );
float	Veh_RPMatSpeed( vehicle_t *veh, float speed );
void	Veh_PerformMove( vehicle_t *vehicle, pmove_t *pm );
void	Veh_PerformAngleVelocity( vehicle_t *vehicle, float frametime, pmove_t *pm );
void	Veh_SetSteeringAngleVelocity( vehicle_t *vehicle );
void	Veh_HoldRearWheels( vehicle_t *vehicle );
void	Veh_PositionModels( vehicle_t *vehicle );
