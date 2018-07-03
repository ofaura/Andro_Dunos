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

#define SPEED (4)

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
	homing_missile.life = 2500;


	ultimates[0][0].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Down
	ultimates[0][0].anim.loop = false;
	ultimates[0][0].speed.x = 1;
	ultimates[0][0].speed.y = SPEED;
	ultimates[0][0].life = 1000;
	ultimates[0][0].stage = 1;

	ultimates[0][1].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Up
	ultimates[0][1].anim.loop = false;
	ultimates[0][1].speed.x = 1;
	ultimates[0][1].speed.y = -1 * SPEED;
	ultimates[0][1].life = 1000;
	ultimates[0][1].stage = 1;


	/*
	ultimates[1][0].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Down
	ultimates[1][0].anim.loop = false;
	ultimates[1][0].speed.x = 1;
	ultimates[1][0].speed.y = SPEED;
	ultimates[1][0].life = 500;
	ultimates[1][0].stage = 2;

	ultimates[1][1].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Up
	ultimates[1][1].anim.loop = false;
	ultimates[1][1].speed.x = 1;
	ultimates[1][1].speed.y = -1 * SPEED;
	ultimates[1][1].life = 250;
	ultimates[1][1].stage = 2;

	ultimates[2][0].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Down
	ultimates[2][0].anim.loop = false;
	ultimates[2][0].speed.x = 1;
	ultimates[2][0].speed.y = SPEED;
	ultimates[2][0].life = 250;
	ultimates[2][0].stage = 3;

	ultimates[2][1].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Up
	ultimates[2][1].anim.loop = false;
	ultimates[2][1].speed.x = 1;
	ultimates[2][1].speed.y = -1 * SPEED;
	ultimates[2][1].life = 250;
	ultimates[2][1].stage = 3;

	ultimates[3][0].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Down
	ultimates[3][0].anim.loop = false;
	ultimates[3][0].speed.x = 1;
	ultimates[3][0].speed.y = SPEED;
	ultimates[3][0].life = 250;
	ultimates[3][0].stage = 4;

	ultimates[3][1].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Up
	ultimates[3][1].anim.loop = false;
	ultimates[3][1].speed.x = 1;
	ultimates[3][1].speed.y = -1 * SPEED;
	ultimates[3][1].life = 250;
	ultimates[3][1].stage = 4;

	ultimates[4][0].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Down
	ultimates[4][0].anim.loop = false;
	ultimates[4][0].speed.x = 1;
	ultimates[4][0].speed.y = SPEED;
	ultimates[4][0].life = 250;
	ultimates[4][0].stage = 5;

	ultimates[4][1].anim.PushBack({ 496, 25, 18, 18 }); // Ball, Up
	ultimates[4][1].anim.loop = false;
	ultimates[4][1].speed.x = 1;
	ultimates[4][1].speed.y = -1 * SPEED;
	ultimates[4][1].life = 250;
	ultimates[4][1].stage = 5;
	*/
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


/*
App->particles->AddParticle(App->particles->ultimates[0][0], position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
App->particles->AddParticle(App->particles->ultimates[0][1], position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
App->particles->AddParticle(App->particles->ultimates[0][2], position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
App->particles->AddParticle(App->particles->ultimates[0][3], position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
App->particles->AddParticle(App->particles->ultimates[0][4], position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
App->particles->AddParticle(App->particles->ultimates[0][5], position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
App->particles->AddParticle(App->particles->ultimates[0][6], position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
*/

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
			p->collider_type = collider_type;
			// (Module*)App->enemies
			p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleShotGravity::AddUltimate(int x, int y, Accel_Shot_Type type, COLLIDER_TYPE collider_type)
{

	switch (type)
	{
	case ULTIMATE_1:

		break;

	case ULTIMATE_2:
		App->particles->AddParticle(App->particles->ultimates[0][0], x + 10, y, collider_type);
		App->particles->AddParticle(App->particles->ultimates[0][1], x + 10, y, collider_type);
		App->particles->AddParticle(App->particles->ultimates[0][2], x + 10, y, collider_type);
		App->particles->AddParticle(App->particles->ultimates[0][3], x + 10, y, collider_type);
		App->particles->AddParticle(App->particles->ultimates[0][4], x + 10, y, collider_type);
		App->particles->AddParticle(App->particles->ultimates[0][5], x + 10, y, collider_type);
		App->particles->AddParticle(App->particles->ultimates[0][6], x + 10, y, collider_type);
		break;

	case ULTIMATE_3:

		break;

	case ULTIMATE_4:

		if (stage == 10)
		{ 
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 25, y, collider_type);
		}
		
		else if (stage == 9)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 60, y - 15, collider_type); // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 60, y + 15, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 60, y, collider_type);
		}

		else if (stage == 8)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 95, y - 30, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 95, y + 30, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 95, y, collider_type);
		}

		else if (stage == 7)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 130, y - 40, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 130, y + 40, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 130, y, collider_type);
		}

		else if (stage == 6)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 165, y - 50, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 165, y + 50, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 165, y, collider_type);
		}

		else if (stage == 5)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 200, y - 60, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 200, y + 60, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 200, y, collider_type);
		}

		else if (stage == 4)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 235, y - 70, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 235, y + 70, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 235, y, collider_type);
		}

		else if (stage == 3)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 270, y - 80, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 270, y + 80, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 270, y, collider_type);
		}

		else if (stage == 2)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 305, y - 90, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 305, y + 90, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 305, y, collider_type);
		}

		else if (stage == 1)
		{
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 340, y - 100, collider_type); // x = x_prev + 35; // x = x_prev + 35, y = y_prev + 15;
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 340, y + 100, collider_type);
			App->particles->AddParticle(App->particles->ultimates[1][0], x + 340, y, collider_type);
		}
		break;
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

				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);

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
	fx(p.fx), born(p.born), life(p.life), time_1(0), time_2(0), speed(p.speed)
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
			if (enemy == nullptr || (enemy->position.x <= ((abs(App->render->camera.x) / SCREEN_SIZE) + 40)) &&
				(enemy->position.x >= ((abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH)))
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
				else if (enemy->position.x <= position.x) { left_ = -1; }

				if (enemy->position.y >= position.y) { down_ = 1; }
				else if (enemy->position.y <= position.y) { down_ = -1; }


				dif_pos[x] = enemy->position.x - position.x;
				dif_pos[y] = enemy->position.y - position.y;

				if (dif_pos[y] == 0)
				{
					vel[y] = 0;
					vel[x] = 5 + 1;
				}

				else
				{
					div = abs(dif_pos[x] / dif_pos[y]);
					vel[y] = down_ * sqrt(pow(5, 2) / (1 + pow(div, 2)));
					vel[x] = (left_ * (div)*vel[y]) + 1;
				}

				

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

			time_1++;

			if (time_1 >= 5)
			{
				time_2++;
			}
	}

	else if (type == ULTIMATE_1)
	{
		if (collider_type == COLLIDER_ULTIMATES)
		{
			if (App->player->turn_ultimate[0][0] == 1 || App->player->turn_ultimate[0][0] == 3)
			{
				if (abs(App->player->ulti_y - position.y) >= 8) // dis
				{
					if (App->player->ulti_y - position.y > 0)
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y - 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}
					else
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y + 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}

					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 8, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0]++;
				}
			}
			else if (App->player->turn_ultimate[0][0] == 2)
			{
				if (abs(App->player->ulti_y - position.y) >= 30) // dis
				{
					if (App->player->ulti_y - position.y > 0)
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], App->player->ulti_y + 30, App->player->ulti_y - 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES); // x = 30, y = +- 5;
					}
					else
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], App->player->ulti_y + 30, App->player->ulti_y + 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}

					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 8, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0]++;
				}
			}
			else if (App->player->turn_ultimate[0][0] == 4)
			{
				if (abs(App->player->ulti_y - position.y) >= 52) // dis
				{
					if (App->player->ulti_y - position.y > 0)
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], App->player->ulti_y + 30, App->player->ulti_y - 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES); // x = 30, y = +- 5;
					}
					else
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], App->player->ulti_y + 30, App->player->ulti_y + 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}

					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 8, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0]++;
				}
			}
			else if (App->player->turn_ultimate[0][0] == 5)
			{
				if (abs(App->player->ulti_y - position.y) >= 30) // dis
				{
					if (App->player->ulti_y - position.y > 0)
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y - 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}
					else
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y + 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}

					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 8, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0]++;
				}
			}

			else if (App->player->turn_ultimate[0][0] == 6)
			{
				if (abs(App->player->ulti_y - position.y) >= 8) // dis
				{
					if (App->player->ulti_y - position.y > 0)
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y - 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}
					else
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y + 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}

					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 8, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0]++;
				}
			}

			else if (App->player->turn_ultimate[0][0] == 7)
			{
				if (abs(App->player->ulti_y - position.y) >= 52) // dis
				{
					if (App->player->ulti_y - position.y > 0)
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], App->player->ulti_y + 30, App->player->ulti_y - 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES); // x = 30, y = +- 5;
					}
					else
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], App->player->ulti_y + 30, App->player->ulti_y + 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}

					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 8, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0]++;
				}
			}

			else if (App->player->turn_ultimate[0][0] == 8)
			{
				if (abs(App->player->ulti_y - position.y) >= 30) // dis
				{
					if (App->player->ulti_y - position.y > 0)
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y - 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}
					else
					{
						App->accel_shot->AddShot(App->accel_shot->ultimates[0][0], position.x, position.y + 5, ULTIMATE_1, 1, 1, COLLIDER_ULTIMATES);
					}

					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 8, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0]++;
				}
			}

			if (App->player->turn_ultimate[0][0] >= 9)
			{
				if (abs(App->player->ulti_y - position.y) >= 52) // dis
				{
					App->particles->AddParticle(App->particles->ultimates[2][2], position.x + 18, position.y, collider_type);
					ret = false;
					App->player->turn_ultimate[0][0] = 1;
					App->player->enable_ultimate = false;
				}
			}

		}
		else if (collider_type == COLLIDER_ULTIMATES_P2)
		{
		
		}
		
		//App->player->ulti_x++;
		//App->player2->ulti_x, do it when it exists
		position.x += speed.x;
		position.y += speed.y;
	}
	

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
