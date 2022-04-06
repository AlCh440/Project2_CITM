#include "PausePanel.h"

PausePanel::PausePanel(bool active) : GuiPanel(active)
{
	Active = active;
}

PausePanel::~PausePanel()
{
}

bool PausePanel::Start()
{
	return true;
}

bool PausePanel::Update(float dt, bool doLogic)
{
	return true;
}

bool PausePanel::Draw()
{
	return true;
}

bool PausePanel::CleanUp()
{
	return true;
}

bool PausePanel::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}
