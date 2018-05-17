#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleEnemyBoss.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStartMenu.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"


ModuleEnemyBoss::ModuleEnemyBoss()
{
	current_animation = NULL;

	NeoGeo.PushBack({ 0, 0, 227, 40 });

	NeoGeo.loop = false;
	NeoGeo.speed = 0.3f;
}

ModuleEnemyBoss::~ModuleEnemyBoss()
{}

// Load assets
bool ModuleEnemyBoss::Start()
{
	LOG("Loading music and textures");
	//App->audio->PlayMusic("Assets/Audio/Music/neoGeo.ogg", 1.0f);
	//graphics = App->textures->Load("Assets/Sprites/NeoGeo/neogeo.png");
	return true;
}

// Update: draw background
update_status ModuleEnemyBoss::Update()

{
	current_animation = &NeoGeo;
	SDL_Rect r = current_animation->GetCurrentFrame();

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 44, 80, &r, 1);

	return UPDATE_CONTINUE;
}

// UnLoad assets
bool ModuleEnemyBoss::CleanUp()
{
	LOG("Unloading Neo Geo logo scene");
	//App->textures->Unload(graphics);
	return true;
}