#include "MageRoom.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

MageRoom::MageRoom(bool isActive) : Module(isActive)
{
	name.Create("Mage_Room");
	toSave = false;
}

MageRoom::~MageRoom()
{
}

bool MageRoom::Awake(pugi::xml_node&)
{
	return true;
}

bool MageRoom::Start()
{
	app->levelManagement->inCombat = false;
	doorOpen = app->audio->LoadFx("Assets/audio/fx/doorOpening.wav");
	app->audio->PlayFx(doorOpen);
	app->physics->Start();
	app->map->Load("ArchmageRoom.tmx");
	app->entities->Start();
	app->entities->entranceIntance->scene = GameScene::VILLAGE;

	if (app->entities->openWorld != nullptr)
	{
		if (app->loadingScreen == false)
		{
			app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_MageRoom);
		}
		else
		{
			app->loadingScreen = false;
		}
	}
	return true;
}

bool MageRoom::PreUpdate()
{
	return true;
}

bool MageRoom::Update(float dt)
{
	return true;
}

bool MageRoom::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool MageRoom::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
