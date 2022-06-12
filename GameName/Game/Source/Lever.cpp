#include "Lever.h"
#include"Log.h"
Lever::Lever(Collider_Type type, iPoint pos) : Interactable(type,pos)
{
	this->type = type;
	position = pos;
	buttonTex = app->tex->Load("Assets/Sprites/UI/GUI_2x.png");
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
	return true;
}

bool Lever::PostUpdate()
{
	return true;
}

void Lever::Interact()
{
}
