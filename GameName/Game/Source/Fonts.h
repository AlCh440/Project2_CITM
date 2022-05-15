#ifndef __FONTS_H__
#define __FONTS_H__

#include "Module.h"
#include "SDL/include/SDL_pixels.h"
#include "SDL_ttf/include/SDL_ttf.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Text
{
	// The font texture
	SDL_Texture* texture = nullptr;
	const char* text;
	SDL_Rect dpsRect;// to store the text texture dimensions

	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;

};

class Fonts : public Module
{
public:

	// Constructor
	Fonts(bool isEnabled);

	// Destructor
	~Fonts();

	bool Start();
	bool CleanUp();
	bool Update(float dt);

	//Load font
	int LoadTIFF(const char* fontPath, int fontSize);

	//Unload font
	void UnloadTIFF(int font_id);

	//Unload all fonts
	void UnloadAllTIFF();

	// Create a surface from font
	// Returns a font index from the fonts array
	// Param rect			- The rectangle where the texture dimensions will be stored
	// Param fontIndex		- The index to refer to a font 
	// Param text			- The text to dispaly
	// Param color			- The color to render the text
	SDL_Texture* LoadRenderedText(SDL_Rect &rect, int font_id, const char* text, SDL_Color color);

	SDL_Texture* LoadRenderedParagraph(SDL_Rect& rect, int font_id, const char* text, SDL_Color color, uint32 wrapedLength);
	
	//Globally used font
	int globalFont;
	//Font used in menu buttons
	int menuButtonFont;

	int titles;

	int battleMenu;

	SDL_Color c_Menus = {38,31,56};

private:

	// An array to keep track and store all loaded fonts
	TTF_Font* fonts[MAX_FONTS];
};


#endif // __FONTS_H__