#include <math.h>
#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleShotGravity.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

ModuleShotGravity::ModuleShotGravity()
{

	// ---- Animation for the base od the shield
	ani1.PushBack({ 386, 30, 8, 9 });
	ani1.loop = true;
	ani1.speed = 0.2f;
	ani[0] = &ani1;
										
	ani2.PushBack({ 386, 15, 8, 9 });
	ani2.loop = true;
	ani2.speed = 0.2f;
	ani[1] = &ani2;
}

ModuleShotGravity::~ModuleShotGravity() {}

bool ModuleShotGravity::Start() {
	bool ret = true;

	graphics = App->textures->Load("Assets/Sprites/Particles/particle.png"); //Loads shield image bank

	if (graphics == nullptr) ret = false; //failsafe for wrong address
	
	t_g = 0;
	position1.x = App->player->position.x;
	position1.y = App->player->position.y;
	// ---- Declares colliders for shield parts individually
	collider1 = App->collision->AddCollider({ position1.x, position1.y, 14, 16 }, COLLIDER_SHIELD_1, this);
	up = 1;

	return ret;
}

update_status ModuleShotGravity::Update() {

	
	position1.x = position1.x + 2;
	position1.y = position1.y + up * (t_g * 2);


	App->render->Blit(graphics, position1.x, position1.y, &(ani[0]->GetCurrentFrame()));
	collider1->SetPos(position1.x, position1.y);
	t_g++;

	return update_status::UPDATE_CONTINUE;
}

void ModuleShotGravity::OnCollision(Collider* col_1)
{

	if ( col_1->type == COLLIDER_ENEMY)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, position1.x, position1.y);
	}

}

bool ModuleShotGravity::CleanUp() {

	// Remove all memory leaks
	LOG("Unloading shield");
	App->textures->Unload(graphics);

	//Get rid of colliders;
	collider1 = nullptr;

	return true;
}
