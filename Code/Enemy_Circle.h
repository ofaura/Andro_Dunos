#ifndef __ENEMY_CIRCLE_H__
#define __ENEMY_CIRCLE_H__

#include "Enemy.h"

class Enemy_Circle : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Circle(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	int score = 200;
};

#endif // __ENEMY_CIRCLE_H__