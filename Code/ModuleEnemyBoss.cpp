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
	// Boss' meteorite
	upHalf.x = 226;
	upHalf.y = 93;
	upHalf.w = 84;
	upHalf.h = 107;

	downHalf.x = 323;
	downHalf.y = 84;
	downHalf.w = 86;
	downHalf.h = 111;
	
	current_animation = NULL;

	NeoGeo.PushBack({ 0, 0, 227, 40 });

	NeoGeo.loop = false;
	NeoGeo.speed = 0.3f;
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

	if (currentTime > lastTime + 9000 && introPlayed == false)
	{
		App->audio->PlayMusic("Assets/Audio/Music/bossLoop.ogg", 0.0f); //Loop music
		introPlayed = true;
	}

	current_animation = &NeoGeo;
	SDL_Rect r = current_animation->GetCurrentFrame();

	// Draw everything --------------------------------------
	//App->render->Blit(graphics, 44, 80, &r, 1);

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