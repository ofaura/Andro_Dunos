#ifndef __ENEMY_SHOOTER_H__
#define __ENEMY_SHOOTER_H__

#include "Enemy.h"

class Enemy_Shooter : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Shooter(int x, int y);

	void Move();
};

#endif // __ENEMY_FIRSTENEMY_H__

