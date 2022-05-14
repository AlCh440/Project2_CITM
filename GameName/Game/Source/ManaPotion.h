#pragma once
#include "Entity.h"
#include "Item.h"
#include "Consumable.h"

class ManaPotion : public Consumable
{
public:

	ManaPotion(iPoint pos);
	ManaPotion(Collider_Type type, iPoint pos);
	ManaPotion(Consumable_Type id);

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);
	virtual bool CleanUp();
	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void Consume(Player* user) override;

protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	int quantity;

};
