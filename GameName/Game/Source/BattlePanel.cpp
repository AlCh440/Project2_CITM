#include "BattlePanel.h"
#include "GuiManager.h"
#include "Entity.h"
#include "BattleTestScene.h"
#include "App.h"
#include "Window.h"
#include <string> 



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


	texBattleElements = app->tex->Load("Assets/Sprites/UI/battleUi.png");

	bt_attack = (GuiButton*)CreateGuiButton(0, app->guiManager, this, { this->position.x +301,this->position.y + 664,40,40 });
	bt_attack->texture = texBattleElements;
	bt_attack->normalRec = { 0,73,40,40 };
	bt_attack->focusedRec = { 80,73,40,40 };
	bt_attack->pressedRec = { 40,73,40,40 };
	bt_attack->disabledRec = { 40,73,40,40 };

	bt_move = (GuiButton*)CreateGuiButton(1, app->guiManager, this, { this->position.x +364 ,this->position.y + 664,40,40 });
	bt_move->texture = texBattleElements;
	bt_move->normalRec = { 0,73,40,40 };
	bt_move->focusedRec = { 80,73,40,40 };
	bt_move->pressedRec = { 40,73,40,40 };
	bt_move->disabledRec = { 40,73,40,40 };

	bt_endTurn = (GuiButton*)CreateGuiButton(2, app->guiManager, this, { this->position.x +428,this->position.y + 664,104,40 }, "End Turn", app->fonts->battleMenu, app->fonts->c_Menus);
	bt_endTurn->texture = texBattleElements;
	bt_endTurn->normalRec = { 120,73,104,40 };
	bt_endTurn->focusedRec = { 120,113,104,40 };
	bt_endTurn->pressedRec = { 280,73,104,40 };
	bt_endTurn->disabledRec = { 224,73,104,40 };


	return true;
}

bool BattlePanel::Update(float dt, bool doLogic)
{
	if (app->battleTest->currentEntity != nullptr)
	{
		if (app->battleTest->currentEntity->data->HasAttackAction == false)
			bt_attack->state = GuiControlState::DISABLED;



		if (app->battleTest->currentEntity->data->HasMoveAction == false)
			bt_move->state = GuiControlState::DISABLED;

	}

	GuiPanel::Update(dt,doLogic);
	return true;
}

bool BattlePanel::Draw()
{
	GuiPanel::Draw();

	if (app->battleTest->currentEntity != nullptr)
	{
		switch (app->battleTest->currentEntity->data->type)
		{
		case PLAYERKNIGHT:
			
			break;
		case PLAYERRANGER:
			
			break;
		case DUMMY:
			
			break;
		default:
			break;
		}
		app->render->DrawTexture(texBattleElements, 114 / app->win->GetScale(), 619 / app->win->GetScale(), &entityFace, 0, 0, 0, 0, 0.5f);
		
		RenderStats();
	}

	SDL_Rect r;
	r = { 0,113,40,40 };
	app->render->DrawTexture(texBattleElements, 301 / app->win->GetScale(), 664 / app->win->GetScale(), &r, 0, 0, 0, 0, 0.5f);
	r = { 40,113,40,40 };
	app->render->DrawTexture(texBattleElements, 364 / app->win->GetScale(), 664 / app->win->GetScale(), &r, 0, 0, 0, 0, 0.5f);


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
		if (app->battleTest->currentEntity->data->battleState == IDLE && app->battleTest->currentEntity->data->HasAttackAction)
			app->battleTest->currentEntity->data->ChangeBattleSate(ATTACK);

	}
	else if (bt_move->id == control->id) {

		if (app->battleTest->currentEntity->data->battleState == IDLE && app->battleTest->currentEntity->data->HasMoveAction)
			app->battleTest->currentEntity->data->ChangeBattleSate(MOVE);
	}
	else if (bt_endTurn->id == control->id){
		
		if (app->battleTest->currentEntity->data->battleState == IDLE)
		{
			app->battleTest->NextEntity();
			LoadEntityUi();
		}
	}
	return true;
}

void BattlePanel::Enable()
{
	Active = true;
	LoadEntityUi();
}

void BattlePanel::LoadEntityUi()
{
	if (app->battleTest->currentEntity != nullptr)
	{

		bt_attack->state = GuiControlState::NORMAL;
		bt_move->state = GuiControlState::NORMAL;
		bt_endTurn->state = GuiControlState::NORMAL;

		UpdateStats(app->battleTest->currentEntity->data);


		switch (app->battleTest->currentEntity->data->type)
		{
		case PLAYERKNIGHT:
		{

			entityFace = { 0,0,48,48 };

		}
			break;
		case PLAYERRANGER:
		{

			entityFace = {48,0,48,48 };
		}
			break;
		case DUMMY:
			entityFace = { 144,0,48,48 };
			bt_attack->state = GuiControlState::DISABLED;
			bt_move->state = GuiControlState::DISABLED;
			bt_endTurn->state = GuiControlState::DISABLED;

			break;
		case SNAKE:
			entityFace = { 6 * 48 ,0,48,48 };
			bt_attack->state = GuiControlState::DISABLED;
			bt_move->state = GuiControlState::DISABLED;
			bt_endTurn->state = GuiControlState::DISABLED;

			break;
		case ARCHMAGE:
			entityFace = { 7 * 48 ,0,48,48 };
			bt_attack->state = GuiControlState::DISABLED;
			bt_move->state = GuiControlState::DISABLED;
			bt_endTurn->state = GuiControlState::DISABLED;

			break;
		default:
			break;
		}

	}
}

void BattlePanel::UpdateStats(Entity* ent)
{
	
	tex_hptext = app->fonts->LoadRenderedText(r_hp, app->fonts->battleMenu, std::to_string(ent->stats.hp).c_str(), app->fonts->c_Menus);
	tex_dmgtext = app->fonts->LoadRenderedText(r_dmg, app->fonts->battleMenu, std::to_string(ent->stats.baseDamage).c_str(), app->fonts->c_Menus);
	tex_mvmtext = app->fonts->LoadRenderedText(r_mvm, app->fonts->battleMenu, std::to_string(ent->stats.movement).c_str(), app->fonts->c_Menus);

}

void BattlePanel::RenderStats()
{
	SDL_Rect r;

	//hp
	r = {0,48,25,25};
	app->render->DrawTexture(texBattleElements, 179 / app->win->GetScale(), 619 / app->win->GetScale(), &r, 0, 0, 0, 0, 0.5f);
	app->render->DrawTexture(tex_hptext, 210 / app->win->GetScale(), 619 / app->win->GetScale(), &r_hp, 0, 0, 0, 0, 0.5f);

	//dmg
	r = { 50,48,25,25 };
	app->render->DrawTexture(texBattleElements, 179 / app->win->GetScale(), 649 / app->win->GetScale(), &r, 0, 0, 0, 0, 0.5f);
	app->render->DrawTexture(tex_dmgtext, 210 / app->win->GetScale(), 649 / app->win->GetScale(), &r_dmg, 0, 0, 0, 0, 0.5f);
	
	//movement
	r = { 25,48,25,25 };
	app->render->DrawTexture(texBattleElements, 179 / app->win->GetScale(), 679 / app->win->GetScale(), &r, 0, 0, 0, 0, 0.5f);
	app->render->DrawTexture(tex_mvmtext, 210 / app->win->GetScale(), 679 / app->win->GetScale(), &r_mvm, 0, 0, 0, 0, 0.5f);
}

