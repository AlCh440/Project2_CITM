#pragma once
#include "Enemy.h"



class Bat : public Enemy
{
public:
	Bat(iPoint pos);
	Bat(Collider_Type type, iPoint pos);
	virtual ~Bat();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void SetPosition(iPoint pos);
	fPoint GetPosition() { return position; };
	void Spawn(iPoint pos);
	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	bool CalculateNextPatrolPoint();
	void UpdatePath();
	void Move(float dt);


public:
	bool onGround = false;
	int counter = 0;

	//in Tiles
	iPoint patrolPoint1;
	iPoint patrolPoint2;
	bool OnPatrolPoint = false;
	bool LoadRequest = false;

	float speedMultiplier = 0.2f;// 1-0   1->slowest-> 0.1 fastest;

	enum BatState {
		PATROL = 0,
		MOVE_TOWARDS = 1,
		JUMP = 2,
		DEATH = 3
	};
	BatState state;


	int curretnTileIndex = 0;

};
