#include "BattleTestScene.h"
#include "Log.h"
#include "App.h"
#include "Map.h"

BattleTestScene::BattleTestScene(bool isActive) : Module(isActive)
{
	name.Create("Battle Test Scene");
}

BattleTestScene::~BattleTestScene()
{
}

bool BattleTestScene::Awake(pugi::xml_node&)
{
	
	return true;
}

bool BattleTestScene::Start()
{
	LOG("Loading Battle Test");

	app->map->Load("BattleGroundTest.tmx");
	return true;
}

bool BattleTestScene::PreUpdate()
{
	return true;
}

bool BattleTestScene::Update(float dt)
{
	return true;
}

bool BattleTestScene::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool BattleTestScene::CleanUp()
{
	return true;
}
