#ifndef __ENEMY_PIPELINER_H__
 #define __ENEMY_PIPELINER_H__

#include "Enemy.h"

class Enemy_Pipeliner : public Enemy
{
private:
	int original_y = 0;
	
	Animation fly;	
	uint lastTimeShoot = 0, currentTime;
	
public:
	
	Enemy_Pipeliner(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 1000;
};

#endif // __ENEMY_PIPELINER_H__ 