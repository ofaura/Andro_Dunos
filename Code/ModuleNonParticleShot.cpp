#include <math.h>
#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleNonParticleShot.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "time.h"
#include <stdio.h> 
#include <stdlib.h> 

#include "SDL/include/SDL_timer.h"

enum Pos
{
	x = 0,
	y
};

ModuleShotGravity::ModuleShotGravity()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleShotGravity::~ModuleShotGravity()
{}

// Load assets
bool ModuleShotGravity::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Sprites/Particles/particles.png");
	
	gravity_shot.anim.PushBack({ 386, 30, 8, 9 });
	gravity_shot.anim.loop = false;
	gravity_shot.anim.speed = 1.0f;
	gravity_shot.life = 2000;

	gravity_shot_2.anim.PushBack({ 386, 15, 8, 9 });
	gravity_shot_2.anim.loop = false;
	gravity_shot_2.anim.speed = 1.0f;
	gravity_shot_2.life = 2000;

	homing_missile.anim.PushBack({ 338, 15, 10, 9 });
	homing_missile.anim.loop = false;
	homing_missile.anim.speed = 1.0f;
	homing_missile.life = 9000;

	return true;
}

// Unload assets
bool ModuleShotGravity::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleShotGravity::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Accel_Shot* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				//Play your fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleShotGravity::AddShot(const Accel_Shot& particle, int x, int y, Accel_Shot_Type type, int up, int left, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Accel_Shot* p = new Accel_Shot(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->type = type;
			p->up = up;
			p->left = left;
			// (Module*)App->enemies
			if (type == GRAVITY_SHOT || type == HOMING_MISSILE)
			{
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			}
			active[i] = p;
			break;
		}
	}
}

void ModuleShotGravity::AddShot(const Accel_Shot& particle, int x, int y, Accel_Shot_Type type, COLLIDER_TYPE collider_type, Uint32 delay)
{
	srand(time(NULL));
	bool check = false;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Accel_Shot* p = new Accel_Shot(particle);
			p->target_aquired = false;
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->type = type;


			for (int counter = 0; counter < MAX_ENEMIES && p->target_aquired == false; counter++)
			{
				if (App->enemies->enemies[counter] != nullptr && App->enemies->enemies[counter]->type != POWER_UP)
				{
					if ((App->enemies->enemies[counter]->position.x >= ((abs(App->render->camera.x) / SCREEN_SIZE) + 40)) &&
						(App->enemies->enemies[counter]->position.x <= ((abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH)))

					{
						p->enemy = App->enemies->enemies[counter];
						check = true;
						//p->target_aquired = true;
					}
				}
			}

			if (check == false)
			{
				p->enemy = nullptr;
			}

			// (Module*)App->enemies
			if (type == GRAVITY_SHOT || type == HOMING_MISSILE)
			{
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			}
			active[i] = p;
			break;
		}


		
	}
}

// Every time a particle hits a wall it triggers an explosion particle
void ModuleShotGravity::OnCollision(Collider* c1, Collider* c2) // add Collider* c2, if problems arise
{

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			// Always destroy particles that collide
			delete active[i];
			active[i] = nullptr;
			break;

		}
	}
}


Accel_Shot::Accel_Shot()
{
	position.SetToZero();
}

Accel_Shot::Accel_Shot(const Accel_Shot& p) :
	anim(p.anim), position(p.position),
	fx(p.fx), born(p.born), life(p.life), time_1(0), time_2(2)
{}

Accel_Shot::~Accel_Shot()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Accel_Shot::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;
	
	//
	if (type == GRAVITY_SHOT)
	{
		if ((1 * time_2) / 2 >= 20)
		{
			position.y += up * 10;
		}
		else
		{
			position.y += 0.5 * (time_2 / 2)*up;
		}

		if (left == -1)
		{
			position.x += left * 2;
		}
		else
		{
			position.x += left * 3;
		}
	}

	else if (type == HOMING_MISSILE)
	{
			if (enemy == nullptr || (position.x <= ((abs(App->render->camera.x) / SCREEN_SIZE))) &&
				(position.x >= ((abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH)))
			{
				position.x += 1;
				position.y += 2;
			}
			else
			{
				// proces: start

				int dif_pos[2];
				int vel[2];
				int div;
				int left_, down_;


				if (enemy->position.x >= position.x) { left_ = 1; }
				else { left_ = -1; }

				if (enemy->position.y >= position.y) { down_ = 1; }
				else { down_ = -1; }


				dif_pos[x] = enemy->position.x - position.x;
				dif_pos[y] = enemy->position.y - position.y;

				if (dif_pos[y] == 0)
				{
					div = 0;
					vel[y] = 0;
				}

				else
				{
					div = abs(dif_pos[x] / dif_pos[y]);
					vel[y] = down_ * sqrt(pow(5, 2) / (1 + pow(div, 2)));
				}

				vel[x] = (left_ * (div)*vel[y]) + 1;

				if (vel[x] == 1 && vel[y] == 0)
				{
					position.x += 1;
					position.y += 2;
				}
				else
				{
					position.x += vel[x];
					position.y += vel[y];
				}
				// proces: end. the main velocity equations come from solving simple trigonometric problem on paper

			}

	}

	time_1++;

	if (time_1 >= 5)
	{
		time_2++;
	}
	//

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
