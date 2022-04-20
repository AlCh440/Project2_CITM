#pragma once

#include "Point.h"
#include <string>
#include "SDL/include/SDL.h"

class Button
{
private:
	enum State {
		DISABLED,
		NORMAL, 
		FOCUSED,
		PRESSED
	};

	SDL_Texture* texture;
	std::string text;

	State state;
	SDL_Rect bounds;
	int font;
public:
	Button();
	Button(SDL_Rect bounds, SDL_Texture* texture, const char* text, int font);
	virtual ~Button();

	void SetPosition(int x, int y);

	void SetFont(int bfont) { font = bfont; }
	void SetBounds(SDL_Rect bbounds) { bounds = bbounds; }
	void SetText(const char* btext) { text = btext; }

	bool Update();
	bool Draw();

	int mouseX, mouseY;
	unsigned int click;

	bool canClick = true;
	bool drawBasic = false;

	bool clicked = false;
};