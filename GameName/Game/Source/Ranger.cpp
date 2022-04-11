#include "Ranger.h"
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

bool Ranger::Start()
{

	lifePoints = 75;
	manaPoints = 75;
	typeOfPlayer = 2;
	actionPoints = 10; // To determine
	isAlive = true;
	// movement t defined in th spawn
	// physBody = app->physics->CreateCircle(30, 30, 15, b2_kinematicBody);
	return true;
}

bool Ranger::PreUpdate()
{

	if (movType == COMBATMOVE)
	{
		if (lifePoints > 0)
		{
			isAlive = true;
		}
		else
		{
			isAlive = false;
			CleanUp();
		}
	}
	else
	{

	}



	return true;
}

bool Ranger::Update(float dt)
{


	return true;
}

bool Ranger::PostUpdate()
{


	return true;
}

bool Ranger::CleanUp()
{
	// destroy the physbody

	return true;
}

// Ranger 

bool Ranger::BasicAttack() // pass an ennemy
{


	return true;
}

bool Ranger::PrecisionShot()
{


	return true;
}

bool Ranger::MultyShot()
{


	return true;
}

bool Ranger::PowerfullStrike()
{


	return true;
}

// OnCollision
void Ranger::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool Ranger::LoadState(pugi::xml_node& data)
{


	return true;
}

bool Ranger::SaveState(pugi::xml_node& data) const
{


	return true;
}