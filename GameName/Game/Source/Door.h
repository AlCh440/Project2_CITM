#pragma once
#include "Entity.h"
class Door : public Entity
{
	bool Start() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool Cleanup() override;
public:
	bool Open;
	PhysBody* left,right;
};

