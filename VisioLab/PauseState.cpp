#pragma once

#include <sstream>
#include "PauseState.h"
#include "Definitions.h"
#include "StackState.h"
#include "HeapState.h"
#include "QueueState.h"
#include "HashState.h"
#include "BSTState.h"
#include "MainMenuState.h"

#include <iostream>

namespace VisioLab {
	PauseState::PauseState(AppDataRef data) : _data(data) {

	}

	void PauseState::Init() {
		this->_data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
		this->_data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
		this->_data->assets.LoadTexture("Home Button", HOME_BUTTON);

		this->_resumeButton.setTexture(this->_data->assets.getTexture("Resume Button"));
		this->_retryButton.setTexture(this->_data->assets.getTexture("Retry Button"));
		this->_homeButton.setTexture(this->_data->assets.getTexture("Home Button"));

		this->_resumeButton.setScale({ 0.6f, 0.6f });
		this->_retryButton.setScale({ 0.7f, 0.7f });
		this->_homeButton.setScale({ 0.7f, 0.7f });

		this->_resumeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_resumeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3) - (this->_resumeButton.getLocalBounds().height / 2));
		this->_retryButton.setPosition((this->_data->window.getSize().x / 2) - (this->_retryButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3 * 1.5) - (this->_retryButton.getLocalBounds().height / 2));
		this->_homeButton.setPosition((this->_data->window.getSize().x / 2) - (this->_homeButton.getLocalBounds().width / 2), (this->_data->window.getSize().y / 3 * 2) - (this->_homeButton.getLocalBounds().height / 2));
	}

	void PauseState::HandleInput() {
		sf::Event event;

		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (this->_data->input.isSpriteClicked(this->_resumeButton, sf::Mouse::Left, this->_data->window)) {
				// Resume App By Popping Of The Current State (Pause State)
				this->_data->machine.RemoveState();
			}

			if (this->_data->input.isSpriteClicked(this->_retryButton, sf::Mouse::Left, this->_data->window)) {
				if(this->_data->ID == __stack)
					this->_data->machine.AddState(StateRef(new StackState(_data)), true);
				else if(this->_data->ID == __heap)
					this->_data->machine.AddState(StateRef(new HeapState(_data)), true);
				else if (this->_data->ID == __queue)
					this->_data->machine.AddState(StateRef(new QueueState(_data)), true);
				else if (this->_data->ID == __hashTable)
					this->_data->machine.AddState(StateRef(new HashState(_data)), true);
				else if (this->_data->ID == __bst)
					this->_data->machine.AddState(StateRef(new BSTState(_data)), true);
			}

			if (this->_data->input.isSpriteClicked(this->_homeButton, sf::Mouse::Left, this->_data->window)) {
				// Remove The Pause State Off The Stack
				this->_data->machine.RemoveState();

				// Switch To Main Menu State By Replacing the current State
				this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
			}
		}
	}

	void PauseState::Update(float dt) {

	}

	void PauseState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->_resumeButton);
		this->_data->window.draw(this->_retryButton);
		this->_data->window.draw(this->_homeButton);

		this->_data->window.display();
	}
}