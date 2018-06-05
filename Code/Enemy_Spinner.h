#ifndef __ENEMY_SPINNER_H__
#define __ENEMY_SPINNER_H__

#include "Enemy.h"

class Enemy_Spinner : public Enemy
{
private:
	Animation fly;

public:

	Enemy_Spinner(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	int score = 100;
};

#endif // __ENEMY_SPINNER_H__