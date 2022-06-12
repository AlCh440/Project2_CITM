#include "Interactable.h"


Interactable::Interactable(Collider_Type type, iPoint pos) : Entity(type, pos) {

	interactTex = app->tex->Load("Assets/Sprites/characters/NPC.png");
}
Interactable::~Interactable() {
	app->tex->UnLoad(interactTex);
}
bool Interactable::Update(float dt)
{
	if (app->entities->openWorldInstance != nullptr && player == nullptr)
		player = app->entities->openWorldInstance;

	if (CheckInteractionDistance() && player != nullptr)
	{
		player->Interact(this);
	}

	return true;
}

bool Interactable::CheckInteractionDistance()
{
	if (app->entities->openWorldInstance != nullptr)
	{
		player = app->entities->openWorld;

		int DistanceX = abs(player->GetPosition().x - GetPosition().x);
		int DistanceY = abs(player->GetPosition().y - GetPosition().y);
		if (interactionRange > DistanceX && interactionRange > DistanceY)
		{
			OnRange = true;
		}
		else {
			OnRange = false;
		}

	}
	return OnRange;
}

bool Interactable::PostUpdate()
{
	if (OnRange)
	{
		SDL_Rect r = { 0,0,9,12 };
		app->render->DrawTexture(interactTex, position.x - 15 + 26, position.y - 20, &r);
	}

	return true;
}
