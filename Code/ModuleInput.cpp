#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBonus.h"
#include "ModuleSceneLevel1.h"
#include "ModuleGameOver.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;

	for (uint i = 0; i < MAX_BUTTONS; ++i)
		gamepad[i] = BUTTON_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			joystick = SDL_GameControllerGetJoystick(controller);
		}

	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	//axis = SDL_GameControllerGetAxis();
	button = SDL_GameControllerButton();

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;

	while (SDL_PollEvent(&keyboardEvent))
	{
		if (keyboardEvent.type == SDL_QUIT)
		{
			return update_status::UPDATE_STOP;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_F8]){
		if (App->level1->IsEnabled())
			App->player2->Enable();
	}
	
	if (keyboard[SDL_SCANCODE_F7]) {
		App->player2->Disable();
		App->p2collision->CleanUp();
	}		

	// Autowin key
	if (App->input->keyboard[SDL_SCANCODE_F2])
	{
		App->fade->FadeToBlack(App->level1, App->bonus);
	}

	// Autolose key
	if (App->input->keyboard[SDL_SCANCODE_F3])
	{
		App->fade->FadeToBlack(App->level1, App->game_over);
	}
	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");	
	SDL_GameControllerClose(controller);
	controller = nullptr;
	SDL_JoystickClose(joystick);
	joystick = nullptr;

	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	return true;
}