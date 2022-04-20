#include "Trigger.h"

Trigger::Trigger() : Entity()
{
	scene = GameScene::NONE;
}

Trigger::Trigger(Collider_Type type, iPoint pos) : Entity(type, pos)
{
}

Trigger::~Trigger()
{
}
