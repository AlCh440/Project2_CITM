#include "TheFall.h"

TheFall::TheFall(bool isActive) : Module(isActive)
{
	name.Create("The fall");
}

TheFall::~TheFall()
{
}

bool TheFall::Awake()
{
	return true;
}

bool TheFall::Start()
{
	return true;
}

bool TheFall::PreUpdate()
{
	return true;
}

bool TheFall::Update(float dt)
{
	return true;
}

bool TheFall::PostUpdate()
{
	return true;
}

bool TheFall::CleanUp()
{
	return true;
}
