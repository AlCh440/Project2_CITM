#include "NpcDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Npc.h"
#include "Player.h"
#include "Entities.h"
#include "Physics.h"
#include "Pathfinding.h"

#include "Log.h"


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
	actualStates = NORMAL;

	iPoint pos;
	pos.x = position.x;
	pos.y = position.y;
	pos = app->map->WorldToMap(pos.x, pos.y);

	tilePos = pos;

	return true;
}

bool NpcDummy::PreUpdate()
{
	return true;
}

bool NpcDummy::Update(float dt)
{
	

	switch (actualStates)
	{
	case NORMAL:
	{
		return true;
	}
	case TALK:
	{
		if (detectionDistance = 3)
		{
			if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN);
				
		}
	}
	}
	return true;
}

bool NpcDummy::PostUpdate()
{
	
	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);
	
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