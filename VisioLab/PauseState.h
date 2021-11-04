#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"

namespace VisioLab {
	class PauseState : public State
	{
	public:
		PauseState(AppDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		AppDataRef _data;
		sf::Sprite _resumeButton;
		sf::Sprite _retryButton;
		sf::Sprite _homeButton;
	};
}