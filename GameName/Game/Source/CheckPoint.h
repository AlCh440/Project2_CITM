#pragma once
#include "Entity.h"
class CheckPoint :   public Entity
{
public:
	CheckPoint(iPoint pos);
	CheckPoint(Collider_Type type, iPoint pos);

	void Open();
	void Transition();
	void Close();

	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;
private:
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool Cleanup();

public:
	enum CheckPointState
	{
		S_IDLE,
		S_TRANSITION,
		S_OPEN
	};
	CheckPointState state;
	Animation idleShrineAnim, transitionShrineAnim, openShrineAnim;
	int frameCounter;
};

