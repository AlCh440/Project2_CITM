#include "MainMenuPanel.h"
#include "Log.h"
#include "App.h"
#include "GuiManager.h"
#include "LevelManagement.h"
#include "Audio.h"
#include "QuestManager.h"


MainMenuPanel::MainMenuPanel(bool active) : GuiPanel(active) 
{
    Active = active;
    id = PanelID::P_START_MENU;
}

MainMenuPanel::~MainMenuPanel()
{
}

bool MainMenuPanel::Start()
{
    //TODO add title

    texture = app->guiManager->tex_mediumPanel;
    bounds = { 0,0,1280,720 };
    position = { 0,0 };

    bt_newGame = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 555 ,this->position.y + 190,170,60 }, "New Game", app->fonts->menuButtonFont, app->fonts->c_Menus);
    bt_newGame->texture = app->guiManager->UItexture2;
    bt_newGame->normalRec = { 0,0,170,60 };
    bt_newGame->focusedRec = { 0,120,170,60 };
    bt_newGame->pressedRec = { 0,59,170,60 };

    bt_loadGame = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { this->position.x + 555, this->position.y + 280, 170,60 }, "Load Game", app->fonts->menuButtonFont, app->fonts->c_Menus);
    bt_loadGame->texture = app->guiManager->UItexture2;
    bt_loadGame->normalRec = { 0,0,170,60 };
    bt_loadGame->focusedRec = { 0,120,170,60 };
    bt_loadGame->pressedRec = { 0,59,170,60 };


    bt_settings = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { this->position.x + 555, this->position.y + 370, 170,60 }, "Settings", app->fonts->menuButtonFont, app->fonts->c_Menus);
    bt_settings->texture = app->guiManager->UItexture2;
    bt_settings->normalRec = { 0,0,170,60 };
    bt_settings->focusedRec = { 0,120,170,60 };
    bt_settings->pressedRec = { 0,59,170,60 };

    bt_quit = (GuiButton*)CreateGuiButton(3, app->guiManager, this, { this->position.x + 555, this->position.y + 460, 170,60 }, "Quit", app->fonts->menuButtonFont, app->fonts->c_Menus);
    bt_quit->texture = app->guiManager->UItexture2;
    bt_quit->normalRec = { 0,0,170,60 };
    bt_quit->focusedRec = { 0,120,170,60 };
    bt_quit->pressedRec = { 0,59,170,60 };

    return true;
}

bool MainMenuPanel::Update(float dt, bool doLogic)
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
        app->audio->StopMusic();
        app->levelManagement->gameScene = GameScene::THE_FALL;
        app->questManager->ActivateQuest(0);
        app->gamePaused = false;
        app->guiManager->OnPause(false);
    }
    else if (control->id == bt_loadGame->id)
    {
        //load Game
        app->LoadGameRequest();
        app->gamePaused = false;
        app->guiManager->OnPause(false); 
    }
    else if (control->id == bt_settings->id)
    {
        app->guiManager->OpenPanel(PanelID::P_SETTINGS);
    }
    else if (control->id == bt_quit->id)
    {
        //close game
        app->exit = true;
    }

    return true;
}
