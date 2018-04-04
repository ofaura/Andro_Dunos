#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntroNeoGeo.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBonus.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"


ModuleBonus::ModuleBonus()
{
	// ground
	Bonus.x = 108;
	Bonus.y = 232;
	Bonus.w = 304;
	Bonus.h = 48;

}

ModuleBonus::~ModuleBonus()
{}

// Load assets
bool ModuleBonus::Start()
{
	LOG("Loading clear bonus");
	App->audio->PlayMusic("Assets/Audio/18_Game_Over.ogg", 1.0f);
	graphics = App->textures->Load("Assets/Sprites/bonus/StageClear-(1).png");
	return true;
}

// UnLoad assets
bool ModuleBonus::CleanUp()
{
	LOG("Unloading Neo Geo logo scene");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleBonus::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 20, 90, &Bonus, 1.0f);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->bonus, App->NeoGeo, 1.0f);
	}

	return UPDATE_CONTINUE;
}