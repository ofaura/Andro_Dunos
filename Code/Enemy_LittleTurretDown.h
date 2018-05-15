#ifndef __ENEMY_LITTLETURRETDOWN_H__
#define __ENEMY_LITTLETURRETDOWN_H__

#include "Enemy.h"

class Enemy_LittleTurretDown : public Enemy
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

	float base = 0;		// X distance between player and turret
	float height = 0;	// Y distance between player and turret

	uint lastTime = 0, currentTime;

public:

	Enemy_LittleTurretDown(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	float AngleCalculator();

	bool turretShoot;
	bool dead = false;
	int score = 200;
};

#endif // __ENEMY_LITTLETURRETUP_H__