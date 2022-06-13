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
	texture = app->guiManager->tex_inventory;
	bounds = { 0,0,1280,720 };
	position = { 0,0 };

	texItems = app->tex->Load("Assets/Sprites/UI/gameItems.png");
	texTabs = app->tex->Load("Assets/Sprites/UI/inventoryTabs.png");

	key01 = { 0, 150, 44, 44 };
	key02 = { 110, 151, 44, 44 };
	key03 = { 227, 151, 44, 44 };
	key04 = { 331, 154, 44, 44 };
	potionHP = { 75, -2, 44, 44 };
	potionMana = { 255, -2, 44, 44 };
	
	spriteKnight = {12, 135, 50, 57 };
	spriteRanger = { 73, 135, 50, 57 };
	spriteTab = { 5, 5, 98, 110 };
	statsShowing = KNIGHT;



		bt_to_knight = (GuiButton*)CreateGuiButton(10, app->guiManager, this, { (this->position.x + 375)*2,(this->position.y + 46)*2, 50, 57 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
		bt_to_knight->texture = app->guiManager->tex_inventory_tabs;
		bt_to_knight->normalRec = { 12, 135, 50, 57 };
		bt_to_knight->focusedRec = { 12, 135, 50, 57 };
		bt_to_knight->pressedRec = { 12, 135, 50, 57 };

	bt_to_ranger = (GuiButton*)CreateGuiButton(11, app->guiManager, this, { (this->position.x + 433)*2,(this->position.y + 45)*2, 50, 57 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_to_ranger->texture = app->guiManager->tex_inventory_tabs;
	bt_to_ranger->normalRec = { 73, 135, 50, 57 };
	bt_to_ranger->focusedRec = { 73, 135, 50, 57 };
	bt_to_ranger->pressedRec = { 73, 135, 50, 57 };

	
	return true;

}

bool InventoryPanel::Update(float dt, bool doLogic)
{
	GuiPanel::Update(dt, doLogic);

	if (app->entities->openWorld->inventory.getFirst() != NULL)
	{
		for (p2ListItem<Item*>* aux = app->entities->openWorld->inventory.getFirst(); aux != NULL; aux = aux->next)
		{
			if (aux->data->button != NULL)
			aux->data->button->Update(dt);
		}
	}
	return true;
}

bool InventoryPanel::Draw()
{
	GuiPanel::Draw();

	return true;
}

void InventoryPanel::DrawItems()
{
	
	for (p2ListItem<Item*>* aux = app->entities->openWorld->inventory.getFirst(); aux->data->button != NULL, aux != NULL; aux = aux->next)
	{
  		//aux->data->button->Draw(app->render);
	}

	// Drawing tab
	if (statsShowing == KNIGHT)
	{
		app->render->DrawTexture(texTabs, (362 + position.x), (36 + position.y), &spriteTab, 0, 0, 0, 0, 0.5f);
	}
	else if (statsShowing == RANGER)
	{
		app->render->DrawTexture(texTabs, 422 + position.x, 36 + position.y, &spriteTab, 0, 0, 0, 0, 0.5f);
	}
	// Drawing character sprites
	
	
}

bool InventoryPanel::CleanUp()
{
	return true;
}

bool InventoryPanel::OnGuiMouseClickEvent(GuiControl* control)
{
	if (control->id == bt_to_knight->id)
	{
		statsShowing = KNIGHT;
	}
	else if (control->id == bt_to_ranger->id)
	{
		statsShowing = RANGER;
	}
	else
	{
		for (p2ListItem<Item*>* aux = app->entities->openWorld->inventory.getFirst(); aux != NULL; aux = aux->next)
		{
			if (aux->data->button != NULL)
			{
				if (control->id == aux->data->button->id)
				{
					if (statsShowing == KNIGHT)
					{
						aux->data->UseItem(app->entities->knightPointer);
					}
					else if (statsShowing == RANGER)
					{
						aux->data->UseItem(app->entities->rangerPointer);
					}
				}
			}
		}
		for (p2ListItem<Item*>* aux = app->entities->openWorld->inventory.getFirst(); aux->data->button != NULL, aux != NULL; aux = aux->next)
		{
			if (aux->data->pendingToDelete == true)
			{
				for (p2ListItem<GuiControl*>* btnDel = controls.getFirst(); btnDel != NULL; btnDel = btnDel->next)
				{
 					if (btnDel->data == (GuiControl*)aux->data->button)
					{
						aux->data->button->updateControl = false;
						//controls.del(btnDel);
						//break;
					}
					
				}
				
				app->entities->openWorld->RemoveFromInventory(aux->data);
				break;
			}
		}
	}

	return true;
}

iPoint InventoryPanel::InitializeItemPos()
{
	iPoint ret(position.x + 444, position.y + 340);

	if (rowCounter == 5)
	{
		rowCounter = 0;
		columnCounter++;
		ret.x = position.x + (444);
		ret.y = position.y + (340) + (131 * columnCounter);
	}

	ret.x += 131 * rowCounter;
	ret.x /= app->win->GetScale();
	ret.y /= app->win->GetScale();

	rowCounter++;
	return ret;
}

void InventoryPanel::SetItemPosition()
{
	int i = 0;
	int j = 0;
	iPoint drawPos(position.x + (222), position.y + (170));
	for (p2ListItem<Item*>* aux = app->entities->openWorld->inventory.getFirst(); aux != NULL; aux = aux->next, i++)
	{
		if (aux->data->button != NULL)
		{
			aux->data->button->SetPosition(drawPos.x / app->win->GetScale(), drawPos.y / app->win->GetScale());


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
}

int InventoryPanel::GetNumberOfButtons()
{
	int ret = numberButtons;
	numberButtons++;
	return ret;
}
