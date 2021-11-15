#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <cstdlib>
#include "NodeCenter.h"
#include "LinkedListADT.h"
#include "FileManager.h"

using namespace std;

namespace VisioLab {
    class Browser : public FileManager {
    protected:
        LinkedListADT<RectangleLink> backward, forward;
        stack<string> History;
        sf::Vector2f scBack, scForward, res;
        sf::Vector2f ccBack, ccForward;
        sf::Font font;

    public:
        Browser(void);
        Browser(const sf::Vector2f& cb, const sf::Vector2f& cf, const sf::Vector2f& res, const sf::Font& f);

        ~Browser();

        void setBackwardStartingPosition(const sf::Vector2f& cb);
        void setForwardStartingPosition(const sf::Vector2f& cf);
        void setResolution(const sf::Vector2f& res);
        void setFont(const sf::Font& f);

        void load(const sf::Vector2f& cb, const sf::Vector2f& cf, const sf::Vector2f& res, const sf::Font& f);
        void resetBackward(void);
        void resetForward(void);
        int searching(const string& txt);
        int Left(void);
        int Right(void);
        const string backwardTop(void);
        const string forwardTop(void);

        void writeToDisk(void);
        void visualize(sf::RenderWindow& window);
    };
}