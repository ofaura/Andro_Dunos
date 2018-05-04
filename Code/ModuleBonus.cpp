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
#include "ModuleUserInterface.h"

#include <cstdio>

ModuleBonus::ModuleBonus()
{
	// Background
	bonusBackground.x = 0;
	bonusBackground.y = 0;
	bonusBackground.w = SCREEN_WIDTH;
	bonusBackground.h = SCREEN_HEIGHT;

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
	App->audio->PlayMusic("Assets/Audio/Music/stageClear.ogg", 1.0f);

	// Textures are loaded
	graphics = App->textures->Load("Assets/Sprites/Bonus/stage_clear.png");
	background = App->textures->Load("Assets/Sprites/StartMenu/background.png");
	scoreRect = App->textures->Load("Assets/Sprites/Bonus/score_small_screen.png");

	// Fonts are loaded
	bonus_font = App->fonts->Load("Assets/Sprites/UI/Fonts/bonus_font.png", "12AELPRY-", 1);
	font_score = App->fonts->Load("Assets/Sprites/UI/Fonts/score_font.png", "1234567890P", 1);
	joined_score = App->fonts->Load("Assets/Sprites/UI/Fonts/final_credits_font.png", "ABCDEGHIJKLMNOPRSTUWXYZ,!", 5);

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
	App->fonts->UnLoad(joined_score);
	App->fonts->UnLoad(font_score);
	App->fonts->UnLoad(bonus_font);
	App->textures->Unload(scoreRect);
	App->textures->Unload(background);
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleBonus::Update()
{
	sprintf_s(App->user_interface->score_text1, 10, "%7d", App->user_interface->score1);
	sprintf_s(App->user_interface->score_text2, 10, "%7d", App->user_interface->score2);

	// Draw everything --------------------------------------
	current_animation = &bonus;
	SDL_Rect r = current_animation->GetCurrentFrame();

	//Background
	App->render->Blit(background, 0, 0, &bonusBackground);

	// Bonus clear animation
	App->render->Blit(graphics, 9, 30, &r, 1);

	// Rectangles
	App->render->Blit(scoreRect, 25, 80, &scorePlayer);
	App->render->Blit(scoreRect, 170, 80, &scorePlayer);

	// Names
	App->fonts->BlitText(47, 84, bonus_font, "PLAYER-1");
	App->fonts->BlitText(192, 84, bonus_font, "PLAYER-2");

	// Points
	App->fonts->BlitText(60, 115, font_score, App->user_interface->score_text1);
	App->fonts->BlitText(125, 115, font_score, "P");
	App->fonts->BlitText(205, 115, font_score, App->user_interface->score_text2);
	App->fonts->BlitText(270, 115, font_score, "P");

	// Joined points
	joinedScore = App->user_interface->score1 + App->user_interface->score2;
	sprintf_s(joinedScore_text, 10, "%7d", joinedScore);
	App->fonts->BlitText(220, 183, font_score, joinedScore_text);
	App->fonts->BlitText(30, 180, joined_score, "JOINED SCORE");
	App->fonts->BlitText(285, 183, font_score, "P");

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->bonus, App->NeoGeo, 1.0f);
	}

	return UPDATE_CONTINUE;
}