#pragma once
#include "GuiManager.h"
class GuiPanel : public GuiManager
{
public:
	GuiPanel(bool isActive);
	~GuiPanel();

	// Called before the first frame
	bool Start();

	bool Update(float dt);

	bool UpdateAll(float dt, bool logic);

	bool Draw();

	// Called before quitting
	bool CleanUp();

	SDL_Rect bounds;
	iPoint position;
	bool Active;
};

