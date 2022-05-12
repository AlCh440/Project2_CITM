#include "BattleTestScene.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Physics.h"
#include "LevelManagement.h"
#include "Pathfinding.h"
#include "Entities.h"
#include "Audio.h"
#include "GuiManager.h"

BattleTestScene::BattleTestScene(bool isActive) : Module(isActive)
{
	name.Create("Battle_test_scene");
	toSave = false;
	saveConfigs = false;
	
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
	//Start UI
	app->guiManager->OpenPanel(P_BATTLE);
	//start etities
	app->entities->Start();

	battleEntities = app->entities->entities;
	currentEntity = app->entities->entities.start;
	currentEntity->data->battleState = MOVE;

	while (currentEntity != nullptr)
	{
		currentEntity->data->battleState = IDLE;
		currentEntity->data->entityTurn = false;

		currentEntity = currentEntity->next;
	}

	currentEntity = app->entities->entities.start;
	currentEntity->data->entityTurn = true;

	//app->render->CameraFocus(currentEntity->data->position);
	app->render->cameraDrag = true;
	//app->render->borderMovement = true;

	entityIndex = 0;

	return true;
}

bool BattleTestScene::PreUpdate()
{
	return true;
}

bool BattleTestScene::Update(float dt)
{

	for (entityIndex; entityIndex < battleEntities.count();)
	{
		if (!currentEntity->data->entityTurn) {
			currentEntity = currentEntity->next;
		//	app->render->CameraFocus(currentEntity->data->position);
		}
		entityIndex++;
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
	app->guiManager->pn_battle->Disable();
	return true;
}

void BattleTestScene::NextEntity()
{
	//Stop current Entity
	currentEntity->data->entityTurn = false;
	currentEntity->data->battleState = IDLE;

	//next entity
	currentEntity = currentEntity->next;

	if (currentEntity == nullptr)
	{
		currentEntity = battleEntities.start;
		currentEntity->data->entityTurn = true;
	}
	else{
		currentEntity->data->entityTurn = true;;
	}
}
