#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"
#include "Animation.h"

#include "Point.h"
#include "SString.h"


class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, SDL_Rect bounds, const char* text, int fontid, SDL_Color textcolor = {255,255,255});
	GuiButton(uint32 id, SDL_Rect bounds);
	virtual ~GuiButton();

	bool Update(float dt);
	bool Draw(Render* render);
	bool CleanUp();

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;

	int fontPosX,fontPosY;

	SDL_Rect normalRec,disabledRec,focusedRec,pressedRec,selectedRec;

	uint focusedfx, selectedfx;
	bool playfx = true;
};

#endif // __GUIBUTTON_H__