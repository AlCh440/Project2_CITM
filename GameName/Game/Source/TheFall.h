#pragma once
#include "Module.h"
#include "p2List.h"
#include "Defs.h"
#include "Animation.h"
#include "Dialog.h"
#include "DialogFonts.h"


struct SDL_Texture;

class TheFall :   public Module
{
public:

	TheFall(bool isActive);

	// Destructor
	virtual ~TheFall();

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

	void FillDialog(Dialog& dialog);


private:
	SDL_Texture* img;
	SDL_Rect rect;

	Dialog dialog;

};

