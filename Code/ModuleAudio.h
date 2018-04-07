#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"


#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 50

class ModuleAudio : public Module
{
public:

	ModuleAudio();

	bool Init();
	bool CleanUp();

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	uint LoadFx(const char* path);
	bool UnLoadFx(uint id);

	bool PlayFx(uint fx, int repeat = 0);

private:

	Mix_Music*	music = nullptr;
	Mix_Chunk*	fx[MAX_FX];
	uint last_fx = 1;
};



#endif // _ModuleAudio_H__