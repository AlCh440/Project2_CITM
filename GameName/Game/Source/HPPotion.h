#pragma once

#include "Entity.h"
#include "Item.h"
#include "Consumable.h"

class HPPotion : public Consumable
{
public:

	HPPotion(iPoint pos);
	HPPotion(Collider_Type type, iPoint pos);
	HPPotion(Consumable_Type id);

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);
	virtual bool CleanUp();
	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	void CreateButton() override;

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	void UseItem(Player* user) override;

protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	int quantity;

};
