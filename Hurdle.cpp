#include "Hurdle.h"
#include <random>
#include <array>

Hurdle::Hurdle(float x, float y) {
	this->hurdle.loadFromFile("graphics/car.png");
	this->hurdleShape.setSize(sf::Vector2f(100.f, 150.f));
	this->hurdleShape.setTexture(&hurdle);
<<<<<<< Updated upstream
	this->hurdleShape.setPosition(x, y);
}
=======
	this->hurdleShape.setFillColor(sf::Color::Cyan);
	this->hurdleShape.setPosition(coordinate.x, coordinate.y);
}


//randomizing location of coordinates
Coordinate Hurdle::randomizer() {
	Coordinate result;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(0.f, 600.f);

	std::array<float, 3> yCoord = { 0.f , 20.f, 40.f };
	int selectY = std::rand() % 3;

	result.x = distribution(generator);;
	result.y = yCoord[selectY];
	return result;
}

>>>>>>> Stashed changes
