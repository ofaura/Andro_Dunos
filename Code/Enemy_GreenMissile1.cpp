#include "Application.h"
#include "Enemy_GreenMissile1.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

Enemy_GreenMissile1::Enemy_GreenMissile1(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 153, 701, 15, 10 });
	fly.PushBack({ 173, 701, 20, 10 });
	fly.PushBack({ 197, 701, 31, 10 });
	fly.loop = true;
	fly.speed = 0.2f;	

	path.PushBack({ 0.0f, 0.7f }, 50);
	path.PushBack({ -2.0f, 0.0f }, 2000);

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 15, 10 }, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT, (Module*)App->enemies);

	original_x = x;
	original_y = y;
}

void Enemy_GreenMissile1::Move()
{	
	position.x = original_x + path.GetCurrentPosition().x;
	position.y = original_y + path.GetCurrentPosition().y;

	collider->SetPos(position.x, position.y);
}

void Enemy_GreenMissile1::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->medium_enemy_death);

	if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER_SHOT_ALT || collider->type == COLLIDER_ULTIMATES)
	{

	}
	if (collider->type == COLLIDER_PLAYER2_SHOT || collider->type == COLLIDER_PLAYER2_SHOT_ALT || collider->type == COLLIDER_ULTIMATES_P2)
	{

	}
}