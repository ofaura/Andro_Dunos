#include "Application.h"
#include "Enemy_GreenMissile2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

Enemy_GreenMissile2::Enemy_GreenMissile2(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 156, 713, 11, 12 });
	fly.PushBack({ 171, 713, 13, 12 });
	fly.PushBack({ 187, 713, 16, 12 });
	fly.loop = true;
	fly.speed = 0.2f;

	path.PushBack({ 0.0f, 0.7f }, 100);
	path.PushBack({ -2.0f, 0.0f }, 2000);

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 15, 12 }, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT, (Module*)App->enemies);

	original_x = x;
	original_y = y;
}

void Enemy_GreenMissile2::Move()
{
	position.x = original_x + path.GetCurrentPosition().x;
	position.y = original_y + path.GetCurrentPosition().y;

	collider->SetPos(position.x, position.y);
}

void Enemy_GreenMissile2::OnCollision(Collider* collider)
{

}