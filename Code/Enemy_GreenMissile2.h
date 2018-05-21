#ifndef __ENEMY_GREENMISSILE2_H__
#define __ENEMY_GREENMISSILE2_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenMissile2 : public Enemy
{
private:
	int original_x = 0;
	int original_y = 0;

	Animation fly;
	Path path;

public:

	Enemy_GreenMissile2(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
};

#endif // __ENEMY_GREENMISSILE2_H__