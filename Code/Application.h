#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleIntroNeoGeo;
class ModuleSceneLevel1;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleAudio;
class ModuleParticles;
class ModuleBonus;
class ModuleStartMenu;
class ModulePlayer2;
class ModuleCollision;
class ModuleEnemies;
class ModuleGameOver;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleIntroNeoGeo* NeoGeo;
	ModuleSceneLevel1* level1;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleBonus* bonus;
	ModuleParticles* particles;
	ModuleStartMenu* start_menu;
	ModulePlayer2* player2;
	ModuleCollision* collision;
	ModuleCollision* p2collision;
	ModuleEnemies* enemies;
	ModuleGameOver* game_over;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__