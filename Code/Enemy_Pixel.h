#ifndef __ENEMY_PIXEL__
#define __ENEMY_PIXEL_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Pixel : public Enemy
{
private:
	int original_x = 0;
	int original_y = 0;
	bool circle;
	int angle;

	float wave = -1.0f;
	bool going_up = true;

	Animation fly_1;
	Animation fly_2;
	Animation* fly[2];

	bool CleanUp();

public:

	Enemy_Pixel(int x, int y);
	SDL_Texture* graphics = nullptr;

	virtual void OnCollision(Collider* collider) override;
	void Move();
};

#endif // __ENEMY_BLUESHOT_H__