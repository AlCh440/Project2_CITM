#include "ManaPotion.h"
#include "Player.h"
#include "Entities.h"


ManaPotion::ManaPotion(Consumable_Type id) : Consumable(id)
{
	consumableId = id;
	itemType = POTION_MANA_;
}

bool ManaPotion::Start()
{
	return true;
}

bool ManaPotion::PreUpdate()
{
	return true;
}

bool ManaPotion::Update(float dt)
{
	return true;
}

bool ManaPotion::CleanUp()
{
	return true;
}

bool ManaPotion::PostUpdate()
{
	return true;
}

void ManaPotion::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void ManaPotion::Consume(Player* user)
{
	user->stats.mana += 50;
	//HAS TO DELETE ITSELF
}
