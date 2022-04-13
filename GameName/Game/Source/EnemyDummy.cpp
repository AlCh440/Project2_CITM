#include "EnemyDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Enemy.h"
#include "Player.h"


EnemyDummy::EnemyDummy(iPoint pos) : Enemy(pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	stats.hp = 10;
	physBody = app->physics->CreateCircle(position.x, position.y, 48);

}

EnemyDummy::EnemyDummy(Collider_Type type, iPoint pos) : Enemy(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	physBody = app->physics->CreateCircle(position.x, position.y, 48);
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
	/*
	switch (state)
	{
	case DEATH:
	{
		// DELETE DUMMY
	} break;
	
	}
	return true;
	*/
	return true;
}

bool EnemyDummy::PostUpdate()
{

	app->render->DrawTexture(texture, position.x, position.y);

	return true;

	if (stats.hp <= 0)
	{
		//state = DEATH;
	}



}

bool EnemyDummy::CleanUp()
{

	app->render->DrawTexture(texture, position.x, position.y);

	return true;

	if (stats.hp <= 0)
	{
		//state = DEATH;
	}



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