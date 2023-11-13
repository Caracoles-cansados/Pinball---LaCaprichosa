#include "ModuleMenu.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"

#include "SDL/include/SDL_scancode.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include <string> 
#include <vector>
#include <iostream>
#include <cmath>

ModuleMenu::ModuleMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	//backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	//backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	//backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	//backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro
	//backgroundAnim.PushBack({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }); //Centro


	//backgroundAnim.loop = false;
	//backgroundAnim.speed = 0.01f;
	//background = { 200,200, SCREEN_WIDTH, SCREEN_HEIGHT };


}

ModuleMenu::~ModuleMenu()
{

}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	////textureBackground2 = App->textures->Load("Assets/Interface/Menu/fondo.png");
	
	textureBackground = App->textures->Load("textures/Menu Inicio.png");
	//Mix_HaltMusic();

	App->renderer->camera.x = 0;
	App->renderer->camera.y = 0;

	
	//currentAnimation = &backgroundAnim;

	return ret;
}

update_status ModuleMenu::Update()
{


	App->renderer->Blit(textureBackground, 0, 0);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		

		App->fade->FadeToBlack(App->menu, App->scene_intro, 20);
	}
	
	


	return update_status::UPDATE_CONTINUE;

}

// Update: draw background
update_status ModuleMenu::PostUpdate()
{


	//App->render->Blit(textureBackground2, 0, 0, SDL_FLIP_NONE, &background, 1);
	App->renderer->Blit(textureBackground, 0, 0);

	
	//currentAnimation->Update();
	return update_status::UPDATE_CONTINUE;
}



