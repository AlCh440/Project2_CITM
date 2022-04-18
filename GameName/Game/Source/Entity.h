#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "App.h"
#include "Physics.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"

struct SDL_Texture;
struct PhysicBody;

struct Statistics
{
	int hp;
	int mana;
	int baseDamage;
	int momevent;
};

class Entity abstract
{
public:

	// Constructor
	// Saves the spawn position for later movement calculations
	Entity(iPoint pos);
	Entity(Collider_Type _type, iPoint pos);

	// Destructor
	virtual ~Entity();

	// Returns the Entity's collider
	PhysBody* GetCollider();

	virtual bool Start();
	virtual bool PreUpdate();
	// Updates animation and collider position
	virtual bool Update(float dt);

	// Called from ModuleEntitys' Update
	virtual bool PostUpdate();

	// Collision response
	virtual void OnCollision(PhysBody* other);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	virtual bool Cleanup();

	// Load / Save
	virtual bool LoadState(pugi::xml_node& data);
	virtual bool SaveState(pugi::xml_node& data) const;

	iPoint GetPosition();
	b2Vec2 GetPositionTileToMeters(iPoint pos);
	void SetPositionTiles();
	void SetPositionPixels();

	Statistics stats;
public:

	
	//enum State
	//{
	//	IDLE,
	//	MOVE,
	//	ATACK,
	//	DEATH,
	//	SCORE
	//};

	// The current position in the world
	iPoint spawnPos;
	iPoint position;
	fPoint centerPosition;//for rigidBody
	fPoint texPosition; //for texture position
	iPoint drawOffset = { 0, 0 };
	Collider_Type type;

	//HP
	

	// The Entity's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	//if debug mode
	bool DEBUG;

	//If Enemy
	//State state;
	PhysBody* physBody = nullptr;

	//Entity Name

	SString name;

	void takeDamage(int damage);

	// Used to activate and regulate turns
	bool entityTurn = false;

	// Returns distance to a point
	int CheckDistanceToPhysBody(PhysBody* PhysPos);

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;
	Animation score;

	// To check diretion anim
	bool goingLeft = true;
};

#endif // __ENTITY_H__