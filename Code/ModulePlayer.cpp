#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
	position.x = 0;
	position.y = SCREEN_HEIGHT / 2;


	idle.PushBack({ 94, 107, 27, 17 });

	idle.speed = 0.2f;


	up.PushBack({ 94, 107, 27, 17 });
	up.PushBack({ 94, 86, 27, 15 });
	up.PushBack({ 94, 66, 27, 15 });
	up.speed = 0.1f;


	down.PushBack({ 94, 107, 27, 17 });
	down.PushBack({ 94, 130, 27, 16 });
	down.PushBack({ 94, 152, 27, 17 });
	down.speed = 0.1f;

	up_static.PushBack({ 94, 86, 27, 15 });

	down_static.PushBack({ 94, 130, 27, 16 });
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/Sprites/lvl1/ships.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	bool going_vertical = false;

	Animation* current_animation = &idle;
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		if (going_vertical)
		{
			current_animation = &up;
			position.y -= speed;
			going_vertical = true;
		}
		current_animation = &up_static;
		position.y -= speed;
		
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1) {
		if (going_vertical)
		{
			current_animation = &down;
			position.y += speed;
			going_vertical = true;
		}
		current_animation = &down_static;
		position.y += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &idle;
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == 1) {
		current_animation = &idle;
		position.x += speed;
	}

	if (position.x <= 0) position.x = 0;
	else if (position.x >= SCREEN_WIDTH - 27) position.x = SCREEN_WIDTH - 27;
	if (position.y <= 0) position.y = 0;
	else if (position.y >= SCREEN_HEIGHT - 17) position.y = SCREEN_HEIGHT - 17;

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y, &r, 1);
	
	return UPDATE_CONTINUE;
}
bool ModulePlayer::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading ship");
	App->textures->Unload(graphics);

	return true;
}