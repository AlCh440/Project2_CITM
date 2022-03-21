#pragma once
#include "Entity.h"
#include "Defs.h"
#include "Point.h"
#include "Animation.h"
#include "Textures.h"
#include "Render.h"
#include "Player.h"

class Knight : public Player
{
public:

	Knight(iPoint pos, int type);
	~Knight();

	bool BasicAttack(); // pass an ennemy
	bool TauntHability();
	bool BindHability();
	bool ConcusionHability();




};