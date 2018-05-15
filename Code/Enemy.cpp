#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

Enemy::Enemy(int x, int y) : position(x, y)
{}

Enemy::~Enemy()
{
	if (collider != nullptr) {
		collider->to_delete = true;
		collider = nullptr;
	}
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
		if (collider != nullptr)
			collider->SetPos(position.x, position.y);

		if (animation != nullptr)
			App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	if (collider->type == COLLIDER_PLAYER_SHOT || (collider->type == COLLIDER_PLAYER) || collider->type == COLLIDER_PLAYER_2)
	{
		App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y);
	}
}