#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (int i = 0; i < MAX_TEXTURES; ++i)
		if (textures[i] != nullptr)
			SDL_DestroyTexture(textures[i]);

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	// Load and image from a path (must be a png) and check for errors
	SDL_Texture* texture = nullptr;
	gSurface = IMG_Load(path);

	if (gSurface == NULL) {
		LOG("Could not load Image. IMG_Load: %s", IMG_GetError());
	}
	
	// create a texture from it to return it (check for errors again)
	else
	{
		texture = SDL_CreateTextureFromSurface(App->render->renderer, gSurface);

		if (texture == NULL)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n", SDL_GetError());
		}
		// free the surface and add the texture to our own array so we can properly free them 
		else
		{
			for (int i = 0; i < MAX_TEXTURES; ++i) {
				textures[i] = SDL_CreateTextureFromSurface(App->render->renderer, gSurface);

				if (textures[i] != nullptr) {
					LOG("Could not create a texture. SDL_CreateTextureFromSurface: %s", IMG_GetError());
				}

			}
		}

		SDL_FreeSurface(gSurface);
	}

	return texture;
}
