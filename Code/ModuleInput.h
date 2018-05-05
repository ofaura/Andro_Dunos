#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"

#define MAX_KEYS 300
#define MAX_BUTTONS 100
#define DEAD_ZONE 0.2f

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum GAMEPAD_BUTTONS{
	ARROW_UP = 0,
	ARROW_DOWN,
	ARROW_RIGHT,
	ARROW_LEFT,
	BUTTON_A,
	BUTTON_B,
	BUTTON_START
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	KEY_STATE gamepad[MAX_BUTTONS];
	SDL_GameController* controller = nullptr;
	SDL_GameController* controller2 = nullptr;

	bool use_controller = false;
	bool use_controller2 = false;
	int controller_index = 0;

	Uint8 buttons[MAX_BUTTONS];

	SDL_Event keyboardEvent;
};

#endif // __ModuleInput_H__