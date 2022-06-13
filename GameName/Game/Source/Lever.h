#pragma once
#ifndef __LEVER_H__
#define __LEVER_H__

#include "Interactable.h"
class Lever :  public Interactable
{
public:
	Lever(Collider_Type type, iPoint pos);
	~Lever();

	bool Start() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	void Interact() override;
	bool active;
	int id;
	SDL_Rect r;
	SDL_Texture* buttonTex;
};
#endif // __LEVER_H__
