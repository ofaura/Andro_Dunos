#ifndef __MODULEBONUS_H__
#define __MODULEBONUS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBonus : public Module
{
public:
	ModuleBonus();
	~ModuleBonus();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect Bonus;

};

#endif // __MODULEBONUS_H__