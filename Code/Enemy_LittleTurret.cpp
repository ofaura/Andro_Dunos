#include "Application.h"
#include "Enemy_LittleTurret.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"

#include <math.h>

Enemy_LittleTurret::Enemy_LittleTurret(int x, int y) : Enemy(x, y)
{
	attack1.PushBack({ 68, 707, 15, 14 });
	attack2.PushBack({ 91, 707, 15, 14 });
	attack3.PushBack({ 112, 707, 14, 15 });
	attack4.PushBack({ 2, 724, 14, 14 });
	attack5.PushBack({ 25, 723, 14, 16 });
	attack6.PushBack({ 47, 724, 14, 14 });
	attack7.PushBack({ 67, 724, 14, 15 });
	attack8.PushBack({ 91, 724, 15, 14 });
	attack9.PushBack({ 111, 724, 15, 14 });

	collider = App->collision->AddCollider({ 0, 0, 14, 14 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void Enemy_LittleTurret::Move()
{
	float base = position.x- App->player->position.x;
	float height = App->player->position.y - position.y;

	//float hipotenuse = sqrt(base * base + height * height);
	
	if (atan (height / base) > 0 && atan(height / base) <= 20) {
		animation = &attack1;
	}
	else if (atan(base / height) > -20 && atan(base / height) <= 0) {
		animation = &attack2;
	}
	/*else {
		animation = &attack9;
	}*/
}

void Enemy_LittleTurret::OnCollision(Collider* collider)
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