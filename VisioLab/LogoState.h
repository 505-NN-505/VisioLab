#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"

namespace VisioLab {
	class LogoState : public State {
	private:
		AppDataRef _data;
		sf::Clock _clock;
		sf::Sprite _background;
	public:
		LogoState(AppDataRef data);
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}