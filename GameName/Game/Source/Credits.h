#pragma once

#ifndef __CREDITS_H__
#define __CREDITS_H__

#include "Module.h"
#include "p2List.h"
#include "Defs.h"
#include "Physics.h"
#include "Animation.h"

struct SDL_Texture;
class EnemyDummy;

class Credits : public Module
{
public:

	Credits(bool isActive);

	// Destructor
	virtual ~Credits();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	uint credits;

private:

	SDL_Texture* img;
	SDL_Rect rect;
	uint music;
	bool playMusic = true;

	bool playCredits = true;

	int waitTime;

	int logoXpos;
	float easingTime = 500; //millisec
	float counter = 0;
};

#endif // __INTRO_H__
