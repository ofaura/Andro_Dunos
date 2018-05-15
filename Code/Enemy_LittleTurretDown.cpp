#include "Application.h"
#include "Enemy_LittleTurretDown.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"
#include <math.h>

Enemy_LittleTurretDown::Enemy_LittleTurretDown(int x, int y) : Enemy(x, y)
{
	attack1.PushBack({ 3, 687, 15, 14 });
	attack2.PushBack({ 23, 687, 15, 14 });
	attack3.PushBack({ 48, 686, 14, 15 });
	attack4.PushBack({ 68, 686, 14, 15 });
	attack5.PushBack({ 90, 686, 14, 16 });
	attack6.PushBack({ 113, 686, 14, 15 });
	attack7.PushBack({ 3, 703, 14, 15 });
	attack8.PushBack({ 22, 705, 15, 14 });
	attack9.PushBack({ 42, 705, 15, 14 });

	collider = App->collision->AddCollider({ 0, 0, 14, 14 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

float Enemy_LittleTurretDown::AngleCalculator() {

	float angle = (atan2(App->player->position.y - position.y, position.x - App->player->position.x) * 180) / PI;
	return angle;
}

void Enemy_LittleTurretDown::Move()
{
	base = position.x - App->player->position.x;
	height = App->player->position.y - position.y;

	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 2500) //shot every 2.5 seconds
	{
		turretShoot = true;
		lastTime = currentTime;

		// If the player passes the turrets 110 units they stop shooting
		if (base < -110) {
			turretShoot = false;
		}
	}

	if (AngleCalculator() > -200 && AngleCalculator() <= -160) {
		animation = &attack9;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange9d, position.x - 3, position.y + 6, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else if (AngleCalculator() > -160 && AngleCalculator() <= -140) {
		animation = &attack8;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange8d, position.x - 2, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else if (AngleCalculator() > -140 && AngleCalculator() <= -120) {
		animation = &attack7;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange7d, position.x - 1, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else if (AngleCalculator() > -120 && AngleCalculator() <= -100) {
		animation = &attack6;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange6d, position.x + 3, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else if (AngleCalculator() > -100 && AngleCalculator() <= -80) {
		animation = &attack5;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange5d, position.x + 3, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else if (AngleCalculator() > -80 && AngleCalculator() <= -60) {
		animation = &attack4;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange4d, position.x + 6, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else if (AngleCalculator() > -60 && AngleCalculator() <= -40) {
		animation = &attack3;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange3d, position.x + 9, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else if (AngleCalculator() > -40 && AngleCalculator() <= -20) {
		animation = &attack2;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange2d, position.x + 9, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
	else {
		animation = &attack1;
		if (turretShoot == true && base < 200) {
			App->particles->AddParticle(App->particles->enemy_shot_orange1d, position.x + 12, position.y, COLLIDER_ENEMY_SHOT);
			turretShoot = false;
		}
	}
}
void Enemy_LittleTurretDown::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->small_enemy_death);

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