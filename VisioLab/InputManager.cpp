#include "InputManager.h"

namespace VisioLab {
	bool InputManager::isSpriteClicked(sf::Sprite &Object, sf::Mouse::Button button, sf::RenderWindow& window) {
		if (sf::Mouse::isButtonPressed(button)) {
			sf::IntRect tempRect(Object.getPosition().x, Object.getPosition().y,
				Object.getGlobalBounds().width, Object.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(window)))
				return true;
		}
		return false;
	}
	bool InputManager::isMouseOnIt(sf::Sprite &Object, sf::Event &ev, sf::RenderWindow& window) {
		if (ev.type == sf::Event::MouseMoved) {
			sf::IntRect tempRect(Object.getPosition().x, Object.getPosition().y,
				Object.getGlobalBounds().width, Object.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(window)))
				return true;
		}
		return false;
	}
	bool InputManager::isMousePressedOnIt(sf::Sprite &Object, sf::Event& ev, sf::RenderWindow& window) {
		if (ev.type == sf::Event::MouseButtonPressed) {
			sf::IntRect tempRect(Object.getPosition().x, Object.getPosition().y,
				Object.getGlobalBounds().width, Object.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(window)))
				return true;
		}
		return false;
	}
	bool InputManager::isMouseReleasedFromIt(sf::Sprite &Object, sf::Event& ev, sf::RenderWindow& window) {
		if (ev.type == sf::Event::MouseButtonReleased) {
			sf::IntRect tempRect(Object.getPosition().x, Object.getPosition().y,
				Object.getGlobalBounds().width, Object.getGlobalBounds().height);
			if (tempRect.contains(sf::Mouse::getPosition(window)))
				return true;
		}
		return false;
	}
	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window) {
		return sf::Mouse::getPosition(window);
	}
}