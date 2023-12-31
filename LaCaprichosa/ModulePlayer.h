#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void OnExitCollision(PhysBody* bodyA, PhysBody* bodyB);
	bool CleanUp();

public:
	
};