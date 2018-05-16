#ifndef __ENEMY_BEYBLADE_H__
#define __ENEMY_BEYBLADE_H__

#include "Enemy.h"

class Enemy_Beyblade : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;

	Animation spin;
	Animation open;
	Animation close;
	Animation leave;
	Animation appear;

	Path path;

	uint lastTimeShoot = 0, currentTime;

public:

	Enemy_Beyblade(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	bool still = false;
	bool shot = false;
	bool leaving = false;
	int score = 250;
};

#endif // __ENEMY_BEYBLADE_H__