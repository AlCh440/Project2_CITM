#include "FracturedRoad.h"

FracturedRoad::FracturedRoad(bool isActive) : Module(isActive)
{
	name.Create("Fractured Road");
}

FracturedRoad::~FracturedRoad()
{
}

bool FracturedRoad::Awake()
{
	return true;
}

bool FracturedRoad::Start()
{
	return true;
}

bool FracturedRoad::PreUpdate()
{
	return true;
}

bool FracturedRoad::Update(float dt)
{
	return true;
}

bool FracturedRoad::PostUpdate()
{
	return true;
}

bool FracturedRoad::CleanUp()
{
	return true;
}
