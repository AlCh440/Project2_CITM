#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"

#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiPanel.h"
#include "GuiToggle.h"


struct SDL_Texture;

class GameOver : public Module
{
public:

	GameOver(bool isActive);

	// Destructor
	virtual ~GameOver();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

private:
	SDL_Texture* img;
	SDL_Rect rect;

	GuiPanel* menuPanel;
	GuiButton* backToTitleButton;
};

#endif // __GAMEOVER_H__
