#include "TheRuins.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Entities.h"
#include "Audio.h"
#include "Physics.h"
#include "GuiManager.h"

TheRuins::TheRuins(bool isActive) : Module(isActive)
{
	name.Create("The_Ruins");
	toSave = false;
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
	app->guiManager->OpenPanel(P_QUEST);
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
