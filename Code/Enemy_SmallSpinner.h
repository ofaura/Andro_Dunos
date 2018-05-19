#ifndef ENEMY_SMALLSPINNER_H_
#define ENEMY_SMALLSPINNER_H_

#include "Enemy.h"

class Enemy_SmallSpinner : public Enemy
{
private:
	int original_y = 0;

	Animation spinning;
	
public:

	Enemy_SmallSpinner(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	int score = 300;
	int random;
};

#endif // !ENEMY_SMALLSPINNER_H_
