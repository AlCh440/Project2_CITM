#include "LevelManagement.h"
#include "Log.h"
#include "Player.h"
#include "Entities.h"
#include "Map.h"
#include <string>
#include <iostream>
#include "App.h"
#include "Audio.h"
using namespace std;

LevelManagement::LevelManagement(bool isActive) : Module(isActive)
{
	name.Create("Level_manager");
	toSave = true;
	saveConfigs = false;
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

	gameScene = GameScene::INTRO;
	lastOpenWorldScene = gameScene;
	currentScene = nullptr;

	playerLastPos_TheFall = { 16 * 32 + 16, 10 * 32 + 16 };
	playerLastPos_GreenPath = { 11 * 32 + 16, 13 * 32 + 16 };
	playerLastPos_Village = { 17 * 32 + 16, 9 * 32 + 16 };
	playerLastPos_GeneralRoom = { 5 * 32 + 16, 8 * 32 + 16 };
	playerLastPos_MageRoom = { 5 * 32 + 16, 8 * 32 + 16 };
	playerLastPos_ShopRoom = { 5 * 32 + 16, 8 * 32 + 16 };
	playerLastPos_TheRuins = { 72 * 32 + 16, 36 * 32 + 16 };
	playerLastPos_FracturedRoad = { 93 * 32 + 16, 55 * 32 + 16 };
	playerLastPos_DragonCliff = { 24 * 32 + 16, 41 * 32 + 16 };

	return true;
}

bool LevelManagement::PreUpdate()
{

	if ((app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) && currentScene->active == true)
	{
		app->levelManagement->inCombat = false;
		gameScene = lastOpenWorldScene;
	}
	if ((app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) && currentScene->active == true)
	{
		app->levelManagement->inCombat = true;
		gameScene = COMBAT;
	}
	if ((app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) && currentScene->active == true)
	{
		app->levelManagement->inCombat = false;
		gameScene = START;
	}
	

	switch (gameScene)
	{
	case INTRO:

	/*	if ((app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && currentScene->active == true)

		app->audio->PlayMusic("assets/audio/music/song_menu.wav");*/
		playMusic = false;
		if ((app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && currentScene->active == true)
		{
			gameScene = START;
		}
		break;
	case START:
	{

	}
		break;
	case GAME_OVER:
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && currentScene->active == true)
		{
			gameScene = START;
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





//	LOG("%s",currentScene->name.GetString());
	switch (gameScene)
	{
	case INTRO:
		if (currentScene == nullptr){
			currentScene = (Module *)app->intro;
			currentScene->Enable();
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
	case GAME_OVER:

		if (currentScene != (Module*)app->gameOver) {
			if (app->fade->Fade(currentScene, (Module*)app->gameOver, 30))
			{
				currentScene = (Module*)app->gameOver;
				LOG("GAME OVER");
			}
		}
		break;
	case THE_FALL:
		if (currentScene != (Module*)app->theFall) {

			if (app->fade->Fade(currentScene, (Module*)app->theFall, 30))
			{
				currentScene = (Module*)app->theFall;
				lastOpenWorldScene = gameScene;
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
				lastOpenWorldScene = gameScene;
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
				lastOpenWorldScene = gameScene;
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
				lastOpenWorldScene = gameScene;
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
				lastOpenWorldScene = gameScene;
				currentLevel = (Module*)app->fracturedRoad;
				LOG("Fractured road");
			}
		}
		break;
	case DRAGON_CLIFF:
		if (currentScene != (Module*)app->dragonCliff) {

			if (app->fade->Fade(currentScene, (Module*)app->dragonCliff, 30))
			{
				currentScene = (Module*)app->dragonCliff;
				lastOpenWorldScene = gameScene;
				currentLevel = (Module*)app->dragonCliff;
				LOG("Dragon Cliff");
			}
		}
		break;
	case GameScene::GENERAL_ROOM:
		if (currentScene != (Module*)app->generalRoom) {

			if (app->fade->Fade(currentScene, (Module*)app->generalRoom, 30))
			{
				currentScene = (Module*)app->generalRoom;
				lastOpenWorldScene = gameScene;
				currentLevel = (Module*)app->generalRoom;
				LOG("General Room");
			}
		}
		break;
	case GameScene::MAGE_ROOM:
		if (currentScene != (Module*)app->mageRoom) {

			if (app->fade->Fade(currentScene, (Module*)app->mageRoom, 30))
			{
				currentScene = (Module*)app->mageRoom;
				lastOpenWorldScene = gameScene;
				currentLevel = (Module*)app->mageRoom;
				LOG("General Room");
			}
		}
		break;
	case GameScene::SHOP_ROOM:
		if (currentScene != (Module*)app->shopRoom) {

			if (app->fade->Fade(currentScene, (Module*)app->shopRoom, 30))
			{
				currentScene = (Module*)app->shopRoom;
				lastOpenWorldScene = gameScene;
				currentLevel = (Module*)app->shopRoom;
				LOG("General Room");
			}
		}
		break;
	case GameScene::WORLD_TEST:
		if (currentScene != (Module*)app->worldTest) {

			if (app->fade->Fade(currentScene, (Module*)app->worldTest, 30))
			{
				currentScene = (Module*)app->worldTest;
				currentLevel = (Module*)app->worldTest;
				LOG("World Test");
			}
		}
		break;
	case GameScene::COMBAT:
		if (currentScene != (Module*)app->battleTest) {

			if (app->fade->Fade(currentScene, (Module*)app->battleTest, 30))
			{
				currentScene = (Module*)app->battleTest;
				currentLevel = (Module*)app->battleTest;
				LOG("Battle Test");
			}
		}
		break;
	case GameScene::CREDITS:

		
			if (app->fade->Fade(currentScene, (Module*)app->battleTest, 30))
			{
				currentScene = (Module*)app->credits;
				currentLevel = (Module*)app->credits;
				LOG("Credits");
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
	switch (gameScene) {
	case GameScene::SCENE1:
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
	if (gameScene != START)
	{
		gameScene = START;
	}
}

void LevelManagement::RestartLevel()
{
	if (app->entities->playerInstance->stats.hp < 0)
	{
		gameScene = GAME_OVER;
	
		app->fade->Fade(currentScene, (Module*)app->gameOver, 60.0f);
	}
	else {
		app->fade->Fade(currentScene, currentLevel, 60.0f);
	}
}

void LevelManagement::LoadScene(GameScene scene)
{
	if (gameScene != scene) {

		gameScene = scene;
	}
}

bool LevelManagement::LoadState(pugi::xml_node& data)
{

	pugi::xml_node lm = data.child("levelManager");

	gameScene =  static_cast<GameScene>(lm.attribute("currentLevel").as_int());
	
	loadLevel = true;
	return true;
}

bool LevelManagement::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node manager = data.append_child("levelManager");

	manager.append_attribute("currentLevel") = gameScene;


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