#include "Application.h"
#include "Enemy_Spinner_Down.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

Enemy_Spinner_Down::Enemy_Spinner_Down(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 150, 368, 22, 22 });
	fly.PushBack({ 179, 368, 22, 22 });
	fly.PushBack({ 208, 368, 22, 22 });
	fly.PushBack({ 237, 368, 22, 22 });
	fly.PushBack({ 150, 395, 22, 22 });
	fly.PushBack({ 179, 395, 22, 22 });
	fly.PushBack({ 208, 395, 22, 22 });
	fly.PushBack({ 237, 395, 22, 22 });
	fly.PushBack({ 150, 428, 22, 22 });
	fly.PushBack({ 179, 428, 22, 22 });
	fly.PushBack({ 208, 428, 22, 22 });
	fly.PushBack({ 237, 428, 22, 22 });


	fly.loop = true;
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 22, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	HP = SPINNER_HP;

	original_x = position.x;
	original_y = position.y;
}

void Enemy_Spinner_Down::Move()
{
	if ((original_x - position.x) < 70)
	{
		position.y -= 1;
		position.x -= 1;
	}

	else if ((original_x - position.x) < 120)
	{
		position.x -= 1;
	}
	else
	{
		position.y += 1;
		position.x -= 1;
	}
}

void Enemy_Spinner_Down::OnCollision(Collider* collider)
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