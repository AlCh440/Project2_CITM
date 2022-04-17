#include "WorldTestScene.h"
#include "Log.h"
#include "App.h"
#include "Map.h"

WorldTestScene::WorldTestScene(bool isActive) : Module(isActive)
{
	name.Create("World Test Scene");
}

WorldTestScene::~WorldTestScene()
{
}

bool WorldTestScene::Awake(pugi::xml_node&)
{


	return true;
}

bool WorldTestScene::Start()
{
	LOG("Loading World Test");

	app->map->Load("WorldMapTest.tmx");

	return true;
}

bool WorldTestScene::PreUpdate()
{
	return true;
}

bool WorldTestScene::Update(float dt)
{
	return true;
}

bool WorldTestScene::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool WorldTestScene::CleanUp()
{
	app->physics->Disable();
	return true;
}
