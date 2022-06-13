#include "DragonCliff.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

DragonCliff::DragonCliff(bool isActive) : Module(isActive)
{
	name.Create("Dragon's_cliff");
	toSave = false;
	saveConfigs = false;
}

DragonCliff::~DragonCliff()
{
}

bool DragonCliff::Awake(pugi::xml_node&)
{
	return true;
}

bool DragonCliff::Start()
{
	img = app->tex->Load("Assets/Maps/dragoncliff_bg.png");
	app->levelManagement->inCombat = false;
	app->physics->Start();
	app->map->Load("level6.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::START;
	app->entities->entranceIntance->scene = GameScene::FRACTURED_ROAD;

	if (app->entities->openWorld != nullptr)
	{
		if (app->loadingScreen == false)
		{
			app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_DragonCliff);
		}
		else
		{
			app->loadingScreen = false;
		}
	}
	return true;
}

bool DragonCliff::PreUpdate()
{
	return true;
}

bool DragonCliff::Update(float dt)
{
	return true;
}

bool DragonCliff::PostUpdate()
{
	SDL_Rect r = { 0,0,1600,670 };
	app->render->DrawTexture(img, 0, 0, &r, 0.8f);
	app->map->Draw();
	return true;
}

bool DragonCliff::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
