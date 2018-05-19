#include "Application.h"
#include "Enemy_Pipeliner.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_Pipeliner::Enemy_Pipeliner(int x, int y) : Enemy(x, y)
{
	idleForward.PushBack({ 149, 12, 16, 16 });
	idleBackward.PushBack({ 149, 12, 16, 16 });
	animation = &idleForward;	

	path.PushBack({ 0.0f, -0.7f }, 55);
	path.PushBack({ 0.0f, 0.7f }, 55);

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	original_y = y;
}

void Enemy_Pipeliner::Move()
{
	currentTime = SDL_GetTicks();
	
	if (currentTime > lastTimeShoot + 1000 && App->player->position.x <= position.x) // Shoots every second
	{
		animation = &idleForward;
		App->particles->AddParticle(App->particles->enemy_shot_yellow1, position.x - 8, position.y + 4, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
	}
	/*else {
		animation = &idleBackward;
		App->particles->AddParticle(App->particles->enemy_shot_yellow2, position.x - 8, position.y + 4, COLLIDER_ENEMY_SHOT);
		lastTimeShoot = currentTime;
	}*/
	
	position.y = original_y + path.GetCurrentPosition().y;
		
	collider->SetPos(position.x, position.y);
}

void Enemy_Pipeliner::OnCollision(Collider* collider)
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