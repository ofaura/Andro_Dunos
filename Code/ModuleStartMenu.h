#ifndef __MODULESTARTMENU_H__
#define __MODULESTARTMENU_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStartMenu : public Module
{
public:
	ModuleStartMenu();
	~ModuleStartMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	SDL_Texture* logo = nullptr;
	SDL_Texture* visco = nullptr;
	SDL_Rect _background;
	SDL_Rect _blue;
	SDL_Rect _logo;
	SDL_Rect _visco;

};

#endif // __MODULESTARTMENU_H__