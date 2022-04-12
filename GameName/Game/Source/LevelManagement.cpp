#include "LevelManagement.h"
#include "Log.h"
#include "Player.h"
#include "Entities.h"
#include "Map.h"
#include <string>
#include <iostream>
using namespace std;

LevelManagement::LevelManagement(bool isActive) : Module(isActive)
{
	name.Create("Level Manager");
}

LevelManagement::~LevelManagement()
{
}

bool LevelManagement::Awake(pugi::xml_node&)
{
	return true;
}

bool LevelManagement::Start()
{
	gameState = GameState::WORLD_TEST;
	currentScene = (Module*)app->dragonCliff;
	return true;
}

bool LevelManagement::PreUpdate()
{

	if ((app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) && currentScene->active == true)
	{
		gameState = WORLD_TEST;
	}
	if ((app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) && currentScene->active == true)
	{
		gameState = COMBAT;
		app->entities->AddEntity(Collider_Type::DUMMY, iPoint(0, 0));
	}
	if ((app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN) && currentScene->active == true)
	{
		physDebug = !physDebug;
	}

	if (physDebug)
	{
		app->physics->DrawColliders();
	}

	//if ((app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) && currentScene->active == true)
	//{
	//	gameState = SCENE1;
	//}
	//if ((app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) && currentScene->active == true)
	//{
	//	RestartLevel();
	//}
	//if ((app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN) && currentScene->active == true)
	//{
	//	app->physics->DrawColliders();
	//}
	switch (gameState)
	{
	case INTRO:
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = START;
		}
		break;
	case START:
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = SCENE1;
		}

		if ((app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) && currentScene->active == true)
		{
			//gameState = SCENE2;
		}
		break;
	case SCENE1:
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			//gameState = SCENE2;
		}
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && currentScene->active == true)
		{
			RestartLevel();
		}
		break;
	case GAME_OVER:
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && currentScene->active == true)
		{
			gameState = START;
			app->physics->ClearAllCollidersLists();
		
		}
		if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN && currentScene->active == true)
		{
			app->LoadGameRequest();
		}
		break;
	default:
		break;
	}
	return true;
}

bool LevelManagement::Update(float dt)
{
//	LOG("Scene: %s", currentScene->name.GetString());

	switch (gameState)
	{
	case INTRO:
		
		break;
	case START:
		if (currentScene != (Module*)app->start) {
			if (app->fade->Fade(currentScene, (Module*)app->start, 60))
			{
				currentScene = (Module*)app->start;
				LOG("START");
			}
		}
		break;
	case GAME_OVER:

		if (currentScene != (Module*)app->gameOver) {
			if (app->fade->Fade(currentScene, (Module*)app->gameOver, 30))
			{
				currentScene = (Module*)app->gameOver;
				LOG("GAME OVER");
			}
		}
		break;
	case SCENE1:
		if (currentScene != (Module*)app->scene1) {

			if (app->fade->Fade(currentScene, (Module*)app->scene1, 30))
			{
				currentScene = (Module*)app->scene1;
				currentLevel = (Module*)app->scene1;
				LOG("Scene 1");
			}
		}
		break;
	case THE_FALL:
		if (currentScene != (Module*)app->theFall) {

			if (app->fade->Fade(currentScene, (Module*)app->theFall, 30))
			{
				currentScene = (Module*)app->theFall;
				currentLevel = (Module*)app->theFall;
				LOG("The fall");
			}
		}
		break;
	case GREEN_PATH:
		if (currentScene != (Module*)app->greenPath) {

			if (app->fade->Fade(currentScene, (Module*)app->greenPath, 30))
			{
				currentScene = (Module*)app->greenPath;
				currentLevel = (Module*)app->greenPath;
				LOG("Green Path");
			}
		}
		break;
	case VILLAGE:
		if (currentScene != (Module*)app->village) {

			if (app->fade->Fade(currentScene, (Module*)app->village, 30))
			{
				currentScene = (Module*)app->village;
				currentLevel = (Module*)app->village;
				LOG("The village");
			}
		}
		break;
	case RUINS:
		if (currentScene != (Module*)app->ruins) {

			if (app->fade->Fade(currentScene, (Module*)app->ruins, 30))
			{
				currentScene = (Module*)app->ruins;
				currentLevel = (Module*)app->ruins;
				LOG("The ruins");
			}
		}
		break;
	case FRACTURED_ROAD:
		if (currentScene != (Module*)app->fracturedRoad) {

			if (app->fade->Fade(currentScene, (Module*)app->fracturedRoad, 30))
			{
				currentScene = (Module*)app->fracturedRoad;
				currentLevel = (Module*)app->fracturedRoad;
				LOG("Fractured road");
			}
		}
		break;
	case DRAGRON_CLIFF:
		if (currentScene != (Module*)app->dragonCliff) {

			if (app->fade->Fade(currentScene, (Module*)app->dragonCliff, 30))
			{
				currentScene = (Module*)app->dragonCliff;
				currentLevel = (Module*)app->dragonCliff;
				LOG("Dragon Cliff");
			}
		}
		break;
	case WORLD_TEST:
		if (currentScene != (Module*)app->worldTest) {

			if (app->fade->Fade(currentScene, (Module*)app->worldTest, 30))
			{
				currentScene = (Module*)app->worldTest;
				currentLevel = (Module*)app->worldTest;
				LOG("World Test");
			}
		}
		break;
	case COMBAT:
		if (currentScene != (Module*)app->battleTest) {

			if (app->fade->Fade(currentScene, (Module*)app->battleTest, 30))
			{
				currentScene = (Module*)app->battleTest;
				currentLevel = (Module*)app->battleTest;
				LOG("Battle Test");
			}
		}
		break;
	default:
		break;

	}
	frameCounter++;
	return true;
}

void LevelManagement::NextLevel()
{
	switch (gameState) {
	case GameState::SCENE1:
		if (levelsPassed < 1) {
			levelsPassed++;
		}
		break;
	default:
		break;
	}
}

void LevelManagement::ReturnToMainMenu()
{
	if (gameState != START)
	{
		gameState = START;
	}
}

void LevelManagement::RestartLevel()
{
	if (app->entities->playerInstance->lifePoints < 0)
	{
		gameState = GAME_OVER;
	
		app->fade->Fade(currentScene, (Module*)app->gameOver, 60.0f);
	}
	else {
		app->fade->Fade(currentScene, currentLevel, 60.0f);
	}
}

bool LevelManagement::LoadState(pugi::xml_node& data)
{
	pugi::xml_document gameStateFile;
	pugi::xml_parse_result  result = gameStateFile.load_file("savegame.xml");
	if (gameStateFile.child("save_state") == NULL)
		return false;

	pugi::xml_node lm = gameStateFile.child("save_state").child("levelManager");

	gameState =  static_cast<GameState>(lm.attribute("currentLevel").as_int());

	loadLevel = true;
	return true;
}

bool LevelManagement::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node manager = data.append_child("levelManager");

	manager.append_attribute("currentLevel") = gameState;


	return true;
}

bool LevelManagement::CleanUp()
{
	if (currentScene != nullptr)
	{
		currentScene = nullptr;
	}
	return true;
}