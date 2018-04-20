#ifndef __ENEMY_POWERUP_H__
#define __ENEMY_POWERUP_H__

#include "Enemy.h"

class Enemy_PowerUp : public Enemy
{
private:

	int original_y = 0;
	//Animation* fly;
	/*

	*/

	Animation fly_1;
	Animation fly_2;
	Animation fly_3;
	Animation fly_4;
	Animation fly_5;
	Animation fly_6;
	Animation fly_7;
	Animation fly_8;
	
	Animation* act[8];
	
	int time = 0, loop = 3;

public:

	SDL_Rect size = { 0,0,26,26 };
	Enemy_PowerUp(int x, int y);
	~Enemy_PowerUp()
	{
		//delete[] fly;
	}

	void Move();
};

#endif // __ENEMY_SPACESHIP_H__
