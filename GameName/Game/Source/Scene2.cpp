#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Animation.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene2.h"
#include "Map.h"
#include "Physics.h"
#include "LevelManagement.h"
#include "Entities.h"
#include "Player.h"
//#include "Musher.h"
//#include "Bat.h"

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

	return true;
}

// Called each loop iteration
bool Scene2::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene2::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool Scene2::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool Scene2::CleanUp()
{
	LOG("CleanUp scene 2");
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
}

bool Scene2::LoadState(pugi::xml_node& data)
{
	bool ret = true;
	return ret;
}

bool Scene2::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	return ret;
}