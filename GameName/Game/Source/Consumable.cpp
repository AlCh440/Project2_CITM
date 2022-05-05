#include "Consumable.h"
#include "Item.h"

Consumable::Consumable(iPoint pos) : Item(pos)
{

}

Consumable::Consumable(Collider_Type type, iPoint pos) : Item(type, pos)
{

}

bool Consumable::Start()
{
	return true;
}

bool Consumable::PreUpdate()
{
	return true;
}

bool Consumable::Update(float dt)
{
	return true;
}

bool Consumable::CleanUp()
{
	return true;
}

bool Consumable::PostUpdate()
{
	return true;
}

void Consumable::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
