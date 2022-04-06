#include "MainMenuPanel.h"


MainMenuPanel::MainMenuPanel(bool active) : GuiPanel(active) 
{
    Active = active;
}

MainMenuPanel::~MainMenuPanel()
{
}

bool MainMenuPanel::Start()
{
    return true;
}

bool MainMenuPanel::Update(float dt, bool doLogic)
{
    return true;
}

bool MainMenuPanel::Draw()
{
    return true;
}

bool MainMenuPanel::CleanUp()
{
    return true;
}

bool MainMenuPanel::OnGuiMouseClickEvent(GuiControl* control)
{
    return true;
}
