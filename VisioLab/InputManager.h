#pragma once

#include <SFML\Graphics.hpp>

namespace VisioLab {
	class InputManager {
	public:
		InputManager() {}
		~InputManager() {}
		bool isSpriteClicked(sf::Sprite &Object, sf::Mouse::Button button, sf::RenderWindow& window);
		bool isMouseOnIt(sf::Sprite &Object, sf::Event& ev, sf::RenderWindow& window);
		bool isMousePressedOnIt(sf::Sprite &Object, sf::Event& ev, sf::RenderWindow& window);
		bool isMouseReleasedFromIt(sf::Sprite &Object, sf::Event& ev, sf::RenderWindow& window);
		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}

