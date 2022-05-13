#include "Mage.h"
#include "Defs.h"
#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "Entities.h"
#include "Physics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Map.h"
#include "Log.h"
#include "Player.h"

// Update Code

bool Mage::Start()
{

	stats.hp = 50;
	stats.mana = 100;
	typeOfPlayer = 3;
	actionPoints = 10; // To determine
	isAlive = true;
	// movement t defined in th spawn
	// physBody = app->physics->CreateCircle(30, 30, 15, b2_kinematicBody);
	return true;
}

bool Mage::PreUpdate()
{

	//if (state == COMBATMOVE)
	//{
	//	if (lifePoints > 0)
	//	{
	//		isAlive = true;
	//	}
	//	else
	//	{
	//		isAlive = false;
	//		CleanUp();
	//	}
	//}
	//else
	//{

	//}



	return true;
}

bool Mage::Update(float dt)
{


	return true;
}

bool Mage::PostUpdate()
{


	return true;
}

bool Mage::CleanUp()
{
	// destroy the physbody

	return true;
}

// Mage 

bool Mage::MagicMissile()
{


	return true;
}

bool Mage::Heal()
{


	return true;
}

bool Mage::PowerfullStrike()
{


	return true;
}

// OnCollision
void Mage::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool Mage::LoadState(pugi::xml_node& data)
{


	return true;
}

bool Mage::SaveState(pugi::xml_node& data) const
{


	return true;
}