#pragma once

#include <SFML/Graphics.hpp>
#include "AlignmentCenter.h"
#include <iostream>

using namespace std;

class Monitor {
	sf::Text text;
	string address;
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Monitor() {}
	Monitor(const string& address, const sf::Font& textFont, int textRes) {
		this->address = address;
		text.setFont(textFont);
		text.setCharacterSize(textRes);
	}
	void setAddress(const string& argAddress) {
		address = argAddress;
	}
	void setText(const string& textString) {
		text.setString(textString);
		sf::Vector2f pos = getPositionText();
		text.setPosition(pos);
	}
	void setFont(sf::Font& textFont) {
		text.setFont(textFont);
	}
	void setCharacterSize(int textRes) {
		text.setCharacterSize(textRes);
	}
	void setTexture(const sf::RectangleShape& plat) {
		texture.loadFromFile(address);
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sf::Vector2f pos = getPositionTexture(plat);
		sprite.setPosition(pos);
	}
	void load(const string& address, sf::Font& textFont, int textRes, const sf::RectangleShape& plat) {
		setAddress(address);
		setCharacterSize(textRes);
		setFont(textFont);
		setTexture(plat);
	}
	sf::Vector2f getPositionTexture(const sf::RectangleShape& rect) {
		return alignCenter(sprite, rect);
	}

	sf::Vector2f getPositionText(void) {
		return alignCenter(text, sprite);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}
};