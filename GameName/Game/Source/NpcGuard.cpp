#include "NpcGuard.h"
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


NpcGuard::NpcGuard(iPoint pos) : Npc(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/NPC.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

}

NpcGuard::NpcGuard(Collider_Type type, iPoint pos) : Npc(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/NPC.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);
}


bool NpcGuard::Start()
{
	actualStates = NORMAL;

	rect = { 2, 55, 26, 38 };

	iPoint pos;
	pos.x = position.x;
	pos.y = position.y;
	pos = app->map->WorldToMap(pos.x, pos.y);

	tilePos = pos;

	return true;
}

bool NpcGuard::PreUpdate()
{
	return true;
}

bool NpcGuard::Update(float dt)
{
	/*int DistanceX
	int DistanceY

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN);

	}*/

	switch (actualStates)
	{
	case NORMAL:
	{
		return true;
	}
	case TALK:
	{
		//Activar dialogo
	}
	}
	return true;
}

bool NpcGuard::PostUpdate()
{

	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);

	app->render->DrawTexture(texture, position.x -15, position.y -20, &rect);

	return true;





}

bool NpcGuard::CleanUp()
{

	app->render->DrawTexture(texture, position.x, position.y);

	return true;



}


// 
void NpcGuard::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool NpcGuard::LoadState(pugi::xml_node& data)
{
	return true;
}

bool NpcGuard::SaveState(pugi::xml_node& data) const
{
	return true;
}