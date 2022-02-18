#pragma once
#include "Collectable.h"
class HPotion :   public Collectable
{
public:
	HPotion(iPoint pos);
	HPotion(Collider_Type type, iPoint pos);

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;
private:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Cleanup();
};

