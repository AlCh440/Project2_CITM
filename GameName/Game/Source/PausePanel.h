#pragma once
#include "GuiPanel.h"
class PausePanel :  public GuiPanel
{

public:
	PausePanel(bool active);
	~PausePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	GuiButton* bt_resume;
	GuiButton* bt_settings;
	GuiButton* bt_saveGame;
	GuiButton* bt_menu;
	GuiButton* bt_quit;
	

};

