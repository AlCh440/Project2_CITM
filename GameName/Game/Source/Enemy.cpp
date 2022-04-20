#include "Enemy.h"
#include "Entities.h"

Enemy::Enemy(iPoint pos) : Entity(pos)
{
}

Enemy::Enemy(Collider_Type type, iPoint pos) : Entity(type,pos)
{
}

void Enemy::Move(float dt)
{
}

void Enemy::UpdatePath()
{
}



bool Enemy::Start() { return true; }
bool Enemy::PreUpdate() { return true; }
bool Enemy::Update(float dt) { return true; }
bool Enemy::CleanUp() { return true; }
bool Enemy::PostUpdate() { return true; }

// Collision response
void Enemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {}

PhysBody* Enemy::checkClosePlayers()
{
	PhysBody* player = app->entities->GetNearestPlayer(physBody);

	if (player == nullptr)
	{
		return nullptr;
	}

	iPoint a;
	iPoint b;
	player->GetPosition(a.x, a.y);
	a = app->map->WorldToMap(a.x, a.y);
	b = app->map->WorldToMap(position.x, position.y);
	int chosing = app->pathFinding->CreatePath(b, a);

	if (chosing < 3)
	{
		return player;
	}
	else return nullptr;
}
