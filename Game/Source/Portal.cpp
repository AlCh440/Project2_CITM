#include "Portal.h"
#include "ModuleEntities.h"

Portal::Portal(iPoint pos) : Entity(pos)
{
	name = "portal";
}

Portal::Portal(Collider_Type type, iPoint pos) : Entity(pos)
{
}

void Portal::Open()
{
	portalState = P_OPEN;
	currentAnim = &openPortalAnim;
}

void Portal::Transition()
{
	portalState = P_TRANSITION;
	currentAnim = &transitionPortalAnim;
}

void Portal::Close()
{
	portalState = P_IDLE;
	currentAnim = &idlePortalAnim;
}

bool Portal::LoadState(pugi::xml_node& data)
{
	return false;
}

bool Portal::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node entity = data.append_child("Portal");
	entity.append_attribute("type") = physBody->type;
	entity.append_attribute("x") = position.x;
	entity.append_attribute("y") = position.y;
	return false;
}

bool Portal::Start()
{
	texture = app->tex->Load("Assets/Spritesx16/props.png");
	//Portal animations
	//Idle anim
	idlePortalAnim.PushBack({ 32, 0, 32, 64 });
	idlePortalAnim.PushBack({ 64, 0, 32, 64 });
	idlePortalAnim.PushBack({ 96, 0, 32, 64 });
	idlePortalAnim.PushBack({ 64, 0, 32, 64 });
	idlePortalAnim.loop = true;
	idlePortalAnim.mustFlip = false;
	idlePortalAnim.speed = 0.05f;
	//Transition anim
	transitionPortalAnim.PushBack({ 128, 0, 32, 64 });
	transitionPortalAnim.PushBack({ 160, 0, 32, 64 });
	transitionPortalAnim.PushBack({ 192, 0, 32, 64 });
	transitionPortalAnim.PushBack({ 224, 0, 32, 64 });
	transitionPortalAnim.loop = false;
	transitionPortalAnim.mustFlip = false;
	transitionPortalAnim.speed = 0.05f;
	//Open anim
	openPortalAnim.PushBack({ 288, 0, 32, 64 });
	openPortalAnim.PushBack({ 320, 0, 32, 64 });
	openPortalAnim.PushBack({ 352, 0, 32, 64 });
	openPortalAnim.PushBack({ 320, 0, 32, 64 });
	openPortalAnim.loop = true;
	openPortalAnim.mustFlip = false;
	openPortalAnim.speed = 0.05f;
	portalState = P_IDLE;
	currentAnim = &idlePortalAnim;

	physBody = app->physics->CreateRectangleSensor(position.x, position.y, 32, 64, b2_staticBody);
	physBody->listener = app->entities;
	physBody->color = { 25,150,25,255 };
	physBody->type = Collider_Type::PORTAL;
	app->physics->allPhysicBodies.add(physBody);
	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	return true;
}

bool Portal::PreUpdate()
{
	return true;
}

bool Portal::Update(float dt)
{

	switch (portalState)
	{
	case P_IDLE:
		idlePortalAnim.Update();
		break;
	case P_TRANSITION:
		transitionPortalAnim.Update();
		if (transitionPortalAnim.HasFinished())
		{
			Open();
		}
		break;
	case P_OPEN:
		openPortalAnim.Update();
		break;
	}

	return true;
}

bool Portal::PostUpdate()
{
	app->render->DrawTexture(texture, METERS_TO_PIXELS(position.x)-(32 * 0.5), METERS_TO_PIXELS(position.y)- (64 * 0.5), &(currentAnim->GetCurrentFrame()));
	return true;
}

bool Portal::Cleanup()
{
	texture = nullptr;
	currentAnim = nullptr;
	return true;
}
