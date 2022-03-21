#pragma once
#include "Entity.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"

enum PlayerState
{
	IDLE,
	MOVE,
	JUMP,
	DOUBLE_JUMP,
	ATTACK,
	DEAD
};

class Player :  public Entity
{
public:
	Player(iPoint pos);
	Player(Collider_Type type, iPoint pos);
	virtual ~Player();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void SetPosition(iPoint pos);
	fPoint GetPosition() { return position; };
	void Spawn(iPoint pos);

	void Movement();
	void GodMovement();
	void UpdateSensorsPosition();

	//attacks
	void MeleeAttack();
	void SkillAttack();
	//skills?

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

public:
	Animation* currentAnim = nullptr;

private:

	int typeOfPlayer = 0; 

	// The type of Player is the variable that decides whitch player we are creating: Knight, Ranger or Mage
	// 1 for Knight
	// 2 for Ranger
	// 3 for Mage
	// else ERROR

	int lifePoints = 1;
	int manaPoints = 1;

};

