#include "Game.h"
#include "Car.h"
#include "Hurdle.h"
#include <random>
#include <array>
#include <iostream>
#include <stdexcept>

Hurdle::Hurdle()
{
	try {
		if (!carSkin.loadFromFile("graphics/car.png"))
			throw std::runtime_error("Could not load car.png");
	}
	catch (const std::exception& error) {	
		std::cerr << "Error: " << error.what();
	}
	this->carShape.setSize(sf::Vector2f(100.f, 150.f));
	this->carShape.setTexture(&carSkin);
	this->carShape.setFillColor(sf::Color::Cyan);
	Coordinate random = randomizer();
	this->carShape.setPosition(random.x, -200.f);
}

