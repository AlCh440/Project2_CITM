#include "BattleTestScene.h"
#include "Log.h"
#include "App.h"
#include "Map.h"
#include "Physics.h"

BattleTestScene::BattleTestScene(bool isActive) : Module(isActive)
{
	name.Create("Battle Test Scene");
}

BattleTestScene::~BattleTestScene()
{
}

bool BattleTestScene::Awake(pugi::xml_node&)
{
	
	return true;
}

bool BattleTestScene::Start()
{
	LOG("Loading Battle Test");

	app->map->Load("BattleGroundTest.tmx");

	testBody = app->physics->CreateCircle(100, 100, 30);

	img=app->tex->Load("Assets/Sprites/dummySprite.png");

	return true;
}

bool BattleTestScene::PreUpdate()
{
	return true;
}

bool BattleTestScene::Update(float dt)
{
	return true;
}

bool BattleTestScene::PostUpdate()
{
	int x = 0;
	int y = 0;
	testBody->GetPosition(x, y);
	rect = { 0,0,50,100 };
	
	app->map->Draw();
	app->render->DrawTexture(img, x, y, &rect);
	return true;
}

bool BattleTestScene::CleanUp()
{
	return true;
}
