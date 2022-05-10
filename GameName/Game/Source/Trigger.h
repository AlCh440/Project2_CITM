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
	~Trigger();

	GameScene scene;
	int id;


};

