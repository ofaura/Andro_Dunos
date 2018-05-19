#include "Application.h"
#include "Enemy_Beyblade.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"

#include "SDL\include\SDL_timer.h"

Enemy_Beyblade::Enemy_Beyblade(int x, int y) : Enemy(x, y)
{
	// Animations
	appear.PushBack({ 203, 300, 18, 25 });
	appear.PushBack({ 144, 7, 18, 25 });
	appear.PushBack({ 203, 300, 18, 25 });
	appear.PushBack({ 144, 7, 18, 25 });
	appear.PushBack({ 203, 300, 18, 25 });
	appear.PushBack({ 144, 7, 18, 25 });
	appear.PushBack({ 203, 300, 18, 25 });
	appear.PushBack({ 144, 7, 18, 25 });
	appear.loop = false;
	appear.speed = 0.2f;

	leave.PushBack({ 203, 300, 18, 25 });
	leave.PushBack({ 144, 7, 18, 25 });
	leave.loop = false;
	leave.speed = 0.2f;

	spin.PushBack({ 170, 300, 18, 25 });
	spin.PushBack({ 203, 300, 18, 25 });
	spin.PushBack({ 236, 300, 18, 25 });
	spin.PushBack({ 170, 300, 18, 25 });
	spin.PushBack({ 203, 300, 18, 25 });
	spin.PushBack({ 236, 300, 18, 25 });
	spin.PushBack({ 170, 300, 18, 25 });
	spin.PushBack({ 203, 300, 18, 25 });
	spin.PushBack({ 236, 300, 18, 25 });
	spin.PushBack({ 170, 300, 18, 25 });
	spin.PushBack({ 203, 300, 18, 25 });
	spin.PushBack({ 236, 300, 18, 25 });
	spin.PushBack({ 170, 300, 18, 25 });
	spin.PushBack({ 203, 300, 18, 25 });
	spin.PushBack({ 236, 300, 18, 25 });
	spin.PushBack({ 170, 300, 18, 25 });
	spin.PushBack({ 203, 300, 18, 25 });
	spin.PushBack({ 236, 300, 18, 25 });
	open.loop = false;
	spin.speed = 0.7f;
	
	open.PushBack({ 170, 300, 18, 25 });
	open.PushBack({ 203, 300, 18, 25 });
	open.PushBack({ 236, 300, 18, 25 });
	open.PushBack({ 170, 331, 18, 25 });
	open.PushBack({ 203, 332, 18, 25 });
	open.PushBack({ 236, 332, 18, 25 });
	open.loop = false;
	open.speed = 0.2f;

	close.PushBack({ 236, 332, 18, 25 });
	close.PushBack({ 203, 332, 18, 25 });
	close.PushBack({ 170, 331, 18, 25 });
	close.PushBack({ 236, 300, 18, 25 });
	close.PushBack({ 203, 300, 18, 25 });
	close.PushBack({ 170, 300, 18, 25 });
	close.loop = false;
	close.speed = 0.2f;

	collider = App->collision->AddCollider({ 0, 0, 18, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &appear;
	original_y = y;
	HP = BEYBLADE;
}

void Enemy_Beyblade::Move()
{
	currentTime = SDL_GetTicks();

	if (currentTime > lastTimeShoot + 1500 && animation == &open) // Shoots at 1.5 seconds
	{
		if (open.Finished() == true && shot == false) {
			App->particles->AddParticle(App->particles->enemy_shot_blue1, position.x + 10, position.y + 8, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->enemy_shot_blue2, position.x + 10, position.y + 8, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->enemy_shot_blue3, position.x + 10, position.y + 8, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->enemy_shot_blue4, position.x + 10, position.y + 8, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->enemy_shot_blue5, position.x + 10, position.y + 8, COLLIDER_ENEMY_SHOT);
			App->particles->AddParticle(App->particles->enemy_shot_blue6, position.x + 10, position.y + 8, COLLIDER_ENEMY_SHOT);
			lastTimeShoot = currentTime;
			animation = &close;
			shot = true;
			still = false;
		}
	}

	if (shot == false) {
		if (appear.Finished() == true) {
				still = true;
				animation = &spin;
		}

		if (spin.Finished() == true) {
			animation = &open;
			lastTimeShoot = currentTime;
		}
	}

	// Movement
	if (leaving == true) {
		
		animation = &appear;
		
		if (appear.Finished()) {
			animation = &leave;
			position.x += 3;
		}
		else {
			position.x++;
		}
	}
	else if (still == true) {
		position.x++;
	}
	else if (shot == false) {
		position.x -= 3;
	}
	else if (spin.Finished() == false){		
		position.x++;
	}

	if (close.Finished() == true && leaving == false) {
		animation = &spin; 
		leaving = true;
	}

	collider->SetPos(position.x, position.y);
}

void Enemy_Beyblade::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->enemy_explosion, position.x, position.y, COLLIDER_NONE);
	App->audio->PlayFx(App->enemies->medium_enemy_death);


	if (dead == false)
	{

		if (collider->type == COLLIDER_PLAYER_SHOT)
		{
			App->user_interface->score1 += score;
		}
		if (collider->type == COLLIDER_PLAYER2_SHOT)
		{
			App->user_interface->score2 += score;
		}
	}

	dead = true;
}