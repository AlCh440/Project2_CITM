#include "Door.h"

Door::Door(Collider_Type type, iPoint pos, int width, int height, bool vertical, bool needKey, bool open):Entity(type,pos)
{
    this->type = type;
    position = pos;
    isVertical = vertical;
    this->needKey = needKey;
    Open = open;
    this->width = width;
    this->height = height;
}

Door::~Door()
{
}

bool Door::Start()
{   
    //load texture

    if (isVertical)
        direction = { 0,1 };
    else
        direction = { 1,0 };


    return true;
}

bool Door::Update(float dt)
{
    if (moving)
    {

    }
    return true;
}

bool Door::PostUpdate()
{
    //draw texture

    return true;
}

bool Door::Cleanup()
{
    return true;
}

bool Door::OpenDoor()
{
    Open = !Open;
    //if closed and not moving
    if (!Open && !moving)
    {
        physBody->body->SetLinearVelocity(direction);
        moving = true;
    }
    //if open and not moving
    else if (Open && !moving)
    {
        physBody->body->SetLinearVelocity(-direction);
        moving = true;
    }

    return false;
}
