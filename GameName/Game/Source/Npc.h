#pragma once

#pragma once

#include "Entity.h"


class Npc : public Entity
{
public:

	Npc(iPoint pos);
	Npc(Collider_Type type, iPoint pos);
	

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);
	virtual bool CleanUp();
	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	// Collision response
	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	//int hitPoints;
	//int score;
	//float detectionDistance = 10; // in pixels
protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	

	
	//int scorePoints = 0;



	Animation idleAnim;
};