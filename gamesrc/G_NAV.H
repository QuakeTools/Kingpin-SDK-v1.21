// ==================================================================
//
//	Character Navigation System (CNS)
//
// ==================================================================

// ==================================================================
// Defines

#define		MAX_NODES				700
#define		MAX_PARENT_NODES		128
#define		MAX_VIS_NODES			15		// bound by file IO methods
#define		MAX_CELLS_PER_NODE		4

#define		MAX_MAP_AXIS			5000
#define		CELL_AXIS_SUBDIVISION	32		// each axis is divided into segments, to form the cell grid
#define		OPTIMIZE_NODES			2000	// check this many nodes per frame

// each node can ONLY be ONE of the following types
#define		NODE_NORMAL				0
#define		NODE_JUMP				1		// jump from this node
#define		NODE_LANDING			2		// landing from a jump node
#define		NODE_PLAT				4		// start riding a platform
#define		NODE_TELEPORT			8		// move into a teleporter
#define		NODE_BUTTON				16
// the following can exist in conjunction with others
#define		NODE_DUCKING			32

// Visibility Tests
#define		VIS_LINE				0
#define		VIS_PARTIAL				1
#define		VIS_FULL				2

// Route types (returned by NAV_Route_*())
#define		ROUTE_NONE				0
#define		ROUTE_INDIRECT			1
#define		ROUTE_DIRECT			2

// Reachable tests
#define		REACHABLE_THOROUGH		4
#define		REACHABLE_AVERAGE		16
#define		REACHABLE_POOR			32

// File I/O
#ifdef _WIN32
#define		DIR_SLASH				"\\"
#else
#define		DIR_SLASH				"/"
#endif

#define		ROUTE_VERSION			4		// incremented each time file structure is changed, to allow automatic updating, if possible
#define		ROUTE_SUBDIR			"navdata"
#define		ROUTE_EXT				"nav"

// #define		DUCKING_MAX_Z			4
#define		DUCKING_MAX_Z			24		// as requested

// Not used anymore, characters have individual max_z values
//#define		STANDING_MAX_Z			32

//ent->nav_data->flags
#define		ND_STATIC				1		// this entity NEVER moves (items)

//ent->nav_build_data->flags
#define		NBD_DUCK_NEWPATH		1		// set this whenever starting to duck while dropping nodes
#define		NBD_JUMPING				2
#define		NBD_SHOWPATH			4

//NAV_GetHidePos parameters
#define		HIDEPOS_FURTHER			-1
#define		HIDEPOS_ANY				0
#define		HIDEPOS_CLOSER			1

// ==================================================================
//#include "q_shared.h"

typedef struct node_s node_t;
typedef struct parent_node_s parent_node_t;
typedef struct cell_node_s cell_node_t;

// ==================================================================
// Node structures
//
// ..................................................................
//	Routes
//
//		This is where the actual route between 2 nodes is stored.
//		This is the base of an array, where each item represents
//		a path between the source node, and the destination
//		(referenced by each array item).

typedef struct
{
	short			path;		// Node to head for, to get to another node, -1 if no route
	unsigned short	dist;		// route distance from this node, to the other node
} route_t;

// ..................................................................
//	Parent (low-detail) nodes
//
//		These are created, by merging a series of close-by (child) nodes
//		into one parent node. These are only used for navigation
//		of units that are not currently loaded into memory.

struct parent_node_s
{
	vec3_t	origin;
	
	route_t	routes[MAX_PARENT_NODES];	// Route data between this and all other parent nodes
};

// ..................................................................
//	Child (high-detail) nodes
//
//		The "normal" state of a node, used when traversing the active
//		geometry.

struct node_s
{
	short	index;					// index of this node in the "nodes" array

	// SAVED DATA
	float	timestamp;				// time node was created (used for node-creation code)
	vec3_t	origin;					// position of node in active geometry
	vec3_t	jump_vel;				// used for jump velocity
	short	node_type;				// one of NODE_* constants (not flags)
	short	goal_index;				// used for jump nodes, so we know which node to land on
	byte	waterlevel;
	short	yaw;					// direction facing when node was dropped
	byte	cast_group;				// set this when the node is dropped inside the territory of a specific gang

	short	visible_nodes[MAX_VIS_NODES]; // nodes that are visible and reachable from this node
	short	num_visible;			// number of nodes visible from this node

	route_t	routes[MAX_NODES];		// Route data between this node and all other nodes

	// Calculated/used at run-time
	csurface_t	*surface;			// surface immediately below the node (used for visibility checking)
	float		ignore_time;		// don't go for this node if level.time < ignore_time
	edict_t		*goal_ent;			// used for trigger/platform/etc relationships

	// used by NAV_GetHidePos() to speed things up
	float		last_sight_check;
	qboolean	last_sight_result;

};

// ..................................................................
//	Cell nodes
//
//		These are used, to keep track of which cells a node belongs to.

struct cell_node_s
{
	node_t			*node;			// node that this cell_node is representing
	cell_node_t		*next;			// next cell_node in the cell's list, NULL if end
};

// ..................................................................
// Active Unit-specific structure
//
//		Stores all information relative to an ACTIVE unit (the unit currently
//		being played.
//
//		It is assumed that the eventual structures for inactive and active
//		units will simply contain pointers to an active_node_data_t or an
//		inactive_node_data_t, with one of them being NULL.

typedef struct
{
	short		node_count;			// number of nodes currently in the unit
	qboolean	modified;			// set if the node data has been modified, so saving will be required

	//	Main Node Array
	//
	//		Used for references between nodes. Allows use
	//		of 16bit array indexes, instead of 32-pointers, which saves LOTS
	//		of memory.
	//
	//		Nodes are allocated as they are added, since the actual nodes are
	//		the main source of memory useage.

	node_t	*nodes[MAX_NODES];

	//	Node Cells
	//
	//		Contains a list of "cell_nodes", which represent a node being in a cell.
	//		Each node can have up to 4 "cell_nodes", which represent each cell that
	//		the node is within.
	//
	//		"cell_nodes" are created dynamically, as each node is created, and assigned
	//		to a cell. These "cell_nodes" are then linked to their cell via a linked
	//		list, which starts with the array below.

	cell_node_t	*cells[CELL_AXIS_SUBDIVISION][CELL_AXIS_SUBDIVISION];

} active_node_data_t;

// ..................................................................
// Inactive Unit-specific structure
//
//		Stores only the navigation data required for an inactive unit, which
//		is MUCH less than an active unit.
//
//		Note that area cell's aren't required here, since searches will be
//		fast enough not to require them, considering the low number of
//		parent nodes in an inactive unit (hence, low-detail nodes).

typedef struct
{

	short		node_count;

	// Parent Node array
	//
	//		Stores a pointer to all parent nodes in the inactive unit.

	parent_node_t	*parent_nodes[MAX_PARENT_NODES];

} inactive_unit_t;

// ..................................................................
// Navigational System data, used for entities

typedef struct
{
	int		flags;			// changes the way the CNS handles the entity

	short	cache_node;				// last successful closest node
	float	cache_node_time;		// time of last cached node
	float	cache_valid_time;		// time a cached node is deemed valid

	short	goal_index;				// 1 + (index of the node to head for)

	csurface_t	*surface;			// current surface standing on
} nav_data_t;

// ..................................................................
// Node Creation

typedef struct
{
	int		flags;
	node_t	*current_node;			// last node dropped, or closest node
	vec3_t	old_org;
	edict_t	*old_groundentity;
	float	last_max_z;				// used for ducking/standing

	vec3_t	ducking_org;

	edict_t	*jump_ent;

	// debugging only
	edict_t	*debug_dest;
} nav_build_data_t;

// ==================================================================
// Navigation Specific variables

cvar_t	*nav_dynamic;
cvar_t	*nav_debug;
cvar_t	*nav_optimize;

cvar_t	*nav_aipath;

// ==================================================================
// Procedure Defines

// g_nav.c
void NAV_InitActiveNodes(	active_node_data_t *active_node_data);
void NAV_PurgeActiveNodes(	active_node_data_t *active_node_data);

node_t *NAV_CreateNode(	edict_t		*ent,
						vec3_t		origin,
						vec3_t		jump_vel,
						short		node_type,
						short		goal_index,
						int			waterlevel );

int NAV_OptimizeRoutes( active_node_data_t *active_node_data );

void NAV_CalculateVisible(	active_node_data_t *active_node_data, node_t *node );
int NAV_CalculateRoutes (	active_node_data_t *active_node_data, node_t *node );

qboolean NAV_Visible(	vec3_t		src,			vec3_t		dest, int vis_type, int ducking );
qboolean NAV_Reachable(	vec3_t		src,			vec3_t		dest, 
						byte		src_waterlevel,	byte		dest_waterlevel,
						int			ducking,		int reachable_type );
qboolean NAV_ClearSight ( edict_t *self, vec3_t dest, edict_t *dest_ent );

void NAV_CalcNodeSurface(	node_t *node );

node_t *NAV_GetClosestNode( edict_t *ent, int vis_type, int ignore_cached, qboolean away_from_enemy );

int NAV_Route_EntityToEntity(	edict_t *src, node_t *current_node, 
								edict_t *dest, int vis_type, int check_all_nodes, route_t *route_out );
int NAV_Route_NodeToEntity(	node_t *node, 
							edict_t *dest, int vis_type, route_t *route_out );
int NAV_Route_EntityToNode(	edict_t *src, node_t *current_node, 
							node_t *dest_node, int vis_type, int check_all_nodes, int check_direct, route_t *route_out );

void NAV_EvaluateMove( edict_t *ent );

// g_nav_io.c
void NAV_WriteActiveNodes(	active_node_data_t *active_node_data, char *unitname);
void NAV_WriteNode(FILE *f, active_node_data_t *active_node_data, node_t *node);
void NAV_ReadActiveNodes(	active_node_data_t *active_node_data, char *unitname);
void NAV_ReadNode( FILE *f, active_node_data_t *active_node_data, node_t *node);

void NAV_FindGoalEnt( node_t *node );

void NAV_CalculateDistances(active_node_data_t *active_node_data);
int NAV_CalculateRouteDistance( active_node_data_t *active_node_data, node_t *src, node_t *dest );

// g_nav_cells.c
int	 NAV_GetCellIndexForAxis(float pos);
void NAV_AddNodeToCells(active_node_data_t *active_node_data, node_t *node);

// g_nav_misc.c
void NAV_DrawLine(vec3_t sorg, vec3_t dorg);
float NAV_Debug_DrawPath(edict_t *src, edict_t *dest);
void NAV_dprintf(char *fmt, ...);

void NAV_RebuildRoutes(active_node_data_t *node_data);		// UNDER DEVELOPMENT!!

float	*NAV_GetCombatPos( edict_t *ent, edict_t *enemy, qboolean melee );
float	*NAV_GetHidePos( edict_t *ent, edict_t *enemy, int hidepos_type );
qboolean	NAV_GetAvoidDirection( edict_t *ent, edict_t *avoid, vec3_t dir );
float *NAV_GetReachableNodeOutsideBounds( edict_t *ent, vec3_t bmins, vec3_t bmaxs );
