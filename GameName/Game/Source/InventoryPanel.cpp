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
		switch (aux->data->type)
		{
		case POTION_HP:
		{

		} break;
		case POTION_MANA:
		{

		} break;
		case KEY:
		{

		} break;
		default:
			break;
		}
		app->render->DrawTexture(texItems, 0, 0);
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
