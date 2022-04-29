#include "Entity.h"


class WorldSpace abstract : public Entity
{
public:

	// Constructor
	// Saves the spawn position for later movement calculations
	WorldSpace();
	WorldSpace(iPoint pos);
	WorldSpace(Collider_Type _type, iPoint pos);

};