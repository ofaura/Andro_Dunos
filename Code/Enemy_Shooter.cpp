#include "Application.h"
#include "Enemy_Shooter.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
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
