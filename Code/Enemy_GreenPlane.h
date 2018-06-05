#ifndef __ENEMY_GREENPLANE_H__
#define __ENEMY_GREENPLANE_H__

#include "Enemy.h"

class Enemy_GreenPlane : public Enemy
{
private:
	float wave = -0.5;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;

	Animation fly;
	uint currentTime = 0, lastTimeShoot;

public:

	Enemy_GreenPlane(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	int score = 100;
};

#endif // __ENEMY_GREENPLANE_H__