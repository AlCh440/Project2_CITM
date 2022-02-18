#ifndef __SCENE2_H__
#define __SCENE2_H__

#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "ModulePhysics.h"
#include "Animation.h"
#include "GuiPanel.h"

struct SDL_Texture;

class Scene2 : public Module
{
public:

	Scene2(bool isActive);

	// Destructor
	virtual ~Scene2();

	// Called before render is available
	bool Awake();

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

	void Enable();
	void Disable();

	// Load / Save
	bool LoadState(pugi::xml_node&);
	bool SaveState(pugi::xml_node&) const;

	int KeysToTake = 3;
private:
	SDL_Texture* img;
	p2List_item<PhysBody*>* collider;

	uint music;
};

#endif // __SCENE2_H__
