#include "ModuleParticles.h"

#include "App.h"

#include "Textures.h"
#include "Render.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool isActive) : Module(isActive)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

	// Explosion Particle
	leaf_0.anim.PushBack({ 0, 0, 8, 8 });
	leaf_0.anim.PushBack({ 0, 0, 8, 8 });
	dust.speed = fPoint(0, 0);
	dust.accel = fPoint(0.01f, 0);
	dust.lifetime = 100;
	dust.anim.loop = true;
	leaf_0.anim.speed = 0.1f;

	// Laser Particle
	dust.anim.PushBack({ 8 * 5, 0, 8, 8 });
	dust.anim.PushBack({ 8 * 5, 0, 8, 8 });
	dust.speed = fPoint(0, 0);
	dust.accel = fPoint(0.01f, 0);
	dust.lifetime = 100;
	dust.anim.loop = true;
	dust.anim.speed = 0.1f;
}

ModuleParticles::~ModuleParticles()
{
	
}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = app->tex->Load("Assets/Sprites/Particles/particles.png");
	
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::Update(float dt)
{
	// TODO 2: Create a loop (for) to iterate all the particles

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::PostUpdate()
{
	// TODO 3: Create a loop (for) to iterate all the particle array to draw them if any particle is active 

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			app->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return true;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, uint delay)
{
	Particle* p = new Particle(particle);
	
	// TODO 1: Create the necesary variables for the Particles
	LOG("particle created");
	p->position.x = (float)x;						
	p->position.y = (float)y;						

	particles[lastParticle++] = p;
	lastParticle %= MAX_ACTIVE_PARTICLES;
}