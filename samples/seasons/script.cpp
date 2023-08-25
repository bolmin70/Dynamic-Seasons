
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


int screenUpdateTimer = 0;

bool once = 0;
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

bool showToast = 0;
int weather_timer;

int seasonLength;
bool visualSettingsOn;
bool regionTemperatureOn;
bool weatherClimatesOn;
bool vestigiaOn;
bool ALWAYS_NO; 

Ped player;
Vector3 playerPos;

void load() {
	ifstream LoadFile;
	LoadFile.open("seasons.dat", std::ofstream::in);

	LoadFile >> seasonTimer >> season; //loads the current season tracker and progress till next season

	LoadFile.close();
}

void save() {
	ofstream SaveFile;
	SaveFile.open("seasons.dat", std::ofstream::trunc);

	SaveFile << seasonTimer << " " << season << " "; //saves the current season tracker and progress till next season

	SaveFile.close();
}


void initialize()
{
	//read the INI file settings
	seasonLength = GetPrivateProfileInt("MISC", "SEASON_LENGTH", 400, ".\\Seasons.ini");
	visualSettingsOn = GetPrivateProfileInt("MISC", "VISUAL_SETTINGS", 1, ".\\Seasons.ini");
	regionTemperatureOn = GetPrivateProfileInt("MISC", "REGION_TEMPERATURE", 1, ".\\Seasons.ini");
	weatherClimatesOn = GetPrivateProfileInt("MISC", "WEATHER_CLIMATES", 1, ".\\Seasons.ini");
	vestigiaOn = GetPrivateProfileInt("VESTIGIA", "COMPATIBILITY_MODE", 0, ".\\Seasons.ini");
	ALWAYS_NO = GetPrivateProfileInt("MISC", "SEASON_WIDGET", 1, ".\\Seasons.ini");


	if (seasonTimer == seasonLength) { //resets the season tracker
		seasonTimer = 0;

		showToast = 1;

		if (season < 3) { //season 3 is winter, so after that it resets to spring season 0
			season++;
		}
		else {
			season = 0;
		}
	}

	

	
	int j = rand() % 2; //chance for an added weather type to run on startup
	if (j) {
		weather_timer = MISC::GET_GAME_TIMER() + (60000 * (60 + rand() % 10));
	}
	else {
		weather_timer = MISC::GET_GAME_TIMER() + 60000;
	}
	
}

#define TURN_OFF 0

void main()
{		
	srand(time(NULL));

	load(); //load the .dat file

	int timer = MISC::GET_GAME_TIMER() + 60000;
	
	initialize();
	

	while (true)
	{
		srand(time(NULL));

		player = PLAYER::PLAYER_PED_ID();
		playerPos = ENTITY::GET_ENTITY_COORDS(player, true, false);
	
		Toasts::updateUI();


	
		//Logic for proper seasons HUD placement when revealing the HUD with Alt or down dpad
		if (GRAPHICS::ANIMPOSTFX_IS_RUNNING("WheelHUDIn") && PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SELECT_RADAR_MODE"))) {
			if (!inAlt) {
				if (no_slowdown) {
					extend_hud_timer = MISC::GET_GAME_TIMER() + 368; 
				}
				inAlt = 1;
			}

		}
		else {
			inAlt = 0;
			if (PAD::IS_CONTROL_JUST_RELEASED(0, MISC::GET_HASH_KEY("INPUT_REVEAL_HUD"))) {
				extend_hud = 1;
				extend_hud_timer = MISC::GET_GAME_TIMER() + 2950; 
			}
		}

		if (extend_hud_timer < MISC::GET_GAME_TIMER() || GRAPHICS::ANIMPOSTFX_IS_RUNNING("WheelHUDIn")) {
			extend_hud = 0;
		}



		
		
		if (ZONE::_GET_MAP_ZONE_AT_COORDS(playerPos.x, playerPos.y, playerPos.z, 10) != 0xE1736CD7) { //when NOT on Guarma
			if (HUD::IS_RADAR_HIDDEN() == true || MISC::GET_MISSION_FLAG()) {



			}
			else {

				float coreX = 0.45;
				float coreY = 0.15;

				if (extend_hud && ALWAYS_NO == 1) { //HUD widget 
					Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_1", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					Misc::drawSprite("rpg_menu_item_effects", "rpg_tank_1", coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
					
					for (int i = 0; i < 10; i++) {
						if ((seasonLength / 10) * i + 1 >= seasonTimer && (seasonLength / 10) * i < seasonTimer) {
							stringstream rpgTank;
							rpgTank << "rpg_tank_";
							rpgTank << (i + 1);

							Misc::drawSprite("rpg_menu_item_effects", rpgTank.str().c_str(), coreX, coreY, 0.03, 0.05, 0, 255, 255, 255, 255);
						}
					}


					Misc::drawSprite("feeds", "help_text_bg", coreX + 0.03, coreY, 0.07, 0.05f, 0, 0, 0, 0, 255);
					switch (season) { //TODO
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

		if (showToast) { //once on boot if the seasons changed

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

		if (!once) { //do it once, the game will update on next boot
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


		if (timer < MISC::GET_GAME_TIMER()) { //Next season timer

			if (seasonTimer < seasonLength) {
				seasonTimer++;
			}


			save(); //saves the data into the .dat file
			timer = MISC::GET_GAME_TIMER() + 60000; //60 seconds/minute interval
		}

		
		
		if (TURN_OFF == 1) { //for debugging
			if (ZONE::_GET_MAP_ZONE_AT_COORDS(playerPos.x, playerPos.y, playerPos.z, 10) != 0xE1736CD7) {



				if (weather_timer < MISC::GET_GAME_TIMER()) {


					int i = rand() % 2;

					if (i) {
						switch (season) {
						case 0: //spring

							break;
						case 1:
							//summer

							break;

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
		
		
		if (screenUpdateTimer < MISC::GET_GAME_TIMER()) {
			
			

			switch (season) {
				case 0: //spring
					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern02");
					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern02", 0.4f); //spring filter set at 0.4 strength	
					break;

				case 1: //summer
					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern01");
					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern01", 0.0f); //a filter set to 0 intensity, to maintain irregularities of other filters
					break;

				case 2: //autumn
					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern01");
					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern01", 0.3f); //autumn filter set at 0.3 strength	
					break;

				case 3: //winter				
					GRAPHICS::ANIMPOSTFX_PLAY("PhotoMode_FilterModern03");
					GRAPHICS::_0xCAB4DD2D5B2B7246("PhotoMode_FilterModern03", 0.4f); //spring filter set at 0.4 strength
					GRAPHICS::_SET_SNOW_COVERAGE_TYPE(2); //RDO snow coverage

					break;
				}
			
			screenUpdateTimer + MISC::GET_GAME_TIMER() + 100; //sets this per 100 millisecond interval
		}
		

		if (ZONE::_GET_MAP_ZONE_AT_COORDS(playerPos.x, playerPos.y, playerPos.z, 10) == 0xE1736CD7) { //turns off all filters when at Guarma
			
			GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern02");
			GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern01");
			GRAPHICS::ANIMPOSTFX_STOP("PhotoMode_FilterModern03");
		}
		if (TASK::GET_SCRIPT_TASK_STATUS(player, 1369124074, true) == 1) { //if a player enters an animscene, disables snow - temporary fix for the camp ledger
			disable_snow = 1;
			snow_timer = MISC::GET_GAME_TIMER() + 2500;
		}
		
		if (disable_snow && snow_timer < MISC::GET_GAME_TIMER()) { //function for disabling snow temporarly
			GRAPHICS::_SET_SNOW_COVERAGE_TYPE(0);

			if (!HUD::IS_RADAR_HIDDEN()) {
				disable_snow = 0;
			}



		}


		WAIT(0);
	}
}

void ScriptMain()
{	
	srand(GetTickCount());
	main();
}
