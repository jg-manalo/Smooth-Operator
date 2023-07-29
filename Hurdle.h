#pragma once
#include <SFML/Graphics.hpp>

struct Coordinate {
	float x;
	float y;
};

class Hurdle{
public:
	Hurdle();
	sf::Texture hurdle;
	sf::RectangleShape hurdleShape;
public:
	Coordinate randomizer();
};

