#ifndef __ENEMY_METEORITE_H__
#define __ENEMY_METEORITE_H__

#include "Enemy.h"

class Enemy_Meteorite : public Enemy
{
private:
	int original_y = 0;

	Animation destroyed;
	Animation idle;

public:

	Enemy_Meteorite(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 100;
};

#endif // __ENEMY_METEORITE_H__