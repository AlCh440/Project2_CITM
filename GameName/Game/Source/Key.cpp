#include "Key.h"

Key::Key(iPoint pos) : Item(pos)
{
}

Key::Key(Collider_Type type, iPoint pos) : Item(type, pos)
{
}

bool Key::Start()
{
	return true;
}

bool Key::PreUpdate()
{
	return true;
}

bool Key::Update(float dt)
{
	return true;
}

bool Key::CleanUp()
{
	return true;
}

bool Key::PostUpdate()
{
	return true;
}

void Key::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
