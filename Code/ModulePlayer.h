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
	SDL_Texture* missile_graphics = nullptr;
	SDL_Texture* backflame = nullptr;

	Animation* current_animation = nullptr;
	Animation* fire_current = nullptr;

	SDL_Rect up1 = { 94, 87, 27, 15 };
	SDL_Rect up2 = { 94, 66, 27, 15 };
	SDL_Rect down1 = { 94, 131, 27, 16 };
	SDL_Rect down2 = { 94, 153, 27, 17 };


	Animation idle;
	Animation respawn;
	Animation respawn_up;
	Animation respawn_down;
	Animation up;
	Animation down;

	Animation fire_idle;
	Animation fire_up1;
	Animation fire_up2;
	Animation fire_down1;
	Animation fire_down2;

	iPoint position, fire_position;
	uint laser1, laser2, laser3, laser4; // main weap of each type

	uint missile1, missile2, missile3, missile4; // second weap of each type
	Animation ani_miss_down, ani_miss_up;
	Animation* missile[2];
	uint player_death, type_change;

	int t, t_2, t_ani, ini_up, ini_down;
	int t_missile;
	int  ini_up_prime, ini_down_prime, t_ani_prime;
	bool enable_missile1, allow;
	bool enable_ultimate;
	int turn_ultimate[4][2];
	int turn_ulti;
	int t_ultimate[3];
	int ulti_x, ulti_y;


	uint type = bullet_type::TYPE_1;
	uint type_ulti;
	int lives = 2;
	int ShootPowerUpLevel = 1, ShootPowerUpLevel_2 = 0, HomingMissile = 0, Shield = 0;

	int damage_1 = 1, damage_2 = 1;
	int current_time = 0;
	int first_time = 0;
	bool dead = false;
	bool respawning = false;
	bool collision = true;
	
	uint y = 0;
	Collider* player = nullptr;
	bool GodMode = false;
};

#endif // __MODULEPLAYER_H__
