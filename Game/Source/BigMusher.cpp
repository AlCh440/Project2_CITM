#include "BigMusher.h"
#include "Globals.h"
#include "App.h"
#include "Map.h"
#include "Input.h"
#include "Player.h"
#include "ModulePhysics.h"
#include "ModuleEntities.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Log.h"
#include <math.h>

BigMusher::BigMusher(iPoint pos) : Enemy(pos)
{
	spawnPos = pos;
}
BigMusher::BigMusher(Collider_Type type, iPoint pos) : Enemy(pos)
{
	spawnPos = pos;
}

BigMusher::~BigMusher()
{
}

bool BigMusher::Awake()
{
	return true;
}

bool BigMusher::Start()
{
	LOG("big MUShER START");
	if (physBody == NULL)
	{
		texture = app->tex->Load("Assets/Spritesx16/characters.png");
		//Idle anim
		idleAnim.PushBack({ 256, 207, 22, 27 });
		idleAnim.PushBack({ 288, 207 , 22, 27 });
		idleAnim.PushBack({ 318, 207 , 22, 27 });
		idleAnim.PushBack({ 288, 207 , 22, 27 });
		idleAnim.loop = true;
		idleAnim.mustFlip = true;
		idleAnim.speed = 0.01f;
		//Walking anim
		walkingAnim.PushBack({ 256, 207, 27, 22 });
		walkingAnim.PushBack({ 288, 207 , 27, 22 });
		walkingAnim.PushBack({ 318, 207 , 27, 22 });
		walkingAnim.PushBack({ 288, 207 , 27, 22 });
		walkingAnim.loop = true;
		walkingAnim.mustFlip = true;
		walkingAnim.speed = 0.1f;

		currentAnim = &idleAnim;

		physBody = app->physics->CreateCircle(position.x, position.y, 16, b2_dynamicBody, { 0,400,125,255 });
		physBody->listener = app->entities;
		physBody->color = { 255,125,0,255 };
		physBody->type = Collider_Type::BIG_MUSHER;

		type = physBody->type;

		physBody->body->SetFixedRotation(true);
		app->physics->allPhysicBodies.add(physBody);

		//make the path 
		pathfinding = new PathFinding(true);

		lives = 10;

		int w, h;
		uchar* data = NULL;
		if (app->map->CreateWalkabilityMap(w, h, &data, 1)) pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);

		lives = 1;
		state = PATROL;
	}

	return true;
}

bool BigMusher::PreUpdate()
{

	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	float distanceToPlayer = position.DistanceTo(app->entities->playerInstance->position);

	switch (state)
	{
	case PATROL:
		if (OnPatrolPoint)
		{
			CalculateNextPatrolPoint();
		}
		if (distanceToPlayer < detectionDistance)
		{
			state = MOVE_TOWARDS;
		}

		break;
	case MOVE_TOWARDS:
		UpdatePath();
		if (distanceToPlayer > detectionDistance)
		{
			state = PATROL;
		}
		break;
	case JUMP:
		break;
	case DEATH:
		break;
	default:
		break;
	}

	return true;
}

bool BigMusher::Update(float dt)
{

	switch (state)
	{
	case PATROL:
		Move(dt);
		break;
	case MOVE_TOWARDS:
		Move(dt);
		break;
	case JUMP:
		break;
	case DEATH:
		app->scene2->KeysToTake--;
		break;
	default:
		break;
	}
	currentAnim->Update();
	return true;
}

bool BigMusher::PostUpdate()
{
	if (DEBUG)
	{
		const DynArray<iPoint>* path = pathfinding->GetLastPath();
		SDL_Rect rect;
		for (uint i = 0; i < path->Count(); ++i)
		{
			iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
			rect.x = (pos.x);
			rect.y = (pos.y);
			rect.w = (16);
			rect.h = (16);
			app->render->DrawRectangle(rect, 255, 125, 0, 150);
		}
	}

	SDL_Rect* rect;
	rect = &currentAnim->GetCurrentFrame();
	if (texture != nullptr)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - rect->w), METERS_TO_PIXELS(physBody->body->GetPosition().y - rect->h),
			&currentAnim->GetCurrentFrame(), 1, spriteRotation, rect->w, rect->h, 1.8f, spriteDir);
	return true;
}

bool BigMusher::CleanUp()
{
	//delete physBody;
	//delete physBody;
	//physBody = nullptr;
	//delete currentAnim;
	//currentAnim = nullptr;
	return true;
}

void BigMusher::Spawn(iPoint pos)
{
	SetPosition(pos);
}

bool BigMusher::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	Start();
	position.x = data.child("BigMusher").attribute("x").as_int();
	position.y = data.child("BigMusher").attribute("y").as_int();
	state = static_cast<BigMusherState>(data.child("BigMusher").attribute("state").as_int());

	LoadRequest = true;

	return ret;
}

bool BigMusher::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node musher = data.append_child("musher");
	musher.append_attribute("type") = physBody->type;
	musher.append_attribute("x") = position.x;
	musher.append_attribute("y") = position.y;
	musher.append_attribute("state") = state;
	return ret;
}

bool BigMusher::CalculateNextPatrolPoint()
{
	iPoint destination;
	iPoint origin;
	// in the destination calculate a new point
	origin.x = METERS_TO_PIXELS(origin.x);
	origin.y = METERS_TO_PIXELS(origin.y);
	//convert Pixels to Tiles
	origin = app->map->WorldToMap((int)origin.x, (int)origin.y);
	destination = patrolPoint1;
	pathfinding->CreatePath(origin, destination);
	//check if it is in the destination
	if (destination == origin)
	{
		if (destination == patrolPoint1)
		{
			destination = patrolPoint2;
		}
		else if (destination == patrolPoint2)
		{
			destination = patrolPoint1;
		}
	}
	//otherwise continue
	return true;
}

void BigMusher::UpdatePath()
{
	iPoint destination;
	destination.x = (int)app->entities->playerInstance->GetPosition().x;
	destination.y = (int)app->entities->playerInstance->GetPosition().y;
	//convert meters to pixels
	destination.x = METERS_TO_PIXELS(destination.x);
	destination.y = METERS_TO_PIXELS(destination.y);

	iPoint origin;
	origin.x = (int)physBody->body->GetPosition().x;
	origin.y = (int)physBody->body->GetPosition().y;
	//convert meters to pixels
	origin.x = METERS_TO_PIXELS(origin.x);
	origin.y = METERS_TO_PIXELS(origin.y);

	//convert Pixels to Tiles
	destination = app->map->WorldToMap(destination.x, destination.y);
	origin = app->map->WorldToMap((int)origin.x, (int)origin.y);

	pathfinding->CreatePath(origin, destination);
}

void BigMusher::Move(float dt)
{
	const DynArray<iPoint>* path = pathfinding->GetLastPath();
	if (path->At(1) != nullptr)
	{
		iPoint currentTile;
		iPoint nextTile;

		currentTile.x = METERS_TO_PIXELS(position.x) - 8;
		currentTile.y = METERS_TO_PIXELS(position.y) - 8;

		b2Vec2 distance;
		b2Vec2 direction;

		nextTile = app->map->MapToWorld(path->At(1)->x, path->At(1)->y);

		if (nextTile != currentTile)
		{
			position.x = physBody->body->GetPosition().x;
			position.y = physBody->body->GetPosition().y;
			currentTile.x = METERS_TO_PIXELS(position.x) - 8;
			currentTile.y = METERS_TO_PIXELS(position.y) - 8;

			direction.x = nextTile.x - currentTile.x;
			direction.y = nextTile.y - currentTile.y;

			if (direction.x >= 0)
				spriteDir = SDL_FLIP_NONE;
			if (direction.x < 0)
				spriteDir = SDL_FLIP_HORIZONTAL;

			if (direction.y <= 0 && spriteDir == SDL_FLIP_NONE)
			{
				spriteRotation = -90;

			}
			else if (direction.y <= 0 && spriteDir == SDL_FLIP_HORIZONTAL)
			{
				spriteRotation = 90;
			}
			else {
				spriteRotation = 0;
			}

			if (speedMultiplier > 1)
				speedMultiplier = 1;
			if (speedMultiplier < 0.1f)
				speedMultiplier = 0.1f;

			direction.x *= speedMultiplier;
			direction.y *= speedMultiplier;

			physBody->body->SetLinearVelocity(direction);
		}
	}
}

void BigMusher::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);

	if (physBody->body != nullptr)
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}