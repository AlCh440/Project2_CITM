#pragma once
#include "GuiPanel.h"
#include "SDL/include/SDL.h"
#include "Defs.h"

enum statsPlayer
{
	KNIGHT,
	RANGER
};

class Item;

class InventoryPanel : public GuiPanel
{

public:
	InventoryPanel(bool active);
	~InventoryPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	void DrawItems() override;
	bool CleanUp();
	bool OnGuiMouseClickEvent(GuiControl* control) override;

	int GetNumberOfButtons() override;

	iPoint InitializeItemPos();
	void SetItemPosition() override;

	GuiButton* bt_resume;
	GuiButton* bt_settings;
	GuiButton* bt_saveGame;
	GuiButton* bt_menu;
	GuiButton* bt_quit;
	
	SDL_Texture* texTabs;
	SDL_Texture* texItems;
	
	SDL_Rect key01;
	SDL_Rect key02;
	SDL_Rect key03;
	SDL_Rect key04;
	SDL_Rect potionHP;
	SDL_Rect potionMana;

	SDL_Rect spriteKnight;
	SDL_Rect spriteRanger;
	SDL_Rect spriteMage;
	SDL_Rect spriteTab;

	GuiButton* bt_to_knight;
	GuiButton* bt_to_ranger;
	GuiButton* bt_to_use;
	GuiButton* bt_to_exit;

	int numberButtons = 0;
	int rowCounter = 0;
	int columnCounter = 0;

	bool showUseButton = false;
	Item* itemToUse;

	statsPlayer statsShowing;
};
