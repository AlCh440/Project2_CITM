#include "Knight.h"
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

bool Knight::Start()
{

	lifePoints = 100;
	manaPoints = 50;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	// movement t defined in th spawn
	// physBody = app->physics->CreateCircle(30, 30, 15, b2_kinematicBody);
	return true;
}

bool Knight::PreUpdate()
{

	if(state == COMBATMOVE)
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

bool Knight::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		state = FREEMOVE;
	}
	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		state = COMBATMOVE;
	}

	switch (state)
	{
	case COMBATMOVE:
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		{
			position.x -= 48;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			position.x += 48;
		}
		else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			position.y -= 48;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		{
			position.y += 48;
		}
	}break;
	case FREEMOVE:
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == (KEY_REPEAT || KEY_DOWN))
		{
			position.x -= 2;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == (KEY_REPEAT || KEY_DOWN))
		{
			position.x += 2;
		}
		else if (app->input->GetKey(SDL_SCANCODE_W) == (KEY_REPEAT || KEY_DOWN))
		{
			position.y -= 2;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == (KEY_REPEAT || KEY_DOWN))
		{
			position.y += 2;
		}
	} break;
	default:
	{

	}break;
	}


	return true;
}

bool Knight::PostUpdate()
{


	return true;
}

bool Knight::CleanUp()
{
	// destroy the physbody

	return true;
}

// Knight 

bool Knight::BasicAttack() // pass an ennemy
{


	return true;
}

bool Knight::TauntHability()
{


	return true;
}

bool Knight::BindHability()
{


	return true;
}

bool Knight::ConcusionHability()
{


	return true;
}

// OnCollision
void Knight::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool Knight::LoadState(pugi::xml_node& data) 
{


	return true;
}

bool Knight::SaveState(pugi::xml_node& data) const
{


	return true;
}