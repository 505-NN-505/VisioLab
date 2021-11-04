#include "App.h"
#include "LogoState.h"

namespace VisioLab {
	App::App(int width, int height, std::string title) {
		_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
		
		// adding the first logo scene on the stack
		_data->machine.AddState(StateRef(new LogoState(this->_data)));
		
		this->Run();
	}
	void App::Run() {
		float newTime, frameTime, interpolation;
		float currentTime = this->_clock.getElapsedTime().asSeconds(); // amount of time since clock stated
		float accumulator = 0.0f;

		// the loop that keeps the window running 
		while (this->_data->window.isOpen()) {
			this->_data->machine.ProcessSateChanges(); // process each state changes, details in StateMachine

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if(frameTime > 0.25f) {
				frameTime = 0.25f;
			}
			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt) {
				this->_data->machine.getActiveState()->HandleInput(); 
				this->_data->machine.getActiveState()->Update(dt);
				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->_data->machine.getActiveState()->Draw(interpolation);
		}
	}
}