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
	// Draw everything --------------------------------------	
	int speed_ground = 2;
	int speed_background = 3;	
	/*
	// diagonal up --------------------------------------	
	if (App->render->camera.x <= -14056 && App->render->camera.x > -14476 || App->render->camera.x <= -17523 && App->render->camera.x > -18357)
	{
		if (App->render->camera.x <= -14056 && App->render->camera.x > -14476)
		{
			App->render->camera.x += speed_ground;
			App->render->camera.y -= speed_ground / 3.5;
		}

		else
		{
			App->render->camera.x += speed_ground;
			App->render->camera.y -= speed_ground / 3.85;
		}
	}
	// diagonal down --------------------------------------	
	else if (App->render->camera.x <= -15833 && App->render->camera.x > (-16300) || App->render->camera.x <= -21154 && App->render->camera.x > -22343)
	{

		if (App->render->camera.x <= -15833 && App->render->camera.x > (-16300))
		{
			App->render->camera.x += speed_ground;
			App->render->camera.y += speed_ground / 4;
		}

		else
		{
			App->render->camera.x += speed_ground;
			App->render->camera.y += speed_ground / 5.3;
		}
	}
	// down --------------------------------------	
	else if (App->render->camera.x <= PIXEL_TO_DISTANCE_X(2927) && App->render->camera.x > PIXEL_TO_DISTANCE_X(3000) && App->render->camera.y > PIXEL_TO_DISTANCE_Y(336))
	{
		App->render->camera.y -= speed_ground;
		//ground_pos_y -= speed_background;
		App->player->position.y += speed_ground / 2;
	}
	// up --------------------------------------	
	else if (App->render->camera.x <= -25000 && App->render->camera.x > -26000 && App->render->camera.y <= 0)
	{
		App->render->camera.y += speed_ground / 3;
	}

	// sideways --------------------------------------	
	else if (App->render->camera.x <= PIXEL_TO_DISTANCE_X(0) && App->render->camera.x > PIXEL_TO_DISTANCE_X(8985))
	{
		App->render->camera.x -= speed_ground;
		ground_pos_x -= speed_background;
		App->player->position.x += speed_ground / 2;
	}
	*/
	App->render->camera.x += 1 * SCREEN_SIZE;
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
