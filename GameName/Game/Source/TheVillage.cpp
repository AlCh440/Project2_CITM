#include "TheVillage.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

TheVillage::TheVillage(bool isActive) : Module(isActive)
{
	name.Create("The_Village");
	toSave = false;
}

TheVillage::~TheVillage()
{
}

bool TheVillage::Awake(pugi::xml_node&)
{
	return true;
}

bool TheVillage::Start()
{
	app->physics->Start();
	app->map->Load("level3.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::START;
	app->entities->entranceIntance->scene = GameScene::GREEN_PATH;

	return true;
}

bool TheVillage::PreUpdate()
{
	return true;
}

bool TheVillage::Update(float dt)
{
	return true;
}

bool TheVillage::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool TheVillage::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
