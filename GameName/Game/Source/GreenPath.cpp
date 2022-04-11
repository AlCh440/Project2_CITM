#include "GreenPath.h"

GreenPath::GreenPath(bool isActive) : Module(isActive)
{
	name.Create("Green Path");
}

GreenPath::~GreenPath()
{
}

bool GreenPath::Awake(pugi::xml_node&)
{
	return true;
}

bool GreenPath::Start()
{
	return true;
}

bool GreenPath::PreUpdate()
{
	return true;
}

bool GreenPath::Update(float dt)
{
	return true;
}

bool GreenPath::PostUpdate()
{
	return true;
}

bool GreenPath::CleanUp()
{
	return true;
}
