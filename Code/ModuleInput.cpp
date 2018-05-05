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
#include "ModuleSceneLevel5.h"
#include "ModuleGameOver.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;

	for (uint i = 0; i < MAX_BUTTONS; ++i)
		gamepad[i] = KEY_IDLE;
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
	SDL_Init(SDL_INIT_GAMECONTROLLER);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (SDL_Init(SDL_INIT_JOYSTICK)< 0) {
		LOG("SDL_INIT_JOYSTICK could not initialize , SDL Error: %s\n", SDL_GetError())
	}
	if (SDL_NumJoysticks() < 1) {
		LOG(" No joysticks connected!\n");
	}
	else {
		controller = SDL_GameControllerOpen(controller_index);
		use_controller = true;
		if (controller == NULL) {
			LOG(" Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			use_controller = false;
		}
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	buttons[ARROW_UP] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	buttons[ARROW_DOWN] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	buttons[ARROW_RIGHT] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	buttons[ARROW_LEFT] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	buttons[BUTTON_A] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A);
	buttons[BUTTON_B] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_B);
	buttons[BUTTON_START] = SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_START);


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

	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (buttons[i] == 1)
		{
			if (gamepad[i] == KEY_IDLE)
				gamepad[i] = KEY_DOWN;
			else
				gamepad[i] = KEY_REPEAT;
		}
		else
		{
			if (gamepad[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				gamepad[i] = KEY_UP;
			else
				gamepad[i] = KEY_IDLE;
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
		if (App->level5->IsEnabled())
			App->player2->Enable();
	}
	
	if (keyboard[SDL_SCANCODE_F7]) {
		App->player2->Disable();
		App->p2collision->CleanUp();
	}		

	// Autowin key
	if (App->input->keyboard[SDL_SCANCODE_F2])
	{
		App->fade->FadeToBlack(App->level5, App->bonus);
	}

	// Autolose key
	if (App->input->keyboard[SDL_SCANCODE_F3])
	{
		App->fade->FadeToBlack(App->level5, App->game_over);
	}
	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");	
	SDL_GameControllerClose(controller);
	controller = nullptr;
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	return true;
}