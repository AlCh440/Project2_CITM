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
	physBody = app->physics->CreateCircle(pos.x, pos.y, 36.f*0.5f, b2_staticBody);
	physBody->entityPtr = this;

	stats.hp = 10;

}

EnemyDummy::EnemyDummy(Collider_Type type, iPoint pos) : Enemy(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 36.f * 0.5f, b2_kinematicBody);
	physBody->entityPtr = this;
	
	stats.hp = 10;
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
		//app->entities->playerInstance->position.x
		//if (METERS_TO_PIXELS(app->entitymanager->player->GetColHitbox()->body->GetPosition().x) > 0)
		if (METERS_TO_PIXELS(app->entities->playerInstance->position.x) > 0)
		{
			actualStates = ATTACK;
			
			if (app->entities->knightInstance->stats.hp <= 0) // and other players
			{
				actualStates = WALK;
			}
		}
		else
		{
			actualStates = WALK;
		}
	
	}
	
	//if (app->entities->playerInsttance.win == true) // revise
	//{
	//	actualStates = WALK;
	//}
	
	
	switch (actualStates)
	{
	case WALK:
	{
		physBody->GetPosition(position.x, position.y);
		
		directionPoint = app->map->WorldToMap(position.x, position.y);
	
	
		//iPoint playerPos;
	
		//EntityCollider->GetPosition(position.x, position.y);
		//directionPoint = app->map->WorldToMap(position.x, position.y);
	
		//playerPos = app->map->WorldToMap(playerPos.x + 15, playerPos.y + 15);
	
		app->pathFinding->CreatePath(directionPoint, { 29,6 });
	
		iPoint NextPos;
	
		const DynArray<iPoint>* lastPath = app->pathFinding->GetLastPath();
	
		if (lastPath->Count() > 1)
		{
			iPoint path(lastPath->At(1)->x, lastPath->At(1)->y);
			NextPos = path;
		}
	
		directionPoint = NextPos;
	
		if (app->physics->debug == true)
		{
			const DynArray<iPoint>* path = app->pathFinding->GetLastPath();
	
			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				//app->render->DrawTexture(, pos.x, pos.y);
				app->pathFinding->DrawPath();
			}
		}
	
	}break;
	case ATTACK:
	{
		physBody->GetPosition(position.x, position.y);
		directionPoint = app->map->WorldToMap(position.x, position.y);
	
	
		iPoint playerPos;
		//app->entitymanager->player->GetColHitbox()->GetPosition(playerPos.x, playerPos.y);
		playerPos.x = app->entities->playerInstance->position.x;
		playerPos.y = app->entities->playerInstance->position.y;
	
		physBody->GetPosition(position.x, position.y);
		directionPoint = app->map->WorldToMap(position.x, position.y);
	
		playerPos = app->map->WorldToMap(playerPos.x + 15, playerPos.y + 15);
	
		app->pathFinding->CreatePath(directionPoint, playerPos);
	
		iPoint NextPos;
	
		const DynArray<iPoint>* lastPath = app->pathFinding->GetLastPath();
	
		if (lastPath->Count() > 1)
		{
			iPoint path(lastPath->At(1)->x, lastPath->At(1)->y);
			NextPos = path;
		}
	
		directionPoint = NextPos;
	
		if (app->physics->debug == true)
		{
			const DynArray<iPoint>* path = app->pathFinding->GetLastPath();
	
			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				//app->render->DrawTexture(app->lvlmanager->pathTex, pos.x, pos.y);
				app->pathFinding->DrawPath();
			}
		}
	
	}break;
	case DIE:
	{
		physBody->GetPosition(position.x, position.y);
		directionPoint = app->map->WorldToMap(position.x, position.y);
	
	}break;
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