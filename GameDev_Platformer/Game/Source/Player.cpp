#include "Player.h"
#include "Globals.h"
#include "App.h"
#include "Audio.h"
#include "Input.h"
#include "ModuleEntities.h"
#include "ModulePhysics.h"
#include "LevelManagement.h"
#include "Render.h"
#include "Map.h"
#include "Log.h"
#include <SDL/include/SDL_scancode.h>


Player::Player(iPoint pos) : Entity(pos)
{
	name = "player";
}

Player::Player(Collider_Type type, iPoint pos) : Entity(type, pos)
{
}

Player::~Player()
{
}

// Load assets
bool Player::Start()
{
	//Initializing player struct data
	if (physBody == NULL)
	{
		state = PlayerState::IDLE;

		texture = app->tex->Load("Assets/Spritesx16/characters.png");
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
		//Skill attack anim
		skillPlayerAnim.PushBack({ 365, 0, 21, 18 });
		skillPlayerAnim.PushBack({ 386, 0, 21, 18 });
		skillPlayerAnim.PushBack({ 407, 0, 21, 18 });
		skillPlayerAnim.PushBack({ 428, 0, 21, 18 });
		skillPlayerAnim.loop = true;
		skillPlayerAnim.mustFlip = true;
		skillPlayerAnim.speed = 0.5f;

		currentAnim = &idlePlayerAnim;
		skillAnim = &skillPlayerAnim;
		state = PlayerState::IDLE;

		position = { 20, 300 };
		physBody = app->physics->CreateCircle(position.x, position.y, colliderRadius, b2_dynamicBody, { 0,250,125,255 });
		physBody->listener = app->entities;
		physBody->type = Collider_Type::PLAYER;
		physBody->body->SetFixedRotation(true);
		app->physics->allPhysicBodies.add(physBody);

		type = physBody->type;

		currentJumpCd = jumpCooldown;

		//sensors
		leftSensor = app->physics->CreateRectangleSensor(position.x, position.y, 4, 10, b2_dynamicBody, { 255,165,0,255 });
		rightSensor = app->physics->CreateRectangleSensor(position.x, position.y, 4, 10, b2_dynamicBody, { 255,165,0,255 });
		topSensor = app->physics->CreateRectangleSensor(position.x, position.y, 12, 4, b2_dynamicBody, { 255,165,0,255 });
		botSensor = app->physics->CreateRectangleSensor(position.x, position.y, 12, 4, b2_dynamicBody, { 255,165,0,255 });

		leftSensor->listener = app->entities;
		rightSensor->listener = app->entities;
		topSensor->listener = app->entities;
		botSensor->listener = app->entities;

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

		jumpFx = app->audio->LoadFx("Assets/audio/fx/Jump.wav");
	}
	return true;
}

bool Player::PreUpdate()
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
		SkillAttack();
		if (state != ATTACK)
			GodMovement();

	}
	else
	{
		MeleeAttack();
		SkillAttack();
		if (state != ATTACK)
			Movement();
	}

	return true;
}

// Update: draw background
bool Player::Update(float dt)
{
	bool ret = true;

	UpdateSensorsPosition();
	currentJumpCd -= dt;


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
		break;
	}


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
		if (currentAnim->HasFinished())
		{
			app->levelManagement->gameState = LevelManagement::GameState::GAME_OVER;
			app->entities->coinsCollected = 0;
		}
		break;
	}
	if (isSkillActive)
	{
		skillPlayerAnim.Update();
		idlePlayerAnim.Reset();
	}
	currentAnim->Update();


	return ret;

}

bool Player::PostUpdate()
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


	if (texture != NULL)
	{
		SDL_Rect* rect;
		rect = &currentAnim->GetCurrentFrame();

		if (state == ATTACK && direction == 1)
		{
			app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 52), METERS_TO_PIXELS(physBody->body->GetPosition().y) - 26,
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else if (isSkillActive)
		{
			if (direction == 1)
			{
				app->render->DrawTexture(texture, METERS_TO_PIXELS(skillAttack->body->GetPosition().x - 15), METERS_TO_PIXELS(skillAttack->body->GetPosition().y -16),
					&(skillAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
			}
			else app->render->DrawTexture(texture, METERS_TO_PIXELS(skillAttack->body->GetPosition().x - 15), METERS_TO_PIXELS(skillAttack->body->GetPosition().y - 16),
				&(skillAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
			app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 16), METERS_TO_PIXELS(physBody->body->GetPosition().y - 26),
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else if (state == DEAD)
		{
			if (direction == 1)
			{
				app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 19), METERS_TO_PIXELS(physBody->body->GetPosition().y - 65),
					&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
			}
			else app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 19), METERS_TO_PIXELS(physBody->body->GetPosition().y - 65),
				&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
		}
		else app->render->DrawTexture(texture, METERS_TO_PIXELS(physBody->body->GetPosition().x - 16), METERS_TO_PIXELS(physBody->body->GetPosition().y - 26),
			&(currentAnim->GetCurrentFrame()), 1, 1, 1, 1, 1.8f, direction);
	}

	if (state == ATTACK && frameCounter < 20)
	{
		frameCounter++;
	}
	else if (frameCounter >= 20)
	{
		state = PlayerState::IDLE;
		frameCounter = 0;
		meleeAttack->pendingToDelete = true;
	}

	if (isSkillActive)
	{
		if (lastDirection == 0)
		{
			if (skillCounter < 30)
			{
				skillAttack->body->SetLinearVelocity({ 20, 0 });
				skillCounter++;
			}
			else if (skillCounter >= 30 && skillCounter < 60)
			{
				skillAttack->body->SetLinearVelocity({ -20, 0 });
				skillCounter++;
			}
			else
			{
				skillAttack->pendingToDelete = true;
				isSkillActive = false;
				skillCounter = 0;
			}
		}
		else
		{
			if (skillCounter < 30)
			{
				skillAttack->body->SetLinearVelocity({ -20, 0 });
				skillCounter++;
			}
			else if (skillCounter >= 30 && skillCounter < 60)
			{
				skillAttack->body->SetLinearVelocity({ 20, 0 });
				skillCounter++;
			}
			else
			{
				skillAttack->pendingToDelete = true;
				isSkillActive = false;
				skillCounter = 0;
				skillPlayerAnim.Reset();
			}
		}
	}

	return true;
}

// Unload assets
bool Player::CleanUp()
{

	leftSensor->pendingToDelete = true;
	rightSensor->pendingToDelete = true;
	topSensor->pendingToDelete = true;
	botSensor->pendingToDelete = true;
	
	leftSensor = nullptr;
	rightSensor = nullptr;
	topSensor = nullptr;
	botSensor = nullptr;

	state = PlayerState::IDLE;
	physBody->pendingToDelete = true;
	physBody = nullptr;
	currentAnim = nullptr;
	
	return true;
}

void Player::SetPosition(iPoint pos)
{
	b2Vec2 newPos;

	iPoint pixelPos = app->map->MapToWorld(pos.x, pos.y);

	newPos.x = PIXEL_TO_METERS(pixelPos.x);
	newPos.y = PIXEL_TO_METERS(pixelPos.y);
	if (physBody->body != nullptr)
		physBody->body->SetTransform(newPos, physBody->body->GetAngle());
}

void Player::Spawn(iPoint pos)
{
	SetPosition(pos);
	state = PlayerState::IDLE;
	lives = 1;
}

void Player::Movement()
{
	if (onGround) {

		//Ground movement
				//Jump
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT) && 
			currentJumpCd <= 0 && (physBody->body->GetLinearVelocity().y < 0.1 && physBody->body->GetLinearVelocity().y > -0.1))
		{
			physBody->body->SetGravityScale(2);
			physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(), true);
			onGround = false;	doubleJump = true;
			currentJumpCd = jumpCooldown;
			state = JUMP;
			app->audio->PlayFx(jumpFx);

			if (physBody->body->GetLinearVelocity().y > speed.y)
			{
				physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x, speed.y });
			}
		}
		else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && state != JUMP)
		{
			physBody->body->SetLinearVelocity({ speed.x, physBody->body->GetLinearVelocity().y });
			state = PlayerState::MOVE;
			direction = SDL_FLIP_NONE;
		}
		else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && state != JUMP)
		{
			physBody->body->SetLinearVelocity({ -speed.x, physBody->body->GetLinearVelocity().y });
			state = PlayerState::MOVE;
			direction = SDL_FLIP_HORIZONTAL;
		}
		else {
			physBody->body->SetLinearVelocity({ 0 , physBody->body->GetLinearVelocity().y });
			state = PlayerState::IDLE;
		}
	}
	else {//on air

		//Double jump
		if ((app->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) && doubleJump)
		{
			physBody->body->SetLinearVelocity({ physBody->body->GetLinearVelocity().x,0 });
			physBody->body->ApplyLinearImpulse(b2Vec2(0, -jumpForce), physBody->body->GetWorldCenter(), true);
			doubleJump = false;
			state = DOUBLE_JUMP;
			app->audio->PlayFx(jumpFx);
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

void Player::GodMovement()
{
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		physBody->body->SetLinearVelocity({ speed.x * 1.5f, physBody->body->GetLinearVelocity().y });
		state = PlayerState::MOVE;
		direction = SDL_FLIP_NONE;
	}
	else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		physBody->body->SetLinearVelocity({ -speed.x * 1.5f, physBody->body->GetLinearVelocity().y });
		state = PlayerState::MOVE;
		direction = SDL_FLIP_HORIZONTAL;
	}
	else physBody->body->SetLinearVelocity({ 0, physBody->body->GetLinearVelocity().y });

	if ((app->input->GetKey(SDL_SCANCODE_UP) || app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT))
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

void Player::UpdateSensorsPosition()
{
	float offset;
	b2Vec2 newPos;
	newPos.x = position.x - PIXEL_TO_METERS(8);
	newPos.y = position.y;
	leftSensor->body->SetTransform(newPos, 0);
	newPos.x = position.x + PIXEL_TO_METERS(8);
	newPos.y = position.y;
	rightSensor->body->SetTransform(newPos, 0);
	newPos.x = position.x;
	newPos.y = position.y - PIXEL_TO_METERS(8);
	topSensor->body->SetTransform(newPos, 0);
	newPos.x = position.x;
	newPos.y = position.y + PIXEL_TO_METERS(8);
	botSensor->body->SetTransform(newPos, 0);
}

void Player::MeleeAttack()
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

void Player::SkillAttack()
{
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && state != ATTACK && isSkillActive == false)
	{
		//attack collider spawn offset 
		int dir = 0;
		if (direction == 1) dir = -25;
		else dir = 20;
		lastDirection = direction;

		skillAttack = app->physics->CreateRectangleSensor(METERS_TO_PIXELS(physBody->body->GetPosition().x) + dir,
					  METERS_TO_PIXELS(physBody->body->GetPosition().y), 18, 20, b2_kinematicBody);
		skillAttack->color = { 120, 50, 100, 155 };
		skillAttack->listener = app->levelManagement->currentScene;
		skillAttack->type = Collider_Type::PLAYER_ATTACK;
		app->physics->allPhysicBodies.add(skillAttack);

		isSkillActive = true;
	}
}

void Player::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

bool Player::LoadState(pugi::xml_node& data)
{
	bool ret = true;

	b2Vec2 p;
	p.x = data.child("player").attribute("x").as_int();
	p.y = data.child("player").attribute("y").as_int();

	physBody->body->SetTransform(p,0);
	lives = data.child("player").attribute("lives").as_int();
	state = static_cast<PlayerState>(data.child("player").attribute("state").as_int());
	app->entities->coinsCollected = data.child("player").attribute("coins").as_int();
	keysCollected = data.child("player").attribute("keys").as_int();

	return ret;
}

bool Player::SaveState(pugi::xml_node& data) const
{
	bool ret = true;
	pugi::xml_node player = data.append_child("player");
	player.append_attribute("type") = type;
	player.append_attribute("x") = physBody->body->GetPosition().x;
	player.append_attribute("y") = physBody->body->GetPosition().y;
	player.append_attribute("lives") = lives;
	player.append_attribute("state") = state;
	player.append_attribute("coins") = app->entities->coinsCollected;
	player.append_attribute("keys") = keysCollected;
	return ret;
}