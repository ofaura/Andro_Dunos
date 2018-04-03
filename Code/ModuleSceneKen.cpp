#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHonda.h"
#include "ModuleInput.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen()
{
	// ground
	NeoGeo.x = 146;
	NeoGeo.y = 236;
	NeoGeo.w = 228;
	NeoGeo.h = 40;

}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	graphics = App->textures->Load("Assets/Sprites/NeoGeo/Neogeo (47).png");
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 50, 90, &NeoGeo, 0.75f); // sea and sky

	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_ken, App->scene_honda, 1.0f);
	}

	return UPDATE_CONTINUE;
}