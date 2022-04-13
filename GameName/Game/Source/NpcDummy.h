
#pragma once

#include "Npc.h"


class NpcDummy : public Npc
{
public:

	NpcDummy(iPoint pos);
	NpcDummy(Collider_Type type, iPoint pos);
	

	
	float detectionDistance = 10; // in pixels

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;

public:

	


	bool Start() override;

	bool CleanUp() override;


	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;

protected:

	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	fPoint lastPosition;
	


	Animation idleAnim;
};