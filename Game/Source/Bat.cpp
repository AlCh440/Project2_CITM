#include "Bat.h"
#include "Globals.h"
#include "App.h"
#include "Map.h"
#include "Input.h"
#include "Player.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "ModuleEntities.h"
#include "Render.h"
#include "Log.h"

Bat::Bat(iPoint pos) : Enemy(pos)
{
	spawnPos = pos;
}
Bat::Bat(Collider_Type type, iPoint pos) : Enemy(pos)
{


	spawnPos = pos;
}

Bat::~Bat()
{

}

bool Bat::Awake()
{
	return true;
}

bool Bat::Start()
{
	LOG("BAT START");

		texture = app->tex->Load("Assets/Spritesx16/bat.png");
		//Idle anim
		idleAnim.PushBack({ 7, 0, 18, 8 });
		idleAnim.PushBack({ 40, 0, 16, 9  });
		idleAnim.PushBack({ 74, 0, 12, 10 });
		idleAnim.PushBack({ 105, 0, 14, 11 });
		idleAnim.PushBack({ 135, 2 , 18, 9 });
		idleAnim.PushBack({ 166, 2, 20, 8 });
		idleAnim.PushBack({ 198, 2, 21, 7 });
		idleAnim.PushBack({ 232, 1, 17, 7  });
		idleAnim.PushBack({ 264, 0, 17, 7 });
		idleAnim.PushBack({ 295, 0, 19, 8 });
		idleAnim.loop = true;
		idleAnim.mustFlip = true;
		idleAnim.speed = 0.2f;
		//death anim
		deathAnim.PushBack({ 128, 0, 32, 32 });
		deathAnim.PushBack({ 128, 32, 32, 32 });
		deathAnim.PushBack({ 128, 64, 32, 32 });
		deathAnim.PushBack({ 128, 96, 32, 32 });
		deathAnim.PushBack({ 128, 128, 32, 32 });
		deathAnim.PushBack({ 128, 160, 32, 32 });
		deathAnim.PushBack({ 128, 192, 32, 32 });
		deathAnim.PushBack({ 128, 124, 32, 32 });
		deathAnim.PushBack({ 128, 156, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 128, 188, 32, 32 });
		deathAnim.PushBack({ 0, 0, 0, 0 });
		deathAnim.loop = false;
		deathAnim.mustFlip = true;
		deathAnim.speed = 0.15f;

		currentAnim = &idleAnim;
		physBody = app->physics->CreateCircle(position.x, position.y, 8, b2_dynamicBody, { 0,400,125,255 });
		physBody->listener = app->entities;
		physBody->color = { 255,255,0,255 };
		physBody->type = Collider_Type::BAT;

		type = physBody->type;

		physBody->body->SetFixedRotation(true);
		app->physics->allPhysicBodies.add(physBody);

		position.x = physBody->body->GetPosition().x;
		position.y = physBody->body->GetPosition().y;
		lastPosition = position;

		state = PATROL;

		//make the path 
		pathfinding = new PathFinding(true);

		lives = 1;

		int w, h;
		uchar* data = NULL;
		if (app->map->CreateWalkabilityMap(w, h, &data,2)) pathfinding->SetMap(w, h, data);
		RELEASE_ARRAY(data);
	
	return true;
}

bool Bat::PreUpdate()
{

	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	float distanceToPlayer = position.DistanceTo(app->entities->playerInstance->position);

	switch (state)
	{
	case PATROL:

		physBody->body->SetLinearVelocity({ 0,-0.2f });
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
		if (counter > 10)
		{
			counter = 0;
		}
		counter++;
		break;
	case JUMP:
		break;
	case DEATH:
		currentAnim = &deathAnim;
		break;
	default:
		break;
	}

	return true;
}

bool Bat::Update(float dt)
{
	switch (state)
	{
	case PATROL:
		
		break;
	case MOVE_TOWARDS:
		Move(dt);
		break;
	case JUMP:
		break;
	case DEATH:
		break;
	default:
		break;
	}
	currentAnim->Update();
	return true;
}

bool Bat::PostUpdate()
{

	const DynArray<iPoint>* path = pathfinding->GetLastPath();
	if (DEBUG)
	{
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

	b2Vec2 newPos;
	newPos.x = lastPosition.x;
	newPos.y = lastPosition.y;


	lastPosition = position;

	SDL_Rect* rect;
	rect = &currentAnim->GetCurrentFrame();
	if (texture != nullptr)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - rect->w), METERS_TO_PIXELS(physBody->body->GetPosition().y - rect->h),
			&currentAnim->GetCurrentFrame(), 1, spriteRotation, rect->w, rect->h, 1.8f, spriteDir);

	switch (state)
	{
	case PATROL:
		break;
	case MOVE_TOWARDS:
		break;
	case JUMP:
		break;
	case DEATH:
		if (currentAnim->HasFinished())
		{
			//physBody->pendingToDelete = true;
			//app->physics->entities.del(app->physics->entities.findNode(physBody));
			//CleanUp();
			//active = false;
		}
		break;
	default:
		break;
	}

	return true;
}

bool Bat::CleanUp()
{
	//delete physBody;
	//physBody = nullptr;
	//delete currentAnim;
	//currentAnim = nullptr;
	return true;
}

void Bat::Spawn(iPoint pos)
{
	SetPosition(pos);
	state = PATROL;
}

bool Bat::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	position.x = data.child("bat").attribute("x").as_int();
	position.y = data.child("bat").attribute("y").as_int();
	state = static_cast<BatState>(data.child("bat").attribute("state").as_int());

	LoadRequest = true;

	return ret;
}

bool Bat::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node bat = data.append_child("bat");
	bat.append_attribute("type") = physBody->type;;
	bat.append_attribute("x") = position.x;
	bat.append_attribute("y") = position.y;
	bat.append_attribute("state") = state;
	return ret;
}

bool Bat::CalculateNextPatrolPoint()
{
	iPoint destination;
	iPoint origin;

	return true;
}

void Bat::UpdatePath()
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

void Bat::Move(float dt)
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
				spriteDir = SDL_FLIP_HORIZONTAL;
			if (direction.x < 0)
				spriteDir = SDL_FLIP_NONE;

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

void Bat::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);

	physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}