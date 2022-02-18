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
#include "ModuleFonts.h"
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
	img = app->tex->Load("Assets/Spritesx16/StartTitle.png");

	SDL_Rect r;
	r.w = 160;
	r.h = 40;

	r.x = (app->win->GetWidth() / 2);
	r.y = (app->win->GetHeight() / 2); 
	
	menuPanel = new GuiPanel(true);
	menuPanel->bounds = { 0,0,0,0};
	menuPanel->position = { 0,0 };
	startButton = (GuiButton*)menuPanel->CreateGuiControl(GuiControlType::BUTTON, 1, "Start",0, { (app->win->GetWidth() / 2)-85 , (app->win->GetHeight() / 2) - 75, 170, 60 }, this);
	startButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png"); //load background button texture
	startButton->normalRec = { 0,0,170,60 }; // set background rect
	startButton->focusedRec = { 0,59,170,60 };

	settingsButton = (GuiButton*)menuPanel->CreateGuiControl(GuiControlType::BUTTON, 2, "Settings",0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2), 170, 60 }, this);
	settingsButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png");
	settingsButton->normalRec = { 340,0,170,60 };
	settingsButton->focusedRec = { 340,60,170,60 };

	loadButton = (GuiButton*)menuPanel->CreateGuiControl(GuiControlType::BUTTON, 3, "Load",0, { (app->win->GetWidth() / 2)-85 , (app->win->GetHeight() / 2) + 75, 170, 60 }, this);
	loadButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png");
	loadButton->normalRec = { 0,120,170,60 };
	loadButton->focusedRec = { 0,180,170,60 };

	if (!app->IsASavedGame())
		loadButton->state = GuiControlState::DISABLED;

	exitButton = (GuiButton*)menuPanel->CreateGuiControl(GuiControlType::BUTTON, 4, "Exit", 0, { (app->win->GetWidth() / 2) - 85 , (app->win->GetHeight() / 2) + 150, 170, 60 }, this);
	exitButton->texture = app->tex->Load("Assets/Spritesx16/GUI.png");
	exitButton->normalRec = { 170,0,170,60 };
	exitButton->focusedRec = { 170,60,170,60 };


	settingsPanel = new GuiPanel(false);
	settingsPanel->bounds = {510,0,266 ,382};
	settingsPanel->position = { (app->win->GetWidth() *40 /100) ,(app->win->GetWidth() *5 / 100) };

	volumeSlider = (GuiSlider*)settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 8, "Volume", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 99), 83, 8 }, this, { (settingsPanel->position.x + 83 + 147), (settingsPanel->position.y + 99), 6, 10 });
	volumeSlider->SetValue(app->audio->GetMusicVolume());

	fxSlider = (GuiSlider*)settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 9, "Fx", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 167), 83, 8 }, this, { (settingsPanel->position.x + 83 + 147), (settingsPanel->position.y + 167), 6, 10 });
	fxSlider->SetValue(app->audio->GetMusicVolume());

	vsyncCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 10, "vsync", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 231), 22, 22 }, this);
	vsyncCheckbox->State = app->render->GetVSYNC();

	fullScreenCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 11, "fullScreen", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 295), 22, 22 }, this);
	fullScreenCheckbox->State = app->win->GetFullScreen();
	

	closePanelBttn = (GuiButton*)settingsPanel->CreateGuiControl(GuiControlType::BUTTON, 7, "close", 0, { (settingsPanel->position.x + 23), (settingsPanel->position.y + 20), 22, 22 }, this);
	closePanelBttn->normalRec = { 66,240,22,22 };
	closePanelBttn->selectedRec = { 66,240,22,22 };
	closePanelBttn->disabledRec = { 66,240,22,22 };
	closePanelBttn->focusedRec = { 66,240,22,22 };
	closePanelBttn->pressedRec = { 66,240,22,22 };

	return true;
}

// Called each loop iteration
bool StartMenu::PreUpdate()
{
	settingsPanel->PreUpdate();
	menuPanel->PreUpdate();
	return true;
}

// Called each loop iteration
bool StartMenu::Update(float dt)
{
	settingsPanel->Update(dt);
	menuPanel->Update(dt);
	return true;
}

// Called each loop iteration
bool StartMenu::PostUpdate()
{
	bool ret = true;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1280;
	rect.h = 480;
	if (img != nullptr && active)
		app->render->DrawTexture(img, 0, 0, &rect, 1.0f, 0.0f, 1, 1, 1, SDL_FLIP_NONE);
	//Draw GUI
	settingsPanel->Draw();
	menuPanel->Draw();

	return ret;
}

// Called before quitting
bool StartMenu::CleanUp()
{
	LOG("Freeing scene main menu ");
	img = nullptr;

	return true;
}

bool StartMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id == startButton->id)
	{
		app->levelManagement->gameState = LevelManagement::SCENE1;
		app->levelManagement->loadLevel = false;

	}
	else if (control->id == exitButton->id)
	{
		app->exit = true;
	}
	else if (control->id == settingsButton->id)
	{
		settingsPanel->Active = true;
		menuPanel->Active = false;
	}
	else if (control->id == closePanelBttn->id)
	{
		settingsPanel->Active = false;
		menuPanel->Active = true;
	}
	else if (control->id == vsyncCheckbox->id)
	{
		app->render->SetVSYNC(vsyncCheckbox->State);
	}
	else if (control->id == fullScreenCheckbox->id)
	{
		app->win->SetFullScreen(fullScreenCheckbox->State);
	}
	else if (control->id == volumeSlider->id)
	{
		app->audio->SetMusicVolume(volumeSlider->value);
	}
	else if (control->id == fxSlider->id)
	{
		app->audio->SetFxVolume(fxSlider->value);
	}
	else if (control->id == loadButton->id)
	{
		app->levelManagement->gameState = LevelManagement::SCENE1;
		app->levelManagement->loadLevel = true;
	}


	return true;
}
