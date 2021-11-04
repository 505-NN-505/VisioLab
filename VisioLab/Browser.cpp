#include <SFML/Graphics.hpp>
#include "Browser.h"

namespace VisioLab {
    Browser::Browser(void) { }
    Browser::Browser(const sf::Vector2f& cb, const sf::Vector2f& cf, const sf::Vector2f& res, const sf::Font& f) {
        scBack = cb;
        scForward = cf;
        font = f;
        resetBackward();
        resetForward();
        this->res = res;
    }

    Browser::~Browser() {
        backward.clear();
        forward.clear();
    }

    void Browser::setBackwardStartingPosition(const sf::Vector2f& cb) {
        scBack = cb;
    }

    void Browser::setForwardStartingPosition(const sf::Vector2f& cf) {
        scForward = cf;
    }

    void Browser::setResolution(const sf::Vector2f& res) {
        this->res = res;
    }

    void Browser::setFont(const sf::Font& f) {
        font = f;
    }

    void Browser::load(const sf::Vector2f& cb, const sf::Vector2f& cf, const sf::Vector2f& res, const sf::Font& f) {
        setBackwardStartingPosition(cb);
        setForwardStartingPosition(cf);
        setResolution(res);
        setFont(f);
        resetBackward();
        resetForward();
    }

    void Browser::resetBackward(void) {
        ccBack = scBack;
    }
    void Browser::resetForward(void) {
        ccForward = scForward;
    }
    void Browser::searching(const string& txt) {
        if (!backward.inLimit()) return;
        RectangleNode newRectangle(font, txt, 35, res, { 255, 131, 0 }, sf::Color::White);
        newRectangle.setPosition(ccBack);
        RectangleLink* newNode = new RectangleLink(NULL, newRectangle, backward.top());
        backward.pushFront(newNode);
        History.push(txt);
        ccBack.y -= res.y;
        forward.clear();
        resetForward();
    }
    void Browser::Left(void) {
        if (backward.size() > 1 && forward.inLimit()) {
            RectangleNode newRectangle(font, backward.top()->getData(), 35, res, { 255, 131, 0 }, sf::Color::White);
            newRectangle.setPosition(ccForward);
            RectangleLink* newNode = new RectangleLink(NULL, newRectangle, forward.top());
            forward.pushFront(newNode);
            ccForward.y -= res.y;
            backward.popFront();
            ccBack.y += res.y;
        }
    }
    void Browser::Right(void) {
        if (!forward.empty() && backward.inLimit()) {
            RectangleNode newRectangle(font, forward.top()->getData(), 35, res, { 255, 131, 0 }, sf::Color::White);
            newRectangle.setPosition(ccBack);
            RectangleLink* newNode = new RectangleLink(NULL, newRectangle, backward.top());
            backward.pushFront(newNode);
            ccBack.y -= res.y;
            forward.popFront();
            ccForward.y += res.y;
        }
    }
    const string Browser::backwardTop(void) {
        return backward.top()->getData();
    }
    const string Browser::forwardTop(void) {
        return forward.top()->getData();
    }

    void Browser::writeToDisk(void) {
        os.open("Results/Browser's History.txt");
        os << "Search History:\n";
        os << History;
        os.close();
        // please give the local address of your prpject's Results folder
        ShellExecute(NULL, TEXT("open"), TEXT("C:\\Users\\505\\source\\repos\\SFML Practice\\SFML Practice\\Results\\Browser's History.txt"), NULL, NULL, SW_NORMAL);
    }

    void Browser::visualize(sf::RenderWindow& window) {
        backward.drawTo(window);
        forward.drawTo(window);
    }
}