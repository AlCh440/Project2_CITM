#include "App.h"
#include "Input.h"
#include "Render.h"
#include "ModulePhysics.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Point.h"
#include "math.h"
#include "Log.h"
#include "Globals.h"
#include "Entity.h"

//#ifdef _DEBUG
//#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
//#else
//#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
//#endif

#ifdef _DEBUG
#pragma comment( lib, "Source/External/Box2D/libx86/Release/Box2D.lib" )
#else
#pragma comment( lib, "Source/External/Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(bool isActive) : Module(isActive)
{
	world = NULL;
	mouse_joint = NULL;
	debug = false;
	name.Create("physics");
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Awake()
{
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	return true;
}

bool ModulePhysics::Start()
{
	if(world == NULL)
	{
		world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
		world->SetContactListener(this);
		b2BodyDef bd;
		ground = world->CreateBody(&bd);
	}
	active = true;
	return true;
}

bool ModulePhysics::PreUpdate()
{
	world->Step(app->dt/1000, 6, 2);//add delta time

	static bool temp = false;

	p2List_item<PhysBody*>* current = allPhysicBodies.getFirst();
	while (current != NULL)
	{
		bool removeItem = false;
		p2List_item<PhysBody*>* itemToRemove = current;
		if (itemToRemove->data->pendingToDelete) {
			removeItem = true;
		}
		current = current->next;
		if (removeItem && itemToRemove->data->body != NULL)
		{
			LOG("Removing item ");
			
			RemoveBodyFromWorld(itemToRemove->data->body);
			itemToRemove->data = NULL;
			allPhysicBodies.del(itemToRemove);

		}
	}
	return true;
}

bool ModulePhysics::Update(float dt)
{
	return true;
}

bool ModulePhysics::PostUpdate()
{

	return true;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, b2BodyType type,b2Color color)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.bullet = true;

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.friction = 0;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius;
	pbody->color;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, b2BodyType type, b2Color _color)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	pbody->color = _color;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height, b2BodyType type,b2Color color)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;
	pbody->color = color;
	return pbody;
}


PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, b2BodyType type, b2Color color)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = pbody->height = 0;
	b->SetUserData(pbody);
	pbody->color = color;
	
	return pbody;
}

b2RevoluteJoint* ModulePhysics::CreateRevoluteJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, float angle, bool collideConnected, bool enableLimit)
{
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = A->body;
	revoluteJointDef.bodyB = B->body;
	revoluteJointDef.collideConnected = collideConnected;
	revoluteJointDef.localAnchorA.Set(anchorA.x, anchorA.y);
	revoluteJointDef.localAnchorB.Set(anchorB.x, anchorB.y);
	revoluteJointDef.referenceAngle = 0;
	revoluteJointDef.enableLimit = enableLimit;
	revoluteJointDef.lowerAngle = -DEG_TO_RAD(angle);
	revoluteJointDef.upperAngle = DEG_TO_RAD(angle);

	return (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
}

b2PrismaticJoint* ModulePhysics::CreatePrismaticJoint(PhysBody* A, b2Vec2 anchorA, PhysBody* B, b2Vec2 anchorB, b2Vec2 axys, float maxHeight, bool collideConnected, bool enableLimit)
{
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = A->body;
	prismaticJointDef.bodyB = B->body;
	prismaticJointDef.collideConnected = collideConnected;
	prismaticJointDef.localAxisA.Set(axys.x, axys.y);
	prismaticJointDef.localAnchorA.Set(anchorA.x, anchorA.y);
	prismaticJointDef.localAnchorB.Set(anchorB.x, anchorB.y);
	prismaticJointDef.referenceAngle = 0;
	prismaticJointDef.enableLimit = enableLimit;
	prismaticJointDef.lowerTranslation = -0.01;
	prismaticJointDef.upperTranslation = maxHeight;

	return (b2PrismaticJoint*)world->CreateJoint(&prismaticJointDef);
}

void ModulePhysics::Disable()
{
	ClearAllCollidersLists();
	active = false;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Clean up Phiscis Module ");
	allPhysicBodies.clear();
	// Delete the whole physics world!
	delete world;
	world = nullptr;
	active = false;

	return true;
}

void ModulePhysics::RemoveBodyFromWorld(b2Body *body)
{
	world->DestroyBody(body);
}

void ModulePhysics::DrawColliders()
{

	if (!DEBUG)
		return;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (p2List_item<PhysBody*>* pb = allPhysicBodies.getFirst(); pb; pb = pb->next)
	{
		for (b2Fixture* f = pb->data->body->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
			{
				// Draw circles ------------------------------------------------
			case b2Shape::e_circle:
			{

				b2CircleShape* shape = (b2CircleShape*)f->GetShape();
				b2Vec2 pos = f->GetBody()->GetPosition();
				app->render->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), pb->data->color.r, pb->data->color.g, pb->data->color.b);

			}
			break;

			// Draw polygons ------------------------------------------------
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
				int32 count = polygonShape->GetVertexCount();
				b2Vec2 prev, v;

				for (int32 i = 0; i < count; ++i)
				{
					v = pb->data->body->GetWorldPoint(polygonShape->GetVertex(i));
					if (i > 0)
						app->render->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), pb->data->color.r, pb->data->color.g, pb->data->color.b);

					prev = v;
				}

				v = pb->data->body->GetWorldPoint(polygonShape->GetVertex(0));
				app->render->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), pb->data->color.r, pb->data->color.g, pb->data->color.b);
			}
			break;

			// Draw chains contour -------------------------------------------
			case b2Shape::e_chain:
			{
				b2ChainShape* shape = (b2ChainShape*)f->GetShape();
				b2Vec2 prev, v;

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = pb->data->body->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
						app->render->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), pb->data->color.r, pb->data->color.g, pb->data->color.b);
					prev = v;
				}

				v = pb->data->body->GetWorldPoint(shape->m_vertices[0]);
				app->render->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), pb->data->color.r, pb->data->color.g, pb->data->color.b);
			}
			break;

			// Draw a single segment(edge) ----------------------------------
			case b2Shape::e_edge:
			{
				b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
				b2Vec2 v1, v2;

				v1 = pb->data->body->GetWorldPoint(shape->m_vertex0);
				v1 = pb->data->body->GetWorldPoint(shape->m_vertex1);
				app->render->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), pb->data->color.r, pb->data->color.g, pb->data->color.b);
			}
			break;
			}
		}
	}

}

void ModulePhysics::ClearAllCollidersLists()
{

	p2List_item<PhysBody*>* current = allPhysicBodies.getFirst();
	while (current != nullptr)
	{
		current->data->pendingToDelete = true;
		current = current->next;
	}
	allPhysicBodies.clear();
	LOG("All colliders have been cleared...");
}

void PhysBody::GetPosition(int& x, int& y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while (fixture != NULL)
	{
		if (fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while (fixture != NULL)
	{
		if (fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx * fx) + (fy * fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			app->render->DrawLine(METERS_TO_PIXELS(x1), METERS_TO_PIXELS(y1), METERS_TO_PIXELS(x2), METERS_TO_PIXELS(y2),255, 0, 0,255);

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);


	//if (physA && physA->entityListener != NULL)
	//	physA->listener->OnCollision(physB);

	//if (physB && physB->entityListener != NULL)
	//	physB->listener->OnCollision(physA);
}

bool ModulePhysics::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	pugi::xml_node physics = data.child("physics");

	if (world == NULL)
	{
		world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
		world->SetContactListener(this);
		b2BodyDef bd;
		ground = world->CreateBody(&bd);
	}


	return ret;
}

bool ModulePhysics::SaveState(pugi::xml_node& data) const
{

	bool ret = true;

	pugi::xml_node physics = data.append_child("physics");


	return ret;
}
