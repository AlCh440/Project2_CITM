#include "SString.h"
#include "Entity.h"
class  Interactable : Entity
{
	void BaseInteract() { Interact(); };
	virtual void Interact() {};

	SString message;
};

