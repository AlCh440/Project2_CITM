#include "HPPotion.h"
#include "Player.h"
#include "Entities.h"


HPPotion::HPPotion(Consumable_Type id) : Consumable(id)
{
	consumableId = id;
	itemType = POTION_HP_;
}

bool HPPotion::Start()
{
	return true;
}

bool HPPotion::PreUpdate()
{
	return true;
}

bool HPPotion::Update(float dt)
{
	return true;
}

bool HPPotion::CleanUp()
{
	return true;
}

bool HPPotion::PostUpdate()
{
	return true;
}

void HPPotion::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void HPPotion::Consume(Player* user)
{
	user->stats.hp += 50;
	//HAS TO DELETE ITSELF
}
