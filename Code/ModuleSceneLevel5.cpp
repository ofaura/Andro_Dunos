#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel5.h"
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
#include "ModuleShield.h"

ModuleSceneLevel5::ModuleSceneLevel5()
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

ModuleSceneLevel5::~ModuleSceneLevel5()
{}

// Load assets
bool ModuleSceneLevel5::Start()
{
	LOG("Loading background assets");
	bool ret = true;

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

	//Audio ---
	App->audio->PlayMusic("Assets/Audio/level1.ogg", 1.0f);

	return ret;
}

// Update: draw background
update_status ModuleSceneLevel5::Update()
{
	//Up
	if (App->render->camera.x >= 7150 * SCREEN_SIZE && App->render->camera.x <= 7200 * SCREEN_SIZE && App->render->camera.y >= 0)
	{
		App->render->camera.y -= 1 * SCREEN_SIZE;

		App->player->position.y -= 1;

		App->player2->position.y -= 1;
	}

	// Diagonal up
	else if (App->render->camera.x >= 4005 * SCREEN_SIZE && App->render->camera.x < 4130 * SCREEN_SIZE || App->render->camera.x >= 5074 * SCREEN_SIZE && App->render->camera.x < 5290 * SCREEN_SIZE)
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
	else if (App->render->camera.y >= 96 * SCREEN_SIZE && App->render->camera.x >= 4530 * SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE ||
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
	else if (App->render->camera.x >= 2921 * SCREEN_SIZE && App->render->camera.x <= 2971 * SCREEN_SIZE && App->render->camera.y < 224 * SCREEN_SIZE)
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

	if (App->render->camera.x == 8800 * SCREEN_SIZE)
	{
		App->fade->FadeToBlack(App->level5, App->bonus, 1.0f);
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
bool ModuleSceneLevel5::CleanUp()
{
	App->collision->CleanUp();

	// Remove all memory leaks
	LOG("Unloading textures");

	App->enemies->Disable();
	App->collision->Disable();
	App->player->Disable();
	App->user_interface->Disable();
	App->shield->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}