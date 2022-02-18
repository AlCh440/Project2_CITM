#pragma once
#include "Module.h"
#include "p2List.h"
#include "App.h"
#include "ModulePhysics.h"
#include "Point.h"
#include "Entity.h"
#include "Player.h"
#include "Portal.h"
#include "CheckPoint.h"

#define MAX_ENTITIES 150
#define SPAWN_MARGIN 20



class Entity;
struct SDL_Texture;
struct PhysicBody;

class ModuleEntities :   public Module
{
public:
	ModuleEntities(bool isActive);
	~ModuleEntities();
	bool Awake();
	bool Start();
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;
	void AddEntity(Collider_Type type ,iPoint spawnPos);
	void RemoveEntity(PhysBody* entity);
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

	// All spawned enemies in the scene
	Entity* entities[MAX_ENTITIES] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	//Player instance reference
	Player* playerInstance;

	Portal* portalInstance;
//	CheckPoint* checkPoint;
	p2List<CheckPoint*> checkPoint;

	//should not be here
	int playerLives,coinsCollected = 0;

	int coinFx, hitFx;
	
};

