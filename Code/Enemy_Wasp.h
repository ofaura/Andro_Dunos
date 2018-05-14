#ifndef __ENEMY_WASP_H__
#define __ENEMY_WASP_H__

#include "Enemy.h"

class Enemy_Wasp : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	bool still = false;
	int original_y = 0;
	Animation fly;

	uint lastTimeShoot = 0, currentTime;
	uint lastTimeUp = 0, lastTimeStill = 1000;

public:

	Enemy_Wasp(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 100;
};

#endif // __ENEMY_WASP_H__