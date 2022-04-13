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
	COMBATMOVE,
	FREEMOVE,
	ATTACK,
	DEAD
};

//enum TypeOfMovement
//{
//	OPENWORLD,
//	COMBATMOVE,
//	DEFAULT
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
	fPoint GetPosition() { return position; };
	virtual void Spawn(iPoint pos);

	void Movement();
	void GodMovement();
	void UpdateSensorsPosition();

	virtual void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Load / Save
	virtual bool LoadState(pugi::xml_node& data);
	virtual bool SaveState(pugi::xml_node& data) const;

public:
	Animation* currentAnim = nullptr;

	int typeOfPlayer = 0;

	// The type of Player is the variable that decides whitch player we are creating: Knight, Ranger or Mage
	// 1 for Knight
	// 2 for Ranger
	// 3 for Mage
	// else ERROR

	int lifePoints = 1;
	int manaPoints = 1;
	int actionPoints = 1;
	//TypeOfMovement movType = DEFAULT;
	PlayerState state = IDLE;
	bool isAlive = true;
	
private:

	

};

