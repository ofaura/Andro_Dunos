#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBonus.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"

ModuleSceneLevel1::ModuleSceneLevel1()
{
	// Background 
	background.x = 0;
	background.y = 0;
	background.w = 2206;
	background.h = 208;

	ground.x = 0;
	ground.y = 0;
	ground.w = 9305;
	ground.h = 563;

	background2.x = 0;
	background2.y = 0;
	background2.w = 2513;
	background2.h = 563;

	background3.x = 0;
	background3.y = 0;
	background3.w = 2206;
	background3.h = 208;

	moon.x = 29;
	moon.y = 20;
	moon.w = 106;
	moon.h = 106;

	mars.x = 0;
	mars.y = 0;
	mars.w = 62;
	mars.h = 62;
}

ModuleSceneLevel1::~ModuleSceneLevel1()
{}

// Load assets
bool ModuleSceneLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	background_texture = App->textures->Load("Assets/Sprites/lvl1/background1.png");
	background3_texture = App->textures->Load("Assets/Sprites/lvl1/background1.png");
	ground_texture = App->textures->Load("Assets/Sprites/lvl1/Floor_all.png");
	background2_texture = App->textures->Load("Assets/Sprites/lvl1/background2.png");
	moon_tex = App->textures->Load("Assets/Sprites/lvl1/Moon.png");
	mars_tex = App->textures->Load("Assets/Sprites/lvl1/mars.png");

	if (IsEnabled()) {
		if (App->player->IsEnabled() == false) {
			App->player->Enable();
		}
	}
	if (IsEnabled() == false) {
		if (App->player->IsEnabled() == true) {
			App->player->Disable();
		}
	}	

	App->user_interface->Enable();

	// Reseting the camera to the start of the level
	App->render->camera.x = App->render->camera.y = 0;
	App->render->camera.w = SCREEN_WIDTH;
	App->render->camera.h = SCREEN_HEIGHT;

	//Enemies ---
	App->enemies->Enable();
	
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_POWERUP, 400, (SCREEN_HEIGHT / 2) - 20);
	
	

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 400, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 415, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 430, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 445, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 475, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 490, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_POWERUP, 500, (SCREEN_HEIGHT / 2) - 20);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 505, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 520, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 580, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 595, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 610, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 625, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 655, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 670, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 685, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 700, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 820, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 810, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 820, 100);

	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 880, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 870, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 880, 150);

	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 940, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 930, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 940, 100);

	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1000, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1010, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1030, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1030, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1040, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1040, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1080, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1090, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1100, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1140, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1150, 115);
	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1160, 130);


	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHOOTER, 1500, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHOOTER, 1550, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHOOTER, 1550, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHOOTER, 1600, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHOOTER, 1600, 130);

	// Colliders ----
	App->collision->Enable();
	App->collision->AddCollider({ 0, 210, 2960, 20 }, COLLIDER_WALL);
	
	App->collision->AddCollider({ 2960, 192, 49, 250 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3000, 400, 50, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3000, 420, 80, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3204, 192, 30, 115 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3234, 200, 30, 90 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3264, 200, 60, 70 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3324, 200, 60, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3384, 200, 50, 55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3434, 200, 600, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3080, 428, 1000, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3890, 415, 75, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4080, 415, 30, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4110, 385, 30, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4140, 355, 40, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4185, 335, 40, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4200, 305, 405, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4010, 170, 50, 70 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4030, 170, 50, 55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4080, 140, 50, 55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4110, 110, 50, 55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4140, 75, 50, 55 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4190, 95, 690, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4605, 325, 20, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4625, 355, 50, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4675, 385, 25, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4700, 417, 35, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4725, 430, 490, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5215, 418, 35, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5245, 385, 35, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5270, 354, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5320, 305, 50, 70 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5355, 270, 50, 70 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5385, 240, 50, 70 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5435, 210, 785, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6220, 240, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6270, 270, 30, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6300, 305, 30, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6330, 355, 55, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6360, 385, 55, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6390, 415, 55, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6445, 435, 833, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7278, 425, 60, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6285, 0, 30, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6315, 35, 30, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6345, 70, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6395, 100, 30, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6430, 150, 30, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6455, 180, 50, 30 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6505, 210, 500, 32 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7005, 210, 70, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7075, 210, 70, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7145, 210, 60, 80 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7165, 190, 30, 110 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7320, 420, 50, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7350, 400, 50, 50 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7400, 200, 50, 250 }, COLLIDER_WALL);
	App->collision->AddCollider({ 7410, 210, 1895, 20 }, COLLIDER_WALL);

	//Audio ---
	App->audio->PlayMusic("Assets/Audio/level1.ogg", 1.0f);

	return ret;
}

// Update: draw background
update_status ModuleSceneLevel1::Update()
{
	//Up
	if (App->render->camera.x >= 7150*SCREEN_SIZE && App->render->camera.x <= 7200* SCREEN_SIZE && App->render->camera.y >= 0)
	{
		App->render->camera.y -= 1 * SCREEN_SIZE;

		App->player->position.y -= 1;

		App->player2->position.y -= 1;
	}

	// Diagonal up
	else if (App->render->camera.x >= 4005*SCREEN_SIZE && App->render->camera.x < 4130*SCREEN_SIZE || App->render->camera.x >= 5074* SCREEN_SIZE && App->render->camera.x < 5290*SCREEN_SIZE)
	{
		App->render->camera.x += SCREEN_SIZE / 2;
		App->render->camera.y -= SCREEN_SIZE / 2;

		if (App->render->camera.x % 2 == 0 && App->render->camera.y % 2 == 0)
		{
			App->player->position.y -= 1;
			App->player->position.x += 1;

			App->player2->position.y -= 1;
			App->player2->position.x += 1;
		}
	}

	// Diagonal down
	else if (App->render->camera.y >= 96* SCREEN_SIZE && App->render->camera.x >= 4530*SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE ||
		App->render->camera.x >= 6125 * SCREEN_SIZE && App->render->camera.x < 6262 * SCREEN_SIZE)
	{
		App->render->camera.x += 0.5 * SCREEN_SIZE;
		App->render->camera.y += 0.5* SCREEN_SIZE;

		if (App->render->camera.x % 2 == 0 && App->render->camera.y % 2 == 0)
		{
			App->player->position.y += 1;
			App->player->position.x += 1;

			App->player2->position.y += 1;
			App->player2->position.x += 1;
		}
		
	}

	//Down
	else if (App->render->camera.x >= 2921 * SCREEN_SIZE && App->render->camera.x <= 2971*SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE)
	{
		App->render->camera.y += 1 * SCREEN_SIZE;

		App->player->position.y += 1;

		App->player2->position.y += 1;

	}

	//Horizontal
	else if (App->render->camera.x >= 0 && App->render->camera.x <= 8800 * SCREEN_SIZE)
	{

		App->render->camera.x += 1 * SCREEN_SIZE;

		App->player->position.x += 1;

		App->player2->position.x += 1;
	}
	
	
	
	if (App->render->camera.y < 400 && App->render->camera.x > 4000)
	{
		App->render->Blit(background3_texture, 3500, 0, &background3, 0.5f, true);
	}

	if (App->render->camera.y > 400)
	{
		App->textures->Unload(background_texture);
	}
	App->render->Blit(background2_texture, 1450, -235, &background2, 0.5f, true);
	App->render->Blit(background_texture, (background_pos_x) / 3.5, background_pos_y, &background, 0.5f, true);
	App->render->Blit(ground_texture, (ground_pos_x) / 3.5, ground_pos_y - 115, &ground, 1.0f, true);
	App->render->Blit(moon_tex, 750, 15, &moon, 0.3f);
	App->render->Blit(mars_tex, 2600, 15, &mars, 0.3f);

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneLevel1::CleanUp()
{
	App->collision->CleanUp();

	// Remove all memory leaks
	LOG("Unloading textures");
	App->textures->Unload(mars_tex);
	App->textures->Unload(moon_tex);
	App->textures->Unload(background2_texture);
	App->textures->Unload(ground_texture);
	App->textures->Unload(background3_texture);
	App->textures->Unload(background_texture);

	App->enemies->Disable();
	App->collision->Disable();
	App->player->Disable();
	App->user_interface->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}
