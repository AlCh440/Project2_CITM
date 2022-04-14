#include "EnemyDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Enemy.h"
#include "Player.h"


EnemyDummy::EnemyDummy(iPoint pos) : Enemy(pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");	
	physBody = app->physics->CreateCircle(pos.x, pos.y, 36.f*0.5f, b2_staticBody);

	stats.hp = 10;

}

EnemyDummy::EnemyDummy(Collider_Type type, iPoint pos) : Enemy(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 36.f * 0.5f, b2_kinematicBody);
	
	
	stats.hp = 10;
}

void EnemyDummy::Move(float dt)
{
}

void EnemyDummy::UpdatePath()
{
}

bool EnemyDummy::Start()
{
	
	return true;
}

bool EnemyDummy::PreUpdate()
{
	return true;
}

bool EnemyDummy::Update(float dt)
{	
	if (stats.hp <= 0)
	{

	}
	else
	{
		// test movement
		
	}



	return true;
}

bool EnemyDummy::PostUpdate()
{

	app->render->DrawTexture(texture, position.x - 20, position.y - 20);

	return true;
}

bool EnemyDummy::CleanUp()
{

	
	return true;
}

bool EnemyDummy::BasicAttack() // pass an Player
{
	return true;
}

// 
void EnemyDummy::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool EnemyDummy::LoadState(pugi::xml_node& data)
{
	return true;
}

bool EnemyDummy::SaveState(pugi::xml_node& data) const
{
	return true;
}