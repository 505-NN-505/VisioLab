#pragma once
#include <SFML/Graphics.hpp>

inline float alignMid(float out) {
	float x = 0;
	float panX = out / 2;
	float res = x + panX;
	return res;
}

template<class Inner, class Outer>
sf::Vector2f alignCenter(Inner in, Outer out) {
	float inLen = in.getLocalBounds().width;
	float outLen = out.getLocalBounds().width;
	float inHeight = in.getLocalBounds().height;
	float outHeight = out.getLocalBounds().height;

	float panX = (outLen - inLen) / 2, panY = (outHeight - inHeight) / 2;
	sf::Vector2f pos = out.getPosition();
	sf::Vector2f res = { pos.x + panX, pos.y + panY };
	return res;
}

inline float alignSorted(float index, int size) {
	float x = alignMid((float)1360);
	x -= (size / 2) * 75;
	x += (index * 75);
	return x;
}