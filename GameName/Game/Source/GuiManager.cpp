#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"

//add all panels here
#include "QuestPanel.h"
#include "MainMenuPanel.h"
#include "PausePanel.h"
#include "SettingsPanel.h"


GuiManager::GuiManager(bool isActive) :Module(isActive)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{

	UItexture = app->tex->Load("Assets/Sprites/UI/GUI.png");
	UItexture2 = app->tex->Load("Assets/Sprites/UI/GUI2.png");

	app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");
	Debug = false;

	pn_quest = new QuestPanel(true);
	pn_start = new MainMenuPanel(true);
	pn_pause = new PausePanel(true);
	pn_settings = new SettingsPanel(true);

	panels.add(pn_quest);
	panels.add(pn_start);
	panels.add(pn_pause);
	panels.add(pn_settings);

	//init panels
	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr && panel->data->Active)
	{
		panel->data->Start();
		panel = panel->next;
	}


	return true;
}


bool GuiManager::Update(float dt)
{	
	if (app->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		Debug = !Debug;

	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;


	UpdateAll(dt,doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}
	
	return true;
}

bool GuiManager::UpdateAll(float dt, bool doLogic) {

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr && panel->data->Active)
	{
		panel->data->Update( dt, doLogic);
		panel = panel->next;
	}

	return true; 

}

bool GuiManager::PostUpdate() {

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr && panel->data->Active)
	{
		panel->data->Draw();
		panel = panel->next;
	}

	return true;

}

bool GuiManager::CleanUp()
{
	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		panel->data->CleanUp();
		panel = panel->next;
	}

	panels.clear();

	UItexture = nullptr;
	UItexture2 = nullptr;

	return true;
}

bool GuiManager::OnGuiMouseClickEvent(GuiControl* control)
{

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr && panel->data->Active)
	{
		if (control->parent == panel->data)
		{
			panel->data->OnGuiMouseClickEvent(control);
		}
		panel = panel->next;
	}

	return true;
}






