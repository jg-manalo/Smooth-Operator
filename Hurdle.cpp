#include "Hurdle.h"

Hurdle::Hurdle(float x, float y) {
	this->hurdle.loadFromFile("graphics/car.png");
	this->hurdleShape.setSize(sf::Vector2f(100.f, 150.f));
	this->hurdleShape.setTexture(&hurdle);
	this->hurdleShape.setPosition(x, y);
}