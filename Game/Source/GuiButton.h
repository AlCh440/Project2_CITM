#ifndef __GUIBUTTON_H__
#define __GUIBUTTON_H__

#include "GuiControl.h"
#include "Animation.h"

#include "Point.h"
#include "SString.h"



class GuiButton : public GuiControl
{
public:

	GuiButton(uint32 id, SDL_Rect bounds, const char* text, int fontid);
	virtual ~GuiButton();

	bool Update(float dt);
	bool Draw(Render* render);

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;


	int fontPosX,fontPosY;


	SDL_Texture* texture;

	SDL_Rect normalRec,disabledRec,focusedRec,pressedRec,selectedRec;

	Animation* hoverAnim, pressedAnim;
	Animation* currentAnim;

	uint focusedfx, selectedfx;
	bool playfx = true;
};

#endif // __GUIBUTTON_H__