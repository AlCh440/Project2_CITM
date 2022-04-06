#pragma once
#include "GuiPanel.h"
class MainMenuPanel : public GuiPanel
{
	MainMenuPanel(bool active);
	~MainMenuPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

};

