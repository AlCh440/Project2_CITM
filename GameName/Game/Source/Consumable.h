#pragma once
#include "Entity.h"
#include "Item.h"

enum Consumable_Type
{
	HP_POTION,
	MANA_POTION
};

class Consumable : public Item
{
public:

	Consumable(iPoint pos);
	Consumable(Collider_Type type, iPoint pos);
	Consumable(Consumable_Type id);

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);
	virtual bool CleanUp();
	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	

	Consumable_Type consumableId;

protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	int quantity;
	
};

