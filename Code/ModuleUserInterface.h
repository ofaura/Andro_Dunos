#ifndef __ModuleUserInterface_H__
#define __ModuleUserInterface_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleUserInterface : public Module
{
public:
	ModuleUserInterface();
	~ModuleUserInterface();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* weaponHud = nullptr;
	SDL_Texture* super = nullptr;

	int font_score = -1;
	int type_score = -1;
	int p2_title = -1;
	int hud_characteristics = -1;
	int highscore_font = -1;
	char score_text[10];

	SDL_Rect HUD1;
	SDL_Rect HUD2;
	SDL_Rect HUD3;
	SDL_Rect HUD4;
	SDL_Rect Life;

	Animation beamCharger; // Showe while charging
	Animation beamCharged; // Showed while charged
	Animation beamNoCharged; // Showed while not pressing space

	bool charging;
	uint chargingSound, chargedSound;

	Uint32 startTime = 0, currentTime;
	bool activatedChange; //Tells if the player is changing of weapon

};

#endif