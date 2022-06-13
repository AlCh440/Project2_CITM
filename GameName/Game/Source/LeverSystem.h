

#pragma once
#include "Entity.h"
#include "Door.h"
#include "Lever.h"
class LeverSystem :public Entity
{
public :
	LeverSystem(Collider_Type type, iPoint pos);
	~LeverSystem();
	bool Start() override;
	bool PreUpdate()override;
	bool Update(float dt)override;
	bool Cleanup() override;
	p2List<Lever*> levers;
	bool Open;
	bool t1,t2,t3;
	Door* door;
	//to identify what system is and match the levers and the door;
	int id;

	enum State {
		NONE,
		T1,
		T2,
		T3,
	};
	State state = NONE;

};

