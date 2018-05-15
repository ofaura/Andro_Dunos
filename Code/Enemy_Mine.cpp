#include "Application.h"
#include "Enemy_Mine.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"

#include <time.h>
#include <iostream>
#include "SDL\include\SDL_timer.h"

Enemy_Mine::Enemy_Mine(int x, int y) : Enemy(x, y)
{
	srand(time(NULL));
	random = rand() % 30;

	blink.PushBack({ 9, 175, 14, 14 });
	blink.PushBack({ 41, 175, 14, 14 });
	blink.PushBack({ 73, 175, 14, 14 });
	blink.PushBack({ 105, 175, 14, 14 });
	blink.PushBack({ 73, 175, 14, 14 });
	blink.PushBack({ 41, 175, 14, 14 });
	blink.loop = true;
	blink.speed = 0.1f;

	collider = App->collision->AddCollider({ 0, 0, 14, 14 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &blink;

	original_y = y;
	original_x = x;
}

void Enemy_Mine::Move()
{

	if ((original_x - position.x) < (110 + random) && change_direction == false)
	{
		if (going_up)
		{
			if (wave > 1.0f)
				going_up = false;
			else
				wave += 0.03f;
		}
		else
		{
			if (wave < -1.0f)
				going_up = true;
			else
				wave -= 0.03f;
		}

		position.y = int(float(original_y) + (30.0f * sinf(wave)));
		position.x -= 2;
		current_y = position.y;
	}

	else
	{
		change_direction = true;
		if ((position.y - current_y) < 30)
		{
			if ((position.y - current_y) < 10)
				position.y += 1;

			else if ((position.y - current_y) < 20)
			{
				position.y += 1;
				position.x += 1;
			}

			else
			{
				position.y += 1;
				position.x += 2;
			}
		}

		else
		{
			position.x += 1;
		}
	}
}

void Enemy_Mine::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->level5->small_enemy_death);

	if (dead == false)
	{

		if (collider->type == COLLIDER_PLAYER_SHOT)
		{
			App->user_interface->score1 += score;
		}
		if (collider->type == COLLIDER_PLAYER2_SHOT)
		{
			App->user_interface->score2 += score;
		}
	}

	dead = true;
}