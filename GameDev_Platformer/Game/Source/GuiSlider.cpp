#include "GuiSlider.h"
#include "App.h"
#include "GuiManager.h"
#include "Log.h"

GuiSlider::GuiSlider(uint32 id, SDL_Rect bounds, SDL_Rect Thumb) : GuiControl(GuiControlType::SLIDER, id)
{
	this->bounds = bounds;
	this->text = text;
	this->thumbBounds = Thumb;
	texture = app->guiManager->UItexture;
	canClick = true;
	drawBasic = false;
	maxValue = 128;
	minValue = 0;
	minValueFrom = bounds.x;
	maxValueFrom = bounds.x + bounds.w;

	backgroundRect = {89,240,82,8};
	thumbRect = {172,240,6,10};
}

GuiSlider::~GuiSlider()
{
}

bool GuiSlider::Update(float dt)
{
	if (state != GuiControlState::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);

		if ((mouseX > bounds.x) && (mouseX < (bounds.x + bounds.w)) &&
			(mouseY > bounds.y) && (mouseY < (bounds.y + bounds.h)))
		{
			state = GuiControlState::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				if (mouseX < bounds.x)
					thumbBounds.x = bounds.x + thumbBounds.w;

				if (mouseX > (bounds.x + bounds.w))
					thumbBounds.x = bounds.x - thumbBounds.w;

				thumbBounds.x = mouseX;

				value = GetValue(mouseX);
				LOG("slider value:%f", GetValue(mouseX));
				state = GuiControlState::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				NotifyObserver();
			}

		}else state = GuiControlState::NORMAL;
	}

	return false;
}

bool GuiSlider::Draw(Render* render)
{


	switch (state)
	{

	case GuiControlState::DISABLED:
	{
		if (app->guiManager->Debug)
		{
			render->DrawRectangle(bounds, 125, 200, 0, 0);
			render->DrawRectangle(thumbBounds, 125, 200, 0, 0);
		}

		if (texture != NULL)
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &backgroundRect);
			render->DrawTexture(texture, thumbBounds.x, thumbBounds.y, &thumbRect);
		}

	} break;

	case GuiControlState::NORMAL:
	{
		if (app->guiManager->Debug)
		{
			render->DrawRectangle(bounds, 125, 125, 0, 125);
			render->DrawRectangle(thumbBounds, 0, 200, 0, 255);
		}
		if (texture != NULL)
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &backgroundRect);
			render->DrawTexture(texture, thumbBounds.x, thumbBounds.y, &thumbRect);
		}
	} break;
	case GuiControlState::FOCUSED:
	{
		if (app->guiManager->Debug)
		{
			render->DrawRectangle(bounds, 255, 255, 255, 160);
			render->DrawRectangle(thumbBounds, 0, 255, 255, 255);
		}
		if (texture != NULL)
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &backgroundRect);
			render->DrawTexture(texture, thumbBounds.x, thumbBounds.y, &thumbRect);
		}
	} break;
	case GuiControlState::PRESSED:
	{

		if (app->guiManager->Debug)
		{
			render->DrawRectangle(bounds, 255, 255, 255, 255);
			render->DrawRectangle(thumbBounds, 0, 255, 255, 255);
		}
		if (texture != NULL)
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &backgroundRect);
			render->DrawTexture(texture, thumbBounds.x, thumbBounds.y, &thumbRect);
		}

	} break;

	case GuiControlState::SELECTED:
	{
		if (app->guiManager->Debug)
		{
			render->DrawRectangle(bounds, 0, 255, 0, 255);
			render->DrawRectangle(thumbBounds, 0, 255, 255, 255);
		}
		if (texture != NULL)
		{
			render->DrawTexture(texture, bounds.x, bounds.y, &backgroundRect);
			render->DrawTexture(texture, thumbBounds.x, thumbBounds.y, &thumbRect);
		}
	}break;

	default:
		break;
	}
	return true;
}

int GuiSlider::GetValue(float pos)
{

	if (pos < bounds.x)
		return value = minValue;

	if (pos > (bounds.x + bounds.w))
		return	value = maxValue;

	value = minValue + (maxValue - minValue) * ((pos - minValueFrom) / (maxValueFrom - minValueFrom));

	return value;
}

void GuiSlider::SetValue(int _value)
{

	thumbBounds.x = bounds.x + ((bounds.x +bounds.w) - bounds.x) * ((_value - 0) / (128 - 0));


}
