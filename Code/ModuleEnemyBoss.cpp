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
#include "ModuleEnemies.h"

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

	lightTube.PushBack({ 87, 106, 45, 26 });
	lightTube.PushBack({ 87, 140, 45, 26 });
	lightTube.PushBack({ 87, 174, 45, 26 });
	lightTube.loop = true;
	lightTube.speed = 0.5f;
	
	//Hatch 1
	openingHatch1.PushBack({ 32, 329, 22, 21 });
	openingHatch1.PushBack({ 60, 329, 22, 21 });
	openingHatch1.PushBack({ 88, 329, 22, 21 });
	openingHatch1.PushBack({ 115, 329, 22, 21 });
	openingHatch1.PushBack({ 141, 329, 22, 21 });
	openingHatch1.PushBack({ 1, 329, 22, 21 });
	openingHatch1.loop = false;
	openingHatch1.speed = 0.15f;

	closingHatch1.PushBack({ 1, 329, 22, 21 });
	closingHatch1.PushBack({ 141, 329, 22, 21 });
	closingHatch1.PushBack({ 115, 329, 22, 21 });
	closingHatch1.PushBack({ 88, 329, 22, 21 });
	closingHatch1.PushBack({ 60, 329, 22, 21 });
	closingHatch1.PushBack({ 32, 329, 22, 21 });
	closingHatch1.loop = false;
	closingHatch1.speed = 0.15f;

	//Hatch 2
	openingHatch2.PushBack({ 32, 460, 22, 21 });
	openingHatch2.PushBack({ 60, 460, 22, 21 });
	openingHatch2.PushBack({ 88, 460, 22, 21 });
	openingHatch2.PushBack({ 115, 460, 22, 21 });
	openingHatch2.PushBack({ 141, 460, 22, 21 });
	openingHatch2.PushBack({ 1, 460, 22, 21 });
	openingHatch2.loop = false;
	openingHatch2.speed = 0.15f;

	closingHatch2.PushBack({ 1, 460, 22, 21 });
	closingHatch2.PushBack({ 141, 460, 22, 21 });
	closingHatch2.PushBack({ 115, 460, 22, 21 });
	closingHatch2.PushBack({ 88, 460, 22, 21 });
	closingHatch2.PushBack({ 60, 460, 22, 21 });
	closingHatch2.PushBack({ 32, 460, 22, 21 });
	closingHatch2.loop = false;
	closingHatch2.speed = 0.15f;

	//Cannon up
	idleUp.PushBack({ 168, 363, 48, 26 });

	shootUp.PushBack({ 233, 363, 48, 26 });
	shootUp.PushBack({ 297, 363, 48, 26 });
	shootUp.PushBack({ 354, 363, 48, 26 });
	shootUp.PushBack({ 412, 363, 48, 26 });
	shootUp.PushBack({ 466, 363, 48, 26 });
	shootUp.PushBack({ 412, 363, 48, 26 });
	shootUp.PushBack({ 354, 363, 48, 26 });
	shootUp.PushBack({ 297, 363, 48, 26 });
	shootUp.PushBack({ 233, 363, 48, 26 });
	shootUp.loop = false;
	shootUp.speed = 0.15f;

	//Cannon down
	idleDown.PushBack({ 168, 421, 48, 26 });

	shootDown.PushBack({ 233, 421, 48, 26 });
	shootDown.PushBack({ 297, 421, 48, 26 });
	shootDown.PushBack({ 354, 421, 48, 26 });
	shootDown.PushBack({ 412, 421, 48, 26 });
	shootDown.PushBack({ 466, 421, 48, 26 });
	shootDown.PushBack({ 412, 421, 48, 26 });
	shootDown.PushBack({ 354, 421, 48, 26 });
	shootDown.PushBack({ 297, 421, 48, 26 });
	shootDown.PushBack({ 233, 421, 48, 26 });
	shootDown.loop = false;
	shootDown.speed = 0.15f;
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

	//Animation pointers
	animationHatch1 = &openingHatch1;
	animationHatch2 = &openingHatch2;

	animationCannonUp = &idleUp;
	animationCannonDown = &idleDown;

	animationLightTube = &lightTube;

	//Initial position
	positionX_uh = 7388;
	positionY_uh = 20;
	positionCoreY = 50;

	positionY_dh = positionY_uh + 80;

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

	if (currentTime > lastTime + 2000 && enemiesAdded == false) {
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINION, positionX_uh + 30, positionY_uh + 23);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINION, positionX_uh + 100, positionY_uh + 23);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINION, positionX_uh + 30, positionY_uh + 152);
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINION, positionX_uh + 100, positionY_uh + 152);		
		enemiesAdded = true;
	}
	else if (currentTime > lastTime + 3000 && enemiesAdded == true) {
		animationHatch1 = &closingHatch1;
		animationHatch2 = &closingHatch2;
	}

	if (currentTime > lastTime + 4000) {
		if(positionY_uh > - 25)
			positionY_uh--;

		if(positionY_dh < 145)
			positionY_dh++;
	}

	SDL_Rect hatch1 = animationHatch1->GetCurrentFrame();
	SDL_Rect hatch2 = animationHatch2->GetCurrentFrame();

	SDL_Rect cannon1 = animationCannonUp->GetCurrentFrame();
	SDL_Rect cannon2 = animationCannonDown->GetCurrentFrame();

	SDL_Rect tube = animationLightTube->GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(graphics, positionX_uh + 25, positionY_uh + 20, &hatch1, 1.0f, true);
	App->render->Blit(graphics, positionX_uh + 25, positionY_dh + 71, &hatch2, 1.0f, true);
	App->render->Blit(graphics, positionX_uh + 13, positionCoreY + 51, &tube, 1.0f, true);
	App->render->Blit(graphics, positionX_uh + 27, positionCoreY, &core, 1.0f, true);
	App->render->Blit(graphics, positionX_uh + 11, positionCoreY + 22, &cannon1, 1.0f, true);
	App->render->Blit(graphics, positionX_uh + 11, positionCoreY + 80, &cannon2, 1.0f, true);
	App->render->Blit(graphics, positionX_uh - 2, positionY_dh, &downHalf, 1.0f, true);
	App->render->Blit(graphics, positionX_uh, positionY_uh, &upHalf, 1.0f, true);

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