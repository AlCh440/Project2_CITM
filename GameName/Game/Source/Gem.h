#pragma once
#include "Collectable.h"
class Gem : public Collectable
{
public:
    Gem(iPoint pos);
    Gem(Collider_Type type,iPoint pos);

    bool LoadState(pugi::xml_node& data);
    bool SaveState(pugi::xml_node& data) const;
private:
    bool Start();
    bool Update(float dt);
    bool PostUpdate();
    bool Cleanup();
};

