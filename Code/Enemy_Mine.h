#ifndef __ENEMY_MINE_H__
#define __ENEMY_MINE_H__

#include "Enemy.h"

class Enemy_Mine : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;

	int original_y = 0;
	int original_x = 0;

	Animation blink;

	int current_y = 0;
	bool change_direction = false;

public:

	Enemy_Mine(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 150;
	int random;

};

#endif // __ENEMY_MINE_H__