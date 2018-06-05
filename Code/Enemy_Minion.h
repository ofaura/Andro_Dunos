#ifndef __ENEMY_MINION_H__
#define __ENEMY_MINION_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Minion : public Enemy
{
private:
	int original_y = 0;
	int original_x = 0;

	Animation fly;
	Path path;

public:

	Enemy_Minion(int x, int y);
	virtual void OnCollision(Collider* collider) override;

	void Move();
	int score = 150;
};

#endif // __ENEMY_SPACESHIP_H__