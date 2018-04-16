#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel2.h"
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

	//Enemies ---
	App->enemies->Enable();
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 350, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 680, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 720, 80);

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
	int speed_ground = 1;
	int speed_background = 1;

	
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
	else if (App->render->camera.x <= -10245 && App->render->camera.x > -11245 && App->render->camera.y > -223)
	{
		App->render->camera.y -= speed_ground / 3;
	}
	// up --------------------------------------	
	else if (App->render->camera.x <= -25000 && App->render->camera.x > -26000 && App->render->camera.y <= 0)
	{
		App->render->camera.y += speed_ground / 3;
	}

	// sideways --------------------------------------	
	else if (App->render->camera.x <= 0 && App->render->camera.x > -30718)
	{
		App->render->camera.x -= speed_ground;
		ground_pos_x -= speed_background;
	}

	App->render->Blit(background_texture, (background_pos_x) / 3.5, background_pos_y, &background, 1.0f);
	App->render->Blit(ground_texture, (ground_pos_x) / 3.5, ground_pos_y - 115, &ground, 1.0f);


	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) 
	{
		App->fade->FadeToBlack(App->level1, App->level2, 1.0f);
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
