#pragma once
#include "GuiPanel.h"
class MatchResultPanel :  public GuiPanel
{
public:
	MatchResultPanel(bool active);
	~MatchResultPanel();

private:
	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();
	bool OnGuiMouseClickEvent(GuiControl* control) override;

	GuiButton* bt_finish;

public:
	void LoadTitle(bool BattleWon);
	SDL_Texture* title;
	bool finalBattleWon = false;
	SDL_Rect r_title;
};

