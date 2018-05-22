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

	 if (currentTime > lastTimeShoot + 400 && pathCreated && original_x + 550 > position.x) {
		App->particles->AddParticle(App->particles->big_shot, position.x, position.y + 15, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
	}

	if (position.x - App->player->position.x < 150 && pathCreated == false) {

		path.PushBack({ 0.5f, 0.0f }, 120);
		path.PushBack({ 0.5f, -0.8f }, 70);
		path.PushBack({ 0.5f, 0.0f }, 50);
		path.PushBack({ 0.5f, 1.2f }, 70);
		path.PushBack({ 0.5f, 0.0f }, 50);
		path.PushBack({ 0.5f, -0.6f }, 120);
		path.PushBack({ 0.5f, 0.6f }, 120);
		path.PushBack({ 0.5f, -1.2f }, 70);
		path.PushBack({ 0.5f, 0.0f }, 50);
		path.PushBack({ 0.5f, 0.7f }, 70);
		path.PushBack({ 0.5f, -0.7f }, 70);
		path.PushBack({ 0.5f, 0.0f }, 50);
		path.PushBack({ 0.5f, 0.8f }, 50);
		path.PushBack({ 0.5f, 0.0f }, 50);
		path.PushBack({ 0.5f, 0.6f }, 70);
		path.PushBack({ 0.5f, -0.6f }, 70);
		path.PushBack({ 0.5f, 0.0f }, 200);
		path.PushBack({ -2.0f, 0.0f }, 50);
		path.PushBack({ 3.0f, 0.0f }, 2000);
		
		pathCreated = true;
		lastTimeShoot = currentTime + 3000;
	}

	if (pathCreated) {
		position.x = original_x + path.GetCurrentPosition().x;
		position.y = original_y + path.GetCurrentPosition().y;
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