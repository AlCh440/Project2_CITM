#include "ManaPotion.h"
#include "Player.h"
#include "Entities.h"
#include "GuiButton.h"
#include "GuiManager.h"

ManaPotion::ManaPotion(Consumable_Type id) : Consumable(id)
{
	consumableId = id;
	itemType = POTION_MANA_;
	texItems = app->tex->Load("Assets/Sprites/UI/gameItems.png");
}

bool ManaPotion::Start()
{
	return true;
}

bool ManaPotion::PreUpdate()
{
	return true;
}

bool ManaPotion::Update(float dt)
{
	return true;
}

bool ManaPotion::CleanUp()
{
	return true;
}

bool ManaPotion::PostUpdate()
{
	return true;
}

void ManaPotion::CreateButton()
{
	iPoint pos = app->guiManager->pn_inventory->InitializeItemPos();
	button = (GuiButton*)app->guiManager->pn_inventory->CreateGuiButton(app->guiManager->pn_inventory->GetNumberOfButtons(), app->guiManager, app->guiManager->pn_inventory, { pos.x, pos.y, 44, 44 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
	button->texture = texItems;

	button->normalRec = { 255, -2, 44, 44 };
	button->focusedRec = { 255, -2, 44, 44 };
	button->pressedRec = { 255, -2, 44, 44 };
}

void ManaPotion::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void ManaPotion::Consume(Player* user)
{
	user->stats.mana += 50;
	//HAS TO DELETE ITSELF
}
