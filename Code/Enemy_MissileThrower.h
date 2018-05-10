#ifndef __ENEMY_MISSILETHROWER_H__
#define __ENEMY_MISSILETHROWER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_MissileThrower : public Enemy
{
private:
	Animation fly_left;
	Animation fly_turn;
	Animation fly_right;

	int original_x = 0;
	int original_y = 0;

public:

	Enemy_MissileThrower(int x, int y);

	uint lastTime = 0, currentTime;

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	bool missileFired = false;
	int score = 150;
};

#endif // __ENEMY_MISSILETHROWER_H__
