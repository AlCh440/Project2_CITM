#pragma once
#include "Entity.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Player.h"

class Mage : public Player
{
public:

	Mage(iPoint pos);// remember to define the type of player
	~Mage();

	//bool BasicAttack(); // pass an ennemy
	bool MagicMissile();
	bool Heal();
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






};