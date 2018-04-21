#include "Application.h"
#include "Enemy_Shooter.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


Enemy_Shooter::Enemy_Shooter(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 0,233,31,27 });
	fly.PushBack({ 31,233,31,27 });

	fly.loop = true;
	fly.speed = 0.4f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 31, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Shooter::Move()
{
	position.y;
	position.x -= 1;
}
