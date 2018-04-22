#ifndef __ENEMY_FIRSTENEMY_H__
#define __ENEMY_FIRSTENEMY_H__

#include "Enemy.h"

class Enemy_FirstEnemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

	bool CleanUp();

public:

	Enemy_FirstEnemy(int x, int y);

	uint death_sound;

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 100;
};

#endif // __ENEMY_FIRSTENEMY_H__