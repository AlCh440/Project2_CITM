#include "ShopRoom.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

ShopRoom::ShopRoom(bool isActive) : Module(isActive)
{
	name.Create("Shop_Room");
	toSave = false;
}

ShopRoom::~ShopRoom()
{
}

bool ShopRoom::Awake(pugi::xml_node&)
{
	return true;
}

bool ShopRoom::Start()
{
	app->levelManagement->inCombat = false;
	doorOpen = app->audio->LoadFx("Assets/audio/fx/doorOpening.wav");
	app->audio->PlayFx(doorOpen);
	app->physics->Start();
	bool a = app->map->Load("Shop.tmx");
	LOG("%i", a);
	app->entities->Start();
	app->entities->entranceIntance->scene = GameScene::VILLAGE;
	
	if (app->entities->openWorld != nullptr)
	{
		if (app->loadingScreen == false)
		{
			app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_ShopRoom);
		}
		else
		{
			app->loadingScreen = false;
		}
	}

	return true;
}

bool ShopRoom::PreUpdate()
{
	return true;
}

bool ShopRoom::Update(float dt)
{
	

	return true;
}

bool ShopRoom::PostUpdate()
{
	app->map->Draw();
	
	return true;
}

bool ShopRoom::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
