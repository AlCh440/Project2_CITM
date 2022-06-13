#pragma once
#include "Interactable.h"
#include "Door.h"
class DoorButton : public Interactable
{
public:
	DoorButton(Collider_Type type, iPoint pos);
	~DoorButton();
	bool Start() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	void Interact() override;


	Door* door;
	bool Pressed;
	int id;
	SDL_Rect r;
	SDL_Texture* buttonTex;

	int counter;
	int time = 32;
};

