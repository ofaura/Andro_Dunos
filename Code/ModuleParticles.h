#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 1000



struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	int damage;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
	bool go;
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* enemy_death = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:

	Particle laser1; // 1
	Particle laser1_2;
	Particle laser1_3;
	Particle laser2_1; // 2
	Particle laser2_2;
	Particle laser2_3a;
	Particle laser2_3b;
	Particle laser2_4a;
	Particle laser2_4b;
	Particle laser2_5;
	Particle laser2_6;
	Particle laser3_1; // 3
	Particle laser3_2;
	Particle laser3_3;
	Particle laser4_1; // 4
	Particle laser4_2;
	Particle laser4_3;

	Particle missile1_1, missile1_2, missile1_3a, missile1_3b;
	Particle missile2_1, missile2_2;

	Particle explosionP1;
	Particle explosionP2;
	Particle enemy_explosion;
	Particle enemy_explosion_alt;
	Particle meteor_explosion;

	Particle enemy_shot_blue;
	Particle enemy_shot_yellow;
	Particle enemy_shot_orange1;
	Particle enemy_shot_orange2;
	Particle enemy_shot_orange3;
	Particle enemy_shot_orange4;
	Particle enemy_shot_orange5;
	Particle enemy_shot_orange6;
	Particle enemy_shot_orange7;
	Particle enemy_shot_orange8;
	Particle enemy_shot_orange9;

	Particle enemy_missile1;
	Particle enemy_missile2;
};

#endif // __MODULEPARTICLES_H__