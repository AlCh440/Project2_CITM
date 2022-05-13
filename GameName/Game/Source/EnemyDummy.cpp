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
	stats.movement = 10;
	moveTime = 32; //milisec
	counter = moveTime;
	moveRange = 5;
	Start();
}

//void EnemyDummy::Move(float dt)
//{
//}

void EnemyDummy::UpdatePath()
{
}

bool EnemyDummy::Start()
{



	//actualStates = WALK;
	

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
	switch (battleState)
	{
	case IDLE:
		//Nothing to do
		//if (entityTurn)
		//{
		//	battleState = MOVE;
		//}
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

bool EnemyDummy::Update(float dt)
{	
	switch (battleState)
	{
	case IDLE:
		//Nothing to do
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

				PhysBody* aux = app->entities->GetNearestPlayer(physBody);
				if (InitPath(aux->entityPtr->tilePos)) {
					NewTarget = true;
				}
			}
		}

		if (MovePath()) {
			entityTurn = false;
			NewTarget = false;
		}
		currentAnim = &idle;
		break;
	case ATTACK:
		//Search for target
		break;
	case DEATH:
		break;
	default:
		break;
	}

	currentAnim->Update();
	return true;
}

bool EnemyDummy::PostUpdate()
{

	switch (battleState)
	{
	case IDLE:
		//Nothing to do
		break;
	case MOVE:
	{
		//Search for new pos//Draw path
		const DynArray<iPoint>* path = pathfinding->GetLastPath();

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


	//render current tile pos
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