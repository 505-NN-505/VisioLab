#pragma once
#include <memory>
#include <string>
#include <SFML\Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "Definitions.h"

namespace VisioLab {
	struct AppData {
		_DS_TYPE ID;				// ID is enum type, basically containts the unique id of DSs
		StateMachine machine;		// The App is made of different states. class StateMachine manages them.
		sf::RenderWindow window;
		AssetManager assets;		// Basically the storage class of textures
		InputManager input;			// special input class for detecting mouse or keyboard input
	};

	typedef std::shared_ptr<AppData> AppDataRef;	// a common pointer for all States

	class App {
	private:
		const float dt = 1.0f / 60.f; //framerate
		sf::Clock _clock;
		AppDataRef _data = std::make_shared<AppData>(); // for accessing different AppData in different states
		void Run();

	public:
		App(int width, int height, std::string title);

	};
}

