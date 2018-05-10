#include "Application.h"
#include "Enemy_Shuttle.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_timer.h"

Enemy_Shuttle::Enemy_Shuttle(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 1, 88, 20, 20 });
	fly.speed = 0.2f;

	go_back.PushBack({ 44, 109, 20, 20 });
	go_back.speed = 0.2f;

	turn.PushBack({ 22, 88, 20, 20 });
	turn.PushBack({ 44, 88, 20, 20 });
	turn.PushBack({ 65, 88, 20, 21 });
	turn.PushBack({ 86, 88, 20, 20 });
	turn.PushBack({ 107, 88, 20, 21 });
	turn.PushBack({ 1, 109, 20, 20 });
	turn.PushBack({ 22, 109, 20, 20 });
	turn.PushBack({ 44, 109, 20, 20 });

	turn.speed = 0.2f;
	turn.loop = false;

	collider = App->collision->AddCollider({ 0, 0, 20, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
}

void Enemy_Shuttle::Move()
{
	
	if ((original_x - position.x) < 150 && change_direction == false)
	{
		animation = &fly;
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
		position.x -= 1;
		current_y = position.y;
	}
	
	else
	{
		animation = &turn;
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
			animation = &go_back;
			position.x += 5;
		}
	}
}

void Enemy_Shuttle::OnCollision(Collider* collider)
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