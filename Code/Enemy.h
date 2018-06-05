#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum Enemy_Type
{
	POWER_UP = 0,
	OTHERS
};

class Enemy
{
protected:
	Animation* animation = nullptr;

public:
	Collider* collider = nullptr;
	iPoint position;
	int HP;
	Enemy_Type type = OTHERS;

public:
	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
};

#endif // __ENEMY_H__