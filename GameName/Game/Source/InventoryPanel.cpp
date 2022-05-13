#include "InventoryPanel.h"
#include "GuiManager.h"
#include "Entities.h"

InventoryPanel::InventoryPanel(bool active) : GuiPanel(active)
{
	Active = active;
	id = PanelID::P_INVENTORY;
}

InventoryPanel::~InventoryPanel()
{

}

bool InventoryPanel::Start()
{
	texture = app->guiManager->tex_invetory;
	bounds = { 0,0,1280,720 };
	position = { 0,0 };

	texItems = app->tex->Load("Assets/Sprites/UI/gameItems.png");
	
	key = { 0, 0, 0, 0 };
	potionHP = { 0, 0, 0, 0 };
	potionMana = { 0, 0, 0, 0 };
	
	return true;
}

bool InventoryPanel::Update(float dt, bool doLogic)
{
	return true;
}

bool InventoryPanel::Draw()
{
	GuiPanel::Draw();
	DrawItems();

	return true;
}

void InventoryPanel::DrawItems()
{
	int i = 0;
	for (p2ListItem<Item*>* aux = app->entities->openWorld->inventory.getFirst(); aux != NULL; aux = aux->next, i++)
	{
		switch (aux->data->itemType)
		{
		case POTION_HP_:
		{
			app->render->DrawTexture(texItems, 0, 0, &potionHP);
		} break;
		case POTION_MANA_:
		{
			app->render->DrawTexture(texItems, 0, 0, &potionMana);
		} break;
		case KEY_:
		{
			int idKey = aux->data->GetKeyId();
			if (idKey == 1)
			{

			}
			else if (idKey == 2)
			{

			}
			else if (idKey == 3)
			{
				
			}
			else if (idKey == 4)
			{

			}
			app->render->DrawTexture(texItems, 0, 0, &key);
		} break;
		default:
			break;
		}
		
	}
}

bool InventoryPanel::CleanUp()
{
	return true;
}

bool InventoryPanel::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}
