#pragma once
#include "Entity.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Player.h"
#include "Physics.h"
#include "Animation.h"

enum knightAttacks
{
	NOATTACK, 
	TAUNT,
	BIND, 
	CONCUSSION
};

class Knight : public Player
{
public:

	Knight(iPoint pos);// remember to define the type of player
	Knight(Collider_Type type, iPoint pos);
	

	bool BasicAttack(Entity* entity); // pass an ennemy
	bool TauntHability(Entity* entity);
	bool BindHability(Entity* entity);
	bool ConcusionHability(PhysBody* tarjet);

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

	
	knightAttacks attackChoosed = NOATTACK;

};