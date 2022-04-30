#include "Dialog.h"
#include "App.h"
#include "Render.h"
#include "DialogFonts.h"
#include "Input.h"
#include "Window.h"

void Dialog::SplitText(std::string text)
{
	std::string line;
	std::string word;

	size_t textLen = text.length();

	for (size_t i = 0; i < textLen; i++) {
		if (text[i] == ' ') {
			if (((line.length() + word.length() + 4) * app->win->GetScale() > max_chars_line)) {
				texts.push_back(line);
				line = word;
				line += " ";

				word = "";
			}
			else {
				line += word;
				line += " ";

				word = "";
			}
		}
		else {
			word += text[i];
		}
	}

	if (word.length() > 0) {
		if (line.length() + word.length() > max_chars_line) {
			texts.push_back(line);
			line = word;
		}
		else {
			line += word;
		}

		texts.push_back(line);
	}
}

Dialog::Dialog() : finished(false), activeNode(NULL)
{
	posX = 0;
	posY = 0;
}

Dialog::~Dialog()
{
}

size_t Dialog::AddNode(DialogNode& node)
{
	size_t id = nodes.size();

	nodes.push_back(node);

	node.nodes.clear();
	node.options.clear();

	return id;
}

void Dialog::SetActiveNode(size_t id)
{
	if (id >= 0 && id < nodes.size()) {
		activeNode = &nodes[id];

		size_t opts = activeNode->options.size();
		SDL_Rect bounds = {
			posX,
			posY + dialogHeight,
			0,
			dialogHeight / 10
		};

		DialogFont& fontobj = app->dialogFonts->GetFont(dialogFont);

		buttons.clear();
		for (size_t i = 0; i < opts; i++) {
			bounds.w = fontobj.char_w * (activeNode->options[i].length() + 4);
			LOG("%i", fontobj.char_w);
			buttons.emplace_back(bounds, dialogImg, activeNode->options[i].c_str(), dialogFont);
			bounds.x += bounds.w * app->win->GetScale();
		}

		texts.clear();
		SplitText(activeNode->text);

		int lines = texts.size();

		/*textXOffset = dialogWidth / 2 - (max_chars_line * char_width) / 2;
		textYOffset = dialogHeight / 2 - (lines * char_height) / 2;*/

		/*if (lines > 1) {
			textYOffset -= ((lines - 1) * char_height / 2);
		}*/
	}
}

void Dialog::Update()
{
	if (activeNode) {

		app->render->DrawTextureScaled(
			dialogImg, posX / app->win->GetScale(),
			posY / app->win->GetScale(),
			dialogWidth / app->win->GetScale(),
			dialogHeight / app->win->GetScale(),
			NULL, 0);

		size_t lines = texts.size();

		for (size_t i = 0; i < lines; i++) {
			app->dialogFonts->BlitText(
				(posX + textXOffset) / app->win->GetScale(),
				(posY + textYOffset + char_height * i * 2) / app->win->GetScale(),
				dialogFont, texts[i].c_str()
			);
		}

		size_t optionSize = activeNode->options.size();

		for (size_t i = 0; i < optionSize; i++) {
			buttons[i].Update();
			buttons[i].Draw();
		}

		if (optionSize > 0) {
			for (size_t i = 0; i < optionSize; i++) {
				if (buttons[i].clicked) {
					SetActiveNode(activeNode->nodes[i]);
					break;
				}
			}
		}
		else {
			if (activeNode->nodes.size() > 0) {
				continueButton.Update();
				continueButton.Draw();

				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || continueButton.clicked) {
					continueButton.clicked = false;
					SetActiveNode(activeNode->nodes[0]);
				}
			}
			else {
				finishButton.Update();
				finishButton.Draw();

				if (finishButton.clicked) {
					finished = true;
				}
			}
		}
	}
	else {
		finished = true;
	}
}

void Dialog::SetPosition(int x, int y)
{
	posX = x;
	posY = y;

	continueButton.SetPosition(x, dialogHeight + y);
	finishButton.SetPosition(x, dialogHeight + y);
}

void Dialog::SetFont(int font)
{
	dialogFont = font;

	DialogFont& fontobj = app->dialogFonts->GetFont(dialogFont);

	SDL_Rect bounds = {
			posX,
			posY + dialogHeight,
			fontobj.char_w * (sizeof("continue") + 4),
			dialogHeight / 10
	};

	continueButton = Button(bounds, dialogImg, "continue", dialogFont);

	bounds.w = fontobj.char_w * (sizeof("finish") + 4);
	finishButton = Button(bounds, dialogImg, "finish", dialogFont);

	char_width = fontobj.char_w;
	char_height = fontobj.char_h;

	max_chars_line = dialogWidth / char_width - 2;
}

void Dialog::SetDialogBg(SDL_Texture* dialog_bg, int width, int height, int offsetLeft, int offsetUp)
{
	dialogImg = dialog_bg;
	dialogWidth = width;
	dialogHeight = height;
	textXOffset = offsetLeft;
	textYOffset = offsetUp;
	
	SetFont(dialogFont);
}