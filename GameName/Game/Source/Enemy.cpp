#include "Enemy.h"

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

bool Enemy::Start()
{
	return false;
}

bool Enemy::PreUpdate()
{
	return false;
}

bool Enemy::Update(float dt)
{
	return false;
}

bool Enemy::CleanUp()
{
	return false;
}

bool Enemy::PostUpdate()
{
	return false;
}

void Enemy::OnCollision(PhysBody* other)
{
}
