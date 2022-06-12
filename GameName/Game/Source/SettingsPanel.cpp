#include "SettingsPanel.h"
#include "App.h"
#include "GuiManager.h"
#include "Fonts.h"
#include "Audio.h"
#include "Window.h"

SettingsPanel::SettingsPanel(bool active) : GuiPanel(active)
{
	Active = active;
	id = PanelID::P_SETTINGS;
}

SettingsPanel::~SettingsPanel()
{
}

bool SettingsPanel::Start()
{
	texture = app->guiManager->tex_bigPanel;
	bounds = { 0,0,1280,720 };
	position = { 0,0 };

	title = app->fonts->LoadRenderedText(r_title, app->fonts->titles, "Settings", app->fonts->c_Menus);

	tg_fixedFps = (GuiToggle*)CreateGuiCheckBox(0, app->guiManager, this, { this->position.x + 450,this->position.y + 350,22,22 });

	tg_fixedFps->texture = app->guiManager->UItexture2;
	tg_fixedFps->textTex = app->fonts->LoadRenderedText(tg_fixedFps->textRect, 0,"60 FPS", {0,0,0});
	tg_fixedFps->textPosition.x = tg_fixedFps->bounds.x + tg_fixedFps->textRect.w + 100;
	tg_fixedFps->textPosition.y = tg_fixedFps->bounds.y + 25;


	tg_fullScreen = (GuiToggle*)CreateGuiCheckBox(1, app->guiManager, this, { this->position.x + 650,this->position.y + 350,22,22 });
	tg_fullScreen->texture = app->guiManager->UItexture2;
	tg_fullScreen->textTex = app->fonts->LoadRenderedText(tg_fullScreen->textRect, 0, "Full Screen", { 0,0,0 });
	tg_fullScreen->textPosition.x = tg_fullScreen->bounds.x + tg_fullScreen->textRect.w + 100;
	tg_fullScreen->textPosition.y = tg_fullScreen->bounds.y + 25;



	sl_fx = (GuiSlider*)CreateGuiSlider(2, app->guiManager, this, { this->position.x + 450, this->position.y + 300, 150 ,50 }, { this->position.x + 450 + 150, this->position.y + 290, 50 ,50 });
	sl_fx->texture =  app->guiManager->UItexture2;
	sl_fx->textTex = app->fonts->LoadRenderedText(sl_fx->textRect, 0, "Fx Volume", { 0,0,0 });
	sl_fx->textPosition.x = sl_fx->bounds.x;
	sl_fx->textPosition.y = sl_fx->bounds.y + 10;
	sl_fx->backgroundRect = { 8,56,154,7 };
	sl_fx->thumbRect = { 22,240,22,22};
	sl_fx->UpdateThumbPos(app->audio->GetFxVolume());

	sl_music = (GuiSlider*)CreateGuiSlider(3, app->guiManager, this, { this->position.x + 650, this->position.y + 300, 150 ,50 }, { this->position.x + 650 + 150, this->position.y + 290, 50 ,50 });
	sl_music->texture = app->guiManager->UItexture2;
	sl_music->textTex = app->fonts->LoadRenderedText(sl_music->textRect, 0, "Music Volume", { 0,0,0 });
	sl_music->textPosition.x = sl_music->bounds.x;
	sl_music->textPosition.y = sl_music->bounds.y + 10;
	sl_music->backgroundRect = { 8,56,154,7 };
	sl_music->thumbRect = { 22,240,22,22 };
	sl_music->UpdateThumbPos(app->audio->GetMusicVolume());


	bt_return = (GuiButton*)CreateGuiButton(4, app->guiManager, this, { this->position.x + 555,this->position.y + 525,170,60 }, "Return", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_return->texture = app->guiManager->UItexture2;
	bt_return->normalRec = { 0,0,170,60 };
	bt_return->focusedRec = { 0,120,170,60 };
	bt_return->pressedRec = { 0,59,170,60 };


	return true;
}

bool SettingsPanel::Update(float dt, bool doLogic)
{
	if (counter < easingTime)
	{

		auto easingFunction = getEasingFunction(EaseOutBounce);
		double progress = easingFunction(UpdateProgress(counter, 0, 100, 0, 1));
		easePosY = (int)UpdateProgress(progress, 0, 1, -100, 0);
		position.y = easePosY;
		counter++;
	}
	GuiPanel::Update(dt, doLogic);
	return true;
}

bool SettingsPanel::Draw()
{
	GuiPanel::Draw();

	float screenScale = 1 / (float)app->win->GetScale();

	app->render->DrawTexture(title, 535 * screenScale, 115 * screenScale, &r_title,0,0,0,0, screenScale);
	return true;
}

bool SettingsPanel::CleanUp()
{
	return true;
}

bool SettingsPanel::OnGuiMouseClickEvent(GuiControl* control)
{

	if (control->id == bt_return->id)
	{
		app->guiManager->OpenPanel(app->guiManager->lastPanel);
	}
	else if (control->id == tg_fixedFps->id)
	{
		app->FPScap60(tg_fixedFps->State);
	}
	else if (control->id == tg_fullScreen->id)
	{
		app->win->SetFullScreen(tg_fullScreen->State);
	}
	else if (control->id == sl_fx->id)
	{
		app->audio->SetFxVolume(sl_fx->GetValue());

	}
	else if (control->id == sl_music->id) 
	{
		app->audio->SetMusicVolume(sl_music->GetValue());
	}

	return true;
}
