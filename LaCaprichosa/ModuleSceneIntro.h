#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);


	void CreateTerrain();
	void CreateObjects();

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	PhysBody* sensor;
	bool sensed;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* background_tex;
	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	PhysBody* ball;

	// Flippers
	PhysBody* bateadorIzquierdo;
	PhysBody* bateadorDerecho;
	PhysBody* bateadorIzquierdoPoint;
	PhysBody* bateadorDerechoPoint;
	int fuerzaBateador = -200;
	SDL_Texture* flipper;
	SDL_Texture* flipper2;

};
