#pragma once
#include "Collectable.h"
class Key :  public Collectable
{
public:
	Key(iPoint pos);
	Key(Collider_Type type, iPoint pos);

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

private:
	bool Start();
	bool Update();
	bool PostUpdate();
	bool Cleanup();
};

