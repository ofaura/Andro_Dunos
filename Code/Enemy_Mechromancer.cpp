#include "Application.h"
#include "Enemy_Mechromancer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_Mechromancer::Enemy_Mechromancer(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 149, 637, 43, 44 });

	collider = App->collision->AddCollider({ 0, 0, 43, 44 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &fly;
	original_x = x;
	original_y = y;
}

void Enemy_Mechromancer::Move()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTimeShoot + 3000 && shots >= 4) // Shoots at one second
	{
		App->particles->AddParticle(App->particles->enemy_shot_yellow1, position.x - 7, position.y + 4, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
		shots++;
	}
	else {

	}

	collider->SetPos(position.x, position.y);
}

void Enemy_Mechromancer::OnCollision(Collider* collider)
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