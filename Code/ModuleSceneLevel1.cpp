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

// BACKGROUND

ModuleSceneLevel1::ModuleSceneLevel1()
{
	// Background 
	background.x = 0;
	background.y = 0;
	background.w = 1654;
	background.h = 85;

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

	// TODO 1: Enable (and properly disable) the player module
	//if (App->player->IsEnabled()==false)
	//App->player->Enable();

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

	App->audio->PlayMusic("Assets/Audio/level1.ogg", 1.0f);
	return ret;
}

// Update: draw background
update_status ModuleSceneLevel1::Update()
{
	// Draw everything --------------------------------------	
	float speed_background = 1;
	float speed_ground = 2;
	// Moving Background

	// diagonal up --------------------------------------	
	if (ground_pos_x <= -14056 && ground_pos_x > - 14476 || ground_pos_x <= -17523 && ground_pos_x > -18357) 
	{
		if (ground_pos_x <= -14056 && ground_pos_x > -14476)
		{
			background_pos_x -= (speed_background);
			ground_pos_x -= (speed_ground);
			ground_pos_y += (speed_ground / 3.5);
			//background_pos_y += speed_background / 2;
		}

		else
		{
			background_pos_x -= (speed_background);
			ground_pos_x -= (speed_ground);
			ground_pos_y += (speed_ground / 3.85);
			//background_pos_y += speed_background / 2;
		}


	}
	// diagonal down --------------------------------------	
	else if (ground_pos_x <= -15833 && ground_pos_x > (-16300) || ground_pos_x <= -21154 && ground_pos_x > -22343)
	{

		if (ground_pos_x <= -15833 && ground_pos_x > (-16300))
		{
			background_pos_x -= (speed_background);
			ground_pos_x -= (speed_ground);
			ground_pos_y -= (speed_ground / 4);
			//background_pos_y += speed_background / 2;

		}

		else
		{
			background_pos_x -= (speed_background);
			ground_pos_x -= (speed_ground);
			ground_pos_y -= (speed_ground / 5.3);
			//background_pos_y += speed_background / 2;
		}
	}
	// down --------------------------------------	
	else if (ground_pos_x <= -10245 && ground_pos_x > -11245 && ground_pos_y > -223)
	{
		ground_pos_y -= (speed_ground / 6);
		background_pos_y -= (speed_background / 3);
	}
	// up --------------------------------------	
	else if (ground_pos_x <= -25000 && ground_pos_x > -26000 && ground_pos_y <= 0)
	{
		ground_pos_y += (speed_ground / 6);
		background_pos_y += (speed_background / 3);
	}
	// sideways --------------------------------------	
	else if (ground_pos_x <= 0 && ground_pos_x > -30718)
	{
		background_pos_x -= (speed_background);
		ground_pos_x -= (speed_ground);
	}

	App->render->Blit(background_texture, (background_pos_x) / 3.5, background_pos_y + 115, &background, 1.0f);
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
	// TODO 5: Remove all memory leaks
	LOG("Unloading textures");
	App->textures->Unload(background_texture);
	App->textures->Unload(ground_texture);
	//if (App->player->IsEnabled() == true)
	App->player->Disable();
	return true;
}
