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



bool Enemy::Start() { return true; }
bool Enemy::PreUpdate() { return true; }
bool Enemy::Update(float dt) { return true; }
bool Enemy::CleanUp() { return true; }
bool Enemy::PostUpdate() { return true; }

// Collision response
void Enemy::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {}
