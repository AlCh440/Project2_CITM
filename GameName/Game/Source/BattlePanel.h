#pragma once
#include "GuiPanel.h"

class Entity;

class BattlePanel :  public GuiPanel
{
public:
	BattlePanel(bool active);
	~BattlePanel();

	bool Start() override;
	bool Update(float dt, bool doLogic) override;
	bool Draw() override;
	bool CleanUp();
	bool OnGuiMouseClickEvent(GuiControl* control) override;

	void Enable() override;
	void LoadEntityUi();

	void UpdateStats(Entity* ent);
	void RenderStats();

	GuiButton* bt_attack;
	GuiButton* bt_move;
	GuiButton* bt_endTurn;

	

	GuiButton* bt_test;

	SDL_Rect entityFace;


	SDL_Texture* tex_hptext;
	SDL_Texture* tex_dmgtext;
	SDL_Texture* tex_mvmtext;

	SDL_Rect r_hp, r_dmg, r_mvm;
};

