#include "PausePanel.h"
#include "App.h"
#include "GuiManager.h"
PausePanel::PausePanel(bool active) : GuiPanel(active)
{
	Active = active;
}

PausePanel::~PausePanel()
{
}

bool PausePanel::Start()
{

	//TODO add title

	texture = app->guiManager->UItexture2;
	bounds = { 81,414,558,266 };
	position = { 600,0 };
	

	bt_resume = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 50,this->position.y + 50,170,60 }, "Resume", 0, { 255,255,255 });
	bt_resume->texture = app->guiManager->UItexture2;
	bt_resume->normalRec = { 0,0,170,60 };
	bt_resume->focusedRec = { 0,120,170,60 };
	bt_resume->pressedRec = { 0,59,170,60 };


	bt_saveGame = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 50,this->position.y + 125,170,60 }, "Save Game", 0, { 255,255,255 });
	bt_saveGame->texture = app->guiManager->UItexture2;
	bt_saveGame->normalRec = { 0,0,170,60 };
	bt_saveGame->focusedRec = { 0,120,170,60 };
	bt_saveGame->pressedRec = { 0,59,170,60 };


	bt_settings = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 280,this->position.y + 50,170,60 }, "Settings", 0, { 255,255,255 });
	bt_settings->texture = app->guiManager->UItexture2;
	bt_settings->normalRec = { 0,0,170,60 };
	bt_settings->focusedRec = { 0,120,170,60 };
	bt_settings->pressedRec = { 0,59,170,60 };


	bt_menu = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 280,this->position.y + 125,170,60 }, "Main Menu", 0, { 255,255,255 });
	bt_menu->texture = app->guiManager->UItexture2;
	bt_menu->normalRec = { 0,0,170,60 };
	bt_menu->focusedRec = { 0,120,170,60 };
	bt_menu->pressedRec = { 0,59,170,60 };


	bt_quit = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 180,this->position.y + 200,170,60 }, "Quit", 0, { 255,255,255 });
	bt_quit->texture = app->guiManager->UItexture2;
	bt_quit->normalRec = { 0,0,170,60 };
	bt_quit->focusedRec = { 0,120,170,60 };
	bt_quit->pressedRec = { 0,59,170,60 };
	
	return true;
}

bool PausePanel::Update(float dt, bool doLogic)
{

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
	}
	else if (control->id == bt_menu->id)
	{
		//go to main menu
	}
	else if (control->id == bt_quit->id)
	{
		//quit game

	}else if(control->id == bt_saveGame->id)
	{
		//save game
	}

	return true;
}
