#pragma once
#include "Entity.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Item.h"
#include "p2List.h"

//enum PlayerState
//{
//	//IDLE,
//	COMBATMOVE,
//	CHOOSINGATTACK,
//	CHOOSINGOBJECTIVE,
//	ATTACKING,
//	DEAD
//};

class Player :  public Entity
{
public:
	Player(iPoint pos);
	Player(Collider_Type type, iPoint pos);
	virtual ~Player();

	virtual bool Start();
	virtual bool PreUpdate();
	virtual bool Update(float dt);
	virtual bool PostUpdate();
	virtual bool CleanUp();
	void SetPosition(iPoint pos);
	iPoint GetPosition() { return position; };
	virtual void Spawn(iPoint pos);

	void Movement();
	void GodMovement();
	void UpdateSensorsPosition();

	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Load / Save
	virtual bool LoadState(pugi::xml_node& data);
	virtual bool SaveState(pugi::xml_node& data) const;

	PhysBody* checkCloseEnemies();

public:
	int typeOfPlayer = 0;

	// The type of Player is the variable that decides whitch player we are creating: Knight, Ranger or Mage
	// 1 for Knight
	// 2 for Ranger
	// 3 for Mage
	// else ERROR


	int actionPoints = 1;
	//PlayerState state = COMBATMOVE;
	bool isAlive = true;
	
	p2List<Item*> Objects;
	Item* ItemEquiped;

private:

	

};

