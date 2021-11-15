#pragma once

#include "HeapState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "Definitions.h"

namespace VisioLab {
	HeapState::HeapState(AppDataRef data) : _data(data) {
		this->_data->ID = __heap;
	}

	void HeapState::Init() {
		this->_data->assets.LoadFont("ARLRDBD", ARLRDBD);
		font = this->_data->assets.getFont("ARLRDBD");
		
		textbox.load(40, sf::Color::White, true, font, { 500, 650 });

		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		_pauseButton.setTexture(this->_data->assets.getTexture("Pause Button"));
		this->_pauseButton.setScale({ 0.3f, 0.3f });
		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width * 0.3, _pauseButton.getPosition().y);

		this->_data->assets.LoadTexture("NextButton", NEXT_BUTTON);
		_nextButton.setTexture(this->_data->assets.getTexture("NextButton"));
		this->_nextButton.setScale({ 0.4f, 0.4f });
		_nextButton.setPosition(this->_data->window.getSize().x - _nextButton.getLocalBounds().width * 0.5, _nextButton.getPosition().y + 330);

		this->_data->assets.LoadTexture("Prefix Code Button", PREFIX_CODE_BUTTON);
		_getPrefixCodes.setTexture(this->_data->assets.getTexture("Prefix Code Button"));
		_getPrefixCodes.setPosition(this->_data->window.getSize().x / 2 - _getPrefixCodes.getLocalBounds().width * 0.5,
									this->_data->window.getSize().y - 120 - _getPrefixCodes.getPosition().y);

		canType = 1, textGiven = isTreeReady = isPrefixCodeGenerated = 0;
	}

	void HeapState::HandleInput() {
		sf::Event event;
		while (this->_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::BackSpace) {
					textbox.deleteChar();
				}
				if (canType && event.key.code == sf::Keyboard::Enter) {
					canType = 0;
					textGiven = 1;
					huff.launch(font, textbox.getText());

					textbox.clear();
				}
			}

			else if (canType && event.type == sf::Event::TextEntered) {
				if (event.key.code != '\b') textbox.typeOn(event);
			}

			if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			}
			if (this->_data->input.isSpriteClicked(this->_getPrefixCodes, sf::Mouse::Left, this->_data->window)) {
				// GENERATE CODES IN THE FILE
				huff.writeToDisk(isPrefixCodeGenerated);
				isPrefixCodeGenerated = 1;
			}
			if (!canType && !isTreeReady && this->_data->input.isSpriteClicked(this->_nextButton, sf::Mouse::Left, this->_data->window)) {
				isTreeReady = huff.huffmanCoding();
			}
		}
	}

	void HeapState::Update(float dt) {

	}

	void HeapState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Black);

		textbox.drawTo(this->_data->window);
		if (textGiven) {
			huff.drawTo(this->_data->window);
			this->_data->window.draw(this->_nextButton);
		}
		if (isTreeReady) this->_data->window.draw(this->_getPrefixCodes);

		this->_data->window.draw(this->_pauseButton);
		this->_data->window.display();
	}
}