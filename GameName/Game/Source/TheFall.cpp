#include "TheFall.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

TheFall::TheFall(bool isActive) : Module(isActive)
{
	name.Create("The fall");
}

TheFall::~TheFall()
{
}

bool TheFall::Awake(pugi::xml_node&)
{
	return true;
}

bool TheFall::Start()
{

	app->map->Load("level1.tmx");
	app->entities->Start();
	app->physics->Enable();

	return true;
}

bool TheFall::PreUpdate()
{
	return true;
}

bool TheFall::Update(float dt)
{
	return true;
}

bool TheFall::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool TheFall::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->Disable();
	app->audio->StopMusic();
	return true;
}
