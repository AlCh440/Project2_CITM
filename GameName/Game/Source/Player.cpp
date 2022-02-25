#include "Player.h"
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
#include <SDL/include/SDL_scancode.h>


Player::Player(iPoint pos) : Entity(pos)
{
	name = "player"; // Maybe change when we create multiple characters
}

Player::Player(Collider_Type type, iPoint pos) : Entity(type, pos)
{
}

Player::~Player()
{
}

// Load assets
bool Player::Start()
{
	//Initializing player struct data
	
	return true;
}

bool Player::PreUpdate()
{
	
	return true;
}


bool Player::Update(float dt)
{
	bool ret = true;



	return ret;

}

bool Player::PostUpdate()
{

	return true;
}

// Unload assets
bool Player::CleanUp()
{
	physBody->pendingToDelete = true;
	physBody = nullptr;
	currentAnim = nullptr;
	
	return true;
}

void Player::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);
	if (physBody->body != nullptr)
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}

void Player::Spawn(iPoint pos)
{
	SetPosition(pos);
}

void Player::Movement()
{

}

void Player::MeleeAttack()
{
	
}

void Player::SkillAttack()
{

}

void GodMovement() 
{

}

void UpdateSensorsPosition()
{

}

void Player::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if ((bodyA != nullptr) && (bodyB != nullptr))
	{

	}
}

bool Player::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	return ret;
}

bool Player::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	return ret;
}