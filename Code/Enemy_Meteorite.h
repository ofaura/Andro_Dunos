#ifndef __ENEMY_METEORITE_H__
#define __ENEMY_METEORITE_H__

#include "Enemy.h"

class Enemy_Meteorite : public Enemy
{
private:
	int original_y = 0;

	Animation idle1;
	Animation idle2;
	Animation idle3;

public:

	Enemy_Meteorite(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 300;
	int random;
};

#endif // __ENEMY_METEORITE_H__