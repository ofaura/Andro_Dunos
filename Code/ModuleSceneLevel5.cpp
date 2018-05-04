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
	App->audio->PlayMusic("Assets/Audio/Music/level5.ogg", 1.0f);

	return ret;
}

// Update: draw background
update_status ModuleSceneLevel5::Update()
{
	

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