#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntroNeoGeo.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStartMenu.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"


ModuleIntroNeoGeo::ModuleIntroNeoGeo()
{
	current_animation = NULL;

	NeoGeo.PushBack({ 0, 1415, 227, 40 });
	NeoGeo.PushBack({ 0, 1371, 227, 40 });
	NeoGeo.PushBack({ 0, 1328, 227, 40 });
	NeoGeo.PushBack({ 0, 1285, 227, 40 });
	NeoGeo.PushBack({ 0, 1243, 227, 40 });
	NeoGeo.PushBack({ 0, 1200, 227, 40 });
	NeoGeo.PushBack({ 0, 1158, 227, 40 });
	NeoGeo.PushBack({ 0, 1115, 227, 40 });
	NeoGeo.PushBack({ 0, 1072, 227, 40 });
	NeoGeo.PushBack({ 0, 1030, 227, 40 });
	NeoGeo.PushBack({ 0, 987, 227, 40 });
	NeoGeo.PushBack({ 0, 944, 227, 40 });
	NeoGeo.PushBack({ 0, 899, 227, 40 });
	NeoGeo.PushBack({ 0, 855, 227, 40 });
	NeoGeo.PushBack({ 0, 810, 227, 40 });
	NeoGeo.PushBack({ 0, 767, 227, 40 });
	NeoGeo.PushBack({ 0, 725, 227, 38 });
	NeoGeo.PushBack({ 0, 686, 227, 35 });
	NeoGeo.PushBack({ 0, 650, 227, 32 });
	NeoGeo.PushBack({ 0, 617, 227, 30 });
	NeoGeo.PushBack({ 0, 587, 227, 28 });
	NeoGeo.PushBack({ 0, 559, 227, 25 });
	NeoGeo.PushBack({ 0, 531, 227, 22 });
	NeoGeo.PushBack({ 0, 508, 227, 20 });
	NeoGeo.PushBack({ 0, 484, 227, 18 });
	NeoGeo.PushBack({ 0, 466, 227, 15 });
	NeoGeo.PushBack({ 0, 451, 227, 12 });
	NeoGeo.PushBack({ 0, 438, 227, 10 });
	NeoGeo.PushBack({ 0, 425, 227, 8 });
	NeoGeo.PushBack({ 0, 414, 227, 5 });
	NeoGeo.PushBack({ 0, 408, 227, 2 });
	NeoGeo.PushBack({ 0, 401, 227, 2 });
	NeoGeo.PushBack({ 0, 393, 227, 5 });
	NeoGeo.PushBack({ 0, 381, 227, 8 });
	NeoGeo.PushBack({ 0, 365, 227, 10 });
	NeoGeo.PushBack({ 0, 348, 227, 12 });
	NeoGeo.PushBack({ 0, 330, 227, 15 });
	NeoGeo.PushBack({ 0, 310, 227, 18 });
	NeoGeo.PushBack({ 0, 286, 227, 20 });
	NeoGeo.PushBack({ 0, 262, 227, 22 });
	NeoGeo.PushBack({ 0, 235, 227, 25 });
	NeoGeo.PushBack({ 0, 203, 227, 28 });
	NeoGeo.PushBack({ 0, 168, 227, 30 });
	NeoGeo.PushBack({ 0, 129, 227, 32 });
	NeoGeo.PushBack({ 0, 88, 227, 35 });
	NeoGeo.PushBack({ 0, 44, 227, 38 });
	NeoGeo.PushBack({ 0, 0, 227, 40 });

	NeoGeo.loop = false;
	NeoGeo.speed = 0.3f;
}

ModuleIntroNeoGeo::~ModuleIntroNeoGeo()
{}

// Load assets
bool ModuleIntroNeoGeo::Start()
{
	LOG("Loading music and textures");
	App->audio->PlayMusic("Assets/Audio/neoGeo.ogg", 1.0f);
	graphics = App->textures->Load("Assets/Sprites/NeoGeo/neogeo.png");
	return true;
}

// UnLoad assets
bool ModuleIntroNeoGeo::CleanUp()
{
	LOG("Unloading Neo Geo logo scene");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleIntroNeoGeo::Update()

{
	current_animation = &NeoGeo;
	SDL_Rect r = current_animation->GetCurrentFrame();
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 44, 80, &r, 1);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->NeoGeo, App->start_menu, 1.0f);
	}

	return UPDATE_CONTINUE;
}