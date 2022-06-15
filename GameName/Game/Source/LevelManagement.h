#ifndef __LEVELMANAGEMENT_H__
#define __LEVELMANAGEMENT_H__
#include "Module.h"

#include "App.h"
#include "Intro.h"
#include "StartMenu.h"
#include "GameOver.h"
#include "FadeToBlack.h"
#include "Render.h"
#include "Input.h"

#define MAX_SIZE 28

enum GameScene {
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
	DRAGON_CLIFF = 10,
	COMBAT = 11,
	WORLD_TEST = 12,
	MAGE_ROOM  = 13,
	GENERAL_ROOM = 14,
	SHOP_ROOM = 15,
	PLAIN = 16,
	CASTLE = 17,
	CAVES = 18,
	FINALBATTLE = 19,
	CREDITS = 20
};

class LevelManagement : public Module
{
public:
	LevelManagement(bool isActive);
	~LevelManagement();
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate() ;
	bool Update(float dt) ;
	bool CleanUp();
	void NextLevel();
	void ReturnToMainMenu();
	void RestartLevel();
	void LoadScene(GameScene scene);

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;
	
	GameScene gameScene;
	GameScene lastOpenWorldScene;
	//CombatState combatState = NOCOMBAT;
	Module* currentScene = nullptr;
	Module* currentLevel = nullptr;

	int gemCount = 0;
	int frameCounter = 0;
	int delayTime = 100;
	int levelsPassed = 0;
	bool loadLevel = false;

	iPoint playerLastPos_TheFall;
	iPoint playerLastPos_GreenPath;
	iPoint playerLastPos_Village;
	iPoint playerLastPos_GeneralRoom;
	iPoint playerLastPos_MageRoom;
	iPoint playerLastPos_ShopRoom;
	iPoint playerLastPos_TheRuins;
	iPoint playerLastPos_FracturedRoad;
	iPoint playerLastPos_DragonCliff;

	GameScene combatScene = PLAIN;

	uint music;
	bool playMusic = true;
	bool inCombat = false;
};
#endif // __LEVELMANAGEMENT_H__
