#include "GuiButton.h"
#include "Render.h"
#include "Fonts.h"
#include "App.h"
#include "GuiManager.h"
#include "Audio.h"
#include "Window.h"

GuiButton::GuiButton(uint32 id, SDL_Rect bounds, const char* text, int fontid, SDL_Color textcolor) : GuiControl(GuiControlType::BUTTON, id)
{
	this->bounds = bounds;
	offset.x = bounds.x;
	offset.y = bounds.y;

	this->text = text;
	font = fontid;
	fontPosX = bounds.x;
	fontPosY = bounds.y;
	texture = app->guiManager->UItexture;
	canClick = true;
	playfx = true;
	if(text != "")
		textTex = app->fonts->LoadRenderedText(textRect, fontid, text, textcolor);
	CenterText(bounds);
	name.Create("Button");
	
}

GuiButton::GuiButton(uint32 id, SDL_Rect bounds) : GuiControl(GuiControlType::BUTTON, id)
{
	name.Create("Button");
	
}

GuiButton::~GuiButton()
{

}

bool GuiButton::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);


		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			state = GuiControlState::FOCUSED;
			
			if (playfx)
			{
				app->audio->PlayFx(1);
				playfx = false;
			}

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN)
			{
				state = GuiControlState::PRESSED;
				playfx = true;
			}

			// Generate event
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

	bounds.x = parent->position.x + offset.x;
	bounds.y = parent->position.y + offset.y;
	CenterText(bounds);

	return true;
}

bool GuiButton::Draw(Render* render)
{

	// Draw the right button depending on state
	switch (state)
	{

	case GuiControlState::DISABLED: 
	{
		if (app->guiManager->Debug)
			render->DrawRectangle(bounds, 125 / app->win->GetScale(), 200/ app->win->GetScale(), 0, 0);

		if (texture != nullptr)
			render->DrawTexture(texture, bounds.x / app->win->GetScale(), bounds.y / app->win->GetScale(), &disabledRec, 0, 0, 0, 0, 0.5f);

		if (textTex != nullptr)
			render->DrawTexture(textTex, textPosition.x / app->win->GetScale(), textPosition.y / app->win->GetScale(), &textRect, 0, 0, 0, 0, 0.5f);

	} break;

	case GuiControlState::NORMAL:
	{
		if (app->guiManager->Debug)
			render->DrawRectangle(bounds, 125, 125, 0,125);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x / app->win->GetScale(), bounds.y / app->win->GetScale(), &normalRec, 0, 0, 0, 0, 0.5f);


		if (textTex != nullptr)
			render->DrawTexture(textTex, textPosition.x / app->win->GetScale(), textPosition.y / app->win->GetScale(), &textRect, 0, 0, 0, 0, 0.5f);

	} break;
	case GuiControlState::FOCUSED:
	{
		if (app->guiManager->Debug)
			render->DrawRectangle(bounds, 255, 255, 255, 160);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x / app->win->GetScale(), bounds.y / app->win->GetScale(), &focusedRec, 0, 0, 0, 0, 0.5f);

		if (textTex != nullptr)
			render->DrawTexture(textTex, textPosition.x / app->win->GetScale(), textPosition.y / app->win->GetScale(), &textRect, 0, 0, 0, 0, 0.5f);

	} break;
	case GuiControlState::PRESSED:
	{
	
		if (app->guiManager->Debug)
			render->DrawRectangle(bounds, 255, 255, 255, 255);
		if (playfx)
		{
			app->audio->PlayFx(2);
			playfx = false;
		}
		if (texture != NULL)
			render->DrawTexture(texture, bounds.x / app->win->GetScale(), bounds.y / app->win->GetScale(), &pressedRec, 0, 0, 0, 0, 0.5f);

		if (textTex != nullptr)
			render->DrawTexture(textTex, textPosition.x / app->win->GetScale(), textPosition.y / app->win->GetScale(), &textRect, 0, 0, 0, 0, 0.5f);

	} break;

	case GuiControlState::SELECTED:
	{
		if (app->guiManager->Debug)
			render->DrawRectangle(bounds, 0, 255, 0, 255);

		if (texture != NULL)
			render->DrawTexture(texture, bounds.x / app->win->GetScale(), bounds.y / app->win->GetScale(), &selectedRec, 0, 0, 0, 0, 0.5f);

		if (textTex != nullptr)
			render->DrawTexture(textTex, textPosition.x / app->win->GetScale(), textPosition.y / app->win->GetScale(), &textRect, 0, 0, 0, 0, 0.5f);
	}break;

	default:
		break;
	}

	return true;
}

bool GuiButton::CleanUp()
{
	textTex = nullptr;
	texture = nullptr;
	return true;
}
