#include "Application.h"
#include "Enemy_Wasp.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_Wasp::Enemy_Wasp(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 199, 12, 22, 19 });
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 22, 19 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Wasp::Move()
{
	currentTime = SDL_GetTicks();	

	if (currentTime > lastTimeUp + 800) {
		going_up = !going_up;
		lastTimeUp = currentTime;
	}

	if (going_up) {
		position.y -= 2;
	}
	else {
		position.y += 2;
	}	

	if (currentTime > lastTimeShoot + 1200) // Shoots every 1.2 seconds
	{
		if(abs(position.x - App->player->position.x) < 200)
			App->particles->AddParticle(App->particles->enemy_shot_yellow, position.x - 7, position.y + 4, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
	}

	collider->SetPos(position.x, position.y);
}

void Enemy_Wasp::OnCollision(Collider* collider)
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