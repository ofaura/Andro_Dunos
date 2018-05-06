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

	// Colliders ----
	App->collision->Enable();
	App->collision->AddCollider({ 1105, 85, 78, 69 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1297, 5, 110, 72 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1473, 181, 110, 59 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1681, 52, 48, 40 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1825, 0, 191, 41 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1867, 41, 55, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1922, 41, 40, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2255, 214, 24, 18 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2279, 195, 36, 37 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2315, 176, 70, 56 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2385, 186, 50, 46 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2435, 199, 46, 33 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2481, 193, 27, 39 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2508, 202, 42, 30 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2550, 209, 14, 23 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2564, 213, 5, 19 }, COLLIDER_WALL);  //same meteorite
	App->collision->AddCollider({ 2569, 216, 11, 16 }, COLLIDER_WALL); //same meteorite
	App->collision->AddCollider({ 2580, 223, 10, 9 }, COLLIDER_WALL);  //same meteorite
	App->collision->AddCollider({ 2463, 0, 191, 49 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2505, 49, 55, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2560, 49, 40, 10 }, COLLIDER_WALL);

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

	App->render->Blit(background_texture, ((background_pos_x) / 3.5), 0, &background, 0.5f, true);	
	App->render->Blit(meteorites_texture1, 1100, background_pos_y, &meteorites1, 1.0f, true);

	return UPDATE_CONTINUE;
}

// Load assets
bool ModuleSceneLevel5::CleanUp()
{
	// Remove all memory leaks
	LOG("Unloading textures");
	App->audio->UnLoadFx(small_enemy_death);
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