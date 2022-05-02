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
	name.Create("Battle_test_scene");
	toSave = false;
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
	//activate physiscs
	app->physics->Start();
	//load map tiles, entities, colliders
	app->map->Load("BattleGroundTest.tmx");
	//start etities
	app->entities->Start();

	battleEntities = app->entities->entities;
	currentEntity = app->entities->entities.start;
	currentEntity->data->battleState = MOVE;

	//start combat
	app->entities->StartPlayerTurn();

	app->render->cameraDrag = false;
	app->render->borderMovement = true;
	return true;
}

bool BattleTestScene::PreUpdate()
{
	return true;
}

bool BattleTestScene::Update(float dt)
{

	for (int i = 0; i < battleEntities.count(); i++)
	{

	}


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
	app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
