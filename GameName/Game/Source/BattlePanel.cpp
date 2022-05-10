#include "BattlePanel.h"
#include "GuiManager.h"
#include "Entity.h"
#include "BattleTestScene.h"


BattlePanel::BattlePanel(bool active) : GuiPanel(active)
{
	Active = active;
	id = PanelID::P_BATTLE;
}

BattlePanel::~BattlePanel()
{
}

bool BattlePanel::Start()
{
	texture = app->tex->Load("Assets/Sprites/UI/BattleUIBackground.png");
	bounds = { 0,0,1080,720 };
	position = { 0,0 };

	bt_attack = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x ,this->position.y,56,56 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_attack->texture = app->guiManager->UItexture2;
	bt_attack->normalRec = { 0,557,56,56 };
	bt_attack->focusedRec = { 0,502,56,56 };
	bt_attack->pressedRec = { 0,557,56,56 };


	bt_move = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { this->position.x ,this->position.y + 56,56,56 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_move->texture = app->guiManager->UItexture2;
	bt_move->normalRec = { 0,347,56,56 };
	bt_move->focusedRec = { 0,297,56,56 };
	bt_move->pressedRec = { 0,347,56,56 };

	bt_endTurn = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { this->position.x ,this->position.y+112,56,56 }, "", app->fonts->menuButtonFont, app->fonts->c_Menus);
	bt_endTurn->texture = app->guiManager->UItexture2;
	bt_endTurn->normalRec = { 0,663,56,56 };
	bt_endTurn->focusedRec = { 0,610,56,56 };
	bt_endTurn->pressedRec = { 0,663,56,56 };


	LoadEntityAttacks();
	return true;
}

bool BattlePanel::Update(float dt, bool doLogic)
{
	bounds.x = app->render->camera.x;
	bounds.y = app->render->camera.y;
	GuiPanel::Update(dt,doLogic);
	return true;
}

bool BattlePanel::Draw()
{
	GuiPanel::Draw();
	return true;
}

bool BattlePanel::CleanUp()
{
	return true;
}

bool BattlePanel::OnGuiMouseClickEvent(GuiControl* control)
{
	if (bt_attack->id == control->id)
	{
		if(app->battleTest->currentEntity->data->HasAttackAction)
			app->battleTest->currentEntity->data->ChangeBattleSate(ATTACK);
	}
	else if (bt_move->id == control->id) {
		if (app->battleTest->currentEntity->data->HasMoveAction)
			app->battleTest->currentEntity->data->ChangeBattleSate(MOVE);
	}
	else if (bt_endTurn->id == control->id){
		app->battleTest->NextEntity();
	}
	return true;
}

void BattlePanel::LoadEntityAttacks()
{
	//if (app->battleTest->currentEntity != nullptr)
	//{
	//	p2ListItem<Attack*>* a = app->battleTest->currentEntity->data->attackList->start;
	//	int i = 0;

	//	while (a != nullptr)
	//	{
	//		bt_test = (GuiButton*)CreateGuiButton(a->data->id, app->guiManager, this, { this->position.x + 538 + (i * 63),this->position.y + 664,40,40 });
	//		bt_test->texture = app->guiManager->UItexture2;
	//		bt_test->normalRec = { 113,302,40,40 };

	//		i++;
	//		a = a->next;
	//	}
	//}
}

