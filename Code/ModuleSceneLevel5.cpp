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
#include "ModuleShield_p2.h"

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
	
	// Mines
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINE, 760, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINE, 800, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINE, 860, 10);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINE, 900, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINE, 960, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_MINE, 1000, 150);
		
	// Shuttle
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1250, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1265, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1280, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1295, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1310, 70);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1325, 70);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1500, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1515, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1530, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1545, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1560, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 1575, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 2600, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 2615, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 2630, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SHUTTLE, 2645, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1600, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1650, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1700, 220);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_WASP, 1750, 120);
	
	// Little turret
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_UP, 1750, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_UP, 1796, 63);
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_UP, 1835, 49);
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_UP, 1875, 38);

	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_DOWN, 2195, 181);
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_DOWN, 2248, 165);
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_DOWN, 2297, 176);
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_DOWN, 2353, 185);
	App->enemies->AddEnemy(ENEMY_TYPES::LITTLE_TURRET_DOWN, 2420, 186);

	// Enemy Xwing
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2275, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2300, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2325, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2350, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2375, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2450, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2475, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2500, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_XWING, 2525, 90);

	// Enemy spinner
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SPINNER, 2650, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SPINNER, 2750, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SPINNER, 2750, 160);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_SPINNER, 2850, 100);

	// Missile thrower
	App->enemies->AddEnemy(ENEMY_TYPES::MISSILE_THROWER, 700, 100);
	
	// Meteorites
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 340, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 390, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 400, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 400, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 430, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 350, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 500, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 500, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 530, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 560, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 510, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 560, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 600, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 680, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 600, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 630, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 700, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 700, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 720, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 800, 20);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 800, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 830, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 900, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMY_METEORITE, 950, 120);

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
	App->collision->AddCollider({ 3191, 201, 47, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3447, 201, 47, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3014, 203, 158, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3270, 203, 158, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3040, 192, 109, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3298, 192, 109, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3047, 186, 65, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3303, 186, 65, 6 }, COLLIDER_WALL);
	
	App->collision->AddCollider({ 4272, 0, 177, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4275, 6, 166, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4303, 24, 69, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4372, 24, 35, 13 }, COLLIDER_WALL);

	App->collision->AddCollider({ 6176, 0, 177, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6178, 6, 166, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6206, 24, 69, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6275, 24, 35, 13 }, COLLIDER_WALL);

	App->collision->AddCollider({ 4852, 87, 57, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4840, 101, 79, 41 }, COLLIDER_WALL);

	App->collision->AddCollider({ 4504, 199, 15, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4519, 190, 14, 34 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4533, 171, 34, 53 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4567, 156, 68, 68 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4635, 166, 41, 60 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4676, 170, 19, 54 }, COLLIDER_WALL);

	App->collision->AddCollider({ 4934, 204, 32, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4966, 186, 68, 38 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5034, 193, 44, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5078, 200, 76, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5154, 208, 44, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5198, 218, 19, 6 }, COLLIDER_WALL);

	App->collision->AddCollider({ 5080, 72, 9, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5089, 69, 7, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5096, 60, 58, 41 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5117, 52, 19, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5092, 100, 46, 4 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5154, 67, 4, 30 }, COLLIDER_WALL);

	App->collision->AddCollider({ 5235, 0, 29, 41 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5264, 0, 64, 61 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5328, 0, 36, 48 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5364, 0, 34, 39 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5398, 0, 14, 24 }, COLLIDER_WALL);

	App->collision->AddCollider({ 5481, 112, 75, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5483, 127, 62, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5489, 92, 66, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5503, 146, 27, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5510, 86, 28, 7 }, COLLIDER_WALL);

	App->collision->AddCollider({ 5580, 211, 14, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5594, 200, 14, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5608, 187, 32, 37 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5640, 172, 66, 52 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5706, 187, 53, 42 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5759, 190, 40, 34 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5799, 186, 91, 38 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5890, 196, 44, 33 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5934, 204, 29, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5963, 215, 12, 9 }, COLLIDER_WALL);

	App->collision->AddCollider({ 5719, 0, 12, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5732, 0, 14, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5746, 0, 53, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5799, 0, 90, 20}, COLLIDER_WALL);
	App->collision->AddCollider({ 5889, 0, 56, 27}, COLLIDER_WALL);
	App->collision->AddCollider({ 5945, 0, 17, 19}, COLLIDER_WALL);
	App->collision->AddCollider({ 5962, 0, 12, 9 }, COLLIDER_WALL);

	App->collision->AddCollider({ 6011, 83, 7, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6018, 65, 14, 47 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6032, 52, 57, 68 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6089, 63, 27, 43 }, COLLIDER_WALL);

	App->collision->AddCollider({ 6249, 167, 8, 18 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6257, 165, 8, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6265, 157, 61, 41 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6283, 148, 20, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6287, 198, 25, 3 }, COLLIDER_WALL);

	App->collision->AddCollider({ 6573, 213, 15, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6588, 200, 9, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6597, 189, 30, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6627, 189, 81, 42 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6631, 176, 58, 6 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6633, 171, 43, 5 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6655, 164, 16, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6708, 185, 51, 99 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6716, 178, 19, 7 }, COLLIDER_WALL);

	App->collision->AddCollider({ 6620, 182, 100, 7 }, COLLIDER_WALL);

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
	App->textures->Unload(meteorites_texture2);
	App->textures->Unload(meteorites_texture1);
	App->textures->Unload(background_texture);

	App->collision->CleanUp();

	App->user_interface->Disable();
	App->enemies->Disable();
	App->collision->Disable();
	App->player->Disable();
	
	if(App->shield->IsEnabled() == true)
		App->shield->Disable();

	if (App->shield_p2->IsEnabled() == true)
		App->shield_p2->Disable();

	if (App->player2->IsEnabled() == true)
		App->player2->Disable();

	return true;
}