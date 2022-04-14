#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Physics.h"
#include "Fonts.h"
#include "Map.h"
#include "Entities.h"
#include "GuiManager.h"
#include "Brofiler/include/optick.h"
#include "LevelManagement.h"
#include "FadeToBlack.h"
#include "QuestManager.h"
#include "Pathfinding.h"
//Scenes 
#include "Intro.h"
#include "StartMenu.h"
#include "GameOver.h"
#include "TheFall.h"
#include "GreenPath.h"
#include "TheVillage.h"
#include "TheRuins.h"
#include "FracturedRoad.h"
#include "DragonCliff.h"

#include "BattleTestScene.h"
#include "WorldTestScene.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;

	//utils
	win = new Window(true);
	input = new Input(true);
	render = new Render(true);
	tex = new Textures(true);
	audio = new Audio(true);
	fonts = new Fonts(true);
	fade = new FadeToBlack(true);
	questManager = new QuestManager(true);
	pathFinding = new PathFinding(true);

	//systems
	map = new Map(true);
	physics = new ModulePhysics(true);
	entities = new ModuleEntities(true);
	levelManagement = new LevelManagement(true);
	guiManager = new GuiManager(true);

	//Scenes
	intro = new Intro(false);
	start = new StartMenu(false);
	gameOver = new GameOver(false);
	theFall = new TheFall(false);
	greenPath = new GreenPath(false);
	village = new TheVillage(false);
	fracturedRoad = new FracturedRoad(false);
	ruins = new TheRuins(false);
	dragonCliff = new DragonCliff(false);

	//test
	worldTest = new WorldTestScene(false);
	battleTest = new BattleTestScene(false);


	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(audio);
	AddModule(fonts);
	AddModule(pathFinding);
	AddModule(fade);
	AddModule(levelManagement);
	AddModule(map);
	AddModule(physics);
	AddModule(questManager);
	
	AddModule(intro);
	AddModule(start);
	AddModule(gameOver);
	AddModule(theFall);
	AddModule(greenPath);
	AddModule(village);
	AddModule(fracturedRoad);
	AddModule(ruins);
    AddModule(dragonCliff);

	AddModule(battleTest);
	AddModule(worldTest);

	AddModule(guiManager);

	AddModule(entities);

	// Render last to swap buffer
	AddModule(render);

}

// Destructor
App::~App()
{
	// Release modules
	p2ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.add(module);
}

// Called before render is available
bool App::Awake()
{
	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	bool ret = false;

	// L01: DONE 3: Load config from XML
	config = LoadConfig(configFile);

	if (config.empty() == false)
	{
		ret = true;
		configApp = config.child("app");

		// L01: DONE 4: Read the title from the config file
		title.Create(configApp.child("title").child_value());
		organization.Create(configApp.child("organization").child_value());
	}

	if (ret == true)
	{
		p2ListItem<Module*>* item;
		item = modules.start;

		while ((item != NULL) && (ret == true))
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool App::Start()
{
	bool ret = true;

	startupTime.Start();
	lastSecFrameTime.Start();

	p2ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{

		if(item->data->active)
			ret = item->data->Start();

		LOG("Module Stared %s", item->data->name.GetString());

		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;
	
	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();
	
	FinishUpdate();

	if (input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Load config from XML file
// NOTE: Function has been redesigned to avoid storing additional variables on the class
pugi::xml_node App::LoadConfig(pugi::xml_document& configFile) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL) LOG("Could not load xml file: %s. pugi error: %s", CONFIG_FILENAME, result.description());
	else ret = configFile.child("config");



	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;
	dt = frameDuration.ReadMs();
	frameDuration.Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	

	// L02: DONE 1: This is a good place to call Load / Save methods
	if (loadGameRequested == true) LoadGame();
	if (saveGameRequested == true) SaveGame();

	float secondsSinceStartup = startupTime.ReadSec();

	if (lastSecFrameTime.Read() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		averageFps = (averageFps + framesPerSecond) / 2;
	}



	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f FPS: %i Delta Time: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);

	if (input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
		FPSCapTo30 = !FPSCapTo30;

	if (FPSCapTo30)
		maxFrameRate = 30;
	else
		maxFrameRate = 60;


	float delay =  float(1000 / maxFrameRate) - frameDuration.ReadMs();



	PerfTimer* delayt = new PerfTimer();
	delayt->Start();
	if (maxFrameRate > 0 && delay > 0) SDL_Delay(delay);


	app->win->SetTitle(title);
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	p2ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;


		if (input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
			item->data->DEBUG = !item->data->DEBUG;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PreUpdate();
	}
	if (exit)
		ret = false;

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate()
{
	bool ret = true;
	PERF_START(ptimer);
	p2ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}
	//PERF_PEEK(ptimer);
	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	p2ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}


	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	p2ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void App::LoadGameRequest()
{
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result  result = gameStateFile.load_file("savegame.xml");

	if (gameStateFile.child("save_state") == NULL)
		ret = false;

	loadGameRequested = ret;
}

// ---------------------------------------
void App::SaveGameRequest() const
{
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result  result = gameStateFile.load_file("savegame.xml");

	if (gameStateFile.child("save_state") == NULL)
	{
		//if no game saved we create a new one 
		gameStateFile.append_child("save_state");
	}else{
		//do we want to override the saved game?
	}
	
	
	saveGameRequested = ret;
}

bool App::IsASavedGame()
{
	bool ret = true;
	pugi::xml_document gameStateFile;
	pugi::xml_parse_result  result = gameStateFile.load_file("savegame.xml");

	if (gameStateFile.child("save_state") == NULL)
		ret = false;

	return ret;
}

// call all the modules to load themselves
bool App::LoadGame()
{
	bool ret = true;

	pugi::xml_document gameStateFile;
	pugi::xml_parse_result  result = gameStateFile.load_file("savegame.xml");
	
	if (result == NULL)
	{
		LOG("Could not load xml file savegame.xml. pugi error: %s", result.description());
		ret = false;
	}
	else {
		p2ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL)
		{
			ret = item->data->LoadState(gameStateFile.child("save_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	loadGameRequested = false;

	LOG("Game Loaded...");

	return ret;
}

// xml save method for current state
bool App::SaveGame() const
{
	bool ret = true;

	pugi::xml_document* saveDoc = new pugi::xml_document();
	pugi::xml_node  saveStateNode = saveDoc->append_child("save_state");

	p2ListItem<Module*>* item;
	item = modules.start;

	while (item != NULL)
	{
		if (ret != item->data->SaveState(saveStateNode.append_child(item->data->name.GetString())))
			LOG("could not save status of %s", item->data->name.GetString());
		item = item->next;
	}

	if (ret != saveDoc->save_file("savegame.xml"))
		LOG("Could not save savegame file....");

	saveGameRequested = false;

	LOG("Game Saved...");

	return ret;
}



