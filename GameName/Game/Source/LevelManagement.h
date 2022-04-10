#ifndef __LEVELMANAGEMENT_H__
#define __LEVELMANAGEMENT_H__
#include "Module.h"


#include "App.h"
#include "Scene1.h"
#include "Intro.h"
#include "StartMenu.h"
#include "GameOver.h"
#include "FadeToBlack.h"
#include "Render.h"
#include "Input.h"


#define MAX_SIZE 28
class LevelManagement : public Module
{
public:
	LevelManagement(bool isActive);
	~LevelManagement();
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool CleanUp() override;
	void NextLevel();
	void ReturnToMainMenu();
	void RestartLevel();

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;


	enum GameState {
		NONE = 0,
		INTRO = 1,
		START = 2,
		GAME_OVER = 3,
		SCENE1 = 4,
		THE_FALL = 5,
		GREEN_PATH = 6,
		RUINS = 7,
		VILLAGE = 8,
		FRACTURED_ROAD = 9,
		DRAGRON_CLIFF = 10,
		COMBAT = 11,
		WORLD_TEST = 12
	};

	GameState gameState;
	Module* currentScene = nullptr;
	Module* currentLevel = nullptr;

	int gemCount = 0;
	int frameCounter = 0;
	int delayTime = 100;
	int levelsPassed = 0;
	bool loadLevel = false;

};
#endif // __LEVELMANAGEMENT_H__
