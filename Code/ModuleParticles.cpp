#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Sprites/player/lasers.png");

	// Explosion particle

	laser1.anim.PushBack({ 22, 51, 15, 6 });
	//laser1.anim.PushBack({ 24, 39, 11, 4 });
	laser1.anim.loop = false;
	laser1.anim.speed = 0.1f;
	laser1.speed.x = 7;
	laser1.life = 2000;

	laser2_1.anim.PushBack({ 6, 69, 10, 3 });
	laser2_1.anim.loop = false;
	laser2_1.speed.x = 8;
	laser2_1.life = 2000;

	laser2_2.anim.PushBack({ 6, 84, 10, 3 });
	laser2_2.anim.loop = false;
	laser2_2.speed.x = -8;
	laser2_2.life = 2000;

	laser3.anim.PushBack({ 16, 101, 32, 3 });
	laser3.anim.loop = false;
	laser3.speed.x = 8;
	laser3.life = 2000;

	laser4_1.anim.PushBack({ 41, 11, 13, 1 });
	laser4_1.anim.PushBack({ 41, 11, 13, 2 });
	laser4_1.anim.PushBack({ 41, 23, 13, 6 });
	laser4_1.anim.loop = false;
	laser4_1.speed.x = 8;
	laser4_1.speed.y = 1;
	laser4_1.anim.speed = 0.5f;
	laser4_1.life = 2000;

	laser4_2.anim.PushBack({ 41, 11, 13, 1 });
	laser4_2.anim.PushBack({ 41, 11, 13, 2 });
	laser4_2.anim.PushBack({ 41, 23, 13, 6 });
	laser4_2.anim.loop = false;
	laser4_2.speed.x = 8;
	laser4_2.speed.y = -1;
	laser4_2.anim.speed = 0.5f;
	laser4_2.life = 2000;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
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
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

// Every time a particle hits a wall it triggers an explosion particle
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (c2->type == COLLIDER_WALL) {
				AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			}
			// Always destroy particles that collide
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
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

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}