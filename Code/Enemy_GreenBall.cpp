#include "Application.h"
#include "Enemy_GreenBall.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#define TIME (100)
#define DISTANCE (100)

Enemy_GreenBall::Enemy_GreenBall(int x, int y) : Enemy(x, y)
{
	fly_1.PushBack({ 150, 514, 16, 16 });

	fly_1.loop = false;
	fly_1.speed = 0.2f;

	fly[0] = &fly_1;

	fly_2.PushBack({ 150, 514, 16, 16 });
	fly_2.PushBack({ 180, 514, 16, 16 });
	fly_2.PushBack({ 210, 514, 16, 16 });
	fly_2.PushBack({ 240, 514, 16, 16 });
	fly_2.PushBack({ 150, 495, 16, 16 });
	fly_2.PushBack({ 180, 495, 16, 16 });
	fly_2.PushBack({ 210, 495, 16, 16 });
	fly_2.PushBack({ 240, 495, 16, 16 });

	fly_2.loop = true;
	fly_2.speed = 0.2f;

	fly[1] = &fly_2;


	circle = false;
	angle = 360;

	graphics = App->textures->Load("Assets/Sprites/Enemies/enemies.png");

	collider = App->collision->AddCollider({ 0, 0, 16, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_x = x;
	original_y = y;
}

void Enemy_GreenBall::Draw(SDL_Texture* sprites)
{
	if (circle == false)
	{
		App->render->Blit(graphics, position.x, position.y, &(fly[0]->GetCurrentFrame()));
	}

	else
	{
		App->render->Blit(graphics, position.x, position.y, &(fly[1]->GetCurrentFrame()));
	}
}

void Enemy_GreenBall::Move()
{

	
	position.x += 0;


	if (circle == false && position.x <= ((abs(App->render->camera.x) / SCREEN_SIZE + (SCREEN_WIDTH / 2))))
	{
		position.x += 1;
	}

	else  if (circle == false)
	{	
		int x = abs(position.x - App->player->position.x);
		int y = abs(position.y - App->player->position.y);

		int diag = sqrt(x * x + y * y);

		if (diag <= DISTANCE)
		{
			circle = true;
		}
	}

	if (circle == true)
	{
		position.x = position.x + 2 *  sinf( (angle * 2 * PI) / 360 ) + 1 /*plus 1 due to scrolling */;
		position.y = position.y + 2 *  cosf( (angle * 2 * PI) / 360 );

		angle = angle - 5;

		if (angle <= 0)
		{
			angle = 360;
			circle = false;
		}
	}

	collider->SetPos(position.x, position.y);
}

bool Enemy_GreenBall::CleanUp() {
	LOG("Unloading Powerup");
	App->textures->Unload(graphics);
	
	return true;
}


void Enemy_GreenBall::OnCollision(Collider* collider)
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