#pragma once
#include "Module.h"
#include "p2List.h"
#include "App.h"
#include "Physics.h"
#include "Point.h"
#include "Entity.h"

#include "Player.h"
#include "Knight.h"
#include "Ranger.h"

#include "Enemy.h"
#include "EnemyDummy.h"
#include "Goblin.h"
#include "KingGoblin.h"
#include "Npc.h"
#include "NpcDummy.h"
#include "NpcGuard.h"
#include "NpcWoVillager.h"
#include "CheckPoint.h"
#include "Trigger.h"


#define MAX_ENTITIES 150
#define SPAWN_MARGIN 20

class DialogManager;

class NpcDummy;
class NpcGuard;
class NpcWoVillager;

//class Entity;
// this will be deleted
//class EnemyDummy;
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

	//used to add entities 
	Entity* AddEntity(Collider_Type type ,iPoint spawnPos, p2List <Item*> items = p2List<Item*>());

	//remove entity with the physBody reference
	void RemoveEntity(PhysBody* entity);
	void RemoveAllEntities();

	// return the closest hitbox
	PhysBody* GetNearestEnemy(PhysBody* Character);
	Entity* GetNearestPlayer(Entity* Character);

	

	//Check all entity collisions here
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;

	// All spawned enemies in the scene
	p2List<Entity*> entities;
	p2List<Enemy*> enemies;
	p2List<Player*> players;
	OpenWorldPlayer* openWorld;
	// Check player turn state
	bool CheckPlayerTurn();

	// Start players turn
	void StartPlayerTurn();

	// Start enemies turn
	void StartEnemiesTurn();

	//
	void NextEnemyTurn();

	//returns entity in a tile
	Entity* GetEntityFromTile(iPoint pos);

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	//Player instance reference
	Player* playerInstance;

	//CheckPoint list reference
	p2List<CheckPoint*> checkPoint;

	//Instances 
	Knight* knightInstance;
	Ranger* rangerInstance;
	OpenWorldPlayer* openWorldInstance;
	EnemyDummy* dummyInstance;
	Goblin* goblinInstance;
	KingGoblin* kingGoblinInstance;
	NpcDummy* dummyNpcInstance;
	NpcGuard* dummyNpcGuardInstance;
	NpcWoVillager* dummyNpcWoVillagerInstance;
	Item* itemInstance;

	// triggers to move room to room
	Trigger* entranceIntance;
	Trigger* exitIntance;

	Trigger* generalEntrance;
	Trigger* mageEntrance;
	Trigger* shopEntrance;
	p2List<Trigger*> listOfCombatTriggers;

	//triggers to enter locations


	int enemiesAlive;
};

