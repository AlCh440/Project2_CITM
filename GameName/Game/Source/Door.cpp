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
    x = position.x;
    y = position.y;
    physBody = app->physics->CreateRectangle(x, y, width, height, b2_kinematicBody, b2Color{ 255,125,125,255 });
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
    physBody->GetPosition(position.x, position.y);
    SDL_Rect r = { position.x,position.y,width,height };
    app->render->DrawRectangle(r, 255, 255, 125, 255, true);

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
