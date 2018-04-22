#include "Application.h"
#include "PowerUp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleShield.h"
#include "ModuleAudio.h"

#include <cstdio>
#include <cstdlib>
#include <time.h>

enum Stages
{
	STILL_1 = 0,
	REFLECTION_1,
	CHANGE_1,
	STILL_2,
	REFLECTION_2,
	CHANGE_2
};

PowerUp::PowerUp(int x, int y) : Enemy(x, y)
{
	srand(1); // doesn't let me do time(NULL)

	powerup_picked = App->audio->LoadFx("Assets/Audio/powerup_picked.wav");

	int random = rand() % 2;

	if (random == 0)
	{
		S_B = true;

		fly_1.PushBack({ 10, 558, 16, 16 }); // still
		fly_1.loop = true;
		act[0] = &fly_1;

		fly_2.PushBack({ 29, 558, 16, 16 }); // reflection
		fly_2.PushBack({ 47, 558, 16, 16 });
		fly_2.PushBack({ 65, 558, 16, 16 });
		fly_1.PushBack({ 10, 558, 16, 16 });
		fly_2.speed = 0.15f;
		fly_2.loop = false;
		act[1] = &fly_2;

		fly_3.PushBack({ 83, 558, 16, 16 }); // Change
		fly_3.PushBack({ 101, 558, 16, 16 });
		fly_3.PushBack({ 101, 622, 16, 16 });
		fly_3.PushBack({ 83, 540, 16, 16 });
		fly_3.PushBack({ 101, 540, 16, 16 });
		fly_4.PushBack({ 10, 540, 16, 16 });
		fly_3.speed = 0.6f;
		fly_3.loop = false;
		act[2] = &fly_3;


		fly_4.PushBack({ 10, 540, 16, 16 }); // still
		fly_4.loop = true;
		act[3] = &fly_4;

		fly_5.PushBack({ 29, 540, 16, 16 }); // reflection
		fly_5.PushBack({ 47, 540, 16, 16 });
		fly_5.PushBack({ 65, 540, 16, 16 });
		fly_4.PushBack({ 10, 540, 16, 16 });

		fly_5.speed = 0.15f;
		fly_5.loop = false;

		act[4] = &fly_5;

		fly_6.PushBack({ 83, 540, 16, 16 }); // Change
		fly_6.PushBack({ 101, 540, 16, 16 });
		fly_6.PushBack({ 101, 622, 16, 16 });
		fly_6.PushBack({ 83, 558, 16, 16 });
		fly_6.PushBack({ 101, 558, 16, 16 });
		fly_4.PushBack({ 10, 540, 16, 16 });

		fly_6.speed = 0.6f;
		fly_6.loop = false;

		act[5] = &fly_6;
	}

	else if (random == 1)
	{

		B_M = true;

		fly_1.PushBack({ 10, 540, 16, 16 }); // still
		fly_1.loop = true;
		act[0] = &fly_1;

		fly_2.PushBack({ 29, 540, 16, 16 }); // reflection
		fly_2.PushBack({ 47, 540, 16, 16 });
		fly_2.PushBack({ 65, 540, 16, 16 });
		fly_2.PushBack({ 10, 540, 16, 16 });

		fly_2.speed = 0.15f;
		fly_2.loop = false;

		act[1] = &fly_2;

		fly_3.PushBack({ 83, 540, 16, 16 }); // Change
		fly_3.PushBack({ 101, 540, 16, 16 });
		fly_3.PushBack({ 101, 622, 16, 16 }); ///
		fly_3.PushBack({ 83, 594, 16, 16 });
		fly_3.PushBack({ 101, 594, 16, 16 });
		fly_3.PushBack({ 10, 594, 16, 16 });

		fly_3.speed = 0.6f;
		fly_3.loop = false;

		act[2] = &fly_3;


		fly_4.PushBack({ 10, 594, 16, 16 }); // still
		fly_4.loop = true;
		act[3] = &fly_4;

		fly_5.PushBack({ 29, 594, 16, 16 }); // reflection
		fly_5.PushBack({ 47, 594, 16, 16 });
		fly_5.PushBack({ 65, 594, 16, 16 });
		fly_5.PushBack({ 10, 594, 16, 16 });
		fly_5.speed = 0.15f;
		fly_5.loop = false;
		act[4] = &fly_5;

		fly_6.PushBack({ 83, 594, 16, 16 }); // Change
		fly_6.PushBack({ 101, 594, 16, 16 });
		fly_6.PushBack({ 101, 622, 16, 16 }); ///
		fly_6.PushBack({ 83, 594, 16, 16 });
		fly_6.PushBack({ 101, 594, 16, 16 });
		fly_6.PushBack({ 10, 594, 16, 16 });
		fly_6.speed = 0.6f;
		fly_6.loop = false;
		act[5] = &fly_6;
	}

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);

	original_y = y;
}

void PowerUp::Draw(SDL_Texture* sprites)
{
	if (time >= 0 && time < 400)
	{
		if (time >= 200 && time < 225)
		{
			App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[REFLECTION_1]->GetCurrentFrame()));
		}
		else
		{
			App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[STILL_1]->GetCurrentFrame()));
		}
	}

	else if (time >= 400 && time < 425)
	{
		App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[CHANGE_1]->GetCurrentFrame()));
	}

	else if (time >= 425 && time < 825)
	{
		if (time >= 625 && time < 650)
		{
			App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[REFLECTION_2]->GetCurrentFrame()));
		}
		else
		{
			App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[STILL_2]->GetCurrentFrame()));
		}
	}

	else if (time >= 825 && time < 850)
	{
		App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(act[CHANGE_2]->GetCurrentFrame()));
	}

	else if (time >= 850)
	{
		for (int counter = 0; counter < CHANGE_2 + 1; counter++)
		{
			act[counter]->Reset();
		}

		time = -1;
	}

	collider->SetPos(position.x, position.y);

	time++;
}

void PowerUp::Move()
{
	//x lim
	if (position.x < abs(App->render->camera.x) / SCREEN_SIZE)
	{
		vel_x = -1 * vel_x;
		position.x = App->render->camera.x / SCREEN_SIZE;
	}
	else if (position.x > ((abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - 16))
	{
		vel_x = -1 * vel_x;
	}

	//y lim

	if (position.y < abs(App->render->camera.y) / SCREEN_SIZE)
	{
		vel_y = -1 * vel_y;
	}
	else if (position.y > (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 16)
	{
		vel_y = -1 * vel_y;
	}

	position.y += vel_y;
	position.x += vel_x;

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

void PowerUp::OnCollision(Collider* collider)
{
	if ((collider->type == COLLIDER_PLAYER))
	{
		App->shield->Enable();
		App->audio->PlayFx(powerup_picked);

	}
	else if (collider->type == COLLIDER_PLAYER_2)
	{

	}
}

bool PowerUp::CleanUp() {
	LOG("Unloading Powerup");
	App->audio->UnLoadFx(powerup_picked);

	return true;
}

