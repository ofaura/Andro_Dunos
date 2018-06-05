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
#include "Enemy_Pixel.h"
#include "ModuleAudio.h"


Enemy_Pixel::Enemy_Pixel(int x, int y) : Enemy(x, y)
{
	fly_1.PushBack({ 0, 0, 1, 1 });
	fly_1.loop = false;

	collider = App->collision->AddCollider({ 0, 0, 1, 1 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	original_x = (App->render->camera.x / SCREEN_SIZE) + SCREEN_WIDTH - 1; //abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH;
	original_y = (App->render->camera.y / SCREEN_SIZE) + (SCREEN_HEIGHT / 2);
	HP = 1;
}

void Enemy_Pixel::Move()
{
	position.x = (App->render->camera.x / SCREEN_SIZE) + SCREEN_WIDTH - 1; //abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH;
	position.y = (App->render->camera.y / SCREEN_SIZE) + (SCREEN_HEIGHT / 2);
}

bool Enemy_Pixel::CleanUp() {
	LOG("Unloading Powerup");
	App->textures->Unload(graphics);

	return true;
}


void Enemy_Pixel::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER_SHOT)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::PIXEL, position.x, position.y);
	}
	if (collider->type == COLLIDER_PLAYER2_SHOT)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::PIXEL, position.x, position.y);
	}
}