#include "SettingsPanel.h"



SettingsPanel::SettingsPanel(bool active) : GuiPanel(active)
{
	Active = active;
}

SettingsPanel::~SettingsPanel()
{
}

bool SettingsPanel::Start()
{
	return true;
}

bool SettingsPanel::Update(float dt, bool doLogic)
{
	return true;
}

bool SettingsPanel::Draw()
{
	return true;
}

bool SettingsPanel::CleanUp()
{
	return true;
}

bool SettingsPanel::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}
