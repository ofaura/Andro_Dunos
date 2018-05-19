#ifndef __MODULESCENELEVEL5_H__
#define __MODULESCENELEVEL5_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneLevel5 : public Module
{
public:
	ModuleSceneLevel5();
	~ModuleSceneLevel5();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background_texture = nullptr;
	SDL_Texture* meteorites_texture1 = nullptr;
	SDL_Texture* meteorites_texture2 = nullptr;
	SDL_Texture* scenario_texture = nullptr;

	SDL_Rect background;
	SDL_Rect meteorites1;
	SDL_Rect meteorites2;

	// Scenario
	SDL_Rect pipeline1;
	SDL_Rect pipeline2;
	SDL_Rect pipeline3;
	SDL_Rect pipeline4;
	SDL_Rect trash1;
	SDL_Rect trash2;
	SDL_Rect trash3;
	SDL_Rect pilar;
	SDL_Rect rock1;
	SDL_Rect rock2;

	int background_pos_x = 0;
	int ground_pos_x = 0;
	float background_pos_y = 0;
	float ground_pos_y = 0;
	long int pos_x = 0;
	int t = 0;

	bool GodMode = false;
};

#endif // __MODULESCENELEVEL5_H__