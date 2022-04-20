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
		app->input->GetMouseWorldPosition(mouseX, mouseY);

		if ((mouseX > bounds.x ) && (mouseX < (bounds.x + bounds.w )) &&
			(mouseY > bounds.y ) && (mouseY < (bounds.y + bounds.h )))
		{
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
	app->render->DrawTextureScaled(texture, bounds.x, bounds.y, bounds.w, bounds.h);

	DialogFont& fontobj = app->dialogFonts->GetFont(font);
	int textXOffset = bounds.w / 2 - fontobj.char_w * text.length() / 2;
	int textYOffset = bounds.h / 2 - fontobj.char_h / 2;
	
	app->dialogFonts->BlitText(bounds.x + textXOffset, bounds.y + textYOffset, font, text.c_str());

	return false;
}