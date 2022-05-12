#include "Entity.h"
#include "App.h"
#include "Log.h"
#include "Physics.h"
#include "Audio.h"
#include "Render.h"
#include "Player.h"

Entity::Entity()
{
}

Entity::Entity(iPoint pos)
{
	position.x = pos.x;
	position.y = pos.y;
}

Entity::Entity(Collider_Type _type, iPoint pos)
{
	position.x = pos.x;
	position.y = pos.y;
	type = _type;
	battleState = IDLE;
	ConfirmMovement = false;
}

Entity::~Entity()
{
	if (physBody != nullptr)
		physBody->pendingToDelete = true;
	texture = nullptr;
	currentAnim = nullptr;

}

PhysBody* Entity::GetCollider() 
{
	return physBody;
}

bool Entity::Start()
{
	return true;
}

bool Entity::PreUpdate()
{
	
	return true;
}

bool Entity::Update(float dt)
{
	return true;
}

bool Entity::PostUpdate()
{
	return true;
}

void Entity::OnCollision(PhysBody* other)
{

}

void Entity::SetToDelete()
{
	if (physBody != nullptr)
		physBody->pendingToDelete = true;
}

bool Entity::Cleanup()
{
	if (physBody != nullptr) physBody->pendingToDelete = true;
	texture = nullptr;
	currentAnim = nullptr;
	return true;
}

bool Entity::LoadState(pugi::xml_node& data)
{
	return true;
}

bool Entity::SaveState(pugi::xml_node& data) const
{
	return true;
}

iPoint Entity::GetPosition()
{
	iPoint pos;
	physBody->GetPosition(pos.x,pos.y);
	return pos;
}

b2Vec2 Entity::GetPositionTileToMeters(iPoint pos)
{
	b2Vec2 newPos;
	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);
	newPos.x = pixelPos.x;
	newPos.y = pixelPos.y;
	return newPos;
}

iPoint Entity::GetPositionTiles()
{
	return iPoint();
}

void Entity::takeDamage(int damage)
{
	LOG("Ouch!");
	stats.hp -= damage;
	OnHit = true;

	if (stats.hp <= 0)
	{
		battleState = DEATH;
		LOG("Dead");
	}
}

void Entity::StartTurn()
{
	HasAttackAction = true;
	HasMoveAction = true;
	entityTurn = true;
}

int Entity::CheckDistanceToPhysBody(PhysBody* PhysPos)
{
	b2Vec2 dist = PhysPos->body->GetPosition() - physBody->body->GetPosition();

	return (abs(dist.x) + abs(dist.y));
}

void Entity::Interpolate(int x, int y, float speed)
{
	newX = (float)x;
	newY = (float)y + 16;
	if (!interpolating)
	{
		h = 0;
		iSpeed = speed;
		if (speed > 1) iSpeed = 1;
		if (speed < 0) iSpeed = 0;
		oldX = position.x + 16;
		oldY = position.y + 16;
		interpolating = true;

		pos_dif_x = newX - oldX;
		pos_dif_y = newY - oldY;
	
	}
	else {
		h += iSpeed;

		if (1 - h < 0)
			h = 1;


		float x_ = oldX + pos_dif_x * h;
		float y_ = oldY + pos_dif_y * h;

		b2Vec2 pos = { PIXEL_TO_METERS(x_),PIXEL_TO_METERS(y_) };
		physBody->body->SetTransform(pos, 0);

		physBody->GetPosition(position.x, position.y);
		if (h == 1)
		{
			interpolating = false;
			h = 0;
			stats.movement -= 1;
		}

	}
}

//Destination must be in map coordinates
bool Entity::InitPath(iPoint destiantion)
{
	bool ret = true;
	// Todo confirm choice 
	if (pathfinding->CreateVisitedPath(tilePos, destiantion) != -1)
	{
		Move = true;
	}
	else {
		LOG("Error creating path...");
		ret = false;
	}
	return ret;
}

//function to update the entity movement
bool Entity::MovePath()
{
	if (Move)
	{
		for (stepCounter; stepCounter < pathfinding->GetLastPath()->Count() && nextStep; )
		{
			nextStep = false;

			currentP = pathfinding->GetLastPath()->At(stepCounter);
			nextP = pathfinding->GetLastPath()->At(stepCounter + 1);


			//end movement
			if (nextP == nullptr)
			{
				Move = false;
				ExpandedBFS = false;
				nextStep = true;
				pathfinding->ResetBFSPath();
				stepCounter = 0;
				battleState = IDLE;
				HasMoveAction = false;
				return true;
			}

			//calculate movement direction
			direction = new iPoint;
			direction->x = nextP->x - currentP->x;
			direction->y = nextP->y - currentP->y;

			//error control and set anim
			if (direction->x >= 1)
			{
				direction->x = 1;
				currentAnim = &walkSide;
			}
			else if (direction->x <= -1)
			{
				direction->x = -1;
				currentAnim = &walkSide;
			}
			else {
				direction->x = 0;
				walkSide.Reset();
			}

			if (direction->y >= 1)
			{
				direction->y = 1;
				currentAnim = &walkDown;
			}
			else if (direction->y <= -1)
			{
				direction->y = -1;
				currentAnim = &walkUp;
			}
			else {
				direction->y = 0;
				walkUp.Reset();
				walkDown.Reset();
			}
			stepCounter++;
		}

		counter -= 1;
		if (counter >= 0 && !nextStep)
		{
			//move
			position.x += direction->x;
			position.y += direction->y;

			//get next tile world position
			iPoint p;
			p = app->map->MapToWorld(nextP->x, nextP->y);

			//get the "correct" position
			iPoint pUpleft;
			pUpleft.x = position.x - app->map->mapData.tileWidth * 0.5f;
			pUpleft.y = position.y - app->map->mapData.tileHeight * 0.5f;

			// check if is in destination position
			if (pUpleft.x == p.x && pUpleft.y == p.y)
			{
				nextStep = true;

				//store the entity position in tiles
				iPoint pos;
				pos.x = position.x;
				pos.y = position.y;
				pos = app->map->WorldToMap(pos.x, pos.y);

				tilePos = pos;
			}

			counter = moveTime;
		}
	}

	return false;
}

void Entity::ChangeBattleSate(BattleSates state)
{
	if (!Move)
	{
		ExpandedBFS = false;
		pathfinding->ResetBFSPath();
		pathfinding->ClearPath();
		battleState = state;
	}
}