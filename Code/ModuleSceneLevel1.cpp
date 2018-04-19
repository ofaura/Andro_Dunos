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
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 400, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 415, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 430, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 445, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 475, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 490, 140);
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

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 715, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 730, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 745, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 760, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 790, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 805, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 820, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 835, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 865, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 880, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 895, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 910, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 940, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 955, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 970, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 985, 140);

	App->enemies->AddEnemy(ENEMY_TYPES::SPACE_SHIP, 1020, 140);

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

		App->player->position.y -= 1;
		App->player->position.x += 1;

		App->player2->position.y -= 1;
		App->player2->position.x += 1;

	}

	// Diagonal down
	else if (App->render->camera.y >= 96* SCREEN_SIZE && App->render->camera.x >= 4530*SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE ||
		App->render->camera.x >= 6125 * SCREEN_SIZE && App->render->camera.x < 6262 * SCREEN_SIZE)
	{
		App->render->camera.x += 0.5 * SCREEN_SIZE;
		App->render->camera.y += 0.5* SCREEN_SIZE;

		App->player->position.y += 1;
		App->player->position.x += 1;

		App->player2->position.y += 1;
		App->player2->position.x += 1;
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
		
	App->render->Blit(background_texture, (background_pos_x) / 3.5, background_pos_y, &background, 0.5f, true);
	App->render->Blit(ground_texture, (ground_pos_x) / 3.5, ground_pos_y - 115, &ground, 1.0f, true);

	// Pressing space the next stage is loaded
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
