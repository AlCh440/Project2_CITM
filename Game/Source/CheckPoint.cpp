#include "CheckPoint.h"
#include "ModuleEntities.h"

CheckPoint::CheckPoint(iPoint pos) : Entity(pos)
{
	name = "checkpoint";
}

CheckPoint::CheckPoint(Collider_Type type, iPoint pos) : Entity(pos)
{
}

void CheckPoint::Open()
{
	shrineState = S_OPEN;
	currentAnim = &openShrineAnim;
}

void CheckPoint::Transition()
{
	shrineState = S_TRANSITION;
	currentAnim = &transitionShrineAnim;
}

void CheckPoint::Close()
{
	shrineState = S_IDLE;
	currentAnim = &idleShrineAnim;
}

bool CheckPoint::LoadState(pugi::xml_node& data)
{
	return false;
}

bool CheckPoint::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node entity = data.append_child("CheckPoint");
	entity.append_attribute("type") = physBody->type;;
	entity.append_attribute("x") = position.x;
	entity.append_attribute("y") = position.y;
	return true;
}

bool CheckPoint::Start()
{
	texture =  app->tex->Load("Assets/Spritesx16/props.png"); 
	//Shrine (checkpoint) animations
	//Idle anim
	idleShrineAnim.PushBack({ 0, 84, 32, 60 });
	idleShrineAnim.loop = false;
	idleShrineAnim.mustFlip = false;
	idleShrineAnim.speed = 0.05f;
	//Transition anim
	transitionShrineAnim.PushBack({ 32, 84, 32, 60 });
	transitionShrineAnim.PushBack({ 64, 84, 32, 60 });
	transitionShrineAnim.loop = false;
	transitionShrineAnim.mustFlip = false;
	transitionShrineAnim.speed = 0.01f;
	//Open anim
	openShrineAnim.PushBack({ 96, 84, 32, 60 });
	openShrineAnim.loop = false;
	openShrineAnim.mustFlip = false;
	openShrineAnim.speed = 0.05f;
	shrineState = S_IDLE;
	currentAnim = &idleShrineAnim;
	frameCounter = 0;

	physBody = app->physics->CreateRectangleSensor(position.x, position.y, 16, 48, b2_staticBody);
	physBody->listener = app->entities;
	physBody->color = { 25,150,25,255 };
	physBody->type = Collider_Type::CHECK_POINT;
	app->physics->allPhysicBodies.add(physBody);

	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	return true;
}

bool CheckPoint::PreUpdate()
{
	return true;
}

bool CheckPoint::Update(float dt)
{
	switch (shrineState)
	{
	case S_IDLE:
		idleShrineAnim.Update();
		break;
	case S_TRANSITION:
		transitionShrineAnim.Update();
		if (transitionShrineAnim.HasFinished())
		{
			Open();
		}
		break;
	case S_OPEN:
		openShrineAnim.Update();
		break;
	}

	return true;
}

bool CheckPoint::PostUpdate()
{
	//app->render->DrawTexture(texture, METERS_TO_PIXELS(position.x)-16, METERS_TO_PIXELS(position.y), &(currentAnim->GetCurrentFrame()));
	app->render->DrawTexture(texture, METERS_TO_PIXELS(position.x) - (16 * 0.5), METERS_TO_PIXELS(position.y) - (48 * 0.5), &(currentAnim->GetCurrentFrame()));
	return true;
}

bool CheckPoint::Cleanup()
{
	//texture = nullptr;
	//currentAnim = nullptr;
	return true;
}
