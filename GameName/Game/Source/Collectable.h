#pragma once
#include "Entity.h"
class Collectable :   public Entity
{
public:
	Collectable(iPoint pos);
	Collectable(Collider_Type type,iPoint pos);
	~Collectable();
protected:
	SDL_Rect r;
};

