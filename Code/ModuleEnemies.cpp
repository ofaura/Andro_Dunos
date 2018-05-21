#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Enemy.h"
#include "Enemy_FirstEnemy.h"
#include "Enemy_PowerUp.h"
#include "Enemy_Shuttle.h"
#include "Enemy_Pipeliner.h"
#include "Enemy_MissileThrower.h"
#include "Enemy_Spinner.h"
#include "Enemy_Spinner_Up.h"
#include "Enemy_Spinner_Down.h"
#include "Enemy_Meteorite.h"
#include "Enemy_LittleTurretUp.h"
#include "Enemy_LittleTurretDown.h"
#include "Enemy_GreenMissile1.h"
#include "Enemy_GreenMissile2.h"
#include "Enemy_GreenPlane.h"
#include "Enemy_SolarPanel.h"
#include "Enemy_Spaceship.h"
#include "Enemy_Beyblade.h"
#include "Enemy_Circle.h"
#include "Enemy_Xwing.h"
#include "Enemy_Beyblade.h"
#include "Enemy_Wasp.h"
#include "Enemy_Mine.h"
#include "Enemy_NinjaBall.h"
#include "PowerUp.h"

#define SPAWN_MARGIN 25

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Assets/Sprites/Enemies/enemies.png");

	//Audios are loaded
	small_enemy_death = App->audio->LoadFx("Assets/Audio/Sound FX/enemy_small_explosion.wav");
	medium_enemy_death = App->audio->LoadFx("Assets/Audio/Sound FX/enemy_medium_explosion.wav");
	greenRocket = App->audio->LoadFx("Assets/Audio/Sound FX/greenRockets_launched.wav");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) //if (queue[i].x > App->render->camera.x)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");
	App->audio->UnLoadFx(greenRocket);
	App->audio->UnLoadFx(medium_enemy_death);
	App->audio->UnLoadFx(small_enemy_death);
	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{

		case ENEMY_TYPES::FIRST_ENEMY:
			enemies[i] = new Enemy_FirstEnemy(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_POWERUP:
			enemies[i] = new Enemy_PowerUp(info.x, info.y);
			break;

		case ENEMY_TYPES::POWERUP:
			enemies[i] = new PowerUp(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_METEORITE:
			enemies[i] = new Enemy_Meteorite(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_SHUTTLE:
			enemies[i] = new Enemy_Shuttle(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_CIRCLE:
			enemies[i] = new Enemy_Circle(info.x, info.y);
			break;

		case ENEMY_TYPES::MISSILE_THROWER:
			enemies[i] = new Enemy_MissileThrower(info.x, info.y);
			break;

		case ENEMY_TYPES::LITTLE_TURRET_UP:
			enemies[i] = new Enemy_LittleTurretUp(info.x, info.y);
			break;

		case ENEMY_TYPES::LITTLE_TURRET_DOWN:
			enemies[i] = new Enemy_LittleTurretDown(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_SPACESHIP:
			enemies[i] = new Enemy_SpaceShip(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_WASP:
			enemies[i] = new Enemy_Wasp(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_SPINNER:
			enemies[i] = new Enemy_Spinner(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_SPINNER_UP:
			enemies[i] = new Enemy_Spinner_Up(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_SPINNER_DOWN:
			enemies[i] = new Enemy_Spinner_Down(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_MINE:
			enemies[i] = new Enemy_Mine(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_BEYBLADE:
			enemies[i] = new Enemy_Beyblade(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_XWING:
			enemies[i] = new Enemy_Xwing(info.x, info.y);
			break;

		case ENEMY_TYPES::ENEMY_PIPELINER:
			enemies[i] = new Enemy_Pipeliner(info.x, info.y);
			break;

		case ENEMY_TYPES::SOLAR_PANEL:
			enemies[i] = new Enemy_SolarPanel(info.x, info.y);
			break;

		case ENEMY_TYPES::GREEN_PLANE:
			enemies[i] = new Enemy_GreenPlane(info.x, info.y);
			break;

		case ENEMY_TYPES::GREEN_MISSILE1:
			enemies[i] = new Enemy_GreenMissile1(info.x, info.y);
			break;		

		case ENEMY_TYPES::GREEN_MISSILE2:
			enemies[i] = new Enemy_GreenMissile2(info.x, info.y);
			break;

		case ENEMY_TYPES::NINJA_BALL:
			enemies[i] = new Enemy_NinjaBall(info.x, info.y);
			break;
		}
	}
}


void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2);
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}