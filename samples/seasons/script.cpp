
#include "script.h"
#include <string>
#include <vector>
#include "Misc.h"
#include "sstream"

#include "Toasts.h"

#include "filesystem"

using namespace std;



int seasonTimer;
int season;


void load() {
	ifstream LoadFile;
	LoadFile.open("seasons.dat", std::ofstream::in);

	LoadFile >> seasonTimer >> season;

	LoadFile.close();
}

void save() {
	ofstream SaveFile;
	SaveFile.open("seasons.dat", std::ofstream::trunc);

	SaveFile << seasonTimer << " " << season << " ";

	SaveFile.close();
}

Prompt Prompt_Calender;
void initialize()
{

	Misc::createPrompt(Prompt_Calender, "INPUT_FRONTEND_ACCEPT", "Calendar", 1, 1616332288);

}

#define TURN_OFF 0

void main()
{		
	

	load();

	
	int timer = MISC::GET_GAME_TIMER() + 60000;
	
	bool showToast = 0;
	
	int seasonLength = GetPrivateProfileInt("MISC", "SEASON_LENGTH", 400, ".\\Seasons.ini");

	bool visualSettingsOn = GetPrivateProfileInt("MISC", "VISUAL_SETTINGS", 1, ".\\Seasons.ini");

	bool regionTemperatureOn = GetPrivateProfileInt("MISC", "REGION_TEMPERATURE", 1, ".\\Seasons.ini");

	bool weatherClimatesOn = GetPrivateProfileInt("MISC", "WEATHER_CLIMATES", 1, ".\\Seasons.ini");

	bool vestigiaOn = GetPrivateProfileInt("VESTIGIA", "COMPATIBILITY_MODE", 0, ".\\Seasons.ini");

	bool ALWAYS_NO = GetPrivateProfileInt("MISC", "SEASON_WIDGET", 1, ".\\Seasons.ini");

	if (seasonTimer == seasonLength) {
		seasonTimer = 0;

		showToast = 1;

		if (season < 3) {
			season++;
		}
		else {
			season = 0;
		}




	}
	srand(time(NULL));


	int weather_timer;
	int j = rand() % 2;
	if (j) {
		weather_timer = MISC::GET_GAME_TIMER() + (60000 * (60 + rand() % 10));
	}
	else {
		weather_timer = MISC::GET_GAME_TIMER() + 60000;
	}


	int screenUpdateTimer = 0;

	bool once = 0;

	/*
	//MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("RAIN"), 1, 1, 0, 0, 0);
	

	


	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_bw", "");

	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_close_spray", "");

	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_cum_01", "");



	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_dak_gp_v2_01", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_dak_gp_v2_02", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_dak_gp_v2_03", "");

	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_dak_up_01", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_dak_up_02", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_dak_up_03", "");




	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_decal", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_ely_01", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_ely_splash", "");



	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_lens", "");

	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_lmr_mist", "");


	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_man", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_man_narrow", "");
	*/

	/* important
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_proto_01", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_proto_01_larger", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_proto_02_cloud", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_proto_02_cloud_va_wide", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_proto_02_cloud_var", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_proto_02_spray", "");
	*/

	/*
	
	//important
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_mist_lg", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_mist_md", "");


	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_soak", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_base", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_base_med", "");
	
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_base_sm", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_cloud", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_lg", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_md", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_sm", "");
	
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_top_bits", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_whitewater", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wfall_strwb_base", "");
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wfall_strwb_top", "");
	

	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_river_mist_gen", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_river_rock_splash", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_river_splash_gen", "");

	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_rapid_dir_splash", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_rapid_dir_splash_light", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_rapid_dir_splash_long", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_rapid_dir_splash_short", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_rapid_dir_splash_wide", "");

	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_rapid_area_spray", "");
	GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_rapid_area_spray_hvy", "");
	
	*/
	//Remove Repeater Particles
	//GRAPHICS::SET_PARTICLE_FX_OVERRIDE("eject_repeater_shell", "");

	initialize();
	//400 minutes = ~6 1/2 hours
	
	bool inAlt = 0;
	int extend_hud_timer = 0;

	bool extend_hud = 0;
	bool inWheel = 0;
	bool in_hud = 0;

	bool no_slowdown = 0;

	bool satchel_opened = 0;
	int satchelTimer = 0;

	bool disable_snow = 0;
	int snow_timer = 0;

	while (true)
	{
		srand(time(NULL));

		Ped player = PLAYER::PLAYER_PED_ID();
		Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);
		Ped playerHorse = PLAYER::_GET_SADDLE_HORSE_FOR_PLAYER(0);


		Toasts::updateUI();


		

		//GRAPHICS::ANIMPOSTFX_PLAY("CAM_PM_F_V0");
		//GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern01");
		
		//1616332288

		HUD::_UIPROMPT_SET_ENABLED(Prompt_Calender, 0);
		HUD::_UIPROMPT_SET_VISIBLE(Prompt_Calender, 0);

		//rpg_tank_1
		//Misc::drawSprite("rpg_textures", "rpg_core_background", 0.08, 0.5, 0.03, 0.05, 0, 0, 0, 0, 220);


		if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("WheelHUDIn") && PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SELECT_RADAR_MODE"))) {
			if (!inAlt) {
				if (no_slowdown) {
					extend_hud_timer = MISC::GET_GAME_TIMER() + 368; //2950
				}


				inAlt = 1;
			}

		}
		else {
			inAlt = 0;
			if (PAD::IS_CONTROL_JUST_RELEASED(0, MISC::GET_HASH_KEY("INPUT_REVEAL_HUD"))) {



				extend_hud = 1;

				extend_hud_timer = MISC::GET_GAME_TIMER() + 2950; //2950

			}

		}





		if (extend_hud_timer < MISC::GET_GAME_TIMER() || GRAPHICS::ANIMPOSTFX_IS_RUNNING("WheelHUDIn")) {
			extend_hud = 0;
		}



		
		
		//MISC::GET_MISSION_FLAG()
		if (ZONE::_GET_MAP_ZONE_AT_COORDS(playerPos.x, playerPos.y, playerPos.z, 10) != 0xE1736CD7) {
			if (HUD::IS_RADAR_HIDDEN() == true || MISC::GET_MISSION_FLAG()) {



			}
			else {

				float coreX = 0.45;
				float coreY = 0.15;

				if (extend_hud && ALWAYS_NO == 1) {
					Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_1", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_1", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					if ((seasonLength / 10) * 1 >= seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_1", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 2 >= seasonTimer && (seasonLength / 10) * 1 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_2", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 3 >= seasonTimer && (seasonLength / 10) * 2 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_3", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 4 >= seasonTimer && (seasonLength / 10) * 3 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_4", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 5 >= seasonTimer && (seasonLength / 10) * 4 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_5", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 6 >= seasonTimer && (seasonLength / 10) * 5 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_6", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 7 >= seasonTimer && (seasonLength / 10) * 6 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_7", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 8 >= seasonTimer && (seasonLength / 10) * 7 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_8", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 9 >= seasonTimer && (seasonLength / 10) * 8 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_9", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}
					if ((seasonLength / 10) * 10 >= seasonTimer && (seasonLength / 10) * 9 < seasonTimer) {
						Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_10", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					}



					Misc::drawSprite("feeds", "help_text_bg", coreX + 0.03, coreY, 0.07, 0.05f, 0, 0, 0, 0, 255);
					switch (season) {
					case 0:
						Misc::drawSprite("rpg_textures", "rpg_hot", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
						Misc::drawText("Spring", coreX + 0.038, coreY + 0.0083, 255, 255, 255, 255, 0, 0.47, 0.47);
						break;
					case 1:
						Misc::drawSprite("rpg_textures", "rpg_hot", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
						Misc::drawText("Summer", coreX + 0.038, coreY + 0.0083, 255, 255, 255, 255, 0, 0.47, 0.47);
						break;
					case 2:
						Misc::drawSprite("rpg_textures", "rpg_cold", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
						Misc::drawText("Autumn", coreX + 0.038, coreY + 0.0083, 255, 255, 255, 255, 0, 0.47, 0.47);
						break;
					case 3:
						Misc::drawSprite("rpg_textures", "rpg_cold", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
						Misc::drawText("Winter", coreX + 0.038, coreY + 0.0083, 255, 255, 255, 255, 0, 0.47, 0.47);
						break;

					}


				}



			}
		}

		if (showToast) {

			switch (season) {
			case 0:
				Toasts::showAdvancedNotification("~COLOR_GREEN~Spring", "Season has changed", "rpg_textures", "rpg_hot", 500);
				break;
			case 1:
				Toasts::showAdvancedNotification("~COLOR_GOLD~Summer", "Season has changed", "rpg_textures", "rpg_hot", 500);
				break;
			case 2:
				Toasts::showAdvancedNotification("~COLOR_ORANGE~Autumn", "Season has changed", "rpg_textures", "rpg_cold", 500);
				break;
			case 3:
				Toasts::showAdvancedNotification("~COLOR_BLUE~Winter", "Season has changed", "rpg_textures", "rpg_cold", 500);
				break;
			}

			showToast = 0;
		}

		if (!once) {
			if (seasonTimer == seasonLength) {


				if (season == 0) {
					if (!vestigiaOn) {
						if (visualSettingsOn) {
							std::rename("lml\\Seasons\\visualsettings.dat", "Seasons\\visualsettingsSpringAutumn.dat");
						}
						if (regionTemperatureOn) {
							std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "Seasons\\regionTemperatureInfoSpringAutumn.xml");
						}
						if (weatherClimatesOn) {
							std::rename("lml\\Seasons\\weatherclimates.xml", "Seasons\\weatherclimatesSpringAutumn.xml");
						}

					}
					else {
						
						std::rename("lml\\Seasons\\visualsettings.dat", "SeasonsVestigia\\visualsettingsSpringAutumn.dat");
						
						std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "SeasonsVestigia\\regionTemperatureInfoSpringAutumn.xml");

						std::rename("lml\\Seasons\\weatherTemperatureConfig.xml", "SeasonsVestigia\\weatherTemperatureConfigSpringAutumn.xml");

						std::rename("lml\\Seasons\\weatherRemapTable.xml", "SeasonsVestigia\\weatherRemapTableSpringAutumn.xml");

						std::rename("lml\\Seasons\\weatherclimates.xml", "SeasonsVestigia\\weatherclimatesSpringAutumn.xml");

						

						
					}



				}
				if (season == 1) {
					if (!vestigiaOn) {
						if (visualSettingsOn) {
							std::rename("lml\\Seasons\\visualsettings.dat", "Seasons\\visualsettingsSummer.dat");
						}
						if (regionTemperatureOn) {
							std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "Seasons\\regionTemperatureInfoSummer.xml");
						}
						if (weatherClimatesOn) {
							std::rename("lml\\Seasons\\weatherclimates.xml", "Seasons\\weatherclimatesSummer.xml");
						}
					}
					else {
						std::rename("lml\\Seasons\\visualsettings.dat", "SeasonsVestigia\\visualsettingsSummer.dat");

						std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "SeasonsVestigia\\regionTemperatureInfoSummer.xml");


						std::rename("lml\\Seasons\\weatherTemperatureConfig.xml", "SeasonsVestigia\\weatherTemperatureConfigSummer.xml");

						std::rename("lml\\Seasons\\weatherRemapTable.xml", "SeasonsVestigia\\weatherRemapTableSummer.xml");

						std::rename("lml\\Seasons\\weatherclimates.xml", "SeasonsVestigia\\weatherclimatesSummer.xml");

					

					}
				}
				if (season == 2) {
					if (!vestigiaOn) {
						if (visualSettingsOn) {
							std::rename("lml\\Seasons\\visualsettings.dat", "Seasons\\visualsettingsSpringAutumn.dat");
						}
						if (regionTemperatureOn) {
							std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "Seasons\\regionTemperatureInfoSpringAutumn.xml");
						}
						if (weatherClimatesOn) {
							std::rename("lml\\Seasons\\weatherclimates.xml", "Seasons\\weatherclimatesSpringAutumn.xml");
						}
					}
					else {
						std::rename("lml\\Seasons\\visualsettings.dat", "SeasonsVestigia\\visualsettingsSpringAutumn.dat");

						std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "SeasonsVestigia\\regionTemperatureInfoSpringAutumn.xml");


						std::rename("lml\\Seasons\\weatherTemperatureConfig.xml", "SeasonsVestigia\\weatherTemperatureConfigSpringAutumn.xml");

						std::rename("lml\\Seasons\\weatherRemapTable.xml", "SeasonsVestigia\\weatherRemapTableSpringAutumn.xml");

						std::rename("lml\\Seasons\\weatherclimates.xml", "SeasonsVestigia\\weatherclimatesSpringAutumn.xml");

				

					}

				}
				if (season == 3) {
					if (!vestigiaOn) {
						if (visualSettingsOn) {
							std::rename("lml\\Seasons\\visualsettings.dat", "Seasons\\visualsettingsWinter.dat");
						}
						if (regionTemperatureOn) {
							std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "Seasons\\regionTemperatureInfoWinter.xml");
						}
						if (weatherClimatesOn) {
							std::rename("lml\\Seasons\\weatherclimates.xml", "Seasons\\weatherclimatesWinter.xml");
						}
					}
					else {
						std::rename("lml\\Seasons\\visualsettings.dat", "SeasonsVestigia\\visualsettingsWinter.dat");

						std::rename("lml\\Seasons\\regionTemperatureInfo.xml", "SeasonsVestigia\\regionTemperatureInfoWinter.xml");


						std::rename("lml\\Seasons\\weatherTemperatureConfig.xml", "SeasonsVestigia\\weatherTemperatureConfigWinter.xml");

						std::rename("lml\\Seasons\\weatherRemapTable.xml", "SeasonsVestigia\\weatherRemapTableWinter.xml");

						std::rename("lml\\Seasons\\weatherclimates.xml", "SeasonsVestigia\\weatherclimatesWinter.xml");

						

					}

				}







				if (season + 1 == 1) {
					if (!vestigiaOn) {
						if (visualSettingsOn) {
							std::rename("Seasons\\visualsettingsSummer.dat", "lml\\Seasons\\visualsettings.dat");
						}
						if (regionTemperatureOn) {
							std::rename("Seasons\\regionTemperatureInfoSummer.xml", "lml\\Seasons\\regionTemperatureInfo.xml");
						}
						if (regionTemperatureOn) {
							std::rename("Seasons\\weatherclimatesSummer.xml", "lml\\Seasons\\weatherclimates.xml");
						}
					}
					else {
						std::rename("SeasonsVestigia\\visualsettingsSummer.dat", "lml\\Seasons\\visualsettings.dat");
						std::rename("SeasonsVestigia\\regionTemperatureInfoSummer.xml", "lml\\Seasons\\regionTemperatureInfo.xml");
				
						std::rename("SeasonsVestigia\\weatherTemperatureConfigSummer.xml", "lml\\Seasons\\weatherTemperatureConfig.xml");
						std::rename("SeasonsVestigia\\weatherRemapTableSummer.xml", "lml\\Seasons\\weatherRemapTable.xml");				
						std::rename("SeasonsVestigia\\weatherclimatesSummer.xml", "lml\\Seasons\\weatherclimates.xml");
			



					}


				}
				if (season + 1 == 2) {
					if (!vestigiaOn) {
					if (visualSettingsOn) {
						std::rename("Seasons\\visualsettingsSpringAutumn.dat", "lml\\Seasons\\visualsettings.dat");
					}
					if (regionTemperatureOn) {
						std::rename("Seasons\\regionTemperatureInfoSpringAutumn.xml", "lml\\Seasons\\regionTemperatureInfo.xml");
					}
					if (regionTemperatureOn) {
						std::rename("Seasons\\weatherclimatesSpringAutumn.xml", "lml\\Seasons\\weatherclimates.xml");
					}
				}
				else {
					std::rename("SeasonsVestigia\\visualsettingsSpringAutumn.dat", "lml\\Seasons\\visualsettings.dat");
					std::rename("SeasonsVestigia\\regionTemperatureInfoSpringAutumn.xml", "lml\\Seasons\\regionTemperatureInfo.xml");

					std::rename("SeasonsVestigia\\weatherTemperatureConfigSpringAutumn.xml", "lml\\Seasons\\weatherTemperatureConfig.xml");
					std::rename("SeasonsVestigia\\weatherRemapTableSpringAutumn.xml", "lml\\Seasons\\weatherRemapTable.xml");
					std::rename("SeasonsVestigia\\weatherclimatesSpringAutumn.xml", "lml\\Seasons\\weatherclimates.xml");
			



				}

				}
				if (season + 1 == 3) {
				if (!vestigiaOn) {
					if (visualSettingsOn) {
						std::rename("Seasons\\visualsettingsWinter.dat", "lml\\Seasons\\visualsettings.dat");
					}
					if (regionTemperatureOn) {
						std::rename("Seasons\\regionTemperatureInfoWinter.xml", "lml\\Seasons\\regionTemperatureInfo.xml");
					}
					if (regionTemperatureOn) {
						std::rename("Seasons\\weatherclimatesWinter.xml", "lml\\Seasons\\weatherclimates.xml");
					}
				}
				else {
					std::rename("SeasonsVestigia\\visualsettingsWinter.dat", "lml\\Seasons\\visualsettings.dat");
					std::rename("SeasonsVestigia\\regionTemperatureInfoWinter.xml", "lml\\Seasons\\regionTemperatureInfo.xml");

					std::rename("SeasonsVestigia\\weatherTemperatureConfigWinter.xml", "lml\\Seasons\\weatherTemperatureConfig.xml");
					std::rename("SeasonsVestigia\\weatherRemapTableWinter.xml", "lml\\Seasons\\weatherRemapTable.xml");
					std::rename("SeasonsVestigia\\weatherclimatesWintern.xml", "lml\\Seasons\\weatherclimates.xml");
			



				}


				}
				if (season + 1 > 3) {
				if (!vestigiaOn) {
					if (visualSettingsOn) {
						std::rename("Seasons\\visualsettingsSpringAutumn.dat", "lml\\Seasons\\visualsettings.dat");
					}
					if (regionTemperatureOn) {
						std::rename("Seasons\\regionTemperatureInfoSpringAutumn.xml", "lml\\Seasons\\regionTemperatureInfo.xml");
					}
					if (regionTemperatureOn) {
						std::rename("Seasons\\weatherclimatesSpringAutumn.xml", "lml\\Seasons\\weatherclimates.xml");
					}
				}
				else {
					std::rename("SeasonsVestigia\\visualsettingsSpringAutumn.dat", "lml\\Seasons\\visualsettings.dat");
					std::rename("SeasonsVestigia\\regionTemperatureInfoSpringAutumn.xml", "lml\\Seasons\\regionTemperatureInfo.xml");

					std::rename("SeasonsVestigia\\weatherTemperatureConfigSpringAutumn.xml", "lml\\Seasons\\weatherTemperatureConfig.xml");
					std::rename("SeasonsVestigia\\weatherRemapTableSpringAutumn.xml", "lml\\Seasons\\weatherRemapTable.xml");
					std::rename("SeasonsVestigia\\weatherclimatesSpringAutumn.xml", "lml\\Seasons\\weatherclimates.xml");
		



				}

				}

				once = 1;
			}
		}


		if (timer < MISC::GET_GAME_TIMER()) {

			if (seasonTimer < seasonLength) {
				seasonTimer++;
			}


			save();
			//+ 60000
			timer = MISC::GET_GAME_TIMER() + 60000; //60 seconds/minute
		}

		//MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("WHITEOUT"), 1, 1, 1, 15, 0);
		
		//GRAPHICS::REMOVE_PARTICLE_FX_IN_RANGE(playerPos.x, playerPos.y, playerPos.z, 30.f);
		/*
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_base_sm", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_cloud", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_lg", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_md", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_splash_sm", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_top_bits", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wf_whitewater", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wfall_strwb_base", "");
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE("ent_amb_wfall_strwb_top", "");
		*/
		
		//ATTRIBUTE::SET_ATTRIBUTE_POINTS(player, 12, 0);
		//ATTRIBUTE::SET_ATTRIBUTE_BASE_RANK(player, 12, 0);
		if (IsKeyPressed(VK_KEY_1)) {
			stringstream test;

			//test << ATTRIBUTE::GET_ATTRIBUTE_POINTS(player, 12) << " ";
			//test << ATTRIBUTE::GET_MAX_ATTRIBUTE_POINTS(player, 12);

			


			//test << " rank: " << ATTRIBUTE::GET_ATTRIBUTE_RANK(player, 13);
			//test << " base: " << ATTRIBUTE::GET_ATTRIBUTE_BASE_RANK(player, 13);
			//test << " bonus: " << ATTRIBUTE::GET_ATTRIBUTE_BONUS_RANK(player, 13);
			//test << " max: " << ATTRIBUTE::GET_MAX_ATTRIBUTE_RANK(player, 13);

			//Misc::showSubtitle(test.str().c_str());



			//ATTRIBUTE::SET_ATTRIBUTE_POINTS(player, 12, 100);
			//ATTRIBUTE::SET_ATTRIBUTE_BASE_RANK(player, 12, 100);
			//ATTRIBUTE::SET_ATTRIBUTE_BONUS_RANK(player, 12, 100);



			//STREAMING::REMOVE_NAMED_PTFX_ASSET(MISC::GET_HASH_KEY("ped_waterfall_collision"));
			/*
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x0B0C3A54);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x17DFBCFE);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x1896BFA5);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x18F452FD);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x234AE536);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x28A683A3);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x2B14AF3F);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x2BB2E496);

			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x2E4FED02);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x33B36F81);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x341050F5);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x3BF48867);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x45C2AB4A);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x536F5146);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x551E48E4);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x55F36577);

			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x58C31CC0);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x5BFFC87D);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x5C1E291E);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x630EA4F5);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x690E3116);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x6C113E2D);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x6DC85416);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0x92BEF240);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xA9701FA6);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xB0387F27);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xB2DD8471);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xB2DD8471);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xB2DD8471);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xB2DD8471);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xB2DD8471);
			STREAMING::REMOVE_NAMED_PTFX_ASSET(0xB2DD8471);

			*/
			//MISC::CLEAR_OVERRIDE_WEATHER();
			//MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("SNOW"), 1, 1, 1, 100, 0);
		}
		
		if (TURN_OFF == 1) {
			if (ZONE::_GET_MAP_ZONE_AT_COORDS(playerPos.x, playerPos.y, playerPos.z, 10) != 0xE1736CD7) {



				if (weather_timer < MISC::GET_GAME_TIMER()) {


					int i = rand() % 2;

					if (i) {
						switch (season) {
						case 0: //early spring

							break;
						case 1:
							//spring/early summer

							break;
							/*
						case 2: //dry summer
							//MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("SUNNY"), 1, 1, 1, 100, 0);


							break;
							*/

						case 2: //autumn
							i = rand() % 5;
							switch (i) {
							case 0:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("DRIZZLE"), 1, 1, 1, 100, 0); break;
							case 1:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("HAIL"), 1, 1, 1, 100, 0); break;
							case 2:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("RAIN"), 1, 1, 1, 100, 0); break;
							case 3:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("SHOWER"), 1, 1, 1, 100, 0); break;
							case 4:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("HURRICANE"), 1, 1, 1, 100, 0); break;




							}

							break;
						case 3: //winter
							i = rand() % 5;
							switch (i) {
							case 0:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("SNOW"), 1, 1, 1, 100, 0); break;
							case 1:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("GROUNDBLIZZARD"), 1, 1, 1, 100, 0); break;
							case 2:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("SNOWLIGHT"), 1, 1, 1, 100, 0); break;
							case 3:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("WHITEOUT"), 1, 1, 1, 100, 0); break;
							case 4:
								MISC::_SET_WEATHER_TYPE(MISC::GET_HASH_KEY("SLEET"), 1, 1, 1, 100, 0); break;


							}


						}
						weather_timer = MISC::GET_GAME_TIMER() + (60000 * (60 + rand() % 10));
					}


				}


			}
		}
		
		//Misc::showSubtitle("pp");
		if (screenUpdateTimer < MISC::GET_GAME_TIMER()) {
			
			

			switch (season) {
				case 0: //early spring

					GRAPHICS::_SET_SNOW_COVERAGE_TYPE(1); //"PlayerRPGEmptyCoreDeadEye" //"MissionChoice"
				
					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern02");








					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern02", 0.40f);
					break;

				case 1: //summer
					/*
					if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("WheelHUDIn") && (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_OPEN_WHEEL_MENU")) || PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SELECT_RADAR_MODE")))) {
						GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern02");

					}
					else {
						GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern02");

					}



					if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("PlayerOverpower")
						|| PLAYER::_0xB16223CB7DA965F0(0) || PLAYER::_0x45AB66D02B601FA7(0) || GRAPHICS::ANIMPOSTFX_IS_RUNNING("MissionChoice")) {
						GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern02");

					}

					*/
					/*
					if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("CameraTakePicture") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("CameraTransitionBlink") 
						|| GRAPHICS::ANIMPOSTFX_IS_RUNNING("CameraTransitionBlink") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("CameraTransitionFlash") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("CameraTransitionWipe_L")
						|| GRAPHICS::ANIMPOSTFX_IS_RUNNING("CameraTransitionWipe_R") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("CameraViewFinder")
						
						|| GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh01") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh02") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh03")
						|| GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh04") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh05") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh06")
						|| GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh08Epi01") || GRAPHICS::ANIMPOSTFX_IS_RUNNING("ChapterTitle_IntroCh09Epi02")

						) {
						GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern02");

					}
					*/


					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern01");

					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern01", 0.0f);
					//GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern02");


					break;
					/*
				case 2: //dry summer
					//GRAPHICS::SET_TIMECYCLE_MODIFIER("nowater");
					//WATER::_DISABLE_WATER_COLLISION();
					break;

					if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SELECT_RADAR_MODE")) || PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_OPEN_WHEEL_MENU"))) {
						GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern02");

					}
					else {
						GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern02");

					}
					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern02", 0.6f);
					*/
				case 2: //autumn

					GRAPHICS::_SET_SNOW_COVERAGE_TYPE(1);





					
					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern01");


					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern01", 0.3f);
				

					break;

				case 3: //winter

					
					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern03");


					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern03", 0.3f);
					GRAPHICS::_SET_SNOW_COVERAGE_TYPE(2);

					break;






				}
			
			
			
			
			screenUpdateTimer + MISC::GET_GAME_TIMER() + 100;
		}
		

		if (ZONE::_GET_MAP_ZONE_AT_COORDS(playerPos.x, playerPos.y, playerPos.z, 10) == 0xE1736CD7) {
			
			GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern02");
			GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern01");
			GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern03");
		}
		if (TASK::GET_SCRIPT_TASK_STATUS(player, 1369124074, true) == 1) {
			//Misc::showSubtitle("pp");
			disable_snow = 1;
			snow_timer = MISC::GET_GAME_TIMER() + 2500;

			

		}
		
		if (disable_snow && snow_timer < MISC::GET_GAME_TIMER()) {
			GRAPHICS::_SET_SNOW_COVERAGE_TYPE(0);

			//if (!PED::IS_PED_USING_ANY_SCENARIO(player)) {
			if (!HUD::IS_RADAR_HIDDEN()) {
				disable_snow = 0;
			}

			//if (!CAM::_0xA24C1D341C6E0D53(1, 0, 0)) {
			//	disable_snow = 0;
			//}

		}


		//TASK::GET_SCRIPT_TASK_STATUS(Global_35, 713668775, true) != 1 && TASK::GET_SCRIPT_TASK_STATUS(Global_35, -208384378, true) != 1


		WAIT(0);
	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
