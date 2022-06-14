#pragma once
#include "GuiControl.h"

class GuiToggle :  public GuiControl
{
public:

	GuiToggle(uint32 id, SDL_Rect bounds);
	virtual ~GuiToggle();

	bool Update(float dt);
	bool Draw(Render* render);
	bool CleanUp();

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;

	bool State = false;

	int fontPosX, fontPosY;

	SDL_Rect normalRec,selectedRec;
};