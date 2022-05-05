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



	idle.PushBack({ 259, 50, 26, 42 });
	idle.PushBack({ 290, 50, 26, 42 });
	idle.PushBack({ 322, 50, 26, 42 });
	idle.PushBack({ 355, 50, 26, 42 });

	idle.PushBack({ 259, 104,26, 42 });

	idle.PushBack({ 355, 50, 26, 42 });
	idle.PushBack({ 322, 50, 26, 42 });
	idle.PushBack({ 290, 50, 26, 42 });
	idle.PushBack({ 259, 50, 26, 42 });

	idle.loop = true;
	idle.speed = 0.05f;

	currentAnim = &idle;

	bardMusic.PushBack({ 9, 50,		0, 42 });
	bardMusic.PushBack({ 9 + 26,		0, 26, 42 });
	bardMusic.PushBack({ 9 + 26 * 2, 0, 26, 42 });
	bardMusic.PushBack({ 9 + 26 * 3, 0, 26, 42 });
	bardMusic.PushBack({ 9 + 26 * 4, 0, 26, 42 });

	bardMusic.loop = true;
	bardMusic.speed = 0.05f;


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
	currentAnim->Update();
	bardMusic.Update();


	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);
	
	app->render->DrawTexture(texture, position.x - 15, position.y - 20, &currentAnim->GetCurrentFrame());
	app->render->DrawTexture(texture, position.x - 15 + 16, position.y - 20 - 6, &bardMusic.GetCurrentFrame());

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