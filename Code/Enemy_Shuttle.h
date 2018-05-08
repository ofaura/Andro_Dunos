#ifndef __ENEMY_SHUTTLE_H__
#define __ENEMY_SHUTTLE_H__

#include "Enemy.h"

class Enemy_Shuttle : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Shuttle(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 200;

};

#endif // __ENEMY_SHUTTLE_H__