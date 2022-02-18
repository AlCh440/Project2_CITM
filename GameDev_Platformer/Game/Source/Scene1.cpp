
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Animation.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene1.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "ModuleEntities.h"
#include "player.h"
#include "Musher.h"
#include "Bat.h"

#include "Defs.h"
#include "Log.h"

Scene1::Scene1(bool isActive) : Module(isActive)
{
	name.Create("level1");
}

// Destructor
Scene1::~Scene1()
{}

// Called before render is available
bool Scene1::Awake()
{
	LOG("Loading Scene 1");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene1::Start()
{
	app->physics->Start();
	app->map->Load("level1.tmx");
	app->audio->PlayMusic("Assets/audio/music/level1.wav");

	app->levelManagement->KeysToTake = 2;

	//Spawn all entities if not load request
	app->entities->Start();


	settingsPanel = new GuiPanel(false);
	settingsPanel->bounds = { 510,0,266 ,382 };
	settingsPanel->position = { (app->win->GetWidth() * 40 / 100) ,(app->win->GetWidth() * 5 / 100) };

	volumeSlider = (GuiSlider*)settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 8, "Volume", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 99), 83, 8 }, this, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 99), 6, 10 });
	volumeSlider->SetValue(app->audio->GetMusicVolume());
	
	fxSlider = (GuiSlider*)settingsPanel->CreateGuiControl(GuiControlType::SLIDER, 9, "Fx", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 167), 83, 8 }, this, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 167), 6, 10 });
	fxSlider->SetValue(app->audio->GetMusicVolume());

	vsyncCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 10, "vsync", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 231), 22, 22 }, this);
	vsyncCheckbox->State = app->render->GetVSYNC();
	
	fullScreenCheckbox = (GuiToggle*)settingsPanel->CreateGuiControl(GuiControlType::CHECKBOX, 11, "fullScreen", 0, { (settingsPanel->position.x + 147), (settingsPanel->position.y + 295), 22, 22 }, this);
	fullScreenCheckbox->State = app->win->GetFullScreen();
	
	closePanelBttn = (GuiButton*)settingsPanel->CreateGuiControl(GuiControlType::BUTTON, 7, "fullScreen", 0, { (settingsPanel->position.x + 23), (settingsPanel->position.y + 20), 22, 22 }, this);
	closePanelBttn->normalRec = { 66,240,22,22 };
	closePanelBttn->selectedRec = { 66,240,22,22 };
	closePanelBttn->disabledRec = { 66,240,22,22 };
	closePanelBttn->focusedRec = { 66,240,22,22 };
	closePanelBttn->pressedRec = { 66,240,22,22 };


	pausePanel = new GuiPanel(false);
	pausePanel->bounds = { 777,0,266 ,382 };
	pausePanel->position = { (app->win->GetWidth() * 40 / 100) ,(app->win->GetWidth() * 5 / 100) };
	
	resumeButton = (GuiButton*)pausePanel->CreateGuiControl(GuiControlType::BUTTON, 6, "Resume", 0, { pausePanel->position.x + 48, pausePanel->position.y + 90,170,60},this);
	resumeButton->texture = app->guiManager->UItexture;
	resumeButton->normalRec = { 170,120,170,60 };
	resumeButton->focusedRec = { 170,180,170,60 };
	
	settingsButton = (GuiButton*)pausePanel->CreateGuiControl(GuiControlType::BUTTON, 2, "stteings", 0, { pausePanel->position.x + 48,pausePanel->position.y + 152,170,60 }, this);;
	settingsButton->texture = app->guiManager->UItexture;
	settingsButton->normalRec = { 340,0,170,60 };
	settingsButton->focusedRec = { 340,60,170,60 };
	
	
	backToTitleButton = (GuiButton*)pausePanel->CreateGuiControl(GuiControlType::BUTTON, 5, "backtotitle", 0, { pausePanel->position.x + 48,pausePanel->position.y + 214,170,60 }, this);;
	backToTitleButton->texture = app->guiManager->UItexture;
	backToTitleButton->normalRec = { 340,120,170,60 };
	backToTitleButton->focusedRec = { 340,180,170,60 };
	
	exitButton = (GuiButton*)pausePanel->CreateGuiControl(GuiControlType::BUTTON, 4, "exit", 0, { pausePanel->position.x + 48,pausePanel->position.y + 276,170,60 }, this);;
	exitButton->texture = app->guiManager->UItexture;
	exitButton->normalRec = { 170,0,170,60 };
	exitButton->focusedRec = { 170,60,170,60 };
	
	closePanelBttn2 = (GuiButton*)settingsPanel->CreateGuiControl(GuiControlType::BUTTON, 7, "fullScreen", 0, { (pausePanel->position.x + 23), (pausePanel->position.y + 20), 22, 22 }, this);
	closePanelBttn2->normalRec = { 66,240,22,22 };
	closePanelBttn2->selectedRec = { 66,240,22,22 };
	closePanelBttn2->disabledRec = { 66,240,22,22 };
	closePanelBttn2->focusedRec = { 66,240,22,22 };
	closePanelBttn2->pressedRec = { 66,240,22,22 };;


	palyerUI = app->tex->Load("Assets/Spritesx16/Sidebar.png");
	timer = 120000;//2min in millis
	app->entities->coinsCollected = 0;


	if (app->levelManagement->loadLevel)
	{
		app->LoadGameRequest();
		app->levelManagement->loadLevel = false;
		app->levelManagement->gameState = app->levelManagement->SCENE1;
		app->levelManagement->currentScene = this;
		return true;
	}



	return true;
}

// Called each loop iteration
bool Scene1::PreUpdate()
{

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		pausePanel->Active = !pausePanel->Active;


	if (app->entities->playerInstance->isGodmodeOn) app->entities->playerInstance->lives = 3;

	return true;
}

// Called each loop iteration
bool Scene1::Update(float dt)
{
    // L02: DONE 3: Request Load / Save when pressing L/S
	if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	if(app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		app->SaveGameRequest();

	if (app->input->GetKey(SDL_SCANCODE_F7) == KEY_DOWN)
	{
		iPoint p;
		p.x = app->entities->checkPoint.getLast()->data->position.x;
		p.y = app->entities->checkPoint.getLast()->data->position.y;

		app->entities->playerInstance->SetPosition(p);
	}

	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
				   app->map->mapData.width, app->map->mapData.height,
				   app->map->mapData.tileWidth, app->map->mapData.tileHeight,
				   app->map->mapData.tilesets.count());

	pausePanel->Update(dt);
	settingsPanel->Update(dt);

	timer -= dt;

	if (timer <= 0)
	{
		app->levelManagement->gameState = app->levelManagement->GameState::GAME_OVER;
	}


	return true;
}

// Called each loop iteration
bool Scene1::PostUpdate()
{
	bool ret = true;

	// Draw functions
	app->map->Draw();
	app->physics->DrawColliders();
	SDL_Rect r = { 0,0,1280,48};

	//background
	app->render->DrawTexture(palyerUI, 0, 0,&r);

	//lives
	r = { 0,262,32,32 };
	int x = 49, y = 4;
	for (int i = 0; i < app->entities->playerInstance->lives; i++)
	{
		app->render->DrawTexture(app->guiManager->UItexture, x + (x*i), y, &r);
	}

	r = {57,262,24,32};
	//coins 
		app->render->DrawTexture(app->guiManager->UItexture,1089 , y, &r);

		std::string s = std::to_string(app->entities->coinsCollected);
		const char* txt = s.c_str(); 
		app->fonts->BlitText(1121, 4, 1, txt);
	//keys
	r = { 33,262,23,32 };
		app->render->DrawTexture(app->guiManager->UItexture, 1177 , y, &r);
		s = std::to_string(app->entities->playerInstance->keysCollected);
		txt = s.c_str(); 
		app->fonts->BlitText(1209, 4, 1, txt);
	//timer 
		int seconds =(int) timer / 1000;
		int min = seconds / 60;
		s = std::to_string(min);
		txt = s.c_str();
		app->fonts->BlitText(987, 4, 1, txt);		
		app->fonts->BlitText(1000, 4, 1, ":");

		s = std::to_string(seconds- (min*60));
		txt = s.c_str();
		app->fonts->BlitText(1019, 4, 1, txt);

	pausePanel->Draw();
	settingsPanel->Draw();



	return ret;
}

// Called before quitting
bool Scene1::CleanUp()
{
	LOG("Disable scene 1");
	app->map->CleanUp();
	app->entities->CleanUp();
	app->physics->CleanUp();
	app->audio->StopMusic();
	return true;
}

void Scene1::Enable()
{
	LOG("Enable scene 1");
	Start();
}

void Scene1::Disable()
{
	LOG("Disable scene 1");
	app->map->CleanUp();
	app->physics->Disable();
	app->entities->Disable();
}

bool Scene1::LoadState(pugi::xml_node& data)
{
	bool ret = true;
	pugi::xml_node level = data.child("level1");
	app->levelManagement->KeysToTake = level.attribute("keys_to_collect").as_int();
	return ret;
}

bool Scene1::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node level = data.append_child("level1");

	level.append_attribute("keys_to_collect") = app->levelManagement->KeysToTake;

	return ret;
}

bool Scene1::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id == resumeButton->id)
	{
		pausePanel->Active = false;

	}
	else if (control->id == backToTitleButton->id)
	{
		app->entities->coinsCollected = 0;
		app->levelManagement->gameState = app->levelManagement->START;
	}
	else if (control->id == exitButton->id)
	{
		app->exit = true;
	}
	else if (control->id == settingsButton->id)
	{
		settingsPanel->Active = true;
		pausePanel->Active = false;
	}
	else if (control->id == closePanelBttn->id)
	{
		settingsPanel->Active = false;
		pausePanel->Active = true;
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


	return true;
}
