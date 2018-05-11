#ifndef __ENEMY_LITTLETURRET_H__
#define __ENEMY_LITTLETURRET_H__

#include "Enemy.h"

class Enemy_LittleTurret : public Enemy
{
private:

	Animation attack1;
	Animation attack2;
	Animation attack3;
	Animation attack4;
	Animation attack5;
	Animation attack6;
	Animation attack7;
	Animation attack8;
	Animation attack9;

public:

	Enemy_LittleTurret(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 200;
};

#endif // __ENEMY_LITTLETURRET_H__