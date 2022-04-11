#include "DragonCliff.h"

DragonCliff::DragonCliff(bool isActive) : Module(isActive)
{
	name.Create("Dragon's Cliff");
}

DragonCliff::~DragonCliff()
{
}

bool DragonCliff::Awake(pugi::xml_node&)
{
	return true;
}

bool DragonCliff::Start()
{
	return true;
}

bool DragonCliff::PreUpdate()
{
	return true;
}

bool DragonCliff::Update(float dt)
{
	return true;
}

bool DragonCliff::PostUpdate()
{
	return true;
}

bool DragonCliff::CleanUp()
{
	return true;
}
