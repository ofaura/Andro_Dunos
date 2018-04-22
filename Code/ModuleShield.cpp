#include <math.h>
#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleShield.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

ModuleShield::ModuleShield() {

}

ModuleShield::~ModuleShield() {}

bool ModuleShield::Start() { 
	//graphics = App->textures->Load("Assets/Sprites/player/shield.png"); //Loads shield image bank


	// ---- Declares initial position, surrounding p1
	position1.x = App->player->position.x + 29; 
	position1.y = App->player->position.y -2;
	position2.x = App->player->position.x + 29;
	position2.y = App->player->position.y + 22;

	// ---- Declares colliders for shield parts individually
	collider1 = App->collision->AddCollider({ position1.x, position1.y, 14, 16 }, COLLIDER_SHIELD_1, this);
	collider2 = App->collision->AddCollider({ position2.x, position2.y, 14, 16 }, COLLIDER_SHIELD_1, this);

	return true; 
}

update_status ModuleShield::Update() { 
	
	// ---- Keeps realtive position to the ship constant
	position1.x = App->player->position.x + 29;
	position1.y = App->player->position.y -8;
	position2.x = App->player->position.x + 29;
	position2.y = App->player->position.y + 10;

	// ---- Updates colliders
	collider1->SetPos(position1.x, position1.y);
	collider2->SetPos(position2.x, position2.y);

	return update_status::UPDATE_CONTINUE; 
}

bool ModuleShield::CleanUp() { 
	
	return true;
}