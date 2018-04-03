#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 0;
	position.y = SCREEN_HEIGHT / 2;

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 94, 107, 27, 17 });

	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	up.PushBack({ 94, 107, 27, 17 });
	up.PushBack({ 94, 86, 27, 15 });
	up.PushBack({ 94, 66, 27, 15 });
	up.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations
	down.PushBack({ 94, 107, 27, 17 });
	down.PushBack({ 94, 130, 27, 16 });
	down.PushBack({ 94, 152, 27, 17 });
	down.speed = 0.1f;
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
	Animation* current_animation = &idle;
	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		current_animation = &up;
		position.y -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_S] == 1) {
		current_animation = &down;
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

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y, &r, 1);
	
	return UPDATE_CONTINUE;
}
bool ModulePlayer::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading honda stage");
	App->textures->Unload(graphics);

	return true;
}