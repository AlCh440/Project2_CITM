#include "SettingsPanel.h"
#include "App.h"
#include "GuiManager.h"
#include "Fonts.h"

SettingsPanel::SettingsPanel(bool active) : GuiPanel(active)
{
	Active = active;
}

SettingsPanel::~SettingsPanel()
{
}

bool SettingsPanel::Start()
{
	texture = app->guiManager->UItexture2;
	bounds = { 81,414,558,266 };
	position = { 600,400 };

	tg_fixedFps = (GuiToggle*)CreateGuiCheckBox(0, app->guiManager, this, { this->position.x + 50,this->position.y + 50,22,22 });

	tg_fixedFps->texture = app->guiManager->UItexture2;
	tg_fixedFps->textTex = app->fonts->LoadRenderedText(tg_fixedFps->textRect, 0,"FPS", {0,0,0});
	tg_fixedFps->textPosition.x = this->position.x + 50;
	tg_fixedFps->textPosition.y = this->position.y + 25;


	tg_fullScreen = (GuiToggle*)CreateGuiCheckBox(1, app->guiManager, this, { this->position.x + 150,this->position.y + 50,22,22 });
	tg_fullScreen->texture = app->guiManager->UItexture2;
	tg_fullScreen->textTex = app->fonts->LoadRenderedText(tg_fullScreen->textRect, 0, "Full Screen", { 0,0,0 });
	tg_fullScreen->textPosition.x = this->position.x + 150;
	tg_fullScreen->textPosition.y = this->position.y + 25;

	sl_fx = (GuiSlider*)CreateGuiSlider(2, app->guiManager, this, { this->position.x + 50, this->position.y + 150, 150 ,50 }, { this->position.x + 50, this->position.y + 140, 50 ,50 });
	sl_fx->texture =  app->guiManager->UItexture2;
	sl_fx->textTex = app->fonts->LoadRenderedText(sl_fx->textRect, 0, "Fx Volume", { 0,0,0 });
	sl_fx->textPosition.x = this->position.x + 50;
	sl_fx->textPosition.y = this->position.y + 150;
	sl_fx->backgroundRect = { 8,56,154,7 };
	sl_fx->thumbRect = { 22,240,22,22};

	sl_music = (GuiSlider*)CreateGuiSlider(2, app->guiManager, this, { this->position.x + 350, this->position.y + 150, 150 ,50 }, { this->position.x + 350, this->position.y + 140, 50 ,50 });
	sl_music->texture = app->guiManager->UItexture2;
	sl_music->textTex = app->fonts->LoadRenderedText(sl_music->textRect, 0, "Music Volume", { 0,0,0 });
	sl_music->textPosition.x = this->position.x + 350;
	sl_music->textPosition.y = this->position.y + 150;
	sl_music->backgroundRect = { 8,56,154,7 };
	sl_music->thumbRect = { 22,240,22,22 };


	bt_return = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x + 180,this->position.y + 200,170,60 }, "Return", 0, { 255,255,255 });
	bt_return->texture = app->guiManager->UItexture2;
	bt_return->normalRec = { 0,0,170,60 };
	bt_return->focusedRec = { 0,120,170,60 };
	bt_return->pressedRec = { 0,59,170,60 };


	return true;
}

bool SettingsPanel::Update(float dt, bool doLogic)
{
	GuiPanel::Update(dt, doLogic);
	return true;
}

bool SettingsPanel::Draw()
{
	GuiPanel::Draw();
	return true;
}

bool SettingsPanel::CleanUp()
{
	return true;
}

bool SettingsPanel::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}
