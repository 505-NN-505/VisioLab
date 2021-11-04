#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace std;

class Textbox {
private:
	sf::Text textbox;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

	void inputLogic(int charTyped) {
		text << static_cast<char>(charTyped);
		textbox.setString(text.str() + "_");
	}

	void deleteLastChar() {
		string t = text.str(), newT = "";
		for (int i = 0; i < text.str().size() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}

public:
	Textbox() { }
	Textbox(int size, sf::Color color, bool set) {
		textbox.setCharacterSize(size);
		setSelected(set);
	}

	void setCharacterSize(int size) {
		textbox.setCharacterSize(size);
	}

	void setFont(sf::Font& font) {
		textbox.setFont(font);
	}

	void setPosition(sf::Vector2f pos) {
		textbox.setPosition(pos);
	}

	void setLimit(bool ToF) {
		hasLimit = ToF;
	}

	void setLimit(bool ToF, int lim) {
		hasLimit = ToF;
		limit = lim;
	}

	void setSelected(bool set) {
		isSelected = set;
		if (isSelected) {
			textbox.setString("_");
		}
		else {
			textbox.setString("");
		}
	}

	void load(int size, sf::Color color, bool set, sf::Font& font, sf::Vector2f pos) {
		setCharacterSize(size);
		setSelected(set);
		setFont(font);
		setPosition(pos);
	}

	string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(textbox);
	}

	void typeOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().size() <= limit) {
						inputLogic(charTyped);
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

	void deleteChar(void) {
		if (hasLimit) {
			if (text.str().size() > limit) {
				deleteLastChar();
			}
		}
		else {
			if (text.str().size() > 0) {
				deleteLastChar();
			}
		}
	}

	void clear() {
		text.str("");
		textbox.setString(text.str());
	}
};