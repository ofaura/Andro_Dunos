#ifndef __ENEMY_PIPELINER_H__
 #define __ENEMY_PIPELINER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Pipeliner : public Enemy
{
private:
	int original_y = 0;
	
	Animation idleForward;
	Animation idleBackward;
	Path path;
	uint lastTimeShoot = 0, currentTime;
	
public:
	
	Enemy_Pipeliner(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	int score = 1000;
};

#endif // __ENEMY_PIPELINER_H__ 