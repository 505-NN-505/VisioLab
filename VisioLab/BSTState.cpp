#pragma once

#include <sstream>
#include "BSTState.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "Definitions.h"

#include <iostream>

namespace VisioLab {
	BSTState::BSTState(AppDataRef data) : _data(data) {
		this->_data->ID = __bst;
	}

	void BSTState::Init() {
        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
        this->_pauseButton.setScale({ 0.3f, 0.3f });
        _pauseButton.setTexture(this->_data->assets.getTexture("Pause Button"));
        _pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width * 0.3, _pauseButton.getPosition().y);

		fnt = f.get_Font();
		val.setFont(fnt);
		val.setFillColor(sf::Color(31, 101, 36));
	}

	void BSTState::HandleInput() {
        sf::Event event;
        while (this->_data->window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                this->_data->window.close();
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::KeyPressed:
                break;
            case sf::Event::MouseButtonPressed:

                mPos.x = sf::Mouse::getPosition(this->_data->window).x;
                mPos.y = sf::Mouse::getPosition(this->_data->window).y;

                if (this->_data->input.isSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
                    this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
                }
                else if (mPos.x > 50 && mPos.x < 180 && mPos.y>80 && mPos.y < 130)
                {
                    select = 0;
                    obj.setValues(2, 1);
                    txt.text2Color(2);
                    txt.text3Color(1);
                    str1.clear();
                    val.setString(str1);
                    obj.clearSearch();
                }
                else if (mPos.x > 50 && mPos.x < 180 && mPos.y>140 && mPos.y < 190)
                {
                    select = 1;
                    obj.setValues(2, 1);
                    obj.setValues(1, 0);
                    txt.text2Color(1);
                    txt.text3Color(2);
                    str2.clear();
                    val.setString(str2);
                }
                break;

            case sf::Event::MouseButtonReleased:
                if (!select)
                {
                    bt.setcolor1(3);
                    bt.setcolor2(1);
                }
                if (select == 1)
                {
                    bt.setcolor1(1);
                    bt.setcolor2(3);
                }
                break;

            case sf::Event::MouseMoved:
                mPos.x = sf::Mouse::getPosition(this->_data->window).x;
                mPos.y = sf::Mouse::getPosition(this->_data->window).y;
                if (mPos.x > 50 && mPos.x < 180 && mPos.y>80 && mPos.y < 130)
                {

                    if (select != 0)
                        bt.setcolor1(2);
                }
                else
                {
                    if (select != 0)
                        bt.setcolor1(1);
                }

                if (mPos.x > 50 && mPos.x < 180 && mPos.y>140 && mPos.y < 190)
                {
                    if (select != 1)
                        bt.setcolor2(2);
                }
                else
                {
                    if (select != 1)
                        bt.setcolor2(1);
                }
                break;

            case sf::Event::TextEntered:

                if (event.text.unicode == 8)

                {
                    if (!select)
                    {
                        if (str1.getSize() <= 0)
                            continue;
                        str1.erase(str1.getSize() - 1, str1.getSize());
                        //  input.setString(str1);
                        //  s=input.getString().toAnsiString();

                        val.setString(str1);
                        obj.setInput(val);
                        s = val.getString().toAnsiString();
                        a = stoi(s);
                        //  val = input;
                    }
                    else if (select == 1)
                    {
                        if (str2.getSize() <= 0)
                            continue;
                        str2.erase(str2.getSize() - 1, str2.getSize());

                        text.setString(str2);
                        st = text.getString().toAnsiString();
                        b = stoi(st);
                        val.setString(str2);
                        string ss = val.getString().toAnsiString();
                    }

                }

                if (event.text.unicode == 13)
                {
                    if (select == 0)
                    {
                        a = stoi(s);
                        t = obj.insert(obj.getRoot(), a);
                        if (flag == 0)
                            obj.setRoot(t);
                        flag = 1;
                        if (!obj.getValues(1))
                            v.push_back(obj.get_input());

                        str1.clear();
                    }
                    else
                    {
                        obj.clearSearch();
                        b = stoi(st);
                        obj.Preorder(obj.getRoot(), b);
                        str2.clear();
                    }
                }
                if (event.text.unicode < 58 && event.text.unicode>43)

                {
                    if (select == 0)
                    {
                        str1 += static_cast<char>(event.text.unicode);

                        val.setString(str1);
                        obj.setInput(val);

                        s = val.getString().toAnsiString();
                    }
                    else
                    {
                        str2 += static_cast<char>(event.text.unicode);

                        text.setString(str2);
                        val.setString(str2);

                        st = text.getString().toAnsiString();
                    }
                }
            }
        }
	}

	void BSTState::Update(float dt) {

	}

	void BSTState::Draw(float dt) {
        lines = obj.getL();

        this->_data->window.clear(sf::Color::Black);
        this->_data->window.draw(text);
        val.setFillColor(sf::Color(31, 101, 36));

        if (select == 0)
            val.setPosition(210, 82);
        else
            val.setPosition(210, 142);

        for (auto& it : lines)
            this->_data->window.draw(it);

        obj.Draw(this->_data->window);
        obj.Search(this->_data->window);

        for (auto& it : v)
        {
            this->_data->window.draw(it);
        }
        bt.draw(this->_data->window);

        if (select == 0)
            bt.drawBox1(this->_data->window);
        if (select == 1)
            bt.drawBox2(this->_data->window);

        this->_data->window.draw(val);
        txt.draw(this->_data->window);

        if (obj.getValues(1) == 1)
            txt.drawNotice1(this->_data->window);
        if (obj.getValues(2) == 0)
            txt.drawNotice2(this->_data->window);
        
        this->_data->window.draw(this->_pauseButton);
        this->_data->window.display();
	}
}