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
	
	key01 = { 0, 150, 44, 44 };
	key02 = { 110, 151, 44, 44 };
	key03 = { 227, 151, 44, 44 };
	key04 = { 331, 154, 44, 44 };
	potionHP = { 75, -2, 44, 44 };
	potionMana = { 255, -2, 44, 44 };
	
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
	int j = 0;
	iPoint drawPos(position.x + (222), position.y + (170));
	for (p2ListItem<Item*>* aux = app->entities->openWorld->inventory.getFirst(); aux != NULL; aux = aux->next, i++)
	{
		switch (aux->data->itemType)
		{
		case POTION_HP_:
		{
			app->render->DrawTexture(texItems, drawPos.x / app->win->GetScale(), drawPos.y / app->win->GetScale(), &potionHP, 0, 0, 0, 0, 0.5f);
		} break;
		case POTION_MANA_:
		{
			app->render->DrawTexture(texItems, drawPos.x / app->win->GetScale(), drawPos.y / app->win->GetScale(), &potionMana, 0, 0, 0, 0, 0.5f);
		} break;
		case KEY_:
		{
			int idKey = aux->data->GetKeyId();
			if (idKey == 1)
			{
				app->render->DrawTexture(texItems, drawPos.x / app->win->GetScale(), drawPos.y / app->win->GetScale(), &key01, 0, 0, 0, 0, 0.5f);
			}
			else if (idKey == 2)
			{
				app->render->DrawTexture(texItems, drawPos.x / app->win->GetScale(), drawPos.y / app->win->GetScale(), &key02, 0, 0, 0, 0, 0.5f);
			}
			else if (idKey == 3)
			{
				app->render->DrawTexture(texItems, drawPos.x / app->win->GetScale(), drawPos.y / app->win->GetScale(), &key03, 0, 0, 0, 0, 0.5f);
			}
			else if (idKey == 4)
			{
				app->render->DrawTexture(texItems, drawPos.x / app->win->GetScale(), drawPos.y / app->win->GetScale(), &key04, 0, 0, 0, 0, 0.5f);
			}
			
			
			
		} break;
		default:
			break;
		}
		drawPos.x += 65;
		if (i == 4)
		{
			i = 0;
			j++;
			drawPos.x = position.x + (222);
			drawPos.y = position.y + (170) + (65 * j);
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
