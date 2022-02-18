#include "HPotion.h"
#include "ModuleEntities.h"
HPotion::HPotion(iPoint pos) : Collectable(pos)
{
	name = "hpotion";
}

HPotion::HPotion(Collider_Type type, iPoint pos) : Collectable(pos)
{
}

bool HPotion::LoadState(pugi::xml_node& data)
{
	
	return true;
}

bool HPotion::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node entity = data.append_child("HealthPotion");
	entity.append_attribute("type") = physBody->type;
	entity.append_attribute("x") = METERS_TO_PIXELS(position.x - (r.w * 0.5));
	entity.append_attribute("y") = METERS_TO_PIXELS(position.y - (r.h * 0.5));

	return true;
}

bool HPotion::Start()
{
	texture = app->tex->Load("Assets/Spritesx16/props.png");
	r.x = 144;
	r.y = 128;
	r.w = 16;
	r.h = 16;
	physBody = app->physics->CreateRectangleSensor(position.x , position.y , 16, 16, b2_staticBody, {25, 200, 25});
	physBody->type = Collider_Type::POTION;
	physBody->listener = app->entities;
	app->physics->allPhysicBodies.add(physBody);


	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;
	return true;
}

bool HPotion::Update()
{
	return true;
}

bool HPotion::PostUpdate()
{
	if (texture != NULL)
		app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x) - (r.w * 0.5), METERS_TO_PIXELS(physBody->body->GetPosition().y) - (r.h * 0.5), &r);
	return true;
}

bool HPotion::Cleanup()
{
	texture = nullptr;
	return true;
}
