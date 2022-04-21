#include "EnemyDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Enemy.h"
#include "Entities.h"
#include "Player.h"
#include "Physics.h"
#include "Pathfinding.h"

#include "Log.h"

EnemyDummy::EnemyDummy(iPoint pos) : Enemy(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/EnemigosProvisional.png");	
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_dynamicBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

	stats.hp = 10;

}

EnemyDummy::EnemyDummy(Collider_Type type, iPoint pos) : Enemy(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/EnemigosProvisional.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);
	
	stats.hp = 10;
	stats.momevent = 10;
}

void EnemyDummy::Move(float dt)
{
}

void EnemyDummy::UpdatePath()
{
}

bool EnemyDummy::Start()
{

	actualStates = WALK;
	pathfinding = new PathFinding(true);
	//create navigation map
	int w, h;
	uchar* data = NULL;
	if (app->map->CreateWalkabilityMap(w, h, &data, 1)) pathfinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);

	inter_speed = 0.02f;

	
	idle.PushBack({ 0, 48 * 3, 48, 48 });
	idle.PushBack({ 48 * 1, 48 * 3, 48, 48 });
	idle.PushBack({ 48 * 2, 48 * 3, 48, 48 });
	idle.PushBack({ 48 * 3, 48 * 3, 48, 48 });
	idle.PushBack({ 48 * 4, 48 * 3, 48, 48 });
	idle.PushBack({ 48 * 5, 48 * 3, 48, 48 });
	idle.PushBack({ 48 * 6, 48 * 3, 48, 48 });
	idle.PushBack({ 48 * 7, 48 * 3, 48, 48 });
	idle.speed = 0.1f;

	inter_speed = 0.02f;

	currentAnim = &idle;
	
	return true;
}

bool EnemyDummy::PreUpdate()
{
	return true;
}

bool EnemyDummy::Update(float dt)
{	
	PhysBody* aux = app->entities->GetNearestPlayer(physBody);

	if (stats.hp <= 0)
	{
		
		//actualStates = DIE;
		//isAlive = false;
	}
	else
	{
		if (aux != nullptr && interpolating == false)
		{
			actualStates = WALK;
		}
		
		if (interpolating)
		{
			actualStates = INTERPOLATING;
		}
	}

	
	switch (actualStates)
	{
	case WALK:
	{

		physBody->GetPosition(position.x, position.y);
		positionToMap = app->map->WorldToMap(position.x, position.y);

		iPoint goingPoint(aux->entityPtr->position.x, aux->entityPtr->position.y);
		goingPoint = app->map->WorldToMap(goingPoint.x, goingPoint.y);

		int distanceInTiles = pathfinding->CreatePath(positionToMap, goingPoint);

		if (distanceInTiles > 2)
		{
			iPoint* going = pathfinding->GetLastPath()->At(1);
			if (going != nullptr)
			{
				if (stats.momevent > 0)
				{

					if (going->x < positionToMap.x) // LEFT
					{
						Interpolate(position.x - 32, position.y, inter_speed);
						--stats.momevent;
					}
					else if (going->x > positionToMap.x) // RIGHT
					{
						Interpolate(position.x + 32, position.y, inter_speed);
						--stats.momevent;
					}
					else if (going->y < positionToMap.y) // UP
					{
						Interpolate(position.x, position.y - 32, inter_speed);
						--stats.momevent;
					}
					else if (going->y > positionToMap.y) // DOWN
					{
						Interpolate(position.x, position.y + 32, inter_speed);
						--stats.momevent;
					}
				}
				else
				{
					//CAN ATTACK???
				}
			}

		}

	}break;
	case INTERPOLATING:
	{
		Interpolate(position.x, position.y, 0.02f);
	} break;
	default:
	{

	}break;
	}
		


	
	if (stats.momevent <= 0)
	{
		stats.momevent = 10;
		
		app->entities->NextEnemyTurn();
		entityTurn = false;
	}

	currentAnim->Update();
	return true;
}

bool EnemyDummy::PostUpdate()
{


	//Draw path
	const DynArray<iPoint>* path = pathfinding->GetLastPath();

	SDL_Rect rect;
	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		rect.x = (pos.x);
		rect.y = (pos.y);
		rect.w = (app->map->mapData.tileWidth);
		rect.h = (app->map->mapData.tileHeight);
		app->render->DrawRectangle(rect, 255, 125, 0, 150);
	}


	app->render->DrawTexture(texture, position.x, position.y, &currentAnim->GetCurrentFrame());

	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);



	return true;
}

bool EnemyDummy::CleanUp()
{

	
	return true;
}

bool EnemyDummy::BasicAttack() // pass an Player
{
	return true;
}

// 
void EnemyDummy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool EnemyDummy::LoadState(pugi::xml_node& data)
{
	return true;
}

bool EnemyDummy::SaveState(pugi::xml_node& data) const
{
	return true;
}