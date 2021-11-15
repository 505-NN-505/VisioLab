#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"
#include "Browser.h"
#include "TextBox.h"
#include "Monitor.h"

namespace VisioLab {
	class StackState : public State {
	private:
		AppDataRef _data;
		sf::RectangleShape recStack, recBrowse;
		sf::Font font;
		sf::Sprite _backwardButton, _searchButton, _forwardButton, _pauseButton, _historyButton;
		Browser browser;
		Textbox textbox1;
		Monitor monitor;
		sf::Sprite warning;
		bool canType, isWarned;

	public:
		StackState(AppDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}