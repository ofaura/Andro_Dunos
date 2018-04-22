#include "Application.h"
#include "Enemy_Shooter.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Globals.h"
#include "ModuleUserInterface.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"
#include <cmath>

Enemy_Shooter::Enemy_Shooter(int x, int y) : Enemy(x, y)
{
	death_sound = App->audio->LoadFx("Assets/Audio/enemy_small_explosion.wav");

	fly.PushBack({ 0,233,31,27 });
	fly.PushBack({ 31,233,31,27 });

	fly.loop = true;
	fly.speed = 0.5f;

	animation = &fly;


	if (abs(position.y - App->player->position.y) < 20)
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
	}


	collider = App->collision->AddCollider({ 0, 0, 31, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	
}

void Enemy_Shooter::Move()
{

	position = original_pos + path.GetCurrentPosition();
	
	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 5000) //shot every 5 seconds
	{
		
		App->particles->AddParticle(App->particles->enemy_shot, position.x, position.y + 15, COLLIDER_ENEMY_SHOT);
		lastTime = currentTime;
	}
	
	collider->SetPos(position.x, position.y);
}

void Enemy_Shooter::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(death_sound);

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

bool Enemy_Shooter::CleanUp() {
	LOG("Unloading spaceship enemy");
	App->audio->UnLoadFx(death_sound);

	return true;
}