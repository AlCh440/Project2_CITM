#include "BattleTestScene.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Physics.h"
#include "LevelManagement.h"
#include "Pathfinding.h"
#include "Entities.h"
#include "Audio.h"

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

	//load map tiles, entities, colliders
	app->map->Load("BattleGroundTest.tmx");

	//create navigation map
	int w, h;
	uchar* data = NULL;
	if (app->map->CreateWalkabilityMap(w, h, &data, 2)) app->pathFinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);

	//start etities
	app->entities->Start();
	//start combat
	app->entities->StartPlayerTurn();



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
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->Disable();
	app->audio->StopMusic();
	return true;
}
