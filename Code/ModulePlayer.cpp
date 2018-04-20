#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleSceneLevel1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "ModuleBonus.h"

#include <stdio.h>

ModulePlayer::ModulePlayer()
{
	current_animation = NULL;

	idle.PushBack({ 94, 108, 27, 17 });

	fire_idle.PushBack({ 73 , 111, 12 , 10 });
	fire_idle.PushBack({ 59, 111, 12, 10 });
	fire_idle.PushBack({ 42, 111, 12, 10 });
	fire_idle.loop = true;
	fire_idle.speed = 1.0f;

	up.PushBack({ 94, 108, 27, 17 });
	up.PushBack(up1);
	up.PushBack(up2);
	up.loop = false;
	up.speed = 0.1f;

	fire_up1.PushBack({ 73, 89, 5, 10});
	fire_up1.PushBack({ 59, 89, 8, 10 });
	fire_up1.PushBack({ 42, 89, 12, 10 });
	fire_up1.loop = true;
	fire_up1.speed = 1.0f;

	fire_up2.PushBack({ 73, 91, 12, 10 });
	fire_up2.PushBack({ 59, 91, 12, 10 });
	fire_up2.PushBack({ 42, 91, 12, 10 });
	fire_up2.loop = true;
	fire_up2.speed = 1.0f;

	down.PushBack({ 94, 108, 27, 17 });
	down.PushBack(down1);
	down.PushBack(down2);
	down.loop = false;
	down.speed = 0.1f;

	fire_down1.PushBack({ 73, 138, 12, 8 });
	fire_down1.PushBack({ 59, 138, 12, 8 });
	fire_down1.PushBack({ 42, 138, 12, 8 });
	fire_down1.loop = true;
	fire_down1.speed = 1.0f;

	fire_down2.PushBack({ 73, 156, 12, 10 });
	fire_down2.PushBack({ 59, 156, 12, 10 });
	fire_down2.PushBack({ 42, 156, 12, 10 });
	fire_down2.loop = true;
	fire_down2.speed = 1.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	graphics = App->textures->Load("Assets/Sprites/player/ships.png"); // arcade version
	laser1 = App->audio->LoadFx("Assets/Audio/laser1.wav");
	laser2 = App->audio->LoadFx("Assets/Audio/laser2.wav");
	laser3 = App->audio->LoadFx("Assets/Audio/laser3.wav");
	laser4 = App->audio->LoadFx("Assets/Audio/laser4.wav");
	laser4 = App->audio->LoadFx("Assets/Audio/laser4.wav");
	player_death = App->audio->LoadFx("Assets/Audio/player_death.wav");


	// The font is loaded 
	font_score = App->fonts->Load("Assets/Sprites/UI/Fonts/score_font.png", "1234567890P", 1);
	type_score = App->fonts->Load("Assets/Sprites/UI/Fonts/type_font.png", "1234-TYPE ", 2);

	lives = 2;

	position.x = 0;
	position.y = SCREEN_HEIGHT / 2;
	App->render->camera.x = 0;
	App->level1->ground_pos_x = 0;
	type = 0;

	player = App->collision->AddCollider({ position.x, position.y, 27, 17 }, COLLIDER_PLAYER, this);
	
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 2;
	if (lives >= 0)
	{

		// Move Player --------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;
			if (current_animation != &down)
			{
				down.Reset();
				current_animation = &down;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;
			if (current_animation != &up)
			{
				up.Reset();
				current_animation = &up;
			}
		}

		if (current_animation != nullptr) { // Determines animation of fire
			if (current_animation->GetCurrentFrame().h == down1.h) {
				fire_current = &fire_down1;
			}

			else if (current_animation->GetCurrentFrame().h == down2.h) {
				fire_current = &fire_down2;
			}

			else if (current_animation->GetCurrentFrame().h == up1.h) {
				fire_current = &fire_up1;
			}

			else if (current_animation->GetCurrentFrame().h == up2.h) {
				fire_current = &fire_up2;
			}

			fire_position.y = position.y + 3;
			fire_position.x = position.x - 14;
		}

		

		// Change weapon type --------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
		{
			if (type >= 0 && type < 3)
			{
				type++;
			}
			else type = 0;

			activatedChange = true;

			// Printing it on the screen
			if (type == 0)
				App->fonts->BlitText(8, 15, type_score, "TYPE-1");
			else if (type == 1)
				App->fonts->BlitText(8, 15, type_score, "TYPE-2");
			else if (type == 2)
				App->fonts->BlitText(8, 15, type_score, "TYPE-3");
			else if (type == 3)
				App->fonts->BlitText(8, 15, type_score, "TYPE-4");

			startTime = currentTime;
			
		}

		currentTime = SDL_GetTicks();

		if (activatedChange = true) {
			if (currentTime - startTime <= 1000) {

				if (type == 0)
					App->fonts->BlitText(8, 15, type_score, "TYPE-1");
				else if (type == 1)
					App->fonts->BlitText(8, 15, type_score, "TYPE-2");
				else if (type == 2)
					App->fonts->BlitText(8, 15, type_score, "TYPE-3");
				else if (type == 3)
					App->fonts->BlitText(8, 15, type_score, "TYPE-4");

				activatedChange = false;
			}
		}

		// Autowin key
		if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_STATE::KEY_DOWN)
		{
			App->fade->FadeToBlack(App->level1, App->bonus);
		}

		// Autolose key
		if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
		{
			App->fade->FadeToBlack(App->level1, App->game_over);
		}

		// Laser shot --------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 0)
		{
			App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 4, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser1);
		}

		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 1)
		{
			App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 12, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 12, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser2);
		}

		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 2)
		{
			App->particles->AddParticle(App->particles->laser3, position.x + 19, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser3);
		}

		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 3)
		{
			App->particles->AddParticle(App->particles->laser4_1, position.x + 19, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 19, position.y + 11, COLLIDER_PLAYER_SHOT);
			App->audio->PlayFx(laser4);
		}

		// Player Idle position if not going up or down -------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		{
		current_animation = &idle;
		fire_current = &fire_idle;
		}

		// Prevent Player from leaving bordrer -------------------------------------
		//x lim
		if (position.x <= abs(App->render->camera.x) / SCREEN_SIZE)
		{
			position.x = 1 + (abs(App->render->camera.x) / SCREEN_SIZE);
		}
		else if (position.x >= ((abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH - 27)))
		{
			position.x = -1 + ((abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH - 27));
		}

		//y lim

		if (position.y <= abs(App->render->camera.y) / SCREEN_SIZE)
		{
			position.y = 1 + abs(App->render->camera.y) / SCREEN_SIZE;
		}
		else if (position.y >= (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 17) // the -50 just showcases that the camera limit on the lower end works, it stopps player before they touch the ground and crash
		{
			position.y = -1 + (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 17;
		}
	}	

	// God mode
	if (App->player->lives >= 0)
	{
		if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
		{

			GodMode = !GodMode;

			if (GodMode == true)
			{
				player->to_delete = true;

				player = nullptr;
			}
			else if (GodMode == false)
			{
				GodMode = false;
				player = App->collision->AddCollider({ position.x, position.y, 27, 17 }, COLLIDER_PLAYER, this);
			}
		}

	// Update collider position to player position
	if (GodMode == false)
		{
			player->SetPos(position.x, position.y);
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect fire = fire_current->GetCurrentFrame();

	// Check player's lives	
	if (App->player->lives < 0)
	{
		App->fade->FadeToBlack(App->level1, App->game_over);
	}
	
	App->render->Blit(graphics, position.x, position.y, &r);
	App->render->Blit(graphics, fire_position.x, fire_position.y, &fire);
	
	// Draw UI (score) --------------------------------------
	sprintf_s(score_text, 10, "%7d", App->enemies->score);

	// Blit the text of the score in at the bottom of the screen	
	App->fonts->BlitText(30, 6, font_score, score_text);
	App->fonts->BlitText(10, 6, font_score, "P1");

	return UPDATE_CONTINUE;
}
bool ModulePlayer::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading ship");
	App->textures->Unload(graphics);

	return true;
}

// Detects collision with a wall. If so, go back to game over screen.
void ModulePlayer::OnCollision(Collider* col_1, Collider* col_2)
{
	if ((col_1->type == COLLIDER_ENEMY_SHOT || col_1->type == COLLIDER_ENEMY) || (col_2->type == COLLIDER_ENEMY_SHOT || col_2->type == COLLIDER_WALL)
		|| (col_2->type == COLLIDER_ENEMY || col_1->type == COLLIDER_WALL))
	{
		App->particles->AddParticle(App->particles->explosionP1, position.x, position.y);

		if (App->player->lives >= 0)
		{
			App->audio->PlayFx(player_death);
			App->player->lives--;

			position.x = 1 + abs(App->render->camera.x) / SCREEN_SIZE;
			position.y = (abs(App->render->camera.y) / SCREEN_SIZE) + (SCREEN_HEIGHT / 2);
		}
		else
		{
			position.x = 0;

			App->fade->FadeToBlack(App->level1, App->game_over);
		}

	}
};