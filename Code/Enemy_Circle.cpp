#include "Application.h"
#include "Enemy_Circle.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

Enemy_Circle::Enemy_Circle(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 3, 197, 19, 20 });
	/*fly.PushBack({ 23, 197, 20, 19 });
	fly.PushBack({ 44, 197, 19, 20 });
	fly.PushBack({ 64, 197, 20, 19 });
	fly.PushBack({ 85, 197, 19, 20 });
	fly.PushBack({ 105, 199, 20, 19 });
	fly.PushBack({ 3, 220, 19, 20 });
	fly.PushBack({ 23, 220, 20, 19 });
	fly.PushBack({ 44, 219, 19, 20 });
	fly.PushBack({ 64, 220, 20, 19 });
	fly.PushBack({ 85, 219, 19, 20 });
	fly.PushBack({ 105, 220, 20, 19 });*/
	fly.speed = 0.4f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 20, 19 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	//HP = CIRCLE;
}

void Enemy_Circle::Move()
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

void Enemy_Circle::OnCollision(Collider* collider)
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