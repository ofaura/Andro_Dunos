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

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		LOG("Audio could not init. SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		ret = false;
	}

	music = Mix_LoadMUS("Assets/Audio/level1.ogg");	
	Mix_FadeInMusic(music, -1, 2000);
	
	if(music == NULL){
		LOG("File could not be found. Mix_Error: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

// Called every audio update
/*update_status ModuleAudio::Update()
{	
	return update_status::UPDATE_CONTINUE;
}*/

// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Quitting SDL input event subsystem");

	if (music != nullptr)
	{
		Mix_FreeMusic(music);
	}

	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}