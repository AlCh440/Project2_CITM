#pragma once
#include "Entity.h"
#include "Globals.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"

enum PlayerState
{
	IDLE,
	MOVE,
	JUMP,
	DOUBLE_JUMP,
	ATTACK,
	DEAD
};

class Player :  public Entity
{
public:
	Player(iPoint pos);
	Player(Collider_Type type, iPoint pos);
	virtual ~Player();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void SetPosition(iPoint pos);
	fPoint GetPosition() { return position; };
	void Spawn(iPoint pos);

	void Movement();
	void GodMovement();
	void UpdateSensorsPosition();

	//attacks
	void MeleeAttack();
	void SkillAttack();
	//skills?

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

	// Load / Save
	bool LoadState(pugi::xml_node& data);
	bool SaveState(pugi::xml_node& data) const;

public:
	Animation* currentAnim = nullptr;
	Animation* skillAnim = nullptr;
	Animation idlePlayerAnim, walkingPlayerAnim, jumpingPlayerAnim, deathPlayerAnim, meleePlayerAnim, skillPlayerAnim;

	float jumpForce = 15;
	float onAirXSpeed = 5;
	float jumpCooldown = 50;
	float currentJumpCd = 0;
	bool isSkillObtained = false;
	bool isSkillActive = false;
	bool doubleJump = false;
	bool onGround = false;
	bool onAir = false;
	bool wallLeft = false;
	bool wallRight = false;
	PlayerState state;
	SDL_RendererFlip direction;
	SDL_RendererFlip lastDirection;
	fPoint lastPosition;
	fPoint position;
	fPoint speed = { 8,8 };
	PhysBody* leftSensor;
	PhysBody* rightSensor;
	PhysBody* botSensor;
	PhysBody* topSensor;

	PhysBody* meleeAttack;
	PhysBody* skillAttack;

	int colliderRadius = 8;
	float gravityScale;

	int score = 0;

	int lives;
	bool isGodmodeOn = false;
	bool LoadRequest = false;

	int frameCounter = 0;
	int skillCounter = 0;

	int keysCollected = 0;

	int jumpFx;
};

