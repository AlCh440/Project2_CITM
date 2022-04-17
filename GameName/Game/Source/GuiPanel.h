#ifndef __GUIPANEL_H__
#define __GUIPANEL_H__



#include "SDL/include/SDL.h"
#include "Point.h"
#include "GuiControl.h"
#include "GuiButton.h"
#include "GuiToggle.h"
#include "GuiSlider.h"
#include "p2List.h"

class GuiPanel
{
public:
	GuiPanel(bool isActive);
	~GuiPanel();

	// Called before the first frame to init all the elemnts of the Panel such as buttons and sliders...*
	virtual bool Start();
	virtual bool Update(float dt, bool doLogic);
	virtual bool Draw();

	// Called before quitting
	bool CleanUp();
	
	//create ui elements
	GuiControl* CreateGuiControl(GuiControlType type, int id, SDL_Rect bounds, Module* observer, GuiPanel* parent, const char* text = "", int fontid = 0, SDL_Rect sliderBounds = { 0,0,0,0 });
	GuiControl* CreateGuiButton(int id, Module* observer, GuiPanel* parent, SDL_Rect bounds, const char* text = "", int fontId = 0, SDL_Color textColor = { 255,255,255 });
	GuiControl* CreateGuiSlider(int id, Module* observer, GuiPanel* parent, SDL_Rect bounds, SDL_Rect sliderBounds);
	GuiControl* CreateGuiCheckBox(int id, Module* observer, GuiPanel* parent, SDL_Rect bounds);

	// this funtion will handle events recived on the panel
	virtual bool OnGuiMouseClickEvent(GuiControl* control);

	void Enable() { Active = true; };
	void Disable() { Active = false; };
	bool GetActive() { return Active; };

public:
	p2List<GuiControl*> controls;
	SDL_Rect bounds;
	iPoint position;
	SDL_Texture* texture;
	bool Active;
	int id;

};

#endif // __GUIPANEL_H__
