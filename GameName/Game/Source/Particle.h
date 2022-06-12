#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "Animation.h"
#include "Point.h"

struct Particle
{
public:
	// Constructor
	Particle();

	// Copy constructor
	Particle(const Particle& p);

	// Called in ModuleParticles' Update
	// Handles the logic of the particle
	// Returns false when the particle reaches its lifetime
	bool Update();

	enum ParticleType
	{
		DEFAULT = 0,
		LEAF = 1,
		DUST = 2,
		LIGHT = 3,
		FIREFLY = 4
	};

public:
	// Defines the position in the screen
	fPoint position;

	// Defines the speed at which the particle will move (pixels per second)
	fPoint speed;
	fPoint accel;

	// A set of rectangle sprites
	Animation anim;

	// Defines wether the particle is alive or not
	// Particles will be set to not alive until "spawnTime" is reached
	bool isAlive = false;

	// Defines the amout of frames this particle has been active
	// Negative values mean the particle is waiting to be activated
	int frameCount = 0;

	// Defines the total amount of frames during which the particle will be active
	uint lifetime = 0;
};

#endif //__PARTICLE_H__