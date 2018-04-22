#ifndef __ENEMY_SHOOTER_H__
#define __ENEMY_SHOOTER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Shooter : public Enemy
{
private:
	Animation fly;
	Path path;

	iPoint original_pos;

public:

	Enemy_Shooter(int x, int y);
	void Move();
	uint lastTime = 0, currentTime;
};

#endif // __ENEMY_FIRSTENEMY_H__

