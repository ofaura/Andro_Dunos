#include "Application.h"
#include "Enemy_MissileThrower.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "Globals.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"
#include <cmath>

enum MOVEMENT
{
	LEFT = 0,
	TURN,
	RIGHT
};

Enemy_MissileThrower::Enemy_MissileThrower(int x, int y) : Enemy(x, y)
{
	// Left
	fly_left.PushBack({ 1, 131, 27, 18 });

	// Turn
	fly_turn.PushBack({ 33, 131, 23, 17 });
	fly_turn.PushBack({ 61, 131, 18, 17 });
	fly_turn.PushBack({ 84, 131, 20, 17 });
	fly_turn.PushBack({ 3, 151, 18, 17 });
	fly_turn.PushBack({ 26, 151, 23, 17 });
	fly_turn.loop = false;
	fly_turn.speed = 0.2f;

	// Right
	fly_right.PushBack({ 54, 151, 27, 18 });

	animation = &fly_left;

	collider = App->collision->AddCollider({ 0, 0, 27, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_x = x;
	original_y = y;

}

void Enemy_MissileThrower::Move()
{
	if (missileFired == false) {
		position.x--;
	}

	if ((original_x - position.x) < 1500 && missileFired == false) //Fires a missile
	{
		App->particles->AddParticle(App->particles->enemy_missile1, position.x, position.y + 15, COLLIDER_ENEMY_SHOT);
		App->particles->AddParticle(App->particles->enemy_missile2, position.x + 12, position.y + 14, COLLIDER_ENEMY_SHOT);
		missileFired = true;
	}

	collider->SetPos(position.x, position.y);
}

void Enemy_MissileThrower::OnCollision(Collider* collider)
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