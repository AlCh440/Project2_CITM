#pragma once
#include "GuiPanel.h"
class MainMenuPanel : public GuiPanel
{

public:
	MainMenuPanel(bool active);
	~MainMenuPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;


	GuiButton* bt_newGame;
	GuiButton* bt_loadGame;
	GuiButton* bt_settings;
	GuiButton* bt_quit;

};

