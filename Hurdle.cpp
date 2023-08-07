#include "Car.h"
#include "Hurdle.h"
#include <random>
#include <array>


//randomizing location of coordinates

Hurdle::Hurdle() {
	Coordinate random = randomizer();
	this->carSkin.loadFromFile("graphics/car.png");
	this->carShape.setFillColor(sf::Color::Cyan);
	this->carShape.setSize(sf::Vector2f(100.f, 150.f));
	this->carShape.setTexture(&carSkin);
	this->carShape.setPosition(random.x, -200.f);
}