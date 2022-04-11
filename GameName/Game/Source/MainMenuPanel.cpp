#include "MainMenuPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"

MainMenuPanel::MainMenuPanel(bool active) : GuiPanel(active) 
{
    Active = active;
}

MainMenuPanel::~MainMenuPanel()
{
}

bool MainMenuPanel::Start()
{
    //TODO add title

    texture = app->guiManager->UItexture2;
    bounds = { 81,414,558,266 };
    position = { 0,0 };

    bt_newGame = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 50 ,this->position.y + 50,170,60 }, "New Game", 0, { 255,255,255 });
    bt_newGame->texture = app->guiManager->UItexture2;
    bt_newGame->normalRec = { 0,0,170,60 };
    bt_newGame->focusedRec = { 0,120,170,60 };
    bt_newGame->pressedRec = { 0,59,170,60 };

    bt_loadGame = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { this->position.x + 50, this->position.y + 170, 170,60 }, "Load Game", 0, { 255,255,255 });
    bt_loadGame->texture = app->guiManager->UItexture2;
    bt_loadGame->normalRec = { 0,0,170,60 };
    bt_loadGame->focusedRec = { 0,120,170,60 };
    bt_loadGame->pressedRec = { 0,59,170,60 };


    bt_settings = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { this->position.x + 280, this->position.y + 50, 170,60 }, "Settings", 0, { 255,255,255 });
    bt_settings->texture = app->guiManager->UItexture2;
    bt_settings->normalRec = { 0,0,170,60 };
    bt_settings->focusedRec = { 0,120,170,60 };
    bt_settings->pressedRec = { 0,59,170,60 };

    bt_quit = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { this->position.x + 280, this->position.y + 170, 170,60 }, "Quit", 0, { 255,255,255 });
    bt_quit->texture = app->guiManager->UItexture2;
    bt_quit->normalRec = { 0,0,170,60 };
    bt_quit->focusedRec = { 0,120,170,60 };
    bt_quit->pressedRec = { 0,59,170,60 };

    return true;
}

bool MainMenuPanel::Update(float dt, bool doLogic)
{
    GuiPanel::Update(dt, doLogic);
    return true;
}

bool MainMenuPanel::Draw()
{
    GuiPanel::Draw();
    return true;
}

bool MainMenuPanel::CleanUp()
{
    return true;
}

bool MainMenuPanel::OnGuiMouseClickEvent(GuiControl* control)
{
    if(control->id == bt_newGame->id)
    {
        //start new game
    }
    else if (control->id == bt_loadGame->id)
    {
        //load Game
    }
    else if (control->id == bt_settings->id)
    {
        //open settings menu
    }
    else if (control->id == bt_quit->id)
    {
        //close game
    }

    return true;
}
