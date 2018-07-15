#include "Application.h"
#include "Enemy_SmallSpinner.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_timer.h"

Enemy_SmallSpinner::Enemy_SmallSpinner(int x, int y) : Enemy(x, y)
{	
	spinning.PushBack({ 150, 455, 16, 16});
	spinning.PushBack({ 179, 455, 16, 16 });
	spinning.PushBack({ 208, 455, 16, 16 });
	spinning.PushBack({ 150, 475, 16, 16 });
	spinning.PushBack({ 179, 475, 16, 16 });
	spinning.PushBack({ 208, 475, 16, 16 });

	spinning.loop = true;
	spinning.speed = 0.5f;
	HP = SMALL_SPINNER_HP;

}

void Enemy_SmallSpinner::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->small_enemy_death);

	if (collider->type == COLLIDER_PLAYER_SHOT || collider->type == COLLIDER_PLAYER_SHOT_ALT || collider->type == COLLIDER_ULTIMATES)
	{
		App->user_interface->score1 += score;
	}
	if (collider->type == COLLIDER_PLAYER2_SHOT || collider->type == COLLIDER_PLAYER2_SHOT_ALT || collider->type == COLLIDER_ULTIMATES_P2)
	{
		App->user_interface->score2 += score;
	}
}

void Enemy_SmallSpinner::Move()
{

}