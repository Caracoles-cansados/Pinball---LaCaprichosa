#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	background_tex = App->textures->Load("textures/background.png");
	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);




	// Pivot 0, 0
	


	ball = App->physics->CreateCircle(300, 100, 25);
	ball->listener = this;


	
	CreateTerrain();
	CreateObjects();



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->physics->GetWorld()->DestroyBody(bateadorIzquierdo->body);
	App->physics->GetWorld()->DestroyBody(bateadorDerecho->body);
	App->physics->GetWorld()->DestroyBody(bateadorIzquierdoPoint->body);
	App->physics->GetWorld()->DestroyBody(bateadorDerechoPoint->body);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	//if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	//{
	//	ray_on = !ray_on;
	//	ray.x = App->input->GetMouseX();
	//	ray.y = App->input->GetMouseY();
	//}

	//if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	//{
	//	circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
	//	circles.getLast()->data->listener = this;
	//}

	//if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	//{
	//	boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	//}

	//if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	//{
	//	// Pivot 0, 0
	//	int rick_head[64] = {
	//		14, 36,
	//		42, 40,
	//		40, 0,
	//		75, 30,
	//		88, 4,
	//		94, 39,
	//		111, 36,
	//		104, 58,
	//		107, 62,
	//		117, 67,
	//		109, 73,
	//		110, 85,
	//		106, 91,
	//		109, 99,
	//		103, 104,
	//		100, 115,
	//		106, 121,
	//		103, 125,
	//		98, 126,
	//		95, 137,
	//		83, 147,
	//		67, 147,
	//		53, 140,
	//		46, 132,
	//		34, 136,
	//		38, 126,
	//		23, 123,
	//		30, 114,
	//		10, 102,
	//		29, 90,
	//		0, 75,
	//		30, 62
	//	};

	//	ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	//}

	//// Prepare for raycast ------------------------------------------------------
	//
	//iPoint mouse;
	//mouse.x = App->input->GetMouseX();
	//mouse.y = App->input->GetMouseY();
	//int ray_hit = ray.DistanceTo(mouse);

	//fVector normal(0.0f, 0.0f);

	//// All draw functions ------------------------------------------------------
	//p2List_item<PhysBody*>* c = circles.getFirst();

	//while(c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);
	//	if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
	//		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
	//	c = c->next;
	//}

	//c = boxes.getFirst();

	//while(c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);
	//	App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
	//	if(ray_on)
	//	{
	//		int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
	//		if(hit >= 0)
	//			ray_hit = hit;
	//	}
	//	c = c->next;
	//}

	//c = ricks.getFirst();

	//while(c != NULL)
	//{
	//	int x, y;
	//	c->data->GetPosition(x, y);
	//	App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
	//	c = c->next;
	//}

	//// ray -----------------
	//if(ray_on == true)
	//{
	//	fVector destination(mouse.x-ray.x, mouse.y-ray.y);
	//	destination.Normalize();
	//	destination *= ray_hit;

	//	App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

	//	if(normal.x != 0.0f)
	//		App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	//}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		bateadorIzquierdo->body->ApplyForceToCenter(b2Vec2(0, fuerzaBateador), 1);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		bateadorDerecho->body->ApplyForceToCenter(b2Vec2(0, fuerzaBateador), 1);
	}

	App->renderer->Blit(background_tex, 0, 0);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}

void ModuleSceneIntro::CreateTerrain()
{

	int background[98] = {
		666, 897,
		665, 2,
		3, 3,
		1, 897,
		225, 898,
		225, 875,
		48, 767,
		29, 738,
		28, 572,
		47, 558,
		47, 544,
		21, 518,
		81, 425,
		27, 346,
		25, 267,
		49, 189,
		87, 135,
		132, 100,
		199, 67,
		280, 48,
		382, 45,
		456, 51,
		518, 61,
		610, 118,
		640, 180,
		642, 297,
		641, 427,
		644, 497,
		641, 585,
		643, 671,
		643, 761,
		644, 819,
		630, 834,
		610, 830,
		604, 812,
		605, 739,
		605, 579,
		604, 500,
		547, 545,
		551, 576,
		584, 596,
		592, 612,
		591, 750,
		568, 770,
		484, 821,
		409, 861,
		397, 876,
		399, 894,
		652, 897
	};
	App->physics->CreateChain(0, 0, background, 98, b2_staticBody);


	int leftThing[18] = {
		213, 801,
		201, 814,
		79, 739,
		68, 720,
		66, 635,
		78, 629,
		97, 640,
		94, 726,
		202, 794
	};
	App->physics->CreateChain(0, 0, leftThing, 18, b2_staticBody);

	int rightThing[22] = {
	421, 818,
	410, 803,
	529, 731,
	524, 642,
	547, 627,
	557, 634,
	560, 663,
	558, 715,
	548, 736,
	527, 751,
	430, 813
	};

	App->physics->CreateChain(0, 0, rightThing, 18, b2_staticBody);
}

void ModuleSceneIntro::CreateObjects()
{


	int x1 = 230;
	int y1 = 810;

	int x2 = 410;
	int y2 = 810;

	int w = 70;
	int h = 10;

	// --- Left flipper ---
	bateadorIzquierdo = App->physics->CreateRectangle(x1, y1, w, h);
	bateadorIzquierdoPoint = App->physics->CreateCircle(x1, y2, 2);
	bateadorIzquierdoPoint->body->SetType(b2_staticBody);

	// Flipper Joint (flipper rectangle x flipper circle to give it some movement)
	b2RevoluteJointDef bateadorIzquierdoJoint;

	bateadorIzquierdoJoint.bodyA = bateadorIzquierdo->body;
	bateadorIzquierdoJoint.bodyB = bateadorIzquierdoPoint->body;
	bateadorIzquierdoJoint.referenceAngle = 0 * DEGTORAD;
	bateadorIzquierdoJoint.enableLimit = true;
	bateadorIzquierdoJoint.lowerAngle = -30 * DEGTORAD;
	bateadorIzquierdoJoint.upperAngle = 30 * DEGTORAD;
	bateadorIzquierdoJoint.localAnchorA.Set(PIXEL_TO_METERS(-33), 0);
	bateadorIzquierdoJoint.localAnchorB.Set(0, 0);
	b2RevoluteJoint* joint_leftFlipper = (b2RevoluteJoint*)App->physics->GetWorld()->CreateJoint(&bateadorIzquierdoJoint);


	// --- Right flipper ---
	bateadorDerecho = App->physics->CreateRectangle(x2, y2, w, h);
	bateadorDerechoPoint = App->physics->CreateCircle(x2, y2, 2);
	bateadorDerechoPoint->body->SetType(b2_staticBody);

	// Flipper Joint
	b2RevoluteJointDef bateadorDerechoJoint;

	bateadorDerechoJoint.bodyA = bateadorDerecho->body;
	bateadorDerechoJoint.bodyB = bateadorDerechoPoint->body;
	bateadorDerechoJoint.referenceAngle = 0 * DEGTORAD;
	bateadorDerechoJoint.enableLimit = true;
	bateadorDerechoJoint.lowerAngle = -30 * DEGTORAD;
	bateadorDerechoJoint.upperAngle = 30 * DEGTORAD;
	bateadorDerechoJoint.localAnchorA.Set(PIXEL_TO_METERS(33), 0);
	bateadorDerechoJoint.localAnchorB.Set(0, 0);
	b2RevoluteJoint* joint_rightFlipper = (b2RevoluteJoint*)App->physics->GetWorld()->CreateJoint(&bateadorDerechoJoint);

	// Get texture
	flipper = App->textures->Load("pinball/sprites/flipper.png");
	flipper2 = App->textures->Load("pinball/sprites/flipper2.png");

}
