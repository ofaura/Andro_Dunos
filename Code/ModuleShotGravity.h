#ifndef _MODULE_SHOT_GRAVITY_
#define _MODULE_SHOT_GRAVITY_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#define ROT_STEPS (8)

struct SDL_Texture;

class ModuleShotGravity : public Module {
public:
	ModuleShotGravity();
	~ModuleShotGravity();

	void OnCollision(Collider* col_1);
	bool Start();
	update_status Move();
	bool CleanUp();

public:
	SDL_Texture * graphics = nullptr;
	int t_g;
	int up;
	Animation ani1, ani2;
	Animation* ani[2];

	Animation* current_lvl;
	int timer;

	Collider* collider1;

	iPoint position1, position2;
};

#endif // !_MODULE_SHIELD_
