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
    physBody = app->physics->CreateRectangle(x, y, width, height, b2_staticBody, b2Color{ 255,125,125,255 });
   
    if (isVertical)
        direction = { 0,1 };
    else
        direction = { 1,0 };
}

Door::~Door()
{
}

bool Door::Start()
{   
    //load texture

    return true;
}

bool Door::Update(float dt)
{


    return true;
}

bool Door::PostUpdate()
{
    //draw texture
    physBody->GetPosition(position.x, position.y);
    SDL_Rect r = { position.x,position.y,width,height };
    if(!Open)
        app->render->DrawRectangle(r, 255, 255, 125, 255, true);
    else
        app->render->DrawRectangle(r, 255, 255, 125, 100, true);
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
    if (!Open)
    {
        physBody->body->SetActive(true);
    }
    //if open and not moving
    else if (Open)
    {
        physBody->body->SetActive(false);
    }

    return true;
}
