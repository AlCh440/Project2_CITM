#include "GreenPath.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

GreenPath::GreenPath(bool isActive) : Module(isActive)
{
	name.Create("Green_path");
	toSave = false;
	saveConfigs = false;
}

GreenPath::~GreenPath()
{
}

bool GreenPath::Awake(pugi::xml_node&)
{
	return true;
}

bool GreenPath::Start()
{
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);
	app->physics->Start();
	app->map->Load("level2.tmx");
	app->entities->Start();
	app->entities->exitIntance->scene = GameScene::VILLAGE;
	app->entities->entranceIntance->scene = GameScene::THE_FALL;
	return true;
}

bool GreenPath::PreUpdate()
{
	return true;
}

bool GreenPath::Update(float dt)
{
	return true;
}

bool GreenPath::PostUpdate()
{
	app->map->Draw();
	return true;
}

bool GreenPath::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}
