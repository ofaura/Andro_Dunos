#include "Application.h"
#include "Enemy_SmallSpinner.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "SDL\include\SDL_timer.h"

Enemy_SmallSpinner::Enemy_SmallSpinner(int x, int y) : Enemy(x, y)
{	
	spinning.PushBack({ 150, 455, 16, 16});
	spinning.PushBack({ 179, 455, 16, 16 });
	spinning.PushBack({ 208, 455, 16, 16 });
	spinning.PushBack({ 150, 475, 16, 16 });
	spinning.PushBack({ 179, 475, 16, 16 });
	spinning.PushBack({ 208, 475, 16, 16 });

	spinning.loop = true;
	spinning.speed = 0.5f;


}

void Enemy_SmallSpinner::OnCollision(Collider* collider)
{

}

void Enemy_SmallSpinner::Move()
{

}