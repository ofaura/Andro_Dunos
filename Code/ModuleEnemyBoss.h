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
	Animation closingHatch1;
	Animation openingHatch1;
	Animation closingHatch2;
	Animation openingHatch2;
	Animation* animationHatch1 = nullptr;
	Animation* animationHatch2 = nullptr;

	// Cannon animations
	Animation idleUp;
	Animation idleDown;
	Animation shootUp;
	Animation shootDown;
	Animation torpede;
	Animation* animationCannonUp = nullptr;
	Animation* animationCannonDown = nullptr;

	//Red light
	Animation lightTube;
	Animation* animationLightTube = nullptr;

	SDL_Rect upHalf;
	SDL_Rect downHalf;
	SDL_Rect core; //Metal structure

	uint boss_death;

	bool musicPlayed = false;
	bool enemiesAdded = false;
	bool cannonShot = false;
	bool going_back = false;

	// Position of the upper half
	int positionX_uh;
	int positionY_uh;

	//Position of the down half
	int positionY_dh;

	//Position of the core
	int positionCoreY;
	int positionLightX;
	
	uint lastTime = 0, currentTime;
	uint lastTimeMusic = 0, currentTimeMusic;
	uint lastTimeShot = 0, currentTimeShot;
	uint lastTimeRing = 0, currentTimeRing;

};

#endif // __MODULEENEMYBOSS_H__