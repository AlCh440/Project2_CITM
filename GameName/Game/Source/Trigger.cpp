#include "Trigger.h"
#include "Log.h"
#include "Entities.h"

Trigger::Trigger() : Entity()
{
	scene = GameScene::NONE;
	id = -1;


	

}

Trigger::Trigger(Collider_Type type, iPoint pos) : Entity(type, pos)
{
	
}

Trigger::~Trigger()
{
}

bool Trigger::Start()
{

	switch (physBody->type)
	{
	case COMBATTRIGGER:
	{
		
		texture = app->tex->Load("Assets/Sprites/characters/EnemigosProvisional.png");

		for (int i = 0; i < 7; i++)
		{
			idle.PushBack({ 48 * i, 48 * 3, 48, 48 });
			idle.speed = 0.05f;
			idle.loop = true;
		}
	}
	break;
	default:
		break;
	}

	return true;
}


bool Trigger::PostUpdate() 
{
	

	if (physBody->type == COMBATTRIGGER) LOG("combat");
	//texture

	switch (physBody->type)
	{
	case COMBATTRIGGER:
	{
		int x, y;
		physBody->GetPosition(x, y);
		idle.Update();

		app->render->DrawTexture(texture, x + 8, y, &idle.GetCurrentFrame());
	}
	break;
	default:
		break;
	}

	return true;
}
