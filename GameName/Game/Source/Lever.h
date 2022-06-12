#pragma once
#include "Interactable.h"
#include "Door.h"
class Lever :  public Interactable
{
public:
	Lever(Collider_Type type, iPoint pos);
	~Lever();
	bool Start() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	void Interact() override;
	Door* door;
	bool active;
	int id;
	SDL_Rect r;
	SDL_Texture* buttonTex;
};

