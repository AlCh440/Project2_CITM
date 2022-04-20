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
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");	
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_dynamicBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

	stats.hp = 10;

}

EnemyDummy::EnemyDummy(Collider_Type type, iPoint pos) : Enemy(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
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
					}
					else if (going->x > positionToMap.x) // RIGHT
					{
						Interpolate(position.x + 32, position.y, inter_speed);
					}
					else if (going->y < positionToMap.y) // UP
					{
						Interpolate(position.x, position.y - 32, inter_speed);
					}
					else if (going->y > positionToMap.y) // DOWN
					{
						Interpolate(position.x, position.y + 32, inter_speed);
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


	app->render->DrawTexture(texture, position.x, position.y);
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