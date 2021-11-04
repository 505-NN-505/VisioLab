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

        void dequeue(void)
        {
            if (backward.empty()) {
                return;
            }
            RectangleNode newRectangle(font, backward.back()->getData(), 25, res, { 255, 131, 0 }, sf::Color::White);
            newRectangle.setPosition(ccForward);
            RectangleLink* newNode = new RectangleLink(NULL, newRectangle, forward.top());
            forward.pushFront(newNode);
            ccForward.y -= res.y;
            backward.popBack();
            if (backward.empty()) {
                resetBackward();
                return;
            }
        }

        void visualize(sf::RenderWindow& window)
        {
            backward.drawTo(window);
            forward.drawTo(window);
        }
    };
}