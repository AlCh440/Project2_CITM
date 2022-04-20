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
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	stats.hp = 100;
	stats.mana = 50;
	stats.momevent = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	state = COMBATMOVE;
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

	currentAnim = &walkSide;

	walkSide.PushBack({0, 0, 32, 48});
	walkSide.PushBack({32, 0, 32, 48});
	walkSide.PushBack({64, 0, 32, 48});
	walkSide.PushBack({96, 0, 32, 48});
	walkSide.loop = false;
	walkSide.speed = 0.2f;
	

	walkDown.PushBack({ 0, 48, 32, 48 });
	walkDown.PushBack({ 32, 48, 32, 48 });
	walkDown.PushBack({ 64, 48, 32, 48 });
	walkDown.PushBack({ 96, 48, 32, 48 });
	walkDown.loop = false;
	walkDown.speed = 0.2f;


	walkUp.PushBack({ 0, 96, 32, 48 });
	walkUp.PushBack({ 32, 96, 32, 48 });
	walkUp.PushBack({ 64, 96, 32, 48 });
	walkUp.PushBack({ 96, 96, 32, 48 });
	walkUp.loop = false;
	walkUp.speed = 0.2f;

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
			position.x -= 32;
			stats.momevent -= 1;
			walkSide.Reset();
			currentAnim = &walkSide;
			goingLeft = true;
		}
		else if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
		{
			position.x += 32;
			stats.momevent -= 1;
			walkSide.Reset();
			currentAnim = &walkSide;
			goingLeft = false;

		}
		else if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
		{
			position.y -= 32;
			stats.momevent -= 1;
			walkSide.Reset();
			currentAnim = &walkUp;
			goingLeft = true;


		}
		else if (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		{
			position.y += 32;
			stats.momevent -= 1;
			walkSide.Reset();
			currentAnim = &walkDown;
			goingLeft = true;
		}

		b2Vec2 teleport = { PIXEL_TO_METERS((float)position.x),  PIXEL_TO_METERS((float)position.y) };
		physBody->body->SetTransform(teleport, 0.f);

	}break;
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

	if (goingLeft)
	{
		app->render->DrawTexture(texture, position.x - 20, position.y - 20, &currentAnim->GetCurrentFrame());
	}
	else
	{
		app->render->DrawTexture(texture, position.x - 20, position.y - 20, &currentAnim->GetCurrentFrame(), 1.0f, 0.0f, 2147483647, 2147483647, SDL_FLIP_HORIZONTAL);
	}
	currentAnim->Update();
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