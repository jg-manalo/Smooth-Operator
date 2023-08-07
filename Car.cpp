// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "dimension.h"
#include "Car.h"
#include "Game.h"
#include <random>
#include <cstdlib>
#include <cstdint>

Car::Car(){
	this->carShape.setSize(sf::Vector2f(100.f, 150.f));
	this->carShape.setPosition(STARTING_PLAYER_XPOSITION, STARTING_PLAYER_YPOSITION);
}

void Car::drivingSound(){
	driveSoundBuffer.loadFromFile("sounds/broom.mp3");
	driving.setBuffer(driveSoundBuffer);
	driving.setLoop(true);
	driving.setVolume(100);
	driving.play();

}

void Car::drivingSoundPause(){
  driving.pause();
}

void Car::brakingSound(){
	brakeSoundBuffer.loadFromFile("sounds/brake.mp3");
	braking.setBuffer(brakeSoundBuffer);
	braking.setVolume(80.f);
	braking.play();
}

Coordinate Car::randomizer() {
	Coordinate result{}; //initializes default values

	//generates a random float values ranging from 0.f to positive 650.f for the X coordinate of the object
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(0.f, 650.f);

	std::array<float, 3> yCoord = { 0.f , -100.f, -200.f };
	uint32_t selectY = std::rand() % 3;

	result.x = distribution(generator);;
	result.y = yCoord[selectY];
	return result;
}

float Car::steerAction(float& speed, float& deltaX, const float& acceleration, sf::Time& deltaTime) {
	if (speed > 0) {
		if (pressedA)
			deltaX -= acceleration * deltaTime.asSeconds();
		else if (pressedD)
			deltaX += acceleration * deltaTime.asSeconds();
	}
	return deltaX;
}

float Car::accelerate(float& speed){
	speed += 0.5f;
	return speed = (speed > 150.f) ? speed = 150.f : speed;
}

bool Car::initializeCrashedSound(){
	return true;
}

bool Car::initializeCarSkin(){
	carSkin.loadFromFile("graphics/car.png");
	this->carShape.setTexture(&carSkin);
	return true;
}
