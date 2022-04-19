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
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f*0.5f, b2_dynamicBody);
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
	
	return true;
}

bool EnemyDummy::PreUpdate()
{
	return true;
}

bool EnemyDummy::Update(float dt)
{	
	if (stats.hp <= 0)
	{
		
		//actualStates = DIE;
		//isAlive = false;
	}
	else
	{
		// test movement
		
	}

	

	if (stats.hp > 0)
	{
		PhysBody* aux = app->entities->GetNearestPlayer(physBody);
		

		physBody->GetPosition(position.x, position.y);
		positionToMap = app->map->WorldToMap(position.x, position.y);
		
		iPoint goingPoint(aux->entityPtr->position.x, aux->entityPtr->position.y);
		goingPoint = app->map->WorldToMap(goingPoint.x, goingPoint.y);

			int distanceInTiles = app->pathFinding->CreatePath(positionToMap, goingPoint);

		if (distanceInTiles > 2)
		{
			const iPoint* going(app->pathFinding->GetLastPath()->At(1));
			if (going != nullptr)
			{
				if (stats.momevent < 0)
				{
					if (going->x < position.x) // LEFT
					{
						position.x -= 16;
						stats.momevent -= 1;
					}
					else if (going->x > position.x) // RIGHT
					{
						position.x += 16;
						stats.momevent -= 1;
					}
					else if (going->y < position.y) // UP
					{
						position.y -= 16;
						stats.momevent -= 1;
					}
					else if (going->y > position.y) // DOWN
					{
						position.y += 16;
						stats.momevent -= 1;
					}
				}
				else
				{
					//CAN ATTACK???
				}
			}
			
		}


	
	}
	
	if (stats.momevent <= 0)
	{
		stats.momevent = 10;
		entityTurn = false;
		app->entities->NextEnemyTurn();
	}


	return true;
}

bool EnemyDummy::PostUpdate()
{

	app->render->DrawTexture(texture, position.x - 20, position.y - 20);
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