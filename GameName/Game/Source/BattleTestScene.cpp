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
	//Start UI
	app->guiManager->OpenPanel(P_BATTLE);


	battleEntities = app->entities->entities;
	currentEntity = app->entities->entities.start;
	currentEntity->data->battleState = IDLE;

	while (currentEntity != nullptr)
	{
		currentEntity->data->battleState = IDLE;
		currentEntity->data->entityTurn = false;

		currentEntity = currentEntity->next;
	}

	currentEntity = app->entities->entities.start;
	currentEntity->data->entityTurn = true;

	app->render->cameraDrag = true;


	entityIndex = 0;
	turnCounter = 0;

	return true;
}

bool BattleTestScene::PreUpdate()
{
	return true;
}

bool BattleTestScene::Update(float dt)
{

	if (!currentEntity->data->entityTurn) {
		NextEntity();
	}

	return true;
}

bool BattleTestScene::PostUpdate()
{
	
	app->map->Draw();

	int x, y;
	SDL_Rect r;

	app->input->GetMouseWorldPosition(x, y);
	iPoint p;
	p.x = x;
	p.y = y;
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	r.x = p.x;
	r.y = p.y;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 125, 255, 255, 150, true);


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

	//next entity
	currentEntity = currentEntity->next;

	//skip entities that are dead
	//while (currentEntity->data->battleState == DEATH)
	//	currentEntity = currentEntity->next;

	if (currentEntity == nullptr)
	{
		// all entitites had their turn
		// start the list again
		//increment the turn coutner
		currentEntity = battleEntities.start;
		currentEntity->data->StartTurn();
		turnCounter++;
	}
	else{
		currentEntity->data->StartTurn();
	}
}
