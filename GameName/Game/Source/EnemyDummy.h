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

	int hitPoints;
	int score;
	float detectionDistance = 10; // in pixels

	bool PostUpdate() override;

protected:
	int spriteRotation = 0;
	SDL_RendererFlip spriteDir;

	fPoint lastPosition;
	fPoint playerPos;
	b2Vec2 movementSpeed;

	PathFinding* pathfinding;
	int scorePoints = 0;



	Animation idleAnim, walkingAnim, jumpingAnim, deathAnim;
};

