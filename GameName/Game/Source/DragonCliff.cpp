#include "DragonCliff.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"

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
