#include "GeneralRoom.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

GeneralRoom::GeneralRoom(bool isActive) : Module(isActive)
{
	name.Create("General_Room");
	toSave = false;
}

GeneralRoom::~GeneralRoom()
{
}

bool GeneralRoom::Awake(pugi::xml_node&)
{
	return true;
}

bool GeneralRoom::Start()
{
	app->levelManagement->inCombat = false;
	doorOpen = app->audio->LoadFx("Assets/audio/fx/doorOpening.wav");
	app->audio->PlayFx(doorOpen);
	app->physics->Start();
	app->map->Load("GeneralRoom.tmx");
	app->entities->Start();
	app->entities->entranceIntance->scene = GameScene::VILLAGE;
	if (app->entities->openWorld != nullptr)
	{
		app->entities->openWorld->SetPositionFromPixels(app->levelManagement->playerLastPos_GeneralRoom);
	}

	return true;
}

bool GeneralRoom::PreUpdate()
{
	return true;
}

bool GeneralRoom::Update(float dt)
{
	return true;
}

bool GeneralRoom::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool GeneralRoom::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	//app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
