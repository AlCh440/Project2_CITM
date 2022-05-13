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

	music = app->audio->PlayMusic("assets/audio/music/village.wav", 0);
	app->physics->Start();
	app->map->Load("level3.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::RUINS;
	app->entities->entranceIntance->scene = GameScene::GREEN_PATH;

	app->entities->generalEntrance->scene= GameScene::GENERAL_ROOM;
	app->entities->mageEntrance->scene = GameScene::MAGE_ROOM;
	app->entities->shopEntrance->scene = GameScene::SHOP_ROOM;

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
