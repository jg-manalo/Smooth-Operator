#pragma once
#include <SFML/Graphics.hpp>

class Car {
public:
	float height = 50;
	float width = 150;
	Car();
	sf::RectangleShape box;
	void move();
};