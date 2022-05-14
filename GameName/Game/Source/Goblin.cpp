#include "Goblin.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Enemy.h"
#include "Entities.h"
#include "Player.h"
#include "Physics.h"
#include "Pathfinding.h"

#include "Log.h"

Goblin::Goblin(iPoint pos) : Enemy(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/EnemigosProvisional.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_dynamicBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

	stats.hp = 10;

}

Goblin::Goblin(Collider_Type type, iPoint pos) : Enemy(type, pos)
{

	name.Create("Goblin");
	texture = app->tex->Load("Assets/Sprites/characters/EnemigosProvisional.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

	stats.hp = 15;
	stats.movement = 10;
	stats.baseDamage = 4;
	moveTime = 32; //milisec
	counter = moveTime;
	moveRange = 5;
	Start();
}


void Goblin::UpdatePath()
{
}

bool Goblin::Start()
{

	stepCounter = 0;
	moveRange = 5;
	pathfinding = new PathFinding(true);

	//create navigation map
	int w, h;
	uchar* data = NULL;
	if (app->map->CreateWalkabilityMap(w, h, &data, 1)) pathfinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);

	//store the entity position in tiles
	iPoint pos;
	pos.x = position.x;
	pos.y = position.y;
	pos = app->map->WorldToMap(pos.x, pos.y);

	tilePos = pos;


	inter_speed = 0.02f;

	


	inter_speed = 0.02f;

	currentAnim = &idle;

	return true;
}

bool Goblin::PreUpdate()
{


	switch (battleState)
	{
	case IDLE:
	{
		//store the entity position in tiles
		iPoint pos;
		pos.x = position.x;
		pos.y = position.y;
		pos = app->map->WorldToMap(pos.x, pos.y);

		tilePos = pos;

		if (OnHit)
			currentAnim = &hit;

		if (entityTurn)
		{

			if (battleState == DEATH)
				break;
			if (target == nullptr)
			{
				target = app->entities->GetNearestPlayer(physBody)->entityPtr;
			}
			else {

				if (HasAttackAction && pathfinding->CreatePath(tilePos, target->tilePos) <= 2)
				{
					battleState = ATTACK;
					attack.Reset();
					currentAnim = &attack;
				}
				else if (HasMoveAction)
				{
					battleState = MOVE;
					currentAnim = &idle;
				}
				else
				{
					// if has mmoved and has no range then, has no attack action
					HasAttackAction = false;
				}
			}
		}
		//if has no attack and no move action end turn
		if (!HasAttackAction && !HasMoveAction) {
			entityTurn = false;
		}

	}
	break;
	case MOVE:
		//Search for new pos
		break;
	case ATTACK:
		//Search for target
		break;
	case DEATH:
		break;
	default:
		break;
	}
	return true;
}

bool Goblin::Update(float dt)
{
	switch (battleState)
	{
	case IDLE:
		//Nothing to do
		if (OnHit)
		{
			if (currentAnim->HasFinished()) {
				OnHit = false;
				hit.Reset();
				currentAnim = &idle;
			}
		}
		break;
	case MOVE:
		if (!Move) {

			//Set available movement tiles
			if (!NewTarget)
			{
				pathfinding->InitBFS(tilePos);
				for (int i = 0; i < stats.movement * moveRange; i++)
				{
					pathfinding->PropagateBFS();
				}

				pathfinding->GenerateWalkeableArea(tilePos, stats.movement);


				PhysBody* aux = app->entities->GetNearestPlayer(physBody);
				if (InitPath(aux->entityPtr->tilePos)) {
					NewTarget = true;
				}
			}
		}

		if (MovePath()) {
			NewTarget = false;
			currentAnim = &idle;
		}
		break;
	case ATTACK:
		//Search for target
		if (target != nullptr && currentAnim->HasFinished())
		{
			target->takeDamage(stats.baseDamage);
			HasAttackAction = false;
			currentAnim = &idle;
			battleState = IDLE;
		}
		break;
	case DEATH:
		break;
	default:
		break;
	}

	currentAnim->Update();
	return true;
}

bool Goblin::PostUpdate()
{
	//render current tile pos
	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);
	switch (battleState)
	{
	case IDLE:
		//Nothing to do
		break;
	case MOVE:
	{
		//Search for new pos//Draw path
		const DynArray<iPoint>* path = pathfinding->GetLastPath();
		if (path != nullptr)
		{
			SDL_Rect rect;
			for (uint i = 0; i < path->Count(); ++i)
			{
				iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
				rect.x = (pos.x);
				rect.y = (pos.y);
				rect.w = (app->map->mapData.tileWidth);
				rect.h = (app->map->mapData.tileHeight);
				app->render->DrawRectangle(rect, 255, 125, 125, 150);
			}
		}
	}
	break;
	case ATTACK:
		//Search for target
		break;
	case DEATH:
		break;
	default:
		break;
	}

	//render entity
	app->render->DrawTexture(texture, position.x - 24, position.y - 32, &currentAnim->GetCurrentFrame());

	return true;
}

bool Goblin::CleanUp()
{
	physBody->pendingToDelete = true;

	return true;
}

bool Goblin::BasicAttack() // pass an Player
{
	return true;
}

// 
void Goblin::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool Goblin::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Goblin::SaveState(pugi::xml_node& data) const
{
	return true;
}
