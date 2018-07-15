#include "Application.h"
#include "Enemy_Wasp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_Wasp::Enemy_Wasp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 199, 12, 22, 19 });
	animation = &fly;
		
	path.PushBack({ 0.0f, -2.0f }, 30);
	path.PushBack({ 0.0f, 0.0f }, 120);
	path.PushBack({ 0.0f, 2.0f }, 30);
	path.PushBack({ 0.0f, 0.0f }, 120);
	path.PushBack({ 0.0f, -2.0f }, 30);
	path.PushBack({ 0.0f, 0.0f }, 120);
	path.PushBack({ 0.0f, 2.0f }, 30);

	collider = App->collision->AddCollider({ 0, 0, 22, 19 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	HP = WASP_HP;
}

void Enemy_Wasp::Move()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTimeShoot + 1200) // Shoots every 1.2 seconds
	{
		App->particles->AddParticle(App->particles->enemy_shot_yellow1, position.x - 7, position.y + 4, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
	}

	position.y = original_y + path.GetCurrentPosition().y;

	collider->SetPos(position.x, position.y);
}

void Enemy_Wasp::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->medium_enemy_death);

	if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER_SHOT_ALT || collider->type == COLLIDER_ULTIMATES)
	{
		App->user_interface->score1 += score;
	}
	if (collider->type == COLLIDER_PLAYER2_SHOT || collider->type == COLLIDER_PLAYER2_SHOT_ALT || collider->type == COLLIDER_ULTIMATES_P2)
	{
		App->user_interface->score2 += score;
	}
}