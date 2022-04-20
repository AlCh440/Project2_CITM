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

enum ENEMY_STATE
{
	INTERPOLATING,
	WALK,
	CHASE,
	ATTACK,
	DIE
};


class Enemy :  public Entity
{
public:

	Enemy(iPoint pos);
	Enemy(Collider_Type type, iPoint pos);
	virtual void Move(float dt);
	virtual void UpdatePath();

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

	fPoint lastPosition;
	fPoint pos;
	b2Vec2 movementSpeed;


	//int scorePoints = 0;


	ENEMY_STATE actualStates;

	iPoint positionToMap;


	Animation idleAnim, walkingAnim, jumpingAnim, deathAnim;
};

