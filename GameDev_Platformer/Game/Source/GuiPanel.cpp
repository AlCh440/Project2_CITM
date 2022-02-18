#include "GuiPanel.h"
#include "App.h"
#include "Render.h"

GuiPanel::GuiPanel(bool isActive) : GuiManager(isActive)
{
	Active = isActive;
}

GuiPanel::~GuiPanel()
{
}

bool GuiPanel::Start()
{
	return false;
}

bool GuiPanel::Update(float dt)
{
	if (!Active)
		return false;

	accumulatedTime += dt;
	if (accumulatedTime >= updateMsCycle) doLogic = true;

	UpdateAll(dt, doLogic);

	if (doLogic == true)
	{
		accumulatedTime = 0.0f;
		doLogic = false;
	}

	return true;
}

bool GuiPanel::UpdateAll(float dt, bool logic)
{

	if (doLogic) {

		ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			control->data->Update(dt);
			control = control->next;
		}

	}
	return true;
}

bool GuiPanel::Draw()
{
	if (!Active)
		return false;


	app->render->DrawTexture(app->guiManager->UItexture,position.x, position.y,&bounds);

	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->Draw(app->render);
		control = control->next;
	}
	return true;
}

bool GuiPanel::CleanUp()
{
	ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		RELEASE(control);
	}

	return true;

}
