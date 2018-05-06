#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel5.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleBonus.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleShield.h"

ModuleSceneLevel5::ModuleSceneLevel5()
{
	// Background 
	background.x = 10;
	background.y = 0;
	background.w = 3970;
	background.h = 199;

	meteorites1.x = 200;
	meteorites1.y = 38;
	meteorites1.w = 1554;
	meteorites1.h = 240;

	meteorites2.x = 9;
	meteorites2.y = 15;
	meteorites2.w = 3766;
	meteorites2.h = 224;
}

ModuleSceneLevel5::~ModuleSceneLevel5()
{}

// Load assets
bool ModuleSceneLevel5::Start()
{
	LOG("Loading background assets");
	bool ret = true;

	//Textures are loaded
	background_texture = App->textures->Load("Assets/Sprites/lvl5/Background/background5.png");
	meteorites_texture1 = App->textures->Load("Assets/Sprites/lvl5/Background/meteorites1.png");
	meteorites_texture2 = App->textures->Load("Assets/Sprites/lvl5/Background/meteorites2.png");

	//Audios are loaded
	small_enemy_death = App->audio->LoadFx("Assets/Audio/Sound FX/enemy_small_explosion.wav");

	if (IsEnabled()) {
		if (App->player->IsEnabled() == false) {
			App->player->Enable();
		}
	}
	if (IsEnabled() == false) {
		if (App->player->IsEnabled() == true) {
			App->player->Disable();
		}
	}

	App->user_interface->Enable();

	// Reseting the camera to the start of the level
	App->render->camera.x = App->render->camera.y = 0;
	App->render->camera.w = SCREEN_WIDTH;
	App->render->camera.h = SCREEN_HEIGHT;

	//Enemies ---
	App->enemies->Enable();

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_POWERUP, 300, (SCREEN_HEIGHT / 2) - 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_POWERUP, 400, (SCREEN_HEIGHT / 2) - 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_POWERUP, 500, (SCREEN_HEIGHT / 2) - 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_POWERUP, 600, (SCREEN_HEIGHT / 2) - 20);

	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 200, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 215, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 230, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::FIRST_ENEMY, 245, 60);

	// Colliders ---
	App->collision->Enable();

	// Meteorite 1
	App->collision->AddCollider({ 1028, 86, 38, 6 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1013, 92, 67, 20 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1005, 112, 78, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1012, 132, 60, 5 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1017, 137, 52, 7 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1028, 144, 35, 8 }, COLLIDER_WALL);	
	
	// Meteorite 2
	App->collision->AddCollider({ 1220, 6, 72, 9 }, COLLIDER_WALL);		
	App->collision->AddCollider({ 1205, 15, 102, 20 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1197, 35, 108, 22 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1207, 57, 89, 8 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1220, 65, 69, 11 }, COLLIDER_WALL);	

	// Meteorite 3
	App->collision->AddCollider({ 1396, 182, 72, 9 }, COLLIDER_WALL);		
	App->collision->AddCollider({ 1381, 191, 102, 20 }, COLLIDER_WALL);	
	App->collision->AddCollider({ 1373, 211, 108, 30 }, COLLIDER_WALL);	
		
	App->collision->AddCollider({ 1581, 52, 48, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1725, 0, 191, 41 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1767, 41, 55, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1822, 41, 40, 10 }, COLLIDER_WALL);

	App->collision->AddCollider({ 2155, 214, 24, 18 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2179, 195, 36, 37 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2215, 176, 70, 56 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2285, 186, 50, 46 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2335, 199, 46, 33 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2381, 193, 27, 39 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2408, 202, 42, 30 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2450, 209, 14, 23 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2464, 213, 5, 19 }, COLLIDER_WALL);  //same meteorite
	App->collision->AddCollider({ 2469, 216, 11, 16 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2480, 223, 10, 9 }, COLLIDER_WALL);  //same meteorite

	App->collision->AddCollider({ 2363, 0, 191, 49 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2405, 49, 55, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2460, 49, 40, 10 }, COLLIDER_WALL);
	
	App->collision->AddCollider({ 3005, 218, 551, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3008, 208, 525, 10 }, COLLIDER_WALL);

	//Audio ---
	App->audio->PlayMusic("Assets/Audio/Music/level5.ogg", 1.0f);

	return ret;
}

// Update: draw background
update_status ModuleSceneLevel5::Update()
{

	if (App->render->camera.x >= 0 && App->render->camera.x <= 8800 * SCREEN_SIZE)
	{
		App->render->camera.x += 1 * SCREEN_SIZE;
		App->player->position.x += 1;
		App->player2->position.x += 1;
	}

	App->render->Blit(background_texture, ((background_pos_x) / 3.5), 20, &background, 0.5f, true);	
	App->render->Blit(meteorites_texture1, 1000, background_pos_y, &meteorites1, 1.0f, true);
	App->render->Blit(meteorites_texture2, 3000, background_pos_y, &meteorites2, 1.0f, true);

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneLevel5::CleanUp()
{
	// Remove all memory leaks
	LOG("Unloading textures");
	App->audio->UnLoadFx(small_enemy_death);
	App->textures->Unload(meteorites_texture2);
	App->textures->Unload(meteorites_texture1);
	App->textures->Unload(background_texture);

	App->collision->CleanUp();

	App->user_interface->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->player->Disable();
	App->shield->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}