#include "Entity.h"
#include "App.h"
#include "ModulePhysics.h"
#include "Audio.h"
#include "Render.h"
#include "Player.h"

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

const PhysBody* Entity::GetCollider() const
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
	physBody->pendingToDelete = true;
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
