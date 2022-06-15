
#include "LeverSystem.h"

LeverSystem::LeverSystem(Collider_Type type, iPoint pos) : Entity(type, pos)
{
	this->type = type;
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	physBody->body->SetActive(false);

}

LeverSystem::~LeverSystem()
{
}

bool LeverSystem::Start()
{
	state = NONE;
	return true;
}

bool LeverSystem::PreUpdate()
{
	return true;
}

bool LeverSystem::Update(float dt)
{
	Lever* lever1 = new Lever();
	Lever* lever2 = new Lever();
	Lever* lever3 = new Lever();

	levers.at(0, lever1);
	levers.at(1, lever2);
	levers.at(2, lever3);




	switch (state)
	{
	case NONE:

		if ((lever1 != nullptr) && (lever2 != nullptr) && (lever3 != nullptr))
		{
			if (lever1->active && !lever2->active && !lever3->active)
				state = T1;

			Open = false;
		}
		
		break;

	case LeverSystem::T1:

		if (lever1->active && lever2->active && !lever3->active)
			state = T2;
		break;

	case LeverSystem::T2:
		if (lever1->active && lever2->active && lever3->active)
			state = T3;
		break;

	case LeverSystem::T3:
		Open = true;
		door->OpenDoor();
		break;

	default:
		break;
	}
	
	

	return true;
}

bool LeverSystem::Cleanup()
{
	door = nullptr;
	levers.clear();
	return true;
}
