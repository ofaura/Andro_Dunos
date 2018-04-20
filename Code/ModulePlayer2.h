#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* col_1, Collider* col_2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	
	int font_score = -1;
	int type_score = -1;
	char score_text[10];

	Animation idle;
	Animation up;
	Animation down;

	iPoint position;
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