#include "GuiButton.h"
#include "GuiManager.h"
#include "Render.h"
#include "ModuleFonts.h"
#include "App.h"
#include "Audio.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text, int fontid) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	this->text = text;
	font = fontid;
	fontPosX = bounds.x;
	fontPosY = bounds.y;
	texture = app->guiManager->UItexture;
	canClick = true;
	drawBasic = false;
	playfx = true;
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x ) && (mouseX < (bounds.x + bounds.w )) &&
			(mouseY > bounds.y ) && (mouseY < (bounds.y + bounds.h )))
		{
			state = GuiControlState::FOCUSED;
			
			if (playfx)
			{
				app->audio->PlayFx(1);
				playfx = false;
			}

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}
		}
		else { 
			state = GuiControlState::NORMAL; 
			playfx = true;
		}

		
	}

	return false;
}

bool GuiButton::Draw(Render* render)
{

	// Draw the right button depending on state


	switch (state)
	{

	case GuiControlState::DISABLED: 
	{
		if (app->guiManager->Debug)
		render->DrawRectangle(bounds, 125, 200, 0, 0);

		if(texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &disabledRec);
	} break;

	case GuiControlState::NORMAL:
	{
		if (app->guiManager->Debug)
		render->DrawRectangle(bounds, 125, 125, 0,125);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &normalRec);
	} break;
	case GuiControlState::FOCUSED:
	{
		if (app->guiManager->Debug)
		render->DrawRectangle(bounds, 255, 255, 255, 160);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &focusedRec);
	} break;
	case GuiControlState::PRESSED:
	{
	
		if (app->guiManager->Debug)
		render->DrawRectangle(bounds, 255, 255, 255, 255);

		app->audio->PlayFx(2);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &pressedRec);

	} break;

	case GuiControlState::SELECTED:
	{
		if (app->guiManager->Debug)
		render->DrawRectangle(bounds, 0, 255, 0, 255);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x, bounds.y, &selectedRec);
	}break;

	default:
		break;
	}

	return false;
}