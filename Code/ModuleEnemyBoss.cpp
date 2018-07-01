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
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"

ModuleEnemyBoss::ModuleEnemyBoss()
{
	HP = BOSS_HP;

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

	shootUp.PushBack({ 231, 363, 48, 26 });
	shootUp.PushBack({ 293, 363, 48, 26 });
	shootUp.PushBack({ 348, 363, 48, 26 });
	shootUp.PushBack({ 404, 363, 48, 26 });
	shootUp.PushBack({ 456, 363, 48, 26 });
	shootUp.PushBack({ 404, 363, 48, 26 });
	shootUp.PushBack({ 348, 363, 48, 26 });
	shootUp.PushBack({ 293, 363, 48, 26 });
	shootUp.PushBack({ 231, 363, 48, 26 });
	shootUp.loop = false;
	shootUp.speed = 0.3f;

	//Cannon down
	idleDown.PushBack({ 168, 421, 48, 26 });

	shootDown.PushBack({ 231, 421, 48, 26 });
	shootDown.PushBack({ 293, 421, 48, 26 });
	shootDown.PushBack({ 348, 421, 48, 26 });
	shootDown.PushBack({ 404, 421, 48, 26 });
	shootDown.PushBack({ 456, 421, 48, 26 });
	shootDown.PushBack({ 404, 421, 48, 26 });
	shootDown.PushBack({ 348, 421, 48, 26 });
	shootDown.PushBack({ 293, 421, 48, 26 });
	shootDown.PushBack({ 231, 421, 48, 26 });
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
	currentTimeMusic = SDL_GetTicks();
	currentTimeShot = SDL_GetTicks();
	currentTimeRing = SDL_GetTicks();

	lastTime = currentTime;
	lastTimeMusic = currentTimeMusic;
	lastTimeShot = currentTimeShot;
	lastTimeRing = currentTimeRing;

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
	positionLightX = positionX_uh + 13;
	positionY_dh = positionY_uh + 80;

	boss = App->collision->AddCollider({ positionX_uh + 11, positionCoreY + 23, 140, 80 }, COLLIDER_ENEMY, this);
	upperHalf = App->collision->AddCollider({ positionX_uh - 2, positionY_uh, 10, 95 }, COLLIDER_WALL, this);
	underHalf = App->collision->AddCollider({ positionX_uh - 2, positionY_dh + 15, 10, 95 }, COLLIDER_WALL, this);

	return true;
}

// Update: draw background
update_status ModuleEnemyBoss::Update()
{
	currentTime = SDL_GetTicks();
	currentTimeMusic = SDL_GetTicks();
	currentTimeShot = SDL_GetTicks();
	currentTimeRing = SDL_GetTicks();

	if (currentTimeMusic > lastTimeMusic + 9000 && musicPlayed == false)
	{
		App->audio->PlayMusic("Assets/Audio/Music/bossLoop.ogg", 0.0f); //Loop music
		musicPlayed = true;
	}

	if (HP > 0) {

		//Hatchs animations
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
			openingHatch1.Reset();
			openingHatch2.Reset();
		}

		//Opening
		if (currentTime > lastTime + 4000 && opened == false && movementEnabled == false) {
			if (positionY_uh > -25)
				positionY_uh--;

			if (positionY_dh < 145)
				positionY_dh++;
			else {
				closing = false;
				movementEnabled = true;
			}
		}
		//Closing
		else if (currentTime > lastTime + 15000 && opened == true) {
			closing = true;

			if (positionY_uh < 20)
				positionY_uh++;

			if (positionY_dh > 100)
				positionY_dh--;

			else {
				going_up = true;
				opened = false;
				enemiesAdded = false;
				animationHatch1 = &openingHatch1;
				animationHatch2 = &openingHatch2;
				closingHatch1.Reset();
				closingHatch2.Reset();
				lastTime = currentTime;
			}
		}		

		//Up and down movement
		if (currentTime > lastTime + 5000 && movementEnabled == true) {

			if (going_up)
			{
				if (positionY_uh > -60) {
					positionY_uh--;
					positionY_dh--;
				}
				else
					going_up = false;
			}
			else
			{
				if (positionY_uh < 40) {
					positionY_uh++;
					positionY_dh++;
				}
				else
					going_up = true;
			}
		}

		if (currentTime > lastTime + 12900 && opened == false) {
			opened = true;
			movementEnabled = false;
		}

		//Light tube movement
		if (going_back)
		{
			if (positionLightX < positionX_uh + 30)
				positionLightX++;
			else
				going_back = false;
		}
		else
		{
			if (positionLightX > positionX_uh + 5)
				positionLightX--;
			else
				going_back = true;
		}

		//Cannons shooting
		if (currentTimeShot > lastTimeShot + 4300 && opened == true && closing == false) {
			animationCannonDown = &shootDown;
			App->particles->AddParticle(App->particles->torpede, positionX_uh + 60, positionCoreY + 83, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->torpedeFire, positionX_uh + 100, positionCoreY + 83, COLLIDER_NONE);
			lastTimeShot = currentTimeShot;
			cannonShot = false;
		}
		else if (currentTimeShot > lastTimeShot + 4000 && opened == true && closing == false) {
			animationCannonUp = &shootUp;
			if (cannonShot == false) {
				App->particles->AddParticle(App->particles->torpede, positionX_uh + 60, positionCoreY + 29, COLLIDER_ENEMY_SHOT);
				App->particles->AddParticle(App->particles->torpedeFire, positionX_uh + 100, positionCoreY + 29, COLLIDER_NONE);
				cannonShot = true;
			}
		}

		if (shootUp.Finished() == true) {
			shootUp.Reset();
			animationCannonUp = &idleUp;
		}

		if (shootDown.Finished() == true) {
			shootDown.Reset();
			animationCannonDown = &idleDown;
		}

		//Colliders update
		upperHalf->SetPos(positionX_uh - 2, positionY_uh);
		underHalf->SetPos(positionX_uh - 2, positionY_dh + 15);

		//Ring shooting
		if (currentTimeRing > lastTimeRing + 3000 && opened == true && closing == false) {
			App->particles->AddParticle(App->particles->ring1, positionLightX - 10, positionCoreY + 55, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->ring2, positionLightX - 10, positionCoreY + 55, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->ring3, positionLightX - 10, positionCoreY + 55, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->ring4, positionLightX - 10, positionCoreY + 55, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->ring5, positionLightX - 10, positionCoreY + 55, COLLIDER_ENEMY_SHOT);
			lastTimeRing = currentTimeRing;
		}
		
		SDL_Rect hatch1 = animationHatch1->GetCurrentFrame();
		SDL_Rect hatch2 = animationHatch2->GetCurrentFrame();

		SDL_Rect cannon1 = animationCannonUp->GetCurrentFrame();
		SDL_Rect cannon2 = animationCannonDown->GetCurrentFrame();

		SDL_Rect tube = animationLightTube->GetCurrentFrame();

		// Draw everything --------------------------------------

		App->render->Blit(graphics, positionX_uh + 25, positionY_uh + 20, &hatch1, 1.0f, true);
		App->render->Blit(graphics, positionX_uh + 25, positionY_dh + 71, &hatch2, 1.0f, true);
		App->render->Blit(graphics, positionLightX, positionCoreY + 51, &tube, 1.0f, true);
		App->render->Blit(graphics, positionX_uh + 27, positionCoreY, &core, 1.0f, true);
		App->render->Blit(graphics, positionX_uh + 11, positionCoreY + 22, &cannon1, 1.0f, true);
		App->render->Blit(graphics, positionX_uh + 11, positionCoreY + 80, &cannon2, 1.0f, true);
		App->render->Blit(graphics, positionX_uh - 2, positionY_dh, &downHalf, 1.0f, true);
		App->render->Blit(graphics, positionX_uh, positionY_uh, &upHalf, 1.0f, true);
		
	}

	return UPDATE_CONTINUE;
}

void ModuleEnemyBoss::OnCollision(Collider* collider1, Collider* collider2) {
	
	if (HP <= 0) {
		//App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
		App->audio->PlayFx(App->enemies->boss_death);

		if (dead == false)
		{
			if ((collider1->type == COLLIDER_PLAYER_SHOT && collider2->type == COLLIDER_ENEMY)||
				(collider2->type == COLLIDER_PLAYER_SHOT && collider1->type == COLLIDER_ENEMY))
			{
				App->user_interface->score1 += bossScore;
			}
			if ((collider1->type == COLLIDER_PLAYER2_SHOT && collider2->type == COLLIDER_ENEMY) ||
				(collider2->type == COLLIDER_PLAYER2_SHOT && collider1->type == COLLIDER_ENEMY))
			{
				App->user_interface->score2 += bossScore;
			}
		}
		dead = true;
	}
	else if(collider1->type != COLLIDER_WALL && collider1->type != COLLIDER_WALL){
		App->audio->PlayFx(App->enemies->enemy_hit);
		HP--;
	}
}

// UnLoad assets
bool ModuleEnemyBoss::CleanUp()
{
	LOG("Unloading Neo Geo logo scene");
	App->audio->UnLoadFx(boss_death);
	App->textures->Unload(graphics);

	return true;
}