#include "Application.h"
#include "Enemy_NinjaBall.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleRender.h"

Enemy_NinjaBall::Enemy_NinjaBall(int x, int y) : Enemy(x, y)
{
	HP = 1;
	nth.PushBack({ 0,0,0,0 });

	spawn.PushBack({ 180, 536, 28, 20 });
	spawn.PushBack({ 216, 536, 28, 20 });
	spawn.PushBack({ 251, 536, 28, 20 });
	spawn.PushBack({ 148, 563, 28, 20 });
	spawn.PushBack({ 181, 563, 28, 20 });
	spawn.PushBack({ 217, 563, 28, 20 });
	spawn.PushBack({ 252, 563, 28, 20 });
	spawn.PushBack({ 148, 536, 28, 20 });

	spawn.speed = 0.1f;
	spawn.loop = false;

	fly.PushBack({ 152, 589, 20, 20 });
	fly.PushBack({ 185, 590, 20, 20 });
	fly.PushBack({ 151, 536, 20, 20 });

	fly.speed = 0.2f;
	fly.loop = true;

	
	animation = &nth;

	collider = App->collision->AddCollider({ 0, 0, 20, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
	HP = NINJA_BALL_HP;
	
}

void Enemy_NinjaBall::Move()
{
	currentTime = SDL_GetTicks();
	if ((original_x - position.x) < 40)
	{
		animation = &nth;
		position.x -= 1;
		a = App->render->camera.x;
	}
	
	else if (App->render->camera.x - a < 70)
	{
		animation = &spawn;		
	}

	else
	{
		animation = &fly;
		position.x -= 3;
	}
	//lastTime = currentTime;
}

void Enemy_NinjaBall::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->medium_enemy_death);

		if (collider->type == COLLIDER_PLAYER_SHOT)
		{
			App->user_interface->score1 += score;
		}
		if (collider->type == COLLIDER_PLAYER2_SHOT)
		{
			App->user_interface->score2 += score;
		}
}