#include "Knight.h"
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

// Update Code
Knight::Knight(Collider_Type type, iPoint pos) : Player(type, pos)
{
	texture = app->tex->Load("Assets/Sprites/characters/charactersSpritesheet.png");
	physBody = app->physics->CreateCircle(pos.x, pos.y, 32.f * 0.5f, b2_dynamicBody);
	physBody->body->SetGravityScale(0);
	physBody->entityPtr = this;
	stats.hp = 100;
	stats.mana = 50;
	stats.movement = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	state = COMBATMOVE;
	moveTime = 32; //milisec
	counter = moveTime;
}

bool Knight::Start()
{

	stats.hp = 100;
	stats.mana = 50;
	stats.movement = 10;
	typeOfPlayer = 1;
	actionPoints = 10; // To determine
	isAlive = true;
	stepCounter = 0;

	direction = new iPoint{ 0, 0 };

	currentAnim = &walkSide;

	walkSide.PushBack({0, 0, 32, 48});
	walkSide.PushBack({32, 0, 32, 48});
	walkSide.PushBack({64, 0, 32, 48});
	walkSide.PushBack({96, 0, 32, 48});
	walkSide.loop = false;
	walkSide.speed = 0.2f;
	

	walkDown.PushBack({ 0, 48, 32, 48 });
	walkDown.PushBack({ 32, 48, 32, 48 });
	walkDown.PushBack({ 64, 48, 32, 48 });
	walkDown.PushBack({ 96, 48, 32, 48 });
	walkDown.loop = false;
	walkDown.speed = 0.2f;


	walkUp.PushBack({ 0, 96, 32, 48 });
	walkUp.PushBack({ 32, 96, 32, 48 });
	walkUp.PushBack({ 64, 96, 32, 48 });
	walkUp.PushBack({ 96, 96, 32, 48 });
	walkUp.loop = false;
	walkUp.speed = 0.2f;

	pathfinding = new PathFinding(true);
	//create navigation map
	int w, h;
	uchar* data = NULL;
	if (app->map->CreateWalkabilityMap(w, h, &data, 1)) pathfinding->SetMap(w, h, data);
	RELEASE_ARRAY(data);

	iPoint mapPos;
	mapPos=app->map->WorldToMap(position.x, position.y);

	pathfinding->InitBFS(mapPos);
	for (int i = 0; i < stats.movement *4 +1; i++)
		pathfinding->PropagateBFS();

	

	return true;
}

bool Knight::PreUpdate()
{

	if(state == COMBATMOVE)
	{
		if (stats.hp > 0)
		{
			isAlive = true;
		}
		else
		{
			isAlive = false;

			//deadth anim

			CleanUp();
		}
	}
	else
	{

	}

	

	return true;
}

bool Knight::Update(float dt)
{
//	LOG("%i", stats.momevent);


	if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		state = COMBATMOVE;
	}
	if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		state = CHOOSINGATTACK;
	}
	switch (state)
	{
	case COMBATMOVE:
	{
		
		//store the entity position in tiles
		iPoint pos;
		pos.x = position.x;
		pos.y = position.y;
		pos = app->map->WorldToMap(pos.x, pos.y);

		tilePos = pos;



		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KeyState::KEY_DOWN && !Move) {
			int x, y;
			app->input->GetMouseWorldPosition(x, y);
			iPoint p;
			p.x = x;
			p.y = y;
			p = app->map->WorldToMap(p.x, p.y);

			if (pathfinding->CreateVisitedPath(tilePos, p) != -1)
			{
				Move = true;
			}
			else {
				LOG("Error creating path...");
			}
		}

		if(Move)
		{
			for (stepCounter; stepCounter < pathfinding->GetLastPath()->Count() && nextStep; )
			{
				nextStep = false;

				currentP = pathfinding->GetLastPath()->At(stepCounter);
				nextP = pathfinding->GetLastPath()->At(stepCounter + 1);


				//end movement
				if (nextP == nullptr)
				{
					Move = false;
					stepCounter = 0;
					nextStep = true;
					break;
				}

				//calculate movement direction
				direction = new iPoint;
				direction->x = nextP->x - currentP->x;
				direction->y = nextP->y - currentP->y;

				walkSide.Reset();
				walkDown.Reset();
				walkUp.Reset();
				//error control and set anim
				if (direction->x >= 1)
				{
					direction->x = 1;
					currentAnim = &walkSide;
				}
				else if (direction->x <= -1)
				{
					direction->x = -1;
					currentAnim = &walkSide;
				}
				else  direction->x = 0; 

				if (direction->y >= 1)
				{
					direction->y = 1; 
					currentAnim = &walkDown;
				}
				else if (direction->y <= -1)
				{
					direction->y = -1;
					currentAnim = &walkUp;
				}
				else direction->y = 0;

				stepCounter++;
			}
				
			counter -= 1;
			if (counter >= 0 && !nextStep)
			{
				//move
				position.x += direction->x;
				position.y += direction->y;


				//get next tile world position
				iPoint p;
				p = app->map->MapToWorld(nextP->x, nextP->y);

				//get the "correct" position
				iPoint pUpleft;
				pUpleft.x = position.x - app->map->mapData.tileWidth * 0.5f;
				pUpleft.y = position.y - app->map->mapData.tileHeight * 0.5f;

				// check if is in destination position
				if (pUpleft.x == p.x && pUpleft.y == p.y)
				{
					nextStep = true;
					stats.movement -= 1;
				}

				counter = moveTime;
			}
		}

		b2Vec2 teleport = { PIXEL_TO_METERS((float)position.x),  PIXEL_TO_METERS((float)position.y) };
		physBody->body->SetTransform(teleport, 0.f);

	}break;
	case CHOOSINGATTACK:
	{
		if (app->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
		{
			attackChoosed = TAUNT;
			state = CHOOSINGOBJECTIVE;
		}
		else if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
		{
			attackChoosed = BIND;
			state = CHOOSINGOBJECTIVE;
		}
		else if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
		{
			attackChoosed = CONCUSSION;
			state = CHOOSINGOBJECTIVE;
		}

	} break;
	case CHOOSINGOBJECTIVE:
	{
		switch (attackChoosed)
		{
		case CONCUSSION:
		{
			// THE PLAYER CHOOSES THE ENEMY HE WANTS, RIGHT NOW  IS JUST THE CLOSER!!!
			ConcusionHability(checkCloseEnemies());
			state = ATTACKING;

		} break;
		default:
		{

		} break;
		}

	} break;
	case ATTACKING:
	{
		state = COMBATMOVE;
	} break;
	default:
	{

	}break;
	}

	if (stats.movement <= 0)
	{
		stats.movement = 10;
		entityTurn = false;

		pathfinding->ResetBFSPath();
		iPoint mapPos;
		mapPos = app->map->WorldToMap(position.x, position.y);

		pathfinding->InitBFS(mapPos);

		for (int i = 0; i < stats.movement * 4 + 1; i++)
			pathfinding->PropagateBFS();

	}
	currentAnim->Update();


	return true;
}

bool Knight::PostUpdate()
{
	SDL_Rect r;

	pathfinding->DrawBFSPath();

	if (direction->x <= 0)
	{
		app->render->DrawTexture(texture, position.x - 20, position.y -30, &currentAnim->GetCurrentFrame());
	}
	else
	{
		app->render->DrawTexture(texture, position.x - 20, position.y -30, &currentAnim->GetCurrentFrame(), 1.0f, 0.0f, 2147483647, 2147483647, 1.0f, SDL_FLIP_HORIZONTAL);
	}



	//Draw path
	const DynArray<iPoint>* path = pathfinding->GetLastPath();

	SDL_Rect rect;
	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		rect.x = (pos.x);
		rect.y = (pos.y);
		rect.w = (app->map->mapData.tileWidth);
		rect.h = (app->map->mapData.tileHeight);
		app->render->DrawRectangle(rect, 255, 125, 0, 150);
	}


	int x, y;

	app->input->GetMouseWorldPosition(x, y);
	iPoint p;
	p.x = x;
	p.y = y;
	p = app->map->WorldToMap(p.x, p.y);
	p = app->map->MapToWorld(p.x, p.y);

	r.x = p.x;
	r.y = p.y;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 125, 255, 255, 150, true);

	r.x = position.x - app->map->mapData.tileWidth * .5f;
	r.y = position.y - app->map->mapData.tileHeight * .5f ;
	r.w = app->map->mapData.tileWidth;
	r.h = app->map->mapData.tileHeight;

	app->render->DrawRectangle(r, 125, 255, 0, 150, true);

	return true;
}

bool Knight::CleanUp()
{
	// destroy the physbody

	return true;
}

bool Knight::BasicAttack() // pass an ennemy
{


	return true;
}

bool Knight::TauntHability()
{


	return true;
}

bool Knight::BindHability()
{


	return true;
}

bool Knight::ConcusionHability(PhysBody* tarjet)
{
	tarjet->entityPtr->takeDamage(20);

	return true;
}

// OnCollision
void Knight::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

}

// Load / Save
bool Knight::LoadState(pugi::xml_node& data) 
{


	return true;
}

bool Knight::SaveState(pugi::xml_node& data) const
{


	return true;
}