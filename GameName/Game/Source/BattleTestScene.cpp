#include "BattleTestScene.h"

BattleTestScene::BattleTestScene(bool isActive) : Module(isActive)
{
	name.Create("Battle Test Scene");
}

BattleTestScene::~BattleTestScene()
{
}

bool BattleTestScene::Awake()
{
	return true;
}

bool BattleTestScene::Start()
{
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
	return true;
}

bool BattleTestScene::CleanUp()
{
	return true;
}
