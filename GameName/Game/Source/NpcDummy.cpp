#include "NpcDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Npc.h"
#include "Player.h"


NpcDummy::NpcDummy(iPoint pos) : Npc(pos)
{
	texture = app->tex->Load("Assets/Sprites/shrek_PNG3.png");
	physBody = app->physics->CreateCircle(position.x, position.y, 48, b2_staticBody);

}

NpcDummy::NpcDummy(Collider_Type type, iPoint pos) : Npc(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/shrek_PNG3.png");
	physBody = app->physics->CreateCircle(position.x, position.y, 48, b2_staticBody);
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