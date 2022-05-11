#pragma once
#include "Entity.h"


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

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);


protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

};



