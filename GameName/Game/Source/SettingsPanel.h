#pragma once
#include "GuiPanel.h"
class SettingsPanel :  public GuiPanel
{
public:

	SettingsPanel(bool active);
	~SettingsPanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control) override;

	bool capTheFrames = false;
	GuiToggle* tg_fullScreen;
	GuiToggle* tg_fixedFps;
	GuiSlider* sl_fx;
	GuiSlider* sl_music;
	GuiButton* bt_return;

	SDL_Texture* title;
	SDL_Rect r_title;
	
};

