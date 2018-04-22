#include <math.h>
#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleShield_p2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

ModuleShield_p2::ModuleShield_p2() {

	// ---- Animation for the base od the shield
	base_anim.PushBack({ 0, 0, 9, 16 });
	base_anim.PushBack({ 11, 0, 9, 16 });
	base_anim.PushBack({ 22, 0, 9, 16 });
	base_anim.PushBack({ 33, 0, 9, 16 });
	base_anim.PushBack({ 44, 0, 9, 16 });
	base_anim.PushBack({ 55, 0, 9, 16 });
	base_anim.loop = true;
	base_anim.speed = 0.2f;

	// ---- Animation for lvl1 LaserShield (Red)
	lvl1.PushBack({ 46, 18, 5, 14 });
	lvl1.PushBack({ 0, 18, 5, 14 });
	lvl1.PushBack({ 7, 18, 5, 14 });
	lvl1.PushBack({ 0, 18, 5, 14 });
	lvl1.loop = true;
	lvl1.speed = 0.5f;

	// ---- Animation for lvl2 LaserShield (Yellow)
	lvl2.PushBack({ 46, 18, 5, 14 });
	lvl2.PushBack({ 30, 18, 5, 14 });
	lvl2.PushBack({ 36, 18, 5, 14 });
	lvl2.PushBack({ 30, 18, 5, 14 });
	lvl2.loop = true;
	lvl2.speed = 0.5f;

	// ---- Animation for lvl3 LaserShield (Green)
	lvl3.PushBack({ 46, 18, 5, 14 });
	lvl3.PushBack({ 15, 18, 5, 14 });
	lvl3.PushBack({ 22, 18, 5, 14 });
	lvl3.PushBack({ 15, 18, 5, 14 });
	lvl3.loop = true;
	lvl3.speed = 0.5f;
}

ModuleShield_p2::~ModuleShield_p2() {}

bool ModuleShield_p2::Start() {
	bool ret = true;

	graphics = App->textures->Load("Assets/Sprites/player/shield.png"); //Loads shield image bank

	if (graphics == nullptr) ret = false; //failsafe for wrong address

	switch (App->player2->type) {

		// ---- Stays in front of ship
	case bullet_type::TYPE_1:
		position1.x = App->player2->position.x + 29;
		position1.y = App->player2->position.y - 8;
		position2.x = App->player2->position.x + 29;
		position2.y = App->player2->position.y + 10;
		break;

		// ---- Stays on either side of the ship
	case bullet_type::TYPE_2:
		position1.x = App->player2->position.x + 5;
		position1.y = App->player2->position.y - 8;
		position2.x = App->player2->position.x + 5;
		position2.y = App->player2->position.y + 10;
		break;

		// ---- Stays in front of ship
	case bullet_type::TYPE_3:
		position1.x = App->player2->position.x + 29;
		position1.y = App->player2->position.y - 8;
		position2.x = App->player2->position.x + 29;
		position2.y = App->player2->position.y + 10;
		break;

		// ---- Stays behind ship
	case bullet_type::TYPE_4:
		position1.x = App->player2->position.x + 29;
		position1.y = App->player2->position.y - 8;
		position2.x = App->player2->position.x + 29;
		position2.y = App->player2->position.y + 10;
		break;
	}


	// ---- Declares colliders for shield parts individually
	collider1 = App->collision->AddCollider({ position1.x, position1.y, 14, 16 }, COLLIDER_SHIELD_1, this);
	collider2 = App->collision->AddCollider({ position2.x, position2.y, 14, 16 }, COLLIDER_SHIELD_1, this);

	return ret;
}

update_status ModuleShield_p2::Update() {

	if (life == 1) current_lvl = &lvl1;
	else if (life == 2)	current_lvl = &lvl2;
	else if (life == 3)	current_lvl = &lvl3;

	// ---- Keeps realtive position to the ship
	switch (App->player2->type) {

		// ---- Stays in front of ship
	case bullet_type::TYPE_1:
		position1.x = App->player2->position.x + 29;
		position1.y = App->player2->position.y - 8;
		position2.x = App->player2->position.x + 29;
		position2.y = App->player2->position.y + 10;
		break;

		// ---- Stays on either side of the ship
	case bullet_type::TYPE_2:
		position1.x = App->player2->position.x + 5;
		position1.y = App->player2->position.y - 15;
		position2.x = App->player2->position.x + 5;
		position2.y = App->player2->position.y + 17;
		break;

		// ---- Stays in front of ship
	case bullet_type::TYPE_3:
		position1.x = App->player2->position.x + 29;
		position1.y = App->player2->position.y - 8;
		position2.x = App->player2->position.x + 29;
		position2.y = App->player2->position.y + 10;
		break;

		// ---- Stays behind ship
	case bullet_type::TYPE_4:
		position1.x = App->player2->position.x - 16;
		position1.y = App->player2->position.y - 8;
		position2.x = App->player2->position.x - 16;
		position2.y = App->player2->position.y + 10;
		break;
	}

	// ---- Updates colliders
	collider1->SetPos(position1.x, position1.y);
	collider2->SetPos(position2.x, position2.y);

	SDL_Rect base = base_anim.GetCurrentFrame();
	SDL_Rect light = current_lvl->GetCurrentFrame();

	// ---- Draw Everything
	App->render->Blit(graphics, position1.x, position1.y, &base);
	App->render->Blit(graphics, position2.x, position2.y, &base);
	App->render->Blit(graphics, position1.x + 8, position1.y + 1, &light);
	App->render->Blit(graphics, position2.x + 8, position2.y + 1, &light);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleShield_p2::CleanUp() {

	// Remove all memory leaks
	LOG("Unloading shield");
	App->textures->Unload(graphics);

	//Get rid of colliders;
	collider1 = nullptr;
	collider2 = nullptr;

	return true;
}

void ModuleShield_p2::OnCollision(Collider* col_1, Collider* col_2)
{
	if (col_1->type == COLLIDER_ENEMY && col_2->type == COLLIDER_SHIELD_1 || col_2->type == COLLIDER_ENEMY && col_1->type == COLLIDER_SHIELD_1)
	{
		life--;
	}
	if (col_1->type == COLLIDER_ENEMY_SHOT && col_2->type == COLLIDER_SHIELD_1 || col_2->type == COLLIDER_ENEMY_SHOT && col_1->type == COLLIDER_SHIELD_1)
	{
		life--;
	}
}