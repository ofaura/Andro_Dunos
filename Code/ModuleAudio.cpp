#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio() : Module()
{}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before audio is available
bool ModuleAudio::Init()
{
	LOG("Init SDL audio system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		LOG("Audio could not init. SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	App->audio->music = Mix_LoadMUS("Assets/Audio/level1.ogg");	
	if(App->audio->music == NULL){
		return false;
	}
	return ret;
}

// Called every audio update
update_status ModuleAudio::Update()
{
	Mix_PlayMusic(music, -1);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	if (music != nullptr)
	{
		Mix_FreeMusic(music);
	}
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}