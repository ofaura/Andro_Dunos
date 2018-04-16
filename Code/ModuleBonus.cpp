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
	current_animation = NULL;

	bonus.PushBack({ 0, 0, 304, 48 });
	bonus.PushBack({ 0, 48, 304, 48 });
	bonus.PushBack({ 0, 96, 304, 48 });
	bonus.PushBack({ 0, 144, 304, 48 });
	bonus.PushBack({ 0, 192, 304, 48 });
	bonus.PushBack({ 0, 240, 304, 48 });
	bonus.PushBack({ 0, 288, 304, 48 });
	bonus.PushBack({ 0, 336, 304, 48 });
	bonus.PushBack({ 0, 384, 304, 48 });
	bonus.PushBack({ 0, 432, 304, 48 });
	bonus.PushBack({ 0, 480, 304, 48 });
	bonus.PushBack({ 0, 528, 304, 48 });
	bonus.PushBack({ 0, 576, 304, 48 });
	bonus.PushBack({ 0, 624, 304, 48 });
	bonus.PushBack({ 0, 672, 304, 48 });
	bonus.PushBack({ 0, 720, 304, 48 });
	bonus.PushBack({ 0, 768, 304, 48 });
	bonus.PushBack({ 0, 816, 304, 48 });
	bonus.PushBack({ 0, 864, 304, 48 });
	bonus.PushBack({ 0, 912, 304, 48 });
	bonus.PushBack({ 0, 960, 304, 48 });
	bonus.PushBack({ 0, 1008, 304, 48 });
	bonus.PushBack({ 0, 1056, 304, 48 });
	bonus.PushBack({ 0, 1104, 304, 48 });
	bonus.PushBack({ 0, 1152, 304, 48 });
	bonus.PushBack({ 0, 1200, 304, 48 });
	bonus.PushBack({ 0, 1248, 304, 48 });
	bonus.PushBack({ 0, 1296, 304, 48 });
	bonus.PushBack({ 0, 1344, 304, 48 });
	bonus.PushBack({ 0, 1392, 304, 48 });
	bonus.PushBack({ 0, 1440, 304, 48 });
	bonus.PushBack({ 0, 1488, 304, 48 });
	bonus.PushBack({ 0, 1536, 304, 48 });
	bonus.PushBack({ 0, 1584, 304, 48 });
	bonus.PushBack({ 0, 1632, 304, 48 });

	bonus.loop = false;
	bonus.speed = 0.4f;

}

ModuleBonus::~ModuleBonus()
{}

// Load assets
bool ModuleBonus::Start()
{
	LOG("Loading clear bonus");
	App->audio->PlayMusic("Assets/Audio/18_Game_Over.ogg", 1.0f);
	graphics = App->textures->Load("Assets/Sprites/bonus/stage_clear.png");
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
	current_animation = &bonus;
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, 9, 80, &r, 1);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->bonus, App->NeoGeo, 1.0f);
	}

	return UPDATE_CONTINUE;
}