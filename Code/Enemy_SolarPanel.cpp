#include "Application.h"
#include "Enemy_SolarPanel.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_SolarPanel::Enemy_SolarPanel(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 333, 44, 48, 82 });
	fly.PushBack({ 394, 44, 48, 82 });
	fly.PushBack({ 455, 44, 48, 82 });
	fly.speed = 0.2;

	open.PushBack({ 517, 44, 48, 82 });
	open.PushBack({ 343, 159, 46, 82 });
	open.PushBack({ 402, 159, 42, 82 });
	open.PushBack({ 457, 159, 36, 82 });
	open.PushBack({ 506, 159, 36, 82 });
	open.loop = true;
	open.speed = 0.3;

	path.PushBack({ 0.0f, -2.0f }, 30);
	path.PushBack({ 0.0f, 0.0f }, 120);
	path.PushBack({ 0.0f, 2.0f }, 30);
	path.PushBack({ 0.0f, 0.0f }, 120);
	path.PushBack({ 0.0f, -2.0f }, 30);
	path.PushBack({ 0.0f, 0.0f }, 120);
	path.PushBack({ 0.0f, 2.0f }, 30);

	collider = App->collision->AddCollider({ 0, 0, 22, 19 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &fly;
	original_y = y;
}

void Enemy_SolarPanel::Move()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTimeShoot + 1200) // Shoots every 1.2 seconds
	{
		App->particles->AddParticle(App->particles->enemy_shot_yellow1, position.x - 7, position.y + 4, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
	}

	position.y = original_y + path.GetCurrentPosition().y;

	collider->SetPos(position.x, position.y);
}

void Enemy_SolarPanel::OnCollision(Collider* collider)
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