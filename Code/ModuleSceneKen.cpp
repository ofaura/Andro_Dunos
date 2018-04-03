#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntroNeoGeo.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneLevel1.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"


ModuleIntroNeoGeo::ModuleIntroNeoGeo()
{
	// ground
	NeoGeo.x = 146;
	NeoGeo.y = 236;
	NeoGeo.w = 228;
	NeoGeo.h = 40;

}

ModuleIntroNeoGeo::~ModuleIntroNeoGeo()
{}

// Load assets
bool ModuleIntroNeoGeo::Start()
{
	LOG("Loading ken scene");
	App->audio->PlayMusic("Assets/Audio/01_Neo_Geo_Logo.ogg", 1.0f);
	graphics = App->textures->Load("Assets/Sprites/NeoGeo/Neogeo (47).png");
	return true;
}

// UnLoad assets
bool ModuleIntroNeoGeo::CleanUp()
{
	LOG("Unloading ken scene");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleIntroNeoGeo::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 50, 90, &NeoGeo, 0.75f); // sea and sky

	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->NeoGeo, App->level1, 1.0f);
	}

	return UPDATE_CONTINUE;
}