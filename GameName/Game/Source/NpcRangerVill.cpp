#include "NpcRangerVill.h"
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


NpcRangerVill::NpcRangerVill(iPoint pos) : Npc(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

}

NpcRangerVill::NpcRangerVill(Collider_Type type, iPoint pos) : Npc(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);
}


bool NpcRangerVill::Start()
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

bool NpcRangerVill::PreUpdate()
{
	return true;
}

bool NpcRangerVill::Update(float dt)
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
			app->dialogManager->dialogActive_RangerText = true;
			app->dialogManager->FillDialog_RangerText(app->dialogManager->dialog_RangerText);
			app->dialogManager->dialog_RangerText.Restart();

			app->audio->PlayFx(villagerSound);

			//it keeps adding to memory the more times you talk -> fix!!
		}

	}

	return true;
}

bool NpcRangerVill::PostUpdate()
{
	//currentAnim->Update();


	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	rect = { 134, 54, 24, 38 };

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);

	app->render->DrawTexture(texture, position.x - 15, position.y - 20, &rect);

	SDL_Rect Rask = { 0,0,9,12 };

	OpenWorldPlayer* player = app->entities->openWorld;

	int DistanceX = abs(player->GetPosition().x - GetPosition().x);
	int DistanceY = abs(player->GetPosition().y - GetPosition().y);

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		app->render->DrawTexture(texture, position.x - 15 + 26, position.y - 20, &Rask);
	}

	return true;





}

bool NpcRangerVill::CleanUp()
{

	physBody->pendingToDelete = true;

	return true;



}


// 
void NpcRangerVill::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool NpcRangerVill::LoadState(pugi::xml_node& data)
{
	return true;
}

bool NpcRangerVill::SaveState(pugi::xml_node& data) const
{
	return true;
}