#ifndef __ENEMY_NINJA_BALL_H__
#define __ENEMY_NINJA_BALL_H__

#include "Enemy.h"

class Enemy_Ninja_Ball : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	Animation spawn;

	uint lastTime = 0, currentTime;

public:

	Enemy_Ninja_Ball(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 50;
};

#endif // __ENEMY_NINJA_BALL_H__