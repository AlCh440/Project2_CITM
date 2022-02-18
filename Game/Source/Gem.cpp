#include "Gem.h"
#include "ModuleEntities.h"

Gem::Gem(iPoint pos) : Collectable(pos)
{
	spawnPos = pos;
	name.Create("Gem");
}

Gem::Gem(Collider_Type type, iPoint pos) : Collectable(pos)
{
}

bool Gem::Start()
{

	texture = app->tex->Load("../Output/Assets/Spritesx16/gems.png");

	r.x = position.x;
	r.y = position.x;
	r.w = 16;
	r.h = 16;
	physBody = app->physics->CreateRectangleSensor(position.x , position.y , r.w, r.h, b2_staticBody);
	physBody->listener = app->entities;
	physBody->color = { 100,50,255,255 };
	physBody->type = Collider_Type::GEM;
	app->physics->allPhysicBodies.add(physBody);

	type = physBody->type;

	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	//texPosition = 

	return true;
}

bool Gem::Update(float dt)
{
	return true;
}

bool Gem::PostUpdate()
{
	bool ret = true;
	r.x = 0;//position in the texture
	r.y = 0;
	r.w = 16;
	r.h = 16;
	if (texture != NULL)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x) - (r.w * 0.5), METERS_TO_PIXELS(physBody->body->GetPosition().y) - (r.h * 0.5), &r);

	return ret;
}

bool Gem::Cleanup()
{
	return true;
}

bool Gem::LoadState(pugi::xml_node& data)
{
	bool ret = true;
	return ret;
}

bool Gem::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node entity = data.append_child("Gem");
	entity.append_attribute("type") = physBody->type;
	entity.append_attribute("x") = position.x;
	entity.append_attribute("y") = position.y;

	return ret;
}

