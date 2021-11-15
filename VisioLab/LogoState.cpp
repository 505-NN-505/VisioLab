#pragma once

#include <sstream>
#include <iostream>
#include "LogoState.h"
#include "Definitions.h"
#include "MainMenuState.h"

namespace VisioLab {
	LogoState::LogoState(AppDataRef data) : _data(data) {

	}

	void LogoState::Init() {
		this->_data->assets.LoadTexture("VisioLabLogo", LOGO_STATE_FILEPATH);

		_background.setTexture(this->_data->assets.getTexture("VisioLabLogo"));
	}

	void LogoState::HandleInput() {
		sf::Event event;

		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
		}
	}

	void LogoState::Update(float dt) {
		if (this->_clock.getElapsedTime().asSeconds() > 2) {	// the logo scene stay for 2 seconds
			// Switch To Main Menu
			this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true); // then the new state MainMenuState will be added
		}																				// replacing the LogoState
	}

	void LogoState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->_background);

		this->_data->window.display();
	}
};