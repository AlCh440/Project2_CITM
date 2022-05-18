#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"
#include "Entities.h"

//add all panels here
#include "QuestPanel.h"
#include "MainMenuPanel.h"
#include "PausePanel.h"
#include "SettingsPanel.h"
#include "BattlePanel.h"
#include "InventoryPanel.h"
#include "MatchResultPanel.h"


GuiManager::GuiManager(bool isActive) :Module(isActive)
{
	name.Create("gui_manager");
	toSave = false;
	saveConfigs = false;
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

	tex_inventory = app->tex->Load("Assets/Sprites/UI/inventory.png");
	tex_inventory_tabs = app->tex->Load("Assets/Sprites/UI/inventoryTabs.png");

	app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");
	inventorySound = app->audio->LoadFx("Assets/audio/fx/openInventory.wav");

	Debug = false;

	//add more UI panels here

	pn_quest = new QuestPanel(false);
	pn_start = new MainMenuPanel(false);
	pn_pause = new PausePanel(false);
	pn_settings = new SettingsPanel(false);
	pn_battle = battlePanelInstance = new BattlePanel(false);
	pn_inventory = new InventoryPanel(false);
	pn_matchResult = new MatchResultPanel(false);

	panels.add(pn_quest);
	panels.add(pn_start);
	panels.add(pn_pause);
	panels.add(pn_settings);
	panels.add(pn_battle);
	panels.add(pn_inventory);
	panels.add(pn_matchResult);

	//init panels
	p2ListItem<GuiPanel*>* panel = panels.start;

	while (panel != nullptr)
	{
		panel->data->Start();
		panel = panel->next;
	}


	return true;
}

bool GuiManager::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		pn_quest->Active = !pn_quest->GetActive();

	if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		pn_inventory->Active = !pn_inventory->GetActive();
		app->audio->PlayFx(inventorySound);
	}
	    
	if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
	{
		OpenPanel(P_MATCH_RESULT);
		app->audio->PlayFx(inventorySound);
	}

	if (app->input)
	Debug = DEBUG;


	return true;
}


bool GuiManager::Update(float dt)
{	

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

void GuiManager::OnPause(bool paused)
{
	if (app->gamePaused)
	{
		pn_pause->Enable();
		app->entities->Pause = true;
		app->physics->Pause = true;
	}
	else
	{
		pn_pause->Disable();
		app->entities->Pause = false;
		app->physics->Pause = false;
	}
}

void GuiManager::OpenPanel(PanelID panel_id)
{
	p2ListItem<GuiPanel*>* panel = panels.start;
	
	while (panel != nullptr)
	{

		if (panel->data->Active == true)
		{
			panel->data->Disable();
			lastPanel = panel->data->id;
		}

		if (panel->data->id == panel_id)
		{
			panel->data->Enable();
			currentPanel = panel->data->id;
		}
		panel = panel->next;
	}
}

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





