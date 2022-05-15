#pragma once
#include "Enemy.h"
#include "Pathfinding.h"

class Goblin : public Enemy
{
public:

	Goblin(iPoint pos);
	Goblin(Collider_Type type, iPoint pos);
	//virtual void Move(float dt);
	virtual void UpdatePath();

	//int hitPoints;
	//int score;
	float detectionDistance = 10; // in pixels

	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;

	bool BasicAttack(); // pass an Player


	bool Start() override;

	bool CleanUp() override;


	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;


	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;

protected:
	int scorePoints = 0;
	bool NewTarget = false;
private:
};