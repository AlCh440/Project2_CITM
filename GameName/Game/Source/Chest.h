#pragma once
#include "Entity.h"
#include "Item.h"
#include "Player.h"

class OpenWorldPlayer;

class Chest : public Item
{
public:

	Chest(iPoint pos);
	Chest(Collider_Type type, iPoint pos);
	Chest(Collider_Type type, iPoint pos, p2List<Item*> items);

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);
	virtual bool CleanUp();
	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void Open(OpenWorldPlayer* player);

protected:
	SDL_RendererFlip spriteDir;

	p2List<Item*> item;
	bool alreadyOpen;
	
	float detectionDistance = 40;

	SDL_Texture* attention;
	uint fxOpen;
	uint fxClose;
};
