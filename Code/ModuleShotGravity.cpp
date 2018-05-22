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

#include "SDL/include/SDL_timer.h"


ModuleShotGravity::ModuleShotGravity()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleShotGravity::~ModuleShotGravity()
{}

// Load assets
bool ModuleShotGravity::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Sprites/Particles/particles.png");
	
	gravity_shot.anim.PushBack({ 386, 30, 8, 9 });
	gravity_shot.anim.loop = false;
	gravity_shot.anim.speed = 1.0f;
	gravity_shot.life = 2000;

	return true;
}

// Unload assets
bool ModuleShotGravity::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);


	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleShotGravity::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Accel_Shot* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				//Play your fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleShotGravity::AddShot(const Accel_Shot& particle, int x, int y, Accel_Shot_Type type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Accel_Shot* p = new Accel_Shot(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->type = type;
			// (Module*)App->enemies
			if (type == GRAVITY_SHOT || type == HOMING_MISSILE)
			{
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), COLLIDER_PLAYER_SHOT, this);
			}
			active[i] = p;
			break;
		}
	}
}

// Every time a particle hits a wall it triggers an explosion particle
void ModuleShotGravity::OnCollision(Collider* c1, Collider* c2) // add Collider* c2, if problems arise
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			// Always destroy particles that collide
			delete active[i];
			active[i] = nullptr;
			break;

		}
	}
}


Accel_Shot::Accel_Shot()
{
	position.SetToZero();
}

Accel_Shot::Accel_Shot(const Accel_Shot& p) :
	anim(p.anim), position(p.position),
	fx(p.fx), born(p.born), life(p.life), time(0), time_2(2)
{}

Accel_Shot::~Accel_Shot()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Accel_Shot::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;
	
	//
	if ((1 * time_2)/2 >= 20)
	{
		position.y += 10;
	}
	else
	{
		position.y += 0.5 * (time_2 / 2);
	}

	position.x += 3;


	time++;

	if (time >= 5)
	{
		time_2++;
	}

	if (time >= 500)
	{
		time = 0;
		time_2 = 0;
	}

	//

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
