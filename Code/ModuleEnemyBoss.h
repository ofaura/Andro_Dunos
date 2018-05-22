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

	SDL_Texture* graphics = nullptr;

	// Hatchs animations
	Animation closingHatchs;
	Animation openingHatchs;
	Animation* animationHatchs = nullptr;

	// Cannon animations
	Animation canonUp;
	Animation canonDown;
	Animation torpede;
	Animation* animationCannonUp = nullptr;
	Animation* animationCannonDown = nullptr;

	//Red light
	Animation lightTube;

	SDL_Rect upHalf;
	SDL_Rect downHalf;
	SDL_Rect core; //Metal structure

	uint boss_death;

	bool musicPlayed = false;

	uint lastTime = 0, currentTime;

};

#endif // __MODULEENEMYBOSS_H__