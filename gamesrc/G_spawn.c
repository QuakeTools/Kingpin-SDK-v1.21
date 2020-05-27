#include "g_local.h"

typedef struct
{
	char	*name;
	void	(*spawn)(edict_t *ent);
} spawn_t;


void SP_item_health (edict_t *self);
void SP_item_health_small (edict_t *self);
void SP_item_health_large (edict_t *self);
void SP_item_health_mega (edict_t *self);

void SP_info_player_start (edict_t *ent);
void SP_info_player_deathmatch (edict_t *ent);
void SP_info_player_coop (edict_t *ent);
void SP_info_player_intermission (edict_t *ent);

void SP_func_plat (edict_t *ent);
void SP_func_rotating (edict_t *ent);
void SP_func_button (edict_t *ent);
void SP_func_door (edict_t *ent);
void SP_func_door_secret (edict_t *ent);
void SP_func_door_rotating (edict_t *ent);
void SP_func_water (edict_t *ent);
void SP_func_train (edict_t *ent);
void SP_func_conveyor (edict_t *self);
void SP_func_wall (edict_t *self);
void SP_func_object (edict_t *self);
void SP_func_explosive (edict_t *self);
void SP_func_timer (edict_t *self);
void SP_func_areaportal (edict_t *ent);
void SP_func_clock (edict_t *ent);
void SP_func_killbox (edict_t *ent);

void SP_trigger_always (edict_t *ent);
void SP_trigger_once (edict_t *ent);
void SP_trigger_multiple (edict_t *ent);
void SP_trigger_relay (edict_t *ent);
void SP_trigger_push (edict_t *ent);
void SP_trigger_hurt (edict_t *ent);
void SP_trigger_key (edict_t *ent);
void SP_trigger_counter (edict_t *ent);
void SP_trigger_elevator (edict_t *ent);
void SP_trigger_gravity (edict_t *ent);
void SP_trigger_monsterjump (edict_t *ent);

void SP_target_temp_entity (edict_t *ent);
void SP_target_speaker (edict_t *ent);
void SP_target_explosion (edict_t *ent);
// JOSEPH 9-APR-99
void SP_target_fire (edict_t *ent);
// END JOSEPH
void SP_target_changelevel (edict_t *ent);
void SP_target_secret (edict_t *ent);
void SP_target_goal (edict_t *ent);
void SP_target_splash (edict_t *ent);
void SP_target_spawner (edict_t *ent);
void SP_target_blaster (edict_t *ent);
void SP_target_crosslevel_trigger (edict_t *ent);
void SP_target_crosslevel_target (edict_t *ent);
void SP_target_laser (edict_t *self);
// void SP_target_help (edict_t *ent);
void SP_target_lightramp (edict_t *self);
void SP_target_earthquake (edict_t *ent);
void SP_target_character (edict_t *ent);
void SP_target_string (edict_t *ent);

void SP_worldspawn (edict_t *ent);
void SP_viewthing (edict_t *ent);

void SP_light (edict_t *self);
void SP_light_mine1 (edict_t *ent);
void SP_light_mine2 (edict_t *ent);
void SP_info_null (edict_t *self);
void SP_info_notnull (edict_t *self);
void SP_path_corner (edict_t *self);

void SP_misc_explobox (edict_t *self);
void SP_misc_gib_arm (edict_t *self);
void SP_misc_gib_leg (edict_t *self);
void SP_misc_gib_head (edict_t *self);
void SP_misc_teleporter (edict_t *self);
void SP_misc_teleporter_dest (edict_t *self);

void SP_turret_breach (edict_t *self);
void SP_turret_base (edict_t *self);
void SP_turret_driver (edict_t *self);

// RAFAEL 14-APR-98
void SP_rotating_light (edict_t *self);
void SP_object_repair (edict_t *self);
void SP_misc_crashviper (edict_t *ent);
void SP_misc_viper_missile (edict_t *self);
void SP_misc_amb4 (edict_t *ent);
void SP_target_mal_laser (edict_t *ent);
// END 14-APR-98

// cast spawns
void SP_cast_punk(edict_t *self);
void SP_cast_thug(edict_t *self);
void SP_cast_runt (edict_t *self);
void SP_cast_thug2(edict_t *self);

void SP_cast_bitch (edict_t *ent);
void SP_cast_dog (edict_t *ent);
void SP_cast_shorty (edict_t *ent);
void SP_cast_whore (edict_t *ent);

// AI stuff
void SP_ai_boundary (edict_t *ent);
void SP_ai_event_hostile (edict_t *ent);
void SP_ai_event_follow (edict_t *ent);
void SP_ai_guard (edict_t *self);
void SP_ai_territory ( edict_t *ent );
void SP_ai_trigger_character (edict_t *ent);
void SP_ai_locked_door (edict_t *ent);

// Episode specific entities
void SP_misc_skidrow_radio (edict_t *self);
void SP_misc_skidrow_ambush (edict_t *self);

// Rafael's entities
void SP_misc_smoke (edict_t *ent);
// done.

// testing models
void SP_misc_fidelA (edict_t *ent);
//void SP_misc_fidelC (edict_t *ent);
void SP_elps (edict_t *self);
void SP_misc_car (edict_t *ent);
//void SP_misc_caustic (edict_t *ent);

// done.
void SP_cast_punk_window (edict_t *ent);
void SP_refl (edict_t *ent);

//void SP_misc_fidelseg (edict_t *ent);

// JOSEPH 4-MAY-99
void SP_light_fire_esm (edict_t *ent);
void SP_light_fire_sm (edict_t *ent);
void SP_light_fire_med (edict_t *ent);
void SP_light_fire_lg (edict_t *ent);
void SP_smoke_esm (edict_t *ent);
void SP_smoke_sm (edict_t *ent);
void SP_smoke_med (edict_t *ent);
void SP_smoke_lg (edict_t *ent);
void SP_func_train_rotating (edict_t *ent);
void SP_func_subdoor_base (edict_t *ent);
void SP_func_subdoor_handle1 (edict_t *ent);
void SP_func_subdoor_handle2 (edict_t *ent);
//void SP_light_sun (edict_t *ent);
void SP_props_trashcanA (edict_t *ent);
void SP_props_trashcan_fall (edict_t *ent);
void SP_props_hydrant (edict_t *ent);
void SP_props_antenna1a (edict_t *self);
void SP_props_antenna2a (edict_t *self);
void SP_props_antenna3a (edict_t *self);
void SP_props_antenna1b (edict_t *self);
void SP_props_antenna2b (edict_t *self);
void SP_props_antenna3b (edict_t *self);
void SP_props_antenna1c (edict_t *self);
void SP_props_antenna2c (edict_t *self);
void SP_props_antenna3c (edict_t *self);
void SP_props_phone (edict_t *self);
void SP_props_aircon (edict_t *self);
void SP_props_fan (edict_t *self);
void SP_props_tablesetA (edict_t *self);
void SP_props_radio (edict_t *self);
void SP_cast_buma (edict_t *self);
void SP_cast_bumb (edict_t *self);
void SP_elements_raincloud (edict_t *self);
void SP_elements_snowcloud (edict_t *self);
void SP_misc_cutscene_trigger (edict_t *self);
void SP_misc_cutscene_camera (edict_t *self);
//void SP_props_crate (edict_t *self);
//void SP_props_crate_32 (edict_t *self);
//void SP_props_crate_48 (edict_t *self);
void SP_props_chair (edict_t *self);
void SP_props_extinguisherA (edict_t *self);
void SP_props_extinguisherB (edict_t *self);
void SP_light_sconce (edict_t *self);
void SP_props_motorcycle (edict_t *self);
void SP_props_ammocrate_bust (edict_t *self);
void SP_props_shelf (edict_t *self);
void SP_props_mattressA (edict_t *self);
void SP_props_mattressB (edict_t *self);
void SP_props_mattressC (edict_t *self);
void SP_trigger_motorcycle (edict_t *self);
void SP_props_tv (edict_t *self);
void SP_props_steam_machine (edict_t *ent);
void SP_light_bulb (edict_t *self);
void SP_props_trash (edict_t *self);
void SP_props_wall_fall (edict_t *self);
void SP_props_trashbottle (edict_t *self);
void SP_props_trashpaper (edict_t *self);
void SP_props_trashwall (edict_t *self);
void SP_props_trashcorner (edict_t *self);
void SP_props_trashbottle_vert (edict_t *self);
void SP_props_blimp (edict_t *self);
void SP_misc_use_cutscene (edict_t *self);
void SP_props_motorcycle_runaway (edict_t *self);
void SP_trigger_hurt_fire (edict_t *self);
void SP_props_shelf_fall (edict_t *self);
void SP_target_fire (edict_t *self);
void SP_props_rat (edict_t *self);
void SP_props_rat_spawner (edict_t *self);
void SP_props_rat_spawner_node (edict_t *self);
void SP_target_flamethrower (edict_t *ent);
void SP_light_pendant (edict_t *self);
void SP_light_deco_sconce (edict_t *self);
void SP_props_shelfB_fall (edict_t *self);
//void SP_props_crate_bust_sm (edict_t *self);
void SP_func_lift (edict_t *self);
void SP_props_roof_vent (edict_t *self);
void SP_props_rat_trigger (edict_t *self);
void SP_props2_truck_die (edict_t *self);
void SP_props_cola_machine (edict_t *self);
void SP_props_cig_machine (edict_t *self);
void SP_props2_barrels_fallA (edict_t *self);
void SP_props2_barrels_fallB (edict_t *self);
void SP_props2_clubcouch (edict_t *self);
void SP_props2_clubchair (edict_t *self);
void SP_props2_vaseA (edict_t *self);
void SP_props2_vaseB (edict_t *self);
void SP_props2_chair_conf (edict_t *self);
void SP_props2_shelf_metal_A_fall (edict_t *self);
void SP_props2_shelf_metal_B_fall (edict_t *self);
void SP_props2_deadguy (edict_t *self);
void SP_props2_chair_push (edict_t *self);
void SP_props_crate_bust_32 (edict_t *self);
void SP_props_crate_bust_48 (edict_t *self);
void SP_props_crate_bust_64 (edict_t *self);
// JOSEPH 8-JUN-99
void SP_props2_flag (edict_t *self);
void SP_props2_fish (edict_t *self);
void SP_props2_fish_trigger (edict_t *self);
void SP_props2_fish_spawner (edict_t *self);
void SP_props2_fish_spawner_node (edict_t *self);
void SP_props2_wall_fish (edict_t *self);
void SP_props2_barrels_fall_ST (edict_t *self);
void SP_props2_sign (edict_t *self);
void SP_props2_lighthouse_beam (edict_t *self);
void SP_props2_boat (edict_t *self);
void SP_props2_buoy (edict_t *self);
void SP_props2_buoy_side (edict_t *self);
void SP_props2_deadguy_underwater (edict_t *self);
void SP_props2_buoy_animate (edict_t *self);
void SP_props2_gargoyle (edict_t *self);
void SP_props2_clothesline (edict_t *self);
void SP_props2_plant_XL (edict_t *self);
void SP_props2_plant_SM (edict_t *self);
void SP_props2_boatphone (edict_t *self);
void SP_props2_ashtray (edict_t *self);
void SP_props2_lunch (edict_t *self);
void SP_props2_deadgal_headless (edict_t *self);
void SP_props2_plant_bush (edict_t *self);
void SP_props2_boat_animate (edict_t *self);
void SP_props2_helicopter_animate (edict_t *self);
void SP_props2_car_animate (edict_t *self);
void SP_props2_car_topup (edict_t *self);
void SP_props2_car_topdown (edict_t *self);
void SP_props2_plant_fern (edict_t *self);
void SP_props2_pinball_machine (edict_t *self);
void SP_props2_barrels_PV_A (edict_t *self);
void SP_props2_barrels_PV_C (edict_t *self);
void SP_props2_barrels_PV_D (edict_t *self);
void SP_props2_barrels_PV_E (edict_t *self);
void SP_props2_barrels_PV_F (edict_t *self);
void SP_light_chandelier (edict_t *self);
void SP_props2_air_train (edict_t *self);
void SP_props3_dead_louie (edict_t *self);
void SP_props3_cut_boss_player_animate (edict_t *self);
void SP_props3_deco_fixture (edict_t *self);
void SP_props3_cut_boss_chick_animate (edict_t *self);
void SP_props3_cut_train_run_animate (edict_t *self);
void SP_props3_cut_A_animate (edict_t *self);
void SP_props3_cut_B_animate (edict_t *self);
void SP_props3_cut_C_animate (edict_t *self);
void SP_props3_cut_D_animate (edict_t *self);
void SP_props3_cash_counter_animate (edict_t *self);
// JOSEPH 11-JUN-99-C
void SP_props2_barrels_PV_B (edict_t *self);
void SP_props3_decanter (edict_t *self);
void SP_props3_whiskey_glass (edict_t *self);
void SP_props3_barrels_fall_nikki_A (edict_t *self);
void SP_props3_barrels_fall_nikki_B (edict_t *self);
void SP_props3_cut_run_to_car_animate (edict_t *self);
void SP_props3_cut_final_animate (edict_t *self);
void SP_props3_cash (edict_t *self);
void SP_props3_cut_truck_driver (edict_t *self);
void SP_props3_cut_pinball_guy_animate (edict_t *self);
// END JOSEPH

void SP_path_corner_cast (edict_t *self);
void SP_misc_alarm (edict_t *ent);

void SP_ai_safespot (edict_t *ent);
void SP_ai_reset (edict_t *ent);
void SP_ai_combat_spot (edict_t *self);

void SP_junior (edict_t *ent);

void SP_misc_skidrow_afraid (edict_t *self);

void SP_misc_steeltown_afraid (edict_t *self);

void SP_misc_barry_fidelc_maya (edict_t *self);

void SP_misc_corky_fidel_mdx_pcx (edict_t *self);
void SP_misc_corky_fidel_mdx_tga (edict_t *self);

void SP_misc_cut_scene (edict_t *self);

void SP_pawn_o_matic (edict_t *self);

// weapon mods
void SP_pistol_mod_damage (edict_t *self);
void SP_pistol_mod_rof (edict_t *self);
void SP_pistol_mod_reload (edict_t *self);

void SP_trigger_unlock (edict_t *self);

void SP_sfx_beacon (edict_t *self);

void SP_misc_skidrow_radio_repeater (edict_t *self);

// void SP_immortal_hostility (edict_t *self);

void SP_cast_bum_sit (edict_t *self);
void SP_trigger_hurt_electric (edict_t *self);
void SP_hmg_mod_cooling (edict_t *self);

void SP_misc_pv_afraid (edict_t *self);

void SP_misc_ty_afraid (edict_t *self);
void SP_ty_mo_boundry (edict_t *self);
void SP_sy_dykes_boundry (edict_t *ent);
void SP_misc_sy_afraid (edict_t *self);

void SP_misc_kroker_afraid (edict_t *self);

void SP_rc_initiation_observer (edict_t *self);
void SP_rc_initiation_brush ( edict_t *ent );
void SP_ty_fuseblown ( edict_t *ent );
void SP_moker_notinoffice ( edict_t *ent );

void SP_ep_skidrow_flag (edict_t *ent);
void SP_sy_oilcan ( edict_t *ent );
void SP_ty_valvehandle ( edict_t *ent );

void SP_pv_fuse_blown1 (edict_t *ent);
void SP_pv_fuse_blown2 (edict_t *ent);
void SP_pv_deadlouie (edict_t *ent);
void SP_sy_blefty (edict_t *ent);

spawn_t	spawns[] = {
	{"item_health", SP_item_health},
	{"item_health_small", SP_item_health_small},
	{"item_health_large", SP_item_health_large},
	{"item_health_mega", SP_item_health_mega},

	{"info_player_start", SP_info_player_start},
	{"info_player_deathmatch", SP_info_player_deathmatch},
	{"info_player_coop", SP_info_player_coop},
	{"info_player_intermission", SP_info_player_intermission},

	{"func_plat", SP_func_plat},
	{"func_button", SP_func_button},
	{"func_door", SP_func_door},
	{"func_door_secret", SP_func_door_secret},
	{"func_door_rotating", SP_func_door_rotating},
	{"func_rotating", SP_func_rotating},
	{"func_train", SP_func_train},
	{"func_water", SP_func_water},
	{"func_conveyor", SP_func_conveyor},
	{"func_areaportal", SP_func_areaportal},
	{"func_clock", SP_func_clock},
	{"func_wall", SP_func_wall},
	{"func_object", SP_func_object},
	{"func_timer", SP_func_timer},
	{"func_explosive", SP_func_explosive},
	{"func_killbox", SP_func_killbox},

	// RAFAEL
	{"func_object_repair", SP_object_repair},
	{"rotating_light", SP_rotating_light},
	
	{"trigger_always", SP_trigger_always},
	{"trigger_once", SP_trigger_once},
	{"trigger_multiple", SP_trigger_multiple},
	{"trigger_relay", SP_trigger_relay},
	{"trigger_push", SP_trigger_push},
	{"trigger_hurt", SP_trigger_hurt},
	{"trigger_key", SP_trigger_key},
	{"trigger_counter", SP_trigger_counter},
	{"trigger_elevator", SP_trigger_elevator},
	{"trigger_gravity", SP_trigger_gravity},
	{"trigger_monsterjump", SP_trigger_monsterjump},

	{"target_temp_entity", SP_target_temp_entity},
	{"target_speaker", SP_target_speaker},
	{"target_explosion", SP_target_explosion},
	{"target_changelevel", SP_target_changelevel},
	{"target_secret", SP_target_secret},
	{"target_goal", SP_target_goal},
	{"target_splash", SP_target_splash},
	{"target_spawner", SP_target_spawner},
	{"target_blaster", SP_target_blaster},
	{"target_crosslevel_trigger", SP_target_crosslevel_trigger},
	{"target_crosslevel_target", SP_target_crosslevel_target},
	{"target_laser", SP_target_laser},
// 	{"target_help", SP_target_help},
	{"target_lightramp", SP_target_lightramp},
	{"target_earthquake", SP_target_earthquake},
	{"target_character", SP_target_character},
	{"target_string", SP_target_string},

	// RAFAEL 15-APR-98
	{"target_mal_laser", SP_target_mal_laser},


	{"worldspawn", SP_worldspawn},
	{"viewthing", SP_viewthing},

	{"light", SP_light},
	{"light_mine1", SP_light_mine1},
	{"light_mine2", SP_light_mine2},
	{"info_null", SP_info_null},
	{"func_group", SP_info_null},
	{"info_notnull", SP_info_notnull},
	{"path_corner", SP_path_corner},

	// RAFAEL 11-05-98
	{"junior", SP_junior},
	// END 11-05-98

	{"misc_explobox", SP_misc_explobox},
	{"misc_gib_arm", SP_misc_gib_arm},
	{"misc_gib_leg", SP_misc_gib_leg},
	{"misc_gib_head", SP_misc_gib_head},
	{"misc_teleporter", SP_misc_teleporter},
	{"misc_teleporter_dest", SP_misc_teleporter_dest},
	{"misc_amb4", SP_misc_amb4},

// Ridah, character spawns
	{"cast_punk", SP_cast_punk},
	{"cast_thug", SP_cast_thug},
	{"cast_thug_sit", SP_cast_thug2},
	{"cast_bitch", SP_cast_bitch},
	{"cast_dog", SP_cast_dog},
// Ridah, done.

	{"cast_runt", SP_cast_runt},
	{"cast_bum_sit", SP_cast_bum_sit},
	{"cast_shorty", SP_cast_shorty},
	{"cast_whore", SP_cast_whore},

	{"cast_punk_window", SP_cast_punk_window},
	{"cast_punk2", SP_cast_thug},				// just for backwards compatibility
	{"cast_rosie", SP_cast_bitch},

	// AI stuff
	{"ai_boundary", SP_ai_boundary},
	{"ai_event_hostile", SP_ai_event_hostile},
	{"ai_event_follow", SP_ai_event_follow},
	{"ai_guard", SP_ai_guard},
	{"ai_territory", SP_ai_territory},
	{"ai_trigger_character", SP_ai_trigger_character},
	{"ai_locked_door", SP_ai_locked_door},

	// Episode specific entities
	{"misc_skidrow_radio", SP_misc_skidrow_radio},
	{"misc_skidrow_ambush", SP_misc_skidrow_ambush},

	{"misc_skidrow_radio_repeater", SP_misc_skidrow_radio_repeater},
	{"ai_ty_fuseblown", SP_ty_fuseblown},
	{"ai_moker_notinoffice", SP_moker_notinoffice},
// Ridah, for testing purposes only!!
	{"misc_grunt", SP_cast_thug},
	{"misc_fidelA", SP_misc_fidelA},
	{"misc_car", SP_misc_car},
// Ridah done.

// Rafael's entities
	{"misc_smoke", SP_misc_smoke},
	{"elps", SP_elps},
//	{"misc_caustic", SP_misc_caustic},
	{"misc_alarm", SP_misc_alarm},
// done.

	{"trigger_hurt_electric",SP_trigger_hurt_electric},

	// {"immortal_hostility",SP_immortal_hostility},

	{"pawn_o_matic", SP_pawn_o_matic},

	{"ai_safespot", SP_ai_safespot},
	{"misc_skidrow_ai_reset", SP_ai_reset},
	{"ai_combat_spot",SP_ai_combat_spot},
	{"misc_skidrow_afraid", SP_misc_skidrow_afraid},
	{"misc_steeltown_afraid", SP_misc_steeltown_afraid},
	{"misc_kroker_afraid", SP_misc_kroker_afraid},

	{"rc_initiation_observer", SP_rc_initiation_observer},
	{"rc_initiation_brush", SP_rc_initiation_brush},

	{"misc_pv_afraid", SP_misc_pv_afraid},
	{"misc_ty_afraid", SP_misc_ty_afraid},
	{"ai_ty_mo_boundry", SP_ty_mo_boundry},
	{"ai_sy_dykes_boundry", SP_sy_dykes_boundry},
	{"misc_sy_afraid", SP_misc_sy_afraid},

	{"ep_skidrow_flag", SP_ep_skidrow_flag},
	{"ai_sy_oilcan", SP_sy_oilcan},
	{"ai_ty_valvehandle", SP_ty_valvehandle},
	{"ai_pv_fuseblown1", SP_pv_fuse_blown1},
	{"ai_pv_fuseblown2", SP_pv_fuse_blown2},
	{"ai_pv_deadlouie", SP_pv_deadlouie},

	{"ai_sy_blefty", SP_sy_blefty},

	{"misc_barry_bitch", SP_misc_barry_fidelc_maya},


	{"misc_corky_fidel_mdx_pcx", SP_misc_corky_fidel_mdx_pcx},
	{"misc_corky_fidel_mdx_tga", SP_misc_corky_fidel_mdx_tga},

	{"misc_cut_scene", SP_misc_cut_scene},

// Joseph's entities
// JOSEPH 4-MAY-99
	{"light_fire_esm",SP_light_fire_esm},
	{"light_fire_sm",SP_light_fire_sm},
	{"light_fire_med",SP_light_fire_med},
	{"light_fire_lg",SP_light_fire_lg},
	{"smoke_esm",SP_smoke_esm},
	{"smoke_sm",SP_smoke_sm},
	{"smoke_med",SP_smoke_med},
	{"smoke_lg",SP_smoke_lg},
	{"func_train_rotating", SP_func_train_rotating},
	{"func_subdoor_base", SP_func_subdoor_base},
	{"func_subdoor_handle1", SP_func_subdoor_handle1},
	{"func_subdoor_handle2", SP_func_subdoor_handle2},
	{"props_trashcanA", SP_props_trashcanA},
	{"props_trashcan_fall", SP_props_trashcan_fall},
	{"props_hydrant", SP_props_hydrant},
    {"props_antenna1a", SP_props_antenna1a},
    {"props_antenna1b", SP_props_antenna1b},
    {"props_antenna1c", SP_props_antenna1c},
    {"props_antenna2a", SP_props_antenna2a},
    {"props_antenna2b", SP_props_antenna2b},
    {"props_antenna2c", SP_props_antenna2c},
    {"props_antenna3a", SP_props_antenna3a},
    {"props_antenna3b", SP_props_antenna3b},
    {"props_antenna3c", SP_props_antenna3c},
    {"props_fan", SP_props_fan},
    {"props_phone", SP_props_phone},
	{"props_aircon", SP_props_aircon},
    {"props_tablesetA", SP_props_tablesetA},
    {"props_radio", SP_props_radio},
	{"cast_buma", SP_cast_buma},
	{"cast_bumb", SP_cast_bumb},
	{"elements_raincloud", SP_elements_raincloud},
	{"elements_snowcloud", SP_elements_snowcloud},
    {"misc_cutscene_trigger", SP_misc_cutscene_trigger},
    {"misc_cutscene_camera", SP_misc_cutscene_camera},
	//{"props_crate", SP_props_crate},
	//{"props_crate_32", SP_props_crate_32},
	//{"props_crate_48", SP_props_crate_48},
	{"trigger_unlock", SP_trigger_unlock},
    {"props_chair", SP_props_chair},
    {"props_extinguisherA", SP_props_extinguisherA},
    {"props_extinguisherB", SP_props_extinguisherB},
    {"light_sconce", SP_light_sconce},
    {"props_motorcycle", SP_props_motorcycle},
	{"props_ammocrate_bust", SP_props_ammocrate_bust},
	{"props_shelf", SP_props_shelf},
    {"props_mattressA", SP_props_mattressA},
    {"props_mattressB", SP_props_mattressB},
    {"props_mattressC", SP_props_mattressC},
	{"trigger_motorcycle", SP_trigger_motorcycle},
    {"props_tv", SP_props_tv},
    {"props_steam_machine", SP_props_steam_machine},
	{"light_bulb", SP_light_bulb},
    {"props_trash", SP_props_trash},
    {"props_wall_fall", SP_props_wall_fall},
    {"props_trashbottle", SP_props_trashbottle},
    {"props_trashwall", SP_props_trashwall},
    {"props_trashpaper", SP_props_trashpaper},
    {"props_trashcorner", SP_props_trashcorner},
    {"props_trashbottle_vert", SP_props_trashbottle_vert},
    {"props_blimp", SP_props_blimp},
    {"misc_use_cutscene", SP_misc_use_cutscene},
    {"props_motorcycle_runaway", SP_props_motorcycle_runaway},
    {"trigger_hurt_fire", SP_trigger_hurt_fire},
	{"props_shelf_fall", SP_props_shelf_fall},	
	{"target_fire", SP_target_fire},
	{"props_rat", SP_props_rat},
    {"props_rat_spawner", SP_props_rat_spawner},
    {"props_rat_spawner_node", SP_props_rat_spawner_node},
	{"target_flamethrower", SP_target_flamethrower},
    {"light_deco_sconce", SP_light_deco_sconce},
    {"light_pendant", SP_light_pendant},
	{"props_shelfB_fall", SP_props_shelfB_fall},
    //{"props_crate_bust_sm", SP_props_crate_bust_sm},
	{"func_lift", SP_func_lift},
	{"props_roof_vent", SP_props_roof_vent},
	{"props_rat_trigger", SP_props_rat_trigger},
	{"props2_truck_die", SP_props2_truck_die},
    {"props_cola_machine", SP_props_cola_machine},
	{"props_cig_machine", SP_props_cig_machine},
    {"props2_barrels_fallA", SP_props2_barrels_fallA},
	{"props2_barrels_fallB", SP_props2_barrels_fallB},
	{"props2_clubcouch", SP_props2_clubcouch},
	{"props2_clubchair", SP_props2_clubchair},
    {"props2_vaseA", SP_props2_vaseA},
    {"props2_vaseB", SP_props2_vaseB},
	{"props2_chair_conf", SP_props2_chair_conf},
	{"props2_shelf_metal_A_fall", SP_props2_shelf_metal_A_fall},
	{"props2_shelf_metal_B_fall", SP_props2_shelf_metal_B_fall},
	{"props2_deadguy", SP_props2_deadguy},
	{"props2_chair_push", SP_props2_chair_push},
	{"props_crate_bust_32", SP_props_crate_bust_32},
	{"props_crate_bust_48", SP_props_crate_bust_48},
	{"props_crate_bust_64", SP_props_crate_bust_64},
	// JOSEPH 8-JUN-99
	{"props2_flag", SP_props2_flag},
	{"props2_fish", SP_props2_fish},
	{"props2_fish_trigger", SP_props2_fish_trigger},
	{"props2_fish_spawner", SP_props2_fish_spawner},
	{"props2_fish_spawner_node", SP_props2_fish_spawner_node},
	{"props2_wall_fish", SP_props2_wall_fish},
	{"props2_barrels_fall_ST", SP_props2_barrels_fall_ST},
	{"props2_sign", SP_props2_sign},
	{"props2_lighthouse_beam", SP_props2_lighthouse_beam},
	{"props2_boat", SP_props2_boat},
	{"props2_buoy", SP_props2_buoy},
	{"props2_buoy_side", SP_props2_buoy_side},
	{"props2_deadguy_underwater", SP_props2_deadguy_underwater},
    {"props2_buoy_animate", SP_props2_buoy_animate},
	{"props2_gargoyle", SP_props2_gargoyle},
    {"props2_clothesline", SP_props2_clothesline},
	{"props2_plant_XL", SP_props2_plant_XL},
	{"props2_plant_SM", SP_props2_plant_SM},
	{"props2_boatphone", SP_props2_boatphone},
	{"props2_ashtray", SP_props2_ashtray},
	{"props2_lunch", SP_props2_lunch},
	{"props2_deadgal_headless", SP_props2_deadgal_headless},
	{"props2_plant_bush", SP_props2_plant_bush},
	{"props2_boat_animate", SP_props2_boat_animate},
    {"props2_helicopter_animate", SP_props2_helicopter_animate},
    {"props2_car_animate", SP_props2_car_animate},
	{"props2_car_topdown", SP_props2_car_topdown},
	{"props2_car_topup", SP_props2_car_topup},
	{"props2_plant_fern", SP_props2_plant_fern},
	{"props2_pinball_machine", SP_props2_pinball_machine},
	{"props2_barrels_PV_A", SP_props2_barrels_PV_A},
	{"props2_barrels_PV_C", SP_props2_barrels_PV_C},
	{"props2_barrels_PV_D", SP_props2_barrels_PV_D},
	{"props2_barrels_PV_E", SP_props2_barrels_PV_E},
	{"props2_barrels_PV_F", SP_props2_barrels_PV_F},
	{"light_chandelier", SP_light_chandelier},
	{"props2_air_train", SP_props2_air_train},
	{"props3_dead_louie", SP_props3_dead_louie},
	{"props3_cut_boss_player_animate", SP_props3_cut_boss_player_animate},
	{"props3_deco_fixture", SP_props3_deco_fixture},
	{"props3_cut_boss_chick_animate", SP_props3_cut_boss_chick_animate},
	{"props3_cut_train_run_animate", SP_props3_cut_train_run_animate},
	{"props3_cut_A_animate", SP_props3_cut_A_animate},
	{"props3_cut_B_animate", SP_props3_cut_B_animate},
	{"props3_cut_C_animate", SP_props3_cut_C_animate},
	{"props3_cut_D_animate", SP_props3_cut_D_animate},
	{"props3_cash_counter_animate", SP_props3_cash_counter_animate},
	// JOSEPH 11-JUN-99-C
	{"props2_barrels_PV_B", SP_props2_barrels_PV_B},
	{"props3_decanter", SP_props3_decanter},
	{"props3_whiskey_glass", SP_props3_whiskey_glass},	
	{"props3_barrels_fall_nikki_A", SP_props3_barrels_fall_nikki_A},
	{"props3_barrels_fall_nikki_B", SP_props3_barrels_fall_nikki_B},
    {"props3_cut_run_to_car_animate", SP_props3_cut_run_to_car_animate},
	{"props3_cut_final_animate", SP_props3_cut_final_animate},
	{"props3_cash", SP_props3_cash},
	{"props3_cut_truck_driver", SP_props3_cut_truck_driver},	
	{"props3_cut_pinball_guy_animate", SP_props3_cut_pinball_guy_animate},
	// END JOSEPH

	{"lightflare", SP_light},
	{"path_corner_cast", SP_path_corner_cast},

// weapon mods
	{"pistol_mod_damage",SP_pistol_mod_damage},
	{"pistol_mod_rof",SP_pistol_mod_rof},
	{"pistol_mod_reload",SP_pistol_mod_reload},
	{"hmg_mod_cooling",SP_hmg_mod_cooling},

	{"sfx_beacon", SP_sfx_beacon},

	{"refl", SP_refl},

	// Teamplay spawns
	{"dm_cashspawn", SP_dm_cashspawn},
	{"dm_safebag", SP_dm_safebag},
	{"dm_props_banner", SP_dm_props_banner},

	{NULL, NULL}
};

/*
===============
ED_CallSpawn

Finds the spawn function for the entity and calls it
===============
*/
void ED_CallSpawn (edict_t *ent)
{
	spawn_t	*s;
	gitem_t	*item;
	int		i;

	if (!ent->classname)
	{
		gi.dprintf ("ED_CallSpawn: NULL classname\n");
		return;
	}

if (!stricmp( ent->classname, "weapon_barmachinegun" ))
{
gi.dprintf("Hacking old BAR machine gun to grenade launcher for KPDM1-cash.bsp\n" );
sprintf( ent->classname, "weapon_grenadelauncher" );
}


	// Ridah: hack, KPDM1 has "item_flametank" which are now "ammo_flametank"
	if (!strcmp( ent->classname, "item_flametank" ))
		strcpy( ent->classname, "ammo_flametank" );


	// check item spawn functions
	for (i=0,item=itemlist ; i<game.num_items ; i++,item++)
	{
		if (!item->classname)
			continue;
		if (!strcmp(item->classname, ent->classname))
		{	// found it
			SpawnItem (ent, item);
			return;
		}
	}

	// check normal spawn functions
	// JOSEPH 17-MAR-99-B
	for (s=spawns ; s->name ; s++)
	{
		if (!strcmp(s->name, ent->classname))
		{	// found it
	
			cvar_t	*props; 
			
			s->spawn (ent);

			// Special light
			if ((ent->lightit > 0) && (ent->lightit < 32) && (!(ent->s.renderfx2&31)))
			{
				ent->s.renderfx2 &= ~RF2_DIR_LIGHTS;
				ent->s.renderfx2 |= RF2_PASSLIGHT;
				ent->s.renderfx2 |= ent->lightit;
			}			

			props = gi.cvar("props", "1", CVAR_ARCHIVE);
			
			// JOSEPH 13-APR-99
			ent->savesolid = ent->solid;				
		
			if ((ent->option) && (!props->value))
			{
				ent->svflags |= SVF_NOCLIENT;				
				ent->solid = SOLID_NOT;
			}
			// END JOSEPH
			
			// JOSEPH 19-MAR-99
			if (ent->noshadow)
			{
				ent->s.renderfx2 &= ~RF2_NOSHADOW;				
			}			
			// END JOSEPH

			return;
		}
	}
	// END JOSEPH
	
	gi.dprintf ("%s doesn't have a spawn function\n", ent->classname);

	G_FreeEdict(ent);
}

/*
=============
ED_NewString
=============
*/
char *ED_NewString (char *string)
{
	char	*newb, *new_p;
	int		i,l;
	
	l = strlen(string) + 1;

	newb = gi.TagMalloc (l, TAG_LEVEL);

	new_p = newb;

	for (i=0 ; i< l ; i++)
	{
		if (string[i] == '\\' && i < l-1)
		{
			i++;
			if (string[i] == 'n')
				*new_p++ = '\n';
			else
				*new_p++ = '\\';
		}
		else
			*new_p++ = string[i];
	}
	
	return newb;
}




/*
===============
ED_ParseField

Takes a key/value pair and sets the binary values
in an edict
===============
*/
void ED_ParseField (char *key, char *value, edict_t *ent)
{
	field_t	*f;
	byte	*b;
	float	v;
	vec3_t	vec;

	for (f=fields ; f->name ; f++)
	{
		if (!(f->flags & FFL_NOSPAWN) && !Q_stricmp(f->name, key))
		{	// found it
			if (f->flags & FFL_SPAWNTEMP)
				b = (byte *)&st;
			else
				b = (byte *)ent;

			switch (f->type)
			{
			case F_LSTRING:
				*(char **)(b+f->ofs) = ED_NewString (value);
				break;
			case F_VECTOR:
				sscanf (value, "%f %f %f", &vec[0], &vec[1], &vec[2]);
				((float *)(b+f->ofs))[0] = vec[0];
				((float *)(b+f->ofs))[1] = vec[1];
				((float *)(b+f->ofs))[2] = vec[2];
				break;
			case F_INT:
				*(int *)(b+f->ofs) = atoi(value);
				break;
			case F_FLOAT:
				*(float *)(b+f->ofs) = atof(value);
				break;
			case F_ANGLEHACK:
				v = atof(value);
				((float *)(b+f->ofs))[0] = 0;
				((float *)(b+f->ofs))[1] = v;
				((float *)(b+f->ofs))[2] = 0;
				break;
			case F_IGNORE:
				break;
			}
			return;
		}
	}
	gi.dprintf ("%s is not a field\n", key);
}

/*
====================
ED_ParseEdict

Parses an edict out of the given string, returning the new position
ed should be a properly initialized empty edict.
====================
*/
char *ED_ParseEdict (char *data, edict_t *ent)
{
	qboolean	init;
	char		keyname[256];
	char		*com_token;

	init = false;
	memset (&st, 0, sizeof(st));

// go through all the dictionary pairs
	while (1)
	{	
	// parse key
		com_token = COM_Parse (&data);
		if (com_token[0] == '}')
			break;
		if (!data)
			gi.error ("ED_ParseEntity: EOF without closing brace");

		strncpy (keyname, com_token, sizeof(keyname)-1);
		
	// parse value	
		com_token = COM_Parse (&data);
		if (!data)
			gi.error ("ED_ParseEntity: EOF without closing brace");

		if (com_token[0] == '}')
			gi.error ("ED_ParseEntity: closing brace without data");

		init = true;	

	// keynames with a leading underscore are used for utility comments,
	// and are immediately discarded by quake

		if (keyname[0] == '_')
		if (strcmp(keyname, "_color"))	// Ridah, let color through for model lighting
			continue;

		ED_ParseField (keyname, com_token, ent);
	}

	if (!init)
		memset (ent, 0, sizeof(*ent));

	return data;
}


// JOSEPH 20-NOV-98
/*
================
G_FindTeams

Chain together all entities with a matching team field.

All but the first will have the FL_TEAMSLAVE flag set.
All but the last will have the teamchain field set to the next one
================
*/
void G_FindTeams (void)
{
	edict_t	*e, *e2, *chain;
	int		i, j;
	int		c, c2;

	c = 0;
	c2 = 0;
	for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
	{
		if (!e->inuse)
			continue;
		if (!e->team)
			continue;
		if (e->flags & FL_TEAMSLAVE)
			continue;
		chain = e;
		e->teammaster = e;
		c++;
		c2++;
		for (j=i+1, e2=e+1 ; j < globals.num_edicts ; j++,e2++)
		{
			if (!e2->inuse)
				continue;
			if (!e2->team)
				continue;
			if (e2->flags & FL_TEAMSLAVE)
				continue;
			if (!strcmp(e->team, e2->team))
			{
				c2++;
				chain->teamchain = e2;
				e2->teammaster = e;
				chain = e2;
				e2->flags |= FL_TEAMSLAVE;
			}
		}
	}

	gi.dprintf ("%i teams with %i entities\n", c, c2);

	c = 0;
	for (i=1, e=g_edicts+i ; i < globals.num_edicts ; i++,e++)
	{
		if (!e->inuse)
			continue;
		if (!e->missteam)
			continue;
		if (!e->misstime)
			continue;
		for (j=1, e2=g_edicts+j ; j < globals.num_edicts ; j++,e2++)
		{
			if (!e2->inuse)
				continue;
			if (!e2->missteam)
				continue;
			if (e2->misstime)
				continue;
			e->missent = e2;
			c++;
			break;
		}
	}	

	gi.dprintf ("%i special teams\n", c);
}
// END JOSEPH

/*
==============
SpawnEntities

Creates a server's entity / program execution context by
parsing textual entity definitions out of an ent file.
==============
*/

// Ridah 5-8-99
char	last_changelevel[64];
extern void LightConfigstrings ();

void SpawnEntities (char *mapname, char *entities, char *spawnpoint)
{
	edict_t		*ent;
	int			inhibit;
	char		*com_token;
	int			i;
	float		skill_level;

	skill_level = floor (skill->value);
	if (skill_level < 0)
		skill_level = 0;
	if (skill_level > 4)
		skill_level = 4;
	if (skill->value != skill_level)
		gi.cvar_forceset("skill", va("%f", skill_level));

	SaveClientData ();

// BEGIN:	Xatrix/Ridah/Navigator/21-mar-1998
	NAV_PurgeActiveNodes (level.node_data);					
// END:		Xatrix/Ridah/Navigator/21-mar-1998

	gi.FreeTags (TAG_LEVEL);
	gi.ClearObjectBoundsCached();	// make sure we wipe the cached list

	memset (&level, 0, sizeof(level));
	memset (g_edicts, 0, game.maxentities * sizeof (g_edicts[0]));

	strncpy (level.mapname, mapname, sizeof(level.mapname)-1);
	strncpy (game.spawnpoint, spawnpoint, sizeof(game.spawnpoint)-1);

	// Ridah 5-8-99, if the spawnpoint starts with "pawn_" only retain it if we have just come from a "pawn_" level
	//	ie. not if we just died
	if (	(strstr(game.spawnpoint, "pawn_") == game.spawnpoint)
		&&	(!last_changelevel || strstr(last_changelevel, "pawn_") != last_changelevel))
	{	// clear it
		game.spawnpoint[0] = '\0';
	}

	// now clear the changelevel string for next time
	last_changelevel[0] = '\0';
	// done.

	num_object_bounds = 0;
	memset (g_objbnds, 0, sizeof(g_objbnds));

// BEGIN:	Xatrix/Ridah/Navigator/19-mar-1998
	// create the node data structure
	level.node_data = gi.TagMalloc (sizeof (active_node_data_t), TAG_GAME);
// END:		Xatrix/Ridah/Navigator/19-mar-1998

	// set client fields on player ents
	for (i=0 ; i<game.maxclients ; i++)
		g_edicts[i+1].client = game.clients + i;

	ent = NULL;
	inhibit = 0;

// parse ents
	while (1)
	{
		// parse the opening brace	
		com_token = COM_Parse (&entities);
		if (!entities)
			break;
		if (com_token[0] != '{')
			gi.error ("ED_LoadFromFile: found %s when expecting {",com_token);

		if (!ent)
			ent = g_edicts;
		else
			ent = G_Spawn ();
		entities = ED_ParseEdict (entities, ent);

		// yet another map hack
		if (!stricmp(level.mapname, "command") && !stricmp(ent->classname, "trigger_once") && !stricmp(ent->model, "*27"))
			ent->spawnflags &= ~SPAWNFLAG_NOT_HARD;

		// remove things (except the world) from different skill levels or deathmatch
		if (ent != g_edicts)
		{
			if (deathmatch->value)
			{
				if ( ent->spawnflags & SPAWNFLAG_NOT_DEATHMATCH )
				{
					G_FreeEdict (ent);	
					inhibit++;
					continue;
				}
			}
			else
			{
				if ( /* ((coop->value) && (ent->spawnflags & SPAWNFLAG_NOT_COOP)) || */
					((skill->value == 0) && (ent->spawnflags & SPAWNFLAG_NOT_EASY)) ||
					((skill->value == 1) && (ent->spawnflags & SPAWNFLAG_NOT_MEDIUM)) ||
					(((skill->value == 2) || (skill->value >= 3)) && (ent->spawnflags & SPAWNFLAG_NOT_HARD))
					)
					{
						G_FreeEdict (ent);	
						inhibit++;
						continue;
					}
			}

			ent->spawnflags &= ~(SPAWNFLAG_NOT_EASY|SPAWNFLAG_NOT_MEDIUM|SPAWNFLAG_NOT_HARD|SPAWNFLAG_NOT_COOP|SPAWNFLAG_NOT_DEATHMATCH);
		}

		ED_CallSpawn (ent);
	}	


// Ridah, HACK, fix spawn spots in team_towers
	if (!strcmp( level.mapname, "team_towers" ))
	{
		edict_t *sp;

		sp = G_Spawn();
		sp->classname = G_CopyString( "info_player_deathmatch" );
		VectorSet( sp->s.origin, 928, -96, 32 );
		sp->s.angles[YAW] = 90;
		ED_CallSpawn( sp );

		sp = G_Spawn();
		sp->classname = G_CopyString( "info_player_deathmatch" );
		VectorSet( sp->s.origin, -944, -944, -32 );
		sp->s.angles[YAW] = 180;
		ED_CallSpawn( sp );

		sp = G_Spawn();
		sp->classname = G_CopyString( "info_player_deathmatch" );
		VectorSet( sp->s.origin, 320, 936, -32 );
		sp->s.angles[YAW] = 90;
		ED_CallSpawn( sp );

		sp = G_Spawn();
		sp->classname = G_CopyString( "info_player_deathmatch" );
		VectorSet( sp->s.origin, -1232, -944, -32 );
		sp->s.angles[YAW] = 0;
		ED_CallSpawn( sp );

		sp = G_Spawn();
		sp->classname = G_CopyString( "info_player_deathmatch" );
		VectorSet( sp->s.origin, 416, 1344, -32 );
		sp->s.angles[YAW] = 180;
		ED_CallSpawn( sp );

		sp = G_Spawn();
		sp->classname = G_CopyString( "info_player_deathmatch" );
		VectorSet( sp->s.origin, 1184, -672, 40 );
		sp->s.angles[YAW] = 180;
		ED_CallSpawn( sp );

		sp = G_Spawn();
		sp->classname = G_CopyString( "info_player_deathmatch" );
		VectorSet( sp->s.origin, -1184, -288, 256 );
		sp->s.angles[YAW] = 270;
		ED_CallSpawn( sp );

	// modifications
		sp = NULL;
		while (sp = G_Find( sp, FOFS(classname), "info_player_deathmatch" ))
		{
			if (VectorDistance( sp->s.origin, tv(552, -1704, 216) ) < 1)
			{
				sp->style = 2;
				break;
			}
		}
	}
	if (!strcmp( level.mapname, "team_rival" ))
	{
		edict_t *sp;

	// modifications
		sp = NULL;
		while (sp = G_Find( sp, FOFS(classname), "info_player_deathmatch" ))
		{
			if (VectorDistance( sp->s.origin, tv(-736, 2272, 288) ) < 1)
			{
				sp->style = 2;
				break;
			}
		}
	}
// done.

	gi.dprintf ("%i entities inhibited\n", inhibit);

#ifdef DEBUG
	i = 1;
	ent = EDICT_NUM(i);
	while (i < globals.num_edicts) {
		if (ent->inuse != 0 && ent->inuse != 1)
			Com_DPrintf("Invalid entity %d\n", i);
		i++, ent++;
	}
#endif

	// Ridah, setup client-side Juniors
	LightConfigstrings ();

	G_FindTeams ();

// BEGIN:	Xatrix/Ridah/Navigator/19-mar-1998
	NAV_ReadActiveNodes (level.node_data, level.mapname);
// END:		Xatrix/Ridah/Navigator/19-mar-1998

	// RAFAEL
	MDX_Bbox_Init ();

}


//===================================================================

#if 0
	// cursor positioning
	xl <value>
	xr <value>
	yb <value>
	yt <value>
	xv <value>
	yv <value>

	// drawing
	statpic <name>
	pic <stat>
	num <fieldwidth> <stat>
	string <stat>

	// control
	if <stat>
	ifeq <stat> <value>
	ifbit <stat> <value>
	endif

#endif

// JOSEPH 15-FEB-99
char *single_statusbar = 
"yb	-24 "

// health
"xv	0 "
"hnum "
"xv	50 "
"pic 0 "

// ammo
// JOSEPH 25-JAN-99
"if 2 "
"	xv	100 "
"	anum 2 "
"	xv	150 "
"	pic 2 "
"endif "
// END JOSEPH


// RAFAEL 
// weapon clip
"if 2 "
"	xv	160 "
"	wanum "
"endif "

// JOSEPH 23-JAN-99-B
// cash
"xv	350 "
"cnum "
"xv	400 "
"pic 0 "
// END JOSEPH

// JOSEPH 2-FEB-99
"talk "
// END JOSEPH

"hire "

// armor
"if 4 "
"	xv	200 "
"	rnum "
"	xv	250 "
"	pic 4 "
"endif "

// selected item
"if 6 "
"	xv	296 "
"	pic 6 "
"endif "

"yb	-50 "

// JOSEPH 25-JAN-99
// picked up item
"if 17 "
"	xv	0 "
"	pic 7 "
"	xv	26 "
"	yb	-42 "
"	stat_string 8 7 "
"	yb	-50 "
"endif "
// END JOSEPH

// Ridah, 26-may-99, disabled this since it's listed above also (duplicated, so it's being drawn twice)
#if 0
// JOSEPH 11-APR-99
// cash
"xv	350 "
"cnum "
"xv	400 "
"pic 0 "
// END JOSEPH
#endif

// timer
"if 9 "
"	xv	262 "
"	num	2	10 "
"	xv	296 "
"	pic	9 "
"endif "

//  help / weapon icon 
"if 11 "
"	xv	148 "
"	pic	11 "
"endif "
;

char *dm_statusbar =
"yb	-24 "

// health
"xv	0 "
"hnum "
"xv	50 "
"pic 0 "

// ammo
// JOSEPH 25-JAN-99
"if 2 "
"	xv	100 "
"	anum 2 "
"	xv	150 "
"	pic 2 "
"endif "
// END JOSEPH


// RAFAEL 
// weapon clip
"if 2 "
"	xv	160 "
"	wanum "
"endif "

// Ridah, 26-may-99, show frag count
"xv 350 "
"frags "

// JOSEPH 2-FEB-99
"talk "
// END JOSEPH

"hire "

"if 4 "
"	xv	200 "
"	rnum "
"	xv	250 "
"	pic 4 "
"endif "

// selected item
"if 6 "
"	xv	296 "
"	pic 6 "
"endif "

"yb	-50 "

// picked up item
"if 17 "
"	xv	0 "
"	pic 7 "
"	xv	26 "
"	yb	-42 "
"	stat_string 8 7 "
"	yb	-50 "
"endif "

// timer
"if 9 "
"	xv	262 "
"	num	2	10 "
"	xv	296 "
"	pic	9 "
"endif "

//  help / weapon icon 
"if 11 "
"	xv	148 "
"	pic	11 "
"endif "
;

char *teamplay_statusbar =
"yb	-24 "

// health
"xv	0 "
"hnum "
"xv	50 "
"pic 0 "

// ammo
"if 2 "
"	xv	100 "
"	anum 2 "
"	xv	150 "
"	pic 2 "
"endif "

// weapon clip
"if 2 "
"	xv	160 "
"	wanum "
"endif "

// cash
"xv	350 "
"cnum "
"xv	400 "
"pic 0 "

"if 4 "
"	xv	200 "
"	rnum "
"	xv	250 "
"	pic 4 "
"endif "

// selected item
"if 6 "
"	xv	296 "
"	pic 6 "
"endif "

"yb	-50 "

// picked up item
"if 17 "
"	xv	0 "
"	pic 7 "
"	xv	26 "
"	yb	-42 "
"	stat_string 8 7 "
"	yb	-50 "
"endif "

// timer
"if 9 "
"	xv	262 "
"	num	2	10 "
"	xv	296 "
"	pic	9 "
"endif "

//  help / weapon icon 
"if 11 "
"	xv	148 "
"	pic	11 "
"endif "

// Bagged cash
"bagcash "

// Ridah, teamplay scores (NOTE: THIS MUST BE LAST!!)
"teams "
//"%s "	disabled, since they get added dynamically according to the team-name strings
//"%s "

;


/*QUAKED worldspawn (0 0 0) ?

Only used for the world.
"episode"	Kingpin episode number
"sky"	environment map name
"sounds"	music cd track number
"gravity"	800 is default gravity
"message"	text to print at user logon
*/
int	client_connected;

void SP_worldspawn (edict_t *ent)
{

	// Ridah, don't allow deathmatching in single player maps
	if (ent->count && deathmatch->value)
	{
		gi.error("\nCannot play this map in DEATHMATCH mode.\n");
		return;
	}

	if (!deathmatch->value)
	{
		// stop them from screwing up single player
		gi.cvar_forceset( "dmflags", "784" );
	}

	// Ridah, so we can init soundindex's for voice_table's
	gameinc++;

	client_connected = 0;

	ent->movetype = MOVETYPE_PUSH;
	ent->solid = SOLID_BSP;
	ent->inuse = true;			// since the world doesn't use G_Spawn()
	ent->s.modelindex = 1;		// world model is always index 1

	//---------------

	// clear all precached voices
	if (num_precached_voices)
	{
		int i;

		for (i=0; i<num_precached_voices; i++)
			precached_voices[i]->soundindex = 0;

		num_precached_voices = 0;
	}

	memset( g_cast_memory, 0, MAX_CHARACTERS * MAX_CHARACTERS * sizeof(cast_memory_t) );
	memset( g_cast_groups, 0, MAX_CAST_GROUPS * sizeof(cast_group_t) );

	num_flares = 0;
	level.num_light_sources = 0;

	level.episode = ent->count;

	// Teamplay
	Teamplay_InitTeamplay();

	// Ridah, hack, since the bar doesn't have an episode value set
	// if (!level.episode)
	//	level.episode = 1;

	// Ridah, init the lightpaint buffers
	memset( lpbuf, 0, sizeof(lpbuf) );
	num_lpbuf = 0;

	// reserve some spots for dead player bodies for coop / deathmatch
	InitBodyQue ();

	// set configstrings for items
	SetItemNames ();

	if (st.nextmap)
		strcpy (level.nextmap, st.nextmap);

	// make some data visible to the server

	if (ent->message && ent->message[0])
	{
		gi.configstring (CS_NAME, ent->message);
		strncpy (level.level_name, ent->message, sizeof(level.level_name));
	}
	else
		strncpy (level.level_name, level.mapname, sizeof(level.level_name));

	gi.configstring (CS_DENSITY, va("%f", st.fogdensity));
	gi.configstring (CS_FOGVAL, va("%f %f %f", st.fogval[0], st.fogval[1], st.fogval[2]));


	gi.configstring (CS_DENSITY2, va("%f", st.fogdensity2));
	gi.configstring (CS_FOGVAL2, va("%f %f %f", st.fogval2[0], st.fogval2[1], st.fogval2[2]));

	if (st.sky && st.sky[0])
		gi.configstring (CS_SKY, st.sky);
	else
		gi.configstring (CS_SKY, "sr");

	gi.configstring (CS_CDTRACK, va("%i", ent->sounds) );

	gi.configstring (CS_MAXCLIENTS, va("%i", (int)(maxclients->value) ) );

	// status bar program
	if (teamplay->value && deathmatch->value)
	{
		char str[1024];

		// add the team names
		strcpy( str, teamplay_statusbar );
		strcat( str, "\"" );
		strcat( str, team_names[1] );
		strcat( str, "\" \"" );
		strcat( str, team_names[2] );
		strcat( str, "\" " );
		gi.configstring (CS_STATUSBAR, str);
	}
	else if (deathmatch->value)
	{
		gi.configstring (CS_STATUSBAR, dm_statusbar);
	}
	else
	{
		gi.configstring (CS_STATUSBAR, single_statusbar);
	}

	//---------------

	// help icon for statusbar
	/*
	// Rafael: not in demo
	
	// we will be using this in the demo when Maxx makes the artwork

	gi.imageindex ("i_help");
	level.pic_health = gi.imageindex ("i_health");
	gi.imageindex ("help");
	gi.imageindex ("field_3");
	*/

	if (!st.gravity)
		gi.cvar_set("sv_gravity", "800");
	else
		gi.cvar_set("sv_gravity", st.gravity);

	// JOSEPH 29-MAR-99
	snd_fry = gi.soundindex ("actors/player/male/fry.wav");	// standing in lava / slime
	// END JOSEPH

	// PrecacheItem (FindItem ("Blaster"));


	// Ridah, in-game effects
//	sp_blood1 = gi.modelindex("sprites/blood/blood1.sp2");


	// JOSEPH 29-MAR-99
	//gi.soundindex ("actors/player/lava1.wav");
	//gi.soundindex ("actors/player/lava2.wav");
	//gi.soundindex ("misc/pc_up.wav");
	//gi.soundindex ("misc/talk1.wav");
	//gi.soundindex ("misc/udeath.wav");

	// gibs
	//gi.soundindex ("items/respawn1.wav");
	// END JOSEPH

	// sexed sounds

	gi.soundindex ("*death1.wav");
	gi.soundindex ("*death2.wav");
	gi.soundindex ("*death3.wav");
	gi.soundindex ("*death4.wav");
	//gi.soundindex ("*fall1.wav");
	//gi.soundindex ("*fall2.wav");	
	gi.soundindex ("*gurp1.wav");		// drowning damage
	gi.soundindex ("*gurp2.wav");	
	gi.soundindex ("*jump1.wav");		// player jump
	gi.soundindex ("*jump2.wav");		// player jump
	gi.soundindex ("*jump3.wav");		// player jump
	gi.soundindex ("*pain25_1.wav");
	gi.soundindex ("*pain25_2.wav");
	gi.soundindex ("*pain50_1.wav");
	gi.soundindex ("*pain50_2.wav");
	gi.soundindex ("*pain75_1.wav");
	gi.soundindex ("*pain75_2.wav");
	gi.soundindex ("*pain100_1.wav");
	gi.soundindex ("*pain100_2.wav");

	//-------------------

	// JOSEPH 29-MAR-99 
	gi.soundindex ("actors/player/male/gasp1.wav");		// gasping for air
	gi.soundindex ("actors/player/male/gasp2.wav");		// head breaking surface, not gasping

	//gi.soundindex ("actors/player/watr_in.wav");	// feet hitting water
	//gi.soundindex ("actors/player/step water/step water.wav");	// feet leaving water

	//gi.soundindex ("actors/player/watr_un.wav");	// head going underwater
	
	//gi.soundindex ("actors/player/u_breath1.wav");
	//gi.soundindex ("actors/player/u_breath2.wav");
	//gi.soundindex ("items/pkup.wav");		// bonus item pickup

	//gi.soundindex ("world/land.wav");		// landing thud
	//gi.soundindex ("misc/h2ohit1.wav");		// landing splash

	//gi.soundindex ("items/damage.wav");
	
	//gi.soundindex ("items/protect.wav");
	//gi.soundindex ("items/protect4.wav");
	//gi.soundindex ("weapons/noammo.wav");
	// END JOSEPH

//	gi.soundindex ("infantry/inflies1.wav");

// JOSEPH 22-JAN-99
	gi.soundindex ("world/trash1.wav");
	gi.soundindex ("world/trash2.wav");
	gi.soundindex ("world/trash3.wav");
	gi.soundindex ("world/crate1.wav");
	gi.soundindex ("world/crate2.wav");
	gi.soundindex ("world/crate3.wav");
	gi.soundindex ("weapons/bullethit_tin.wav");
	gi.soundindex ("weapons/bullethit_tin2.wav");
	gi.soundindex ("weapons/bullethit_tin3.wav");
// END JOSEPH

	gi.soundindex ("weapons/ric1.wav");
	gi.soundindex ("weapons/ric2.wav");
	gi.soundindex ("weapons/ric3.wav");

	// ----------------------------------------------------------------------------------
	// Vweap weapon models
	//
	// !!!!!!!!!!!!!!!
	// These must be defined in the same order as the corresponding CLIP_* in gl_locals.h, so that
	// the client knows which model to use
	// !!!!!!!!!!!!!!!

	gi.modelindex ("#w_pipe.mdx");				// CLIP_NONE
	gi.modelindex ("#w_pistol.mdx");			// CLIP_PISTOL
	gi.modelindex ("#w_shotgun.mdx");			// CLIP_SHOTGUN
	gi.modelindex ("#w_tommygun.mdx");			// CLIP_TOMMGUN
	gi.modelindex ("#w_heavy machinegun.mdx");	// CLIP_SLUGS
	gi.modelindex ("#w_grenade launcher.mdx");	// CLIP_GRENADES
	gi.modelindex ("#w_bazooka.mdx");			// CLIP_ROCKETS
	gi.modelindex ("#w_flamethrower.mdx");		// CLIP_FLAMEGUN
	// ----------------------------------------------------------------------------------


//
// Setup light animation tables. 'a' is total darkness, 'z' is doublebright.
//

	// DAN 28-OCT-98
	// 0 normal
	gi.configstring(CS_LIGHTS+0, "m");
	
	// 1 FIRE FLICKER (first variety)
	gi.configstring(CS_LIGHTS+1, "mmnmmommommnonmmonqnmmo");
	
	// 2 SLOW STRONG PULSE
	gi.configstring(CS_LIGHTS+2, "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba");
	
	// 3 CANDLE (first variety)
	gi.configstring(CS_LIGHTS+3, "mmmmmaaaaammmmmaaaaaabcdefgabcdefg");
	
	// 4 FAST STROBE
	gi.configstring(CS_LIGHTS+4, "mamamamamama");
	
	// 5 GENTLE PULSE 1
	gi.configstring(CS_LIGHTS+5,"jklmnopqrstuvwxyzyxwvutsrqponmlkj");
	
	// 6 FIRE FLICKER (second variety)
	gi.configstring(CS_LIGHTS+6, "nmonqnmomnmomomno");
	
	// 7 CANDLE (second variety)
	gi.configstring(CS_LIGHTS+7, "mmmaaaabcdefgmmmmaaaammmaamm");
	
	// 8 CANDLE (third variety)
	gi.configstring(CS_LIGHTS+8, "mmmaaammmaaammmabcdefaaaammmmabcdefmmmaaaa");
	
	// 9 SLOW STRONG STROBE
	gi.configstring(CS_LIGHTS+9, "aaaaaaaazzzzzzzz");
	
	// 10 FLUORESCENT FLICKER (first variety)
	gi.configstring(CS_LIGHTS+10, "mmamammmmammamamaaamammma");

	// 11 SLOW PULSE FADES TO BLACK
	gi.configstring(CS_LIGHTS+11, "abcdefghijklmnopqrrqponmlkjihgfedcba");
	
	// new kingpin light styles (these are still temp)
	// 12 FIRE FLICKER (third variety)
	gi.configstring(CS_LIGHTS+12, "mmnommomhkmmomnonmmonqnmmo");
	
	// 13 FLUORESCENT FLICKER (second variety)
	gi.configstring(CS_LIGHTS+13, "kmamaamakmmmaakmamakmakmmmma");

	// 14 FLUORESCENT FLICKER (third variety)
	gi.configstring(CS_LIGHTS+14, "kmmmakakmmaaamammamkmamakmmmma");

	// 15 REALISTIC FADE (first variety)
	gi.configstring(CS_LIGHTS+15, "mmnnoonnmmmmmmmmmnmmmmnonmmmmmmm");

	// 16 REALISTIC FADE (second variety)
	gi.configstring(CS_LIGHTS+16, "mmmmnonmmmmnmmmmmnonmmmmmnmmmmmmm");
	 	
	// 17 SLOW STRONG STROBE (out of phase with 9)
	gi.configstring(CS_LIGHTS+17, "zzzzzzzzaaaaaaaa");

	// 18 THREE CYCLE STROBE (cycle 1)
	gi.configstring(CS_LIGHTS+18, "zzzzzzzzaaaaaaaaaaaaaaaa");

	// 19 THREE CYCLE STROBE (cycle 2)
	gi.configstring(CS_LIGHTS+19, "aaaaaaaazzzzzzzzaaaaaaaa");

	// 20 THREE CYCLE STROBE (cycle 3)
	gi.configstring(CS_LIGHTS+20, "aaaaaaaaaaaaaaaazzzzzzzz");
	// END 28-OCT-98

	// styles 32-62 are assigned by the light program for switchable lights
	// styles 32-62 are assigned by the light program for switchable lights

	// 63 testing
	gi.configstring(CS_LIGHTS+63, "a");

}

