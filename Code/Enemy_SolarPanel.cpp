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

	HP = SOLAR_PANEL_HP;
}

void Enemy_SolarPanel::Move()
{
	currentTime = SDL_GetTicks();

	if (open.Finished() == true && currentTime > lastTimeShoot + 3000 && shot == false) // Shoots at one second
	{
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 40, position.y + 4);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 30, position.y + 10);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 22, position.y + 18);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 16, position.y + 28);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOT, position.x + 12, position.y + 40);

		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOTDOWN, position.x + 12, position.y + 42);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOTDOWN, position.x + 16, position.y + 54);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOTDOWN, position.x + 22, position.y + 64);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOTDOWN, position.x + 30, position.y + 72);
		App->enemies->AddEnemy(ENEMY_TYPES::BLUE_SHOTDOWN, position.x + 40, position.y + 78);

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



		if (collider->type == COLLIDER_PLAYER_SHOT)
		{
			App->user_interface->score1 += score;
		}
		if (collider->type == COLLIDER_PLAYER2_SHOT)
		{
			App->user_interface->score2 += score;
		}

}