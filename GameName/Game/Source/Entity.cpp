#include "Entity.h"
#include "App.h"
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

void Entity::takeDamage(int damage)
{
	stats.hp -= damage;
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