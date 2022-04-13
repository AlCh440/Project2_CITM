#include "Npc.h"

Npc::Npc(iPoint pos) : Entity(pos)
{
}

Npc::Npc(Collider_Type type, iPoint pos) : Entity(type, pos)
{
}

bool Npc::Start() { return true; }
bool Npc::PreUpdate() { return true; }
bool Npc::Update(float dt) { return true; }
bool Npc::CleanUp() { return true; }
bool Npc::PostUpdate() { return true; }

// Collision response
void Npc::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {}