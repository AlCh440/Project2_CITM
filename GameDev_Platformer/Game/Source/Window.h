#ifndef __PORTALDOW_H__
#define __PORTALDOW_H__

#include "Module.h"

struct SDL_Window;
struct SDL_Surface;

class Window : public Module
{
public:

	Window(bool isActive);

	// Destructor
	virtual ~Window();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Changae title
	void SetTitle(const char* title);

	// Retrive window size
	void GetWindowSize(uint& width, uint& height) const;

	// Retrieve window scale
	uint GetScale() const;

	// Retrieve window Width
	int GetWidth() const;

	// Retrieve window height
	int GetHeight() const;

	void SetFullScreen(bool fullScreen);
	bool GetFullScreen();

public:
	// The window we'll be rendering to
	SDL_Window* window;

	// The surface contained by the window
	SDL_Surface* screenSurface;

private:
	SString title;
	uint width;
	uint height;
	uint scale;

	bool fullScreen;
};

#endif // __PORTALDOW_H__
