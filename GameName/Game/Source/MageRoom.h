#pragma once

#include "Module.h"
#include "p2List.h"
#include "Defs.h"
#include "Physics.h"
#include "Animation.h"

struct SDL_Texture;

class MageRoom :   public Module
{
public:

	MageRoom(bool isActive);

	// Destructor
	virtual ~MageRoom();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* img;
	SDL_Rect rect;
	uint doorOpen;
};

