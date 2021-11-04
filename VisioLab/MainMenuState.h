#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"

namespace VisioLab
{
	class MainMenuState : public State
	{
	private:
		AppDataRef _data;

		sf::Sprite _stackButton;
		sf::Sprite _heapButton;
		sf::Sprite _queueButton;
		sf::Sprite _hashButton;
		sf::Sprite _bstButton;
		sf::Sprite _exitButton;

	public:
		MainMenuState(AppDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}