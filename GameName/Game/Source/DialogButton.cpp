#include "DialogButton.h"
#include "Render.h"
#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "DialogFonts.h"

Button::Button()
{
}

Button::Button(SDL_Rect bounds, SDL_Texture* texture, const char* text, int font)
{
	this->texture = texture;
	this->bounds = bounds;
	this->text = text;
	this->font = font;

	canClick = true;
	drawBasic = false;

	state = State::NORMAL;
}

Button::~Button()
{

}

void Button::SetPosition(int x, int y)
{
	bounds.x = x;
	bounds.y = y;
}

bool Button::Update()
{
	if (state != State::DISABLED)
	{
		// L14: TODO 3: Update the state of the GUiButton according to the mouse position
		int mouseX, mouseY;

		app->input->GetMousePosition(mouseX, mouseY);

		mouseX *= app->win->GetScale();
		mouseY *= app->win->GetScale();

		LOG("bounds pos x: %i", mouseX);
		LOG("bounds pos y: %i", mouseY);

		if ((mouseX > bounds.x ) && (mouseX < (bounds.x + bounds.w * app->win->GetScale())) &&
			(mouseY > bounds.y ) && (mouseY < (bounds.y + bounds.h * app->win->GetScale())))
		{
			LOG("true");
			state = State::FOCUSED;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_REPEAT)
			{
				state = State::PRESSED;
			}

			// If mouse button pressed -> Generate event!
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_UP)
			{
				clicked = true;
			}
		}
		else state = State::NORMAL;
	}

	return false;
}

bool Button::Draw()
{
	app->render->DrawTextureScaled(texture, bounds.x / app->win->GetScale(), bounds.y / app->win->GetScale(), bounds.w, bounds.h,NULL,0);

	DialogFont& fontobj = app->dialogFonts->GetFont(font);
	int textXOffset = bounds.w / 2 - fontobj.char_w * text.length() / 2;
	int textYOffset = bounds.h / 2 - fontobj.char_h / 2;
	
	app->dialogFonts->BlitText((bounds.x + textXOffset) / app->win->GetScale(), (bounds.y + textYOffset) / app->win->GetScale(), font, text.c_str());
	return true;
}