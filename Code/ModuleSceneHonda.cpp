#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneKen.h"
#include "ModuleAudio.h"

// BACKGROUND

ModuleSceneHonda::ModuleSceneHonda()
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

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	
	background_texture = App->textures->Load("Assets/Sprites/lvl1/background1.png");
	ground_texture = App->textures->Load("Assets/Sprites/lvl1/Floor_all.png");

	// TODO 1: Enable (and properly disable) the player module
	if (App->player->IsEnabled()==false)
	App->player->Enable();

	App->audio->PlayMusic("Assets/Audio/level1.ogg", 1.0f);
	return ret;
}

// Load assets
bool ModuleSceneHonda::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading honda stage");
	App->textures->Unload(background_texture);
	App->textures->Unload(ground_texture);
	if (App->player->IsEnabled() == true)
	App->player->Disable();
	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------	
	float speed_background = 2;
	float speed_ground = 1;

	if (background_pos_x < 251) {
		background_pos_x -= speed_background;
	}
	if (ground_pos_x < 251) {
		ground_pos_x -= speed_ground;
	}

	App->render->Blit(background_texture, (background_pos_x) / 3.5, 115, &background, 1.0f);
	App->render->Blit(ground_texture, (ground_pos_x) / 3.5, -115, &ground, 1.0f);

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) 
	{
		App->fade->FadeToBlack(App->scene_honda, App->scene_ken, 1.0f);
	}
	return UPDATE_CONTINUE;
}