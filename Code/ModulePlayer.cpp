#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleSceneLevel5.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleFonts.h"
#include "ModuleEnemies.h"
#include "ModuleBonus.h"
#include "ModuleUserInterface.h"
#include "ModuleShield.h"
#include "ModuleNonParticleShot.h"


ModulePlayer::ModulePlayer()
{
	current_animation = NULL;
	

	idle.PushBack({ 94, 108, 27, 17 });

	respawn.PushBack({ 94, 108, 27, 17 });
	respawn.PushBack({ 0, 0, 0, 0 });
	respawn.speed = 0.1f;
	respawn.loop = true;

	fire_idle.PushBack({ 73 , 111, 12 , 10 });
	fire_idle.PushBack({ 59, 111, 12, 10 });
	fire_idle.PushBack({ 42, 111, 12, 10 });
	fire_idle.loop = true;
	fire_idle.speed = 1.0f;

	up.PushBack({ 94, 108, 27, 17 });
	up.PushBack(up1);
	up.PushBack(up2);
	up.loop = false;
	up.speed = 0.1f;
	
	respawn_up.PushBack({ 94, 66, 27, 15 });
	respawn_up.PushBack({ 0, 0, 0, 0 });
	respawn_up.loop = true;
	respawn_up.speed = 0.1f;

	fire_up1.PushBack({ 73, 89, 5, 10});
	fire_up1.PushBack({ 59, 89, 8, 10 });
	fire_up1.PushBack({ 42, 89, 12, 10 });
	fire_up1.loop = true;
	fire_up1.speed = 1.0f;

	fire_up2.PushBack({ 73, 91, 12, 10 });
	fire_up2.PushBack({ 59, 91, 12, 10 });
	fire_up2.PushBack({ 42, 91, 12, 10 });
	fire_up2.loop = true;
	fire_up2.speed = 1.0f;

	down.PushBack({ 94, 108, 27, 17 });
	down.PushBack({ 0, 0, 0, 0 });
	down.PushBack(down1);
	down.PushBack(down2);
	down.loop = false;
	down.speed = 0.1f;

	respawn_down.PushBack({ 94, 153, 27, 17 });
	respawn_down.PushBack({ 0, 0, 0, 0 });
	respawn_down.loop = true;
	respawn_down.speed = 0.1f;

	fire_down1.PushBack({ 73, 138, 12, 8 });
	fire_down1.PushBack({ 59, 138, 12, 8 });
	fire_down1.PushBack({ 42, 138, 12, 8 });
	fire_down1.loop = true;
	fire_down1.speed = 1.0f;

	fire_down2.PushBack({ 73, 156, 12, 10 });
	fire_down2.PushBack({ 59, 156, 12, 10 });
	fire_down2.PushBack({ 42, 156, 12, 10 });
	fire_down2.loop = true;
	fire_down2.speed = 1.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	graphics = App->textures->Load("Assets/Sprites/player/ships.png"); // arcade version
	missile_graphics = App->textures->Load("Assets/Sprites/Particles/particles.png");
	t = 0;
	t_2 = 0;
	t_ani = 0;
	ini_down = 9;
	ini_up = 0;
	ini_down_prime = 9;
	ini_up_prime = 0;
	t_missile = 0;
	enable_missile1 = false;

	ani_miss_down.PushBack({ 296, 61, 12, 8 });
	ani_miss_down.PushBack({ 297, 105, 12, 9 });
	ani_miss_down.loop = false;
	ani_miss_down.speed = 0.1f;

	missile[0] = &ani_miss_down;

	ani_miss_up.PushBack({ 296, 61, 12, 8 });
	ani_miss_up.PushBack({ 297, 90, 12, 8 });
	ani_miss_up.loop = false;
	ani_miss_up.speed = 0.1f;

	missile[1] = &ani_miss_up;

	ShootPowerUpLevel = 1; // Primary Weap
	ShootPowerUpLevel_2 = 0; // Secondary Weap
	HomingMissile = 0; // Selfevident
	Shield = 0; // Selfevident

	// Audios are loaded
	laser1 = App->audio->LoadFx("Assets/Audio/Sound FX/laser1.wav");
	laser2 = App->audio->LoadFx("Assets/Audio/Sound FX/laser2.wav");
	laser3 = App->audio->LoadFx("Assets/Audio/Sound FX/laser3.wav");
	laser4 = App->audio->LoadFx("Assets/Audio/Sound FX/laser4.wav");
	player_death = App->audio->LoadFx("Assets/Audio/Sound FX/player_death.wav");
	type_change = App->audio->LoadFx("Assets/Audio/Sound FX/type_change.wav");

	position.x = 0;
	position.y = SCREEN_HEIGHT / 2;
	App->render->camera.x = 0;
	App->level5->ground_pos_x = 0;
	type = 0;

	lives = 2;


	player = App->collision->AddCollider({ position.x, position.y, 27, 17 }, COLLIDER_PLAYER, this);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	current_time = SDL_GetTicks() - first_time;

	if (dead == true && lives >= 0) 
	{
		current_animation = &respawn;
		if (current_time < 1000) {
			respawning = true;
		} else{
			respawning = false;
		}
		if (current_time < 4000) 
		{
			
			player->type = COLLIDER_NONE;
			if (current_time < 750)
			{
				position.x++;
			}			
		}

		else 
		{
			player->type = COLLIDER_PLAYER;
			dead = false;
			collision = true;
		}
	}

	int speed = 2;
	if (lives >= 0)
	{

		// Move Player --------------------------------------
	if(respawning==false){
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) == 1)
		{
			position.x -= speed;
		}
		else if (App->input->gamepadP1LAxisX < -6400) {
			position.x -= speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) == 1)
		{
			position.x += speed;
		}
		else if (App->input->gamepadP1LAxisX > 6400) {
			position.x += speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) == 1)
		{
			position.y += speed;
			if (dead == false) {
				if (current_animation != &down)
				{
					down.Reset();
					current_animation = &down;
				}
			}
			else if (dead == true) {
				if (current_animation != &respawn_down)
				{
					respawn_down.Reset();
					current_animation = &respawn_down;
				}
			}
		}
		else if (App->input->gamepadP1LAxisY > 6400) {
			position.y += speed;
			if (dead == false) {
				if (current_animation != &down)
				{
					down.Reset();
					current_animation = &down;
				}
			}
			else if (dead == true) {
				if (current_animation != &respawn_down)
				{
					respawn_down.Reset();
					current_animation = &respawn_down;
				}
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) == 1)
		{
			position.y -= speed;
			if (dead == false) {
				if (current_animation != &up)
					{
						up.Reset();
						current_animation = &up;
					}
			}
			else if (dead == true) {
				if (current_animation != &respawn_up)
				{
					respawn_up.Reset();
					current_animation = &respawn_up;
				}
			}
			
		}
		else if (App->input->gamepadP1LAxisY < -6400) {
			position.y -= speed;
			if (dead == false) {
				if (current_animation != &up)
					{
						up.Reset();
						current_animation = &up;
				}
			}
			else if (dead == true) {
				if (current_animation != &respawn_up)
				{
					respawn_up.Reset();
					current_animation = &respawn_up;
				}
			}
			
		}
	}
		if (current_animation != nullptr) { // Determines animation of fire
			if (current_animation->GetCurrentFrame().h == down1.h) {
				fire_current = &fire_down1;
			}

			else if (current_animation->GetCurrentFrame().h == down2.h) {
				fire_current = &fire_down2;
			}

			else if (current_animation->GetCurrentFrame().h == up1.h) {
				fire_current = &fire_up1;
			}

			else if (current_animation->GetCurrentFrame().h == up2.h) {
				fire_current = &fire_up2;
			}

			fire_position.y = position.y + 3;
			fire_position.x = position.x - 14;
		}		

		// Change weapon type --------------------------------------


		if (App->input->gamepadP1BPressed == true && App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_IDLE)
		{
			App->input->keyboard[SDL_SCANCODE_E] = KEY_STATE::KEY_DOWN;
		}
		else if (App->input->gamepadP1BPressed == true)
		{
			App->input->keyboard[SDL_SCANCODE_E] = KEY_STATE::KEY_REPEAT;
		}


		if (App->input->keyboard[SDL_SCANCODE_E] == KEY_STATE::KEY_DOWN)
		{
			if (type >= 0 && type < 3)
			{
				type++;
				App->audio->PlayFx(type_change);
			}
			else
			{
				type = 0;
				App->audio->PlayFx(type_change);
			}



			switch (type)
			{
			
			case bullet_type::TYPE_1:
				

				if (ShootPowerUpLevel == 1)
				{
					damage_1 = 1;
				}
					
				else if (ShootPowerUpLevel == 2)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 3)
				{
					damage_1 = 3;
				}

				else if (ShootPowerUpLevel == 4)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 5)
				{
					damage_1 = 4;
				}

				else if (ShootPowerUpLevel == 6)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel >= 7)
				{
					damage_1 = 5;
				}

				//--------------------------------------

				if (ShootPowerUpLevel_2 == 1)
				{
					damage_2 = 1;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 2;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 3;
				}

				break;
			case bullet_type::TYPE_2:

				if (ShootPowerUpLevel == 1)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 2)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 3)
				{
					damage_1 = 3;
				}

				else if (ShootPowerUpLevel == 4)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 5)
				{
					damage_1 = 4;
				}

				else if (ShootPowerUpLevel == 6)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel >= 7)
				{
					damage_1 = 5;
				}

				//--------------------------------------

				if (ShootPowerUpLevel_2 == 1)
				{
					damage_2 = 1;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 2;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 3;
				}

				break;
			case bullet_type::TYPE_3:

				if (ShootPowerUpLevel == 1)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 2)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 3)
				{
					damage_1 = 3;
				}

				else if (ShootPowerUpLevel == 4)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel >= 5)
				{
					damage_1 = 4;
				}

				//--------------------------------------

				if (ShootPowerUpLevel_2 == 1)
				{
					damage_2 = 1;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 2;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 3;
				}

				break;
			case bullet_type::TYPE_4:

				if (ShootPowerUpLevel == 1)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 2)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 3)
				{
					damage_1 = 3;
				}

				else if (ShootPowerUpLevel == 4)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel == 5)
				{
					damage_1 = 4;
				}

				else if (ShootPowerUpLevel == 6)
				{
					damage_1 = 2;
				}

				else if (ShootPowerUpLevel >= 7)
				{
					damage_1 = 5;
				}

				//--------------------------------------

				if (ShootPowerUpLevel_2 == 1)
				{
					damage_2 = 1;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 2;
				}

				else if (ShootPowerUpLevel_2 == 2)
				{
					damage_2 = 3;
				}

				break;
			}
		}


		// shoot -------------------------------------- 

		
		if (App->input->gamepadP1APressed == true && App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_IDLE)
		{
			App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_DOWN;
		}
		else if (App->input->gamepadP1APressed == true)
		{
			App->input->keyboard[SDL_SCANCODE_SPACE] = KEY_STATE::KEY_REPEAT;
		}


		t++;
		t_missile++;

		// Homing Missile
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN //|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1
			|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) /*|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)*/)
		{
			if (HomingMissile >= 1 && t_missile >= 100)
			{
				//App->accel_shot->AddShot(App->accel_shot->gravity_shot, position.x, position.y + 5, GRAVITY_SHOT, 1, 1);
				//AddShot(const Accel_Shot& particle, int x, int y, Accel_Shot_Type type, Uint32 delay);
				App->accel_shot->AddShot(App->accel_shot->homing_missile, position.x + 5, position.y + 5, HOMING_MISSILE, COLLIDER_PLAYER_SHOT_ALT);
				t_missile = 0;
			}
		}

		// TYPE-1, PRIMARY WEAP
		if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN //|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1
			|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) /*|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)*/ && type == bullet_type::TYPE_1)
		{
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) //|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)
			{
				if (ShootPowerUpLevel == 1) {
					App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 4, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser1);
				}
				else if (ShootPowerUpLevel == 2) {
					App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 15, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1, position.x + 32, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 3, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser1);
				}
				else if (ShootPowerUpLevel == 3)
				{
					App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 19, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_2, position.x + 32, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1, position.x + 25, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser1);
				}
				else if (ShootPowerUpLevel == 4)
				{
					App->particles->AddParticle(App->particles->laser1_2, position.x + 23, position.y + 19, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_2, position.x + 32, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_2, position.x + 23, position.y + -1, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser1);
				}

				else if (ShootPowerUpLevel == 5)
				{
					App->particles->AddParticle(App->particles->laser1_2, position.x + 23, position.y + 21, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_2, position.x + 32, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_2, position.x + 32, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_2, position.x + 23, position.y - 3, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser1);
				}

				else if (ShootPowerUpLevel == 6)
				{
					App->particles->AddParticle(App->particles->laser1_2, position.x + 23, position.y + 25, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_3, position.x + 32, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_3, position.x + 32, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_2, position.x + 23, position.y - 7, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser1);
				}
				else if (ShootPowerUpLevel >= 7)
				{
					App->particles->AddParticle(App->particles->laser1_3, position.x + 23, position.y + 25, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_3, position.x + 32, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_3, position.x + 32, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser1_3, position.x + 23, position.y - 11, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser1);
				}

			}

			// TYPE-1, SECONDARY WEAP // more damage on lvl 3 and level 5, current lvl 3 will be lvl 4
			if (ShootPowerUpLevel_2 >= 3 && t > 100)
			{
				enable_missile1 = true;
				t_ani = 1;
				t = 0;
			}

			else if (ShootPowerUpLevel_2 == 2 && t > 100)
			{
				t_ani = 1;
				t = 0;
			}
			else if (ShootPowerUpLevel_2 == 1 && t > 100)
			{
				t_ani = 1;
				t = 0;
			}


		}

		// TYPE-2, PRIMARY WEAP
		else if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN //|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1
			|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)/* || (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)*/ && type == bullet_type::TYPE_2)
		{
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) //|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)
			{

				if (ShootPowerUpLevel == 1)
				{
					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser2);
				}
				else if (ShootPowerUpLevel == 2)
				{
					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 12, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 15, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser2);
				}
				else if (ShootPowerUpLevel == 3)
				{
					App->particles->AddParticle(App->particles->laser2_3a, position.x, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_3b, position.x, position.y + 11, COLLIDER_PLAYER_SHOT);

					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 15, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser2);
				}
				else if (ShootPowerUpLevel == 4)
				{
					App->particles->AddParticle(App->particles->laser2_3a, position.x, position.y + 6, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_3b, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_2, position.x, position.y + 7, COLLIDER_PLAYER_SHOT);

					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser2);
				}

				else if (ShootPowerUpLevel == 5)
				{
					App->particles->AddParticle(App->particles->laser2_4a, position.x, position.y + 6, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_4b, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_5, position.x, position.y + 7, COLLIDER_PLAYER_SHOT);

					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 7, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 13, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser2);
				}

				else if (ShootPowerUpLevel == 6)
				{
					App->particles->AddParticle(App->particles->laser2_4a, position.x, position.y + 6, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_4b, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_5, position.x, position.y + 7, COLLIDER_PLAYER_SHOT);

					App->particles->AddParticle(App->particles->laser2_1, position.x + 15, position.y + 6, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_1, position.x + 7, position.y + -3, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_1, position.x + 7, position.y + 15, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser2);
				}
				else if (ShootPowerUpLevel >= 7)
				{
					App->particles->AddParticle(App->particles->laser2_4a, position.x, position.y + 6, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_4b, position.x, position.y + 8, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_5, position.x, position.y + 7, COLLIDER_PLAYER_SHOT);

					App->particles->AddParticle(App->particles->laser2_6, position.x + 15, position.y + 6, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_1, position.x + 7, position.y + -1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser2_1, position.x + 7, position.y + 14, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser2);
				}


			}

			if (ShootPowerUpLevel_2 >= 1) // 
			{

				if (ShootPowerUpLevel_2 >= 3 && t > 100)
				{
					App->particles->AddParticle(App->particles->missile2_4, position.x + 5, position.y - 3, COLLIDER_PLAYER_SHOT_ALT);
					App->particles->AddParticle(App->particles->missile2_3, position.x + 5, position.y + 15, COLLIDER_PLAYER_SHOT_ALT);
					App->audio->PlayFx(laser1); // missile1, meanwhile laser1 SFX

				}

				if (ShootPowerUpLevel_2 >= 2 && t > 100)
				{
					App->particles->AddParticle(App->particles->missile2_2, position.x + 5, position.y - 3, COLLIDER_PLAYER_SHOT_ALT);
					App->audio->PlayFx(laser1); // missile1, meanwhile laser1 SFX

				}

				if (t > 100)
				{
					App->particles->AddParticle(App->particles->missile2_1, position.x + 5, position.y + 15, COLLIDER_PLAYER_SHOT_ALT);
					App->audio->PlayFx(laser1); // missile1, meanwhile laser1 SFX
					t = 0;
				}
			}
		}

		// TYPE-3, PRIMARY WEAP
		else if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN
			|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) /*|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)*/ && type == bullet_type::TYPE_3)
		{
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) //|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)
			{

				if (ShootPowerUpLevel == 1) {
					App->particles->AddParticle(App->particles->laser3[0], position.x + 19, position.y + 11, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser3);
				}
				else if (ShootPowerUpLevel == 2) {
					App->particles->AddParticle(App->particles->laser3[1], position.x + 8, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[2], position.x + 8, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser3);
				}
				else if (ShootPowerUpLevel == 3)
				{
					App->particles->AddParticle(App->particles->laser3[1], position.x + 8, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[2], position.x + 8, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[3], position.x + 8, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[4], position.x + 8, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser3);
				}

				else if (ShootPowerUpLevel == 4)
				{
					App->particles->AddParticle(App->particles->laser3[5], position.x + 6, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[6], position.x + 6, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[7], position.x + 6, position.y + 1, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[8], position.x + 6, position.y + 5, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser3);
				}


				else if (ShootPowerUpLevel >= 5)
				{
					App->particles->AddParticle(App->particles->laser3[9], position.x + 2, position.y + -3, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[10], position.x + 2, position.y + 0, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[11], position.x + 2, position.y + -3, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser3[12], position.x + 2, position.y + 0, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser3);
				}

			}

			if (ShootPowerUpLevel_2 >= 1) // 
			{
				if (ShootPowerUpLevel_2 >= 3 && t > 100)
				{
					App->accel_shot->AddShot(App->accel_shot->gravity_shot_2, position.x + 10, position.y + 5, GRAVITY_SHOT, -1, -1, COLLIDER_PLAYER_SHOT_ALT); // HOMING MISSILE
					App->accel_shot->AddShot(App->accel_shot->gravity_shot, position.x + 10, position.y + 5, GRAVITY_SHOT, 1, -1, COLLIDER_PLAYER_SHOT_ALT); // HOMING MISSILE
					App->audio->PlayFx(laser1); //2 change
				}

				if (ShootPowerUpLevel_2 >= 2 && t > 100)
				{
				App->accel_shot->AddShot(App->accel_shot->gravity_shot_2, position.x, position.y + 5, GRAVITY_SHOT, -1, 1, COLLIDER_PLAYER_SHOT_ALT); // HOMING MISSILE
				App->audio->PlayFx(laser1); //2 change
				}

				if (t > 100) //
				{
					App->accel_shot->AddShot(App->accel_shot->gravity_shot, position.x, position.y + 5, GRAVITY_SHOT, 1, 1, COLLIDER_PLAYER_SHOT_ALT); // could also be: HOMING MISSILE
					App->audio->PlayFx(laser1); //2 change
					t = 0;
				}
			}
		}

		// TYPE-4, PRIMARY WEAP
		else if ((App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN
			|| App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT) /*|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)*/ && type == bullet_type::TYPE_4)
		{

			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) //|| (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_A)) == 1)
			{
				if (ShootPowerUpLevel == 1) {
					App->particles->AddParticle(App->particles->laser4[1], position.x + 19, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[2], position.x + 19, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser4);
				}
				else if (ShootPowerUpLevel == 2) {
					App->particles->AddParticle(App->particles->laser4[0], position.x + 28, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[1], position.x + 19, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[2], position.x + 19, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser4);
				}
				else if (ShootPowerUpLevel == 3) {
					App->particles->AddParticle(App->particles->laser4[3], position.x + 28, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[4], position.x + 19, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[5], position.x + 19, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser4);
				}
				else if (ShootPowerUpLevel == 4)
				{
					App->particles->AddParticle(App->particles->laser4[4], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[5], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[6], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[7], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser4);
				}
				else if (ShootPowerUpLevel == 5)
				{
					App->particles->AddParticle(App->particles->laser4[6], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[7], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[8], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[9], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser4);
				}
				else if (ShootPowerUpLevel == 6)
				{

					App->particles->AddParticle(App->particles->laser4[6], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[7], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[8], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[9], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[10], position.x + 40, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser4);
				}
				else if (ShootPowerUpLevel >= 7)
				{

					App->particles->AddParticle(App->particles->laser4[11], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[12], position.x + 10, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[8], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[9], position.x + 25, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->laser4[10], position.x + 40, position.y + 9, COLLIDER_PLAYER_SHOT);
					App->audio->PlayFx(laser4);
				}
			}

			if (ShootPowerUpLevel_2 >= 1) // 
			{
				if (ShootPowerUpLevel_2 >= 2 && t > 100)
				{
					App->particles->AddParticle(App->particles->missile4[0], position.x + 8, position.y + 1, COLLIDER_PLAYER_SHOT_ALT);
					App->particles->AddParticle(App->particles->missile4[1], position.x + 8, position.y + 13, COLLIDER_PLAYER_SHOT_ALT);
					App->particles->AddParticle(App->particles->missile4[2], position.x + 3, position.y - 6, COLLIDER_PLAYER_SHOT_ALT);
					App->particles->AddParticle(App->particles->missile4[3], position.x + 3, position.y + 5, COLLIDER_PLAYER_SHOT_ALT);
					App->audio->PlayFx(laser4);
				}

				if (t > 100)
				{
					App->particles->AddParticle(App->particles->missile4[0], position.x + 8, position.y + 1, COLLIDER_PLAYER_SHOT_ALT);
					App->particles->AddParticle(App->particles->missile4[1], position.x + 8, position.y + 13, COLLIDER_PLAYER_SHOT_ALT);
					App->audio->PlayFx(laser4);
					t = 0;
				}
			}

		}


		// Begin: Part of Type-1
		if (t_ani >= 1 && t_ani < 16)
		{
			ini_down++;
			App->render->Blit(missile_graphics, position.x + 5, position.y + ini_down, &(missile[0]->GetCurrentFrame()));
			if (ShootPowerUpLevel_2 >= 2)
			{
				ini_up--;
				App->render->Blit(missile_graphics, position.x + 5, position.y + ini_up, &(missile[1]->GetCurrentFrame()));
			}
			t_ani++;
		}
		else if (t_ani >= 16)
		{
			if (ShootPowerUpLevel_2 >= 2)
			{
				App->particles->AddParticle(App->particles->missile1_2, position.x + 5, position.y - 7, COLLIDER_PLAYER_SHOT_ALT);
				App->audio->PlayFx(laser1); // missile1, meanwhile laser1 SFX
				missile[1]->Reset();
				ini_up = 0;
			}
			App->particles->AddParticle(App->particles->missile1_1, position.x + 5, position.y + 20, COLLIDER_PLAYER_SHOT_ALT);
			App->audio->PlayFx(laser1); // missile1, meanwhile laser1 SFX
			missile[0]->Reset();
			ini_down = 9;
			
			t_ani = 0;
		}

		if (enable_missile1 == true)
		{
			t_2++;
			if (t_2 >= 20)
			{
				if (t_2 >= 20 && t_2 < 35)
				{
					ini_down_prime++;
					App->render->Blit(missile_graphics, position.x + 5, position.y + ini_down_prime, &(missile[0]->GetCurrentFrame()));
					ini_up_prime--;
					App->render->Blit(missile_graphics, position.x + 5, position.y + ini_up_prime, &(missile[1]->GetCurrentFrame()));
		
				}

				else if (t_2 >= 35)
				{

					App->particles->AddParticle(App->particles->missile1_3b, position.x + 5, position.y - 7, COLLIDER_PLAYER_SHOT_ALT);
					App->audio->PlayFx(laser1); // missile1, meanwhile laser1 SFX
					missile[1]->Reset();
					
					
					App->particles->AddParticle(App->particles->missile1_3a, position.x + 5, position.y + 20, COLLIDER_PLAYER_SHOT_ALT);
					App->audio->PlayFx(laser1); // missile1, meanwhile laser1 SFX
					missile[0]->Reset();  

					enable_missile1 = false;

					ini_up_prime = 0;
					ini_down_prime = 9;
					t_2 = 0;
				}
			}
		}
		// End: part of Type-1

		// Shield
		if (Shield != 0)
		{

			App->shield->Enable();

		}

		// Player Idle position if not going up or down -------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE && (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) == 0
			&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && (SDL_GameControllerGetButton(App->input->controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) == 0 && dead == false
			&& (App->input->gamepadP1LAxisY < 6400 && App->input->gamepadP1LAxisY > -6400) && (App->input->gamepadP1LAxisX < 6400 && App->input->gamepadP1LAxisX > -6400))
		{
		current_animation = &idle;
		fire_current = &fire_idle;
		}

		// Prevent Player from leaving bordrer -------------------------------------
		//x lim
		if (respawning == false) {
			if (position.x <= abs(App->render->camera.x) / SCREEN_SIZE)
			{
				position.x = 1 + (abs(App->render->camera.x) / SCREEN_SIZE);
			}
			else if (position.x >= ((abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH - 27)))
			{
				position.x = -1 + ((abs(App->render->camera.x) / SCREEN_SIZE + SCREEN_WIDTH - 27));
			}
		}
		//y lim

		if (position.y <= abs(App->render->camera.y) / SCREEN_SIZE)
		{
			position.y = 1 + abs(App->render->camera.y) / SCREEN_SIZE;
		}
		else if (position.y >= (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 17) // the -50 just showcases that the camera limit on the lower end works, it stopps player before they touch the ground and crash
		{
			position.y = -1 + (abs(App->render->camera.y) / SCREEN_SIZE) + SCREEN_HEIGHT - 17;
		}
	}	


	if (App->input->gamepadP1YPressed == true && App->input->keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_IDLE)
	{
		App->input->keyboard[SDL_SCANCODE_F5] = KEY_STATE::KEY_DOWN;
	}
	else if (App->input->gamepadP1YPressed == true)
	{
		App->input->keyboard[SDL_SCANCODE_F5] = KEY_STATE::KEY_REPEAT;
	}

	// God mode
	if (App->player->lives >= 0)
	{
		if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
		{			
				GodMode = !GodMode;

				if (GodMode == true)
				{
					if (player->type != COLLIDER_NONE) {
						player->to_delete = true;
						
						player = nullptr;
					}
				}
				else if (GodMode == false)
				{
					GodMode = false;
					player = App->collision->AddCollider({ position.x, position.y, 27, 17 }, COLLIDER_PLAYER, this);
				}
		}

	// Update collider position to player position
	if (GodMode == false)
		{
			player->SetPos(position.x, position.y);
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect fire = fire_current->GetCurrentFrame();

	// Blitting the player
	App->render->Blit(graphics, position.x, position.y, &r);
	App->render->Blit(graphics, fire_position.x, fire_position.y, &fire);

	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	// Remove all memory leaks
	LOG("Unloading ship");
	App->audio->UnLoadFx(type_change);
	App->audio->UnLoadFx(player_death);
	App->audio->UnLoadFx(laser4);
	App->audio->UnLoadFx(laser3);
	App->audio->UnLoadFx(laser2);
	App->audio->UnLoadFx(laser1);
	App->textures->Unload(graphics);

	return true;
}

// Detects collision with a wall. If so, go back to game over screen.
void ModulePlayer::OnCollision(Collider* col_1, Collider* col_2)
{
	if ((col_1->type == COLLIDER_ENEMY_SHOT || col_1->type == COLLIDER_ENEMY) || (col_2->type == COLLIDER_ENEMY_SHOT || col_2->type == COLLIDER_WALL)
		|| (col_2->type == COLLIDER_ENEMY || col_1->type == COLLIDER_WALL))
	{

		App->particles->AddParticle(App->particles->explosionP1, position.x, position.y);

		if (App->player->lives >= 0)
		{

			dead = true;
			first_time = SDL_GetTicks();
			App->audio->PlayFx(player_death);
			if (collision == true) {
				App->player->lives--;
			}
			collision = false;

			if (lives == -1)
			{
				App->fade->FadeToBlack(App->level5, App->game_over);
			}
			position.x = 1 + abs(App->render->camera.x) / SCREEN_SIZE - 30;
			position.y = (abs(App->render->camera.y) / SCREEN_SIZE) + (SCREEN_HEIGHT / 2);
		}

	}
};
