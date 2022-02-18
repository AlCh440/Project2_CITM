#pragma once
#include "Module.h"
//#include "Entity.h"
#include "p2List.h"
#include "Box2D/Box2D/Box2D.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -25.0f

//#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
//#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define PIXELS_PER_METER 16.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.0625f // this is 1 / PIXELS_PER_METER !

#define RAD_PER_DEG ((float)180/b2_pi)
#define DEG_PER_RAD ((float)b2_pi/180)
#define RAD_TO_DEG(r) ((float) RAD_PER_DEG * r)
#define DEG_TO_RAD(r) ((float) DEG_PER_RAD * r)

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)


enum Collider_Type {

	GEM,
	KEY, 
	BAT,
	MUSHER,
	BIG_MUSHER,
	CHECK_POINT, 
	SPAWNER,
	DEATH,
	PORTAL,
	PLAYER,
	PLAYER_ATTACK,
	GROUND,
	ENEMY,
	POTION,
	PLAYER_X_SENSOR,
	PLAYER_Y_SENSOR,
	NO_TYPE
};

struct Color {
	float r, g, b, a;
};
// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}
	~PhysBody()
	{
		//if(body!=NULL)
		//body->GetWorld()->DestroyBody(body);
		listener = nullptr;
	}

	void GetPosition(int& x, int& y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	b2Color color;
public:
	int width, height;
	b2Body* body;
	Collider_Type type;
	Module* listener;
	bool pendingToDelete = false;
	int id;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(bool isActive);
	~ModulePhysics();

	bool Awake();
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	void Disable();
	bool CleanUp();
	void RemoveBodyFromWorld(b2Body *body);
	void DrawColliders();
	void ClearAllCollidersLists();

	PhysBody* CreateCircle(int x, int y, int radius, b2BodyType type = b2_dynamicBody, b2Color color = { 255,255,255,255 });
	PhysBody* CreateRectangle(int x, int y, int width, int height, b2BodyType type = b2_dynamicBody, b2Color color = { 255,255,255,255 });
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height, b2BodyType type = b2_dynamicBody, b2Color color = { 255,255,255,255 });
	PhysBody* CreateChain(int x, int y, int* points, int size, b2BodyType type = b2_dynamicBody, b2Color color = { 255,255,255,255 });

	b2RevoluteJoint* CreateRevoluteJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, float angle = 0.0f, bool collideConnected = false, bool enableLimit = true);
	b2PrismaticJoint* CreatePrismaticJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, b2Vec2 axys, float maxHeight = 0.0f, bool collideConnected = true, bool enableLimit = true);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact) override;


	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;


	PhysBody* test;

	bool debug;
	b2MouseJoint* mouse_joint;
	p2List<PhysBody*> allPhysicBodies;

	p2List<PhysBody*> BodiesToRemove;

private:

	b2World* world;
	b2Body* ground;

	b2Body* mouseBody;
	b2Vec2 p;
};