#include "PausePanel.h"
#include "App.h"
#include "GuiManager.h"
#include "LevelManagement.h"
#include "Window.h"

PausePanel::PausePanel(bool active) : GuiPanel(active)
{
	Active = active;
	id = PanelID::P_PAUSE;
}

PausePanel::~PausePanel()
{
}

bool PausePanel::Start()
{
	texture = app->guiManager->tex_smallPanel;
	bounds = { 0,0,1280,720 };
	position = { 0,0 };
	

	title = app->fonts->LoadRenderedText(r_title, app->fonts->titles, "Pause", app->fonts->c_Menus);

	bt_resume = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 555,this->position.y + 150,170,60 }, "Resume", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_resume->texture = app->guiManager->UItexture2;
	bt_resume->normalRec = { 0,0,170,60 };
	bt_resume->focusedRec = { 0,120,170,60 };
	bt_resume->pressedRec = { 0,59,170,60 };


	bt_saveGame = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { this->position.x + 555,this->position.y + 240,170,60 }, "Save Game", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_saveGame->texture = app->guiManager->UItexture2;
	bt_saveGame->normalRec = { 0,0,170,60 };
	bt_saveGame->focusedRec = { 0,120,170,60 };
	bt_saveGame->pressedRec = { 0,59,170,60 };


	bt_settings = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { this->position.x + 555,this->position.y + 330,170,60 }, "Settings", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_settings->texture = app->guiManager->UItexture2;
	bt_settings->normalRec = { 0,0,170,60 };
	bt_settings->focusedRec = { 0,120,170,60 };
	bt_settings->pressedRec = { 0,59,170,60 };


	bt_menu = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { this->position.x + 555,this->position.y + 410,170,60 }, "Main Menu", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_menu->texture = app->guiManager->UItexture2;
	bt_menu->normalRec = { 0,0,170,60 };
	bt_menu->focusedRec = { 0,120,170,60 };
	bt_menu->pressedRec = { 0,59,170,60 };


	bt_quit = (GuiButton*)CreateGuiButton(4, app->guiManager, this, { this->position.x + 555,this->position.y + 500 ,170,60 }, "Quit", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_quit->texture = app->guiManager->UItexture2;
	bt_quit->normalRec = { 0,0,170,60 };
	bt_quit->focusedRec = { 0,120,170,60 };
	bt_quit->pressedRec = { 0,59,170,60 };
	
	return true;
}

bool PausePanel::Update(float dt, bool doLogic)
{
	if (counter < easingTime)
	{

		auto easingFunction = getEasingFunction(EaseOutBounce);
		double progress = easingFunction(UpdateProgress(counter, 0, 100, 0, 1));
		easePosY = (int)UpdateProgress(progress, 0, 1, -100, 0);
		position.y = easePosY;
		counter++;
	}
	GuiPanel::Update(dt, doLogic);
	return true;
}

bool PausePanel::Draw()
{
	GuiPanel::Draw();
	return true;
}

bool PausePanel::CleanUp()
{
	return true;
}

bool PausePanel::OnGuiMouseClickEvent(GuiControl* control)
{

	if (control->id == bt_resume->id)
	{
		//resume game
		app->gamePaused = false;
		app->guiManager->OnPause(false);
	}
	else if (control->id == bt_menu->id)
	{
		app->levelManagement->gameScene = START;
	}
	else if (control->id == bt_quit->id)
	{
		app->exit = true;

	}else if(control->id == bt_saveGame->id)
	{
		//save game
		app->SaveGameRequest();
	}
	else if (control->id == bt_settings->id)
	{
		app->guiManager->OpenPanel(PanelID::P_SETTINGS);
	}

	return true;
}
