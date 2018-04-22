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
	int score1 = 0, score2 = 0;
	char score_text1[10];
	char score_text2[10];

	SDL_Rect HUD1;
	SDL_Rect HUD2;
	SDL_Rect HUD3;
	SDL_Rect HUD4;
	SDL_Rect Life1, Life2; // Lives remaining of p1 and p2

	Animation beamCharger; // Showe while charging
	Animation beamCharged; // Showed while charged
	Animation beamNoCharged; // Showed while not pressing space

	Animation beamCharger2; // Showe while charging
	Animation beamCharged2; // Showed while charged
	Animation beamNoCharged2; // Showed while not pressing space

	bool powerUp = true;
	bool charging;
	uint chargingSound, chargedSound;

	Uint32 startTime1 = 0, currentTime1;
	Uint32 startTime2 = 0, currentTime2;
	bool activatedChange1, activatedChange2; //Tells if the players are changing of weapon

};

#endif