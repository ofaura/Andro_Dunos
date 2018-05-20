#ifndef __ENEMY_SOLARPANEL_H__
#define __ENEMY_SOLARPANEL_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_SolarPanel : public Enemy
{
private:
	int original_x = 0;

	Animation fly;
	Animation open;
	Path path;

	uint lastTimeShoot = 0, currentTime;

public:

	Enemy_SolarPanel(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	bool dead = false;
	bool shot = false;
	int score = 8000;
};

#endif // __ENEMY_SOLARPANEL_H__