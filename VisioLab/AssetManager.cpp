#include "AssetManager.h"
namespace VisioLab {
	void AssetManager::LoadTexture(std::string name, std::string fileName) {
		sf::Texture texture;
		if (texture.loadFromFile(fileName)) {
			this->_textures[name] = texture;
			texture.setSmooth(true);
		}
	}

	sf::Texture& AssetManager::getTexture(std::string name) {
		return this->_textures[name];
	}

	void AssetManager::LoadFont(std::string name, std::string fileName) {
		sf::Font font;
		if (font.loadFromFile(fileName)) {
			this->_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::getFont(std::string name) {
		return this->_fonts[name];
	}
}