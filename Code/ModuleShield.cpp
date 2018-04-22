#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleShield.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

ModuleShield::ModuleShield() {}

ModuleShield::~ModuleShield() {}

bool ModuleShield::Start() { 
	
	
	return true; 
}

update_status ModuleShield::Update() { 
	
	return update_status::UPDATE_CONTINUE; 
}

bool ModuleShield::CleanUp() { 
	
	return true;
}