#pragma once
#include "Entity.h"
class Portal :    public Entity
{
public:
	Portal(iPoint pos);
	Portal(Collider_Type type, iPoint pos);

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
	Animation idlePortalAnim, transitionPortalAnim, openPortalAnim;
	enum PortalState
	{
		P_IDLE,
		P_TRANSITION,
		P_OPEN
	};
	PortalState portalState;
};

