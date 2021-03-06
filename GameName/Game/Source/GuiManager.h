#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "p2List.h"
#include "GuiPanel.h"
#include "BattlePanel.h"
#include "MatchResultPanel.h"


enum GuiType {
	MAIN_MENU,
	SETTINGS,
	PAUSE,
	QUEST,
	DIALOG,
	GAMEOVER,
	GAME_HUD
};

class GuiManager : public Module
{
public:

	// Constructor
	GuiManager(bool isActive);

	// Destructor
	virtual ~GuiManager();

	// Called before the first frame
	bool Awake(pugi::xml_node&) override;
	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool UpdateAll(float dt,bool logic);
	bool PostUpdate();
	// Called before quitting
	bool CleanUp();
	void OnPause(bool paused);

	void OpenPanel(PanelID panel_id);
	//void OpenPanel(GuiState panel);

	bool OnGuiMouseClickEvent(GuiControl* control);

	uint inventorySound;

public:


	p2List<GuiPanel*> panels;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	//Gui textures Used
	SDL_Texture* UItexture = nullptr;
	SDL_Texture* UItexture2 = nullptr;
	SDL_Texture* tex_smallPanel = nullptr;
	SDL_Texture* tex_mediumPanel = nullptr;
	SDL_Texture* tex_bigPanel = nullptr;
	SDL_Texture* tex_inventory = nullptr;
	SDL_Texture* tex_inventory_tabs = nullptr;
	SDL_Texture* tex_inventory_Items = nullptr;


	int mainFont;
	int numberFont;
	bool Debug = false;


	//gui panels used in the game
	GuiPanel* pn_quest;
	GuiPanel* pn_start;
	GuiPanel* pn_pause;
	GuiPanel* pn_settings;
	GuiPanel* pn_gameOver;
	GuiPanel* pn_battle;
	GuiPanel* pn_inventory;
	GuiPanel* pn_matchResult;

	p2List<PanelID>* panelTrace;
	PanelID lastPanel;
	int currentPanel;

	BattlePanel* battlePanelInstance;
	MatchResultPanel* matchResultInstance;
};

#endif // __GUIMANAGER_H__
