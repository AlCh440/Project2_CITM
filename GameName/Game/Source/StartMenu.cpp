#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "StartMenu.h"
#include "App.h"
#include "GuiManager.h"
#include "LevelManagement.h"
#include "Fonts.h"
#include "Defs.h"
#include "Log.h"

StartMenu::StartMenu(bool isActive) : Module(isActive)
{
	name.Create("start_menu");
}

// Destructor
StartMenu::~StartMenu()
{}

// Called before render is available
bool StartMenu::Awake()
{
	LOG("Loading Start Scene");
	bool ret = true;
	

	return ret;
}

// Called before the first frame
bool StartMenu::Start()
{
	
	img = app->tex->Load("Assets/Sprites/UI/screen_title.jpg");
	rect = { 0, 0,1280,720};

	music = app->audio->PlayMusic("assets/audio/music/song_menu.wav");
	img = app->tex->Load("Assets/Sprites/UI/StartTitleBackground.jpg");
	rect = { 0, 0,1503,716 };


	app->guiManager->OpenPanel(PanelID::P_START_MENU);

	return true;
}

// Called each loop iteration
bool StartMenu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool StartMenu::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool StartMenu::PostUpdate()
{
	bool ret = true;

	
	app->render->DrawTexture(img, 0, 0,&rect);
	return ret;
}

// Called before quitting
bool StartMenu::CleanUp()
{
	LOG("Freeing scene main menu ");
	img = nullptr;
	app->guiManager->pn_start->Disable();
	return true;
	
}

bool StartMenu::OnGuiMouseClickEvent(GuiControl* control)
{


	return true;
}
