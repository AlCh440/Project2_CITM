#include "Key.h"
#include "GuiButton.h"
#include "GuiManager.h"
#include "Window.h"

Key::Key(int id_) : Item()
{
	keyId = id_;
	itemType = itemType::KEY_;
	texItems = app->tex->Load("Assets/Sprites/UI/gameItems.png");
}

Key::Key(iPoint pos) : Item(pos)
{
}

Key::Key(Collider_Type type, iPoint pos) : Item(type, pos)
{
}

bool Key::Start()
{
	
	return true;
}

bool Key::PreUpdate()
{
	return true;
}

bool Key::Update(float dt)
{
	return true;
}

bool Key::CleanUp()
{
	return true;
}

bool Key::PostUpdate()
{
	return true;
}

void Key::CreateButton()
{
	iPoint pos = app->guiManager->pn_inventory->InitializeItemPos();
	button = (GuiButton*)app->guiManager->pn_inventory->CreateGuiButton(app->guiManager->pn_inventory->GetNumberOfButtons(), app->guiManager, app->guiManager->pn_inventory, { pos.x, pos.y, 44, 44 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);

	button->texture = texItems;
	if (keyId == 1)
	{
		button->normalRec = { 0, 150, 44, 44 };
		button->focusedRec = { 0, 150, 44, 44 };
		button->pressedRec = { 0, 150, 44, 44 };
	}
	else if (keyId == 2)
	{
		button->normalRec = { 110, 151, 44, 44 };
		button->focusedRec = { 110, 151, 44, 44 };
		button->pressedRec = { 110, 151, 44, 44 };
	}
	else if (keyId == 3)
	{
		button->normalRec = { 227, 151, 44, 44 };
		button->focusedRec = { 227, 151, 44, 44 };
		button->pressedRec = { 227, 151, 44, 44 };
	}
	else if (keyId == 4)
	{
		button->normalRec = { 331, 154, 44, 44 };
		button->focusedRec = { 331, 154, 44, 44 };
		button->pressedRec = { 331, 154, 44, 44 };
	}
	
	
}

int Key::GetKeyId()
{
	return keyId;
}

void Key::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
