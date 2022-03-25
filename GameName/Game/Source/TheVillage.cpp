#include "TheVillage.h"

TheVillage::TheVillage(bool isActive) : Module(isActive)
{
	name.Create("The Village");
}

TheVillage::~TheVillage()
{
}

bool TheVillage::Awake()
{
	return true;
}

bool TheVillage::Start()
{
	return true;
}

bool TheVillage::PreUpdate()
{
	return true;
}

bool TheVillage::Update(float dt)
{
	return true;
}

bool TheVillage::PostUpdate()
{
	return true;
}

bool TheVillage::CleanUp()
{
	return true;
}
