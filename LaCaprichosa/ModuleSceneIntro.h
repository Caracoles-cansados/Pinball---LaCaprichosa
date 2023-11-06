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
	PhysBody* paletaIzquierdo;
	PhysBody* paletaDerecho;
	PhysBody* paletaIzquierdoPoint;
	PhysBody* paletaDerechoPoint;
	int fuerzaPaleta = -200;
	int springForce;
	SDL_Texture* flipper;
	SDL_Texture* flipper2;


	
	PhysBody* muelleInicio;
	PhysBody* muelleInicioPoint;
	PhysBody* bola;
	PhysBody* bola2;
	PhysBody* bola3;
	PhysBody* bola4;


	bool crearBola = false;
};
