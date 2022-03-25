#include "WorldTestScene.h"

WorldTestScene::WorldTestScene(bool isActive) : Module(isActive)
{
	name.Create("World Test Scene");
}

WorldTestScene::~WorldTestScene()
{
}

bool WorldTestScene::Awake()
{
	return true;
}

bool WorldTestScene::Start()
{
	return true;
}

bool WorldTestScene::PreUpdate()
{
	return true;
}

bool WorldTestScene::Update(float dt)
{
	return true;
}

bool WorldTestScene::PostUpdate()
{
	return true;
}

bool WorldTestScene::CleanUp()
{
	return true;
}
