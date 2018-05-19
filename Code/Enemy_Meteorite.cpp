#include "Application.h"
#include "Enemy_Meteorite.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

#include <cstdlib>
#include <time.h>


Enemy_Meteorite::Enemy_Meteorite(int x, int y) : Enemy(x, y)
{
	srand(time(NULL));

	random = rand() % 3;

	if (random == 0) {
		// Meteorite 1
		idle1.PushBack({ 9, 50, 30, 29 });
		animation = &idle1;
		collider = App->collision->AddCollider({ 0, 0, 30, 29 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	}
	else if (random == 1) {
		// Meteorite 2
		idle2.PushBack({ 45, 50, 32, 30 });
		animation = &idle2;
		collider = App->collision->AddCollider({ 0, 0, 32, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	}
	else {
		// Meteorite 3
		idle3.PushBack({ 83, 52, 32, 24 });
		animation = &idle3;
		collider = App->collision->AddCollider({ 0, 0, 32, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	}

	original_y = y;
	HP = 0;
}

void Enemy_Meteorite::Move()
{
	//Meteorites move forward in a rect line
	if (random == 0) {
		position.y = original_y;
		position.x -= 1;
	}
	else if (random == 1) {
		position.y = original_y;
		position.x -= 2;
	}
	else {
		position.y = original_y;
		position.x -= 3;
	}
}

void Enemy_Meteorite::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->meteor_explosion, position.x + 20, position.y, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->enemy_explosion_alt, position.x, position.y, COLLIDER_NONE);
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