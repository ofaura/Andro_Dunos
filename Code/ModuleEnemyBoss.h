#ifndef __MODULEENEMYBOSS_H__
#define __MODULEENEMYBOSS_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleEnemyBoss : public Module
{
public:
	ModuleEnemyBoss();
	~ModuleEnemyBoss();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	Animation NeoGeo;
	Animation* current_animation = nullptr;

	uint boss_death;

	bool introPlayed = false;

	uint lastTime = 0, currentTime;

};

#endif // __MODULEENEMYBOSS_H__