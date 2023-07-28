#include "Hurdle.h"
#include <random>
#include <array>

//randomizing location of coordinates
Coordinate Hurdle::randomizer() {
	Coordinate result;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(0.f, 650.f);

	std::array<float, 3> yCoord = { 0.f , -100.f, -200.f };
	int selectY = std::rand() % 3;

	result.x = distribution(generator);;
	result.y = yCoord[selectY];
	return result;
}

Hurdle::Hurdle() {
	Coordinate random = randomizer();
	this->hurdle.loadFromFile("graphics/car.png");
	this->hurdleShape.setFillColor(sf::Color::Cyan);
	this->hurdleShape.setSize(sf::Vector2f(100.f, 150.f));
	this->hurdleShape.setTexture(&hurdle);
	this->hurdleShape.setPosition(random.x, random.y);
}