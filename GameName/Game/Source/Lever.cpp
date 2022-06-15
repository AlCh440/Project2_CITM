#include "Lever.h"
#include"Log.h"
Lever::Lever(Collider_Type type, iPoint pos) : Interactable(type,pos)
{
	this->type = type;
	position = pos;
	buttonTex = app->tex->Load("Assets/Sprites/UI/GUI_2x.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	active = false;
	message = "Lever interact!";
}

Lever::Lever() : Interactable()
{
}

Lever::~Lever()
{
}

bool Lever::Start()
{
	return true;
}

bool Lever::Update(float dt)
{
	Interactable::Update(dt);
	return true;
}

bool Lever::PostUpdate()
{
	Interactable::PostUpdate();

	if (active)
	{
		r = { 145,144,16,16 };
		app->render->DrawTexture(buttonTex, position.x, position.y, &r);
	}
	else {
		r = { 129,144,16,16 };
		app->render->DrawTexture(buttonTex, position.x, position.y, &r);
	}
	return true;
}

bool Lever::Cleanup()
{
	buttonTex = nullptr;
	return true;
}

void Lever::Interact()
{
	LOG(message.GetString());
	active = !active;
}
