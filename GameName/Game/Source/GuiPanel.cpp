#include "GuiPanel.h"
#include "App.h"
#include "Render.h"
#include "Window.h"


GuiPanel::GuiPanel(bool isActive)
{
	Active = isActive;
}

GuiPanel::~GuiPanel()
{
}

bool GuiPanel::Start()
{
	return true;
}

bool GuiPanel::Update(float dt, bool doLogic)
{
	if (!Active)
		return false;

	if (doLogic) {

		p2ListItem<GuiControl*>* control = controls.start;

		while (control != nullptr)
		{
			if (control->data->updateControl == true)
			{
				control->data->Update(dt);
				
			}
			control = control->next;
		}

	}

	return true;
}

bool GuiPanel::Draw()
{
	if (!Active)
		return false;

	//draw background
	if(texture != nullptr)
		app->render->DrawTexture(texture, position.x / app->win->GetScale(), position.y / app->win->GetScale(), &bounds, 0, 0, 0, 0, 0.5f);
	
	DrawItems();

	//draw items
	p2ListItem<GuiControl*>* control = controls.start;
	
	while (control != nullptr)
	{
		if (control->data->updateControl == true)
		{
			control->data->Draw(app->render);

		}
		control = control->next;
	}
	return true;
}

void GuiPanel::Enable()
{
	Active = true;

	//reset ease timer
	counter = 0;

	p2ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		//TODO fix position when enable
		control->data->bounds.x =  position.x + control->data->bounds.x;
		control->data->bounds.y =  position.y + control->data->bounds.y;
		control->data->CenterText(control->data->bounds);
		control = control->next;
	}
}

void GuiPanel::Disable()
{
	Active = false;
}

bool GuiPanel::CleanUp()
{
	texture = nullptr;

	p2ListItem<GuiControl*>* control = controls.start;

	while (control != nullptr)
	{
		control->data->CleanUp();
		control = control->next;
	}

	return true;

}

GuiControl* GuiPanel::CreateGuiControl(GuiControlType type, int id, SDL_Rect bounds, Module* observer, GuiPanel* parent, const char* text, int fontid, SDL_Rect sliderBounds)
{

	GuiControl* control = nullptr;

	//Call the constructor according to the GuiControlType
	switch (type)
	{
	case GuiControlType::BUTTON:
		control = new GuiButton(id, bounds, text, fontid);
		break;
	case GuiControlType::SLIDER:
		control = new GuiSlider(id, bounds, sliderBounds);
		break;
	case GuiControlType::CHECKBOX:
		control = new GuiToggle(id, bounds);
		break;

		// More Gui Controls can go here

	default:
		break;
	}

	//Set the observer
	control->SetObserver(observer);
	control->SetParent(parent);

	// Created GuiControls are added to the list of controls
	if (control != nullptr) parent->controls.add(control);

	return control;
}

GuiControl* GuiPanel::CreateGuiButton(int id, Module* observer, GuiPanel* parent, SDL_Rect bounds, const char* text, int fontId, SDL_Color textColor)
{
	GuiControl* control = nullptr;

	control = new GuiButton(id, bounds, text, fontId, textColor);
	control->SetObserver(observer);
	control->SetParent(parent);

	if (control != nullptr) parent->controls.add(control);

	return control;
}

GuiControl* GuiPanel::CreateGuiSlider(int id, Module* observer, GuiPanel* parent, SDL_Rect bounds, SDL_Rect sliderBounds)
{
	GuiControl* control = nullptr;

	control = new GuiSlider(id, bounds, sliderBounds);
	control->SetObserver(observer);
	control->SetParent(parent);

	if (control != nullptr) parent->controls.add(control);

	return control;
}

GuiControl* GuiPanel::CreateGuiCheckBox(int id, Module* observer, GuiPanel* parent, SDL_Rect bounds)
{
	GuiControl* control = nullptr;

	control = new GuiToggle(id, bounds);
	control->SetObserver(observer);
	control->SetParent(parent);

	if (control != nullptr) parent->controls.add(control);

	return control;
}


bool GuiPanel::OnGuiMouseClickEvent(GuiControl* control)
{
	return true;
}


