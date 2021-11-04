#pragma once

#include <sstream>
#include "HashState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "Definitions.h"

#include <iostream>

namespace VisioLab {
	HashState::HashState(AppDataRef data) : _data(data) {
		this->_data->ID = __hashTable;
	}

	void HashState::Init() {
		sf::RectangleShape recPlat(sf::Vector2f(1360.0, 760.0));

		recPlat.setPosition(0, 0);

		recPlat.setFillColor(sf::Color(8, 6, 18));

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_pauseButton.setScale({ 0.3f, 0.3f });
		_pauseButton.setTexture(this->_data->assets.getTexture("Pause Button"));
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width * 0.3, _pauseButton.getPosition().y);

		this->_data->assets.LoadTexture("Enqueue Button", ENQUEUE_BUTTON);
		_enqueueButton.setTexture(this->_data->assets.getTexture("Enqueue Button"));
		_enqueueButton.setPosition({ 650.f, 600.f });

		this->_data->assets.LoadFont("Marker Felt", MARKER_FELT);
		font = this->_data->assets.getFont("Marker Felt");

		hashing.load({ 100, 40 }, { 180, 70 }, font, " ");
		textbox1.load(15, sf::Color::White, false, font, { 600, 700 });
		monitor.load("Resources/Textures/monitor.png", font, 50, recPlat);

		canType = 0;
	}

	void HashState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event))
		{
			if (event.type == event.Closed)
			{
				this->_data->window.close();
			}

			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::BackSpace)
				{
					textbox1.deleteChar();
				}
				if (event.key.code == sf::Keyboard::Enter)
				{
					canType = 0;
					string x = hashing.linearProbing(textbox1.getText(), this->_data->window);
					monitor.setText(x);
					textbox1.clear();
					//searchButton.resetBgColor();
				}
			}

			else if (canType && event.type == sf::Event::TextEntered)
			{
				if (event.key.code != '\b') textbox1.typeOn(event);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i clicked = { event.mouseButton.x, event.mouseButton.y };

					if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
						this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
					}


					if (this->_data->input.isSpriteClicked(this->_enqueueButton, sf::Mouse::Left, this->_data->window)) {
						canType = 1;
						//_enqueueButton.setBgColor(sf::Color({ 255, 7, 58 }));
						textbox1.setSelected(true);
					}
				}
			}

			else if (event.type == sf::Event::MouseButtonReleased)
			{
				//_forwardButton.resetBgColor();
			}
			/*
			else if (!canType && event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);


				if (_forwardButton.isMouseClicked(mousePos))
					_forwardButton.setBgColor(sf::Color({ 44, 44, 255 }));
				else
					_forwardButton.resetBgColor();

				if (_enqueueButton.isMouseClicked(mousePos))
					_enqueueButton.setBgColor(sf::Color({ 44, 44, 255 }));
				else
					_enqueueButton.resetBgColor();
			}
			*/
		}
	}

	void HashState::Update(float dt) {

	}

	void HashState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(recPlat);

		this->_data->window.draw(_enqueueButton);
		this->_data->window.draw(_forwardButton);

		textbox1.drawTo(this->_data->window);
		monitor.drawTo(this->_data->window);
		hashing.visualize(this->_data->window);

		this->_data->window.draw(this->_pauseButton);

		this->_data->window.display();
	}
}