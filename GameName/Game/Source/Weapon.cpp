#include "Weapon.h"
#include "Item.h"

Weapon::Weapon(iPoint pos) : Item(pos)
{
}

Weapon::Weapon(Collider_Type type, iPoint pos) : Item(type, pos)
{
}

bool Weapon::Start()
{
	return true;
}

bool Weapon::PreUpdate()
{
	return true;
}

bool Weapon::Update(float dt)
{
	return true;
}

bool Weapon::CleanUp()
{
	return true;
}

bool Weapon::PostUpdate()
{
	return true;
}

void Weapon::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
