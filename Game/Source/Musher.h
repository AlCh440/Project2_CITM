#pragma once
#include "Enemy.h"

class Musher : public Enemy
{
public:
	Musher(iPoint position);
	Musher(Collider_Type type, iPoint position);
	virtual ~Musher();

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
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;
	bool CalculateNextPatrolPoint();
	void UpdatePath();
	void Move(float dt);

public:

	float jumpForce = 0.2f;
	bool onGround = false;

	float detectionDistance = 10; // in pixels

	//in Tiles
	iPoint patrolPoint1;
	iPoint patrolPoint2;
	bool OnPatrolPoint = false;

	float speedMultiplier = 0.2f;// 1-0   1->slowest-> 0.1 fastest;

	enum MusherState {
		PATROL = 0,
		MOVE_TOWARDS = 1,
		JUMP = 2,
		DEATH = 3
	};
	MusherState state;
	bool LoadRequest = false;

	int curretnTileIndex =0;
};