#pragma once

#include "Enemy.h"
#include "Pathfinding.h"



struct Statistics
{
	int hp;
	int mana;
	int baseDamage;
	int momevent;
};

class EnemyDummy : public Enemy
{
public:

	EnemyDummy(iPoint pos);
	EnemyDummy(Collider_Type type, iPoint pos);
	virtual void Move(float dt);
	virtual void UpdatePath();

	//int hitPoints;
	//int score;
	float detectionDistance = 10; // in pixels

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;

public:

	bool BasicAttack(); // pass an Player
	

	bool Start() override;
	
	bool CleanUp() override;


	void OnCollision(PhysBody* other) override;

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;

protected:

	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	fPoint lastPosition;
	fPoint playerPos;
	b2Vec2 movementSpeed;

	PathFinding* pathfinding;
	int scorePoints = 0;

	Statistics stats;

	Animation idleAnim, walkingAnim, jumpingAnim, deathAnim;
};

