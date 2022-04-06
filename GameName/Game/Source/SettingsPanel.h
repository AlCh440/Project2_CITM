#pragma once
#include "GuiPanel.h"
class SettingsPanel :  public GuiPanel
{
	SettingsPanel(bool active);
	~SettingsPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;


};

