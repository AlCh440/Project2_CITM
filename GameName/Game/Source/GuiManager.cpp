#include "GuiManager.h"
#include "App.h"
#include "Textures.h"
#include "Fonts.h"
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

		p2ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}

	}
	return true; 

}

bool GuiManager::Draw() {

	p2ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}

	return true;

}

bool GuiManager::CleanUp()
{
	p2ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;
}




