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
Knight::Knight(Collider_Type type, iPoint pos) : Player(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 36.f * 0.5f, b2_staticBody);
	stats.hp = 100;
	stats.mana = 50;
	stats.momevent = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
}

bool Knight::Start()
{

	stats.hp = 100;
	stats.mana = 50;
	stats.momevent = 10;
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
		if (stats.hp > 0)
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
	LOG("%i", stats.momevent);

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		state = FREEMOVE;
	}
	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		state = COMBATMOVE;
	}
	if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		state = CHOOSINGATTACK;
	}
	switch (state)
	{
	case COMBATMOVE:
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
		{
			position.x -= 48;
			stats.momevent -= 1;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			position.x += 48;
			stats.momevent -= 1;
		}
		else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			position.y -= 48;
			stats.momevent -= 1;
		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		{
			position.y += 48;
			stats.momevent -= 1;
		}
	}break;
	case FREEMOVE:
	{
		if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN))
		{
			position.x -= 2;
		}
		else if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN))
		{
			position.x += 2;
		}
		else if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN))
		{
			position.y -= 2;
		}
		else if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN))
		{
			position.y += 2;
		}
	} break;
	case CHOOSINGATTACK:
	{
		if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
		{
			attackChoosed = TAUNT;
			state = CHOOSINGOBJECTIVE;
		}
		else if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
		{
			attackChoosed = BIND;
			state = CHOOSINGOBJECTIVE;
		}
		else if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
		{
			attackChoosed = CONCUSSION;
			state = CHOOSINGOBJECTIVE;
		}

	} break;
	case CHOOSINGOBJECTIVE:
	{
		switch (attackChoosed)
		{
		case CONCUSSION:
		{
			// THE PLAYER CHOOSES THE ENEMY HE WANTS, RIGHT NOW  IS JUST THE CLOSER!!!
			ConcusionHability(checkCloseEnemies());
			state = ATTACKING;

		} break;
		default:
		{

		} break;
		}

	} break;
	case ATTACKING:
	{
		state = COMBATMOVE;
	} break;
	default:
	{

	}break;
	}

	if (stats.momevent <= 0)
	{
		stats.momevent = 10;
		entityTurn = false;
	}

	return true;
}

bool Knight::PostUpdate()
{
	app->render->DrawTexture(texture, position.x - 20, position.y - 20);

	return true;
}

bool Knight::CleanUp()
{
	// destroy the physbody

	return true;
}

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

bool Knight::ConcusionHability(PhysBody* tarjet)
{
	tarjet->entityPtr->takeDamage(20);

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