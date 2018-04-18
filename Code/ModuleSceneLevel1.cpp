#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBonus.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"


ModuleSceneLevel1::ModuleSceneLevel1()
{
	// Background 
	background.x = 0;
	background.y = 0;
	background.w = 1654;
	background.h = 208;

	ground.x = 0;
	ground.y = 0;
	ground.w = 9305;
	ground.h = 563;
}

ModuleSceneLevel1::~ModuleSceneLevel1()
{}

// Load assets
bool ModuleSceneLevel1::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	background_texture = App->textures->Load("Assets/Sprites/lvl1/background1.png");
	ground_texture = App->textures->Load("Assets/Sprites/lvl1/Floor_all.png");

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

	// Reseting the camera to the start of the level
	App->render->camera.x = App->render->camera.y = 0;
	App->render->camera.w = SCREEN_WIDTH;
	App->render->camera.h = SCREEN_HEIGHT;

	//Enemies ---
	App->enemies->Enable();
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 600, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 650, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 700, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 750, 80);

	// Colliders ---
	App->collision->Enable();
	App->collision->AddCollider({ 0, 192, 2960, 32 }, COLLIDER_WALL);

	//Audio ---
	App->audio->PlayMusic("Assets/Audio/level1.ogg", 1.0f);

	return ret;
}

// Update: draw background
update_status ModuleSceneLevel1::Update()
{
	
	/*
	if (App->render->camera.y == 2 && App->render->camera.x > 10500 && App->render->camera.x < 12100)
	{
		App->render->camera.x += 1 * SCREEN_SIZE;
	}
	
	else if (App->render->camera.x >= 10149 && App->render->camera.y >= 2 && App->render->camera.x < 11000)
	{
		App->render->camera.x += 0.5 * SCREEN_SIZE;
		App->render->camera.y -= 0.5 * SCREEN_SIZE;
	}

	else if (App->render->camera.y == 448 && App->render->camera.x < 10150 && App->render->camera.x > 9100)
	{
		App->render->camera.x += 10 * SCREEN_SIZE;
	}

	else if (App->render->camera.y >= 193 && App->render->camera.x >= 9060 && App->render->camera.y < 449)
	{
		App->render->camera.x += 0.5 * SCREEN_SIZE;
		App->render->camera.y += 0.5 * SCREEN_SIZE;
	}

	else if (App->render->camera.y == 193 && App->render->camera.x < 9060)
	{
		App->render->camera.x += 10 * SCREEN_SIZE;
	}

	else if (App->render->camera.x >= 8010 && App->render->camera.y >= 193 && App->render->camera.x < 9000)
	{
		App->render->camera.x += 0.5 * SCREEN_SIZE;
		App->render->camera.y -= 0.5 * SCREEN_SIZE;
	}

	else if (App->render->camera.y == 448 && App->render->camera.x >= 5843 && App->render->camera.x < 8011)
	{
		App->render->camera.x += 224 * SCREEN_SIZE;
	}

	else if (App->render->camera.x == 5843 && App->render->camera.y < 449)
	{
		App->render->camera.y += 224 * SCREEN_SIZE;
	}

	else if (App->render->camera.x < 5844 && App->render->camera.y == 0)
	{
		App->render->camera.x += 2921.5 * SCREEN_SIZE;
	}
	
	*/
	
	
	
	//Up
	if (App->render->camera.x >= 7150*SCREEN_SIZE && App->render->camera.x <= 7200* SCREEN_SIZE && App->render->camera.y >= 0)
	{
		App->render->camera.y -= 1 * SCREEN_SIZE;
		App->player->position.y -= 1;

	}

	// Diagonal up
	else if (App->render->camera.x >= 4005*SCREEN_SIZE && App->render->camera.x < 4130*SCREEN_SIZE || App->render->camera.x >= 5074* SCREEN_SIZE && App->render->camera.x < 5290*SCREEN_SIZE)
	{
		App->render->camera.x += SCREEN_SIZE / 2;
		App->render->camera.y -= SCREEN_SIZE / 2;
		App->player->position.y -= 1;
		App->player->position.x += 1;


	}

	// Diagonal down
	else if (App->render->camera.y >= 96* SCREEN_SIZE && App->render->camera.x >= 4530*SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE ||
		App->render->camera.x >= 6125 * SCREEN_SIZE && App->render->camera.x < 6262 * SCREEN_SIZE)
	{
		App->render->camera.x += 0.5 * SCREEN_SIZE;
		App->render->camera.y += 0.5* SCREEN_SIZE;
		App->player->position.y += 1;
		App->player->position.x += 1;
	}

	//Down
	else if (App->render->camera.x >= 2921 * SCREEN_SIZE && App->render->camera.x <= 2971*SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE)
	{
		App->render->camera.y += 1 * SCREEN_SIZE;
		App->player->position.y += 1;

	}

	//Horizontal
	else if (App->render->camera.x >= 0 && App->render->camera.x <= 8800 * SCREEN_SIZE)
	{
		if (t == 0) // if you wanna start the ship at a certain point in the map
		{

			App->render->camera.x += 0 * SCREEN_SIZE;
			App->player->position.x += 0;

			t++;
		}
		else
		{
			App->render->camera.x += 1 * SCREEN_SIZE;
			App->player->position.x += 1;
		}

	}
		
	App->render->Blit(background_texture, (background_pos_x) / 3.5, background_pos_y, &background, 0.5f, true);
	App->render->Blit(ground_texture, (ground_pos_x) / 3.5, ground_pos_y - 115, &ground, 1.0f, true);

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) 
	{
		App->fade->FadeToBlack(App->level1, App->bonus, 1.0f);
	}

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneLevel1::CleanUp()
{


	App->collision->CleanUp();

	// TODO 5: Remove all memory leaks
	LOG("Unloading textures");
	App->textures->Unload(background_texture);
	App->textures->Unload(ground_texture);
	App->enemies->Disable();
	App->collision->Disable();
	App->player->Disable();
	return true;
}
