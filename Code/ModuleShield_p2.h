#ifndef _MODULE_SHIELD_P2_H_
#define _MODULE_SHIELD_P2_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleShield_p2 : public Module {
public:
	ModuleShield_p2();
	~ModuleShield_p2();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* col_1, Collider* col_2);

public:
	SDL_Texture* graphics = nullptr;

	Animation base_anim, lvl1, lvl2, lvl3;
	Animation* current_lvl;

	Collider* collider1;
	Collider* collider2;

	iPoint position1, position2;
	int life = 3;

};

#endif // !_MODULE_SHIELD_H_