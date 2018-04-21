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

	beamCharger.x = 29;
	beamCharger.y = 28;
	beamCharger.w = 64;
	beamCharger.h = 6;
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

	return true;
}

update_status ModuleUserInterface::Update()
{
	if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
	{
		activatedChange = true;

		// Printing it on the screen
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

	// ------------------------------------------------
	// DRAWING THE UI
	// ------------------------------------------------

	currentTime = SDL_GetTicks();

	// Printing it on the screen
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

	sprintf_s(score_text, 10, "%7d", App->enemies->score);

	// Blit the text of the score in at the bottom of the screen	
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
	App->render->Blit(super, 74, 25, &beamCharger, 1, false);


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