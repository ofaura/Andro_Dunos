#ifndef __ENEMY_SPACESHIP_H__
#define __ENEMY_SPACESHIP_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SpaceShip : public Enemy
{
private:
	int original_y = 0;
	int original_x = 0;

	Animation fly;
	Path path;

public:

	Enemy_SpaceShip(int x, int y);
	virtual void OnCollision(Collider* collider) override;

	uint death_sound;

	void Move();
	int score = 150;
};

#endif // __ENEMY_SPACESHIP_H__