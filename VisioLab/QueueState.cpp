#pragma once

#include <sstream>
#include "QueueState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "Definitions.h"

#include <iostream>

namespace VisioLab {
	QueueState::QueueState(AppDataRef data) : _data(data) {
		this->_data->ID = __queue;
	}

	void QueueState::Init() {
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

		this->_data->assets.LoadTexture("Forward Button", FORWARD_BUTTON);
		_forwardButton.setTexture(this->_data->assets.getTexture("Forward Button"));
		_forwardButton.setPosition({ 800.f, 600.f });

		this->_data->assets.LoadFont("ARLRDBD", ARLRDBD);
		font = this->_data->assets.getFont("ARLRDBD");

		queueScheduling.load({ 100, 100 }, { 1000, 600 }, { 180, 80 }, font);
		textbox1.load(30, sf::Color::White, false, font, { 600, 700 });
		monitor.load("Resources/Textures/cds.png", font, 50, recPlat);

		canType = 0;
	}

	void QueueState::HandleInput() {
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
					queueScheduling.enqueue(textbox1.getText());
					textbox1.clear();
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

					if (this->_data->input.isSpriteClicked(this->_forwardButton, sf::Mouse::Left, this->_data->window)) {
						bool done = queueScheduling.dequeue();
						if(done) monitor.setText(queueScheduling.forwardTop());
					}
					if (this->_data->input.isSpriteClicked(this->_enqueueButton, sf::Mouse::Left, this->_data->window)) {
						canType = 1;
						textbox1.setSelected(true);
					}
				}
			}

			if (!canType && this->_data->input.isMouseOnIt(this->_forwardButton, event, this->_data->window)) {
				_forwardButton.setColor(sf::Color::Blue);
			}
			else {
				_forwardButton.setColor(sf::Color::White);
			}
			if (this->_data->input.isMouseOnIt(this->_enqueueButton, event, this->_data->window)) {
				_enqueueButton.setColor(sf::Color::Blue);
				if (canType) _enqueueButton.setColor(sf::Color::Red);
			}
			else {
				if (canType) _enqueueButton.setColor(sf::Color::Red);
				else _enqueueButton.setColor(sf::Color::White);
			}

			if (!canType && this->_data->input.isMousePressedOnIt(this->_forwardButton, event, this->_data->window)) {
				_forwardButton.setColor(sf::Color::Green);
			}
			else if (!canType && this->_data->input.isMouseReleasedFromIt(this->_forwardButton, event, this->_data->window)) {
				_forwardButton.setColor(sf::Color::Blue);
			}
			if (!canType && this->_data->input.isMousePressedOnIt(this->_enqueueButton, event, this->_data->window)) {
				_enqueueButton.setColor(sf::Color::Green);
			}
			else if (!canType && this->_data->input.isMouseReleasedFromIt(this->_enqueueButton, event, this->_data->window)) {
				_enqueueButton.setColor(sf::Color::Blue);
			}
		}
	}

	void QueueState::Update(float dt) {

	}

	void QueueState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw(recPlat);

		this->_data->window.draw(_enqueueButton);
		this->_data->window.draw(_forwardButton);

		textbox1.drawTo(this->_data->window);
		monitor.drawTo(this->_data->window);
		queueScheduling.visualize(this->_data->window);

		this->_data->window.draw(this->_pauseButton);

		this->_data->window.display();
	}
}