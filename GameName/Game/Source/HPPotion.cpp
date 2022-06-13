#include "HPPotion.h"
#include "Player.h"
#include "Entities.h"
#include "GuiButton.h"
#include "GuiManager.h"

HPPotion::HPPotion(Consumable_Type id) : Consumable(id)
{
	consumableId = id;
	itemType = POTION_HP_;
	texItems = app->tex->Load("Assets/Sprites/UI/gameitems.png");
}

bool HPPotion::Start()
{
	return true;
}

bool HPPotion::PreUpdate()
{
	return true;
}

bool HPPotion::Update(float dt)
{
	return true;
}

bool HPPotion::CleanUp()
{
	return true;
}

bool HPPotion::PostUpdate()
{
	return true;
}

void HPPotion::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}

void HPPotion::CreateButton()
{
	iPoint pos = app->guiManager->pn_inventory->InitializeItemPos();
	button = (GuiButton*)app->guiManager->pn_inventory->CreateGuiButton(app->guiManager->pn_inventory->GetNumberOfButtons(), app->guiManager, app->guiManager->pn_inventory, { pos.x, pos.y, 44, 44 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
	button->texture = texItems;
	button->normalRec = { 75, -2, 44, 44 };
	button->focusedRec = { 75, -2, 44, 44 };
	button->pressedRec = { 75, -2, 44, 44 };
}

void HPPotion::Consume(Player* user)
{
	user->stats.hp += 50;
	//HAS TO DELETE ITSELF
}
