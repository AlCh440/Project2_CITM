#include "Chest.h"
#include "OpenWorldPlayer.h"
#include "Entities.h"

#include "Key.h"

Chest::Chest(iPoint pos) : Item(pos)
{
}

Chest::Chest(Collider_Type type, iPoint pos) : Item(type, pos)
{

}

Chest::Chest(Collider_Type type, iPoint pos, p2List<Item*> items) : Item(type, pos)
{
	item = items;
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	Key* k = new Key(1);
	item.add(k);
	k = new Key(2);
	item.add(k);
}

bool Chest::Start()
{
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
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
		{
			Open(player);
			CleanUp();
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
	app->render->DrawTexture(texture, position.x, position.y);

	return true;
}

void Chest::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void Chest::Open(OpenWorldPlayer* player)
{
	while (item.getFirst() != nullptr)
	{
		p2ListItem<Item*>* aux = item.getFirst();
		player->inventory.add(aux->data);
		item.del(aux);
	}
}
