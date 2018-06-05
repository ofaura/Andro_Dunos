#ifndef __ENEMY_BLUESHOTDOWN_H__
#define __ENEMY_BLUESHOTDOWN_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BlueshotDown : public Enemy
{
private:
	int original_x = 0;
	int original_y = 0;

	float wave = -1.0f;
	bool going_up = true;

	Animation fly;
	Path path;

public:

	Enemy_BlueshotDown(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
};

#endif // __ENEMY_BLUESHOT_H__