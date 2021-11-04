#pragma once

#include<iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "NodeCenter.h"
#include "HeapADT.h"
#include "FileManager.h"

using namespace std;

namespace VisioLab {
	class HuffmanTree : public FileManager {
		vector<huffmanNode> huffList;
		prio_queue<huffmanNode> pq;
		string initialString, compatibleString;
		map<string, string> prefixCodes;
		sf::Vector2f pos = { 0.f, 500.f };
		int totalNode;

	public:
		HuffmanTree();
		~HuffmanTree();

		int getTotalNode(void);
		vector<pair<string, int>> getHuffmanString(const string& text);
		void launch(sf::Font& font, const string& text);
		bool huffmanCoding(void);
		void writeToDisk(bool written);
		void drawTo(sf::RenderWindow& window);
	};
}