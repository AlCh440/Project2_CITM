#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "ModuleFonts.h"
#include "Window.h"
#include "Render.h"
#include "Audio.h"
#include "LevelManagement.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiToggle.h"
#include "GuiPanel.h"




GuiManager::GuiManager(bool isActive) :Module(isActive)
{
	name.Create("guiManager");
}

GuiManager::~GuiManager() {}

bool GuiManager::Start()
{

	mainFont = app->fonts->Load("Assets/GUI/Fonts/Font.png", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", 1);
	mainFont = app->fonts->Load("Assets/GUI/Fonts/numbers.png", "1234567890:", 1);
	UItexture = app->tex->Load("Assets/Spritesx16/GUI.png");

	app->audio->LoadFx("Assets/audio/fx/buttonFocus.wav");
	app->audio->LoadFx("Assets/audio/fx/buttonPressed.wav");
	Debug = false;

	return true;
}

GuiControl* GuiManager::CreateGuiControl(GuiControlType type, int id, const char* text,int fontid, SDL_Rect bounds, Module* observer, SDL_Rect sliderBounds)
{

	GuiControl* control = nullptr;

	//Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, bounds, text, fontid);
		break;
	case GuiControlType::SLIDER:
		control = new GuiSlider(id, bounds, sliderBounds);
		break;
	case GuiControlType::CHECKBOX:
		control = new GuiToggle(id, bounds);
		break;
	
	// More Gui Controls can go here

	default:
		break;
	}

	//Set the observer

	control->SetObserver(observer);
	//control->SetTexture(texture);

	// Created GuiControls are added to the list of controls
	if (control != nullptr) controls.add(control);

	return control;
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

	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}

	}
	return true; 

}

bool GuiManager::Draw() {

	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}

	return true;

}

bool GuiManager::CleanUp()
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;
}
//
//bool GuiManager::OnGuiMouseClickEvent(GuiControl* control)
//{
//	if (control->id == startButton->id)
//	{
//		app->levelManagement->gameState = LevelManagement::SCENE1;
//
//	}
//	else if (control->id == exitButton->id)
//	{
//		app->exit = true;
//	}
//	else if (control->id == settingsButton->id)
//	{
//		settingsPanel->Active = true;
//	}
//	else if (control->id == closePanelBttn->id)
//	{
//		settingsPanel->Active = false;
//	}
//	else if (control->id == vsyncCheckbox->id)
//	{
//		app->render->SetVSYNC(vsyncCheckbox->State);
//	}
//	else if (control->id == fullScreenCheckbox->id)
//	{
//		app->win->SetFullScreen(fullScreenCheckbox->State);
//	}
//	else if (control->id == volumeSlider->id)
//	{
//		app->audio->SetMusicVolume(volumeSlider->id);
//	}
//	else if (control->id == fxSlider->id)
//	{
//		app->audio->SetFxVolume(fxSlider->value);
//	}
//
//
//	return true;
//}
//
//void GuiManager::CreateStartMenu()
//{
//
//	startMenuPanel = new GuiPanel(true);
//	startMenuPanel->bounds = { 0,0,app->win->GetWidth(), app->win->GetWidth()};
//	startMenuPanel->position = {0 ,0 };
//
//	startButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 1, "Start", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) - 75, 170, 60 }, this);
//	startButton->texture = UItexture;
//	startButton->normalRec = { 172,1,170,60 }; 
//
//	settingsButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 2, "Settings", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2), 170, 60 }, this);
//	settingsButton->texture = UItexture;
//	settingsButton->normalRec = { 343,1,170,60 };
//
//	loadButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 3, "Load", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) + 75, 170, 60 }, this);
//	loadButton->texture = UItexture;
//	loadButton->normalRec = { 514,1,170,60 };
//	loadButton->disabledRec = { 514,62,170,60 };
//
//	if (!app->IsASavedGame())
//		loadButton->state = GuiControlState::DISABLED;
//
//	exitButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) + 150, 170, 60 }, this);
//	exitButton->texture = UItexture;
//	exitButton->normalRec = { 172,62,170,60 };
//	exitButton->disabledRec = { 172,62,170,60 };
//}
//
//void GuiManager::CreateSettingsMenu()
//{
//	settingsPanel = new GuiPanel(false);
//	settingsPanel->bounds = { 510,0,266 ,382 };
//	settingsPanel->position = { (app->win->GetWidth() * 40 / 100) ,(app->win->GetWidth() * 5 / 100) };
//	
//	volumeSlider = (GuiSlider*)settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 8, "Volume", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 99), 83, 8 }, this, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 99), 6, 10 });
//	fxSlider = (GuiSlider*)settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 9, "Fx", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 167), 83, 8 }, this, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 167), 6, 10 });
//	vsyncCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 10, "vsync", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 231), 22, 22 }, this);
//	fullScreenCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 11, "fullScreen", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 295), 22, 22 }, this);
//	
//	closePanelBttn = (GuiButton*)settingsPanel->CreateGuiControl(GuiControlType::BUTTON, 7, "Close", 0, { (settingsPanel->position.x + 23), (settingsPanel->position.y + 20), 22, 22 }, this);
//	closePanelBttn->normalRec = { 66,240,22,22 };
//	closePanelBttn->selectedRec = { 66,240,22,22 };
//	closePanelBttn->disabledRec = { 66,240,22,22 };
//	closePanelBttn->focusedRec = { 66,240,22,22 };
//	closePanelBttn->pressedRec = { 66,240,22,22 };
//}
//
//void GuiManager::CreatePauseMenu()
//{
//	pauseMenuPanel = new GuiPanel(false);
//	pauseMenuPanel->bounds = { 510,0,266 ,382 };
//	pauseMenuPanel->position = { (app->win->GetWidth() * 40 / 100) ,(app->win->GetWidth() * 5 / 100) };
//
//	resumeButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 6, "Resume", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2), 170, 60 }, this);
//	resumeButton->texture = UItexture;
//	resumeButton->normalRec = { 343,1,170,60 };
//
//	settingsButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 2, "Settings", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2), 170, 60 }, this);
//	settingsButton->texture = UItexture;
//	settingsButton->normalRec = { 343,1,170,60 };
//
//	backToTitleButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 5, "BackToTile", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2), 170, 60 }, this);
//	backToTitleButton->texture = UItexture;
//	backToTitleButton->normalRec = { 343,1,170,60 };
//
//	exitButton = (GuiButton*)startMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) + 150, 170, 60 }, this);
//	exitButton->texture = UItexture;
//	exitButton->normalRec = { 172,62,170,60 };
//	exitButton->disabledRec = { 172,62,170,60 };
//}
//
//void GuiManager::CreateGameOverMenu()
//{
//	gameOverMenuPanel = new GuiPanel(true);
//	gameOverMenuPanel->bounds = { 0,0,app->win->GetWidth(), app->win->GetWidth() };
//	gameOverMenuPanel->position = { 0 ,0 };
//
//	backToTitleButton = (GuiButton*)gameOverMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 1, "BackToTitle", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) - 75, 170, 60 }, this);
//	backToTitleButton->texture = UItexture;
//	backToTitleButton->normalRec = { 172,1,170,60 };
//
//
//	exitButton = (GuiButton*)gameOverMenuPanel->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) + 150, 170, 60 }, this);
//	exitButton->texture = UItexture;
//	exitButton->normalRec = { 172,62,170,60 };
//	exitButton->disabledRec = { 172,62,170,60 };
//}
//
//void GuiManager::CreateInGameUI()
//{
//}



