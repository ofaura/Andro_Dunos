#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 21

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleIntroNeoGeo;
class ModuleSceneLevel5;
class ModulePlayer;
class ModuleUserInterface;
class ModuleFadeToBlack;
class Module;
class ModuleAudio;
class ModuleParticles;
class ModuleBonus;
class ModuleShield;
class ModuleShield_p2;
class ModuleStartMenu;
class ModulePlayer2;
class ModuleCollision;
class ModuleEnemies;
class ModuleGameOver;
class ModuleFonts;
class ModuleEnemyBoss;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleIntroNeoGeo* NeoGeo;
	ModuleSceneLevel5* level5;
	ModulePlayer* player;
	ModuleUserInterface* user_interface;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleBonus* bonus;
	ModuleShield* shield;
	ModuleShield_p2* shield_p2;
	ModuleParticles* particles;
	ModuleStartMenu* start_menu;
	ModulePlayer2* player2;
	ModuleCollision* collision;
	ModuleEnemies* enemies;
	ModuleGameOver* game_over;
	ModuleFonts* fonts;
	ModuleEnemyBoss* boss;

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