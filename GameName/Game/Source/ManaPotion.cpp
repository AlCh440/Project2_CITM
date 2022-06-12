#include "ManaPotion.h"
#include "Player.h"
#include "Entities.h"
#include "GuiButton.h"
#include "GuiManager.h"

ManaPotion::ManaPotion(Consumable_Type id) : Consumable(id)
{
	consumableId = id;
	itemType = POTION_MANA_;
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
	button = (GuiButton*)app->guiManager->pn_inventory->CreateGuiButton(app->guiManager->pn_inventory->GetNumberOfButtons(), app->guiManager, app->guiManager->pn_inventory, { 0, 0, 44, 44 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
	button->texture = texItems;
	button->normalRec = { 0, 150, 44, 44 };
	button->focusedRec = { 0, 150, 44, 44 };
	button->pressedRec = { 0, 150, 44, 44 };
}

void ManaPotion::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void ManaPotion::Consume(Player* user)
{
	user->stats.mana += 50;
	//HAS TO DELETE ITSELF
}
