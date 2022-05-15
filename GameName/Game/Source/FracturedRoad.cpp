#include "FracturedRoad.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

FracturedRoad::FracturedRoad(bool isActive) : Module(isActive)
{
	name.Create("Fractured_Road");
	toSave = false;
	saveConfigs = false;
}

FracturedRoad::~FracturedRoad()
{
}

bool FracturedRoad::Awake(pugi::xml_node&)
{
	return true;
}

bool FracturedRoad::Start()
{
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);

	app->physics->Start();
	app->map->Load("level5.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::DRAGON_CLIFF;
	app->entities->entranceIntance->scene = GameScene::RUINS;

	return true;
}

bool FracturedRoad::PreUpdate()
{
	return true;
}

bool FracturedRoad::Update(float dt)
{
	return true;
}

bool FracturedRoad::PostUpdate()
{

	app->map->Draw();
	return true;
}

bool FracturedRoad::CleanUp()
{

	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
