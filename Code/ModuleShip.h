#ifndef __ModuleShip_H__
#define __ModuleShip_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleShip : public Module
{
public:
	ModuleShip();
	~ModuleShip();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	iPoint position;


};

#endif