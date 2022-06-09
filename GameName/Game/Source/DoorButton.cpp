#include "DoorButton.h"

void DoorButton::Interact()
{
	if (door != nullptr)
	{
		door->Open = !door->Open;
	}
}
