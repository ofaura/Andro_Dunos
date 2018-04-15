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

ModulePlayer::ModulePlayer()
{
	current_animation = NULL;

	idle.PushBack({ 94, 108, 27, 17 });

	up.PushBack({ 94, 108, 27, 17 });
	up.PushBack({ 94, 87, 27, 15 });
	up.PushBack({ 94, 66, 27, 15 });
	up.loop = false;
	up.speed = 0.1f;

	down.PushBack({ 94, 108, 27, 17 });
	down.PushBack({ 94, 131, 27, 16 });
	down.PushBack({ 94, 153, 27, 17 });
	down.loop = false;
	down.speed = 0.1f;

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

	lives = 2;

	position.x = 0;
	position.y = SCREEN_HEIGHT / 2;

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
		// Change weapon type --------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
		{
			if (type >= 0 && type < 3)
			{
				type++;
			}
			else type = 0;
		}

		// Laser shot --------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 0)
		{
			App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 4);
			App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 9);
			App->audio->PlayFx(laser1);
		}

		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 1)
		{
			App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 12);
			App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 12);
			App->audio->PlayFx(laser2);
		}

		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 2)
		{
			App->particles->AddParticle(App->particles->laser3, position.x + 19, position.y + 11);
			App->audio->PlayFx(laser3);
		}

		else if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN && type == 3)
		{
			App->particles->AddParticle(App->particles->laser4_1, position.x + 19, position.y + 11);
			App->particles->AddParticle(App->particles->laser4_2, position.x + 19, position.y + 11);
			App->audio->PlayFx(laser4);
		}

		// Player Idle position if not going up or down -------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
			&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		{
		current_animation = &idle;
		}
	}

	// Prevent Player from leaving bordrer -------------------------------------
	if (position.x <= 0) position.x = 0;
	else if (position.x >= SCREEN_WIDTH - 27) position.x = SCREEN_WIDTH - 27;
	if (position.y <= 0) position.y = 0;
	else if (position.y >= SCREEN_HEIGHT - 17) position.y = SCREEN_HEIGHT - 17;

	if (lives >= 0)
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
	
	// Check player's lives
	App->render->Blit(graphics, position.x, position.y, &r, 1);
	if (lives < 0)
	{
		App->fade->FadeToBlack(App->level1, App->game_over);
	}

	
	return UPDATE_CONTINUE;
}
bool ModulePlayer::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading ship");
	App->textures->Unload(graphics);

	return true;
}

// Detects collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* col_1, Collider* col_2) {
	if ((col_1->type == COLLIDER_WALL || col_1->type == COLLIDER_ENEMY) || (col_2->type == COLLIDER_WALL ||col_2->type == COLLIDER_ENEMY))
	{		
		if (lives >= 0)
		{
			lives--;
			/*SDL_Rect r = current_animation->GetCurrentFrame();
			App->render->Blit(graphics, position.x, position.y, &r, 1);*/ // for the explosion, biatch
			if (lives >= 0)
			{
				position.x = 0;
				position.y = SCREEN_HEIGHT / 2;
			}
		}

	}
		
};