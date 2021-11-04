#pragma once

#include <map>
#include <SFML\Graphics.hpp>

namespace VisioLab {
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> _textures;
		std::map<std::string, sf::Font> _fonts;

	public:
		AssetManager() {}
		~AssetManager() {}
		void LoadTexture(std::string name, std::string fileName);
		sf::Texture& getTexture(std::string name);

		void LoadFont(std::string name, std::string fileName);
		sf::Font& getFont(std::string name);

	};
}

