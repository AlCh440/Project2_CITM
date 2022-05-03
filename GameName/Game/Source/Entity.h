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
#include "Pathfinding.h"

struct SDL_Texture;
struct PhysicBody;

struct Statistics
{
	int hp;
	int mana;
	int baseDamage;
	int movement;
};
enum BattleSates {
	MOVE,			//Find a target positin, move to it
	ATTACK,			//Show selected attack range, use it
	DEATH,			//Display death animation
	IDLE			//Entity in idle state waiting turn
};

class Entity abstract
{
public:

	// Constructor
	// Saves the spawn position for later movement calculations
	Entity();
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
	iPoint GetPositionTiles();
	void SetPositionPixels();

	Statistics stats;



//----------------------------------------------------------------------------
// Common scene elements
//----------------------------------------------------------------------------
public:
	void takeDamage(int damage);
	// Returns distance to a point
	int CheckDistanceToPhysBody(PhysBody* PhysPos);
	// The current position in the world
	iPoint spawnPos;
	iPoint position;
	fPoint centerPosition;//for rigidBody
	fPoint texPosition; //for texture position
	iPoint drawOffset = { 0, 0 };
	Collider_Type type;

	// The Entity's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	//if debug mode
	bool DEBUG;

	//If Enemy
	PhysBody* physBody = nullptr;

	//Entity Name
	SString name;

	PathFinding* pathfinding;

	// Used to activate and regulate turns
	bool entityTurn = false;

	bool Pause = false;

	void Interpolate(int x, int y, float speed);

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	Animation walkSide;
	Animation walkUp;
	Animation walkDown;
	Animation idle;
//----------------------------------------------------------------------------
// Battle scene elements
//----------------------------------------------------------------------------
public:
	iPoint tilePos;
	bool ExpandedBFS;
	bool ConfirmMovement;
	BattleSates battleState;

	bool InitPath(iPoint destiantion);
	bool MovePath();
	void DrawPath();
protected:
	iPoint* currentP;
	iPoint* nextP;
	iPoint* direction;
	//counts the tiles advanced in combat mode
	int stepCounter = 0; 
	int moveRange;
	int attackRange;
	bool Move;
	bool nextStep = true;
	float moveTime ;
	float counter = 0;

	float iSpeed;
	bool interpolating = false;
	float oldX;
	float oldY;
	float newX;
	float newY;
	float pos_dif_x;
	float pos_dif_y;
	float h = 0;
	float inter_speed;
private:

//----------------------------------------------------------------------------
// World scene elements
//----------------------------------------------------------------------------
public:
	int interactionRange;
protected:
	void WorldMove();
private:

};

#endif // __ENTITY_H__