#include "OpenWorldPlayer.h"
#include "Defs.h"
#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "Entities.h"
#include "Physics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Map.h"
#include "Log.h"
#include "Player.h"
#include "Item.h"
#include "Interactable.h"
#include "ModuleParticles.h"

#include "HPPotion.h"
#include "ManaPotion.h"
#include "Key.h"

// Update Code
OpenWorldPlayer::OpenWorldPlayer(Collider_Type type, iPoint pos) : Player(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpriteSheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.4f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->listener = app->entities;
	physBody->color = { 255,155,255,255 };
	physBody->type = type;
	entityTurn = true;
	Start();
}

OpenWorldPlayer::OpenWorldPlayer(Collider_Type type, iPoint pos, p2List	<Item*> inventory_) : Player(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpriteSheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.4f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->listener = app->entities;
	physBody->color = { 255,155,255,255 };
	physBody->type = type;
	entityTurn = true;
	inventory = inventory_;
}

OpenWorldPlayer::~OpenWorldPlayer()
{
		
}

bool OpenWorldPlayer::Start()
{
	fxStepsDef = app->audio->LoadFx("Assets/audio/fx/fxStepDef.wav");
	fxStepsDirt = app->audio->LoadFx("Assets/audio/fx/fxDirtStep.wav");
	fxStepsGrass = app->audio->LoadFx("Assets/audio/fx/fxGrassStep.wav");

	stats.hp = 100;
	stats.mana = 50;
	stats.movement = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	canMove = true;

	currentAnim = &walkSide;
	walkSpeed = 0.1f;

	walkSide.PushBack({ 0, 0, 32, 48 });
	walkSide.PushBack({ 32, 0, 32, 48 });
	walkSide.PushBack({ 64, 0, 32, 48 });
	walkSide.PushBack({ 96, 0, 32, 48 });
	walkSide.loop = true;
	walkSide.speed = walkSpeed;


	walkDown.PushBack({ 0, 48, 32, 48 });
	walkDown.PushBack({ 32, 48, 32, 48 });
	walkDown.PushBack({ 64, 48, 32, 48 });
	walkDown.PushBack({ 96, 48, 32, 48 });
	walkDown.loop = true;
	walkDown.speed = walkSpeed;


	walkUp.PushBack({ 0, 96, 32, 48 });
	walkUp.PushBack({ 32, 96, 32, 48 });
	walkUp.PushBack({ 64, 96, 32, 48 });
	walkUp.PushBack({ 96, 96, 32, 48 });
	walkUp.loop = true;
	walkUp.speed = walkSpeed;

	idle.PushBack({ 0, 48, 32, 48 });
	idle.loop = false;
	idle.speed = walkSpeed;

	currentAnim = &idle;
	return true;
}

bool OpenWorldPlayer::PreUpdate()
{
	if (AdminMode)
	{
		if (!physBody->body->GetFixtureList()->IsSensor())
		{
			physBody->body->GetFixtureList()->SetSensor(true);
		}
		
	}
	else if (physBody->body->GetFixtureList()->IsSensor())
	{
		physBody->body->GetFixtureList()->SetSensor(false);
	}


	return true;

}

bool OpenWorldPlayer::Update(float dt)
{

	app->render->CameraFocus(position);

	bool goLeft = (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT);
	
	bool goRight = (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT);
	
	bool goUp = (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT);
	
	bool goDown = (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT);
	
	b2Vec2 movement = { (float)(goRight - goLeft), (float)(goDown - goUp) };
	movement.Normalize();

	movement.x *= velocity;
	movement.y *= velocity;


	if (AdminMode)
	{
		if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			movement.x *= 10;
			movement.y *= 10;
		}

		physBody->body->SetLinearVelocity(movement);
	}
	else
	{
		if (CanMove())
		{
			if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
			{
				movement.x *= 1.6f;
				movement.y *= 1.6f;
			}
			physBody->body->SetLinearVelocity(movement);
		}
		else 
		{
			b2Vec2 v(0, 0);
			physBody->body->SetLinearVelocity(v);
		}
	}

	physBody->GetPosition(position.x, position.y);


	



	Animation* lastDirection = currentAnim;

	if (CanMove())
	{
		if (movement.x != 0 || movement.y != 0)
		{
			if (stepsTimer > 0)
			{
				if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
				{
					stepsTimer -= 1.3f;
				}
				else {
					stepsTimer--;
				}
			}
			else
			{
				app->audio->PlayFx(currentSteps);
				stepsTimer = stepsTimerRef;
			}
		}



		if (movement.x > 0)
		{
			currentAnim = &walkSide;
			lastDirection = &walkSide;
			lastDirection->speed = walkSpeed;
			goingLeft = false;
			/*app->audio->PlayFx(currentSteps);*/
			
		}
		else if (movement.x < 0)
		{
			currentAnim = &walkSide;
			lastDirection = &walkSide;
			lastDirection->speed = walkSpeed;
			goingLeft = true;
			//app->audio->PlayFx(currentSteps);
			
		}
		else if (movement.y < 0)
		{
			currentAnim = &walkUp;
			lastDirection = &walkUp;
			lastDirection->speed = walkSpeed;
			//app->audio->PlayFx(currentSteps);
			
			//app->audio->Pause = true;
		}
		else if (movement.y > 0)
		{
			currentAnim = &walkDown;
			lastDirection = &walkDown;
			lastDirection->speed = walkSpeed;
			//app->audio->PlayFx(currentSteps);
			
			//app->audio->PlayFx(steps);
		}
		else
		{
			currentAnim = lastDirection;
			lastDirection->Reset();
			lastDirection->speed = 0;
			//app->audio->PlayFx(steps);
		}
	}
	else
	{
		currentAnim = lastDirection;
		lastDirection->Reset();
		lastDirection->speed = 0;
		//app->audio->Pause = true;
	}

	bool cont = true;
	for (p2ListItem<MapLayer*>* layer = app->map->mapData.layers.getFirst(); layer && cont == true; layer = layer->next)
	{
		iPoint pos = { GetPositionTiles().x, GetPositionTiles().y };

		int tileID = -4;

		if (layer)
		{
			tileID = layer->data->Get(pos.x, pos.y);
		}

		//LOG("tileID %i", tileID);

		switch (tileID)
		{
		case 118:
		{
			currentSteps = fxStepsGrass;
			cont = false;
			//LOG("step grass");
		}
		break;
		case 197:
		{
			currentSteps = fxStepsDirt;
			cont = false;
			//LOG("step dirt");

		}
		break;
		case 219:
		{
			currentSteps = fxStepsDirt;
			cont = false;
			//LOG("step dirt");

		}
		break;
		default:
		{
			currentSteps = fxStepsDef;
			//LOG("step default");

		}
		break;
		}

		if ((movement.x != 0 || movement.y != 0) && (tileID == 219 || tileID == 197))
		{
			if (app->RandomRange(0, 3) == 3)
			{

				Particle* p = app->particles->AddParticle(app->particles->dust,
					app->RandomRange(position.x + 18, position.x - 10), app->RandomRange(position.y + 15, position.y + 19));

				/*p->speed = fPoint(app->RandomRange(0.01f, -0.01f), app->RandomRange(0.1f, .3f));
				p->accel = fPoint(app->RandomRange(0.02f, -0.02f), app->RandomRange(0.f, 0.03f));*/
				p->anim.speed = app->RandomRange(0.05f, 0.1f);

				int rnd_leaf = app->RandomRange(0, 3);
				switch (rnd_leaf)
				{
				case 1:
					p->anim.Update();
					break;
				case 2:
				{
					p->anim.Update();
					p->anim.Update();
				}
				break;
				case 3:
				{
					p->anim.Update();
					p->anim.Update();
					p->anim.Update();
				}
				break;
				default:
					break;
				}
			}
		}

	}
	

	return true;
}

bool OpenWorldPlayer::PostUpdate()
{
	currentAnim->Update();

	if (goingLeft)
	{
		app->render->DrawTexture(texture, position.x - 3, position.y - 20, &currentAnim->GetCurrentFrame());
	}
	else
	{
		app->render->DrawTexture(texture, position.x - 4, position.y - 20, &currentAnim->GetCurrentFrame(), 1.0f, 0.0f, 2147483647, 2147483647, 1.0f, SDL_FLIP_HORIZONTAL);
	}


	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		AdminMode = !AdminMode;

	

	return true;
}

bool OpenWorldPlayer::CleanUp()
{
	// destroy the physbody

	return true;
}

void OpenWorldPlayer::Interact(Interactable* interactable)
{
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		interactable->BaseInteract();
	}
}

void OpenWorldPlayer::RestartPhysBody(iPoint pos, Collider_Type type)
{
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->listener = app->entities;
	physBody->color = { 255,155,255,255 };
	physBody->type = type;
	physBody->GetPosition(position.x, position.y);

}


// OnCollision
void OpenWorldPlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

void OpenWorldPlayer::SetPositionFromPixels(iPoint pos)
{
	b2Vec2 newPos;

	newPos.x = PIXEL_TO_METERS(pos.x);
	newPos.y = PIXEL_TO_METERS(pos.y);
	physBody->body->SetTransform(newPos, 0);
}

// Load / Save
bool OpenWorldPlayer::LoadState(pugi::xml_node& data)
{
	float x_ = data.child("player").attribute("x").as_int();
	float y_ = data.child("player").attribute("y").as_int();

	b2Vec2 pos = { PIXEL_TO_METERS(x_),PIXEL_TO_METERS(y_) };
	
	LOG("%i, %i", x_, y_);
	physBody->body->SetTransform(pos, 0);
	mapPlayerUpdate = false;

	pugi::xml_node node_01 = data.child("player").child("inventory");

	if (node_01 != NULL)
	{
		for (pugi::xml_node node_02 = node_01.child("item"); node_02 != NULL; node_02 = node_02.next_sibling())
		{
			int aux_01 = node_02.attribute("id").as_int();
			switch (aux_01)
			{
			case 1:
			{
				HPPotion* hp = new HPPotion(HP_POTION);
				hp->CreateButton();
				inventory.add(hp);
				
			} break;
			case 2:
			{
				ManaPotion* mp = new ManaPotion(MANA_POTION);
				mp->CreateButton();
				inventory.add(mp);
			} break;
			case 3:
			{
				int aux_02 = node_02.attribute("keyId").as_int();
				
				Key* k = new Key(aux_02);
				k->CreateButton();
				inventory.add(k);
			} break;
			}
		}
	}
	return true;
}

bool OpenWorldPlayer::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node node_01 = data.append_child("player");
	
	iPoint pos(position.x, position.y);

	node_01.append_attribute("x") = position.x;
	node_01.append_attribute("y") = position.y;

	if (inventory.getFirst() != NULL)
	{
		pugi::xml_node node_02 = node_01.append_child("inventory");
		pugi::xml_node node_03;
		for (p2ListItem<Item*>* aux = inventory.getFirst(); aux != nullptr; aux = aux->next)
		{
			switch (aux->data->itemType)
			{
			case itemType::POTION_HP_:
			{
				node_03 = node_02.append_child("item");
				node_03.append_attribute("id") = 1;
			} break;
			case itemType::POTION_MANA_:
			{
				node_03 = node_02.append_child("item");
				node_03.append_attribute("id") = 2;
			} break;
			case itemType::KEY_:
			{
				node_03 = node_02.append_child("item");
				node_03.append_attribute("id") = 3;
				node_03.append_attribute("keyId") = aux->data->GetKeyId();
			}
			}
		}
	}

	return true;
}

void OpenWorldPlayer::RemoveFromInventory(Item* item)
{
	for (p2ListItem<Item*>* aux = inventory.getFirst(); aux != nullptr; aux = aux->next)
	{
		if (item == aux->data)
		{

			inventory.del(aux);
			
			aux->data = nullptr;
			break;
		}
	}
}
