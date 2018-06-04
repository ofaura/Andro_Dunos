#ifndef __ENEMY_BLUESHOT_H__
#define __ENEMY_BLUESHOT_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BlueShot : public Enemy
{
private:
	int original_x = 0;
	int original_y = 0;

	float wave = -1.0f;
	bool going_up = true;

	Animation fly;
	Path path;

public:

	Enemy_BlueShot(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
};

#endif // __ENEMY_BLUESHOT_H__