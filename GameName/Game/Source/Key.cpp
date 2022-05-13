#include "Key.h"

Key::Key(int id_) : Item()
{
	keyId = id_;
	itemType = itemType::KEY_;
}

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

int Key::GetKeyId()
{
	return keyId;
}

void Key::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
