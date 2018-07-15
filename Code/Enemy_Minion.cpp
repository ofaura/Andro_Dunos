#include "Application.h"
#include "Enemy_Minion.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleUserInterface.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"


Enemy_Minion::Enemy_Minion(int x, int y) : Enemy(x, y)
{

	if (y > 100) {
		fly.PushBack({ 436, 287, 16, 16 });
		fly.PushBack({ 467, 287, 16, 16 });
		fly.PushBack({ 496, 287, 16, 16 });
		fly.PushBack({ 527, 287, 16, 16 });
		fly.speed = 0.2f;
	}
	else {
		fly.PushBack({ 312, 287, 16, 16 });
		fly.PushBack({ 343, 287, 16, 16 });
		fly.PushBack({ 372, 287, 16, 16 });
		fly.PushBack({ 403, 287, 16, 16 });
		fly.speed = 0.2f;
	}

	path.PushBack({ -2.0f, 0.0f }, 90);
	path.PushBack({ 0.0f, 0.0f }, 80);
	path.PushBack({ -2.0f, 0.0f }, 8000);

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
	HP = MINION_HP;
}

void Enemy_Minion::Move()
{
	currentTime = SDL_GetTicks();

	if (getTime == false) {
		lastTimeShoot = currentTime;
		getTime = true;
	}

	if (currentTime > lastTimeShoot + 2000 && shot == false)
	{
		if(position.y > 100)
			App->particles->AddParticle(App->particles->beamShotDown, position.x + 3, position.y + 4, COLLIDER_ENEMY_SHOT);
		else
			App->particles->AddParticle(App->particles->beamShotUp, position.x + 3, position.y - 4, COLLIDER_ENEMY_SHOT);

		shot = true;
		lastTimeShoot = currentTime;
	}

	position.x = original_x + path.GetCurrentPosition().x;

	collider->SetPos(position.x, position.y);
}

void Enemy_Minion::OnCollision(Collider* collider)
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