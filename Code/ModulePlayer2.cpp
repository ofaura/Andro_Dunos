#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

ModulePlayer2::ModulePlayer2()
{
	position.x = 0;
	position.y = SCREEN_HEIGHT / 2 + 50;

	current_animation = NULL;

	idle.PushBack({ 154, 108, 27, 17 });


	up.PushBack({ 154, 108, 27, 17 });
	up.PushBack({ 154, 87, 27, 15 });
	up.PushBack({ 154, 66, 27, 15 });
	up.loop = false;
	up.speed = 0.1f;

	down.PushBack({ 154, 108, 27, 17 });
	down.PushBack({ 154, 131, 27, 16 });
	down.PushBack({ 154, 153, 27, 17 });
	down.loop = false;
	down.speed = 0.1f;

}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	graphics = App->textures->Load("Assets/Sprites/player/ships.png"); // arcade version
	laser1 = App->audio->LoadFx("Assets/Audio/laser1.wav");
	laser2 = App->audio->LoadFx("Assets/Audio/laser2.wav");
	laser3 = App->audio->LoadFx("Assets/Audio/laser3.wav");
	laser4 = App->audio->LoadFx("Assets/Audio/laser4.wav");
	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	int speed = 2;

	// Move Player --------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}
	// Change weapon type --------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_DOWN)
	{
		if (type >= 0 && type < 3)
		{
			type++;
		}
		else type = 0;
	}

	// Laser shot --------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN && type == 0)
	{
		App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 4);
		App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 9);
		App->audio->PlayFx(laser1);
	}

	else if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN && type == 1)
	{
		App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 12);
		App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 12);
		App->audio->PlayFx(laser2);
	}

	else if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN && type == 2)
	{
		App->particles->AddParticle(App->particles->laser3, position.x + 19, position.y + 11);
		App->audio->PlayFx(laser3);
	}

	else if (App->input->keyboard[SDL_SCANCODE_N] == KEY_STATE::KEY_DOWN && type == 3)
	{
		App->particles->AddParticle(App->particles->laser4_1, position.x + 19, position.y + 11);
		App->particles->AddParticle(App->particles->laser4_2, position.x + 19, position.y + 11);
		App->audio->PlayFx(laser4);
	}

	// Player Idle position if not going up or down -------------------------------------
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	// Prevent Player from leaving bordrer -------------------------------------
	if (position.x <= 0) position.x = 0;
	else if (position.x >= SCREEN_WIDTH - 27) position.x = SCREEN_WIDTH - 27;
	if (position.y <= 0) position.y = 0;
	else if (position.y >= SCREEN_HEIGHT - 17) position.y = SCREEN_HEIGHT - 17;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y, &r, 1);

	return UPDATE_CONTINUE;
}
bool ModulePlayer2::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading ship");
	App->textures->Unload(graphics);

	return true;
}