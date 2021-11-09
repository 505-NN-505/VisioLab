#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "NodeCenter.h"
#include "LinkedListADT.h"
#include "Browser.h"
#include <sstream>

using namespace std;

namespace VisioLab {
    class HashVisio
    {
    private:
        vector <RectangleNode> v;
        sf::Vector2f sc, cc;    //starting coordinate & current coordinate
        sf::Vector2f res;
        sf::Font font;
    public:
        HashVisio(void) { }
        ~HashVisio()
        {
            //  backward.clear();
            //  forward.clear();
        }

        HashVisio(const sf::Vector2f& cpos,
            const sf::Vector2f& res, const sf::Font& f, const string& txt)
        {
            sc = cpos;
            cc = cpos; //starting coordinate
            font = f;
            this->res = res;
            for (int i = 0; i < 10; i++)
            {
                v.push_back(RectangleNode(font, txt, 25, res, { 255, 131, 0 }, sf::Color::Black));
                v[i].setPosition(cc);
                cc.y += res.y;
            }
        }

        void load(const sf::Vector2f& cpos,
            const sf::Vector2f& res, const sf::Font& f, const string& txt) {

            sc = cpos;
            cc = cpos; //starting coordinate
            font = f;
            this->res = res;
            for (int i = 0; i < 10; i++)
            {
                v.push_back(RectangleNode(font, txt, 25, res, { 255, 131, 0 }, sf::Color::Black));
                v[i].setPosition(cc);
                cc.y += res.y;
            }
        }


        void visualize(sf::RenderWindow& window)
        {
            for (int i = 0; i < 10; i++)
                v[i].drawNode(window);
        }

        string linearProbing(const string& txt, sf::RenderWindow& window)
        {
            stringstream geek(txt);
            int value = 0;
            geek >> value;
            string s = to_string(value);
            int i = 0, count = 1;
            int id = (value + i) % 10;
            while (v[id].getValue() != -1)
            {
                v[id].setFillColor({ 220,20,60 });
                count++;
                i++;
                id = (value + i) % 10;
                if (count > 6)
                {
                    return "input abondoned!";
                }
            }
            v[id].set_string(s);
            v[id].setTextPosition({ sc.x , sc.y + res.y * id });
            v[id].setOutlineColor(sf::Color::White);
            string s1 = "index: " + to_string(id);
            return s1;
        }

    };
}