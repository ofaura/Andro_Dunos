#ifndef _MODULE_SHOT_GRAVITY_
#define _MODULE_SHOT_GRAVITY_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "Enemy.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 1000

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

enum Accel_Shot_Type
{
	GRAVITY_SHOT = 0,
	HOMING_MISSILE,
	ULTIMATE_1,
	ULTIMATE_2,
	ULTIMATE_3,
	ULTIMATE_4

};

struct Accel_Shot
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	int damage;
	int time_1, time_2;
	int up = 1;
	int left = 1;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	int stage;
	Accel_Shot_Type type;
	COLLIDER_TYPE collider_type;
	Enemy* enemy;
	bool target_aquired;

	Accel_Shot();
	Accel_Shot(const Accel_Shot& p);
	~Accel_Shot();
	bool Update();
	bool go;
};

class ModuleShotGravity : public Module
{
public:
	ModuleShotGravity();
	~ModuleShotGravity();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddUltimate(int x, int y, Accel_Shot_Type type, COLLIDER_TYPE collider_type);
	void AddShot(const Accel_Shot& particle, int x, int y, Accel_Shot_Type type, int up , int left, COLLIDER_TYPE collider_type, Uint32 delay = 0);
	void AddShot(const Accel_Shot& particle, int x, int y, Accel_Shot_Type type, COLLIDER_TYPE collider_type, Uint32 delay = 0);

	bool center;
	int stage;
	Animation g_shot;
	Accel_Shot gravity_shot, gravity_shot_2;
	Accel_Shot homing_missile, ultimates[5][2], ultimates_;
	Accel_Shot* active[MAX_ACTIVE_PARTICLES];

private:


	SDL_Texture * graphics = nullptr;
	SDL_Texture* enemy_death = nullptr;

};
#endif // !_MODULE_SHIELD_
