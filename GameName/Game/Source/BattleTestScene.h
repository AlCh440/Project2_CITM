#pragma once
#include "Module.h"
#include "p2List.h"
#include "Defs.h"
#include "Physics.h"
#include "Animation.h"
#include "Fonts.h"

struct SDL_Texture;

class BattleTestScene : public Module
{
public:

	BattleTestScene(bool isActive);

	// Destructor
	virtual ~BattleTestScene();

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

	void NextEntity();

private:
	SDL_Texture* entityText;
	SDL_Rect rect;

	int entityIndex = 0;
	p2List<Entity*> battleEntities;
public:
	p2ListItem<Entity*>* currentEntity;
	int turnCounter = 0;
};
