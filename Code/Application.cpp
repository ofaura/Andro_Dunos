#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleIntroNeoGeo.h"
#include "ModuleSceneLevel5.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleBonus.h"
#include "ModuleParticles.h"
#include "ModuleStartMenu.h"
#include "ModulePlayer2.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemyBoss.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleGameOver.h"
#include "ModuleFonts.h"
#include "ModuleShield.h"
#include "ModuleShield_p2.h"
#include "ModuleNonParticleShot.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = level5 = new ModuleSceneLevel5();
	modules[i++] = NeoGeo = new ModuleIntroNeoGeo();
	modules[i++] = start_menu = new ModuleStartMenu();
	modules[i++] = bonus = new ModuleBonus();
	modules[i++] = shield_p2 = new ModuleShield_p2();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = accel_shot = new ModuleShotGravity();
	modules[i++] = shield = new ModuleShield();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = boss = new ModuleEnemyBoss();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = user_interface = new ModuleUserInterface();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = game_over = new ModuleGameOver();
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be enabled on the first update of a new scene
	player->Disable();
	player2->Disable();
	enemies->Disable();

	// Disable the map that you do not start with
	level5->Disable();
	bonus->Disable();
	start_menu->Disable();
	game_over->Disable();
	shield->Disable();
	shield_p2->Disable();
	//accel_shot->Disable();
	boss->Disable();

	collision->Disable();
	user_interface->Disable();
	

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}