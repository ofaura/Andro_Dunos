#ifndef __ENEMY_SHOOTER_H__
#define __ENEMY_SHOOTER_H__

#include "Enemy.h"

class Enemy_Shooter : public Enemy
{
private:

	int original_y = 0, time = 0;
	int shot_x, shot_y;
	Animation fly, shot;

public:

	Enemy_Shooter(int x, int y);

	void Move();
	void Draw();
};

#endif // __ENEMY_FIRSTENEMY_H__

