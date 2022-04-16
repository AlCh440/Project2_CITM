#pragma once
#include "GuiPanel.h"
#include "p2List.h"
#include "Quest.h"

class DialogPanel : public GuiPanel
{

public:
	DialogPanel(bool active);
	~DialogPanel();

	enum DialogMoments { NPC1, NPC2, NPC3 };

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	
	
	GuiButton* dialogueButton;
	GuiButton* finishButton;
	GuiButton* cancelButton;
	GuiButton* answer1b;

	p2ListItem<Quest*>* currentDialog;
	SDL_Texture* notAvailableTex;
	SDL_Rect notavailable;

	SDL_Texture* availableTex;
	SDL_Rect rAvailable;

	SDL_Texture* answer1Tex;
	SDL_Rect answer1;
};

