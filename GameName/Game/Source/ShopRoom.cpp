#include "ShopRoom.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

ShopRoom::ShopRoom(bool isActive) : Module(isActive)
{
	name.Create("Mage_Room");
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
	app->physics->Start();
	app->map->Load("Shop.tmx");
	app->entities->Start();
	app->entities->entranceIntance->scene = GameScene::VILLAGE;
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
	return true;
}