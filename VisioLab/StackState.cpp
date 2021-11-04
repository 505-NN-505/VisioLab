#pragma once

#include <sstream>
#include "StackState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "Definitions.h"

#include <iostream>

namespace VisioLab {
	StackState::StackState(AppDataRef data) : _data(data) {
		this->_data->ID = __stack;
	}

	void StackState::Init() {
		recStack.setSize(sf::Vector2f(665.0, 750.0));
		recBrowse.setSize(sf::Vector2f(665.0, 750.0));

		recStack.setPosition(10, 10);
		recBrowse.setPosition(670 + 10, 10);

		recStack.setFillColor(sf::Color::Black);
		recBrowse.setFillColor(sf::Color::Black);

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_pauseButton.setScale({ 0.3f, 0.3f });
		_pauseButton.setTexture(this->_data->assets.getTexture("Pause Button"));
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width * 0.3, _pauseButton.getPosition().y);

		this->_data->assets.LoadTexture("Backward Button", BACKWARD_BUTTON);
		_backwardButton.setTexture(this->_data->assets.getTexture("Backward Button"));
		_backwardButton.setPosition({ 850.f, 600.f });

		this->_data->assets.LoadTexture("Search Button", SEARCH_BUTTON);
		_searchButton.setTexture(this->_data->assets.getTexture("Search Button"));
		_searchButton.setPosition({ 1000.f, 600.f });

		this->_data->assets.LoadTexture("Forward Button", FORWARD_BUTTON);
		_forwardButton.setTexture(this->_data->assets.getTexture("Forward Button"));
		_forwardButton.setPosition({ 1150.f, 600.f });

		this->_data->assets.LoadTexture("History", HISTORY_BUTTON);
		_historyButton.setTexture(this->_data->assets.getTexture("History"));
		_historyButton.setPosition({ 950.f, 110.f });
	
		this->_data->assets.LoadFont("Marker Felt", MARKER_FELT);
		font = this->_data->assets.getFont("Marker Felt");

		browser.load({ 100, 600 }, { 400, 600 }, { 180, 80 }, font);
		textbox1.load(30, sf::Color::White, false, font, { 980, 680 });
		monitor.load("Resources/Textures/monitor.png", font, 60, recBrowse);

		canType = 0;
	}

	void StackState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace) {
					textbox1.deleteChar();
				}
				if (event.key.code == sf::Keyboard::Enter) {
					canType = 0;
					browser.searching(textbox1.getText());
					monitor.setText(browser.backwardTop());
					textbox1.clear();
				}
			}

			else if (canType && event.type == sf::Event::TextEntered) {
				if (event.key.code != '\b') textbox1.typeOn(event);
			}

			if (this->_data->input.isSpriteClicked(this->_backwardButton, sf::Mouse::Left, this->_data->window)) {
				browser.Left();
				monitor.setText(browser.backwardTop());
			}
			else if (this->_data->input.isSpriteClicked(this->_forwardButton, sf::Mouse::Left, this->_data->window)) {
				browser.Right();
				monitor.setText(browser.backwardTop());
			}
			else if (this->_data->input.isSpriteClicked(this->_searchButton, sf::Mouse::Left, this->_data->window)) {
				canType = 1;
				textbox1.setSelected(true);
			}
			else if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			else if (this->_data->input.isSpriteClicked(this->_historyButton, sf::Mouse::Left, this->_data->window)) {
				browser.writeToDisk();
			}
		}
	}

	void StackState::Update(float dt) {

	}

	void StackState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(recStack);
		this->_data->window.draw(recBrowse);

		this->_data->window.draw(_backwardButton);
		this->_data->window.draw(_searchButton);
		this->_data->window.draw(_forwardButton);
		this->_data->window.draw(_historyButton);

		textbox1.drawTo(this->_data->window);
		monitor.drawTo(this->_data->window);
		browser.visualize(this->_data->window);

		this->_data->window.draw(this->_pauseButton);

		this->_data->window.display();
	}
}