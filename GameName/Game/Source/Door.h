#pragma once
#include "Entity.h"
class Door : public Entity
{
public:
	Door();
	Door(Collider_Type type, iPoint pos,int with = 32,int height = 32,bool vertical = true,bool needKey = false,bool open=false);
	~Door();
	bool Start() override;
	bool Update(float dt) override;
	bool PostUpdate() override;
	bool Cleanup() override;
	bool OpenDoor();
	int id;
	int size;
	int x, y, width, height;
private:

	bool Open;
	bool needKey = true;
	bool moving = false;
	bool isVertical = true;
	float velocity = 10;

	b2Vec2 direction;
	
};

