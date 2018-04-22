#ifndef _MODULE_SHIELD_H_
#define _MODULE_SHIELD_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleShield : public Module{
public:
	ModuleShield();
	~ModuleShield();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Collider* collider1;
	Collider* collider2;

	iPoint position1, position2;

};

#endif // !_MODULE_SHIELD_
