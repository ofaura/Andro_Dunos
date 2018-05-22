#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleEnemyBoss.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStartMenu.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

ModuleEnemyBoss::ModuleEnemyBoss()
{
	//Meteorite
	upHalf.x = 226;
	upHalf.y = 93;
	upHalf.w = 84;
	upHalf.h = 107;

	downHalf.x = 323;
	downHalf.y = 84;
	downHalf.w = 86;
	downHalf.h = 111;

	//Structure
	core.x = 449;
	core.y = 81;
	core.w = 56;
	core.h = 128;
	
	//Hatchs
	closingHatchs.PushBack({ 32, 329, 22, 152 });
	closingHatchs.PushBack({ 60, 329, 22, 152 });
	closingHatchs.PushBack({ 88, 329, 22, 152 });
	closingHatchs.PushBack({ 115, 329, 22, 152 });
	closingHatchs.PushBack({ 141, 329, 22, 152 });
	closingHatchs.PushBack({ 1, 329, 22, 152 });
	closingHatchs.loop = false;
	closingHatchs.speed = 0.15f;

	openingHatchs.PushBack({ 1, 329, 22, 152 });
	openingHatchs.PushBack({ 141, 329, 22, 152 });
	openingHatchs.PushBack({ 115, 329, 22, 152 });
	openingHatchs.PushBack({ 88, 329, 22, 152 });
	openingHatchs.PushBack({ 60, 329, 22, 152 });
	openingHatchs.PushBack({ 32, 329, 22, 152 });
	openingHatchs.loop = false;
	openingHatchs.speed = 0.15f;
}

ModuleEnemyBoss::~ModuleEnemyBoss()
{}

// Load assets
bool ModuleEnemyBoss::Start()
{
	LOG("Loading music and textures");

	//Textures are loaded
	graphics = App->textures->Load("Assets/Sprites/Enemies/boss.png");

	//Audios are loaded
	boss_death = App->audio->LoadFx("Assets/Audio/Sound FX/boss_death.wav");

	App->audio->PlayMusic("Assets/Audio/Music/bossIntro.ogg", 0.0f); //Intro music

	currentTime = SDL_GetTicks();
	lastTime = currentTime;

	return true;
}

// Update: draw background
update_status ModuleEnemyBoss::Update()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 9000 && musicPlayed == false)
	{
		App->audio->PlayMusic("Assets/Audio/Music/bossLoop.ogg", 0.0f); //Loop music
		musicPlayed = true;
	}

	animationHatchs = &openingHatchs;

	SDL_Rect hatchs = animationHatchs->GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 7420, 50, &hatchs, 1.0f, true);
	App->render->Blit(graphics, 7395, 30, &upHalf, 1.0f, true);
	App->render->Blit(graphics, 7393, 110, &downHalf, 1.0f, true);

	return UPDATE_CONTINUE;
}

// UnLoad assets
bool ModuleEnemyBoss::CleanUp()
{
	LOG("Unloading Neo Geo logo scene");
	App->audio->UnLoadFx(boss_death);
	App->textures->Unload(graphics);

	return true;
}