#pragma once
#include "Entity.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Player.h"

enum rangerAttacks
{
	BASIC_ATTACK_,
	TAUNT_,
	BIND_,
	CONCUSSION_
};

class Ranger : public Player
{
public:

	Ranger(iPoint pos);// remember to define the type of player
	Ranger(Collider_Type type, iPoint pos);
	~Ranger();

	bool BasicAttack(); // pass an ennemy
	bool PrecisionShot();
	bool MultyShot();
	bool PowerfullStrike();

	bool Start() override;
	bool PreUpdate() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool CleanUp() override;


	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;

	// Load / Save
	bool LoadState(pugi::xml_node& data) override;
	bool SaveState(pugi::xml_node& data) const override;

private:
	uint attack;

	Animation basicHit;
	rangerAttacks attackChoosed;
};