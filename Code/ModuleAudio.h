#ifndef __MODULEAUDIO_H__
#define __MODULEAUDIO_H__

#include "Module.h"
#include "Globals.h"

struct _Mix_Music;
struct Mix_Chunk;


class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	_Mix_Music* music = nullptr;
};


#endif // __MODULEAUDIO_H__