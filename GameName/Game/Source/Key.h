#pragma once
#pragma once
#include "Entity.h"
#include "Item.h"

class Key : public Item
{
public:

	Key(iPoint pos);
	Key(Collider_Type type, iPoint pos);

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);
	virtual bool CleanUp();
	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	int id;

protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;


};
