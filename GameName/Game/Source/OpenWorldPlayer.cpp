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
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpriteSheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->listener = app->entities;
	physBody->color = { 255,155,255,255 };
	physBody->type = type;
	entityTurn = true;
}

OpenWorldPlayer::~OpenWorldPlayer()
{
		
}

bool OpenWorldPlayer::Start()
{
	stats.hp = 100;
	stats.mana = 50;
	stats.movement = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	canMove = true;

	currentAnim = &walkSide;
	walkSpeed = 0.1f;

	walkSide.PushBack({ 0, 0, 32, 48 });
	walkSide.PushBack({ 32, 0, 32, 48 });
	walkSide.PushBack({ 64, 0, 32, 48 });
	walkSide.PushBack({ 96, 0, 32, 48 });
	walkSide.loop = true;
	walkSide.speed = walkSpeed;


	walkDown.PushBack({ 0, 48, 32, 48 });
	walkDown.PushBack({ 32, 48, 32, 48 });
	walkDown.PushBack({ 64, 48, 32, 48 });
	walkDown.PushBack({ 96, 48, 32, 48 });
	walkDown.loop = true;
	walkDown.speed = walkSpeed;


	walkUp.PushBack({ 0, 96, 32, 48 });
	walkUp.PushBack({ 32, 96, 32, 48 });
	walkUp.PushBack({ 64, 96, 32, 48 });
	walkUp.PushBack({ 96, 96, 32, 48 });
	walkUp.loop = true;
	walkUp.speed = walkSpeed;

	idle.PushBack({ 0, 48, 32, 48 });
	idle.loop = false;
	idle.speed = walkSpeed;

	currentAnim = &idle;
	return true;
}

bool OpenWorldPlayer::PreUpdate()
{
	if (AdminMode)
	{
		if (!physBody->body->GetFixtureList()->IsSensor())
		{
			physBody->body->GetFixtureList()->SetSensor(true);
		}
		
	}
	else if (physBody->body->GetFixtureList()->IsSensor())
	{
		physBody->body->GetFixtureList()->SetSensor(false);
	}


	return true;

}

bool OpenWorldPlayer::Update(float dt)
{
	
	app->render->CameraFocus(position);

	bool goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	bool goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);
	bool goUp = (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT);
	bool goDown = (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT);

	b2Vec2 movement = { (float)(goRight - goLeft), (float)(goDown - goUp) };
	movement.Normalize();

	movement.x *= velocity;
	movement.y *= velocity;


	

	if (AdminMode)
	{
		if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			movement.x *= 2;
			movement.y *= 2;
		}

		physBody->body->SetLinearVelocity(movement);
	}
	else
	{
		if (CanMove())
		{
			physBody->body->SetLinearVelocity(movement);
		}
		else 
		{
			b2Vec2 v(0, 0);
			physBody->body->SetLinearVelocity(v);
		}
	}

	physBody->GetPosition(position.x, position.y);

	Animation* lastDirection = currentAnim;

	if (CanMove())
	{
		if (movement.x > 0)
		{
			currentAnim = &walkSide;
			lastDirection = &walkSide;
			lastDirection->speed = walkSpeed;
			goingLeft = false;
		}
		else if (movement.x < 0)
		{
			currentAnim = &walkSide;
			lastDirection = &walkSide;
			lastDirection->speed = walkSpeed;
			goingLeft = true;
		}
		else if (movement.y < 0)
		{
			currentAnim = &walkUp;
			lastDirection = &walkUp;
			lastDirection->speed = walkSpeed;
			goingLeft = false;
		}
		else if (movement.y > 0)
		{
			currentAnim = &walkDown;
			lastDirection = &walkDown;
			lastDirection->speed = walkSpeed;
			goingLeft = false;
		}
		else
		{
			currentAnim = lastDirection;
			lastDirection->Reset();
			lastDirection->speed = 0;
		}
	}
	else
	{
		currentAnim = lastDirection;
		lastDirection->Reset();
		lastDirection->speed = 0;
	}

	return true;
}

bool OpenWorldPlayer::PostUpdate()
{
	currentAnim->Update();

	if (goingLeft)
	{
		app->render->DrawTexture(texture, position.x - 0, position.y - 16, &currentAnim->GetCurrentFrame());
	}
	else
	{
		app->render->DrawTexture(texture, position.x - 0, position.y - 16, &currentAnim->GetCurrentFrame(), 1.0f, 0.0f, 2147483647, 2147483647, 1.0f, SDL_FLIP_HORIZONTAL);
	}


	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		AdminMode = !AdminMode;

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




	float x_ = data.child("player").attribute("x").as_int();
	float y_ = data.child("player").attribute("y").as_int();

	b2Vec2 pos = { PIXEL_TO_METERS(x_),PIXEL_TO_METERS(y_) };
	
	LOG("%i, %i", x_, y_);
	physBody->body->SetTransform(pos, 0);

	return true;
}

bool OpenWorldPlayer::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node enemy_ = data.append_child("player");
	
	iPoint pos(position.x, position.y);

	enemy_.append_attribute("x") = position.x;
	enemy_.append_attribute("y") = position.y;

	return true;
}