#include "Application.h"
#include "Enemy_LittleTurret.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"

Enemy_LittleTurret::Enemy_LittleTurret(int x, int y) : Enemy(x, y)
{
	attack.PushBack({ 68, 707, 15, 14 });
	/*attack.PushBack({ 91, 707, 15, 14 });
	attack.PushBack({ 112, 707, 14, 15 });
	attack.PushBack({ 2, 724, 14, 14 });
	attack.PushBack({ 25, 723, 14, 16 });
	attack.PushBack({ 47, 724, 14, 14 });
	attack.PushBack({ 67, 724, 14, 15 });
	attack.PushBack({ 91, 724, 15, 14 });
	attack.PushBack({ 111, 724, 15, 14 });*/

	attack.speed = 0.4f;
	animation = &attack;

	collider = App->collision->AddCollider({ 0, 0, 14, 14 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
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