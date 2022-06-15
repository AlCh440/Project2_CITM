#pragma once
#include "Enemy.h"
#include "Pathfinding.h"

class EnemySnake : public Enemy
{
public:

	EnemySnake(iPoint pos);
	EnemySnake(Collider_Type type, iPoint pos);
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

	Animation GetAnimIdle()
	{
		return idle;
	}

protected:
	int scorePoints = 0;	
	bool NewTarget = false;

	int timer = 0;
	int timerRef = 40;

	uint tileMove;
	uint mummyDeath;
	uint mummyAttack;
private:
};

