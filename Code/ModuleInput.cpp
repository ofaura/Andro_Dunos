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

	//for (uint i = 0; i < MAX_BUTTONS; ++i)
		//gamepad[i] = KEY_IDLE;
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


	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(0)) 
		{
			controller = SDL_GameControllerOpen(0);
		}
		if (SDL_IsGameController(1)) {
			controller2 = SDL_GameControllerOpen(1);
			break;
		}

	}
	
		if (controller == NULL) {
			LOG(" Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			use_controller = false;
		}
	

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);







	//CONTROLLER INPUT
	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		if (SDL_IsGameController(i))
		{
			if (i == 0)
			{
				if (SDL_IsGameController(i))
				{
					controller = SDL_GameControllerOpen(i);
					if (SDL_GameControllerGetAttached(controller))
					{
						gamepadP1LAxisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
						gamepadP1LAxisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
						gamepadP1APressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
						gamepadP1BPressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
						gamepadP1YPressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
						gamepadP1StartPressed = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
						gamepadP1con = true;
					}
					else
					{
						SDL_GameControllerClose(controller);
						controller = nullptr;
						gamepadP1con = false;
					}
				}
			}
			else if (i<1)
			{
				gamepadP2con = false;
				SDL_GameControllerClose(controller2);
				controller2 = nullptr;
				gamepadP2con = false;
			}
			else if (i == 1 || i == 0 && gamepadP1con == false)
			{
				if (SDL_IsGameController(i))
				{
					controller2 = SDL_GameControllerOpen(i);
					if (SDL_GameControllerGetAttached(controller2))
					{
						gamepadP2LAxisX = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_LEFTX);
						gamepadP2LAxisY = SDL_GameControllerGetAxis(controller2, SDL_CONTROLLER_AXIS_LEFTY);
						gamepadP2APressed = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_A);
						gamepadP2BPressed = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_B);
						gamepadP2YPressed = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_Y);
						gamepadP2StartPressed = SDL_GameControllerGetButton(controller2, SDL_CONTROLLER_BUTTON_START);
						gamepadP2con = true;
						break;
					}
					else
					{
						SDL_GameControllerClose(controller2);
						controller2 = nullptr;
						gamepadP2con = false;
					}
				}
			}
		}
	}



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
		if (App->level5->IsEnabled())
		{
			//App->player2->Enable();
		}
			
	}
	
	if (keyboard[SDL_SCANCODE_F7]) {
		App->player2->Disable();
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