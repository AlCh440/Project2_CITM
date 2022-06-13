#pragma once
#include "Entity.h"
#include "GuiButton.h"

enum itemType {
	NO_TYPE_,
	CHEST_,
	POTION_HP_,
	POTION_MANA_,
	KEY_,
	EXIT_
};

class Item : public Entity
{
public:

	Item();
	Item(iPoint pos);
	Item(Collider_Type type, iPoint pos);

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);
	virtual bool CleanUp();
	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	virtual void CreateButton() { };

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	virtual int GetKeyId() { return int(); };
	itemType itemType;

	GuiButton* button;

	SDL_Texture* texItems;

protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

};



