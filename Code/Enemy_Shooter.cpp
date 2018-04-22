#include "Application.h"
#include "Enemy_Shooter.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "SDL\include\SDL_timer.h"
#include "Globals.h"
#include <cmath>

Enemy_Shooter::Enemy_Shooter(int x, int y) : Enemy(x, y)
{

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
