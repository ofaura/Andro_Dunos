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

	int background_pos_x = 0;
	int ground_pos_x = 0;
	float background_pos_y = 0;
	float ground_pos_y = 0;
};

#endif // __MODULESCENELEVEL2_H__