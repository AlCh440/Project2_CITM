#include "Key.h"
#include "GuiManager.h"
#include "Window.h"

Key::Key(int id_) : Item()
{
	keyId = id_;
	itemType = itemType::KEY_;

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
	/*
	button = (GuiButton*)app->guiManager->pn_inventory->CreateGuiButton(
		app->guiManager->pn_inventory->GetNumberOfButtons(),
		app->guiManager, app->guiManager->pn_inventory,
		{ (position.x + (uint)(222)) / app->win->GetScale(), ( position.y + (uint)(170)) / app->win->GetScale(), 44, 44 },
		"", 
		app->fonts->menuButtonFont, 
		app->fonts->c_Menus);

	button = (GuiButton*)app->guiManager->pn_inventory->CreateGuiButton(app->guiManager->pn_inventory->GetNumberOfButtons(), app->guiManager, app->guiManager->pn_inventory, { (int)((position.x + 222)) / app->win->GetScale(), (int)((position.y + 170) / app->win->GetScale()), 44, 44 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);

	button->texture = texItems;
	button->normalRec = { 0, 150, 44, 44 };
	button->focusedRec = { 0, 150, 44, 44 };
	button->pressedRec = { 0, 150, 44, 44 };
	*/
}

int Key::GetKeyId()
{
	return keyId;
}

void Key::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
