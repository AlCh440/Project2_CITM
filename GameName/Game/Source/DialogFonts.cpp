#include "DialogFonts.h"
#include "App.h"

#include "Textures.h"
#include "Render.h"

#include<string.h>
#include "Window.h"

DialogFonts::DialogFonts(bool isActive) : Module(isActive)
{
	name.Create("dialog");
	toSave = false;
	saveConfigs = false;
}

DialogFonts::~DialogFonts()
{

}

// Load new texture from file path
int DialogFonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = app->tex->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].texture == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	DialogFont& font = fonts[id];

	font.texture = tex;
	font.rows = rows;

	// TODO 1: Finish storing font data

	// totalLength ---	length of the lookup table
	// table ---------  All characters displayed in the same order as the texture
	// columns -------  Amount of chars per row of the texture
	// char_w --------	Width of each character
	// char_h --------	Height of each character
	strcpy_s(fonts[id].table, MAX_FONT_CHARS, characters);
	font.totalLength = strlen(characters);
	font.columns = fonts[id].totalLength / rows;

	uint tex_w, tex_h;
	app->tex->GetSize(tex, tex_w, tex_h);
	font.char_w = tex_w / font.columns;
	font.char_h = tex_h / font.rows;
	// L10: DONE: Set render logical size	font.char_h = tex_h / font.rows;

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void DialogFonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].texture != nullptr)
	{
		app->tex->UnLoad(fonts[font_id].texture);
		fonts[font_id].texture = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

void DialogFonts::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].texture == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const DialogFont* font = &fonts[font_id];
	SDL_Rect spriteRect;
	uint len = strlen(text);

	spriteRect.w = font->char_w;
	spriteRect.h = font->char_h;

	for (uint i = 0; i < len; ++i)
	{
		// Find character
		uint charIndex = 0;
		// Location of the current character in the lookup table
		for (uint j = 0; j < font->totalLength; ++j)
		{
			if (font->table[j] == text[i])
			{
				charIndex = j;
				break;
			}
		}
		// Position of the current character in the sprite
		spriteRect.x = spriteRect.w * (charIndex % font->columns);
		spriteRect.y = spriteRect.h * (charIndex / font->columns);

		app->render->DrawTexture(font->texture, x, y, &spriteRect, 0);



		x += spriteRect.w;
	}
}
