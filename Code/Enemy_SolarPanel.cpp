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
	open.loop = false;
	open.speed = 0.2;

	close.PushBack({ 457, 159, 36, 82 });
	close.PushBack({ 402, 159, 42, 82 });
	close.PushBack({ 343, 159, 46, 82 });
	close.PushBack({ 517, 44, 48, 82 });
	close.loop = false;
	close.speed = 0.2;

	collider = App->collision->AddCollider({ 0, 0, 36, 82 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &fly;
	original_x = x;
}

void Enemy_SolarPanel::Move()
{
	currentTime = SDL_GetTicks();

	if (open.Finished() == true && currentTime > lastTimeShoot + 3000 && shot == false) // Shoots at one second
	{
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x - 10, position.y + 40);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x, position.y + 40);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 10, position.y + 40);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 20, position.y + 40);

		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x - 10, position.y + 60);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x, position.y + 60);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 10, position.y + 60);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 20, position.y + 60);

		lastTimeShoot = currentTime;
		shot = true;
	}

	if (position.x < original_x + 50 && App->player->position.x > position.x - 200) {
		position.x += 2;
	}
	else if (shot == false && App->player->position.x > position.x - 200) {
		animation = &open;
	}

	if (shot == true && currentTime > lastTimeShoot + 1400 && leaving == false) {
		animation = &close;
		position.x += 3;
	}

	if (close.Finished()) {
		leaving = true;
	}

	if (leaving == true) {
		animation = &fly;
		position.x += 3;
	}

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