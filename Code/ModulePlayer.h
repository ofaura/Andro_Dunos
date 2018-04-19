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
	Animation* current_animation = nullptr;

	int font_score = -1;
	char score_text[10];

	Animation idle;
	Animation up;
	Animation down;

	Animation fire_idle;
	Animation fire_up1;
	Animation fire_up2;
	Animation fire_down1;
	Animation fire_down2;

	iPoint position;
	uint laser1, laser2, laser3, laser4, player_death;
	uint type = 0;

	int lives = 2;

	uint y = 0;
	Collider* player = nullptr;
	bool GodMode = false;
};

#endif