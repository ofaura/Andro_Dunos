#include "Application.h"
#include "Enemy_MissileThrower.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Globals.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"
#include <cmath>

Enemy_MissileThrower::Enemy_MissileThrower(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 1, 131, 27, 18 });
	fly.PushBack({ 33, 131, 23, 17 });
	fly.PushBack({ 61, 131, 18, 17 });
	fly.PushBack({ 84, 131, 20, 17 });
	fly.PushBack({ 3, 151, 18, 17 });
	fly.PushBack({ 26, 151, 23, 17 });
	fly.PushBack({ 54, 151, 27, 18 });

	fly.loop = true;
	fly.speed = 0.5f;

	animation = &fly;


	/*if (abs(position.y - App->player->position.y) < 20)
	{
		path.PushBack({ -0.5f, 0.4f }, 60);
		path.PushBack({ -0.5f, -0.4f }, 60);
		path.PushBack({ 1.0f, 0.0f }, 100);
		path.PushBack({ -0.5f, 0.0f }, 300);
		path.loop = false;
	}

	else if (position.y < App->player->position.y)
	{
		path.PushBack({ -0.5f, 0.4f }, 60);
		path.PushBack({ 1.0f, 0.0f }, 100);
		path.PushBack({ -0.5f, 0.0f }, 300);
		path.loop = false;
	}

	else if (position.y > App->player->position.y)
	{
		path.PushBack({ -0.5f, -0.4f }, 60);
		path.PushBack({ 1.0f, 0.0f }, 100);
		path.PushBack({ -0.5f, 0.0f }, 300);
		path.loop = false;
	}*/


	collider = App->collision->AddCollider({ 0, 0, 27, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;

}

void Enemy_MissileThrower::Move()
{
	position = original_pos + path.GetCurrentPosition();

	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 1000) //Fires a missile every second
	{
		App->particles->AddParticle(App->particles->enemy_missile1, position.x, position.y + 15, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemy_missile2, position.x + 12, position.y + 14, COLLIDER_ENEMY_SHOT);
		lastTime = currentTime;
	}

	collider->SetPos(position.x, position.y);
}

void Enemy_MissileThrower::OnCollision(Collider* collider)
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