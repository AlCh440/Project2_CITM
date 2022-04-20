#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Intro.h"
#include "Map.h"
#include "Physics.h"
#include "player.h"
#include "EnemyDummy.h"

#include "Defs.h"
#include "Log.h"

Intro::Intro(bool isActive) : Module(isActive)
{
	name.Create("intro");
}

// Destructor
Intro::~Intro()
{}

// Called before render is available
bool Intro::Awake()
{
	LOG("Loading Intro Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Intro::Start()
{
	//yes = new EnemyDummy(iPoint(30, 200));

	
	//music2 = app->audio->PlayMusic("assets/audio/music/song_1_2.wav");

	img = app->tex->Load("Assets/Sprites/UI/screen_logo.jpg");
	rect = { 0, 0, 1280, 720 };

	return true;
}

// Called each loop iteration
bool Intro::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Intro::Update(float dt)
{
	
	
	return true;
}

// Called each loop iteration
bool Intro::PostUpdate()
{
	//yes->PostUpdate();

	app->render->DrawTexture(img, 0, 0, &rect);

	return true;
}

// Called before quitting
bool Intro::CleanUp()
{
	LOG("Freeing scene intro");
	active = false;
	img = nullptr;
	return true;
}