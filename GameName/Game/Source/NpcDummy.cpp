#include "NpcDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Npc.h"
#include "Player.h"
#include "Entities.h"
#include "Physics.h"
#include "Pathfinding.h"
#include "OpenWorldPlayer.h"

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

	rect = { 259, 49, 30, 43 };

	iPoint pos;
	pos.x = position.x;
	pos.y = position.y;
	pos = app->map->WorldToMap(pos.x, pos.y);

	tilePos = pos;

	inter_speed = 0.02f;


	idle.PushBack({ 259, 49, 30, 43 });
	idle.PushBack({ 290, 51, 31, 41 });
	idle.PushBack({322, 39, 30, 53 });
	idle.PushBack({ 355, 39, 26, 53 });
	idle.PushBack({ 258, 93, 29, 47 });
	idle.PushBack({ 259, 49, 30, 43 });
	
	idle.speed = 0.1f;

	inter_speed = 0.02f;

	currentAnim = &idle;

	return true;
}

bool NpcDummy::PreUpdate()
{
	return true;
}

bool NpcDummy::Update(float dt)
{
	OpenWorldPlayer* player = (OpenWorldPlayer*)app->entities->playerInstance;

	int DistanceX = abs(player->GetPosition().x - GetPosition().x);
	int DistanceY = abs(player->GetPosition().y - GetPosition().y);

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			app->dialogManager->dialogActive_NoName = true;
			app->dialogManager->FillDialog_Test(app->dialogManager->dialog_Test);
			app->dialogManager->dialog_Test.Restart();

			//it keeps adding to memory the more times you talk -> fix!!
		}

	}

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

bool NpcDummy::PostUpdate()
{
	
	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);
	
	app->render->DrawTexture(texture, position.x - 15, position.y - 20, &rect);

	SDL_Rect Rask = { 0,0,9,12 };

	OpenWorldPlayer* player = (OpenWorldPlayer*)app->entities->playerInstance;

	int DistanceX = abs(player->GetPosition().x - GetPosition().x);
	int DistanceY = abs(player->GetPosition().y - GetPosition().y);

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		app->render->DrawTexture(texture, position.x - 15 + 26, position.y - 20, &Rask);
	}

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