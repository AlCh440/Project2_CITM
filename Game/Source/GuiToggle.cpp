#include "GuiToggle.h"
#include "GuiManager.h"
#include "Render.h"
#include "ModuleFonts.h"
#include "App.h"
#include "Audio.h"

GuiToggle::GuiToggle(uint32 id, SDL_Rect bounds) : GuiControl(GuiControlType::TOGGLE, id)
{
	this->bounds = bounds;
	texture = app->guiManager->UItexture;
	canClick = true;
	drawBasic = false;
	State = false;
	normalRec = { 0,240,22,22 };
	selectedRec = { 66,240,22,22 };
}

GuiToggle::~GuiToggle()
{
}

bool GuiToggle::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
			{
				State = !State;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}

		if (State)
			state = GuiControlState::SELECTED;
		else
			state = GuiControlState::NORMAL;
	}
	return false;
}

bool GuiToggle::Draw(Render* render)
{


	switch (state)
	{
	case GuiControlState::NORMAL:
	{
		if (app->guiManager->Debug)
		render->DrawRectangle(bounds, 125, 125, 0, 125);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &normalRec);
	} break;
	case GuiControlState::PRESSED:
	{
		if (app->guiManager->Debug)
		render->DrawRectangle(bounds, 255, 255, 255, 255);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &selectedRec);

	} break;
	case GuiControlState::SELECTED:
		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &selectedRec);
		break;
	default:
		break;
	}
	return false;
}
