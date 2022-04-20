#pragma once
#include "Entity.h"
#include "App.h"
#include "LevelManagement.h"


class Trigger :  public Entity
{
public:
	Trigger();
	Trigger(Collider_Type type, iPoint pos);
	~Trigger();

	GameScene scene;
};

