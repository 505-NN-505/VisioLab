#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "NodeCenter.h"
#include "LinkedListADT.h"
#include "Browser.h"

using namespace std;

namespace VisioLab {
    class QueueVisio : public Browser
    {
    public:
        void enqueue(const string& txt)
        {
            RectangleNode newRectangle(font, txt, 25, res, { 255, 131, 0 }, sf::Color::White);
            newRectangle.setPosition(ccBack);

            RectangleLink* newNode = new RectangleLink(NULL, newRectangle, backward.top());
            backward.pushFront(newNode);
            ccBack.y += res.y;
        }

        bool dequeue(void)
        {
            if (backward.empty()) {
                return 0;
            }
            RectangleNode newRectangle(font, backward.back()->getData(), 25, res, { 255, 131, 0 }, sf::Color::White);
            newRectangle.setPosition(ccForward);
            RectangleLink* newNode = new RectangleLink(NULL, newRectangle, forward.top());
            forward.pushFront(newNode);
            ccForward.y -= res.y;
            backward.popBack();
            if (backward.empty()) {
                resetBackward();
                return 1;
            }
            return 1;
        }

        void visualize(sf::RenderWindow& window)
        {
            backward.drawTo(window);
            forward.drawTo(window);
        }
    };
}