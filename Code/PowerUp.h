#ifndef __POWERUP_H__
#define __POWERUP_H__

#include "Enemy.h"

class PowerUp : public Enemy
{
private:

	int original_y = 0;

	bool CleanUp();

	Animation fly_1, fly_2, fly_3, fly_4, fly_5, fly_6;
	Animation* act[6];
	int vel_y = -1, vel_x = -1;
	int time = 0, loop = 3;

public:

	SDL_Rect size = { 0,0,26,26 };
	PowerUp(int x, int y);
	~PowerUp() {}

	void OnCollision(Collider* collider);
	void Draw(SDL_Texture* sprites);

	uint powerup_picked;

	SDL_Texture* graphics = nullptr;

	bool S_B = false, B_M = false, M_U = false, U_S = false;

	void Move();
};

#endif // __POWERUP_H__

