#include "Application.h"
#include "Enemy_Xwing.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

Enemy_Xwing::Enemy_Xwing(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 163, 238, 25, 26 });
	fly.PushBack({ 200, 238, 25, 26 });
	fly.PushBack({ 237, 238, 25, 26 });
	fly.PushBack({ 162, 269, 25, 26 });
	fly.PushBack({ 199, 269, 25, 26 });
	fly.PushBack({ 236, 269, 25, 26 });
	fly.speed = 0.3f;
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 25, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	HP = XWING_HP;
}

void Enemy_Xwing::Move()
{
	if ((position.x - App->player->position.x) < 100 && shot == false) {
		App->particles->AddParticle(App->particles->enemy_shot_orange1d, position.x - 3, position.y + 2, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemy_shot_orange1d, position.x - 3, position.y + 18, COLLIDER_ENEMY_SHOT);
		shot = true;
	}

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
	position.x -= 3;
}

void Enemy_Xwing::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->medium_enemy_death);

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