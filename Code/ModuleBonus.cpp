#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleIntroNeoGeo.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBonus.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"

ModuleBonus::ModuleBonus()
{
	// Player score
	scorePlayer.x = 2;
	scorePlayer.y = 23;
	scorePlayer.w = 124;
	scorePlayer.h = 75;

	// Animations
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
	App->audio->PlayMusic("Assets/Audio/stageClear.ogg", 1.0f);

	// Textures are loaded
	graphics = App->textures->Load("Assets/Sprites/Bonus/stage_clear.png");
	graphics = App->textures->Load("Assets/Sprites/Bonus/stage_clear.png");
	scoreRect = App->textures->Load("Assets/Sprites/Bonus/score_small_screen.png");

	// Fonts are loaded
	bonus_font = App->fonts->Load("Assets/Sprites/UI/Fonts/bonus_font.png", "12AELPRY-", 1);

	// Reseting the camera
	App->render->camera.x = App->render->camera.y = 0;
	App->render->camera.w = SCREEN_WIDTH;
	App->render->camera.h = SCREEN_HEIGHT;

	return true;
}

// UnLoad assets
bool ModuleBonus::CleanUp()
{
	LOG("Unloading bonus scene");
	App->fonts->UnLoad(bonus_font);
	App->textures->Unload(scoreRect);
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleBonus::Update()
{
	// Draw everything --------------------------------------
	current_animation = &bonus;
	SDL_Rect r = current_animation->GetCurrentFrame();

	// Bonus clear animation
	App->render->Blit(graphics, 9, 30, &r, 1);

	// Rectangles
	App->render->Blit(scoreRect, 25, 80, &scorePlayer);
	App->render->Blit(scoreRect, 170, 80, &scorePlayer);

	// Names
	App->fonts->BlitText(47, 84, bonus_font, "PLAYER-1");
	App->fonts->BlitText(192, 84, bonus_font, "PLAYER-2");

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->bonus, App->NeoGeo, 1.0f);
	}

	return UPDATE_CONTINUE;
}