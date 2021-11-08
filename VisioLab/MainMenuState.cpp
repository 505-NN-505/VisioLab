#pragma once

#include <sstream>
#include "MainMenuState.h"
#include "StackState.h"
#include "HeapState.h"
#include "QueueState.h"
#include "HashState.h"
#include "BSTState.h"
#include "Definitions.h"

#include <iostream>

namespace VisioLab {
	MainMenuState::MainMenuState(AppDataRef data) : _data(data) {

	}

	void MainMenuState::Init() {
		this->_data->assets.LoadTexture("Stack Button", MAIN_MENU_STACK_BUTTON);
		this->_data->assets.LoadTexture("Heap Button", MAIN_MENU_HEAP_BUTTON);
		this->_data->assets.LoadTexture("Queue Button", MAIN_MENU_QUEUE_BUTTON);
		this->_data->assets.LoadTexture("Hash Button", MAIN_MENU_HASHTABLE_BUTTON);
		this->_data->assets.LoadTexture("BST Button", MAIN_MENU_BST_BUTTON);
		this->_data->assets.LoadTexture("EXIT Button", MAIN_MENU_EXIT_BUTTON);

		this->_stackButton.setTexture(this->_data->assets.getTexture("Stack Button"));
		this->_heapButton.setTexture(this->_data->assets.getTexture("Heap Button"));
		this->_queueButton.setTexture(this->_data->assets.getTexture("Queue Button"));
		this->_hashButton.setTexture(this->_data->assets.getTexture("Hash Button"));
		this->_bstButton.setTexture(this->_data->assets.getTexture("BST Button"));
		this->_exitButton.setTexture(this->_data->assets.getTexture("EXIT Button"));
		
		this->_stackButton.setScale({ 0.35f, 0.35f });
		this->_stackButton.setPosition((SCREEN_WIDTH / 2) - (this->_stackButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - 200 - (this->_stackButton.getGlobalBounds().height / 2));
		this->_heapButton.setPosition((SCREEN_WIDTH / 2) - (this->_heapButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - 100 - (this->_heapButton.getGlobalBounds().height / 2));
		this->_queueButton.setScale({ 0.5f, 0.5f });
		this->_queueButton.setPosition((SCREEN_WIDTH / 2) - (this->_queueButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (this->_queueButton.getGlobalBounds().height / 2));
		this->_hashButton.setScale({ 0.5f, 0.5f });
		this->_hashButton.setPosition((SCREEN_WIDTH / 2) - (this->_hashButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) + 100 - (this->_hashButton.getGlobalBounds().height / 2));
		this->_bstButton.setScale({ 0.5f, 0.5f });
		this->_bstButton.setPosition((SCREEN_WIDTH / 2) - (this->_bstButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) + 200 - (this->_bstButton.getGlobalBounds().height / 2));
		this->_exitButton.setPosition((SCREEN_WIDTH / 2) - (this->_exitButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) + 300 - (this->_exitButton.getGlobalBounds().height / 2));
	
	}

	void MainMenuState::HandleInput() {
		sf::Event event;

		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			if (this->_data->input.isSpriteClicked(this->_stackButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new StackState(_data)), true);
			}
			if (this->_data->input.isSpriteClicked(this->_heapButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new HeapState(_data)), true);
			}
			if (this->_data->input.isSpriteClicked(this->_queueButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new QueueState(_data)), true);
			}
			if (this->_data->input.isSpriteClicked(this->_hashButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new HashState(_data)), true);
			}
			if (this->_data->input.isSpriteClicked(this->_bstButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new BSTState(_data)), true);
			}
			if (this->_data->input.isSpriteClicked(this->_exitButton, sf::Mouse::Left, this->_data->window)) {
				exit(0);
			}
		}
	}

	void MainMenuState::Update(float dt) {

	}

	void MainMenuState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(this->_stackButton);
		this->_data->window.draw(this->_heapButton);
		this->_data->window.draw(this->_queueButton);
		this->_data->window.draw(this->_hashButton);
		this->_data->window.draw(this->_bstButton);
		this->_data->window.draw(this->_exitButton);

		this->_data->window.display();
	}
}