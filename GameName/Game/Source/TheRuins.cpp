#include "TheRuins.h"

TheRuins::TheRuins(bool isActive) : Module(isActive)
{
	name.Create("The Ruins");
}

TheRuins::~TheRuins()
{
}

bool TheRuins::Awake(pugi::xml_node&)
{
	return true;
}

bool TheRuins::Start()
{
	return true;
}

bool TheRuins::PreUpdate()
{
	return true;
}

bool TheRuins::Update(float dt)
{
	return true;
}

bool TheRuins::PostUpdate()
{
	return true;
}

bool TheRuins::CleanUp()
{
	return true;
}
