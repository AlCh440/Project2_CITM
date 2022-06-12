#include "DoorButton.h"
#include"Log.h"

DoorButton::DoorButton(Collider_Type type, iPoint pos):Interactable(type,pos)
{
	this->type = type;
	position = pos;
	buttonTex = app->tex->Load("Assets/Sprites/UI/GUI_2x.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_staticBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	message = "Door button!";
}

DoorButton::~DoorButton()
{
}

bool DoorButton::Start()
{
	for (int i = 0; i < app->entities->entities.count(); i++)
	{
		if
	}
	return true;
}

bool DoorButton::Update(float dt)
{
	Interactable::Update(dt);

	return true;
}

bool DoorButton::PostUpdate()
{
	Interactable::PostUpdate();

	if(Pressed)
	{
		r = { 145,144,16,16 };
		app->render->DrawTexture(buttonTex, position.x, position.y, &r);
	}
	else {
		r = {129,144,16,16};
		app->render->DrawTexture(buttonTex, position.x, position.y, &r);
	}
	return true;
}

void DoorButton::Interact()
{
	LOG(message.GetString());
	if (door != nullptr)
	{		
		door->OpenDoor();
		Pressed = true;
	}
}
