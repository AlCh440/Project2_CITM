#pragma once
#include "GuiPanel.h"
#include "SDL/include/SDL.h"



class InventoryPanel : public GuiPanel
{

public:
	InventoryPanel(bool active);
	~InventoryPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	void DrawItems();
	bool CleanUp();
	bool OnGuiMouseClickEvent(GuiControl* control) override;

	GuiButton* bt_resume;
	GuiButton* bt_settings;
	GuiButton* bt_saveGame;
	GuiButton* bt_menu;
	GuiButton* bt_quit;
	
	SDL_Texture* title;
	SDL_Texture* texItems;
	
	SDL_Rect key01;
	SDL_Rect key02;
	SDL_Rect key03;
	SDL_Rect key04;
	SDL_Rect potionHP;
	SDL_Rect potionMana;

};
