#ifndef __ModuleEnemies_H__
#define __ModuleEnemies_H__

#include "Module.h"

#define MAX_ENEMIES 200

enum ENEMY_TYPES
{
	NO_TYPE,
	FIRST_ENEMY,
	ENEMY_POWERUP,
	POWERUP,
	ENEMY_METEORITE,
	ENEMY_SHUTTLE,
	ENEMY_SPACESHIP,
	ENEMY_CIRCLE,
	MISSILE_THROWER,
	LITTLE_TURRET_UP,
	LITTLE_TURRET_DOWN,
	ENEMY_WASP,
	ENEMY_SPINNER,
	ENEMY_MINE,
	ENEMY_XWING,
	ENEMY_BEYBLADE,
	ENEMY_PIPELINER,
	SOLAR_PANEL
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	uint small_enemy_death;
	uint medium_enemy_death;

	bool AddEnemy(ENEMY_TYPES type, int x, int y);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__