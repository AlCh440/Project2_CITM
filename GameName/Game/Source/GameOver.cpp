#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "GameOver.h"
#include "LevelManagement.h"
#include "Physics.h"
#include "player.h"

#include "Defs.h"
#include "Log.h"

GameOver::GameOver(bool isActive) : Module(isActive)
{
	name.Create("game_over");
}

// Destructor
GameOver::~GameOver()
{}

// Called before render is available
bool GameOver::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool GameOver::Start()
{

	return true;
}

// Called each loop iteration
bool GameOver::PreUpdate()
{
	bool ret = true;
	return ret;
}

// Called each loop iteration
bool GameOver::Update(float dt)
{
	return true;
}

// Called each loop iteration
bool GameOver::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool GameOver::CleanUp()
{
	LOG("Freeing scene gameover");
	active = false;
	img = nullptr;
	return true;
}

bool GameOver::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}
