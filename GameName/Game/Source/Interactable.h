#ifndef __INTERACTABLE_H__
#define __INTERACTABLE_H__

#include "SString.h"
#include "Entity.h"
#include "Entities.h"
class OpenWorldPlayer;
class  Interactable : public Entity
{
public:
	Interactable(Collider_Type type, iPoint pos);
	~Interactable();

	void BaseInteract() { Interact(); };
	virtual void Interact() {};

	bool Update(float dt) override;
	bool CheckInteractionDistance();
	bool PostUpdate();
	bool OnRange = false;
	float interactionRange = 45;
	SString message;

	SDL_Texture* interactTex;
	OpenWorldPlayer* player;
};
#endif //__INTERACTABLE_H__
