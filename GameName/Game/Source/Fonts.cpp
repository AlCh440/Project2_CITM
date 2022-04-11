
#include "Fonts.h"
#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Log.h"
#include <string.h>

Fonts::Fonts(bool isEnabled) : Module(isEnabled)
{
	name.Create("fonts");
}

Fonts::~Fonts()
{

}

bool Fonts::Start()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	
	// check SDL version 
	LOG("We compiled against SDL version %u.%u.%u ...",
		compiled.major, compiled.minor, compiled.patch);

	// initialize the TTF library
	LOG("TTF status %i", TTF_Init());

	if (TTF_Init() == -1) {
		LOG("Can't init ttf library");
		LOG(TTF_GetError());
	}

	for (int i = 0; i < MAX_FONTS; ++i)
		fonts[i] = nullptr;

	//This takes in the path to the font file and the point size we want to render at.
	globalFont = LoadTIFF("./Assets/Sprites/UI/Fonts/RobotoMedium.ttf", 24);
	titles = LoadTIFF("./Assets/Sprites/UI/Fonts/VT323-Regular.ttf",48);

	menuButtonFont = LoadTIFF("./Assets/Sprites/UI/Fonts/VT323-Regular.ttf", 60);

	return true;
}

bool Fonts::CleanUp()
{

	UnloadAllTIFF();
	TTF_Quit();

	return true;
}

bool Fonts::Update(float dt)
{

	return true;
}

int Fonts::LoadTIFF(const char* fontPath,int fontSize)
{
	int id = -1;
	if(fontPath == NULL || fontSize == NULL)
	{
		LOG("Could not load font...");
		return id;
	}

	id = 0;

	for (; id < MAX_FONTS; ++id)
		if (fonts[id] == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", fontPath, MAX_FONTS);
		return id;
	}

	//this opens a font style and sets a size
	fonts[id] = TTF_OpenFont(fontPath, fontSize);

	if (fonts[id] == nullptr)
	{
		LOG("can't load font");
		LOG(TTF_GetError());

		return -1;
	}
	else {
		LOG("font loaded succesfully");
	}

	return id;
}

void Fonts::UnloadTIFF(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id] != nullptr)
	{
		TTF_CloseFont(fonts[font_id]);
		fonts[font_id] = nullptr;
		LOG("Successfully Unloaded font_id %d", font_id);
	}
}

void Fonts::UnloadAllTIFF()
{
	for (int i = 0; i < MAX_FONTS; i++)
	{
		if (fonts[i] != nullptr)
		{
			TTF_CloseFont(fonts[i]);
			fonts[i] = nullptr;
			LOG("Successfully Unloaded font_id %d", i);
		}
	}
}

SDL_Texture* Fonts::LoadRenderedText(SDL_Rect &rect, int font_id, const char* text, SDL_Color color)
{

	if (fonts[font_id] == NULL)
	{
		LOG("The font %i is empty", font_id);
		return nullptr;
	}

	SDL_Surface* surface = TTF_RenderText_Blended(fonts[font_id],text, color);
	SDL_Texture* tex = nullptr;

	if (surface == NULL)
	{
		LOG(TTF_GetError());
		return nullptr;
	}
	else {

		//creates the texture with the text
		tex = SDL_CreateTextureFromSurface(app->render->renderer, surface);

		if (tex == nullptr)
		{
		   LOG("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());		

		}else{
			//Get image dimensions
			rect = { 0, 0, surface->w, surface->h };
		}
		
		SDL_FreeSurface(surface);
	}	
	return tex;
}

SDL_Texture* Fonts::LoadRenderedParagraph(SDL_Rect& rect, int font_id, const char* text, SDL_Color color, uint32 wrapedLength)
{
	if (fonts[font_id] == NULL)
	{
		LOG("The font %i is empty", font_id);
		return nullptr;		
	}

	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(fonts[font_id], text, color, wrapedLength);
	SDL_Texture* tex = nullptr;

	if (surface == NULL)
	{
		LOG(TTF_GetError());
		return nullptr;
	}
	else {

		//creates the texture with the text
		tex = SDL_CreateTextureFromSurface(app->render->renderer, surface);

		if (tex == nullptr)
		{
			LOG("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());

		}
		else {
			//Get image dimensions
			rect = { 0, 0, surface->w, surface->h };
		}

		SDL_FreeSurface(surface);
	}
	return tex;
}


