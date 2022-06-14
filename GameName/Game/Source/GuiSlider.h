#pragma once
#include "GuiControl.h"
#include "Animation.h"

#include "Point.h"
#include "SString.h"

class GuiSlider : public GuiControl
{

public:

	GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect Thumb);
	virtual ~GuiSlider();

	bool Update(float dt);
	bool Draw(Render* render);
	bool CleanUp();
	int UpdateValue(float pos);
	void UpdateThumbPos(int value);

	int GetValue() { return value; };

	int mouseX, mouseY;
	unsigned int click;

	int value;

	bool canClick = true;
	bool drawBasic = false;

	SDL_Rect thumbBounds;
	SDL_Rect thumbRect;
	SDL_Rect backgroundRect;
	SDL_Texture* texture;

	int maxValue, minValue;
	int maxValueFrom, minValueFrom;

	Animation* hoverAnim, pressedAnim;
	Animation* currentAnim;
};