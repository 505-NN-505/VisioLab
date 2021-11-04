#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "App.h"
#include "BST.h"

namespace VisioLab {
	class BSTState : public State {
	private:
		AppDataRef _data;
        vector<sf::Text> v;
        sf::Font fnt;

        Fonts f;
        sf::Sprite _pauseButton;

        int a, b, c = 0, select = 2;
        string s, st;
        char ch1;
        sf::Text val;
        vector<sf::VertexArray> lines;

        BST obj;
        Node* t;
        Buttons bt;
        Texts txt;
        sf::Vector2i mPos;
        sf::String str1, str2, notice = "Maximum height of this tree is 5";
        sf::Text text, text1;

        int flag = 0;

	public:
        BSTState(AppDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
	};
}