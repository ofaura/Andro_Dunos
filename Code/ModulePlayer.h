#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* col_1, Collider* col_2);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* backflame = nullptr;
	SDL_Texture* weaponHud = nullptr;
	SDL_Texture* super = nullptr;

	Animation* current_animation = nullptr;
	Animation* fire_current = nullptr;

	int font_score = -1;
	int type_score = -1;
	int p2_title = -1;
	int highscore_font = -1;
	char score_text[10];

	SDL_Rect up1 = { 94, 87, 27, 15 };
	SDL_Rect up2 = { 94, 66, 27, 15 };
	SDL_Rect down1 = { 94, 131, 27, 16 };
	SDL_Rect down2 = { 94, 153, 27, 17 };
	
	SDL_Rect HUD1;
	SDL_Rect HUD2;
	SDL_Rect HUD3;
	SDL_Rect HUD4;
	SDL_Rect Life;
	SDL_Rect beamCharger;

	Animation idle;
	Animation up;
	Animation down;

	Animation fire_idle;
	Animation fire_up1;
	Animation fire_up2;
	Animation fire_down1;
	Animation fire_down2;

	iPoint position, fire_position;
	uint laser1, laser2, laser3, laser4;
	uint player_death, type_change;
	uint type = 0;

	Uint32 startTime = 0, currentTime;
	bool activatedChange; //Tells if the player is changing of weapon

	int lives = 2;

	uint y = 0;
	Collider* player = nullptr;
	bool GodMode = false;
};

#endif