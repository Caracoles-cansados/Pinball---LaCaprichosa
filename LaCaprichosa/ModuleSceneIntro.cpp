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
	


	ball = App->physics->CreateCircle(672, 700, 15);
	ball->listener = this;
	ball->type = BALL;
	
	


	
	CreateTerrain();
	CreateObjects();



	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->physics->GetWorld()->DestroyBody(paletaIzquierdo->body);
	App->physics->GetWorld()->DestroyBody(paletaDerecho->body);
	App->physics->GetWorld()->DestroyBody(paletaIzquierdoPoint->body);
	App->physics->GetWorld()->DestroyBody(paletaDerechoPoint->body);

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
		paletaIzquierdo->body->ApplyForceToCenter(b2Vec2(0, fuerzaPaleta), 1);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		paletaDerecho->body->ApplyForceToCenter(b2Vec2(0, fuerzaPaleta), 1);
	}


	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
		//paletaInicio->body->ApplyForceToCenter(b2Vec2(0, fuerzaPaleta), 1);
		
		
		if (springForce < 900) {
			springForce += 10;

		}
		muelleInicio->body->ApplyForceToCenter(b2Vec2(0, springForce), 1);
	}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP) {
		springForce = 0;
	}
	App->renderer->Blit(background_tex, 0, 0);

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		ball = App->physics->CreateCircle(672, 700, 15);
		ball->listener = this;
		ball->type = BALL;
	}

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
	
	if ((bodyA->type == BALL && bodyB->type == RESETBALL) || (bodyA->type == RESETBALL  && bodyB->type == BALL)) {
		LOG("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

		delete ball;

		ball = App->physics->CreateCircle(672, 700, 15);
		ball->listener = this;
		ball->type = BALL;
	}


}

void ModuleSceneIntro::CreateTerrain()
{

	//int background[98] = {
	//	666, 897,
	//	665, 2,
	//	3, 3,
	//	1, 897,
	//	225, 898,
	//	225, 875,
	//	48, 767,
	//	29, 738,
	//	28, 572,
	//	47, 558,
	//	47, 544,
	//	21, 518,
	//	81, 425,
	//	27, 346,
	//	25, 267,
	//	49, 189,
	//	87, 135,
	//	132, 100,
	//	199, 67,
	//	280, 48,
	//	382, 45,
	//	456, 51,
	//	518, 61,
	//	610, 118,
	//	640, 180,
	//	642, 297,
	//	641, 427,
	//	644, 497,
	//	641, 585,
	//	643, 671,
	//	643, 761,
	//	644, 819,
	//	630, 834,
	//	610, 830,
	//	604, 812,
	//	605, 739,
	//	605, 579,
	//	604, 500,
	//	547, 545,
	//	551, 576,
	//	584, 596,
	//	592, 612,
	//	591, 750,
	//	568, 770,
	//	484, 821,
	//	409, 861,
	//	397, 876,
	//	399, 894,
	//	652, 897
	//};
	//App->physics->CreateChain(0, 0, background, 98, b2_staticBody);



	int background[108] = {
	-1, 898,
	50, 898,
	50, 646,
	58, 610,
	71, 585,
	95, 572,
	121, 566,
	142, 556,
	152, 541,
	156, 520,
	151, 501,
	138, 483,
	113, 469,
	92, 451,
	73, 431,
	56, 410,
	50, 388,
	50, 351,
	50, 311,
	38, 285,
	13, 265,
	0, 250,
	-1, 200,
	8, 186,
	17, 173,
	29, 165,
	42, 155,
	44, 145,
	38, 136,
	26, 129,
	15, 118,
	4, 103,
	3, 90,
	7, 74,
	18, 62,
	33, 47,
	50, 33,
	67, 20,
	88, 9,
	107, 1,
	125, -2,
	598, -1,
	623, 11,
	637, 16,
	654, 28,
	668, 42,
	676, 58,
	690, 80,
	698, 100,
	697, 900,
	743, 852,
	737, -48,
	-50, -50,
	-45, 894
	};
	App->physics->CreateChain(0, 0, background, 108, b2_staticBody);



	/*int leftThing[18] = {
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

	App->physics->CreateChain(0, 0, rightThing, 18, b2_staticBody);*/

	
	// Pivot 0, 0
	int cosaderecha[80] = {
		648, 899,
		650, 152,
		641, 114,
		621, 87,
		589, 64,
		561, 49,
		542, 51,
		536, 63,
		534, 83,
		545, 95,
		555, 103,
		568, 112,
		592, 129,
		602, 149,
		605, 180,
		605, 211,
		605, 241,
		602, 267,
		597, 291,
		590, 308,
		577, 322,
		564, 336,
		555, 356,
		550, 372,
		548, 394,
		549, 416,
		550, 435,
		561, 454,
		574, 470,
		584, 485,
		597, 497,
		604, 507,
		618, 525,
		625, 541,
		630, 570,
		635, 596,
		640, 624,
		643, 651,
		644, 678,
		644, 911
	};
	App->physics->CreateChain(0, 0, cosaderecha, 80, b2_staticBody);

	int cosaarriba[64] = {
		268, 51,
		256, 53,
		248, 62,
		246, 75,
		246, 85,
		247, 93,
		252, 100,
		258, 104,
		267, 113,
		276, 121,
		280, 127,
		284, 133,
		299, 144,
		315, 146,
		321, 146,
		330, 146,
		342, 148,
		357, 148,
		402, 149,
		412, 143,
		421, 136,
		424, 132,
		431, 126,
		440, 114,
		445, 106,
		449, 98,
		450, 84,
		449, 66,
		448, 60,
		440, 52,
		429, 49,
		281, 48
	};
	App->physics->CreateChain(0, 0, cosaarriba, 64, b2_staticBody);

	int cosaizquierda[94] = {
	81, 163,
	87, 156,
	97, 153,
	108, 153,
	117, 159,
	125, 164,
	134, 172,
	144, 184,
	157, 198,
	171, 212,
	180, 223,
	189, 236,
	193, 250,
	199, 266,
	200, 300,
	200, 312,
	200, 387,
	196, 398,
	192, 402,
	189, 407,
	182, 413,
	175, 419,
	165, 426,
	157, 428,
	148, 429,
	139, 429,
	130, 425,
	123, 420,
	115, 414,
	109, 405,
	103, 392,
	99, 375,
	101, 352,
	100, 326,
	100, 315,
	99, 304,
	93, 291,
	84, 282,
	71, 270,
	59, 261,
	51, 252,
	49, 243,
	48, 231,
	47, 222,
	47, 212,
	51, 201,
	76, 168
	};
	App->physics->CreateChain(0, 0, cosaizquierda, 94, b2_staticBody);

	int cosaabajo[184] = {
	200, 910,
	94, 800,
	96, 649,
	129, 618,
	138, 614,
	146, 620,
	145, 626,
	137, 630,
	118, 637,
	108, 646,
	105, 652,
	103, 798,
	213, 908,
	222, 916,
	242, 911,
	249, 904,
	244, 899,
	145, 800,
	145, 704,
	141, 690,
	147, 679,
	153, 678,
	157, 681,
	160, 685,
	160, 693,
	156, 705,
	156, 712,
	159, 721,
	165, 731,
	171, 735,
	176, 738,
	180, 743,
	183, 748,
	183, 755,
	183, 761,
	181, 769,
	178, 775,
	171, 781,
	163, 787,
	157, 795,
	157, 801,
	160, 805,
	255, 899,
	259, 979,
	266, 1020,
	402, 1022,
	441, 899,
	540, 799,
	541, 792,
	535, 788,
	521, 778,
	516, 773,
	512, 761,
	512, 750,
	514, 742,
	524, 734,
	531, 731,
	538, 720,
	541, 710,
	543, 699,
	543, 632,
	542, 612,
	548, 607,
	553, 609,
	556, 614,
	554, 623,
	552, 633,
	550, 800,
	452, 900,
	452, 910,
	458, 921,
	470, 925,
	483, 924,
	492, 910,
	494, 898,
	593, 796,
	596, 601,
	570, 580,
	560, 568,
	562, 562,
	568, 558,
	574, 561,
	582, 568,
	594, 582,
	602, 596,
	601, 800,
	505, 900,
	460, 1059,
	364, 1125,
	249, 1092,
	211, 1012,
	201, 945
	};

	App->physics->CreateChain(0, 0, cosaabajo, 184, b2_staticBody);

<<<<<<< HEAD
	int champi[60] = {
	356, 417,
	333, 416,
	320, 408,
	312, 397,
	311, 382,
	317, 376,
	327, 376,
	336, 380,
	346, 380,
	351, 373,
	351, 363,
	347, 356,
	347, 347,
	352, 340,
	360, 337,
	368, 338,
	375, 347,
	374, 358,
	371, 367,
	371, 376,
	375, 380,
	386, 377,
	395, 376,
	402, 379,
	407, 388,
	407, 394,
	403, 403,
	396, 408,
	382, 413,
	371, 417
	};
	App->physics->CreateChain(0, 0, champi, 60, b2_staticBody);
=======
	PhysBody* colisionPerder = App->physics->CreateRectangle(450, 450, 900, 20, b2_staticBody);
	colisionPerder->type = RESETBALL;
	colisionPerder->listener = this;

>>>>>>> 5b2ed2e8092bce2606d981b2eae65796dbb2b952
}

void ModuleSceneIntro::CreateObjects()
{







	bola = App->physics->CreateBolas(200, 150, 14);
	bola->body->SetType(b2_staticBody);
	bola->body->SetFixedRotation(true);
	



	bola2 = App->physics->CreateBolas(500, 150, 16);
	bola2->body->SetType(b2_staticBody);
	bola2->body->SetFixedRotation(true);

	bola3 = App->physics->CreateBolas(550, 250, 16);
	bola3->body->SetType(b2_staticBody);
	bola3->body->SetFixedRotation(true);

	bola4 = App->physics->CreateBolas(450, 300, 16);
	bola4->body->SetType(b2_staticBody);
	bola4->body->SetFixedRotation(true);


	//Paleta inicio
	muelleInicio = App->physics->CreateRectangle(673, 775, 30, 20);
	
	muelleInicio->body->SetFixedRotation(true);
	muelleInicioPoint = App->physics->CreateCircle(673, 830, 2);
	muelleInicioPoint->body->SetType(b2_staticBody);

	b2DistanceJointDef muelleDef;

	muelleDef.bodyA = muelleInicio->body;
	muelleDef.bodyB = muelleInicioPoint->body;

	muelleDef.localAnchorA.Set(0, 0);
	muelleDef.localAnchorB.Set(0, 0);

	muelleDef.length = 1.5f;

	muelleDef.collideConnected = true;

	muelleDef.frequencyHz = 7.0f;
	muelleDef.dampingRatio = 0.05f;

	b2PrismaticJoint* muelleJoint = (b2PrismaticJoint*)App->physics->GetWorld()->CreateJoint(&muelleDef);
	

	int x1 = 200;
	int y1 = 800;

	int x2 = 500;
	int y2 = 800;

	int w = 148;
	int h = 20;

	// --- Left flipper ---
	paletaIzquierdo = App->physics->CreateRectangle(x1, y1, w, h);
	paletaIzquierdoPoint = App->physics->CreateCircle(x1, y2, 2);
	paletaIzquierdoPoint->body->SetType(b2_staticBody);

	// Flipper Joint (flipper rectangle x flipper circle to give it some movement)
	b2RevoluteJointDef paletaIzquierdoJoint;

	paletaIzquierdoJoint.bodyA = paletaIzquierdo->body;
	paletaIzquierdoJoint.bodyB = paletaIzquierdoPoint->body;
	paletaIzquierdoJoint.referenceAngle = 0 * DEGTORAD;
	paletaIzquierdoJoint.enableLimit = true;
	paletaIzquierdoJoint.lowerAngle = -30 * DEGTORAD;
	paletaIzquierdoJoint.upperAngle = 30 * DEGTORAD;
	paletaIzquierdoJoint.localAnchorA.Set(PIXEL_TO_METERS(-50), 0);
	paletaIzquierdoJoint.localAnchorB.Set(0, 0);
	b2RevoluteJoint* joint_leftFlipper = (b2RevoluteJoint*)App->physics->GetWorld()->CreateJoint(&paletaIzquierdoJoint);


	// --- Right flipper ---
	paletaDerecho = App->physics->CreateRectangle(x2, y2, w, h);
	paletaDerechoPoint = App->physics->CreateCircle(x2, y2, 2);
	paletaDerechoPoint->body->SetType(b2_staticBody);

	// Flipper Joint
	b2RevoluteJointDef paletaDerechoJoint;

	paletaDerechoJoint.bodyA = paletaDerecho->body;
	paletaDerechoJoint.bodyB = paletaDerechoPoint->body;
	paletaDerechoJoint.referenceAngle = 0 * DEGTORAD;
	paletaDerechoJoint.enableLimit = true;
	paletaDerechoJoint.lowerAngle = -30 * DEGTORAD;
	paletaDerechoJoint.upperAngle = 30 * DEGTORAD;
	paletaDerechoJoint.localAnchorA.Set(PIXEL_TO_METERS(50), 0);
	paletaDerechoJoint.localAnchorB.Set(0, 0);
	b2RevoluteJoint* joint_rightFlipper = (b2RevoluteJoint*)App->physics->GetWorld()->CreateJoint(&paletaDerechoJoint);

	// Get texture
	flipper = App->textures->Load("pinball/sprites/flipper.png");
	flipper2 = App->textures->Load("pinball/sprites/flipper2.png");

}




