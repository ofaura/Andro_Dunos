#ifndef __MODULESCENESCORE_H__
#define __MODULESCENESCORE_H__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneScore : public Module
{
public:
	ModuleSceneScore();
	~ModuleSceneScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	SDL_Rect _background;

};

#endif // __MODULESCENESCORE_H__