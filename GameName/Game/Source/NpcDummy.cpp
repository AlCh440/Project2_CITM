#include "NpcDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Npc.h"
#include "Player.h"
#include "Entities.h"
#include "Physics.h"


NpcDummy::NpcDummy(iPoint pos) : Npc(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/NPC.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

}

NpcDummy::NpcDummy(Collider_Type type, iPoint pos) : Npc(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/NPC.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);
}


bool NpcDummy::Start()
{


	return true;
}

bool NpcDummy::PreUpdate()
{
	return true;
}

bool NpcDummy::Update(float dt)
{
	/*
	switch (state)
	{
	case DEATH:
	{
		// DELETE DUMMY
	} break;

	}
	return true;
	*/
	return true;
}

bool NpcDummy::PostUpdate()
{

	app->render->DrawTexture(texture, position.x, position.y);

	return true;

	



}

bool NpcDummy::CleanUp()
{

	app->render->DrawTexture(texture, position.x, position.y);

	return true;

	

}


// 
void NpcDummy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool NpcDummy::LoadState(pugi::xml_node& data)
{
	return true;
}

bool NpcDummy::SaveState(pugi::xml_node& data) const
{
	return true;
}