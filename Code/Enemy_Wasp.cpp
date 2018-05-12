#include "Application.h"
#include "Enemy_Wasp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_Wasp::Enemy_Wasp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 199, 12, 22, 19 });
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 22, 19 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Wasp::Move()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 2000) //shot every 2 seconds
	{

		App->particles->AddParticle(App->particles->enemy_shot_yellow, position.x, position.y + 8, COLLIDER_ENEMY_SHOT);
		lastTime = currentTime;
	}

	collider->SetPos(position.x, position.y);
}

void Enemy_Wasp::OnCollision(Collider* collider)
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