#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

enum bullet_type {
	TYPE_1,
	TYPE_2,
	TYPE_3,
	TYPE_4
};

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
	Animation* fire_current = nullptr;

	SDL_Rect up1 = { 94, 87, 27, 15 };
	SDL_Rect up2 = { 94, 66, 27, 15 };
	SDL_Rect down1 = { 94, 131, 27, 16 };
	SDL_Rect down2 = { 94, 153, 27, 17 };

	Animation idle;
	Animation up;
	Animation down;

	Animation fire_idle;
	Animation fire_up1;
	Animation fire_up2;
	Animation fire_down1;
	Animation fire_down2;

	int t = 0, t_2 = 0;
	bool enable;

	iPoint position, fire_position;
	uint laser1, laser2, laser3, laser4; // main weap of each type
	uint missile1, missile2, missile3, missile4; // second weap of each type
	uint player_death, type_change;
	uint type = bullet_type::TYPE_1;

	int lives = 2;
	int ShootPowerUpLevel = 1, ShootPowerUpLevel_2 = 0, HomingMissile = 0, Shield = 0;


	uint y = 0;
	Collider* player = nullptr;
	bool GodMode = false;
};

#endif // __MODULEPLAYER_H__
