#pragma once
#include "Interactable.h"
#include "Door.h"
class DoorButton :  public Interactable
{
	void Interact() override;
	Door* door;
};

