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
#include "Dialog.h"


GuiManager::GuiManager(bool isActive) :Module(isActive)
{
	name.Create("gui manager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Awake(pugi::xml_node&)
{
	return true;
}

bool GuiManager::Start()
{

	UItexture = app->tex->Load("Assets/Sprites/UI/GUI.png");
	UItexture2 = app->tex->Load("Assets/Sprites/UI/GUI2.png");

	tex_smallPanel = app->tex->Load("Assets/Sprites/UI/smallPanel.png");
	tex_mediumPanel = app->tex->Load("Assets/Sprites/UI/mediumPanel.png");
	tex_bigPanel = app->tex->Load("Assets/Sprites/UI/bigPanel.png");


	app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");

	Debug = false;

	pn_quest = new QuestPanel(false);
	pn_start = new MainMenuPanel(false);
	pn_pause = new PausePanel(false);
	pn_settings = new SettingsPanel(false);
	pn_dialog = new DialogPanel(false);

	panels.add(pn_quest);
	panels.add(pn_start);
	panels.add(pn_pause);
	panels.add(pn_settings);
	panels.add(pn_dialog);

	//init panels
	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		panel->data->Start();
		panel = panel->next;
	}


	return true;
}


bool GuiManager::Update(float dt)
{	

	if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
		pn_start->Active = !pn_start->GetActive();
	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
		pn_settings->Active = !pn_settings->GetActive();
	if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
		pn_pause->Active = !pn_pause->GetActive();
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		pn_quest->Active = !pn_quest->GetActive();
	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		pn_dialog->Active = !pn_dialog->GetActive();

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

	while (panel != nullptr )
	{
		if(panel->data->Active)
			panel->data->Update( dt, doLogic);
		
		panel = panel->next;
	}

	return true; 

}

bool GuiManager::PostUpdate() {

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		if(panel->data->Active)
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

void GuiManager::OpenPanel(int panel_id)
{
	p2ListItem<GuiPanel*>* panel = panels.start;
	
	while (panel != nullptr)
	{
		if (panel->data->id == panel_id)
		{
			panel->data->Enable();
			break;
		}
		panel = panel->next;
	}
}

//void GuiManager::OpenPanel(GuiState panel)
//{
//	switch (panel)
//	{
//	case MAIN_MENU:
//		pn_start->Enable();
//
//		pn_gameOver->Disable();
//		pn_pause->Disable();
//		pn_quest->Disable();
//		pn_settings->Disable();
//		pn_dialog->Disable();
//		break;
//	case GAME_OVER:
//		pn_gameOver->Enable();
//
//		pn_start->Disable();
//		pn_pause->Disable();
//		pn_quest->Disable();
//		pn_settings->Disable();
//		pn_dialog->Disable();
//		break;
//	case SETTINGS:
//		pn_settings->Enable();
//
//		pn_gameOver->Disable();
//		pn_pause->Disable();
//		pn_quest->Disable();
//		pn_start->Disable();
//		pn_dialog->Disable();
//		break;
//	case PAUSE:
//		pn_pause->Enable();
//
//		pn_start->Disable();
//		pn_gameOver->Disable();		
//		pn_quest->Disable();
//		pn_settings->Disable();
//		pn_dialog->Disable();
//		break;
//	case QUEST:
//		pn_quest->Enable();
//
//		pn_pause->Disable();
//		pn_start->Disable();
//		pn_gameOver->Disable();
//		pn_settings->Disable();
//		pn_dialog->Disable();
//		break;
//	case DIALOG:
//		pn_dialog->Enable();
//
//		pn_pause->Disable();
//		pn_start->Disable();
//		pn_gameOver->Disable();
//		pn_quest->Disable();
//		pn_settings->Disable();
//		break;
//	default:
//		break;
//	}
//
//}

bool GuiManager::OnGuiMouseClickEvent(GuiControl* control)
{

	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		if (control->parent == panel->data && panel->data->Active)
		{
			panel->data->OnGuiMouseClickEvent(control);
		}
		panel = panel->next;
	}

	return true;
}






