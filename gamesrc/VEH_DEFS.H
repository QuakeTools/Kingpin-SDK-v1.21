//=======================================================================

vehicle_t	global_vehicles[MAX_VEHICLES];

//=======================================================================

gearbox_t	commodore_gearbox =
{
	7,		// num_gears (Neutral, Reverse + 5 gears)

	{
		{
			"Reverse",		// display name
			0,				// index
			-2				// gear ratio
		},
		{
			"Neutral",
			1,
			0
		},
		{
			"1st",
			2,
			2.8
		},
		{
			"2nd",
			3,
			2.0
		},
		{
			"3rd",
			4,
			1.5
		},
		{
			"4th",
			5,
			1.0
		},
		{
			"5th",
			6,
			0.8
		}
	}

};

wheel_traction_table_t	generic_wheel_traction =
{
	0.8,		// concrete
	0.6,		// fabric
	0.4,		// gravel
	0.7,		// metal
	0.1,		// snow
	0.6,		// tile
	0.7			// wood
};

wheel_t		generic_wheel =
{
	29,						// radius (cm)
	&generic_wheel_traction	// traction table
};

vehicle_define_t	vehicle_defines[] =
{

	{
		"Commodore VT",

		&commodore_gearbox,
		&generic_wheel,
		150,				// wheelspan width (cm)
		250,				// wheelspan length (cm)
		1650,			// weight (kg)
		40,				// maximum steering angle
		180,			// engine power output (kW)
		3,				// diff ratio

		"models/vehicles/cars/viper/tris_test.md2",		// body model
		0,												// body skin

		"models/vehicles/cars/misc/wheel.md2",				// wheel model
		0,												// wheel skin

		NULL,											// gear change sound
	},

	{
		NULL
	}

};
