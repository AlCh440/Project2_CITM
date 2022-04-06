#pragma once
#include "GuiPanel.h"
class PausePanel :  public GuiPanel
{

	PausePanel(bool active);
	~PausePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;
};

