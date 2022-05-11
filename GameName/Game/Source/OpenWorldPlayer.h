#pragma once
#include "Entity.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Player.h"
#include "Item.h"

class Item;

class OpenWorldPlayer : public Player
{
public:

	OpenWorldPlayer(iPoint pos);// remember to define the type of player
	OpenWorldPlayer(Collider_Type type, iPoint pos);
	~OpenWorldPlayer();

	//bool BasicAttack(); // pass an ennemy
	

	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;


	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;
	void SetMotion(bool active)
	{
		canMove = active;
	}

	bool CanMove() const
	{
		return canMove;
	}

	float32 velocity = 7;

	p2List <Item*> inventory;
	Item* knightEquiped;
	Item* MageEquiped;

private:

	Animation walkUp;
	Animation walkDown;
	Animation walkSide;
	Animation idle;
	float walkSpeed;

	bool goingLeft;
	bool AdminMode;
	bool canMove;
};