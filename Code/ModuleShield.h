#ifndef _MODULE_SHIELD_
#define _MODULE_SHIELD_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleShield : public Module{
public:
	ModuleShield();
	~ModuleShield();

	bool Init() { return true; }
	bool Start() { return true; }
	update_status Update() { return update_status::UPDATE_CONTINUE; }
	bool CleanUp() { return true; }

public:
	SDL_Rect* shield1;
	SDL_Rect* shield2;
	SDL_Rect* shield3;
	SDL_Rect* shield4;

};

#endif // !_MODULE_SHIELD_
