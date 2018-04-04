#ifndef __MODULESCENELEVEL2_H__
#define __MODULESCENELEVEL2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneLevel2 : public Module
{
public:
	ModuleSceneLevel2();
	~ModuleSceneLevel2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background_texture = nullptr;
	SDL_Texture* ground_texture = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
};

#endif // __MODULESCENELEVEL2_H__