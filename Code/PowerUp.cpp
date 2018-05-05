#include "Application.h"
#include "PowerUp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleShield.h"
#include "ModuleShield_p2.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"

#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <string>

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
	srand(time(NULL)); // doesn't let me do time(NULL)

	powerup_picked = App->audio->LoadFx("Assets/Audio/Sound FX/powerup_picked.wav");
	graphics = App->textures->Load("Assets/Sprites/Enemies/enemies.png");

	random = rand() % 2;

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
	if (milliseconds >= 0 && milliseconds < 400)
	{
		if (milliseconds >= 200 && milliseconds < 225)
		{
			App->render->Blit(graphics, position.x, position.y, &(act[REFLECTION_1]->GetCurrentFrame()));
		}
		else
		{
			App->render->Blit(graphics, position.x, position.y, &(act[STILL_1]->GetCurrentFrame()));
		}
	}

	else if (milliseconds >= 400 && milliseconds < 425)
	{
		App->render->Blit(graphics, position.x, position.y, &(act[CHANGE_1]->GetCurrentFrame()));
	}

	else if (milliseconds >= 425 && milliseconds < 825)
	{
		if (milliseconds >= 625 && milliseconds < 650)
		{
			App->render->Blit(graphics, position.x, position.y, &(act[REFLECTION_2]->GetCurrentFrame()));
		}
		else
		{
			App->render->Blit(graphics, position.x, position.y, &(act[STILL_2]->GetCurrentFrame()));
		}
	}

	else if (milliseconds >= 825 && milliseconds < 850)
	{
		App->render->Blit(graphics, position.x, position.y, &(act[CHANGE_2]->GetCurrentFrame()));
	}

	else if (milliseconds >= 850)
	{
		for (int counter = 0; counter < CHANGE_2 + 1; counter++)
		{
			act[counter]->Reset();
		}

		milliseconds = -1;
	}

	collider->SetPos(position.x, position.y);

	milliseconds++;
}

void PowerUp::Move()
{
	//x lim
	if (position.x < abs(App->render->camera.x) / SCREEN_SIZE)
	{
		vel_x = -1 * vel_x;
		position.x = App->render->camera.x / SCREEN_SIZE;
	}
	else if (position.x >((abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - 16))
	{
		vel_x = -1 * vel_x;
	}

	//y lim

	if (position.y < abs(App->render->camera.y) / SCREEN_SIZE)
	{
		vel_y = -1 * vel_y;
	}
	else if (position.y >(abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 16)
	{
		vel_y = -1 * vel_y;
	}

	position.y += vel_y;
	position.x += vel_x;

	if (App->render->camera.x >= 0 && App->render->camera.x <= 8800 * SCREEN_SIZE)
	{
		position.x += 1;
	}
}

void PowerUp::OnCollision(Collider* collider)
{
	if (S_B == true) {

		if ((collider->type == COLLIDER_PLAYER))
		{
			App->audio->PlayFx(powerup_picked);
			App->player->ShootPowerUpLevel = 2;

		}
		else if (collider->type == COLLIDER_PLAYER_2)
		{			
			App->audio->PlayFx(powerup_picked);
			App->player2->ShootPowerUpLevel2 = 2;
		}
	}
	
	else if (B_M == true) {
		if ((collider->type == COLLIDER_PLAYER))
		{
			App->shield->Enable();
			App->audio->PlayFx(powerup_picked);

		}
		else if (collider->type == COLLIDER_PLAYER_2)
		{
			App->shield_p2->Enable();
			App->audio->PlayFx(powerup_picked);
		}
	}
}

bool PowerUp::CleanUp() {
	LOG("Unloading Powerup");
	App->textures->Unload(graphics);
	App->audio->UnLoadFx(powerup_picked);

	return true;
}

