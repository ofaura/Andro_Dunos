#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "ModuleUserInterface.h"

#include <stdio.h>

ModuleUserInterface::ModuleUserInterface()
{	
	HUD1.x = 14;
	HUD1.y = 35;
	HUD1.w = 127;
	HUD1.h = 7;

	HUD2.x = 14;
	HUD2.y = 46;
	HUD2.w = 127;
	HUD2.h = 7;

	HUD3.x = 14;
	HUD3.y = 69;
	HUD3.w = 127;
	HUD3.h = 7;

	HUD4.x = 14;
	HUD4.y = 57;
	HUD4.w = 127;
	HUD4.h = 7;

	Life.x = 15;
	Life.y = 24;
	Life.w = 7;
	Life.h = 7;

	// Beam charger
	beamNoCharged.PushBack({ 29, 28, 64, 6 });

	beamCharged.PushBack({ 165, 96, 64, 7 });
	beamCharged.PushBack({ 165, 107, 64, 7 });
	beamCharged.PushBack({ 165, 116, 64, 7 });
	beamCharged.PushBack({ 165, 126, 64, 7 });
	beamCharged.loop = true;
	beamCharged.speed = 0.5f;

	beamCharger.PushBack({ 29, 28, 64, 6 });
	beamCharger.PushBack({ 29, 35, 64, 6 });
	beamCharger.PushBack({ 29, 42, 64, 6 });
	beamCharger.PushBack({ 29, 49, 64, 6 });
	beamCharger.PushBack({ 29, 56, 64, 6 });
	beamCharger.PushBack({ 29, 63, 64, 6 });
	beamCharger.PushBack({ 29, 70, 64, 6 });
	beamCharger.PushBack({ 29, 77, 64, 6 });
	beamCharger.PushBack({ 29, 84, 64, 6 });
	beamCharger.PushBack({ 29, 91, 64, 6 });
	beamCharger.PushBack({ 29, 98, 64, 6 });
	beamCharger.PushBack({ 29, 105, 64, 6 });
	beamCharger.PushBack({ 29, 112, 64, 6 });
	beamCharger.PushBack({ 29, 119, 64, 6 });
	beamCharger.PushBack({ 29, 126, 64, 6 });
	beamCharger.PushBack({ 29, 133, 64, 6 });
	beamCharger.PushBack({ 29, 140, 64, 6 });
	beamCharger.PushBack({ 29, 147, 64, 6 });
	beamCharger.PushBack({ 29, 154, 64, 6 });
	beamCharger.PushBack({ 29, 161, 64, 6 });
	beamCharger.PushBack({ 29, 168, 64, 6 });
	beamCharger.PushBack({ 29, 175, 64, 6 });
	beamCharger.PushBack({ 29, 182, 64, 6 });
	beamCharger.PushBack({ 29, 189, 64, 6 });
	beamCharger.PushBack({ 29, 196, 64, 6 });
	beamCharger.PushBack({ 29, 203, 64, 6 });
	beamCharger.PushBack({ 29, 210, 64, 6 });
	beamCharger.PushBack({ 29, 217, 64, 6 });
	beamCharger.PushBack({ 29, 224, 64, 6 });
	beamCharger.PushBack({ 97, 28, 64, 6 });
	beamCharger.PushBack({ 97, 35, 64, 6 });
	beamCharger.PushBack({ 97, 42, 64, 6 });
	beamCharger.PushBack({ 97, 49, 64, 6 });
	beamCharger.PushBack({ 97, 56, 64, 6 });
	beamCharger.PushBack({ 97, 63, 64, 6 });
	beamCharger.PushBack({ 97, 70, 64, 6 });
	beamCharger.PushBack({ 97, 77, 64, 6 });
	beamCharger.PushBack({ 97, 84, 64, 6 });
	beamCharger.PushBack({ 97, 91, 64, 6 });
	beamCharger.PushBack({ 97, 98, 64, 6 });
	beamCharger.PushBack({ 97, 105, 64, 6 });
	beamCharger.PushBack({ 97, 112, 64, 6 });
	beamCharger.PushBack({ 97, 119, 64, 6 });
	beamCharger.PushBack({ 97, 126, 64, 6 });
	beamCharger.PushBack({ 97, 133, 64, 6 });
	beamCharger.PushBack({ 97, 140, 64, 6 });
	beamCharger.PushBack({ 97, 147, 64, 6 });
	beamCharger.PushBack({ 97, 154, 64, 6 });
	beamCharger.PushBack({ 97, 161, 64, 6 });
	beamCharger.PushBack({ 97, 168, 64, 6 });
	beamCharger.PushBack({ 97, 175, 64, 6 });
	beamCharger.PushBack({ 97, 182, 64, 6 });
	beamCharger.PushBack({ 97, 189, 64, 6 });
	beamCharger.PushBack({ 97, 196, 64, 6 });
	beamCharger.PushBack({ 97, 203, 64, 6 });
	beamCharger.PushBack({ 97, 210, 64, 6 });
	beamCharger.PushBack({ 165, 28, 64, 6 });
	beamCharger.PushBack({ 165, 35, 64, 6 });
	beamCharger.PushBack({ 165, 42, 64, 6 });
	beamCharger.PushBack({ 165, 49, 64, 6 });
	beamCharger.PushBack({ 165, 56, 64, 6 });
	beamCharger.PushBack({ 165, 63, 64, 6 });	
	beamCharger.PushBack({ 165, 73, 64, 6 });
	beamCharger.PushBack({ 165, 80, 64, 7 });
	beamCharger.PushBack({ 165, 86, 64, 7 });
	beamCharger.PushBack({ 165, 96, 64, 7 });
	beamCharger.PushBack({ 165, 107, 64, 7 });
	beamCharger.PushBack({ 165, 116, 64, 7 });
	beamCharger.PushBack({ 165, 126, 64, 7 });

	beamCharger.loop = false;
	beamCharger.speed = 0.5f;
}

ModuleUserInterface::~ModuleUserInterface()
{}

// Load assets
bool ModuleUserInterface::Start()
{
	LOG("Loading UI textures");
	weaponHud = App->textures->Load("Assets/Sprites/UI/laser_types.png");
	super = App->textures->Load("Assets/Sprites/UI/beam_charge.png");

	// The font is loaded
	font_score = App->fonts->Load("Assets/Sprites/UI/Fonts/score_font.png", "1234567890P", 1);
	type_score = App->fonts->Load("Assets/Sprites/UI/Fonts/type_font.png", "1234-TYPE ", 2);
	p2_title = App->fonts->Load("Assets/Sprites/UI/Fonts/player2_start_font.png", "12BENOPRSTU ", 1);
	highscore_font = App->fonts->Load("Assets/Sprites/UI/Fonts/highscore_font.png", "1234567890HI- ", 2);
	hud_characteristics = App->fonts->Load("Assets/Sprites/UI/Fonts/numbers_powerup.png", "012345678", 1);

	// Audios are loaded
	chargedSound = App->audio->LoadFx("Assets/Audio/special_charged.wav");
	chargingSound = App->audio->LoadFx("Assets/Audio/charging_special.wav");

	return true;
}

update_status ModuleUserInterface::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
	{
		activatedChange = true;

		if (App->player->type == 0)
			App->fonts->BlitText(8, 15, type_score, "TYPE-1");
		else if (App->player->type == 1)
			App->fonts->BlitText(8, 15, type_score, "TYPE-2");
		else if (App->player->type == 2)
			App->fonts->BlitText(8, 15, type_score, "TYPE-3");
		else if (App->player->type == 3)
			App->fonts->BlitText(8, 15, type_score, "TYPE-4");

		startTime = currentTime;
	}

	currentTime = SDL_GetTicks();

	// ------------------------------------------------
	// DRAWING THE UI
	// ------------------------------------------------	

	// Printing weapons' HUD on the screen
	if (activatedChange = true) {
		if (currentTime - startTime <= 700) {

			if (App->player->type == 0)
				App->fonts->BlitText(8, 15, type_score, "TYPE-1");
			else if (App->player->type == 1)
				App->fonts->BlitText(8, 15, type_score, "TYPE-2");
			else if (App->player->type == 2)
				App->fonts->BlitText(8, 15, type_score, "TYPE-3");
			else if (App->player->type == 3)
				App->fonts->BlitText(8, 15, type_score, "TYPE-4");

			activatedChange = false;
		}
	}
	
	// Blit the text of the score in at the bottom of the screen	
	sprintf_s(score_text, 10, "%7d", App->enemies->score);

	// Player 1 
	App->fonts->BlitText(33, 6, font_score, score_text);
	App->fonts->BlitText(8, 6, font_score, "1P");

	// Player 2 
	App->fonts->BlitText(244, 6, font_score, score_text);
	App->fonts->BlitText(214, 6, font_score, "2P");

	// High score
	App->fonts->BlitText(147, 6, highscore_font, "100000");
	App->fonts->BlitText(107, 6, highscore_font, "HI-");

	// Title remembering you can have a second player	
	if (App->player2->IsEnabled() == false)
		App->fonts->BlitText(180, 15, p2_title, "PRESS 2P BUTTON");

	// Weapon characteristics UI
	if (activatedChange == true) {
		if (App->player->type == 0)
			App->render->Blit(weaponHud, 8, 16, &HUD1, 1, false);
		else if (App->player->type == 1)
			App->render->Blit(weaponHud, 8, 16, &HUD2, 1, false);
		else if (App->player->type == 2)
			App->render->Blit(weaponHud, 8, 16, &HUD3, 1, false);
		else if (App->player->type == 3)
			App->render->Blit(weaponHud, 8, 16, &HUD4, 1, false);

		App->fonts->BlitText(34, 17, hud_characteristics, "1");
		App->fonts->BlitText(66, 17, hud_characteristics, "0");
		App->fonts->BlitText(98, 17, hud_characteristics, "0");
		App->fonts->BlitText(130, 17, hud_characteristics, "0");
	}

	// Player's lives
	if (App->player->lives == 2)
		App->render->Blit(weaponHud, 17, 25, &Life, 1, false);
	if (App->player->lives >= 1)
		App->render->Blit(weaponHud, 24, 25, &Life, 1, false);

	// Beam charger
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) {
		if (beamCharger.Finished()) {
			App->render->Blit(super, 74, 25, &(beamCharged.GetCurrentFrame()), 1, false);
		}
		else {
			App->render->Blit(super, 74, 25, &(beamCharger.GetCurrentFrame()), 1, false);
		}
	}
	else 
	{
		App->render->Blit(super, 74, 25, &(beamNoCharged.GetCurrentFrame()), 1, false);
		beamCharger.Reset();
	}

	return UPDATE_CONTINUE;
}

bool ModuleUserInterface::CleanUp()
{
	// Remove all memory leaks
	LOG("Unloading UI");
	App->textures->Unload(super);
	App->textures->Unload(weaponHud);

	return true;
}