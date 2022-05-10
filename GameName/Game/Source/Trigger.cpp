#include "Trigger.h"

Trigger::Trigger() : Entity()
{
	scene = GameScene::NONE;
	id = -1;

	

}

Trigger::Trigger(Collider_Type type, iPoint pos) : Entity(type, pos)
{
}

Trigger::~Trigger()
{
}

bool Trigger::PostUpdate() 
{
	//texture

	return true;
}
