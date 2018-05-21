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
	graphics = App->textures->Load("Assets/Sprites/Particles/particles.png");
	// Explosion particle

	// Enemy shots
	enemy_shot_yellow1.anim.PushBack({ 328, 228, 8, 12 });
	enemy_shot_yellow1.anim.PushBack({ 356, 228, 12, 12 });
	enemy_shot_yellow1.anim.PushBack({ 388, 228, 14, 12 });
	enemy_shot_yellow1.anim.PushBack({ 356, 228, 12, 12 });
	enemy_shot_yellow1.anim.PushBack({ 328, 228, 8, 12 });
	enemy_shot_yellow1.anim.PushBack({ 302, 228, 6, 12 });
	enemy_shot_yellow1.anim.PushBack({ 266, 228, 16, 12 });
	enemy_shot_yellow1.anim.loop = false;
	enemy_shot_yellow1.anim.speed = 1.0f;
	enemy_shot_yellow1.speed.x -= 5;
	enemy_shot_yellow1.life = 2000;	

	enemy_shot_yellow2.anim.PushBack({ 328, 228, 8, 12 });
	enemy_shot_yellow2.anim.PushBack({ 356, 228, 12, 12 });
	enemy_shot_yellow2.anim.PushBack({ 408, 228, 14, 12 });
	enemy_shot_yellow2.anim.PushBack({ 356, 228, 12, 12 });
	enemy_shot_yellow2.anim.PushBack({ 328, 228, 8, 12 });
	enemy_shot_yellow2.anim.PushBack({ 302, 228, 6, 12 });
	enemy_shot_yellow2.anim.PushBack({ 266, 228, 16, 12 });
	enemy_shot_yellow2.anim.loop = false;
	enemy_shot_yellow2.anim.speed = 1.0f;
	enemy_shot_yellow2.speed.x += 6;
	enemy_shot_yellow2.life = 2000;

	enemy_shot_blue1.anim.PushBack({ 9, 115, 6, 8 });
	enemy_shot_blue1.anim.PushBack({ 19, 116, 6, 6 });
	enemy_shot_blue1.anim.PushBack({ 29, 116, 8, 6 });
	enemy_shot_blue1.anim.PushBack({ 41, 116, 6, 6 });
	enemy_shot_blue1.anim.loop = true;
	enemy_shot_blue1.anim.speed = 0.2f;
	enemy_shot_blue1.speed.x -= 2;
	enemy_shot_blue1.speed.y -= 1;
	enemy_shot_blue1.life = 2000;

	enemy_shot_blue2.anim.PushBack({ 9, 115, 6, 8 });
	enemy_shot_blue2.anim.PushBack({ 19, 116, 6, 6 });
	enemy_shot_blue2.anim.PushBack({ 29, 116, 8, 6 });
	enemy_shot_blue2.anim.PushBack({ 41, 116, 6, 6 });
	enemy_shot_blue2.anim.loop = true;
	enemy_shot_blue2.anim.speed = 0.2f;
	enemy_shot_blue2.speed.x -= 2;
	enemy_shot_blue2.life = 2000;

	enemy_shot_blue3.anim.PushBack({ 9, 115, 6, 8 });
	enemy_shot_blue3.anim.PushBack({ 19, 116, 6, 6 });
	enemy_shot_blue3.anim.PushBack({ 29, 116, 8, 6 });
	enemy_shot_blue3.anim.PushBack({ 41, 116, 6, 6 });
	enemy_shot_blue3.anim.loop = true;
	enemy_shot_blue3.anim.speed = 0.2f;
	enemy_shot_blue3.speed.x -= 2;
	enemy_shot_blue3.speed.y += 1;
	enemy_shot_blue3.life = 2000;

	enemy_shot_blue4.anim.PushBack({ 9, 115, 6, 8 });
	enemy_shot_blue4.anim.PushBack({ 19, 116, 6, 6 });
	enemy_shot_blue4.anim.PushBack({ 29, 116, 8, 6 });
	enemy_shot_blue4.anim.PushBack({ 41, 116, 6, 6 });
	enemy_shot_blue4.anim.loop = true;
	enemy_shot_blue4.anim.speed = 0.2f;
	enemy_shot_blue4.speed.x += 3;
	enemy_shot_blue4.speed.y -= 1;
	enemy_shot_blue4.life = 2000;

	enemy_shot_blue5.anim.PushBack({ 9, 115, 6, 8 });
	enemy_shot_blue5.anim.PushBack({ 19, 116, 6, 6 });
	enemy_shot_blue5.anim.PushBack({ 29, 116, 8, 6 });
	enemy_shot_blue5.anim.PushBack({ 41, 116, 6, 6 });
	enemy_shot_blue5.anim.loop = true;
	enemy_shot_blue5.anim.speed = 0.2f;
	enemy_shot_blue5.speed.x += 3;
	enemy_shot_blue5.life = 2000;

	enemy_shot_blue6.anim.PushBack({ 9, 115, 6, 8 });
	enemy_shot_blue6.anim.PushBack({ 19, 116, 6, 6 });
	enemy_shot_blue6.anim.PushBack({ 29, 116, 8, 6 });
	enemy_shot_blue6.anim.PushBack({ 41, 116, 6, 6 });
	enemy_shot_blue6.anim.loop = true;
	enemy_shot_blue6.anim.speed = 0.2f;
	enemy_shot_blue6.speed.x += 3;
	enemy_shot_blue6.speed.y += 1;
	enemy_shot_blue6.life = 2000;
	
	enemy_shot_orange1u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange1u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange1u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange1u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange1u.anim.loop = true;
	enemy_shot_orange1u.anim.speed = 0.5f;
	enemy_shot_orange1u.speed.x -= 2;
	enemy_shot_orange1u.life = 2000;

	enemy_shot_orange2u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange2u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange2u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange2u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange2u.anim.loop = true;
	enemy_shot_orange2u.anim.speed = 0.5f;
	enemy_shot_orange2u.speed.x -= 2;
	enemy_shot_orange2u.speed.y += 1;
	enemy_shot_orange2u.life = 2000;

	enemy_shot_orange3u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange3u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange3u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange3u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange3u.anim.loop = true;
	enemy_shot_orange3u.anim.speed = 0.5f;
	enemy_shot_orange3u.speed.x -= 2;
	enemy_shot_orange3u.speed.y += 2;
	enemy_shot_orange3u.life = 2000;

	enemy_shot_orange4u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange4u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange4u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange4u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange4u.anim.loop = true;
	enemy_shot_orange4u.anim.speed = 0.5f;
	enemy_shot_orange4u.speed.x -= 1;
	enemy_shot_orange4u.speed.y += 2;
	enemy_shot_orange4u.life = 2000;

	enemy_shot_orange5u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange5u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange5u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange5u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange5u.anim.loop = true;
	enemy_shot_orange5u.anim.speed = 0.5f;
	enemy_shot_orange5u.speed.y += 2;
	enemy_shot_orange5u.life = 2000;

	enemy_shot_orange6u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange6u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange6u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange6u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange6u.anim.loop = true;
	enemy_shot_orange6u.anim.speed = 0.5f;
	enemy_shot_orange6u.speed.x += 1;
	enemy_shot_orange6u.speed.y += 2;
	enemy_shot_orange6u.life = 2000;

	enemy_shot_orange7u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange7u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange7u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange7u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange7u.anim.loop = true;
	enemy_shot_orange7u.anim.speed = 0.5f;
	enemy_shot_orange7u.speed.x += 2;
	enemy_shot_orange7u.speed.y += 2;
	enemy_shot_orange7u.life = 2000;

	enemy_shot_orange8u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange8u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange8u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange8u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange8u.anim.loop = true;
	enemy_shot_orange8u.anim.speed = 0.5f;
	enemy_shot_orange8u.speed.x += 2;
	enemy_shot_orange8u.speed.y += 1;
	enemy_shot_orange8u.life = 2000;

	enemy_shot_orange9u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange9u.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange9u.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange9u.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange9u.anim.loop = true;
	enemy_shot_orange9u.anim.speed = 0.5f;
	enemy_shot_orange9u.speed.x += 2;
	enemy_shot_orange9u.life = 2000;

	//-----------------------------------------------------------------------------

	enemy_shot_orange1d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange1d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange1d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange1d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange1d.anim.loop = true;
	enemy_shot_orange1d.anim.speed = 0.5f;
	enemy_shot_orange1d.speed.x -= 2;
	enemy_shot_orange1d.life = 2000;

	enemy_shot_orange2d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange2d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange2d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange2d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange2d.anim.loop = true;
	enemy_shot_orange2d.anim.speed = 0.5f;
	enemy_shot_orange2d.speed.x -= 2;
	enemy_shot_orange2d.speed.y -= 1;
	enemy_shot_orange2d.life = 2000;

	enemy_shot_orange3d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange3d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange3d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange3d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange3d.anim.loop = true;
	enemy_shot_orange3d.anim.speed = 0.5f;
	enemy_shot_orange3d.speed.x -= 2;
	enemy_shot_orange3d.speed.y -= 2;
	enemy_shot_orange3d.life = 2000;

	enemy_shot_orange4d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange4d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange4d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange4d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange4d.anim.loop = true;
	enemy_shot_orange4d.anim.speed = 0.5f;
	enemy_shot_orange4d.speed.x -= 1;
	enemy_shot_orange4d.speed.y -= 2;
	enemy_shot_orange4d.life = 2000;

	enemy_shot_orange5d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange5d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange5d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange5d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange5d.anim.loop = true;
	enemy_shot_orange5d.anim.speed = 0.5f;
	enemy_shot_orange5d.speed.y -= 2;
	enemy_shot_orange5d.life = 2000;

	enemy_shot_orange6d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange6d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange6d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange6d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange6d.anim.loop = true;
	enemy_shot_orange6d.anim.speed = 0.5f;
	enemy_shot_orange6d.speed.x += 1;
	enemy_shot_orange6d.speed.y -= 2;
	enemy_shot_orange6d.life = 2000;

	enemy_shot_orange7d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange7d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange7d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange7d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange7d.anim.loop = true;
	enemy_shot_orange7d.anim.speed = 0.5f;
	enemy_shot_orange7d.speed.x += 2;
	enemy_shot_orange7d.speed.y -= 2;
	enemy_shot_orange7d.life = 2000;

	enemy_shot_orange8d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange8d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange8d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange8d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange8d.anim.loop = true;
	enemy_shot_orange8d.anim.speed = 0.5f;
	enemy_shot_orange8d.speed.x += 2;
	enemy_shot_orange8d.speed.y -= 1;
	enemy_shot_orange8d.life = 2000;

	enemy_shot_orange9d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange9d.anim.PushBack({ 288, 220, 6, 6 });
	enemy_shot_orange9d.anim.PushBack({ 280, 220, 6, 6 });
	enemy_shot_orange9d.anim.PushBack({ 296, 220, 6, 6 });
	enemy_shot_orange9d.anim.loop = true;
	enemy_shot_orange9d.anim.speed = 0.5f;
	enemy_shot_orange9d.speed.x += 2;
	enemy_shot_orange9d.life = 2000;

	// Enemy missiles
	enemy_missile1.anim.PushBack({ 264, 188, 15, 10 });
	enemy_missile1.anim.PushBack({ 284, 188, 20, 10 });
	enemy_missile1.anim.PushBack({ 308, 188, 31, 10 });
	enemy_missile1.anim.loop = true;
	enemy_missile1.anim.speed = 0.2f;
	enemy_missile1.speed.x -= 2;
	enemy_missile1.life = 2000;

	enemy_missile2.anim.PushBack({ 267, 200, 11, 12 });
	enemy_missile2.anim.PushBack({ 282, 200, 13, 12 });
	enemy_missile2.anim.PushBack({ 298, 200, 16, 12 });
	enemy_missile2.anim.loop = true;
	enemy_missile2.anim.speed = 0.2f;
	enemy_missile2.speed.x -= 2;
	enemy_missile2.life = 2000;

	// Player main weapon
	laser1.anim.PushBack({ 24, 39, 11, 4 });
	laser1.anim.loop = false;
	laser1.anim.speed = 0.1f;
	laser1.speed.x = 7;
	laser1.life = 2000;

	laser1_2.anim.PushBack({ 22, 51, 15, 6 });
	laser1_2.anim.loop = false;
	laser1_2.anim.speed = 0.1f;
	laser1_2.speed.x = 7;
	laser1_2.life = 2000;

	laser1_3.anim.PushBack({ 21, 6, 16, 10 });
	laser1_3.anim.loop = false;
	laser1_3.anim.speed = 0.1f;
	laser1_3.speed.x = 7;
	laser1_3.life = 2000;
	

	laser2_1.anim.PushBack({ 6, 69, 10, 3 });
	laser2_1.anim.loop = false;
	laser2_1.speed.x = 8;
	laser2_1.life = 2000;

	laser2_2.anim.PushBack({ 6, 84, 10, 3 });
	laser2_2.anim.loop = false;
	laser2_2.speed.x = -8;
	laser2_2.life = 2000;

	laser2_3a.anim.PushBack({ 23, 69, 10, 8 });
	laser2_3a.anim.loop = false;
	laser2_3a.speed.x = -8;
	laser2_3a.speed.y = 5;
	laser2_3a.life = 2000;

	laser2_3b.anim.PushBack({ 23, 78, 10, 8 });
	laser2_3b.anim.loop = false;
	laser2_3b.speed.x = -8;
	laser2_3b.speed.y = -5;
	laser2_3b.life = 2000;
	
	laser2_4a.anim.PushBack({ 5, 37, 11, 8 });
	laser2_4a.anim.loop = false;
	laser2_4a.speed.x = -8;
	laser2_4a.speed.y = 5;
	laser2_4a.life = 2000;

	laser2_4b.anim.PushBack({ 5, 50, 11, 8 });
	laser2_4b.anim.loop = false;
	laser2_4b.speed.x = -8;
	laser2_4b.speed.y = -5;
	laser2_4b.life = 2000;

	laser2_5.anim.PushBack({ 3, 23, 15, 5 });
	laser2_5.anim.loop = false;
	laser2_5.speed.x = -8;
	laser2_5.life = 2000;

	laser2_6.anim.PushBack({ 3, 8, 15, 5 });
	laser2_6.anim.loop = false;
	laser2_6.speed.x = 8;
	laser2_6.life = 2000;
	//
	laser3[0].anim.PushBack({ 16, 101, 32, 3 });
	laser3[0].anim.loop = false;
	laser3[0].speed.x = 8;
	laser3[0].life = 2000;
	
	laser3[1].anim.PushBack({ 57, 35, 16, 18 });
	laser3[1].anim.loop = false;
	laser3[1].speed.x = 7;
	laser3[1].speed.y = -6;
	laser3[1].life = 2000;

	laser3[2].anim.PushBack({ 57, 60, 16, 18 });
	laser3[2].anim.loop = false;
	laser3[2].speed.x = 7;
	laser3[2].speed.y = 6;
	laser3[2].life = 2000;

	laser3[3].anim.PushBack({ 463, 49, 16, 18 });
	laser3[3].anim.loop = false;
	laser3[3].speed.x = -5;
	laser3[3].speed.y = -6;
	laser3[3].life = 2000;

	laser3[4].anim.PushBack({ 463, 74, 16, 18 });
	laser3[4].anim.loop = false;
	laser3[4].speed.x = -5;
	laser3[4].speed.y = 6;
	laser3[4].life = 2000;
	//
	laser3[5].anim.PushBack({ 76, 2, 16, 22 });
	laser3[5].anim.loop = false;
	laser3[5].speed.x = 7;
	laser3[5].speed.y = -6;
	laser3[5].life = 2000;

	laser3[6].anim.PushBack({ 76, 32, 16, 22 });
	laser3[6].anim.loop = false;
	laser3[6].speed.x = 7;
	laser3[6].speed.y = 6;
	laser3[6].life = 2000;

	laser3[7].anim.PushBack({ 444, 10, 16, 22 });
	laser3[7].anim.loop = false;
	laser3[7].speed.x = -5;
	laser3[7].speed.y = -6;
	laser3[7].life = 2000;

	laser3[8].anim.PushBack({ 444, 40, 16, 22 });
	laser3[8].anim.loop = false;
	laser3[8].speed.x = -5;
	laser3[8].speed.y = 6;
	laser3[8].life = 2000;
	//
	laser3[9].anim.PushBack({ 94, 0, 31, 31 });
	laser3[9].anim.loop = false;
	laser3[9].speed.x = 7;
	laser3[9].speed.y = -6;
	laser3[9].life = 2000;

	laser3[10].anim.PushBack({ 94, 32, 31, 31 });
	laser3[10].anim.loop = false;
	laser3[10].speed.x = 7;
	laser3[10].speed.y = 6;
	laser3[10].life = 2000;

	laser3[11].anim.PushBack({ 411, 0, 31, 31 });
	laser3[11].anim.loop = false;
	laser3[11].speed.x = -5;
	laser3[11].speed.y = -6;
	laser3[11].life = 2000;

	laser3[12].anim.PushBack({ 411, 32, 31, 31 });
	laser3[12].anim.loop = false;
	laser3[12].speed.x = -5;
	laser3[12].speed.y = 6;
	laser3[12].life = 2000;
	//

	laser3[16].life = 2000;

	laser4[0].anim.PushBack({ 41, 11, 13, 1 });
	laser4[0].anim.PushBack({ 41, 11, 13, 2 });
	laser4[0].anim.PushBack({ 41, 23, 13, 6 });
	laser4[0].anim.loop = false;
	laser4[0].speed.x = 8;
	laser4[0].anim.speed = 0.75f;
	laser4[0].life = 2000;

	laser4[1].anim.PushBack({ 41, 11, 13, 1 });
	laser4[1].anim.PushBack({ 41, 23, 13, 6 });
	laser4[1].anim.loop = false;
	laser4[1].speed.x = 8;
	laser4[1].speed.y = 1;
	laser4[1].anim.speed = 0.75f;
	laser4[1].life = 2000;

	laser4[2].anim.PushBack({ 41, 11, 13, 1 });
	laser4[2].anim.PushBack({ 41, 11, 13, 2 });
	laser4[2].anim.PushBack({ 41, 23, 13, 6 });
	laser4[2].anim.loop = false;
	laser4[2].speed.x = 8;
	laser4[2].speed.y = -1;
	laser4[2].anim.speed = 0.75f;
	laser4[2].life = 2000;

	laser4[3].anim.PushBack({ 41, 11, 13, 1 });
	laser4[3].anim.PushBack({ 41, 11, 13, 2 });
	laser4[3].anim.PushBack({ 41, 23, 13, 6 });
	laser4[3].anim.PushBack({ 41, 38, 13, 8 });
	laser4[3].anim.loop = false;
	laser4[3].speed.x = 8;
	laser4[3].anim.speed = 0.75f;
	laser4[3].life = 2000;

	laser4[4].anim.PushBack({ 41, 11, 13, 1 });
	laser4[4].anim.PushBack({ 41, 23, 13, 6 });
	laser4[4].anim.PushBack({ 41, 38, 13, 8 });
	laser4[4].anim.loop = false;
	laser4[4].speed.x = 8;
	laser4[4].speed.y = 1;
	laser4[4].anim.speed = 0.75f;
	laser4[4].life = 2000;

	laser4[5].anim.PushBack({ 41, 11, 13, 1 });
	laser4[5].anim.PushBack({ 41, 11, 13, 2 });
	laser4[5].anim.PushBack({ 41, 23, 13, 6 });
	laser4[5].anim.PushBack({ 41, 38, 13, 8 });
	laser4[5].anim.loop = false;
	laser4[5].speed.x = 8;
	laser4[5].speed.y = -1;
	laser4[5].anim.speed = 0.75f;
	laser4[5].life = 2000;

	laser4[6].anim.PushBack({ 41, 11, 13, 1 });
	laser4[6].anim.PushBack({ 41, 23, 13, 6 });
	laser4[6].anim.PushBack({ 41, 38, 13, 8 });
	laser4[6].anim.loop = false;
	laser4[6].speed.x = 8;
	laser4[6].speed.y = 2;
	laser4[6].anim.speed = 0.75f;
	laser4[6].life = 2000;

	laser4[7].anim.PushBack({ 41, 11, 13, 1 });
	laser4[7].anim.PushBack({ 41, 11, 13, 2 });
	laser4[7].anim.PushBack({ 41, 23, 13, 6 });
	laser4[7].anim.PushBack({ 41, 38, 13, 8 });
	laser4[7].anim.loop = false;
	laser4[7].speed.x = 8;
	laser4[7].speed.y = -2;
	laser4[7].anim.speed = 0.75f;
	laser4[7].life = 2000;

	laser4[8].anim.PushBack({ 41, 11, 13, 1 });
	laser4[8].anim.PushBack({ 41, 23, 13, 6 });
	laser4[8].anim.PushBack({ 41, 23, 13, 6 });
	laser4[8].anim.PushBack({ 41, 23, 13, 6 });
	laser4[8].anim.PushBack({ 41, 38, 13, 8 });
	laser4[8].anim.PushBack({ 41, 38, 13, 8 });
	laser4[8].anim.PushBack({ 41, 38, 13, 8 });
	laser4[8].anim.PushBack({ 41, 49, 13, 12 });
	laser4[8].anim.PushBack({ 41, 49, 13, 12 });
	laser4[8].anim.PushBack({ 41, 49, 13, 12 });
	laser4[8].anim.PushBack({ 41, 49, 13, 12 });
	laser4[8].anim.PushBack({ 41, 64, 13, 14 });
	laser4[8].anim.loop = false;
	laser4[8].speed.x = 8;
	laser4[8].speed.y = 1;
	laser4[8].anim.speed = 0.75f;
	laser4[8].life = 2000;

	laser4[9].anim.PushBack({ 41, 11, 13, 1 });
	laser4[9].anim.PushBack({ 41, 23, 13, 6 });
	laser4[9].anim.PushBack({ 41, 23, 13, 6 });
	laser4[9].anim.PushBack({ 41, 23, 13, 6 });
	laser4[9].anim.PushBack({ 41, 38, 13, 8 });
	laser4[9].anim.PushBack({ 41, 38, 13, 8 });
	laser4[9].anim.PushBack({ 41, 38, 13, 8 });
	laser4[9].anim.PushBack({ 41, 49, 13, 12 });
	laser4[9].anim.PushBack({ 41, 49, 13, 12 });
	laser4[9].anim.PushBack({ 41, 49, 13, 12 });
	laser4[9].anim.PushBack({ 41, 49, 13, 12 });
	laser4[9].anim.PushBack({ 41, 64, 13, 14 });
	laser4[9].anim.loop = false;
	laser4[9].speed.x = 8;
	laser4[9].speed.y = -1;
	laser4[9].anim.speed = 0.75f;
	laser4[9].life = 2000;

	laser4[10].anim.PushBack({ 41, 11, 13, 1 });
	laser4[10].anim.PushBack({ 41, 23, 13, 6 });
	laser4[10].anim.PushBack({ 41, 23, 13, 6 });
	laser4[10].anim.PushBack({ 41, 23, 13, 6 });
	laser4[10].anim.PushBack({ 41, 38, 13, 8 });
	laser4[10].anim.PushBack({ 41, 38, 13, 8 });
	laser4[10].anim.PushBack({ 41, 38, 13, 8 });
	laser4[10].anim.PushBack({ 41, 49, 13, 12 });
	laser4[10].anim.PushBack({ 41, 49, 13, 12 });
	laser4[10].anim.PushBack({ 41, 49, 13, 12 });
	laser4[10].anim.PushBack({ 41, 49, 13, 12 });
	laser4[10].anim.PushBack({ 41, 64, 13, 14 });
	laser4[10].anim.loop = false;
	laser4[10].speed.x = 8;
	laser4[10].anim.speed = 0.75f;
	laser4[10].life = 2000;

	laser4[11].anim.PushBack({ 41, 11, 13, 1 });
	laser4[11].anim.PushBack({ 41, 23, 13, 6 });
	laser4[11].anim.PushBack({ 41, 23, 13, 6 });
	laser4[11].anim.PushBack({ 41, 23, 13, 6 });
	laser4[11].anim.PushBack({ 41, 38, 13, 8 });
	laser4[11].anim.PushBack({ 41, 38, 13, 8 });
	laser4[11].anim.PushBack({ 41, 38, 13, 8 });
	laser4[11].anim.PushBack({ 41, 49, 13, 12 });
	laser4[11].anim.PushBack({ 41, 49, 13, 12 });
	laser4[11].anim.PushBack({ 41, 49, 13, 12 });
	laser4[11].anim.PushBack({ 41, 49, 13, 12 });
	laser4[11].anim.PushBack({ 41, 64, 13, 14 });
	laser4[11].anim.loop = false;
	laser4[11].speed.x = 8;
	laser4[11].speed.y = 2;
	laser4[11].anim.speed = 0.75f;
	laser4[11].life = 2000;

	laser4[12].anim.PushBack({ 41, 11, 13, 1 });
	laser4[12].anim.PushBack({ 41, 23, 13, 6 });
	laser4[12].anim.PushBack({ 41, 23, 13, 6 });
	laser4[12].anim.PushBack({ 41, 23, 13, 6 });
	laser4[12].anim.PushBack({ 41, 38, 13, 8 });
	laser4[12].anim.PushBack({ 41, 38, 13, 8 });
	laser4[12].anim.PushBack({ 41, 38, 13, 8 });
	laser4[12].anim.PushBack({ 41, 49, 13, 12 });
	laser4[12].anim.PushBack({ 41, 49, 13, 12 });
	laser4[12].anim.PushBack({ 41, 49, 13, 12 });
	laser4[12].anim.PushBack({ 41, 49, 13, 12 });
	laser4[12].anim.PushBack({ 41, 64, 13, 14 });
	laser4[12].anim.loop = false;
	laser4[12].speed.x = 8;
	laser4[12].speed.y = -2;
	laser4[12].anim.speed = 0.75f;
	laser4[12].life = 2000;


	//PLayer scond weapon	

	missile1_1.anim.PushBack({ 297, 105, 12, 9 }); //
	missile1_1.anim.loop = true; // false;
	missile1_1.speed.x = 4;//1;
	missile1_1.speed.y = 2;//0;
	missile1_1.anim.speed = 0.1f;
	missile1_1.life = 2000;

	missile1_2.anim.PushBack({ 297, 90, 12, 8 });
	missile1_2.anim.loop = true;
	missile1_2.speed.x = 4;
	missile1_2.speed.y = -2;
	missile1_2.anim.speed = 0.3f;
	missile1_2.life = 2000;

	missile1_3a.anim.PushBack({ 296, 131, 10, 10 });
	//missile1_3a.anim.PushBack({ 297, 16, 12, 8 });
	missile1_3a.anim.loop = true;
	missile1_3a.speed.x = 2;
	missile1_3a.speed.y = 2;
	missile1_3a.anim.speed = 0.3f;
	missile1_3a.life = 2000;

	//missile1_3b.anim.PushBack({ 297, 75, 12, 8 });
	missile1_3b.anim.PushBack({ 297, 146, 10, 10 });
	missile1_3b.anim.loop = true;
	missile1_3b.speed.x = 2;
	missile1_3b.speed.y = -2;
	missile1_3b.anim.speed = 0.3f;
	missile1_3b.life = 2000;
	//
	
	missile2_1.anim.PushBack({ 268, 59, 12, 9 });
	missile2_1.anim.PushBack({ 268, 46, 12, 9 });
	missile2_1.anim.loop = true;
	missile2_1.speed.x = 1;
	missile2_1.speed.y = 2;
	missile2_1.anim.speed = 0.15f;
	missile2_1.life = 2000;

	missile2_2.anim.PushBack({ 268, 59, 12, 9 });
	missile2_2.anim.PushBack({ 268, 46, 12, 9 });
	missile2_2.anim.loop = true;
	missile2_2.speed.x = 1;
	missile2_2.speed.y = -2;
	missile2_2.anim.speed = 0.15f;
	missile2_2.life = 2000;

	missile2_3.anim.PushBack({ 268, 59, 12, 9 });
	missile2_3.anim.PushBack({ 268, 46, 12, 9 });
	missile2_3.anim.loop = true;
	missile2_3.speed.x = 2;
	missile2_3.speed.y = 2;
	missile2_3.anim.speed = 0.15f;
	missile2_3.life = 2000;

	missile2_4.anim.PushBack({ 268, 59, 12, 9 });
	missile2_4.anim.PushBack({ 268, 46, 12, 9 });
	missile2_4.anim.loop = true;
	missile2_4.speed.x = 2;
	missile2_4.speed.y = -2;
	missile2_4.anim.speed = 0.15f;
	missile2_4.life = 2000;
	

	// Player 1 death
	explosionP1.anim.PushBack({ 11, 146, 27, 17});
	explosionP1.anim.PushBack({ 48, 145, 28, 18 });
	explosionP1.anim.PushBack({ 86, 142, 30, 21 });
	explosionP1.anim.PushBack({ 126, 138, 31, 26 });
	explosionP1.anim.PushBack({ 168, 137, 32, 26 });
	explosionP1.anim.PushBack({ 210, 135, 32, 31 });
	explosionP1.anim.PushBack({ 11, 180, 32, 32 });
	explosionP1.anim.PushBack({ 55, 179, 30, 30 });
	explosionP1.anim.PushBack({ 97, 189, 28, 20 });
	explosionP1.anim.PushBack({ 137, 194, 24, 15 });
	explosionP1.anim.PushBack({ 198, 173, 19, 11 });
	explosionP1.anim.PushBack({ 204, 200, 9, 32 });
	explosionP1.anim.PushBack({ 15, 228, 17, 13 });
	explosionP1.anim.PushBack({ 44, 226, 15, 15 });
	explosionP1.anim.PushBack({ 80, 233, 7, 3 });
	explosionP1.anim.PushBack({ 140, 235, 2, 1 });
	explosionP1.anim.loop = false;
	explosionP1.anim.speed = 0.3f;
	explosionP1.life = 500;

	// Player 2 death
	explosionP2.anim.PushBack({ 137, 18, 27, 17 });
	explosionP2.anim.PushBack({ 174, 17, 28, 18 });
	explosionP2.anim.PushBack({ 212, 14, 30, 21 });
	explosionP2.anim.PushBack({ 140, 44, 31, 26 });
	explosionP2.anim.PushBack({ 183, 45, 32, 26 });
	explosionP2.anim.PushBack({ 139, 83, 32, 31 });
	explosionP2.anim.PushBack({ 181, 83, 32, 32 });
	explosionP2.anim.PushBack({ 55, 179, 30, 30 });
	explosionP2.anim.PushBack({ 97, 189, 28, 20 });
	explosionP2.anim.PushBack({ 137, 194, 24, 15 });
	explosionP2.anim.PushBack({ 198, 173, 19, 11 });
	explosionP2.anim.PushBack({ 204, 200, 9, 32 });
	explosionP2.anim.PushBack({ 15, 228, 17, 13 });
	explosionP2.anim.PushBack({ 44, 226, 15, 15 });
	explosionP2.anim.PushBack({ 80, 233, 7, 3 });
	explosionP2.anim.PushBack({ 140, 235, 2, 1 });
	explosionP2.anim.loop = false;
	explosionP2.anim.speed = 0.3f;
	explosionP2.life = 500;

	// Enemy death
	enemy_explosion.anim.PushBack({ 130, 270, 4, 4 });
	enemy_explosion.anim.PushBack({ 137, 262, 12, 12 });
	enemy_explosion.anim.PushBack({ 153, 242, 32, 32 });
	enemy_explosion.anim.PushBack({ 188, 243, 30, 30 });
	enemy_explosion.anim.PushBack({ 222, 244, 30, 30 });
	enemy_explosion.anim.PushBack({ 143, 282, 30, 30 });
	enemy_explosion.anim.PushBack({ 177, 283, 30, 30 });
	enemy_explosion.anim.PushBack({ 212, 281, 32, 32 });
	enemy_explosion.anim.PushBack({ 149, 318, 32, 32 });
	enemy_explosion.anim.PushBack({ 196, 318, 32, 23 });

	enemy_explosion.anim.loop = false;
	enemy_explosion.anim.speed = 0.3f;
	enemy_explosion.life = 500;

	enemy_explosion_alt.anim.PushBack({ 7, 262, 8, 8 });
	enemy_explosion_alt.anim.PushBack({ 17, 258, 13, 14 });
	enemy_explosion_alt.anim.PushBack({ 33, 247, 25, 25 });
	enemy_explosion_alt.anim.PushBack({ 63, 246, 27, 26 });
	enemy_explosion_alt.anim.PushBack({ 93, 243, 30, 29 });
	enemy_explosion_alt.anim.PushBack({ 7, 279, 29, 28 });
	enemy_explosion_alt.anim.PushBack({ 40, 278, 29, 28 });
	enemy_explosion_alt.anim.PushBack({ 73, 279, 28, 28 });
	enemy_explosion_alt.anim.PushBack({ 103, 279, 29, 28 });
	enemy_explosion_alt.anim.PushBack({ 7, 314, 29, 28 });
	enemy_explosion_alt.anim.PushBack({ 40, 314, 28, 28 });
	enemy_explosion_alt.anim.PushBack({ 73, 314, 26, 28});
	enemy_explosion_alt.anim.PushBack({ 103, 314, 21, 28});
	enemy_explosion_alt.anim.PushBack({ 7, 347, 17, 27});
	enemy_explosion_alt.anim.PushBack({ 40, 347, 6, 10});

	enemy_explosion_alt.anim.loop = false;
	enemy_explosion_alt.anim.speed = 0.3f;
	enemy_explosion_alt.life = 500;

	// ---- Meteor Death Animation
	meteor_explosion.anim.PushBack({ 275, 325, 25, 43});
	meteor_explosion.anim.PushBack({ 300, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 325, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 350, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 375, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 400, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 425, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 450, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 475, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 500, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 525, 325, 25, 43 });
	meteor_explosion.anim.PushBack({ 550, 325, 25, 43 });

	meteor_explosion.anim.loop = false;
	meteor_explosion.anim.speed = 0.3f;
	meteor_explosion.life = 500;



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
void ModuleParticles::OnCollision(Collider* c1, Collider* c2) // add Collider* c2, if problems arise
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


	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}