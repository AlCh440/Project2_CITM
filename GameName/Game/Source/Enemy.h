#pragma once
#include "Entity.h"
#include "Pathfinding.h"



struct Stats
{
	int hp;
	int mana;
	int baseDamage;
	int momevent;
};

class Enemy :  public Entity
{
public:

	Enemy(iPoint pos);
	Enemy(Collider_Type type, iPoint pos);
	virtual void Move(float dt);
	virtual void UpdatePath();

	bool Start() override;
	bool PreUpdate() override;
	// Updates animation and collider position
	bool Update(float dt) override;
	bool CleanUp() override;
	// Called from ModuleEntitys' Update
	bool PostUpdate() override;

	// Collision response
	void OnCollision(PhysBody* other) override;
	

protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	fPoint lastPosition;
	fPoint playerPos;
	b2Vec2 movementSpeed;

	PathFinding* pathfinding;
	//int scorePoints = 0;



	Animation idleAnim, walkingAnim, jumpingAnim, deathAnim;
};

