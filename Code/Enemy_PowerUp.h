#ifndef __ENEMY_POWERUP_H__
#define __ENEMY_POWERUP_H__

#include "Enemy.h"

class Enemy_PowerUp : public Enemy
{
private:

	int original_y = 0;

	bool CleanUp();

	Animation fly_1, fly_2, fly_3, fly_4, fly_5, fly_6, fly_7, fly_8;
	
	Animation* act[8];

public:
	
	int time = 0, loop = 3;

	Enemy_PowerUp(int x, int y);

	SDL_Texture* graphics = nullptr;

	uint death_sound;

	void Enemy_PowerUp::OnCollision(Collider* collider);
	void Enemy_PowerUp::Draw(SDL_Texture* sprites);

	void Move();
};

#endif // __ENEMY_POWERUP_H__
