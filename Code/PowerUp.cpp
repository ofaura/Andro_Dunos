#include "Application.h"
#include "PowerUp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
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
	srand(3);

	//int random = rand() % 4;

	int random = 0;

	if (random == 0)
	{
		S_B = true;

		fly_1.PushBack({ 10, 558, 16, 16 }); // still
		fly_1.loop = true;
		act[0] = &fly_1;

		fly_2.PushBack({ 29, 558, 16, 16 }); // reflection
		fly_2.PushBack({ 47, 558, 16, 16 });
		fly_2.PushBack({ 65, 558, 16, 16 });
		fly_2.speed = 0.1f;
		fly_2.loop = true;
		act[1] = &fly_2;

		fly_3.PushBack({ 83, 558, 16, 16 }); // Change
		fly_3.PushBack({ 101, 558, 16, 16 });
		fly_3.PushBack({ 101, 622, 16, 16 });
		fly_3.PushBack({ 83, 540, 16, 16 });
		fly_3.PushBack({ 101, 540, 16, 16 });
		fly_3.speed = 0.6f;
		fly_3.loop = false;
		act[2] = &fly_3;


		fly_4.PushBack({ 10, 540, 16, 16 }); // still
		fly_4.loop = true;
		act[3] = &fly_4;

		fly_5.PushBack({ 29, 540, 16, 16 }); // reflection
		fly_5.PushBack({ 47, 540, 16, 16 });
		fly_5.PushBack({ 65, 540, 16, 16 });

		fly_5.speed = 0.1f;
		fly_5.loop = true;

		act[4] = &fly_5;

		fly_6.PushBack({ 83, 540, 16, 16 }); // Change
		fly_6.PushBack({ 101, 540, 16, 16 });
		fly_6.PushBack({ 101, 622, 16, 16 });
		fly_6.PushBack({ 83, 558, 16, 16 });
		fly_6.PushBack({ 101, 558, 16, 16 });

		fly_6.speed = 0.6f;
		fly_6.loop = false;

		act[5] = &fly_6;
	}

	else if (random == 1)
	{
		B_M = true;


		fly_3.PushBack({ 10, 540, 16, 16 });
		fly_3.PushBack({ 10, 540, 16, 16 });
		fly_3.PushBack({ 10, 540, 16, 16 });//
		fly_3.PushBack({ 29, 540, 16, 16 });
		fly_3.PushBack({ 47, 540, 16, 16 });
		fly_3.PushBack({ 65, 540, 16, 16 });

		fly_3.speed = 0.4f;
		fly_3.loop = true;

		act[0] = &fly_3;

		fly_4.PushBack({ 83, 540, 16, 16 });
		fly_4.PushBack({ 101, 540, 16, 16 });

		fly_4.speed = 0.4f;
		fly_4.loop = false;

		act[1] = &fly_2;

		fly_1.PushBack({ 10, 594, 16, 16 });
		fly_1.PushBack({ 10, 594, 16, 16 });
		fly_1.PushBack({ 10, 594, 16, 16 });//
		fly_1.PushBack({ 29, 594, 16, 16 });
		fly_1.PushBack({ 47, 594, 16, 16 });
		fly_1.PushBack({ 65, 594, 16, 16 });

		fly_1.speed = 0.4f;
		fly_1.loop = true;

		act[2] = &fly_1;

		fly_2.PushBack({ 83, 594, 16, 16 });
		fly_2.PushBack({ 101, 594, 16, 16 });

		fly_2.speed = 0.4f;
		fly_2.loop = false;

		act[3] = &fly_2;
	}
	
	else if (random == 2)
	{
		M_U = true;


		fly_1.PushBack({ 10, 594, 16, 16 });
		fly_1.PushBack({ 10, 594, 16, 16 });
		fly_1.PushBack({ 10, 594, 16, 16 });//
		fly_1.PushBack({ 29, 594, 16, 16 });
		fly_1.PushBack({ 47, 594, 16, 16 });
		fly_1.PushBack({ 65, 594, 16, 16 });

		fly_1.speed = 0.4f;
		fly_1.loop = true;

		act[0] = &fly_1;

		fly_2.PushBack({ 83, 594, 16, 16 });
		fly_2.PushBack({ 101, 594, 16, 16 });

		fly_2.speed = 0.4f;
		fly_2.loop = false;

		act[1] = &fly_2;

		fly_3.PushBack({ 10, 576, 16, 16 });
		fly_3.PushBack({ 10, 576, 16, 16 });
		fly_3.PushBack({ 10, 576, 16, 16 });//
		fly_3.PushBack({ 29, 576, 16, 16 });
		fly_3.PushBack({ 47, 576, 16, 16 });
		fly_3.PushBack({ 65, 576, 16, 16 });

		fly_3.speed = 0.4f;
		fly_3.loop = true;

		act[2] = &fly_3;

		fly_4.PushBack({ 83, 576, 16, 16 });
		fly_4.PushBack({ 101, 576, 16, 16 });

		fly_4.speed = 0.4f;
		fly_4.loop = false;

		act[3] = &fly_2;

	}
	
	else if (random == 3)
	{
		U_S = true;


		fly_3.PushBack({ 10, 576, 16, 16 });
		fly_3.PushBack({ 10, 576, 16, 16 });
		fly_3.PushBack({ 10, 576, 16, 16 });//
		fly_3.PushBack({ 29, 576, 16, 16 });
		fly_3.PushBack({ 47, 576, 16, 16 });
		fly_3.PushBack({ 65, 576, 16, 16 });

		fly_3.speed = 0.4f;
		fly_3.loop = true;

		act[0] = &fly_3;

		fly_4.PushBack({ 83, 576, 16, 16 });
		fly_4.PushBack({ 101, 576, 16, 16 });

		fly_4.speed = 0.4f;
		fly_4.loop = false;

		act[1] = &fly_2;

		fly_1.PushBack({ 10, 558, 16, 16 });
		fly_1.PushBack({ 10, 558, 16, 16 });
		fly_1.PushBack({ 10, 558, 16, 16 });//
		fly_1.PushBack({ 29, 558, 16, 16 });
		fly_1.PushBack({ 47, 558, 16, 16 });
		fly_1.PushBack({ 65, 558, 16, 16 });

		fly_1.speed = 0.4f;
		fly_1.loop = true;

		act[2] = &fly_1;

		fly_2.PushBack({ 83, 558, 16, 16 });
		fly_2.PushBack({ 101, 558, 16, 16 });

		fly_2.speed = 0.4f;
		fly_2.loop = false;

		act[3] = &fly_2;

	}


	//	fly.loop = true;


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

	time++;
}

void PowerUp::Move()
{
	//x lim
	if (position.x < abs(App->render->camera.x) / SCREEN_SIZE)
	{
		vel_x = -1 * vel_x;
		position.x += 1;
	}
	else if (position.x > ((abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - 27))
	{
		vel_x = -1 * vel_x;
		position.x += 1;
	}

	//y lim

	if (position.y < abs(App->render->camera.y) / SCREEN_SIZE)
	{
		vel_y = -1 * vel_y;
	}
	else if (position.y > (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 17)
	{
		vel_y = -1 * vel_y;
	}

	position.y += vel_y;
	position.x += vel_x;
}

void PowerUp::OnCollision(Collider* collider)
{
	if ((collider->type == COLLIDER_PLAYER) || collider->type == COLLIDER_PLAYER_2)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y);
	}
}

