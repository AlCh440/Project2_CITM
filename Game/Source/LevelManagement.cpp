#include "LevelManagement.h"
#include "Log.h"
#include "Player.h"
#include "ModuleEntities.h"
#include "Map.h"
#include <string>
#include <iostream>
using namespace std;

LevelManagement::LevelManagement(bool isActive) : Module(isActive)
{
	name.Create("levelManager");
}

LevelManagement::~LevelManagement()
{
}

bool LevelManagement::Start()
{
	gameState = GameState::INTRO;
	currentScene = (Module*)app->intro;
	return true;
}

bool LevelManagement::PreUpdate()
{

	if ((app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) && currentScene->active == true)
	{
		gameState = SCENE1;
	}
	if ((app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) && currentScene->active == true)
	{
		RestartLevel();
	}
	switch (gameState)
	{
	case INTRO:
		//cout << "Intro\n";
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = START;
		}
		break;
	case START:
		//cout << "Start \n";
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = SCENE1;
		}

		if ((app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) && currentScene->active == true)
		{
			gameState = SCENE2;
		}
		break;
	case SCENE1:
		//cout << "Scene 1 \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = SCENE2;
		}
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && currentScene->active == true)
		{
			RestartLevel();
		}
		break;
	case SCENE2:
		//cout << "Scene 2 \n";
		if (app->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN && currentScene->active == true)
		{
			gameState = GAME_OVER;
		}
		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN && currentScene->active == true)
		{
			RestartLevel();
		}
		break;
	case GAME_OVER:
		//cout << "GAME OVER \n";
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


	switch (gameState)
	{
	case INTRO:
		if (currentScene == nullptr) {
			currentScene = (Module*)app->intro;
			LOG("INTRO");

		}
		else {
			gameState = START;
			app->fade->Fade(currentScene, (Module*)app->intro, 60);
		}
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
	case SCENE1:
		if (currentScene != (Module*)app->scene1) {

			if (app->fade->Fade(currentScene, (Module*)app->scene1, 30))
			{
				currentScene = (Module*)app->scene1;
				currentLevel = (Module*)app->scene1;
				LOG("LEVEL 1");
			}
		}
		break;
	case SCENE2:

		if (currentScene != (Module*)app->scene2)
		{
			if (app->fade->Fade(currentScene, (Module*)app->scene2, 30))
			{
				currentScene = (Module*)app->scene2;
				currentLevel = (Module*)app->scene2;
				LOG("LEVEL 2");
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
		gameState = SCENE2;
		break;
	case GameState::SCENE2:
		if (levelsPassed < 2) {
			levelsPassed++;
		}
		gameState = START;
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
	if (app->entities->playerInstance->state == PlayerState::DEAD)
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

	if (gameState == SCENE1)
	{
		app->fade->Fade(currentScene, app->scene1, 60.0f);
	}
	else if (gameState == SCENE2) {
		app->fade->Fade(currentScene, app->scene2, 60.0f);
	}
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