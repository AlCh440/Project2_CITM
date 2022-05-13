#include "TheRuins.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

TheRuins::TheRuins(bool isActive) : Module(isActive)
{
	name.Create("The_Ruins");
	toSave = false;
	saveConfigs = false;
}

TheRuins::~TheRuins()
{
}

bool TheRuins::Awake(pugi::xml_node&)
{
	return true;
}

bool TheRuins::Start()
{
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);

	app->physics->Start();
	app->map->Load("level4.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::FRACTURED_ROAD;
	app->entities->entranceIntance->scene = GameScene::VILLAGE;
	
	
	return true;
}

bool TheRuins::PreUpdate()
{
	return true;
}

bool TheRuins::Update(float dt)
{
	return true;
}

bool TheRuins::PostUpdate()
{
	app->map->Draw();
	
	
	return true;
}

bool TheRuins::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->StopMusic();

	return true;
}
