#include "NpcArchmageComb.h"
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


NpcArchmageComb::NpcArchmageComb(iPoint pos) : Npc(pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 16.0f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);

}

NpcArchmageComb::NpcArchmageComb(Collider_Type type, iPoint pos) : Npc(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->entityPtr = this;
	physBody->body->SetGravityScale(0);
}


bool NpcArchmageComb::Start()
{

	villagerSound = app->audio->LoadFx("Assets/audio/fx/villager.wav");

	actualStates = NORMAL;

	rect = { 0, 256, 40, 40 };

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

bool NpcArchmageComb::PreUpdate()
{
	return true;
}

bool NpcArchmageComb::Update(float dt)
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
			app->dialogManager->dialogActive_ArchmageCombat = true;
			app->dialogManager->FillDialog_ArchmageCombat(app->dialogManager->dialog_ArchmageCombat);
			app->dialogManager->dialog_ArchmageCombat.Restart();

			app->audio->PlayFx(villagerSound);

			//it keeps adding to memory the more times you talk -> fix!!
		}

	}

	return true;
}

bool NpcArchmageComb::PostUpdate()
{
	//currentAnim->Update();


	SDL_Rect r;
	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 255, 100, 255, 150, true);

	//app->render->DrawTexture(texture, position.x - 15, position.y - 20, &currentAnim->GetCurrentFrame());

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

bool NpcArchmageComb::CleanUp()
{

	physBody->pendingToDelete = true;

	return true;



}


// 
void NpcArchmageComb::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool NpcArchmageComb::LoadState(pugi::xml_node& data)
{
	return true;
}

bool NpcArchmageComb::SaveState(pugi::xml_node& data) const
{
	return true;
}