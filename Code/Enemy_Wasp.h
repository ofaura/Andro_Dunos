#ifndef __ENEMY_WASP_H__
#define __ENEMY_WASP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Wasp : public Enemy
{
private:
	int original_y = 0;

	Animation fly;
	Path path;

	uint lastTimeShoot = 0, currentTime;

public:

	Enemy_Wasp(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	int score = 100;
};

#endif // __ENEMY_WASP_H__