#ifndef _MODULE_SHIELD_P2_H
#define _MODULE_SHIELD_P2_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleShield_p2 : public Module {
public:
	ModuleShield_p2();
	~ModuleShield_p2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Collider* collider1;
	Collider* collider2;

	iPoint position1, position2;

};

#endif // !_MODULE_SHIELD_