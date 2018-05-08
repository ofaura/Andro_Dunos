#include "Application.h"
#include "Enemy_Meteorite.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleSceneLevel5.h"
#include "ModuleAudio.h"

Enemy_Meteorite::Enemy_Meteorite(int x, int y) : Enemy(x, y)
{
	//Idle meteorite
	idle.PushBack({ 52, 180, 32, 24});

	//Destroying meteorite
	destroyed.PushBack({ 0,3,18,12 });
	destroyed.speed = 0.4f;

	animation = &idle;

	collider = App->collision->AddCollider({ 0, 0, 18, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Meteorite::Move()
{
	//Meteorites move forward in a rect line
	position.y = original_y;
	position.x -= 1;
}

void Enemy_Meteorite::OnCollision(Collider* collider)
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