#ifndef __GUIMANAGER_H__
#define __GUIMANAGER_H__

#include "Module.h"

#include "GuiControl.h"

#include "List.h"

class GuiManager : public Module
{
public:

	// Constructor
	GuiManager(bool isActive);

	// Destructor
	virtual ~GuiManager();

	// Called before the first frame
	 bool Start();

	 bool Update(float dt);

	bool UpdateAll(float dt,bool logic);

	bool Draw();

	// Called before quitting
	bool CleanUp();

	//bool OnGuiMouseClickEvent(GuiControl* control);


	//void CreateStartMenu();
	//void CreateSettingsMenu();
	//void CreatePauseMenu();
	//void CreateGameOverMenu();
	//void CreateInGameUI();

	// Additional methods
	GuiControl* CreateGuiControl(GuiControlType type, int id, const char* text, int fontid, SDL_Rect bounds, Module* observer, SDL_Rect sliderBounds = { 0,0,0,0 });
	void DestroyGuiControl(GuiControl* entity);
	void AddGuiControl(GuiControl* entity);

public:

	List<GuiControl*> controls;

	float accumulatedTime = 0.0f;
	float updateMsCycle = 0.0f;
	bool doLogic = false;

	SDL_Texture* UItexture;

	int mainFont;
	int numberFont;
	bool Debug = false;


	//GuiButton* startButton;//1
	//GuiButton* settingsButton;//2
	//GuiButton* loadButton;//3
	//GuiButton* exitButton;//4
	//GuiButton* backToTitleButton;//5
	//GuiButton* resumeButton;//6
	//GuiButton* closePanelBttn;//7

	//GuiSlider* volumeSlider;//8
	//GuiSlider* fxSlider;//9
	//GuiToggle* vsyncCheckbox;//10
	//GuiToggle* fullScreenCheckbox;//11


	//GuiPanel* startMenuPanel;
	//GuiPanel* settingsPanel;
	//GuiPanel* pauseMenuPanel;
	//GuiPanel* gameOverMenuPanel;

	//GuiPanel* currentActivePanel;
};

#endif // __GUIMANAGER_H__
