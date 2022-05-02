#include "TheFall.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"


TheFall::TheFall(bool isActive) : Module(isActive)
{
	name.Create("The_fall");
	toSave = false;
}

TheFall::~TheFall()
{
}

bool TheFall::Awake(pugi::xml_node&)
{
	return true;
}

bool TheFall::Start()
{
	music = app->audio->PlayMusic("assets/audio/music/song_1_2.wav", 0);

	app->physics->Start();
	app->map->Load("level1.tmx");
	app->entities->Start();
	
	app->entities->exitIntance->scene = GameScene::GREEN_PATH;

	
	return true;
}

bool TheFall::PreUpdate()
{
	return true;
}

bool TheFall::Update(float dt)
{

	

	return true;
}

bool TheFall::PostUpdate()
{
	app->map->Draw();
	
	return true;
}

bool TheFall::CleanUp()
{
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}

