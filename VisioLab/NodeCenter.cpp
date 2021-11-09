#include <SFML/Graphics.hpp>
#include "NodeCenter.h"

RectangleNode::RectangleNode(const sf::Font& textFont, const string& textString, int textRes, const sf::Vector2f& resolution, const sf::Vector3i& color, const sf::Color& tColor) {
	text.setFont(textFont);
	text.setString(textString);
	text.setCharacterSize(textRes);

	this->resolution = resolution;
	rect.setSize(resolution);
	rect.setFillColor(sf::Color(color.x, color.y, color.z));
	rect.setOutlineColor(tColor);
	rect.setOutlineThickness(5.0);

	drawable = text;
	string str = "";
	for (int i = 0; i < textString.size(); i++) {
		sf::Vector2f curPos = drawable.findCharacterPos(i);
		if (curPos.x <= resolution.x - 50)
			str += textString[i];
		else {
			str += "..";
			break;
		}
	}
	drawable.setString(str);
}

void RectangleNode::setFont(sf::Font& font) {
	text.setFont(font);
}

void RectangleNode::setPosition(sf::Vector2f pos) {
	rect.setPosition(pos);

	float tLen = drawable.getLocalBounds().width;
	float rLen = rect.getLocalBounds().width;
	float tHeight = drawable.getLocalBounds().height;
	float rHeight = rect.getLocalBounds().height;

	float panX = (rLen - tLen) / 2, panY = (rHeight - tHeight) / 2;
	drawable.setPosition(pos.x + panX, pos.y + panY);
}

void RectangleNode::drawNode(sf::RenderWindow& window) {
	window.draw(rect);
	window.draw(drawable);
}

const sf::RectangleShape& RectangleNode::getRec(void) {
	return rect;
}
const sf::Text& RectangleNode::getText(void) {
	return text;
}
const string RectangleNode::getContent(void) {
	string res = drawable.getString();
	return res;
}

const int RectangleNode::getValue(void) {
	string res = drawable.getString();
	string s = " ";
	if (s == res)
		return -1;
	else
		return 1;
}

void RectangleNode::setFillColor(const sf::Vector3i& color)
{
	rect.setFillColor(sf::Color(color.x, color.y, color.z));
}

void RectangleNode::set_string(const string& textString)
{
	drawable.setString(textString);
}

void RectangleNode::setTextPosition(sf::Vector2f pos)
{
	float tLen = drawable.getLocalBounds().width;
	float tHeight = drawable.getLocalBounds().height;

	float rLen = rect.getLocalBounds().width;
	float rHeight = rect.getLocalBounds().height;

	float panX = (rLen - tLen) / 2, panY = (rHeight - tHeight) / 2;
	drawable.setPosition(pos.x + panX, pos.y + panY);
}

void RectangleNode::setOutlineColor(const sf::Color& tColor)
{
	rect.setOutlineColor(tColor);
}


// member functions for Link Nodes (Doubly Linked List)

RectangleLink::RectangleLink(RectangleLink* argPrev, const RectangleNode& argInfo, RectangleLink* argNext) {
	prev = argPrev;
	R = argInfo;
	next = argNext;
}
void RectangleLink::setNext(RectangleLink* address) {
	next = address;
}
void RectangleLink::setPrev(RectangleLink* address) {
	prev = address;
}
RectangleLink* RectangleLink::getNext(void) {
	return next;
}
RectangleLink* RectangleLink::getPrev(void) {
	return prev;
}
const string RectangleLink::getData(void) {
	return R.getContent();
}
void RectangleLink::drawTo(sf::RenderWindow& window) {
	R.drawNode(window);
}


// member functions for Edge Nodes (Tree)

Edge::Edge(sf::Vector2f size = {75, 5}) {
	line.setSize(size);
	line.setFillColor(sf::Color::White);
	angle = -45.f;
	type = 0;
}

void Edge::setType(bool type) {
	this->type = type;
	angle = (!type ? -45.f : 225.f);
	line.setRotation(angle);
}

void Edge::setPosition(sf::Vector2f position) {
	line.setPosition(position);
}

bool Edge::getType(void) {
	return type;
}

sf::Vector2f Edge::getPosition(void) {
	return line.getPosition();
}

sf::Vector2f Edge::getEndPosition(void) {
	sf::Vector2f pos = line.getPosition();
	float l = line.getSize().x * (float)cos(line.getRotation() * PI / 180);
	float h = line.getSize().x * (float)sin(line.getRotation() * PI / 180);
	return { pos.x + l, pos.y + h };
}

void Edge::movePosition(sf::Vector2f delta) {
	line.move(delta);
}

void Edge::drawTo(sf::RenderWindow& window) {
	window.draw(line);
}



// member functions for Circular Shaped Nodes (Tree)

CircleNode::CircleNode(bool type = false, float radius = (float)(30), int size = 500) : type(type) {
	circle.setRadius(radius);
	circle.setPointCount(size);
	circle.setFillColor(sf::Color(61, 72, 73));
}

void CircleNode::setType(bool type) {
	this->type = type;
	if (type)
		circle.setFillColor(sf::Color(44, 44, 255));
	else
		circle.setFillColor(sf::Color(255, 7, 58));
}

void CircleNode::setPosition(sf::Vector2f position) {
	circle.setPosition(position);
	setUpperPosition(position);
}

void CircleNode::setUpperPosition(const sf::Vector2f position) {
	upperPosition.x = position.x + circle.getRadius();
	upperPosition.y = position.y + (float)2.5;
}

void CircleNode::setText(const sf::Font& font, const string& ch) {
	character.setFont(font);
	character.setCharacterSize(35);
	character.setString(ch);
	sf::Vector2f textPos = alignCenter(character, circle);
	character.setPosition(textPos);
}

sf::Vector2f CircleNode::getPosition(void) {
	return circle.getPosition();
}

sf::Vector2f CircleNode::getUpperPosition(void) {
	return upperPosition;
}

const string CircleNode::getText(void) {
	string res = character.getString();
	return res;
}

bool CircleNode::getType(void) {
	return type;
}

void CircleNode::movePosition(sf::Vector2f delta) {
	circle.move(delta);
	character.move(delta);
	setUpperPosition(circle.getPosition());
}

void CircleNode::drawTo(sf::RenderWindow& window) {
	window.draw(circle);
	window.draw(character);
}



// member functions for Huffman Tree Nodes

huffmanNode::huffmanNode() {
	freq = -1;
	height = -1;
}
huffmanNode::huffmanNode(int argFreq, float argHeight, sf::Vector2f position, const vector<Edge>& argEdgeList, const vector<CircleNode>& argNodeList) {
	freq = argFreq;
	height = argHeight;
	jointPosition = position;
	edgeList = argEdgeList;
	nodeList = argNodeList;
}

huffmanNode::huffmanNode(int argFreq, float height, sf::Vector2f position, sf::Font& font, const string& ch) {
	freq = argFreq;
	this->height = height;
	CircleNode node;
	node.setPosition(position);
	node.setText(font, ch);
	jointPosition = node.getUpperPosition();
	nodeList.push_back(node);
}

void huffmanNode::setFreq(int value) {
	freq = value;
}

void huffmanNode::setHeight(float value) {
	height = value;
}

void huffmanNode::setEdgeList(const vector<Edge>& list) {
	edgeList = list;
}

void huffmanNode::setNodeList(const vector<CircleNode>& list) {
	nodeList = list;
}

int huffmanNode::getFrequency(void) {
	return freq;
}

float huffmanNode::getHeight(void) {
	return height;
}

const vector<Edge>& huffmanNode::getEdgeList(void) {
	return edgeList;
}

const vector<CircleNode>& huffmanNode::getNodeList(void) {
	return nodeList;
}

sf::Vector2f huffmanNode::getPosition(void) {
	return nodeList[0].getPosition();
}

sf::Vector2f huffmanNode::getJointPosition(void) {
	return jointPosition;
}

void huffmanNode::fixPosition(float delta) {
	moveJointPosition(delta);
	for (int i = 0; i < (int)nodeList.size(); i++) {
		nodeList[i].movePosition({ delta, 0 });
	}
	for (int i = 0; i < (int)edgeList.size(); i++) {
		edgeList[i].movePosition({ delta, 0 });
	}
}

void huffmanNode::fixNodePosition(float weight, int totalNodes) {
	float oldX = getPosition().x;
	float newX = alignSorted(weight, totalNodes);
	fixPosition(newX - oldX);
}

void huffmanNode::moveJointPosition(float delta) {
	jointPosition.x += delta;
}

void huffmanNode::addEdge(bool type, float coef) {
	Edge e1({ coef * 53, 5 });
	e1.setPosition(jointPosition);
	e1.setType(type);
	if (edgeList.empty()) {
		nodeList.front().setType(type);
	}
	edgeList.push_back(e1);
	jointPosition = e1.getEndPosition();
}

void huffmanNode::drawTo(sf::RenderWindow& window) {
	for (auto it : edgeList) {
		it.drawTo(window);
	}
	for (auto it : nodeList) {
		it.drawTo(window);
	}
}