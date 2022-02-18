#include "Collectable.h"
Collectable::Collectable(iPoint pos) : Entity(pos)
{
}

Collectable::Collectable(Collider_Type type, iPoint pos) : Entity(type, pos)
{
}