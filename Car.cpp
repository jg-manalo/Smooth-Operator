// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Car.h"
#include "dimension.h"
#include <random>
#include <cstdlib>
#include <cstdint>
#include <stdexcept>
#include <iostream>

Car::Car() : speed{ 0.f }, deltaX{ 0.f }, deltaY{ 0.f }, friction{ 32.f }, speedMultiplier{ 10.f } 
{
	
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

Car::~Car(){
	std::cout << "Car Class Destructor Invoked\n";
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

	result.x = distribution(generator);;
	result.y = -200.f;
	return result;
}

float Car::steerAction(const float& speed, float& deltaX, const float& speedMultiplier, sf::Time& deltaTime, const float& pressedA, const float& pressedD) {
	
	if (speed > 0) {
		if (pressedA)
			this->deltaX -=  (this->speed  * deltaTime.asSeconds()) / this->speedMultiplier;
		else if (pressedD)
			this->deltaX += (this->speed * deltaTime.asSeconds()) / this->speedMultiplier;
	}
	return this->deltaX;
}

float Car::accelerate(float& speed){
	this->speed += 0.5f;
	return this->speed = (this->speed > 200.f)? this->speed = 200.f : this->speed;
}

float Car::decelerate(float& speed){
	this->speed -= 0.5f;
	return this->speed = (this->speed < 0.f)? this->speed = 0.f : this->speed;
}

float Car::musicVolumeControl(float& musicVolume){
	return musicVolume = (musicVolume > 100.f) ? musicVolume = 100.f : musicVolume += 0.5f;
}
