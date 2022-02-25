#include "CheckPoint.h"
#include "Entities.h"

CheckPoint::CheckPoint(iPoint pos) : Entity(pos)
{
	name = "checkpoint";
}

CheckPoint::CheckPoint(Collider_Type type, iPoint pos) : Entity(pos)
{
}

void CheckPoint::Open()
{
}

void CheckPoint::Transition()
{
}

void CheckPoint::Close()
{
}

bool CheckPoint::LoadState(pugi::xml_node& data)
{
	return false;
}

bool CheckPoint::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node entity = data.append_child("CheckPoint");
	entity.append_attribute("type") = physBody->type;;
	entity.append_attribute("x") = position.x;
	entity.append_attribute("y") = position.y;
	return true;
}

bool CheckPoint::Start()
{
	

	return true;
}

bool CheckPoint::PreUpdate()
{
	return true;
}

bool CheckPoint::Update(float dt)
{

	return true;
}

bool CheckPoint::PostUpdate()
{
	
	return true;
}

bool CheckPoint::Cleanup()
{
	return true;
}
