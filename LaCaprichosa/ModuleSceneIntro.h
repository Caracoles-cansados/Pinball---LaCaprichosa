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

	void OnExitCollision(PhysBody* bodyA, PhysBody* bodyB);


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

	SDL_Texture* pizzaRuleta_tex;
	SDL_Texture* bola_tex;

	SDL_Texture* luces1_tex;
	SDL_Texture* luces2_tex;
	SDL_Texture* luces3_tex;
	SDL_Texture* luces4_tex;
	SDL_Texture* luces5_tex;
	SDL_Texture* luces6_tex;


	SDL_Texture* mano_tex;


	SDL_Texture* paletaL_tex;
	SDL_Texture* paletaR_tex;

	uint bonus_fx;
	p2Point<int> ray;
	bool ray_on;

	PhysBody* ball;

	// Flippers
	PhysBody* paletaIzquierdo;
	PhysBody* paletaDerecho;
	PhysBody* paletaIzquierdoPoint;
	PhysBody* paletaDerechoPoint;
	int fuerzaPaleta = -600;
	int springForce;
	
	int puntuacionJuego = 0;

	
	PhysBody* muelleInicio;
	PhysBody* muelleInicioPoint;
	PhysBody* bola;
	PhysBody* bola2;
	PhysBody* bola3;
	PhysBody* bola4;


	PhysBody* rebotadorAbajoL;
	PhysBody* rebotadorAbajoR;





	PhysBody* circuloGiratorio;


	bool crearBola = false;
	bool estaRotando = false;
	int ruletaX = 350;
	int ruletaY = 600;
	int ruletaR = 150;
	int ruletaForce = 6;
	int ruletaAngle = 0;


	int puntuacionAlTocar = 100;

};
