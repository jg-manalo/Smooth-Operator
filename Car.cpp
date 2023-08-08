// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Car.h"
#include "dimension.h"
#include <random>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <array>

Car::Car() : speed{ 0.f }, deltaX{ 0.f }, deltaY{ 0.f }, friction{ 32.f }, acceleration{ 10.f } {
	
	try {
		if (!carSkin.loadFromFile("graphics/car.png"))
			throw std::runtime_error("Could not load car.png");

		if (!crashedSoundBuffer.loadFromFile("sounds/undertaker.mp3"))
			throw std::runtime_error("Could not load undertaker.mp3");

		if (!driveSoundBuffer.loadFromFile("sounds/broom.mp3"))
			throw std::runtime_error("Could not load broom.mp3");

		if (!brakeSoundBuffer.loadFromFile("sounds/brake.mp3"))
			throw std::runtime_error("Could not load brake.mp3");
	}
	catch (const std::exception& error) {
		std::cerr << "Error: " << error.what();
	}

	this->carShape.setPosition(STARTING_PLAYER_XPOSITION, STARTING_PLAYER_YPOSITION);
	this->carShape.setSize(sf::Vector2f(100.f, 150.f));
	this->carShape.setTexture(&carSkin);

	this->drivingSound.setBuffer(driveSoundBuffer);
	this->brakingSound.setBuffer(brakeSoundBuffer);
	this->crashedSound.setBuffer(crashedSoundBuffer);

}


void Car::drivingSoundFX(){
	this->drivingSound.setLoop(true);
	this->drivingSound.setVolume(100);
	this->drivingSound.play();

}

void Car::drivingSoundPauseFX(){
  drivingSound.pause();
}

void Car::brakingSoundFX(){
	this->brakingSound.setBuffer(brakeSoundBuffer);
	this->brakingSound.setVolume(80.f);
	this->brakingSound.play();
}

void Car::crashedSoundFX(){
	this->crashedSound.play();
}

Coordinate Car::randomizer() {
	Coordinate result{}; //initializes default values

	//generates a random float values ranging from 0.f to positive 650.f for the X coordinate of the object
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(0.f, 650.f);

	std::array<float, 3> yCoordinate = { 0.f , -100.f, -200.f };
	uint32_t selectY = std::rand() % 3;

	result.x = distribution(generator);;
	result.y = yCoordinate[selectY];
	return result;
}

float Car::steerAction(const float& speed, float& deltaX, const float& acceleration, sf::Time& deltaTime, const float& pressedA, const float& pressedD) {
	
	if (speed > 0) {
		if (pressedA)
			deltaX -=  (speed  * deltaTime.asSeconds()) / acceleration;
		else if (pressedD)
			deltaX += (speed * deltaTime.asSeconds()) / acceleration;
	}
	return deltaX;
}

float Car::accelerate(float& speed){
	speed += 0.5f;
	return speed = (speed > 350.f) ? speed = 350.f : speed;
}

float Car::decelerate(float& speed){
	speed -= 0.5f;
	return speed = (speed < 0.f)? speed = 0.f : speed;
}

float Car::musicVolumeControl(float& musicVolume){
	musicVolume += 0.5f;
	return musicVolume = (musicVolume > 100.f) ? musicVolume = 100.f : musicVolume;
}
