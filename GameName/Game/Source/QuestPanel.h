#pragma once
#include "GuiPanel.h"
#include "p2List.h"
#include "Quest.h"

class QuestPanel :  public GuiPanel
{

public:
	QuestPanel(bool active);
	~QuestPanel();


	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	GuiButton* nextButton;
	GuiButton* completeButton;
	GuiButton* dialogueButton;
	GuiButton* finishButton;
	GuiButton* offQuestPanel;

	p2ListItem<Quest*>* currentQuest;

	SDL_Texture* notAvailableTex;
	SDL_Rect notavailable;

	SDL_Texture* availableTex;
	SDL_Rect rAvailable;

	SDL_Texture* activeTex;
	SDL_Rect rActive;

	SDL_Texture* completedTex;
	SDL_Rect rCompleted;

	SDL_Rect test = {0,0,200,200};

	int windowScale;
};

