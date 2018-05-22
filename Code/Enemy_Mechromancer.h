#ifndef __ENEMY_MECRHOMANCER_H__
#define __ENEMY_MECHORMANCER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Mechromancer : public Enemy
{
private:
	int original_x = 0;
	int original_y = 0;

	Animation fly;
	Path path;

	uint lastTimeShoot = 0, currentTime;

public:

	Enemy_Mechromancer(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	bool pathCreated = false;
	uint shots = 0;
	int score = 200;
};

#endif // __ENEMY_MECHROMANCER_H__