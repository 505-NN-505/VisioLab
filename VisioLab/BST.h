#pragma once

#include <SFML/Graphics.hpp>
#include<iostream>

using namespace std;

namespace VisioLab {
    class Node
    {
    private:
        int data;
        float X, Y;
        Node* left, * right, * parent;
        sf::CircleShape shape;
    public:

        Node(int k)
        {
            shape.setRadius(35);
            shape.setFillColor(sf::Color::White);
            shape.setOutlineThickness(3);
            shape.setOutlineColor(sf::Color(31, 101, 36));
            left = right = parent = NULL;
            data = k;

        };
        ~Node()
        {
        }

        friend class BST;

        void shapeColor()
        {
            shape.setFillColor(sf::Color(249, 244, 77));
        }
    };

    class Fonts
    {
    protected:
        sf::Font font;

    public:
        Fonts()
        {
            font.loadFromFile("Resources/Fonts/ARLRDBD.TTF");
        }

        sf::Font get_Font()
        {
            return font;
        }
    };

    class BST
    {
    private:

        float x = 680, y = 200, x1, y1;
        vector<Node> node;
        vector<Node>::iterator it;
        int b = 0, n, f = 1, count = 0;
        int full = 0, found = 1;
        Node* p[32];
        Node* root = NULL;
        sf::Font font;
        vector<sf::VertexArray> L;
        sf::Text input;
        vector<Node> srch;


    public:
        BST()
        {

        };
        ~BST()
        {
        }
        void setRoot(Node* t)
        {
            root = t;
        }
        Node* getRoot()
        {
            return root;
        }
        void drawLeftNode(Node* t, int l)
        {
            switch (l)
            {
            case 0:
                x = 680;
                y = 150;
                full = 0;
                break;
            case 1:
                x = x - 300;
                y = 250;
                full = 0;
                break;
            case 2:
                x = x - 140;
                y = 350;
                full = 0;
                break;
            case 3:
                x -= 80;
                y = 450;
                full = 0;
                break;
            case 4:
                x -= 46;
                y = 550;
                full = 0;
                break;
            default:
                full = 1;
                break;
            }
        }

        void drawRightNode(Node* t, int r)
        {
            switch (r)
            {
            case 0:
                x = 680;
                y = 150;
                full = 0;
                break;
            case 1:
                x = x + 300;
                y = 250;
                full = 0;
                break;
            case 2:
                x = x + 140;
                y = 350;
                full = 0;
                break;
            case 3:
                x += 80;
                y = 450;
                full = 0;
                break;
            case 4:
                x += 46;
                y = 550;
                full = 0;
                break;
            default:
                full = 1;
                break;
            }
        }
        void setInput(sf::Text val)
        {
            input = val;
        }
        sf::Text get_input()
        {
            return input;
        }

        Node* insert(Node* curr, int key)
        {

            if (f == 1)
            {
                x = 680;
                y = 150;
                count = 0;
            }

            if (curr == NULL)
            {
                p[b] = new Node(key);


                sf::VertexArray line(sf::Lines, 2);
                line[0].position = sf::Vector2f(x1, y1);
                line[1].position = sf::Vector2f(x + 30, y + 30);
                line[1].color = sf::Color(31, 101, 36);
                if (full != 1)
                {
                    curr = p[b];

                    curr->shape.setPosition(x, y);
                    input.setPosition(x + 15, y + 15);
                    node.push_back(*curr);



                    if (root == NULL)
                    {
                        root = curr;
                    }
                    else
                        L.push_back(line);
                    b++;
                }
                f = 1;
                return curr;
            }

            if (key < curr->data)
            {

                count++;
                if (curr->left == NULL)
                {
                    x1 = x + 30;
                    y1 = y + 30;
                }
                drawLeftNode(curr, count);

                f = 0;
                curr->left = insert(curr->left, key);

            }

            else
            {
                count++;
                if (curr->right == NULL)
                {
                    x1 = x + 30;
                    y1 = y + 30;
                }
                drawRightNode(curr, count);

                f = 0;

                curr->right = insert(curr->right, key);

            }
            return curr;

        }

        void Preorder(Node* curr, int key)
        {
            Node* pp[32];
            Node* temp;
            int k = 0;
            float X, Y;
            if (curr == NULL)
            {
                if (srch.empty())
                    found = 0;
                else found = 1;
                return;
            }
            if (curr->data == key)
            {
                pp[k] = new Node(key);
                temp = pp[k];
                X = curr->shape.getPosition().x;
                Y = curr->shape.getPosition().y;
                temp->shape.setPosition(X, Y);
                temp->shapeColor();
                srch.push_back(*temp);
                k++;
            }

            Preorder(curr->left, key);
            Preorder(curr->right, key);
        }

        void Draw(sf::RenderWindow& window)
        {
            for (it = node.begin(); it != node.end(); it++)
            {
                window.draw(it->shape);
            }
        }
        void Search(sf::RenderWindow& window)
        {
            for (it = srch.begin(); it != srch.end(); it++)
            {
                window.draw(it->shape);
            }

        }
        vector<sf::VertexArray>& getL()
        {
            return L;
        }
        int getValues(int t)
        {
            if (t == 1)
                return full;
            else if (t == 2)
                return found;
        }
        void setValues(int n, int t)
        {
            if (n == 1)
                full = t;
            else
                found = t;
        }
        void clearSearch()
        {
            srch.clear();
        }

    };


    class Buttons
    {
    private:
        sf::RectangleShape rect1, rect2, box1, box2;
    public:
        Buttons()
        {
            rect1.setSize(sf::Vector2f(130, 50));
            rect2.setSize(sf::Vector2f(130, 50));
            rect1.setPosition(50, 80);
            rect2.setPosition(50, 140);
            rect1.setOutlineColor(sf::Color(31, 101, 36));
            rect2.setOutlineColor(sf::Color(31, 101, 36));

            box1.setSize(sf::Vector2f(100, 50));
            box2.setSize(sf::Vector2f(100, 50));
            box1.setPosition(200, 80);
            box2.setPosition(200, 140);
            box1.setOutlineColor(sf::Color(31, 101, 36));
            box2.setOutlineColor(sf::Color(31, 101, 36));
        }
        ~Buttons()
        {

        }
        void setcolor1(int color)
        {
            if (color == 1)
                rect1.setFillColor(sf::Color::White);
            else if (color == 2)
                rect1.setFillColor(sf::Color(80, 224, 90));
            else
                rect1.setFillColor(sf::Color(31, 101, 36));
        }

        void setcolor2(int color)
        {
            if (color == 1)
                rect2.setFillColor(sf::Color::White);
            else if (color == 2)
                rect2.setFillColor(sf::Color(80, 224, 90));
            else
                rect2.setFillColor(sf::Color(31, 101, 36));
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(rect1);
            window.draw(rect2);
        }

        void drawBox1(sf::RenderWindow& window)
        {
            window.draw(box1);
        }
        void drawBox2(sf::RenderWindow& window)
        {
            window.draw(box2);
        }

        void Box1Color(int color)
        {
            if (color == 1)
                box1.setFillColor(sf::Color::White);
            else
                box1.setFillColor(sf::Color(31, 101, 36));
        }

        void Box2Color1(int color)
        {
            if (color == 1)
                box2.setFillColor(sf::Color::White);
            else
                box2.setFillColor(sf::Color(31, 101, 36));
        }

    };
    class Texts : public Fonts
    {
    private:
        sf::String str1 = "Binary Search Tree", str2 = "Insert", str3 = "Search";
        sf::String ntc1 = "Maximum Height of this tree can be 5", ntc2 = "Node not found";
        sf::Text text1, text2, text3, notice1, notice2;


    public:
        Texts()
        {
            text1.setString(str1);
            text1.setPosition(420, 10);
            text1.setFont(font);
            text1.setCharacterSize(66);

            text1.setOutlineColor(sf::Color(31, 101, 36));
            text1.setOutlineThickness(3);

            text2.setString(str2);
            text2.setPosition(55, 85);
            text2.setFont(font);
            text2.setFillColor(sf::Color(31, 101, 36));
            text2.setCharacterSize(32);

            text3.setString(str3);
            text3.setPosition(55, 145);
            text3.setFont(font);
            text3.setFillColor(sf::Color(31, 101, 36));
            text3.setCharacterSize(32);

            notice1.setString(ntc1);
            notice1.setPosition(700, 650);
            notice1.setFont(font);
            notice1.setFillColor(sf::Color(58, 199, 49));
            notice1.setCharacterSize(32);

            notice2.setString(ntc2);
            notice2.setPosition(900, 650);
            notice2.setFont(font);
            notice2.setFillColor(sf::Color(358, 199, 49));
            notice2.setCharacterSize(32);

        }
        void draw(sf::RenderWindow& window)
        {
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
        }
        void drawNotice1(sf::RenderWindow& window)
        {
            window.draw(notice1);
        }
        void drawNotice2(sf::RenderWindow& window)
        {
            window.draw(notice2);
        }

        void text2Color(int color)
        {
            if (color == 1)
                text2.setFillColor(sf::Color(31, 101, 36));
            else
                text2.setFillColor(sf::Color::White);
        }

        void text3Color(int color)
        {
            if (color == 1)
                text3.setFillColor(sf::Color(31, 101, 36));
            else
                text3.setFillColor(sf::Color::White);
        }
    };
}