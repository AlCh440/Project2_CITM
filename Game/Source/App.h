#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "List.h"
#include "PerfTimer.h"
#include "Timer.h"
#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class LevelManagement;
class FadeToBlack;
class Intro;
class StartMenu;
class Scene1;
class Scene2;
class GameOver;
class Map;
class ModulePhysics;
class ModuleEntities;
class GuiManager;
class ModuleFonts;


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
	void SaveGameRequest() const;

	bool IsASavedGame();

private:

	// Load config file
	// NOTE: It receives config document
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

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
	LevelManagement* levelManagement;
	FadeToBlack* fade;
	Intro* intro;
	StartMenu* start;
	Scene1* scene1;
	Scene2* scene2;
	GameOver* gameOver;
	Map* map;
	ModulePhysics* physics;
	ModuleEntities* entities;
	GuiManager* guiManager;
	ModuleFonts* fonts;
	
	float dt;
	bool exit = false;

private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

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
};

extern App* app;

#endif	// __APP_H__