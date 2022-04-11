#pragma once
#include "GuiPanel.h"
#include "Quest.h"

class QuestHUD : public GuiPanel
{

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	ListItem<Quest*>* currentQuest;
};

