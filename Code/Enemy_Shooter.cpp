#include "Application.h"
#include "Enemy_Shooter.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


Enemy_Shooter::Enemy_Shooter(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 0,233,31,27 });
	fly.PushBack({ 31,233,31,27 });

	fly.loop = true;
	fly.speed = 0.01f;

	animation = &fly;

	//shot.PushBack({});


	Animation* shot_a = nullptr;

	collider = App->collision->AddCollider({ 0, 0, 31, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_Shooter::Move()
{


	//Up
	if (App->render->camera.x >= 7150 * SCREEN_SIZE && App->render->camera.x <= 7200 * SCREEN_SIZE && App->render->camera.y >= 0)
	{
		position.y -= 1;
	}

	// Diagonal up
	else if (App->render->camera.x >= 4005 * SCREEN_SIZE && App->render->camera.x < 4130 * SCREEN_SIZE || App->render->camera.x >= 5074 * SCREEN_SIZE && App->render->camera.x < 5290 * SCREEN_SIZE)
	{
		position.y -= 1;
		position.x += 1;
	}

	// Diagonal down
	else if (App->render->camera.y >= 96 * SCREEN_SIZE && App->render->camera.x >= 4530 * SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE ||
		App->render->camera.x >= 6125 * SCREEN_SIZE && App->render->camera.x < 6262 * SCREEN_SIZE)
	{
		position.y += 1;
		position.x += 1;
	}

	//Down
	else if (App->render->camera.x >= 2921 * SCREEN_SIZE && App->render->camera.x <= 2971 * SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE)
	{
		position.y += 1;
	}

	//Horizontal
	else if (App->render->camera.x >= 0 && App->render->camera.x <= 8800 * SCREEN_SIZE)
	{
		position.x += 1;
	}

	position.y;
	position.x -= 1;

	time++;
}

void Enemy_Shooter::Draw()
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(App->textures->Load("Assets/Sprites/Enemies/enemies.png"), position.x, position.y, &(animation->GetCurrentFrame()));
}