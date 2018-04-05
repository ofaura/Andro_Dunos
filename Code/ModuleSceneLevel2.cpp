#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBonus.h"
#include "ModuleAudio.h"

// BACKGROUND

ModuleSceneLevel2::ModuleSceneLevel2()
{
	// Background 
	background.x = 47;
	background.y = 26;
	background.w = 410;
	background.h = 225;

	ground.x = 182;
	ground.y = 881;
	ground.w = 500;
	ground.h = 150;
}

ModuleSceneLevel2::~ModuleSceneLevel2()
{}

// Load assets
bool ModuleSceneLevel2::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	background_texture = App->textures->Load("Assets/Sprites/lvl2/Background lvl 2.png");
	ground_texture = App->textures->Load("Assets/Sprites/lvl2/Floor 2.png");

	// TODO 1: Enable (and properly disable) the player module
//	if (App->player->IsEnabled() == false)
	if (IsEnabled()) {
		if (App->player->IsEnabled()==false) {
			App->player->Enable();
		}
	}
	if (IsEnabled()==false) {
		if (App->player->IsEnabled() ==true) {
			App->player->Disable();
		}
	}

	App->audio->PlayMusic("Assets/Audio/level2.ogg", 1.0f);
	return ret;
}



// Update: draw background
update_status ModuleSceneLevel2::Update()
{
	// Draw everything --------------------------------------	
	
	App->render->Blit(background_texture, 0, 0, &background, 1.0f);
	App->render->Blit(ground_texture, 0, 118, &ground, 1.0f);

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->level2, App->bonus, 1.0f);
	}
	return UPDATE_CONTINUE;
}

bool ModuleSceneLevel2::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading textures");
	App->textures->Unload(background_texture);
	App->textures->Unload(ground_texture);
	//if (App->player->IsEnabled() == true)
	App->player->Disable();
	return true;
}
