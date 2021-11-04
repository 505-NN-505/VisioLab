#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"
#include "HashVisio.h"
#include "TextBox.h"
#include "Monitor.h"

namespace VisioLab {
	class HashState : public State {
	private:
		AppDataRef _data;
		sf::RectangleShape recPlat;
		sf::Font font;
		sf::Sprite _enqueueButton, _forwardButton, _pauseButton;
		HashVisio hashing;
		Textbox textbox1;
		Monitor monitor;
		bool canType;

	public:
		HashState(AppDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}