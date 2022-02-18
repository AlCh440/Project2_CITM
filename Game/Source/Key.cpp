#include "Key.h"
#include "ModuleEntities.h"
Key::Key(iPoint pos) : Collectable(pos)
{
	spawnPos = pos;
	name = "key";
}

Key::Key(Collider_Type type, iPoint pos) : Collectable(pos)
{
	spawnPos = pos;
}


bool Key::Start()
{
	texture = app->tex->Load("../Output/Assets/Spritesx16/gems.png");

	r.x = position.x;
	r.y = position.x;
	r.w = 16;
	r.h = 16;
	physBody = app->physics->CreateRectangleSensor(position.x, position.y, r.w, r.h, b2_staticBody);
	physBody->listener = app->entities;
	physBody->color = { 100,50,255,255 };
	physBody->type = Collider_Type::KEY;
	app->physics->allPhysicBodies.add(physBody);


	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;



	return true;
}

bool Key::Update()
{
	return true;
}

bool Key::PostUpdate()
{
	r.x = 16;//position in the texture
	r.y = 0;
	r.w = 16;
	r.h = 16;
	if (texture != NULL)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x) - (r.w * 0.5), METERS_TO_PIXELS(physBody->body->GetPosition().y) - (r.h * 0.5), &r);

	return true;
}

bool Key::Cleanup()
{
	return true;
}

bool Key::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	position.x = data.child("Key").attribute("x").as_int();
	position.y = data.child("Key").attribute("y").as_int();

	return ret;
}

bool Key::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node entity = data.append_child("Key");
	entity.append_attribute("type") = physBody->type;;
	entity.append_attribute("x") = position.x;
	entity.append_attribute("y") = position.y;
	return ret;
}