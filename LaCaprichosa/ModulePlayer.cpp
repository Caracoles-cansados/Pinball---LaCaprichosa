#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	return true;

	PPSound1 = App->audio->LoadFx("audio/PP1.wav");
	PPSound2 = App->audio->LoadFx("audio/PP2.wav");
	PPSound3 = App->audio->LoadFx("audio/PP3.wav");
	PPSound4 = App->audio->LoadFx("audio/PP4.wav");
	PPSound5 = App->audio->LoadFx("audio/PP5.wav");

	App->audio->PlayMusic("audio/music.ogg", 1.0f);
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	if (bodyB->type == PLATAFORMA_ROTANTE) {
		LOG("TA DENTROOOOOO");
	}

}

void ModulePlayer::OnExitCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB->type == PLATAFORMA_ROTANTE) {
		LOG("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	}
}





