#pragma once
#include "GuiPanel.h"

class BattlePanel :  public GuiPanel
{
public:
	BattlePanel(bool active);
	~BattlePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();
	bool OnGuiMouseClickEvent(GuiControl* control) override;

	void Enable() override;
	void LoadEntityAttacks();


	GuiButton* bt_attack;
	GuiButton* bt_move;
	GuiButton* bt_endTurn;


	GuiButton* bt_test;
};

