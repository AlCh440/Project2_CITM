#ifndef __INTRO_H__
#define __INTRO_H__

#include "Module.h"
#include "p2List.h"
#include "Defs.h"
#include "Physics.h"
#include "Animation.h"

struct SDL_Texture;
class EnemyDummy;

class Intro : public Module
{
public:

	Intro(bool isActive);

	// Destructor
	virtual ~Intro();

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

	uint intro;
private:
	SDL_Texture* img;
	SDL_Rect rect;
	
	bool playintro = true;

	int waitTime;

	int logoXpos;
	float easingTime = 500; //millisec
	float counter = 0;
};

#endif // __INTRO_H__
