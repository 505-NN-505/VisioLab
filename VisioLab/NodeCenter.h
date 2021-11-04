#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "AlignmentCenter.h"
using namespace std;

const double PI = acos(-1.0);

class RectangleNode {
	sf::RectangleShape rect;
	sf::Text text, drawable;
	sf::Vector2f resolution;

public:
	RectangleNode() { }
	RectangleNode(const sf::Font& textFont, const string& textString, int textRes, const sf::Vector2f& resolution, const sf::Vector3i& color, const sf::Color& tColor);
	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);
	void setFillColor(const sf::Vector3i& color);
	void set_string(const string& textString);
	void setTextPosition(sf::Vector2f pos);
	void setOutlineColor(const sf::Color& tColor);
	void drawNode(sf::RenderWindow& window);
	const sf::RectangleShape& getRec(void);
	const sf::Text& getText(void);
	const string getContent(void);
	const int getValue(void);
};

class RectangleLink {
	RectangleLink* prev, * next;
	RectangleNode R;
public:
	RectangleLink(RectangleLink* argPrev, const RectangleNode& argInfo, RectangleLink* argNext);
	
	void setNext(RectangleLink* address);
	void setPrev(RectangleLink* address);
	
	RectangleLink* getNext(void);
	RectangleLink* getPrev(void);
	const string getData(void);
	
	void drawTo(sf::RenderWindow& window);
};

class Edge {
	sf::RectangleShape line;
	bool type;	// 0->left edge or 1->right edge
	float angle;
public:
	Edge(sf::Vector2f size);

	void setType(bool type);
	void setPosition(sf::Vector2f position);

	bool getType(void);
	sf::Vector2f getPosition(void);
	sf::Vector2f getEndPosition(void);
	void movePosition(sf::Vector2f delta);

	void drawTo(sf::RenderWindow& window);
};

class CircleNode {
	sf::CircleShape circle;
	bool type;
	sf::Font font;
	sf::Text character;
	sf::Vector2f upperPosition;

public:
	CircleNode(bool type, float radius, int size);

	void setType(bool type);
	void setPosition(sf::Vector2f position);
	void setUpperPosition(const sf::Vector2f position);
	void setText(const sf::Font& font, const string& ch);

	sf::Vector2f getPosition(void);
	sf::Vector2f getUpperPosition(void);
	const string getText(void);
	bool getType(void);
	void movePosition(sf::Vector2f delta);

	void drawTo(sf::RenderWindow& window);
};

class huffmanNode {
	int freq;
	float height;
	sf::Vector2f jointPosition;
	vector<Edge> edgeList;
	vector<CircleNode> nodeList;

public:
	huffmanNode();
	huffmanNode(int argFreq, float argHeight, sf::Vector2f position, const vector<Edge>& argEdgeList, const vector<CircleNode>& argNodeList);
	huffmanNode(int argFreq, float height, sf::Vector2f position, sf::Font& font, const string& ch);

	void setFreq(int value);
	void setHeight(float value);
	void setEdgeList(const vector<Edge>& list);
	void setNodeList(const vector<CircleNode>& list);

	int getFrequency(void);
	float getHeight(void);
	const vector<Edge>& getEdgeList(void);
	const vector<CircleNode>& getNodeList(void);
	sf::Vector2f getPosition(void);
	sf::Vector2f getJointPosition(void);
	
	void fixPosition(float delta);
	void fixNodePosition(float weight, int totalNodes);
	void moveJointPosition(float delta);

	void addEdge(bool type, float coef);
	void drawTo(sf::RenderWindow& window);
};