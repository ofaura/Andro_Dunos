#include "Application.h"
#include "Enemy_BlueShot.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

Enemy_BlueShot::Enemy_BlueShot(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 158, 736, 5, 7 });
	fly.PushBack({ 166, 736, 5, 6 });
	fly.PushBack({ 174, 736, 7, 6 });
	fly.PushBack({ 183, 736, 6, 6 });
	fly.loop = true;
	fly.speed = 0.2f;
	
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 8, 8 }, COLLIDER_TYPE::COLLIDER_ENEMY_SHOT, (Module*)App->enemies);

	original_x = x;
	original_y = y;
}

void Enemy_BlueShot::Move()
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

	collider->SetPos(position.x, position.y);
}

void Enemy_BlueShot::OnCollision(Collider* collider)
{

}