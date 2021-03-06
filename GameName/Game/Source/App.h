#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "p2List.h"
#include "PerfTimer.h"
#include "Timer.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "savegame.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class FadeToBlack;
class Fonts;
class DialogFonts;

class Map;
class ModulePhysics;
class ModuleEntities;
class GuiManager;
class DialogManager;
class LevelManagement;
class QuestManager;
class PathFinding;
class ModuleParticles;

class Intro;
class StartMenu;
class GameOver;
class Scene1;
class TheFall;
class GreenPath;
class TheVillage;
class FracturedRoad;
class TheRuins;
class DragonCliff;

class GeneralRoom;
class MageRoom;
class ShopRoom;
class Credits;

class WorldTestScene;
class BattleTestScene;



class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest();
	bool SaveGameRequest() const;

	bool IsASavedGame();

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;
	bool SaveConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();


	// Load / Save
	bool LoadGame();
	bool SaveGame() const;

public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Map* map;
	ModulePhysics* physics;
	ModuleEntities* entities;
	GuiManager* guiManager;
	DialogManager* dialogManager;
	Fonts* fonts;
	DialogFonts* dialogFonts;
	QuestManager* questManager;
	PathFinding* pathFinding;
	ModuleParticles* particles;

	//scenes
	LevelManagement* levelManagement;
	FadeToBlack* fade;
	Intro* intro;
	StartMenu* start;
	GameOver* gameOver;
	Scene1* scene1;
	TheFall* theFall;
	GreenPath* greenPath;
	TheVillage* village;
	FracturedRoad* fracturedRoad;
	TheRuins* ruins;
	DragonCliff* dragonCliff;

	GeneralRoom* generalRoom;
	MageRoom* mageRoom;
	ShopRoom* shopRoom;
	Credits* credits;

	//test
	WorldTestScene* worldTest;
	BattleTestScene* battleTest;

	float dt;
	bool exit = false;

	bool gamePaused = false;

	void SetPause(bool state)
	{
		gamePaused = state;
	}

	bool GetPause() const
	{
		return gamePaused;
	}


	void FPScap60(bool state)
	{
		FPSCapTo30 = state;
	}


	int RandomRange(int value01, int value02) {

		if (value01 > value02) {

			int i = value01;
			value01 = value02;
			value02 = i;

		}
		return(rand() % (value02 - value01 + 1) + value01);

	}

	float RandomRange(float value01, float value02) {

		if (value01 > value02) {

			float i = value01;
			value01 = value02;
			value02 = i;

		}
		return(rand() / (RAND_MAX / (value02 - value01)) + value01);

	}


	bool loadingScreen = false;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	p2List<Module*> modules;

	uint frames;
	

	mutable bool saveGameRequested;
	bool loadGameRequested;

	PerfTimer ptimer;
	PerfTimer frameDuration;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;
	bool FPSCapTo30 = false;
	float averageFps = 0.0f;

	uint32 maxFrameRate =0;

	bool Debug = false;
};

extern App* app;

#endif	// __APP_H__