#pragma once

#include "Npc.h"
#include "Dialog.h"
#include "DialogManager.h"

class DialogManager;


class NpcGuard : public Npc
{
public:

	NpcGuard(iPoint pos);
	NpcGuard(Collider_Type type, iPoint pos);



	float detectionDistance = 45; // in pixels

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;

	bool Start() override;

	bool CleanUp() override;


	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;

protected:
	uint villagerSound;
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	fPoint lastPosition;

private:
	SDL_Rect rect;
	Animation idleAnim;
};