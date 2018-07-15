#include "Application.h"
#include "Enemy_GreenPlane.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_GreenPlane::Enemy_GreenPlane(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 6, 641, 23, 17 });
	fly.PushBack({ 35, 639, 23, 20 });
	fly.PushBack({ 63, 637, 23, 22 });
	fly.PushBack({ 91, 638, 23, 19 });
	fly.PushBack({ 63, 637, 23, 22 });
	fly.PushBack({ 35, 639, 23, 20 });

	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 23, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
	HP = GREEN_PLANE_HP;
}


void Enemy_GreenPlane::Move()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTimeShoot + 1500 && original_x > position.x + 50) // Shoots every 1.2 seconds
	{
		App->particles->AddParticle(App->particles->enemy_shot_blue1, position.x - 2, position.y + 6, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
	}
	
	if (going_up)
	{
		if (wave > 0.5f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -0.5f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (20.0f * sinf(wave)));
	position.x -= 1;

	collider->SetPos(position.x, position.y);
}

void Enemy_GreenPlane::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->medium_enemy_death);

	if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER_SHOT_ALT || collider->type == COLLIDER_ULTIMATES)
	{
		App->user_interface->score1 += score;
	}
	if (collider->type == COLLIDER_PLAYER2_SHOT || collider->type == COLLIDER_PLAYER2_SHOT_ALT || collider->type == COLLIDER_ULTIMATES_P2)
	{
		App->user_interface->score2 += score;
	}

}