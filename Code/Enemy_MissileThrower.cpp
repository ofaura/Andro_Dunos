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

	// Path
	path.PushBack({ -1.0f, 0.0f }, 70);
	path.PushBack({ 0.0f, 0.0f }, 150);
	path.PushBack({ -0.5f, -0.8f }, 50);
	path.PushBack({ 2.0f, 0.0f }, 2000);

	collider = App->collision->AddCollider({ 0, 0, 27, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_x = x;
	original_y = y;
	
	HP = MISSILE_THROWER_HP;
}

void Enemy_MissileThrower::Move()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 1500 && missileFired == true) // Returns in 1.2 seconds
	{
		animation = &fly_turn;
	}

	if ((position.x - App->player->position.x) < 200 && missileFired == false) //Fires a missile
	{
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_MISSILE1, position.x, position.y);
		App->enemies->AddEnemy(ENEMY_TYPES::GREEN_MISSILE2, position.x + 14, position.y - 1);

		App->audio->PlayFx(App->enemies->greenRocket);
		missileFired = true; 
		lastTime = currentTime;
	}
	
	if ((position.x - App->player->position.x) > 100 && missileFired == true) {
		if (fly_turn.Finished() == true) {
			turned = true;
		}
	}

	if (turned == true) {
		animation = &fly_right;
	}

	position.x = original_x + path.GetCurrentPosition().x;
	position.y = original_y + path.GetCurrentPosition().y;

	collider->SetPos(position.x, position.y);
}

void Enemy_MissileThrower::OnCollision(Collider* collider)
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