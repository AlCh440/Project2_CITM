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

	//load map tiles, entities, colliders

	//activate physiscs
	app->physics->Start();

	//Load map depending on the zone
	switch (app->levelManagement->combatScene)
	{
	case PLAIN:
		app->map->Load("BattleGroundTest.tmx");
		break;
	case CASTLE:
		app->map->Load("combat_castle.tmx");
		break;
	case CAVES:
		app->map->Load("combat_caves.tmx");
		break;
	case FINALBATTLE:
		app->map->Load("combat_final.tmx");
		break;
	default:
		app->map->Load("BattleGroundTest.tmx");
		break;
	}

	//start etities
	app->entities->Start();

	app->audio->PlayMusic("assets/audio/music/CombatEnAmakna.wav", 0.5f);

	pointer = app->tex->Load("Assets/Sprites/UI/pathFinigTiles.png");
	rect = { 0,0,32,32 };

	app->levelManagement->inCombat = true;
	app->render->ResetCameraPosition();

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

	//Start UI when everything is loaded
	app->guiManager->OpenPanel(P_BATTLE);
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

	app->input->GetMouseWorldPosition(x, y);
	iPoint p;
	p.x = x;
	p.y = y;
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	app->render->DrawTexture(pointer,p.x,p.y,&rect);

	return true;
}

void BattleTestScene::NextEntity()
{
	//Stop current Entity
	currentEntity->data->entityTurn = false;

	if(currentEntity->data->battleState != DEATH)
		currentEntity->data->battleState = IDLE;

	//next entity
	currentEntity = currentEntity->next;

	//check that we are not at the end of the list
	if (currentEntity == nullptr)
	{
		//Check all win/lose conditions
		if (CheckWinCondition())
		{
			//all enemies dead, players won the battle
			//victory screen
			//exit menu
			LOG("BATTLE WON!");
			app->guiManager->matchResultInstance->LoadTitle(true);
			app->guiManager->OpenPanel(P_MATCH_RESULT);
		}
		else if (CheckLoseCondition())
		{
			//all players dead
			//lose screen
			//exit menu
			LOG("BATTLE LOST!");
			app->guiManager->matchResultInstance->LoadTitle(false);
			app->guiManager->OpenPanel(P_MATCH_RESULT);
		}

		// all entitites had their turn
		// start the list again
		//increment the turn coutner
		currentEntity = battleEntities.start;
		turnCounter++;
	}

	app->guiManager->battlePanelInstance->LoadEntityUi();

	//skip entities that are dead
	if (currentEntity->data->battleState == DEATH)
		NextEntity();
	else
		currentEntity->data->StartTurn();
}

bool BattleTestScene::CheckWinCondition()
{
	bool ret = false;

	p2ListItem<Enemy*>* e = app->entities->enemies.start;

	while (e != nullptr)
	{
		if (e->data->battleState == DEATH)
			ret = true;
		else
			ret = false;

		e = e->next;
	}

	return ret;
}

bool BattleTestScene::CheckLoseCondition()
{
	bool ret = false;

	p2ListItem<Player*>* e = app->entities->players.start;

	while (e != nullptr)
	{
		if (e->data->battleState == DEATH)
			ret = true;
		else
			ret = false;

		e = e->next;
	}

	return ret;
}


bool BattleTestScene::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	app->guiManager->pn_battle->Disable();
	return true;
}

