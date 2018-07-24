#ifndef __ENEMY_GREENBALL__
#define __ENEMY_GREENBALL_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_GreenBall : public Enemy
{
private:
	int original_x = 0;
	int original_y = 0;
	bool circle;
	int angle;
	int fix_y, fix_x;

	float wave = -1.0f;
	bool going_up = true;

	Animation fly_1;
	Animation fly_2;
	Animation* fly[2];

	bool CleanUp();

public:

	int score = 100;
	Enemy_GreenBall(int x, int y);
	void Draw(SDL_Texture* sprites);
	SDL_Texture* graphics = nullptr;

	virtual void OnCollision(Collider* collider) override;
	void Move();
};

#endif // __ENEMY_BLUESHOT_H__