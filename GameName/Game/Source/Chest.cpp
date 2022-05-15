#include "Chest.h"
#include "OpenWorldPlayer.h"
#include "Entities.h"

#include "Key.h"
#include "HPPotion.h"
#include "ManaPotion.h"

Chest::Chest(iPoint pos) : Item(pos)
{
}

Chest::Chest(Collider_Type type, iPoint pos) : Item(type, pos)
{
	alreadyOpen = false;
	texture = app->tex->Load("Assets/Maps/tileset.png");
	attention = app->tex->Load("Assets/Sprites/characters/NPC.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
}

Chest::Chest(Collider_Type type, iPoint pos, p2List<Item*> items) : Item(type, pos)
{

	alreadyOpen = false;
	texture = app->tex->Load("Assets/Maps/tileset.png");
	attention = app->tex->Load("Assets/Sprites/characters/NPC.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	
}

bool Chest::Start()
{
	fxOpen = app->audio->LoadFx("Assets/audio/fx/chestOpen.wav");
	fxClose = app->audio->LoadFx("Assets/audio/fx/chestClosing.wav");
	return true;
}

bool Chest::PreUpdate()
{
	return true;
}

bool Chest::Update(float dt)
{
	OpenWorldPlayer* player = app->entities->openWorld;

	int DistanceX = abs(player->GetPosition().x - GetPosition().x);
	int DistanceY = abs(player->GetPosition().y - GetPosition().y);

	if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && !alreadyOpen)
		{
			Open(player);
			CleanUp();
			alreadyOpen = true;
			app->audio->PlayFx(fxOpen, false);
		}

	}

	return true;
}

bool Chest::CleanUp()
{
	 
	return true;
}

bool Chest::PostUpdate()
{
	SDL_Rect rClosed = { 0,448,32,32 };
	SDL_Rect rOpen = { 32,448,32,32 };
	
	if (app->entities->openWorld != nullptr)
	{
		OpenWorldPlayer* player = (OpenWorldPlayer*)app->entities->openWorld;

		int DistanceX = abs(player->GetPosition().x - GetPosition().x);
		int DistanceY = abs(player->GetPosition().y - GetPosition().y);

		SDL_Rect Rask = { 0,0,9,12 };

		if (!alreadyOpen)
		{
			app->render->DrawTexture(texture, position.x - 16, position.y - 16, &rClosed);

			if (DistanceX <= detectionDistance && DistanceY <= detectionDistance)
			{
				app->render->DrawTexture(attention, position.x - 15 + 26, position.y - 20, &Rask);
			}
		}
		else
		{
			app->render->DrawTexture(texture, position.x - 16, position.y -16, &rOpen);
		} 
		
	}
	return true;
}

void Chest::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void Chest::Open(OpenWorldPlayer* player)
{
	while (itemList.getFirst() != nullptr)
	{
		p2ListItem<Item*>* aux = itemList.getFirst();
		player->inventory.add(aux->data);
		itemList.del(aux);
	}
}

void Chest::AddItem(Item* item)
{
	itemList.add(item);
}
