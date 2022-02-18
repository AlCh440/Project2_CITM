#include "Globals.h"
#include "App.h"
#include "Input.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "ModulePlayer.h"
#include "Map.h"
#include "Log.h"
#include <SDL/include/SDL_scancode.h>

ModulePlayer::ModulePlayer(bool isActive) : Module(isActive)
{
	name.Create("player");
}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Awake()
{

	return true;
}

// Load assets
bool ModulePlayer::Start()
{
	//Initializing player struct data
	if (physBody == NULL)
	{
		state = IDLE;

		playerTexture = app->tex->Load("Assets/Spritesx16/characters.png");
		//Idle anim
		idlePlayerAnim.PushBack({ 262, 43, 16, 21 });
		idlePlayerAnim.PushBack({ 294, 43, 16, 21 });
		idlePlayerAnim.PushBack({ 327, 43, 16, 21 });
		idlePlayerAnim.loop = false;
		idlePlayerAnim.mustFlip = true;
		idlePlayerAnim.speed = 0.04f;
		//Walking anim
		walkingPlayerAnim.PushBack({ 390, 43, 16, 21 });
		walkingPlayerAnim.PushBack({ 454, 43, 16, 21 });
		walkingPlayerAnim.loop = true;
		walkingPlayerAnim.mustFlip = true;
		walkingPlayerAnim.speed = 0.1f;
		//Jump anim
		jumpingPlayerAnim.PushBack({ 390, 43, 16, 21 });
		jumpingPlayerAnim.PushBack({ 422, 43, 16, 21 });
		jumpingPlayerAnim.PushBack({ 454, 43, 16, 21 });
		jumpingPlayerAnim.PushBack({ 486, 47, 16, 16 });
		jumpingPlayerAnim.loop = false;
		jumpingPlayerAnim.mustFlip = true;
		jumpingPlayerAnim.speed = 0.1f;
		//Death anim
		deathPlayerAnim.PushBack({ 0, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 19, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 38, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 57, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 76, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 95, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 114, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 133, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 152, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 171, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 171, 212, 19, 44 });
		deathPlayerAnim.PushBack({ 171, 212, 19, 44 });
		deathPlayerAnim.loop = false;
		deathPlayerAnim.mustFlip = true;
		deathPlayerAnim.speed = 0.1f;
		//Melee attack anim
		meleePlayerAnim.PushBack({ 0, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 0, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 37, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 74, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 111, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 148, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 185, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 222, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 259, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 296, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 333, 0, 37, 28 });
		meleePlayerAnim.PushBack({ 333, 0, 37, 28 });
		meleePlayerAnim.loop = false;
		meleePlayerAnim.mustFlip = true;
		meleePlayerAnim.speed = 0.3f;

		currentAnim = &idlePlayerAnim;
		state = IDLE;

		position = { 20, 300 };
		physBody = app->physics->CreateCircle(position.x, position.y, colliderRadius, b2_dynamicBody, { 0,250,125,255 });
		physBody->listener = app->levelManagement->currentScene;
		physBody->type = Collider_Type::PLAYER;
		physBody->body->SetFixedRotation(true);
		app->physics->allPhysicBodies.add(physBody);


		currentJumpCd = jumpCooldown;

		//sensors
		leftSensor = app->physics->CreateRectangleSensor(position.x, position.y,4,10, b2_dynamicBody, { 255,165,0,255 });
		rightSensor = app->physics->CreateRectangleSensor(position.x, position.y,4,10, b2_dynamicBody, { 255,165,0,255 });
		topSensor = app->physics->CreateRectangleSensor(position.x, position.y,12,4, b2_dynamicBody, { 255,165,0,255 });
		botSensor = app->physics->CreateRectangleSensor(position.x, position.y,12,4, b2_dynamicBody, { 255,165,0,255 });

		//leftSensor->listener = app->player;
		//rightSensor->listener = app->player;
		//topSensor->listener = app->player;
		//botSensor->listener = app->player;

		leftSensor->type = Collider_Type::PLAYER_X_SENSOR;
		rightSensor->type = Collider_Type::PLAYER_X_SENSOR;
		topSensor->type = Collider_Type::PLAYER_Y_SENSOR;
		botSensor->type = Collider_Type::PLAYER_Y_SENSOR;

		app->physics->allPhysicBodies.add(leftSensor);
		app->physics->allPhysicBodies.add(rightSensor);
		app->physics->allPhysicBodies.add(topSensor);
		app->physics->allPhysicBodies.add(botSensor);

		position.x = physBody->body->GetPosition().x;
		position.y = physBody->body->GetPosition().y;
		lastPosition = position;

		lives = 1;
	}
	else if (physBody->body == NULL) {

		physBody = app->physics->CreateCircle(position.x, position.y, colliderRadius, b2_dynamicBody, { 0,250,125,255 });
		physBody->listener = app->levelManagement->currentScene;
		physBody->type = Collider_Type::PLAYER;
		physBody->body->SetFixedRotation(true);
		app->physics->allPhysicBodies.add(physBody);

		position.x = physBody->body->GetPosition().x;
		position.y = physBody->body->GetPosition().y;

		//sensors
		leftSensor = app->physics->CreateRectangleSensor(position.x, position.y, 4, 10, b2_dynamicBody, { 255,165,0,255 });
		rightSensor = app->physics->CreateRectangleSensor(position.x, position.y, 4, 10, b2_dynamicBody, { 255,165,0,255 });
		topSensor = app->physics->CreateRectangleSensor(position.x, position.y, 12, 4, b2_dynamicBody, { 255,165,0,255 });
		botSensor = app->physics->CreateRectangleSensor(position.x, position.y, 12, 4, b2_dynamicBody, { 255,165,0,255 });

		//leftSensor->listener = app->player;
		//rightSensor->listener = app->player;
		//topSensor->listener = app->player;
		//botSensor->listener = app->player;

		leftSensor->type = Collider_Type::PLAYER_X_SENSOR;
		rightSensor->type = Collider_Type::PLAYER_X_SENSOR;
		topSensor->type = Collider_Type::PLAYER_Y_SENSOR;
		botSensor->type = Collider_Type::PLAYER_Y_SENSOR;

		app->physics->allPhysicBodies.add(leftSensor);
		app->physics->allPhysicBodies.add(rightSensor);
		app->physics->allPhysicBodies.add(topSensor);
		app->physics->allPhysicBodies.add(botSensor);

		lastPosition = position;
	}
	return true;
}

bool ModulePlayer::PreUpdate()
{
	if (LoadRequest)
	{
		iPoint p;
		p.x = position.x;
		p.y = position.y;
		SetPosition(p);
		LoadRequest = false;
	}

	if (lives <= 0) state = DEAD;

	if (state == DEAD) // if dead exit function, we wont input anything
		return true;

	position.x = physBody->body->GetPosition().x;
	position.y = physBody->body->GetPosition().y;

	if (physBody->body->GetLinearVelocity().y > 1)
	{
		physBody->body->SetGravityScale(3);
		onGround = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
		isGodmodeOn = !isGodmodeOn;

	if (isGodmodeOn)
	{
		MeleeAttack();
		if (state != ATTACK)
			GodMovement();

	}else
	{
		MeleeAttack();
		if(state != ATTACK)
			Movement();
	}
	
	return true;
}

// Update: draw background
bool ModulePlayer::Update(float dt)
{
	bool ret = true;

	UpdateSensorsPosition();
	currentJumpCd -= dt;

	switch (state)
	{
	case IDLE:
		idlePlayerAnim.Update();
		walkingPlayerAnim.Reset();
		meleePlayerAnim.Reset();
		break;
	case JUMP:
		jumpingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		walkingPlayerAnim.Reset();
		meleePlayerAnim.Reset();
		break;
	case MOVE:
		walkingPlayerAnim.Update();
		idlePlayerAnim.Reset();
		meleePlayerAnim.Reset();
		break;
	case ATTACK:
		meleePlayerAnim.Update();
		idlePlayerAnim.Reset();
		break;
	case DEAD:
		physBody->body->SetType(b2_staticBody);
		break;
	}
	currentAnim->Update();
	

	return ret;

}

bool ModulePlayer::PostUpdate()
{
	//check if player in map boundaries; Screen size is in pixels
	fPoint pixelPosition;
	pixelPosition.x = METERS_TO_PIXELS(position.x);
	pixelPosition.y = METERS_TO_PIXELS(position.y);

	b2Vec2 newPos;
	newPos.x = lastPosition.x;
	newPos.y = lastPosition.y;

	//Left Right boundaries
	if ((pixelPosition.x + colliderRadius) > SCREEN_WIDTH || (pixelPosition.x - colliderRadius) < 0)
	{
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
		physBody->body->SetLinearVelocity({ 0, physBody->body->GetLinearVelocity().y });
	}

	//Top Bot boundaries
	if ((pixelPosition.y + colliderRadius) > SCREEN_HEIGHT || (pixelPosition.y - colliderRadius) < 0)
	{
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
		physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, 0 });
	}

	//store Lats position after all the update
	lastPosition = position;


	switch (state)
	{
	case IDLE:
		currentAnim = &idlePlayerAnim;
		break;
	case MOVE:
		currentAnim = &walkingPlayerAnim;
		break;
	case JUMP:
		currentAnim = &jumpingPlayerAnim;
		break;
	case ATTACK:
		currentAnim = &meleePlayerAnim;
		break;
	case DEAD:
		currentAnim = &deathPlayerAnim;
		if (currentAnim->HasFinished())
		{
			app->levelManagement->gameState = LevelManagement::GameState::GAME_OVER;
		}
		break;
	}

	if (playerTexture != NULL)
	{
		SDL_Rect* rect;
		rect = &currentAnim->GetCurrentFrame();

		if (state == ATTACK && direction == 1)
		{
			app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 52), METERS_TO_PIXELS(physBody->body->GetPosition().y) - 26,
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else if (state == DEAD)
		{
			if (direction == 1)
			{
				app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 19), METERS_TO_PIXELS(physBody->body->GetPosition().y - 65),
					&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
			}
			else app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 19), METERS_TO_PIXELS(physBody->body->GetPosition().y - 65),
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else app->render->DrawTexture(playerTexture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 16), METERS_TO_PIXELS(physBody->body->GetPosition().y - 26),
			&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
	}
		

	if (state == ATTACK && frameCounter < 20)
	{
		frameCounter++;
	}
	else if (frameCounter >= 20)
	{
		state = IDLE;
		frameCounter = 0;
		meleeAttack->pendingToDelete = true;
	}

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	if (physBody != nullptr)
	{
		leftSensor->pendingToDelete = true;
		rightSensor->pendingToDelete = true;
		topSensor->pendingToDelete = true;
		botSensor->pendingToDelete = true;

		delete leftSensor;
		delete	rightSensor;
		delete topSensor;
		delete botSensor;


		leftSensor = nullptr;
		rightSensor = nullptr;
		topSensor = nullptr;
		botSensor = nullptr;

		state = IDLE;
		physBody->pendingToDelete = true;
		delete physBody;
		physBody = nullptr;
		currentAnim = nullptr;
	}
	return true;
}

void ModulePlayer::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);
	if(physBody->body != nullptr)
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}

void ModulePlayer::Spawn(iPoint pos)
{
	Enable();
	SetPosition(pos);
	state = IDLE;
	lives = 1;
}

void ModulePlayer::Movement()
{
	if (onGround){

		//Ground movement
				//Jump
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) && currentJumpCd <= 0 && (physBody->body->GetLinearVelocity().y < 0.1 && physBody->body->GetLinearVelocity().y > -0.1))
		{
			physBody->body->SetGravityScale(2);
			physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(), true);
			onGround = false;	doubleJump = true;
			currentJumpCd = jumpCooldown;
			state = JUMP;

			if (physBody->body->GetLinearVelocity().y > speed.y)
			{
				physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y });
			}
		}else
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				physBody->body->SetLinearVelocity({ speed.x, physBody->body->GetLinearVelocity().y });
				state = MOVE;
				direction = SDL_FLIP_NONE;
			}
			else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				physBody->body->SetLinearVelocity({ -speed.x, physBody->body->GetLinearVelocity().y });
				state = MOVE;
				direction = SDL_FLIP_HORIZONTAL;
			}
			else {
				physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });
				state = IDLE;
			}
		

		////Jump
		//if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) && currentJumpCd <= 0 && (physBody->body->GetLinearVelocity().y < 0.1 && physBody->body->GetLinearVelocity().y > -0.1))
		//{
		//	physBody->body->SetGravityScale(2);
		//	physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(), true);
		//	onGround = false;	doubleJump = true;
		//	currentJumpCd = jumpCooldown;
		//	state = JUMP;

		//	if (physBody->body->GetLinearVelocity().y > speed.y)
		//	{
		//		physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y });
		//	}
		//}
	}
	else {//on air

		//Double jump
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && doubleJump)
		{
			physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x,0 });
			physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(), true);
			doubleJump = false;
			state = DOUBLE_JUMP;

			if (physBody->body->GetLinearVelocity().y >= speed.y)
			{
				
				physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y });
			}
		}

		//on air X movement
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			physBody->body->SetLinearVelocity({ onAirXSpeed, physBody->body->GetLinearVelocity().y });
			direction = SDL_FLIP_NONE;
		}
		else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			physBody->body->SetLinearVelocity({ -onAirXSpeed, physBody->body->GetLinearVelocity().y });
			direction = SDL_FLIP_HORIZONTAL;
		}

	}
}

void ModulePlayer::GodMovement()
{
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		physBody->body->SetLinearVelocity({ speed.x * 1.5f, physBody->body->GetLinearVelocity().y });
		state = MOVE;
		direction = SDL_FLIP_NONE;
	}
	else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT )
	{
		physBody->body->SetLinearVelocity({ -speed.x * 1.5f, physBody->body->GetLinearVelocity().y });
		state = MOVE;
		direction = SDL_FLIP_HORIZONTAL;
	}
	else physBody->body->SetLinearVelocity({ 0, physBody->body->GetLinearVelocity().y });

	if ((app->input->GetKey(SDL_SCANCODE_UP) || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) )
	{
		physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, -speed.y * 1.5f });
		state = JUMP;
	}
	else if ((app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT))
	{
		physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y * 1.5f });
		state = JUMP;
	}
	else physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, 0 });
}

void ModulePlayer::UpdateSensorsPosition()
{
	float offset;
	b2Vec2 newPos;
	newPos.x = position.x - PIXEL_TO_METERS(8);
	newPos.y = position.y;
	leftSensor->body->SetTransform(newPos, 0);
	newPos.x = position.x + PIXEL_TO_METERS(8);
	newPos.y = position.y;
	rightSensor->body->SetTransform(newPos, 0);
	newPos.x = position.x ;
	newPos.y = position.y - PIXEL_TO_METERS(8);
	topSensor->body->SetTransform(newPos, 0);
	newPos.x = position.x;
	newPos.y = position.y + PIXEL_TO_METERS(8);
	botSensor->body->SetTransform(newPos, 0);
}

void ModulePlayer::MeleeAttack()
{
	if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && state != ATTACK)
	{
		//attack collider spawn offset 
		int dir = 0;
		if (direction == 1) dir = -25;
		else dir = 20;

		physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });

		meleeAttack = app->physics->CreateRectangleSensor(METERS_TO_PIXELS(physBody->body->GetPosition().x) + dir,
			METERS_TO_PIXELS(physBody->body->GetPosition().y), 18, 20, b2_staticBody);
		meleeAttack->color = { 120, 50, 100, 155 };
		meleeAttack->listener = app->levelManagement->currentScene;
		meleeAttack->type = Collider_Type::PLAYER_ATTACK;
		app->physics->allPhysicBodies.add(meleeAttack);

		state = ATTACK;
	}
}

void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	wallLeft = false;
	wallRight = false;
	if (bodyA->type == PLAYER_X_SENSOR && bodyB->type == GROUND)
	{
		if (bodyA->body == leftSensor->body)
		{
			LOG("left collison");
			wallLeft = true;
		}
		if (bodyA->body == rightSensor->body)
		{
			LOG("right collison");
			wallRight = true;
		}
	}
	else if (bodyA->type == PLAYER_Y_SENSOR && bodyB->type == GROUND)
	{
		if (bodyA->body == topSensor->body)
		{
			LOG("top collison");
		}
		else if (bodyA->body == botSensor->body)
		{
			LOG("bot collison");
			onGround = true;
			doubleJump = false;
			physBody->body->SetGravityScale(1);
		}
	}
	

}

bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	position.x = data.child("player").attribute("x").as_int();
	position.y = data.child("player").attribute("y").as_int();
	lives = data.child("player").attribute("lives").as_int();
	state = static_cast<PlayerState>(data.child("player").attribute("state").as_int());

	LoadRequest = true;

	return ret;
}

bool ModulePlayer::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node player = data.append_child("player");
	player.append_attribute("x") = physBody->body->GetPosition().x;
	player.append_attribute("y") = physBody->body->GetPosition().y;
	player.append_attribute("lives") = lives;
	player.append_attribute("state") = state;
	return ret;
}