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
	bonus.PushBack({ 0, 50, 304, 48 });
	bonus.PushBack({ 0, 101, 304, 43 });
	bonus.PushBack({ 0, 147, 304, 43 });
	bonus.PushBack({ 0, 195, 304, 40 });
	bonus.PushBack({ 0, 240, 304, 37 });
	bonus.PushBack({ 0, 281, 304, 34 });
	bonus.PushBack({ 0, 319, 304, 32 });
	bonus.PushBack({ 0, 356, 304, 29 });
	bonus.PushBack({ 0, 390, 304, 26 });
	bonus.PushBack({ 0, 421, 304, 23 });
	bonus.PushBack({ 0, 448, 304, 21 });
	bonus.PushBack({ 0, 472, 304, 18 });
	bonus.PushBack({ 0, 495, 304, 15 });
	bonus.PushBack({ 0, 514, 304, 12 });
	bonus.PushBack({ 0, 530, 304, 8 });
	bonus.PushBack({ 0, 543, 304, 5 });
	bonus.PushBack({ 0, 556, 304, 2 });
	bonus.PushBack({ 0, 563, 304, 2 });
	bonus.PushBack({ 0, 571, 304, 5 });
	bonus.PushBack({ 0, 583, 304, 7 });
	bonus.PushBack({ 0, 598, 304, 9 });
	bonus.PushBack({ 0, 614, 304, 11 });
	bonus.PushBack({ 0, 634, 304, 12 });
	bonus.PushBack({ 0, 654, 304, 13 });
	bonus.PushBack({ 0, 675, 304, 15 });
	bonus.PushBack({ 0, 697, 304, 16 });
	bonus.PushBack({ 0, 720, 304, 18 });
	bonus.PushBack({ 0, 744, 304, 20 });
	bonus.PushBack({ 0, 771, 304, 22 });
	bonus.PushBack({ 0, 802, 304, 24 });
	bonus.PushBack({ 0, 833, 304, 26 });
	bonus.PushBack({ 0, 865, 304, 26 });
	bonus.PushBack({ 0, 898, 304, 28 });
	bonus.PushBack({ 0, 934, 304, 28 });

	bonus.loop = false;
	bonus.speed = 0.3f;

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