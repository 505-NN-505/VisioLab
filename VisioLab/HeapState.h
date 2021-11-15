#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"
#include "HuffmanTree.h"
#include "TextBox.h"

namespace VisioLab {
	class HeapState : public State {
	private:
		AppDataRef _data;

		sf::Font font;
		Textbox textbox;

		HuffmanTree huff;
		
		sf::Sprite _pauseButton, _getPrefixCodes, _nextButton;
		bool canType, textGiven, isTreeReady, isPrefixCodeGenerated;

	public:
		HeapState(AppDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}