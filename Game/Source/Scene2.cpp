#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Animation.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene2.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "ModuleEntities.h"
#include "Player.h"
#include "Musher.h"
#include "Bat.h"

#include "Defs.h"
#include "Log.h"

Scene2::Scene2(bool isActive) : Module(isActive)
{
	name.Create("level2");
}

// Destructor
Scene2::~Scene2()
{}

// Called before render is available
bool Scene2::Awake()
{
	LOG("Loading Scene 2");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene2::Start()
{
	app->physics->Start();
	app->map->Load("level2.tmx");
	//	app->audio->PlayMusic("Assets/audio/music/level1.wav");

	app->levelManagement->KeysToTake = 3;

	//Spawn all entities
	app->entities->Start();

	return true;
}

// Called each loop iteration
bool Scene2::PreUpdate()
{

	if (app->entities->playerInstance->isGodmodeOn) app->entities->playerInstance->lives = 3;

	return true;
}

// Called each loop iteration
bool Scene2::Update(float dt)
{
	// L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F5))
		app->SaveGameRequest();

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());



	return true;
}

// Called each loop iteration
bool Scene2::PostUpdate()
{
	bool ret = true;

	// Draw functions
	app->map->Draw();
	app->physics->DrawColliders();

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;


	return ret;
}

// Called before quitting
bool Scene2::CleanUp()
{
	LOG("Disable scene 2");
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->PlayMusic("");
	return true;
}

void Scene2::Enable()
{
	LOG("Enable scene 1");
	Start();
}

void Scene2::Disable()
{
	LOG("Disable scene 1");
	app->map->CleanUp();
	app->physics->Disable();
	app->entities->Disable();
}

bool Scene2::LoadState(pugi::xml_node& data)
{
	bool ret = true;
	pugi::xml_node level = data.child("level1");
	KeysToTake = level.attribute("keys_to_collect").as_int();
	return ret;
}

bool Scene2::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node level = data.append_child("level1");

	level.append_attribute("keys_to_collect") = KeysToTake;

	return ret;
}