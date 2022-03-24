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
}

EnemyDummy::EnemyDummy(Collider_Type type, iPoint pos) : Enemy(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
	stats.hp = 10;
}

void EnemyDummy::Move(float dt)
{
}

void EnemyDummy::UpdatePath()
{
}

bool EnemyDummy::Update(float dt)
{	
	switch (state)
	{
	case DEATH:
	{
		// DELETE DUMMY
	} break;
	
	}
	return true;
}

bool EnemyDummy::PostUpdate()
{

	app->render->DrawTexture(texture, position.x, position.y);

	return true;

	if (stats.hp <= 0)
	{
		state = DEATH;
	}



}