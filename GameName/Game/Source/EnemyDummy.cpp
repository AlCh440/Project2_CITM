#include "EnemyDummy.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Enemy.h"
#include "Player.h"
#include "Player.cpp"


EnemyDummy::EnemyDummy(iPoint pos) : Enemy(pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
}

EnemyDummy::EnemyDummy(Collider_Type type, iPoint pos) : Enemy(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/dummySprite.png");
}

void EnemyDummy::Move(float dt)
{
}

void EnemyDummy::UpdatePath()
{
}

bool EnemyDummy::PostUpdate()
{
	int hp;
	
	app->render->DrawTexture(texture, position.x, position.y);

	return true;

	if (  hp  = 0)
	{
		state = DEATH;
	}
	
	

}
