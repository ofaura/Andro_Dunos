#ifndef __ENEMY_SPINNER_DOWN_H__
#define __ENEMY_SPINNER_DOWN_H__

#include "Enemy.h"

class Enemy_Spinner_Down : public Enemy
{
private:
	Animation fly;
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	uint lastTime = 0, currentTime;
	bool curve = false;

public:

	Enemy_Spinner_Down(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 100;
};

#endif // __ENEMY_SPINNER_DOWN_H__