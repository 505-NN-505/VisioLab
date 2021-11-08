#include <SFML/Graphics.hpp>
#include "HuffmanTree.h"

#include <windows.h>
#include <mmsystem.h>

namespace VisioLab {
	HuffmanTree::HuffmanTree() : totalNode(0) {
	
	}
	HuffmanTree::~HuffmanTree() {

	}

	int HuffmanTree::getTotalNode(void) {
		return totalNode;
	}

	vector<pair<string, int>> HuffmanTree::getHuffmanString(const string& text) {
		map<char, int> freq;
		vector<pair<string, int>> res;
		for (auto it : text) {
			if (it != ' ') freq[it]++;
		}
		for (auto it : freq) {
			string str = "";
			str += it.first;
			res.push_back({ str, it.second });
		}
		return res;
	}

	void HuffmanTree::launch(sf::Font& font, const string& text) {
		initialString = text;
		vector<pair<string, int>> final = getHuffmanString(text);

		totalNode = final.size();
		pos.x = alignSorted(0, totalNode);

		huffmanNode h;
		huffList.push_back(h);

		for (auto it : final) {
			huffmanNode h(it.second, 0, pos, font, it.first);
			huffList.push_back(h);
			pos.x += 75;
		}

		pq.setHeap(huffList);
	}

	void HuffmanTree::writeToDisk(bool written) {
		if (!written) {
			for (auto it = prefixCodes.begin(); it != prefixCodes.end(); it++) {
				reverse(it->second.begin(), it->second.end());
			}
			ofstream osHuffman;
			osHuffman.open("Results/Prefix Codes.txt");
			osHuffman << "Your Message from input:\n";
			osHuffman << initialString << "\n\n";
			osHuffman << "Prefix Codes:\n";
			osHuffman << prefixCodes;
			osHuffman.close();
		}

		FileManager::writeToDisk();
		std::string nDir = "\"" + workingDir + "\\\\Results\\\\Prefix Codes.txt" + "\"";
		std::wstring stemp = std::wstring(nDir.begin(), nDir.end());

		LPCWSTR sw = stemp.c_str();
		ShellExecute(NULL, TEXT("open"), sw, NULL, NULL, SW_NORMAL);
	}

	bool HuffmanTree::huffmanCoding(void) {
		if (pq.size() > 1) {
			huffmanNode h1 = pq.top();
			pq.pop();
			huffmanNode h2 = pq.top();
			pq.pop();

			float newHeight = max(h1.getHeight(), h2.getHeight()) + 1;
			int newFrequency = h1.getFrequency() + h2.getFrequency();

			h1.fixNodePosition(0, totalNode);
			h2.fixNodePosition(h1.getNodeList().size(), totalNode);

			h1.addEdge(0, h2.getNodeList().size());
			h2.addEdge(1, h1.getNodeList().size());

			vector<CircleNode> tempv = h1.getNodeList();
			for (int i = 0; i < tempv.size(); i++) {
				prefixCodes[tempv[i].getText()].push_back('0');
			}

			tempv = h2.getNodeList();
			for (int i = 0; i < tempv.size(); i++) {
				prefixCodes[tempv[i].getText()].push_back('1');
			}

			vector<Edge> newEdgeList = h1.getEdgeList(), tempE = h2.getEdgeList();
			for (int i = 0; i < tempE.size(); i++) {
				newEdgeList.push_back(tempE[i]);
			}

			vector<CircleNode> newNodeList = h1.getNodeList(), tempN = h2.getNodeList();
			for (int i = 0; i < tempN.size(); i++) {
				newNodeList.push_back(tempN[i]);
			}

			huffmanNode final(newFrequency, newHeight, h1.getJointPosition(), newEdgeList, newNodeList);
			pq.push(final);

			return pq.size() <= 1;
		}
		else {
			return 1;
		}
	}

	void HuffmanTree::drawTo(sf::RenderWindow& window) {
		pq.drawTo(window);
	}
}