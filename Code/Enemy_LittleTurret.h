#ifndef __ENEMY_LITTLETURRET_H__
#define __ENEMY_LITTLETURRET_H__

#include "Enemy.h"

class Enemy_LittleTurret : public Enemy
{
private:

	Animation attack;

public:

	Enemy_LittleTurret(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	bool dead = false;
	int score = 200;
};

#endif // __ENEMY_LITTLETURRET_H__