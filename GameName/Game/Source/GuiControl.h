#ifndef __GUICONTROL_H__
#define __GUICONTROL_H__


#include "Module.h"
#include "Input.h"
#include "Render.h"
#include "Fonts.h"
#include "Point.h"
#include "SString.h"
#include "Point.h"


#include "SDL/include/SDL.h"



enum class GuiControlType
{
	BUTTON,
	TOGGLE,
	CHECKBOX,
	SLIDER,
	SLIDERBAR,
	COMBOBOX,
	DROPDOWNBOX,
	INPUTBOX,
	VALUEBOX,
	SPINNER
};

enum class GuiControlState
{
	DISABLED,
	NORMAL,
	FOCUSED,
	PRESSED,
	SELECTED
};

class GuiPanel;

class GuiControl
{
public:

	GuiControl(GuiControlType type, uint32 id) : type(type), id(id), state(GuiControlState::NORMAL) {}

	GuiControl(GuiControlType type, SDL_Rect bounds, const char* text, int font) :
		type(type),
		state(GuiControlState::NORMAL),
		bounds(bounds),
		text(text),
		font(font)
	{
		color.r = 255; color.g = 255; color.b = 255;
		texture = NULL;
	}

	~GuiControl() {

	}

	virtual bool Update(float dt)
	{
		return true;
	}

	virtual bool Draw(Render* render)
	{
		return true;
	}

	virtual bool CleanUp()
	{
		return true;
	}

	void SetTexture(SDL_Texture* tex)
	{
		texture = tex;
		section = { 0, 0, 0, 0 };
	}

	void SetObserver(Module* module)
	{
		observer = module;
	}

	void SetParent(GuiPanel* panel)
	{
		parent = panel;
	}

	void NotifyObserver()
	{
		observer->OnGuiMouseClickEvent(this);
	}

	void CenterText(SDL_Rect parent) 
	{
		textPosition.x = bounds.x + ((bounds.w - textRect.w) / 2);
		textPosition.y = bounds.y + ((bounds.h - textRect.h) / 2);
	}

public:

	uint32 id;
	GuiControlType type;
	GuiControlState state;

	const char* text;       // Control text (if required)
	int font;				// font texture index
	SDL_Texture* textTex;	// Text texture
	SDL_Rect textRect;		// Text bounds
	iPoint textPosition;	// Text position (center texture)
	SDL_Color textColor;	// Text color


	SDL_Rect bounds;        // Position and size
	SDL_Color color;        // Tint color

	SDL_Texture* texture;   // Texture atlas reference
	SDL_Rect section;       // Texture atlas base section

	Module* observer;       // Observer GuiManager Module (it should probably be an array/list)
	GuiPanel* parent;		//Panel where the element is located
	uint soundfx;

	SString name;

	iPoint offset;
	int fontPosX, fontPosY; // font texture position
};

#endif // __GUICONTROL_H__