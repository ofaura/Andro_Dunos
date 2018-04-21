#ifndef __ENEMY_POWERUP_H__
#define __ENEMY_POWERUP_H__

#include "Enemy.h"

class Enemy_PowerUp : public Enemy
{
private:

	int original_y = 0;
	//Animation* fly;
	/*

	*/

	Animation fly_1, fly_2, fly_3, fly_4, fly_5, fly_6, fly_7, fly_8;
	
	Animation* act[8];

public:
	
	int time = 0, loop = 3;
	bool live = true;

	Enemy_PowerUp(int x, int y);

	~Enemy_PowerUp()
	{
		//delete[] act;
	}

	virtual void Enemy_PowerUp::OnCollision(Collider* collider);

	void Move();
};

#endif // __ENEMY_POWERUP_H__
