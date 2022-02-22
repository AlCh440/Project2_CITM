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
