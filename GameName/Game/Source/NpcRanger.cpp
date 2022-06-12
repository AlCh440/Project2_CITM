#include "NpcRanger.h"
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


NpcRanger::NpcRanger(iPoint pos) : Npc(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

}

NpcRanger::NpcRanger(Collider_Type type, iPoint pos) : Npc(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);
}


bool NpcRanger::Start()
{

	villagerSound = app->audio->LoadFx("Assets/audio/fx/villager.wav");

	actualStates = NORMAL;

	//rect = { 134, 54, 24, 38 };

	iPoint pos;
	pos.x = position.x;
	pos.y = position.y;
	pos = app->map->WorldToMap(pos.x, pos.y);

	tilePos = pos;

	/*idle.PushBack({ 132, 56, 24, 36 });
	idle.PushBack({ 132, 56, 24, 36 });
	idle.PushBack({ 164, 56, 24, 36 });
	idle.PushBack({ 164, 56, 24, 36 });
	idle.PushBack({ 197, 56, 24, 36 });
	idle.PushBack({ 197, 56, 24, 36 });
	idle.PushBack({ 229, 56, 24, 36 });
	idle.PushBack({ 229, 56, 24, 36 });



	idle.loop = true;
	idle.speed = 0.05f;

	currentAnim = &idle;*/

	return true;
}

bool NpcRanger::PreUpdate()
{
	return true;
}

bool NpcRanger::Update(float dt)
{
	/*int DistanceX
	int DistanceY

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN);

	}*/
	OpenWorldPlayer* player = app->entities->openWorld;

	int DistanceX = abs(player->GetPosition().x - GetPosition().x);
	int DistanceY = abs(player->GetPosition().y - GetPosition().y);

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			app->dialogManager->dialogActive_Ranger = true;
			app->dialogManager->FillDialog_Ranger(app->dialogManager->dialog_Ranger);
			app->dialogManager->dialog_Ranger.Restart();

			app->audio->PlayFx(villagerSound);


		}

	}

	return true;
}

bool NpcRanger::PostUpdate()
{
	//currentAnim->Update();
	rect = { 134, 54, 24, 38 };

	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);

	app->render->DrawTexture(texture, position.x - 15, position.y - 20, &rect);

	SDL_Rect Rask = { 0,180,9,12 };

	OpenWorldPlayer* player = app->entities->openWorld;

	int DistanceX = abs(player->GetPosition().x - GetPosition().x);
	int DistanceY = abs(player->GetPosition().y - GetPosition().y);

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		app->render->DrawTexture(texture, position.x - 15 + 26, position.y - 20, &Rask);
	}

	return true;





}

bool NpcRanger::CleanUp()
{

	physBody->pendingToDelete = true;

	return true;



}


// 
void NpcRanger::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool NpcRanger::LoadState(pugi::xml_node& data)
{
	return true;
}

bool NpcRanger::SaveState(pugi::xml_node& data) const
{
	return true;
}