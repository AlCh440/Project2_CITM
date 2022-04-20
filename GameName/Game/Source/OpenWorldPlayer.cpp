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
	stats.momevent = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;

	currentAnim = &walkSide;

	walkSide.PushBack({ 0, 0, 32, 48 });
	walkSide.PushBack({ 32, 0, 32, 48 });
	walkSide.PushBack({ 64, 0, 32, 48 });
	walkSide.PushBack({ 96, 0, 32, 48 });
	walkSide.loop = true;
	walkSide.speed = 0.1f;


	walkDown.PushBack({ 0, 48, 32, 48 });
	walkDown.PushBack({ 32, 48, 32, 48 });
	walkDown.PushBack({ 64, 48, 32, 48 });
	walkDown.PushBack({ 96, 48, 32, 48 });
	walkDown.loop = true;
	walkDown.speed = 0.1f;


	walkUp.PushBack({ 0, 96, 32, 48 });
	walkUp.PushBack({ 32, 96, 32, 48 });
	walkUp.PushBack({ 64, 96, 32, 48 });
	walkUp.PushBack({ 96, 96, 32, 48 });
	walkUp.loop = true;
	walkUp.speed = 0.1f;

	idle.PushBack({ 0, 48, 32, 48 });
	idle.loop = false;
	idle.speed = 0.2f;
	return true;
}

bool OpenWorldPlayer::PreUpdate()
{



	return true;
}

bool OpenWorldPlayer::Update(float dt)
{

	
	app->render->CameraFocus(fPoint{ (float)position.x, (float)position.y });



	bool goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	bool goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);
	bool goUp = (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT);
	bool goDown = (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT);

	b2Vec2 movement = { (goRight - goLeft) * velocity, (goDown - goUp) * velocity };

	physBody->body->SetLinearVelocity(movement);
	physBody->GetPosition(position.x, position.y);

	if (movement.x > 0)
	{
		currentAnim = &walkSide;
		goingLeft = false;
	}
	else if (movement.x < 0)
	{
		currentAnim = &walkSide;
		goingLeft = true;
	}
	else if (movement.y < 0)
	{
		currentAnim = &walkUp;
		goingLeft = false;
	}
	else if (movement.y > 0)
	{
		currentAnim = &walkDown;
		goingLeft = false;
	}
	else
	{
		currentAnim = &idle;
	}
	return true;
}

bool OpenWorldPlayer::PostUpdate()
{
	currentAnim->Update();

	if (goingLeft)
	{
		app->render->DrawTexture(texture, position.x - 20, position.y - 20, &currentAnim->GetCurrentFrame());
	}
	else
	{
		app->render->DrawTexture(texture, position.x - 20, position.y - 20, &currentAnim->GetCurrentFrame(), 1.0f, 0.0f, 2147483647, 2147483647, 1.0f, SDL_FLIP_HORIZONTAL);
	}

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