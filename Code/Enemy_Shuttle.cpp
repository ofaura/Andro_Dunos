#include "Application.h"
#include "Enemy_Shuttle.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"

Enemy_Shuttle::Enemy_Shuttle(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 1, 88, 20, 20 });
	fly.PushBack({ 22, 88, 20, 20 });
	fly.PushBack({ 44, 88, 20, 20 });
	fly.PushBack({ 65, 88, 20, 21 });
	fly.PushBack({ 86, 88, 20, 20 });
	fly.PushBack({ 107, 88, 20, 21 });
	fly.PushBack({ 1, 109, 20, 20 });
	fly.PushBack({ 22, 109, 20, 20 });
	fly.PushBack({ 44, 109, 20, 20 });

	fly.speed = 0.4f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 18, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Shuttle::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (20.0f * sinf(wave)));
	position.x -= 1;
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