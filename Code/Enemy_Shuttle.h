#ifndef __ENEMY_SHUTTLE_H__
#define __ENEMY_SHUTTLE_H__

#include "Enemy.h"

class Enemy_Shuttle : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	Animation fly;
	Animation go_back;
	Animation turn;
	int current_y = 0;
	bool change_direction = false;

public:

	Enemy_Shuttle(int x, int y);

	virtual void OnCollision(Collider* collider) override;
	void Move();
	int score = 200;
	int current_time = 0;
	int first_time = 0;
	int circle = 0;
	
};

#endif // __ENEMY_SHUTTLE_H__