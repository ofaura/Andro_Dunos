#include "Application.h"
#include "Enemy_PowerUp.h"
#include "ModuleEnemies.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

enum SHIP_ACT
{
	LEFT = 0,
	TURN_1,
	LEFT_DOWN,
	TURN_2,
	LEFT_UP,
	TURN_3,
	RIGHT,
	TURN_4,
};

Enemy_PowerUp::Enemy_PowerUp(int x, int y) : Enemy(x, y)
{
	fly_1.PushBack({ 1,270,18,26 }); // left - iddle
	fly_1.PushBack({ 27,270,18,26 }); //  left - move
	fly_1.speed = 0.4f;

	act[LEFT] = &fly_1;

	fly_2.PushBack({ 53,270,18,25 }); // 1st turn
	fly_2.PushBack({ 79,270,18,26 });
	fly_2.speed = 0.1f;
	fly_2.loop = 0.1f;

	act[TURN_1] = &fly_2;

	fly_3.PushBack({ 79, 270, 18, 25 }); // (left, down) - idle
	fly_3.PushBack({ 104,271,20,26 }); // (left, down) - move
	fly_3.speed = 0.4f;

	act[LEFT_DOWN] = &fly_3;


	fly_4.PushBack({ 1,315,18,26 }); // 2nd turn
	fly_4.PushBack({ 27,315,18,25 });
	fly_4.PushBack({ 53,315,18,25 });
	fly_4.speed = 0.1f;
	fly_4.loop = false;

	act[TURN_2] = &fly_4;

	fly_5.PushBack({ 105,315,20,26 }); // (left, up) - idle
	fly_5.PushBack({ 79,315,18,25 }); // (left,up) - move
	fly_5.speed = 0.4f;
	fly_5.loop = true;

	act[LEFT_UP] = &fly_5;

	fly_6.PushBack({ 1,359,21,21 }); // 3rd turn
	fly_6.PushBack({ 24,359,26,18 });
	fly_6.PushBack({ 49,359,26,18 });
	fly_6.PushBack({ 76,359,25,19 });
	fly_6.PushBack({ 102,359,26,18 });
	fly_6.PushBack({ 1,387,21,21 });
	fly_6.PushBack({ 25,387,21,21 });
	fly_6.PushBack({ 53,384,18,25 });
	fly_6.PushBack({ 81,384,18,25 });
	fly_6.PushBack({ 107,383,18,26 });
	fly_6.PushBack({ 1,413,18,26 });
	fly_6.PushBack({ 29,413,18,26 });
	fly_6.PushBack({ 54,413,18,26 });
	fly_6.speed = 0.25f;
	fly_6.loop = false;

	act[TURN_3] = &fly_6;

	fly_7.PushBack({ 80,413,18,26 }); // right - idle
	fly_7.PushBack({ 106,413,18,26 }); // right - move
	fly_7.speed = 0.4f;

	act[RIGHT] = &fly_7;


	fly_8.PushBack({ 6,451,18,24 }); // 4th turn
	fly_8.PushBack({ 28,454,21,21 });
	fly_8.PushBack({ 52,455,22,18 });
	fly_8.PushBack({ 75,455,26,17 });
	fly_8.PushBack({ 101,455,26,18 });
	fly_8.PushBack({ 0,480,25,18 });
	fly_8.PushBack({ 25,480,25,18 });
	fly_8.PushBack({ 51,476,21,21 });
	fly_8.PushBack({ 78,476,21,21 });
	fly_8.PushBack({ 105,477,18,25 });
	fly_8.PushBack({ 5,502,18,25 });
	fly_8.PushBack({ 29,501,18,26 });
	fly_8.PushBack({ 55,501,18,26 });
	fly_8.PushBack({ 80,502,18,26 });
	fly_8.PushBack({ 106,502,18,26 });
	fly_8.speed = 0.4f;
	fly_8.loop = false;

	act[TURN_4] = &fly_8;

	collider = App->collision->AddCollider({ 0, 0, 20, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_PowerUp::Move()
{
	if (position.x >= ((abs(App->render->camera.x) / SCREEN_SIZE + (SCREEN_WIDTH - 30))))
	{
		position.x -= 1;
		App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[LEFT]->GetCurrentFrame()));
	}

	else
	{
		if (loop >= 0)
		{

			if (time >= 521)
			{
				for(int counter = 0; counter < TURN_4+1; counter++)
				{
					act[counter]->Reset();
				}
			}

			if (time >= 0 && time < 75)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[LEFT]->GetCurrentFrame()));
			}

			else if (time >= 75 && time < 125)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[LEFT]->GetCurrentFrame()));
				position.x -= 1;
			}
			else if (time >= 125 && time < 150)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[TURN_1]->GetCurrentFrame()));

			}
			else if (time >= 150 && time < 200)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[LEFT_DOWN]->GetCurrentFrame()));
				position.x -= 1;
				position.y += 1;
			}

			else if (time >= 200 && time < 225)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[TURN_2]->GetCurrentFrame()));
			}
			else if (time >= 225 && time < 275)
			{
				act[TURN_2]->Reset();
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[LEFT_UP]->GetCurrentFrame()));
				position.x -= 1;
				position.y -= 1;
			}
			else if (time >= 275 && time < 325)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[TURN_3]->GetCurrentFrame()));
			}
			else if (time >= 325 && time < 470)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[RIGHT]->GetCurrentFrame()));
				position.x += 1;
			}
			else if (time >= 470 && time < 520)
			{
				App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[TURN_4]->GetCurrentFrame()));
				
			}

			else if (time >= 520)
			{
				loop--;
			}

			time++;
		}

		else
		{
			App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[LEFT]->GetCurrentFrame()));
			position.x -= 1;
		}

		//Up
		if (App->render->camera.x >= 7150 * SCREEN_SIZE && App->render->camera.x <= 7200 * SCREEN_SIZE && App->render->camera.y >= 0)
		{
			position.y -= 1;
		}

		// Diagonal up
		else if (App->render->camera.x >= 4005 * SCREEN_SIZE && App->render->camera.x < 4130 * SCREEN_SIZE || App->render->camera.x >= 5074 * SCREEN_SIZE && App->render->camera.x < 5290 * SCREEN_SIZE)
		{
			position.y -= 1;
			position.x += 1;
		}

		// Diagonal down
		else if (App->render->camera.y >= 96 * SCREEN_SIZE && App->render->camera.x >= 4530 * SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE ||
			App->render->camera.x >= 6125 * SCREEN_SIZE && App->render->camera.x < 6262 * SCREEN_SIZE)
		{
			position.y += 1;
			position.x += 1;
		}

		//Down
		else if (App->render->camera.x >= 2921 * SCREEN_SIZE && App->render->camera.x <= 2971 * SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE)
		{
			position.y += 1;
		}

		//Horizontal
		else if (App->render->camera.x >= 0 && App->render->camera.x <= 8800 * SCREEN_SIZE)
		{
			position.x += 1;
		}

	}


}

void Enemy_PowerUp::Draw(SDL_Texture* sprites)
{
	collider->SetPos(position.x, position.y);
}

void Enemy_PowerUp::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER_SHOT || (collider->type == COLLIDER_PLAYER) || (collider->type == COLLIDER_PLAYER_2))
	{
		App->enemies->AddEnemy(ENEMY_TYPES::POWERUP, position.x, position.y);
		App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y);
	}
	
}