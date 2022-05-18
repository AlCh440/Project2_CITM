#pragma once
#include "Entity.h"
#include "App.h"
#include "LevelManagement.h"
#include "Animation.h"

class Trigger :  public Entity
{
public:
	Trigger();
	Trigger(Collider_Type type, iPoint pos);
	bool PostUpdate() override;
	bool Start();
	~Trigger();

	GameScene scene;
	int id;


};

