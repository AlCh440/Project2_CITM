#include "Item.h"
#include "Entities.h"

Item::Item(iPoint pos) : Entity(pos)
{
}

Item::Item(Collider_Type type, iPoint pos) : Entity(type, pos)
{
}

bool Item::Start()
{
	return true;
}

bool Item::PreUpdate()
{
	return true;
}

bool Item::Update(float dt)
{
	return true;
}

bool Item::CleanUp()
{
	return true;
}

bool Item::PostUpdate()
{
	return true;
}

void Item::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
