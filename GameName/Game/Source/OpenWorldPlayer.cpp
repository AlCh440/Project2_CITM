#include "OpenWorldPlayer.h"
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
OpenWorldPlayer::OpenWorldPlayer(Collider_Type type, iPoint pos) : Player(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 36.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	entityTurn = true;
}

OpenWorldPlayer::~OpenWorldPlayer()
{
		
}

bool OpenWorldPlayer::Start()
{
	stats.hp = 100;
	stats.mana = 50;
	stats.momevent = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;

	return true;

}

bool OpenWorldPlayer::PreUpdate()
{



	return true;
}

bool OpenWorldPlayer::Update(float dt)
{

	
	app->render->CameraFocus(fPoint{ physBody->body->GetPosition().x,physBody->body->GetPosition().y });

	if ((app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN))
	{
		physBody->body->SetLinearVelocity(b2Vec2{ -velocity,0 });
	}
	else if ((app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN))
	{
		physBody->body->SetLinearVelocity(b2Vec2{ velocity,0 });
	}
	else if ((app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN))
	{
		physBody->body->SetLinearVelocity(b2Vec2{ 0,-velocity });
	}
	else if ((app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) || (app->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN))
	{
		physBody->body->SetLinearVelocity(b2Vec2{ 0,velocity });
	}
	else {
		physBody->body->SetLinearVelocity(b2Vec2{ 0,0 });
	}
	
	physBody->GetPosition(position.x, position.y);

	return true;
}

bool OpenWorldPlayer::PostUpdate()
{
	app->render->DrawTexture(texture, position.x , position.y );

	return true;
}

bool OpenWorldPlayer::CleanUp()
{
	// destroy the physbody

	return true;
}


// OnCollision
void OpenWorldPlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool OpenWorldPlayer::LoadState(pugi::xml_node& data)
{


	return true;
}

bool OpenWorldPlayer::SaveState(pugi::xml_node& data) const
{


	return true;
}