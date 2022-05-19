#include "MatchResultPanel.h"
#include "App.h"
#include "GuiManager.h"
#include "LevelManagement.h"
#include "Window.h"

MatchResultPanel::MatchResultPanel(bool active) : GuiPanel(active)
{
	Active = active;
	id = PanelID::P_MATCH_RESULT;
}

MatchResultPanel::~MatchResultPanel()
{
}

bool MatchResultPanel::Start()
{
	texture = app->guiManager->tex_smallPanel;
	bounds = { 0,0,1280,720 };
	position = { 0,0 };

	title = app->fonts->LoadRenderedText(r_title, app->fonts->titles, "Match Result", app->fonts->c_Menus);
	

	bt_finish = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { bounds.x + 555,bounds.y + 350,170,60 }, "Finish", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_finish->texture = app->guiManager->UItexture2;
	bt_finish->normalRec = { 0,0,170,60 };
	bt_finish->focusedRec = { 0,120,170,60 };
	bt_finish->pressedRec = { 0,59,170,60 };

	return true;
}

bool MatchResultPanel::Update(float dt, bool doLogic)
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

bool MatchResultPanel::Draw()
{
	GuiPanel::Draw();
	if (title != nullptr)
		app->render->DrawTexture(title, (position.x + (bounds.w * 0.5f) - (r_title.w * 0.5f)) / app->win->GetScale(), (position.y + 150) / app->win->GetScale(), &r_title, 0, 0, 0, 0, 0.5f);
	return true;
}

bool MatchResultPanel::CleanUp()
{
	return true;
}

bool MatchResultPanel::OnGuiMouseClickEvent(GuiControl* control)
{

	if (control->id == bt_finish->id)
	{
		app->levelManagement->gameScene = app->levelManagement->lastOpenWorldScene;
		Disable();
	}

	return true;
}

void MatchResultPanel::LoadTitle(bool BattleWon)
{
	if (BattleWon)
	{
		title = app->fonts->LoadRenderedText(r_title, app->fonts->titles, "Victory", app->fonts->c_Menus);
	}
	else {
		title = app->fonts->LoadRenderedText(r_title, app->fonts->titles, "Defeat", app->fonts->c_Menus);
	}
}
