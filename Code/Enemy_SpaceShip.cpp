#include "Application.h"
#include "Enemy_SpaceShip.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleUserInterface.h"
#include "ModuleAudio.h"

Enemy_SpaceShip::Enemy_SpaceShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 150, 216, 29, 13 });
	fly.PushBack({ 180, 215, 29, 16 });
	fly.PushBack({ 210, 216, 29, 17 });
	fly.PushBack({ 240, 216, 29, 14 });
	fly.speed = 0.08f;
	animation = &fly;

	if (y > 100) {
		path.PushBack({ -1.0f, 0.0f }, 60);
		path.PushBack({ 1.3f, 1.3f }, 25);
		path.PushBack({ -1.0f, 0.0f }, 2000);
	}
	else {
		path.PushBack({ -1.0f, 0.0f }, 60);
		path.PushBack({ 1.3f, -1.3f }, 25);
		path.PushBack({ -1.0f, 0.0f }, 2000);
	}

	collider = App->collision->AddCollider({ 0, 0, 32, 17 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_x = x;
	HP = SPACE_SHIP_HP;
}

void Enemy_SpaceShip::Move()
{
	position.y = original_y + path.GetCurrentPosition().y;
	position.x = original_x + path.GetCurrentPosition().x;

	collider->SetPos(position.x, position.y);
}

void Enemy_SpaceShip::OnCollision(Collider* collider)
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