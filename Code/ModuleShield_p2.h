#ifndef _MODULE_SHIELD_2_H_
#define _MODULE_SHIELD_2_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleShield.h"

struct SDL_Texture;

class ModuleShield_p2 : public Module {

	public:
		ModuleShield_p2();
		~ModuleShield_p2();

		void OnCollision(Collider* col_1, Collider* col_2);
		bool Start();
		update_status Update();
		bool CleanUp();
		int HP;

	public:
		SDL_Texture * graphics = nullptr;

		Animation base_anim, lvl1, lvl2, lvl3;
		Animation rotation_lvl1[ROT_STEPS];
		Animation rotation_level[ROT_STEPS];

		Animation* current_lvl;
		int timer;

		Collider* collider1;
		Collider* collider2;

		iPoint position1_, position2_;
		iPoint pos1_t1_[8], pos2_t1_[8];
		int circ;
		//int life = 3;
};

#endif // !_MODULE_SHIELD_
